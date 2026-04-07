# Documentation Notes (English) - 1.6.2

- Current release: `1.6.2`
- Update cycle: `1.6.1 -> 1.6.2`

## Key Technical Changes (`1.6.1 -> 1.6.2`)

- UDP multicast delivery is more robust for LAN logger workflows thanks to better interface resolution, protocol filtering, and default-route fallback.
- TCI startup is now tolerant of asynchronous ready/power reporting from SunSDR / ExpertSDR3 style radios.
- Startup audio recovery now retries after refreshing cached Qt audio devices when CAT is disconnected or device enumeration races the UI.
- `qmap/libqmap` has been migrated fully to native C++, removing the last active cross-platform CMake Fortran backend.
- The active astronomy/ephemeris path has been migrated to native C++ and the old active Fortran astronomy chain has been removed from the maintained build.
- Additional obsolete Fortran and archival WSPR/JT/QSO50 sources were removed from the maintained tree, while `map65/libm65` remains Windows-only in CMake.
- Version metadata, workflow defaults, release docs, and GitHub release notes are aligned to `1.6.2`.

## Release Assets

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort / experimental, if generated)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`

## Linux Minimum Requirements

- `x86_64` with SSE2 or `aarch64` / ARM64 64-bit CPU
- 4 GB RAM minimum, 500 MB free disk
- 64-bit Linux desktop session on X11 or Wayland able to run Qt5 AppImages
- `glibc >= 2.35` for Linux `x86_64`
- `glibc >= 2.38` for Linux `aarch64` *(Debian Trixie baseline)*
- `libfuse2`, ALSA/PulseAudio/PipeWire, and serial/USB permissions as needed

## Startup Guidance

macOS quarantine workaround:

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

- [README.md](../README.md)
- [RELEASE_NOTES_1.6.2.md](../RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](./GITHUB_RELEASE_BODY_1.6.2.md)
