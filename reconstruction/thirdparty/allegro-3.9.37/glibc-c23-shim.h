/* Force-included (-include) when building Allegro 3.9.37 with glibc >= 2.28.
 * glibc's <math.h> declares the C23 narrowing functions fadd, fsub, fmul,
 * fdiv and fsqrt when _GNU_SOURCE is set; Allegro 3.9.37 defines fixed-point
 * functions with the same names (include/allegro/al386gcc.h). Include
 * <math.h> first with glibc's names moved aside, so Allegro's own
 * definitions are the only ones visible. Allegro's sources are not changed. */
#ifndef __ASSEMBLER__    /* the makefile passes CFLAGS to .s files too */
#define _GNU_SOURCE 1
#define fadd  glibc_c23_fadd
#define fsub  glibc_c23_fsub
#define fmul  glibc_c23_fmul
#define fdiv  glibc_c23_fdiv
#define fsqrt glibc_c23_fsqrt
#include <math.h>
#undef fadd
#undef fsub
#undef fmul
#undef fdiv
#undef fsqrt
#endif
