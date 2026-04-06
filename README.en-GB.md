# Decodium (macOS/Linux Fork) - 1.6.1

- Current stable release: `1.6.1`
- Update cycle: `1.6.0 -> 1.6.1`

## Changes in 1.6.1 (`1.6.0 -> 1.6.1`)

- completed the maintained native C++ migration of the active legacy JT runtime, covering JT4, JT9, and JT65 decode paths.
- promoted Q65 and WSPR active runtime paths to Fortran-free native implementations and finished the Echo runtime/tool migration to native C++.
- removed the remaining active-path legacy ABI naming from the maintained app/runtime surface, including the historical FFT `four2a` compatibility naming.
- cleaned obsolete Fortran sources and compatibility files from `lib/`, `qmap/libqmap/`, `map65/libm65/`, and the old Echo tooling path.
- fixed Linux build/startup regressions in `mainwindow.cpp`, deferred network-client initialization, `QSocketNotifier` handling, Qt logging teardown, and GNU ld linkage in compare/sim targets.
- fixed the macOS `Invalid Iconset` packaging blocker by generating `.icns` through a deterministic Python helper.
- kept `build-arm-output/` permanently excluded from source staging and git tracking.
- aligned local version metadata, workflow defaults, release docs, and GitHub release notes to semantic version `1.6.1`.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(Debian Trixie baseline)*

## Release Assets

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

## Linux Minimum Requirements

Hardware:

- `x86_64` CPU with SSE2, or `aarch64` / ARM64 64-bit CPU
- dual-core 2.0 GHz or better, or equivalent modern ARM64 SoC
- 4 GB RAM minimum (8 GB recommended)
- at least 500 MB free disk space
- audio/CAT/serial/USB hardware suitable for weak-signal operation

Software:

- 64-bit Linux distribution with an X11 or Wayland desktop session capable of running Qt5 AppImages
- Linux `x86_64` AppImage: `glibc >= 2.35`
- Linux `aarch64` AppImage: `glibc >= 2.38` *(Debian Trixie baseline)*
- `libfuse2` / FUSE2 for direct AppImage mounting
- ALSA, PulseAudio, or PipeWire
- serial/USB access permissions for CAT or external devices

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
- [RELEASE_NOTES_1.6.1.md](RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](doc/GITHUB_RELEASE_BODY_1.6.1.md)
