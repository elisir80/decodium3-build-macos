# Decodium v3.0 SE "Raptor" - Fork 9H1SR 1.5.0

This repository contains the macOS and Linux AppImage fork of Decodium 3 FT2, with runtime stability fixes, FT2 protocol/QSO-flow work, AutoCQ hardening, decoder sync from upstream, and new certificate tooling maintained in this tree.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Current fork release: `1.5.0`
- Update cycle: `1.4.9 -> 1.5.0`
- Upstream sync baseline: `2603182239`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Highlights (`1.4.9 -> 1.5.0`)

- Audio startup recovery:
- added an RX health-check at startup so the app can recover automatically when audio devices are selected correctly but no RX audio arrives yet.
- when needed, Decodium now reopens the configured audio streams and re-arms monitor state instead of forcing a manual visit to Audio Preferences.
- FT8 / FT4 / FT2 QSO correctness:
- fixed final `73` handling in standard 5-message flows when the other station sends `RR73` or `73` first.
- fixed several end-of-QSO paths that could log too early, miss the final `73`, or restart CQ while stale DX state was still visible.
- live map and DX context are now cleared correctly when the QSO is closed and the station returns to CQ.
- AutoCQ stability:
- recently worked calls are now blocked consistently across all caller-selection paths, avoiding immediate duplicate QSOs with the same station.
- queue handoff now resets retry counters, reports, and QSO state before the next caller starts.
- FT8 retry accounting now counts real missed periods only, so "5 tries" means 5 actual transmit opportunities.
- added richer `debug.txt` tracing for AutoCQ partner selection, queue handoff, retry progression, and recent-work suppression.
- FT2 decoder / upstream sync:
- imported the upstream watchdog-rescue fix so a valid reply is not lost when the TX watchdog fires at the same time.
- added `lib/ft2/decode174_91_ft2.f90` and moved FT2 triggered decode to the dedicated FT2 LDPC path.
- aligned shared LDPC decoders with the upstream Normalized Min-Sum decoder refresh.
- FT2 Quick QSO and message policies:
- kept the `2 msg / 3 msg / 5 msg` selector and added a `Quick QSO` toggle as a UI alias for FT2 `2 msg`.
- aligned FT2 Quick QSO to the current short-flow schema, including mixed-mode handling and backward compatibility for older `TU` behaviour.
- certificate tooling:
- added local Decodium certificate parsing/loading, autoload from the writable data directory, and status indication in the main status bar.
- added `tools/generate_cert.py` for generating `.decodium` certificate files compatible with the in-app loader.
- Release/process:
- local UI version, workflow defaults, release naming, and GitHub release notes are now aligned to semantic version `1.5.0`.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (best effort / experimental)
- Linux x86_64 AppImage

## Release Assets

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

No `.pkg` installers are produced in this fork release line.

## Linux Minimum Requirements

Hardware:

- `x86_64` CPU
- dual-core 2.0 GHz or better
- 4 GB RAM minimum (8 GB recommended)
- at least 500 MB free disk space
- 1280x800 display or better recommended
- radio/CAT/audio hardware according to your station setup

Software:

- Linux `x86_64` with `glibc >= 2.35`
- `libfuse2` / FUSE2 support for AppImage mounting
- ALSA, PulseAudio, or PipeWire audio stack
- a desktop session capable of running Qt5 AppImages
- network access recommended for NTP, DX Cluster, and online station workflows

## Startup Guidance

If macOS blocks startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

To avoid issues caused by the AppImage read-only filesystem, it is recommended to start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Related Documentation

- English README: [README.en-GB.md](README.en-GB.md)
- Italian README: [README.it.md](README.it.md)
- Spanish README: [README.es.md](README.es.md)
- Release notes (EN/IT/ES): [RELEASE_NOTES_1.5.0.md](RELEASE_NOTES_1.5.0.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release body (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_1.5.0.md](doc/GITHUB_RELEASE_BODY_1.5.0.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
