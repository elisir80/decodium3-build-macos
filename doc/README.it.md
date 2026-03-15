# Note di Documentazione (Italiano) - v1.4.7

Questo indice raccoglie la documentazione release-oriented del ciclo corrente del fork.

- Release corrente: `v1.4.7`
- Ciclo aggiornamento: `v1.4.6 -> v1.4.7`
- Focus principale: hardening runtime/decode FT2, continuita' AutoCQ, integrazione AutoSpot/DX Cluster e allineamento release.

## Cambi Tecnici Principali (`v1.4.6 -> v1.4.7`)

- guardia async Tx FT2 portata a `300 ms`.
- filtro false decode FT2 esteso con validazione prefissi `cty.dat`.
- rendering FT2 `TΔ` e normalizzazione marker resi piu' robusti per preservare l'allineamento colonne.
- stabilizzati lock partner / retry / ritorno a CQ dopo `73` confermato in AutoCQ.
- impostazioni con nuova sezione endpoint AutoSpot e flag enable.
- finestra DX Cluster ora interrogata via endpoint DxSpider configurabile con gestione telnet/prompt piu' robusta.
- dashboard web con toggle AutoSpot, feedback comandi migliore e preset modo piu' stabili.
- stato menu `Dati Astronomici` ora coerente con chiusura reale finestra.

## Artifact Release

- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_v1.4.7.md](../RELEASE_NOTES_v1.4.7.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](./GITHUB_RELEASE_BODY_v1.4.7.md)
- [CHANGELOG.md](../CHANGELOG.md)
