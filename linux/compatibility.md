# Compatibility with modern Linux

Tested on Linux 7.3.1 (CachyOS, x86-64, 2026), KDE Wayland session with
XWayland (VERIFIED).

| Topic | Result | Class |
|---|---|---|
| Executing the i386 static binary | works (IA32 emulation) | VERIFIED |
| UPX 1.20 stub | works; needs writable, exec `/tmp` and `/proc` | VERIFIED |
| linuxthreads on a modern kernel | starts (manager thread, RT signals); `_sysctl` ENOSYS tolerated | VERIFIED |
| X11 windowed mode (XWayland) | works; first-run info screen shown | VERIFIED |
| MIT-SHM | works when the X server can see the SysV shm segment; in an IPC-isolated sandbox: `X Error BadValue (MIT-SHM)` | VERIFIED |
| Fullscreen (DGA/VidMode) | not tested; XWayland emulates VidMode but DGA is generally unavailable | UNKNOWN (expected to fail or fall back) |
| Linux console graphics | not applicable on most modern systems (no VGA I/O from user space, framebuffer access rights); failed without `/dev/console` | VERIFIED (failure in sandbox) |
| Sound (original) | no `/dev/dsp` -> silent. Options: kernel ALSA OSS emulation (`snd-pcm-oss`, `snd-seq-oss`), `osspd`/CUSE. `padsp`/`aoss` **cannot** work (they use `LD_PRELOAD`, and the binary is static) | VERIFIED (silent) / STRONGLY INFERRED (options) |
| Sound (rebuild) | works with `padsp` (32-bit `libpulsedsp.so`): effects, MP3, MOD | VERIFIED (T16, Debian 12 i386) |
| Joystick | Allegro 3.9.37 opens `/dev/js0`..; current systems create `/dev/input/jsN` (joydev), so a link or bind mount is needed; `P1.Joystick.type = 1`. Tested with a uinput virtual pad bound to `/dev/js0`: detected (`num_joysticks = 1`), menus/select/fights respond, identical in both binaries; the VS-mode stage select does not accept confirmation with a pad enabled (both binaries) | VERIFIED (T25, virtual pad); physical pads untested |
| CD audio | libcda opens `/dev/cdrom` (or `$CDAUDIO`) and uses the Linux CDROM ioctls; with an emulated drive both binaries issue identical ioctl sequences (TOC read, PLAYMSF for the track, status polling every 6 frames, restart at track end) | VERIFIED (T26, emulated drive); real drive untested |
| Keyboard repeat in X | cannot be disabled by MUGEN; use `xset r off` (readme) | VERIFIED (readme) |
| Beta expiry (2002-07-01) | flag set (VERIFIED: banner on screen); only forces the info screen and the banner, nothing else reads the flag, so the game stays usable | STRONGLY INFERRED (from the code; menus not exercised in tests) |
| Time zone | expiry date compared in UTC (`gmtime`); `/etc/localtime` read by glibc tz init | VERIFIED |

## The rebuild (VERIFIED, experiments T7–T16)

`mugen-rebuilt` is a dynamically linked i386 ELF. It is not packed, and it
uses NPTL instead of linuxthreads.

| Requirement | Detail |
|---|---|
| CPU / kernel | x86 or x86-64 with IA32 emulation (as for the original) |
| C library | glibc **≥ 2.29**, 32-bit (built in Debian 11, glibc 2.31; highest symbol version needed: `GLIBC_2.29`). musl is not supported: on Alpine 3.22 (i386) the rebuild does not start, while the static original runs |
| Libraries (32-bit) | libX11, libXext, libXxf86vm, zlib. Allegro, JGMOD, libcda and LibAmp are linked statically |
| Display | X11 or XWayland, windowed mode. Verified on the host's XWayland and on Xvfb in every container |
| Sound | `padsp` (see [audio.md](audio.md)) |

Cross-distribution result (same binary, same inputs, frame dumps compared
byte for byte). Current release binary (after the x87 fixes, T28):

| Distribution (container image) | Original runs | Rebuild runs | Rebuild title = original (90 frames) | Rebuild match = original (600 frames) | Rebuild match = rebuild on Debian 11 |
|---|---|---|---|---|---|
| Debian 11 i386 | yes | yes | 90/90 | 595/600 | reference |
| Debian 12 i386 | yes | yes | 90/90 | 595/600 | 600/600 |
| Ubuntu 24.04 amd64 + i386 libs | yes | yes | 90/90 | 595/600 | 600/600 |
| Fedora 42 x86-64 + i686 libs | yes | yes | 90/90 | 595/600 | 600/600 |
| Arch Linux + lib32 | yes | yes | 90/90 | 595/600 | 600/600 |
| openSUSE Tumbleweed + 32bit libs | yes | yes | 90/90 | 595/600 | 600/600 |
| Alpine 3.22 i386 (musl) | yes | **no** (needs glibc) | – | – | – |
| CachyOS host (x86-64, lib32) | yes | yes | see T18–T30 (host campaign) | | |

The 5 differing match frames differ in 7 pixels each (one scanline of a
floor reflection; the first release differed in 169 of 600 frames by up to
16 pixels). The result is the same on every distribution.

Install commands per distribution:
[../preservation/modern-linux.md](../preservation/modern-linux.md).
