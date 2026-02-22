# Decodium 3 FT2 (macOS Fork)

Fork maintained by **Salvatore Raccampo 9H1SR**.

## Project Description

This project is a macOS-oriented fork of Decodium 3 FT2 / WSJT-X based code.
It includes practical fixes for modern macOS build and runtime behaviour:

- shared-memory diagnostics and reliability improvements;
- helper subprocess packaging (`jt9`, `wsprd`) inside `ft2.app`;
- FT2 + JTDX shared-memory coexistence support on macOS;
- release automation for Sequoia/Tahoe-compatible artifacts.

## Current Baseline

- Source branch: `master`
- Latest stable release: `v1.0.6`
- Compatibility target: macOS Sequoia (15.x) + Tahoe (26.x)

## What is New in v1.0.6

- Fixed a startup failure path that raised:
  `Fatal Error / Sub-process error / Failed to close orphaned jt9 process`.
- If a lingering `jt9` shared-memory segment is still valid, startup now reuses
  it instead of failing immediately.
- Safety behaviour remains strict if the existing segment size is too small.

## Quick Start (macOS)

```bash
cmake -S . -B build
cmake --build build -j8
open build/ft2.app
```

## Release Automation

Use the local release script:

```bash
scripts/release-macos.sh v1.0.6 --publish --repo elisir80/decodium3-build-macos
```

For one DMG that works on both macOS Sequoia (15.x) and Tahoe (26.x), build
with:

```bash
scripts/release-macos.sh v1.0.6 --compat-macos 15.0
```

Important: if you build locally on Tahoe with Homebrew libraries compiled with
`minos 26.0`, the compatibility check can fail by design. Use the GitHub
workflow `Release macOS (Sequoia+Tahoe)` (runner `macos-15`) to generate a
cross-version DMG and PKG.

The release process generates:

- `decodium3-ft2-<version>-macos-<arch>.dmg`
- `decodium3-ft2-<version>-macos-<arch>.zip`
- `decodium3-ft2-<version>-macos-<arch>.pkg`
- `decodium3-ft2-<version>-sha256.txt`

The macOS installer package (`.pkg`) installs `ft2.app` and configures
shared-memory sysctl values (`shmmax`/`shmall`) required for FT2/JTDX coexistence.

## If macOS Blocks the PKG

If Gatekeeper blocks the installer (`cannot be opened because Apple cannot
check it for malicious software`), use:

1. Open `System Settings` -> `Privacy & Security`.
2. Scroll to Security and find the message about the blocked pkg.
3. Click `Open Anyway`.
4. Confirm with password/Touch ID.
5. Re-open the pkg installer.

Alternative method:

1. In Finder, right-click the `.pkg` file.
2. Click `Open`.
3. Confirm `Open` in the warning dialogue.

Terminal fallback (advanced users only):

```bash
xattr -dr com.apple.quarantine /path/to/decodium3-ft2-<version>-macos-arm64.pkg
open /path/to/decodium3-ft2-<version>-macos-arm64.pkg
```

## Shared Memory on macOS

If you see errors about shared-memory size limits, check:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Recommended coexistence profile (FT2 + JTDX):

- `kern.sysv.shmmax=104857600`
- `kern.sysv.shmall=51200`

Reference files:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`
- `Darwin/ft2-pkg-postinstall.sh`

## Changelog

See `CHANGELOG.md`.

## Documentation

Detailed fork notes are available in:

- `doc/README.en-GB.md`
- `doc/README.it.md`

## Licence

The project remains under GPLv3 terms inherited from upstream WSJT-X/Decodium
components. See licensing material in the source tree.
