# Game execution

## Modes (readme, VERIFIED; flow from `MainLoop`)

Arcade, Versus, Team Arcade, Team Versus, Team Co-op, Survival, Survival
Co-op, Training, Watch, Options, Exit. Team modes: Single, Simul (2 at
once), Turns (up to 4 in sequence). Turns-mode order rotation by holding
a direction (readme chart).

## Match sequence

```
CharacterSelectScreen -> (arcade list / survival random team) -> precache
loop over opponents:
   [character intro storyboard] -> VersusScreen -> GamePlay:
       GameLoadStage, players reset
       rounds: round intro ("Round N", "Fight") -> GameLoop frames ->
               KO / time over -> win poses -> next round or match end
   ContinueScreen (arcade) / GameWinScreenUpdate / GameSurvivalResultsUpdate
[ending storyboard] -> credits -> back to title
```

(VERIFIED as call structure in `MainLoop`, `GamePlay`, `GameLoop`; the
round sub-steps follow `fight.def` timings: `round.time`, `fight.time`,
`KO.time`, `over.waittime`, `over.wintime`, `win.time`.)

## Training

Training menu (dummy control: Cooperative/AI/Manual; guard; dummy mode;
distance; button jam; minimise with M), `TrainingMenuReset/Update/Draw`
(`menus.c`) (VERIFIED names; behaviour from readme).

## Logging

`-log <file>` "Records match data to <file>" (`LogPreMatch`) (VERIFIED
string and function).
