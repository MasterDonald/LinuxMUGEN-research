# Third-party libraries: provenance and patches

The original executable links its libraries statically. The rebuild uses
the same libraries, rebuilt from their original sources by `../build.sh`
into `OUTDIR/libs32/` (nothing is installed system-wide). This directory holds only **our** files: patches, a shim
header and reconstructed code. The upstream sources are downloaded and
checked by SHA-256 on every build.

## Downloads (VERIFIED: hashes in ../downloads/SHA256SUMS)

| File | SHA-256 | Source |
|---|---|---|
| `allegro-3.9.37.tar.gz` | `ab2af22f…59ce6` | SourceForge, project `alleg`, files/allegro/3.9.37 |
| `jgmod-master.tar.gz` (JGMOD 0.99) | `4b4670a5…acd94` | GitHub `ArtificialRaccoon/JGMOD`, branch `main` |
| `libcda-master.tar.gz` (libcda 0.5.1) | `c1ddcc7a…13554` | GitHub `wangp/libcda`, branch `master` |
| `amp-0.7.6.tgz` | `c08e91d5…c69b8` | NetBSD pkgsrc distfiles mirror (`ftp.netbsd.org/pub/pkgsrc/distfiles/`) |

The two GitHub archives are branch snapshots, not tagged releases. Their
hash pins the exact content that was used; a later push to the branch would
change the hash and the build would stop with "checksum mismatch".

## Allegro 3.9.37 (`allegro-3.9.37/`)

Exact version of the binary (VERIFIED: "Allegro 3.9.37 (CVS), Unix" in
`.rodata`). The sources are not edited by hand; two files adapt them to a
2020s toolchain without changing behaviour:

- `modern-toolchain.patch` (5 files):
  - `src/fli.c`: cast-as-lvalue (`(*((unsigned char *)(p))++)`) is not C
    since GCC 4. The portable branch of the same macros is used.
  - `src/sound.c`: `extern DIGI_DRIVER digi_none;` followed by a `static`
    definition. Now declared `static`.
  - `src/i386/icpus.s`: `fnstsw %eax` becomes `fnstsw %ax`. Same encoding;
    modern GAS rejects the 32-bit operand.
  - `src/misc/modexgfx.s`: `movl mem, %es` becomes `mov mem, %es`. Same
    encoding.
  - `src/linux/fbcon.c`: `default:` at the end of a block becomes
    `default: ;`. GCC 10 rejects a label at the end of a compound statement.
- `glibc-c23-shim.h`: force-included with `-include`. glibc ≥ 2.28 declares
  the C23 functions `fadd`, `fsub`, `fmul`, `fdiv` and `fsqrt`. Allegro has
  fixed-point functions with the same names. The shim includes `<math.h>`
  with glibc's names moved aside.

Configuration: `--enable-static --disable-shared --disable-modules`. ALSA,
ESD and SVGAlib are disabled; the drivers left are those that are built
into the binary (OSS, X11/XShm/VidMode, fbcon, VGA, VBE/AF). The
`stamp-h.in` file is touched so that `alunixac.hin` is not regenerated.

## JGMOD 0.99

Not edited. The 11 player and loader files are compiled into
`libjgmod.a`. Relation to the binary: all 128 JGMOD functions in the
binary exist in 0.99 under the same names (STRONGLY INFERRED as a close
version). 0.99 is dated 2002-10-08, six months after the build, so internal
differences cannot be ruled out (UNKNOWN). MOD playback was verified (T16).

## libcda 0.5.1 (`libcda/`)

`linux.c` is not edited. `libcda-mugen-additions.c` adds three entry
points that are in the binary but in no published libcda release:

| Function | Address | Size | Reconstruction (VERIFIED from objdump) |
|---|---|---|---|
| `cd_play_now` | 0x081bbc10 | 175 B | instruction for instruction the same as `cd_play` |
| `cd_play_loop` | 0x081bbcc0 | 175 B | the same as `cd_play` |
| `cd_is_playing` | 0x081bbef0 | 23 B | `cd_current_track() != 0` |

CD audio is untested: no CD hardware was available.

## LibAmp (`libamp/`)

The original LibAmp source (Ove Kåven's Allegro port of Tomislav Uzelac's
amp) was not found. The only archived trace is Ove Kåven's download page
as captured by the Internet Archive on 1998-12-05, which links "libamp.zip"
("LibAmp 0.3, a useless(?) DJGPP+Allegro port of Amp"). The zip file itself
was not archived (VERIFIED 2026-11-06: the Wayback CDX index for
`arcticnet.no/~ovek/files/*` has no entry for `libamp.zip`). LibAmp was
therefore reconstructed:

- **Decoder**: amp 0.7.6 sources, plus `amp-0.7.6-libamp.patch`, which
  changes `getbits.c` and `audio.h` to read from an Allegro `PACKFILE`
  (`pack_fread`, `pack_fseek`, `pack_feof`). The binary's versions of these
  functions do this (VERIFIED at 0x080e4d00, 0x080e4d60, 0x080e4de0), and
  so does the patch. A backward seek on a PACKFILE calls `abort()`, as in
  the binary. The decoder function set and table sizes match amp 0.7.6
  (VERIFIED). The exact amp version that LibAmp 0.3 was based on is UNKNOWN.
- **`audiolib.c`**: the public API (`install_amp`, `load_amp`, `poll_amp`,
  `seek_amp_abs`, `unload_amp`, `set_volume_mp3`, `get_volume_mp3`, …),
  14 functions decompiled from object `audiolib.c`
  (0x080e0b10–0x080e17d1).
- **`audioalg.c`**: output through an Allegro `AUDIOSTREAM` with a ring
  buffer. 21 functions decompiled from object `audioalg.c`
  (0x080e17e0–0x080e2329).
- `libamp.h`, `config.h`: our header for the API, and amp's configuration
  for Linux/i386.

Defects in the original are reproduced and marked `AS IN ORIGINAL`:

1. A dead `amp_playing` test in the seek function.
2. The source pointer is not advanced between ring-buffer chunks. This is
   harmless, because whole-granule writes never cross the ring end.
3. The stereo silence padding writes the wrong words.
4. `get_volume_mp3` is a bare `ret` in the binary, so it returns whatever
   is in EAX. The reconstruction returns 0.

MP3 playback was verified (T16).

## System libraries

zlib, libX11, libXext and libXxf86vm are the distribution's 32-bit
packages. libm and libpthread come from glibc. How each library relates
to the version in the original binary is documented in the research tree
(LINUXMUGEN-RESEARCH/linux/libraries.md).
