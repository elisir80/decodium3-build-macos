# Documentation Notes (English) - 1.5.2

This index groups the release-facing documentation for the current fork cycle.

- Current release: `1.5.2`
- Update cycle: `1.5.1 -> 1.5.2`
- Primary focus: FT2 decoder/protocol updates, AutoCQ and Wait Features correctness, startup audio recovery, web-app parity, complete UI translations, and release/version alignment.

## Key Technical Changes (`1.5.1 -> 1.5.2`)

- FT2 decoder refresh with the dedicated upstream FT2 LDPC path and updated FT2 bitmetrics support.
- FT2 `Quick QSO` / `2 msg / 3 msg / 5 msg` flow completion with mixed-mode TU handling.
- Wait Features + AutoSeq active-QSO lock restored for FT4/FT8.
- startup and wake RX-audio recovery tied to real monitor activation.
- web-app/dashboard parity extended with Manual TX, Speedy, D-CW, async, Quick QSO, and 2/3/5 message controls.
- bundled UI translations completed and FT2 async decoder tags removed from visible decode panes.
- release versioning centralised via `fork_release_version.txt`.

## Release Artifacts

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
- [RELEASE_NOTES_1.5.2.md](../RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](./GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](../CHANGELOG.md)
