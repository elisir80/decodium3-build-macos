# Note di Documentazione (Italiano) - 1.6.1

- Release corrente: `1.6.1`
- Ciclo aggiornamento: `1.6.0 -> 1.6.1`

## Cambi Tecnici Principali (`1.6.0 -> 1.6.1`)

- I path runtime attivi JT4, JT9 e JT65 sono ora mantenuti sul decode stack nativo C++.
- I path runtime attivi Q65 e WSPR sono Fortran-free, ed Echo gira ora sul runtime/tool path nativo C++.
- La superficie runtime mantenuta non porta piu' lo storico naming FFT `four2a` ne' i relativi residui di cleanup ABI legacy.
- Rimossi sorgenti Fortran obsoleti da `lib/`, `qmap/libqmap/`, `map65/libm65/` e dal vecchio tree tool Echo.
- Aggiunti fix Linux di build/startup per `mainwindow.cpp`, inizializzazione differita client, `QSocketNotifier`, teardown logging Qt e linkage GNU ld dei compare tool.
- Il packaging release macOS genera ora `.icns` tramite helper Python deterministico.
- Metadati versione, default workflow, documenti release e note GitHub sono allineati a `1.6.1`.

## Artifact Release

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort / sperimentale, se generato)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`

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
- [RELEASE_NOTES_1.6.1.md](../RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](./GITHUB_RELEASE_BODY_1.6.1.md)
