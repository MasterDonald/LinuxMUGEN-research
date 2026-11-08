# Subsystem analysis

For each subsystem: files, responsibilities, inputs and outputs, and
dependencies. Function lists per file: [module-index.md](module-index.md).
File-level call counts (computed from the reconstruction):
[../artifacts/file_callgraph.json](../artifacts/file_callgraph.json); the
diagram is in [diagrams/file-callgraph.mmd](diagrams/file-callgraph.mmd).

Most-called modules (fan-in, call sites): `arith.c` 1,055 (expression
evaluation), `txtparse.c` 964 (text parser), `spr-lib.c` 504, `ebcommon.c`
413, `common.c` 331, `array.c` 249. Most-calling modules (fan-out):
`st-exprn.c` 907, `st-ctrl.c` 721, `gameloop.c` 338, `p-make.c` 316,
`menus.c` 281 (VERIFIED, counted from the code).

| Subsystem | Files | Responsibilities | In / out | Depends on | Class |
|---|---|---|---|---|---|
| Startup and config | main.c, init.c, system.c, cmdline.c | parse the command line (`MugenCmdLine`), init Allegro, video, input, sound, timers (`GameInit`); read and write `mugen.cfg` (`GameConfigRead`, `GameSaveOptions`); load motif (`GameLoadSystem`), fight data (`GameLoadFightData`) | in: argv, mugen.cfg, system.def, fight.def; out: global block `g`, rewritten mugen.cfg | txtparse, vbuf, g-lib, snd-lib, time-lib, kbll, pad | VERIFIED |
| Menus and screens | menus.c, charsel.c, gameloop.c (continue, win, survival results), cutscene.c, display.c | title menu `ModeSelect` (info screen, expiry banner), `OptionsScreen`, `KeyConfigScreen`, training menu, `CharacterSelectScreen`, `VersusScreen`, storyboards (`PlayCutscene`, `Scene*`) | in: select.def, system.def, storyboards; out: chosen mode, teams, stage | font-lib, spr-lib, anim-lib, bg-lib, snd-lib, input | VERIFIED |
| Match control | main.c (`MainLoop`, `GamePlay`), match.c, gameloop.c, common.c | arcade/team/survival lists, rounds, KO/time-over, stage load (`GameLoadStage`), per-frame loop (`GameLoop`/`GameUpdate`), debug hot keys | in: teams, stage DEF; out: frames, results | everything below | VERIFIED |
| Players | p-make.c, p-update.c, p-input.c, p-info.c, helper.c, projctl.c | load DEF/CNS/CMD/AIR/SFF/SND (`PlayerDefLoad*`, also from ZIP); per-tick update (`PlayerUpdate`: physics, bounds, binding, hit checks `PlayerCheckHit`, `Player1HitP2`, `PlayerGetHit`); helpers and projectiles | in: character files, input; out: player state, sounds, explods | state machine, anim-lib, clsn-lib, spr-lib, snd-lib | VERIFIED |
| State machine and expressions | state.c, state-i.c, st-ctrl.c, st-trig.c, st-exprn.c, arith.c | parse states, controllers and triggers; compile expressions to postfix; evaluate every tick; apply controllers | in: CNS/CMD text; out: player changes | txtparse, array, players | VERIFIED |
| AI | p-ai.c | computer opponents (`AIForNormal*`, `AICheckForAttacks`), training dummy, **AI learning** (`AILearn*`, `AILearnDataLoad/Save`, `ElecbyteAIB` files with version check) | in: player state; out: synthetic input | players | VERIFIED (names, strings) / HYPOTHESIS (learning algorithm details) |
| Effects | explod.c, afterimg.c, pal.c (PalFX), sound.c | explods (`ExplodArray*`, sys-explods), afterimages, palette effects (`PalFXUpdate`, `PalGrpFlag` groups) | in: controllers; out: draw lists, palette changes | spr-lib, pal-lib | VERIFIED |
| Music | bgm.c, snd-lib.c | stage and motif music by extension: MIDI, MP3 (LibAmp), MOD (JGMOD), CD audio (libcda) (`BGMLoad`, `BGMCheckExtension`, `MP3*`, `MOD*`, `CDA*`) | in: file names; out: audio | Allegro, JGMOD, LibAmp, libcda | VERIFIED |
| Rendering | vbuf.c, spr16-lb.c, spr16add.c, spr16sub.c, spr-lib.c, anim-lib.c, bg-lib.c, g-lib.c, font-lib.c, pal-lib.c | 16-bit virtual buffer, 8->16-bit sprite blitters (normal, mirrored, scaled, rotated, additive, subtractive, shadows), BG layers and parallax, fonts | in: SFF, palettes; out: frame to Allegro `screen` | Allegro | VERIFIED |
| Input | kbll-lib.c, pad-lib.c, input-lb.c, inp-kbi.c, inp-menu.c, p-input.c, cmd-dtct.c | keyboard via Allegro low-level callback, remapped to DOS scancodes; joysticks; unified input (`UInp*`); command detection with buffers | in: devices; out: per-player button and direction bits, command matches | Allegro | VERIFIED |
| Resources and caching | spr-read.c, ebcommon.c (`MF*` streams), unzip.c, precache.c, txtparse.c | file access from disk, memory or ZIP; background precache thread; player cache (`PlayerCache`) | in: files; out: loaded resources | zlib, minizip, pthread | VERIFIED |
| Debug GUI | gui-lib.c, clipbrd.c | small window system for the debug display (Ctrl-D), clipboard text for `DisplayToClipboard`/`AppendToClipboard` controllers and warnings | in: debug state; out: overlay | vbuf, font-lib | VERIFIED |
| Timing | time-lib.c, display.c | 180 Hz Allegro timer (`TimerInit(180)`), 16.16 fixed-point frame sync (`TimerSetSyncFPS`), frame skipping (`FrameSkipUpdate`) | out: sync ticks | Allegro timer | VERIFIED |

## Palette FX and palette groups (detail)

`PalGrpFlag` is a 160-bit set (5 dwords) that selects palette groups (each
loaded sprite palette belongs to a group). `PalGrpMakeFlag(group)`,
`PalGrpOrFlag/XorFlag/AndFlagZero/FlagEqual/FlagIsNonZero` combine the
sets; `PalGrpSetAdd/SetMul/SetInvertAll/SetColorBal/SetClear` apply PalFX
parameters to every palette in a set; `PalGrpBuildFight` builds the groups
for a match. Evidence: assembly of these functions (5-word loops, `ret $4`
struct returns), see RESEARCH-METHODOLOGY.md #7 (VERIFIED structure;
"palette group" meaning from names: STRONGLY INFERRED).
