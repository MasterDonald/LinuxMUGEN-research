/*
 * anim-lib.c -- animations, sprite drawing dispatch, priority sprite list
 * Loads .air animation files into AnimRC tables, plays animation instances
 * (actions, elements, looping, collision boxes per element), and draws their
 * sprites with flip, scale, rotation and blending. Holds the priority sprite
 * list that sorts sprite draws by sprpriority, and persistent stand-alone
 * animations.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/anim-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* AnimRCReadFile @ 0x08048200, 133 bytes
 *
 * Loads an .air file: parses it with the text parser, then builds the AnimRC
 * (AnimRCReadFileTP). On failure, ErrorMessage holds "TXTPARSE error opening
 * <file>" or "Anim error reading <file>" and NULL is returned.
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: TPReadFile, AnimRCReadFileTP, TPFree
 * C library: strcat
 * Called by: GameLoadFightData, PlayerDefLoadPtr
 * Messages:
 *   "\nTXTPARSE error opening "
 *   "\nAnim error reading "
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int * AnimRCReadFile(char *filename)

{
  uint32_t *tp;
  int *animrc;
  
  tp = TPReadFile(filename);
  if (tp == (uint32_t *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,filename);
    animrc = (int *)0x0;
  }
  else {
    animrc = AnimRCReadFileTP((int)tp);
    if (animrc == (int *)0x0) {
      strcat((char *)ErrorMessage,"\nAnim error reading ");
      strcat((char *)ErrorMessage,filename);
    }
    TPFree(tp);
  }
  return animrc;
}

/* AnimRCReadFileTP @ 0x08048290, 1428 bytes
 *
 * Builds an AnimRC from a parsed .air file. It counts the "[Begin Action n]"
 * groups (at least one is required: "Need at least one action"), creates the
 * action array and reads each group line by line. Lines handled:
 * - element lines ("group, image, x, y, time, flip, blend"), parsed by
 * AnimElemParseLine;
 * - "Loopstart", which marks the element the action loops back to;
 * - "Clsn1[n] = ..." / "Clsn2[n] = ..." boxes and their
 * "Clsn1Default:"/"Clsn2Default:" forms (ClsnParseLine), attached to the
 * following elements.
 *
 * It then computes each element's start tick, the action's loop time and
 * loop start time. Errors such as "Error reading line in %s elem %i" or
 * "Error in clsn1 in %s elem %i" go to ErrorMessage. Returns the AnimRC or
 * NULL.
 *
 * Parameters:
 *   tp           int
 *
 * Calls: ecalloc, TPGroupMatchCount, ArrayNew, TPGroupScanFirst,
 *        strimatch, TPGroupScanNext, TPAccessFirstLine, TPAccessNextLine,
 *        TPAccessReset, strimatchlen, ClsnParseLine, ClsnArrayInstance,
 *        AnimElemParseLine, ArrayAdd, AnimRCFree
 * C library: sprintf, __strtol_internal
 * Called by: AnimRCReadFile, BGArrayReadTP, GameLoadFightData,
 *            GameLoadSystem, PlayerDefLoadZip, SiSceneReadTP
 * Messages:
 *   "begin action "
 *   "Need at least one action"
 *   "Out of memory."
 *   "Error reading line in %s elem %i"
 *   "Error in clsn1 in %s elem %i"
 *   "Error in clsn2 in %s elem %i"
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 3 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       15 variables), because their address is taken.
 */
int * AnimRCReadFileTP(int tp)

{
  bool b1;
  int *mem;
  int count;
  uint32_t *array;
  int i5;
  uint32_t u6;
  char *line;
  uint32_t stale_var;
  int i2;
  char c9;
  int *pi10;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define clsn (*(void **)(frame + 0x4))
#define clsn2 (*(void **)(frame + 0x8))
#define stk_74 (*(int *)(frame + 0xc))
#define stk_6c (*(int *)(frame + 0x14))
#define stk_68 (*(int *)(frame + 0x18))
#define stk_54 (*(uint32_t *)(frame + 0x2c))
#define stk_4c (*(uint32_t *)(frame + 0x34))
#define stk_48 (*(uint32_t *)(frame + 0x38))
#define stk_44 (*(void **)(frame + 0x3c))
#define stk_40 (*(void **)(frame + 0x40))
#define array2 (*(uint32_t **)(frame + 0x44))
#define stk_38 (*(size_t *)(frame + 0x48))
#define stk_34 (*(int *)(frame + 0x4c))
#define stk_30 (*(int *)(frame + 0x50))
#define stk_2c (*(int *)(frame + 0x54))
  
  mem = (int *)ecalloc(1,8);
  if (mem != (int *)0x0) {
    count = TPGroupMatchCount(tp,"begin action ");
    mem[1] = count;
    if (count < 1) {
      sprintf((char *)ErrorMessage,"Need at least one action");
    }
    else {
      array = ArrayNew(mem[1],0x14,0);
      *mem = (int)array;
      if (array == (uint32_t *)0x0) {
        sprintf((char *)ErrorMessage,"Out of memory.",mem,mem);
      }
      else {
        count = TPGroupScanFirst(tp);
        stk_74 = 0;
        while( true ) {
          if (mem[1] <= stk_74) {
            return mem;
          }
          array2 = (uint32_t *)0x0;
          stk_38 = 0;
          stk_34 = 0;
          stk_30 = 0;
          stk_2c = 0;
          while (i5 = strimatch((char *)(count + 1),"begin action "), i5 == 0) {
            count = TPGroupScanNext(tp);
          }
          u6 = __strtol_internal((uint8_t *)(count + 0xe),(uint32_t *)0x0,10,0);
          stk_30 = 0;
          stk_2c = 0;
          stk_38 = 0;
          line = (char *)TPAccessFirstLine(tp);
          while (line != (char *)0x0) {
            c9 = *line;
            if (((uint8_t)(c9 - 0x30U) < 10) || (c9 == '-')) {
              stk_38 = stk_38 + 1;
              c9 = *line;
            }
            if (((c9 == 'L') || (c9 == 'l')) && ((uint8_t)(line[1] - 0x30U) < 10)) {
              stk_38 = stk_38 + 1;
            }
            line = (char *)TPAccessNextLine(tp);
          }
          TPAccessReset(tp);
          array2 = ArrayNew(stk_38,0x30,0);
          if (array2 == (uint32_t *)0x0) break;
          stk_34 = 0;
          clsn2 = (void *)0x0;
          clsn = (void *)0x0;
          if (0 < (int)stk_38) {
            i5 = 0;
            do {
              b1 = false;
              pi10 = &stk_6c;
              for (i2 = 0xc; i2 != 0; i2 = i2 + -1) {
                *pi10 = 0;
                pi10 = pi10 + 1;
              }
              stk_4c = 0x100;
              stk_48 = 0;
              do {
                line = (char *)TPAccessNextLine(tp);
                if (line == (char *)0x0) {
                  sprintf((char *)ErrorMessage,"Error reading line in %s elem %i",count,i5 + 1);
                  goto L_08048408;
                }
                i2 = strimatchlen((int)line,(int)&str_loopstart_6a34,9);
                if (i2 != 0) {
                  b1 = true;
                }
                i2 = strimatchlen((int)line,(int)&str_clsn1_6a3e,5);
                if (i2 != 0) {
                  stk_44 = ClsnParseLine((int)line,tp);
                  if (stk_44 == (void *)0x0) {
                    sprintf((char *)ErrorMessage,"Error in clsn1 in %s elem %i",count,i5);
                    goto L_08048408;
                  }
                  if ((line[5] == 'd') || (line[5] == 'D')) {
                    stk_54 = stk_54 | 4;
                    clsn2 = stk_44;
                  }
                }
                i2 = strimatchlen((int)line,(int)&str_clsn2_6a61,5);
                if (i2 != 0) {
                  stk_40 = ClsnParseLine((int)line,tp);
                  if (stk_40 == (void *)0x0) {
                    sprintf((char *)ErrorMessage,"Error in clsn2 in %s elem %i",count,i5);
                    goto L_08048408;
                  }
                  if ((line[5] == 'd') || (line[5] == 'D')) {
                    stk_54 = stk_54 | 8;
                    clsn = stk_40;
                  }
                }
                c9 = *line;
              } while ((((c9 != 'L') && (c9 != 'l')) || (9 < (uint8_t)(line[1] - 0x30U))) &&
                      ((9 < (uint8_t)(c9 - 0x30U) && (c9 != '-'))));
              if ((clsn2 != (void *)0x0) &&
                 ((stk_44 == (void *)0x0 &&
                  (stk_44 = (void *)ClsnArrayInstance((int)clsn2), stk_44 == (void *)0x0))))
              {
                sprintf((char *)ErrorMessage,"Internal lib error in %s elem %i",count,i5);
                goto L_08048408;
              }
              if (((clsn != (void *)0x0) && (stk_40 == (void *)0x0)) &&
                 (stk_40 = (void *)ClsnArrayInstance((int)clsn), stk_40 == (void *)0x0)) {
                sprintf((char *)ErrorMessage,"Internal lib error in %s elem %i",count,i5);
                goto L_08048408;
              }
              if (i5 == 0) {
                stk_6c = 0;
              }
              else {
                pi10 = (int *)((i5 + -1) * array2[1] + array2[5]);
                stk_6c = pi10[1] + *pi10;
              }
              if (b1) {
                stk_30 = stk_6c;
                stk_2c = i5;
              }
              i2 = 0;
              c9 = *line;
              while ((9 < (uint8_t)(c9 - 0x30U) && (c9 != '-'))) {
                if (c9 == '\0') {
                  sprintf((char *)ErrorMessage,"Syntax error in %s elem %i",count,i5 + 1);
                  goto L_08048408;
                }
                i2 = i2 + 1;
                c9 = line[i2];
              }
              b1 = AnimElemParseLine(line + i2,(int)&stk_6c,count,i5);
              if (ZEXT8(b1) == 0) goto L_08048408;
              if (stk_68 == -1) {
                stk_34 = stk_68;
              }
              else {
                stk_34 = stk_34 + stk_68;
              }
              i2 = i5 + 1;
              ArrayAdd((int)array2,&stk_6c,0,i5);
              i5 = i2;
            } while (i2 < (int)stk_38);
          }
          if (stk_2c == -1) {
            stk_2c = 0;
          }
          ArrayAdd(*mem,&array2,0,u6);
          count = TPGroupScanNext(tp);
          stk_74 = stk_74 + 1;
        }
        sprintf((char *)ErrorMessage,"Out of memory.",0,0);
      }
    }
L_08048408:
    AnimRCFree(mem);
  }
  return (int *)0x0;
}
#undef clsn
#undef clsn2
#undef stk_74
#undef stk_6c
#undef stk_68
#undef stk_54
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef array2
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c

/* AnimElemParseLine @ 0x08048830, 383 bytes
 *
 * Parses one AIR element line: sprite group, sprite image, x and y offset,
 * duration (ticks, -1 = forever), optional flip ("H", "V", "HV") and
 * optional blend ("A", "A1", "S", "AS<n>D<m>"). Fewer than five fields is an
 * error: "Too few arguments on element %i of %s".
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *
 * Calls: AnimElemProcessFlipFlags, AnimElemProcessDrawFlags
 * C library: __strtol_internal, sprintf
 * Called by: AnimRCReadFileTP
 * Messages:
 *   "Too few arguments on element %i of %s:\n%s (%i)"
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 1 call results that the caller reads as stale_EAX assigned explicitly
 */
bool AnimElemParseLine(char *arg1,int arg2,uint32_t arg3,int arg4)

{
  uint8_t b1;
  char c2;
  uint32_t u3;
  uint32_t stale_EAX;
  int i4;
  int stk_14;
  
  i4 = 0;
  stk_14 = 0;
  if (*arg1 != '\0') {
    while( true ) {
      b1 = *(uint8_t *)(__ctype_b + 1 + arg1[i4] * 2);
      while ((b1 & 0x20) != 0) {
        i4 = i4 + 1;
        b1 = *(uint8_t *)(__ctype_b + 1 + arg1[i4] * 2);
      }
      c2 = arg1[i4];
      if (c2 == '\0') break;
      switch(stk_14) {
      case 0:
        u3 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 8) = u3;
        break;
      case 1:
        u3 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 0xc) = u3;
        break;
      case 2:
        u3 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 0x10) = u3;
        break;
      case 3:
        u3 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 0x14) = u3;
        break;
      case 4:
        u3 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 4) = u3;
        break;
      case 5:
        u3 = AnimElemProcessFlipFlags(arg1 + i4);
        *(uint32_t *)(arg2 + 0x18) = *(uint32_t *)(arg2 + 0x18) | u3;
        break;
      case 6:
        stale_EAX = AnimElemProcessDrawFlags(arg1 + i4,(uint32_t *)(arg2 + 0x20),(uint32_t *)(arg2 + 0x24));
        *(uint32_t *)(arg2 + 0x1c) = stale_EAX;
        break;
      default:
        goto L_default_08048889;
      }
      c2 = arg1[i4];
L_default_08048889:
      stk_14 = stk_14 + 1;
      while ((c2 != ',' && (c2 != '\0'))) {
        i4 = i4 + 1;
        c2 = arg1[i4];
      }
      if ((c2 == '\0') || (i4 = i4 + 1, arg1[i4] == '\0')) break;
    }
  }
  if (4 >= stk_14) {
    sprintf((char *)ErrorMessage,"Too few arguments on element %i of %s:\n%s (%i)",arg4 + 1,
            arg3,arg1,stk_14,i4,i4);
  }
  return 4 < stk_14;
}

/* AnimElemProcessFlipFlags @ 0x080489b0, 76 bytes
 *
 * Parses the flip field of an AIR element: 'H' sets bit 0 (horizontal), 'V'
 * bit 1 (vertical), case-insensitive, up to the next comma.
 *
 * Parameters:
 *   arg1         char *
 *
 * Called by: AnimElemParseLine
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimElemProcessFlipFlags(char *arg1)

{
  char c1;
  int i2;
  uint32_t u3;
  int i4;
  
  u3 = 0;
  i4 = 0;
  c1 = *arg1;
  while ((c1 != '\0' && (c1 != ','))) {
    i2 = *(int *)(__ctype_tolower + arg1[i4] * 4);
    if (i2 == 0x68) {
      u3 = u3 | 1;
    }
    else if (i2 == 0x76) {
      u3 = u3 | 2;
    }
    i4 = i4 + 1;
    c1 = arg1[i4];
  }
  return u3;
}

/* AnimElemProcessDrawFlags @ 0x08048a00, 309 bytes
 *
 * Parses the blend field of an AIR element and returns the blend mode,
 * storing the source and destination alpha:
 * - "A": additive, 256/256;
 * - "A1": additive with half destination, 256/128;
 * - "S": subtractive;
 * - "AS<n>D<m>": additive with explicit source and destination alpha.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t *
 *   arg3         uint32_t *
 *
 * C library: __strtol_internal
 * Called by: AnimElemParseLine
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: Ghidra output of 0x08048a00-0x08048b35 with the return values restored.
 *       Reason: Ghidra merged three return paths with a stack temporary and
 *       printed "return in_stack_ffffffec"; the subtractive-transparency flag
 *       "S" was therefore lost and no sprite was drawn with subtraction (found
 *       by the call-count comparison: W_PutSpriteTransSub* 50 calls vs 0).
 *       VERIFIED return values: empty string and no 'a'/'s' found -> 0
 *       (0x08048b2b xor %eax,%eax); 's' -> 2 (0x08048b16 mov $0x2,%eax); "a1" ->
 *       3; "a" not followed by 's' -> 1; "as<n>d<m>" -> 3 (0x8(%esp)). Draw
 *       flags: 1 = add, 2 = subtract, 3 = add with source/destination alpha
 *       (arg2 = source, arg3 = destination, 0..256).
 */
uint32_t AnimElemProcessDrawFlags(char *arg1,uint32_t *arg2,uint32_t *arg3)
{
  uint8_t b1;
  uint32_t u2;
  int i3;
  int i4;
  int i5;

  i4 = 0;
  if (*arg1 == '\0') {
    return 0;
  }
  while (i5 = *(int *)(__ctype_tolower + arg1[i4] * 4), i5 != 0x61) {
    if (i5 == 0x73) {
      return 2;
    }
    i4 = i4 + 1;
    if (arg1[i4] == '\0') {
      return 0;
    }
  }
  if (arg1[i4 + 1] == '1') {
    *arg2 = 0x100;
    *arg3 = 0x80;
    return 3;
  }
  if (*(int *)(__ctype_tolower + arg1[i4 + 1] * 4) != 0x73) {
    return 1;
  }
  i4 = i4 + 2;
  i5 = (int)arg1[i4];
  i3 = __ctype_tolower;
  if ((*(uint8_t *)(__ctype_b + 1 + i5 * 2) & 8) != 0) {
    u2 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
    i3 = __ctype_tolower;
    *arg2 = u2;
    i5 = (int)arg1[i4];
  }
  if (arg1[i4] != '\0') {
    b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    while ((b1 & 8) != 0) {
      i4 = i4 + 1;
      if (arg1[i4] == '\0') {
        i5 = 0;
        break;
      }
      i5 = (int)arg1[i4];
      b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    }
  }
  if ((*(int *)(i3 + i5 * 4) == 100) &&
     ((*(uint8_t *)(__ctype_b + 1 + arg1[i4 + 1] * 2) & 8) != 0)) {
    u2 = __strtol_internal((uint8_t *)(arg1 + i4 + 1),(uint32_t *)0x0,10,0);
    *arg3 = u2;
  }
  return 3;
}

/* AnimRCFree @ 0x08048b40, 168 bytes
 *
 * Frees an AnimRC: every action's element array and collision box arrays,
 * then the action array.
 *
 * Parameters:
 *   animrc       int *
 *
 * Calls: ArrayScanFirst, ClsnArrayFree, ArrayScanNext, ArrayFree
 * C library: free
 * Called by: AnimRCReadFileTP, BGArrayFree, GameFreeFightData,
 *            GameUnloadSystem, PlayerRCFree, SiSceneFree
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimRCFree(int *animrc)

{
  void *array;
  uint32_t entry_EAX;
  int item;
  uint32_t stale_EAX;
  int i3;
  int i4;
  
  if (animrc == (int *)0x0) {
    return entry_EAX;
  }
  item = *animrc;
  if (item != 0) {
    i4 = 0;
    i3 = animrc[1];
    if (0 < i3) {
      while( true ) {
        array = *(void **)(i4 * *(int *)(item + 4) + *(int *)(item + 0x14));
        if (array != (void *)0x0) {
          item = ArrayScanFirst((int)array);
          while (item != 0) {
            ClsnArrayFree(*(void **)(item + 0x28));
            ClsnArrayFree(*(void **)(item + 0x2c));
            item = ArrayScanNext((int)array);
          }
          ArrayFree(array);
          i3 = animrc[1];
        }
        i4 = i4 + 1;
        if (i3 <= i4) break;
        item = *animrc;
      }
    }
    ArrayFree((void *)*animrc);
  }
  free(animrc);
  return stale_EAX;
}

/* AnimNew @ 0x08048bf0, 72 bytes
 *
 * Creates an animation instance for an AnimRC, drawing from a sprite array.
 * The blend override [8] starts at -1 (use each element's own blend) and the
 * alpha at 256/256 (opaque).
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *
 * Calls: ecalloc
 * Called by: BGArrayAddAnim, ExplodArrayNew, PlayerNew, SiSceneReadTP
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t * AnimNew(uint32_t arg1,uint32_t arg2)

{
  uint32_t *mem;
  
  mem = (uint32_t *)ecalloc(1,0x38);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    *mem = arg1;
    mem[1] = arg2;
    mem[8] = 0xffffffff;
    mem[9] = 0x100;
    mem[10] = 0x100;
  }
  return mem;
}

/* AnimSet @ 0x08048c40, 36 bytes
 *
 * Reinitialises an animation instance in place (all fields zeroed) for a new
 * AnimRC and sprite array.
 *
 * Parameters:
 *   anim         uint32_t *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Called by: AnimPerArrayAdd
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimSet(uint32_t *anim,uint32_t arg2,uint32_t arg3)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = anim;
  for (i1 = 0xe; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  *anim = arg2;
  anim[1] = arg3;
  return;
}

/* AnimCopy @ 0x08048c70, 21 bytes
 *
 * Copies a whole animation instance (used when a projectile inherits its
 * owner's animation).
 *
 * Parameters:
 *   anim         uint32_t *
 *   src          uint32_t *
 *
 * Called by: ProjArrayAdd
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimCopy(uint32_t *anim,uint32_t *src)

{
  int i1;
  
  for (i1 = 0xe; i1 != 0; i1 = i1 + -1) {
    *anim = *src;
    src = src + 1;
    anim = anim + 1;
  }
  return;
}

/* AnimFree @ 0x08048c90, 52 bytes
 *
 * Frees an animation instance. The sprite array is freed too when the
 * instance owns it (field [2] set).
 *
 * Parameters:
 *   anim         void *
 *
 * Calls: SpriteArrayFree
 * C library: free
 * Called by: BGArrayFree, ExplodArrayFree, PlayerFree, SiSceneFree
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimFree(void *anim)

{
  uint32_t stale_EAX;
  uint32_t entry_ECX;
  
  if (anim != (void *)0x0) {
    if (*(int *)((int)anim + 8) != 0) {
      SpriteArrayFree(*(int **)((int)anim + 4));
    }
    free(anim);
    return stale_EAX;
  }
  return entry_ECX;
}

/* AnimUpdate @ 0x08048cd0, 156 bytes
 *
 * Advances the animation by one tick. When the action time passes the loop
 * time, it wraps to the loop start (and returns 1 to report the loop). It
 * then selects the element for the current time (AnimUpdateElemptr) and
 * looks up its sprite in the sprite array, caching the index for drawing.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Calls: AnimUpdateElemptr, SpriteArrayGetNum
 * Called by: AnimChangeActionElem, AnimPerUpdate, BGArrayUpdate,
 *            ContinueScreenLoop, ExplodUpdate, GameUpdate,
 *            ProjArrayUpdate, SiSceneUpdate
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimUpdate(uint32_t *anim)

{
  int i1;
  uint32_t index;
  int i3;
  uint32_t u4;
  
  i3 = anim[3] * *(int *)(*(int *)*anim + 4) + *(int *)(*(int *)*anim + 0x14);
  u4 = 0;
  AnimUpdateElemptr(anim);
  i1 = *(int *)(i3 + 8);
  if ((i1 <= (int)anim[7]) && (i1 != -1)) {
    anim[7] = *(uint32_t *)(i3 + 0xc);
    u4 = 1;
    i1 = *(int *)(*(int *)*anim + 4);
    i3 = *(int *)(*(int *)*anim + 0x14);
    anim[5] = 0;
    anim[4] = *(uint32_t *)(*(int *)(i1 * anim[3] + i3) + 0x14);
    AnimUpdateElemptr(anim);
  }
  index = SpriteArrayGetNum((int *)anim[1],*(int *)(anim[4] + 8),*(int *)(anim[4] + 0xc));
  anim[0xb] = index;
  anim[6] = anim[6] + 1;
  anim[7] = anim[7] + 1;
  return u4;
}

/* AnimUpdateElemptr @ 0x08048d70, 88 bytes
 *
 * Selects the element whose start tick is the last one <= the action time
 * and stores it as the current element.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Called by: AnimChangeActionElem, AnimUpdate
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int AnimUpdateElemptr(uint32_t *anim)

{
  int i1;
  int i2;
  int *pi3;
  int *pi4;
  
  i2 = anim[5];
  i1 = *(int *)(*(int *)*anim + 0x14);
  pi4 = (int *)(anim[3] * *(int *)(*(int *)*anim + 4) + i1);
  if (i2 < pi4[1]) {
    pi3 = (int *)(i2 * *(int *)(*pi4 + 4) + *(int *)(*pi4 + 0x14));
    i1 = anim[7];
    if (*pi3 <= i1) {
      anim[4] = pi3;
      while (i2 = i2 + 1, i2 < pi4[1]) {
        pi3 = (int *)(i2 * *(int *)(*pi4 + 4) + *(int *)(*pi4 + 0x14));
        i1 = anim[7];
        if (i1 < *pi3) {
          return i1;
        }
        anim[4] = pi3;
        anim[5] = i2;
      }
    }
  }
  return i1;
}

/* AnimResetAction @ 0x08048dd0, 62 bytes
 *
 * Restarts the current action from tick 0 at its first element (falls back
 * to action 0 if the index is invalid).
 *
 * Parameters:
 *   anim         int *
 *
 * Called by: AnimChangeActionElem, AnimPerArrayAdd, BGArrayCtrlUpdate,
 *            BGArrayReset, ExplodAdd, PlayerChangeAnim, PlayerReset,
 *            ProjArrayAdd, SysExplodCreate
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimResetAction(int *anim)

{
  int i1;
  int i2;
  int i3;
  
  i3 = anim[3];
  if (((int *)*anim)[1] < i3) {
    anim[3] = 0;
    i3 = 0;
  }
  i1 = *(int *)*anim;
  i2 = *(int *)(i1 + 4);
  i1 = *(int *)(i1 + 0x14);
  anim[6] = 0;
  i3 = *(int *)(i3 * i2 + i1);
  anim[7] = 0;
  anim[4] = *(int *)(i3 + 0x14);
  anim[5] = 0;
  return;
}

/* AnimChangeAction @ 0x08048e10, 29 bytes
 *
 * AnimChangeActionTime with time 0.
 *
 * Parameters:
 *   anim         int *
 *   grpno        int
 *   actionno     int
 *
 * Calls: AnimChangeActionTime
 * Called by: AnimChangeActionElem, AnimPerArrayAdd, BGArrayAddAnim,
 *            BGArrayCtrlUpdate, BGArrayReset, ExplodAdd, PlayerAutoTurn,
 *            PlayerChangeAnim, PlayerChangeAnimElem, ProjArrayAdd,
 *            ProjArrayUpdate, SiSceneUpdate, SysExplodCreate
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimChangeAction(int *anim,int grpno,int actionno)

{
  uint32_t u1;
  
  u1 = AnimChangeActionTime(anim,grpno,actionno,0);
  return u1;
}

/* AnimChangeActionTime @ 0x08048e30, 141 bytes
 *
 * Switches to action number `actionno` (array key (grpno, actionno); grpno
 * is always 0) and sets the action time to `time`. When the action differs
 * from the current one, the element pointer is reset first. Returns 0 when
 * the action does not exist; the instance then keeps its previous action.
 *
 * Parameters:
 *   anim         int *
 *   grpno        int
 *   actionno     int
 *   time         int
 *
 * Calls: AnimGrpNoToIdx
 * Called by: AnimChangeAction
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimChangeActionTime(int *anim,int grpno,int actionno,int time)

{
  int *pi1;
  int i2;
  int index;
  uint32_t u4;
  
  if (((int *)*anim)[1] < anim[3]) {
    index = *(int *)*anim;
    anim[3] = 0;
    pi1 = *(int **)(index + 0x14);
    anim[5] = 0;
    anim[4] = *(int *)(*pi1 + 0x14);
  }
  index = AnimGrpNoToIdx(anim,grpno,actionno);
  if (index == -1) {
    u4 = 0;
  }
  else {
    if (anim[3] != index) {
      anim[3] = index;
      if (time != -1) {
        anim[6] = time;
        anim[7] = time;
      }
      index = *(int *)(*(int *)*anim + 4);
      i2 = *(int *)(*(int *)*anim + 0x14);
      anim[5] = 0;
      anim[4] = *(int *)(*(int *)(index * anim[3] + i2) + 0x14);
    }
    u4 = 1;
  }
  return u4;
}

/* AnimChangeActionElem @ 0x08048ec0, 157 bytes
 *
 * Switches to action `actionno` and advances the clock to the start of
 * element `elem` (when it is in range). Used by ChangeAnim/ChangeAnim2 with
 * "elem = n" (PlayerChangeAnimElem).
 *
 * Parameters:
 *   anim         int *
 *   grpno        int
 *   actionno     int
 *   elem         int
 *
 * Calls: AnimChangeAction, AnimResetAction, AnimUpdateElemptr, AnimUpdate
 * Called by: PlayerChangeAnimElem
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimChangeActionElem(int *anim,int grpno,int actionno,int elem)

{
  int i1;
  
  i1 = AnimChangeAction(anim,grpno,actionno);
  if (i1 != 0) {
    AnimResetAction(anim);
    if ((-1 < elem) &&
       (elem < *(int *)(*(int *)(*(int *)*anim + 4) * anim[3] +
                           *(int *)(*(int *)*anim + 0x14) + 4))) {
      if (elem == 0) {
        return 1;
      }
      AnimUpdateElemptr(anim);
      i1 = anim[5];
      while( true ) {
        if (i1 == elem) {
          anim[6] = anim[6] + -1;
          anim[7] = anim[7] + -1;
          return 1;
        }
        i1 = AnimUpdate(anim);
        if (i1 != 0) break;
        i1 = anim[5];
      }
    }
  }
  return 0;
}

/* AnimDraw @ 0x08048f60, 29 bytes
 *
 * AnimDrawFlip without flip.
 *
 * Parameters:
 *   anim         uint32_t *
 *   x            int
 *   y            int
 *
 * Calls: AnimDrawFlip
 * Called by: SiSceneDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimDraw(uint32_t *anim,int x,int y)

{
  AnimDrawFlip(anim,x,y,0);
  return;
}

/* AnimDrawFlip @ 0x08048f80, 601 bytes
 *
 * Draws the current element at (x, y). It combines the element's flip with
 * the requested one (FlipFlagMix), mixes the element alpha with the instance
 * alpha, offsets by the sprite axis and the element offset, and queues the
 * sprite in the priority list (PRSprAdd) or draws it directly
 * (AnimDrawSprFlip).
 *
 * Parameters:
 *   anim         uint32_t *
 *   x            int
 *   y            int
 *   flip         uint32_t
 *
 * Calls: HFlipToSgn, VFlipToSgn, FlipFlagMix, AlphaMixSrc, AlphaMixDest,
 *        SpriteArrayAccess, AnimDrawSprFlip, PRSprAdd
 * Called by: AnimDraw, AnimDrawScaleFlip
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       16 variables), because their address is taken.
 */
void AnimDrawFlip(uint32_t *anim,int x,int y,uint32_t flip)

{
  int i1;
  int *pi2;
  int i3;
  int i4;
  uint32_t u5;
  int i6;
  int i7;
  int *pi8;
  int *pi9;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_78 (*(int *)(frame + 0x8))
#define stk_74 (*(int *)(frame + 0xc))
#define stk_70 (*(int *)(frame + 0x10))
#define stk_5c (*(int *)(frame + 0x24))
#define stk_58 (*(uint32_t *)(frame + 0x28))
#define stk_54 (*(int *)(frame + 0x2c))
#define stk_50 (*(uint32_t *)(frame + 0x30))
#define stk_4c (*(int *)(frame + 0x34))
#define stk_48 (*(int *)(frame + 0x38))
#define stk_44 (*(uint32_t *)(frame + 0x3c))
#define stk_40 (*(int *)(frame + 0x40))
#define stk_3c (*(int *)(frame + 0x44))
#define stk_38 (*(int *)(frame + 0x48))
#define stk_34 (*(uint32_t *)(frame + 0x4c))
#define stk_30 (*(uint32_t *)(frame + 0x50))
#define stk_28 (*(uint32_t *)(frame + 0x58))
  
  pi2 = (int *)(*(int *)(*(int *)*anim + 4) * anim[3] + *(int *)(*(int *)*anim + 0x14));
  stk_74 = 0;
  if (0 < pi2[1]) {
    i3 = anim[7];
    do {
      pi8 = (int *)(stk_74 * *(int *)(*pi2 + 4) + *(int *)(*pi2 + 0x14));
      if ((*pi8 <= i3 + -1) && ((i3 + -1 < *pi8 + pi8[1] || (pi8[1] == -1)))) {
        i3 = HFlipToSgn(flip);
        i3 = i3 * pi8[4] + x;
        i4 = VFlipToSgn(flip);
        i4 = i4 * pi8[5] + y;
        u5 = FlipFlagMix(flip,pi8[6] & 3);
        stk_70 = anim[8];
        if (stk_70 == -1) {
          stk_70 = pi8[7];
          stk_78 = pi8[8];
          i6 = pi8[9];
        }
        else {
          stk_78 = AlphaMixSrc(anim[9],pi8[8]);
          i6 = AlphaMixDest(anim[10],pi8[9]);
        }
        i1 = anim[0xb];
        if (i1 == -1) {
          i3 = anim[7];
        }
        else {
          SpriteArrayAccess((int *)anim[1],i1);
          if (anim[0xc] == 0) {
            AnimDrawSprFlip((int *)anim[1],i1,i3,i4,u5,stk_70,stk_78,i6);
          }
          else {
            pi9 = &stk_5c;
            for (i7 = 0xe; i7 != 0; i7 = i7 + -1) {
              *pi9 = 0;
              pi9 = pi9 + 1;
            }
            stk_50 = 0;
            stk_5c = anim[0xd];
            stk_58 = anim[1];
            stk_30 = 0x3f800000;
            stk_34 = 0x3f800000;
            stk_40 = stk_70;
            stk_3c = stk_78;
            stk_44 = 1;
            stk_54 = i1;
            stk_4c = i3;
            stk_48 = i4;
            stk_38 = i6;
            stk_28 = u5;
            PRSprAdd((int *)anim[0xc],&stk_5c);
          }
          i3 = anim[7];
        }
      }
    } while ((*pi8 <= i3 + -1) && (stk_74 = stk_74 + 1, stk_74 < pi2[1]));
  }
  return;
}
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_28

/* AnimDrawScale @ 0x080491e0, 39 bytes
 *
 * AnimDrawScaleFlip without flip.
 *
 * Parameters:
 *   anim         uint32_t *
 *   x            int
 *   y            int
 *   xscale       float
 *   yscale       float
 *
 * Calls: AnimDrawScaleFlip
 * Called by: BGAnimDrawTile, BGDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimDrawScale(uint32_t *anim,int x,int y,float xscale,float yscale)

{
  AnimDrawScaleFlip(anim,x,y,xscale,yscale,0);
  return;
}

/* AnimDrawScaleFlip @ 0x08049210, 811 bytes
 *
 * AnimDrawFlip with x and y scale factors; falls back to AnimDrawFlip at
 * scale 1. Used by backgrounds and stage zoom.
 *
 * Parameters:
 *   anim         uint32_t *
 *   x            int
 *   y            int
 *   xscale       float
 *   yscale       float
 *   flip         uint32_t
 *
 * Calls: AnimDrawFlip, HFlipToSgn, roundfloat, VFlipToSgn, FlipFlagMix,
 *        AlphaMixSrc, AlphaMixDest, SpriteArrayAccess, PRSprAdd,
 *        AnimScaleSpr_S
 * Called by: AnimDrawScale, AnimPerDraw, AnimPerDrawScale, ExplodDraw,
 *            PlayerDrawAnim, ProjArrayDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       16 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void AnimDrawScaleFlip(uint32_t *anim,int x,int y,float xscale,float yscale,
                      uint32_t flip)

{
  int i1;
  int *pi2;
  int i3;
  int i4;
  uint32_t u5;
  int i6;
  int i7;
  int *pi8;
  int *pi9;
  float80 f10;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_78 (*(int *)(frame + 0x8))
#define stk_74 (*(int *)(frame + 0xc))
#define stk_70 (*(int *)(frame + 0x10))
#define stk_5c (*(int *)(frame + 0x24))
#define stk_58 (*(uint32_t *)(frame + 0x28))
#define stk_54 (*(int *)(frame + 0x2c))
#define stk_50 (*(uint32_t *)(frame + 0x30))
#define stk_4c (*(int *)(frame + 0x34))
#define stk_48 (*(int *)(frame + 0x38))
#define stk_44 (*(uint32_t *)(frame + 0x3c))
#define stk_40 (*(int *)(frame + 0x40))
#define stk_3c (*(int *)(frame + 0x44))
#define stk_38 (*(int *)(frame + 0x48))
#define stk_34 (*(float *)(frame + 0x4c))
#define stk_30 (*(float *)(frame + 0x50))
#define stk_28 (*(uint32_t *)(frame + 0x58))
  
  pi2 = (int *)(*(int *)(*(int *)*anim + 4) * anim[3] + *(int *)(*(int *)*anim + 0x14));
  if ((xscale == 1.0) && (yscale == 1.0)) {
    AnimDrawFlip(anim,x,y,flip);
  }
  else {
    stk_70 = 0;
    if (0 < pi2[1]) {
      i3 = anim[7];
      do {
        pi8 = (int *)(stk_70 * *(int *)(*pi2 + 4) + *(int *)(*pi2 + 0x14));
        if ((*pi8 <= i3 + -1) && ((i3 + -1 < *pi8 + pi8[1] || (pi8[1] == -1)))) {
          i3 = HFlipToSgn(flip);
          i3 = roundfloat((float80)i3 * (float80)pi8[4] * xscale);
          i4 = VFlipToSgn(flip);
          i4 = roundfloat((float80)i4 * (float80)pi8[5] * yscale);
          u5 = FlipFlagMix(flip,pi8[6] & 3);
          stk_74 = anim[8];
          if (stk_74 == -1) {
            stk_74 = pi8[7];
            stk_78 = pi8[8];
            i6 = pi8[9];
          }
          else {
            stk_78 = AlphaMixSrc(anim[9],pi8[8]);
            i6 = AlphaMixDest(anim[10],pi8[9]);
          }
          i1 = anim[0xb];
          if (i1 != -1) {
            SpriteArrayAccess((int *)anim[1],i1);
            if (anim[0xc] != 0) {
              pi9 = &stk_5c;
              for (i7 = 0xe; i7 != 0; i7 = i7 + -1) {
                *pi9 = 0;
                pi9 = pi9 + 1;
              }
              stk_5c = anim[0xd];
              stk_58 = anim[1];
              stk_40 = stk_74;
              stk_3c = stk_78;
              stk_50 = 0;
              stk_44 = 2;
              stk_34 = xscale;
              stk_30 = yscale;
              stk_54 = i1;
              stk_4c = i3 + x;
              stk_48 = i4 + y;
              stk_38 = i6;
              stk_28 = u5;
              PRSprAdd((int *)anim[0xc],&stk_5c);
              i3 = anim[7];
              goto L_08049512;
            }
            i7 = VFlipToSgn(u5);
            f10 = (float80)i7 * yscale;
            i7 = HFlipToSgn(u5);
            AnimScaleSpr_S((int *)anim[1],i1,i3 + x,i4 + y,
                           (float80)i7 * xscale,f10,stk_74,stk_78,i6);
          }
          i3 = anim[7];
        }
L_08049512: ;
      } while ((*pi8 <= i3 + -1) && (stk_70 = stk_70 + 1, stk_70 < pi2[1]));
    }
  }
  return;
}
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_28

/* AnimDrawRotateFlip @ 0x08049540, 819 bytes
 *
 * Draws the current element rotated by `angle` with scale and flip
 * (AnimRotateSpr), queuing it in the priority list. Used for players with an
 * AngleDraw state controller.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: HFlipToSgn, VFlipToSgn, FlipFlagMix, AlphaMixSrc, AlphaMixDest,
 *        SpriteArrayAccess, PRSprAdd, AnimRotateSpr
 * Called by: PlayerDrawAnim
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       16 variables), because their address is taken.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void AnimDrawRotateFlip(uint32_t *arg1,int arg2,int arg3,float arg4,float arg5,
                       float arg6,uint32_t arg7)

{
  int *pi1;
  int i2;
  int i3;
  uint32_t u4;
  int i5;
  int i6;
  int i7;
  int i8;
  int *pi9;
  int *pi10;
  float80 f11;
  float80 f12;
  float80 f13;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_7c (*(int *)(frame + 0x4))
#define stk_78 (*(int *)(frame + 0x8))
#define stk_5c (*(int *)(frame + 0x24))
#define stk_58 (*(uint32_t *)(frame + 0x28))
#define stk_54 (*(int *)(frame + 0x2c))
#define stk_50 (*(uint32_t *)(frame + 0x30))
#define stk_4c (*(int *)(frame + 0x34))
#define stk_48 (*(int *)(frame + 0x38))
#define stk_44 (*(uint32_t *)(frame + 0x3c))
#define stk_40 (*(uint32_t *)(frame + 0x40))
#define stk_3c (*(int *)(frame + 0x44))
#define stk_38 (*(int *)(frame + 0x48))
#define stk_34 (*(float *)(frame + 0x4c))
#define stk_30 (*(float *)(frame + 0x50))
#define stk_2c (*(float *)(frame + 0x54))
#define stk_28 (*(uint32_t *)(frame + 0x58))
  
  pi1 = (int *)(*(int *)(*(int *)*arg1 + 4) * arg1[3] + *(int *)(*(int *)*arg1 + 0x14));
  stk_78 = 0;
  if (0 < pi1[1]) {
    i2 = arg1[7];
    do {
      pi9 = (int *)(stk_78 * *(int *)(*pi1 + 4) + *(int *)(*pi1 + 0x14));
      if ((*pi9 <= i2 + -1) && ((i2 + -1 < *pi9 + pi9[1] || (pi9[1] == -1)))) {
        i2 = HFlipToSgn(arg7);
        i2 = (int)X87_FIST32((float80)i2 * (float80)pi9[4] * arg5 + (float)arg2);
        i3 = VFlipToSgn(arg7);
        i3 = (int)X87_FIST32((float80)i3 * (float80)pi9[5] * arg6 + (float)arg3);
        u4 = FlipFlagMix(arg7,pi9[6] & 3);
        i8 = arg1[8];
        if (i8 == -1) {
          stk_7c = pi9[8];
          i8 = pi9[7];
          i5 = pi9[9];
        }
        else {
          stk_7c = AlphaMixSrc(arg1[9],pi9[8]);
          i5 = AlphaMixDest(arg1[10],pi9[9]);
        }
        i6 = HFlipToSgn(arg7);
        arg4 = (float80)i6 * arg4;
        i6 = arg1[0xb];
        if (i6 != -1) {
          SpriteArrayAccess((int *)arg1[1],i6);
          if (arg1[0xc] != 0) {
            pi10 = &stk_5c;
            for (i8 = 0xe; i8 != 0; i8 = i8 + -1) {
              *pi10 = 0;
              pi10 = pi10 + 1;
            }
            stk_50 = 0;
            stk_5c = arg1[0xd];
            stk_34 = arg5;
            stk_58 = arg1[1];
            stk_44 = 3;
            stk_30 = arg6;
            stk_40 = arg1[8];
            stk_3c = stk_7c;
            stk_54 = i6;
            stk_4c = i2;
            stk_48 = i3;
            stk_38 = i5;
            stk_2c = arg4;
            stk_28 = u4;
            PRSprAdd((int *)arg1[0xc],&stk_5c);
            i2 = arg1[7];
            goto L_0804984a;
          }
          f13 = 1.0;
          f12 = 1.0;
          i7 = VFlipToSgn(u4);
          f11 = (float80)i7 * arg6;
          i7 = HFlipToSgn(u4);
          AnimRotateSpr((int *)arg1[1],i6,i2,i3,arg4,(float80)i7 * arg5,f11,
                        f12,f13,i8,stk_7c,i5);
        }
        i2 = arg1[7];
      }
L_0804984a: ;
    } while ((*pi9 <= i2 + -1) && (stk_78 = stk_78 + 1, stk_78 < pi1[1]));
  }
  return;
}
#undef stk_7c
#undef stk_78
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28

/* AnimCurIDGrp @ 0x08049880, 25 bytes
 *
 * Returns the first key of the current action (always 0 for AIR actions).
 * Not called in this build.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Calls: ArrayIdxToGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimCurIDGrp(uint32_t *anim)

{
  ArrayIdxToGrp(*(int *)*anim,anim[3]);
  return;
}

/* AnimCurIDno @ 0x080498a0, 25 bytes
 *
 * Returns the action number of the current action (its second key). This is
 * the value of the Anim trigger.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Calls: ArrayIdxToItem
 * Called by: PlayerKBUpdate, SCtrlTrigEval, ShowDebugInfo
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimCurIDno(uint32_t *anim)

{
  uint32_t u1;
  
  u1 = ArrayIdxToItem(*(int *)*anim,anim[3]);
  return u1;
}

/* AnimCurElemStartTime @ 0x080498c0, 52 bytes
 *
 * Returns the start tick of element `elem` in the current action, or -1 if
 * it does not exist. Used by the AnimElemTime trigger.
 *
 * Parameters:
 *   anim         uint32_t *
 *   elem         int
 *
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimCurElemStartTime(uint32_t *anim,int elem)

{
  int i1;
  int *pi2;
  uint32_t u3;
  
  pi2 = (int *)(*(int *)(*(int *)*anim + 4) * anim[3] + *(int *)(*(int *)*anim + 0x14));
  if (elem < pi2[1]) {
    i1 = *pi2;
    u3 = *(uint32_t *)(elem * *(int *)(i1 + 4) + *(int *)(i1 + 0x14));
  }
  else {
    u3 = 0xffffffff;
  }
  return u3;
}

/* AnimElemNo @ 0x08049900, 150 bytes
 *
 * Returns the element number that will be showing `offset` ticks from now,
 * taking looping into account. Used by the AnimElemNo trigger.
 *
 * Parameters:
 *   anim         uint32_t *
 *   offset       int
 *
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int AnimElemNo(uint32_t *anim,int offset)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int *pi5;
  
  i4 = anim[7];
  pi5 = (int *)(anim[3] * *(int *)(*(int *)*anim + 4) + *(int *)(*(int *)*anim + 0x14));
  i3 = pi5[2] - pi5[3];
  i2 = i4 + offset;
  if (i2 < 0) {
    if (i4 < pi5[2]) {
      return 0xffffffff;
    }
    i2 = (i3 - offset) + i4;
  }
  if ((pi5[2] <= i2) && (pi5[2] != -1)) {
    i2 = (i2 - pi5[3]) % i3 + pi5[3];
  }
  i4 = 0;
  if (0 < pi5[1]) {
    i3 = *pi5;
    i1 = **(int **)(i3 + 0x14);
    while ((i1 <= i2 && (i4 = i4 + 1, i4 < pi5[1]))) {
      i1 = *(int *)(i4 * *(int *)(i3 + 4) + *(int *)(i3 + 0x14));
    }
  }
  return i4;
}

/* AnimIdxToIDGrp @ 0x080499a0, 17 bytes
 *
 * Returns the first key of action index `idx`.
 *
 * Parameters:
 *   anim         uint32_t *
 *   index        int
 *
 * Calls: ArrayIdxToGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimIdxToIDGrp(uint32_t *anim,int index)

{
  ArrayIdxToGrp(*(int *)*anim,index);
  return;
}

/* AnimIdxToIDno @ 0x080499c0, 17 bytes
 *
 * Returns the second key of action index `idx`.
 *
 * Parameters:
 *   anim         uint32_t *
 *   index        int
 *
 * Calls: ArrayIdxToItem
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimIdxToIDno(uint32_t *anim,int index)

{
  ArrayIdxToItem(*(int *)*anim,index);
  return;
}

/* AnimGrpNoToIdx @ 0x080499e0, 17 bytes
 *
 * Returns the array index of the action keyed (grpno, actionno), or -1
 * (ArrayFind).
 *
 * Parameters:
 *   anim         uint32_t *
 *   grpno        int
 *   actionno     int
 *
 * Calls: ArrayFind
 * Called by: AnimChangeActionTime, AnimGetLoopstarttimeID,
 *            AnimGetLooptimeID, PlayerAnimExist, PlayerCheck,
 *            PlayerSelfAnimExist
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGrpNoToIdx(uint32_t *anim,int grpno,int actionno)

{
  uint32_t index;
  
  index = ArrayFind(*(int *)*anim,grpno,actionno);
  return index;
}

/* AnimGetLooptime @ 0x08049a00, 24 bytes
 *
 * Returns the current action's total length in ticks (-1 when an element
 * lasts forever). Used by AnimTime.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Called by: AnimGetCorrectedTime, ExplodSetParams, GameUpdate,
 *            PlayerMakeDust, PlayerSCtrlApplyElem, PlayerSparkCreate,
 *            PlayerUpdate, ProjArrayUpdate, SCtrlTrigEval, ShowDebugInfo,
 *            SysExplodCreate
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGetLooptime(uint32_t *anim)

{
  return *(uint32_t *)
          (*(int *)(*(int *)*anim + 4) * anim[3] + *(int *)(*(int *)*anim + 0x14) + 8);
}

/* AnimGetLooptimeID @ 0x08049a20, 47 bytes
 *
 * Returns the loop time of action key (grp, no). Not called in this build.
 *
 * Parameters:
 *   anim         uint32_t *
 *   arg2         int
 *   arg3         int
 *
 * Calls: AnimGrpNoToIdx
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGetLooptimeID(uint32_t *anim,int arg2,int arg3)

{
  int *pi1;
  int index;
  
  pi1 = (int *)*anim;
  index = AnimGrpNoToIdx(anim,arg2,arg3);
  return *(uint32_t *)(index * *(int *)(*pi1 + 4) + *(int *)(*pi1 + 0x14) + 8);
}

/* AnimGetLoopstarttime @ 0x08049a50, 24 bytes
 *
 * Returns the tick at which the current action loops back.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Called by: AnimGetCorrectedTime
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGetLoopstarttime(uint32_t *anim)

{
  return *(uint32_t *)
          (*(int *)(*(int *)*anim + 4) * anim[3] + *(int *)(*(int *)*anim + 0x14) + 0xc);
}

/* AnimGetLoopstarttimeID @ 0x08049a70, 47 bytes
 *
 * Returns the loop start tick of action key (grp, no). Not called in this
 * build.
 *
 * Parameters:
 *   anim         uint32_t *
 *   arg2         int
 *   arg3         int
 *
 * Calls: AnimGrpNoToIdx
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGetLoopstarttimeID(uint32_t *anim,int arg2,int arg3)

{
  int *pi1;
  int index;
  
  pi1 = (int *)*anim;
  index = AnimGrpNoToIdx(anim,arg2,arg3);
  return *(uint32_t *)(index * *(int *)(*pi1 + 4) + *(int *)(*pi1 + 0x14) + 0xc);
}

/* AnimGetTime @ 0x08049aa0, 8 bytes
 *
 * Returns the current action time (ticks since the action started).
 *
 * Parameters:
 *   anim         int
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimGetTime(int anim)

{
  return *(uint32_t *)(anim + 0x1c);
}

/* AnimGetCorrectedTime @ 0x08049ab0, 44 bytes
 *
 * Returns the action time folded into the loop (time - looptime + loopstart
 * once past the end). Not called in this build.
 *
 * Parameters:
 *   anim         uint32_t *
 *
 * Calls: AnimGetLooptime, AnimGetLoopstarttime
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int AnimGetCorrectedTime(uint32_t *anim)

{
  int looptime;
  uint32_t u2;
  
  looptime = AnimGetLooptime(anim);
  if ((int)anim[7] < looptime) {
    return anim[7];
  }
  u2 = AnimGetLoopstarttime(anim);
  return u2;
}

/* AnimCurSpriteIdx @ 0x08049ae0, 8 bytes
 *
 * Returns the sprite array index of the current element's sprite (cached by
 * AnimUpdate). Used to draw shadows.
 *
 * Parameters:
 *   anim         int
 *
 * Called by: ExplodDrawShadow, PlayerDrawShadow, ProjDrawShadow
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t AnimCurSpriteIdx(int anim)

{
  return *(uint32_t *)(anim + 0x2c);
}

/* PRSprArrayNew @ 0x08049af0, 122 bytes
 *
 * Creates the priority sprite list: an array of sprite draw requests plus a
 * sorted index, sized for `capacity` entries. Reports "Out of memory." on
 * failure.
 *
 * Parameters:
 *   arg1         size_t
 *
 * Calls: ecalloc, ArrayNew, PRSprArrayFree
 * C library: sprintf
 * Called by: GameVarInit
 * Messages:
 *   "Out of memory."
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t * PRSprArrayNew(size_t arg1)

{
  uint32_t *mem;
  uint32_t *array;
  int mem2;
  uint32_t stale_EDX;
  
  mem = (uint32_t *)ecalloc(1,8);
  if (mem != (uint32_t *)0x0) {
    array = ArrayNew(arg1,0x38,0);
    *mem = array;
    if (array == (uint32_t *)0x0) {
      sprintf((char *)ErrorMessage,"Out of memory.",stale_EDX,stale_EDX);
    }
    else {
      mem2 = ecalloc(arg1,4);
      mem[1] = mem2;
      if (mem2 != 0) {
        return mem;
      }
    }
    PRSprArrayFree(mem);
  }
  return (uint32_t *)0x0;
}

/* PRSprArrayFree @ 0x08049b70, 60 bytes
 *
 * Frees the priority sprite list.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ArrayFree
 * C library: free
 * Called by: GameVarDeInit, PRSprArrayNew
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t PRSprArrayFree(uint32_t *arg1)

{
  uint32_t stale_EAX;
  uint32_t entry_EDX;
  
  if (arg1 != (uint32_t *)0x0) {
    ArrayFree((void *)*arg1);
    if ((void *)arg1[1] != (void *)0x0) {
      free((void *)arg1[1]);
    }
    free(arg1);
    return stale_EAX;
  }
  return entry_EDX;
}

/* PRSprArrayClear @ 0x08049bb0, 15 bytes
 *
 * Empties the priority sprite list (done every frame before drawing).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayClear
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            ModeSelect, OptionsScreen, PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void PRSprArrayClear(int *arg1)

{
  ArrayClear(*arg1);
  return;
}

/* PRSprAdd @ 0x08049bc0, 145 bytes
 *
 * Adds a sprite draw request to the priority list, keeping the index sorted
 * by sprite priority (the request's first word). Equal priorities keep
 * insertion order. Returns 0 when the list is full.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *
 * Calls: ArrayAdd
 * Called by: AftImgDraw, AnimDrawFlip, AnimDrawRotateFlip,
 *            AnimDrawScaleFlip
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t PRSprAdd(int *arg1,int *arg2)

{
  int i1;
  int array;
  int i3;
  int index;
  uint32_t u5;
  int i6;
  uint32_t *pu7;
  int i2;
  
  i1 = *arg2;
  array = *arg1;
  i3 = arg1[1];
  index = ArrayAdd(array,arg2,0,i1);
  if (index == -1) {
    u5 = 0;
  }
  else {
    i6 = *(int *)(array + 8);
    i2 = 0;
    if (0 < i6 + -1) {
      do {
        if (i1 <= *(int *)(*(int *)(array + ARRAY_INDEX) + 0xc + *(int *)(i3 + i2 * 4) * 0x10)) {
          i6 = i6 + -1;
          if (i2 < i6) {
            pu7 = (uint32_t *)(i3 + i6 * 4);
            do {
              i6 = i6 + -1;
              *pu7 = pu7[-1];
              pu7 = pu7 + -1;
            } while (i2 < i6);
          }
          break;
        }
        i2 = i2 + 1;
      } while (i2 < i6 + -1);
    }
    *(int *)(i3 + i2 * 4) = index;
    u5 = 1;
  }
  return u5;
}

/* PRSprDraw @ 0x08049c60, 356 bytes
 *
 * Draws one queued sprite request: plain, scaled (AnimScaleSpr_S) or rotated
 * (AnimRotateSpr), with its flip and blend.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: VFlipToSgn, HFlipToSgn, AnimScaleSpr_S, AnimDrawSprFlip,
 *        AnimRotateSpr
 * Called by: PRSprArrayDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void PRSprDraw(int arg1)

{
  int i1;
  uint32_t u2;
  float80 f3;
  uint32_t u4;
  int i5;
  float80 f6;
  int i7;
  float80 f8;
  
  u2 = 0;
  if ((*(int *)(arg1 + 0xc) != 0) && (i7 = *(int *)(arg1 + 4), i7 != 0)) {
    u2 = *(uint32_t *)(i7 + 0x14);
    *(int *)(i7 + 0x14) = *(int *)(arg1 + 0xc);
  }
  i7 = *(int *)(arg1 + 0x18);
  if (i7 == 2) {
    if (*(int *)(arg1 + 4) != 0) {
      i7 = *(int *)(arg1 + 0x24);
      i5 = *(int *)(arg1 + 0x20);
      u4 = *(uint32_t *)(arg1 + 0x1c);
      i1 = VFlipToSgn(*(uint32_t *)(arg1 + 0x34));
      f3 = (float80)i1 * *(float *)(arg1 + 0x2c);
      i1 = HFlipToSgn(*(uint32_t *)(arg1 + 0x34));
      AnimScaleSpr_S(*(int **)(arg1 + 4),*(int *)(arg1 + 8),*(int *)(arg1 + 0x10),
                     *(int *)(arg1 + 0x14),(float80)i1 * *(float *)(arg1 + 0x28),f3,u4,
                     i5,i7);
    }
  }
  else if (i7 < 3) {
    if ((i7 == 1) && (*(int *)(arg1 + 4) != 0)) {
      AnimDrawSprFlip(*(int **)(arg1 + 4),*(int *)(arg1 + 8),*(int *)(arg1 + 0x10),
                      *(int *)(arg1 + 0x14),*(int *)(arg1 + 0x34),
                      *(uint32_t *)(arg1 + 0x1c),*(int *)(arg1 + 0x20),
                      *(int *)(arg1 + 0x24));
    }
  }
  else if ((i7 == 3) && (*(int *)(arg1 + 4) != 0)) {
    i7 = *(int *)(arg1 + 0x24);
    i5 = *(int *)(arg1 + 0x20);
    u4 = *(uint32_t *)(arg1 + 0x1c);
    f8 = 1.0;
    f6 = 1.0;
    i1 = VFlipToSgn(*(uint32_t *)(arg1 + 0x34));
    f3 = (float80)i1 * *(float *)(arg1 + 0x2c);
    i1 = HFlipToSgn(*(uint32_t *)(arg1 + 0x34));
    AnimRotateSpr(*(int **)(arg1 + 4),*(int *)(arg1 + 8),*(int *)(arg1 + 0x10),
                  *(int *)(arg1 + 0x14),*(float *)(arg1 + 0x30),
                  (float80)i1 * *(float *)(arg1 + 0x28),f3,f6,f8,u4,i5,i7);
  }
  if ((*(int *)(arg1 + 0xc) != 0) && (*(int *)(arg1 + 4) != 0)) {
    *(uint32_t *)(*(int *)(arg1 + 4) + 0x14) = u2;
  }
  return;
}

/* PRSprArrayDraw @ 0x08049dd0, 57 bytes
 *
 * Draws all queued requests in priority order (lowest first, so higher
 * priorities end up on top).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: PRSprDraw
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void PRSprArrayDraw(int *arg1)

{
  int i1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  i1 = *arg1;
  i3 = *(int *)(i1 + 8);
  if (0 < i3) {
    do {
      i2 = *(int *)(i1 + 4) * *(int *)(arg1[1] + i4 * 4) + *(int *)(i1 + 0x14);
      if (i2 != 0) {
        PRSprDraw(i2);
        i3 = *(int *)(i1 + 8);
      }
      i4 = i4 + 1;
    } while (i4 < i3);
  }
  return;
}

/* PRSprArrayScale @ 0x08049e10, 212 bytes
 *
 * Multiplies the positions of all queued requests by `scale` and switches
 * unscaled requests to scaled drawing. GameLoop uses it for the resolution
 * scale.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *
 * Called by: GameLoop
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int PRSprArrayScale(int *arg1,float arg2)

{
  float80 f1;
  int i2;
  int entry_EAX;
  int i3;
  int i4;
  int i5;
  int stk_14;
  
  i2 = *arg1;
  i3 = *(int *)(i2 + 8);
  stk_14 = entry_EAX;
  if (0 < i3) {
    i5 = 0;
    do {
      i4 = *(int *)(i2 + 0x14) + *(int *)(i2 + 4) * *(int *)(arg1[1] + i5 * 4);
      if (i4 != 0) {
        *(int *)(i4 + 0x10) = (int)X87_FIST32((float80)*(int *)(i4 + 0x10) * arg2);
        stk_14 = (int)X87_FIST32((float80)*(int *)(i4 + 0x14) * arg2);
        *(int *)(i4 + 0x14) = stk_14;
        if (*(int *)(i4 + 0x18) - 1U < 2) {
          f1 = *(float *)(i4 + 0x28);
          *(uint32_t *)(i4 + 0x18) = 2;
          i3 = *(int *)(i2 + 8);
        }
        else {
          if (*(int *)(i4 + 0x18) != 3) {
            i3 = *(int *)(i2 + 8);
            goto L_08049ed3;
          }
          f1 = *(float *)(i4 + 0x28);
          i3 = *(int *)(i2 + 8);
        }
        *(float *)(i4 + 0x28) = f1 * arg2;
        *(float *)(i4 + 0x2c) = *(float *)(i4 + 0x2c) * arg2;
      }
L_08049ed3:
      i5 = i5 + 1;
    } while (i5 < i3);
  }
  return stk_14;
}

/* AnimPerUpdate @ 0x08049ef0, 33 bytes
 *
 * Advances one persistent animation (AnimUpdate). Returns 1 while it is
 * still playing and 0 once its action has run through once; the caller then
 * deletes it. Persistent animations play a single time.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AnimUpdate
 * Called by: AnimPerArrayUpdate, AnimPerArrayUpdateGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint8_t AnimPerUpdate(int arg1)

{
  int i1;
  
  i1 = AnimUpdate((uint32_t *)(arg1 + 0x14));
  return (i1 != 0) - 1U & 1;
}

/* AnimPerDraw @ 0x08049f20, 51 bytes
 *
 * Draws one persistent animation at its position plus (x, y), with its scale
 * and flip (AnimDrawScaleFlip).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: AnimDrawScaleFlip
 * Called by: AnimPerArrayDraw, AnimPerArrayDrawGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerDraw(int *arg1,int arg2,int arg3)

{
  AnimDrawScaleFlip(arg1 + 5,*arg1 + arg2,arg1[1] + arg3,BITS_I2F(arg1[3]),
                    BITS_I2F(arg1[4]),arg1[2]);
  return;
}

/* AnimPerDrawScale @ 0x08049f60, 146 bytes
 *
 * Draws one persistent animation scaled, relative to the camera.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         float
 *
 * Calls: AnimDrawScaleFlip
 * Called by: AnimPerArrayDrawScaleGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerDrawScale(int *arg1,int arg2,int arg3,float arg4)

{
  AnimDrawScaleFlip(arg1 + 5,(int)X87_FIST32((float)(*arg1 + arg2) * arg4),
                    (int)X87_FIST32((float)(arg3 + arg1[1]) * arg4),BITS_I2F(arg1[3]) * arg4,
                    BITS_I2F(arg1[4]) * arg4,arg1[2]);
  return;
}

/* AnimPerArrayNew @ 0x0804a000, 78 bytes
 *
 * Creates the array of persistent animations: stand-alone, play-once
 * animations that live outside the players. They are created by the
 * GameMakeAnim state controller (a "GameMakeAnim" string exists in the
 * executable) through PlayerSCtrlApplyElem.
 *
 * Parameters:
 *   arg1         size_t
 *
 * Calls: ecalloc, ArrayNew, AnimPerArrayFree
 * Called by: GameVarInit
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t * AnimPerArrayNew(size_t arg1)

{
  uint32_t *mem;
  uint32_t *array;
  
  mem = (uint32_t *)ecalloc(1,4);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    array = ArrayNew(arg1,0x4c,0);
    *mem = array;
    if (array == (uint32_t *)0x0) {
      AnimPerArrayFree(mem);
      mem = (uint32_t *)0x0;
    }
  }
  return mem;
}

/* AnimPerArrayFree @ 0x0804a050, 39 bytes
 *
 * Frees the persistent animation array.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ArrayFree
 * C library: free
 * Called by: AnimPerArrayNew, GameVarDeInit
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayFree(uint32_t *arg1)

{
  if (arg1 != (uint32_t *)0x0) {
    ArrayFree((void *)*arg1);
    free(arg1);
    return;
  }
  return;
}

/* AnimPerArrayAdd @ 0x0804a080, 197 bytes
 *
 * Adds a persistent animation. Record: [0] x, [1] y, [2] flip, [3]/[4] scale
 * (1.0), then the animation instance, created for an AnimRC and sprite array
 * and started on the requested action. It is stored under group 1. Returns
 * the slot, or -1 if the action does not exist or the array is full.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         int
 *   arg6         uint32_t
 *   arg7         uint32_t
 *   arg8         uint32_t
 *   arg9         uint32_t
 *
 * Calls: AnimSet, AnimChangeAction, AnimResetAction, ArrayAdd
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes, 9
 *       variables), because their address is taken.
 */
uint32_t AnimPerArrayAdd(int *arg1,uint32_t arg2,uint32_t arg3,int arg4,int arg5,
                    uint32_t arg6,uint32_t arg7,uint32_t arg8,uint32_t arg9)

{
  int i1;
  uint32_t index;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_6c (*(uint32_t *)(frame + 0x4))
#define stk_68 (*(uint32_t *)(frame + 0x8))
#define stk_64 (*(uint32_t *)(frame + 0xc))
#define stk_60 (*(uint32_t *)(frame + 0x10))
#define stk_5c (*(uint32_t *)(frame + 0x14))
#define anim (*(int (*)[8])(frame + 0x18))
#define stk_38 (*(uint32_t *)(frame + 0x38))
#define stk_34 (*(uint32_t *)(frame + 0x3c))
#define stk_30 (*(uint32_t *)(frame + 0x40))
  
  stk_6c = arg6;
  stk_68 = arg7;
  stk_64 = arg8;
  stk_5c = 0x3f800000;
  stk_60 = 0x3f800000;
  AnimSet(anim,arg2,arg3);
  stk_38 = arg9;
  stk_30 = 0x100;
  stk_34 = 0x100;
  i1 = AnimChangeAction(anim,arg4,arg5);
  if (i1 == 0) {
    index = 0xffffffff;
  }
  else {
    AnimResetAction(anim);
    index = ArrayAdd(*arg1,&stk_6c,1,0);
    index = (index != 0xffffffff) - 1 | index;
  }
  return index;
}
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef anim
#undef stk_38
#undef stk_34
#undef stk_30

/* AnimPerArraySetNo @ 0x0804a150, 25 bytes
 *
 * Changes the group number stored for slot `idx` of the persistent animation
 * array.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         uint32_t
 *
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArraySetNo(int *arg1,int arg2,uint32_t arg3)

{
  *(uint32_t *)(*(int *)(*arg1 + 0x18) + 8 + arg2 * 0x10) = arg3;
  return;
}

/* AnimPerArrayDelete @ 0x0804a170, 15 bytes
 *
 * Removes slot `idx` from the persistent animation array.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ArrayDelete
 * Called by: AnimPerArrayUpdate, AnimPerArrayUpdateGrp
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayDelete(int *arg1,int arg2)

{
  ArrayDelete(*arg1,arg2);
  return;
}

/* AnimPerArrayClear @ 0x0804a180, 15 bytes
 *
 * Removes all persistent animations (round reset).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayClear
 * Called by: GameRoundReset
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayClear(int *arg1)

{
  ArrayClear(*arg1);
  return;
}

/* AnimPerArrayUpdate @ 0x0804a190, 70 bytes
 *
 * Updates every persistent animation and deletes those that have finished.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, AnimPerUpdate, AnimPerArrayDelete, ArrayScanNext
 * Called by: ContinueScreenLoop, GameUpdate
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t AnimPerArrayUpdate(int *arg1)

{
  int array;
  uint8_t b2;
  int item;
  uint32_t stale_var;
  uint32_t stk_c;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    b2 = AnimPerUpdate(item);
    if (ZEXT8(b2) == 0) {
      AnimPerArrayDelete(arg1,*(int *)(array + 0x1c));
    }
    item = ArrayScanNext(array);
  }
  return stk_c;
}

/* AnimPerArrayUpdateGrp @ 0x0804a1e0, 108 bytes
 *
 * AnimPerArrayUpdate for the animations of one group only. Not called in
 * this build.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *
 * Calls: ArrayScanFirst, ArrayIdxToGrp, AnimPerUpdate, AnimPerArrayDelete,
 *        ArrayScanNext
 *
 * Elecbyte file: src/lib/anim-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void AnimPerArrayUpdateGrp(int *arg1,uint32_t arg2)

{
  int array;
  uint8_t b2;
  int item;
  uint32_t u4;
  uint32_t stale_var;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    u4 = ArrayIdxToGrp(array,*(int *)(array + 0x1c));
    if ((arg2 & u4) != 0) {
      b2 = AnimPerUpdate(item);
      if (ZEXT8(b2) == 0) {
        AnimPerArrayDelete(arg1,*(int *)(array + 0x1c));
      }
    }
    item = ArrayScanNext(array);
  }
  return;
}

/* AnimPerArrayDraw @ 0x0804a250, 60 bytes
 *
 * Draws every persistent animation. Not called in this build.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: ArrayScanFirst, AnimPerDraw, ArrayScanNext
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayDraw(int *arg1,int arg2,int arg3)

{
  int array;
  int *item;
  
  array = *arg1;
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    AnimPerDraw(item,arg2,arg3);
    item = (int *)ArrayScanNext(array);
  }
  return;
}

/* AnimPerArrayDrawGrp @ 0x0804a290, 91 bytes
 *
 * Draws the persistent animations of one group.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *   arg3         int
 *   arg4         int
 *
 * Calls: ArrayScanFirst, ArrayIdxToGrp, AnimPerDraw, ArrayScanNext
 * Called by: ContinueScreenLoop
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayDrawGrp(int *arg1,uint32_t arg2,int arg3,int arg4)

{
  int array;
  int *item;
  uint32_t u3;
  
  array = *arg1;
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    u3 = ArrayIdxToGrp(array,*(int *)(array + 0x1c));
    if ((arg2 & u3) != 0) {
      AnimPerDraw(item,arg3,arg4);
    }
    item = (int *)ArrayScanNext(array);
  }
  return;
}

/* AnimPerArrayDrawScaleGrp @ 0x0804a2f0, 95 bytes
 *
 * Draws the persistent animations of one group with scaling (camera zoom).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *   arg3         int
 *   arg4         int
 *   arg5         float
 *
 * Calls: ArrayScanFirst, ArrayIdxToGrp, AnimPerDrawScale, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimPerArrayDrawScaleGrp(int *arg1,uint32_t arg2,int arg3,int arg4,float arg5)

{
  int array;
  int *item;
  uint32_t u3;
  
  array = *arg1;
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    u3 = ArrayIdxToGrp(array,*(int *)(array + 0x1c));
    if ((arg2 & u3) != 0) {
      AnimPerDrawScale(item,arg3,arg4,arg5);
    }
    item = (int *)ArrayScanNext(array);
  }
  return;
}

/* FlipFlagMix @ 0x0804a350, 11 bytes
 *
 * Combines two flip flag sets (XOR): flipping a flipped sprite cancels out.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *
 * Called by: AftImgUpdate, AnimDrawFlip, AnimDrawRotateFlip,
 *            AnimDrawScaleFlip
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
uint32_t FlipFlagMix(uint32_t arg1,uint32_t arg2)

{
  return arg2 ^ arg1;
}

/* AnimDrawSprFlip @ 0x0804a360, 744 bytes
 *
 * Draws one sprite with flip and blend at (x, y). It picks the matching
 * blitter: plain, transparent-additive, subtractive or additive with alpha
 * ("_B"), each in normal, H, V and HV mirrored forms.
 *
 * Parameters:
 *   sprites      int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         uint32_t
 *   arg7         int
 *   arg8         int
 *
 * Calls: W_PutSpriteTransAddMirH, W_PutSpriteTransSubMirH,
 *        W_PutSpriteTransAddMirH_B, W_PutSpriteMirH, W_PutSpriteTransAdd,
 *        W_PutSpriteTransSub, W_PutSpriteTransAdd_B, W_PutSprite,
 *        W_PutSpriteTransAddMirV, W_PutSpriteTransSubMirHV,
 *        W_PutSpriteTransAddMirV_B, W_PutSpriteMirV,
 *        W_PutSpriteTransAddMirHV, W_PutSpriteTransAddMirHV_B,
 *        W_PutSpriteMirHV
 * Called by: AnimDrawFlip, PRSprDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimDrawSprFlip(int *sprites,int arg2,int arg3,int arg4,int arg5,uint32_t arg6
                    ,int arg7,int arg8)

{
  if (arg5 == 1) {
    switch(arg6) {
    case 1:
      W_PutSpriteTransAddMirH(sprites,arg2,arg3,arg4);
      return;
    case 2:
      W_PutSpriteTransSubMirH(sprites,arg2,arg3,arg4);
      return;
    case 3:
      W_PutSpriteTransAddMirH_B(sprites,arg2,arg3,arg4,arg7,arg8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirH(sprites,arg2,arg3,arg4);
      return;
    }
  }
  else if (arg5 < 2) {
    if (arg5 == 0) {
      switch(arg6) {
      case 1:
        W_PutSpriteTransAdd(sprites,arg2,arg3,arg4);
        return;
      case 2:
        W_PutSpriteTransSub(sprites,arg2,arg3,arg4);
        return;
      case 3:
        W_PutSpriteTransAdd_B(sprites,arg2,arg3,arg4,arg7,arg8);
        return;
      case 0xffffffff:
      case 0:
        W_PutSprite(sprites,arg2,arg3,arg4);
        return;
      }
    }
  }
  else if (arg5 == 2) {
    switch(arg6) {
    case 1:
      W_PutSpriteTransAddMirV(sprites,arg2,arg3,arg4);
      return;
    case 2:
      W_PutSpriteTransSubMirHV(sprites,arg2,arg3,arg4);
      return;
    case 3:
      W_PutSpriteTransAddMirV_B(sprites,arg2,arg3,arg4,arg7,arg8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirV(sprites,arg2,arg3,arg4);
      return;
    }
  }
  else if (arg5 == 3) {
    switch(arg6) {
    case 1:
      W_PutSpriteTransAddMirHV(sprites,arg2,arg3,arg4);
      return;
    case 2:
      W_PutSpriteTransSubMirHV(sprites,arg2,arg3,arg4);
      return;
    case 3:
      W_PutSpriteTransAddMirHV_B(sprites,arg2,arg3,arg4,arg7,arg8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirHV(sprites,arg2,arg3,arg4);
      return;
    }
  }
  return;
}

/* AnimScaleSpr_S @ 0x0804a650, 312 bytes
 *
 * Draws one sprite scaled, picking the scaled blitter (plain, additive,
 * subtractive, additive with alpha).
 *
 * Parameters:
 *   sprites      int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *   arg8         int
 *   arg9         int
 *
 * Calls: W_ScaleSpriteTransAdd_S, W_ScaleSpriteTransSub_S,
 *        W_ScaleSpriteTransAdd_B_S, W_ScaleSprite_S
 * Called by: AnimDrawScaleFlip, PRSprDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimScaleSpr_S(int *sprites,int arg2,int arg3,int arg4,float arg5,float arg6,
                   uint32_t arg7,int arg8,int arg9)

{
  switch(arg7) {
  case 1:
    W_ScaleSpriteTransAdd_S(sprites,arg2,(float)arg3,(float)arg4,arg5,arg6);
    return;
  case 2:
    W_ScaleSpriteTransSub_S(sprites,arg2,(float)arg3,(float)arg4,arg5,arg6);
    return;
  case 3:
    W_ScaleSpriteTransAdd_B_S
              (sprites,arg2,(float)arg3,(float)arg4,arg5,arg6,arg8,arg9);
    return;
  case 0xffffffff:
  case 0:
    W_ScaleSprite_S(sprites,arg2,(float)arg3,(float)arg4,arg5,arg6);
    return;
  default:
    return;
  }
}

/* AnimRotateSpr @ 0x0804a790, 368 bytes
 *
 * Draws one sprite rotated and scaled around its axis, picking the rotating
 * blitter (plain, additive, subtractive, additive with alpha).
 *
 * Parameters:
 *   sprites      int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        uint32_t
 *   arg11        int
 *   arg12        int
 *
 * Calls: W_RotateSpriteTransAdd_P, W_RotateSpriteTransSub_P,
 *        W_RotateSpriteTransAdd_B_P, W_RotateSprite_P
 * Called by: AnimDrawRotateFlip, PRSprDraw
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
void AnimRotateSpr(int *sprites,int arg2,int arg3,int arg4,float arg5,float arg6,
                  float arg7,float arg8,float arg9,uint32_t arg10,int arg11,
                  int arg12)

{
  switch(arg10) {
  case 1:
    W_RotateSpriteTransAdd_P
              (sprites,arg2,(float)arg3,(float)arg4,arg5,arg6,arg7,arg8,arg9
              );
    return;
  case 2:
    W_RotateSpriteTransSub_P
              (sprites,arg2,(float)arg3,(float)arg4,arg5,arg6,arg7,arg8,arg9
              );
    return;
  case 3:
    W_RotateSpriteTransAdd_B_P
              (sprites,arg2,(float)arg3,(float)arg4,arg5,arg6,arg7,arg8,arg9
               ,arg11,arg12);
    return;
  case 0xffffffff:
  case 0:
    W_RotateSprite_P(sprites,arg2,(float)arg3,(float)arg4,arg5,arg6,arg7,arg8,
                     arg9);
    return;
  default:
    return;
  }
}

/* AlphaMixSrc @ 0x0804a900, 15 bytes
 *
 * Combines two source alpha values (a * b / 256).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AnimDrawFlip, AnimDrawRotateFlip, AnimDrawScaleFlip
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int AlphaMixSrc(int arg1,int arg2)

{
  return arg2 * arg1 >> 8;
}

/* AlphaMixDest @ 0x0804a910, 24 bytes
 *
 * Combines two destination alpha values: a + (256 - a) * b / 256.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AnimDrawFlip, AnimDrawRotateFlip, AnimDrawScaleFlip
 *
 * Elecbyte file: src/lib/anim-lib.c
 */
int AlphaMixDest(int arg1,int arg2)

{
  return arg1 + ((0x100 - arg1) * arg2 >> 8);
}

