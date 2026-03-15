# Decodium 3 FT2 (macOS Fork) - v1.4.8

Fork maintained by **Salvatore Raccampo 9H1SR**.

## Project Description

This repository is a Decodium/WSJT-X fork focused on macOS and Linux packaging, FT2 operator/runtime stability, AutoCQ correctness, and hardened remote/DX-cluster workflows.

Latest stable release: `v1.4.8`.

## Changes in v1.4.8 (`v1.4.7 -> v1.4.8`)

- FT2 timing and operator workflow:
- aligned `NUM_FT2_SYMBOLS` from `105` to `103` and reduced the FT2 Tx timing margin from `0.5 s` to `0.2 s` above waveform duration.
- added FT2 `Speedy`, `D-CW`, and `TX NOW` workflow support for immediate or preloaded transmit handling.
- FT2 auto-sequence logic now stays coherent even when the standard AutoSeq checkbox is hidden in FT2 mode.
- FT2 QSO/signoff correctness:
- FT2 no longer logs a QSO before the local final signoff has been sent and the partner final acknowledgment has actually arrived.
- if FT2 exhausts the RR73/73 retry budget without partner acknowledgment, transmission stops without auto-log.
- partner `RR73/73` handling no longer skips the local final `73` in FT2 AutoCQ/auto-sequence flows.
- FT2 async duplicate suppression now removes repeated same-payload hypotheses across nearby audio bins, so split duplicate exchanges no longer reach the decode flow.
- Remote Web / dashboard hardening:
- RemoteCommandServer is now blocked on non-loopback bind when no access token is configured.
- non-loopback token length must be at least `12` characters.
- wildcard CORS headers were removed from the remote HTTP API.
- WebSocket connections now require an allowed same-origin `Origin` instead of accepting arbitrary browser origins.
- String/buffer safety:
- fixed the concrete COM-port formatting overflow risk in `lib/ptt.c`.
- applied bounded formatting to related PTT code in `lib/ft2` and `map65`.
- hardened `map65` device-info, status-label, and astronomical text formatting.
- Release/build pipeline:
- macOS packaging now tolerates leftover CPack mounted DMG images instead of failing the whole release when staged output is already valid.

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
- [RELEASE_NOTES_v1.4.8.md](RELEASE_NOTES_v1.4.8.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](doc/GITHUB_RELEASE_BODY_v1.4.8.md)
- [doc/README.en-GB.md](doc/README.en-GB.md)
- [doc/README.it.md](doc/README.it.md)
- [doc/README.es.md](doc/README.es.md)

## Licence

GPLv3 inherited from upstream WSJT-X/Decodium codebase.
