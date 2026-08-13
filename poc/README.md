# Format String Vulnerabilities — PoC

Proof-of-concept a supporto della tesi triennale *"Vulnerabilità Format String: teoria, sfruttamento e mitigazioni"* (Lexiang Ye, Università di Parma).

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
│   ├── leak_write_demo.c
│   └── vuln_service.c
└── exploits/
    ├── sez2_2_info_leak.py
    ├── sez2_3_write.py
    ├── sez2_4_byte_write.py
    └── exploit.py
```

## Ambiente

Requisiti: Docker.

Ambiente pinnato: Ubuntu 22.04 LTS, glibc 2.35, GCC 11.4.0. Strumenti principali: pwndbg, pwntools.

```bash
cd environment
docker compose up --build
```

Apre una bash dentro al container con l'intera repo montata su `/poc`.

## Build dei target

Dentro al container:

```bash
cd /poc/targets
make
```

## Target -> sezioni della tesi

| File | Sezioni | Ruolo |
|---|---|---|
| `leak_write_demo.c` | §2.2, §2.3, §2.4 | programma minimale, una tecnica alla volta |
| `vuln_service.c` | Cap. 3 | target persistente per l'exploit end-to-end |

## Eseguire gli exploit

```bash
cd /poc/exploits
python3 sez2_2_info_leak.py
```

Ogni script si connette in locale all'eseguibile.
