# Project history

## The software

M.U.G.E.N is a 2D fighting-game engine written by **Elecbyte**. Its behaviour
is driven by text definition files (DEF, CNS, CMD, AIR) and binary resource
archives (SFF sprites, SND sounds). For years it was distributed as freeware
DOS betas built with DJGPP. On **1 November 2001** Elecbyte switched
platforms: "Platform change to Linux. DOS platform is no longer supported"
(VERIFIED: `docs/updates.txt`, "1 Nov 2001" entry). The package studied here
is the **last of those Linux betas, "beta release version 2002.04.14"**
(VERIFIED: `readme.txt` header, the embedded constants
`MUGENDATE_Y/M/D = 2002/4/14` at `.data` `0x08287a78`-`0x08287a80`, and
"BETA 2002.04.14" on the in-game information screen).

The archive was received as a folder called `LINUX MUGEN 14.04.2002`. The
task description gave the date as "14.02.2002". Every primary source says
14 April 2002 (`2002.04.14`), so this project uses that date (VERIFIED).

## Timeline (from shipped files and the binary)

| Date | Event | Evidence |
|---|---|---|
| "9X.06.27" | First public MUGEN release | readme "When MUGEN?" (VERIFIED as a claim in the readme) |
| 2000-01-01 | Version referenced as the incompatibility baseline | `docs/incompt2.txt` (VERIFIED) |
| 2001-10-12 .. 2001-11-10 | Most sample data files last modified (KFM, fight/system data, stages) | file mtimes, `artifacts/inventory.tsv` (VERIFIED as timestamps) |
| 2001-11-01 | First Linux beta; DOS dropped | `docs/updates.txt` (VERIFIED) |
| 2001-11-14 | Survival modes added | `docs/updates.txt` (VERIFIED) |
| 2001-12-10 | `system.def` motifs last modified | mtimes (VERIFIED) |
| **2002-04-14** | **This build** (zipped characters, `[Remap]`, MoveReversed trigger, ...) | updates.txt, embedded date (VERIFIED) |
| 2002-04-20 | Executable file timestamp; docs regenerated | mtime of `mugen` and docs (VERIFIED) |
| 2002-04-21 | `readme.txt`, `updates.txt`, `select.def`, `mugen.cfg` timestamps | mtimes (VERIFIED) |
| 2002-06-01 | End of license term per readme Appendix A | readme (VERIFIED) |
| **2002-07-01** | **Expiry date coded in the executable** | `MUGENEXPDATE_Y/M/D = 2002/7/1` at `0x08287a84`-`0x08287a8c`; info screen text "until 1st July 2002" (VERIFIED) |

The one-month gap between the license text (1 June) and the coded expiry
(1 July) is real: both values appear verbatim in their sources. Whether it
was a deliberate grace period is UNKNOWN.

## This project

1. Inventory and hashing of all 112 files ([artifacts/inventory.tsv](artifacts/inventory.tsv)).
2. Unpacking the UPX 1.20 executable losslessly (UPX 5.2.0 `-d`), on a
   read-only copy.
3. Mapping the static link: 778 object files, attributed by `FILE`
   symbols and `gcc2_compiled.` markers to Elecbyte code and third-party
   libraries.
4. Decompiling all 1,307 Elecbyte functions with **REA** (Ghidra 12.1.4
   backend) as a baseline.
5. A corrective Ghidra pass: Decompiler Parameter ID, calling-convention
   repair, global and local type commits, return-type decisions, tail-call
   and thunk handling, recovered structures and hand-verified prototypes.
   Every correction was checked against the assembly and the REA baseline.
6. Generating a reconstructed source tree with a byte-exact data image, and
   compiling it with modern GCC (`-m32`).
7. Running the original binary in a sandbox on a 2026 Linux system
   (strace, screenshots).
8. Writing this documentation.
