# Notas de Documentacion (Espanol) - 1.5.0

Este indice agrupa la documentacion orientada a release del ciclo actual del fork.

- Release actual: `1.5.0`
- Ciclo de actualizacion: `1.4.9 -> 1.5.0`
- Foco principal: recuperacion audio al arrancar, correccion QSO FT8/FT4/FT2, estabilidad AutoCQ, Quick QSO FT2, sync de decoders y tooling de certificados.

## Cambios Tecnicos Principales (`1.4.9 -> 1.5.0`)

- recuperacion automatica RX audio al arranque cuando los dispositivos guardados estan presentes pero RX sigue mudo.
- fixes del `73` final en FT8, FT4 y FT2 estandar.
- refactor FT2 Quick QSO y boton `Quick QSO` conectado a FT2 `2 msg`.
- prevencion duplicate-rework AutoCQ, reset de estado de cola y conteo retry sobre periodos reales.
- path LDPC dedicado FT2 y alineacion de decoders compartidos Normalized Min-Sum.
- soporte certificados Decodium y herramienta `tools/generate_cert.py`.

## Artefactos Release

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- 500 MB libres en disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Arranque

macOS quarantine:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extract-run:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Ficheros Relacionados

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_1.5.0.md](../RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](./GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](../CHANGELOG.md)
