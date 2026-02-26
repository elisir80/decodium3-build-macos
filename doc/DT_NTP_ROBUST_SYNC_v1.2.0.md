# DT/NTP Robust Sync Architecture - Fork v1.2.0

Date: 2026-02-26

## Context

In real-world FT2 operation, timing quality is constrained by:

- local clock drift,
- audio-device drift,
- CAT/PTT latency variability,
- sparse or partially inconsistent NTP responses.

The v1.2.0 fork introduces a lock-preserving strategy that avoids abrupt timing swings while keeping responsiveness to true drift.

## Design principles

1. TX slot scheduling must remain tied to raw system time.
2. NTP is used for synchronization state and correction logic, not direct hard phase injection into slot scheduler.
3. Sparse server sets (`2-3`) must not be trusted for immediate medium/large jumps.
4. DT feedback must be conservative when NTP is healthy.

## Architecture overview

### A) NTP sample pipeline

1. Resolve and query a randomized subset of NTP servers.
2. Prefer IPv4 path when available (macOS path reliability).
3. Validate packet structure and echoed originate timestamp.
4. Reject RTT above configured threshold.
5. Reject absurd offsets (`MAX_OFFSET_MS` guard).

### B) Coherence filtering

Before offset application:

- build densest cluster within configurable window (`m_clusterWindowMs`),
- optionally tighten around existing lock (`m_lockWindowMs`),
- reject incoherent high-range sets.

This reduces mixed-cluster contamination (example: divergent server groups).

### C) Weak-sync gate

Offset updates are mediated by:

- deadband (`m_weakDeadbandMs`),
- standard confirmation count,
- strong-step confirmation count,
- emergency threshold for very large unavoidable corrections.

This prevents oscillation from jittery sample cycles.

### D) Sparse-jump guard (new in v1.2.0)

If lock exists and server count is low (`<=3`):

- jumps above `m_sparseJumpMs` require `m_sparseJumpConfirmNeeded` consecutive confirmations in same direction.

Effect:

- suppresses one-off `+/-100ms` class jumps from sparse cycles,
- still allows true drift over repeated consistent evidence.

### E) Hold behavior

On no-response cycles:

- maintain lock and report hold state when previous sync context is still valid,
- delay coarse fallback actions,
- avoid UI collapse to "no sync" when usable lock is still active.

### F) HTTP fallback behavior

Used only as safety net when UDP/NTP path fails.

With active lock:

- coarse HTTP jumps are rejected if outside tolerance,
- fallback failure keeps lock hold state instead of forcing desync.

## DT feedback behavior

DT correction loop now applies:

- adaptive EMA,
- per-step clamp,
- total clamp,
- decay on sample drought,
- additional conservatism when NTP is healthy (`isSynced && |offset| < 100ms`).

Coloring logic uses both:

- instantaneous DT quality (`m_avgDtValue`),
- accumulated correction magnitude (`m_dtCorrection_ms`).

This avoids misleading "green" status while correction remains heavily saturated.

## Default robust parameters in v1.2.0

- strong step threshold: `350ms`
- strong step confirm: `4`
- sparse jump threshold: `50ms`
- sparse jump confirm: `4`

These defaults were promoted from field-tested runtime env values.

## Environment overrides retained

All key guards remain overrideable for diagnostics and edge tuning:

- `FT2_NTP_WEAK_SYNC`
- `FT2_NTP_WEAK_DEADBAND_MS`
- `FT2_NTP_WEAK_STRONG_MS`
- `FT2_NTP_WEAK_EMERGENCY_MS`
- `FT2_NTP_WEAK_CONFIRM`
- `FT2_NTP_WEAK_STRONG_CONFIRM`
- `FT2_NTP_CLUSTER_WINDOW_MS`
- `FT2_NTP_LOCK_WINDOW_MS`
- `FT2_NTP_HTTP_LOCK_TOL_MS`
- `FT2_NTP_SPARSE_JUMP_MS`
- `FT2_NTP_SPARSE_JUMP_CONFIRM`
- `FT2_NTP_HTTP_HOLDOFF_MS`

## Difference versus original Raptor behavior

Compared with upstream Raptor baseline:

- added explicit lock-aware hold state management,
- added sparse-server jump confirmation layer,
- strengthened coherence/cluster filtering before apply,
- made HTTP fallback lock-safe (non-destructive),
- reduced DT aggressiveness when NTP is healthy,
- improved DT visual semantics to reflect correction saturation.

Operationally this trades a small amount of adaptation speed for a large reduction in false jumps and drift oscillation under imperfect network/server conditions.
