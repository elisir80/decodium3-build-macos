# Decodium 3 FT2 (Fork macOS) - v1.4.9

Este fork empaqueta Decodium 3 FT2 para macOS y Linux AppImage, con fixes adicionales de runtime FT2, actualizaciones del decoder y automatizacion release mantenidos en este repositorio.

Release estable actual: `v1.4.9`.

## Cambios en v1.4.9 (`v1.4.8 -> v1.4.9`)

- Decoder FT2:
- escala LLR del triggered decode FT2 subida de `2.83` a `3.2`.
- normalizacion de los tres flujos LLR FT2 antes del decode LDPC.
- anadida channel estimation adaptativa con metricas FT2 MMSE-equalized para canales con fading.
- introducido `ft2_channel_est.f90` y enlazado al build Fortran FT2.
- Runtime / async FT2:
- anadido el nuevo visualizador dedicado FT2 async.
- S-meter async FT2 alimentado desde el path real de decode FT2.
- polling async FT2 reducido a `100 ms`.
- fan-out `postDecode()` / `write_all()` diferido para mantener reactivo el path async.
- Startup y AutoCQ FT2:
- el arranque ya no fuerza `FT2`; se respetan otra vez modo/frecuencia guardados.
- FT2 ahora engancha de inmediato la primera respuesta dirigida mientras estas llamando CQ.
- la adquisicion de un nuevo partner AutoCQ resetea correctamente contadores retry/miss sucios, evitando cambios prematuros de partner.
- UI / usabilidad:
- anadido menu `Language` en la barra principal.
- el idioma UI se guarda en settings y se reaplica al reinicio si no pasas un override CLI.
- las columnas de la ventana DX Cluster ahora son redimensionables por el usuario y persistentes entre sesiones.
- Linux / datos astronomicos:
- el lookup de `JPLEPH` cubre ahora paths AppImage, paths share Linux, directorio de trabajo actual y builds out-of-source mediante `CMAKE_SOURCE_DIR`.
- el packaging Linux AppImage ahora incluye `JPLEPH` dentro de `usr/share/wsjtx`.

## Artefactos de Release

- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- al menos 500 MB libres en disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Inicio

Si macOS bloquea el inicio:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Para evitar problemas debidos al sistema de archivos de solo lectura de las AppImage, se recomienda iniciar Decodium extrayendo primero la AppImage y ejecutando despues el programa desde la carpeta extraida.

Ejecutar los siguientes comandos en la terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Archivos Relacionados

- [README.md](README.md)
- [README.en-GB.md](README.en-GB.md)
- [README.it.md](README.it.md)
- [RELEASE_NOTES_v1.4.9.md](RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](doc/GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](CHANGELOG.md)
