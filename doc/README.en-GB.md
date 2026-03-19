# Documentation Notes (English) - 1.5.1

This index groups the release-facing documentation for the current fork cycle.

- Current release: `1.5.1`
- Update cycle: `1.5.0 -> 1.5.1`
- Primary focus: updater integration, FT2/FT4/FT8 late-signoff correctness, AutoCQ direct-reply hardening, map cleanup, and PSK Reporter identity alignment.

## Key Technical Changes (`1.5.0 -> 1.5.1`)

- in-app GitHub release checker plus direct asset selection for macOS/Linux.
- late-signoff recovery across FT2/FT4/FT8 so delayed `73/RR73` still logs correctly.
- direct-caller arming fixes for AutoCQ when leaving CQ and starting `Tx2`.
- stale-report fix on the first direct FT2 reply.
- world-map CQ cleanup and PSK Reporter title-string alignment.

## Release Artifacts

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
- [RELEASE_NOTES_1.5.1.md](../RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](./GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](../CHANGELOG.md)
