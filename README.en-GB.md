# Decodium 3 FT2 (macOS Fork)

Fork maintained by **Salvatore Raccampo 9H1SR**.

## Project Description

This project is a macOS-oriented fork of Decodium 3 FT2 / WSJT-X based code.
It includes practical fixes for modern macOS builds and runtime behaviour:

- shared-memory diagnostics and reliability improvements;
- helper subprocess packaging (`jt9`, `wsprd`) inside `ft2.app`;
- guidance and files for FT2 + JTDX shared-memory coexistence on macOS.

## Current Baseline

- Source branch: `master`
- Initial tagged baseline in this fork: `v1.0`

## Quick Start (macOS)

```bash
cmake -S . -B build
cmake --build build -j8
open build/ft2.app
```

## Release Automation

Use the local release script:

```bash
scripts/release-macos.sh v1.0.3 --publish --repo elisir80/decodium3-build-macos
```

The release process now also generates a macOS installer package (`.pkg`) that:

- installs `ft2.app` into `/Applications`;
- installs and loads `com.ft2.jtdx.sysctl.plist` in `/Library/LaunchDaemons`;
- applies shared-memory sysctl values required by FT2 (`shmmax`/`shmall`).

## If macOS blocks the PKG

If Gatekeeper blocks the installer (`cannot be opened because Apple cannot
check it for malicious software`), use:

1. Open `System Settings` -> `Privacy & Security`.
2. Scroll to the Security section and find the message about the blocked pkg.
3. Click `Open Anyway`.
4. Confirm with your password/Touch ID.
5. Re-open the pkg installer.

Alternative method:

1. In Finder, right-click the `.pkg` file.
2. Click `Open`.
3. Confirm `Open` in the warning dialog.

Terminal fallback (advanced users only):

```bash
xattr -dr com.apple.quarantine /path/to/decodium3-ft2-v1.0.3-macos-arm64.pkg
open /path/to/decodium3-ft2-v1.0.3-macos-arm64.pkg
```

## Shared Memory on macOS

If you see errors about shared memory size limits, check:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Use the provided coexistence plist when FT2 and JTDX are both installed:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`
- `Darwin/ft2-pkg-postinstall.sh`

## Documentation

Detailed project notes are available in:

- `doc/README.en-GB.md`
- `doc/README.it.md`

## Licence

The project remains under GPLv3 terms inherited from upstream WSJT-X/Decodium
components. See licensing material in the source tree.
