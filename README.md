# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.7

This repository contains the macOS-focused fork build of Decodium 3 FT2, including Linux AppImage release flow and the current DxSpider-based AutoSpot/DX Cluster integration.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Fork release: `v1.4.7`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Scope (`v1.4.6 -> v1.4.7`)

- FT2 runtime/decode hardening:
- increased the FT2 async Tx guard from `100 ms` to `300 ms` to stabilize first-Tx timing.
- added FT2 false-decode rejection based on `cty.dat` prefix validation.
- rewrote FT2 `TΔ` rendering with structured parsing so columns no longer drift when packed rows or variable mode markers are present.
- kept FT2 marker normalization consistent when `~` appears in decode flow.
- AutoCQ/QSO flow hardening:
- strengthened active-partner lock so in-progress QSOs are not hijacked by other callers.
- aligned missed-period handling to the real retry budget (`5` attempts).
- reset stale missed-period state when a valid caller/partner reply advances the QSO.
- after confirmed partner `73`, AutoCQ now returns to CQ instead of transmitting an extra `RR73`.
- AutoSpot / DX Cluster / remote control:
- added configurable AutoSpot section in Settings (`host`, `port`, enable flag).
- DX Cluster window now uses a configurable DxSpider telnet endpoint instead of the old fixed HamQTH feed.
- added telnet IAC handling, prompt detection, `UNSET/DX` quiet fetch, and clearer submit/verify tracing in `autospot.log`.
- web dashboard now supports AutoSpot toggle, clearer command/auth status, and more stable per-mode preset apply/save behavior.
- UI/runtime fixes:
- closing `Astronomical Data` with the window `X` now clears the related menu check state.
- Linux settings dialog keeps oversize tab pages scrollable and preserves the bottom action buttons.

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

To avoid issues caused by the AppImage read-only filesystem, start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## macOS Quarantine Command

If macOS blocks startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Build and Run

```bash
cmake --build build -j6
./build/ft2.app/Contents/MacOS/ft2
```

## Documentation

- English README: [README.en-GB.md](README.en-GB.md)
- Italian README: [README.it.md](README.it.md)
- Spanish README: [README.es.md](README.es.md)
- Release notes (EN/IT/ES): [RELEASE_NOTES_v1.4.7.md](RELEASE_NOTES_v1.4.7.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release template (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_v1.4.7.md](doc/GITHUB_RELEASE_BODY_v1.4.7.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
