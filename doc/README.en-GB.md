# Documentation Notes (British English)

## Scope

Repository-specific notes for the macOS fork.

## Current Release Context

- Latest stable release: `v1.3.7`
- Targets: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (experimental), Linux x86_64 AppImage

## Build and Runtime Notes

### Build output

- `build/ft2.app/Contents/MacOS/ft2`
- helper executables in the same bundle path (`jt9`, `wsprd`)

### Shared memory on macOS

- This fork now uses `SharedMemorySegment` with file-backed `mmap` on Darwin.
- The release flow no longer depends on System V shared-memory `sysctl` tuning (`kern.sysv.shmmax/shmall`).

### Security/concurrency hardening and UI/runtime updates (v1.3.7)

- Added world-map contact click handling with marker highlight and DX call/grid transfer.
- Added configurable map click mode (`Map: single click starts Tx`).
- Added persistent `View -> World Map` visibility state.
- Added new tool windows: `Ionospheric Forecast` and `DX Cluster`.
- Improved day/night map rendering and end-of-QSO path cleanup logic.
- Improved compact/two-row top-controls behavior for small displays.
- Decode sequence-start timestamp is now captured before decode start to avoid startup misalignment.
- Registered `ModulatorState` as Qt metatype for robust queued cross-thread delivery.
- Default Qt style set to `Fusion` for consistent macOS rendering.
- Removed hardcoded legacy revision suffix source affecting PSKReporter `Using:`.

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

### Gatekeeper quarantine command

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## References

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.3.7.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.7.md`
- `doc/README.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
