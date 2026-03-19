# Note di Documentazione (Italiano) - 1.5.1

Questo indice raccoglie la documentazione release-oriented del ciclo corrente del fork.

- Release corrente: `1.5.1`
- Ciclo aggiornamento: `1.5.0 -> 1.5.1`
- Focus principale: updater interno, correttezza late-signoff FT2/FT4/FT8, hardening AutoCQ sulle direct reply, pulizia mappa e allineamento PSK Reporter.

## Cambi Tecnici Principali (`1.5.0 -> 1.5.1`)

- checker update GitHub integrato con scelta diretta dell'asset corretto per macOS/Linux.
- recovery late-signoff FT2/FT4/FT8 cosi' `73/RR73` ritardati possono ancora andare a log.
- fix AutoCQ sui caller diretti quando si esce da CQ e si deve armare subito `Tx2`.
- fix del report stantio sul primo reply FT2 diretto.
- pulizia mappa in CQ e allineamento stringa titolo usata verso PSK Reporter.

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

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM minima 4 GB (consigliati 8 GB)
- 500 MB liberi su disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guida Avvio

macOS quarantine:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extract-run:

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
- [RELEASE_NOTES_1.5.1.md](../RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](./GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](../CHANGELOG.md)
