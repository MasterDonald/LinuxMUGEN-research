# Resource loading

## Observed order at start-up (VERIFIED, strace T3, default motif)

```
data/mugen.cfg                     read, then rewritten (FirstRun 1 -> 0)
/dev/dsp, ./patches.dat, ./midi/, /tmp/, /dev/sequencer   (sound probing)
_mugen__.tmp                       write test (then removed)
font/f-4x6.fnt, font/f-6x9.fnt     system fonts
data/system.def, data/system.sff, data/system.snd          motif
data/font/f-4x6.fnt (ENOENT) -> ./font/f-4x6.fnt           motif-relative lookup with fallback
data/font/f-6x9.fnt (ENOENT) -> ./font/f-6x9.fnt
data/font/jg.fnt    (ENOENT) -> ./font/jg.fnt
data/fight.def, data/fight.sff, data/fight.snd, data/fightfx.sff, data/fightfx.air, data/common.snd
data/font/num1.fnt  (ENOENT) -> ./font/num1.fnt
data/font/name1.fnt (ENOENT) -> ./font/name1.fnt
data/select.def
chars/kfm/kfm.def, chars/kfm/kfm.sff                       select-screen info / precache
stages/kfm.def                                             stage list check
```

## Lookup rules

- Files named in a motif are looked up relative to the motif directory
  first, then the game root (`FindFileDir`, `FindFileDirEx`,
  `ChangeFileDir`, `common.c`) (VERIFIED, strace pattern and names).
- Character files are relative to the character's directory, or inside
  `<name>.zip` (2002.04.14).
- `UnloadSystem = 1` frees motif data during matches (`GameUnloadSystem`);
  `BufferedRead` reads whole files into memory (`SndSetBufReadMode`,
  `ReadMode`/`BufferedReadMode` in `spr-read.c`, `snd-lib.c`).
- **Precache:** `PrecacheInit/Start/RequestChar/RequestTeam/Finish`; a
  worker thread loads the next characters while menus run; `Precache = 0`
  disables it (VERIFIED names and keys).
- **Player cache:** `PlayerCache` characters stay loaded between matches.
