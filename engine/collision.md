# Collision and hit detection

## Boxes (`clsn-lib.c`, VERIFIED)

- Clsn1 (attack) and Clsn2 (hurt) rectangles come from the AIR file
  (`ClsnParseLine`). They are stored as integer rectangles
  `x1,y1,x2,y2`, scaled on load by `clsnxscale/clsnyscale` when not 1.0.
- Detection: `ClsnMixDetectRect`, `ClsnMixDetectRectIndiv`,
  `ClsnArrayDetectRect`, `ClsnArrayDetectRectFlip` (rectangle overlap
  with horizontal flip per facing and per-player scale).

## Hits (`p-update.c`, `st-exprn.c`, VERIFIED names and call graph)

`PlayerCheckHit` -> `PlayerCheckP1HitP2` -> `Player1HitP2` (apply HitDef:
damage, guard, `PlayerGetHit`, `PlayerTakeDamage`, hit sparks as explods,
sounds) ; reversals: `PlayerCheckReversal`, `Player1ReverseP2`
(ReversalDef) ; projectiles: `PlayerCheckHitProj`, `PlayerCheckProjHit`,
`CheckProjHitProj` ; attribute filters: `PlayerCheckAttrHit` (`nothitby`,
`hitby`, `HitOverride`). HitDef fields come from `SCtrlParseHitDef` /
`SCtrlInitHitDef`.

## Notes from 2002.04.14 (updates.txt, VERIFIED)

- HitDef `ground.type`/`air.type` hi/lo are swapped when P2 is hit from
  behind (since 14 Nov 2001).
- `MoveContact`, `MoveGuarded`, `MoveHit` return the time since contact.
- Known issue: `HitOverride` always prevents being hit by attacks with a
  `p2stateno` (readme).
