# M.U.G.E.N beta 2002.04.14 (Linux) — rebuild kit

Everything needed to build the reconstructed engine as a 32-bit Linux
executable, and nothing else. The kit does not depend on the
`LINUXMUGEN-RESEARCH` tree it was extracted from.

**Not Elecbyte's source code.** `src/` was rebuilt from the 2002.04.14
executable (Ghidra 12.1.4 decompiler output, corrected, made compilable,
then translated into readable names and documented). It is meant for
personal preservation use only. Do not redistribute the source or the
binary. The game data (characters, stages, `data/`, fonts) is **not**
included: you need your own copy of the original archive.

## Contents

| Path | What |
|---|---|
| `build.sh` | builds the four libraries and the game, offline (default) or `--online` |
| `run-with-sound.sh` | starts the game with the 32-bit PulseAudio OSS wrapper (see "Running") |
| `Makefile` | the game build (called by `build.sh`; usable on its own with `LIBS32=`) |
| `src/`, `include/`, `data/mugen_data.S` | reconstructed engine: 59 documented C files, headers, byte-exact data image (see "Reading the sources") |
| `compat/allegro_inline.c` | hand-written wrappers for Allegro inline bank-switch routines |
| `thirdparty/` | patches and reconstructed code for the 2002 libraries; provenance in `thirdparty/PROVENANCE.md` |
| `downloads/` | the original library sources (offline build) and `SHA256SUMS` |

Libraries built from `downloads/`: Allegro 3.9.37 (the exact version in the
original binary), JGMOD 0.99, libcda 0.5.1 (plus three functions recovered
from the binary), and LibAmp (amp 0.7.6 plus a reconstruction of the lost
Allegro glue). zlib, libX11, libXext and libXxf86vm come from the system.

## Requirements

- `gcc` with `-m32` support (32-bit glibc development files), `make`,
  `patch`, `tar`, `sha256sum`
- 32-bit development files of libX11, libXext, libXxf86vm and zlib
- for `--online`: `curl` or `wget` and network access

Debian/Ubuntu i386 example: `apt install gcc make patch libx11-dev
libxext-dev libxxf86vm-dev zlib1g-dev`. On x86-64 distributions install the
multilib/lib32 equivalents. The kit was tested on Debian 11 i386 and on Arch
Linux-based CachyOS x86-64 with lib32 packages (see "Tested builds").

## Building

```sh
./build.sh                 # offline: uses downloads/, output in ./build
./build.sh /tmp/out        # offline, other output directory
./build.sh --online        # downloads the sources into OUTDIR/downloads first
```

Both modes check every archive against `downloads/SHA256SUMS` and stop on a
mismatch. The JGMOD and libcda archives are GitHub branch snapshots. If
upstream changes them, `--online` stops with a checksum error; use the
offline copies then. Logs go to `OUTDIR/build.log`; the result is
`OUTDIR/mugen-rebuilt`.

### Portable binaries

The executable needs at least the glibc version it was built against.

| Built on | glibc symbol version needed |
|---|---|
| Debian 11 i386 (GCC 10.2.1, glibc 2.31) | GLIBC_2.29 |
| CachyOS x86-64 (GCC 16.2.1, glibc 2.44) | GLIBC_2.43 |

Build on the oldest distribution you want to support. The Debian 11 build
was tested on Debian 11 and 12, Ubuntu 24.04, Fedora 42, Arch Linux, openSUSE
Tumbleweed and CachyOS. musl systems (Alpine) cannot run it.

A Debian 11 i386 container works. The tested method used an unpacked
`debian:bullseye` (i386) image under bubblewrap with the packages above
installed, running `build.sh` inside it with the network disabled. With
Docker or Podman this would look like the following (NOT tested in this
form):

```sh
podman run --rm -v "$PWD":/kit --platform linux/386 debian:bullseye sh -c \
  'apt-get update && apt-get install -y gcc make patch libx11-dev libxext-dev libxxf86vm-dev zlib1g-dev && /kit/build.sh /kit/build-debian11'
```

### Tested builds

| Build | Result |
|---|---|
| offline, Debian 11 i386 container, no network (2026-11-11, translated and documented sources) | built; `.text`, `.rodata` and `.data` byte-identical to the reference build below (the translation only renames, uses equivalent types and named constants, and adds comments) |
| offline, Debian 11 i386 container, no network (2026-11-08, decompiler-style sources) | built; byte-identical to the reference build |
| `--online`, CachyOS host (GCC 16.2.1, glibc 2.44), 2026-11-07 | all four downloads matched `SHA256SUMS`; built (older source revision) |
| the reference build, tested against the original game (2026-11-08) | identical game state in 10 game-mode scenarios, the CNS test character, 25 parser error messages, 91 state-controller acceptance cases, and full matches with eight third-party characters (incl. Balam_Knowledge vs Blizzard_Sword_Princess); same results on Debian 11/12, Ubuntu 24.04, Fedora 42, Arch Linux and openSUSE Tumbleweed (research tree: experiments/test-results.md T33-T42) |

Reference build (Debian 11, GCC 10.2.1), SHA-256 of the sections:

```
.text    01361794625f512cc77ee9fd5db378f33af0a11d84b92709bb623cf03aa68263
.rodata  4e8f1aabbf47ec645f5a56b1718aba5f88b55009c0b96f328a85cb0a23d1c56f
.data    c23e956ee53facb1b71348f9b7fc661e6c28b6d3533d44079eb1efe76b4d89c2
```

Known remaining difference from the original: shadows, reflections and
other scaled sprites can differ on one scanline by a few pixels in some
frames. Game state is not affected.

### Optimisation and speed

The game is compiled with `-O2` and options that keep the decompiled
code's meaning (see the comment at the top of the `Makefile`). Builds
before 2026-11-08 used `-O0`. They ran complex characters about five times
slower than the original: matches started late and could not hold 60
frames per second. Measured with Balam_Knowledge vs Blizzard_Sword_Princess
on a CachyOS host:

| | Original 2002 binary | `-O0` build | current build |
|---|---|---|---|
| character load time | 2.4 s | 9.9 s | 2.8 s |
| `-speedtest` (10,000 frames, logic only) | 30-34 s | 161 s | 23-30 s |
| frames per second during the match | 60 | 54-60 | 60 |

Do not change the optimisation options without re-running a comparison
against the original: plain `-O2` breaks the game (undefined behaviour in
decompiled code) and `-fexcess-precision=fast` with `-O2` changes results.

To compare: `objcopy -O binary --only-section=.text build/mugen-rebuilt t.bin && sha256sum t.bin`.
The whole file differs between builds because the debug information
records the build directory.

## Reading the sources

- **Function and file names** are Elecbyte's own (the original executable
  kept its symbol table). `src/elecbyte-lib/` is their engine library
  (`src/lib/` in their tree), `src/game/` the game (`src/mugen/`).
- **Comment blocks.** Every function starts with a block: original
  address and size, what it does, its parameters, the text keys, player
  fields and globals it reads and writes, what it calls and what calls it,
  its messages, and reconstruction notes. Every file starts with a
  module description.
- **Headers.** `include/compat.h` has the fixed-size types, `float80` (x87
  80-bit) and the helper macros (`X87_FIST32` = float-to-int as the x87 did
  it, `BITS_I2F` = reinterpret bits, `ZEXT8`, `CONCAT31`...).
  `include/mugen_fields.h` names the structure offsets: `player[PL_LIFE]`,
  `g[G_FRAME_COUNT]`, `CD_*`, `ARRAY_*`.
- **Name forms.**
  - `L_<address>` are labels at that original address.
  - `str_<text>` and `d_<address>` are data symbols.
  - `stale_`, `saved_` and `entry_` variables are register values the
    original read without visibly setting them (kept for exactness).
  - `argN` is a parameter whose role is not named yet; its comment block
    says what it is.
  - `stk_`/`buf_` variables and `frame` are stack locals kept at their
    original offsets.

## Running

Copy the original game directory somewhere writable and run the binary from
inside it:

```sh
cd mugen-copy          # contains data/, chars/, stages/, font/
/path/to/mugen-rebuilt
```

- **Display:** X11 or XWayland, windowed (`[Video Linux]` in `data/mugen.cfg`).
  Keyboard auto-repeat cannot be switched off by the game under X; the
  readme recommends `xset r off`.
- **Sound:** Allegro 3.9.37 only has an OSS driver (`/dev/dsp`). PulseAudio's
  OSS wrapper library `libpulsedsp.so` provides it, and works with PipeWire's
  PulseAudio server too. The game is a 32-bit program, so it needs the
  **32-bit** build of that library, which x86-64 systems usually don't
  install. Without it, `padsp ./mugen-rebuilt` prints

  ```
  ERROR: ld.so: object '/usr/$LIB/pulseaudio/libpulsedsp.so' from LD_PRELOAD cannot be preloaded (cannot open shared object file): ignored.
  ```

  and the game runs silently. (`$LIB` is expanded by the loader: for a
  32-bit program on Arch/CachyOS it is `lib32`, VERIFIED, so the file looked
  for is `/usr/lib32/pulseaudio/libpulsedsp.so`.) Install:

  | Distribution | Package | Status |
  |---|---|---|
  | Arch Linux, CachyOS, Manjaro (multilib) | `sudo pacman -S lib32-libpulse` (adds 6 packages) | VERIFIED on CachyOS: with the package's files in place, `padsp ./mugen-rebuilt` has sound (effects, MP3) through PipeWire 1.6, and exits cleanly from the EXIT menu |
  | Fedora | `sudo dnf install pulseaudio-libs.i686` (contains `/usr/lib/pulseaudio/libpulsedsp.so`) | from repository metadata, not run |
  | openSUSE | `sudo zypper install pulseaudio-utils-32bit` (contains `/usr/lib/pulseaudio/libpulsedsp.so`) | from the package file list, not run |
  | Debian/Ubuntu x86-64 | the 32-bit library is in `pulseaudio-utils:i386`, which cannot be installed next to the 64-bit `pulseaudio-utils` (VERIFIED by a simulated install on Ubuntu 24.04); install `libpulse0:i386` and unpack the library from the i386 package (`apt-get download pulseaudio-utils:i386; dpkg-deb -x pulseaudio-utils_*_i386.deb pa32`) | not run |
  | Debian/Ubuntu i386 | `pulseaudio-utils` | VERIFIED (Debian 12 i386) |

  Then start the game with `padsp ./mugen-rebuilt`, or with
  `./run-with-sound.sh` (copied next to the binary by `build.sh`). The
  script preloads the library by absolute path, says which package is
  missing instead of starting silently, and accepts a library outside the
  system paths (`MUGEN_PULSEDSP=/path/libpulsedsp.so`, plus
  `MUGEN_PULSE_LIBDIR=` for its 32-bit dependencies; VERIFIED with the Arch
  package files unpacked in a user directory). Sound effects, MP3, MOD and
  MIDI (DIGMID, with a `patches.dat` in the game directory) were tested
  this way. `.wav` files are not supported as background music by this
  engine version.
- **Volume:** the engine (through Allegro's `set_volume()`) writes the OSS
  PCM mixer with `MasterWavVolume` from mugen.cfg (default 255 = 100%) at
  start-up and at every match. The original 2002 binary does the same.
  Through libpulsedsp this sets the volume of the whole default output
  device, so plain `padsp ./mugen-rebuilt` turns the desktop volume up to
  100%. `run-with-sound.sh` switches libpulsedsp's mixer emulation off
  (`PADSP_NO_MIXER=1`, the same as `padsp -M`): the game's volume settings
  are then applied in software and the system volume is left alone
  (VERIFIED on Debian 12 i386 with PulseAudio and on CachyOS with PipeWire
  1.6.10). `MUGEN_OSS_MIXER=1 ./run-with-sound.sh` restores the original
  behaviour. With plain `padsp`, use `padsp -M ./mugen-rebuilt`.
- **Debian 12:** its `padsp` script is broken (`$LIB` is escaped twice, so
  nothing is preloaded and the game is silent). Use `run-with-sound.sh`.
- **Ctrl-C / SIGINT:** interrupting the game from the terminal can end in a
  segmentation fault: Allegro's signal handler shuts the library down in a
  background thread while the main thread is still running. The original
  2002 binary does the same (VERIFIED, 3 of 3 runs). Leave through the EXIT
  menu instead (VERIFIED: clean exit, status 0).
- **Joystick:** Allegro reads `/dev/js0` (legacy joydev API). Modern systems
  name the device `/dev/input/js0`, so create a link or a bind mount, and
  set `P1.Joystick.type = 1` in `[Input]`.
- **CD audio:** libcda opens `/dev/cdrom` (or the device in `$CDAUDIO`).
  `bgmusic = N.da` plays CD track N.
- The beta's expiry date (2002-07-01) has passed. The game shows the
  information screen (press F1) and a banner, and is otherwise usable.

## Licence notes

Allegro 3.9.37 ("giftware"), JGMOD, libcda and amp keep their own licences;
see the files inside the archives in `downloads/`. The reconstructed engine
code has no licence from Elecbyte. Keep it private.
