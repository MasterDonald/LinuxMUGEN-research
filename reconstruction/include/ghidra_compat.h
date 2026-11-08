/*
 * ghidra_compat.h -- definitions for the types and helper macros that the
 * Ghidra decompiler uses in its C output, so the reconstructed files can be
 * compiled with GCC for i386 (-m32). Semantics follow the Ghidra decompiler
 * documentation; ROUND() was checked against the original instructions (see
 * engine/... and binary-analysis/executable-analysis.md, "x87 conversions").
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

#if !defined(__i386__)
#error "The reconstruction assumes 32-bit pointers; build with -m32."
#endif

typedef unsigned char      undefined;
typedef unsigned char      undefined1;
typedef unsigned short     undefined2;
typedef unsigned int       undefined3;   /* only ever used through CONCAT31 */
typedef unsigned int       undefined4;
typedef unsigned long long undefined5, undefined6, undefined7, undefined8;
typedef unsigned char      byte;
typedef unsigned short     ushort;
typedef unsigned short     word;
typedef unsigned int       uint;
typedef unsigned int       dword;
typedef unsigned long      ulong;
typedef long long          longlong;
typedef unsigned long long ulonglong;
typedef long double        longdouble;
typedef long double        float10;
typedef unsigned char      uchar;
typedef signed char        sbyte;
typedef int                code();       /* unprototyped: used as (code *)(args) */
typedef unsigned int       int3;         /* 3-byte integer piece, only in CONCAT31 */
typedef unsigned int       uint3;        /* 3-byte unsigned piece */
#ifndef __cplusplus
typedef _Bool bool;
#define true 1
#define false 0
#endif

/* Concatenate the high and low parts of a value: CONCATxy(hi, lo) where
 * x and y are the byte sizes of the pieces. */
#define CONCAT11(h,l) ((ushort)(((uint)(uchar)(h) << 8) | (uchar)(l)))
#define CONCAT12(h,l) ((uint)(((uint)(uchar)(h) << 16) | (ushort)(l)))
#define CONCAT13(h,l) ((uint)(((uint)(uchar)(h) << 24) | ((uint)(l) & 0xffffff)))
#define CONCAT14(h,l) ((ulonglong)(((ulonglong)(uchar)(h) << 32) | (uint)(l)))
#define CONCAT15(h,l) ((ulonglong)(((ulonglong)(uchar)(h) << 40) | ((ulonglong)(l) & 0xffffffffffULL)))
#define CONCAT21(h,l) ((uint)(((uint)(ushort)(h) << 8) | (uchar)(l)))
#define CONCAT22(h,l) ((uint)(((uint)(ushort)(h) << 16) | (ushort)(l)))
#define CONCAT26(h,l) ((ulonglong)(((ulonglong)(ushort)(h) << 48) | ((ulonglong)(l) & 0xffffffffffffULL)))
#define CONCAT31(h,l) ((uint)(((uint)(h) << 8) | (uchar)(l)))
#define CONCAT44(h,l) ((ulonglong)(((ulonglong)(uint)(h) << 32) | (uint)(l)))
/* SUBxy(v, n): take y bytes of x-byte value v starting at byte n. */
#define SUB41(v,n) ((uchar)((uint)(v) >> ((n)*8)))
#define SUB42(v,n) ((ushort)((uint)(v) >> ((n)*8)))
#define SUB81(v,n) ((uchar)((ulonglong)(v) >> ((n)*8)))
#define SUB84(v,n) ((uint)((ulonglong)(v) >> ((n)*8)))
#define SUB21(v,n) ((uchar)((ushort)(v) >> ((n)*8)))
#define SUB101(v,n) ((uchar)0) /* x87 internal; inspect assembly if hit */
#define ZEXT14(v) ((uint)(uchar)(v))
#define ZEXT24(v) ((uint)(ushort)(v))
#define ZEXT48(v) ((ulonglong)(uint)(v))
/* CONCAT31(extraout_var, x) where the callee returned a full 32-bit value:
 * the upper bytes are zero. */
#define GHIDRA_ZEXT8(v) ((uint)(uchar)(v))
/* Bit reinterpretations between integer and float types (p-code CASTs that
 * Ghidra prints like value conversions. The operand
 * is first brought to the CAST's source type, then its bytes are copied. */
#define GHIDRA_I2F(x)    ({ unsigned int ghidra_s_ = (unsigned int)(x); float ghidra_d_; \
                            __builtin_memcpy(&ghidra_d_, &ghidra_s_, 4); ghidra_d_; })
#define GHIDRA_L2D(x)    ({ unsigned long long ghidra_s_ = (unsigned long long)(x); double ghidra_d_; \
                            __builtin_memcpy(&ghidra_d_, &ghidra_s_, 8); ghidra_d_; })
#define GHIDRA_F2I(T, x) ({ float ghidra_s_ = (float)(x); T ghidra_d_; \
                            __builtin_memcpy(&ghidra_d_, &ghidra_s_, 4); ghidra_d_; })
/* the same for a float lvalue / into a float lvalue: the bytes are copied in
 * place, never through the x87 unit (which quiets signalling NaNs) */
#define GHIDRA_F2I_LV(T, lv) ({ T ghidra_d_; __builtin_memcpy(&ghidra_d_, &(lv), 4); ghidra_d_; })
#define GHIDRA_STORE_BITS(lv, x) do { unsigned int ghidra_s_ = (unsigned int)(x); \
                            __builtin_memcpy(&(lv), &ghidra_s_, 4); } while (0)
#define GHIDRA_D2L(T, x) ({ double ghidra_s_ = (double)(x); T ghidra_d_; \
                            __builtin_memcpy(&ghidra_d_, &ghidra_s_, 8); ghidra_d_; })
#define SEXT14(v) ((int)(signed char)(v))
#define SEXT24(v) ((int)(short)(v))
#define SEXT48(v) ((longlong)(int)(v))
/* Flag helpers */
#define CARRY1(a,b) ((uchar)((uchar)(a) + (uchar)(b)) < (uchar)(a))
#define CARRY4(a,b) ((uint)((uint)(a) + (uint)(b)) < (uint)(a))
#define SCARRY4(a,b) (((int)(a) > 0 && (int)(b) > 0 && (int)((uint)(a)+(uint)(b)) < 0) || \
                      ((int)(a) < 0 && (int)(b) < 0 && (int)((uint)(a)+(uint)(b)) >= 0))
#define SBORROW4(a,b) ((((int)(a) ^ (int)(b)) & ((int)(a) ^ (int)((uint)(a) - (uint)(b)))) < 0)
#define SBORROW1(a,b) ((((signed char)(a) ^ (signed char)(b)) & ((signed char)(a) ^ (signed char)((a) - (b)))) < 0)
#define GHIDRA_ISNAN(x) ((x) != (x))   /* Ghidra prints NAN(x); renamed by the generator */
#define ABS(x) ((x) < 0 ? -(x) : (x))
/* GCC 2.96 float->int: fnstcw; RC=11 (truncate); fistp; fldcw restore.
 * Verified at 0x80495ee: this is C truncation, i.e. a plain cast. */
#define ROUND(x) ((longlong)(x))
/* fist/fistp into a 32-bit integer (fistl, fistpl;
 * rewrites those ROUND sites to this): with RC = truncate, a value whose
 * truncation does not fit in 32 bits, and NaN, store the x87 "integer
 * indefinite" 0x80000000. (int)(longlong)x would wrap modulo 2^32 instead
 * (experiments T36: 1e10 gave 0x540be400 in the rebuild, 0x80000000 in the
 * original). The 64-bit fistpll sites keep ROUND. */
/* a 32-bit word that holds an int or a float Python Script:
 * copies keep the bits; .i for integer use, .f for float */
typedef union { int i; float f; } ghidra_word32;
static __inline__ int GHIDRA_FIST32(long double x)
{
    return (x > -2147483649.0L && x < 2147483648.0L) ? (int)x : (int)0x80000000u;
}
/* x87 frndint in the rounding mode the original set just before it
 * (tools/round_modes.py); ROUND above is the truncating fist/fistp step. */
#define GHIDRA_FLOOR(x) floorl(x)
#define GHIDRA_CEIL(x)  ceill(x)
#define GHIDRA_TRUNC(x) truncl(x)
#define GHIDRA_RINT(x)  rintl(x)
#define TRUNC(x) ((longlong)(x))

/* Function types named by Ghidra's generic C library archive */
typedef void *__start_routine(void *);
typedef void __func(void);
