# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.2.0

This release (`v1.2.0`) is based on the upstream Decodium 3.0 SE Raptor codebase and ports the project to a stable macOS runtime path with persistent rig/audio behavior.

- Upstream base: `iu8lmc/Decodium-3.0-Codename-Raptor`
- Fork release: `v1.2.0`
- App bundle: `ft2.app`
- License: GPLv3

## What v1.2.0 adds on top of upstream Raptor

- macOS launch/runtime path fixed for `ft2.app` (no legacy `wsjtx.app` subprocess mismatch).
- `jt9` colocation in app bundle guaranteed after build on macOS.
- Dedicated app profile namespace (`ApplicationName=ft2`) to avoid collisions with WSJT-X profile data.
- TX stability hardening on macOS:
  - robust PTT handshake with delayed-start fallback,
  - synchronous modulator stop/start cleanup,
  - defensive stop path cleanup for pending timers/states,
  - startup microphone permission preflight to prevent late popup during active operation.
- Audio/radio settings persistence improvements:
  - persistent channel validation/fallback,
  - better handling of CAT TX audio source with DX Lab path,
  - FT2 defaults merge into legacy profiles when missing.
- UI/branding cleanup:
  - title string includes fork identity and version,
  - graph windows show Decodium branding,
  - removed pre-release blocking popup,
  - restored multi-mode controls while keeping FT2 as operational focus.
- NTP/DT robust sync strategy for real-world FT2 operation:
  - lock-aware weak sync with confirmations/deadband,
  - cluster/consensus filters and sparse-server jump gating,
  - hold behavior on temporary no-response cycles,
  - conservative DT feedback when NTP is healthy.

## Technical docs

- Release notes: [RELEASE_NOTES_v1.2.0.md](RELEASE_NOTES_v1.2.0.md)
- macOS porting details: [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- DT/NTP technical architecture: [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- TX/audio stability notes (historical): [doc/FT2_STABILITY_v110.md](doc/FT2_STABILITY_v110.md)
- Changelog: [CHANGELOG.md](CHANGELOG.md)

## Build (local macOS)

```bash
cmake -B build-raptor-port -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Release \
  -DWSJT_GENERATE_DOCS=OFF \
  -DWSJT_SKIP_MANPAGES=ON \
  -DWSJT_BUILD_UTILS=OFF

cmake --build build-raptor-port --target wsjtx -j8
```

Run:

```bash
/Users/salvo/Desktop/ft2/decodium3-raptor-merge/build-raptor-port/ft2.app/Contents/MacOS/ft2
```

## CI release targets (GitHub Actions)

The macOS release workflow is configured for:

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia

Each job produces a packaged `ft2.app` artifact tagged with release/version and platform metadata.

## Credits

- WSJT-X by Joe Taylor K1JT and the WSJT Development Group
- Decodium v3.0 SE Raptor by IU8LMC
- Fork integration/porting by Salvatore Raccampo 9H1SR
