# SND: sound archive

Sources: `formats`; 4 shipped files (`kfm.snd`, `common.snd`,
`fight.snd`, `system.snd`); loader `SndReadFileSNDPtr`, `SndReadFileWAVPtr`
(`snd-lib.c`).

## Header (512 bytes)

| Offset | Size | Field | Observed |
|---|---|---|---|
| 0 | 12 | `ElecbyteSnd\0` | all files |
| 12 | 4 | version | `04 00 00 00` in all files (formats.txt: "4 verhi, 4 verlo") |
| 16 | 4 | number of sounds | 12, 10, 8, 3 (matches the walk, VERIFIED) |
| 20 | 4 | first subfile offset | 512 |
| 24 | 488 | unused | |

## Subfile (16-byte header + data)

| Offset | Size | Field |
|---|---|---|
| 0 | 4 | next subfile offset |
| 4 | 4 | data length |
| 8 | 4 | group number |
| 12 | 4 | sample number |
| **16** | n | RIFF/WAVE file |

formats.txt says the sound data starts at "08-", which is wrong. In every
file the WAV starts at subfile offset 16, right after group and sample
(VERIFIED by `tools/parse_formats.py`).

## Sample formats present (VERIFIED)

All samples are PCM (format tag 1), mono, 8-bit, at 8,000 / 11,025 /
16,000 / 22,050 Hz. They are played through Allegro voices
(`allocate_voice`, `voice_set_frequency`, `voice_set_pan`, ...). See
[../engine/audio-system.md](../engine/audio-system.md).
