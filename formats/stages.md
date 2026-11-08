# Stages

Examples: `stages/kfm.def` (+ `kfm.sff`, 231,149 bytes, 7 images) and
`stages/stage0.def` (+ `stage0.sff`). Reference: `docs/bgs.html`,
`docs/tutorial/bg-tut.html`. Loader: `GameLoadStage` / `GameBGLoad`
(`match.c`, `init.c`) plus the background library `bg-lib.c`.

## Groups and keys (VERIFIED from string references)

| Group | Keys |
|---|---|
| `[Info]` | `name` |
| `[Camera]` | `startx`, `starty`, `boundleft`, `boundright`, `boundhigh`, `boundlow`, `verticalfollow`, `floortension`, `tension` |
| `[PlayerInfo]` | `p1startx/y/z`, `p1facing`, `p2startx/y/z`, `p2facing`, `leftbound`, `rightbound`, `topbound`, `botbound` |
| `[Scaling]` | `topz`, `botz`, `topscale`, `botscale` |
| `[Bound]` | `screenleft`, `screenright` |
| `[StageInfo]` | `zoffset`, `zoffsetlink`, `autoturn`, `resetbg` |
| `[Shadow]` | `intensity`, `color`, `yscale`, `fade.range` |
| `[Reflection]` | `intensity` |
| `[Music]` | `bgmusic`, `bgvolume` |
| `[BGdef]` | `spr`, `debugbg` |
| `[BG name]` | `type` (normal/parallax/anim), `spriteno`, `actionno`, `start`, `delta`, `trans`, `alpha`, `mask`, `tile`, `tilespacing`, `window`, `windowdelta`, `velocity`, `sin.x`, `sin.y`, `layerno`, `positionlink`, `width`, `xscale`, `yscalestart`, `yscaledelta`, `id` |
| `[BGCtrlDef]` / `[BGCtrl]` | `type`, `time`, `looptime`, `ctrlid`, `value`, `x`, `y` (`BGArrayReadCtrlTP`, `BGArrayCtrlUpdate`) |

kfm.def defines `[BG 0]`, `[BG Floor]`, `[BG Ceiling]`,
`[BG Wall reflection on floor]`, `[BG Wall]`, `[BG Pillar Bottom]`,
`[BG Pillar Top]`. Parallax floors are drawn by `BGParalSetup` and the
rotate/scale blitters (VERIFIED names). The default start stage comes from
`mugen.cfg` `StartStage = stages/stage0.def`.
