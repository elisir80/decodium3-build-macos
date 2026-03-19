# Decodium 3 FT2 (macOS/Linux Fork) - 1.5.1

This fork packages Decodium 3 FT2 for macOS and Linux AppImage, with FT2/FT4/FT8 QSO-closing fixes, AutoCQ state-machine hardening, internal update checks, upstream decoder sync, and Decodium certificate tooling maintained in this repository.

Current stable release: `1.5.1`.

## Changes in 1.5.1 (`1.5.0 -> 1.5.1`)

- Internal updater:
- added GitHub release checks at startup and a manual `Help > Check for updates...` action.
- the updater now resolves the best-matching macOS/Linux asset directly instead of opening only the generic release page.
- QSO flow and logging:
- fixed several FT2/FT4/FT8 late-signoff paths where the app could keep sending `73/RR73`, miss the final log, or fail to recover a delayed close.
- fixed the path where the remote final `73/RR73` arrived after the local station had already sent its own signoff.
- improved late-final-ack recovery after timeout so delayed `73/RR73` from the active partner can still be logged correctly.
- AutoCQ:
- fixed stale partner reuse after returning to CQ.
- fixed direct-caller cases that were decoded correctly but still left the app transmitting CQ instead of arming `Tx2`.
- fixed the first direct FT2 reply using a stale report value from the previous QSO instead of the current caller SNR.
- expanded recent-work and abandoned-partner suppression to reduce duplicate rework after deferred closures.
- Map and identity:
- fixed the live world map showing a fake active QSO path while transmitting plain CQ.
- aligned the PSK Reporter program identifier to the exact title-bar string shown by the application.
- Diagnostics/process:
- expanded `debug.txt` tracing for direct-caller arming, stale-partner cleanup, late signoff recovery, and updater asset selection.
- local UI version, workflow defaults, and release documents are now aligned to semantic version `1.5.1`.

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
- network access recommended for NTP, DX Cluster, and PSK Reporter workflows

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
- [RELEASE_NOTES_1.5.1.md](RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](doc/GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](CHANGELOG.md)
