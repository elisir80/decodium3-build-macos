# Decodium 3 FT2 (macOS Fork) - v1.4.7

Fork maintained by **Salvatore Raccampo 9H1SR**.

## Project Description

This repository is a Decodium/WSJT-X fork focused on macOS and Linux packaging, FT2 runtime stability, AutoCQ reliability, and DX cluster / AutoSpot operational workflows.

Latest stable release: `v1.4.7`.

## Changes in v1.4.7 (`v1.4.6 -> v1.4.7`)

- FT2 runtime/decode hardening:
- increased FT2 async Tx guard from `100 ms` to `300 ms`.
- added FT2 false-decode rejection using `cty.dat` prefix validation.
- rewrote FT2 `TΔ` rendering through structured parsing so columns stay aligned with packed rows and variable markers.
- kept FT2 mode-marker normalization consistent when `~` appears in decode flow.
- AutoCQ/QSO sequencing:
- stronger active-partner lock so another caller cannot take over an in-progress QSO.
- missed-period logic now matches the full `5` retry budget.
- stale missed-period state is cleared as soon as a valid caller/partner reply advances the QSO.
- after a confirmed partner `73`, AutoCQ returns to CQ instead of sending an extra `RR73`.
- AutoSpot / DX Cluster / web dashboard:
- new Settings page section for AutoSpot endpoint (`host`, `port`, enabled flag).
- DX Cluster window now queries a configurable DxSpider telnet node instead of the fixed HamQTH source.
- improved telnet prompt negotiation, `UNSET/DX` quiet fetch, login fallback, and submit/verify diagnostics in `autospot.log`.
- dashboard/web app now exposes AutoSpot toggle, better command/auth feedback, and more stable current-mode preset save/apply behavior.
- Desktop/runtime fixes:
- `Astronomical Data` menu action now unchecks when the window is closed with the titlebar `X`.
- Linux settings dialog keeps oversized tab pages scrollable with bottom action buttons still reachable.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (experimental / best effort)
- Linux x86_64 AppImage

## Linux Minimum Requirements

- Architecture: `x86_64` (64-bit)
- CPU: dual-core 2.0 GHz or better
- RAM: 4 GB minimum (8 GB recommended)
- Storage: at least 500 MB free for AppImage + logs/settings
- Runtime/software:
- Linux with `glibc >= 2.35` (Ubuntu 22.04 class or newer)
- `libfuse2` / FUSE2 support
- ALSA, PulseAudio, or PipeWire audio stack
- Station integration: CAT/audio hardware according to radio setup

## Linux AppImage Launch Recommendation

To avoid issues caused by the AppImage read-only filesystem, Decodium should be started by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## macOS Quarantine Command

If Gatekeeper blocks startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Build and Run (local)

```bash
cmake --build build -j6
./build/ft2.app/Contents/MacOS/ft2
```

## Documentation

- [README.md](README.md)
- [README.it.md](README.it.md)
- [README.es.md](README.es.md)
- [RELEASE_NOTES_v1.4.7.md](RELEASE_NOTES_v1.4.7.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](doc/GITHUB_RELEASE_BODY_v1.4.7.md)
- [doc/README.en-GB.md](doc/README.en-GB.md)
- [doc/README.it.md](doc/README.it.md)
- [doc/README.es.md](doc/README.es.md)

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
