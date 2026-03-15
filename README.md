# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.8

This repository contains the macOS-focused fork build of Decodium 3 FT2, including Linux AppImage release flow, FT2 operator/runtime improvements, and hardened remote-control behavior.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Fork release: `v1.4.8`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Scope (`v1.4.7 -> v1.4.8`)

- FT2 timing and operator workflow:
- aligned `NUM_FT2_SYMBOLS` from `105` to `103` and refined FT2 Tx duration margin from `0.5 s` to `0.2 s` over waveform duration.
- added FT2 `Speedy`, `D-CW`, and `TX NOW` operator workflow support for immediate or preloaded transmit handling.
- FT2 auto-sequence logic now stays coherent even when the standard AutoSeq checkbox is hidden in FT2 UI.
- FT2 QSO/signoff correctness:
- FT2 no longer logs a QSO before the local signoff has been sent and the partner final acknowledgment has really arrived.
- if FT2 reaches the RR73/73 retry budget without final partner acknowledgment, transmission stops without logging.
- partner `RR73/73` handling no longer skips the local final `73` in FT2 AutoCQ/auto-sequence flows.
- FT2 async duplicate suppression now rejects repeated same-payload hypotheses across near audio bins, so duplicated exchanges no longer appear in the decode flow.
- Remote Web / dashboard security hardening:
- RemoteCommandServer is now blocked on non-loopback bind unless an access token is configured.
- non-loopback token length must be at least `12` characters.
- wildcard HTTP CORS headers were removed from the remote API.
- WebSocket connections now require an allowed same-origin `Origin` instead of accepting arbitrary browser origins.
- String/buffer safety cleanup:
- fixed the concrete COM-port formatting overflow risk in `lib/ptt.c`.
- applied bounded formatting to related PTT code in `lib/ft2` and `map65`.
- hardened `map65` device-info, status-label, and astronomical text formatting paths.
- Release/build pipeline:
- macOS release packaging now tolerates leftover CPack mounted DMG images instead of failing the whole release if staged output is already valid.

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
- Release notes (EN/IT/ES): [RELEASE_NOTES_v1.4.8.md](RELEASE_NOTES_v1.4.8.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release template (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_v1.4.8.md](doc/GITHUB_RELEASE_BODY_v1.4.8.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
