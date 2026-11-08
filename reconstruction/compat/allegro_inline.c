/*
 * allegro_inline.c -- C entry points for Allegro inline functions that the
 * original code used through inline expansion.
 *
 * Hand-written (not decompiled). The Elecbyte blitters in vbuf.c call the
 * bitmap bank-switch routines the way Allegro's i386 inline functions do:
 * read_bank/write_bank with %edx = bitmap and %eax = line (result in %eax),
 * unwrite_bank with %edx = bitmap (VERIFIED: blit_32to16_RGBtoBGR
 * 0x0807d5f0-0x0807d689, stretch_blit_32to16_RGBtoBGR 0x0807d952-0x0807da55).
 * Ghidra cannot express register arguments of indirect calls, so the
 * reconstructed C calls these wrappers, compiled against the real Allegro
 * header so the inline code is Allegro's own.
 */
#include <allegro.h>

unsigned long ALG_bmp_read_line(void *bmp, int line)  { return bmp_read_line((BITMAP *)bmp, line); }
unsigned long ALG_bmp_write_line(void *bmp, int line) { return bmp_write_line((BITMAP *)bmp, line); }
void ALG_bmp_unwrite_line(void *bmp)                  { bmp_unwrite_line((BITMAP *)bmp); }
