# Note di Documentazione (Italiano)

## Scopo

Questo documento descrive la documentazione specifica del fork macOS.
Non sostituisce la guida utente completa WSJT-X in `doc/user_guide/en/`.

## Contesto release attuale

- Ultima release stabile: `v1.0.7`
- Target compatibilita': macOS Sequoia (15.x) + Tahoe (26.x)

## Cambi principali in v1.0.7

- Il titolo finestra principale ora include attribuzione fork e versione release del fork.
- Il sistema build include `FORK_RELEASE_VERSION`, e l'automazione release passa
  il tag all'app per mostrarlo nel titolo.
- I contenuti root del DMG sono stati puliti, rimuovendo file installer legacy
  WSJT-X e aggiungendo note specifiche FT2 (`ReadMe_FT2.txt`).
- Migliorata la visibilita' dello Skip Tx1 con tooltip espliciti e feedback in status bar.

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
