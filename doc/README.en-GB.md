# Documentation Notes (English) - v1.4.9

This index groups the release-facing documentation for the current fork cycle.

- Current release: `v1.4.9`
- Update cycle: `v1.4.8 -> v1.4.9`
- Primary focus: FT2 decoder improvements, FT2 async visual feedback, FT2 startup/AutoCQ correctness, Linux astronomical data packaging, and UI language/cluster usability improvements.

## Key Technical Changes (`v1.4.8 -> v1.4.9`)

- FT2 triggered decode now uses stronger `3.2` LLR scaling and explicit normalization on all three FT2 LLR branches.
- adaptive FT2 channel estimation with MMSE-equalized bit metrics added through `ft2_channel_est.f90`.
- new FT2 async visualizer widget added, with real decode-path S-meter updates and `100 ms` polling cadence.
- FT2 startup no longer forces FT2 mode; saved mode/frequency is respected.
- FT2 immediate directed reply handling and stale AutoCQ retry counter reset reduce missed first callers and premature partner switching.
- new `Language` menu persists UI language in settings and `main.cpp` now reloads that stored language.
- DX Cluster columns are resizable and their header state is persisted.
- `JPLEPH` lookup now covers AppImage, Linux share paths, working directory, and `CMAKE_SOURCE_DIR`, and Linux AppImage packaging now bundles the file.

## Release Artifacts

- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage.sha256.txt`

## Linux Minimum Requirements

- `x86_64` CPU, dual-core 2.0 GHz+
- 4 GB RAM minimum (8 GB recommended)
- 500 MB free disk space
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio, or PipeWire

## Startup Guidance

macOS quarantine:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extract-run flow:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Related Files

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_v1.4.9.md](../RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](./GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](../CHANGELOG.md)
