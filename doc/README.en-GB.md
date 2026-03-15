# Documentation Notes (English) - v1.4.8

This index groups the release-facing documentation for the current fork cycle.

- Current release: `v1.4.8`
- Update cycle: `v1.4.7 -> v1.4.8`
- Primary focus: FT2 timing/operator refinements, FT2 signoff correctness, remote-web hardening, string-safety fixes, and release robustness.

## Key Technical Changes (`v1.4.7 -> v1.4.8`)

- FT2 symbol/timing alignment updated to `103` symbols and `0.2 s` timing margin.
- FT2 `Speedy`, `D-CW`, and `TX NOW` workflow support added.
- FT2 signoff/logging waits for real partner acknowledgment and stops cleanly without logging when retries are exhausted.
- FT2 duplicate decode suppression hardened for async nearby-bin hypotheses.
- Remote web now enforces token authentication on non-loopback bind, removes wildcard CORS, and validates WebSocket `Origin`.
- concrete bounded-formatting fixes applied in `lib/ptt.c`, `lib/ft2`, and multiple `map65` paths.
- macOS release packaging now survives leftover CPack DMG mounts.

## Release Artifacts

- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_v1.4.8.md](../RELEASE_NOTES_v1.4.8.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](./GITHUB_RELEASE_BODY_v1.4.8.md)
- [CHANGELOG.md](../CHANGELOG.md)
