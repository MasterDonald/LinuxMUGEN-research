/* Two libcda entry points that exist in the LINUXMUGEN 2002.04.14 binary but
 * not in any published libcda release (0.5 / 0.5.1, Peter Wang).
 *
 * VERIFIED (objdump of the unpacked binary): cd_play_now @ 0x081bbc10 and
 * cd_play_loop @ 0x081bbcc0 are 175 bytes each and instruction-for-
 * instruction identical to cd_play @ 0x081bbb60, which is libcda's
 * play(track, track) with USE_PLAYMSF inlined (cd_get_tracks, lead-out 0xAA
 * for the last track, two get_tocentry calls, ioctl CDROMPLAYMSF 0x5303).
 * The names suggest different intent (play immediately / loop), but in this
 * build they behave exactly like cd_play, so they are defined that way. */
#include "libcda.h"

int cd_play_now(int track)  { return cd_play(track); }
int cd_play_loop(int track) { return cd_play(track); }

/* cd_is_playing @ 0x081bbef0 (23 bytes) is not in libcda 0.5.1 either; it
 * returns cd_current_track() != 0 (VERIFIED: call cd_current_track; setne). */
int cd_is_playing(void)     { return cd_current_track() != 0; }
