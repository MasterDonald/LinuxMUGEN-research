# Dependencies

LINUXMUGEN is **fully static**: no `PT_INTERP`, no `DT_NEEDED`; `ldd`
reports "not a dynamic executable" (VERIFIED, user observation confirmed by
`readelf -l`). All libraries below are linked into the executable.

## Linked libraries

| Library | Version | Evidence | Role |
|---|---|---|---|
| Allegro | **3.9.37 (CVS)**, Unix port | `allegro_id` = "Allegro 3.9.37 (CVS), Unix" (initialised `.data` at 0x0828c4c0) | Graphics, input, timers, sound mixer, MIDI, config, file packing |
| JGMOD | (version string not found) | strings "JGMOD : ...", `install_mod`, `play_mod`, `load_jgm.c` | MOD/S3M/XM/IT (IT incomplete: "IT support is not completed yet") music |
| LibAmp (Allegro port) | (unknown) | `install_amp`, `load_amp`, `poll_amp`; readme thanks Tomislav Uzelac and Ove Kaaven | MP3 music |
| libcda | (unknown) | `linux.c` with `cd_init`, `cd_play`...; readme thanks Peter Wang and Brennan Underwood | CD audio |
| zlib | 1.1.3 | "inflate 1.1.3 Copyright 1995-1998 Mark Adler" | ZIP character support |
| minizip `unzip.c` | 0.15 | "unzip 0.15 Copyright 1998 Gilles Vollant" | ZIP directory and file access |
| libX11, libXext (XShm), libXxf86dga (DGA 1 and 2), libXxf86vm | XFree86 4.x era (exact version UNKNOWN) | object names (`XF86DGA2.c`, `XShm.c`, `lcUTF8.c`, `XKB*.c`) | X Window System client |
| linuxthreads | glibc 2.2.4 add-on | `manager.c`, `pthread.c`, `spinlock.c` | Allegro background threads, MUGEN precache worker (`PrecacheWorkerThread`) |
| glibc | 2.2.4 | STABS paths | C library (static) |
| libdl (static) | glibc 2.2.4 | `dlopen.c`... | Allegro plugin modules (`umodules.c`), NSS |
| libgcc | gcc 2.95.2 build tree (see executable-analysis.md) | STABS | 64-bit arithmetic helpers (`__divdi3`, `__moddi3`) |

## Functions the game code calls in each library

From Ghidra Script over 0x08048200-0x080d5e70 (VERIFIED):

**Allegro (67):** `_alemu_stricmp`, `_alemu_strlwr`, `allegro_exit`, `allocate_voice`, `blit`, `create_bitmap_ex`, `create_sample`, `create_video_bitmap`, `deallocate_voice`, `destroy_bitmap`, `destroy_midi`, `destroy_sample`, `detect_digi_driver`, `detect_midi_driver`, `install_allegro`, `install_int_ex`, `install_joystick`, `install_keyboard`, `install_mouse`, `install_sound`, `install_timer`, `load_midi`, `lock_sample`, `makecol`, `midi_pause`, `midi_resume`, `midi_seek`, `mouse_needs_poll`, `override_config_data`, `play_looped_midi`, `play_midi`, `play_sample`, `poll_joystick`, `poll_mouse`, `pow`, `reallocate_voice`, `rect`, `remove_int`, `remove_joystick`, `remove_keyboard`, `remove_sound`, `remove_timer`, `reserve_voices`, `rest`, `save_pcx`, `set_clip`, `set_color_depth`, `set_gfx_mode`, `set_keyboard_rate`, `set_leds`, `set_volume`, `show_video_bitmap`, `stop_midi`, `stretch_blit`, `voice_check`, `voice_get_frequency`, `voice_get_pan`, `voice_get_position`, `voice_get_volume`, `voice_set_frequency`, `voice_set_pan`, `voice_set_playmode`, `voice_set_position`, `voice_set_volume`, `voice_start`, `voice_stop`, `vsync`

**JGMOD (10):** `destroy_mod`, `get_mod_volume`, `install_mod`, `load_mod`, `pause_mod`, `play_mod`, `remove_mod`, `resume_mod`, `set_mod_volume`, `stop_mod`

**LibAmp (6):** `get_volume_mp3`, `install_amp`, `load_amp`, `poll_amp`, `set_volume_mp3`, `unload_amp`

**libcda (17):** `cd_close`, `cd_current_track`, `cd_eject`, `cd_exit`, `cd_get_tracks`, `cd_get_volume`, `cd_init`, `cd_is_audio`, `cd_is_paused`, `cd_is_playing`, `cd_pause`, `cd_play`, `cd_play_loop`, `cd_play_now`, `cd_resume`, `cd_set_volume`, `cd_stop`

**zlib (4):** `crc32`, `inflate`, `inflateEnd`, `inflateInit2_`

**libc/libm/pthread (50):** `_IO_feof`, `_IO_fgets`, `_IO_fprintf`, `_IO_printf`, `_IO_sscanf`, `_IO_vsprintf`, `_IO_vsscanf`, `__access`, `__assert_fail`, `__chdir`, `__errno_location`, `__libc_calloc`, `__libc_malloc`, `__new_fclose`, `__new_fopen`, `__pthread_create_2_1`, `__pthread_yield`, `__random`, `__realloc`, `__strtod_internal`, `__strtol_internal`, `exit`, `ferror`, `fflush`, `fgetc`, `fread`, `free`, `fseek`, `ftell`, `fwrite`, `getcwd`, `gmtime`, `isnan`, `memcpy`, `memmove`, `memset`, `pthread_mutex_destroy`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `remove`, `sprintf`, `srandom`, `strcat`, `strcmp`, `strcpy`, `strlen`, `strncmp`, `strncpy`, `time`

Globals the game reads directly: `screen`, `gfx_capabilities`,
`system_driver`, `key[]`, `key_led_flag`, `keyboard_lowlevel_callback`,
`joy[]`, `num_joysticks`, `mouse_x`, `mouse_y`, `mouse_b`,
`_rgb_{r,g,b}_shift_{16,24}` (Allegro); `stdout`, `stderr`, `__ctype_b`,
`__ctype_tolower`, `__ctype_toupper` (glibc 2.2) (VERIFIED,
`artifacts/refs_typed.tsv`).

## Run-time (non-linked) dependencies

| Resource | Needed for | Evidence |
|---|---|---|
| X server (`DISPLAY`, `XAUTHORITY`, `/tmp/.X11-unix/X0`) | windowed or fullscreen X modes | strace T3 |
| SysV shared memory visible to the X server | MIT-SHM blitting (else X error BadValue) | test T3a |
| `/dev/dsp`, `/dev/mixer` | sound (OSS) | strace |
| `/dev/sequencer` or `patches.dat` (DIGMID) | MIDI music | strace |
| `/dev/js0`.. | joysticks | strings |
| `/dev/cdrom` | CD audio | strings |
| `/usr/(local/)lib/allegro/modules.lst` + `.so` modules | optional Allegro drivers (ESD, ALSA, aRts, ...) | strace |
| `allegro.cfg` (cwd or `$HOME`) | optional Allegro configuration | strace (`stat("./allegro.cfg")`) |
| `/etc/localtime` | read by glibc time-zone initialisation; the expiry check itself uses UTC (`time` + `gmtime` in `GameVarInit`) | strace; code |
| Writable `./data/` and game root | `mugen.cfg` rewrite, `_mugen__.tmp` write test, `mugen?.pcx` screenshots | strace T3, readme |
| AI learning files (`ElecbyteAIB` header, version-checked) | `AILearnDataLoad/Save` (`p-ai.c`); path supplied by the caller (UNKNOWN which file) | decompiled code |
