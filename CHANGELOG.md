# Changelog

## [1.2.0] - 2026-02-26

Fork release based on Decodium v3.0 SE Raptor with macOS-focused runtime stabilization and robust DT/NTP timing control.

### Added

- Dedicated fork release identity `v1.2.0` in window title and release metadata.
- `tx-support.log` runtime log for TX/PTT/audio troubleshooting.
- macOS microphone permission preflight at startup.
- NTP robust sync controls:
  - deadband + confirmation weak-sync,
  - cluster/consensus filtering,
  - sparse-server jump confirmation,
  - lock hold behavior during temporary outages.

### Changed

- App namespace and bundle path standardized to `ft2.app` / `ft2`.
- macOS subprocess launch fixed (`jt9` copied beside app executable at build time).
- TX start/stop sequencing hardened for CAT/PTT lag and race conditions.
- Modulator FT2 guard enforces coherent symbol/tone parameters.
- Audio settings persistence made more defensive for channel/device restoration.
- FT2 band defaults auto-merged for legacy profiles without FT2 entries.
- Graph window titles aligned to Decodium branding.
- Removed pre-release popup from startup path.

### Fixed

- `execve` failures caused by legacy `wsjtx.app` path assumptions.
- Intermittent "PTT active but no modulation" scenarios in repeated FT2 cycles.
- Late macOS microphone popup interrupting active operations.
- Disabled/clipped audio channel selectors and invalid persisted channel states.
- NTP state dropping to unstable offsets when server set quality degrades.

### CI/Build

- macOS build workflow prepared for multi-target release matrix:
  - Apple Silicon Tahoe
  - Apple Silicon Sequoia
  - Apple Intel Sequoia
- Workflow dependency set updated and artifact naming aligned to `v1.2.0`.
