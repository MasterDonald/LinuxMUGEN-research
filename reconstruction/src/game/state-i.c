/*
 * state-i.c -- state helpers
 * The expression stack pops, compiling controller keys into expressions, the
 * small parsers for positions, special flags, sounds, animations, velocities
 * and hit attributes, and the redirection record.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/state-i.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SPopI @ 0x080d0830, 201 bytes
 *
 * Pops an int from the expression stack. A float value is truncated with a
 * warning ("trigger arg truncated to int"). Underflow is fatal.
 *
 * Parameters:
 *   player       int
 *   out          int *
 *
 * Calls: Warn, ErrorExit
 * C library: sprintf
 * Called by: SCtrlTrigEval
 * Messages:
 *   "Fatal: Expression stack underflow."
 *   "trigger arg truncated to int"
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 */
char SPopI(int player,int *out)

{
  int i1;
  int *pi2;
  
  pi2 = MyStackIdx;
  if (-1 < (int)MyStackIdx) {
    i1 = MyStack[(int)MyStackIdx];
    pi2 = (int *)((int)MyStackIdx + -1);
    if (-1 < (int)pi2) {
      MyStackIdx = (int *)((int)MyStackIdx + -2);
      if (i1 == 1) {
        *out = (int)X87_FIST32(BITS_I2F(MyStack[(int)pi2]));
        Warn(player,(int)&str_trigger_arg_truncated_to_int_cdc1);
        return '\x02';
      }
      *out = MyStack[(int)pi2];
      return (i1 == 4) * '\x02' + '\x01';
    }
  }
  MyStackIdx = pi2;
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.",MyStackIdx,MyStackIdx);
  ErrorExit();
  return '\0';
}

/* SPopF @ 0x080d0900, 145 bytes
 *
 * Pops a float from the expression stack (ints are converted). Underflow is
 * fatal.
 *
 * Parameters:
 *   arg1         uint32_t
 *   out          float *
 *
 * Calls: ErrorExit
 * C library: sprintf
 * Called by: SCtrlTrigEval
 * Messages:
 *   "Fatal: Expression stack underflow."
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
char SPopF(uint32_t arg1,float *out)

{
  int *pi1;
  int saved_EBX;
  
  pi1 = MyStackIdx;
  if (-1 < (int)MyStackIdx) {
    saved_EBX = MyStack[(int)MyStackIdx];
    pi1 = (int *)((int)MyStackIdx + -1);
    if (-1 < (int)pi1) {
      MyStackIdx = (int *)((int)MyStackIdx + -2);
      if (saved_EBX == 1) {
        *out = BITS_I2F(MyStack[(int)pi1]);
      }
      else {
        *out = (float)MyStack[(int)pi1];
      }
      return (saved_EBX == 4) + '\x02';
    }
  }
  MyStackIdx = pi1;
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.",saved_EBX,saved_EBX);
  ErrorExit();
  return '\0';
}

/* StackUnderflow @ 0x080d09a0, 26 bytes
 *
 * Fatal error "Expression stack underflow.".
 *
 * Calls: ErrorExit
 * C library: sprintf
 * Called by: SCtrlTrigEval
 * Messages:
 *   "Fatal: Expression stack underflow."
 *
 * Elecbyte file: src/mugen/state-i.c
 */
uint32_t StackUnderflow(void)

{
  uint32_t u1;
  
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.");
  u1 = ErrorExit();
  return u1;
}

/* ItoP_TPConstI @ 0x080d09c0, 109 bytes
 *
 * Reads the integer expression of key `keyname` from a controller group and
 * compiles it. A missing key gives the constant `defval`. Returns 0 on a
 * parse error.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   expr         int *
 *   player       int
 *   defval       int
 *
 * Calls: TPGetValue, ConstExpI, InfixToPostfix
 * Called by: SCtrlParseAftImgParams, SCtrlParseElemType,
 *            SCtrlParseEnvShake, SCtrlParseExplod, SCtrlParseHelper,
 *            SCtrlParseHitDef, SCtrlParseHitOverride, SCtrlParsePalFX,
 *            SCtrlParsePause, SCtrlParseProjectile, SCtrlParseState,
 *            SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/state-i.c
 */
uint32_t ItoP_TPConstI(int tp,char *keyname,int *expr,int player,int defval)

{
  uint8_t *value;
  uint32_t u2;
  
  value = (uint8_t *)TPGetValue(tp,keyname);
  ConstExpI(expr,defval);
  if (value != (uint8_t *)0x0) {
    u2 = InfixToPostfix(value,expr,player,(uint32_t *)0x0,1);
    return u2;
  }
  return 1;
}

/* ItoP_TPConstF @ 0x080d0a30, 109 bytes
 *
 * ItoP_TPConstI for float expressions.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   expr         int *
 *   player       int
 *   defval       int
 *
 * Calls: TPGetValue, ConstExpF, InfixToPostfix
 * Called by: SCtrlParseElemType, SCtrlParseEnvShake, SCtrlParseHelper,
 *            SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/state-i.c
 */
uint32_t ItoP_TPConstF(int tp,char *keyname,int *expr,int player,int defval)

{
  uint8_t *value;
  uint32_t u2;
  
  value = (uint8_t *)TPGetValue(tp,keyname);
  ConstExpF(expr,defval);
  if (value != (uint8_t *)0x0) {
    u2 = InfixToPostfix(value,expr,player,(uint32_t *)0x0,2);
    return u2;
  }
  return 1;
}

/* SCtrlReadExpList @ 0x080d0aa0, 484 bytes
 *
 * Parses a comma-separated list of expressions ("x, y, z") into up to `n`
 * compiled expressions with the given int/float types. Missing trailing
 * values are left empty. Returns the number read, or a parse error.
 *
 * Parameters:
 *   text         uint8_t *
 *   types        char *
 *   player       int
 *   end          uint32_t *
 *
 * Calls: ErrorExit, InfixToPostfix, FreeExpression
 * C library: strlen
 * Called by: ParseAnim, ParseSnd, SCtrlParseAftImgParams,
 *            SCtrlParseElemType, SCtrlParseExplod, SCtrlParseHelper,
 *            SCtrlParseHitDef, SCtrlParsePalFX, SCtrlParseProjectile,
 *            SCtrlParseState, SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after end
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 7
 *       variables), because their address is taken.
 */
uint8_t * SCtrlReadExpList(uint8_t *text,char *types,int player,uint32_t *end,...)

{
  va_list va;
  va_start(va, end);
  char c1;
  uint8_t b2;
  int *expr;
  size_t s4;
  int i5;
  uint8_t *pb6;
  uint8_t *text2;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_3c (*(uint32_t **)(frame + 0x4))
#define stk_38 (*(int *)(frame + 0x8))
#define stk_34 (*(int *)(frame + 0xc))
#define stk_30 (*(uint8_t **)(frame + 0x10))
#define stk_2c (*(int *)(frame + 0x14))
#define stk_28 (*(int *)(frame + 0x18))
#define stk_24 (*(int *)(frame + 0x1c))
  
  stk_34 = 0;
  stk_38 = 0;
  if (text != (uint8_t *)0x0) {
    for (i5 = 0; s4 = strlen(types), i5 < (int)s4; i5 = i5 + 1) {
      c1 = types[i5];
      if (((c1 == 'n') || (c1 == 'i')) || (c1 == 'f')) {
        stk_34 = stk_34 + 1;
      }
    }
    if ((types[stk_34] == ':') || (types[stk_34] == '\0')) {
      pb6 = (uint8_t *)0x0;
      text2 = text;
      if (0 < stk_34) {
        stk_3c = va;
        do {
          b2 = pb6[(int)types];
          if (b2 == 0x69) {
            stk_38 = 1;
          }
          else if ((char)b2 < 'j') {
            if (b2 == 0x66) {
              stk_38 = 2;
            }
            else {
L_080d0b80:
              ErrorExit();
            }
          }
          else {
            if (b2 != 0x6e) goto L_080d0b80;
            stk_38 = 0;
          }
          expr = (int *)*stk_3c;
          stk_2c = *expr;
          stk_28 = expr[1];
          stk_24 = expr[2];
          i5 = InfixToPostfix(text2,expr,player,&stk_30,stk_38);
          if (i5 == 0) break;
          b2 = *stk_30;
          if (b2 == 0x2c) {
            if ((int)pb6 < stk_34 + -1) {
              stk_30 = stk_30 + 1;
            }
          }
          else if (b2 != 0) {
            i5 = stk_34;
            if (pb6 == (uint8_t *)(stk_34 + -1)) {
              do {
                i5 = i5 + 1;
              } while (text[i5] != b2);
              if (text[i5] != 0) goto L_080d0c46;
            }
            FreeExpression(expr);
            *expr = stk_2c;
            expr[1] = stk_28;
            expr[2] = stk_24;
            break;
          }
L_080d0c46:
          pb6 = pb6 + 1;
          text2 = stk_30;
          stk_3c = stk_3c + 1;
        } while ((int)pb6 < stk_34);
      }
      b2 = *(uint8_t *)(__ctype_b + 1 + (char)*text2 * 2);
      while ((b2 & 0x20) != 0) {
        text2 = text2 + 1;
        b2 = *(uint8_t *)(__ctype_b + 1 + (char)*text2 * 2);
      }
      if (end == (uint32_t *)0x0) {
        return pb6;
      }
      *end = text2;
      return pb6;
    }
  }
  return (uint8_t *)0x0;
}
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24

/* SCtrlReadExpListArray @ 0x080d0c90, 493 bytes
 *
 * SCtrlReadExpList for the argument lists of triggers (into an expression
 * array).
 *
 * Parameters:
 *   arg1         uint8_t *
 *   arg2         char *
 *   player       int
 *   arg4         uint32_t *
 *   arg5         int
 *   arg6         int
 *   arg7         int *
 *   arg8         int
 *
 * Calls: ErrorExit, InfToPostArray
 * C library: strlen
 * Called by: SCtrlParseTrigger
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: decompiler flag: type propagation did not settle
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 4
 *       variables), because their address is taken.
 */
int SCtrlReadExpListArray
              (uint8_t *arg1,char *arg2,int player,uint32_t *arg4,int arg5,int arg6,
              int *arg7,int arg8)

{
  char c1;
  uint8_t b2;
  uint8_t b3;
  size_t s4;
  char *pc5;
  int i6;
  int i2;
  uint8_t *text;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_20 (*(char **)(frame + 0x0))
#define stk_1c (*(int *)(frame + 0x4))
#define stk_18 (*(int *)(frame + 0x8))
#define stk_14 (*(uint8_t **)(frame + 0xc))
  
  i2 = 0;
  stk_18 = 0;
  stk_1c = 0;
  stk_20 = (char *)0x0;
  if (arg1 != (uint8_t *)0x0) {
    for (; s4 = strlen(arg2), i2 < (int)s4; i2 = i2 + 1) {
      c1 = arg2[i2];
      if (((c1 == 'n') || (c1 == 'i')) || (c1 == 'f')) {
        stk_18 = stk_18 + 1;
      }
    }
    if ((arg2[stk_18] == ':') || (arg2[stk_18] == '\0')) {
      i2 = 0;
      text = arg1;
      if (0 < stk_18) {
        do {
          c1 = arg2[i2];
          if (c1 == 'i') {
            stk_1c = 1;
          }
          else if (c1 < 'j') {
            if (c1 == 'f') {
              stk_1c = 2;
            }
            else {
L_080d0d60:
              ErrorExit();
            }
          }
          else {
            if (c1 != 'n') goto L_080d0d60;
            stk_1c = 0;
          }
          pc5 = InfToPostArray(text,(float *)(arg5 + (int)stk_20 * 4),stk_20 + arg6,
                                  player,(uint8_t *)(arg8 - (int)stk_20),&stk_14,stk_1c);
          if (pc5 == (char *)0x0) break;
          stk_20 = stk_20 + (int)pc5;
          b2 = *stk_14;
          if (b2 == 0x2c) {
            if (i2 < stk_18 + -1) {
              stk_14 = stk_14 + 1;
            }
          }
          else if (b2 != 0) {
            if (i2 != stk_18 + -1) {
              stk_20 = stk_20 + -(int)pc5;
              break;
            }
            b3 = arg1[stk_18];
            i6 = stk_18;
            while (b3 != b2) {
              i6 = i6 + 1;
              b3 = arg1[i6];
            }
            if (b3 == 0) {
              stk_20 = stk_20 + -(int)pc5;
              break;
            }
          }
          i2 = i2 + 1;
          text = stk_14;
        } while (i2 < stk_18);
      }
      b2 = *(uint8_t *)(__ctype_b + 1 + (char)*text * 2);
      while ((b2 & 0x20) != 0) {
        text = text + 1;
        b2 = *(uint8_t *)(__ctype_b + 1 + (char)*text * 2);
      }
      if (arg4 != (uint32_t *)0x0) {
        *arg4 = text;
      }
      *arg7 = (int)stk_20;
      return i2;
    }
  }
  return 0;
}
#undef stk_20
#undef stk_1c
#undef stk_18
#undef stk_14

/* ParsePosType @ 0x080d0e80, 84 bytes
 *
 * Parses a "postype" value by its first letter: "p1" 0, "front" 1, "back" 2,
 * "left" 3, "right" 4, "p2" 5. Anything else gives -1.
 *
 * Parameters:
 *   arg1         char *
 *
 * Called by: SCtrlParseExplod, SCtrlParseHelper, SCtrlParseProjectile
 *
 * Elecbyte file: src/mugen/state-i.c
 */
int ParsePosType(char *arg1)

{
  switch(*(uint32_t *)(__ctype_tolower + *arg1 * 4)) {
  case 0x62:
    return 2;
  default:
    return -1;
  case 0x66:
    return 1;
  case 0x6c:
    return 3;
  case 0x70:
    return (uint32_t)(*(int *)(__ctype_tolower + arg1[1] * 4) == 0x32) * 5;
  case 0x72:
    return 4;
  }
}

/* ParseSpecialFlag @ 0x080d0ee0, 1025 bytes
 *
 * Parses an AssertSpecial flag name into its bit: intro, invisible,
 * roundnotover, nobardisplay, nobg, nofg, nostandguard, nocrouchguard,
 * noairguard, noautoturn, nojugglecheck, noko, nokosnd, nokoslow, noshadow,
 * globalnoshadow, nomusic, nowalk, timerfreeze, unguardable.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t *
 *   arg3         uint32_t *
 *
 * C library: strcpy, _alemu_strlwr, flag
 * Called by: SCtrlParseElemType
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol
 *       _alemu_strlwr
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t ParseSpecialFlag(char *arg1,uint32_t *arg2,uint32_t *arg3)

{
  int i1;
  uint8_t *pb2;
  uint8_t *pb3;
  bool b4;
  bool b5;
  bool b6;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(uint8_t (*)[76])(frame + 0x4))
  
  strcpy((char *)stk_5c,arg1);
  _alemu_strlwr((char *)stk_5c);
  b4 = 0;  /* dead flag (repz cmpsb, count 6) */
  b6 = 0;  /* dead flag (repz cmpsb, count 6) */
  i1 = 6;
  pb2 = stk_5c;
  pb3 = (uint8_t *)"intro";
  do {
    if (i1 == 0) break;
    i1 = i1 + -1;
    b4 = *pb2 < *pb3;
    b6 = *pb2 == *pb3;
    pb2 = pb2 + 1;
    pb3 = pb3 + 1;
  } while (b6);
  b5 = (!b4 && !b6) < b4;
  b4 = (!b4 && !b6) == b4;
  if (b4) {
    *arg2 = 0;
    *arg3 = 0;
  }
  else {
    i1 = 0xd;
    pb2 = stk_5c;
    pb3 = (uint8_t *)"roundnotover";
    do {
      if (i1 == 0) break;
      i1 = i1 + -1;
      b5 = *pb2 < *pb3;
      b4 = *pb2 == *pb3;
      pb2 = pb2 + 1;
      pb3 = pb3 + 1;
    } while (b4);
    b6 = (!b5 && !b4) < b5;
    b4 = (!b5 && !b4) == b5;
    if (b4) {
      *arg2 = 1;
      *arg3 = 0;
    }
    else {
      i1 = 5;
      pb2 = stk_5c;
      pb3 = &str_noko;
      do {
        if (i1 == 0) break;
        i1 = i1 + -1;
        b6 = *pb2 < *pb3;
        b4 = *pb2 == *pb3;
        pb2 = pb2 + 1;
        pb3 = pb3 + 1;
      } while (b4);
      b5 = (!b6 && !b4) < b6;
      b4 = (!b6 && !b4) == b6;
      if (b4) {
        *arg2 = 2;
        *arg3 = 0;
      }
      else {
        i1 = 8;
        pb2 = stk_5c;
        pb3 = &str_nokosnd;
        do {
          if (i1 == 0) break;
          i1 = i1 + -1;
          b5 = *pb2 < *pb3;
          b4 = *pb2 == *pb3;
          pb2 = pb2 + 1;
          pb3 = pb3 + 1;
        } while (b4);
        b6 = (!b5 && !b4) < b5;
        b4 = (!b5 && !b4) == b5;
        if (b4) {
          *arg2 = 3;
          *arg3 = 0;
        }
        else {
          i1 = 9;
          pb2 = stk_5c;
          pb3 = (uint8_t *)"nokoslow";
          do {
            if (i1 == 0) break;
            i1 = i1 + -1;
            b6 = *pb2 < *pb3;
            b4 = *pb2 == *pb3;
            pb2 = pb2 + 1;
            pb3 = pb3 + 1;
          } while (b4);
          b5 = (!b6 && !b4) < b6;
          b4 = (!b6 && !b4) == b6;
          if (b4) {
            *arg2 = 4;
            *arg3 = 0;
          }
          else {
            i1 = 8;
            pb2 = stk_5c;
            pb3 = (uint8_t *)"nomusic";
            do {
              if (i1 == 0) break;
              i1 = i1 + -1;
              b5 = *pb2 < *pb3;
              b4 = *pb2 == *pb3;
              pb2 = pb2 + 1;
              pb3 = pb3 + 1;
            } while (b4);
            b6 = (!b5 && !b4) < b5;
            b4 = (!b5 && !b4) == b5;
            if (b4) {
              *arg2 = 5;
              *arg3 = 0;
            }
            else {
              i1 = 0xf;
              pb2 = stk_5c;
              pb3 = (uint8_t *)"globalnoshadow";
              do {
                if (i1 == 0) break;
                i1 = i1 + -1;
                b6 = *pb2 < *pb3;
                b4 = *pb2 == *pb3;
                pb2 = pb2 + 1;
                pb3 = pb3 + 1;
              } while (b4);
              b5 = (!b6 && !b4) < b6;
              b4 = (!b6 && !b4) == b6;
              if (b4) {
                *arg2 = 6;
                *arg3 = 0;
              }
              else {
                i1 = 0xc;
                pb2 = stk_5c;
                pb3 = (uint8_t *)"timerfreeze";
                do {
                  if (i1 == 0) break;
                  i1 = i1 + -1;
                  b5 = *pb2 < *pb3;
                  b4 = *pb2 == *pb3;
                  pb2 = pb2 + 1;
                  pb3 = pb3 + 1;
                } while (b4);
                b6 = (!b5 && !b4) < b5;
                b4 = (!b5 && !b4) == b5;
                if (b4) {
                  *arg2 = 7;
                  *arg3 = 0;
                }
                else {
                  i1 = 0xd;
                  pb2 = stk_5c;
                  pb3 = (uint8_t *)"nobardisplay";
                  do {
                    if (i1 == 0) break;
                    i1 = i1 + -1;
                    b6 = *pb2 < *pb3;
                    b4 = *pb2 == *pb3;
                    pb2 = pb2 + 1;
                    pb3 = pb3 + 1;
                  } while (b4);
                  b5 = (!b6 && !b4) < b6;
                  b4 = (!b6 && !b4) == b6;
                  if (b4) {
                    *arg2 = 8;
                    *arg3 = 0;
                  }
                  else {
                    i1 = 5;
                    pb2 = stk_5c;
                    pb3 = &str_nobg;
                    do {
                      if (i1 == 0) break;
                      i1 = i1 + -1;
                      b5 = *pb2 < *pb3;
                      b4 = *pb2 == *pb3;
                      pb2 = pb2 + 1;
                      pb3 = pb3 + 1;
                    } while (b4);
                    b6 = (!b5 && !b4) < b5;
                    b4 = (!b5 && !b4) == b5;
                    if (b4) {
                      *arg2 = 9;
                      *arg3 = 0;
                    }
                    else {
                      i1 = 5;
                      pb2 = stk_5c;
                      pb3 = &str_nofg;
                      do {
                        if (i1 == 0) break;
                        i1 = i1 + -1;
                        b6 = *pb2 < *pb3;
                        b4 = *pb2 == *pb3;
                        pb2 = pb2 + 1;
                        pb3 = pb3 + 1;
                      } while (b4);
                      b5 = (!b6 && !b4) < b6;
                      b4 = (!b6 && !b4) == b6;
                      if (b4) {
                        *arg2 = 10;
                        *arg3 = 0;
                      }
                      else {
                        i1 = 0xd;
                        pb2 = stk_5c;
                        pb3 = (uint8_t *)"nostandguard";
                        do {
                          if (i1 == 0) break;
                          i1 = i1 + -1;
                          b5 = *pb2 < *pb3;
                          b4 = *pb2 == *pb3;
                          pb2 = pb2 + 1;
                          pb3 = pb3 + 1;
                        } while (b4);
                        b6 = (!b5 && !b4) < b5;
                        b4 = (!b5 && !b4) == b5;
                        if (b4) {
                          *arg2 = 0;
                          *arg3 = 1;
                        }
                        else {
                          i1 = 0xe;
                          pb2 = stk_5c;
                          pb3 = (uint8_t *)"nocrouchguard";
                          do {
                            if (i1 == 0) break;
                            i1 = i1 + -1;
                            b6 = *pb2 < *pb3;
                            b4 = *pb2 == *pb3;
                            pb2 = pb2 + 1;
                            pb3 = pb3 + 1;
                          } while (b4);
                          b5 = (!b6 && !b4) < b6;
                          b4 = (!b6 && !b4) == b6;
                          if (b4) {
                            *arg2 = 1;
                            *arg3 = 1;
                          }
                          else {
                            i1 = 0xb;
                            pb2 = stk_5c;
                            pb3 = (uint8_t *)"noairguard";
                            do {
                              if (i1 == 0) break;
                              i1 = i1 + -1;
                              b5 = *pb2 < *pb3;
                              b4 = *pb2 == *pb3;
                              pb2 = pb2 + 1;
                              pb3 = pb3 + 1;
                            } while (b4);
                            b6 = (!b5 && !b4) < b5;
                            b4 = (!b5 && !b4) == b5;
                            if (b4) {
                              *arg2 = 2;
                              *arg3 = 1;
                            }
                            else {
                              i1 = 0xb;
                              pb2 = stk_5c;
                              pb3 = (uint8_t *)"noautoturn";
                              do {
                                if (i1 == 0) break;
                                i1 = i1 + -1;
                                b6 = *pb2 < *pb3;
                                b4 = *pb2 == *pb3;
                                pb2 = pb2 + 1;
                                pb3 = pb3 + 1;
                              } while (b4);
                              b5 = (!b6 && !b4) < b6;
                              b4 = (!b6 && !b4) == b6;
                              if (b4) {
                                *arg2 = 3;
                                *arg3 = 1;
                              }
                              else {
                                i1 = 9;
                                pb2 = stk_5c;
                                pb3 = (uint8_t *)(int)&str_noshadow;
                                do {
                                  if (i1 == 0) break;
                                  i1 = i1 + -1;
                                  b5 = *pb2 < *pb3;
                                  b4 = *pb2 == *pb3;
                                  pb2 = pb2 + 1;
                                  pb3 = pb3 + 1;
                                } while (b4);
                                b6 = (!b5 && !b4) < b5;
                                b4 = (!b5 && !b4) == b5;
                                if (b4) {
                                  *arg2 = 4;
                                  *arg3 = 1;
                                }
                                else {
                                  i1 = 0xe;
                                  pb2 = stk_5c;
                                  pb3 = (uint8_t *)"nojugglecheck";
                                  do {
                                    if (i1 == 0) break;
                                    i1 = i1 + -1;
                                    b6 = *pb2 < *pb3;
                                    b4 = *pb2 == *pb3;
                                    pb2 = pb2 + 1;
                                    pb3 = pb3 + 1;
                                  } while (b4);
                                  b5 = (!b6 && !b4) < b6;
                                  b4 = (!b6 && !b4) == b6;
                                  if (b4) {
                                    *arg2 = 5;
                                    *arg3 = 1;
                                  }
                                  else {
                                    i1 = 7;
                                    pb2 = stk_5c;
                                    pb3 = (uint8_t *)"nowalk";
                                    do {
                                      if (i1 == 0) break;
                                      i1 = i1 + -1;
                                      b5 = *pb2 < *pb3;
                                      b4 = *pb2 == *pb3;
                                      pb2 = pb2 + 1;
                                      pb3 = pb3 + 1;
                                    } while (b4);
                                    b6 = (!b5 && !b4) < b5;
                                    b4 = (!b5 && !b4) == b5;
                                    if (b4) {
                                      *arg2 = 6;
                                      *arg3 = 1;
                                    }
                                    else {
                                      i1 = 0xc;
                                      pb2 = stk_5c;
                                      pb3 = (uint8_t *)"unguardable";
                                      do {
                                        if (i1 == 0) break;
                                        i1 = i1 + -1;
                                        b6 = *pb2 < *pb3;
                                        b4 = *pb2 == *pb3;
                                        pb2 = pb2 + 1;
                                        pb3 = pb3 + 1;
                                      } while (b4);
                                      b5 = (!b6 && !b4) < b6;
                                      b4 = (!b6 && !b4) == b6;
                                      if (b4) {
                                        *arg2 = 7;
                                        *arg3 = 1;
                                      }
                                      else {
                                        i1 = 10;
                                        pb2 = stk_5c;
                                        pb3 = (uint8_t *)"invisible";
                                        do {
                                          if (i1 == 0) break;
                                          i1 = i1 + -1;
                                          b5 = *pb2 < *pb3;
                                          b4 = *pb2 == *pb3;
                                          pb2 = pb2 + 1;
                                          pb3 = pb3 + 1;
                                        } while (b4);
                                        if ((!b5 && !b4) != b5) {
                                          return 0;
                                        }
                                        *arg2 = 8;
                                        *arg3 = 1;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 1;
}
#undef stk_5c

/* ParseAnim @ 0x080d12f0, 119 bytes
 *
 * Parses an animation reference with optional "S" prefix (use the player's
 * own animations) into an expression list.
 *
 * Parameters:
 *   text         uint8_t *
 *   arg2         int *
 *   arg3         uint32_t *
 *   player       int
 *
 * Calls: SCtrlReadExpList
 * Called by: SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
bool ParseAnim(uint8_t *text,int *arg2,uint32_t *arg3,int player)

{
  int i1;
  uint8_t *rest2;
  char *entry_ECX;
  bool b3;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_8 (*(char **)(frame + 0x8))
  
  if (text == (uint8_t *)0x0) {
    return true;
  }
  i1 = *(int *)(__ctype_tolower + (char)*text * 4);
  if (i1 == 0x66) {
    *arg3 = 1;
  }
  else {
    if (i1 != 0x73) goto L_080d132f;
    *arg3 = 0;
  }
  text = text + 1;
L_080d132f:
  stk_8 = entry_ECX;
  rest2 = SCtrlReadExpList(text,"i",player,&stk_8,arg2);
  if (rest2 == (uint8_t *)0x0) {
    b3 = false;
  }
  else {
    b3 = *stk_8 == '\0';
  }
  return b3;
}
#undef stk_8

/* ParseSnd @ 0x080d1370, 128 bytes
 *
 * Parses a sound reference "[S]group, number" (the "S" prefix selects the
 * player's own sounds instead of common.snd) into an expression list.
 *
 * Parameters:
 *   text         uint8_t *
 *   arg2         int *
 *   arg3         int *
 *   arg4         uint32_t *
 *   player       int
 *
 * Calls: SCtrlReadExpList
 * Called by: SCtrlParseHitDef, SCtrlParsePlaySndInfo, SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t ParseSnd(uint8_t *text,int *arg2,int *arg3,uint32_t *arg4,int player)

{
  int i1;
  uint8_t *rest2;
  uint32_t u3;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_8 (*(char **)(frame + 0x8))
  
  if (text == (uint8_t *)0x0) {
    return 1;
  }
  i1 = *(int *)(__ctype_tolower + (char)*text * 4);
  if (i1 == 0x66) {
    *arg4 = 1;
  }
  else {
    if (i1 != 0x73) goto L_080d13af;
    *arg4 = 0;
  }
  text = text + 1;
L_080d13af:
  rest2 = SCtrlReadExpList(text,"ii",player,&stk_8,arg2,arg3);
  if (rest2 == (uint8_t *)0x0) {
    u3 = 0;
  }
  else {
    u3 = (uint32_t)(*stk_8 == '\0');
  }
  return u3;
}
#undef stk_8

/* ParseVel @ 0x080d13f0, 306 bytes
 *
 * Parses a velocity pair "x, y" into two float expressions (constant ones
 * folded).
 *
 * Parameters:
 *   text         uint8_t *
 *   expr         int *
 *   expr2        int *  (expr)
 *   player       int
 *
 * Calls: ConstExpF, InfixToPostfix
 * Called by: SCtrlParseHitDef
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
bool ParseVel(uint8_t *text,int *expr,int *expr2,int player)

{
  uint8_t b1;
  int i2;
  uint8_t *text2;
  uint8_t *pb4;
  bool b5;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(uint8_t **)(frame + 0x0))
  
  if (text == (uint8_t *)0x0) {
    return true;
  }
  if ((*(int *)(__ctype_tolower + (char)*text * 4) == 0x6e) &&
     ((((*(uint8_t *)(__ctype_b + 1 + (char)text[1] * 2) & 0x20) != 0 || (text[1] == 0x2c)) ||
      (text[1] == 0)))) {
    ConstExpF(expr,-0x39001000);
    text2 = text + 1;
L_080d1471:
    if (*text2 != 0x2c) {
      return *text2 == 0;
    }
    do {
      pb4 = text2;
      text2 = pb4 + 1;
    } while ((*(uint8_t *)(__ctype_b + 1 + (char)*text2 * 2) & 0x20) != 0);
    if ((*(int *)(__ctype_tolower + (char)*text2 * 4) == 0x6e) &&
       (((*(uint8_t *)(__ctype_b + 1 + (char)pb4[2] * 2) & 0x20) != 0 || (pb4[2] == 0)))) {
      ConstExpF(expr2,-0x39001000);
      stk_10 = pb4 + 2;
    }
    else {
      i2 = InfixToPostfix(text2,expr2,player,&stk_10,2);
      if (i2 == 0) goto L_080d14f0;
    }
    b1 = *(uint8_t *)(__ctype_b + 1 + (char)*stk_10 * 2);
    while ((b1 & 0x20) != 0) {
      stk_10 = stk_10 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + (char)*stk_10 * 2);
    }
    b5 = *stk_10 == 0;
  }
  else {
    i2 = InfixToPostfix(text,expr,player,&stk_10,2);
    text2 = stk_10;
    if (i2 != 0) goto L_080d1471;
L_080d14f0:
    b5 = false;
  }
  return b5;
}
#undef stk_10

/* ParseHitAttr @ 0x080d1530, 796 bytes
 *
 * Parses a hit attribute string such as "SCA, NA, SA" (state types S/C/A,
 * then attack types N/S/H and A/T/P) into attribute bits. Used by HitDef
 * attr, HitBy/NotHitBy, HitOverride and the HitDefAttr trigger.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: SCtrlParseElemType, SCtrlParseHitDef, SCtrlParseHitOverride,
 *            SCtrlParseTrigger
 *
 * Elecbyte file: src/mugen/state-i.c
 * Note: decompiler flag: type propagation did not settle
 */
uint32_t ParseHitAttr(int arg1,int arg2)

{
  uint8_t b1;
  int i2;
  int i3;
  char c4;
  uint32_t u5;
  
  u5 = 0;
  if (arg1 == 0) {
    return 0xffffffff;
  }
  i2 = (int)*(char *)arg1;
  i3 = 0;
  b1 = *(uint8_t *)(__ctype_b + 1 + i2 * 2);
  while ((b1 & 4) != 0) {
    i2 = *(int *)(__ctype_tolower + i2 * 4);
    if (i2 == 99) {
      u5 = u5 | 2;
    }
    else if (i2 < 100) {
      if (i2 != 0x61) {
        return 0xffffffff;
      }
      u5 = u5 | 4;
    }
    else {
      if (i2 != 0x73) {
        return 0xffffffff;
      }
      u5 = u5 | 1;
    }
    i3 = i3 + 1;
    i2 = (int)*(char *)(i3 + arg1);
    b1 = *(uint8_t *)(__ctype_b + 1 + i2 * 2);
  }
  c4 = *(char *)(i3 + arg1);
  while (c4 != '\0') {
    if ((*(uint8_t *)(__ctype_b + 1 + *(char *)(i3 + arg1) * 2) & 0x20) != 0) {
      do {
        i3 = i3 + 1;
      } while ((*(uint8_t *)(__ctype_b + 1 + *(char *)(i3 + arg1) * 2) & 0x20) != 0);
      c4 = *(char *)(i3 + arg1);
    }
    if (c4 != ',') break;
    i3 = i3 + 1;
    i2 = (int)*(char *)(i3 + arg1);
    b1 = *(uint8_t *)(__ctype_b + 1 + i2 * 2);
    while ((b1 & 0x20) != 0) {
      i3 = i3 + 1;
      i2 = (int)*(char *)(i3 + arg1);
      b1 = *(uint8_t *)(__ctype_b + 1 + i2 * 2);
    }
    i2 = *(int *)(__ctype_tolower + i2 * 4);
    if (i2 == 0x68) {
      i2 = *(int *)(__ctype_tolower + *(char *)(i3 + 1 + arg1) * 4);
      if (i2 == 0x61) {
        u5 = u5 | 0x20;
        i3 = i3 + 1;
      }
      else if (i2 < 0x62) {
        if (i2 != 0x20) {
          if (i2 < 0x21) goto L_join_080d1752;
L_join_080d1769:
          if (i2 != 0x2c) {
            return 0xffffffff;
          }
        }
L_080d1820:
        u5 = u5 | 0x920;
      }
      else if (i2 == 0x70) {
        u5 = u5 | 0x800;
        i3 = i3 + 1;
      }
      else {
        if (i2 != 0x74) {
          return 0xffffffff;
        }
        u5 = u5 | 0x100;
        i3 = i3 + 1;
      }
    }
    else if (i2 < 0x69) {
      if (i2 != 0x61) {
        return 0xffffffff;
      }
      i2 = *(int *)(__ctype_tolower + *(char *)(i3 + 1 + arg1) * 4);
      if (i2 == 0x61) {
        u5 = u5 | 0x38;
        i3 = i3 + 1;
      }
      else {
        if (i2 < 0x62) {
          if (i2 != 0x20) {
            if (0x20 < i2) goto L_join_080d1769;
L_join_080d1752:
            if ((i2 != 0) && (i2 != 9)) {
              return 0xffffffff;
            }
          }
          goto L_080d1820;
        }
        if (i2 == 0x70) {
          u5 = u5 | 0xe00;
          i3 = i3 + 1;
        }
        else {
          if (i2 != 0x74) {
            return 0xffffffff;
          }
          u5 = u5 | 0x1c0;
          i3 = i3 + 1;
        }
      }
    }
    else if (i2 == 0x6e) {
      i2 = *(int *)(__ctype_tolower + *(char *)(i3 + 1 + arg1) * 4);
      if (i2 == 0x61) {
        u5 = u5 | 8;
        i3 = i3 + 1;
      }
      else if (i2 < 0x62) {
        if (i2 != 0x20) {
          if (i2 < 0x21) {
            if ((i2 != 0) && (i2 != 9)) {
              return 0xffffffff;
            }
          }
          else if (i2 != 0x2c) {
            return 0xffffffff;
          }
        }
        u5 = u5 | 0x248;
      }
      else if (i2 == 0x70) {
        u5 = u5 | 0x200;
        i3 = i3 + 1;
      }
      else {
        if (i2 != 0x74) {
          return 0xffffffff;
        }
        u5 = u5 | 0x40;
        i3 = i3 + 1;
      }
    }
    else {
      if (i2 != 0x73) {
        return 0xffffffff;
      }
      i2 = *(int *)(__ctype_tolower + *(char *)(i3 + 1 + arg1) * 4);
      if (i2 == 0x61) {
        u5 = u5 | 0x10;
        i3 = i3 + 1;
      }
      else if (i2 < 0x62) {
        if (i2 != 0x20) {
          if (i2 < 0x21) {
            if ((i2 != 0) && (i2 != 9)) {
              return 0xffffffff;
            }
          }
          else if (i2 != 0x2c) {
            return 0xffffffff;
          }
        }
        u5 = u5 | 0x490;
      }
      else if (i2 == 0x70) {
        u5 = u5 | 0x400;
        i3 = i3 + 1;
      }
      else {
        if (i2 != 0x74) {
          return 0xffffffff;
        }
        u5 = u5 | 0x80;
        i3 = i3 + 1;
      }
    }
    i3 = i3 + 1;
    c4 = *(char *)(i3 + arg1);
  }
  if (arg2 != 0) {
    *(int *)arg2 = i3 + arg1;
  }
  return u5;
}

/* ParseHitFlag @ 0x080d1850, 130 bytes
 *
 * Parses a HitDef hitflag/guardflag string into flag bits. Letters
 * (case-insensitive): H, L, M, A, F, D, P, '+' and '-'. In .cns terms: H
 * high, L low, M mid (H and L), A air, F fall, D down, P. '+' and '-'
 * restrict the hit to players that are, or are not, already in a get-hit
 * state. In bits, '+' sets 0x100 and '-' clears bit 1 of the default value
 * 2.
 *
 * Parameters:
 *   arg1         char *
 *
 * Called by: SCtrlParseHitDef
 *
 * Elecbyte file: src/mugen/state-i.c
 */
uint32_t ParseHitFlag(char *arg1)

{
  char c1;
  int i2;
  uint32_t u3;
  
  i2 = 0;
  u3 = 2;
  c1 = *arg1;
  while (c1 != '\0') {
    switch(*(uint32_t *)(__ctype_tolower + arg1[i2] * 4)) {
    case 0x2b:
      u3 = u3 | 0x100;
      break;
    case 0x2d:
      u3 = u3 & 0xfffffffd;
      break;
    case 0x61:
      u3 = u3 | 0x10;
      break;
    case 100:
      u3 = u3 | 0x40;
      break;
    case 0x66:
      u3 = u3 | 0x20;
      break;
    case 0x68:
      u3 = u3 | 4;
      break;
    case 0x6c:
      u3 = u3 | 8;
      break;
    case 0x6d:
      u3 = u3 | 0xc;
      break;
    case 0x70:
      u3 = u3 | 0x80;
    }
    i2 = i2 + 1;
    c1 = arg1[i2];
  }
  return u3;
}

/* PlayerGetRedirInfo @ 0x080d18e0, 200 bytes
 *
 * Fills the redirection record of a player: itself, its parent and root
 * (helpers), and its partner and enemies, so that redirected triggers and
 * controllers can find them.
 *
 * Parameters:
 *   player       int
 *   arg2         uint32_t *
 *
 * Player fields read: teamside
 * Calls: HelperParent, HelperRoot
 * Called by: PlayerSCtrlUpdate, PlayerSCtrlUpdateSpec
 *
 * Elecbyte file: src/mugen/state-i.c
 */
void PlayerGetRedirInfo(int player,uint32_t *arg2)

{
  int i1;
  uint32_t player2;
  uint32_t player3;
  int *pi4;
  
  pi4 = g;
  *arg2 = 0;
  arg2[1] = player;
  arg2[2] = 0;
  arg2[3] = 0;
  arg2[4] = 0;
  if (pi4[0x731d] == 0) {
    i1 = *(int *)(player + PLB_TEAMSIDE);
    *arg2 = *(uint32_t *)(player + 0x3424);
    if (i1 == 1) {
      arg2[1] = pi4[0x73da];
    }
    pi4 = g;
    if (i1 == 2) {
      arg2[1] = g[0x73db];
    }
  }
  i1 = pi4[0x73da];
  if (player == i1) {
    i1 = pi4[0x73dc];
  }
  else if (player != pi4[0x73dc]) {
    i1 = pi4[0x73db];
    if (player == i1) {
      i1 = pi4[0x73dd];
    }
    else if (player != pi4[0x73dd]) goto L_080d198b;
  }
  arg2[2] = i1;
L_080d198b:
  player2 = HelperParent(player);
  arg2[3] = player2;
  player3 = HelperRoot(player);
  arg2[4] = player3;
  return;
}

