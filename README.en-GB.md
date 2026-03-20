# Decodium 3 FT2 (macOS/Linux Fork) - 1.5.2

This fork packages Decodium 3 FT2 for macOS and Linux AppImage, with FT2/FT4/FT8 QSO-closing fixes, AutoCQ hardening, FT2 decoder updates from upstream, startup audio recovery, updater support, web-app parity controls, complete UI translations, and Decodium certificate tooling maintained in this repository.

Current stable release: `1.5.2`.

## Changes in 1.5.2 (`1.5.1 -> 1.5.2`)

- FT2 / FT4 / FT8 runtime correctness:
- hardened late-signoff, late-final-ack, stale-partner, retry, and direct-reply paths across standard QSO flows so completed QSOs log correctly and do not loop on `73` / `RR73`.
- restored the active-QSO lock used by `Wait Features + AutoSeq` in FT4/FT8 so a running QSO is not interrupted by queued calling logic.
- fixed stale callsign/report reuse when AutoCQ moves from CQ to a new direct caller or from one queued station to the next.
- FT2 protocol and decoder work:
- aligned FT2 decoder code to the dedicated upstream FT2 LDPC path and refreshed FT2 bitmetrics support.
- completed the FT2 `2 msg / 3 msg / 5 msg` flow, including `Quick QSO`, mixed-mode TU handling, and current FT2 short-QSO routing.
- hid FT2 async/triggered decoder tags (`T`, `aN`) from decode panes and collapsed async/sync duplicates into one logical decode.
- Audio / UI / remote control:
- strengthened startup and wake-from-sleep RX-audio recovery so monitor-on now triggers health checks and automatic reopen of streams if audio stays silent.
- brought the web app/dashboard closer to desktop parity with `Manual TX`, `Speedy`, `D-CW`, async card, `Quick QSO`, and `2/3/5 msg` controls.
- completed all bundled UI translation files so menu, popup, and in-program strings no longer ship with unfinished gaps.
- Platform / tooling:
- added Decodium certificate loading/autoload/status plus the local `tools/generate_cert.py` generator.
- kept the internal updater and refined it to open the best matching macOS/Linux asset directly.
- centralised release versioning through `fork_release_version.txt` so local builds, workflows, and GitHub releases stay aligned.
- Map and identity:
- fixed stale or fake live-map links while returning to CQ or transmitting plain CQ.
- aligned PSK Reporter identity to the exact application title string.

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
- network access recommended for NTP, DX Cluster, PSK Reporter, updater, and online features

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
- [RELEASE_NOTES_1.5.2.md](RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](doc/GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](CHANGELOG.md)
