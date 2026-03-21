# Documentation Notes (English) - 1.5.3

This index groups the release-facing documentation for the current fork cycle.

- Current release: `1.5.3`
- Update cycle: `1.5.2 -> 1.5.3`
- Primary focus: CQRLOG compatibility, FT4/FT8 Wait Features correctness, local version propagation, new bundled DE/FR translations, and release alignment.

## Key Technical Changes (`1.5.2 -> 1.5.3`)

- restored Linux `CQRLOG wsjtx remote` interoperability by keeping historical UDP listen-port behaviour and using `WSJTX` as the compatibility client id.
- fixed local rebuild propagation so a changed `fork_release_version.txt` forces the right version into the compiled app.
- tightened FT4/FT8 `Wait Features + AutoSeq` so busy-slot collisions now pause the current TX cycle instead of calling over an active QSO.
- added bundled German and French UI translations and filtered the language menu to actual bundled translations only.
- aligned release defaults and documentation to `1.5.3`, including the experimental Linux Hamlib workflow default.

## Release Artifacts

- `decodium3-ft2-1.5.3-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.3-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.3-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.3-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.3-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.3-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.3-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.3-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.3-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.3-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.3-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.3-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.5.3-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.3-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_1.5.3.md](../RELEASE_NOTES_1.5.3.md)
- [doc/GITHUB_RELEASE_BODY_1.5.3.md](./GITHUB_RELEASE_BODY_1.5.3.md)
- [CHANGELOG.md](../CHANGELOG.md)
