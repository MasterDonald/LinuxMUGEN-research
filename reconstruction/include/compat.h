/*
 * compat.h -- low-level helpers used throughout the engine sources.
 *
 * The engine was reconstructed from the 2002.04.14 executable (built by
 * Elecbyte with GCC 2.96 for i386). Some operations of that machine code
 * have no exact counterpart in plain C; they are spelled with the macros
 * and inline functions below so that the compiled program behaves exactly
 * like the original. Each one is explained where it is defined.
 *
 * Integer types are the standard <stdint.h> ones. Where the original code
 * treats a 32-bit word without a clear type, the sources use uint32_t.
 *
 * Do not "simplify" these helpers: each of them fixed a measured
 * difference against the original (RESEARCH-METHODOLOGY.md lists the
 * problem classes and the tests that found them).
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

#if !defined(__i386__)
#error "The engine sources assume 32-bit pointers and the x87 FPU; build with -m32."
#endif

/* The x87 80-bit extended format. GCC 2.96 kept many intermediate values
 * in x87 registers at this precision; variables of this type reproduce that
 * (RESEARCH-METHODOLOGY #32, #41). Kept as a typedef: spelling it as plain
 * `long double` changes GCC's instruction scheduling in places. */
typedef long double float80;

/* An unprototyped function type, for calls through function pointers whose
 * signature varies (callback tables, Allegro driver vtables). */
typedef int generic_fn();
/* Thread start routine and plain callback types (pthread, atexit). */
typedef void *__start_routine(void *);
typedef void __func(void);

#ifndef __cplusplus
typedef _Bool bool;
#define true 1
#define false 0
#endif

/* ---- Combining and splitting integers ------------------------------------
 * CONCATxy(hi, lo): build a value from an x-byte high part and a y-byte low
 * part (the original moved partial registers, e.g. `mov al, ...` into a
 * register whose upper bytes held something else).                        */
#define CONCAT11(h,l) ((uint16_t)(((uint32_t)(uint8_t)(h) << 8) | (uint8_t)(l)))
#define CONCAT12(h,l) ((uint32_t)(((uint32_t)(uint8_t)(h) << 16) | (uint16_t)(l)))
#define CONCAT13(h,l) ((uint32_t)(((uint32_t)(uint8_t)(h) << 24) | ((uint32_t)(l) & 0xffffff)))
#define CONCAT14(h,l) ((uint64_t)(((uint64_t)(uint8_t)(h) << 32) | (uint32_t)(l)))
#define CONCAT15(h,l) ((uint64_t)(((uint64_t)(uint8_t)(h) << 40) | ((uint64_t)(l) & 0xffffffffffULL)))
#define CONCAT21(h,l) ((uint32_t)(((uint32_t)(uint16_t)(h) << 8) | (uint8_t)(l)))
#define CONCAT22(h,l) ((uint32_t)(((uint32_t)(uint16_t)(h) << 16) | (uint16_t)(l)))
#define CONCAT26(h,l) ((uint64_t)(((uint64_t)(uint16_t)(h) << 48) | ((uint64_t)(l) & 0xffffffffffffULL)))
#define CONCAT31(h,l) ((uint32_t)(((uint32_t)(h) << 8) | (uint8_t)(l)))
#define CONCAT44(h,l) ((uint64_t)(((uint64_t)(uint32_t)(h) << 32) | (uint32_t)(l)))
/* SUBxy(v, n): y bytes of the x-byte value v, starting at byte n. */
#define SUB41(v,n) ((uint8_t)((uint32_t)(v) >> ((n)*8)))
#define SUB42(v,n) ((uint16_t)((uint32_t)(v) >> ((n)*8)))
#define SUB81(v,n) ((uint8_t)((uint64_t)(v) >> ((n)*8)))
#define SUB84(v,n) ((uint32_t)((uint64_t)(v) >> ((n)*8)))
#define SUB21(v,n) ((uint8_t)((uint16_t)(v) >> ((n)*8)))
#define SUB101(v,n) ((uint8_t)0) /* x87 register piece; inspect the assembly if hit */
/* Zero and sign extension. ZEXT8 is used where a function returns a byte
 * (e.g. a bool) and the caller reads the whole register: the upper bytes
 * are known to be zero. */
#define ZEXT14(v) ((uint32_t)(uint8_t)(v))
#define ZEXT24(v) ((uint32_t)(uint16_t)(v))
#define ZEXT48(v) ((uint64_t)(uint32_t)(v))
#define ZEXT8(v)  ((uint32_t)(uint8_t)(v))
#define SEXT14(v) ((int)(signed char)(v))
#define SEXT24(v) ((int)(short)(v))
#define SEXT48(v) ((int64_t)(int)(v))

/* ---- Flag computations ----------------------------------------------------
 * The carry / signed-overflow flags the original tested after an add or
 * subtract.                                                               */
#define CARRY1(a,b) ((uint8_t)((uint8_t)(a) + (uint8_t)(b)) < (uint8_t)(a))
#define CARRY4(a,b) ((uint32_t)((uint32_t)(a) + (uint32_t)(b)) < (uint32_t)(a))
#define SCARRY4(a,b) (((int)(a) > 0 && (int)(b) > 0 && (int)((uint32_t)(a)+(uint32_t)(b)) < 0) || \
                      ((int)(a) < 0 && (int)(b) < 0 && (int)((uint32_t)(a)+(uint32_t)(b)) >= 0))
#define SBORROW4(a,b) ((((int)(a) ^ (int)(b)) & ((int)(a) ^ (int)((uint32_t)(a) - (uint32_t)(b)))) < 0)
#define SBORROW1(a,b) ((((signed char)(a) ^ (signed char)(b)) & ((signed char)(a) ^ (signed char)((a) - (b)))) < 0)
#define IS_NAN(x) ((x) != (x))
#define ABS(x) ((x) < 0 ? -(x) : (x))

/* ---- Bit reinterpretation between integers and floats ---------------------
 * The engine often stores floats in int-typed memory (and the reverse).
 * These copy the bytes; they never convert the value.
 *   BITS_I2F(x)        the 32 bits of integer x read as a float
 *   BITS_F2I(T, x)     the 32 bits of float x read as integer type T
 *   BITS_L2D(x)        the 64 bits of integer x read as a double
 *   BITS_D2L(T, x)     the 64 bits of double x read as integer type T
 *   BITS_F2I_LV(T, lv) like BITS_F2I, reading a float variable's bytes in
 *                      place (never through the x87 unit, which would quiet
 *                      a signalling-NaN bit pattern; RESEARCH-METHODOLOGY #37)
 *   STORE_BITS(lv, x)  store the 32 bits of integer x into float variable lv */
#define BITS_I2F(x)    ({ unsigned int _bits_src = (unsigned int)(x); float _bits_dst; \
                          __builtin_memcpy(&_bits_dst, &_bits_src, 4); _bits_dst; })
#define BITS_L2D(x)    ({ unsigned long long _bits_src = (unsigned long long)(x); double _bits_dst; \
                          __builtin_memcpy(&_bits_dst, &_bits_src, 8); _bits_dst; })
#define BITS_F2I(T, x) ({ float _bits_src = (float)(x); T _bits_dst; \
                          __builtin_memcpy(&_bits_dst, &_bits_src, 4); _bits_dst; })
#define BITS_F2I_LV(T, lv) ({ T _bits_dst; __builtin_memcpy(&_bits_dst, &(lv), 4); _bits_dst; })
#define STORE_BITS(lv, x) do { unsigned int _bits_src = (unsigned int)(x); \
                          __builtin_memcpy(&(lv), &_bits_src, 4); } while (0)
#define BITS_D2L(T, x) ({ double _bits_src = (double)(x); T _bits_dst; \
                          __builtin_memcpy(&_bits_dst, &_bits_src, 8); _bits_dst; })

/* A 32-bit word holding either an int or a float: copies keep the bits.
 * Used for the expression evaluator's operands (EvalExpression), which
 * the original tests with integer instructions in the integer branches
 * (RESEARCH-METHODOLOGY #36). */
typedef union { int i; float f; } word32_t;

/* ---- x87 float-to-integer conversions --------------------------------------
 * GCC 2.96 converts with the x87 unit: fnstcw, rounding control = truncate,
 * fist/fistp, fldcw.
 *   X87_FIST32(x)  32-bit store (fistl/fistpl): truncation; a result that
 *                  does not fit, or NaN, gives 0x80000000 ("integer
 *                  indefinite"), never a wrapped value (RESEARCH-METHODOLOGY #35)
 *   X87_FIST64(x)  64-bit store (fistpll): truncation to long long
 * x87 frndint in the rounding mode the original selected just before it:
 *   X87_FLOOR / X87_CEIL / X87_TRUNC (round toward -inf / +inf / zero),
 *   X87_RINT (default mode, round to nearest even).                        */
static __inline__ int X87_FIST32(long double x)
{
    return (x > -2147483649.0L && x < 2147483648.0L) ? (int)x : (int)0x80000000u;
}
#define X87_FIST64(x) ((int64_t)(x))
#define X87_FLOOR(x) floorl(x)
#define X87_CEIL(x)  ceill(x)
#define X87_TRUNC(x) truncl(x)
#define X87_RINT(x)  rintl(x)
