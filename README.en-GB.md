# Decodium 3 FT2 (macOS Fork) - v1.4.9

This fork packages Decodium 3 FT2 for macOS and Linux AppImage, with additional FT2 runtime fixes, decoder updates, and release automation maintained in this repository.

Latest stable release: `v1.4.9`.

## Changes in v1.4.9 (`v1.4.8 -> v1.4.9`)

- FT2 decoder:
- raised FT2 triggered-decode LLR scaling from `2.83` to `3.2`.
- normalized all three FT2 LLR metric streams before LDPC decode.
- added adaptive channel estimation with MMSE-equalized FT2 bit metrics for fading channels.
- introduced `ft2_channel_est.f90` and linked it into the FT2 Fortran build.
- FT2 async/runtime:
- added a dedicated FT2 async visualizer widget.
- FT2 async S-meter is now fed from the real FT2 decode path.
- FT2 async polling reduced to `100 ms`.
- deferred `postDecode()` / `write_all()` fan-out to keep the async decode path responsive.
- FT2 startup and AutoCQ behavior:
- startup no longer forces `FT2`; saved mode/frequency is respected again.
- FT2 now handles the first immediate directed reply while CQ is active.
- fresh AutoCQ partner acquisition now resets stale retry/miss counters to avoid premature partner switching.
- UI / usability:
- added a `Language` menu to the main menu bar.
- UI language is now persisted in settings and restored on next start when no CLI override is provided.
- DX Cluster columns are now user-resizable and their widths are persisted.
- Linux / astronomical data:
- `JPLEPH` lookup now covers AppImage paths, Linux share paths, current working directory, and out-of-source builds using `CMAKE_SOURCE_DIR`.
- Linux AppImage packaging now ships `JPLEPH` inside `usr/share/wsjtx`.

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
- at least 500 MB free disk space
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio, or PipeWire

## Startup Guidance

If macOS blocks startup:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

To avoid issues caused by the AppImage read-only filesystem, start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Related Files

- [README.md](README.md)
- [README.it.md](README.it.md)
- [README.es.md](README.es.md)
- [RELEASE_NOTES_v1.4.9.md](RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](doc/GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](CHANGELOG.md)
