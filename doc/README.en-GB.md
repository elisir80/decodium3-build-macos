# Documentation Notes (English) - v1.4.7

This index groups the release-facing documentation for the current fork cycle.

- Current release: `v1.4.7`
- Update cycle: `v1.4.6 -> v1.4.7`
- Primary focus: FT2 runtime/decode hardening, AutoCQ continuity, AutoSpot/DX Cluster integration, and release alignment.

## Key Technical Changes (`v1.4.6 -> v1.4.7`)

- FT2 async Tx guard raised to `300 ms`.
- FT2 false-decode filtering extended with `cty.dat` prefix validation.
- FT2 `TΔ` rendering and marker normalization hardened to preserve column alignment.
- AutoCQ partner lock / retry / confirmed-73 return-to-CQ behavior stabilized.
- Settings now expose AutoSpot endpoint configuration and enable flag.
- DX Cluster window now queries a configurable DxSpider telnet endpoint with better telnet/prompt handling.
- Web dashboard adds AutoSpot toggle, stronger command feedback, and more stable mode presets.
- `Astronomical Data` menu state now follows real window close events.

## Release Artifacts

- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_v1.4.7.md](../RELEASE_NOTES_v1.4.7.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](./GITHUB_RELEASE_BODY_v1.4.7.md)
- [CHANGELOG.md](../CHANGELOG.md)
