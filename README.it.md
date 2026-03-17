# Decodium 3 FT2 (Fork macOS) - v1.4.9

Questo fork confeziona Decodium 3 FT2 per macOS e Linux AppImage, con fix aggiuntivi di runtime FT2, aggiornamenti decoder e automazione release mantenuti in questo repository.

Release stabile corrente: `v1.4.9`.

## Novita' v1.4.9 (`v1.4.8 -> v1.4.9`)

- Decoder FT2:
- scalatura LLR del triggered decode FT2 alzata da `2.83` a `3.2`.
- normalizzazione di tutti e tre i flussi LLR FT2 prima del decode LDPC.
- aggiunta channel estimation adattiva con metriche FT2 MMSE-equalized per canali con fading.
- introdotto `ft2_channel_est.f90` e agganciato al build Fortran FT2.
- Runtime / async FT2:
- aggiunto il nuovo visualizzatore dedicato FT2 async.
- S-meter async FT2 alimentato dal path reale di decode FT2.
- polling async FT2 ridotto a `100 ms`.
- fan-out `postDecode()` / `write_all()` differito per mantenere reattivo il path async.
- Startup e AutoCQ FT2:
- l'avvio non forza piu' `FT2`; modo/frequenza salvati vengono rispettati di nuovo.
- FT2 ora aggancia subito la prima risposta diretta mentre stai chiamando CQ.
- l'aggancio di un nuovo partner AutoCQ ora resetta correttamente contatori retry/miss sporchi, evitando cambi partner prematuri.
- UI / usabilita':
- aggiunto menu `Language` nella barra menu principale.
- la lingua UI viene salvata nelle impostazioni e riapplicata al riavvio se non passi un override CLI.
- le colonne della finestra DX Cluster sono ora ridimensionabili dall'utente e persistenti tra sessioni.
- Linux / dati astronomici:
- il lookup di `JPLEPH` copre ora path AppImage, path share Linux, working directory corrente e build out-of-source tramite `CMAKE_SOURCE_DIR`.
- il packaging Linux AppImage include ora `JPLEPH` dentro `usr/share/wsjtx`.

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
- almeno 500 MB liberi su disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

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

## File Collegati

- [README.md](README.md)
- [README.en-GB.md](README.en-GB.md)
- [README.es.md](README.es.md)
- [RELEASE_NOTES_v1.4.9.md](RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](doc/GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](CHANGELOG.md)
