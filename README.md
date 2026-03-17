# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.9

This repository contains the macOS-focused fork build of Decodium 3 FT2, including Linux AppImage release flow, FT2 decoder/runtime improvements, FT2 AutoCQ correctness fixes, and release packaging updates across macOS and Linux.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Fork release: `v1.4.9`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Scope (`v1.4.8 -> v1.4.9`)

- FT2 decoder improvements:
- increased FT2 triggered-decode LLR scaling from `2.83` to `3.2` and normalized all three FT2 LLR paths before LDPC decoding.
- imported adaptive FT2 channel estimation with MMSE-equalized bit metrics for selective-fading HF paths.
- added the new `lib/ft2/ft2_channel_est.f90` decoder stage and wired it into the FT2 Fortran build.
- FT2 async runtime / operator feedback:
- added the new FT2 async visualizer widget with live RX/TX state and S-meter updates from the actual FT2 decode path.
- reduced FT2 async polling from `750 ms` to `100 ms` and deferred UI/log fan-out with `QTimer::singleShot(0)` to keep the decode path responsive.
- preserved FT2 async line formatting/timestamps instead of trimming away the original fixed-column structure.
- FT2 workflow correctness:
- the application no longer forces `FT2` at startup; saved mode/frequency is respected again.
- FT2 can now react immediately to a first directed reply while CQ is active instead of missing the first caller.
- fresh AutoCQ partner lock now clears stale retry/miss counters before a new QSO starts, preventing premature partner switches.
- Language/UI improvements:
- added a `Language` menu in the main menu bar.
- selected UI language is now stored in settings and reused on next startup when no CLI language override is passed.
- DX Cluster window columns are now manually resizable and persisted between sessions.
- Linux / Astronomical Data:
- `JPLEPH` lookup now covers AppImage paths, standard Linux install paths, current working directory, and out-of-source builds via `CMAKE_SOURCE_DIR`.
- Linux AppImage workflows now bundle `contrib/Ephemeris/JPLEPH` into `usr/share/wsjtx`.

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
- Release notes (EN/IT/ES): [RELEASE_NOTES_v1.4.9.md](RELEASE_NOTES_v1.4.9.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release template (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_v1.4.9.md](doc/GITHUB_RELEASE_BODY_v1.4.9.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
