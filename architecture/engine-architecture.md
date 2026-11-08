# Engine architecture

Statements here come from the decompiled code, the symbol names (original
Elecbyte names) and the call graph. Function names alone are never taken
as proof of behaviour; where only a name supports a statement it is marked
HYPOTHESIS.

## Layers

| Layer | Files | Responsibility | Class |
|---|---|---|---|
| Platform | Allegro, X11, glibc | display, input devices, timers, audio output, files | VERIFIED |
| Elecbyte engine library | `anim-lib.c` .. `lthreads.c` (28) | generic 2D services: virtual buffers and blitters (`vbuf.c`, `spr16*.c`), sprite archives (`spr-lib.c`, `spr-read.c`), animations (`anim-lib.c`), backgrounds (`bg-lib.c`), collision boxes (`clsn-lib.c`), command detection (`cmd-dtct.c`), text parser (`txtparse.c`), sound (`snd-lib.c`), input (`kbll-lib.c`, `pad-lib.c`, `input-lb.c`, `inp-kbi.c`, `inp-menu.c`), palettes (`pal-lib.c`), fonts (`font-lib.c`), timers (`time-lib.c`), storyboards (`cutscene.c`), debug GUI (`gui-lib.c`), clipboard text (`clipbrd.c`), generic arrays (`array.c`), misc and streams (`ebcommon.c`), threads (`lthreads.c`) | VERIFIED (file attribution) / STRONGLY INFERRED (responsibilities, from function sets) |
| MUGEN game | `afterimg.c` .. `precache.c` (30) | the fighting game: modes, menus, character select, matches, players and their state machines, expressions, AI, effects, music, precaching | same |

The game layer calls the library layer, never the other way, except
through callbacks (e.g. `SceneRegisterBGMFn` lets storyboards start music
through `bgm.c`) (VERIFIED: call graph direction in `artifacts/callees.tsv`
and `refs_typed.tsv`).

## Central data structures (offsets from the reconstruction)

| Structure | Evidence | Notes |
|---|---|---|
| Global game block `g` | 1 pointer in `.data`; offsets up to 0x20b5c | settings (`g[0x6ef3]` sound enable, `g[0x755b..]` sound params), error text at `+0x20748`, debug window at `+0x20b5c`, motif path at `+0x5380`, players `g[0x73da]`/`g[0x73db]`, expiry flag `g[0x74e6]` (VERIFIED, each from code) |
| Player | `int *player` (typed in the reconstruction); fields like `[0x4ef]` (animation), `[0x2fa]`/`[0x2fb]` (state lists), `[0x972]` (palette group flags as `PalGrpFlag`), `+0x25c8` | many hundreds of fields; recovering them is the main task of a 64-bit port (STRONGLY INFERRED) |
| `PalGrpFlag` | 5 x uint32 bit set, passed by value | VERIFIED (see architecture/subsystem-analysis.md, Palette FX) |
| `MugenCmdLine` | 0x32c bytes, passed by value to `GameInit` | VERIFIED |
| Text-parser handle (`TP*`) | 0x34-byte header with line/group index arrays | VERIFIED (`TPReadFilePtr`) |
| Arrays | generic resizable arrays (`ArrayNew`, `ArrayAddResize`, `ArrayScanFirst/Next`) used for players, helpers, explods, BG layers | VERIFIED |

## State machine

Each player runs the CNS state machine: special states (`[Statedef -1]`,
`-2`, `-3`) and the current state's controllers are tested every tick
(`PlayerSCtrlUpdate`, `PlayerSCtrlUpdateSpec`); triggers are evaluated from
compiled postfix arrays (`SCtrlTrigEval`, `EvalExpressionI/F`); controllers
run in `PlayerSCtrlApplyElem` (VERIFIED by call graph and the controller
switch). See [../formats/cns.md](../formats/cns.md) and
[../engine/character-system.md](../engine/character-system.md).

## Concurrency

- The Allegro timer callback `TimerHandler` (180 Hz) increments `Ticks`
  and the sync counter. The main thread busy-waits in `TimerWaitSync`
  (VERIFIED, 0x0807b160).
- The keyboard low-level callback `KBBufferRawHook` fills `KBBuffer` and
  flag arrays (VERIFIED).
- `PrecacheWorkerThread` loads characters in the background, guarded by
  `EBT_Mutex*` (VERIFIED names and calls). Note the original
  `EBT_MutexInit` bug (initialises a stack copy).
