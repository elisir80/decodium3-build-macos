# Decodium 3 FT2 (macOS/Linux Fork) - 1.5.0

This fork packages Decodium 3 FT2 for macOS and Linux AppImage, with FT2 Quick QSO work, QSO-sequencing fixes, AutoCQ stability improvements, decoder updates, and Decodium certificate tooling maintained in this repository.

Current stable release: `1.5.0`.

## Changes in 1.5.0 (`1.4.9 -> 1.5.0`)

- Audio startup:
- automatic RX audio recovery added when devices are selected but startup still comes up silent.
- audio stream reopen and monitor re-arm logic now mirror the manual "Audio Preferences -> OK" recovery path.
- QSO flow and logging:
- fixed final `73` behaviour in FT8, FT4, and FT2 standard 5-message flows when the other station sends `RR73` or `73` first.
- fixed multiple FT2 Quick QSO logging paths, including late log-after-own-73 fallback.
- DX map and active DX fields now clear correctly when the app returns to CQ after a completed QSO.
- AutoCQ:
- duplicate rework protection now blocks recently completed calls on every caller-selection path.
- queue handoff resets stale retry counters, reports, and caller state before the next QSO begins.
- FT8 retry timeout now counts actual missed periods only.
- `debug.txt` now records AutoCQ partner changes, queue starts, handoffs, retry progression, and recent-work skips.
- FT2 protocol/runtime:
- imported upstream watchdog rescue fix.
- added dedicated FT2 LDPC decoder file and routed FT2 triggered decode to it.
- aligned shared LDPC decoders to the upstream Normalized Min-Sum decoder refresh.
- Quick QSO:
- `Quick QSO` button added as a UI alias for FT2 `2 msg`.
- current Quick QSO flow is aligned to the short schema requested for FT2 while keeping backward compatibility for older `TU` variants.
- Certificates/tooling:
- added Decodium certificate loader/autoload and main-window status indicator.
- added `tools/generate_cert.py` to generate `.decodium` certificate files.

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

Hardware:

- `x86_64` CPU, dual-core 2.0 GHz+
- 4 GB RAM minimum (8 GB recommended)
- at least 500 MB free disk space
- 1280x800 display or better recommended
- radio/CAT/audio hardware according to station setup

Software:

- Linux `x86_64` with `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio, or PipeWire
- Qt5-capable desktop environment
- network access recommended for NTP/DX Cluster workflows

## Startup Guidance

If macOS blocks startup:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

To avoid issues caused by the AppImage read-only filesystem, it is recommended to start Decodium by extracting the AppImage first and then running the program from the extracted directory.

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
- [RELEASE_NOTES_1.5.0.md](RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](doc/GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](CHANGELOG.md)
