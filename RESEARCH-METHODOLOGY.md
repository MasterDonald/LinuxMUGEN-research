# Research methodology

## Principles

- The original files are never modified.
- Every claim carries an evidence class (VERIFIED / STRONGLY INFERRED /
  HYPOTHESIS / UNKNOWN), its source, and an address, offset or command.
- Decompiler output is treated as a hypothesis about the code. Each
  systematic correction was checked against the instructions; see
  "Validation" below.
- Dynamic tests ran only in a `bwrap` sandbox on a copy of the game
  directory, with no network.

## Tools

| Tool | Version | Use |
|---|---|---|
| REA (`rea-agents`) | 6.8.0 | MCP front end |
| Ghidra (headless) | 12.1.4, JDK 25 | Analysis backend for REA, and the corrective passes |
| UPX | 5.2.0 | Lossless unpacking (`upx -d`) of the UPX 1.20 `linux.exec/i386` stub |
| binutils | system | `readelf`, `objdump` (disassembly, STABS, symbols), `strings` |
| strace, bwrap | system | Dynamic tracing in a sandbox |
| GCC | 16.2.1 (`-m32`) host; **10.2.1 in Debian 11 i386** for the release build | Compile checks; the release binary is built in the oldest supported distribution |
| gdb | 10.1 (Debian 11) and distro versions | Frame-locked differential captures, watchpoints, call counts |
| Distribution root filesystems | Docker Hub images (digests in artifacts/distro_images.txt), run with bubblewrap; packages installed with a mapped-root user namespace | Release build, headless tests (Xvfb), cross-distribution matrix |
| Python 3 | system | Pipeline scripts |

## Pipeline

```
mugen (UPX 1.20) --upx -d--> mugen.unpacked
   |                            |
   |   readelf -s  ----------> symtab.txt Python Script--> funcmap.tsv (5,750 functions -> source file)
   |                            |
   |   REA open_binary + decompile_all (Ghidra default analysis)
   |                            +--> decomp_elecbyte/ (baseline, 1,307 files)
   |
   +-- Ghidra headless project:
        PreEnableParamId          enable Decompiler Parameter ID
        FixCallingConvention      reset bogus __regparmN to __cdecl
        ApplyGlobalTypes          commit types from Python Script
        ApplyReturns              return types from Python Script
        MarkTailCalls             CALL_RETURN override on tail-call jumps
        DefineTypes               PalGrpFlag, MugenCmdLine
        SetSignatures             hand-verified prototypes (manual_signatures.tsv)
        SetLocalTypes             hand-verified stack locals (manual_locals.tsv)
        SetVarargOverrides        call-site signatures of SCtrlReadExpList
        ExportElecbyte / ExportRefs / ListCallees
        ListFloatCasts / ExportCastKinds / ExportRoundSites
                                    |
                                    v
        decomp_typed/ + refs_typed.tsv + signatures.tsv
                                    |
                              Python Scripts
                                    |  decomp_final/
                      Python Scripts  (+ reconstruction/overrides/)
                                    v
        reconstruction/{src,include,data,compat}
                                    |  build_release.sh (Debian 11 i386):
                                    |  build_libs32.sh -> Allegro 3.9.37, JGMOD, libcda, LibAmp
                                    v
        mugen-rebuilt  --tools/difftest/--> frame/state comparison with the original
```

## Problems found in the decompiler output and how each was handled

Each problem was found by a check, explained from the assembly, and fixed
in the Ghidra database where possible, so the decompiler produces
consistent code. The C output was not patched by hand except where noted.

| # | Problem | How it was detected | Root cause (VERIFIED in assembly) | Fix |
|---|---|---|---|---|
| 1 | Call arguments missing (1,220 call sites) | Python Script | GCC 2.96 pads calls to 16-byte alignment with dummy `push` instructions; without callee parameter counts Ghidra can't tell padding from arguments | Decompiler Parameter ID (missing args: 1,220 -> 4) |
| 2 | Fake `__regparm1/2/3` conventions (137 functions) | Prototypes with register parameters; `push %edx; push %edx` prologues (e.g. `PRSprArrayFree` `0x8049b70`) | Parameter ID read prologue alignment pushes as saved register arguments | Ghidra Script (Elecbyte, JGMOD, LibAmp, Allegro ranges) |
| 3 | Arguments shifted by one around `fgets`/`ftell`/`fread`/`fwrite`/`fclose`/`cd_set_volume` | `in_EAX` arguments, small constants cast to `FILE *` | Same regparm error on six library callees | Real prototypes, forced `__cdecl` (`manual_signatures.tsv`) |
| 4 | Globals typed differently in each function (`g` as `int` and `int *`) | Compile errors (subscripts on int) | Weak `undefined4` globals; the decompiler guesses per function | Ghidra script (142 globals) |
| 5 | Wrong return types (`ecalloc` returned void; 64-bit returns) | Callers using the result of void functions | Parameter ID with "commit void returns" off; EDX padding pushes read as 64-bit returns | Python Script (REA baseline + caller usage) + Ghidra Script. A first attempt that read registers after calls was discarded: padding pushes made it unreliable |
| 6 | Callee body pasted into its caller (12 functions, e.g. `EBT_MutexLock`, `SndMidiReadFile`, `ContinueScreen`) | Library internals (`__pthread_initial_thread`) appearing in Elecbyte code | Tail-call `jmp` into a thunk or small function | Ghidra Script: CALL_RETURN flow override |
| 7 | Parameters missing in 32 functions (varargs, struct by value) | Python Script: independent stack-depth tracker counting incoming argument reads | Variadic and by-value arguments are invisible to Parameter ID | Hand-verified prototypes: varargs, `PalGrpFlag`, `MugenCmdLine` |
| 8 | Stack-tracking failures (`main`, `GameInit`) | `StackY` variables, "unreachable block" warnings, `&stack0x…` | `rep movsl` by-value copy of a 0x32c-byte struct; GCC "rebalance" of `esp` | `main` rewritten by hand from assembly (`reconstruction/overrides/`); `GameInit` by-value parameters attached by an exact offset table in the generator |
| 9 | Value-stack locals typed `float` holding ints and pointers (`InfToPostArray`) | `case 1.4013e-45:` labels (float bit patterns of 1, 2, ...) | Expression evaluator keeps an untyped 4-byte cell stack | Ghidra Script (`int[132]`) |

| 10 | Float struct fields read/written as int<->float **value conversions** (165 sites in 35 functions, e.g. `PlayerUpdate`) | Python Script: for each `(float)p[i]` / `p[i] = (int)x`, check the instruction at byte offset `i*4` | Ghidra prints INT2FLOAT and a reinterpreting cast with the same `(float)` text; struct pointers typed `int *` (VERIFIED: `flds 0x224(%ebx)` vs C `(float)player[0x89]`) | Generator rewrites only the confirmed offsets to `*(float *)&p[i]` (the check is a lower bound, see COMPLETENESS-REPORT.md) |
| 11 | Function addresses as integer literals (`install_int_ex(0x807af40, ...)`) | grep for literals equal to function entries | Ghidra did not resolve the code pointer | Generator replaces them with `(int)TimerHandler` |
| 12 | Busy-wait loops on interrupt-updated globals | reading `TimerWaitSync` | The original reloads `SyncCur` every iteration (VERIFIED 0x0807b160); modern optimisers would not without `volatile` | Timer, keyboard and input-flag globals declared `volatile` |


### Problems found when linking and running the rebuild (2026-11-07)

Each was found by a crash, a differential test or a static scan, explained
from the assembly, and fixed in the Ghidra database or by a generator rule
(listed in a `FIXUP:` comment on the function), never by editing `src/`.

| # | Problem | Detected by | Root cause (VERIFIED in assembly) | Fix |
|---|---|---|---|---|
| 13 | Inlined `repz cmpsb` with flags initialised from `&stack0x..` (5 functions) | compile error | Ghidra seeds CF/ZF from an earlier stack comparison; with a constant non-zero count the loop always overwrites them | Rule: dead flag initialisations set to 0 |
| 14 | `PalGrpMakeFlag(&stack0x..)` hidden-return struct written into the argument area (7 sites) | compile error | GCC 2.96 built the by-value struct directly in the outgoing argument slots | Rule: explicit `PalGrpFlag` temporary passed to the next call |
| 15 | Loop entered in the middle, stack depth lost (`BGArrayFree`, `SiSceneFree`, `PlayerUpdate`) | compile error | Join of paths with different apparent depth | Overrides for the two small ones; for `PlayerUpdate` the local buffer is widened so the pseudo-pushes stay in it |
| 16 | Stack buffers typed as one scalar (`TPGroupSeek`: 4-byte `local_11c` receives a whole "[section]" string) and structs split over several locals (`FontReadFilePtr`) | crash in `GameConfigRead` | Ghidra types locals from the accesses it sees; callees write more | **Frame emulation**: in the 181 functions where a local's address escapes, all named locals are placed at their original frame offsets in one byte array |
| 17 | Variadic arguments of a shared `sprintf` lost (31 sites) | crash, Python Script | several error paths push their own arguments and jump to one call | Explicit argument array; arguments recovered from the pushes for `GameConfigRead` (Python Script), 0 elsewhere |
| 18 | Indirect calls with register arguments (Allegro bank switching) and lost stack arguments (`set_window_title`) | crash | `read_bank`/`write_bank` take `%edx`/`%eax`; inline Allegro functions | `compat/allegro_inline.c` (compiled with the real header) + site patches |
| 19 | `.rodata` tables declared as bytes and truncated to Ghidra's type length (`KeyCfgToKBIMap`: 4 of 44 bytes) | crash | data emitted per referenced address | typed declarations; extents from the symbol table, overlapping items merged |
| 20 | Data addresses printed as integers (197 literals, e.g. "ElecbyteSpr" at 0x82772cc) | SFF load failure | no Ghidra symbol at the address | Rule: literal -> reference into the data image |
| 21 | Callee result typed `bool`/`char`, upper bytes as `extraout_var` (200 sites) | "Can't read video config" | callees return full 32-bit values (all 56 checked) | Rule: `GHIDRA_ZEXT8()` |
| 22 | **int/float bit reinterpretations printed as value conversions** (612 p-code CASTs in 57 functions) | NaN positions, wrong backgrounds | Ghidra prints CAST and FLOAT_INT2FLOAT/TRUNC the same way | Ghidra Script (exact inventory), Ghidra Script (classifies every printed cast by p-code data flow), Python Script (rewrites to `GHIDRA_I2F`/`GHIDRA_F2I`) |
| 23 | Floats stored into / read from `undefined4` locations, arguments and returns | background element fields `-1.0` stored as `-1` | `undefined4` is typeless in Ghidra, `uint` in C | Rule: bit copies, driven by an expression-type inference |
| 24 | x87 `frndint` printed as `ROUND()` regardless of the rounding mode (88 sites) | sprite edges, trigger `floor()`/`ceil()` | the preceding `fldcw` sets RC=down/up/truncate | Ghidra Script + Python Script: `GHIDRA_FLOOR/CEIL/TRUNC/RINT` |
| 25 | Wrong prototypes: `EvalExpressionF` returns `float` in ST0 (119 callers read `extraout_ST0`), `SPopI` pops an int, BG/player struct pointers typed `float *` | NaN velocities, wrong BG positions | `flds; ret`; `mov` stores | `manual_signatures.tsv` |
| 26 | Variadic `SCtrlReadExpList` (67 call sites, args lost in `SCtrlParseElemType`) | crash in the state parser | one pointer per n/i/f character, walked from the first variadic slot | variadic prototype + Ghidra Script (call-site signatures from the format string) |
| 27 | Return value lost: `SysExplodCreate` returns the index in `%ebx` but Ghidra reused the variable; `AnimElemProcessDrawFlags` returns 0/2 on three paths printed as `return in_stack_..` | crash; the call-count comparison (subtractive sprites drawn 50 vs 0 times) | decompiler variable merging | overrides |
| 28 | Library prototypes with wrong arity (`install_sound`, `lock_sample`) | `gcc -aux-info` comparison with the Allegro headers | Parameter ID | site patches + corrected declarations |
| 29 | glibc 2.34+ / 2.38+ incompatibilities (`pthread_yield`, `__isoc23_*`), labels before `}` for GCC 10 | link errors, portability | | `sched_yield`, `_DEFAULT_SOURCE`, empty statement rule |
| 30 | amp's out-of-bounds loops turned into infinite loops by GCC 10 | MP3 playback crash | UB in `xr[ch][0][l]` | `-fno-aggressive-loop-optimizations` |

### Problems found by the host test campaign (2026-11-07, experiments T18–T30)

| # | Problem | Detected by | Root cause (VERIFIED in assembly) | Fix |
|---|---|---|---|---|
| 31 | Single-precision constants used as doubles (17 literals in 16 functions) | CNS test character: P1's attack multiplier 1.9499999 (original) vs 1.95 (rebuild) after `AttackMulSet value = 1.5` with attack 130 | `fmuls 0x8278824` at 0x080c0d99 multiplies by the **float** 0.01f; Ghidra prints `0.01`, which C reads as a double | Python Script: literals whose value matches an inexact 4-byte x87 memory operand of the same function get an `f` suffix (8-byte operands with the same value would be reported as ambiguous; there were none) |
| 32 | x87 register temporaries rounded to float (269 `fVar`/`dVar` locals) | joystick Arcade test: P1's X position differs in the last bit at frame 1555; the known "edge pixel" differences in scaled shadows/reflections | GCC 2.96 -O2 kept such values in x87 registers at 80-bit precision (`PlayerCheckOverlap` 0x080b3752–0x080b37b3 keeps the distance in st(0) and never stores it); at -O0 a C `float` variable is stored to a 4-byte slot on every assignment. Ghidra names stack-resident locals `local_XX`, so `fVarN`/`dVarN` are exactly the values that were not | Rule `apply_x87_temps`: these temporaries are declared `float10` (= `long double`, the x87 80-bit format). Stores, arguments and return values are still rounded by C's conversions, as `fstps` did. Result: CNS test 1500/1500 frames identical (was 1213), AI match 2457/2500 (was 431/600 in T11), remaining differences one scanline of at most 7 pixels |
| 33 | Signed/unsigned 16-bit comparison in the DoubleRes = 1 filter | host campaign: back buffer and game state identical, but output row 1 of the 640x480 `screen` bitmap differed (34 pixels) | `V_DoubleResDiag` compares pixels as 16-bit registers (0x080531e8–0x0805320a: `cmp %ax,%dx`); Ghidra typed the first-row source pointer `undefined2 *` and the temporary `short`, so C's promotions made pixels >= 0x8000 unequal | site patch (source pointer `short *`); a scan of all functions for `==`/`!=` between unsigned and signed 16-bit operands found only these two sites |
| 34 | Variadic arguments lost when the format is not visible | survival results screen "Rounds survived: 128" (original 0); "State machine stuck in loop ... (stopped after 3 loops): 0 for (null)"; 22 of 25 parser error messages printed `(null)` | the format comes from a data file (system.def `winstext`) or several error paths share one `sprintf` (GCC 2.96 pushes per path, then jumps); Ghidra shows only the fixed arguments | audit of every call to a variadic function (Python Script: original pushes vs source arguments, padding and shared calls classified); per-path arguments from the assembly in `FORMAT_ARGS`; two site patches. The generator now also handles wrapped and repeated format assignments (T33) |
| 35 | 32-bit fist/fistp written as a 64-bit conversion | Balam_Knowledge / test character: `floor(-4294967296.0)`, 1e10, 3e9 gave wrapped values (1e10 -> 0x540be400) instead of 0x80000000 | `ROUND(x)` was `(longlong)(x)`, correct for the 105 `fistpll` sites; the 586 `fistpl`/`fistl` sites store 32 bits and give the x87 "integer indefinite" 0x80000000 on overflow and NaN | `GHIDRA_FIST32()` in ghidra_compat.h; Python Script rewrites the ROUND token of every 32-bit fist site (it already classified each site by instruction) (T36) |
| 36 | Integer operands of the expression evaluator held in float variables | Balam_Knowledge diverged at frame 2: `var(8) & -2147483648` true in the original, false in the rebuild; `var(0) = 2143289345` false | Ghidra typed the operand words `fVar8`/`fVar4`/`unaff_EDI` float because they also carry floats; the original tests them with integer instructions in the integer branches (0x080849d0 `cmp $0x1,%ebp; test %edi,%edi`). As floats, 0x80000000 (-0.0) tested as zero and NaN patterns compared unequal | rule `WORD32_OPERANDS`: the three words become `ghidra_word32` (union of int and float); integer uses read `.i`, float uses `.f` (T36) |
| 37 | Float-typed copies quiet signalling NaNs | test character: `var(0) = 2139095041` (0x7f800001) stored as 0x7fc00001 in the rebuild | integer words in arrays Ghidra typed `float` (the expression parser's value stack) were copied with `flds`/`fstps`; loading a signalling NaN into the x87 unit sets the quiet bit. The original copies them with integer moves (`rep movsl` at 0x0808383a) | rule `apply_bits_copies`: copy statements between float pointers become 4-byte `memcpy`, reinterpreting reads of float array elements read the bytes in place. A broader version (all float lvalues and stores) was tried and made things worse; it was withdrawn (T36) |
| 38 | Float field read as an integer, missed by the oracle | genjitsu&friends diverged at frame 260: a projectile created in frame 259 hit P2 in the original only; Balam_Knowledge vs Blizzard_Sword_Princess played a much longer match than in the original | `PlayerCheckProjHit` subtracts the projectile's y position as a float (`fsubs 0x48(%ebp)` at 0x080b5f40); the source had `(float)piVar8[0x12]`, an int-to-float conversion of the bit pattern. Python script matches displacements regardless of the base register, and a stack temporary `fistpl 0x48(%esp)` made the field look integer | the oracle ignores `%esp`-relative operands (stack temporaries are never fields); it found exactly this one site (T39) |
| 39 | -O2 build: undefined behaviour and excess precision | the -O0 build ran Balam_Knowledge vs Blizzard 5.2x slower than the original (late start, dropped frames); first -O2 build: "Can't find file fight.def"; then last-bit differences (D-Donald's attack multiplier) | (a) Ghidra writes integer[pointer] (`__n[(int)param_2]` in `splitdirfile`); with the integer 0 GCC deletes the store through a "null pointer"; (b) with `-fexcess-precision=standard` (needed so that assignments round as the -O0 stores did) C evaluates floating constants in long double, so 0.01f became 0.01; (c) `gameloop.c` and `p-update.c` gave different pixels/state at -O2; a per-function bisection showed the cause was the precision mode, not optimisation (see #41) | flags `-fno-strict-overflow -fno-delete-null-pointer-checks -fno-isolate-erroneous-paths-dereference -fexcess-precision=standard`; site patch for `splitdirfile`; generator pass `apply_const_casts` (77 inexact constants cast to their type); after #41 every file is built with -O2 (the Makefile keeps an `O0_SRC` list, now empty). Each step bisected per object file against the original (T40) |
| 40 | Test-harness artefact: heap pointers hashed as data | state "differences" from frame 1-3 with Balam_Knowledge although frames, pixels and match length agreed | the driver masked pointer-like words only in 0x08000000-0x0fffffff and >= 0xe0000000; Balam's 59 MB of sprites push the heap past 0x10000000, and the static original maps blocks elsewhere | Python Script masks every value inside a mapped region of the process (/proc/PID/maps), except in the var/fvar/sysvar arrays, which hold game data (a var equal to 0x1419fa15 fell inside one binary's heap) (T40) |
| 41 | Integer-to-float conversions rounded to single precision | norris: HitDef damage 2147483647 scaled by the attack multiplier gave 0x80000000 instead of 0x7fffffff (state diverged at frame 1808); `gameloop.c`/`p-update.c` differed at -O2 | Ghidra prints x87 `fild` as `(float)<int>`. `fild` is exact (80-bit) and rounds nothing; under `-fexcess-precision=standard` the C cast rounds to float at once (2147483647 -> 2147483648.0f), so `damage * mul + 0.5` overflowed in the following 32-bit fist. At -O0 (default "fast" excess precision) GCC kept the value unrounded, which is why the -O0 build was right | generator pass `apply_int2float_exact`: casts of integer-typed operands (`iVarN`, `int *` arrays, `(int)` expressions, `*(int *)`, `GHIDRA_F2I/FIST32`) become `(float10)`, exact for every 32-bit integer in any precision mode; 719 sites in 112 functions. With it all 59 files build with -O2 and all eight third-party characters match the original (T41) |

## Mechanical rewrites in the generator

All are listed as `FIXUP:` comments above the affected function:

- `gcc2_compiled_` -> `_mangled_main` (label shared with `main`'s address);
- `void` functions that only "returned" unaffected registers;
- Ghidra partial-variable syntax `x._O_S_` -> sized access at byte offset;
- pointer-typed `case` labels;
- `&stack0x…` in varargs functions -> `va_list`;
- x87 control-word save statements removed (the truncating cast is the
  `ROUND()` macro, VERIFIED at `0x80495ee`: `movb $0xc,0x3d(%esp)`, i.e.
  RC=truncate);
- `PalGrpFlag` by-value loads; `::g` shadowing; `NAN(x)` -> `GHIDRA_ISNAN(x)`;
- x87 register temporaries (`fVarN`, `dVarN`) declared `float10` (#32).

Before the generator, Python Script marks single-precision
constants (#31) in the decompiled C, after Python Script.

## Validation

| Check | Result |
|---|---|
| Decompiled body covers each symbol's full byte range (Python Script) | 1,307/1,307; all uncovered bytes are alignment padding |
| REA baseline vs final pass (Python Script) | 68 functions flagged; reviewed classes are documented in `artifacts/review_list.json` |
| Parameter oracle (Python Script) | 1,226 match; 38 have extra (unused) parameters; 21 "missing" are all explained (varargs, `PalGrpFlag` by value); 22 untracked |
| Float reinterpretations | p-code inventory 612; 584 rewritten from the p-code; the assembly oracle as second net ([artifacts/cast_reinterp_report.json](artifacts/cast_reinterp_report.json)) |
| Library prototypes vs the real headers (`gcc -aux-info`) | 96 compared, 3 differed, fixed |
| Compile and link | 59/59 files; working executable |
| **Differential tests** (`tools/difftest/`) | title 90/90 frames identical; AI-vs-AI round ends on the same frame with identical sampled frames except scaled-sprite edge pixels; player records identical at frames 2–20 |
| Cross-distribution | identical frames on six glibc distributions |

### Differential testing method

The original (unpacked, debug sections stripped so that gdb 10 can load it;
VERIFIED identical loaded segments) and the rebuild are run under gdb in a
headless Xvfb inside the same root filesystem. The gdb scripts are the same
for both binaries because the rebuild exports the original data symbol names
(`g`, `V_Current`, `MasterPal`, ...):

1. `srandom()`'s argument is pinned (the game seeds with `time(NULL)`).
2. On entry to `ModeSelect`/`GameLoop`, frame skipping is switched off
   (`g[0x7305] = 0`), so every logic tick is drawn and wall-clock speed has
   no effect; the debug FPS readout is pinned.
3. At every `MasterPalFinishedDraw` (end of a drawn frame) the current back
   buffer (`V_BufGetSurface(V_Current, V_CurrentIdx)`, 320x240x16) is dumped.
4. Python Script compares dumps byte for byte; Python Script
   compares state dumps word by word, ignoring pointer values.

Host test campaign (T18–T30): the same principle, extended by
Python Script (gdb Python) so that input, configuration and
data can vary. Lessons from building it, each found because the original
disagreed with itself or with the rebuild for a reason outside the code
under test:

- `run > file` in gdb replaces the program arguments given with `--args`;
  the driver repeats them.
- In the static original a symbolic breakpoint on `srandom` is placed
  after the prologue, where `$esp+4` is not the argument; the seed is now
  pinned at the raw entry address, set once `main` is reached (so that the
  rebuild's libc `srandom`/`srand` is resolved).
- X keyboard auto-repeat is generated on wall-clock time; it is switched
  off on the test X server (the MUGEN readme recommends `xset r off`).
- Delivering X key events to a program stopped under gdb proved unreliable:
  Allegro's background thread handles the queue, the socket is read only by
  the next screen blit, and events were occasionally lost. Keys are
  therefore injected one level lower by default: the PC scancodes Allegro's
  X keyboard driver would produce (its own keysym table, `pckeys.json`) are
  passed to Allegro's `_handle_pckey()` from the main thread with the other
  threads stopped. This covers Allegro's keyboard translation, `key[]`, the
  game's `KBBufferRawHook` and everything after it. The X path is kept as an
  option and was used for smoke tests (T18).
- The player record is 0x3464 bytes (`ecalloc(1,0x3464)` in `PlayerNew`
  0x080af8f0); hashing more includes unrelated heap bytes. Pointer-like
  words are masked because heap addresses differ between the binaries.
- Game-level call traces include only calls made from Elecbyte functions
  (GCC 10 inlines some of Allegro's internal calls). In the original, gdb
  occasionally reports one breakpoint hit twice (it varies between runs of
  the same binary), so consecutive identical entries are collapsed.
- Output options (resolution, Stretch, DoubleRes, colour depth) do not
  change the 320x240 back buffer, so the stretched/filtered image is also
  compared, read from Allegro's `screen` bitmap. Captures from the X server
  were timing dependent.

When frames differ, the cause is localised with state dumps, call counts
(breakpoint hit counts per function) and hardware watchpoints on a
differing pixel or field; the original is checked against itself to rule out
non-determinism.

"Compiles" never meant "behaves identically": linking and running the
rebuild (crashes, static scans and the differential tests) exposed 15
problem classes (#16–#30 above), and the differential tests eleven more
(#31–#39, #41), plus one harness artefact (#40) in code that already compiled, besides the
three compile-error classes #13–#15.
