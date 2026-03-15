# Decodium 3 FT2 (Fork macOS) - v1.4.7

Fork mantenido por **Salvatore Raccampo 9H1SR**.

Para la vista general bilingue, ver [README.md](README.md).

## Cambios en v1.4.7 (`v1.4.6 -> v1.4.7`)

- Hardening runtime/decode FT2:
- guardia async Tx FT2 aumentada de `100 ms` a `300 ms`.
- anadido filtro de false decode FT2 basado en validacion de prefijos `cty.dat`.
- renderizado FT2 `TΔ` reescrito con parsing estructurado para mantener columnas alineadas con filas packed y marcadores variables.
- normalizacion del marcador FT2 mantenida coherente cuando aparece `~` en el flujo decode.
- Secuenciacion AutoCQ/QSO:
- lock de pareja activa mas fuerte para evitar takeover por otros callers durante un QSO en curso.
- logica de periodos perdidos alineada con el presupuesto real de `5` reintentos.
- estado stale de periodos perdidos limpiado cuando una respuesta valida de caller/pareja hace avanzar el QSO.
- tras `73` confirmado por la pareja, AutoCQ vuelve a CQ en lugar de enviar un `RR73` extra.
- AutoSpot / DX Cluster / dashboard web:
- nueva seccion de ajustes para endpoint AutoSpot (`host`, `puerto`, flag enable).
- la ventana DX Cluster ahora consulta un nodo DxSpider telnet configurable, no el feed HamQTH fijo.
- mejor manejo de prompts telnet, fetch silencioso `UNSET/DX`, fallback de login y diagnostico submit/verify en `autospot.log`.
- la dashboard/web app ahora incluye toggle AutoSpot, feedback mas claro de comandos/auth y presets por modo mas estables en save/apply.
- Correcciones desktop/runtime:
- la opcion de menu `Datos Astronomicos` se desmarca al cerrar la ventana con la `X`.
- el dialogo de ajustes en Linux mantiene scroll en paginas de tabs sobredimensionadas, con botones de accion siempre accesibles.

## Objetivos de release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (experimental / best effort)
- Linux x86_64 AppImage

## Requisitos minimos Linux

- Arquitectura: `x86_64` (64 bits)
- CPU: dual-core 2.0 GHz o superior
- RAM: 4 GB minimo (8 GB recomendado)
- Disco: al menos 500 MB libres (AppImage + logs + configuracion)
- Runtime/software:
- Linux con `glibc >= 2.35` (clase Ubuntu 22.04 o posterior)
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire
- Integracion de estacion: hardware CAT/audio segun configuracion de radio

## Recomendacion de arranque AppImage en Linux

Para evitar problemas debidos al sistema de archivos de solo lectura de las AppImage, se recomienda iniciar Decodium extrayendo primero la AppImage y ejecutando despues el programa desde la carpeta extraida.

Ejecutar los siguientes comandos en la terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Comando macOS (cuarentena)

Si Gatekeeper bloquea el inicio, ejecutar:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Build local

```bash
cmake --build build -j6
./build/ft2.app/Contents/MacOS/ft2
```

## Documentacion

- [README.en-GB.md](README.en-GB.md)
- [README.it.md](README.it.md)
- [RELEASE_NOTES_v1.4.7.md](RELEASE_NOTES_v1.4.7.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](doc/GITHUB_RELEASE_BODY_v1.4.7.md)
- [doc/README.es.md](doc/README.es.md)
