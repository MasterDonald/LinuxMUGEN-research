/*
 * libamp.h -- interface of the reconstructed LibAmp (see audiolib.c).
 * Prototypes reconstructed from the binary's code and its callers in MUGEN
 * (snd-lib.c MP3Init/MP3LoadAndPlay/MP3Poll/MP3Unload/MP3SetVol/MP3GetVol).
 * This is not the original header, which is lost.
 */
#ifndef LIBAMP_H
#define LIBAMP_H

struct AUDIO_HEADER;

int  install_amp(void);
int  load_amp(char *filename, int loop);
int  poll_amp(void);            /* 1 = frame decoded, 0 = waiting, -1 = finished */
int  run_amp(void);
int  replay_amp(void);
int  seek_amp_abs(int frame);
int  seek_amp_rel(int frames);
int  unload_amp(void);
void get_amp_info(struct AUDIO_HEADER *header);
int  read_amp_frame(struct AUDIO_HEADER *header);
int  init_replay(void);
void set_volume_mp3(int vol);
int  get_volume_mp3(void);

extern int amp_loaded, amp_playing, amp_draining, amp_looping;
extern int amp_bitrate, amp_samprat, amp_layer, amp_mpg_ver, amp_stereo, amp_pollsize;
extern int amp_frame, amp_dec_frame, amp_time, amp_dec_time, amp_reverse_phase;
extern char amp_filename[256];

/* audioalg.c: amp's audio interface implemented with Allegro streams */
void audioOpen(int frequency, int stereo, int volume);
int  audioBufferOpen(int frequency, int stereo, int volume);
void audioSetVolume(int volume);
void audioFlush(void);
void audioBufferFlush(void);
void audioClose(void);
void audioBufferClose(void);
int  audioWrite(char *buf, int bytes);
void audioBufferWrite(char *buf, int bytes);
void printout(void);
int  audioAlloc(void);
void audioStop(void);
void audioStart(void);
int  audioReady(void);
int  audioUsedSpace(void);
int  audioSpaceRemaining(void);
int  audioBufferGetFrame(void);
int  audioIsPlaying(void);
void audioBufferPad(void);

#endif
