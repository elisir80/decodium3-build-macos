# Documentation Notes (British English)

## Scope

Repository-specific notes for the macOS fork.

## Current Release Context

- Latest stable release: `v1.3.0`
- Targets: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel

## Build and Runtime Notes

### Build output

- `build/ft2.app/Contents/MacOS/ft2`
- helper executables in the same bundle path (`jt9`, `wsprd`)

### Shared memory on macOS

- This fork now uses `SharedMemorySegment` with file-backed `mmap` on Darwin.
- The release flow no longer depends on System V shared-memory `sysctl` tuning (`kern.sysv.shmmax/shmall`).

### Release artifacts

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`

### Gatekeeper quarantine command

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## References

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.3.0.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.0.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
