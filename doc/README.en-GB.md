# Documentation Notes (English) - 1.5.0

This index groups the release-facing documentation for the current fork cycle.

- Current release: `1.5.0`
- Update cycle: `1.4.9 -> 1.5.0`
- Primary focus: startup audio recovery, FT8/FT4/FT2 QSO correctness, AutoCQ stability, FT2 Quick QSO, decoder sync, and certificate tooling.

## Key Technical Changes (`1.4.9 -> 1.5.0`)

- automatic RX audio recovery at startup when saved devices are present but RX remains silent.
- final `73` correctness fixes for FT8, FT4, and FT2 standard flows.
- FT2 Quick QSO refactor plus `Quick QSO` button mapped to FT2 `2 msg`.
- AutoCQ duplicate-rework prevention, queue-state resets, and real-period retry accounting.
- dedicated FT2 LDPC decoder path plus shared Normalized Min-Sum decoder alignment.
- Decodium certificate loader/status support and `tools/generate_cert.py`.

## Release Artifacts

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_1.5.0.md](../RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](./GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](../CHANGELOG.md)
