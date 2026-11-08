# AIR: animations

Example: `chars/kfm/kfm.air` (47,098 bytes, CRLF). Reference:
`docs/air.txt`. Loader: `AnimRCReadFile` -> `AnimRCReadFileTP` ->
`AnimElemParseLine`, `ClsnParseLine` (`anim-lib.c`, `clsn-lib.c`).

```
[Begin Action 0]
Clsn2Default: 2
 Clsn2[0] = -13,  0, 16,-79
 Clsn2[1] =   5,-79, -7,-93
0,0, 0,0, 10
0,1, 0,0, 7
```

| Element | Syntax | Meaning |
|---|---|---|
| Action | `[Begin Action N]` | animation number |
| Collision defaults | `Clsn1Default: n` / `Clsn2Default: n` + n boxes | attack (1) / hurt (2) boxes for all following frames |
| Per-frame boxes | `Clsn1: n` / `Clsn2: n` + `ClsnK[i] = x1,y1,x2,y2` | boxes for the next frame only |
| Frame | `group, image, xoffset, yoffset, time[, flip[, trans]]` | sprite, offset, duration in ticks (-1 = forever); flip `H`/`V`/`HV`; trans `A`, `S`, `AS`... |
| Loop | `Loopstart` | loop point |

Collision box coordinates are scaled on load by `clsnxscale`/`clsnyscale`
when not 1.0 (VERIFIED, `ClsnParseLine`, 0x0804e800). Draw flags are
decoded by `AnimElemProcessDrawFlags`; transparency uses the additive and
subtractive blitters (see ../engine/rendering.md). readme Known Issues:
"Collision boxes in helpers inherit parent's scale, regardless of own
scale".
