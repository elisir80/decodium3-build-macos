# Documentation Notes (English) - 1.6.1

- Current release: `1.6.1`
- Update cycle: `1.6.0 -> 1.6.1`

## Key Technical Changes (`1.6.0 -> 1.6.1`)

- JT4, JT9, and JT65 active runtime paths are now maintained on the native C++ decode stack.
- Q65 and WSPR active runtime paths are Fortran-free, and Echo now runs through the native C++ runtime/tool path.
- The active maintained runtime surface no longer carries the historical FFT `four2a` naming or the related legacy ABI cleanup residues.
- Obsolete Fortran sources were removed from `lib/`, `qmap/libqmap/`, `map65/libm65/`, and the old Echo tooling tree.
- Linux build/startup fixes were added for `mainwindow.cpp`, deferred client initialization, `QSocketNotifier`, Qt logging teardown, and GNU ld compare-tool linkage.
- macOS release packaging now generates `.icns` through a deterministic Python helper.
- Version metadata, workflow defaults, release docs, and GitHub release notes are aligned to `1.6.1`.

## Release Assets

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort / experimental, if generated)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`

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

To avoid issues caused by the AppImage read-only filesystem, it is recommended to start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Related Files

- [README.md](../README.md)
- [RELEASE_NOTES_1.6.1.md](../RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](./GITHUB_RELEASE_BODY_1.6.1.md)
