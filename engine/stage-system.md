# Stage system

- Loading: `GameLoadStage` / `GameBGLoad` (`match.c`) read the stage DEF
  groups listed in [../formats/stages.md](../formats/stages.md) and the
  BG layers (`BGArrayReadTP`, `BGArrayReadCtrlTP`, `bg-lib.c`).
- BG types: normal (tiled, windowed, sin motion), parallax (`BGParalSetup`,
  drawn with the rotate/scale blitters), animated (`actionno`, using AIR
  actions in the stage DEF) (VERIFIED: keys and functions).
- BG controllers (`[BGCtrlDef]`): `BGArrayCtrlUpdate` changes visibility,
  velocity and position over time.
- Camera: `CameraMoveP`, `CameraMoveAbs` follow the players within
  `[Camera]` bounds, with tension and vertical follow (VERIFIED names and
  keys).
- Z/scale: `[Scaling]` topz/botz/topscale/botscale (sprite scaling by depth).
- Music: `[Music] bgmusic` (MIDI, MP3, MOD, or CD track) through `bgm.c`.
- Reload: Shift-F4 (`GameReloadStage`) (VERIFIED name, readme).
