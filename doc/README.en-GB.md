# Documentation Notes (British English)

## Scope

This document describes repository-specific documentation for the macOS fork.
It does not replace the full WSJT-X user guide under `doc/user_guide/en/`.

## Current Release Context

- Latest stable release: `v1.0.7`
- Compatibility target: macOS Sequoia (15.x) + Tahoe (26.x)

## Key Changes in v1.0.7

- Main window title now includes fork attribution and fork release version.
- Build system includes `FORK_RELEASE_VERSION`, and release automation passes
  the release tag into the app title.
- DMG root content was cleaned to remove legacy WSJT-X installer files and to
  ship FT2-specific notes (`ReadMe_FT2.txt`).
- Skip Tx1 discoverability improved with explicit tooltips and status feedback.

## Build and Runtime Notes

### Build tree

Primary build output:

- `build/ft2.app/Contents/MacOS/ft2`

Helper executables expected beside it:

- `build/ft2.app/Contents/MacOS/jt9`
- `build/ft2.app/Contents/MacOS/wsprd`

The CMake configuration in this fork copies helper executables into the app
bundle after building `ft2`.

### Shared memory

FT2 requires a shared-memory segment around 48 MB.

Useful checks:

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

### macOS installer package

Release packages include a `.pkg` installer that applies shared-memory
sysctl settings automatically to avoid startup failures on systems where
`kern.sysv.shmmax` is too low by default.

### If installer launch is blocked by Gatekeeper

Use `System Settings` -> `Privacy & Security` -> `Open Anyway` for the blocked
pkg, then confirm with password/Touch ID.

You can also right-click the pkg in Finder and choose `Open`.

## User-facing Fork Attribution

Fork attribution is shown in:

- main window title (via `program_title()`);
- About dialogue text.

## Changelog and Upstream Documentation

- Fork changelog: `CHANGELOG.md`
- Upstream user guide sources: `doc/user_guide/en/`
