# Decodium (Fork macOS/Linux) - 1.6.1

- Release stabile corrente: `1.6.1`
- Ciclo aggiornamento: `1.6.0 -> 1.6.1`

## Novita' 1.6.1 (`1.6.0 -> 1.6.1`)

- completata la migrazione nativa C++ mantenuta del runtime JT legacy attivo, coprendo i path decode JT4, JT9 e JT65.
- promossi a implementazioni native Fortran-free i path runtime attivi Q65 e WSPR e completata la migrazione a C++ nativo del runtime/tool path Echo.
- rimosso dalla superficie app/runtime mantenuta il naming legacy ABI residuo del path attivo, incluso lo storico naming FFT `four2a`.
- ripuliti sorgenti Fortran obsoleti e file di compatibilita' da `lib/`, `qmap/libqmap/`, `map65/libm65/` e dal vecchio path tool Echo.
- corrette regressioni Linux di build/startup in `mainwindow.cpp`, nell'inizializzazione differita dei client di rete, nella gestione `QSocketNotifier`, nel teardown logging Qt e nel link GNU ld dei target compare/sim.
- corretto il blocco packaging macOS `Invalid Iconset` generando il file `.icns` con un helper Python deterministico.
- mantenuta l'esclusione permanente di `build-arm-output/` dallo staging sorgenti e dal tracking git.
- allineati metadati versione locali, default workflow, documentazione release e note GitHub alla semver `1.6.1`.

## Target Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / sperimentale)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

## Artifact Release

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

## Requisiti Minimi Linux

Hardware:

- CPU `x86_64` con SSE2, oppure CPU `aarch64` / ARM64 64-bit
- dual-core 2.0 GHz o meglio, oppure SoC ARM64 moderno equivalente
- minimo 4 GB RAM (8 GB raccomandati)
- almeno 500 MB liberi su disco
- hardware audio/CAT/seriale/USB adatto al weak-signal

Software:

- distribuzione Linux 64-bit con sessione desktop X11 o Wayland capace di eseguire AppImage Qt5
- AppImage Linux `x86_64`: `glibc >= 2.35`
- AppImage Linux `aarch64`: `glibc >= 2.38` *(baseline Debian Trixie)*
- `libfuse2` / FUSE2 per montare direttamente l'AppImage
- ALSA, PulseAudio o PipeWire
- permessi di accesso seriale/USB per CAT o dispositivi esterni

## Guida Avvio

Se macOS blocca l'avvio:

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

- [README.md](README.md)
- [README.en-GB.md](README.en-GB.md)
- [README.es.md](README.es.md)
- [RELEASE_NOTES_1.6.1.md](RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](doc/GITHUB_RELEASE_BODY_1.6.1.md)
