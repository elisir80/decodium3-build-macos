# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.7 (Italiano)

Per la versione bilingue completa (English + Italiano), vedere [README.md](README.md).

## Sintesi italiana

Questa release fork (`v1.3.7`) e' basata su Decodium v3.0 SE Raptor upstream e introduce i seguenti fix/aggiornamenti rispetto a `v1.3.6`:

- selezione contatti direttamente dal mappamondo con highlight marker e compilazione DX call/grid;
- nuova opzione configurazione `Map: single click starts Tx` per invertire logica single/double click mappa;
- visibilita' `View -> World Map` resa persistente tra riavvii;
- nuova finestra `Ionospheric Forecast` (dati HamQSL + immagine sole, refresh periodico);
- nuova finestra `DX Cluster` (spot live con filtro modo e banda corrente);
- rendering giorno/notte mappa migliorato e pulizia percorsi stale su fine QSO;
- layout controlli top migliorato in modalita' compatta/2 righe su display piccoli;
- fix affidabilita' decode all'avvio: timestamp sequence-start impostato su ingest audio prima del decode;
- fix affidabilita' segnali cross-thread `ModulatorState` (registrazione metatype Qt esplicita);
- stile UI predefinito impostato a `Fusion` per coerenza grafica cross-macOS;
- rimozione sorgente hardcoded del suffisso legacy revision: `Using:` su PSKReporter non mostra piu' `mod by IU8LMC...`.

## Target release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (12.x, sperimentale/best-effort)
- Linux x86_64 AppImage

## Requisiti minimi Linux

- Architettura: `x86_64` (64 bit)
- CPU: dual-core 2.0 GHz o superiore
- RAM: minimo 4 GB (consigliati 8 GB)
- Spazio disco: almeno 500 MB liberi (AppImage + log + impostazioni)
- Runtime:
  - Linux con `glibc >= 2.35` (classe Ubuntu 22.04 o successiva)
  - supporto `libfuse2` / FUSE2 per avvio AppImage
  - stack audio ALSA, PulseAudio o PipeWire
- Integrazione stazione: hardware CAT/audio secondo setup radio

## Comando macOS (quarantena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentazione

- [RELEASE_NOTES_v1.3.7.md](RELEASE_NOTES_v1.3.7.md)
- [CHANGELOG.md](CHANGELOG.md)
- [README.es.md](README.es.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- [doc/README.es.md](doc/README.es.md)
