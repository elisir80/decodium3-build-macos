#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage:
  scripts/release-macos.sh <version> [--publish] [--repo owner/repo]

Examples:
  scripts/release-macos.sh v1.0.3
  scripts/release-macos.sh v1.0.3 --publish --repo elisir80/decodium3-build-macos

What it does:
  1) Builds the project in ./build
  2) Generates macOS DMG via CPack (DragNDrop)
  3) Creates a macOS installer PKG that installs ft2.app and configures
     shared-memory sysctl values for FT2/JTDX coexistence
  4) Creates versioned assets:
       decodium3-ft2-<version>-macos-<arch>.dmg
       decodium3-ft2-<version>-macos-<arch>.zip
       decodium3-ft2-<version>-macos-<arch>.pkg
       decodium3-ft2-<version>-sha256.txt
  5) Optionally creates/updates the GitHub release when --publish is used
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

echo "[1/5] Building project..."
cmake --build "$BUILD_DIR" -j"$JOBS"

echo "[2/5] Generating DMG with CPack..."
(
  cd "$BUILD_DIR"
  cpack -G DragNDrop
)

LATEST_DMG="$(cd "$BUILD_DIR" && ls -t *-Darwin.dmg 2>/dev/null | head -n1 || true)"
if [[ -z "$LATEST_DMG" ]]; then
  echo "error: no DMG produced by CPack"
  exit 1
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

echo "[3/5] Building macOS installer package..."
rm -rf "$PKG_ROOT" "$PKG_SCRIPTS_DIR"
mkdir -p "${PKG_ROOT}/Applications" "$PKG_SCRIPTS_DIR"
/usr/bin/ditto "${BUILD_DIR}/${APP_NAME}" "${PKG_ROOT}/Applications/${APP_NAME}"
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

echo "[4/5] Creating release assets..."
cp -f "${BUILD_DIR}/${LATEST_DMG}" "${BUILD_DIR}/${DMG_OUT}"
(
  cd "$BUILD_DIR"
  /usr/bin/zip -qry "$ZIP_OUT" "$APP_NAME"
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

  echo "[5/5] Publishing release to ${REPO}..."
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
