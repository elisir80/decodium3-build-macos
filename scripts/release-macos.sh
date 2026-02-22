#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage:
  scripts/release-macos.sh <version> [--publish] [--repo owner/repo]
                                 [--compat-macos 15.0] [--skip-compat-check]
                                 [--codesign-identity "-"]

Examples:
  scripts/release-macos.sh v1.0.3
  scripts/release-macos.sh v1.0.3 --publish --repo elisir80/decodium3-build-macos

What it does:
  1) Configures the project in ./build
  2) Builds the project in ./build
  3) Generates macOS DMG via CPack (DragNDrop)
  4) Verifies bundle compatibility (absolute deps + minos threshold)
  5) Re-signs the app bundle (ad-hoc by default) and creates a macOS installer
     PKG that installs ft2.app and configures
     shared-memory sysctl values for FT2/JTDX coexistence
  6) Creates versioned assets:
       decodium3-ft2-<version>-macos-<arch>.dmg
       decodium3-ft2-<version>-macos-<arch>.zip
       decodium3-ft2-<version>-macos-<arch>.pkg
       decodium3-ft2-<version>-sha256.txt
  7) Optionally creates/updates the GitHub release when --publish is used
EOF
}

if [[ $# -lt 1 ]]; then
  usage
  exit 1
fi

VERSION_RAW="$1"
shift

VERSION="$VERSION_RAW"
if [[ "$VERSION" != v* ]]; then
  VERSION="v${VERSION}"
fi

PUBLISH=0
REPO="elisir80/decodium3-build-macos"
COMPAT_MACOS="15.0"
SKIP_COMPAT_CHECK=0
CODESIGN_IDENTITY="${CODESIGN_IDENTITY:--}"

version_gt() {
  local lhs="$1"
  local rhs="$2"
  [[ "$(printf '%s\n%s\n' "$lhs" "$rhs" | sort -V | tail -n1)" == "$lhs" && "$lhs" != "$rhs" ]]
}

check_bundle_compatibility() {
  local app_bundle="$1"
  local compat_macos="$2"
  local has_absolute_deps=0
  local has_bad_minos=0

  while IFS= read -r file_path; do
    if ! file "$file_path" | grep -q "Mach-O"; then
      continue
    fi

    while IFS= read -r dep_path; do
      case "$dep_path" in
        /opt/*|/usr/local/*|/Users/*)
          echo "error: absolute runtime dependency in bundle:"
          echo "  ${file_path} -> ${dep_path}"
          has_absolute_deps=1
          ;;
      esac
    done < <(otool -L "$file_path" | awk 'NR>1 {print $1}')

    local minos
    minos="$(otool -l "$file_path" | awk '/LC_BUILD_VERSION/{s=1} s && $1=="minos"{print $2; exit}')"
    if [[ -n "$minos" ]] && version_gt "$minos" "$compat_macos"; then
      echo "error: incompatible min deployment target:"
      echo "  ${file_path} -> minos ${minos} (required <= ${compat_macos})"
      has_bad_minos=1
    fi
  done < <(find "$app_bundle" -type f)

  if [[ "$has_absolute_deps" -ne 0 || "$has_bad_minos" -ne 0 ]]; then
    return 1
  fi
  return 0
}

sign_app_bundle() {
  local app_bundle="$1"
  local sign_identity="$2"

  if ! command -v codesign >/dev/null 2>&1; then
    echo "error: codesign tool not found"
    return 1
  fi

  echo "Signing app bundle with identity: ${sign_identity}"
  codesign --force --deep --sign "${sign_identity}" --timestamp=none "${app_bundle}" >/dev/null
  codesign --verify --deep --strict --verbose=2 "${app_bundle}" >/dev/null
}

create_dmg_from_staged_root() {
  local staged_root="$1"
  local out_dmg="$2"
  local vol_name="$3"
  local tmp_dmg="${out_dmg}.tmp.dmg"

  rm -f "${out_dmg}" "${tmp_dmg}"
  hdiutil create \
    -volname "${vol_name}" \
    -srcfolder "${staged_root}" \
    -fs HFS+ \
    -format UDZO \
    "${tmp_dmg}" >/dev/null
  mv -f "${tmp_dmg}" "${out_dmg}"
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --publish)
      PUBLISH=1
      shift
      ;;
    --repo)
      if [[ $# -lt 2 ]]; then
        echo "error: --repo requires a value"
        exit 1
      fi
      REPO="$2"
      shift 2
      ;;
    --compat-macos)
      if [[ $# -lt 2 ]]; then
        echo "error: --compat-macos requires a value"
        exit 1
      fi
      COMPAT_MACOS="$2"
      shift 2
      ;;
    --skip-compat-check)
      SKIP_COMPAT_CHECK=1
      shift
      ;;
    --codesign-identity)
      if [[ $# -lt 2 ]]; then
        echo "error: --codesign-identity requires a value"
        exit 1
      fi
      CODESIGN_IDENTITY="$2"
      shift 2
      ;;
    *)
      echo "error: unknown argument: $1"
      usage
      exit 1
      ;;
  esac
done

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
APP_NAME="ft2.app"
PREFIX="decodium3-ft2"
ARCH="$(uname -m)"
PKG_IDENTIFIER="com.9h1sr.decodium3.ft2"
PKG_POSTINSTALL="${ROOT_DIR}/Darwin/ft2-pkg-postinstall.sh"
PKG_SYSCTL_PLIST="${ROOT_DIR}/Darwin/com.ft2.jtdx.sysctl.plist"

if [[ "$ARCH" == "x86_64" ]]; then
  ARCH_LABEL="x86_64"
elif [[ "$ARCH" == "arm64" || "$ARCH" == "aarch64" ]]; then
  ARCH_LABEL="arm64"
else
  ARCH_LABEL="$ARCH"
fi

JOBS="$(sysctl -n hw.ncpu 2>/dev/null || echo 8)"

echo "[1/7] Configuring project (macOS target ${COMPAT_MACOS})..."
cmake_args=(
  -DCMAKE_BUILD_TYPE=Release
  -DCMAKE_OSX_DEPLOYMENT_TARGET="$COMPAT_MACOS"
  -DWSJT_GENERATE_DOCS=OFF
  -DWSJT_SKIP_MANPAGES=ON
  -DWSJT_BUILD_UTILS=OFF
)

# Respect externally provided CMake prefix paths (e.g. qt@5 on GitHub Actions).
if [[ -n "${CMAKE_PREFIX_PATH:-}" ]]; then
  cmake_args+=("-DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
fi

cmake \
  -S "$ROOT_DIR" \
  -B "$BUILD_DIR" \
  "${cmake_args[@]}"

echo "[2/7] Building project..."
cmake --build "$BUILD_DIR" -j"$JOBS"

echo "[3/7] Generating DMG with CPack..."
(
  cd "$BUILD_DIR"
  cpack -G DragNDrop
)

LATEST_DMG="$(cd "$BUILD_DIR" && ls -t *-Darwin.dmg 2>/dev/null | head -n1 || true)"
if [[ -z "$LATEST_DMG" ]]; then
  echo "error: no DMG produced by CPack"
  exit 1
fi
STAGED_APP="$(cd "$BUILD_DIR" && ls -td _CPack_Packages/Darwin/DragNDrop/*/ft2.app 2>/dev/null | head -n1 || true)"
if [[ -z "$STAGED_APP" ]]; then
  echo "error: unable to locate staged ft2.app from CPack output"
  exit 1
fi
STAGED_APP_ABS="${BUILD_DIR}/${STAGED_APP}"
STAGED_ROOT_ABS="$(dirname "${STAGED_APP_ABS}")"

if [[ "$SKIP_COMPAT_CHECK" -eq 0 ]]; then
  echo "[4/7] Checking bundle compatibility target macOS ${COMPAT_MACOS}..."
  if ! check_bundle_compatibility "${BUILD_DIR}/${STAGED_APP}" "$COMPAT_MACOS"; then
    echo
    echo "Bundle compatibility check failed."
    echo "Use --skip-compat-check to override (not recommended for release)."
    exit 1
  fi
else
  echo "[4/7] Skipping compatibility checks (--skip-compat-check)."
fi

DMG_OUT="${PREFIX}-${VERSION}-macos-${ARCH_LABEL}.dmg"
ZIP_OUT="${PREFIX}-${VERSION}-macos-${ARCH_LABEL}.zip"
PKG_OUT="${PREFIX}-${VERSION}-macos-${ARCH_LABEL}.pkg"
SHA_OUT="${PREFIX}-${VERSION}-sha256.txt"
PKG_VERSION="${VERSION#v}"
PKG_ROOT="${BUILD_DIR}/pkgroot-${VERSION}"
PKG_SCRIPTS_DIR="${BUILD_DIR}/pkgscripts-${VERSION}"

if [[ ! -f "$PKG_POSTINSTALL" ]]; then
  echo "error: missing postinstall script: $PKG_POSTINSTALL"
  exit 1
fi
if [[ ! -f "$PKG_SYSCTL_PLIST" ]]; then
  echo "error: missing shared-memory plist: $PKG_SYSCTL_PLIST"
  exit 1
fi

echo "[5/7] Re-signing app bundle and building macOS installer package..."
sign_app_bundle "${STAGED_APP_ABS}" "${CODESIGN_IDENTITY}"

rm -rf "$PKG_ROOT" "$PKG_SCRIPTS_DIR"
mkdir -p "${PKG_ROOT}/Applications" "$PKG_SCRIPTS_DIR"
/usr/bin/ditto "${STAGED_APP_ABS}" "${PKG_ROOT}/Applications/${APP_NAME}"
cp -f "$PKG_POSTINSTALL" "${PKG_SCRIPTS_DIR}/postinstall"
cp -f "$PKG_SYSCTL_PLIST" "${PKG_SCRIPTS_DIR}/${PKG_SYSCTL_PLIST##*/}"
chmod 755 "${PKG_SCRIPTS_DIR}/postinstall"

pkgbuild \
  --root "$PKG_ROOT" \
  --identifier "$PKG_IDENTIFIER" \
  --version "$PKG_VERSION" \
  --install-location "/" \
  --scripts "$PKG_SCRIPTS_DIR" \
  "${BUILD_DIR}/${PKG_OUT}"

echo "[6/7] Creating release assets..."
create_dmg_from_staged_root "${STAGED_ROOT_ABS}" "${BUILD_DIR}/${DMG_OUT}" "ft2"
(
  /usr/bin/ditto -c -k --sequesterRsrc --keepParent "${STAGED_APP_ABS}" "${BUILD_DIR}/${ZIP_OUT}"
  cd "$BUILD_DIR"
  shasum -a 256 "$DMG_OUT" "$ZIP_OUT" "$PKG_OUT" > "$SHA_OUT"
)

echo "Assets ready:"
ls -lh "${BUILD_DIR}/${DMG_OUT}" "${BUILD_DIR}/${ZIP_OUT}" "${BUILD_DIR}/${PKG_OUT}" "${BUILD_DIR}/${SHA_OUT}"
echo
cat "${BUILD_DIR}/${SHA_OUT}"

if [[ "$PUBLISH" -eq 1 ]]; then
  if ! command -v gh >/dev/null; then
    echo "error: gh CLI not found. Install it first (brew install gh)."
    exit 1
  fi

  NOTES_FILE="$(mktemp)"
  cat >"$NOTES_FILE" <<EOF
# Decodium 3 FT2 ${VERSION} (macOS)

## English (UK)
Incremental release for the macOS fork.

This release adds an installable macOS package (`.pkg`) that configures
shared-memory sysctl values automatically (`kern.sysv.shmmax`/`shmall`)
for reliable FT2 startup and FT2/JTDX coexistence.

Assets:
- \`${DMG_OUT}\`
- \`${ZIP_OUT}\`
- \`${PKG_OUT}\`
- \`${SHA_OUT}\`

## Italiano
Release incrementale del fork macOS.

Questa release aggiunge un pacchetto installabile macOS (`.pkg`) che
configura automaticamente i valori sysctl della memoria condivisa
(`kern.sysv.shmmax`/`shmall`) per avvio affidabile di FT2 e coesistenza
FT2/JTDX.

Asset:
- \`${DMG_OUT}\`
- \`${ZIP_OUT}\`
- \`${PKG_OUT}\`
- \`${SHA_OUT}\`
EOF

  echo "[7/7] Publishing release to ${REPO}..."
  if gh release view "$VERSION" --repo "$REPO" >/dev/null 2>&1; then
    gh release upload "$VERSION" \
      "${BUILD_DIR}/${DMG_OUT}" \
      "${BUILD_DIR}/${ZIP_OUT}" \
      "${BUILD_DIR}/${PKG_OUT}" \
      "${BUILD_DIR}/${SHA_OUT}" \
      --repo "$REPO" \
      --clobber
    gh release edit "$VERSION" --repo "$REPO" --notes-file "$NOTES_FILE"
  else
    gh release create "$VERSION" \
      "${BUILD_DIR}/${DMG_OUT}" \
      "${BUILD_DIR}/${ZIP_OUT}" \
      "${BUILD_DIR}/${PKG_OUT}" \
      "${BUILD_DIR}/${SHA_OUT}" \
      --repo "$REPO" \
      --title "Decodium 3 FT2 ${VERSION} (macOS)" \
      --notes-file "$NOTES_FILE"
  fi

  rm -f "$NOTES_FILE"
  echo "Release published."
fi
