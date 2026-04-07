# Decodium - Fork 9H1SR 1.6.2

This repository contains the maintained macOS and Linux AppImage fork of Decodium, focused on FT2/FT4 operator workflow reliability, multicast/TCI interoperability, aggressive native C++ migration of the maintained runtime, and reproducible macOS/Linux release engineering.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Current fork release: `1.6.2`
- Update cycle: `1.6.1 -> 1.6.2`
- Upstream sync baseline: `2603182239`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- Licence: GPLv3

## Release Highlights (`1.6.1 -> 1.6.2`)

- hardened UDP multicast delivery for LAN log-integration workflows by improving interface resolution, protocol-aware multicast interface filtering, and default-route fallback when forced-interface sends fail.
- improved TCI startup behavior for SunSDR / ExpertSDR3 style asynchronous radios by avoiding premature "TCI SDR is not switched on" failures before the ready/power state arrives.
- improved intermittent startup audio recovery when CAT is absent or the cached Qt audio device list briefly resolves to null at launch.
- finished the maintained `qmap/libqmap` migration to native C++ and removed the last active CMake Fortran backend from the cross-platform macOS/Linux application surface.
- completed the astronomy/ephemeris migration used by the active app path and removed the old active CMake Fortran astronomy chain.
- cleaned additional obsolete Fortran and archival WSPR/JT/QSO50 sources from the maintained tree while keeping `map65/libm65` gated to Windows-only CMake builds.
- kept `build-arm-output/` excluded permanently from git tracking and source staging while preserving the Debian Trixie ARM64 AppImage publication path.
- aligned local version metadata, workflow defaults, readmes, docs, changelog, release notes, repository description, GitHub tag, and release body to semantic version `1.6.2`.

## Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (best effort / experimental)
- Linux x86_64 AppImage
- Linux aarch64 AppImage (Debian Trixie baseline)

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

No `.pkg` installers are produced in this fork release line.

## Linux Minimum Requirements

Hardware:

- `x86_64` CPU with SSE2 support, or `aarch64` / ARM64 64-bit CPU
- dual-core 2.0 GHz or better, or equivalent modern ARM64 SoC
- 4 GB RAM minimum (8 GB recommended)
- at least 500 MB free disk space
- 1280x800 display or better recommended
- audio/CAT/serial/USB hardware suitable for amateur-radio weak-signal operation

Software:

- 64-bit Linux distribution with an X11 or Wayland desktop session capable of running Qt5 AppImages
- Linux `x86_64` AppImage: `glibc >= 2.35`
- Linux `aarch64` AppImage: `glibc >= 2.38` (Debian Trixie baseline)
- `libfuse2` / FUSE2 support if you want to mount the AppImage directly
- ALSA, PulseAudio, or PipeWire audio stack
- access permissions for serial/USB devices (`dialout`, `uucp`, or distro equivalent) when CAT or external radios are used
- network access recommended for NTP, PSK Reporter, multicast logging, DX Cluster, updater, and online station workflows

## Linux Local Build Note

The published AppImages already bundle the required Qt multimedia runtime. If you build Decodium locally on Ubuntu/Debian, install the minimum system multimedia packages too, otherwise the audio device lists may remain empty or disabled even though the AppImage works correctly.

Recommended minimum packages for local Ubuntu/Debian builds:

```bash
sudo apt update
sudo apt install \
  qtmultimedia5-dev \
  libqt5multimedia5 \
  libqt5multimedia5-plugins \
  libqt5multimediawidgets5 \
  libqt5multimediagsttools5 \
  libpulse-mainloop-glib0 \
  pulseaudio-utils \
  gstreamer1.0-plugins-base \
  gstreamer1.0-plugins-good
```

## Startup Guidance

If macOS blocks startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Eseguire i seguenti comandi nel terminale:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Related Documentation

- English README: [README.en-GB.md](README.en-GB.md)
- Italian README: [README.it.md](README.it.md)
- Spanish README: [README.es.md](README.es.md)
- Release notes (EN/IT/ES): [RELEASE_NOTES_1.6.2.md](RELEASE_NOTES_1.6.2.md)
- Changelog (EN/IT/ES): [CHANGELOG.md](CHANGELOG.md)
- GitHub release body (EN/IT/ES): [doc/GITHUB_RELEASE_BODY_1.6.2.md](doc/GITHUB_RELEASE_BODY_1.6.2.md)
- Docs index (EN): [doc/README.en-GB.md](doc/README.en-GB.md)
- Docs index (IT): [doc/README.it.md](doc/README.it.md)
- Docs index (ES): [doc/README.es.md](doc/README.es.md)
