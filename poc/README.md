# Vulnerabilità format string — PoC

Proof-of-concept a supporto della tesi triennale *"Vulnerabilità format string: teoria, sfruttamento e mitigazioni"* (Lexiang Ye, Università di Parma).

Contiene un ambiente Docker riproducibile e gli esperimenti discussi nei Capitoli 2, 3 e 4: dimostrazioni isolate di leak/write via format string (§2.2–2.4), lo sviluppo completo di un exploit end-to-end (Cap. 3) e la verifica delle mitigazioni contro gli stessi binari (Cap. 4).

> Codice a scopo didattico/dimostrativo, pensato per girare esclusivamente nell'ambiente Docker fornito.

## Struttura

```text
poc/
├── README.md
├── .gitignore
├── environment/
│   ├── Dockerfile
│   └── docker-compose.yml
├── targets/
│   ├── Makefile
│   ├── leak_demo.c
│   ├── write_demo.c
│   └── vuln_service.c
└── exploits/
    ├── sez2_2_info_leak.py
    ├── sez2_3_write.py
    ├── sez2_4_partial_write.py
    └── exploit.py
```

## Ambiente

Requisiti: Docker.

Ambiente pinnato: Ubuntu 22.04 LTS, glibc 2.35, GCC 11.4.0. Strumenti principali: pwndbg, pwntools.

```bash
cd environment
docker compose up -d --build       # build e avvio del container
docker compose exec bin-exp bash   # apre una bash interattiva nel container
```

La bash parte in `/poc`, con l'intera repo montata su quella cartella. Per fermare il container: `docker compose down`.

## Build dei target

Dentro al container:

```bash
cd /poc/targets
make              # leak_demo, write_demo, vuln_service — Cap. 2 e 3
make fortified    # leak_demo_fortified, vuln_service_fortified — Cap. 4
```
I binari compilati non sono versionati (vedi `.gitignore`): si costruiscono da sorgente a ogni build, così il sorgente resta l'unica fonte di verità. I target fortificati ricompilano gli stessi `leak_demo.c`/`vuln_service.c` con `-O1`, la soglia minima perché `_FORTIFY_SOURCE` (già di default nel toolchain, ma inerte a `-O0`) diventi effettiva.

## Target -> sezioni della tesi

| File | Sezioni | Ruolo |
|---|---|---|
| `leak_demo.c` | §2.2, §4.3 | target per l'information disclosure; contiene anche la riga commentata `printf(buf, 0)` per la dimostrazione di `-Wformat-nonliteral` |
| `write_demo.c` | §2.3, §2.4 | target per mostrare la scrittura in memoria |
| `vuln_service.c` | Cap. 3 | target persistente per l'exploit end-to-end |
| `leak_demo_fortified` | §4.1 | `leak_demo.c` ricompilato con `-O1`: verifica dei controlli di `_FORTIFY_SOURCE` |
| `vuln_service_fortified` | §4.2 | `vuln_service.c` ricompilato con `-O1`: stesso `exploit.py` del Cap. 3 contro il binario fortificato |

Gli ultimi due non hanno un proprio sorgente: sono `leak_demo.c` e `vuln_service.c` ricompilati da `make fortified` (vedi sopra), non file `.c` a parte.

La verifica di §4.3, a differenza di tutto il resto, non passa da `make`: si fa commentando/scommentando a mano le due righe `printf` in `leak_demo.c` e ricompilando direttamente:
- `gcc-11 -fsyntax-only leak_demo.c` per l'avviso di default (`-Wformat-security`);
- `gcc-11 -fsyntax-only -Wformat-nonliteral leak_demo.c` dopo aver attivato `printf(buf, 0)`.

## Eseguire gli exploit

```bash
cd /poc/exploits
python3 sez2_2_info_leak.py
```

Ogni script si connette in locale all'eseguibile. `exploit.py` punta di default a `vuln_service`; per la verifica del Cap. 4 (§4.2) contro il binario fortificato basta commentare/scommentare le due righe `ELF(...)` in testa allo script.
