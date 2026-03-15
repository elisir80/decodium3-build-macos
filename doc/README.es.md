# Notas de Documentacion (Espanol) - v1.4.8

Este indice agrupa la documentacion orientada a release del ciclo actual del fork.

- Release actual: `v1.4.8`
- Ciclo de actualizacion: `v1.4.7 -> v1.4.8`
- Foco principal: refinamientos timing/operator FT2, correccion signoff FT2, hardening remoto web, fixes bounded de cadenas y robustez release.

## Cambios Tecnicos Principales (`v1.4.7 -> v1.4.8`)

- FT2 ajustado a `103` simbolos con margen Tx reducido a `0.2 s`.
- anadido soporte FT2 `Speedy`, `D-CW` y `TX NOW`.
- FT2 ahora espera el ack final de la pareja antes del log y se detiene limpio sin log si se agotan los reintentos.
- dedupe async FT2 mas robusto contra hipotesis duplicadas en bins cercanos.
- remote web con token obligatorio fuera de loopback, sin wildcard CORS y validacion `Origin` WebSocket.
- fixes bounded-formatting en `lib/ptt.c`, `lib/ft2` y varios paths `map65`.
- packaging release macOS mas robusto frente a mounts DMG residuales de CPack.

## Artefactos de Release

- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- 500 MB libres en disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Inicio

macOS cuarentena:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extraer-y-ejecutar:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Archivos Relacionados

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_v1.4.8.md](../RELEASE_NOTES_v1.4.8.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](./GITHUB_RELEASE_BODY_v1.4.8.md)
- [CHANGELOG.md](../CHANGELOG.md)
