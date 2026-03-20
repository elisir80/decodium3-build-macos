# Decodium v3.0 SE "Raptor" - Fork 9H1SR 1.5.2

This repository contains the macOS and Linux AppImage fork of Decodium 3 FT2, with FT2/FT4/FT8 runtime fixes, AutoCQ hardening, FT2 decoder updates from upstream, startup audio recovery, updater support, web-app parity controls, complete UI translations, and Decodium certificate tooling maintained in this tree.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Current fork release: `1.5.2`
- Update cycle: `1.5.1 -> 1.5.2`
- Upstream sync baseline: `2603182239`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Highlights (`1.5.1 -> 1.5.2`)

- FT2 / FT4 / FT8 runtime correctness:
- hardened late-signoff, late-final-ack, stale-partner, retry, and direct-reply paths across standard QSO flows so completed QSOs log correctly and do not loop on `73` / `RR73`.
- restored the active-QSO lock used by `Wait Features + AutoSeq` in FT4/FT8 so a running QSO is not interrupted by queued calling logic.
- fixed stale callsign/report reuse when AutoCQ moves from CQ to a new direct caller or from one queued station to the next.
- FT2 protocol and decoder work:
- aligned FT2 decoder code to the dedicated upstream FT2 LDPC path and refreshed FT2 bitmetrics support.
- completed the FT2 `2 msg / 3 msg / 5 msg` flow, including `Quick QSO`, mixed-mode TU handling, and current FT2 short-QSO routing.
- hidden FT2 async/triggered decoder tags (`T`, `aN`) from decode panes and collapsed async/sync duplicates into one logical decode.
- Audio / UI / remote control:
- strengthened startup and wake-from-sleep RX-audio recovery so monitor-on now triggers health checks and automatic reopen of streams if audio stays silent.
- brought the web app/dashboard closer to desktop parity with `Manual TX`, `Speedy`, `D-CW`, async card, `Quick QSO`, and `2/3/5 msg` controls.
- completed all bundled UI translation files so menu, popup, and in-program strings no longer ship with unfinished gaps.
- Platform / tooling:
- added Decodium certificate loading/autoload/status plus the local `tools/generate_cert.py` generator.
- kept the internal updater and refined it to open the best matching macOS/Linux asset directly.
- centralised release versioning through `fork_release_version.txt` so local builds, workflows, and GitHub releases stay aligned.
- Map / identity:
- fixed stale or fake live-map links while returning to CQ or transmitting plain CQ.
- aligned PSK Reporter identity to the exact application title string.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (best effort / experimental)
- Linux x86_64 AppImage

## Release Assets

- `decodium3-ft2-1.5.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage.sha256.txt`

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
- network access recommended for NTP, DX Cluster, PSK Reporter, updater, and online station workflows

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
- Release notes (EN/IT/ES): [RELEASE_NOTES_1.5.2.md](RELEASE_NOTES_1.5.2.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release body (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_1.5.2.md](doc/GITHUB_RELEASE_BODY_1.5.2.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
