# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.2

Questo fork confeziona Decodium 3 FT2 per macOS e Linux AppImage, con fix di chiusura QSO FT2/FT4/FT8, hardening AutoCQ, aggiornamenti decoder FT2 da upstream, recovery audio all'avvio, supporto updater, controlli web app allineati, traduzioni UI complete e tooling certificati Decodium mantenuti in questo repository.

Release stabile corrente: `1.5.2`.

## Novita' 1.5.2 (`1.5.1 -> 1.5.2`)

- Correttezza runtime FT2 / FT4 / FT8:
- irrobustiti i path standard di late-signoff, late-final-ack, partner stantio, retry e direct-reply, cosi' i QSO completati vanno a log correttamente e non restano in loop su `73` / `RR73`.
- ripristinato il lock QSO attivo usato da `Wait Features + AutoSeq` in FT4/FT8, cosi' un QSO in corso non viene interrotto dalla logica di chiamata in coda.
- corretto il riuso di nominativi e report stantii quando AutoCQ passa dal CQ a un nuovo caller diretto o da una stazione in coda alla successiva.
- Protocollo FT2 e decoder:
- allineato il codice decoder FT2 al path LDPC FT2 dedicato upstream e aggiornato il supporto bitmetrics FT2.
- completato il flow FT2 `2 msg / 3 msg / 5 msg`, inclusi `Quick QSO`, gestione TU mixed-mode e routing del QSO corto FT2 corrente.
- nascosti i tag decoder FT2 async/triggered (`T`, `aN`) dalle finestre decode e collassati i duplicati async/sync in un solo decode logico.
- Audio / UI / controllo remoto:
- rafforzato il recovery RX-audio all'avvio e al wake: il monitor-on arma ora health-check e reopen automatico degli stream se l'audio resta muto.
- portata la web app piu' vicina alla parita' desktop con `Manual TX`, `Speedy`, `D-CW`, card async, `Quick QSO` e controlli `2/3/5 msg`.
- completati tutti i file traduzione UI bundle, cosi' menu, popup e stringhe interne non escono piu' con buchi `unfinished`.
- Piattaforma / tooling:
- aggiunti load/autoload/stato certificati Decodium piu' il generatore locale `tools/generate_cert.py`.
- mantenuto l'updater interno e rifinita l'apertura diretta dell'asset macOS/Linux piu' adatto.
- centralizzato il versioning release tramite `fork_release_version.txt`, cosi' build locali, workflow e release GitHub restano allineati.
- Mappa e identita':
- corretti i link live-map stantii o falsi durante il ritorno a CQ o il CQ puro.
- allineata l'identita' PSK Reporter esattamente alla stringa del titolo applicazione.

## Artifact Release

- `decodium3-ft2-1.5.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage.sha256.txt`

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
- accesso rete consigliato per NTP, DX Cluster, PSK Reporter, updater e funzioni online

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
- [RELEASE_NOTES_1.5.2.md](RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](doc/GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](CHANGELOG.md)
