# ACT: palette files

| Property | Value | Class |
|---|---|---|
| Size | 768 bytes = 256 RGB triplets (all 6 KFM palettes) | VERIFIED |
| Order | **reversed**: file entry *i* is stored at palette index 255 - *i* | VERIFIED: `Pal4Read3File` (`pal-lib.c`, 0x08056120) writes entry *i* to `(0xff - i) * 4` |
| In-memory form | 4 bytes per colour (R, G, B, unused), "Pal4" | VERIFIED (same function) |
| Use | Character palettes `pal1`..`pal12` in the character DEF; `pal.defaults` gives preference order | VERIFIED (kfm.def) |
| Index 0 | In shipped files the last triplet (file end) is index 0 after reversal, i.e. the transparent colour of the 8-bit sprites (all KFM ACTs end with 255,255,255) | VERIFIED (bytes); that index 0 is the transparent colour: HYPOTHESIS (not yet confirmed in the blitters) |

readme Known Issues: "No support for multiple palettes in players".
