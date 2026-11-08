# Audio

## Drivers linked (VERIFIED by object files and strace)

| Kind | Driver | Device |
|---|---|---|
| Digital (WAV voices) | Allegro OSS digi driver (`uoss.c`) + software mixer (`mixer.c`) | `/dev/dsp` (opened `O_WRONLY|O_NONBLOCK`), `/dev/mixer` |
| MIDI | OSS sequencer (`uossmidi.c`) | `/dev/sequencer` |
| MIDI (software) | DIGMID (`digmid.c`) | needs `patches.dat` (looked up in cwd, `./midi/`, `/tmp/`) |
| MOD/S3M/XM/IT | JGMOD (`ModVoices = 6` voices) | through Allegro voices |
| MP3 | LibAmp (`poll_amp` from the game loop) | through Allegro voices |
| CD audio | libcda | `/dev/cdrom` (ioctl) |
| ESD, ALSA, aRts | only through Allegro plugin modules (`modules.lst`); none built in | readme mentions esd |

On the test system `/dev/dsp` and `/dev/sequencer` did not exist. MUGEN
carried on silently (VERIFIED T3).

## Getting sound on a modern system

| Program | Route | Status |
|---|---|---|
| Rebuild (`mugen-rebuilt`, dynamically linked) | `padsp ./mugen-rebuilt`, or `LD_PRELOAD=<32-bit libpulsedsp.so> ./mugen-rebuilt`. The **32-bit** `libpulsedsp.so` must be installed (Arch/CachyOS: `lib32-libpulse`; other distributions: preservation/modern-linux.md); otherwise the loader reports "cannot be preloaded" and the game is silent (T31) | VERIFIED in Debian 12 i386 with a PulseAudio null sink inside the container (no host audio device involved): sound effects, MP3 (LibAmp) and MOD (JGMOD) recorded from the sink |
| Rebuild on the host (CachyOS, PipeWire 1.6.10 with pipewire-pulse) | `LD_PRELOAD` of the 32-bit `libpulsedsp.so` from Arch's `lib32-libpulse` (with 8 dependency libraries not present on the host, from the Arch rootfs, via `LD_LIBRARY_PATH`), output to a temporary PipeWire null sink | VERIFIED (T23): sound effects, MP3, MOD and MIDI (DIGMID) recorded from the sink monitor |
| Rebuild | kernel OSS emulation (`modprobe snd-pcm-oss`) | HYPOTHESIS (not tested) |
| Original (static) | `LD_PRELOAD` cannot work on a static binary. Only a real `/dev/dsp` helps: `snd-pcm-oss` or `osspd` (CUSE) | STRONGLY INFERRED (not tested) |

Notes:

- Allegro's OSS driver (opened `O_WRONLY|O_NONBLOCK`, configured with
  `SNDCTL_DSP_*`) worked unchanged with `libpulsedsp`'s emulation (T16).
- MIDI goes through `/dev/sequencer`, which `padsp` does not emulate. Without
  it, `MidiDevice = Auto` fails and the engine retries with MIDI disabled.
  **DIGMID works** (VERIFIED T23): `MidiDevice = DIGMID` plus a `patches.dat`
  in the game directory. The one used was made with Allegro 3.9.37's own
  `pat2dat` (built in the Debian 11 container) from the FreePats General MIDI
  SoundFont (`pat2dat -o -c patches.dat freepats-general-midi.sf2 test.mid`
  keeps only the instruments the tune uses). The kernel OSS sequencer
  (`snd-seq-oss`) is untested.
- `.wav` files are not played as background music by this version
  (experiments/observations.md 24).
- **Volume** (T32, T38): Allegro's `set_volume()` first tries the driver's
  hardware mixer. The OSS driver writes `SOUND_MIXER_PCM` on `/dev/mixer`
  with MasterWavVolume (255 by default), at start-up, on the title screen
  and at every match; only if that fails does Allegro scale in software.
  libpulsedsp emulates `/dev/mixer` by setting the volume of the **default
  output device** (it ignores `PULSE_SINK`). So under padsp the game drives
  the desktop volume: 255 -> 100%, 128 -> 50%, 40 -> 15% (Debian 12 i386,
  PulseAudio; same on CachyOS, PipeWire 1.6.10). This is the original's
  behaviour, not a reconstruction fault. With `PADSP_NO_MIXER=1` (`padsp
  -M`) the mixer open fails, Allegro scales in software (recorded RMS 18 at
  MasterWavVolume 255 vs 2 at 40), and the system volume stays where the
  user put it. The kit's `run-with-sound.sh` sets this by default;
  `MUGEN_OSS_MIXER=1` restores the original behaviour.
- Debian 12's `padsp` script escapes `$LIB` twice, so it preloads nothing
  (the game is silent); preload the library by path or use the kit launcher.
- The static original cannot use `LD_PRELOAD`. Its engine-side sound logic
  was compared with the rebuild using Allegro's silent driver
  (`WavDevice = NONE`): identical calls to the sample/voice/MIDI/MOD/MP3/CD
  functions from game code (T23).
- The package that provides 32-bit `libpulsedsp.so` differs by
  distribution (see [../preservation/modern-linux.md](../preservation/modern-linux.md)).
  Only Debian 12 i386 was tested.

## Configuration (`[Sound Linux]` in mugen.cfg)

`Sound`, `StereoEffects`, `PanningWidth`, `ReverseStereo`, `WavDevice`
(parsed by `SndParseWavDevice`), `WavChannels` (12), `ModVoices`,
`MidiDevice` (`SndParseMidiDevice`), `MasterWavVolume`, `WavVolume`,
`MidiVolume`, `MP3Volume`, `ModVolume`, `CDAVolume`, `PlayMIDI`,
`PlayMP3`, `PlayMOD`, `PlayCDA`, `CDADevice`. Command line: `-nosound`,
`-nomusic`.

Details of the game side: [../engine/audio-system.md](../engine/audio-system.md).
