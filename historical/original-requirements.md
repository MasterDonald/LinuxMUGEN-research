# Original requirements

## Stated by Elecbyte (readme.txt, VERIFIED)

- CPU: minimum Pentium 90, recommended Pentium 200.
- Memory: "32 MB should suffice, although 64 MB is probably much safer";
  more for team modes and large characters.
- Display: "meant to run under 320x240 in 16-bit colour"; 640x480 possible.
- Runs "under console and X-Windows".
- Sound: "linux sound uses esd or /dev/dsp, but 2.4.X kernels have changed to
  /dev/sound/dsp".
- Joystick, multi-joystick: "linux must be set up correctly first".

## Derived from the binary

| Requirement | Value | Evidence | Class |
|---|---|---|---|
| CPU architecture | i386 (32-bit x86), x87 FPU | ELF header; x87 code throughout | VERIFIED |
| Kernel | Linux >= 2.2.5 | `.note.ABI-tag` "Linux, ABI: 2.2.5" | VERIFIED |
| C library | none at run time (glibc 2.2.4 linked statically); NSS/iconv/locale modules may still be dlopened | static ELF, no PT_INTERP; `dlopen.c` linked | VERIFIED |
| X server | X11 with MIT-SHM (optional), XFree86-DGA and VidMode (fullscreen) | Xlib, XShm, XF86DGA/DGA2, XF86VMode objects linked; MIT-SHM `XShmAttach` seen in tests | VERIFIED |
| Console graphics | VGA / Mode-X / VBE-AF / framebuffer (`/dev/fb0`) drivers; console access usually needs root | `vga.c`, `modex.c`, `vbeaf.c`, `fbcon.c`; readme "running MUGEN as root may improve video performance" | VERIFIED |
| Sound | OSS `/dev/dsp`, `/dev/mixer`; MIDI via `/dev/sequencer` or DIGMID patches (`patches.dat`) | `uoss.c`, `uossmidi.c`, `digmid.c`; strace | VERIFIED |
| ESD | through an Allegro plugin module (`modules.lst`); not built in | no ESD code linked; Allegro looks for `/usr/(local/)lib/allegro/modules.lst` | VERIFIED (absence) / STRONGLY INFERRED (plugin path) |
| Joystick | Linux joystick API `/dev/js0`, `/dev/js%d` | strings in `ljoy.c` | VERIFIED |
| Mouse (console) | `/dev/mouse`, GPM `/dev/gpmdata`, MS/PS2 protocols | strings; `lmsems.c`, `lmseps2.c`, `lmsegpmd.c` | VERIFIED |
| CD audio | `/dev/cdrom` via libcda (ioctl) | string; `linux.c` (libcda) | VERIFIED |
| Writable game directory | `data/mugen.cfg` rewritten; `_mugen__.tmp` test file; screenshots `mugen?.pcx` | strace T3; readme | VERIFIED |
| Writable, executable `/tmp` | UPX stub writes `/tmp/upxXXXXXXXXXXX` and execs it via `/proc/<pid>/fd` | strace T2 | VERIFIED |

## Target distribution

Built on **Mandrake Linux 8.1** (GCC "2.96-0.62mdk", glibc 2.2.4 RPM build
paths) (STRONGLY INFERRED from `.comment` and STABS). Because the binary is
static, it was meant to run on any i386 Linux of its time with X11 or a
supported console driver (STRONGLY INFERRED). The readme names no
distribution.
