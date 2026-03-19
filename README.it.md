# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.1

Questo fork confeziona Decodium 3 FT2 per macOS e Linux AppImage, con fix di chiusura QSO FT2/FT4/FT8, hardening della state machine AutoCQ, controllo aggiornamenti interno, sync decoder da upstream e tooling certificati Decodium mantenuti in questo repository.

Release stabile corrente: `1.5.1`.

## Novita' 1.5.1 (`1.5.0 -> 1.5.1`)

- Aggiornamenti interni:
- aggiunto controllo update interno contro GitHub Releases all'avvio.
- aggiunta voce `Help > Check for updates...`.
- l'updater apre ora direttamente l'asset corretto per la piattaforma corrente invece della sola pagina release generica.
- Flusso QSO e log:
- corretti piu' path tardivi FT2/FT4/FT8 in cui l'app poteva continuare a mandare `73/RR73`, perdere il log finale o non recuperare una chiusura ritardata.
- corretto il caso in cui il `73/RR73` finale del partner arrivava dopo che la stazione locale aveva gia' inviato il proprio signoff.
- migliorato il recovery del final-ack tardivo dopo timeout, cosi' un `73/RR73` ritardato puo' ancora essere messo a log correttamente.
- AutoCQ:
- corretto il riuso di partner stantii dopo il ritorno a CQ.
- corretti i casi di caller diretto decodificato ma con l'app che continuava a trasmettere CQ invece di armare `Tx2`.
- corretto il primo reply FT2 diretto che poteva usare un report stantio del QSO precedente invece dell'SNR reale del caller corrente.
- esteso il blocco recent-work e abandoned-partner per ridurre i richiami duplicati dopo chiusure differite.
- Mappa e identita':
- corretta la live world map che poteva mostrare un falso collegamento attivo mentre stavi trasmettendo solo CQ.
- allineato l'identificativo software inviato a PSK Reporter esattamente alla stringa mostrata nella barra del titolo.
- Diagnostica/processo:
- esteso `debug.txt` con tracing piu' ricco per armo caller diretto, cleanup partner stantio, recovery late signoff e selezione asset updater.
- versione UI locale, default workflow e documentazione release sono ora allineati alla semver `1.5.1`.

## Artifact Release

- `decodium3-ft2-1.5.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage.sha256.txt`

## Requisiti Minimi Linux

Hardware:

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM minima 4 GB (consigliati 8 GB)
- almeno 500 MB liberi su disco
- display 1280x800 o superiore consigliato
- hardware radio/CAT/audio secondo la propria stazione

Software:

- Linux `x86_64` con `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire
- ambiente desktop capace di eseguire AppImage Qt5
- accesso rete consigliato per NTP, DX Cluster e PSK Reporter

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
- [RELEASE_NOTES_1.5.1.md](RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](doc/GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](CHANGELOG.md)
