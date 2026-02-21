# Note di Documentazione (Italiano)

## Scopo

Questo documento descrive la documentazione specifica del fork macOS.
Non sostituisce la guida utente completa WSJT-X in `doc/user_guide/en/`.

## Contenuti

- Note di build/runtime per macOS;
- aspettative sulla configurazione della memoria condivisa;
- flusso di coesistenza FT2 + JTDX;
- comportamento di packaging rilevante per questo fork.

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
parametri sysctl della memoria condivisa, per evitare errori di avvio
quando `kern.sysv.shmmax` risulta troppo basso di default.

## Attribuzione Fork lato UI

L'attribuzione del fork e' visibile in:

- titolo finestra principale (via `program_title()`);
- testo della finestra About.

## Documentazione Upstream

Per i dettagli operativi completi usa la guida utente upstream in:

- `doc/user_guide/en/`
