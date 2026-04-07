# Decodium (macOS/Linux Fork) - 1.6.2

- Current stable release: `1.6.2`
- Update cycle: `1.6.1 -> 1.6.2`

## Changes in 1.6.2 (`1.6.1 -> 1.6.2`)

- hardened UDP multicast delivery for LAN logger integrations by resolving multicast interfaces more reliably and falling back to the default route when forced-interface sends fail.
- improved TCI startup behavior for asynchronous SunSDR / ExpertSDR3 style radios so Decodium no longer fails too early while waiting for the ready/power state.
- improved intermittent startup audio recovery when CAT is disconnected or cached Qt audio devices temporarily resolve as null.
- completed the maintained `qmap/libqmap` migration to native C++ and removed the last active cross-platform CMake Fortran backend.
- completed the astronomy/ephemeris migration used by the maintained app path and removed the old active Fortran astronomy chain from the CMake build.
- cleaned additional obsolete Fortran and archival WSPR/JT/QSO50 sources from the maintained tree while keeping `map65/libm65` gated to Windows-only CMake builds.
- kept `build-arm-output/` permanently excluded from source staging and git tracking.
- aligned local version metadata, workflow defaults, release docs, and GitHub release notes to semantic version `1.6.2`.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(Debian Trixie baseline)*

## Release Assets

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage.sha256.txt`

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

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

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
- [RELEASE_NOTES_1.6.2.md](RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](doc/GITHUB_RELEASE_BODY_1.6.2.md)
