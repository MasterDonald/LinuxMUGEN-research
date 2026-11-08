# Graphics

## Drivers linked (Allegro 3.9.37 Unix; VERIFIED by object files)

| Environment | Objects | Notes |
|---|---|---|
| X11 windowed | `xgfxdrv.c`, `xwin.c`, `xvtable.c`, `XShm.c` | MIT-SHM image (`shmget` 307,200 bytes = 320x240x4 on a 24-bit visual, VERIFIED T3) |
| X11 fullscreen | `XF86DGA.c`, `XF86DGA2.c`, `XF86VMode.c` | DGA direct framebuffer and VidMode mode switching |
| Linux console | `lgfxdrv.c`, `vga.c` (mode 13h), `modex.c` (Mode-X), `vbeaf.c` (VBE/AF 2.0: "Obsolete VBE/AF version (need 2.0 or greater)"), `fbcon.c` (`/dev/fb0`, `/etc/fb.modes`), `lvga.c`, `lvgahelp.c`, `vgaregs.c`, `vtswitch.c` | needs console access; readme: "console must use same res and depth as screen ... unless root" |
| Plugin modules | `umodules.c` reads `modules.lst` | e.g. DGA2 or svgalib modules of an installed Allegro (none needed) |

## MUGEN's rendering model (VERIFIED from function names and code; details in ../engine/rendering.md)

- Internal resolution **320x240**, colour depth from `mugen.cfg`
  `[Video Linux] Depth` (default 16). "M.U.G.E.N is meant to run under
  320x240 in 16-bit colour" (readme).
- An off-screen 16-bit buffer (`V_Alloc`/`V_AllocDepth(0x140, 0xf0, 0x10)`,
  i.e. 320x240x16 in `GameVarInit`) is drawn with Elecbyte's own blitters
  (`W_*` functions), then copied to the Allegro `screen`
  (`V_BufToScreen*`, `DrawToScreen`).
- `Stretch` / `DoubleRes` scale the 320x240 image to 640x480
  (`V_BufToScreenStretch`, `V_DoubleRes`, `G_*` modes in `g-lib.c`).
- `BlitMode = PageFlip` (alternatives handled by `G_SetBlitMode`).
- `VRetrace` (Ctrl-V in game) waits for vertical retrace via Allegro
  `vsync()`.
- Screenshots: F12 saves `mugen?.pcx` (Allegro `save_pcx`).

## Known 2002 limitations (readme, VERIFIED)

- "depth in mugen.cfg must match depth when in X". On the 2026 test system,
  Depth=16 ran fine on a 24/32-bit XWayland visual, because Allegro's xwin
  converted colours (VERIFIED T3).
- Running in a window "can be slow; try fullscreen".
