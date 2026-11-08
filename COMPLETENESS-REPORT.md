# Completeness report

What is done, how far it can be trusted, and what is left. Snapshot of
2026-11-08 (after session 5: -O2 build with original speed, all eight
third-party characters matching the original).

## 1. Artifacts accounted for

| Area | Coverage |
|---|---|
| Files in the archive | 112/112 inventoried with size, date, SHA-256 and type ([artifacts/inventory.tsv](artifacts/inventory.tsv)) |
| Binary resources (SFF, SND, FNT, ACT) | 29/29 parsed and validated ([artifacts/formats_parsed.jsonl](artifacts/formats_parsed.jsonl)) |
| Text definitions (DEF, AIR, CMD, CNS, CFG) | Documented from the shipped files and the engine's parsers ([formats/](formats/)) |
| Executable | Unpacked; all 24 sections and 778 object files identified |
| Functions | 5,750 functions attributed to source files; the 1,307 Elecbyte functions decompiled |

## 2. Reconstruction status (`reconstruction/`)

### Build

All **59 of 59** reconstructed files compile, and the tree links into a
working 32-bit executable against libraries built from their original
sources (section 3). The release build runs inside Debian 11 i386 (GCC
10.2, glibc 2.31); the binary needs glibc 2.29 or newer and 32-bit libX11,
libXext, libXxf86vm and zlib. `build.sh` does the whole build. VERIFIED.

### Behaviour compared with the original (differential tests)

Both programs run headless under gdb with identical inputs: frame skipping
disabled, the `srandom` seed pinned, and the debug FPS readout pinned. Each
drawn frame's 16-bit back buffer is dumped and compared byte for byte.
Results (VERIFIED, T10–T14):

| Test | Result |
|---|---|
| Title / main menu with the information screen, 90 frames | **90/90 frames pixel-identical** |
| AI-vs-AI quick match (`kfm` vs `kfm`, stage `kfm`), first 600 frames | 431/600 identical; in the other frames at most 16 pixels differ, all at the edges of scaled shadow/reflection sprites |
| Same match, whole round, every 25th frame | Both runs end on the **same frame** (6,275+); every sampled frame shows the same positions, life bars and timer; at most 280 differing pixels in one frame (a reflection edge row), typically 0–30 |
| Game state (global block `g`, all player records, palette globals) at frames 2–20 | Player records **word-for-word identical**; `g` differs only in the stored `time()` seed and a timing statistic |
| Original vs original (same harness) | 600/600 identical once the FPS readout is pinned, so the harness is deterministic |

These first tests used the earlier release. The **host test campaign** then
compared the current release with the original over 78 scenarios and
213,595 drawn frames, with scripted key and joystick input, data and
configuration variants, command-line options, emulated CD drive, and a CNS
test character:

| Area | Result (VERIFIED) |
|---|---|
| Game modes, menus, select screens, debug hot keys (T19, T25b) | game state identical on every fight frame; co-op started by P1 cannot continue in either binary (bug in the original); started by P2 it plays, identically |
| 27 mugen.cfg variants incl. resolution, Stretch, DoubleRes 1/2/3, depth, sound devices (T20) | identical, incl. the stretched/filtered `screen` bitmap (after fix #33) |
| select.def rosters, motifs `kfm`/`big` (T21) | identical (a zipped character fails to load in both) |
| Command-line options, `-log`, 6 storyboards (T22) | identical, incl. stdout and log files |
| Sound/music logic, CD, joystick (T23, T25, T26) | identical call and ioctl sequences; pad works in both |
| CNS test character, 82 of 86 controllers (T27) | 1500/1500 frames identical; 42/42 values as documented |
| Totals | state identical in 60/61 fight tests (the exception is the X-path smoke test, a harness effect); 46 tests pixel-identical, the rest differ by at most one 7-pixel scanline in some frames |

Session 4 (T33-T38, 2026-11-08) added:

| Area | Result (VERIFIED) |
|---|---|
| 25 parser error messages (broken CNS files) | 25/25 identical (before the fix 22 printed `(null)`) |
| 88 + 3 state-controller templates | identical acceptance in both: 86/88 (RemapPal, VictoryQuote unknown to this version) + TagIn/TagOut/GameMakeAnim |
| 8 third-party characters vs kfm, whole matches | all 8 identical game state after session 5 (T39-T41); Balam_Knowledge vs Blizzard_Sword_Princess 3484/3484 |
| Speed (T40) | session-4 release (-O0) 5.2x slower than the original; final release (-O2) as fast: load 2.8 s vs 2.4 s, 60 frames per second |
| Evaluator edge cases (46 values: overflow, INT_MIN, NaN bit patterns) | identical after the fixes #35-#37 |
| Regression of 10 game-mode scenarios with the final binary | game state identical in all |
| Six glibc distributions | matrix unchanged; fix fingerprint identical everywhere |

The remaining pixel differences have a known cause (section 4, "x87 extended
precision").

### Portability (VERIFIED, T15)

The same binary (built once on Debian 11) gives the **same frames on Debian
11, Debian 12 (i386), Ubuntu 24.04, Fedora 42, Arch Linux and openSUSE
Tumbleweed** (x86-64 with 32-bit libraries). Its title frames match the
original's pixel for pixel on every one of them; its match frames are
identical to its own Debian 11 run. The original (static) runs on all of
them and on Alpine; the rebuild needs glibc, so it does not start on Alpine
(musl). Re-run with the current release (T28): the match frames are now identical
to the original's in 595/600 frames on every glibc distribution.
The host campaign (T18–T30) ran on CachyOS natively.

### Sound (VERIFIED, T16)

Allegro 3.9.37 only has an OSS driver. The rebuild is dynamically linked, so
the PulseAudio/PipeWire OSS wrapper (`padsp`, i.e. `LD_PRELOAD` of
`libpulsedsp.so`) gives it `/dev/dsp`. Recordings of the PulseAudio sink
show sound effects, an MP3 test tone decoded by the reconstructed LibAmp
(440 Hz component about 1,500× the baseline) and a MOD test tune played by
JGMOD (261 Hz component about 10^5× the baseline) The static original
original cannot use `LD_PRELOAD`, so it stays silent on modern systems.
T23 repeated this on the host's PipeWire server and added MIDI through
DIGMID (`patches.dat` made with Allegro's `pat2dat` from FreePats). The
original's sound logic was compared through Allegro's silent driver
(identical calls). CD audio was tested with an emulated drive (T26); no
real CD hardware was available.

### Where the reconstruction deviates from a pure decompilation

Everything below is mechanical, listed in a `FIXUP:` comment above the
function, and justified in RESEARCH-METHODOLOGY.md:

| Kind | Count |
|---|---|
| Hand-written overrides (`reconstruction/overrides/`) | 6: `_mangled_main`, `BGArrayFree`, `SiSceneFree`, `unzlocal_getByte`, `SysExplodCreate`, `AnimElemProcessDrawFlags` |
| Exact-text site patches (`SITE_PATCHES`, each with its assembly evidence) | 9 functions (incl. `V_DoubleResDiag`, #33) |
| Generator rules applied | frame emulation (181 functions), float/int bit reinterpretations from the p-code (584 casts in 56 functions + oracle), x87 rounding modes (88 `frndint`), single-precision constants (17 literals in 16 functions), x87 register temporaries kept at 80 bits (269 locals), zero-extension of byte results (82 functions), data-address literals (31), ... (full list in RESEARCH-METHODOLOGY.md) |
| Ghidra database corrections | 71 hand-verified prototypes, 8 local types, 67 call-site overrides (variadic `SCtrlReadExpList`) |

## 3. Libraries

| Library | Version used | Relation to the binary |
|---|---|---|
| Allegro | **3.9.37** (SourceForge release tarball) | VERIFIED same version ("Allegro 3.9.37 (CVS), Unix" in the binary). Modern toolchain patch (5 files) + a force-included header for glibc's C23 math names: [reconstruction/thirdparty/allegro-3.9.37/](reconstruction/thirdparty/allegro-3.9.37/) |
| JGMOD | 0.99 (2002-10-08, GitHub archive) | STRONGLY INFERRED close: the binary's 128 JGMOD functions are all present in 0.99 under the same names; 0.99 is six months later than the build, so internal differences are possible (UNKNOWN) |
| libcda | 0.5.1 (GitHub, = 0.5 + licence change) | VERIFIED same backend (`linux.c` helpers match); three entry points that exist only in the binary (`cd_play_now`, `cd_play_loop`, `cd_is_playing`) were recovered from the assembly |
| LibAmp | **reconstructed**: amp 0.7.6 decoder + patch, `audiolib.c`/`audioalg.c` decompiled from the binary | The original LibAmp source is lost (only "LibAmp 0.3, 1998" is known from Ove Kåven's archived page; the file itself was not archived). Decoder function set and table sizes match amp 0.7.6 (VERIFIED); the PACKFILE I/O patch reproduces the binary's `get_input`/`dummy_getinfo`/`rewind_stream` (VERIFIED) |
| zlib, X11, pthread, libm | system | |

Allegro 4.4.3.1 was also downloaded and compared (section 5).

## 4. Known residual differences and risks

- **x87 extended precision (mostly fixed, T28).** GCC 2.96 at -O2 kept
  some floating-point intermediates in 80-bit x87 registers and used
  single-precision constants; the first reconstruction rounded every C
  `float` variable and read the constants as doubles. Two rules now restore
  the original precision. Before them, two game-state values differed in the 
  last bit in the host tests (an attack multiplier, a position after the 
  push check). After them, game state is identical in every test, and the 
  remaining pixel differences are one scanline of at most 7 pixels in some 
  frames (floor shadows/reflections), probably float return values: 
  C rounds them, the original returned them in st(0).
- **Optimised build.** The release is built with -O2 and options that
  keep the decompiled code's meaning (Makefile). Six problem classes (#35-#39,
  #41) concerned integers and floats passing through C types that do not
  match the x87 code; more such sites may exist in paths no test reached.
  The differential tests are the safeguard: rerun them after any change of
  compiler or options.
- **Values the original returned from untouched registers.**
  `SysExplodCreate` returns the caller's `%ebx` on three early-exit paths
  (unreproducible in C; the override returns -1 = "no explod");
  `get_volume_mp3` returns whatever is in EAX (the reconstruction returns
  0). Callers were checked: the first only compares with -1, the second only
  feeds a volume display.
- **Unclassified reinterpretations in 12 functions**
  ([artifacts/cast_reinterp_report.json](artifacts/cast_reinterp_report.json)):
  of the 612 int/float CASTs Ghidra lists, 584 are rewritten, 14 are casts
  of x87-intrinsic results (no conversion involved, correctly left alone)
  and about 14 could not be tied to a printed cast. The assembly oracle
  covers part of them; the differential tests (now covering all game
  modes, menus, storyboards, sound, CD, joystick and a CNS test character,
  T18–T30) found no effect.
- **Tested only with emulated hardware**: joystick (uinput virtual pad),
  CD drive (ioctl emulation), display (Xvfb; `FullScreen = 1` with real
  DGA/VidMode untested); the OSS MIDI sequencer was not available (DIGMID
  MIDI was tested). Characters: kfm, the test character and eight
  third-party characters (session 4).

## 5. Documentation coverage

| Section | State |
|---|---|
| historical/ | Complete from shipped evidence; external history marked UNKNOWN where not verifiable |
| architecture/, engine/, runtime/ | Module-level reconstruction from symbols, decompiled code and strace; function-level detail is in the code; structure map in engine/struct-map.md |
| binary-analysis/, linux/ | Complete, incl. library versions and the Allegro 3.9.37/4.4 ABI comparison |
| formats/ | Complete for the shipped examples |
| preservation/ | Original and rebuild verified on modern Linux; reproducible steps for both |

## 6. Things NOT done (deliberately)

- No modification of original files (verified by hash at the end of each
  session; all work used copies).
- No circumvention of the beta expiry. It only forces the info screen and a
  banner (VERIFIED by every reader of `g[0x74e6]`); the rebuild behaves the
  same.
- No generation of `expires = M,D,Y,checksum` values.
- No redistribution: the rebuilt executable and the reconstructed source are
  for personal preservation use (see README.md, "Legal note").
