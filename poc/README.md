# Vulnerabilità format string — PoC

Proof-of-concept a supporto della tesi triennale *"Vulnerabilità format string: teoria, sfruttamento e mitigazioni"* (Lexiang Ye, Università di Parma).

Contiene un ambiente Docker riproducibile e gli exploit discussi nei Capitoli 2 e 3: dimostrazioni isolate di leak/write via format string (§2.2–2.4) e lo sviluppo completo di un exploit end-to-end (Cap. 3).

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
make
```
I binari compilati non sono versionati (vedi `.gitignore`): si costruiscono da sorgente a ogni build, così il sorgente resta l'unica fonte di verità.

## Target -> sezioni della tesi

| File | Sezioni | Ruolo |
|---|---|---|
| `leak_demo.c` | §2.2 | target per mostrare l'information disclosure |
| `write_demo.c` | §2.3, §2.4 | target per mostrare la scrittura in memoria |
| `vuln_service.c` | Cap. 3 | target persistente per l'exploit end-to-end |

## Eseguire gli exploit

```bash
cd /poc/exploits
python3 sez2_2_info_leak.py
```

Ogni script si connette in locale all'eseguibile.
