# Decodium Fork v1.2.0 (base: Decodium v3.0 SE Raptor)

Fork release focused on macOS operational stability and robust timing behavior for live FT2 usage, while preserving the Raptor coding/decoding baseline.

## Highlights

- Based on upstream Decodium v3.0 SE Raptor.
- macOS app/runtime migration finalized on `ft2.app`.
- Fixed subprocess layout (`jt9` path and bundle colocation).
- Startup microphone preflight to prevent delayed macOS permission popup during operation.
- TX/PTT/audio stabilization:
  - PTT ack/fallback guard path,
  - synchronous modulator stop/start cleanup,
  - defensive timer/state cleanup on stop/restart.
- Audio/radio settings persistence hardened (channels/devices/CAT TX source behavior).
- Robust DT/NTP synchronization strategy:
  - weak-sync with confirmation/deadband,
  - coherence/cluster filtering,
  - sparse-server jump confirmation,
  - lock hold during temporary response loss.
- Release docs and changelog added.

## Documentation

- Release notes: `RELEASE_NOTES_v1.2.0.md`
- Changelog: `CHANGELOG.md`
- macOS porting details: `doc/MACOS_PORTING_v1.2.0.md`
- DT/NTP technical details: `doc/DT_NTP_ROBUST_SYNC_v1.2.0.md`

## Build targets in CI

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
