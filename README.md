# Decodium v3.0 SE "Raptor" - Fork 9H1SR 1.5.1

This repository contains the macOS and Linux AppImage fork of Decodium 3 FT2, with FT2/FT4/FT8 runtime fixes, AutoCQ hardening, on-air QSO closing fixes, updater support, map cleanup, decoder sync from upstream, and Decodium certificate tooling maintained in this tree.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Current fork release: `1.5.1`
- Update cycle: `1.5.0 -> 1.5.1`
- Upstream sync baseline: `2603182239`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Highlights (`1.5.0 -> 1.5.1`)

- Internal updater:
- added in-app update checking against GitHub Releases.
- added `Help > Check for updates...`.
- the updater now opens the best matching asset directly for the running platform instead of only sending users to the generic release page.
- FT2 / FT4 / FT8 QSO completion:
- fixed multiple late-signoff and late-final-ack paths where the app could miss the final log, keep sending `73/RR73`, or fail to recover a QSO that closed late.
- fixed missed autolog cases after the local station had already sent its own signoff and the partner `73/RR73` arrived afterwards.
- improved timeout recovery so late `73/RR73` from the active partner can still log correctly instead of being mistaken for a new caller.
- AutoCQ and direct replies:
- fixed stale-partner reuse after returning to CQ, so a new direct caller no longer inherits an old DX callsign.
- fixed CQ-to-direct-reply transitions that could decode the caller but continue transmitting CQ instead of arming `Tx2`.
- fixed the first direct FT2 reply using a stale report value from the previous QSO instead of the current caller SNR.
- extended recent-work / abandoned-partner suppression to reduce duplicate rework after late or deferred QSO closure.
- World map and PSK Reporter identity:
- fixed the live map showing a fake active path while transmitting plain CQ.
- aligned the PSK Reporter program identifier to the exact title-bar string shown by the application.
- Diagnostics:
- expanded `debug.txt` tracing for direct-caller arming, late signoff recovery, stale-partner cleanup, and updater selection decisions.
- Release/process:
- local UI version, workflow defaults, asset naming, and release documents are now aligned to semantic version `1.5.1`.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (best effort / experimental)
- Linux x86_64 AppImage

## Release Assets

- `decodium3-ft2-1.5.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage.sha256.txt`

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
- network access recommended for NTP, DX Cluster, PSK Reporter, and online station workflows

## Startup Guidance

If macOS blocks startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Eseguire i seguenti comandi nel terminale:

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
- Release notes (EN/IT/ES): [RELEASE_NOTES_1.5.1.md](RELEASE_NOTES_1.5.1.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release body (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_1.5.1.md](doc/GITHUB_RELEASE_BODY_1.5.1.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
