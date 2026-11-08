# Engine structure map (unresolved question 6)

Field offsets of the engine's data structures, recovered from the
2002.04.14 binary through the reconstructed source. Written 2026-11-08.
Machine-readable: [../artifacts/structmap/structmap.tsv](../artifacts/structmap/structmap.tsv)
(struct, offset, name, type, source, evidence); the inputs and the
programs that produce it are in `artifacts/structmap/` and
`tools/structmap/`.

**Scope.** The original carries no type information for Elecbyte code: its
STABS debug data covers only the statically linked glibc objects (VERIFIED:
`objdump -G` lists no Elecbyte source file). Every name below is inferred
from what the code does with the field. Where a field has no name, its role
("read by trigger X", "written by controller Y") is given. The map is not
complete: the player record has 3,353 words, of which 95 offsets are named
here. It covers the fields that CNS code, the configuration files and the
character files can reach, which are the ones a port has to keep.

## Evidence classes used here

- **VERIFIED**: the field is the destination of a named key read
  (`TPGetValueInt(tp, "life", def + 0x10ac)`), a controller parameter slot
  (`InfixToPostfix(value, elem + 0x18)`), or a fact checked in the
  assembly or at run time (listed in `FACTS` in `build_structmap.py`).
- **STRONGLY INFERRED**: the field is read when a trigger is evaluated, or
  written when a controller runs. The role is certain; the exact meaning
  can include helper fields (redirection, team data) read in the same case.

## How the map was built

| Source | Program | What it gives |
|---|---|---|
| Text keys read into memory | `tools/structmap/mine_keys.py` | 395 destinations: key name -> base + byte offset (base resolved through `X = g;` / `X = g + n;` aliases) |
| CNS triggers | `tools/structmap/mine_triggers.py` | trigger name -> internal ID (`SCtrlParseTrigger`) -> player fields read in `case ID:` of `SCtrlTrigEval`; 9 IDs named by hand from the parser (`FIX` table) |
| State controllers | `tools/structmap/mine_ctrls.py` | controller name -> type ID, parameter -> element offset (`SCtrlParseElemType`); player fields written per type (`PlayerSCtrlApplyElem`) |
| Controller type IDs | assembly (`movl $ID,0x10(..)` after the name comparison) | `artifacts/structmap/ctrl_ids.tsv` |
| Allocation sizes | `ecalloc`/`calloc` calls with constant sizes | the inventory below |
| Merge | `tools/structmap/build_structmap.py`, `render_md.py` | `structmap.tsv` and the tables below |

## Structure inventory

| Structure | Size (bytes) | Allocated by | Linked from | Fields mapped |
|---|---|---|---|---|
| `g` (global game state) | 0x20b60 | `GameInit` | pointer at 0x08287a74 | 199 |
| Player record (players, helpers) | 0x3464 | `PlayerNew` 0x080af8f0 | table `g + 0x1cf64` (8 slots) | 95 |
| Character definition (`CharDef`) | 0x22e0 | `PlayerDefLoadPtr` / `PlayerDefLoadZip` | player +0x0 | 73 |
| Controller element (`SCtrlElem`) | 0x68 + per-type blocks (0x28-0x69c) | `SCtrlParseElemType` | state controller arrays | 187 slots over 89 types |
| HitDef / ReversalDef block | 0x514 | `SCtrlParseElemType` | controller element | via the HitDef keys (not tabulated) |
| Projectile definition | 0x118 | `SCtrlParseProjectile` | controller element | - |
| Runtime projectile | 0x2dc | `ProjArrayNew` (Array of 0x2dc) | player +0x21c -> {Array *, ..} | - |
| Explod | 0xe4 | `ExplodArrayNew` | - | - |
| Afterimage | 0x7c + n x 0x67c | `AftImgNew` / `AftImgInit` | - | - |
| Animation | 0x38 | `AnimNew` | player +0x13bc (current) | - |
| Generic array (`Array`) | 0x2c header | `ArrayNew` | everywhere | +0x0 flags, +0x4 element size, +0x8 count, +0xc capacity, +0x14 data, +0x18 index table |
| Select-screen cell | 0x2038 | `CharselReadConfig` | `cellHead` | - |
| Character info (select screen) | 0x702c | `CharInfoInit` / `FindCharacters` | `g[0x14b4]` | 6 |
| Select configuration (`slct`) | (static, 0x082a6be4) | - | - | 38 |
| Background element | 0x54 | `BGArrayNew` | - | 11 |
| Background controller | 0x54 | `BGArrayReadCtrlTP` | - | 14 |
| Font | 0x81c | `FontReadFilePtr_0_01` | - | 7 |
| Storyboard scene | 0x10e8 | `SiSceneReadTP` | - | 1 |
| Text-parser handle | 0x34 | `TPReadFilePtr` | - | - |
| Memory/zip file handle (`MF`) | 0x24 | `MFfopenFile` / `MFfopenMem` / `MFfopenZip` | - | - |
| Sprite array | 0x1c | `SpriteArrayNewSize` | - | - |
| Collision box array | n x 0x14 | `ClsnArrayNew` | - | - |
| Palette group | 0x180 + n x 0x18 | `PalGrpAdd` | - | - |
| Command list | n x 0x18 | `PlayerCMDLoadTP` | - | - |
| Compiled expression | 3 words: type/postfix pointer, type array, value or length | `InfixToPostfix` | controller elements, triggers | +0x0, +0x4, +0x8 (VERIFIED, `ConstExpI`) |

## Key facts about the main structures

- **Player record.** +0x0 points to the character definition. +0x4 is the
  player ID, +0x1c the helper flag (set when there is no definition).
  var(0..59) are at +0xe40, fvar(0..39) at +0xf30. Position x/y at
  +0x19c/+0x1a0, velocity x/y at +0x1b4/+0x1b8, facing at +0x190, life and
  lifemax at +0x160/+0x164. stateno +0xbf4, prevstateno +0xbf8, state time
  +0xdfc, statetype +0xe00, movetype +0xe04, ctrl +0xe0c. Current
  animation at +0x13bc, palno at +0x13c4, projectiles at +0x21c, standby at
  +0x3460 (the record's last word).
- **Character definition.** name at +0x0 (47 characters), displayname at
  +0x30. The [Data], [Size], [Velocity] and [Movement] constants start at
  +0x10ac (life) and run to about +0x11d0. The definition table lists every
  key with its offset.
- **Controller element.** +0x10 is the type ID. Parameters are compiled
  expressions in 12-byte slots from +0x18. The type IDs are in the last
  table. Several controllers share an ID with a flag: HitBy/NotHitBy 0x1e;
  PalFX/BGPalFX/AllPalFX 0xd8; Null and ForceFeedback 0 (ForceFeedback
  does nothing on Linux); VarSet/VarAdd 4/5, Display/AppendToClipboard
  0x136/0x137 (computed from the name).

## Field tables (generated)


#### Player

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x0 | chardef | CharDef * | VERIFIED | PlayerNew 0x080af8f0: *rec = param_1 |
| +0x4 | id (player ID); read by trigger id; read by trigger numexplod; read by trigger numexplod(ID) | int | VERIFIED | PlayerNew: rec[1] = g[0x749d]; trigger id reads +0x4; SCtrlTrigEval case 0x61; SCtrlTrigEval case 0x96; SCtrlTrigEval ca |
| +0xc | read by trigger ishometeam; read by trigger loseXX; read by trigger teamside; read by trigger winXX; read by trigger winperfect | int | STRONGLY INFERRED | SCtrlTrigEval case 0x7a; SCtrlTrigEval case 0x6e; SCtrlTrigEval case 0x78; SCtrlTrigEval case 0x6d; SCtrlTrigEval case 0 |
| +0x10 | read by trigger teammode | int | STRONGLY INFERRED | SCtrlTrigEval case 0x79 |
| +0x1c | ishelper; read by trigger ishelper; read by trigger ishelper(ID) | int | VERIFIED | PlayerNew: rec[7] = (chardef == NULL); trigger ishelper reads +0x1c; SCtrlTrigEval case 0xc9; SCtrlTrigEval case 0x14f |
| +0x160 | life; read by trigger life | int | VERIFIED | trigger life; SCtrlTrigEval case 0xf |
| +0x164 | lifemax; read by trigger lifemax | int | VERIFIED | trigger lifemax; SCtrlTrigEval case 0x10 |
| +0x188 | attack multiplier; written by controller attackmulset | float/int | STRONGLY INFERRED | earlier analysis (AttackMulSet); PlayerSCtrlApplyElem type 0x69 |
| +0x18c | written by controller defencemulset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x6a |
| +0x190 | facing; read by trigger backedgebodydist,backedgedist; read by trigger facing; read by trigger frontedgebodydist,frontedgedist; read by trigger hitvel; read by  | int | VERIFIED | trigger facing; VelSet multiplies x by it; SCtrlTrigEval case 0xc; SCtrlTrigEval case 0x63; SCtrlTrigEval case 0xb; SCtr |
| +0x19c | pos x; read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist; read by trigger pos; read by trigger screenpos; written b | float/int | VERIFIED | PosSet writes +0x19c/+0x1a0; trigger pos; SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb; SCtrlTrigEval case 0x4; SCtrlT |
| +0x1a0 | pos y; read by trigger p2bodydist; read by trigger p2dist; read by trigger parentdist; read by trigger pos; read by trigger rootdist; read by trigger screenpos; | float/int | VERIFIED | PosSet/PosAdd; SCtrlTrigEval case 0x9; SCtrlTrigEval case 0x8; SCtrlTrigEval case 0xcb; SCtrlTrigEval case 0x4; SCtrlTri |
| +0x1a4 | read by trigger p2bodydist; read by trigger p2dist; read by trigger parentdist; read by trigger pos; read by trigger rootdist | int | STRONGLY INFERRED | SCtrlTrigEval case 0x9; SCtrlTrigEval case 0x8; SCtrlTrigEval case 0xcb; SCtrlTrigEval case 0x4; SCtrlTrigEval case 0xcc |
| +0x1b4 | read by trigger vel; vel x; written by controller hitfallvel; written by controller hitvelset; written by controller veladd; written by controller velmul; writt | int/float | VERIFIED | SCtrlTrigEval case 0x6; VelSet/VelAdd/VelMul write +0x1b4/+0x1b8; trigger vel; PlayerSCtrlApplyElem type 0x67; PlayerSCt |
| +0x1b8 | read by trigger vel; vel y; written by controller gravity; written by controller hitfallvel; written by controller hitvelset; written by controller veladd; writ | int/float | VERIFIED | SCtrlTrigEval case 0x6; VelSet/VelAdd/VelMul; PlayerSCtrlApplyElem type 0x1b; PlayerSCtrlApplyElem type 0x67; PlayerSCtr |
| +0x1bc | read by trigger vel | int | STRONGLY INFERRED | SCtrlTrigEval case 0x6 |
| +0x1c0 | written by controller offset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1c |
| +0x1c4 | written by controller offset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1c |
| +0x1cc | written by controller sprpriority | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x33 |
| +0x1d4 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist | int | STRONGLY INFERRED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb |
| +0x1d8 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist | int | STRONGLY INFERRED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb |
| +0x1e0 | written by controller superpause | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0xd6 |
| +0x1e4 | written by controller screenbound | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x32 |
| +0x1e8 | written by controller screenbound | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x32 |
| +0x1ec | written by controller screenbound | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x32 |
| +0x1f0 | written by controller playerpush | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x51 |
| +0x1f4 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist; written by controller width | int | STRONGLY INFERRED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb; PlayerSCtrlApplyElem type 0x28 |
| +0x1f8 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist; written by controller width | int | STRONGLY INFERRED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb; PlayerSCtrlApplyElem type 0x28 |
| +0x1fc | written by controller width | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x28 |
| +0x200 | written by controller width | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x28 |
| +0x210 | read by trigger projcontactN; read by trigger projguardedN; read by trigger projhitN; read by trigger projhittime | int | STRONGLY INFERRED | SCtrlTrigEval case 0x40; SCtrlTrigEval case 0x3f; SCtrlTrigEval case 0x3e; SCtrlTrigEval case 0x151 |
| +0x214 | read by trigger projcanceltime; read by trigger projcontactN; read by trigger projcontacttime; read by trigger projguardedN; read by trigger projguardedtime; re | int | STRONGLY INFERRED | SCtrlTrigEval case 0x15b; SCtrlTrigEval case 0x40; SCtrlTrigEval case 0x153; SCtrlTrigEval case 0x3f; SCtrlTrigEval case |
| +0x218 | read by trigger projguardedN; read by trigger projhitN; read by trigger projhittime | int | STRONGLY INFERRED | SCtrlTrigEval case 0x3f; SCtrlTrigEval case 0x3e; SCtrlTrigEval case 0x151 |
| +0x21c | read by trigger numproj; read by trigger numprojid | int | STRONGLY INFERRED | SCtrlTrigEval case 0x3c; SCtrlTrigEval case 0x154 |
| +0x220 | read by trigger numtarget(ID) | int | STRONGLY INFERRED | SCtrlTrigEval case 0x156 |
| +0x964 | pointer into CharDef+0x11b4; written by controller selfstate | ptr/int | VERIFIED | PlayerNew: rec[0x259] = chardef + 0x11b4; PlayerSCtrlApplyElem type 0x2 |
| +0xbec | written by controller selfstate | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x2 |
| +0xbf0 | written by controller selfstate | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x2 |
| +0xbf4 | read by trigger stateno; stateno | int | VERIFIED | SCtrlTrigEval case 0x28; trigger stateno; state-loop error pushes 0xbf4(%ebx) |
| +0xbf8 | prevstateno; read by trigger prevstateno | int | VERIFIED | trigger prevstateno; SCtrlTrigEval case 0x29 |
| +0xdfc | read by trigger statetime; read by trigger timemod; time (state time) | int | VERIFIED | SCtrlTrigEval case 0x0; SCtrlTrigEval case 0x7; triggers time/statetime/timemod |
| +0xe00 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist; read by trigger statetype; statetype; written by controller stat | int | VERIFIED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb; SCtrlTrigEval case 0x2b; trigger statetype; PlayerSCtrlApplyElem type 0x |
| +0xe04 | movetype; read by trigger hitdefattr; read by trigger movetype; written by controller statetypeset | int | VERIFIED | trigger movetype; SCtrlTrigEval case 0x30; SCtrlTrigEval case 0x2d; PlayerSCtrlApplyElem type 0x6e |
| +0xe08 | written by controller statetypeset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x6e |
| +0xe0c | ctrl; read by trigger ctrl; written by controller changestate; written by controller ctrlset; written by controller selfstate | int | VERIFIED | trigger ctrl; CtrlSet writes it; SCtrlTrigEval case 0x2f; PlayerSCtrlApplyElem type 0x1; PlayerSCtrlApplyElem type 0x14; |
| +0xe18 | read by trigger hitpausetime | int | STRONGLY INFERRED | SCtrlTrigEval case 0x68 |
| +0xe20 | written by controller posfreeze | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x17 |
| +0xe24 | read by trigger alive | int | STRONGLY INFERRED | SCtrlTrigEval case 0x13 |
| +0xe30 | read by trigger movecontact; read by trigger moveguarded; read by trigger movehit; read by trigger movereversed; written by controller movehitreset | int | STRONGLY INFERRED | SCtrlTrigEval case 0x22; SCtrlTrigEval case 0x21; SCtrlTrigEval case 0x20; SCtrlTrigEval case 0x23; PlayerSCtrlApplyElem |
| +0xe34 | read by trigger movereversed | int | STRONGLY INFERRED | SCtrlTrigEval case 0x23 |
| +0xe40 | var(0..59) | int[60] | VERIFIED | EvalExpression := : rec[0x390 + i] (i < 0x3d checked) |
| +0xf30 | fvar(0..39) | float[40] | VERIFIED | EvalExpression: rec[0x3cc + i] (i <= 0x28) |
| +0xff8 | written by controller superpause | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0xd6 |
| +0xffc | written by controller hitby/nothitby | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1e |
| +0x1000 | written by controller hitby/nothitby | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1e |
| +0x1004 | written by controller hitby/nothitby | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1e |
| +0x1008 | written by controller hitby/nothitby | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x1e |
| +0x100c | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1010 | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1018 | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x101c | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1020 | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1024 | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1028 | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x102c | read by trigger gethitvar | int | STRONGLY INFERRED | SCtrlTrigEval case 0xb4 |
| +0x1034 | read by trigger hitshakeover | int | STRONGLY INFERRED | SCtrlTrigEval case 0x65 |
| +0x1038 | read by trigger hitover | int | STRONGLY INFERRED | SCtrlTrigEval case 0x66 |
| +0x1058 | read by trigger hitvel | int | STRONGLY INFERRED | SCtrlTrigEval case 0x67 |
| +0x1070 | read by trigger hitfall; written by controller hitfallset | int | STRONGLY INFERRED | SCtrlTrigEval case 0x64; PlayerSCtrlApplyElem type 0x64 |
| +0x1074 | written by controller hitfalldamage | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x66 |
| +0x1078 | written by controller hitfallset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x64 |
| +0x107c | written by controller hitfallset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x64 |
| +0x1080 | read by trigger canrecover | int | STRONGLY INFERRED | SCtrlTrigEval case 0x69 |
| +0x1084 | read by trigger canrecover | int | STRONGLY INFERRED | SCtrlTrigEval case 0x69 |
| +0x1088 | read by trigger canrecover | int | STRONGLY INFERRED | SCtrlTrigEval case 0x69 |
| +0x1094 | written by controller fallenvshake | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0xc9 |
| +0x1164 | read by trigger hitdefattr | int | STRONGLY INFERRED | SCtrlTrigEval case 0x30 |
| +0x12cc | written by controller attackdist | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x50 |
| +0x1348 | read by trigger backedgebodydist,backedgedist; read by trigger frontedgebodydist,frontedgedist | int | STRONGLY INFERRED | SCtrlTrigEval case 0xc; SCtrlTrigEval case 0xb |
| +0x134c | written by controller angledraw | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x3c |
| +0x1350 | written by controller angledraw | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x3c |
| +0x137c | written by controller angleadd; written by controller angledraw; written by controller anglemul; written by controller angleset | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x3e; PlayerSCtrlApplyElem type 0x3c; PlayerSCtrlApplyElem type 0x3f; PlayerSCtrlApplyElem typ |
| +0x1380 | written by controller angledraw | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x3c |
| +0x1388 | written by controller trans | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x41 |
| +0x138c | written by controller trans | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x41 |
| +0x1390 | written by controller trans | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x41 |
| +0x1394 | written by controller afterimage | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0xd2 |
| +0x139c | read by trigger hitcount | int | STRONGLY INFERRED | SCtrlTrigEval case 0x1e |
| +0x13a0 | read by trigger uniqhitcount | int | STRONGLY INFERRED | SCtrlTrigEval case 0x1f |
| +0x13bc | current animation; read by trigger anim; read by trigger animelemno; read by trigger animelemtime; read by trigger animtime | Anim */int | VERIFIED | triggers anim/animtime/animelemno use rec[0x4ef]; SCtrlTrigEval case 0x3; SCtrlTrigEval case 0x15c; SCtrlTrigEval case 0 |
| +0x13c0 | written by controller selfstate | int | STRONGLY INFERRED | PlayerSCtrlApplyElem type 0x2 |
| +0x13c4 | palno; read by trigger palno | int | VERIFIED | trigger palno; SCtrlTrigEval case 0x6b |
| +0x2618 | read by trigger ishelper(ID) | int | STRONGLY INFERRED | SCtrlTrigEval case 0x14f |
| +0x342c | read by trigger roundsexisted | int | STRONGLY INFERRED | SCtrlTrigEval case 0x75 |
| +0x3460 | read by trigger standby; standby; written by controller tagout | int | VERIFIED | SCtrlTrigEval case 0xcd; trigger standby reads +0x3460 (last word of the 0x3464 record); PlayerSCtrlApplyElem type 0x274 |

#### CharDef

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x0 | name; sprite; stcommon; walk.down; yscale | char[0x30]/char[]/float | VERIFIED | PlayerDefLoadPtr: GetQuotedString("name", def, 0x2f); PlayerDefLoadZip (key "sprite"); PlayerDefLoadZip (key "stcommon") |
| +0x30 | displayname | char[] | VERIFIED | PlayerDefLoadPtr: displayname (default = name) |
| +0x90 | versiondate[0] | int | VERIFIED | PlayerDefLoadZip (key "versiondate[0]") |
| +0x94 | versiondate[1] | int | VERIFIED | PlayerDefLoadZip (key "versiondate[1]") |
| +0x98 | versiondate[2] | int | VERIFIED | PlayerDefLoadZip (key "versiondate[2]") |
| +0x9c | mugenversion[0] | int | VERIFIED | PlayerDefLoadZip (key "mugenversion[0]") |
| +0xa0 | mugenversion[1] | int | VERIFIED | PlayerDefLoadZip (key "mugenversion[1]") |
| +0xa4 | mugenversion[2] | int | VERIFIED | PlayerDefLoadZip (key "mugenversion[2]") |
| +0x10ac | life | uint | VERIFIED | PlayerCNSLoadTP (key "life") |
| +0x10b0 | power | uint | VERIFIED | PlayerCNSLoadTP (key "power") |
| +0x10b4 | attack | uint | VERIFIED | PlayerCNSLoadTP (key "attack") |
| +0x10b8 | attack.z.width[0] | int | VERIFIED | PlayerCNSLoadTP (key "attack.z.width[0]") |
| +0x10bc | attack.z.width[1] | int | VERIFIED | PlayerCNSLoadTP (key "attack.z.width[1]") |
| +0x10c0 | airjuggle | uint | VERIFIED | PlayerCNSLoadTP (key "airjuggle") |
| +0x10c4 | attack.dist | uint | VERIFIED | PlayerCNSLoadTP (key "attack.dist") |
| +0x10c8 | proj.attack.dist | uint | VERIFIED | PlayerCNSLoadTP (key "proj.attack.dist") |
| +0x10cc | defence | uint | VERIFIED | PlayerCNSLoadTP (key "defence") |
| +0x10d0 | fall.defence_up | float | VERIFIED | PlayerCNSLoadTP (key "fall.defence_up") |
| +0x10d4 | liedown.time | uint | VERIFIED | PlayerCNSLoadTP (key "liedown.time") |
| +0x10d8 | xscale | float | VERIFIED | PlayerCNSLoadTP (key "xscale") |
| +0x10e0 | ground.back | uint | VERIFIED | PlayerCNSLoadTP (key "ground.back") |
| +0x10e4 | ground.front | uint | VERIFIED | PlayerCNSLoadTP (key "ground.front") |
| +0x10e8 | air.back | uint | VERIFIED | PlayerCNSLoadTP (key "air.back") |
| +0x10ec | air.front | uint | VERIFIED | PlayerCNSLoadTP (key "air.front") |
| +0x10f0 | z.width | uint | VERIFIED | PlayerCNSLoadTP (key "z.width") |
| +0x10f4 | height | uint | VERIFIED | PlayerCNSLoadTP (key "height") |
| +0x10f8 | proj.doscale | uint | VERIFIED | PlayerCNSLoadTP (key "proj.doscale") |
| +0x10fc | head.pos[0] | int | VERIFIED | PlayerCNSLoadTP (key "head.pos[0]") |
| +0x1100 | head.pos[1] | int | VERIFIED | PlayerCNSLoadTP (key "head.pos[1]") |
| +0x1104 | mid.pos[0] | int | VERIFIED | PlayerCNSLoadTP (key "mid.pos[0]") |
| +0x1108 | mid.pos[1] | int | VERIFIED | PlayerCNSLoadTP (key "mid.pos[1]") |
| +0x110c | shadowoffset | uint | VERIFIED | PlayerCNSLoadTP (key "shadowoffset") |
| +0x1110 | walk.fwd | float | VERIFIED | PlayerCNSLoadTP (key "walk.fwd") |
| +0x1114 | walk.back | float | VERIFIED | PlayerCNSLoadTP (key "walk.back") |
| +0x1118 | walk.up | float | VERIFIED | PlayerCNSLoadTP (key "walk.up") |
| +0x1120 | run.fwd[0] | float | VERIFIED | PlayerCNSLoadTP (key "run.fwd[0]") |
| +0x1124 | run.fwd[1] | float | VERIFIED | PlayerCNSLoadTP (key "run.fwd[1]") |
| +0x1128 | run.back[0] | float | VERIFIED | PlayerCNSLoadTP (key "run.back[0]") |
| +0x112c | run.back[1] | float | VERIFIED | PlayerCNSLoadTP (key "run.back[1]") |
| +0x1130 | run.down[0] | float | VERIFIED | PlayerCNSLoadTP (key "run.down[0]") |
| +0x1134 | run.down[1] | float | VERIFIED | PlayerCNSLoadTP (key "run.down[1]") |
| +0x1138 | run.up[0] | float | VERIFIED | PlayerCNSLoadTP (key "run.up[0]") |
| +0x113c | run.up[1] | float | VERIFIED | PlayerCNSLoadTP (key "run.up[1]") |
| +0x1140 | jump.neu[1] | float | VERIFIED | PlayerCNSLoadTP (key "jump.neu[1]") |
| +0x1144 | jump.neu[0] | float | VERIFIED | PlayerCNSLoadTP (key "jump.neu[0]") |
| +0x1148 | jump.fwd | float | VERIFIED | PlayerCNSLoadTP (key "jump.fwd") |
| +0x114c | jump.back | float | VERIFIED | PlayerCNSLoadTP (key "jump.back") |
| +0x1150 | jump.up | float | VERIFIED | PlayerCNSLoadTP (key "jump.up") |
| +0x1154 | jump.down | float | VERIFIED | PlayerCNSLoadTP (key "jump.down") |
| +0x1158 | runjump.fwd[1] | float | VERIFIED | PlayerCNSLoadTP (key "runjump.fwd[1]") |
| +0x115c | runjump.fwd[0] | float | VERIFIED | PlayerCNSLoadTP (key "runjump.fwd[0]") |
| +0x1160 | runjump.back | float | VERIFIED | PlayerCNSLoadTP (key "runjump.back") |
| +0x1164 | runjump.up | float | VERIFIED | PlayerCNSLoadTP (key "runjump.up") |
| +0x1168 | runjump.down | float | VERIFIED | PlayerCNSLoadTP (key "runjump.down") |
| +0x116c | airjump.num | uint | VERIFIED | PlayerCNSLoadTP (key "airjump.num") |
| +0x1170 | airjump.height | uint | VERIFIED | PlayerCNSLoadTP (key "airjump.height") |
| +0x1174 | airjump.neu[1] | float | VERIFIED | PlayerCNSLoadTP (key "airjump.neu[1]") |
| +0x1178 | airjump.neu[0] | float | VERIFIED | PlayerCNSLoadTP (key "airjump.neu[0]") |
| +0x117c | airjump.fwd | float | VERIFIED | PlayerCNSLoadTP (key "airjump.fwd") |
| +0x1180 | airjump.back | float | VERIFIED | PlayerCNSLoadTP (key "airjump.back") |
| +0x1184 | airjump.up | float | VERIFIED | PlayerCNSLoadTP (key "airjump.up") |
| +0x1188 | airjump.down | float | VERIFIED | PlayerCNSLoadTP (key "airjump.down") |
| +0x118c | yaccel | float | VERIFIED | PlayerCNSLoadTP (key "yaccel") |
| +0x1190 | stand.friction | float | VERIFIED | PlayerCNSLoadTP (key "stand.friction") |
| +0x1194 | crouch.friction | float | VERIFIED | PlayerCNSLoadTP (key "crouch.friction") |
| +0x1198 | sparkno | uint | VERIFIED | PlayerCNSLoadTP (key "sparkno") |
| +0x119c | guard.sparkno | uint | VERIFIED | PlayerCNSLoadTP (key "guard.sparkno") |
| +0x11a0 | ko.echo | uint | VERIFIED | PlayerCNSLoadTP (key "ko.echo") |
| +0x11a4 | draw.offset[0] | int | VERIFIED | PlayerCNSLoadTP (key "draw.offset[0]") |
| +0x11a8 | draw.offset[1] | int | VERIFIED | PlayerCNSLoadTP (key "draw.offset[1]") |
| +0x11ac | IntPersistIndex | uint | VERIFIED | PlayerCNSLoadTP (key "IntPersistIndex") |
| +0x11b0 | FloatPersistIndex | uint | VERIFIED | PlayerCNSLoadTP (key "FloatPersistIndex") |
| +0x11d0 | volume | uint | VERIFIED | PlayerCNSLoadTP (key "volume") |

#### g

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x4014 | fadein.time | int | VERIFIED | GameLoadSystem (key "fadein.time") |
| +0x4200 | startx | uint | VERIFIED | GameLoadStage (key "startx") |
| +0x4204 | starty | uint | VERIFIED | GameLoadStage (key "starty") |
| +0x4208 | boundleft | uint | VERIFIED | GameLoadStage (key "boundleft") |
| +0x420c | boundright | uint | VERIFIED | GameLoadStage (key "boundright") |
| +0x4210 | boundhigh | uint | VERIFIED | GameLoadStage (key "boundhigh") |
| +0x4214 | boundlow | uint | VERIFIED | GameLoadStage (key "boundlow") |
| +0x4218 | verticalfollow | float | VERIFIED | GameLoadStage (key "verticalfollow") |
| +0x421c | tension | uint | VERIFIED | GameLoadStage (key "tension") |
| +0x4220 | floortension | uint | VERIFIED | GameLoadStage (key "floortension") |
| +0x4224 | p1startx | uint | VERIFIED | GameLoadStage (key "p1startx") |
| +0x4228 | p2startx | uint | VERIFIED | GameLoadStage (key "p2startx") |
| +0x4234 | p1starty | uint | VERIFIED | GameLoadStage (key "p1starty") |
| +0x4238 | p2starty | uint | VERIFIED | GameLoadStage (key "p2starty") |
| +0x4244 | p1startz | uint | VERIFIED | GameLoadStage (key "p1startz") |
| +0x4248 | p2startz | uint | VERIFIED | GameLoadStage (key "p2startz") |
| +0x4254 | p1facing | uint | VERIFIED | GameLoadStage (key "p1facing") |
| +0x4258 | p2facing | uint | VERIFIED | GameLoadStage (key "p2facing") |
| +0x4264 | leftbound | uint | VERIFIED | GameLoadStage (key "leftbound") |
| +0x4268 | rightbound | uint | VERIFIED | GameLoadStage (key "rightbound") |
| +0x426c | topbound | uint | VERIFIED | GameLoadStage (key "topbound") |
| +0x4270 | botbound | uint | VERIFIED | GameLoadStage (key "botbound") |
| +0x4274 | autoturn | uint | VERIFIED | GameLoadStage (key "autoturn") |
| +0x4278 | topz | uint | VERIFIED | GameLoadStage (key "topz") |
| +0x427c | botz | uint | VERIFIED | GameLoadStage (key "botz") |
| +0x4280 | topscale | float | VERIFIED | GameLoadStage (key "topscale") |
| +0x4284 | botscale | float | VERIFIED | GameLoadStage (key "botscale") |
| +0x4288 | screenright | uint | VERIFIED | GameLoadStage (key "screenright") |
| +0x428c | screenleft | uint | VERIFIED | GameLoadStage (key "screenleft") |
| +0x4290 | intensity | uint | VERIFIED | GameLoadStage (key "intensity") |
| +0x4298 | yscale | float | VERIFIED | GameLoadStage (key "yscale") |
| +0x429c | fade.range[0] | int | VERIFIED | GameLoadStage (key "fade.range[0]") |
| +0x42a0 | fade.range[1] | int | VERIFIED | GameLoadStage (key "fade.range[1]") |
| +0x42a4 | intensity | uint | VERIFIED | GameLoadStage (key "intensity") |
| +0x42c0 | bgvolume | uint | VERIFIED | GameLoadStage (key "bgvolume") |
| +0x5380 | select | char[] | VERIFIED | GameLoadSystem (key "select") |
| +0x6380 | fadein.time | int | VERIFIED | CharselReadConfig (key "fadein.time") |
| +0x6d44 | logo.storyboard | char[] | VERIFIED | GameLoadSystem (key "logo.storyboard") |
| +0x7d44 | intro.storyboard | char[] | VERIFIED | GameLoadSystem (key "intro.storyboard") |
| +0x8d48 | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0x8d4c | storyboard | char[] | VERIFIED | GameLoadSystem (key "storyboard") |
| +0x9d4c | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0x9d50 | storyboard | char[] | VERIFIED | GameLoadSystem (key "storyboard") |
| +0xad50 | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0xad54 | wintext.* | SysExplod | VERIFIED | GameLoadSystem (key "wintext.*") |
| +0xadc0 | pose.time | uint | VERIFIED | GameLoadSystem (key "pose.time") |
| +0xadc4 | fadein.time | uint | VERIFIED | GameLoadSystem (key "fadein.time") |
| +0xadc8 | fadeout.time | uint | VERIFIED | GameLoadSystem (key "fadeout.time") |
| +0xadcc | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0xadd0 | winstext.* | SysExplod | VERIFIED | GameLoadSystem (key "winstext.*") |
| +0xae3c | show.time | uint | VERIFIED | GameLoadSystem (key "show.time") |
| +0xae40 | fadein.time | uint | VERIFIED | GameLoadSystem (key "fadein.time") |
| +0xae44 | fadeout.time | uint | VERIFIED | GameLoadSystem (key "fadeout.time") |
| +0xae48 | roundstowin | uint | VERIFIED | GameLoadSystem (key "roundstowin") |
| +0xae4c | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0xae50 | storyboard | char[] | VERIFIED | GameLoadSystem (key "storyboard") |
| +0xbe50 | enabled | uint | VERIFIED | GameLoadSystem (key "enabled") |
| +0xbe54 | storyboard | char[] | VERIFIED | GameLoadSystem (key "storyboard") |
| +0x10500 | zoffset | uint | VERIFIED | GameLoadStage (key "zoffset") |
| +0x10508 | zoffsetlink | uint | VERIFIED | GameLoadStage (key "zoffsetlink") |
| +0x138a4 | bg.* | SysExplod | VERIFIED | GameLoadFightData (key "bg.*") |
| +0x13910 | counter.* | SysExplod | VERIFIED | GameLoadFightData (key "counter.*") |
| +0x1397c | pos[0] | int | VERIFIED | GameLoadFightData (key "pos[0]") |
| +0x13980 | pos[1] | int | VERIFIED | GameLoadFightData (key "pos[1]") |
| +0x1398c | pos[1] | int | VERIFIED | GameLoadFightData (key "pos[1]") |
| +0x13990 | start.x | uint | VERIFIED | GameLoadFightData (key "start.x") |
| +0x13994 | displaytime | uint | VERIFIED | GameLoadFightData (key "displaytime") |
| +0x13998 | counter.font[0] | int | VERIFIED | GameLoadFightData (key "counter.font[0]") |
| +0x1399c | counter.font[1] | int | VERIFIED | GameLoadFightData (key "counter.font[1]") |
| +0x139a0 | counter.shake | uint | VERIFIED | GameLoadFightData (key "counter.shake") |
| +0x139a4 | text.font[0] | int | VERIFIED | GameLoadFightData (key "text.font[0]") |
| +0x139a8 | text.font[1] | int | VERIFIED | GameLoadFightData (key "text.font[1]") |
| +0x139ac | text.offset[0] | int | VERIFIED | GameLoadFightData (key "text.offset[0]") |
| +0x139b0 | text.offset[1] | int | VERIFIED | GameLoadFightData (key "text.offset[1]") |
| +0x139d4 | match.wins | uint | VERIFIED | GameLoadFightData (key "match.wins") |
| +0x139d8 | match.maxdrawgames | uint | VERIFIED | GameLoadFightData (key "match.maxdrawgames") |
| +0x139dc | start.waittime | uint | VERIFIED | GameLoadFightData (key "start.waittime") |
| +0x139e4 | pos[0] | int | VERIFIED | GameLoadFightData (key "pos[0]") |
| +0x139e8 | pos[1] | int | VERIFIED | GameLoadFightData (key "pos[1]") |
| +0x139ec | round.default.* | SysExplod | VERIFIED | GameLoadFightData (key "round.default.*") |
| +0x13e90 | round.time | uint | VERIFIED | GameLoadFightData (key "round.time") |
| +0x13e94 | round.sndtime | uint | VERIFIED | GameLoadFightData (key "round.sndtime") |
| +0x13ee8 | fight.* | SysExplod | VERIFIED | GameLoadFightData (key "fight.*") |
| +0x13f54 | fight.time | uint | VERIFIED | GameLoadFightData (key "fight.time") |
| +0x13f5c | fight.snd[0] | int | VERIFIED | GameLoadFightData (key "fight.snd[0]") |
| +0x13f60 | fight.snd[1] | int | VERIFIED | GameLoadFightData (key "fight.snd[1]") |
| +0x13f64 | KO.* | SysExplod | VERIFIED | GameLoadFightData (key "KO.*") |
| +0x140a8 | KO.time | uint | VERIFIED | GameLoadFightData (key "KO.time") |
| +0x140ac | KO.sndtime | uint | VERIFIED | GameLoadFightData (key "KO.sndtime") |
| +0x140b0 | KO.snd[0] | int | VERIFIED | GameLoadFightData (key "KO.snd[0]") |
| +0x140b4 | KO.snd[1] | int | VERIFIED | GameLoadFightData (key "KO.snd[1]") |
| +0x140b8 | DKO.snd[0] | int | VERIFIED | GameLoadFightData (key "DKO.snd[0]") |
| +0x140bc | DKO.snd[1] | int | VERIFIED | GameLoadFightData (key "DKO.snd[1]") |
| +0x140c0 | TO.snd[0] | int | VERIFIED | GameLoadFightData (key "TO.snd[0]") |
| +0x140c4 | TO.snd[1] | int | VERIFIED | GameLoadFightData (key "TO.snd[1]") |
| +0x140c8 | win.* | SysExplod | VERIFIED | GameLoadFightData (key "win.*") |
| +0x141a0 | draw.* | SysExplod | VERIFIED | GameLoadFightData (key "draw.*") |
| +0x1420c | win.snd[0] | int | VERIFIED | GameLoadFightData (key "win.snd[0]") |
| +0x14210 | win.snd[1] | int | VERIFIED | GameLoadFightData (key "win.snd[1]") |
| +0x14214 | lose.snd[0] | int | VERIFIED | GameLoadFightData (key "lose.snd[0]") |
| +0x14218 | lose.snd[1] | int | VERIFIED | GameLoadFightData (key "lose.snd[1]") |
| +0x1421c | draw.snd[0] | int | VERIFIED | GameLoadFightData (key "draw.snd[0]") |
| +0x14220 | draw.snd[1] | int | VERIFIED | GameLoadFightData (key "draw.snd[1]") |
| +0x14224 | win.time | uint | VERIFIED | GameLoadFightData (key "win.time") |
| +0x14228 | ctrl.time | uint | VERIFIED | GameLoadFightData (key "ctrl.time") |
| +0x1422c | slow.time | uint | VERIFIED | GameLoadFightData (key "slow.time") |
| +0x14230 | over.waittime | uint | VERIFIED | GameLoadFightData (key "over.waittime") |
| +0x14234 | over.hittime | uint | VERIFIED | GameLoadFightData (key "over.hittime") |
| +0x14238 | over.wintime | uint | VERIFIED | GameLoadFightData (key "over.wintime") |
| +0x1423c | over.time | uint | VERIFIED | GameLoadFightData (key "over.time") |
| +0x14ad0 | useiconupto | uint | VERIFIED | GameLoadFightData (key "useiconupto") |
| +0x1bbd0 | wavvolume | uint | VERIFIED | GameConfigRead (key "wavvolume") |
| +0x1bbd4 | masterwavvolume | uint | VERIFIED | GameConfigRead (key "masterwavvolume") |
| +0x1bbd8 | cdavolume | uint | VERIFIED | GameConfigRead (key "cdavolume") |
| +0x1bbdc | midivolume | uint | VERIFIED | GameConfigRead (key "midivolume") |
| +0x1bbe0 | mp3volume | uint | VERIFIED | GameConfigRead (key "mp3volume") |
| +0x1bbe4 | modvolume | uint | VERIFIED | GameConfigRead (key "modvolume") |
| +0x1cc78 | default.attack.lifetopowermul | float | VERIFIED | GameConfigRead (key "default.attack.lifetopowermul") |
| +0x1cc7c | default.gethit.lifetopowermul | float | VERIFIED | GameConfigRead (key "default.gethit.lifetopowermul") |
| +0x1cc80 | super.targetdefencemul | float | VERIFIED | GameConfigRead (key "super.targetdefencemul") |
| +0x1ce24 | p1.usekeyboard | uint | VERIFIED | GameConfigRead (key "p1.usekeyboard") |
| +0x1ce28 | p2.usekeyboard | uint | VERIFIED | GameConfigRead (key "p2.usekeyboard") |
| +0x1ce34 | p1.joystick.type | uint | VERIFIED | GameConfigRead (key "p1.joystick.type") |
| +0x1ce38 | p2.joystick.type | uint | VERIFIED | GameConfigRead (key "p2.joystick.type") |
| +0x1ce3c | forcefeedback | uint | VERIFIED | GameConfigRead (key "forcefeedback") |
| +0x1ce40 | psxdelay | uint | VERIFIED | GameConfigRead (key "psxdelay") |
| +0x1d3a4 | intro.waitcycles | uint | VERIFIED | GameLoadSystem (key "intro.waitcycles") |
| +0x1d3a8 | title.waittime | uint | VERIFIED | GameLoadSystem (key "title.waittime") |
| +0x1d3ac | select.enabled | uint | VERIFIED | GameLoadSystem (key "select.enabled") |
| +0x1d3b0 | vsscreen.enabled | uint | VERIFIED | GameLoadSystem (key "vsscreen.enabled") |
| +0x1d3b4 | fight.endtime | uint | VERIFIED | GameLoadSystem (key "fight.endtime") |
| +0x1d3b8 | fight.playbgm | uint | VERIFIED | GameLoadSystem (key "fight.playbgm") |
| +0x1d3bc | fight.bars.display | uint | VERIFIED | GameLoadSystem (key "fight.bars.display") |
| +0x1d3c0 | debuginfo | uint | VERIFIED | GameLoadSystem (key "debuginfo") |
| +0x1d54c | width | uint | VERIFIED | GameConfigRead (key "width") |
| +0x1d550 | height | uint | VERIFIED | GameConfigRead (key "height") |
| +0x1d554 | depth | uint | VERIFIED | GameConfigRead (key "depth") |
| +0x1d564 | doubleres | uint | VERIFIED | GameConfigRead (key "doubleres") |
| +0x1d568 | vretrace | uint | VERIFIED | GameConfigRead (key "vretrace") |
| +0x1d574 | wavchannels | uint | VERIFIED | GameConfigRead (key "wavchannels") |
| +0x1d578 | modvoices | uint | VERIFIED | GameConfigRead (key "modvoices") |
| +0x1d580 | playmp3 | uint | VERIFIED | GameConfigRead (key "playmp3") |
| +0x1d584 | playmidi | uint | VERIFIED | GameConfigRead (key "playmidi") |
| +0x1d588 | playmod | uint | VERIFIED | GameConfigRead (key "playmod") |
| +0x1d58c | playcda | uint | VERIFIED | GameConfigRead (key "playcda") |
| +0x1d5b0 | stereoeffects | uint | VERIFIED | GameConfigRead (key "stereoeffects") |
| +0x1d5b4 | panningwidth | uint | VERIFIED | GameConfigRead (key "panningwidth") |
| +0x1d5b8 | pausebgmondefocus | uint | VERIFIED | GameConfigRead (key "pausebgmondefocus") |
| +0x1d5c0 | drawshadows | uint | VERIFIED | GameConfigRead (key "drawshadows") |
| +0x1d5c4 | afterimagemax | uint | VERIFIED | GameConfigRead (key "afterimagemax") |
| +0x1d5c8 | layeredspritemax | uint | VERIFIED | GameConfigRead (key "layeredspritemax") |
| +0x1d5cc | explodmax | uint | VERIFIED | GameConfigRead (key "explodmax") |
| +0x1d5d0 | sysexplodmax | uint | VERIFIED | GameConfigRead (key "sysexplodmax") |
| +0x1d5d4 | helpermax | uint | VERIFIED | GameConfigRead (key "helpermax") |
| +0x1d5d8 | playerprojectilemax | uint | VERIFIED | GameConfigRead (key "playerprojectilemax") |
| +0x1d5dc | playerpalmax | uint | VERIFIED | GameConfigRead (key "playerpalmax") |
| +0x1d5e0 | firstrun | uint | VERIFIED | GameConfigRead (key "firstrun") |
| +0x1d5e8 | precache | uint | VERIFIED | GameConfigRead (key "precache") |
| +0x1d5f0 | unloadsystem | uint | VERIFIED | GameConfigRead (key "unloadsystem") |
| +0x1d5f4 | pauseondefocus | uint | VERIFIED | GameConfigRead (key "pauseondefocus") |
| +0x1d5f8 | ai.randomcolor | uint | VERIFIED | GameConfigRead (key "ai.randomcolor") |
| +0x1e678 | Difficulty | uint | VERIFIED | GameLoadOptions (key "Difficulty") |
| +0x1e67c | Life | uint | VERIFIED | GameLoadOptions (key "Life") |
| +0x1e680 | Time | uint | VERIFIED | GameLoadOptions (key "Time") |
| +0x1e684 | GameSpeed | uint | VERIFIED | GameLoadOptions (key "GameSpeed") |
| +0x1e688 | WavVolume | uint | VERIFIED | GameLoadOptions (key "WavVolume") |
| +0x1e68c | MidiVolume | uint | VERIFIED | GameLoadOptions (key "MidiVolume") |
| +0x1e6ac | p1.joystick.type | uint | VERIFIED | GameLoadOptions (key "p1.joystick.type") |
| +0x1e6c0 | p2.joystick.type | uint | VERIFIED | GameLoadOptions (key "p2.joystick.type") |
| +0x1e6d0 | Team.1VS2Life | uint | VERIFIED | GameLoadOptions (key "Team.1VS2Life") |
| +0x1e6d4 | Team.LoseOnKO | uint | VERIFIED | GameLoadOptions (key "Team.LoseOnKO") |
| +0x1e6e0 | motif | char[] | VERIFIED | GameLoadOptions (key "motif") |
| +0x20734 | debug | uint | VERIFIED | GameConfigRead (key "debug") |
| +0x20738 | allowdebugmode | uint | VERIFIED | GameConfigRead (key "allowdebugmode") |
| +0x2073c | allowdebugkeys | uint | VERIFIED | GameConfigRead (key "allowdebugkeys") |
| +0x20b48 | speedup | uint | VERIFIED | GameConfigRead (key "speedup") |
| +0x2477c | menu.pos[0] | int | VERIFIED | GameLoadSystem (key "menu.pos[0]") |
| +0x24780 | menu.pos[1] | int | VERIFIED | GameLoadSystem (key "menu.pos[1]") |
| +0x24784 | menu.item.font[0] | int | VERIFIED | GameLoadSystem (key "menu.item.font[0]") |
| +0x24788 | menu.item.font[2] | int | VERIFIED | GameLoadSystem (key "menu.item.font[2]") |
| +0x2478c | menu.item.font[1] | int | VERIFIED | GameLoadSystem (key "menu.item.font[1]") |
| +0x24790 | menu.item.active.font[0] | int | VERIFIED | GameLoadSystem (key "menu.item.active.font[0]") |
| +0x24798 | menu.item.active.font[1] | int | VERIFIED | GameLoadSystem (key "menu.item.active.font[1]") |
| +0x2479c | menu.item.spacing[0] | int | VERIFIED | GameLoadSystem (key "menu.item.spacing[0]") |
| +0x247a0 | menu.item.spacing[1] | int | VERIFIED | GameLoadSystem (key "menu.item.spacing[1]") |
| +0x24904 | menu.window.margins.y[0] | int | VERIFIED | GameLoadSystem (key "menu.window.margins.y[0]") |
| +0x24908 | menu.window.margins.y[1] | int | VERIFIED | GameLoadSystem (key "menu.window.margins.y[1]") |
| +0x2490c | menu.window.visibleitems | uint | VERIFIED | GameLoadSystem (key "menu.window.visibleitems") |
| +0x24910 | menu.boxcursor.visible | uint | VERIFIED | GameLoadSystem (key "menu.boxcursor.visible") |
| +0x24914 | menu.boxcursor.coords[0] | int | VERIFIED | GameLoadSystem (key "menu.boxcursor.coords[0]") |
| +0x24918 | menu.boxcursor.coords[1] | int | VERIFIED | GameLoadSystem (key "menu.boxcursor.coords[1]") |
| +0x2491c | menu.boxcursor.coords[2] | int | VERIFIED | GameLoadSystem (key "menu.boxcursor.coords[2]") |
| +0x24920 | menu.boxcursor.coords[3] | int | VERIFIED | GameLoadSystem (key "menu.boxcursor.coords[3]") |
| +0x2d5a0 | fadein.time | uint | VERIFIED | GameLoadSystem (key "fadein.time") |
| +0x2d5a4 | fadeout.time | uint | VERIFIED | GameLoadSystem (key "fadeout.time") |
| +0x3c314 | sound | uint | VERIFIED | GameConfigRead (key "sound") |
| +0x3dca8 | stretch | uint | VERIFIED | GameConfigRead (key "stretch") |
| +0x3dd04 | gamespeed | uint | VERIFIED | GameConfigRead (key "gamespeed") |
| +0x3dd2c | playercache | uint | VERIFIED | GameConfigRead (key "playercache") |

#### Slct

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x1004 | fadeout.time | uint | VERIFIED | CharselReadConfig (key "fadeout.time") |
| +0x1008 | pos[0] | int | VERIFIED | CharselReadConfig (key "pos[0]") |
| +0x100c | pos[1] | int | VERIFIED | CharselReadConfig (key "pos[1]") |
| +0x1014 | columns | uint | VERIFIED | CharselReadConfig (key "columns") |
| +0x1018 | cell.spacing | uint | VERIFIED | CharselReadConfig (key "cell.spacing") |
| +0x101c | cell.size[0] | int | VERIFIED | CharselReadConfig (key "cell.size[0]") |
| +0x1020 | cell.size[1] | int | VERIFIED | CharselReadConfig (key "cell.size[1]") |
| +0x1024 | wrapping | uint | VERIFIED | CharselReadConfig (key "wrapping") |
| +0x1028 | showemptyboxes | uint | VERIFIED | CharselReadConfig (key "showemptyboxes") |
| +0x102c | moveoveremptyboxes | uint | VERIFIED | CharselReadConfig (key "moveoveremptyboxes") |
| +0x1030 | portrait.scale[0] | float | VERIFIED | CharselReadConfig (key "portrait.scale[0]") |
| +0x1034 | portrait.scale[1] | float | VERIFIED | CharselReadConfig (key "portrait.scale[1]") |
| +0x1038 | portrait.offset[0] | int | VERIFIED | CharselReadConfig (key "portrait.offset[0]") |
| +0x103c | portrait.offset[1] | int | VERIFIED | CharselReadConfig (key "portrait.offset[1]") |
| +0x1040 | p1.cursor.startcell[0] | int | VERIFIED | CharselReadConfig (key "p1.cursor.startcell[0]") |
| +0x1044 | p2.cursor.startcell[0] | int | VERIFIED | CharselReadConfig (key "p2.cursor.startcell[0]") |
| +0x1048 | p1.cursor.startcell[1] | int | VERIFIED | CharselReadConfig (key "p1.cursor.startcell[1]") |
| +0x104c | p2.cursor.startcell[1] | int | VERIFIED | CharselReadConfig (key "p2.cursor.startcell[1]") |
| +0x1090 | p2.cursor.blink | uint | VERIFIED | CharselReadConfig (key "p2.cursor.blink") |
| +0x10c4 | random.move.snd.cancel | uint | VERIFIED | CharselReadConfig (key "random.move.snd.cancel") |
| +0x10e0 | title.offset[0] | int | VERIFIED | CharselReadConfig (key "title.offset[0]") |
| +0x10e4 | title.offset[1] | int | VERIFIED | CharselReadConfig (key "title.offset[1]") |
| +0x10e8 | title.font[0] | int | VERIFIED | CharselReadConfig (key "title.font[0]") |
| +0x10ec | title.font[1] | int | VERIFIED | CharselReadConfig (key "title.font[1]") |
| +0x10f0 | title.font[2] | int | VERIFIED | CharselReadConfig (key "title.font[2]") |
| +0x10f4 | cell.bg.* | int | VERIFIED | CharselReadConfig (key "cell.bg.*") |
| +0x1160 | cell.random.* | int | VERIFIED | CharselReadConfig (key "cell.random.*") |
| +0x11cc | cell.random.switchtime | uint | VERIFIED | CharselReadConfig (key "cell.random.switchtime") |
| +0x1380 | stage.pos[0] | int | VERIFIED | CharselReadConfig (key "stage.pos[0]") |
| +0x1384 | stage.pos[1] | int | VERIFIED | CharselReadConfig (key "stage.pos[1]") |
| +0x1388 | stage.active.font[0] | int | VERIFIED | CharselReadConfig (key "stage.active.font[0]") |
| +0x138c | stage.active2.font[0] | int | VERIFIED | CharselReadConfig (key "stage.active2.font[0]") |
| +0x1390 | stage.done.font[0] | int | VERIFIED | CharselReadConfig (key "stage.done.font[0]") |
| +0x1394 | stage.active.font[1] | int | VERIFIED | CharselReadConfig (key "stage.active.font[1]") |
| +0x1398 | stage.active2.font[1] | int | VERIFIED | CharselReadConfig (key "stage.active2.font[1]") |
| +0x139c | stage.done.font[1] | int | VERIFIED | CharselReadConfig (key "stage.done.font[1]") |
| +0x13a0 | stage.active.font[2] | int | VERIFIED | CharselReadConfig (key "stage.active.font[2]") |
| +0x13f4 | teammenu.move.wrapping | uint | VERIFIED | CharselReadConfig (key "teammenu.move.wrapping") |

#### CharInfo

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x5014 | pal.defaults[0] | int | VERIFIED | FindCharacters (key "pal.defaults[0]") |
| +0x5018 | pal.defaults[1] | int | VERIFIED | FindCharacters (key "pal.defaults[1]") |
| +0x501c | pal.defaults[2] | int | VERIFIED | FindCharacters (key "pal.defaults[2]") |
| +0x5020 | pal.defaults[3] | int | VERIFIED | FindCharacters (key "pal.defaults[3]") |
| +0x5028 | intro.storyboard | char[] | VERIFIED | FindCharacters (key "intro.storyboard") |
| +0x6027 | ending.storyboard | char[] | VERIFIED | FindCharacters (key "ending.storyboard") |

#### KeyConfig

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x4 | Jump | uint | VERIFIED | PlayerLoadKeys (key "Jump") |
| +0x8 | Right | uint | VERIFIED | PlayerLoadKeys (key "Right") |
| +0xc | Crouch | uint | VERIFIED | PlayerLoadKeys (key "Crouch") |
| +0x10 | Left | uint | VERIFIED | PlayerLoadKeys (key "Left") |
| +0x14 | A | uint | VERIFIED | PlayerLoadKeys (key "A") |
| +0x18 | B | uint | VERIFIED | PlayerLoadKeys (key "B") |
| +0x1c | C | uint | VERIFIED | PlayerLoadKeys (key "C") |
| +0x20 | X | uint | VERIFIED | PlayerLoadKeys (key "X") |
| +0x24 | Y | uint | VERIFIED | PlayerLoadKeys (key "Y") |
| +0x28 | Z | uint | VERIFIED | PlayerLoadKeys (key "Z") |
| +0x2c | Start | uint | VERIFIED | PlayerLoadKeys (key "Start") |

#### BGElem

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x34 | tilespacing[0] | int | VERIFIED | BGArrayReadTP (key "tilespacing[0]") |
| +0x38 | tilespacing[1] | int | VERIFIED | BGArrayReadTP (key "tilespacing[1]") |
| +0x50 | window[0] | int | VERIFIED | BGArrayReadTP (key "window[0]") |
| +0x58 | window[1] | int | VERIFIED | BGArrayReadTP (key "window[1]") |
| +0x60 | windowdelta[0] | float | VERIFIED | BGArrayReadTP (key "windowdelta[0]") |
| +0x64 | windowdelta[1] | float | VERIFIED | BGArrayReadTP (key "windowdelta[1]") |
| +0xd4 | sin.x[0] | float | VERIFIED | BGArrayReadTP (key "sin.x[0]") |
| +0xd8 | sin.y[0] | float | VERIFIED | BGArrayReadTP (key "sin.y[0]") |
| +0xdc | sin.x[1] | float | VERIFIED | BGArrayReadTP (key "sin.x[1]") |
| +0xe0 | sin.y[1] | float | VERIFIED | BGArrayReadTP (key "sin.y[1]") |
| +0xe4 | sin.x[2] | float | VERIFIED | BGArrayReadTP (key "sin.x[2]") |

#### BGCtrl

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x0 | ctrlid[0] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[0]") |
| +0x4 | ctrlid[1] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[1]") |
| +0x8 | ctrlid[2] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[2]") |
| +0xc | ctrlid[3] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[3]") |
| +0x10 | ctrlid[4] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[4]") |
| +0x14 | ctrlid[5] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[5]") |
| +0x18 | ctrlid[6] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[6]") |
| +0x1c | ctrlid[7] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[7]") |
| +0x20 | ctrlid[8] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[8]") |
| +0x24 | ctrlid[9] | int | VERIFIED | BGArrayReadCtrlTP (key "ctrlid[9]") |
| +0x34 | time[0] | int | VERIFIED | BGArrayReadCtrlTP (key "time[0]") |
| +0x38 | time[1] | int | VERIFIED | BGArrayReadCtrlTP (key "time[1]") |
| +0x44 | value[0]; x | float | VERIFIED | BGArrayReadCtrlTP (key "value[0]"); BGArrayReadCtrlTP (key "x") |
| +0x48 | value[1] | float | VERIFIED | BGArrayReadCtrlTP (key "value[1]") |

#### Font

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x0 | offset[0] | int | VERIFIED | FontReadFilePtr_0_01 (key "offset[0]") |
| +0x4 | offset[1] | int | VERIFIED | FontReadFilePtr_0_01 (key "offset[1]") |
| +0x8 | size[0] | int | VERIFIED | FontReadFilePtr_0_01 (key "size[0]") |
| +0xc | size[1] | int | VERIFIED | FontReadFilePtr_0_01 (key "size[1]") |
| +0x14 | spacing[0] | int | VERIFIED | FontReadFilePtr_0_01 (key "spacing[0]") |
| +0x18 | spacing[1] | int | VERIFIED | FontReadFilePtr_0_01 (key "spacing[1]") |
| +0x1c | colors | uint | VERIFIED | FontReadFilePtr_0_01 (key "colors") |

#### Scene

| Offset | Field (name or role) | Type | Evidence | Source |
|---|---|---|---|---|
| +0x10e4 | startscene | uint | VERIFIED | SiSceneReadTP (key "startscene") |

#### Controller elements (SCtrlElem)

Common layout: +0x10 type ID; expression slots of 12 bytes from +0x18 (+0x18, +0x24, +0x30, +0x3c, +0x48, +0x54, ...). Per controller:

| Controller | Type ID | Parameter -> element offset(s) |
|---|---|---|
| afterimage | |  |
| afterimagetime | |  |
| allpalfx | |  |
| angleadd | |  |
| angledraw | | (default) +0x48 (f 0x3f800000),+0x54 (f 0x3f800000); scale +0x48,+0x54 |
| angleset | |  |
| assertspecial | | (default) +0x18 (i local_128),+0x24 (i -1),+0x30 (i -1),+0x3c (i local_124),+0x48 (i local_124) |
| attackdist | |  |
| attackmulset | |  |
| bgpalfx | |  |
| bindtoparent | | (default) +0x18 (i 1); pos +0x3c,+0x48,+0x54 |
| bindtoroot | | (default) +0x18 (i 1); params +0x18,+0x24,+0x30,+0x3c,+0x48; pos +0x54 |
| bindtotarget | | (default) +0x18 (i 1),+0x24 (i 0),+0x30 (i -1),+0x54 (f 0); pos +0x3c,+0x48 |
| changeanim | | value +0x18 |
| changeanim2 | | value +0x18 |
| clearclipboard | |  |
| ctrlset | |  |
| defencemulset | |  |
| destroyself | |  |
| envcolor | | (default) +0x24 (i 1),+0x3c (i 0xff),+0x48 (i 0xff),+0x54 (i 0xff) |
| envshake | |  |
| explod | |  |
| explodbindtime | | (default) +0x18 (i -1) |
| fallenvshake | |  |
| ff | |  |
| forcefeedback | |  |
| fv | | (default) +0x18 (i 1),+0x30 (i -1),+0x3c (f -0x39001000),+0x48 (f -0x39001000),+0x54 (f 0); pos +0x3c,+0x48 |
| gamemakeanim | | (default) +0x18 (i 0),+0x24 (i 0),+0x3c (f 0),+0x48 (f 0) |
| gravity | |  |
| helper | |  |
| hitadd | |  |
| hitby | | (default) +0x18 (i uVar6),+0x30 (i iVar8) |
| hitdef | |  |
| hitfalldamage | |  |
| hitfallset | | (default) +0x18 (i -1),+0x3c (f -0x39001000),+0x48 (f -0x39001000); value +0x18; velocity +0x3c,+0x48 |
| hitfallvel | |  |
| hitoverride | |  |
| hitvelset | | x +0x18 |
| lifeadd | | value +0x18; (default) +0x24 (i 1); kill +0x24 |
| lifeset | |  |
| makedust | | (default) +0x30 (i 3),+0x54 (f 0x3f800000) |
| modifyexplod | |  |
| movehitreset | |  |
| nothitby | | (default) +0x18 (i uVar6),+0x30 (i iVar8) |
| null | | (default) +0x30 (i uVar6) |
| offset | | (default) +0x18 (i 1),+0x24 (i 1) |
| palfx | |  |
| parentvarset | | (default) +0x30 (i uVar6) |
| pause | |  |
| playerpush | |  |
| playsnd | |  |
| posadd | | (default) +0x18 (i 1),+0x24 (i 1),+0x30 (i 1); x +0x3c; y +0x48 |
| posfreeze | |  |
| posset | | (default) +0x18 (i 1),+0x24 (i 1),+0x30 (i 1); x +0x3c; y +0x48 |
| poweradd | |  |
| powerset | |  |
| projectile | |  |
| removeexplod | |  |
| reversaldef | |  |
| screenbound | | (default) +0x24 (i 0),+0x30 (i 0); movecamera +0x24,+0x30 |
| selfstate | | value +0x18; (default) +0x24 (i -1); ctrl +0x24 |
| sndpan | | channel +0x18; abspan +0x24; (default) +0x30 (i 1) |
| sprpriority | |  |
| statetypeset | | (default) +0x18 (i -1),+0x24 (i -1),+0x30 (i -1) |
| stopsnd | |  |
| superpause | |  |
| tagin | | stateno +0x18; (default) +0x24 (i -1); partnerstateno +0x24 |
| tagout | |  |
| targetdrop | | (default) +0x18 (i -1) |
| targetfacing | |  |
| targetlifeadd | | (default) +0x24 (i 1) |
| targetpoweradd | |  |
| targetstate | |  |
| targetveladd | |  |
| targetvelset | |  |
| trans | | (default) +0x24 (i 0x100),+0x30 (i 0); alpha +0x24,+0x30 |
| turn | |  |
| type | | value +0x18; (default) +0x24 (i -1); ctrl +0x24 |
| varrandom | | (default) +0x30 (i 1000) |
| varrangeset | |  |
| veladd | | (default) +0x18 (i 1),+0x24 (i 1),+0x30 (i 1); x +0x3c; y +0x48 |
| velmul | | (default) +0x18 (i 1),+0x24 (i 1),+0x30 (i 1); x +0x3c; y +0x48 |
| velset | | (default) +0x18 (i 1),+0x24 (i 1),+0x30 (i 1); x +0x3c; y +0x48 |
| width | | (default) +0x18 (i 0),+0x24 (i 0),+0x30 (i 0),+0x3c (i 0); edge +0x18,+0x24; player +0x30,+0x3c |

#### Controller type IDs (from the assembly; `artifacts/structmap/ctrl_ids.tsv`)

| Controller | Type ID (elem +0x10) | Controller | Type ID |
|---|---|---|---|
| null | 0x0 | targetvelset | 0x4b |
| forcefeedback | 0x0 | targetveladd | 0x4c |
| changestate | 0x1 | targetfacing | 0x4d |
| selfstate | 0x2 | targetdrop | 0x4e |
| turn | 0x3 | attackdist | 0x50 |
| varset | 0x4 | playerpush | 0x51 |
| varadd | 0x5 | hitfallset | 0x64 |
| varrandom | 0x6 | hitvelset | 0x65 |
| varrangeset | 0x7 | hitfalldamage | 0x66 |
| lifeset | 0xa | hitfallvel | 0x67 |
| lifeadd | 0xb | hitadd | 0x68 |
| powerset | 0xc | attackmulset | 0x69 |
| poweradd | 0xd | defencemulset | 0x6a |
| ctrlset | 0x14 | statetypeset | 0x6e |
| posset | 0x15 | hitoverride | 0x78 |
| posadd | 0x16 | movehitreset | 0x82 |
| posfreeze | 0x17 | assertspecial | 0x96 |
| velset | 0x18 | envshake | 0xc8 |
| veladd | 0x19 | fallenvshake | 0xc9 |
| velmul | 0x1a | envcolor | 0xca |
| gravity | 0x1b | gamemakeanim | 0xcb |
| offset | 0x1c | afterimage | 0xd2 |
| hitby | 0x1e | afterimagetime | 0xd3 |
| nothitby | 0x1e | pause | 0xd4 |
| changeanim | 0x20 | superpause | 0xd6 |
| changeanim2 | 0x21 | makedust | 0xd7 |
| playsnd | 0x22 | palfx | 0xd8 |
| stopsnd | 0x23 | bgpalfx | 0xd8 |
| sndpan | 0x24 | allpalfx | 0xd8 |
| hitdef | 0x25 | explod | 0xdc |
| reversaldef | 0x26 | removeexplod | 0xdd |
| projectile | 0x27 | explodbindtime | 0xde |
| width | 0x28 | modifyexplod | 0xdf |
| screenbound | 0x32 | helper | 0x12c |
| sprpriority | 0x33 | destroyself | 0x12d |
| angledraw | 0x3c | parentvarset | 0x130 |
| angleset | 0x3d | parentvaradd | 0x131 |
| angleadd | 0x3e | displaytoclipboard | 0x136 |
| anglemul | 0x3f | appendtoclipboard | 0x137 |
| trans | 0x41 | clearclipboard | 0x138 |
| targetbind | 0x46 | bindtoparent | 0x140 |
| bindtotarget | 0x47 | bindtoroot | 0x141 |
| targetstate | 0x48 | tagin | 0x2743 |
| targetpoweradd | 0x49 | tagout | 0x2744 |
| targetlifeadd | 0x4a |  |  |
