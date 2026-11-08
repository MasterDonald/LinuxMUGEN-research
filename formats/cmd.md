# CMD: commands and input

Example: `chars/kfm/kfm.cmd`. Parsers: `PlayerCMDLoad`, `PlayerCMDLoadTP`
(`p-make.c`); detection: `cmd-dtct.c` (14 functions).

```
[Defaults]
command.time = 15
command.buffer.time = 1

[Command]
name = "TripleKFPalm"
command = ~D, DF, F, D, DF, F, x
time = 20
```

| Item | Notes |
|---|---|
| `[Defaults]` | `command.time`, `command.buffer.time` (VERIFIED keys) |
| `[Command]` | `name`, `command`, `time`, `buffer.time` |
| Symbols | `~` release, `/` hold, `$` 4-way direction, `>` no other input between, `+` simultaneous, buttons `a b c x y z s`, directions `B DB D DF F UF U UB` (docs/cns, kfm.cmd) |
| `[Remap]` | **new in 2002.04.14**: button remapping (`remap` group read in `p-make.c`, VERIFIED) |
| State entry | `[Statedef -1]` in the CMD with `ChangeState` controllers triggered by `command = "name"` |

2002.04.14 fixes (updates.txt): `$` release no longer detected as a press;
the same command is no longer detected repeatedly when the last button is
mashed.
