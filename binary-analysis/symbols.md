# Symbols

## Overview (VERIFIED, `readelf -s` on the unpacked binary)

| Kind | Count |
|---|---|
| FUNC | 5,750 |
| OBJECT | 2,143 |
| NOTYPE (labels, incl. one `gcc2_compiled.` per GCC object) | 1,869 |
| FILE (one per object file) | 778 |
| SECTION | 23 |
| **total** | **10,563** |

The binary is **not stripped**, so original Elecbyte function and global
names are preserved (`PlayerSCtrlApplyElem`, `GameLoop`, `SpriteReadSFFPtr`,
`MUGENEXPDATE_Y`, ...). That makes the reconstruction far more readable than
a typical decompilation. Names prove nothing about behaviour by themselves:
every behavioural statement in this repository comes from code.

## Attributing functions to source files

Python Script uses two facts about GCC 2.x static links
(VERIFIED):

1. Local symbols follow their object's `FILE` symbol in `.symtab`.
2. Each GCC-compiled object starts with a local `gcc2_compiled.` label at the
   start of its `.text` contribution.

Global functions are assigned to the object whose `gcc2_compiled.` range
contains them. Data-only objects share their marker address with the next
object, so on ties the last object in link order wins. Result:
[../artifacts/funcmap.tsv](../artifacts/funcmap.tsv) (address, size,
binding, name, source file, method). Known limit: glibc assembler objects
have no marker, so their functions fall into the previous C object's range;
this does not affect the Elecbyte range.

## Special symbols

| Symbol | Address | Meaning | Class |
|---|---|---|---|
| `main` | 0x08113aa0 (36 bytes, `umain.c`) | Allegro's Unix `main`, calls `_mangled_main` | VERIFIED |
| `_mangled_main` | 0x0809c470 (`main.c`) | MUGEN's real `main` (Allegro `END_OF_MAIN`) | VERIFIED |
| `gcc2_compiled.` | 0x0809c470 and others | Shares addresses with functions; Ghidra sometimes picks it as the primary name (fixed in the reconstruction) | VERIFIED |
| `g` | 0x08287a74 (.data, 4 bytes) | Pointer to the large global game-state block. Offsets above 0x20b5c are used, so the block is >133 KB | VERIFIED (uses) |
| `MUGENDATE_{Y,M,D}` | 0x08287a78.. | Build date 2002-04-14 | VERIFIED |
| `MUGENEXPDATE_{Y,M,D}` | 0x08287a84.. | Expiry 2002-07-01 (can be replaced from mugen.cfg `expires`) | VERIFIED |
| `allegro_id` | 0x0828c4c0 | "Allegro 3.9.37 (CVS), Unix" | VERIFIED |
| `ErrorMessage` | 0x082c0780 (256-byte COMMON) | Error text built with `strcat` before `ErrorExit` | VERIFIED |
| `V_Width`, `V_Height`, `W_x1`.. | COMMON | Virtual screen and clip window | VERIFIED (names, uses) |
| `ci` | 0x082c1680 (36,864 bytes COMMON) | Large table at the end of the Elecbyte COMMON block (character info, by name and `CharInfoInit`) | HYPOTHESIS |

## Function-local statics

GCC 2.96 names them `name.N` (`oldtime.0`, `CurCall.1`, `ShowInfoNow.0`,
`nokoflag.0`, ...). Ghidra prints them as `name_N`. The reconstruction maps
each one to its exact original address through GCC `__asm__` labels
(`include/mugen_data.h`). File-static symbols with the same name in
different files (`GlobalTemp` in five files, `BufferedReadMode` twice) stay
distinct the same way.

## Global types committed for the reconstruction

[../artifacts/global_types.tsv](../artifacts/global_types.tsv) lists the
concrete type chosen for each of the 163 referenced Elecbyte globals, with
the usage evidence (`index`, `deref`, `int_offset`, ...) behind each choice.
