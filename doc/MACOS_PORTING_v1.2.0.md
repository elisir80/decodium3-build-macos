# macOS Porting Notes - Fork v1.2.0

Date: 2026-02-26

Target repo state: branch `merge/raptor-v110-port`

## Objective

Make the Raptor base operationally stable on macOS for continuous FT2 use with real rigs (CAT/PTT + USB audio), without requiring manual workaround loops at each startup.

## 1) Bundle/executable migration to `ft2.app`

### Problem

Upstream path assumptions and helper scripts still expected `wsjtx.app`/`wsjtx` in key places. On macOS this caused subprocess launch failures (`jt9` not found next to executable).

### Applied changes

- `WSJT_APP_BUNDLE_NAME` and `WSJT_APP_EXECUTABLE_NAME` introduced in CMake.
- install and bundle-fixup paths switched to these variables.
- `wsjtx` target output executable set to `ft2`.
- GUI identifier updated to `org.decodium.ft2`.
- post-build copy ensures `jt9` sits in the same `Contents/MacOS` directory as `ft2`.

### Result

- Startup no longer depends on legacy `wsjtx.app` assumptions.
- `ft2` can start `jt9` reliably from app bundle runtime path.

## 2) Application namespace and settings isolation

### Problem

Using `WSJT-X` app name risks profile overlap, stale settings collision, and inconsistent restore behavior in shared environments.

### Applied change

- `QApplication::setApplicationName("ft2")`.

### Result

- Separate profile namespace under macOS app-support path.
- Consistent `ft2.ini` style behavior without WSJT-X interference.

## 3) Microphone permission reliability

### Problem

macOS microphone consent popup appearing late (during operation) caused instability and TX/audio side effects.

### Applied change

- Startup preflight probe with `QAudioInput` on selected/default input device.
- Immediate start/stop just to trigger permission flow predictably.
- Logging integrated into `tx-support.log`.

### Result

- Permission prompt appears at startup phase instead of mid-QSO.

## 4) TX/PTT/audio race-condition hardening

### Problem

Intermittent behavior where CAT/PTT appeared successful but modulation became mute after repeated cycles.

### Applied changes

- PTT request timestamping and audit logs.
- PTT ack path starts TX with controlled delay.
- fallback start triggers if ack is late beyond guard time.
- stop path clears delayed-start timers and pending flags.
- synchronous modulator stop helper to avoid stale active-state carryover.
- explicit restart when stale active modulator state is detected at TX start.

### Result

- Repeated FT2 TX cycles no longer depend on manual re-selection/reopen.
- Lower probability of "first TX ok, next TX silent" behavior.

## 5) Audio device/channel persistence fixes

### Problem

Stored channel selections could become invalid after device re-enumeration, resulting in silent TX/RX.

### Applied changes

- channel combo width/contents policy adjusted for translated UI labels.
- persisted channel values revalidated against runtime-supported channels.
- automatic fallback to first valid channel if persisted value is invalid.
- explicit revalidation pass after setting restored channel indices.

### Result

- Less risk of silent audio due to stale or unsupported channel settings.

## 6) CAT UI behavior for DX Lab style rigs

### Problem

TX audio source section could be disabled when CAT capability probing was incomplete in proxy/backend flows.

### Applied change

- TX audio source group kept enabled for `DX Lab` rig path, allowing persisted preference management.

### Result

- predictable config experience for DX Lab integration path.

## 7) Legacy profile compatibility (FT2 frequencies)

### Problem

Some imported WSJT-X/legacy profiles lacked FT2 entries, leaving band selection unusable in FT2 mode.

### Applied change

- FT2 frequency rows auto-merged from defaults when missing.

### Result

- FT2 mode remains operable even with old profile data.

## 8) Branding and runtime UX consistency

### Applied changes

- graph windows title switched to Decodium branding.
- pre-release blocking popup removed from runtime path.
- title string updated with fork identity/version.

## 9) Support logging

Path:

- `~/Library/Application Support/ft2/tx-support.log`

Modes:

- default compact logging for critical events,
- verbose mode via `FT2_TX_VERBOSE_LOG=1`.

Purpose:

- isolate root cause of PTT/audio state mismatches in field tests.

## 10) CI/release packaging alignment

`build-macos.yml` updated to package `ft2.app` artifacts and align launcher/executable naming with the migrated bundle layout.
