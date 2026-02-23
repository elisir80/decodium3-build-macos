# Note di Documentazione (Italiano)

## Scopo

Questo documento descrive la documentazione specifica del fork macOS.
Non sostituisce la guida utente completa WSJT-X in `doc/user_guide/en/`.

## Contesto release attuale

- Ultima release stabile: `v1.0.9`
- Target compatibilita': macOS Sequoia (15.x), Tahoe (26.x), e Intel Sequoia (15.x)

## Cambi principali in v1.0.9

- La GUI principale ora ha un terzo pannello integrato (`Live World Map`) a
  fianco di Attivita' di Banda e Frequenza Rx.
- La mappa usa sfondo terra reale, overlay geografico, maschera giorno/notte e
  zoom automatico sull'area con traffico attivo.
- I tracciati sono separati per ruolo:
  `IN->ME` (chiamata diretta verso di te), `ME->DX` (tua chiamata verso DX),
  `BAND` (stazione vista in banda ma non in QSO diretto con te).
- Durante la TX viene animato solo il percorso `ME->DX`; a fine TX vengono
  mostrati per pochi secondi i chiamanti in coda ricevuti durante la TX.
- Rafforzata l'associazione nominativo/locator con fallback `CALL3.TXT` +
  AD1CCty per evitare frecce mancanti quando il locator non e' esplicito.
- Rendering etichette ottimizzato per ridurre sovrapposizioni (font piu'
  piccolo, priorita' ai casi rilevanti, limite etichette visibili).

## Note di Build e Runtime

### Build tree

Output principale della build:

- `build/ft2.app/Contents/MacOS/ft2`

Eseguibili di supporto attesi nello stesso percorso:

- `build/ft2.app/Contents/MacOS/jt9`
- `build/ft2.app/Contents/MacOS/wsprd`

La configurazione CMake di questo fork copia gli eseguibili di supporto
nel bundle applicativo dopo la build di `ft2`.

### Memoria condivisa

FT2 richiede un segmento di memoria condivisa di circa 48 MB.

Controlli utili:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Profilo consigliato per coesistenza FT2 + JTDX:

- `kern.sysv.shmmax=104857600`
- `kern.sysv.shmall=51200`

File di riferimento:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`
- `Darwin/ft2-pkg-postinstall.sh`

### Pacchetto installer macOS

Le release includono un installer `.pkg` che applica automaticamente i
parametri sysctl della memoria condivisa, per evitare errori di avvio quando
`kern.sysv.shmmax` risulta troppo basso di default.

### Se l'avvio dell'installer viene bloccato da Gatekeeper

Usa `Impostazioni di Sistema` -> `Privacy e sicurezza` -> `Apri comunque`
per il pkg bloccato, poi conferma con password/Touch ID.

In alternativa fai click destro sul pkg in Finder e scegli `Apri`.

## Attribuzione Fork lato UI

L'attribuzione del fork e' visibile in:

- titolo finestra principale (via `program_title()`);
- testo della finestra About.

## Changelog e documentazione upstream

- Changelog fork: `CHANGELOG.md`
- Guida utente upstream: `doc/user_guide/en/`
