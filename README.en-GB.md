# Decodium 3 FT2 (macOS Fork)

Fork maintained by **Salvatore Raccampo 9H1SR**.

## Project Description

This repository is a macOS-focused Decodium/WSJT-X fork with runtime hardening,
security fixes, and release automation for:

- Apple Silicon Tahoe (26.x)
- Apple Silicon Sequoia (15.x)
- Apple Intel Sequoia (15.x)
- Apple Intel Monterey (12.x, experimental best-effort)
- Linux x86_64 AppImage

## Current Baseline

- Source branch: `master`
- Latest stable release: `v1.3.7`
- App bundle/executable: `ft2.app` / `ft2`

## Key Notes for v1.3.7

- Added interactive world-map contact selection with marker highlight and DX call/grid propagation.
- Added configuration toggle for map click behavior (`Map: single click starts Tx`).
- Added persistent visibility control for `View -> World Map`.
- Added new `Ionospheric Forecast` tool window (HamQSL XML + sun image, timed refresh).
- Added new `DX Cluster` tool window (live spots, current-band context, mode filter).
- Improved world-map day/night rendering and end-of-QSO path cleanup.
- Improved compact/two-row top-control layout behavior on small displays.
- Decode timing reliability fix: sequence start timestamp is captured at data ingest before decode.
- Cross-thread reliability improvement for modulator state signals via explicit Qt metatype registration.
- Default UI style set to `Fusion` for consistent rendering across macOS variants.
- Removed hardcoded legacy revision suffix source to keep PSKReporter `Using:` branding clean.
- `.pkg` remains unnecessary; release line stays on DMG/ZIP/SHA256 for macOS plus AppImage/SHA256 for Linux.

## Quick Start (macOS)

```bash
cmake -S . -B build -DFORK_RELEASE_VERSION=v1.3.7
cmake --build build -j8
./build/ft2.app/Contents/MacOS/ft2
```

## Release Automation

Local release script:

```bash
scripts/release-macos.sh v1.3.7 --publish --repo elisir80/decodium3-build-macos
```

Per-platform suffix example:

```bash
scripts/release-macos.sh v1.3.7 --compat-macos 15.0 --asset-suffix macos-sequoia-arm64
```

Generated assets:

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`

Note: `.pkg` is no longer required for shared-memory sysctl setup in this fork release flow.

## Linux Minimum Requirements

- Architecture: `x86_64` (64-bit)
- CPU: dual-core 2.0 GHz or better
- RAM: 4 GB minimum (8 GB recommended)
- Storage: 500 MB free (AppImage + logs + settings)
- Runtime:
  - Linux with `glibc >= 2.35` (Ubuntu 22.04 class or newer)
  - `libfuse2` / FUSE2 support for AppImage execution
  - ALSA, PulseAudio, or PipeWire audio stack
- Station integration: CAT/audio hardware according to radio setup

## macOS Quarantine Command

If Gatekeeper blocks startup after download/install, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentation

- `README.md`
- `README.es.md`
- `RELEASE_NOTES_v1.3.7.md`
- `CHANGELOG.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.7.md`
- `doc/README.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
