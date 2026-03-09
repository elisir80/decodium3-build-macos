# Notas de Documentacion (Espanol)

## Alcance

Notas especificas del fork macOS dentro de este repositorio.

## Contexto de release actual

- Ultima release estable: `v1.4.2`
- Objetivos: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (experimental), Linux x86_64 AppImage

## Notas de build y runtime

### Salida de compilacion

- `build/ft2.app/Contents/MacOS/ft2`
- ejecutables auxiliares en el mismo bundle (`jt9`, `wsprd`)

### Memoria compartida en macOS

- Este fork usa `SharedMemorySegment` con backend `mmap` en Darwin.
- El flujo de release no depende de ajustes `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Resumen consolidado v1.4.2

- Peticiones LotW migradas de GET URL con credenciales a POST HTTPS.
- Politica estricta de redirect para LotW con credenciales (HTTPS + host esperado).
- Bind web remoto LAN/WAN ahora requiere token >= 12 caracteres.
- Dialogo de ajustes Linux ajustado a geometria visible de pantalla.
- Hardening decode async con stack/thread-pool dedicado y guardas anti-solapamiento.
- Comportamiento de controles FT2 finalizado:
  - Async L2 ON por defecto en FT2 y OFF automatico fuera de FT2,
  - `Bloquear Freq Tx` y `Tx par/1°` ocultos en FT2.
- Acciones `View -> Ionospheric Forecast` y `View -> DX Cluster` restauradas.
- Eventos TX del dashboard remoto preservados correctamente durante refresh.

### Artefactos de release

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`
- `decodium3-ft2-<version>-linux-x86_64.AppImage`
- `decodium3-ft2-<version>-linux-x86_64.AppImage.sha256.txt`

### Requisitos minimos Linux

- Arquitectura: `x86_64`
- CPU: dual-core 2.0 GHz o superior
- RAM: 4 GB minimo
- Runtime: `glibc >= 2.35`, `libfuse2`/FUSE2, ALSA/PulseAudio/PipeWire

### Recomendacion AppImage

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

### Comando cuarentena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Referencias

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.4.2.md`
- `doc/GITHUB_RELEASE_BODY_v1.4.2.md`
- `doc/WEBAPP_SETUP_GUIDE.es.md`
- `doc/WEBAPP_SETUP_GUIDE.en-GB.md`
- `doc/WEBAPP_SETUP_GUIDE.it.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
