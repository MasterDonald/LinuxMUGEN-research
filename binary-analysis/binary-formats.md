# Binary formats in the package

## File inventory

All 112 files, with size, date, SHA-256 and `file` type:
[../artifacts/inventory.tsv](../artifacts/inventory.tsv) (VERIFIED). Summary:

| Directory | Files | Contents |
|---|---|---|
| `/` | 3 | `mugen` (UPX ELF), `readme.txt`, `updates.txt` |
| `chars/` | 1 + kfm (16) | Kung Fu Man: DEF, CNS, CMD, AIR, SFF, SND, 6 ACT palettes, intro and ending storyboards (DEF + SFF), readme |
| `data/` | 13 + big (2) + kfm (10) | Default motif: `system.def/.sff/.snd`, `fight.def/.sff/.snd`, `fightfx.air/.sff`, `common.snd`, `common1.cns`, `select.def`, `mugen.cfg`; motifs `big` and `kfm` |
| `docs/` | 21 + tutorial (33) | HTML/RTF/TXT documentation, GIF tutorial images |
| `font/` | 9 | `.fnt` bitmap fonts |
| `stages/` | 4 | `kfm.def/.sff`, `stage0.def/.sff` |

## Elecbyte containers (VERIFIED by Python Script on every file)

| Signature (12 bytes) | Format | Files | Version bytes 12-15 |
|---|---|---|---|
| `ElecbyteSpr\0` | SFF sprite archive | 11 | `00 01 00 01` (dword 0x01000100 = "1.01") |
| `ElecbyteSnd\0` | SND sound archive | 4 | `04 00 00 00` |
| `ElecbyteFnt\0` | FNT font | 9 | `00 01 00 00` |
| `ElecbyteAIB\0`? | AI learning data (not shipped) | 0 | checked against the MUGEN version (`AILearnDataLoad`) |

Format details: [../formats/sff.md](../formats/sff.md),
[../formats/snd.md](../formats/snd.md), FNT below,
[../formats/act.md](../formats/act.md).

### FNT (VERIFIED on all 9 fonts)

| Offset | Size | Field |
|---|---|---|
| 0 | 12 | `ElecbyteFnt\0` |
| 12 | 4 | version bytes `00 01 00 00` (docs/formats.txt says "2 verhi, 2 verlo"; the files disagree) |
| 16 | 4 | PCX offset (always 64) |
| 20 | 4 | PCX length |
| 24 | 4 | text offset (= 64 + PCX length) |
| 28 | 4 | text length (text runs to end of file in all 9 files) |
| 32 | 32 | unused |

The PCX is an 8-bit, 1-plane RLE image (version 5) with a 256-colour
palette: one row of glyphs, heights 6-13 px. The text part is an INI-like
`[Def]` section and a `[Map]` glyph table, parsed by the engine's text
parser (`TPGroupSeek(...,"def")`, `"map"` in `font-lib.c`).

## The executable

See [executable-analysis.md](executable-analysis.md). For the
reconstruction, Elecbyte's data is re-emitted byte for byte in
`reconstruction/data/mugen_data.S`:

| Region | Range | Bytes | Content |
|---|---|---|---|
| `.data` | 0x082870f0-0x08288060 | 3,952 | initialised globals (clsn scale, graphics state, key tables, date constants, `g`, name/type tables) |
| `.bss` statics | 0x082a6298-0x082a6c00 | 2,408 | file-static buffers (`KBBuffer`, `padbuf`, `GlobalTemp`s, ...) |
| COMMON | 0x082c0680-0x082ca680 | 40,960 | globals (`ErrorMessage`, `V_*`/`W_*`, input flags, timers, GUI, `MyStack`, `ci`) |

Pointers stored in `.data` were turned into symbol references (functions,
labels, or individual strings from the merged string pool), each annotated
with its original value.
