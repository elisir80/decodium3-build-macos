# Decodium (Fork macOS/Linux) - 1.6.2

- Release stabile corrente: `1.6.2`
- Ciclo aggiornamento: `1.6.1 -> 1.6.2`

## Novita' 1.6.2 (`1.6.1 -> 1.6.2`)

- irrobustito l'invio UDP multicast per integrazioni logger LAN, migliorando la risoluzione delle interfacce multicast e aggiungendo il fallback sulla route di default quando l'invio forzato per interfaccia fallisce.
- migliorato lo startup TCI per radio asincrone stile SunSDR / ExpertSDR3, cosi' Decodium non fallisce piu' troppo presto mentre aspetta stato ready/power.
- migliorato il recupero audio intermittente all'avvio quando il CAT e' scollegato o la cache dei device audio Qt torna temporaneamente nulla.
- completata la migrazione nativa C++ mantenuta di `qmap/libqmap` e rimosso l'ultimo backend Fortran CMake attivo cross-platform.
- completata la migrazione astronomia/effemeridi usata dal path applicativo mantenuto e rimossa dal build CMake la vecchia catena astronomica Fortran attiva.
- ripuliti dal tree mantenuto ulteriori sorgenti Fortran obsoleti e archivi WSPR/JT/QSO50, mantenendo `map65/libm65` confinato alle sole build CMake Windows.
- mantenuta l'esclusione permanente di `build-arm-output/` dallo staging sorgenti e dal tracking git.
- allineati metadati versione locali, default workflow, documenti release e note GitHub alla semver `1.6.2`.

## Target Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / sperimentale)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

## Asset Release

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage.sha256.txt`

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
- permessi seriale/USB richiesti da CAT e radio esterne

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
- [RELEASE_NOTES_1.6.2.md](RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](doc/GITHUB_RELEASE_BODY_1.6.2.md)
