# Note di Documentazione (Italiano) - 1.6.2

- Release corrente: `1.6.2`
- Ciclo aggiornamento: `1.6.1 -> 1.6.2`

## Cambi Tecnici Principali (`1.6.1 -> 1.6.2`)

- La consegna UDP multicast e' piu' robusta per i workflow LAN logger grazie a migliore risoluzione interfacce, filtro protocollo e fallback sulla route di default.
- Lo startup TCI ora tollera radio asincrone stile SunSDR / ExpertSDR3 che pubblicano ready/power in ritardo.
- Il recupero audio all'avvio ora ritenta dopo refresh della cache device audio Qt quando il CAT e' scollegato o l'enumerazione corre in race con la UI.
- `qmap/libqmap` e' stato migrato completamente a C++ nativo, rimuovendo l'ultimo backend Fortran CMake attivo cross-platform.
- Il path astronomia/effemeridi attivo e' stato migrato a C++ nativo e la vecchia catena astronomica Fortran attiva e' stata rimossa dal build mantenuto.
- Rimossi ulteriori sorgenti Fortran obsoleti e archivi WSPR/JT/QSO50 dal tree mantenuto, mentre `map65/libm65` resta solo Windows in CMake.
- Metadati versione, default workflow, documenti release e note GitHub sono allineati a `1.6.2`.

## Artifact Release

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort / sperimentale, se generato)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`

## Requisiti Minimi Linux

- CPU `x86_64` con SSE2 oppure CPU `aarch64` / ARM64 64-bit
- minimo 4 GB RAM, 500 MB liberi su disco
- distribuzione Linux 64-bit con sessione desktop X11 o Wayland capace di eseguire AppImage Qt5
- `glibc >= 2.35` per Linux `x86_64`
- `glibc >= 2.38` per Linux `aarch64` *(baseline Debian Trixie)*
- `libfuse2`, ALSA/PulseAudio/PipeWire e permessi seriale/USB secondo necessita'

## Guida Avvio

Workaround quarantena macOS:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Eseguire i seguenti comandi nel terminale:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## File Correlati

- [README.it.md](../README.it.md)
- [RELEASE_NOTES_1.6.2.md](../RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](./GITHUB_RELEASE_BODY_1.6.2.md)
