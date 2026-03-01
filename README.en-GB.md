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
- Latest stable release: `v1.3.5`
- App bundle/executable: `ft2.app` / `ft2`

## Key Notes for v1.3.5

- TCI binary frame parser hardening with strict header/payload bounds validation.
- TCI pseudo-sync waits refactored to avoid nested `QEventLoop::exec()` loops in `mysleep1..8`.
- Cross-thread TX waveform safety: `foxcom_.wave` now read through guarded snapshots.
- TCI C++/Fortran boundary strengthened with `kin` clamping and bounded writes.
- macOS audio path stability updates (Sequoia-safe stop path + underrun handling improvements).
- TOTP generation now uses NTP-corrected time.
- `QRegExp` migrated to `QRegularExpression` in critical runtime/network paths (`mainwindow`, `wsprnet`).
- Cloudlog/LotW transport hardening: HTTPS/TLS enforcement without insecure downgrade paths.
- UDP control packet filtering tightened in MessageClient (trusted senders + target id checks).
- ADIF/log integrity hardening with field sanitization and mutex-protected append paths.
- NTP reliability upgrades: single-server bootstrap confirmations, adaptive retry/RTT thresholds, auto fallback pin to `time.apple.com`, and consistent live status text in weak-hold states.
- Startup CTY behavior improved: immediate auto-download when missing and HTTPS source URL.
- Existing fork baseline retained: mmap shared-memory backend on macOS (no `.pkg`), startup mode/frequency alignment, and small-display UI improvements.

## Quick Start (macOS)

```bash
cmake -S . -B build -DFORK_RELEASE_VERSION=v1.3.5
cmake --build build -j8
./build/ft2.app/Contents/MacOS/ft2
```

## Release Automation

Local release script:

```bash
scripts/release-macos.sh v1.3.5 --publish --repo elisir80/decodium3-build-macos
```

Per-platform suffix example:

```bash
scripts/release-macos.sh v1.3.5 --compat-macos 15.0 --asset-suffix macos-sequoia-arm64
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
- `RELEASE_NOTES_v1.3.5.md`
- `CHANGELOG.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.5.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
