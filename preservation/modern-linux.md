# Running LINUXMUGEN on modern Linux

Two ways: the original static binary (below) or the rebuilt executable
(section "Running the rebuild" at the end).

## The original

Verified on Linux 7.3.1 x86-64 (CachyOS, 2026), KDE Wayland + XWayland
(experiments T3).

## Requirements

1. 32-bit x86 support in the kernel (`CONFIG_IA32_EMULATION=y`; standard
   on mainstream distributions). No 32-bit libraries are needed: the
   binary is static.
2. Run from the game directory (relative paths) on a **copy** (it rewrites
   `data/mugen.cfg`).
3. `/tmp` writable and not `noexec`, and `/proc` mounted (UPX stub). If
   `/tmp` is `noexec`, unpack once instead: `upx -d -o mugen.unpacked mugen`
   (lossless; SHA-256 of the result
   d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
4. An X server (`DISPLAY`). XWayland works for windowed mode
   (`FullScreen = 0`, the default).
5. If the program runs in a sandbox, share SysV IPC with the X server
   (MIT-SHM); otherwise X error BadValue.

## Sound

Allegro 3.9.37 only has an OSS driver (`/dev/dsp`). The rebuild is
dynamically linked, so PulseAudio's OSS wrapper library `libpulsedsp.so` can
provide `/dev/dsp`; it also works with PipeWire's PulseAudio server
(VERIFIED with PipeWire 1.6.10, T23 and T31). The game is a 32-bit program
and needs the **32-bit** build of that library.

`padsp` preloads `/usr/$LIB/pulseaudio/libpulsedsp.so`; the loader expands
`$LIB` per program. For a 32-bit program on Arch/CachyOS it expands to
`lib32` (VERIFIED with a probe library, T31). If the 32-bit library is not
installed, the loader prints

```
ERROR: ld.so: object '/usr/$LIB/pulseaudio/libpulsedsp.so' from LD_PRELOAD cannot be preloaded (cannot open shared object file): ignored.
```

and the game runs without sound (it prints the name unexpanded).

| Distribution | 32-bit libpulsedsp.so from | Status |
|---|---|---|
| Arch Linux, CachyOS, Manjaro | `lib32-libpulse` (multilib; pacman adds 6 packages) | VERIFIED (T31): with exactly that package set's files in place, unmodified `padsp ./mugen-rebuilt` has sound and exits cleanly |
| Fedora | `pulseaudio-libs.i686` | repository metadata (`dnf repoquery --whatprovides`), not run |
| openSUSE Tumbleweed | `pulseaudio-utils-32bit` | package file list, not run |
| Debian/Ubuntu x86-64 | `pulseaudio-utils:i386`, which conflicts with the 64-bit `pulseaudio-utils` (simulated install on Ubuntu 24.04); alternative: install `libpulse0:i386` and unpack the library from the i386 .deb, then preload it by path | not run |
| Debian/Ubuntu i386 | `pulseaudio-utils` | VERIFIED (Debian 12 i386, T16) |

```sh
padsp ./mugen-rebuilt                                        # once the 32-bit library is installed
LD_PRELOAD=/usr/lib32/pulseaudio/libpulsedsp.so ./mugen-rebuilt   # the same, explicit path (Arch)
```

The standalone rebuild kit ships `run-with-sound.sh`. It finds the 32-bit
library, names the missing package otherwise, and accepts a library outside
the system paths (`MUGEN_PULSEDSP`, `MUGEN_PULSE_LIBDIR`). It also switches off
libpulsedsp's mixer emulation, because otherwise the game sets the desktop
volume to MasterWavVolume (100% by default) at every match, as the original
does (linux/audio.md, "Volume"). `padsp -M ./mugen-rebuilt` has the same
effect.

Tested content: sound effects, MP3 (LibAmp), MOD (JGMOD), MIDI through
DIGMID; CD audio with an emulated drive. The OSS MIDI sequencer was not
available.

Interrupting the game with Ctrl-C (SIGINT) can end in a segmentation fault
inside Allegro's shutdown. The original binary does the same (VERIFIED, T31),
so leave through the EXIT menu.

## Differences from the original

- Scaled shadow/reflection sprites may differ from the original by a few
  edge pixels (x87 precision; COMPLETENESS-REPORT.md section 4).
- Error messages for broken character files may show "(null)" instead of
  the offending text in two parser functions.
- Everything else tested is identical, including the beta-expiry notice.
