/*
 * arith.c -- expressions
 * The trigger and parameter expression compiler (infix to postfix) and the
 * stack interpreter that evaluates expressions for a player.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/arith.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ipow @ 0x08082880, 74 bytes
 *
 * Integer power a^b by binary exponentiation (b >= 0); used by the "**"
 * operator for ints.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: EvalExpression
 *
 * Elecbyte file: src/mugen/arith.c
 */
int ipow(int arg1,int arg2)

{
  int i1;
  uint8_t b2;
  
  b2 = 1;
  i1 = 1;
  if ((arg2 != 0) && (i1 = arg1, 1 < arg2)) {
    do {
      i1 = i1 * i1;
      if ((arg2 >> (b2 - 1 & 0x1f) & 1U) != 0) {
        i1 = i1 * arg1;
      }
      b2 = b2 + 1;
    } while (1 << (b2 & 0x1f) <= arg2);
  }
  return i1;
}

/* StackErrorExit @ 0x080828d0, 26 bytes
 *
 * Fatal error "Parser stack overflow error" (expression too deeply nested).
 *
 * Calls: ErrorExit
 * C library: sprintf
 * Called by: InfToPostArray
 * Messages:
 *   "Parser stack overflow error"
 *
 * Elecbyte file: src/mugen/arith.c
 */
void StackErrorExit(void)

{
  sprintf((char *)ErrorMessage,"Parser stack overflow error");
  ErrorExit();
  return;
}

/* PriorityCheck @ 0x080828f0, 137 bytes
 *
 * Returns the precedence of an operator code for the infix-to-postfix
 * conversion (higher binds tighter): unary operators, "**", "* / %", "+ -",
 * comparisons, "=" / "!=", the bitwise and logical operators.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: InfToPostArray
 *
 * Elecbyte file: src/mugen/arith.c
 */
uint32_t PriorityCheck(uint32_t arg1)

{
  switch(arg1) {
  case 1:
  case 2:
    return 8;
  case 3:
  case 4:
  case 5:
  case 6:
    return 10;
  case 7:
  case 8:
  case 9:
  case 10:
    return 9;
  case 0xb:
    return 3;
  case 0xc:
    return 1;
  case 0xd:
  case 0x13:
  case 0x16:
    return 0xe;
  case 0xe:
    return 2;
  case 0xf:
    return 0xd;
  case 0x10:
    return 6;
  case 0x11:
    return 4;
  case 0x12:
    return 5;
  case 0x14:
  case 0x15:
    return 7;
  case 0x17:
  case 0x18:
    return 0xb;
  case 0x19:
  case 0x1a:
  case 0x1b:
    return 0xc;
  case 0x1c:
  case 0x1d:
    return 0xf;
  default:
    return 0;
  }
}

/* OpLength @ 0x08082980, 35 bytes
 *
 * Returns the number of characters of an operator code's token (1 or 2:
 * "&&", "||", "^^", "**", "!=", "<=", ">=", ":=").
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: InfToPostArray
 *
 * Elecbyte file: src/mugen/arith.c
 */
uint32_t OpLength(uint32_t arg1)

{
  switch(arg1) {
  case 1:
  case 3:
  case 4:
  case 0xd:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    return 1;
  case 2:
  case 5:
  case 6:
  case 0xb:
  case 0xc:
  case 0xe:
  case 0xf:
  case 0x14:
  case 0x15:
    return 2;
  default:
    return 0;
  }
}

/* OpTypeCheck @ 0x080829b0, 37 bytes
 *
 * Returns true if operator `op` accepts an operand of type `type` (int-only
 * operators such as "%", "&", "|", "~" reject floats).
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *
 * Called by: EvalExpression
 *
 * Elecbyte file: src/mugen/arith.c
 */
bool OpTypeCheck(uint32_t arg1,int arg2)

{
  switch(arg1) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x13:
  case 0x15:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1c:
  case 0x1d:
    return true;
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x14:
  case 0x16:
  case 0x1b:
    return arg2 == 1;
  default:
    return false;
  }
}

/* OperCode @ 0x080829e0, 228 bytes
 *
 * Returns the operator code of the operator at the start of `text`: "!",
 * "!=", "%", "&", "&&", "(", ")", "*", "**", "+", "-", "/", ":", "<", "<=",
 * "=", ">", ">=", "^", "^^", "|", "||", "~". Returns 0 if there is no
 * operator there.
 *
 * Parameters:
 *   arg1         uint8_t *
 *
 * Called by: InfToPostArray
 *
 * Elecbyte file: src/mugen/arith.c
 */
int OperCode(uint8_t *arg1)

{
  switch(*arg1) {
  case 0x21:
    return ((arg1[1] != '=') - 1 & 0xfffffff5) + 0xd;
  default:
    return 0;
  case 0x25:
    return 0x1b;
  case 0x26:
    return (uint32_t)(arg1[1] != '&') * 5 + 0xb;
  case 0x28:
    return 0x1c;
  case 0x29:
    return 0x1d;
  case 0x2a:
    return ((arg1[1] != '*') - 1 & 0xfffffff6) + 0x19;
  case 0x2b:
    return 0x17;
  case 0x2d:
    return 0x18;
  case 0x2f:
    return 0x1a;
  case 0x3a:
    return ((arg1[1] == '=') - 1 & 0xffffffec) + 0x14;
  case 0x3c:
    return (uint32_t)(arg1[1] == '=') * 2 + 4;
  case 0x3d:
    return 1;
  case 0x3e:
    return (uint32_t)(arg1[1] == '=') * 2 + 3;
  case 0x5e:
    return (uint32_t)(arg1[1] != '^') * 4 + 0xe;
  case 0x7c:
    return (uint32_t)(arg1[1] != '|') * 5 + 0xc;
  case 0x7e:
    return 0x16;
  }
}

/* InfToPostArray @ 0x08082ad0, 3243 bytes
 *
 * The expression compiler. Converts an infix expression (the text of a
 * trigger or parameter) into postfix code with the shunting-yard method.
 * Numbers become int or float constants. Names become trigger codes
 * (SCtrlParseTrigger), with their arguments compiled recursively. Operators
 * are ordered by PriorityCheck, and interval comparisons ("= [a, b]") are
 * expanded. The result types are checked against `want_type`. Stops at `end`
 * (for comma-separated lists). Returns the number of code words, or 0 on a
 * syntax error (message in ErrorMessage).
 *
 * Parameters:
 *   text         uint8_t *
 *   values       float *
 *   types        void *
 *   player       int
 *   max_tokens   uint8_t *
 *   end          uint32_t *
 *   want_type    int
 *
 * Calls: OperCode, PriorityCheck, TriggerFree, SCtrlParseTrigger,
 *        StackErrorExit, OpLength, SCtrlTrigArity
 * C library: strlen, __strtol_internal, __strtod_internal,
 *            __builtin_memcpy, memcpy, sprintf
 * Called by: InfixToPostfix, SCtrlReadExpListArray
 * Messages:
 *   "Died parsing %s"
 *   "Expected int value and read float."
 *   "Malformed expression encountered: %s"
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: float words copied as bytes: 4 copies, 0 array reads (apply_bits_copies)
 * Note: Locals live in `frame`, laid out as on the original stack (0x5f0 bytes,
 *       16 variables), because their address is taken.
 */
char * InfToPostArray(uint8_t *text,float *values,void *types,int player,uint8_t *max_tokens,
                     uint32_t *end,int want_type)

{
  int *pi1;
  char c2;
  size_t s3;
  uint32_t stale_var;
  uint8_t *pb4;
  uint8_t *stale_ECX;
  uint8_t *stale_ECX_00;
  uint32_t u5;
  uint8_t b6;
  char *pc7;
  int i2;
  int j;
  float *pf10;
  uint8_t *pb11;
  float *pf12;
  bool b13;
  bool b14;
  float80 l15;
  char *rest2;
  int vstack [132];
  unsigned char frame[0x5f0] __attribute__((aligned(16)));
#define text2 (*(uint8_t **)(frame + 0xc))
#define stk_5c8 (*(uint32_t *)(frame + 0x28))
#define stk_5c4 (*(uint32_t *)(frame + 0x2c))
#define stk_5ac (*(int *)(frame + 0x44))
#define stk_5a8 (*(int *)(frame + 0x48))
#define stk_5a4 (*(char **)(frame + 0x4c))
#define stk_5a0 (*(char **)(frame + 0x50))
#define stk_59c (*(int *)(frame + 0x54))
#define stk_598 (*(char **)(frame + 0x58))
#define stk_594 (*(char **)(frame + 0x5c))
#define stk_590 (*(uint8_t *(*)[12])(frame + 0x60))
#define stk_560 (*(float *)(frame + 0x90))
#define stk_55c (*(uint8_t (*)[64])(frame + 0x94))
#define stk_51c (*(char (*)[128])(frame + 0xd4))
#define stk_49c (*(uint8_t (*)[128])(frame + 0x154))
#define stk_41c (*(float (*)[127])(frame + 0x1d4))
  
  stk_59c = 0;
  stk_5a0 = (char *)0x0;
  stk_5a4 = (char *)0x0;
  stk_5a8 = -1;
  stk_5ac = 0;
  if (text == (uint8_t *)0x0) {
    return (char *)0xffffffff;
  }
  text2 = text;
L_08083527:
  do {
    s3 = strlen((char *)text2);
    pb4 = stale_ECX;
    if ((s3 == 0) || ((pb4 = text2, end != (uint32_t *)0x0 && (*text2 == 0x2c)))
       ) {
L_08083557:
      if (stk_5a8 < 0) goto L_080835a3;
      pb4 = stk_55c;
      goto L_08083573;
    }
    if ((((*(uint8_t *)(__ctype_b + 1 + (char)*text2 * 2) & 8) != 0) ||
        ((((b6 = *text2, b6 == 0x2d &&
           ((*(uint8_t *)(__ctype_b + 1 + (char)text2[1] * 2) & 8) != 0)) ||
          ((b6 == 0x2e && ((*(uint8_t *)(__ctype_b + 1 + (char)text2[1] * 2) & 8) != 0)))) ||
         (((b6 == 0x2d && (text2[1] == 0x2e)) &&
          ((*(uint8_t *)(__ctype_b + 1 + (char)text2[2] * 2) & 8) != 0)))))) &&
       (((stk_5ac != 1 && (stk_5ac != 4)) && (stk_5ac != 6)))) {
      stk_5ac = 1;
      if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
      u5 = __strtol_internal(text2,stk_590,10,0);
      b13 = *stk_590[0] < 0x2e;
      if (*stk_590[0] == 0x2e) {
L_08082c18:
        l15 = __strtod_internal((int)text2,(int *)stk_590,0);
        stk_560 = (float)l15;
        vstack[(int)(stk_5a0 + 1)] = BITS_F2I(int, stk_560);
        stk_5a0[(int)stk_49c] = '\x01';
      }
      else {
        i2 = 2;
        b14 = false;
        pb11 = &str_empty_74ff;
        do {
          if (i2 == 0) break;
          i2 = i2 + -1;
          b13 = *pb4 < *pb11;
          b14 = *pb4 == *pb11;
          pb4 = pb4 + 1;
          pb11 = pb11 + 1;
        } while (b14);
        if ((!b13 && !b14) == b13) goto L_08082c18;
        vstack[(int)(stk_5a0 + 1)] = u5;
        stk_5a0[(int)stk_49c] = '\0';
      }
      stk_5a0 = stk_5a0 + 1;
      text2 = stk_590[0];
      goto L_08083527;
    }
    i2 = OperCode(text2);
    if (i2 == 0) {
      b6 = *text2;
    }
    else {
      b13 = false;
      b6 = *text2;
      pb4 = (uint8_t *)0x0;
      if ((b6 == 0x28) || (b6 == 0x5b)) {
        pb4 = (uint8_t *)0x1;
      }
      if (pb4 == (uint8_t *)0x0) {
        pb4 = (uint8_t *)0x0;
        if ((b6 == 0x29) || (b6 == 0x5d)) {
          pb4 = (uint8_t *)0x1;
        }
        if (pb4 != (uint8_t *)0x0) goto L_08082ccc;
      }
      else {
L_08082ccc:
        b13 = true;
      }
      if (!b13) {
        if ((i2 == 0x18) && (((stk_5ac == 0 || (stk_5ac == 5)) || (stk_5ac == 2)))) {
          i2 = 0x13;
        }
        if (stk_5ac == 2) {
          c2 = (char)i2;
          b13 = false;
          if (((c2 == '\r') || (c2 == '~')) || (c2 == '\x13')) {
            b13 = true;
          }
          if (!b13) goto L_0808373b;
        }
        if (i2 == 0x14) {
          if (stk_5ac != 4) goto L_0808373b;
          pi1 = (int *)vstack[(int)stk_5a0];
          if ((1 < *pi1 - 0x157U) || (pi1[1] != 0)) goto L_0808373b;
          if (*pi1 == 0x158) {
            i2 = 0x15;
          }
          j = PriorityCheck((int)(char)i2);
          if ((((j < stk_59c) && (b6 = stk_55c[stk_5a8], b6 != 0x1c)) &&
              (b6 != 0x14)) && (b6 != 0x15)) goto L_0808373b;
          TriggerFree(pi1);
          stk_5a0 = stk_5a0 + -1;
        }
        stk_5ac = 2;
        do {
          b13 = false;
          if (i2 == 0x14) {
L_08082e51:
            b13 = true;
          }
          else {
            b14 = false;
            if (((i2 == 0xd) || (i2 == 0x7e)) || (i2 == 0x13)) {
              b14 = true;
            }
            if (b14) goto L_08082e51;
          }
          if ((b13) || (j = PriorityCheck(i2), stk_59c < j)) {
            b13 = false;
            if (i2 == 0x14) {
L_08082e91:
              b13 = true;
            }
            else {
              b14 = false;
              if (((i2 == 0xd) || (i2 == 0x7e)) || (i2 == 0x13)) {
                b14 = true;
              }
              if (b14) goto L_08082e91;
            }
            if ((!b13) || (j = PriorityCheck(i2), stk_59c <= j)) goto L_08082e9e;
          }
          if (stk_5a8 == -1) goto L_08082e9e;
          vstack[(int)(stk_5a0 + 1)] = (int)(char)stk_55c[stk_5a8];
          stk_5a0[(int)stk_49c] = '\x02';
          stk_5a0 = stk_5a0 + 1;
          j = stk_5a8 + -1;
          if (j < 0) {
            stk_59c = 0;
            stk_5a8 = j;
          }
          else {
            stk_59c = PriorityCheck((int)(char)stk_55c[stk_5a8 + -1]);
            stk_5a8 = j;
          }
        } while( true );
      }
    }
    if (b6 != 0x5b) {
      if (b6 != 0x28) {
        b13 = false;
        if ((b6 == 0x29) || (b6 == 0x5d)) {
          b13 = true;
        }
        if (b13) {
          if (end != (uint32_t *)0x0) goto L_08083557;
          goto L_0808373b;
        }
        b13 = false;
        if (((*(uint8_t *)(__ctype_b + (char)b6 * 2) & 8) != 0) || (b6 == 0x5f)) {
          b13 = true;
        }
        if (b13) {
          rest2 = SCtrlParseTrigger((char *)text2,player,vstack + (int)(stk_5a0 + 1),
                                      stk_49c + (int)stk_5a0,(int)max_tokens - (int)stk_5a0,
                                      (int *)stk_590);
          if (rest2 == (char *)0x0) {
            rest2 = "Died parsing %s";
            max_tokens = (uint8_t *)0x0;
            goto L_0808372e;
          }
          stk_5a0 = stk_5a0 + (int)rest2;
          stk_5ac = 4;
          if ((int)max_tokens < (int)stk_5a0) {
            rest2 = "Overabundance.";
            text = max_tokens;
            goto L_0808372e;
          }
          text2 = stk_590[0];
        }
        else {
          if ((*(uint8_t *)(__ctype_b + 1 + (char)*text2 * 2) & 0x20) == 0) goto L_0808373b;
          text2 = text2 + 1;
        }
        goto L_08083527;
      }
      OperCode(text2);
      if (stk_5ac == 1) goto L_0808373b;
      rest2 = InfToPostArray(text2 + 1,stk_41c,stk_51c,player,max_tokens + -(int)stk_5a0,
                               &stk_598,0);
      if (rest2 != (char *)0x0) {
        if (*stk_598 != ',') {
          if (*stk_598 != ')') goto L_0808373b;
          pf10 = stk_41c;
          pf12 = (float *)(vstack + (int)(stk_5a0 + 1));
          for (u5 = (uint32_t)rest2 & 0x3fffffff; u5 != 0; u5 = u5 - 1) {
            __builtin_memcpy(pf12, pf10, 4);
            pf10 = pf10 + 1;
            pf12 = pf12 + 1;
          }
          pb4 = stk_49c + (int)stk_5a0;
          stk_5a0 = stk_5a0 + (int)rest2;
          memcpy(pb4,stk_51c,(size_t)rest2);
          text2 = (uint8_t *)(stk_598 + 1);
          stk_5ac = 6;
          goto L_08083527;
        }
        stk_5a4 = InfToPostArray((uint8_t *)(stk_598 + 1),stk_41c + (int)rest2,
                                   stk_51c + (int)rest2,player,
                                   max_tokens + -(int)stk_5a0 + -(int)rest2,&stk_598,0);
        if (stk_5a4 == (char *)0x0) goto L_0808373b;
        b13 = false;
        if ((*stk_598 == ')') || (*stk_598 == ']')) {
          b13 = true;
        }
        if (!b13) goto L_0808373b;
        pc7 = stk_598 + 1;
        b6 = *(uint8_t *)(__ctype_b + 1 + stk_598[1] * 2);
        while ((b6 & 0x20) != 0) {
          pc7 = pc7 + 1;
          b6 = *(uint8_t *)(__ctype_b + 1 + *pc7 * 2);
        }
        if ((*pc7 != ')') && (*pc7 != '\0')) goto L_0808373b;
      }
      if ((stk_5ac - 5U < 2) || ((stk_5a8 == -1 || (1 < (int)(char)stk_55c[stk_5a8] - 1U))))
      goto L_0808373b;
      stk_5ac = 3;
      stk_5c8 = (uint32_t)(*stk_598 != ')');
      while (i2 = PriorityCheck(stk_5c8 + 7), i2 <= stk_59c) {
        if (stk_5a8 == -1) {
          stk_59c = 0;
          break;
        }
        i2 = stk_5a8 + -1;
        if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
        vstack[(int)(stk_5a0 + 1)] = (int)(char)stk_55c[stk_5a8];
        stk_5a0[(int)stk_49c] = '\x02';
        stk_5a0 = stk_5a0 + 1;
        if (i2 < 0) {
          stk_59c = 0;
          stk_5a8 = i2;
        }
        else {
          stk_59c = PriorityCheck((int)(char)stk_55c[stk_5a8 + -1]);
          stk_5a8 = i2;
        }
      }
      rest2 = stk_5a4 + (int)rest2;
      pf10 = stk_41c;
      pf12 = (float *)(vstack + (int)(stk_5a0 + 1));
      for (u5 = (uint32_t)rest2 & 0x3fffffff; u5 != 0; u5 = u5 - 1) {
        __builtin_memcpy(pf12, pf10, 4);
        pf10 = pf10 + 1;
        pf12 = pf12 + 1;
      }
      memcpy(stk_5a0 + (int)stk_49c,stk_51c,(size_t)rest2);
      stk_5a0 = stk_5a0 + (int)rest2;
      text2 = (uint8_t *)(stk_598 + 1);
      if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
      vstack[(int)(stk_5a0 + 1)] = stk_5c8 + 7;
      stk_5a0[(int)stk_49c] = '\x02';
      stk_5a0 = stk_5a0 + 1;
      goto L_08083527;
    }
    b13 = false;
    if (((stk_5ac != 2) || (stk_5a8 == -1)) || (1 < (int)(char)stk_55c[stk_5a8] - 1U))
    goto L_0808373b;
    stk_5ac = 3;
    rest2 = InfToPostArray(text2 + 1,stk_41c,stk_51c,player,max_tokens + -(int)stk_5a0,
                             &stk_594,0);
    if (((rest2 == (char *)0x0) || (*stk_594 != ',')) ||
       (stk_5a4 = InfToPostArray((uint8_t *)(stk_594 + 1),stk_41c + (int)rest2,
                                   rest2 + (int)stk_51c,player,
                                   max_tokens + -(int)stk_5a0 + -(int)rest2,&stk_594,0),
       stk_5a4 == (char *)0x0)) goto L_0808373b;
    b14 = false;
    if ((*stk_594 == ')') || (*stk_594 == ']')) {
      b14 = true;
    }
    if (b14) {
      pc7 = stk_594 + 1;
      if ((*(uint8_t *)(__ctype_b + 1 + stk_594[1] * 2) & 0x20) == 0) {
        c2 = stk_594[1];
      }
      else {
        c2 = '\0';
        if (stk_594[1] != '\0') {
          do {
            pc7 = pc7 + 1;
            if ((*(uint8_t *)(__ctype_b + 1 + *pc7 * 2) & 0x20) == 0) {
              c2 = *pc7;
              goto L_08083017;
            }
          } while (*pc7 != '\0');
          c2 = '\0';
        }
      }
L_08083017:
      if ((c2 != ')') && (c2 != '\0')) goto L_0808301f;
      stk_5c4 = (uint32_t)(*stk_594 != ')');
      while (i2 = PriorityCheck(stk_5c4 + 9), i2 <= stk_59c) {
        if (stk_5a8 == -1) {
          stk_59c = 0;
          break;
        }
        i2 = stk_5a8 + -1;
        if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
        vstack[(int)(stk_5a0 + 1)] = (int)(char)stk_55c[stk_5a8];
        stk_5a0[(int)stk_49c] = '\x02';
        stk_5a0 = stk_5a0 + 1;
        if (i2 < 0) {
          stk_59c = 0;
          stk_5a8 = i2;
        }
        else {
          stk_59c = PriorityCheck((int)(char)stk_55c[stk_5a8 + -1]);
          stk_5a8 = i2;
        }
      }
      rest2 = stk_5a4 + (int)rest2;
      pf10 = stk_41c;
      pf12 = (float *)(vstack + (int)(stk_5a0 + 1));
      for (u5 = (uint32_t)rest2 & 0x3fffffff; u5 != 0; u5 = u5 - 1) {
        __builtin_memcpy(pf12, pf10, 4);
        pf10 = pf10 + 1;
        pf12 = pf12 + 1;
      }
      memcpy(stk_5a0 + (int)stk_49c,stk_51c,(size_t)rest2);
      stk_5a0 = stk_5a0 + (int)rest2;
      if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
      vstack[(int)(stk_5a0 + 1)] = stk_5c4 + 9;
      stk_5a0[(int)stk_49c] = '\x02';
      stk_5a0 = stk_5a0 + 1;
      text2 = (uint8_t *)(stk_594 + 1);
    }
    else {
L_0808301f:
      b13 = true;
    }
    if (b13) goto L_0808373b;
  } while( true );
L_08082e9e:
  if (0x3f < stk_5a8 + 1) {
    StackErrorExit();
  }
  stk_55c[stk_5a8 + 1] = (uint8_t)i2;
  stk_59c = PriorityCheck(i2);
  i2 = OpLength(i2);
  text2 = text2 + i2;
  stk_5a8 = stk_5a8 + 1;
  goto L_08083527;
  while( true ) {
    vstack[(int)(stk_5a0 + 1)] = (int)(char)pb4[stk_5a8];
    stk_5a0[(int)stk_49c] = '\x02';
    stk_5a0 = stk_5a0 + 1;
    stk_5a8 = stk_5a8 + -1;
    if (stk_5a8 < 0) break;
L_08083573:
    if ((int)max_tokens <= (int)stk_5a0) goto L_0808373b;
  }
L_080835a3:
  if (stk_5a0 == (char *)0x0) goto L_0808373b;
  if ((stk_49c[0] < 2) && (stk_5a0 == (char *)0x1)) {
    if ((want_type == 2) && (stk_49c[0] == 0)) {
      stk_49c[0] = 1;
      vstack[1] = BITS_F2I(int, (float)vstack[1]);
      goto L_08083610;
    }
    if ((want_type != 1) || (stk_49c[0] != 1)) goto L_08083610;
    rest2 = "Expected int value and read float.";
    text = pb4;
    max_tokens = pb4;
  }
  else {
L_08083610:
    j = 0;
    i2 = 0;
    if (0 < (int)stk_5a0) {
      do {
        b6 = stk_49c[j];
        if (b6 < 2) {
L_080836a4:
          i2 = i2 + 1;
        }
        else {
          if (b6 != 2) {
            if (b6 == 3) {
              c2 = SCtrlTrigArity(*(int *)vstack[j + 1]);
              i2 = i2 - ZEXT8(c2);
              pb4 = stale_ECX_00;
              if (-1 < i2) goto L_080836a4;
            }
            goto L_default_08083643;
          }
          switch(vstack[j + 1]) {
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 0xb:
          case 0xc:
          case 0xe:
          case 0xf:
          case 0x10:
          case 0x11:
          case 0x12:
          case 0x14:
          case 0x15:
          case 0x17:
          case 0x18:
          case 0x19:
          case 0x1a:
          case 0x1b:
            if (i2 < 2) goto L_default_08083643;
            i2 = i2 + -1;
            break;
          case 7:
          case 8:
          case 9:
          case 10:
            if (i2 < 3) goto L_default_08083643;
            i2 = i2 + -2;
            j = j + 1;
            break;
          case 0xd:
          case 0x13:
          case 0x16:
            if (i2 == 0) goto L_default_08083643;
            break;
          default:
            goto L_default_08083643;
          }
        }
        j = j + 1;
      } while (j < (int)stk_5a0);
    }
    if (i2 == 1) {
      if (end != (uint32_t *)0x0) {
        *end = text2;
      }
      pf10 = (float *)vstack;
      for (u5 = (uint32_t)stk_5a0 & 0x3fffffff; pf10 = pf10 + 1, u5 != 0;
          u5 = u5 - 1) {
        __builtin_memcpy(values, pf10, 4);
        values = values + 1;
      }
      memcpy(types,stk_49c,(size_t)stk_5a0);
      return stk_5a0;
    }
L_default_08083643:
    rest2 = "Malformed expression encountered: %s";
    max_tokens = pb4;
  }
L_0808372e:
  sprintf((char *)ErrorMessage,rest2,text,max_tokens);
L_0808373b:
  i2 = 0;
  if (0 < (int)stk_5a0) {
    do {
      if (stk_49c[i2] == 3) {
        TriggerFree((void *)vstack[i2 + 1]);
      }
      i2 = i2 + 1;
    } while (i2 < (int)stk_5a0);
  }
  return (char *)0x0;
}
#undef text2
#undef stk_5c8
#undef stk_5c4
#undef stk_5ac
#undef stk_5a8
#undef stk_5a4
#undef stk_5a0
#undef stk_59c
#undef stk_598
#undef stk_594
#undef stk_590
#undef stk_560
#undef stk_55c
#undef stk_51c
#undef stk_49c
#undef stk_41c

/* InfixToPostfix @ 0x08083780, 225 bytes
 *
 * Compiles `text` into the expression record `expr` (InfToPostArray into
 * temporary arrays, then copied to exact-size blocks). Constant results are
 * stored as constants so they cost nothing at run time. Returns nonzero on
 * success.
 *
 * Parameters:
 *   text         uint8_t *
 *   expr         int *
 *   player       int
 *   end          uint32_t *
 *   want_type    int
 *
 * Calls: InfToPostArray, ecalloc
 * C library: __builtin_memcpy, memcpy
 * Called by: ItoP_TPConstF, ItoP_TPConstI, ParseVel,
 *            SCtrlParseAftImgParams, SCtrlParseElem, SCtrlParseElemType,
 *            SCtrlParseExplod, SCtrlParseHelper, SCtrlParseHitDef,
 *            SCtrlParseHitOverride, SCtrlParsePalFX,
 *            SCtrlParsePlaySndInfo, SCtrlParseProjectile, SCtrlParseState,
 *            SCtrlParseTrigger, SCtrlReadExpList
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: float words copied as bytes: 1 copies, 1 array reads (apply_bits_copies)
 * Note: Locals live in `frame`, laid out as on the original stack (0x2a0 bytes,
 *       2 variables), because their address is taken.
 */
uint32_t InfixToPostfix(uint8_t *text,int *expr,int player,uint32_t *end,int want_type)

{
  uint32_t u1;
  char *n;
  int mem;
  uint32_t u3;
  float *pf4;
  float *pf5;
  unsigned char frame[0x2a0] __attribute__((aligned(16)));
#define stk_29c (*(uint8_t (*)[128])(frame + 0x4))
#define stk_21c (*(float (*)[131])(frame + 0x84))
  
  u1 = 1;
  if (text != (uint8_t *)0x0) {
    n = InfToPostArray(text,stk_21c,stk_29c,player,(uint8_t *)0x80,end,want_type);
    if (n == (char *)0x0) {
      u1 = 0;
    }
    else {
      if ((n == (char *)0x1) && (stk_29c[0] < 2)) {
        expr[1] = 0;
        expr[2] = BITS_F2I_LV(int, stk_21c[0]);
        *expr = (int)(char)stk_29c[0];
      }
      else {
        mem = ecalloc((size_t)n,4);
        *expr = mem;
        mem = ecalloc((size_t)n,1);
        expr[1] = mem;
        expr[2] = (int)n;
        pf4 = stk_21c;
        pf5 = (float *)*expr;
        for (u3 = (uint32_t)n & 0x3fffffff; u3 != 0; u3 = u3 - 1) {
          __builtin_memcpy(pf5, pf4, 4);
          pf4 = pf4 + 1;
          pf5 = pf5 + 1;
        }
        memcpy((void *)expr[1],stk_29c,(size_t)n);
      }
      u1 = 1;
    }
  }
  return u1;
}
#undef stk_29c
#undef stk_21c

/* FreeExpression @ 0x08083870, 114 bytes
 *
 * Frees a compiled expression's code and type arrays, including the argument
 * blocks of its trigger codes.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: TriggerFree
 * C library: free
 * Called by: AftImgParamsEFree, ConstExpF, ConstExpI, EnvShakeEFree,
 *            ExplodInfoFree, FreeExpArray, HelperInfoFree, HitDefEFree,
 *            HitOverrideEFree, MoreExpFree, PalFXEFree, PauseInfoFree,
 *            PlaySndInfoFree, ProjMakeInfoFree, SCtrlParseHitDef,
 *            SCtrlRCElemFree, ... (21 callers)
 *
 * Elecbyte file: src/mugen/arith.c
 */
uint32_t FreeExpression(int *expr)

{
  int i1;
  uint32_t entry_EDX;
  int i2;
  int i3;
  
  i1 = expr[1];
  if (i1 != 0) {
    i3 = 0;
    i2 = expr[2];
    if (0 < i2) {
      while( true ) {
        if (*(char *)(i3 + i1) == '\x03') {
          TriggerFree(*(void **)(*expr + i3 * 4));
          i2 = expr[2];
        }
        i3 = i3 + 1;
        if (i2 <= i3) break;
        i1 = expr[1];
      }
    }
    free((void *)expr[1]);
    free((void *)*expr);
  }
  *expr = 0;
  expr[1] = 0;
  expr[2] = 0;
  return entry_EDX;
}

/* FreeExpNoTrig @ 0x080838f0, 59 bytes
 *
 * Frees a compiled expression's arrays without visiting trigger argument
 * blocks. Not called in this build.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * C library: free
 *
 * Elecbyte file: src/mugen/arith.c
 */
void FreeExpNoTrig(uint32_t *arg1)

{
  if ((void *)arg1[1] != (void *)0x0) {
    free((void *)arg1[1]);
    free((void *)*arg1);
  }
  *arg1 = 0;
  arg1[1] = 0;
  arg1[2] = 0;
  return;
}

/* FreeExpArray @ 0x08083930, 68 bytes
 *
 * Frees every expression of an array of expressions, then the array.
 *
 * Parameters:
 *   array        void *
 *
 * Calls: ArrayScanFirst, FreeExpression, ArrayScanNext, ArrayFree
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
uint32_t FreeExpArray(void *array)

{
  int *item;
  uint32_t u2;
  uint32_t saved_EBX;
  
  if (array != (void *)0x0) {
    item = (int *)ArrayScanFirst((int)array);
    while (item != (int *)0x0) {
      FreeExpression(item);
      item = (int *)ArrayScanNext((int)array);
    }
    u2 = ArrayFree(array);
    return u2;
  }
  return saved_EBX;
}

/* ConstExpI @ 0x08083980, 50 bytes
 *
 * Turns an expression into the int constant `value` (freeing any code it
 * had).
 *
 * Parameters:
 *   expr         int *
 *   value        int
 *
 * Calls: FreeExpression
 * Called by: ItoP_TPConstI, SCtrlParseAftImgParams, SCtrlParseElemType,
 *            SCtrlParseExplod, SCtrlParseHelper, SCtrlParseHitDef,
 *            SCtrlParseHitOverride, SCtrlParsePalFX,
 *            SCtrlParsePlaySndInfo, SCtrlParseProjectile, SCtrlParseState,
 *            SCtrlParseSuperPause, SCtrlParseTrigger
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void ConstExpI(int *expr,int value)

{
  uint32_t saved_EBX;
  
  if (expr[1] != 0) {
    FreeExpression(expr);
    expr[1] = 0;
  }
  *expr = 0;
  expr[2] = value;
  return;
}

/* ConstExpF @ 0x080839c0, 52 bytes
 *
 * Turns an expression into the float constant whose bits are `value_bits`.
 *
 * Parameters:
 *   expr         int *
 *   value_bits   int
 *
 * Calls: FreeExpression
 * Called by: ItoP_TPConstF, ParseVel, SCtrlParseAftImgParams,
 *            SCtrlParseElemType, SCtrlParseExplod, SCtrlParseHitDef,
 *            SCtrlParseProjectile, SCtrlParseState
 *
 * Elecbyte file: src/mugen/arith.c
 */
void ConstExpF(int *expr,int value_bits)

{
  if (expr[1] != 0) {
    FreeExpression(expr);
    expr[1] = 0;
  }
  *expr = 1;
  expr[2] = value_bits;
  return;
}

/* expcpy @ 0x08083a00, 157 bytes
 *
 * Copies an expression (code and type arrays duplicated).
 *
 * Parameters:
 *   dest         int *
 *   src          int *
 *
 * Calls: FreeExpression, ecalloc
 * C library: memcpy
 * Called by: expcpytrig
 *
 * Elecbyte file: src/mugen/arith.c
 */
uint32_t expcpy(int *dest,int *src)

{
  int mem;
  uint32_t u2;
  uint32_t u3;
  uint32_t *pu4;
  uint32_t *pu5;
  
  FreeExpression(dest);
  if (src[1] == 0) {
    *dest = *src;
    dest[1] = src[1];
    dest[2] = src[2];
L_08083a90:
    u2 = 1;
  }
  else {
    mem = ecalloc(src[2],4);
    *dest = mem;
    if (mem != 0) {
      mem = ecalloc(src[2],1);
      dest[1] = mem;
      if (mem != 0) {
        dest[2] = src[2];
        pu4 = (uint32_t *)*src;
        pu5 = (uint32_t *)*dest;
        for (u3 = src[2] & 0x3fffffff; u3 != 0; u3 = u3 - 1) {
          *pu5 = *pu4;
          pu4 = pu4 + 1;
          pu5 = pu5 + 1;
        }
        memcpy((void *)dest[1],(void *)src[1],src[2]);
        goto L_08083a90;
      }
    }
    u2 = 0;
  }
  return u2;
}

/* expcpytrig @ 0x08083aa0, 148 bytes
 *
 * Copies an expression including the argument blocks of its trigger codes
 * (trigcpy). "Uh-oh. Alloc error" on failure.
 *
 * Parameters:
 *   dest         int *
 *   src          int *
 *
 * Calls: expcpy, ecalloc, ErrorExit, trigcpy
 * C library: sprintf
 * Called by: SCtrlParseElemType, SCtrlParseHitDef, SCtrlParseProjectile,
 *            trigcpy
 * Messages:
 *   "Uh-oh. Alloc error"
 *
 * Elecbyte file: src/mugen/arith.c
 */
uint32_t expcpytrig(int *dest,int *src)

{
  int i1;
  int *mem;
  int i3;
  int i4;
  
  expcpy(dest,src);
  i1 = dest[1];
  if (i1 != 0) {
    i4 = 0;
    i3 = dest[2];
    if (0 < i3) {
      while( true ) {
        if (*(char *)(i4 + i1) == '\x03') {
          mem = (int *)ecalloc(1,0x38);
          if (mem == (int *)0x0) {
            sprintf((char *)ErrorMessage,"Uh-oh. Alloc error",0,0);
            ErrorExit();
            return 0;
          }
          trigcpy(mem,*(int **)(*dest + i4 * 4));
          *(int **)(*dest + i4 * 4) = mem;
          i3 = dest[2];
        }
        i4 = i4 + 1;
        if (i3 <= i4) break;
        i1 = dest[1];
      }
    }
  }
  return 1;
}

/* ExpMulF @ 0x08083b40, 184 bytes
 *
 * Multiplies an expression by a float constant: a constant expression is
 * folded; otherwise "constant, *" is appended to its code. Used to scale
 * HitDef values.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *
 * Calls: ErrorExit
 * C library: realloc
 * Called by: SCtrlParseHitDef
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
float ExpMulF(int *arg1,float arg2)

{
  void *pv1;
  float80 f2;
  int i3;
  
  if (arg1[1] == 0) {
    if (*arg1 == 0) {
      f2 = (float80)arg1[2] * arg2;
      *arg1 = 1;
      arg1[2] = BITS_F2I(int, f2);
    }
    else {
      f2 = arg2 * BITS_I2F(arg1[2]);
      arg1[2] = BITS_F2I(int, f2);
    }
  }
  else {
    i3 = arg1[2];
    arg1[2] = i3 + 2;
    pv1 = realloc((void *)*arg1,(i3 + 2) * 4);
    *arg1 = (int)pv1;
    pv1 = realloc((void *)arg1[1],arg1[2]);
    i3 = *arg1;
    arg1[1] = (int)pv1;
    if ((i3 == 0) || (pv1 == (void *)0x0)) {
      ErrorExit();
      i3 = *arg1;
    }
    *(float *)(i3 + -8 + arg1[2] * 4) = arg2;
    *(uint32_t *)(i3 + -4 + arg1[2] * 4) = 0x19;
    *(uint8_t *)(arg1[2] + arg1[1] + -2) = 1;
    f2 = BITS_I2F((arg1[2] + arg1[1]));
    *(uint8_t *)(BITS_F2I(int, f2) + -1) = 2;
  }
  return f2;
}

/* ExpDivI @ 0x08083c00, 204 bytes
 *
 * Divides an expression by an int constant (folded for constants, appended
 * otherwise). "Can't realloc memory." on failure.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ErrorExit
 * C library: realloc, sprintf
 * Called by: SCtrlParseHitDef
 * Messages:
 *   "Can\'t realloc memory."
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
float ExpDivI(int *arg1,int arg2)

{
  int i1;
  float80 f2;
  void *pv3;
  int i4;
  
  if (arg1[1] == 0) {
    if (*arg1 == 0) {
      f2 = BITS_I2F((arg1[2] / arg2));
    }
    else {
      f2 = BITS_I2F(arg1[2]) / (float)arg2;
    }
    arg1[2] = BITS_F2I(int, f2);
    *arg1 = 1;
  }
  else {
    i4 = arg1[2];
    arg1[2] = i4 + 2;
    pv3 = realloc((void *)*arg1,(i4 + 2) * 4);
    *arg1 = (int)pv3;
    pv3 = realloc((void *)arg1[1],arg1[2] << 2);
    i4 = *arg1;
    arg1[1] = (int)pv3;
    if ((i4 == 0) || (pv3 == (void *)0x0)) {
      sprintf((char *)ErrorMessage,"Can\'t realloc memory.",pv3,pv3);
      ErrorExit();
      i4 = *arg1;
    }
    *(int *)(i4 + -8 + arg1[2] * 4) = arg2;
    i1 = arg1[1];
    *(uint32_t *)(i4 + -4 + arg1[2] * 4) = 0x1a;
    *(uint8_t *)(arg1[2] + i1 + -2) = 0;
    f2 = BITS_I2F((arg1[2] + arg1[1]));
    *(uint8_t *)(BITS_F2I(int, f2) + -1) = 2;
  }
  return f2;
}

/* ShowExp @ 0x08083cd0, 360 bytes
 *
 * Debug dump of an expression: each code word with its type ("%d (int)" /
 * "%f (float)") after the result. Used when an evaluation goes wrong.
 *
 * Parameters:
 *   arg1         char *
 *   expr         int *
 *   player       int *
 *
 * Calls: EvalExpression
 * C library: sprintf, strcat
 * Called by: EvalExpression
 * Messages:
 *   "%d (int)"
 *   "%f (float)"
 *   "\nData: "
 *   "\nTypes: "
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xb0 bytes, 5
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ShowExp(char *arg1,int *expr,int *player)

{
  char c1;
  int type;
  uint32_t stale_ECX;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t u3;
  char *pc4;
  float80 d5;
  unsigned char frame[0xb0] __attribute__((aligned(16)));
#define stk_a4 (*(int *)(frame + 0xc))
#define stk_a0 (*(float (*)[5])(frame + 0x10))
#define stk_8c (*(char *(*)[4])(frame + 0x24))
#define stk_7c (*(char **)(frame + 0x34))
#define stk_6c (*(char (*)[92])(frame + 0x44))
  
  stk_8c[0] = "int";
  stk_8c[1] = "float";
  stk_8c[2] = "oper";
  stk_8c[3] = "trig";
  stk_7c = "SC";
  if (expr[1] == 0) {
    type = EvalExpression(player,expr,&stk_a4,(int *)stk_a0);
    if (type == 1) {
      d5 = BITS_L2D(CONCAT44(1,stk_a4));
      pc4 = "%d (int)";
    }
    else {
      if (type != 2) {
        return;
      }
      d5 = (double)stk_a0[0];
      pc4 = "%f (float)";
    }
    sprintf(arg1,pc4,d5);
  }
  else {
    type = 0;
    sprintf(arg1,"\nData: ");
    u3 = stale_EDX;
    if (0 < expr[2]) {
      do {
        c1 = *(char *)(type + expr[1]);
        if (c1 == '\x01') {
          d5 = (double)*(float *)(*expr + type * 4);
          pc4 = "%f,";
        }
        else {
          if (c1 == '\x03') {
            d5 = BITS_L2D(CONCAT44(CONCAT31((uint32_t)((uint32_t)expr[1] >> 8),c1),
                                     **(uint32_t **)(*expr + type * 4)));
          }
          else {
            d5 = BITS_L2D(CONCAT44(u3,*(uint32_t *)(*expr + type * 4)));
          }
          pc4 = "%d,";
        }
        sprintf(stk_6c,pc4,d5);
        type = type + 1;
        strcat(arg1,stk_6c);
        u3 = stale_EDX_00;
      } while (type < expr[2]);
    }
    sprintf(stk_6c,"\nTypes: ",u3,u3);
    for (type = 0; strcat(arg1,stk_6c), type < expr[2]; type = type + 1) {
      sprintf(stk_6c,"%s,",stk_8c[*(char *)(type + expr[1])],stale_ECX);
    }
  }
  return;
}
#undef stk_a4
#undef stk_a0
#undef stk_8c
#undef stk_7c
#undef stk_6c

/* EvalExpressionI @ 0x08083e40, 283 bytes
 *
 * Evaluates an expression for a player as an int. Constants return directly.
 * Float results are truncated, with a warning when `warn` is set
 * ("expression truncated to int"). Malformed expressions are fatal.
 *
 * Parameters:
 *   player       int
 *   expr         int *
 *   warn         int
 *
 * Player fields read: stateno
 * Globals read: frame_count, clipboard
 * Calls: EvalExpression, ErrorExit, ClipboardAppend
 * C library: sprintf
 * Called by: ExplodMakeFromInfo, ExplodModifyFromInfo, ExplodSetParams,
 *            HelperMake, PlayerSCtrlApplyElem, PlayerSCtrlUpdate,
 *            SCtrlDoPlaySndInfo, SCtrlInitAftImgParams, SCtrlInitEnvShake,
 *            SCtrlInitHitDef, SCtrlInitHitOverride, SCtrlInitPalFX,
 *            SCtrlInitPause, SCtrlInitProjectile, SCtrlTrigEval
 * Messages:
 *   "%4i: Fatal: Player %s (%i) in state %i: malformed expression"
 *   "%i Warning: expression truncated to integer:\nplayer %s (%i) in state
 *     %i: %f"
 *   "%i Warning: expression short-circuited, returning 0:\nplayer %s (%i)
 *     in state %i"
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: removed 1 x87 control-word save statements
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 5
 *       variables), because their address is taken.
 */
int EvalExpressionI(int player,int *expr,int warn)

{
  int type;
  uint32_t stale_ECX;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(int *)(frame + 0xc))
#define stk_10 (*(float *)(frame + 0x10))
#define stk_c (*(int *)(frame + 0x14))
#define stk_8 (*(uint16_t *)(frame + 0x18))
#define stk_6 (*(uint16_t *)(frame + 0x1a))
  
  type = EvalExpression((int *)player,expr,&stk_14,(int *)&stk_10);
  if (type == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),*(uint32_t *)(player + PLB_STATENO),
            stale_ECX,stale_ECX);
    ErrorExit();
  }
  else if (type == 2) {
    stk_14 = (int)X87_FIST32(stk_10);
    if (warn != 0) {
      stk_c = stk_14;
      ClipboardAppend((int *)g[G_CLIPBOARD],
                      "%i Warning: expression truncated to integer:\nplayer %s (%i) in state %i: %f"
                      ,g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),
                      *(uint32_t *)(player + PLB_STATENO),(double)stk_10);
    }
  }
  else if (type == 3) {
    ClipboardAppend((int *)g[G_CLIPBOARD],
                    "%i Warning: expression short-circuited, returning 0:\nplayer %s (%i) in state %i"
                    ,g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),
                    *(uint32_t *)(player + PLB_STATENO),stale_ECX,stale_ECX);
    stk_14 = 0;
  }
  return stk_14;
}
#undef stk_14
#undef stk_10
#undef stk_c
#undef stk_8
#undef stk_6

/* EvalExpressionF @ 0x08083f60, 182 bytes
 *
 * Evaluates an expression for a player as a float (int results converted).
 * Malformed expressions are fatal.
 *
 * Parameters:
 *   player       int *
 *   expr         int *
 *
 * Player fields read: id, stateno
 * Globals read: frame_count, clipboard
 * Calls: EvalExpression, ErrorExit, ClipboardAppend
 * C library: sprintf
 * Called by: ExplodSetParams, HelperMake, PlayerSCtrlApplyElem,
 *            PlayerSCtrlUpdate, SCtrlDoPlaySndInfo, SCtrlInitAftImgParams,
 *            SCtrlInitEnvShake, SCtrlInitHitDef, SCtrlInitProjectile
 * Messages:
 *   "%4i: Fatal: Player %s (%i) in state %i: malformed expression"
 *   "%i Warning: expression short-circuited, returning 0: player %s (%i)
 *     in state %i"
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 2
 *       variables), because their address is taken.
 */
float EvalExpressionF(int *player,int *expr)

{
  int type;
  uint32_t stale_ECX;
  float entry_EDX;
  uint32_t stale_EDX;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_c (*(float *)(frame + 0x4))
#define stk_8 (*(float *)(frame + 0x8))
  
  stk_c = entry_EDX;
  stk_8 = entry_EDX;
  type = EvalExpression(player,expr,(int *)&stk_c,(int *)&stk_8);
  if (type == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[G_FRAME_COUNT],player + 8,player[PL_ID],player[PL_STATENO],stale_ECX,stale_ECX);
    ErrorExit();
  }
  else if (type == 1) {
    stk_8 = (float80)BITS_F2I(int, stk_c);
  }
  else if (type == 3) {
    ClipboardAppend((int *)g[G_CLIPBOARD],
                    "%i Warning: expression short-circuited, returning 0: player %s (%i) in state %i"
                    ,g[G_FRAME_COUNT],player + 8,player[PL_ID],player[PL_STATENO],stale_EDX,stale_EDX);
    stk_8 = 0.0;
  }
  return stk_8;
}
#undef stk_c
#undef stk_8

/* EvalExpression @ 0x08084020, 4625 bytes
 *
 * The expression interpreter. Runs postfix code on the typed value stack.
 * Constants are pushed; trigger codes call SCtrlTrigEval; operators pop
 * their operands and push the result. Int and float arithmetic follow the
 * operand types. Logical operators produce 0/1, "**" uses ipow or pow, and
 * division by zero gives a warning. The result comes back as int or float
 * with its type. Errors: "Expression stack overflow.", "Type mismatch
 * detected: %d", "Invalid exponentiation".
 *
 * Parameters:
 *   player       int *
 *   expr         int *
 *   out_int      int *
 *   out_float    int *
 *
 * Player fields read: id, stateno
 * Player fields written: var, fvar
 * Globals read: errmsg, frame_count
 * Calls: ErrorExit, SCtrlTrigEval, OpTypeCheck, ShowExp, ipow, Warn
 * C library: sprintf, pow, isnan
 * Called by: EvalExpressionF, EvalExpressionI, PlayerSCtrlApplyElem,
 *            SCtrlTrigTest, ShowExp
 * Messages:
 *   "Expression stack overflow."
 *   "Type mismatch detected: %d"
 *   "Invalid exponentiation"
 *   "Short-circuited var assign ignored"
 *   "Divison by zero"
 *   "Modulus by zero"
 *
 * Elecbyte file: src/mugen/arith.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: 2 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 32-bit operand words f8, f4, saved_EDI kept as raw words (word32_t), see
 *       WORD32_OPERANDS
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t EvalExpression(int *player,int *expr,int *out_int,int *out_float)

{
  int *pi1;
  int *pi2;
  char c3;
  word32_t f4;
  int i5;
  bool b6;
  uint32_t stale_var;
  int i7;
  word32_t f8;
  int *pi9;
  uint32_t u10;
  uint32_t u11;
  int saved_EBP;
  word32_t saved_EDI;
  float80 d12;
  char *msg;
  int stk_144;
  float stk_140;
  float stk_120;
  float stk_11c;
  float stk_118;
  int stk_114;
  
  pi2 = MyStackIdx;
  stk_118 = 0.0;
  stk_11c = 0.0;
  stk_120 = 0.0;
  i7 = expr[1];
  if (i7 == 0) {
    if (*expr == 0) {
      *out_int = expr[2];
      return 1;
    }
    if (*expr != 1) {
      return 0;
    }
    *out_float = expr[2];
    return 2;
  }
  stk_114 = 0;
  if (0 < expr[2]) {
    do {
      c3 = *(char *)(stk_114 + i7);
      if (c3 != '\x02') {
        if (c3 < '\x03') {
          if (c3 < '\0') {
L_08084ff7:
            stk_144 = *expr;
            goto L_08085004;
          }
          i7 = *(int *)(*expr + stk_114 * 4);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          pi9 = (int *)((int)MyStackIdx + 1);
          MyStackIdx = pi9;
          MyStack[(int)pi9] = i7;
          c3 = *(char *)(stk_114 + expr[1]);
          if (0x7e < (int)pi9) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = (int)c3;
        }
        else {
          if (c3 != '\x03') goto L_08084ff7;
          SCtrlTrigEval(player,*(int **)(*expr + stk_114 * 4));
        }
        goto L_default_0808437f;
      }
      pi9 = MyStackIdx;
      if ((int)MyStackIdx < 0) goto L_080851e2;
      pi9 = (int *)((int)MyStackIdx + -1);
      if ((int)pi9 < 0) goto L_080851e2;
      pi1 = (int *)((int)MyStackIdx + -2);
      f8.i = (MyStack[(int)pi9]);
      saved_EBP = 1;
      if (MyStack[(int)MyStackIdx] == 1) {
        saved_EBP = 2;
        stk_118 = f8.f;
      }
      stk_144 = *expr;
      i7 = *(int *)(stk_144 + stk_114 * 4);
      b6 = false;
      if (((i7 == 0xd) || (i7 == 0x7e)) || (i7 == 0x13)) {
        b6 = true;
      }
      if (!b6) {
        pi9 = pi1;
        if ((int)pi1 < 0) goto L_080851e2;
        pi9 = (int *)((int)MyStackIdx + -3);
        if ((int)pi9 < 0) goto L_080851e2;
        saved_EDI.i = (MyStack[(int)pi9]);
        if ((saved_EBP == 2) || (MyStack[(int)pi1] == 1)) {
          stk_11c = saved_EDI.f;
          if (saved_EBP == 2) {
            if (MyStack[(int)pi1] == 0) {
              stk_11c = (float)((int)saved_EDI.i);
            }
          }
          else {
            stk_118 = (float)((int)f8.i);
            saved_EBP = 2;
          }
        }
        stk_144 = *expr;
        pi1 = MyStackIdx + -1;
      }
      MyStackIdx = pi1;
      b6 = OpTypeCheck(*(uint32_t *)(stk_144 + stk_114 * 4),saved_EBP);
      if (ZEXT8(b6) == 0) {
        sprintf((char *)(g + G_ERRMSG),"Type mismatch detected: %d",
                *(uint32_t *)(*expr + stk_114 * 4));
        ShowExp((char *)ErrorMessage,expr,player);
        ErrorExit();
      }
      stk_144 = *expr;
      switch(*(uint32_t *)(stk_144 + stk_114 * 4)) {
      case 1:
      case 2:
        if (saved_EBP == 1) {
          b6 = saved_EDI.i == f8.i;
        }
        else {
          b6 = stk_11c == stk_118;
        }
        u10 = (uint32_t)b6;
        if (*(int *)(stk_144 + stk_114 * 4) != 1) {
          u10 = (uint32_t)(u10 == 0);
        }
        goto L_08084bab;
      case 3:
      case 6:
        if (saved_EBP == 1) {
          b6 = ((int)f8.i) < ((int)saved_EDI.i);
        }
        else {
          b6 = stk_118 < stk_11c;
        }
        u10 = (uint32_t)b6;
        if (*(int *)(stk_144 + stk_114 * 4) != 3) {
          u10 = (uint32_t)(u10 == 0);
        }
        goto L_0808488f;
      case 4:
      case 5:
        if (saved_EBP == 1) {
          b6 = ((int)saved_EDI.i) < ((int)f8.i);
        }
        else {
          b6 = stk_11c < stk_118;
        }
        u10 = (uint32_t)b6;
        if (*(int *)(stk_144 + stk_114 * 4) != 4) {
          u10 = (uint32_t)(u10 == 0);
        }
        goto L_08084bab;
      case 7:
      case 8:
      case 9:
      case 10:
        pi9 = MyStackIdx;
        if (((*(char *)(stk_114 + 1 + expr[1]) != '\x02') ||
            (1 < *(int *)(stk_144 + 4 + stk_114 * 4) - 1U)) || ((int)MyStackIdx < 0))
        goto L_080851e2;
        i7 = MyStack[(int)MyStackIdx];
        pi9 = (int *)((int)MyStackIdx + -1);
        if ((int)pi9 < 0) goto L_080851e2;
        f4.i = (MyStack[(int)pi9]);
        MyStackIdx = (int *)((int)MyStackIdx + -2);
        if (i7 == 4) goto L_08084ff7;
        i5 = *expr;
        u10 = (uint32_t)(*(int *)(i5 + 4 + stk_114 * 4) == 1);
        u11 = u10 ^ 1;
        if (i7 == 1) {
          stk_120 = f4.f;
        }
        if ((saved_EBP == 1) && (i7 == 1)) {
          saved_EBP = 2;
          stk_118 = (float)((int)f8.i);
          stk_11c = (float)((int)saved_EDI.i);
        }
        else if ((saved_EBP == 2) && (i7 == 0)) {
          stk_120 = (float)((int)f4.i);
        }
        if (saved_EBP == 1) {
          i7 = *(int *)(i5 + stk_114 * 4);
          if (i7 == 8) {
            if ((((int)f4.i) <= ((int)saved_EDI.i)) || (((int)f8.i) < ((int)f4.i))) {
L_08084f06:
              u10 = u11;
            }
          }
          else if (i7 < 9) {
            if (i7 != 7) goto L_08084fac;
            if ((((int)f4.i) <= ((int)saved_EDI.i)) || (((int)f8.i) <= ((int)f4.i))) {
L_08084f40:
              u10 = u11;
            }
          }
          else if (i7 == 9) {
            if ((((int)f4.i) < ((int)saved_EDI.i)) || (((int)f8.i) <= ((int)f4.i))) goto L_08084f71;
          }
          else {
            if (i7 != 10) goto L_08084fac;
            if ((((int)f4.i) < ((int)saved_EDI.i)) || (((int)f8.i) < ((int)f4.i))) goto L_08084f40;
          }
L_join_08084f11:
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = u10;
        }
        else {
          i7 = *(int *)(i5 + stk_114 * 4);
          if (i7 == 8) {
            if ((stk_120 <= stk_11c) || (stk_118 < stk_120)) goto L_08084f06;
            goto L_join_08084f11;
          }
          if (i7 < 9) {
            if (i7 == 7) {
              if (stk_11c < stk_120) {
                b6 = stk_118 <= stk_120;
L_08084f6b:
                if (!b6) goto L_join_08084f11;
              }
L_08084f71:
              u10 = u11;
              goto L_join_08084f11;
            }
          }
          else {
            if (i7 == 9) {
              if ((stk_120 < stk_11c) || (stk_118 <= stk_120)) goto L_08084f40;
              goto L_join_08084f11;
            }
            if (i7 == 10) {
              if (stk_11c <= stk_120) {
                b6 = stk_118 < stk_120;
                goto L_08084f6b;
              }
              goto L_08084f71;
            }
          }
        }
L_08084fac:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        stk_114 = stk_114 + 1;
        MyStack[(int)MyStackIdx] = 0;
        break;
      case 0xb:
        if (saved_EBP == 1) {
          i7 = 0;
          if ((saved_EDI.i != 0) && (f8.i != 0)) {
            i7 = 1;
          }
        }
        else {
          i7 = 0;
          if ((stk_11c != 0.0) && (stk_118 != 0.0)) {
            i7 = 1;
          }
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = i7;
        goto L_join_08084b76;
      case 0xc:
        if (saved_EBP == 1) {
          i7 = 0;
          if ((saved_EDI.i != 0) || (f8.i != 0)) {
            i7 = 1;
          }
        }
        else {
          i7 = 0;
          if ((stk_11c != 0.0) || (stk_118 != 0.0)) {
            i7 = 1;
          }
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = i7;
        goto L_join_08084b76;
      case 0xd:
        if (saved_EBP == 1) {
          u10 = (uint32_t)(f8.i == 0);
        }
        else {
          u10 = (uint32_t)(stk_118 == 0.0);
        }
        goto L_join_08084b1a;
      case 0xe:
        if (saved_EBP == 1) {
          u10 = 0;
          if (((saved_EDI.i != 0) || (f8.i != 0)) && ((f8.i == 0 || (saved_EDI.i == 0)))) {
            u10 = 1;
          }
        }
        else {
          u10 = 0;
          if (stk_11c == 0.0) {
            if (stk_118 != 0.0) {
              if (stk_11c != 0.0) goto L_08084a22;
              goto L_08084a33;
            }
          }
          else {
L_08084a22:
            if (stk_118 == 0.0) {
L_08084a33:
              u10 = 1;
            }
          }
        }
L_join_08084b1a:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = u10;
L_join_08084b76:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        goto L_08084c4d;
      case 0xf:
        if (saved_EBP == 1) {
          if (-1 < ((int)f8.i)) {
            u10 = ipow(((int)saved_EDI.i),((int)f8.i));
            goto L_08084bf6;
          }
          stk_11c = (float)((int)saved_EDI.i);
          stk_118 = (float)((int)f8.i);
        }
        d12 = pow((double)stk_11c,(double)stk_118);
        f8.f = (float)d12;
        i7 = isnan((double)f8.f);
        stk_120 = f8.f;
        if (i7 != 0) goto L_08084ff7;
        goto L_08084c76;
      case 0x10:
        u10 = ((uint32_t)f8.i) & ((uint32_t)saved_EDI.i);
        goto L_08084bf6;
      case 0x11:
        u10 = ((uint32_t)f8.i) | ((uint32_t)saved_EDI.i);
L_08084bf6:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = u10;
        goto L_join_08084c2c;
      case 0x12:
        u10 = ((uint32_t)f8.i) ^ ((uint32_t)saved_EDI.i);
        goto L_08084bab;
      case 0x13:
        if (saved_EBP == 1) {
          u10 = -((int)f8.i);
          goto L_08084bf6;
        }
        f8.f = -stk_118;
L_08084c76:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = ((int)f8.i);
L_join_08084498:
        if (0x7e < (int)pi9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 1;
        break;
      case 0x14:
        if (saved_EBP == 1) {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)f8.i);
        }
        else {
          f8.i = ((int)X87_FIST32(stk_118));
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",stk_144);
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)f8.i);
          Warn((int)player,(int)&str_float_truncated_to_int_in_va_77c0);
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 0;
        if (saved_EBP == 2) {
          saved_EDI.i = ((int)X87_FIST32(stk_11c));
        }
        if (((uint32_t)saved_EDI.i) < 0x3d) {
          player[((int)saved_EDI.i) + PL_VAR] = ((int)f8.i);
        }
        else {
L_080847dc:
          Warn((int)player,(int)&str_assignment_to_illegal_variab_7800);
        }
        break;
      case 0x15:
        if (saved_EBP == 1) {
          stk_118 = (float)((int)f8.i);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = BITS_F2I(int, stk_118);
        }
        else {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)f8.i);
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 1;
        if (saved_EBP == 2) {
          saved_EDI.i = ((int)X87_FIST32(stk_11c));
        }
        if (0x28 < ((uint32_t)saved_EDI.i)) goto L_080847dc;
        player[((int)saved_EDI.i) + PL_FVAR] = BITS_F2I(int, stk_118);
        break;
      case 0x16:
        u10 = ((uint32_t)f8.i) ^ 0xffffffff;
L_08084bab:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = u10;
L_join_08084c2c:
        if (0x7e < (int)pi9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
L_08084c4d:
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 0;
        break;
      case 0x17:
        if (saved_EBP == 1) {
          u10 = ((int)saved_EDI.i) + ((int)f8.i);
          goto L_0808488f;
        }
        stk_140 = stk_118 + stk_11c;
        b6 = (int)MyStackIdx + -0x7e < 0;
L_08084465:
        if (MyStackIdx != (int *)0x7e && SBORROW4((int)MyStackIdx,0x7e) == b6) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = BITS_F2I(int, stk_140);
        goto L_join_08084498;
      case 0x18:
        if (saved_EBP != 1) {
          stk_140 = stk_11c - stk_118;
L_08084452:
          b6 = (int)MyStackIdx + -0x7e < 0;
          goto L_08084465;
        }
        u10 = ((int)saved_EDI.i) - ((int)f8.i);
        goto L_0808488f;
      case 0x19:
        if (saved_EBP != 1) {
          stk_140 = stk_118 * stk_11c;
          b6 = (int)MyStackIdx + -0x7e < 0;
          goto L_08084465;
        }
        u10 = ((int)f8.i) * ((int)saved_EDI.i);
L_0808488f:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = u10;
        goto L_join_08084c2c;
      case 0x1a:
        if (saved_EBP == 1) {
          if (f8.i != 0) {
            u10 = ((int)saved_EDI.i) / ((int)f8.i);
            goto L_0808488f;
          }
        }
        else if (stk_118 != 0.0) {
          stk_140 = stk_11c / stk_118;
          goto L_08084452;
        }
        goto L_08085004;
      case 0x1b:
        if (f8.i != 0) {
          u10 = ((int)saved_EDI.i) % ((int)f8.i);
          goto L_08084bf6;
        }
L_08085004:
        switch(*(uint32_t *)(stk_144 + stk_114 * 4)) {
        case 7:
        case 8:
        case 9:
        case 10:
          stk_114 = stk_114 + 1;
        default:
          goto L_case_08085017_b;
        case 0xf:
          msg = "Invalid exponentiation";
          break;
        case 0x14:
        case 0x15:
          msg = "Short-circuited var assign ignored";
          break;
        case 0x1a:
          msg = "Divison by zero";
          break;
        case 0x1b:
          msg = "Modulus by zero";
        }
        Warn((int)player,(int)msg);
L_case_08085017_b:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        pi9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = pi9;
        MyStack[(int)pi9] = 0;
        if (0x7e < (int)pi9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 4;
      }
L_default_0808437f:
      stk_114 = stk_114 + 1;
      if (expr[2] <= stk_114) break;
      i7 = expr[1];
    } while( true );
  }
  pi9 = MyStackIdx;
  if ((int)MyStackIdx - (int)pi2 == 2) {
    if (-1 < (int)MyStackIdx) {
      saved_EBP = MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if (saved_EBP == 0) {
      b6 = false;
      if (-1 < (int)MyStackIdx) {
        *out_int = MyStack[(int)MyStackIdx];
        b6 = true;
        MyStackIdx = (int *)((int)MyStackIdx + -1);
      }
    }
    else {
      if (saved_EBP == 1) {
        pi9 = MyStackIdx;
        if (-1 < (int)MyStackIdx) {
          pi2 = MyStack + (int)MyStackIdx;
          MyStackIdx = (int *)((int)MyStackIdx + -1);
          *out_float = *pi2;
          return 2;
        }
        goto L_080851e2;
      }
      if (saved_EBP != 4) {
        return 0;
      }
      b6 = false;
      if (-1 < (int)MyStackIdx) {
        b6 = true;
        *out_int = MyStack[(int)MyStackIdx];
        MyStackIdx = (int *)((int)MyStackIdx + -1);
      }
    }
    pi9 = MyStackIdx;
    if (b6) {
      return 1;
    }
  }
L_080851e2:
  MyStackIdx = pi9;
  sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
          g[G_FRAME_COUNT],player + 8,player[PL_ID],player[PL_STATENO],saved_EDI.i,saved_EDI.i);
  ErrorExit();
  return 0;
}

