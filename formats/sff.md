# SFF: sprite archive (version 1.01)

Sources: `formats` (Elecbyte), the 11 shipped SFF
files, and the loader `SpriteReadSFFPtr`, `SpriteReadSFFPtr_1_01`,
`SpriteReadSFFListPtr_1_01` (`spr-read.c`).

## Header (512 bytes)

| Offset | Size | Field | Notes |
|---|---|---|---|
| 0 | 12 | `ElecbyteSpr\0` | compared with `repz cmpsb` (0x805c0ca) (VERIFIED) |
| 12 | 4 | version | must equal dword **0x01000100** (bytes `00 01 00 01`), else the `_2_00` reader runs, which is a stub that returns 0 = failure (VERIFIED 0x805c0d6, 0x805c3a0). formats.txt lists the bytes as "verhi, verlo, verlo2, verlo3"; on disk byte 15 = 1 (major) and byte 13 = 1 |
| 16 | 4 | number of groups | informational; matches the distinct groups in all files (VERIFIED) |
| 20 | 4 | number of images | the loader iterates exactly this many subfiles (VERIFIED: loop bound `param_2+0x14`) |
| 24 | 4 | offset of the first subfile | always 512 in the shipped files |
| 28 | 4 | subheader size | 32 |
| 32 | 1 | palette type | 1 = shared (characters: `kfm.sff`), 0 = individual (system, fight, stages) |
| 33 | 479 | unused / comment | |

## Subfile header (32 bytes)

| Offset | Size | Field | Notes |
|---|---|---|---|
| 0 | 4 | next subfile offset | **the last subfile's value is the file size, not 0** as formats.txt says (VERIFIED in all files) |
| 4 | 4 | data length | 0 = linked sprite. **When byte 18 = 1 the length still includes the absent 768-byte palette** (length overstates by 768; VERIFIED: 221/223 subfiles of kfm.sff, also system, fightfx and stage files) |
| 8 | 2 | axis X (signed) | |
| 10 | 2 | axis Y (signed) | |
| 12 | 2 | group | |
| 14 | 2 | image number | |
| 16 | 2 | index of the linked sprite | used when length = 0 (41 linked sprites in kfm.sff) |
| 18 | 1 | same palette as previous | the loader calls `SpriteUsePal` with the previous palette (VERIFIED) |
| 19 | 13 | unused | |
| 32 | n | PCX image | 8-bit, 1 plane, RLE (all files). The 256-colour palette (`0x0C` + 768 bytes) follows when byte 18 = 0 |

**Parsing rule implied by the files:** follow `next` from header field 24
for `images` steps; take data length as `next - (off + 32)`, not the
length field.

## Palettes

Shared-palette SFFs (characters) are drawn with the ACT palette chosen at
select time (`pal1..pal12` in the character DEF, `pal.defaults`); see
[act.md](act.md). Sprites are 8-bit and rendered into a 16-bit framebuffer
through 8->16-bit blitters (`spr16-lb.c`, `spr16add.c`, `spr16sub.c`; see
[../engine/rendering.md](../engine/rendering.md)).

## Limits observed

- SFF v2 is not supported, but a reader entry point exists (stub).
- Per readme: "run sprmaker with the -c -f -p command line options" to
  produce the smallest file. `sprmaker` is not included.
