# CNS: constants and state machine

Examples: `chars/kfm/kfm.cns` (64,798 bytes), `data/common1.cns` (39,382
bytes). References: `docs/cns.html`, `docs/sctrls.html` (state
controllers), `docs/trigger.html`, `docs/exp.html` (expressions).

## Constants groups (`p-make.c`, VERIFIED keys)

- `[Data]`: `life`, `power`, `attack`, `defence`, `fall.defence_up`,
  `liedown.time`, `airjuggle`, `sparkno`, `guard.sparkno`, `KO.echo`,
  `volume`, `IntPersistIndex`, `FloatPersistIndex`
- `[Size]`: `xscale`, `yscale`, `ground.back/front`, `air.back/front`,
  `height`, `attack.dist`, `proj.attack.dist`, `proj.doscale`,
  `head.pos`, `mid.pos`, `shadowoffset`, `draw.offset`, `z.width`,
  `attack.z.width`
- `[Velocity]`: `walk.fwd/back/up/down`, `run.*`, `jump.neu/back/fwd/up/down`,
  `runjump.*`, `airjump.*`
- `[Movement]`: `airjump.num`, `airjump.height`, `yaccel`,
  `stand.friction`, `crouch.friction`

## States

`[Statedef N]` (`type`, `movetype`, `physics`, `anim`, `velset`, `ctrl`,
`poweradd`, `juggle`, `facep2`, `hitdefpersist`, `movehitpersist`,
`hitcountpersist`, `sprpriority`), followed by `[State N, label]`
controller blocks with `type`, `trigger1..N`/`triggerall` and parameters.

Pipeline (VERIFIED by function names and call graph):
`SctrlReadFileTP` / `SctrlAddFileTP` -> `SCtrlParseState` ->
`SCtrlParseElem` / `SCtrlParseElemType` (controller type and parameters)
-> `SCtrlParseTrigger` (triggers compiled to postfix by
`InfixToPostfix`/`InfToPostArray`, `arith.c`) -> at run time
`PlayerSCtrlUpdate` -> `SCtrlTrigTest`/`SCtrlTrigEval` ->
`PlayerSCtrlApplyElem` (one large switch over controller types).

### Controller and parameter vocabulary recognised by the parser

From `SCtrlParseElemType`'s string table (VERIFIED):

`abspan add add1 addalpha alpha angleadd angledraw anglemul angleset anim
appendtoclipboard assertspecial attackdist attackmulset bindtotarget
changeanim changeanim2 changestate channel clearclipboard ctrl ctrlset
defencemulset destroyself displaytoclipboard edge elem envcolor excludeID
facing fallenvshake forcefeedback gamemakeanim gravity hitadd
hitfalldamage hitfallset hitfallvel hitoverride hitvelset id keepone kill
lifeset makedust modifyexplod movecamera movehitreset movetype nothitby pan
params partnerstateno physics player playerpush pos pos2 posadd posfreeze
posset powerset projectile random range removeexplod reversal.attr
reversaldef scale screenbound selfstate slot sndpan spacing stateno
statetype statetypeset stopsnd sub superpause tagin tagout targetbind
targetdrop targetfacing targetlifeadd targetpoweradd targetstate
targetveladd targetvelset text time trans type under value value2
varrandom varrangeset velocity x y z`

### Trigger vocabulary (VERIFIED, string table of `st-trig.c`)

`abs acos airtype alive anim animelem animelemno animelemtime animexist
animtime asin atan authorname backedgebodydist backedgedist canrecover
ceil command const cos ctrl drawgame e enemy enemynear exp facing
fallcount fall.* floor frontedgebodydist frontedgedist fvar gametime
gethitvar groundtype helper hitcount hitdefattr hitfall hitover
hitpausetime hitshakeover hitshaketime hitvel id ifelse inguarddist
isbound ishelper ishometeam life lifemax ln log matchno matchover
movecontact moveguarded movehit movereversed movetype name numenemy
numexplod numhelper numpartner numproj numprojid numtarget p1name
p2bodydist p2dist p2life p2movetype p2name p2stateno p2statetype p3name
p4name palno parent parentdist partner pi playerid playeridexist pos
power powermax prevstateno projcanceltime projcontacttime
projguardedtime projhittime random root rootdist roundno roundsexisted
roundstate screenpos selfanimexist simul sin single stagevar standby
stateno statetime statetype sysfvar sysvar tan target teammode teamside
tickspersecond time timemod turns uniqhitcount var vel winperfect
xveladd yveladd`

New in 2002.04.14: `MoveReversed`; `MoveContact`/`MoveGuarded`/`MoveHit`
return time since the status change (updates.txt; VERIFIED present).

### Expressions

Infix expressions are compiled to a postfix array (`InfToPostArray`, 3,243
bytes) and evaluated on an **untyped 4-byte value stack**: int, float and
pointer share one cell type (VERIFIED: the reconstruction needed `vstack`
as `int[132]`; operator dispatch is a switch over small integer codes).
`EvalExpressionI` / `EvalExpressionF` return int and float results.
Constants are looked up through the `CnstName`/`CnstType` tables (67
entries, `.data` 0x08287ae0/0x08287c00), e.g. `data.power`.

### common1.cns

Shared states (stand, walk, jump, guard, get-hit, ...). Since 2002.04.14,
guard release in states 120, 130, 131, 132 is handled in common1.cns
instead of inside the executable (updates.txt "Changed from previous
version").
