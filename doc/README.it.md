# Note di Documentazione (Italiano) - v1.4.9

Questo indice raccoglie la documentazione release-oriented del ciclo corrente del fork.

- Release corrente: `v1.4.9`
- Ciclo aggiornamento: `v1.4.8 -> v1.4.9`
- Focus principale: miglioramenti decoder FT2, feedback visivo async FT2, correttezza startup/AutoCQ FT2, packaging dati astronomici Linux e miglioramenti UI lingua/cluster.

## Cambi Tecnici Principali (`v1.4.8 -> v1.4.9`)

- Il triggered decode FT2 usa ora scalatura LLR `3.2` e normalizzazione esplicita di tutti e tre i rami LLR FT2.
- aggiunta channel estimation adattiva FT2 con metriche MMSE-equalized tramite `ft2_channel_est.f90`.
- nuovo visualizzatore dedicato FT2 async, con S-meter aggiornato dal decode reale e polling a `100 ms`.
- l'avvio FT2 non viene piu' forzato; modo/frequenza salvati vengono rispettati.
- la gestione risposta diretta immediata FT2 e il reset dei contatori retry AutoCQ riducono primi caller persi e cambi partner prematuri.
- nuovo menu `Language` persistente in settings e ricaricato da `main.cpp`.
- colonne DX Cluster ridimensionabili e stato header persistente.
- lookup `JPLEPH` esteso ad AppImage, path share Linux, working directory e `CMAKE_SOURCE_DIR`, con packaging AppImage che ora include il file.

## Artifact Release

- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage.sha256.txt`

## Requisiti Minimi Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM minima 4 GB (consigliati 8 GB)
- 500 MB liberi su disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guida Avvio

macOS quarantena:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage estrai-ed-esegui:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## File Collegati

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_v1.4.9.md](../RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](./GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](../CHANGELOG.md)
