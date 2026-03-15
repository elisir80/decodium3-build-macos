# Decodium 3 FT2 (Fork macOS) - v1.4.8

Fork mantenido por **Salvatore Raccampo 9H1SR**.

Para la vista general bilingue, ver [README.md](README.md).

## Cambios en v1.4.8 (`v1.4.7 -> v1.4.8`)

- Timing FT2 y workflow de operador:
- `NUM_FT2_SYMBOLS` alineado de `105` a `103` y margen Tx FT2 reducido de `0.5 s` a `0.2 s` sobre la duracion de onda.
- anadido soporte FT2 para workflows `Speedy`, `D-CW` y boton `TX NOW` para envio inmediato o precargado.
- la logica AutoSeq FT2 sigue siendo coherente aunque la checkbox AutoSeq estandar este oculta en el modo FT2.
- Correccion QSO/signoff FT2:
- FT2 ya no manda un QSO al log antes de que el signoff local haya sido transmitido y haya llegado el ack final real de la pareja.
- si FT2 agota el presupuesto de reintentos RR73/73 sin ack de la pareja, la transmision se detiene sin autolog.
- el manejo de `RR73/73` de la pareja ya no salta el `73` local en flujos FT2 AutoCQ/auto-sequence.
- la supresion async de duplicados FT2 ahora elimina hipotesis repetidas con el mismo payload en bins de audio cercanos, evitando intercambios duplicados en el flujo decode.
- Hardening Remote Web / dashboard:
- RemoteCommandServer ahora se bloquea en bind no-loopback cuando no hay token de acceso configurado.
- en bind no-loopback el token debe tener al menos `12` caracteres.
- se eliminaron los headers CORS wildcard del API HTTP remoto.
- las conexiones WebSocket ahora requieren un `Origin` same-origin permitido en lugar de aceptar origanes arbitrarios del navegador.
- Seguridad de cadenas/buffer:
- corregido el riesgo concreto de overflow al formatear la puerta COM en `lib/ptt.c`.
- aplicada formateacion bounded al codigo PTT relacionado en `lib/ft2` y `map65`.
- reforzados los paths `map65` para device-info, labels de estado y texto astronomico.
- Pipeline release/build:
- el packaging macOS ahora tolera imagenes DMG montadas residuales de CPack sin fallar toda la release cuando el staging ya es valido.

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
- [RELEASE_NOTES_v1.4.8.md](RELEASE_NOTES_v1.4.8.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](doc/GITHUB_RELEASE_BODY_v1.4.8.md)
- [doc/README.es.md](doc/README.es.md)
