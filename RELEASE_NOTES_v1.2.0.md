# Release Notes - Fork v1.2.0

Date: 2026-02-26

Base: Decodium v3.0 SE "Raptor" (upstream IU8LMC)

Release type: fork integration + macOS stabilization release

## Identity and scope

- Fork release version: `1.2.0`
- Base stack version remains the Raptor line (`3.0.0-rc1` app core lineage)
- Primary app bundle/executable on macOS: `ft2.app` / `ft2`

This release does not replace upstream Raptor identity; it layers operational hardening and platform porting required for stable field use on macOS.

## Main integration goals completed

- Keep Raptor coding/decoding improvements as base.
- Preserve prior fork gains from the `1.1.0` workstream:
  - macOS TX/audio robustness,
  - persistent rig/audio behavior,
  - world/third-pane integration continuity,
  - UDP/network operational continuity.
- Reconcile runtime naming and launch paths around `ft2.app`.
- Stabilize DT/NTP behavior under real radio operation and sparse NTP responses.

## macOS-specific fixes in v1.2.0

### Runtime and process layout

- `QApplication` name moved to `ft2` to isolate settings/data/temp from WSJT-X profiles.
- `jt9` subprocess launch path fixed for `ft2.app` layout.
- CMake post-build copy ensures `jt9` is colocated with main executable in macOS bundle.
- Bundle fixup logic adjusted for executable rename (`ft2` instead of `wsjtx`).

### Permissions and startup behavior

- macOS microphone permission is primed at startup via short audio-input preflight.
- Pre-release popup removed from startup flow to avoid operational interruption.

### TX/PTT/audio robustness

- PTT request timestamping and delayed-start fallback path added.
- FT2 start sequence now tolerates CAT ack delay with guarded fallback.
- Stop paths clear pending PTT/start timers defensively.
- Modulator stop path supports synchronous teardown to reduce stale-state races.
- FT2 modulator parameter guard forces coherent symbol/frame/tone values.
- TX support logging added (`~/Library/Application Support/ft2/tx-support.log`).

### Configuration persistence hardening

- Channel combo sizing adjusted for translated labels and clipping prevention.
- Persisted audio channels are revalidated and auto-fallback to supported values.
- DX Lab CAT path keeps TX audio source controls usable/persisted.
- Legacy profiles missing FT2 frequencies are auto-healed by merging FT2 defaults.

## DT/NTP timing behavior in v1.2.0

Detailed architecture is documented in:

- `doc/DT_NTP_ROBUST_SYNC_v1.2.0.md`

Summary:

- NTP no longer blindly applies sparse/bad server jumps.
- Lock-aware hold behavior preserves good offsets through short outages.
- Sparse server jump confirmation avoids single-cycle spikes.
- DT correction remains conservative when NTP is healthy.
- Scheduler remains tied to raw system time (no direct NTP phase shift in TX slot timing).

## UI/branding adjustments

- Main title includes fork identity:
  - `Decodium v3.0 FT2 "Raptor" v<base> | Fork by Salvatore Raccampo 9H1SR v 1.2.0`
- Graph windows show Decodium branding instead of WSJT-X naming.
- Menu branding cleanup retained (`Decodium v3.0 SE`, no KP5/NP3VI suffix in title).

## Build and release targets

The macOS release workflow is configured for:

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia

Artifacts are emitted per-target with release-identifiable names.

## Recommended validation before publishing tag

- 20-30 minutes live FT2 operations (CQ + responses + stop/restart cycles).
- Confirm no recurrent "PTT active, no modulation" behavior.
- Confirm NTP does not produce repeated large jumps on sparse server counts.
- Confirm DT remains within expected operational envelope under sustained TX/RX.

## Tagging

Release tag: `v1.2.0`

Suggested annotated tag message:

`Fork v1.2.0 based on Decodium v3.0 SE Raptor: macOS runtime port, TX/audio/PTT stabilization, robust DT/NTP sync logic, and multi-target macOS CI packaging.`
