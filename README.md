# Decodium 3 FT2 (macOS fork)

Fork by **Salvatore Raccampo 9H1SR**.

This repository contains the Decodium 3 FT2 source tree plus macOS-focused
build, packaging, compatibility, and runtime fixes.

Latest stable release line:

- `v1.0.6` (macOS arm64)
- Compatibility target: macOS Sequoia (15.x) and Tahoe (26.x)

## Highlights in v1.0.6

- startup no longer fails with a fatal `Sub-process error` when a reusable
  lingering `jt9` shared-memory segment exists;
- shared-memory startup now reuses a valid segment and keeps a hard stop only
  for invalid segment size.

## Language Guides

- British English: `README.en-GB.md`
- Italiano: `README.it.md`

## Changelog

- `CHANGELOG.md`

## Documentation

- British English: `doc/README.en-GB.md`
- Italiano: `doc/README.it.md`
