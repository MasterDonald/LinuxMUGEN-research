/*
 * audiolib.c -- LibAmp public API (Allegro MP3 playback on top of amp).
 *
 * RECONSTRUCTED from the LINUXMUGEN 2002.04.14 binary (unpacked SHA-256
 * d9444262...c409d1), object "audiolib.c", 0x080e0b10-0x080e17d1, 14
 * functions. The original LibAmp source (Ove Kaaven's Allegro port of
 * Tomislav Uzelac's amp, credited in readme.txt) could not be found; the
 * only archived reference is the "LibAmp 0.3" entry of Ove Kaaven's 1998
 * download page, whose file was not archived.
 *
 * Method: Ghidra 12.1.4 decompilation of every function, checked against
 * objdump. Names of functions and globals are the symbol names in the
 * binary; parameter names, types and comments are ours. Where the code
 * repeats amp 0.7.6 (audio.c), amp's own names are used. Behaviour that
 * looks unintended in the original is kept and marked "AS IN ORIGINAL".
 */
#define AUDIO                    /* define amp's globals (audio.h) here */
#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include "amp.h"
#include "audio.h"
#include "getbits.h"
#include "formats.h"
#include "layer2.h"
#include "layer3.h"
#include "misc2.h"
#include "position.h"
#include "transform.h"
#include "libamp.h"

/* public state, all GLOBAL symbols in the binary (sizes from .symtab) */
int amp_loaded;                  /* 0x082895bc, .data = 0 */
int amp_reverse_phase;           /* 0x082895c0, .data = 0; read by audioalg.c */
struct AUDIO_HEADER amp_cur_header;   /* 0x082ca6e0, 48 bytes */
int amp_stereo, amp_mpg_ver, amp_draining, amp_layer, amp_playing;
int amp_pollsize, amp_dec_frame, amp_frame, amp_time, amp_samprat;
int amp_dec_time, amp_bitrate, amp_looping;
char amp_filename[256];          /* 0x082ca980, 256 bytes */

static int is_installed;         /* "is_installed.0", function-static of install_amp */

/* amp state cleared by load_amp: append, data, f_bdirty, bclean_bytes
 * (getbits.h), s[2][32][18] = 0x1200 bytes and res[32][18] = 0x900 bytes
 * (transform.h), nch (audio.h). */

/* GETHDR + CRC, as in amp's decodeMPEG/play loop; inlined three times in
 * the binary (load_amp, init_replay, seek_amp_abs). */
static int next_header(void)
{
   int g = gethdr(&amp_cur_header);
   if (g != 0) {
      report_header_error(g);
      if (g == GETHDR_EOF && A_FORMAT_WAVE)
         wav_end(&amp_cur_header);
      A_WRITE_TO_FILE = 0;
      A_FORMAT_WAVE = 0;
      return -1;
   }
   if (amp_cur_header.protection_bit == 0)
      getcrc();
   return 0;
}

static void update_frame(void)
{
   int f = audioBufferGetFrame();
   if (f >= 0)
      amp_frame = f;
   amp_time = (amp_frame * 1152) / amp_samprat;
}

int install_amp(void)                                   /* 0x080e14f0 */
{
   if (!is_installed) {
      premultiply();
      imdct_init();
      calculate_t43();
      AUDIO_BUFFER_SIZE = 0x4b000;
      A_DUMP_BINARY = 0;
      A_QUIET = 1;
      A_FORMAT_WAVE = 0;
      A_SHOW_CNT = 0;
      A_SET_VOLUME = -1;
      A_SHOW_TIME = 0;
      A_AUDIO_PLAY = 1;
      A_WRITE_TO_FILE = 0;
      A_MSG_STDOUT = 0;
      A_DOWNMIX = 0;
      is_installed = 1;
   }
   return is_installed;
}

int load_amp(char *filename, int loop)                  /* 0x080e0b10 */
{
   int g;

   if (amp_loaded && !unload_amp())
      return 0;
   if (!install_amp())                                  /* inlined in the binary */
      return 0;
   in_file = pack_fopen(strcpy(amp_filename, filename), "rb");
   if (in_file == NULL) {
      warn("Could not open file: %s\n", filename);     /* 0x80e0c03 */
      return 0;
   }
   nch = 0;
   data = 0;
   append = 0;
   f_bdirty = 1;
   bclean_bytes = 0;
   memset(s, 0, 0x1200);
   memset(res, 0, 0x900);
   g = gethdr(&amp_cur_header);
   if (g != 0) {
      report_header_error(g);
      pack_fclose(in_file);
      return 0;
   }
   if (amp_cur_header.protection_bit == 0)
      getcrc();
   get_amp_info(&amp_cur_header);                       /* inlined in the binary */
   if (AUDIO_BUFFER_SIZE == 0)
      audioOpen(amp_samprat, amp_stereo && !A_DOWNMIX, A_SET_VOLUME);
   else
      audioBufferOpen(amp_samprat, amp_stereo && !A_DOWNMIX, A_SET_VOLUME);
   amp_loaded = 1;
   amp_playing = 1;
   amp_dec_frame = 0;
   amp_frame = 0;
   amp_time = 0;
   amp_dec_time = 0;
   amp_looping = loop;
   return 1;
}

void get_amp_info(struct AUDIO_HEADER *h)               /* 0x080e16b0 */
{
   amp_bitrate = t_bitrate[h->ID][3 - h->layer][h->bitrate_index];
   amp_layer = 4 - h->layer;
   amp_samprat = t_sampling_frequency[h->ID][h->sampling_frequency];
   amp_mpg_ver = (h->ID != 1) + 1;
   amp_stereo = (h->mode != 3);
   amp_pollsize = 1152;
   if (amp_layer == 3 && h->ID == 0)
      amp_pollsize = 576;
}

int init_replay(void)                                   /* 0x080e0e10 */
{
   pack_fclose(in_file);
   in_file = pack_fopen(amp_filename, "rb");
   if (in_file == NULL)
      die("could not reopen file");
   amp_dec_frame = 0;
   amp_dec_time = 0;
   if (next_header() < 0) {
      amp_playing = 0;
      if (!audioIsPlaying()) {
         audioStop();
         return -1;
      }
      amp_draining = 1;
      return 0;
   }
   if (!amp_playing && !amp_draining) {
      amp_frame = amp_dec_frame;
      audioStart();
      update_frame();
   }
   amp_draining = 0;
   amp_playing = 1;
   return 1;
}

int read_amp_frame(struct AUDIO_HEADER *h)              /* 0x080e1740 */
{
   int err;

   if (h->layer == 1)
      err = layer3_frame(h, amp_dec_frame);         /* cnt = amp_dec_frame (0x80e1752) */
   else if (h->layer == 2)
      err = layer2_frame(h, amp_dec_frame);
   else
      return 1;
   if (err == 0)
      return 1;
   unload_amp();
   warn(" error. blip.\n");
   return 0;
}

int poll_amp(void)                                      /* 0x080e0f80 */
{
   int need;

   if (!amp_loaded)
      return -1;
   if (!amp_playing) {
      if (!amp_draining)
         return -1;
      if (audioUsedSpace() != 0) {
         audioBufferPad();
         audioBufferWrite(NULL, 0);
      }
      update_frame();
      if (audioIsPlaying())
         return 0;
      amp_draining = 0;
      audioStop();
      return -1;
   }
   need = 1152;
   if (amp_cur_header.layer == 1 && amp_cur_header.ID == 0)
      need = 576;
   if (audioSpaceRemaining() < need) {
      audioBufferWrite(NULL, 0);
      update_frame();
      if (audioSpaceRemaining() < need)
         return 0;
   }
   amp_dec_frame++;
   amp_dec_time = (amp_dec_frame * 1152) / amp_samprat;
   if (read_amp_frame(&amp_cur_header)) {              /* inlined in the binary */
      update_frame();
      if (next_header() >= 0)
         return 1;
   }
   else
      update_frame();
   if (amp_looping)
      return init_replay();
   amp_playing = 0;
   if (!audioIsPlaying()) {
      audioStop();
      return -1;
   }
   amp_draining = 1;
   return 0;
}

int seek_amp_abs(int frame)                             /* 0x080e1260 */
{
   if (!amp_loaded)
      return -1;
   if (amp_playing) {
      audioStop();
      amp_draining = 0;
      amp_playing = 0;
   }
   if (frame > amp_dec_frame) {
      amp_dec_frame += ffwd(&amp_cur_header, frame - amp_dec_frame);
   }
   else if (frame < amp_dec_frame) {
      pack_fclose(in_file);
      in_file = pack_fopen(amp_filename, "rb");
      if (in_file == NULL)
         die("could not reopen file");
      amp_dec_frame = 0;
      amp_dec_time = 0;
      if (next_header() < 0)
         return -1;
      amp_dec_frame += ffwd(&amp_cur_header, frame);
   }
   /* AS IN ORIGINAL: amp_playing was cleared above, so this test is dead */
   if (amp_playing) {
      amp_draining = 0;
      amp_playing = 1;
      return 0;
   }
   if (!amp_draining) {
      amp_frame = amp_dec_frame;
      audioStart();
      update_frame();
   }
   amp_playing = 1;
   amp_draining = 0;
   return 0;
}

int seek_amp_rel(int frames)                            /* 0x080e1620 */
{
   int f = amp_frame + frames;
   return seek_amp_abs(f < 0 ? 0 : f);                 /* binary: f & ~(f >> 31) */
}

int run_amp(void)                                       /* 0x080e1590 */
{
   int r;
   if (!amp_loaded || (!amp_playing && !amp_draining))
      return -1;
   do {
      r = poll_amp();
   } while (r > 0);
   return r;
}

int replay_amp(void)                                    /* 0x080e15d0 */
{
   if (!amp_loaded)
      return -1;
   if (amp_playing) {
      audioStop();
      amp_draining = 0;
      amp_playing = 0;
   }
   return init_replay();
}

int unload_amp(void)                                    /* 0x080e1640 */
{
   if (!amp_loaded)
      return 0;
   amp_draining = 0;
   amp_playing = 0;
   amp_loaded = 0;
   if (AUDIO_BUFFER_SIZE == 0)
      audioClose();
   else
      audioBufferClose();
   pack_fclose(in_file);
   return 1;
}

void report_header_error(int err)                       /* 0x080e1450, as amp 0.7.6 audio.c */
{
   switch (err) {
      case GETHDR_ERR:
         die("error reading mpeg bitstream. exiting.\n");
         break;
      case GETHDR_NS:
         warn("this is a file in MPEG 2.5 format, which is not defined\n");
         warn("by ISO/MPEG. It is \"a special Fraunhofer format\".\n");
         warn("amp does not support this format. sorry.\n");
         break;
      case GETHDR_FL1:
         warn("ISO/MPEG layer 1 is not supported by amp (yet).\n");
         break;
      case GETHDR_FF:
         warn("free format bitstreams are not supported. sorry.\n");
         break;
      case GETHDR_SYN:
         warn("oops, we're out of sync.\n");
         break;
      case GETHDR_EOF:
      default:
         break;
   }
}

void set_volume_mp3(int vol)                            /* 0x080e17c0 */
{
   set_volume(vol * 2, -1);
}

/* AS IN ORIGINAL: the function body in the binary is a single "ret"
 * (0x080e17d0), i.e. it returns whatever is in EAX. MUGEN's only caller
 * (MP3GetVol @ 0x08058060, snd-lib.c) therefore receives an unspecified value. We
 * return 0 so the result is at least deterministic; documented in
 * LINUXMUGEN-RESEARCH/engine/audio-system.md. */
int get_volume_mp3(void)
{
   return 0;
}
