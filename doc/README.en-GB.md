# Documentation Notes (British English)

## Scope

This document describes repository-specific documentation for the macOS fork.
It does not replace the full WSJT-X user guide under `doc/user_guide/en/`.

## Contents

- Build/runtime notes for macOS;
- shared-memory configuration expectations;
- FT2 + JTDX coexistence workflow;
- packaging behaviour relevant to this fork.

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

## User-facing Fork Attribution

Fork attribution is shown in:

- main window title (via `program_title()`);
- About dialogue text.

## Upstream Documentation

For complete operational details, use upstream user guide sources in:

- `doc/user_guide/en/`
