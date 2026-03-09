# Documentation Notes (British English)

## Scope

Repository-specific notes for the macOS fork.

## Current Release Context

- Latest stable release: `v1.4.2`
- Targets: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (experimental), Linux x86_64 AppImage

## Build and Runtime Notes

### Build output

- `build/ft2.app/Contents/MacOS/ft2`
- helper executables in the same bundle path (`jt9`, `wsprd`)

### Shared memory on macOS

- This fork uses `SharedMemorySegment` with file-backed `mmap` on Darwin.
- The release flow no longer depends on System V shared-memory `sysctl` tuning (`kern.sysv.shmmax/shmall`).

### v1.4.2 consolidated highlights

- LotW requests moved from credentialed GET URL to HTTPS POST body.
- Strict redirect policy for credentialed LotW requests (HTTPS + expected host).
- Remote web LAN/WAN bind now requires token length >= 12.
- Linux settings dialog is clamped to visible screen geometry.
- Async decode thread-pool stack/overlap hardening (Linux-focused stability pass).
- FT2 control behavior finalized:
  - Async L2 defaults ON in FT2, auto-OFF outside FT2,
  - `Lock Tx Freq` and `Tx even/1st` hidden in FT2.
- `View -> Ionospheric Forecast` and `View -> DX Cluster` actions restored.
- Remote dashboard TX events preserved correctly across refresh cycles.

### Release artifacts

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`
- `decodium3-ft2-<version>-linux-x86_64.AppImage`
- `decodium3-ft2-<version>-linux-x86_64.AppImage.sha256.txt`

### Linux minimum requirements

- Architecture: `x86_64`
- CPU: dual-core 2.0 GHz or better
- RAM: 4 GB minimum
- Runtime: `glibc >= 2.35`, `libfuse2`/FUSE2, ALSA/PulseAudio/PipeWire

### Linux AppImage recommendation

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

### Gatekeeper quarantine command

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## References

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.4.2.md`
- `doc/GITHUB_RELEASE_BODY_v1.4.2.md`
- `doc/WEBAPP_SETUP_GUIDE.en-GB.md`
- `doc/WEBAPP_SETUP_GUIDE.it.md`
- `doc/WEBAPP_SETUP_GUIDE.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
