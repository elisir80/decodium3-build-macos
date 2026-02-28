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
- Latest stable release: `v1.3.3`
- App bundle/executable: `ft2.app` / `ft2`

## Key Notes for v1.3.3

- Imported upstream Raptor features: B4 strikethrough in Band Activity, Auto CQ caller FIFO queue, TX bracket waterfall overlay, and auto `cty.dat` refresh/download policy.
- FT2 decoder tuning imported from upstream (`syncmin` adaptive profile, extended AP types, relaxed deep-search thresholds, OSD depth near `nfqso`).
- Shared memory on macOS moved to file-backed `mmap` path (`SharedMemorySegment`), reducing System V fragility.
- Hardened NTP/DT behavior and mode-specific tuning for FT2/FT4/FT8.
- CAT reconnection and startup mode-selection robustness improvements.
- Security fixes applied on TLS handling and network paths documented in changelog/release notes.
- Startup freeze/hang mitigation: expensive startup file loading moved off the main UI thread.
- CTY/grid/satellite/comments file parsing hardened with size/bounds guards and fallback recovery.
- Small-display UI responsiveness improved with automatic top-controls 2-row layout and light-theme seconds/progress visibility fixes.

## Quick Start (macOS)

```bash
cmake -S . -B build -DFORK_RELEASE_VERSION=v1.3.3
cmake --build build -j8
./build/ft2.app/Contents/MacOS/ft2
```

## Release Automation

Local release script:

```bash
scripts/release-macos.sh v1.3.3 --publish --repo elisir80/decodium3-build-macos
```

Per-platform suffix example:

```bash
scripts/release-macos.sh v1.3.3 --compat-macos 15.0 --asset-suffix macos-sequoia-arm64
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
- `RELEASE_NOTES_v1.3.3.md`
- `CHANGELOG.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.3.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
