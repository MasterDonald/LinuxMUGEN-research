# Rendering

## Pipeline (VERIFIED: function names, call graph, `GameVarInit`)

1. A 320x240x16-bit off-screen surface is created with
   `V_AllocDepth(0x140, 0xf0, 0x10)` (`vbuf.c`). `V_SetBuf` selects the
   current target; `W_Define` sets the clip window (`W_x1..W_y2`).
2. Everything is drawn into it with Elecbyte's own blitters, not Allegro's
   (153 `W_*` functions):
   - families **Put / Scale / Rotate** x **plain / TransAdd / TransSub /
     Shadow** x **mirror none / H / V / HV**;
   - suffixes: `8to16` (8-bit paletted sprite into the 16-bit surface),
     `_B` (blend variant, e.g. `W_BoxFillTransAdd16_B50`, 50%), `_P`, `_S`
     (rotate/scale paths);
   - primitives: `W_Cls`, `W_Box`, `W_BoxFill`, `W_BoxFillTransAdd16`,
     `W_BoxFillTransSub16`, `W_Line`, `W_PutPixel`.
   Additive and subtractive modes implement the AIR/explod `trans` types
   (`A`, `S`) and stage `trans`. Shadows use subtractive blits with the
   stage `[Shadow]` intensity.
3. The finished frame is copied to Allegro's `screen`, optionally
   stretched 2x (`V_BufToScreen`, `V_BufToScreenXY`,
   `V_BufToScreenStretch`, `V_DoubleRes`), with page flipping per
   `BlitMode` (`g-lib.c`: `G_SetMode`, `G_SetBlitMode`).

## Colour

- Sprites are 8-bit paletted; palettes are kept as 32-bit "Pal4" entries
  and converted to the 16-bit screen format with Allegro's
  `_rgb_{r,g,b}_shift_16` (VERIFIED: the code builds colours as
  `r << _rgb_r_shift_16 | ...`).
- `MasterPal*` (`pal-lib.c`) tracks palette changes per frame
  (`MasterPalProcessChanges`, `MasterPalFinishedDraw`); PalFX
  (`pal.c`, `PalFXUpdate`) applies add/mul/colour/invert effects to
  palette groups (`PalGrpFlag`).

## Draw order (from `GameLoop` calls)

Back BG layers -> shadows -> afterimages -> players, explods and
projectiles (sprite priority) -> front BG layers -> lifebars, power, time,
round text -> combo counter -> debug overlays (Clsn boxes with Ctrl-C,
debug text with Ctrl-D, GUI window) -> training menu.

## Fonts

`.fnt` fonts (PCX glyph strip + `[Map]`), drawn by `V_FontDraw*`,
`V_FontWrite*` (printf-style, varargs) with left/center/right alignment
(`font-lib.c`). 2002.04.14 fixed right/center justification after a
newline (updates.txt).
