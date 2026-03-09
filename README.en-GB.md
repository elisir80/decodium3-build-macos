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
- Latest stable release: `v1.4.2`
- App bundle/executable: `ft2.app` / `ft2`

## Key Notes for v1.4.2

This release covers the `v1.4.1 -> v1.4.2` cycle:

- LotW security hardening:
  - moved credentialed LotW download requests from URL GET to HTTPS POST body,
  - removed credential-bearing URL-style logging,
  - enforced strict redirect policy for credentialed requests (HTTPS + expected host).
- Remote web hardening:
  - LAN/WAN bind is refused when token length is below 12 characters,
  - explicit warning is shown for plaintext HTTP/WS usage on exposed binds.
- Linux stability fixes:
  - settings dialog is clamped to visible screen geometry (action buttons reachable),
  - async decode now runs with dedicated thread pool stack sizing + overlap guards.
- FT2 control consistency:
  - Async L2 defaults ON when entering FT2 and auto-disables outside FT2,
  - `Lock Tx Freq` and `Tx even/1st` are hidden (and forced OFF) in FT2.
- UI/tooling restoration:
  - `View -> Ionospheric Forecast` and `View -> DX Cluster` window actions restored.
- Web dashboard RX/TX activity:
  - TX events are preserved across refresh and initial TX transitions are now reported correctly.
- No `.pkg` installer flow (DMG/ZIP/SHA256 for macOS, AppImage/SHA256 for Linux).

## Quick Start (macOS)

```bash
cmake -S . -B build -DFORK_RELEASE_VERSION=v1.4.2
cmake --build build -j8
./build/ft2.app/Contents/MacOS/ft2
```

## Release Automation

Local release script:

```bash
scripts/release-macos.sh v1.4.2 --publish --repo elisir80/decodium3-build-macos
```

Per-platform suffix example:

```bash
scripts/release-macos.sh v1.4.2 --compat-macos 15.0 --asset-suffix macos-sequoia-arm64
```

## Hamlib in Release Builds

- macOS workflows run `brew update` and `brew upgrade hamlib` before build/package.
- Linux workflows build Hamlib from the latest official GitHub release and install it to `/usr/local` before compiling `ft2`.
- Workflow logs always print the effective Hamlib version (`rigctl --version`, `pkg-config --modversion hamlib`).

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

## Linux AppImage Launch Recommendation

To avoid issues caused by AppImage read-only filesystem mode:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## macOS Quarantine Command

If Gatekeeper blocks startup after download/install, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentation

- `README.md`
- `README.it.md`
- `README.es.md`
- `RELEASE_NOTES_v1.4.2.md`
- `CHANGELOG.md`
- `doc/GITHUB_RELEASE_BODY_v1.4.2.md`
- `doc/WEBAPP_SETUP_GUIDE.en-GB.md`
- `doc/WEBAPP_SETUP_GUIDE.it.md`
- `doc/WEBAPP_SETUP_GUIDE.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
