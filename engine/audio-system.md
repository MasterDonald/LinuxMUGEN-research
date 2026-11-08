# Audio system

## Sound effects (`snd-lib.c`, `sound.c`)

- SND files load into sound arrays (`SndReadFile`, `SndReadFileSNDPtr`;
  WAVs via `SndReadFileWAVPtr`). Each sound becomes an Allegro `SAMPLE`
  (`create_sample`).
- Voices: `WavChannels` (12) Allegro voices are reserved
  (`reserve_voices`). Elecbyte voice management:
  `SndVoiceReserve/Unreserve/Start/Stop/SetVol/SetPan/SetFreq/SetLoop`,
  `SndIDPlay/Stop/IsPlaying` (channel-addressed playback for the PlaySnd
  and StopSnd controllers).
- Panning: `PanningWidth`, `StereoEffects`, `ReverseStereo`
  (`SndSetReverseStereo`), pan scaled by `SndPanMul`.
- Volumes: master, WAV, MIDI, MP3, MOD, CDA (`SndSetVol`, `GameSetVol`).

## Music (`bgm.c` + `snd-lib.c`)

`BGMLoad` picks a player from the file extension (`BGMCheckExtension`):

| Type | Engine | Calls |
|---|---|---|
| MIDI | Allegro MIDI (OSS sequencer or DIGMID) | `SndMidiReadFile` -> `load_midi`, `play_looped_midi` |
| MP3 | LibAmp | `MP3LoadAndPlay` -> `load_amp`, `poll_amp` every frame |
| MOD/S3M/XM/IT | JGMOD | `MODLoad` -> `load_mod`, `play_mod` |
| CD audio | libcda | `CDAPlay` -> `cd_play`, `cd_play_loop` |

`PlayMIDI`, `PlayMP3`, `PlayMOD`, `PlayCDA` enable each type; `-nomusic`
disables all of them (VERIFIED: keys and calls).

Observed at run time (experiments T23, T26; identical in original and
rebuild):

- `BGMLoad` does nothing unless a digital sound driver is installed, so
  without sound there is no music of any kind, CD included.
- `.wav` is recognised by `CheckExtension` (type 3) but not played as music.
- CD: `bgmusic = N.da` → `CDAInit` (`cd_init`) at load, `cd_play_loop(N)` at
  start, then `cd_is_playing()` every 6 frames and `cd_play_now(N)` when
  the track has stopped; that is how looping is implemented.
- `MidiDevice = Auto` without `/dev/sequencer`: `install_sound(-1, -1)`
  fails and the engine retries with `install_sound(-1, 0)` (no MIDI).
  With `MidiDevice = DIGMID` and a `patches.dat`, MIDI music plays through
  the digital voices.

## MP3 playback internals (LibAmp, reconstructed)

LibAmp's source is lost, so it was reconstructed from the binary
([../reconstruction/thirdparty/README.md](../reconstruction/thirdparty/README.md)).
How it works (VERIFIED from the decompiled code and objdump):

- `load_amp(file, loop)` opens the file as an Allegro `PACKFILE`, reads the
  first MPEG header and starts an Allegro `AUDIOSTREAM`
  (`play_audio_stream(0x4800, 16, stereo, freq, 255, 128)`).
- `poll_amp()`, called once per game frame, decodes layer II/III frames
  into a ring buffer of 0x9000 sample frames. Each time half a stream
  buffer (0x4800 frames) is ready, it is copied into the stream. Signed
  16-bit PCM is converted to Allegro's unsigned format (XOR 0x8000).
- Seeking backwards reopens the file and fast-forwards, because PACKFILEs
  only seek forwards.
- `set_volume_mp3(v)` calls `set_volume(v * 2, -1)`, which changes the
  **global** Allegro digital volume. In the binary, `get_volume_mp3` is a
  bare `ret`, so `MP3GetVol` (0x08058060) receives an unspecified value
  (VERIFIED). The reconstruction returns 0.

MP3 and MOD music were verified audible in the rebuild (experiments T16).

## Device layer

See [../linux/audio.md](../linux/audio.md) (OSS `/dev/dsp`,
`/dev/sequencer`).
