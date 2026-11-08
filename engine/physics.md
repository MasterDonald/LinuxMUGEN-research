# Physics

Sources: decompiled `PlayerUpdate` (`p-update.c`), CNS constants,
`docs/cns.html`.

| Aspect | Implementation | Class |
|---|---|---|
| Representation | **float** fields of the player struct (x87 `flds/fsts`) at offsets 0x19c, 0x1a0 (added to each tick: position x/y) and 0x224, 0x228 (velocity x/y) | VERIFIED (float type: instructions at 0x80b23be..0x80b2402); field meaning STRONGLY INFERRED (pos += vel pattern) |
| Integration | per tick: velocity x multiplied by the float at 0x22c (`flds 0x224; fmuls 0x22c; fsts 0x224`), then added to position (`p[0x67] += p[0x89]`, `p[0x68] += p[0x8a]`) | VERIFIED (assembly and reconstructed `PlayerUpdate`) |
| Gravity | `yaccel` from `[Movement]` added to y velocity in air states (statetype A, physics A) | STRONGLY INFERRED (CNS key + docs; code path not individually traced) |
| Friction | `stand.friction`, `crouch.friction` multiply x velocity in physics S and C | STRONGLY INFERRED (keys, docs) |
| Screen bounds and player push | `ScreenBound`, `StageBound` (`p-update.c`) with `[PlayerInfo]`/`[Bound]` limits; `screenbound` and `playerpush` controllers | VERIFIED (function names); details STRONGLY INFERRED |
| Binding | `PlayerUpdateBindTo`, `bindtotarget`, `targetbind` | VERIFIED (names, controllers) |
| Hit pause / shake | `hitpausetime`, `hitshaketime` triggers; `Pause`/`SuperPause` controllers | VERIFIED (vocabulary) |
