# DEF and other INI-like text files

All text definitions (DEF, CNS, CMD, CFG, AIR sections, FNT text parts,
storyboards) go through one engine-wide **text parser** (`txtparse.c`,
prefix `TP`): `TPReadFile` / `TPReadFilePtr` / `TPReadMFPtr` load a file
into line arrays, `TPGroupSeek` finds a `[Group]`, and `TPGetValue*` /
`TPScanf` read `key = value` pairs (VERIFIED: names and call sites
throughout).

## Lexical rules (VERIFIED from `TPReadFilePtr`, 0x0807b880)

- Lines are read with `fgets` into a **256-byte buffer**
  (`fgets(line, 0x100, file)`), so longer lines are split.
- `;` starts a comment. The line is cut at the first `;`.
- Trailing newline and trailing whitespace are removed (`TPisspace`), and
  so is leading whitespace.
- `TPCaseSensitive` (global, `.data` 0x08287a20) controls key matching. The
  CNS docs and observed behaviour treat names case-insensitively (STRONGLY
  INFERRED).
- The parser stores the file text in one block and builds index arrays of
  up to 0x100 lines and 0x40 groups initially (`local_138 = 0x100`,
  `local_13c = 0x40`), grown with `realloc` in steps of 0x100 (VERIFIED).
- Files may come from disk, from memory, or from inside a ZIP
  (`TPReadMFPtr` uses the `MF*` stream layer of `ebcommon.c`: `MFfopen`,
  `MFzopen`, `MFfgets`, ...) (VERIFIED).

## Character DEF (example: `chars/kfm/kfm.def`)

Groups and keys read by the player loader (`p-make.c`, VERIFIED from string
references):

| Group | Keys |
|---|---|
| `[Info]` | `name`, `displayname`, `versiondate` (MM,DD,YYYY), `mugenversion` (MM,DD,YYYY; checked: "Character is not designed to run on this version of M.U.G.E.N."), `author`, `pal.defaults` |
| `[Files]` | `cmd`, `cns`, `st`, `stcommon`, `sprite`, `anim`, `sound`, `pal1`..`pal12` (`ai` is also referenced) |
| `[Arcade]` | `intro.storyboard`, `ending.storyboard` (read by `charsel.c`) |

Character constants (`[Data]`, `[Size]`, `[Velocity]`, `[Movement]`) live in
the CNS file: see [cns.md](cns.md). Since 2002.04.14 a character may be a
**ZIP** whose name matches its DEF (`PlayerDefLoadZip`, minizip `unzOpen`;
updates.txt "experimental ZIP character support") (VERIFIED).

## mugen.cfg (`data/mugen.cfg`)

Read by `GameConfigRead` / `GameLoadOptions` (`system.c`) and rewritten
by `GameSaveOptions` (VERIFIED: the file is opened `O_WRONLY|O_TRUNC` at
startup when `FirstRun` changes). Groups: `[Options]`, `[Rules]`,
`[Config]`, `[Debug]`, `[Video Linux]`, `[Sound Linux]`, `[Misc]`,
`[Arcade]`, `[Input]`, `[P1 Keys]`, `[P2 Keys]`, `[P1 Joystick]`,
`[P2 Joystick]`.

Keys the engine reads (from `system.c` string references, VERIFIED). Ones
missing from the shipped file are in **bold**:

`Difficulty Life Time GameSpeed WavVolume MidiVolume Team.1VS2Life
Team.LoseOnKO motif GameType Default.Attack.LifeToPowerMul
Default.GetHit.LifeToPowerMul Super.TargetDefenceMul AfterImageMax
LayeredSpriteMax ExplodMax SysExplodMax HelperMax PlayerProjectileMax
FirstRun Debug AllowDebugMode AllowDebugKeys Speedup StartStage Width
Height Depth Stretch DoubleRes VRetrace FullScreen BlitMode Sound
StereoEffects PanningWidth ReverseStereo WavDevice WavChannels ModVoices
MidiDevice MasterWavVolume MP3Volume ModVolume CDAVolume PlayMIDI PlayMP3
PlayMOD PlayCDA CDADevice PlayerCache Precache BufferedRead UnloadSystem
PauseOnDefocus DrawShadows ForceFeedback` and, not present in the shipped
file, **`PauseBGMOnDefocus PlayerPalMax PSXDelay DebugInfo Expires`**
(VERIFIED by grepping `data/mugen.cfg`).

- Keys in `[P1 Keys]`/`[P2 Keys]` are **DOS set-1 scancodes** (e.g.
  `Jump = 200` = 0xC8 = extended Up). The engine translates Allegro key
  codes to these via `KBAllegRemapMap` (VERIFIED, `kbll-lib.c`).
- `expires = M,D,Y,checksum` (hex checksum) replaces the built-in expiry
  date if the checksum matches a value derived from the build date
  (VERIFIED, `GameConfigRead`; see runtime/startup.md).

## system.def (motif)

Read by `GameLoadSystem` / `GameLoadSystemDefs` (`system.c`), `charsel.c`
and the screens. Groups: `[Files]` (`spr`, `snd`, `logo.storyboard`,
`intro.storyboard`, `select`, `fight`, fonts), `[Music]`, `[Title Info]`,
`[Select Info]`, `[VS Screen]`, `[Demo Mode]`, `[Continue Screen]`,
`[Game Over Screen]`, `[Win Screen]`, `[Default Ending]`, `[End Credits]`,
`[Survival Results Screen]`, `[Option Info]` (VERIFIED). File lookup tries
the motif directory, then the game root, then `data/` (VERIFIED, strace:
`data/font/f-4x6.fnt` fails, then `./font/f-4x6.fnt`).

## select.def

`[Characters]` (one character per line, optional stage and `includestage`
settings), `[ExtraStages]`, `[Options]` (`arcade.maxmatches`,
`team.maxmatches`) (VERIFIED, `charsel.c` keys `Characters`,
`extrastages`, `arcade.maxmatches`, `team.maxmatches`). Nonexistent stages
are excluded automatically (updates.txt 14 Nov 2001).

## fight.def

Lifebars, powerbars, faces, names, time, combo, round announcements and
win icons. Groups `[Files]`, `[Lifebar]`, `[Simul Lifebar]`,
`[Turns Lifebar]`, `[Powerbar]`, `[Face]`, `[Simul Face]`, `[Turns Face]`,
`[Name]`, `[Simul Name]`, `[Turns Name]`, `[Time]`, `[Combo]`, `[Round]`,
`[WinIcon]`. Keys include `round.time`, `fight.snd`, `KO.time`, `ctrl.time`,
`over.waittime`, `match.wins`, `match.maxdrawgames` (VERIFIED, `init.c`).

## Storyboards (logo, intro, ending, credits)

`[SceneDef]`, `[Scene N]` with `fadein.time`, `fadeout.time`, `clearcolor`,
`end.time`, `layerall.pos`, `bgm`, `bgm.loop`, `bg.name`, `window`,
`startscene` (VERIFIED, `cutscene.c`). readme: "Storyboards lack text and
sound options".
