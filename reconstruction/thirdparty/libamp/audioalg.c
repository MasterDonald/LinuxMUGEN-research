/*
 * audioalg.c -- LibAmp audio output through Allegro audio streams.
 * Replaces amp 0.7.6's audioIO_*.c and buffer.c.
 *
 * RECONSTRUCTED from the LINUXMUGEN 2002.04.14 binary, object "audioalg.c",
 * 0x080e17e0-0x080e2329, 21 functions (see audiolib.c for the method).
 * Static variable names are the LOCAL symbol names of audioalg.c in the
 * binary (audio_left, buffer_head, ...).
 *
 * Design (VERIFIED from the code): decoded PCM is written into a ring buffer
 * of 0x9000 sample frames (buffer_left), with the decoder frame number of
 * every sample frame in buffer_frame. Whenever half a stream buffer
 * (0x4800 frames) is ready, it is copied into the Allegro AUDIOSTREAM
 * (play_audio_stream(0x4800, 16 bits, stereo, freq, vol 255, pan 128)),
 * and the frame numbers into stream_frame at the stream's refill buffer, so
 * audioBufferGetFrame can map the voice position back to a decoder frame.
 * 16-bit signed samples are converted to Allegro's unsigned format by
 * XOR 0x8000 per channel.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>
#include "amp.h"
#include "audio.h"
#include "transform.h"     /* sample_buffer */
#include "libamp.h"

#define RING   0x9000           /* ring buffer, sample frames */
#define HALF   0x4800           /* AUDIOSTREAM length, sample frames */

int AUDIO_BUFFER_SIZE;          /* amp 0.7.6 buffer.c global; 0x082cd168 */
void *amp_buf_left, *amp_buf_right;   /* last stream buffer filled */
int amp_buf_len;
void *amp_play_left, *amp_play_right; /* approximate play pointer in the sample */
int amp_play_len;

static AUDIOSTREAM *audio_left, *audio_right;   /* audio_right is never opened */
static void *stream_left;
static int stream_right;
static int freq, instereo;
static char *buffer_left, *buffer_right;        /* buffer_right is never allocated */
static unsigned int buffer_head, buffer_tail, buffer_used;
static int last_frame;
static int *buffer_frame, *stream_frame;

extern int amp_dec_frame, amp_reverse_phase;

static int audioBufferAlloc(void)                       /* 0x080e17e0 */
{
   buffer_left = malloc((instereo + 1) * RING * 2);
   if (buffer_left && (buffer_frame = malloc(RING * 4)) && (stream_frame = malloc(RING * 4))) {
      memset(stream_frame, -1, RING * 4);
      return 1;
   }
   return 0;
}

static void audioBufferTransfer(void)                   /* 0x080e1860 */
{
   for (;;) {
      if (!stream_left)
         stream_left = get_audio_stream_buffer(audio_left);
      if (!stream_left || buffer_used < HALF)
         break;
      memcpy(stream_left, buffer_left + (instereo * 2 + 2) * buffer_tail, (instereo + 1) * HALF * 2);
      memcpy(stream_frame + audio_left->bufnum * HALF, buffer_frame + buffer_tail, HALF * 4);
      free_audio_stream_buffer(audio_left);
      amp_buf_left = amp_buf_right = stream_left;
      buffer_tail = (buffer_tail + HALF) % RING;
      stream_right = 0;
      stream_left = NULL;
      buffer_used -= HALF;
   }
}

static void restart_stream(void)
{
   audio_left = play_audio_stream(HALF, 16, instereo, freq, 255, 128);
   if (!audio_left)
      die("Unable to open audio device\n");
}

void audioStop(void)                                    /* 0x080e2020 */
{
   if (audio_left)
      stop_audio_stream(audio_left);
   if (audio_right)
      stop_audio_stream(audio_right);
   amp_buf_left = amp_buf_right = NULL;
   audio_left = audio_right = NULL;
   buffer_used = buffer_tail = buffer_head = 0;
}

void audioStart(void)                                   /* 0x080e20a0 */
{
   restart_stream();
   memset(stream_frame, -1, RING * 4);
}

/* audioFlush 0x080e1b50 and audioBufferFlush 0x080e1960 are identical
 * (stop + restart) in the binary. */
void audioFlush(void)       { audioStop(); audioStart(); }
void audioBufferFlush(void) { audioStop(); audioStart(); }

static void open_common(int frequency, int stereo, int volume)
{
   instereo = (stereo != 0);
   freq = frequency;
   restart_stream();
   if (!audioBufferAlloc())
      die("Unable to allocate write buffer\n");
   buffer_used = buffer_tail = buffer_head = 0;
   stream_left = NULL;
   stream_right = 0;
   amp_buf_left = amp_buf_right = NULL;
   amp_buf_len = HALF;
   amp_play_left = amp_play_right = NULL;
   amp_play_len = 0x400;
   if (volume != -1)
      audioSetVolume(volume);
}

/* audioOpen 0x080e1a30 and audioBufferOpen 0x080e1d20 have the same body;
 * audioBufferOpen returns 0. */
void audioOpen(int frequency, int stereo, int volume)       { open_common(frequency, stereo, volume); }
int  audioBufferOpen(int frequency, int stereo, int volume) { open_common(frequency, stereo, volume); return 0; }

void audioSetVolume(int volume)                         /* 0x080e1b30 */
{
   set_volume(volume * 2, -1);
}

/* audioClose 0x080e1c20 and audioBufferClose 0x080e1e20 are identical. */
static void close_common(void)
{
   if (audio_left)
      stop_audio_stream(audio_left);
   if (audio_right)
      stop_audio_stream(audio_right);
   free(buffer_left);
   free(buffer_right);
   free(buffer_frame);
   free(stream_frame);
}
void audioClose(void)       { close_common(); }
void audioBufferClose(void) { close_common(); }

int audioWrite(char *buf, int bytes)                    /* 0x080e1c90 */
{
   audioBufferWrite(buf, bytes);
   return bytes;
}

/* amp's buffer.c printout() without the byte-swapping loop and without the
 * AUDIO_BUFFER_SIZE == 0 branch (VERIFIED 0x080e1cb0, 103 bytes). */
void printout(void)
{
   int j = (nch == 2) ? 32 * 18 * 2 : 32 * 18;
   if (A_WRITE_TO_FILE)
      fwrite(sample_buffer, sizeof(short), j, out_file);
   if (A_AUDIO_PLAY)
      audioBufferWrite((char *)sample_buffer, j * sizeof(short));
}

void audioBufferWrite(char *buf, int bytes)             /* 0x080e1e90 */
{
   unsigned int n = instereo ? (unsigned int)bytes >> 2 : (unsigned int)bytes >> 1;
   unsigned int chunk, i;

   while (n) {
      chunk = RING - buffer_head;
      if (n < chunk)
         chunk = n;
      while (chunk + buffer_used > RING)
         audioBufferTransfer();
      /* AS IN ORIGINAL: every chunk is read from the start of buf (the source
       * pointer is never advanced, VERIFIED: "mov %ebp,%esi" per chunk). A
       * second chunk only happens when a write crosses the end of the ring;
       * 0x9000 is a multiple of 1152 and 576, so whole-granule writes from
       * printout() never cross it. */
      if (!instereo) {
         unsigned short *src = (unsigned short *)buf, *dst = (unsigned short *)buffer_left + buffer_head;
         for (i = 0; i < chunk; i++)
            dst[i] = src[i] ^ 0x8000;
      }
      else {
         unsigned int *src = (unsigned int *)buf, *dst = (unsigned int *)buffer_left + buffer_head;
         unsigned int x = amp_reverse_phase ? 0x7fff8000u : 0x80008000u;
         for (i = 0; i < chunk; i++)
            dst[i] = src[i] ^ x;
      }
      for (i = 0; i < chunk; i++)
         buffer_frame[buffer_head + i] = amp_dec_frame;
      last_frame = amp_dec_frame;
      buffer_head = (buffer_head + chunk) % RING;
      buffer_used += chunk;
      n -= chunk;
   }
   audioBufferTransfer();                               /* tail call */
}

int audioAlloc(void)                                    /* 0x080e1fe0 */
{
   audio_left = play_audio_stream(HALF, 16, instereo, freq, 255, 128);
   return audio_left != NULL;
}

int audioReady(void)                                    /* 0x080e2100 */
{
   if (!stream_left)
      stream_left = get_audio_stream_buffer(audio_left);
   return stream_left != NULL;
}

int audioUsedSpace(void)      { return buffer_used; }          /* 0x080e2140 */
int audioSpaceRemaining(void) { return RING - buffer_used; }   /* 0x080e2150 */

int audioBufferGetFrame(void)                           /* 0x080e2160 */
{
   int pos;

   if (!amp_buf_left)
      return -1;
   amp_play_left = amp_play_right = NULL;
   if (audio_left && (pos = voice_get_position(audio_left->voice)) >= 0) {
      amp_play_left = amp_play_right =
         (char *)audio_left->samp->data + (pos >> 10) * (instereo * 0x800 + 0x800);
      return stream_frame[pos];
   }
   return last_frame + 1;
}

/* Returns non-zero while data is still queued or no stream buffer is free. */
int audioIsPlaying(void)                                /* 0x080e21f0 */
{
   if (buffer_used)
      return 1;
   if (!stream_left)
      stream_left = get_audio_stream_buffer(audio_left);
   return stream_left == NULL;
}

/* Pads the ring with silence up to one stream buffer (HALF frames) so the
 * tail of a song is transferred. Runs only for 1 <= buffer_used <= 0x47ff. */
void audioBufferPad(void)                               /* 0x080e2240 */
{
   int pad, i, c;
   unsigned short *p;

   if (buffer_used - 1 > 0x47fe)
      return;
   pad = HALF - buffer_used;
   p = (unsigned short *)buffer_left + buffer_head;
   if (instereo) {
      /* AS IN ORIGINAL: the stereo fill starts at word buffer_head (not
       * 2 * buffer_head) and steps 2 words, i.e. it writes one channel of
       * the wrong frames, then one more word (VERIFIED 0x80e2267-0x80e229a). */
      for (i = 0; i < pad; i++)
         p[i * 2] = 0x8000;
      c = pad > 0 ? pad : 0;
      ((unsigned short *)buffer_left)[buffer_head + c * 2 + 1] = 0x8000;
   }
   else {
      for (i = 0; i < pad; i++)
         p[i] = 0x8000;
   }
   for (i = 0; i < pad; i++)
      buffer_frame[buffer_head + i] = last_frame + 1;
   buffer_head = (buffer_head + pad) % RING;
   buffer_used += pad;
}
