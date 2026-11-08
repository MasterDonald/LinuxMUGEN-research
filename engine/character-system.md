# Character system

## Loading (VERIFIED: functions, strings, strace)

See diagram [../architecture/diagrams/character-load.mmd](../architecture/diagrams/character-load.mmd).

1. `select.def` lists characters. `FindCharacters` / `CharInfoInit` read
   each character's `[Info]` (name, displayname, portraits, palettes) for
   the select screen.
2. On selection (or precache), `PlayerDefLoad` loads `chars/<name>/<name>.def`,
   or `PlayerDefLoadZip` loads it from `<name>.zip` (minizip).
3. `PlayerDefLoadPtr` parses `[Info]`/`[Files]`, checks `mugenversion`,
   then loads constants (`PlayerCNSLoadTP`), states (`SctrlReadFileTP`,
   `SctrlAddFileTP` with `stcommon`), commands (`PlayerCMDLoadTP`),
   animations (`AnimRCReadFile`), sprites (`SpriteReadSFF*`), sounds
   (`SndReadFile`) and palettes (`Pal4Read3File`).
4. `PlayerNew` creates the run-time player; `PlayerReset` resets it for a
   round. Team modes create 2-4 players (`-p3`, `-p4` on the command line).
5. **Player cache:** up to `PlayerCache` loaded characters are kept in
   memory (`PlayerCacheChangePriority`); `Precache*` loads the next
   opponents in a worker thread (`PrecacheWorkerThread`).

## Run time

Per tick: input -> command detection -> state machine (special states and
current state) -> physics -> animation update (`AnimUpdate`) -> hit
detection -> effects. Helpers are additional players with parents
(`HelperMake`, `HelperDestroy`; `helper.c`); projectiles are separate
objects (`projctl.c`, `ProjArray*`).

## AI (`p-ai.c`)

- Normal AI: `AIForNormalDecisions`, `AIForNormalAttack`,
  `AIForNormalGuard`, `AIForNormalMove`, `AIForNormalRandom`,
  `AICheckForAttacks`, `AIBuildCounterAttackList`; difficulty from
  `Difficulty` and the arcade/team/survival `AIramp` settings.
- **Learning**: `AILearn*` functions record move outcomes
  (`PlayerAILearnMoveUpdate/End`, `AILearnClsnUpdate`) and can save and
  load `ElecbyteAIB` files (`AILearnDataSave/Load`, MUGEN version check).
  Learning behaviour: HYPOTHESIS from names; the algorithm is in the code.
