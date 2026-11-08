# Libraries

The original executable carries all its libraries statically (see
[../binary-analysis/dependencies.md](../binary-analysis/dependencies.md)).
This page is about what the **rebuild** uses on a modern system and how the
versions were matched. Provenance and patches:
[../reconstruction/thirdparty/README.md](../reconstruction/thirdparty/README.md).

## What the rebuild links (VERIFIED, experiments T7–T8)

| Original (linked in 2002) | Used by the rebuild | Evidence of the match |
|---|---|---|
| Allegro 3.9.37 (CVS) Unix | **Allegro 3.9.37** release tarball, static, built with `tools/build_libs32.sh` (OSS digital + MIDI drivers, X11 + XShm + XF86VidMode, fbcon/VGA/VBE-AF drivers compiled in, as in the binary) | version string "Allegro 3.9.37 (CVS), Unix" in the binary; every Allegro symbol the game calls resolves; frame-identical output (T10) |
| JGMOD | JGMOD 0.99 (2002-10-08) | the binary's 128 JGMOD functions all exist in 0.99 under the same names (STRONGLY INFERRED close; exact version UNKNOWN) |
| LibAmp | **reconstructed**: amp 0.7.6 decoder + PACKFILE patch, `audiolib.c` and `audioalg.c` decompiled from the binary | decoder function set and table sizes match amp 0.7.6; I/O functions match the patch; MP3 playback verified (T16) |
| libcda | libcda 0.5.1 + `cd_play_now`, `cd_play_loop`, `cd_is_playing` recovered from the binary | `linux.c` helper set (`copy_cd_error`, `get_tocentry`, `get_subchnl`) matches |
| zlib 1.1.3 | system zlib (32-bit) | `inflate`, `inflateInit2_`, `crc32` |
| minizip unzip.c 0.15 | the reconstructed `unzip.c` (part of the tree; `unzlocal_getByte` written from the minizip 0.15 source and checked against the assembly) | |
| glibc 2.2.4 (static) | system glibc >= 2.29 (32-bit) | `__ctype_b` etc. mapped to the glibc 2.3+ accessors; `__strtol_internal`/`__strtod_internal` to `strtol`/`strtod`; `pthread_yield` (removed in 2.34) to `sched_yield`; built with `_DEFAULT_SOURCE` so no `__isoc23_*` symbols are needed (`include/mugen_common.h`) |
| linuxthreads | NPTL | 5 thin wrappers in `lthreads.c`. Note the original bug: `EBT_MutexInit` initialises a mutex on its own stack (VERIFIED) |
| XFree86 Xlib, Xext, DGA, VidMode | system libX11, libXext, libXxf86vm (32-bit), through Allegro only | DGA is not built (no headers on modern systems; windowed X11 is the default) |

## Allegro 3.9.37 versus 4.4 (VERIFIED, compile-time `offsetof` on both headers)

Allegro 4.4.3.1 (the last 4.x release) was considered for the rebuild
because it has ALSA and PulseAudio-compatible drivers. Its ABI differs from
3.9.37 in places the decompiled code uses directly:

| Item | 3.9.37 | 4.4.3.1 | Used by the game |
|---|---|---|---|
| `BITMAP` (size, `vtable` at 0x1c, `line[]` at 0x40) | same | same | yes (`screen[7]`, bank switching) |
| `GFX_VTABLE.acquire` / `.release` | 0x10 / 0x14 | 0x10 / 0x14 | yes |
| `GFX_VTABLE.clear_to_color` | 0x94 | 0xa0 | yes (`g-lib.c`, `vbuf.c`) |
| `SAMPLE` (size 36, `data` at 0x20) | same | same | yes |
| `JOYSTICK_INFO` size / `button[]` offset | 380 / 252 | 568 / 312 | yes (`joy + i*0x17c + ...`) |
| `SYSTEM_DRIVER.desktop_color_depth` | 0x6c | 0x60 | yes (`system_driver + 0x6c`) |
| `SYSTEM_DRIVER.yield_timeslice` | 0x74 | 0x6c | no |
| Key codes `KEY_A`..`KEY_KANJI` (1..102) | same | same | yes |
| Key codes from `KEY_MODIFIERS` (`KEY_LSHIFT` ...) | 103..114 | 115..126 (4.2 added 12 keys) | yes (`KBAllegRemapMap`, 116 entries) |
| `KEY_MAX` | 115 | 127 | `key[]` is 115 bytes in the binary |

A 4.4 build would therefore need every raw-offset access rewritten as an API
call (as `compat/allegro_inline.c` does for bank switching) and a key-code
translation layer. Allegro 3.9.37 was chosen instead: same code, same
behaviour, and sound is available through `padsp` (linux/audio.md).

## Library prototypes

The decompiled code declares library functions with Ghidra's prototypes.
They were compared with the real Allegro 3.9.37, JGMOD, libcda and LibAmp
headers (`gcc -aux-info`): 96 matched, 3 differed in argument count
(`install_sound`, `lock_sample`, `cd_init`); the first two were corrected
from the assembly, the third passes one harmless extra argument as the
original does.
