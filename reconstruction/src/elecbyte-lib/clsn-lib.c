/*
 * clsn-lib.c -- collision boxes
 * Collision box arrays (Clsn1 attack and Clsn2 body boxes from .air files),
 * their parsing and the overlap tests with facing used for hits, pushes and
 * reversals.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/clsn-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ClsnArrayNew @ 0x0804e660, 89 bytes
 *
 * Creates a collision box array with room for `capacity` boxes (reference
 * count 1). Returns NULL for a capacity below 1 or on failure.
 *
 * Parameters:
 *   arg1         size_t
 *
 * Calls: ecalloc, ClsnArrayFree
 * Called by: ClsnArrayCopy, ClsnParseLine, EB_GUINewWindow
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnArrayNew(size_t arg1)

{
  uint32_t *mem;
  int mem2;
  
  if ((0 < (int)arg1) && (mem = (uint32_t *)ecalloc(1,0x14), mem != (uint32_t *)0x0)) {
    *mem = 1;
    mem[1] = arg1;
    mem[4] = 1;
    mem2 = ecalloc(arg1,0x14);
    mem[2] = mem2;
    if (mem2 != 0) {
      return mem;
    }
    ClsnArrayFree(mem);
  }
  return 0;
}

/* ClsnArrayFree @ 0x0804e6c0, 57 bytes
 *
 * Decrements a box array's reference count and frees it when it reaches
 * zero. Box arrays are shared by consecutive animation elements.
 *
 * Parameters:
 *   clsn         void *
 *
 * C library: free
 * Called by: AnimRCFree, ClsnArrayNew, ClsnParseLine
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnArrayFree(void *clsn)

{
  uint32_t entry_EAX;
  int i1;
  uint32_t stale_EAX;
  
  if ((clsn != (void *)0x0) &&
     (i1 = *(int *)((int)clsn + 0x10) + -1, *(int *)((int)clsn + 0x10) = i1, i1 < 1))
  {
    if (*(void **)((int)clsn + 8) != (void *)0x0) {
      free(*(void **)((int)clsn + 8));
    }
    free(clsn);
    return stale_EAX;
  }
  return entry_EAX;
}

/* ClsnArrayCopy @ 0x0804e700, 75 bytes
 *
 * Makes an independent copy of a box array. Not called in this build.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ClsnArrayNew
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t * ClsnArrayCopy(uint32_t *arg1)

{
  uint32_t *pu1;
  uint32_t u2;
  uint32_t *pu3;
  uint32_t *pu4;
  
  pu1 = (uint32_t *)ClsnArrayNew(arg1[1]);
  if (pu1 == (uint32_t *)0x0) {
    pu1 = (uint32_t *)0x0;
  }
  else {
    pu1[1] = arg1[1];
    pu1[3] = arg1[3];
    *pu1 = *arg1;
    pu3 = (uint32_t *)arg1[2];
    pu4 = (uint32_t *)pu1[2];
    for (u2 = arg1[1] * 5 & 0x3fffffff; u2 != 0; u2 = u2 - 1) {
      *pu4 = *pu3;
      pu3 = pu3 + 1;
      pu4 = pu4 + 1;
    }
  }
  return pu1;
}

/* ClsnArrayInstance @ 0x0804e750, 12 bytes
 *
 * Adds a reference to a box array (another animation element shares it).
 *
 * Parameters:
 *   clsn         int
 *
 * Called by: AnimRCReadFileTP
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
int ClsnArrayInstance(int clsn)

{
  *(int *)(clsn + 0x10) = *(int *)(clsn + 0x10) + 1;
  return clsn;
}

/* ClsnArrayAdd @ 0x0804e760, 79 bytes
 *
 * Appends a box (5 ints) to a box array if there is room. Returns true on
 * success.
 *
 * Parameters:
 *   clsn         int
 *   box          uint32_t *
 *
 * Called by: ClsnArrayAddRect
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
bool ClsnArrayAdd(int clsn,uint32_t *box)

{
  int i1;
  bool b2;
  int i3;
  
  i3 = *(int *)(clsn + 0xc);
  b2 = i3 < *(int *)(clsn + 4);
  if (b2) {
    i1 = *(int *)(clsn + 8);
    i3 = i3 * 0x14;
    *(uint32_t *)(i1 + i3) = *box;
    *(uint32_t *)(i1 + 4 + i3) = box[1];
    *(uint32_t *)(i1 + 8 + i3) = box[2];
    *(uint32_t *)(i1 + 0xc + i3) = box[3];
    *(uint32_t *)(i1 + 0x10 + i3) = box[4];
    *(int *)(clsn + 0xc) = *(int *)(clsn + 0xc) + 1;
  }
  return b2;
}

/* ClsnArrayAddRect @ 0x0804e7b0, 67 bytes
 *
 * Appends a box with the given type and corners, putting the corners in
 * order.
 *
 * Parameters:
 *   clsn         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: ClsnArrayAdd
 * Called by: ClsnParseLine, EB_GUINewWindow
 *
 * Elecbyte file: src/lib/clsn-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 5
 *       variables), because their address is taken.
 */
void ClsnArrayAddRect(int clsn,uint32_t arg2,uint32_t arg3,uint32_t arg4,
                     uint32_t arg5)

{

  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_2c (*(uint32_t *)(frame + 0x4))
#define stk_28 (*(uint32_t *)(frame + 0x8))
#define stk_24 (*(uint32_t *)(frame + 0xc))
#define stk_20 (*(uint32_t *)(frame + 0x10))
#define stk_1c (*(uint32_t *)(frame + 0x14))
  
  stk_1c = arg5;
  stk_2c = 0;
  stk_28 = arg2;
  stk_24 = arg3;
  stk_20 = arg4;
  ClsnArrayAdd(clsn,&stk_2c);
  return;
}
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20
#undef stk_1c

/* ClsnParseLine @ 0x0804e800, 1016 bytes
 *
 * Parses a "Clsn1: n" / "Clsn2Default: n" header line of an AIR file and the
 * n "Clsn1[i] = x1, y1, x2, y2" lines that follow (read with
 * TPAccessNextLine). Returns the new box array, or NULL on a syntax error.
 *
 * Parameters:
 *   arg1         int
 *   tp           int
 *
 * Calls: ClsnArrayNew, TPAccessNextLine, ClsnArrayFree, strimatchlen,
 *        ClsnArrayAddRect
 * C library: __strtol_internal
 * Called by: AnimRCReadFileTP
 *
 * Elecbyte file: src/lib/clsn-lib.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void * ClsnParseLine(int arg1,int tp)

{
  uint8_t b1;
  uint32_t u2;
  void *clsn;
  int line;
  int i5;
  uint32_t u6;
  char c7;
  uint32_t stk_2c;
  uint32_t stk_28;
  uint32_t stk_24;
  int stk_20;
  
  c7 = '\0';
  stk_20 = 5;
  if (*(char *)(arg1 + 5) != '\0') {
    if (*(char *)(arg1 + 5) == ':') {
      c7 = ':';
    }
    else {
      do {
        stk_20 = stk_20 + 1;
        c7 = *(char *)(stk_20 + arg1);
        if (c7 == '\0') break;
      } while (c7 != ':');
    }
  }
  if (c7 != '\0') {
    do {
      stk_20 = stk_20 + 1;
    } while ((*(uint8_t *)(__ctype_b + 1 + *(char *)(stk_20 + arg1) * 2) & 0x20) != 0);
    if ((*(uint8_t *)(__ctype_b + 1 + *(char *)(stk_20 + arg1) * 2) & 8) != 0) {
      u2 = __strtol_internal((uint8_t *)(arg1 + stk_20),(uint32_t *)0x0,10,0);
      clsn = (void *)ClsnArrayNew(u2);
      if (clsn != (void *)0x0) {
        stk_20 = 0;
        if (*(int *)((int)clsn + 4) < 1) {
          return clsn;
        }
L_0804e930:
        line = TPAccessNextLine(tp);
        if (line == 0) {
L_0804e908:
          ClsnArrayFree(clsn);
        }
        else {
          i5 = strimatchlen(line,(int)&str_clsn,4);
          if (i5 != 0) {
            c7 = *(char *)(line + 5);
            i5 = 5;
            if (c7 != '=') {
              i5 = 5;
              do {
                if (c7 == '\0') goto L_0804e908;
                i5 = i5 + 1;
                c7 = *(char *)(i5 + line);
              } while (c7 != '=');
            }
            while( true ) {
              i5 = i5 + 1;
              c7 = *(char *)(i5 + line);
              if (((uint8_t)(c7 - 0x30U) < 10) || (c7 == '-')) break;
              if (c7 == '\0') goto L_0804e908;
            }
            stk_24 = __strtol_internal((uint8_t *)(i5 + line),(uint32_t *)0x0,10,0);
            c7 = ',';
            b1 = *(uint8_t *)(i5 + line);
            if (b1 != 0x2c) {
              if (b1 == 0) {
                c7 = '\0';
              }
              else {
                do {
                  i5 = i5 + 1;
                  c7 = *(char *)(i5 + line);
                  if (c7 == ',') break;
                } while (c7 != '\0');
              }
            }
            do {
              if (((uint8_t)(c7 - 0x30U) < 10) || (c7 == '-')) goto L_0804e9ec;
              if (c7 == '\0') goto L_0804e908;
              i5 = i5 + 1;
              c7 = *(char *)(i5 + line);
            } while( true );
          }
        }
      }
    }
  }
  return (void *)0x0;
L_0804e9ec:
  stk_28 = __strtol_internal((uint8_t *)(i5 + line),(uint32_t *)0x0,10,0);
  c7 = ',';
  b1 = *(uint8_t *)(i5 + line);
  if (b1 != 0x2c) {
    if (b1 == 0) {
      c7 = '\0';
    }
    else {
      do {
        i5 = i5 + 1;
        c7 = *(char *)(i5 + line);
        if (c7 == ',') break;
      } while (c7 != '\0');
    }
  }
  do {
    if (((uint8_t)(c7 - 0x30U) < 10) || (c7 == '-')) break;
    if (c7 == '\0') goto L_0804e908;
    i5 = i5 + 1;
    c7 = *(char *)(i5 + line);
  } while( true );
  u2 = __strtol_internal((uint8_t *)(i5 + line),(uint32_t *)0x0,10,0);
  c7 = ',';
  b1 = *(uint8_t *)(i5 + line);
  if (b1 != 0x2c) {
    if (b1 == 0) {
      c7 = '\0';
    }
    else {
      do {
        i5 = i5 + 1;
        c7 = *(char *)(i5 + line);
        if (c7 == ',') break;
      } while (c7 != '\0');
    }
  }
  do {
    if (((uint8_t)(c7 - 0x30U) < 10) || (c7 == '-')) break;
    if (c7 == '\0') goto L_0804e908;
    i5 = i5 + 1;
    c7 = *(char *)(i5 + line);
  } while( true );
  u6 = __strtol_internal((uint8_t *)(i5 + line),(uint32_t *)0x0,10,0);
  stk_2c = u2;
  if ((int)u2 < (int)stk_24) {
    stk_2c = stk_24;
    stk_24 = u2;
  }
  u2 = u6;
  if ((int)u6 < (int)stk_28) {
    u2 = stk_28;
    stk_28 = u6;
  }
  if ((BITS_I2F(clsnxscale) != 1.0) || (BITS_I2F(clsnyscale) != 1.0)) {
    u2 = (uint32_t)X87_FIST32((float80)(int)u2 * BITS_I2F(clsnyscale));
    stk_2c = (uint32_t)X87_FIST32((float80)(int)stk_2c * BITS_I2F(clsnxscale));
    stk_28 = (uint32_t)X87_FIST32((float80)(int)stk_28 * BITS_I2F(clsnyscale));
    stk_24 = (uint32_t)X87_FIST32((float80)(int)stk_24 * BITS_I2F(clsnxscale));
  }
  ClsnArrayAddRect((int)clsn,stk_24,stk_28,stk_2c,u2);
  stk_20 = stk_20 + 1;
  if (*(int *)((int)clsn + 4) <= stk_20) {
    return clsn;
  }
  goto L_0804e930;
}

/* ClsnMixDetectRectIndiv @ 0x0804ec00, 124 bytes
 *
 * Tests whether one box overlaps any box of another array, both at given
 * offsets. Returns the index of the first hit, or -1. Used by the debug GUI
 * to find the window under the mouse.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: DetermineFocus
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnMixDetectRectIndiv(int arg1,int arg2,int arg3,int arg4)

{
  int i1;
  bool b2;
  int i2;
  int i4;
  
  i2 = 0;
  if (0 < *(int *)(arg2 + 4)) {
    i4 = 0;
    do {
      b2 = false;
      i1 = *(int *)(arg2 + 8) + i4;
      if ((((*(int *)(arg1 + 4) <= arg3 + *(int *)(i1 + 0xc)) &&
           (arg3 + *(int *)(i1 + 4) <= *(int *)(arg1 + 0xc))) &&
          (*(int *)(arg1 + 8) <= arg4 + *(int *)(i1 + 0x10))) &&
         (arg4 + *(int *)(i1 + 8) <= *(int *)(arg1 + 0x10))) {
        b2 = true;
      }
      if (b2) {
        return i2;
      }
      i2 = i2 + 1;
      i4 = i4 + 0x14;
    } while (i2 < *(int *)(arg2 + 4));
  }
  return 0xffffffff;
}

/* ClsnMixDetectRect @ 0x0804ec80, 126 bytes
 *
 * Returns nonzero if box `a` overlaps any box of array `b` placed at offset
 * (x, y).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: ClsnArrayDetectRect
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnMixDetectRect(int arg1,int arg2,int arg3,int arg4)

{
  int i1;
  bool b2;
  int i2;
  int i4;
  
  i2 = 0;
  if (0 < *(int *)(arg2 + 4)) {
    i4 = 0;
    do {
      b2 = false;
      i1 = *(int *)(arg2 + 8) + i4;
      if ((((*(int *)(arg1 + 4) <= arg3 + *(int *)(i1 + 0xc)) &&
           (arg3 + *(int *)(i1 + 4) <= *(int *)(arg1 + 0xc))) &&
          (*(int *)(arg1 + 8) <= arg4 + *(int *)(i1 + 0x10))) &&
         (arg4 + *(int *)(i1 + 8) <= *(int *)(arg1 + 0x10))) {
        b2 = true;
      }
      if (b2) {
        return 1;
      }
      i2 = i2 + 1;
      i4 = i4 + 0x14;
    } while (i2 < *(int *)(arg2 + 4));
  }
  return 0;
}

/* ClsnMixDetectRectHFlip1 @ 0x0804ed00, 158 bytes
 *
 * ClsnMixDetectRect with box `a` mirrored horizontally (x1/x2 negated).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: ClsnArrayDetectRectFlip
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnMixDetectRectHFlip1(int arg1,int arg2,int arg3,int arg4)

{
  bool b1;
  int i2;
  int i3;
  int stk_1c;
  
  i3 = 0;
  if (0 < *(int *)(arg2 + 4)) {
    stk_1c = 0;
    do {
      i2 = stk_1c + *(int *)(arg2 + 8);
      b1 = false;
      if ((((-*(int *)(arg1 + 0xc) <= arg3 + *(int *)(i2 + 0xc)) &&
           (arg3 + *(int *)(i2 + 4) <= -*(int *)(arg1 + 4))) &&
          (*(int *)(arg1 + 8) <= arg4 + *(int *)(i2 + 0x10))) &&
         (arg4 + *(int *)(i2 + 8) <= *(int *)(arg1 + 0x10))) {
        b1 = true;
      }
      if (b1) {
        return 1;
      }
      i3 = i3 + 1;
      stk_1c = stk_1c + 0x14;
    } while (i3 < *(int *)(arg2 + 4));
  }
  return 0;
}

/* ClsnMixDetectRectHFlipAll @ 0x0804eda0, 158 bytes
 *
 * ClsnMixDetectRect with every box of array `b` mirrored horizontally.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: ClsnArrayDetectRectFlip
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnMixDetectRectHFlipAll(int arg1,int arg2,int arg3,int arg4)

{
  bool b1;
  int i2;
  int i3;
  int stk_1c;
  
  i3 = 0;
  if (0 < *(int *)(arg2 + 4)) {
    stk_1c = 0;
    do {
      i2 = stk_1c + *(int *)(arg2 + 8);
      b1 = false;
      if ((((-*(int *)(arg1 + 0xc) <= arg3 - *(int *)(i2 + 4)) &&
           (arg3 - *(int *)(i2 + 0xc) <= -*(int *)(arg1 + 4))) &&
          (*(int *)(arg1 + 8) <= arg4 + *(int *)(i2 + 0x10))) &&
         (arg4 + *(int *)(i2 + 8) <= *(int *)(arg1 + 0x10))) {
        b1 = true;
      }
      if (b1) {
        return 1;
      }
      i3 = i3 + 1;
      stk_1c = stk_1c + 0x14;
    } while (i3 < *(int *)(arg2 + 4));
  }
  return 0;
}

/* ClsnArrayDetectRect @ 0x0804ee40, 114 bytes
 *
 * Returns nonzero if any box of array `a` overlaps any box of array `b`
 * placed at offset (x, y).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *
 * Calls: ClsnMixDetectRect
 * Called by: ClsnArrayDetectRectFlip
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnArrayDetectRect(int *arg1,int *arg2,int arg3,int arg4)

{
  int i1;
  int i2;
  int i3;
  
  if ((((arg1 != (int *)0x0) && (arg2 != (int *)0x0)) && (*arg1 != 0)) &&
     ((*arg2 != 0 && (i2 = 0, 0 < arg1[1])))) {
    i3 = 0;
    do {
      i1 = ClsnMixDetectRect(i3 + arg1[2],(int)arg2,arg3,arg4);
      if (i1 != 0) {
        return 1;
      }
      i2 = i2 + 1;
      i3 = i3 + 0x14;
    } while (i2 < arg1[1]);
  }
  return 0;
}

/* ClsnArrayDetectRectFlip @ 0x0804eec0, 365 bytes
 *
 * Collision test between two box arrays with facing: `flip_a` and `flip_b`
 * say which array is mirrored horizontally (a player facing left). Returns
 * nonzero on any overlap. This is the test behind hits, pushes, reversals
 * and projectile contact.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *
 * Calls: ClsnArrayDetectRect, ClsnMixDetectRectHFlip1,
 *        ClsnMixDetectRectHFlipAll
 * Called by: AIAttackInRange, CheckProjHitProj, PlayerCheckHit,
 *            PlayerCheckHitProj, PlayerCheckProjHit, PlayerCheckReversal,
 *            PlayerPushCheck, ProjClsnDetect
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t
ClsnArrayDetectRectFlip(int *arg1,int *arg2,int arg3,int arg4,int arg5,int arg6)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  
  if ((((arg1 != (int *)0x0) && (arg2 != (int *)0x0)) && (*arg1 != 0)) && (*arg2 != 0))
  {
    if ((arg5 == 0) && (arg6 == 0)) {
      u1 = ClsnArrayDetectRect(arg1,arg2,arg3,arg4);
      return u1;
    }
    if (((arg5 == 1) && (arg6 == 0)) && (i3 = 0, 0 < arg1[1])) {
      i4 = 0;
      do {
        i2 = ClsnMixDetectRectHFlip1(i4 + arg1[2],(int)arg2,arg3,arg4);
        if (i2 != 0) {
          return 1;
        }
        i3 = i3 + 1;
        i4 = i4 + 0x14;
      } while (i3 < arg1[1]);
    }
    if (((arg5 == 0) && (arg6 == 1)) && (i3 = 0, 0 < arg2[1])) {
      i4 = 0;
      do {
        i2 = ClsnMixDetectRectHFlip1(i4 + arg2[2],(int)arg1,-arg3,-arg4);
        if (i2 != 0) {
          return 1;
        }
        i3 = i3 + 1;
        i4 = i4 + 0x14;
      } while (i3 < arg2[1]);
    }
    if (((arg5 == 1) && (arg6 == 1)) && (i3 = 0, 0 < arg1[1])) {
      i4 = 0;
      do {
        i2 = ClsnMixDetectRectHFlipAll(i4 + arg1[2],(int)arg2,arg3,arg4);
        if (i2 != 0) {
          return 1;
        }
        i3 = i3 + 1;
        i4 = i4 + 0x14;
      } while (i3 < arg1[1]);
    }
  }
  return 0;
}

/* ClsnDetectRect @ 0x0804f030, 74 bytes
 *
 * Returns nonzero if two single boxes overlap (the second at offset (x, y)).
 * Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnDetectRect(int arg1,int arg2,int arg3,int arg4)

{
  uint32_t u1;
  
  u1 = 0;
  if ((((*(int *)(arg1 + 4) <= arg3 + *(int *)(arg2 + 0xc)) &&
       (arg3 + *(int *)(arg2 + 4) <= *(int *)(arg1 + 0xc))) &&
      (*(int *)(arg1 + 8) <= arg4 + *(int *)(arg2 + 0x10))) &&
     (arg4 + *(int *)(arg2 + 8) <= *(int *)(arg1 + 0x10))) {
    u1 = 1;
  }
  return u1;
}

/* ClsnDetectRectHFlip1 @ 0x0804f080, 86 bytes
 *
 * ClsnDetectRect with the first box mirrored. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnDetectRectHFlip1(int arg1,int arg2,int arg3,int arg4)

{
  uint32_t u1;
  
  u1 = 0;
  if ((((-*(int *)(arg1 + 0xc) <= arg3 + *(int *)(arg2 + 0xc)) &&
       (arg3 + *(int *)(arg2 + 4) <= -*(int *)(arg1 + 4))) &&
      (*(int *)(arg1 + 8) <= arg4 + *(int *)(arg2 + 0x10))) &&
     (arg4 + *(int *)(arg2 + 8) <= *(int *)(arg1 + 0x10))) {
    u1 = 1;
  }
  return u1;
}

/* ClsnDetectRectHFlipAll @ 0x0804f0e0, 86 bytes
 *
 * ClsnDetectRect with the second box mirrored. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Elecbyte file: src/lib/clsn-lib.c
 */
uint32_t ClsnDetectRectHFlipAll(int arg1,int arg2,int arg3,int arg4)

{
  uint32_t u1;
  
  u1 = 0;
  if ((((-*(int *)(arg1 + 0xc) <= arg3 - *(int *)(arg2 + 4)) &&
       (arg3 - *(int *)(arg2 + 0xc) <= -*(int *)(arg1 + 4))) &&
      (*(int *)(arg1 + 8) <= arg4 + *(int *)(arg2 + 0x10))) &&
     (arg4 + *(int *)(arg2 + 8) <= *(int *)(arg1 + 0x10))) {
    u1 = 1;
  }
  return u1;
}

