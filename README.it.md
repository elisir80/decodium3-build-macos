# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.0

Questo fork confeziona Decodium 3 FT2 per macOS e Linux AppImage, con lavoro specifico su Quick QSO FT2, fix di sequenziamento QSO, hardening AutoCQ, aggiornamenti decoder e tooling certificati Decodium mantenuti in questo repository.

Release stabile corrente: `1.5.0`.

## Novita' 1.5.0 (`1.4.9 -> 1.5.0`)

- Startup audio:
- aggiunto recovery automatico RX quando le periferiche sono selezionate correttamente ma all'avvio l'audio resta muto.
- la riapertura stream e il riarmo del monitor replicano il percorso di recovery manuale "Preferenze Audio -> OK".
- Flusso QSO e log:
- corretto il `73` finale in FT8, FT4 e FT2 standard a 5 messaggi quando il corrispondente manda prima `RR73` o `73`.
- corretti diversi path di log in FT2 Quick QSO, compreso il fallback "log dopo il mio 73".
- mappa DX e campi DX attivi vengono ora puliti correttamente quando l'app torna a CQ a QSO chiuso.
- AutoCQ:
- il blocco dei recent-worked impedisce ora i doppi richiami immediati dello stesso nominativo su tutti i path di selezione.
- il passaggio al caller successivo resetta retry, report e stato QSO prima di iniziare il nuovo contatto.
- in FT8 il timeout dei retry conta ora solo i periodi realmente persi.
- `debug.txt` traccia ora cambio partner, start queue, handoff, progress retry e skip dei nominativi appena lavorati.
- Protocollo/runtime FT2:
- importato il fix upstream del watchdog rescue.
- aggiunto il decoder LDPC dedicato FT2 e agganciato il triggered decode FT2 a quel path.
- allineati i decoder LDPC condivisi al refresh upstream Normalized Min-Sum.
- Quick QSO:
- aggiunto il bottone `Quick QSO` come alias UI del profilo FT2 `2 msg`.
- il flow Quick QSO corrente e' stato allineato allo schema corto richiesto per FT2 mantenendo backward compatibility per le varianti `TU` piu' vecchie.
- Certificati/tooling:
- aggiunti loader/autoload certificati Decodium e indicatore stato nella finestra principale.
- aggiunto `tools/generate_cert.py` per generare file certificato `.decodium`.

## Artifact Release

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

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
- accesso rete consigliato per NTP, DX Cluster e workflow online

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
- [RELEASE_NOTES_1.5.0.md](RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](doc/GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](CHANGELOG.md)
