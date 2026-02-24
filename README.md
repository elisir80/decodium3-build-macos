# Decodium 3 FT2 (macOS fork)

Fork by **Salvatore Raccampo 9H1SR**.

This repository contains the Decodium 3 FT2 source tree plus macOS-focused
build, packaging, compatibility, and runtime fixes.

Latest stable release line:

- `v1.1.0` (macOS arm64 + x86_64 Intel)
- Compatibility target: macOS Sequoia (15.x), Tahoe (26.x), and Intel Sequoia (15.x)

## Highlights in v1.1.0

- audio output auto-rebind recovery on transient runtime failures;
- improved output-device stability and non-fatal underrun handling;
- improved UDP/network interface handling (preserve selected interfaces even when temporarily unavailable);
- NTP hardening and fallback reliability improvements, plus status-bar "last sync age";
- DT timing improvements for remote operation with configurable clock compensation limits in `Settings -> Advanced`;
- release automation kept for dual architecture artifacts (arm64 + x86_64 Intel).

## If ft2.app Does Not Start (macOS)

Run from Terminal:

```bash
xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Language Guides

- British English: `README.en-GB.md`
- Italiano: `README.it.md`

## Changelog

- `CHANGELOG.md`

## Documentation

- British English: `doc/README.en-GB.md`
- Italiano: `doc/README.it.md`
