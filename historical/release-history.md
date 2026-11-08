# Release history

All entries come from files shipped in the archive. External history (web
announcements, mirrors) could not be checked offline and is marked UNKNOWN.

## Versions mentioned in the package

| Version / date | Facts | Evidence | Class |
|---|---|---|---|
| 9X.06.27 | "Our first public release version" | readme.txt, "When MUGEN?" | VERIFIED (as stated by Elecbyte) |
| 2000.01.01 and earlier | Characters for these versions need changes; see incompt2.txt | readme.txt "Updates"; docs/incompt2.txt (2001-10-28) | VERIFIED |
| 1 Nov 2001 | "Platform change to Linux. DOS platform is no longer supported" | docs/updates.txt | VERIFIED |
| 14 Nov 2001 | Survival and Co-op Survival modes; AI ramping options in mugen.cfg | docs/updates.txt | VERIFIED |
| **14 April 2002** | Zipped characters (experimental), CMD `[Remap]`, MoveReversed trigger, ReversalDef sparkxy change, HitDef p1/p2sprpriority, Pause/SuperPause pausebg and endcmdbuftime, training AI level, CMD `$` direction fix, font justification fix, guard-release handling moved to common1.cns, precaching tweaks | docs/updates.txt "14 April 2002" | VERIFIED |

The complete changelog (66,978 bytes, newest first) is `docs/updates.txt`.
It is byte-identical to `updates.txt` in the root (VERIFIED: same SHA-256).

## Build identity of this executable

| Property | Value | Evidence |
|---|---|---|
| Version string | `M.U.G.E.N test ver %i.%02i.%02i (c)%i Elecbyte`, filled from the date constants | string at file offset 0x230020 of the unpacked binary; `PrintHelp` in `cmdline.c` |
| Build date constants | `MUGENDATE_Y=2002, _M=4, _D=14` | `.data` 0x08287a78, 0x08287a7c, 0x08287a80 |
| Expiry constants | `MUGENEXPDATE_Y=2002, _M=7, _D=1` | `.data` 0x08287a84, 0x08287a88, 0x08287a8c |
| On-screen | "BETA 2002.04.14", "until 1st July 2002" | screenshot, experiments/test-results.md T3 |
| File timestamp | 2002-04-20 | archive mtime |

## Relationship to DOS and Windows MUGEN

- The DOS line (DJGPP + Allegro) ended with the Linux switch on
  1 Nov 2001 (VERIFIED, updates.txt).
- This Linux build keeps the DOS input model: key codes in mugen.cfg are DOS
  set-1 scancodes, and `KBAllegRemapMap` translates Allegro key codes back to
  them (VERIFIED, `kbll-lib.c`). The readme still says "Exit - Returns you to
  the DOS prompt" and thanks DJ Delorie for DJGPP (VERIFIED). The text was
  carried over from the DOS readme (STRONGLY INFERRED).
- Windows MUGEN (WinMUGEN) is not mentioned anywhere in the package. Any
  relationship is outside this evidence (UNKNOWN here).
- The data formats (SFF v1.01, SND, FNT, AIR/CMD/CNS) are the same family as
  the DOS betas (STRONGLY INFERRED: incompt2.txt discusses migration from
  2000.01.01 only for CNS/CMD semantics, not container formats).
