/*
 * mugen_common.h -- included by every reconstructed source file.
 * Order matters: libc headers first (the original was built against glibc
 * 2.2.4 headers), then the decompiler compatibility layer, then the
 * generated prototype and data declarations.
 */
#pragma once
/* _DEFAULT_SOURCE, not _GNU_SOURCE: with _GNU_SOURCE, glibc >= 2.38 redirects
 * sscanf/strtol to __isoc23_* symbols and the binary would not start on
 * older distributions (see preservation/modern-linux.md). */
#define _DEFAULT_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>
#include <pthread.h>
#include <assert.h>
#include "ghidra_compat.h"
typedef struct tm tm;
typedef FILE _IO_FILE;
#include "mugen_types.h"
/* compat/allegro_inline.c: Allegro inline functions with register arguments */
unsigned long ALG_bmp_read_line(void *bmp, int line);
unsigned long ALG_bmp_write_line(void *bmp, int line);
void ALG_bmp_unwrite_line(void *bmp);
#include "mugen_protos.h"
#include "mugen_data.h"

/* glibc 2.2 exported its ctype tables as plain globals; glibc >= 2.3 only
 * exposes them through accessor functions. The decompiled code reads the
 * pointer value directly (inlined isxxx()/tolower() macros), so map the old
 * names onto the accessors. */
#define __ctype_b       ((int)*__ctype_b_loc())
#define __ctype_tolower ((int)*__ctype_tolower_loc())
#define __ctype_toupper ((int)*__ctype_toupper_loc())

/* Ghidra pseudo-functions and glibc 2.2 internals that appear in the
 * decompiled code (inlined by GCC 2.96 from glibc 2.2.4 headers). */
#define fsin(x)                          sinl(x)            /* x87 FSIN */
/* pthread_yield() was removed from glibc 2.34; glibc implemented it as
 * sched_yield() (nptl/pthread_yield.c), which is what the original called
 * through linuxthreads. */
#include <sched.h>
#define pthread_yield()                  sched_yield()
/* Other x87 instructions Ghidra prints as pseudo-functions (sleigh x86
 * pcodeops). Semantics from the Intel SDM; argument order as in Ghidra's
 * output: fpatan(ST1, ST0) = atan(ST1/ST0) with quadrant, i.e. atan2. */
#define fcos(x)                          cosl(x)            /* FCOS */
#define fptan(x)                         tanl(x)            /* FPTAN (the pushed 1.0 is dropped by GCC) */
#define fpatan(y, x)                     atan2l((y), (x))   /* FPATAN */
#define f2xm1(x)                         (exp2l(x) - 1.0L)  /* F2XM1: 2^x - 1, |x| <= 1 */
#define fscale(a, b)                     scalbnl((a), (int)(b)) /* FSCALE: a * 2^trunc(b) */
#define SQRT(x)                          sqrtl(x)           /* FSQRT */
#define log2(x)                          log2l(x)           /* FYL2X with ST1 = 1: x87 extended precision */
#define builtin_strncpy(d, s, n)         strncpy((d), (s), (n))
#define __strtod_internal(s, e, grp)     strtod((s), (e))   /* atof()/strtod() inline */
#define __strtol_internal(s, e, b, grp)  strtol((s), (e), (b))
