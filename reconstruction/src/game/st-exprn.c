/*
 * st-exprn.c -- controller parameter blocks
 * Parsing and evaluating the parameter blocks of the complex controllers:
 * HitDef, Projectile, Explod, Helper, AfterImage, PalFX, EnvShake, Pause,
 * SuperPause, PlaySnd, HitOverride.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/st-exprn.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* TPGetValuePrefix @ 0x080c3810, 49 bytes
 *
 * Reads key prefix + `key` (for example "afterimage." + "time" inside a
 * Projectile) from a controller group.
 *
 * Parameters:
 *   tp           int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Calls: TPGetValue
 * C library: sprintf
 * Called by: SCtrlParseAftImgParams
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
char * TPGetValuePrefix(int tp,uint32_t arg2,uint32_t arg3)

{
  char *value;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define keyname (*(char (*)[84])(frame + 0x4))
  
  sprintf(keyname,"%s%s",arg2,arg3);
  value = TPGetValue(tp,keyname);
  return value;
}
#undef keyname

/* StringAdd @ 0x080c3850, 35 bytes
 *
 * Concatenates two strings into a static buffer (used to build prefixed key
 * names).
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * C library: sprintf
 * Called by: SCtrlParseAftImgParams
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
char * StringAdd(char *arg1,uint32_t arg2,uint32_t arg3)

{
  sprintf(arg1,"%s%s",arg2,arg3);
  return arg1;
}

/* SCtrlParseAftImgParams @ 0x080c3880, 1437 bytes
 *
 * Compiles the AfterImage parameters, optionally with a key prefix: time,
 * length, timegap, framegap, trans and alpha, palcolor, palinvertall,
 * palbright, palcontrast, palpostbright, paladd, palmul. Constants are
 * folded; missing keys get the documented defaults.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *   arg4         uint32_t
 *
 * Calls: ConstExpI, ConstExpF, TPGetValuePrefix, InfixToPostfix,
 *        StringAdd, ItoP_TPConstI, SCtrlReadExpList, GetDrawType
 * Called by: SCtrlParseElemType, SCtrlParseProjectile
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes, 4
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseAftImgParams(int tp,int player,int *expr,uint32_t arg4)

{
  int *expr2;
  uint8_t *value;
  int player2;
  char *keyname;
  int *expr3;
  int i5;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_68 (*(int *)(frame + 0x8))
#define stk_64 (*(int *)(frame + 0xc))
#define stk_60 (*(char **)(frame + 0x10))
#define stk_5c (*(char (*)[76])(frame + 0x14))
  
  ConstExpI(expr + 0x40,0x100);
  ConstExpI(expr + 0x43,0x100);
  ConstExpI(expr + 3,0x14);
  ConstExpI(expr + 6,1);
  ConstExpI(expr + 9,4);
  ConstExpI(expr,1);
  expr2 = expr + 0x15;
  ConstExpI(expr + 0x12,0x1e);
  ConstExpI(expr2,0x1e);
  ConstExpI(expr + 0x18,0x1e);
  ConstExpI(expr + 0x1b,0x78);
  ConstExpI(expr + 0x1e,0x78);
  ConstExpI(expr + 0x21,0xdc);
  ConstExpI(expr + 0x24,0);
  ConstExpI(expr + 0x27,0);
  ConstExpI(expr + 0x2a,0);
  ConstExpI(expr + 0x2d,10);
  ConstExpI(expr + 0x30,10);
  ConstExpI(expr + 0x33,0x19);
  ConstExpF(expr + 0x36,0x3f266666);
  ConstExpF(expr + 0x39,0x3f266666);
  ConstExpF(expr + 0x3c,0x3f400000);
  expr[0x3f] = 0;
  value = (uint8_t *)TPGetValuePrefix(tp,arg4,"time");
  player2 = InfixToPostfix(value,expr,player,(uint32_t *)0x0,1);
  if (player2 != 0) {
    value = (uint8_t *)TPGetValuePrefix(tp,arg4,"length");
    player2 = InfixToPostfix(value,expr + 3,player,(uint32_t *)0x0,1);
    if (player2 != 0) {
      expr3 = expr + 0xc;
      i5 = 0x100;
      player2 = player;
      keyname = StringAdd(stk_5c,arg4,"palcolor");
      player2 = ItoP_TPConstI(tp,keyname,expr3,player2,i5);
      if (player2 != 0) {
        i5 = 0;
        expr3 = expr + 0xf;
        player2 = player;
        keyname = StringAdd(stk_5c,arg4,"palinvertall");
        player2 = ItoP_TPConstI(tp,keyname,expr3,player2,i5);
        if ((((player2 != 0) &&
             ((value = (uint8_t *)TPGetValuePrefix(tp,arg4,"palbright"), value == (uint8_t *)0x0
              || ((value = SCtrlReadExpList(value,"iii",player,&stk_60,expr2,expr2,expr + 0x18
                                            ), value != (uint8_t *)0x0 && (*stk_60 == '\0')))))) &&
            ((value = (uint8_t *)TPGetValuePrefix(tp,arg4,"palcontrast"),
             value == (uint8_t *)0x0 ||
             ((value = SCtrlReadExpList(value,"iii",player,&stk_60,expr + 0x1b,
                                         expr + 0x1e,expr + 0x21), value != (uint8_t *)0x0 &&
              (*stk_60 == '\0')))))) &&
           ((((value = (uint8_t *)TPGetValuePrefix(tp,arg4,"palpostbright"),
              value == (uint8_t *)0x0 ||
              ((value = SCtrlReadExpList(value,"iii",player,&stk_60,expr + 0x24,
                                          expr + 0x27,expr + 0x2a), value != (uint8_t *)0x0 &&
               (*stk_60 == '\0')))) &&
             ((value = (uint8_t *)TPGetValuePrefix(tp,arg4,"paladd"), value == (uint8_t *)0x0 ||
              ((value = SCtrlReadExpList(value,"iii",player,&stk_60,expr + 0x2d,
                                          expr + 0x30,expr + 0x33), value != (uint8_t *)0x0 &&
               (*stk_60 == '\0')))))) &&
            ((value = (uint8_t *)TPGetValuePrefix(tp,arg4,"palmul"), value == (uint8_t *)0x0 ||
             ((value = SCtrlReadExpList(value,"fff",player,&stk_60,expr + 0x36,
                                         expr + 0x39,expr + 0x3c), value != (uint8_t *)0x0 &&
              (*stk_60 == '\0')))))))) {
          value = (uint8_t *)TPGetValuePrefix(tp,arg4,"timegap");
          player2 = InfixToPostfix(value,expr + 6,player,(uint32_t *)0x0,1);
          if (player2 != 0) {
            value = (uint8_t *)TPGetValuePrefix(tp,arg4,"framegap");
            player2 = InfixToPostfix(value,expr + 9,player,(uint32_t *)0x0,1);
            if (player2 != 0) {
              expr[0x3f] = 0;
              keyname = (char *)TPGetValuePrefix(tp,arg4,"trans");
              if (keyname != (char *)0x0) {
                stk_64 = -1;
                stk_68 = -1;
                player2 = GetDrawType(keyname,&stk_68,&stk_64);
                expr[0x3f] = player2;
                if (player2 != -2) {
                  player2 = stk_68;
                  if (stk_68 == -1) {
                    player2 = 0x100;
                  }
                  ConstExpI(expr + 0x40,player2);
                  if (stk_64 != -1) {
                    ConstExpI(expr + 0x43,stk_64);
                  }
                  if ((stk_68 == -1) &&
                     (value = (uint8_t *)TPGetValuePrefix(tp,arg4,"alpha"),
                     value != (uint8_t *)0x0)) {
                    value = SCtrlReadExpList(value,"ii",player,&stk_60,expr + 0x40,
                                              expr + 0x43);
                    if (value == (uint8_t *)0x0) {
                      return 0;
                    }
                    if (*stk_60 != '\0') {
                      return 0;
                    }
                  }
                }
              }
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c

/* SCtrlInitAftImgParams @ 0x080c3e20, 671 bytes
 *
 * Evaluates AfterImage parameters for a player and starts the effect
 * (AftImgSetup). Warnings: "length for afterimage exceeds maximum of %i",
 * "illegal time for afterimage", "illegal length"...
 *
 * Parameters:
 *   expr         int
 *   arg2         int
 *   arg3         uint32_t
 *   player       int *
 *
 * Calls: EvalExpressionI, Warn, VWarn, EvalExpressionF, AftImgSetup
 * Called by: PlayerSCtrlApplyElem, SCtrlInitProjectile
 * Messages:
 *   "length for afterimage exceeds maximum of %i"
 *   "illegal time for afterimage"
 *   "illegal length for afterimage"
 *   "illegal timegap for afterimage"
 *   "illegal framegap for afterimage"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 4 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       20 variables), because their address is taken.
 */
uint32_t SCtrlInitAftImgParams(int expr,int arg2,uint32_t arg3,int *player)

{
  int value;
  int *pi2;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_7c (*(int (*)[5])(frame + 0x4))
#define value2 (*(int *)(frame + 0x18))
#define value3 (*(int *)(frame + 0x1c))
#define value4 (*(int *)(frame + 0x20))
#define value5 (*(int *)(frame + 0x24))
#define value6 (*(int *)(frame + 0x28))
#define value7 (*(int *)(frame + 0x2c))
#define value8 (*(int *)(frame + 0x30))
#define value9 (*(int *)(frame + 0x34))
#define value10 (*(int *)(frame + 0x38))
#define value11 (*(int *)(frame + 0x3c))
#define value12 (*(int *)(frame + 0x40))
#define value13 (*(int *)(frame + 0x44))
#define value14 (*(int *)(frame + 0x48))
#define value15 (*(float *)(frame + 0x4c))
#define value16 (*(float *)(frame + 0x50))
#define value17 (*(float *)(frame + 0x54))
#define stk_28 (*(uint32_t *)(frame + 0x58))
#define value18 (*(int *)(frame + 0x5c))
#define value19 (*(int *)(frame + 0x60))
  
  pi2 = stk_7c;
  for (value = 0x18; value != 0; value = value + -1) {
    *pi2 = 0;
    pi2 = pi2 + 1;
  }
  stk_7c[0] = EvalExpressionI((int)player,expr,1);
  if (stk_7c[0] < -1) {
    stk_7c[0] = 1;
    Warn((int)player,(int)&str_illegal_time_for_afterimage_b7c4);
  }
  value = EvalExpressionI((int)player,expr + 0xc,1);
  if (value < 1) {
    stk_7c[1] = 0x14;
    Warn((int)player,(int)&str_illegal_length_for_afterimag_b7e0);
    value = stk_7c[1];
  }
  else {
    stk_7c[1] = *(int *)(arg2 + 4);
    if (stk_7c[1] < value) {
      VWarn((int)player,"length for afterimage exceeds maximum of %i",*(uint32_t *)(arg2 + 4),
            pi2);
      value = stk_7c[1];
    }
  }
  stk_7c[1] = value;
  stk_7c[2] = EvalExpressionI((int)player,expr + 0x18,1);
  if (stk_7c[2] < 1) {
    stk_7c[2] = 1;
    Warn((int)player,(int)&str_illegal_timegap_for_afterima_c220);
  }
  stk_7c[3] = EvalExpressionI((int)player,expr + 0x24,1);
  if (stk_7c[3] < 1) {
    stk_7c[3] = 4;
    Warn((int)player,(int)&str_illegal_framegap_for_afterim_c240);
  }
  stk_7c[4] = EvalExpressionI((int)player,expr + 0x30,1);
  value2 = EvalExpressionI((int)player,expr + 0x3c,1);
  value3 = EvalExpressionI((int)player,expr + 0x48,1);
  value4 = EvalExpressionI((int)player,expr + 0x54,1);
  value5 = EvalExpressionI((int)player,expr + 0x60,1);
  value6 = EvalExpressionI((int)player,expr + 0x6c,1);
  value7 = EvalExpressionI((int)player,expr + 0x78,1);
  value8 = EvalExpressionI((int)player,expr + 0x84,1);
  value9 = EvalExpressionI((int)player,expr + 0x90,1);
  value10 = EvalExpressionI((int)player,expr + 0x9c,1);
  value11 = EvalExpressionI((int)player,expr + 0xa8,1);
  value12 = EvalExpressionI((int)player,expr + 0xb4,1);
  value13 = EvalExpressionI((int)player,expr + 0xc0,1);
  value14 = EvalExpressionI((int)player,expr + 0xcc,1);
  value15 = EvalExpressionF(player,(int *)(expr + 0xd8));
  value16 = EvalExpressionF(player,(int *)(expr + 0xe4));
  value17 = EvalExpressionF(player,(int *)(expr + 0xf0));
  stk_28 = *(uint32_t *)(expr + 0xfc);
  value18 = EvalExpressionI((int)player,expr + 0x100,1);
  value19 = EvalExpressionI((int)player,expr + 0x10c,1);
  AftImgSetup(arg2,stk_7c,arg3);
  return 1;
}
#undef stk_7c
#undef value2
#undef value3
#undef value4
#undef value5
#undef value6
#undef value7
#undef value8
#undef value9
#undef value10
#undef value11
#undef value12
#undef value13
#undef value14
#undef value15
#undef value16
#undef value17
#undef stk_28
#undef value18
#undef value19

/* AftImgParamsEFree @ 0x080c40c0, 297 bytes
 *
 * Frees an AfterImage parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 * Called by: ProjMakeInfoFree, SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void AftImgParamsEFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 6);
  FreeExpression(expr + 9);
  FreeExpression(expr + 0xc);
  FreeExpression(expr + 0xf);
  FreeExpression(expr + 0x12);
  FreeExpression(expr + 0x15);
  FreeExpression(expr + 0x18);
  FreeExpression(expr + 0x1b);
  FreeExpression(expr + 0x1e);
  FreeExpression(expr + 0x21);
  FreeExpression(expr + 0x24);
  FreeExpression(expr + 0x27);
  FreeExpression(expr + 0x2a);
  FreeExpression(expr + 0x2d);
  FreeExpression(expr + 0x30);
  FreeExpression(expr + 0x33);
  FreeExpression(expr + 0x36);
  FreeExpression(expr + 0x39);
  FreeExpression(expr + 0x3c);
  FreeExpression(expr + 0x40);
  FreeExpression(expr + 0x43);
  return;
}

/* SCtrlParseEnvShake @ 0x080c41f0, 285 bytes
 *
 * Compiles the EnvShake parameters, optionally with a key prefix
 * ("envshake." / "fall.envshake." inside a HitDef): time (default 0), dir,
 * ampl (default -4), freq (default 60.0), phase (default 0; a missing phase
 * is remembered so the default can depend on freq).
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *   arg4         uint32_t
 *
 * Calls: ItoP_TPConstI, ItoP_TPConstF, TPGetValue
 * C library: sprintf
 * Called by: SCtrlParseElemType, SCtrlParseHitDef
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseEnvShake(int tp,int player,int *expr,uint32_t arg4)

{
  int i1;
  char *value;
  uint32_t stale_ECX;
  uint32_t stale_EDX;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define keyname (*(char (*)[76])(frame + 0x4))
  
  sprintf(keyname,"%stime",arg4);
  i1 = ItoP_TPConstI(tp,keyname,expr,player,0);
  if (i1 != 0) {
    sprintf(keyname,"%sdir",arg4,i1);
    i1 = ItoP_TPConstI(tp,keyname,expr + 3,player,0);
    if (i1 != 0) {
      sprintf(keyname,"%sampl",arg4,stale_ECX);
      i1 = ItoP_TPConstI(tp,keyname,expr + 9,player,-4);
      if (i1 != 0) {
        sprintf(keyname,"%sfreq",arg4,stale_EDX);
        i1 = ItoP_TPConstF(tp,keyname,expr + 6,player,0x42700000);
        if (i1 != 0) {
          sprintf(keyname,"%sphase",arg4,i1);
          i1 = ItoP_TPConstF(tp,keyname,expr + 0xc,player,0);
          if (i1 != 0) {
            value = TPGetValue(tp,keyname);
            expr[0xf] = (uint32_t)(value == (char *)0x0);
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
#undef keyname

/* SCtrlInitEnvShake @ 0x080c4310, 200 bytes
 *
 * Evaluates EnvShake parameters and starts the screen shake. Warning:
 * "negative freq for EnvShake".
 *
 * Parameters:
 *   expr         int *
 *   arg2         uint32_t *
 *   player       int *
 *
 * Calls: EvalExpressionI, EvalExpressionF, Warn
 * Called by: PlayerSCtrlApplyElem, SCtrlInitHitDef
 * Messages:
 *   "negative freq for EnvShake"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 3 assignments,
 *       0 calls, 0 returns
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t SCtrlInitEnvShake(int *expr,uint32_t *arg2,int *player)

{
  int value;
  uint32_t *pu2;
  float80 value2;
  
  pu2 = arg2;
  for (value = 6; value != 0; value = value + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  value = EvalExpressionI((int)player,expr,1);
  arg2[1] = value;
  value2 = EvalExpressionF(player,expr + 9);
  arg2[4] = BITS_F2I(uint32_t, value2);
  value2 = EvalExpressionF(player,expr + 0xc);
  arg2[5] = BITS_F2I(uint32_t, value2);
  value2 = EvalExpressionF(player,expr + 6);
  if (value2 == 0.0) {
    value2 = ((float)0.001f);
  }
  if (value2 < 0.0) {
    value2 = value2 * -1.0;
    Warn((int)player,(int)&str_negative_freq_for_envshake_b821);
  }
  value = expr[0xf];
  arg2[3] = BITS_F2I(uint32_t, value2);
  if ((value != 0) && (90.0 <= value2)) {
    arg2[5] = 0x42b40000;
  }
  *arg2 = 0;
  return 1;
}

/* EnvShakeEFree @ 0x080c43e0, 63 bytes
 *
 * Frees an EnvShake parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 * Called by: HitDefEFree, SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void EnvShakeEFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 6);
  FreeExpression(expr + 9);
  FreeExpression(expr + 0xc);
  return;
}

/* SCtrlParseExplod @ 0x080c4420, 1776 bytes
 *
 * Compiles the Explod parameters: anim (with the "F" prefix for fightfx),
 * id, pos, postype, facing, vfacing, bindtime, vel/velocity, accel, random,
 * removetime, supermove/supermovetime, pausemovetime, scale, sprpriority,
 * ontop, shadow, ownpal, removeongethit, ignorehitpause, trans and alpha.
 * "Illegal postype" on a bad position type.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *   arg4         int
 *
 * Text keys read: "id", "anim", "pos", "vel", "velocity", "accel",
 *                 "random", "supermove", "supermovetime", "pausemovetime",
 *                 "removetime", "scale", "postype", "bindtime",
 *                 "sprpriority", "ontop", "facing", "vfacing", "shadow",
 *                 "ownpal", "removeongethit", "ignorehitpause", "trans",
 *                 "alpha"
 * Globals read: errmsg
 * Calls: ConstExpF, ItoP_TPConstI, TPGetValue, InfixToPostfix,
 *        SCtrlReadExpList, ParsePosType, ConstExpI, GetDrawType
 * C library: sprintf
 * Called by: SCtrlParseElemType
 * Messages:
 *   "Illegal postype: %s"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 3
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseExplod(int tp,int player,int *expr,int arg4)

{
  int i1;
  uint8_t *value;
  char *value2;
  uint32_t stale_EDX;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_1c (*(int *)(frame + 0x4))
#define stk_18 (*(int *)(frame + 0x8))
#define stk_14 (*(char **)(frame + 0xc))
  
  expr[0x31] = ((arg4 != 0) - 1 & 0x7fef) - 0x7fef;
  if (arg4 == 0) {
    i1 = 0x3f800000;
  }
  else {
    i1 = -0x39001000;
  }
  ConstExpF(expr + 0x2b,i1);
  if (arg4 == 0) {
    i1 = 0x3f800000;
  }
  else {
    i1 = -0x39001000;
  }
  ConstExpF(expr + 0x2e,i1);
  i1 = ItoP_TPConstI(tp,"id",expr,player,(arg4 == 0) - 1);
  if (i1 == 0) {
    return 0;
  }
  value = (uint8_t *)TPGetValue(tp,"anim");
  if (value != (uint8_t *)0x0) {
    if ((*value == 0x66) || (*value == 0x46)) {
      i1 = InfixToPostfix(value + 1,expr + 3,player,(uint32_t *)0x0,1);
      if (i1 == 0) {
        return 0;
      }
      expr[6] = 1;
    }
    else {
      i1 = InfixToPostfix(value,expr + 3,player,(uint32_t *)0x0,1);
      if (i1 == 0) {
        return 0;
      }
    }
  }
  value = (uint8_t *)TPGetValue(tp,"pos");
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"ii",player,&stk_14,expr + 7,expr + 10);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  value = (uint8_t *)TPGetValue(tp,"vel");
  if (value == (uint8_t *)0x0) {
    value = (uint8_t *)TPGetValue(tp,"velocity");
  }
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0xd,expr + 0x10);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  value = (uint8_t *)TPGetValue(tp,"accel");
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x13,expr + 0x16);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  value = (uint8_t *)TPGetValue(tp,"random");
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"ii",player,&stk_14,expr + 0x19,expr + 0x1c);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  i1 = ItoP_TPConstI(tp,"supermove",expr + 0x1f,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"supermovetime",expr + 0x22,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"pausemovetime",expr + 0x25,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"removetime",expr + 0x28,player,
                        ((arg4 == 0) - 1 & 0xffff8013) - 2);
  if (i1 == 0) {
    return 0;
  }
  value = (uint8_t *)TPGetValue(tp,"scale");
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x2b,expr + 0x2e);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  value2 = TPGetValue(tp,"postype");
  if (value2 != (char *)0x0) {
    i1 = ParsePosType(value2);
    expr[0x31] = i1;
    if (i1 == -1) {
      sprintf((char *)(g + G_ERRMSG),"Illegal postype: %s",value2,stale_EDX);
      return 0;
    }
  }
  i1 = ItoP_TPConstI(tp,"bindtime",expr + 0x32,player,
                        ((arg4 == 0) - 1 & 0xffff8010) + 1);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"sprpriority",expr + 0x35,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"ontop",expr + 0x38,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"facing",expr + 0x3b,player,1);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"vfacing",expr + 0x3e,player,1);
  if (i1 == 0) {
    return 0;
  }
  if (arg4 != 0) {
    ConstExpI(expr + 0x41,-0x7fef);
  }
  value = (uint8_t *)TPGetValue(tp,"shadow");
  if (value != (uint8_t *)0x0) {
    value = SCtrlReadExpList(value,"iii",player,&stk_14,expr + 0x41,expr + 0x44,
                              expr + 0x47);
    if (value == (uint8_t *)0x0) {
      return 0;
    }
    if (*stk_14 != '\0') {
      return 0;
    }
  }
  i1 = ItoP_TPConstI(tp,"ownpal",expr + 0x4a,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"removeongethit",expr + 0x4d,player,
                        ((arg4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (i1 == 0) {
    return 0;
  }
  i1 = ItoP_TPConstI(tp,"ignorehitpause",expr + 0x50,player,
                        ((arg4 == 0) - 1 & 0xffff8010) + 1);
  if (i1 == 0) {
    return 0;
  }
  expr[0x53] = ((arg4 == 0) - 1 & 0xffff8012) - 1;
  value2 = TPGetValue(tp,"trans");
  if (value2 == (char *)0x0) {
    return 1;
  }
  stk_18 = -1;
  stk_1c = -1;
  i1 = GetDrawType(value2,&stk_1c,&stk_18);
  expr[0x53] = i1;
  if (i1 == -2) {
    return 1;
  }
  i1 = stk_1c;
  if (stk_1c == -1) {
    if (arg4 == 0) {
      i1 = 0x100;
    }
    else {
      i1 = -0x7fef;
    }
  }
  ConstExpI(expr + 0x54,i1);
  i1 = stk_18;
  if (stk_18 == -1) {
    if (arg4 == 0) goto L_080c4aaa;
    i1 = -0x7fef;
  }
  ConstExpI(expr + 0x57,i1);
L_080c4aaa:
  if (((stk_1c == -1) && (value = (uint8_t *)TPGetValue(tp,"alpha"), value != (uint8_t *)0x0)) &&
     ((value = SCtrlReadExpList(value,"ii",player,&stk_14,expr + 0x54,expr + 0x57),
      value == (uint8_t *)0x0 || (*stk_14 != '\0')))) {
    return 0;
  }
  return 1;
}
#undef stk_1c
#undef stk_18
#undef stk_14

/* ExplodInfoFree @ 0x080c4b10, 381 bytes
 *
 * Frees an Explod parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void ExplodInfoFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 7);
  FreeExpression(expr + 10);
  FreeExpression(expr + 0xd);
  FreeExpression(expr + 0x10);
  FreeExpression(expr + 0x13);
  FreeExpression(expr + 0x16);
  FreeExpression(expr + 0x19);
  FreeExpression(expr + 0x1c);
  FreeExpression(expr + 0x1f);
  FreeExpression(expr + 0x22);
  FreeExpression(expr + 0x25);
  FreeExpression(expr + 0x28);
  FreeExpression(expr + 0x2b);
  FreeExpression(expr + 0x2e);
  FreeExpression(expr + 0x32);
  FreeExpression(expr + 0x35);
  FreeExpression(expr + 0x38);
  FreeExpression(expr + 0x3b);
  FreeExpression(expr + 0x3e);
  FreeExpression(expr + 0x41);
  FreeExpression(expr + 0x44);
  FreeExpression(expr + 0x47);
  FreeExpression(expr + 0x4a);
  FreeExpression(expr + 0x4d);
  FreeExpression(expr + 0x50);
  FreeExpression(expr + 0x54);
  FreeExpression(expr + 0x57);
  return;
}

/* SCtrlParsePalFX @ 0x080c4c90, 491 bytes
 *
 * Compiles PalFX parameters (time, add, mul, sinadd, invertall, color),
 * optionally with the "palfx." prefix used inside a HitDef.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   arg3         int
 *   arg4         int
 *
 * Calls: ConstExpI, TPGetValue, InfixToPostfix, SCtrlReadExpList,
 *        ItoP_TPConstI
 * Called by: SCtrlParseElemType, SCtrlParseHitDef
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
bool SCtrlParsePalFX(int tp,int player,int arg3,int arg4)

{
  char *keyname;
  uint8_t *value;
  int i3;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(char **)(frame + 0xc))
  
  ConstExpI((int *)(arg3 + 0x40),0x100);
  ConstExpI((int *)(arg3 + 0x4c),0x100);
  ConstExpI((int *)(arg3 + 0x58),0x100);
  keyname = "palfx.time";
  if (arg4 == 0) {
    keyname = "time";
  }
  value = (uint8_t *)TPGetValue(tp,keyname);
  i3 = InfixToPostfix(value,(int *)(arg3 + 4),player,(uint32_t *)0x0,1);
  if (i3 != 0) {
    keyname = "palfx.mul";
    if (arg4 == 0) {
      keyname = "mul";
    }
    value = (uint8_t *)TPGetValue(tp,keyname);
    if ((value == (uint8_t *)0x0) ||
       ((value = SCtrlReadExpList(value,"iii",player,&stk_14,(int *)(arg3 + 0x40),
                                   (int *)(arg3 + 0x4c),(int *)(arg3 + 0x58)),
        value == (uint8_t *)0x3 && (*stk_14 == '\0')))) {
      keyname = "palfx.add";
      if (arg4 == 0) {
        keyname = "add";
      }
      value = (uint8_t *)TPGetValue(tp,keyname);
      if ((value == (uint8_t *)0x0) ||
         ((value = SCtrlReadExpList(value,"iii",player,&stk_14,(int *)(arg3 + 0x1c),
                                     (int *)(arg3 + 0x28),(int *)(arg3 + 0x34)),
          value == (uint8_t *)0x3 && (*stk_14 == '\0')))) {
        keyname = "palfx.sinadd";
        if (arg4 == 0) {
          keyname = "sinadd";
        }
        value = (uint8_t *)TPGetValue(tp,keyname);
        if ((value == (uint8_t *)0x0) ||
           ((value = SCtrlReadExpList(value,"iiii",player,&stk_14,(int *)(arg3 + 100),
                                       (int *)(arg3 + 0x70),(int *)(arg3 + 0x7c),
                                       (int *)(arg3 + 0x94)), value + -3 < (uint8_t *)0x2 &&
            (*stk_14 == '\0')))) {
          keyname = "palfx.invertall";
          if (arg4 == 0) {
            keyname = "invertall";
          }
          i3 = ItoP_TPConstI(tp,keyname,(int *)(arg3 + 0x88),player,0);
          if (i3 != 0) {
            keyname = "palfx.color";
            if (arg4 == 0) {
              keyname = "color";
            }
            i3 = ItoP_TPConstI(tp,keyname,(int *)(arg3 + 0x10),player,0x100);
            return i3 != 0;
          }
        }
      }
    }
  }
  return false;
}
#undef stk_14

/* SCtrlInitPalFX @ 0x080c4e80, 414 bytes
 *
 * Evaluates PalFX parameters and starts the effect on the player's palette
 * group (or all palettes for AllPalFX). Warnings: "invalid PalFX time",
 * "invalid PalFX color value", "invalid PalFX mul value".
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t *
 *   player       int
 *
 * Calls: EvalExpressionI, Warn
 * Called by: PlayerSCtrlApplyElem, SCtrlInitHitDef
 * Messages:
 *   "invalid PalFX time"
 *   "invalid PalFX color value"
 *   "invalid PalFX mul value"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 3 data addresses refer to the data image (data/mugen_data.S).
 */
uint32_t SCtrlInitPalFX(int *arg1,uint32_t *arg2,int player)

{
  uint32_t value;
  int value2;
  int *pi3;
  
  if (*arg1 == 1) {
    arg2 = g + 0x6ed5;
  }
  else if (*arg1 == 2) {
    arg2 = g + 0x6ee4;
  }
  pi3 = arg2;
  for (value2 = 0xf; value2 != 0; value2 = value2 + -1) {
    *pi3 = 0;
    pi3 = pi3 + 1;
  }
  value2 = EvalExpressionI(player,arg1 + 1,1);
  arg2[1] = value2;
  if (value2 < -1) {
    arg2[1] = 0;
    Warn(player,(int)&str_invalid_palfx_time_b8cb);
  }
  value = EvalExpressionI(player,arg1 + 4,1);
  arg2[2] = value;
  if (0x100 < value) {
    Warn(player,(int)&str_invalid_palfx_color_value_b8de);
  }
  value2 = EvalExpressionI(player,arg1 + 7,1);
  arg2[3] = value2;
  value2 = EvalExpressionI(player,arg1 + 10,1);
  arg2[4] = value2;
  value2 = EvalExpressionI(player,arg1 + 0xd,1);
  arg2[5] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x10,1);
  arg2[6] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x13,1);
  arg2[7] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x16,1);
  arg2[8] = value2;
  if ((((int)arg2[6] < 0) || ((int)arg2[7] < 0)) || (value2 < 0)) {
    Warn(player,(int)&str_invalid_palfx_mul_value_b8f8);
  }
  value2 = EvalExpressionI(player,arg1 + 0x19,1);
  arg2[9] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x1c,1);
  arg2[10] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x1f,1);
  arg2[0xb] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x25,1);
  arg2[0xd] = value2;
  value2 = EvalExpressionI(player,arg1 + 0x22,1);
  arg2[0xc] = value2;
  return 1;
}

/* PalFXEFree @ 0x080c5020, 160 bytes
 *
 * Frees a PalFX parameter block.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: FreeExpression
 * Called by: HitDefEFree, SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void PalFXEFree(int arg1)

{
  FreeExpression((int *)(arg1 + 4));
  FreeExpression((int *)(arg1 + 0x10));
  FreeExpression((int *)(arg1 + 0x1c));
  FreeExpression((int *)(arg1 + 0x28));
  FreeExpression((int *)(arg1 + 0x34));
  FreeExpression((int *)(arg1 + 0x40));
  FreeExpression((int *)(arg1 + 0x4c));
  FreeExpression((int *)(arg1 + 0x58));
  FreeExpression((int *)(arg1 + 100));
  FreeExpression((int *)(arg1 + 0x70));
  FreeExpression((int *)(arg1 + 0x7c));
  FreeExpression((int *)(arg1 + 0x88));
  FreeExpression((int *)(arg1 + 0x94));
  return;
}

/* SCtrlParsePlaySndInfo @ 0x080c50c0, 465 bytes
 *
 * Compiles PlaySnd parameters: value (sound "[F]group, number"), volume,
 * channel, lowpriority, freqmul, loop, pan / abspan.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *
 * Text keys read: "value", "volume", "channel", "lowpriority", "freqmul",
 *                 "loop", "abspan", "pan"
 * Calls: TPGetValue, ConstExpI, ParseSnd, InfixToPostfix
 * Called by: SCtrlParseElemType
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SCtrlParsePlaySndInfo(int tp,int player,int *expr)

{
  uint8_t *value;
  int i2;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(int *)(frame + 0xc))
  
  value = (uint8_t *)TPGetValue(tp,"value");
  if (value != (uint8_t *)0x0) {
    ConstExpI(expr,-1);
    ConstExpI(expr + 0x10,1);
    stk_14 = 0;
    i2 = ParseSnd(value,expr + 3,expr + 6,&stk_14,player);
    if (i2 != 0) {
      expr[0xc] = stk_14;
      value = (uint8_t *)TPGetValue(tp,"volume");
      i2 = InfixToPostfix(value,expr + 9,player,(uint32_t *)0x0,1);
      if (i2 != 0) {
        value = (uint8_t *)TPGetValue(tp,"channel");
        i2 = InfixToPostfix(value,expr,player,(uint32_t *)0x0,1);
        if (i2 != 0) {
          value = (uint8_t *)TPGetValue(tp,"lowpriority");
          i2 = InfixToPostfix(value,expr + 0xd,player,(uint32_t *)0x0,1);
          if (i2 != 0) {
            value = (uint8_t *)TPGetValue(tp,"freqmul");
            i2 = InfixToPostfix(value,expr + 0x10,player,(uint32_t *)0x0,2);
            if (i2 != 0) {
              value = (uint8_t *)TPGetValue(tp,"loop");
              i2 = InfixToPostfix(value,expr + 0x13,player,(uint32_t *)0x0,1);
              if (i2 != 0) {
                value = (uint8_t *)TPGetValue(tp,"abspan");
                if (value == (uint8_t *)0x0) {
                  value = (uint8_t *)TPGetValue(tp,"pan");
                  i2 = InfixToPostfix(value,expr + 0x17,player,(uint32_t *)0x0,1);
                  if (i2 != 0) {
                    return 1;
                  }
                }
                else {
                  i2 = InfixToPostfix(value,expr + 0x17,player,(uint32_t *)0x0,1);
                  if (i2 != 0) {
                    expr[0x16] = 1;
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
#undef stk_14

/* SCtrlDoPlaySndInfo @ 0x080c52a0, 840 bytes
 *
 * Executes a PlaySnd for a player. It evaluates the parameters and picks the
 * player's own sounds or common.snd (the "F" prefix). It respects
 * "lowpriority" when the channel is busy, prepares the voice, then sets
 * panning (relative to the player's screen position, or absolute), volume,
 * frequency and loop, and starts it. Warnings: "Illegal playsnd channel.",
 * "Illegal playsnd groupno.", ...
 *
 * Parameters:
 *   player       int *
 *   expr         int
 *
 * Player fields read: pos_x, facing
 * Globals read: sound_linux_stereoeffects, sound_linux_wavvolume
 * Calls: EvalExpressionI, Warn, PlayerSndID, SndIDIsPlaying, SndIDPrepare,
 *        ScrPositionToPan, SndCorrectVolOff, PanVolumeAdjust,
 *        SndVoiceGetFreq, EvalExpressionF, SndVoiceSetVol,
 *        SndVoiceSetFreq, SndVoiceSetPan, SndVoiceSetLoop, SndVoiceStart
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "Illegal playsnd channel."
 *   "Illegal playsnd groupno."
 *   "Illegal playsnd sndno."
 *   "Non-positive freqmul."
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 4 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int SCtrlDoPlaySndInfo(int *player,int expr)

{
  int value;
  int value2;
  int *pi3;
  int value3;
  int *sounds;
  float80 value4;
  
  pi3 = g;
  if (((g[0x6ef3] != 0) && (expr != 0)) && (g[0x7308] == 0)) {
    if (*(int *)(expr + 0x30) == 0) {
      sounds = (int *)((int *)*player)[0x475];
      pi3 = (int *)*player;
    }
    else {
      sounds = (int *)g[0x4156];
    }
    if (sounds != (int *)0x0) {
      value = EvalExpressionI((int)player,expr,1);
      if (0x20 < value + 1U) {
        value = -1;
        Warn((int)player,(int)&str_illegal_playsnd_channel_b924);
      }
      value = PlayerSndID((int)player,value);
      value2 = EvalExpressionI((int)player,expr + 0x34,1);
      if (((value2 == 0) || (value == -1)) ||
         (pi3 = (int *)SndIDIsPlaying(value), pi3 == (int *)0x0)) {
        value2 = EvalExpressionI((int)player,expr + 0xc,1);
        if (value2 < -1) {
          value2 = -1;
          Warn((int)player,(int)&str_illegal_playsnd_groupno_b93d);
        }
        value3 = EvalExpressionI((int)player,expr + 0x18,1);
        if (value3 < -1) {
          value3 = -1;
          Warn((int)player,(int)&str_illegal_playsnd_sndno_b956);
        }
        pi3 = (int *)SndIDPrepare(value,sounds,value2,value3);
        if ((pi3 != (int *)0xffffffff) && (value2 != -1)) {
          value = EvalExpressionI((int)player,expr + 0x5c,1);
          if (*(int *)(expr + 0x58) == 0) {
            value = (int)X87_FIST32((BITS_I2F(player[PL_POS_X]) - (float)g[0x7311]) +
                               (float)(value * player[PL_FACING]));
          }
          else {
            value = value * player[PL_FACING] + 0xa0;
          }
          if (g[G_SOUND_LINUX_STEREOEFFECTS] == 0) {
            value = 0;
          }
          else {
            value = ScrPositionToPan(value);
          }
          value2 = EvalExpressionI((int)player,expr + 0x24,1);
          value2 = SndCorrectVolOff(value2);
          value2 = value2 + g[G_SOUND_LINUX_WAVVOLUME];
          if (*(int *)(expr + 0x30) == 0) {
            value3 = SndCorrectVolOff(*(int *)(*player + 0x11d0));
            value2 = value2 + value3;
          }
          value3 = PanVolumeAdjust(value2,value);
          value2 = SndVoiceGetFreq((int)pi3);
          value4 = EvalExpressionF(player,(int *)(expr + 0x40));
          if (value4 <= 0.0) {
            value4 = 1.0;
            Warn((int)player,(int)&str_non_positive_freqmul_b96d);
          }
          if ((value4 != 1.0) && (value2 = (int)X87_FIST32((float80)value2 * value4), value2 < 0x65)) {
            value2 = 100;
          }
          SndVoiceSetVol((int)pi3,value3);
          SndVoiceSetFreq((int)pi3,value2);
          SndVoiceSetPan((int)pi3,value);
          value = EvalExpressionI((int)player,expr + 0x4c,1);
          SndVoiceSetLoop((int)pi3,(uint32_t)(value != 0));
          pi3 = (int *)SndVoiceStart((int)pi3);
        }
      }
    }
  }
  return (int)pi3;
}

/* PlaySndInfoFree @ 0x080c55f0, 96 bytes
 *
 * Frees a PlaySnd parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void PlaySndInfoFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 6);
  FreeExpression(expr + 9);
  FreeExpression(expr + 0xd);
  FreeExpression(expr + 0x10);
  FreeExpression(expr + 0x13);
  FreeExpression(expr + 0x17);
  return;
}

/* SCtrlParseHitOverride @ 0x080c5650, 238 bytes
 *
 * Compiles HitOverride parameters: attr, slot, stateno, time, forceair.
 * "Invalid attr: %s" for a bad attribute string.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   arg3         int *
 *
 * Text keys read: "attr", "stateno", "time", "forceair"
 * Globals read: errmsg
 * Calls: ConstExpI, TPGetValue, ParseHitAttr, InfixToPostfix,
 *        ItoP_TPConstI
 * C library: sprintf
 * Called by: SCtrlParseElemType
 * Messages:
 *   "Invalid attr: %s"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
bool SCtrlParseHitOverride(int tp,int player,int *arg3)

{
  char *value;
  uint32_t u2;
  uint8_t *value2;
  int i4;
  uint32_t stale_ECX;
  
  ConstExpI(arg3 + 4,1);
  ConstExpI(arg3 + 1,-1);
  value = TPGetValue(tp,"attr");
  if (value != (char *)0x0) {
    u2 = ParseHitAttr((int)value,0);
    *arg3 = u2;
    if (u2 == 0xffffffff) {
      sprintf((char *)(g + G_ERRMSG),"Invalid attr: %s",value,stale_ECX);
      return false;
    }
  }
  value2 = (uint8_t *)TPGetValue(tp,"stateno");
  i4 = InfixToPostfix(value2,arg3 + 1,player,(uint32_t *)0x0,1);
  if (i4 != 0) {
    value2 = (uint8_t *)TPGetValue(tp,"time");
    i4 = InfixToPostfix(value2,arg3 + 4,player,(uint32_t *)0x0,1);
    if (i4 != 0) {
      i4 = ItoP_TPConstI(tp,"forceair",arg3 + 7,player,0);
      return i4 != 0;
    }
  }
  return false;
}

/* SCtrlInitHitOverride @ 0x080c5740, 151 bytes
 *
 * Evaluates HitOverride parameters into one of the player's override slots.
 * Warnings: "Illegal hitoverride stateno.", "Illegal hitoverride time.".
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *   player       int
 *
 * Calls: EvalExpressionI, Warn
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "Illegal hitoverride stateno."
 *   "Illegal hitoverride time."
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 2 data addresses refer to the data image (data/mugen_data.S).
 */
uint32_t SCtrlInitHitOverride(uint32_t *arg1,uint32_t *arg2,int player)

{
  int value;
  
  *arg2 = 1;
  arg2[1] = *arg1;
  value = EvalExpressionI(player,arg1 + 1,1);
  if (value < -1) {
    value = -1;
    Warn(player,(int)&str_illegal_hitoverride_stateno_b99d);
  }
  arg2[2] = value;
  value = EvalExpressionI(player,arg1 + 4,1);
  if (value < -1) {
    value = 1;
    Warn(player,(int)&str_illegal_hitoverride_time_b9ba);
  }
  arg2[3] = value;
  value = EvalExpressionI(player,arg1 + 7,1);
  arg2[4] = value;
  return 1;
}

/* HitOverrideEFree @ 0x080c57e0, 44 bytes
 *
 * Frees a HitOverride parameter block.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: FreeExpression
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void HitOverrideEFree(int arg1)

{
  FreeExpression((int *)(arg1 + 4));
  FreeExpression((int *)(arg1 + 0x10));
  FreeExpression((int *)(arg1 + 0x1c));
  return;
}

/* SCtrlParseHitDef @ 0x080c5810, 6992 bytes
 *
 * Compiles every HitDef parameter (also used for ReversalDef and
 * Projectile). Groups of keys:
 * - attack: attr, hitflag, guardflag, affectteam, animtype, air.animtype,
 * fall.animtype, priority, damage, pausetime, guard.pausetime, sparkno,
 * guard.sparkno, sparkxy, hitsound, guardsound;
 * - ground, guard and air reaction: ground.type, air.type,
 * ground/guard.slidetime, ground/guard/air.hittime, guard.ctrltime,
 * guard.dist, yaccel, ground/guard/air/airguard/down.velocity, the
 * cornerpush.veloff values, down.hittime, down.bounce;
 * - state changes: id, chainid, nochainid, hitonce, kill, guard.kill,
 * fall.kill, numhits, getpower, givepower, p1sprpriority, p2sprpriority,
 * p1facing, p1getp2facing, p2facing, p1stateno, p2stateno, p2getp1state,
 * forcestand;
 * - falls: fall, fall.xvelocity, fall.yvelocity, fall.recover,
 * fall.recovertime, fall.damage, air.fall, air.juggle;
 * - other: mindist, maxdist, snap, attack.width, the "palfx." effect, and
 * the "envshake." and "fall.envshake." shakes.
 *
 * Constant values are folded; several values are pre-scaled
 * (ExpMulF/ExpDivI).
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   hitdef       uint32_t *
 *
 * Text keys read: "attr", "affectteam", "id", "chainid", "nochainid",
 *                 "sparkno", "guard.sparkno", "sparkxy", "pausetime",
 *                 "guard.pausetime", "kill", "guard.kill", "fall.kill",
 *                 "hitonce", "numhits", "damage", "getpower", "givepower",
 *                 "priority", "hitsound", "guardsound",
 *                 "ground.slidetime", "ground.hittime", "ground.velocity",
 *                 ...
 * Globals read: rules_default_attack_lifetopowermul,
 *               rules_default_gethit_lifetopowermul, errmsg
 * Calls: ConstExpI, TPGetValue, ParseHitAttr, InfixToPostfix,
 *        SCtrlReadExpList, expcpytrig, ItoP_TPConstI, ExpMulF, ExpDivI,
 *        ParseSnd, ParseVel, ConstExpF, FreeExpression, ParseHitFlag,
 *        SCtrlParsePalFX, SCtrlParseEnvShake
 * C library: memcpy
 * Called by: SCtrlParseElemType, SCtrlParseProjectile
 * Messages:
 *   "Invalid animtype"
 *   "Invalid air.animtype"
 *   "Invalid fall.animtype"
 *   "Invalid ground.type"
 *   "Invalid air.type"
 *   "Invalid affectteam value"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
bool SCtrlParseHitDef(int tp,int player,uint32_t *hitdef)

{
  int *expr;
  int *expr2;
  uint8_t b1;
  bool b2;
  char *value;
  uint32_t u4;
  uint8_t *value2;
  int i6;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int *expr3;
  uint32_t stale_var_01;
  size_t n;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(char **)(frame + 0xc))
  
  ConstExpI(hitdef + 0x38,-1);
  ConstExpI(hitdef + 0x3f,-1);
  hitdef[0x45] = 1;
  hitdef[0x3e] = 1;
  ConstExpI(hitdef + 0x4c,-1);
  ConstExpI(hitdef + 0x4f,-1);
  ConstExpI(hitdef + 0xf2,-1);
  ConstExpI(hitdef + 5,-1);
  ConstExpI(hitdef + 8,-1);
  ConstExpI(hitdef + 0xb,-1);
  *hitdef = 2;
  value = TPGetValue(tp,"attr");
  if (value != (char *)0x0) {
    u4 = ParseHitAttr((int)value,0);
    hitdef[1] = u4;
    if (u4 == 0xffffffff) {
      return false;
    }
  }
  value = TPGetValue(tp,"affectteam");
  if (value == (char *)0x0) {
L_080c5957:
    ConstExpI(hitdef + 0x1a,-1);
    ConstExpI(hitdef + 0x35,1);
    ConstExpI(hitdef + 0x65,0);
    value2 = (uint8_t *)TPGetValue(tp,"id");
    i6 = InfixToPostfix(value2,hitdef + 2,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"chainid");
    i6 = InfixToPostfix(value2,hitdef + 5,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"nochainid");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 8,hitdef + 0xb);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    expr3 = hitdef + 0x8d;
    ConstExpI(expr3,-2);
    value2 = (uint8_t *)TPGetValue(tp,"sparkno");
    if (value2 != (uint8_t *)0x0) {
      if (*(int *)(__ctype_tolower + (char)*value2 * 4) == 0x73) {
        i6 = InfixToPostfix(value2 + 1,expr3,player,(uint32_t *)0x0,1);
        if (i6 == 0) {
          return false;
        }
        hitdef[0x90] = 1;
      }
      else {
        i6 = InfixToPostfix(value2,expr3,player,(uint32_t *)0x0,1);
        if (i6 == 0) {
          return false;
        }
      }
    }
    expr3 = hitdef + 0x91;
    ConstExpI(expr3,-2);
    value2 = (uint8_t *)TPGetValue(tp,"guard.sparkno");
    if (value2 != (uint8_t *)0x0) {
      if (*(int *)(__ctype_tolower + (char)*value2 * 4) == 0x73) {
        i6 = InfixToPostfix(value2 + 1,expr3,player,(uint32_t *)0x0,1);
        if (i6 == 0) {
          return false;
        }
        hitdef[0x94] = 1;
      }
      else {
        i6 = InfixToPostfix(value2,expr3,player,(uint32_t *)0x0,1);
        if (i6 == 0) {
          return false;
        }
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"sparkxy");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x95,hitdef + 0x98);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"pausetime");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x32,hitdef + 0x2f);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.pausetime");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xf8,hitdef + 0x32);
L_080c5c8d:
      expcpytrig(hitdef + 0xf5,hitdef + 0x2f);
    }
    else {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0xf8,hitdef + 0xf5);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      if (value2 == (uint8_t *)0x1) goto L_080c5c8d;
    }
    i6 = ItoP_TPConstI(tp,"kill",hitdef + 0xe,player,1);
    if (i6 == 0) {
      return false;
    }
    i6 = ItoP_TPConstI(tp,"guard.kill",hitdef + 0x11,player,1);
    if (i6 == 0) {
      return false;
    }
    i6 = ItoP_TPConstI(tp,"fall.kill",hitdef + 0x14,player,1);
    if (i6 == 0) {
      return false;
    }
    i6 = ItoP_TPConstI(tp,"hitonce",hitdef + 0x17,player,(uint32_t)((hitdef[1] & 0x1c0) != 0)
                         );
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"numhits");
    i6 = InfixToPostfix(value2,hitdef + 0x35,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"damage");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x1d,hitdef + 0x20);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"getpower");
    if (value2 == (uint8_t *)0x0) {
      expr3 = hitdef + 0x23;
      expcpytrig(expr3,hitdef + 0x1d);
      ExpMulF(expr3,BITS_I2F(g[G_RULES_DEFAULT_ATTACK_LIFETOPOWERMUL]));
      expcpytrig(hitdef + 0x26,expr3);
L_080c5e6f:
      ExpDivI(hitdef + 0x26,2);
    }
    else {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x23,hitdef + 0x26);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      if (value2 == (uint8_t *)0x1) {
        expcpytrig(hitdef + 0x26,hitdef + 0x23);
        goto L_080c5e6f;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"givepower");
    if (value2 == (uint8_t *)0x0) {
      expr3 = hitdef + 0x29;
      expcpytrig(expr3,hitdef + 0x1d);
      ExpMulF(expr3,BITS_I2F(g[G_RULES_DEFAULT_GETHIT_LIFETOPOWERMUL]));
      expcpytrig(hitdef + 0x2c,expr3);
L_080c5f1a:
      ExpDivI(hitdef + 0x2c,2);
    }
    else {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x29,hitdef + 0x2c);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      if (value2 == (uint8_t *)0x1) {
        expcpytrig(hitdef + 0x2c,hitdef + 0x29);
        goto L_080c5f1a;
      }
    }
    ConstExpI(hitdef + 0x48,4);
    hitdef[0x4b] = 0;
    value2 = (uint8_t *)TPGetValue(tp,"priority");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"i:,",player,&stk_14,hitdef + 0x48);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        b1 = *(uint8_t *)(__ctype_b + 1 + stk_14[1] * 2);
        stk_14 = stk_14 + 1;
        while ((b1 & 0x20) != 0) {
          stk_14 = stk_14 + 1;
          b1 = *(uint8_t *)(__ctype_b + 1 + *stk_14 * 2);
        }
        i6 = *(int *)(__ctype_tolower + *stk_14 * 4);
        if (i6 == 0x68) {
          hitdef[0x4b] = 0;
        }
        else if (i6 < 0x69) {
          if (i6 != 100) {
            return false;
          }
          hitdef[0x4b] = 2;
        }
        else {
          if (i6 != 0x6d) {
            return false;
          }
          hitdef[0x4b] = 1;
        }
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"hitsound");
    i6 = ParseSnd(value2,hitdef + 0x38,hitdef + 0x3b,hitdef + 0x3e,player);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"guardsound");
    i6 = ParseSnd(value2,hitdef + 0x3f,hitdef + 0x42,hitdef + 0x45,player);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"ground.slidetime");
    i6 = InfixToPostfix(value2,hitdef + 0xba,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"ground.hittime");
    i6 = InfixToPostfix(value2,hitdef + 0xb7,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"ground.velocity");
    b2 = ParseVel(value2,hitdef + 0xbd,hitdef + 0xc0,player);
    if (ZEXT8(b2) == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"air.velocity");
    b2 = ParseVel(value2,hitdef + 0xce,hitdef + 0xd1,player);
    if (ZEXT8(b2) == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"air.juggle");
    i6 = InfixToPostfix(value2,hitdef + 0x1a,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    ConstExpI(hitdef + 200,0x14);
    value2 = (uint8_t *)TPGetValue(tp,"air.hittime");
    i6 = InfixToPostfix(value2,hitdef + 200,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"attack.width");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,hitdef + 0x4c,hitdef + 0x4f);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    expr3 = hitdef + 0xa1;
    expr = hitdef + 0xa4;
    ConstExpI(expr3,-0x401);
    expr2 = hitdef + 0xa7;
    ConstExpI(expr,-0x401);
    ConstExpI(expr2,-0x401);
    ConstExpI(hitdef + 0xaa,-0x401);
    ConstExpI(hitdef + 0xad,-0x401);
    ConstExpI(hitdef + 0xb0,-0x401);
    value2 = (uint8_t *)TPGetValue(tp,"snap");
    if (value2 == (uint8_t *)0x0) {
      value2 = (uint8_t *)TPGetValue(tp,"mindist");
      if (value2 != (uint8_t *)0x0) {
        value2 = SCtrlReadExpList(value2,"iii",player,&stk_14,expr3,expr,expr2);
        if (value2 == (uint8_t *)0x0) {
          return false;
        }
        if (*stk_14 != '\0') {
          return false;
        }
      }
      value2 = (uint8_t *)TPGetValue(tp,"maxdist");
      if (value2 != (uint8_t *)0x0) {
        value2 = SCtrlReadExpList(value2,"iii",player,&stk_14,hitdef + 0xaa,hitdef + 0xad,
                                  hitdef + 0xb0);
        if (value2 == (uint8_t *)0x0) {
          return false;
        }
        if (*stk_14 != '\0') {
          return false;
        }
      }
    }
    else {
      value2 = SCtrlReadExpList(value2,"iiii",player,&stk_14,expr3,expr,expr2,hitdef + 0x5b);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      hitdef[0xaa] = hitdef[0xa1];
      hitdef[0xab] = hitdef[0xa2];
      hitdef[0xac] = hitdef[0xa3];
      hitdef[0xad] = hitdef[0xa4];
      hitdef[0xae] = hitdef[0xa5];
      hitdef[0xaf] = hitdef[0xa6];
      hitdef[0xb0] = hitdef[0xa7];
      hitdef[0xb1] = hitdef[0xa8];
      hitdef[0xb2] = hitdef[0xa9];
    }
    ConstExpI(hitdef + 0x5e,1);
    value2 = (uint8_t *)TPGetValue(tp,"p1sprpriority");
    if (value2 == (uint8_t *)0x0) {
      value2 = (uint8_t *)TPGetValue(tp,"sprpriority");
    }
    i6 = InfixToPostfix(value2,hitdef + 0x5e,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    i6 = ItoP_TPConstI(tp,"p2sprpriority",hitdef + 0x61,player,0);
    if (i6 == 0) {
      return false;
    }
    ConstExpI(hitdef + 0x9b,0);
    value2 = (uint8_t *)TPGetValue(tp,"p1facing");
    i6 = InfixToPostfix(value2,hitdef + 0x9b,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"p1getp2facing");
    i6 = InfixToPostfix(value2,hitdef + 0x9e,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"p2facing");
    i6 = InfixToPostfix(value2,hitdef + 0xb3,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    ConstExpI(hitdef + 0x52,-1);
    ConstExpI(hitdef + 0x55,-1);
    ConstExpI(hitdef + 0x58,0);
    value2 = (uint8_t *)TPGetValue(tp,"p1stateno");
    i6 = InfixToPostfix(value2,hitdef + 0x52,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"p2stateno");
    if (value2 != (uint8_t *)0x0) {
      ConstExpI(hitdef + 0x58,1);
      i6 = InfixToPostfix(value2,hitdef + 0x55,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"p2getp1state");
    i6 = InfixToPostfix(value2,hitdef + 0x58,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"forcestand");
    if (value2 != (uint8_t *)0x0) {
      hitdef[0x68] = 1;
      i6 = InfixToPostfix(value2,hitdef + 0x65,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    ConstExpI(hitdef + 0x6a,0);
    ConstExpF(hitdef + 0x6e,-0x39001000);
    ConstExpF(hitdef + 0x71,-0x3f700000);
    ConstExpI(hitdef + 0x74,1);
    ConstExpI(hitdef + 0x77,4);
    value2 = (uint8_t *)TPGetValue(tp,"fall.damage");
    i6 = InfixToPostfix(value2,hitdef + 0x6a,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"fall.xvelocity");
    i6 = InfixToPostfix(value2,hitdef + 0x6e,player,(uint32_t *)0x0,2);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"fall.yvelocity");
    i6 = InfixToPostfix(value2,hitdef + 0x71,player,(uint32_t *)0x0,2);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"fall.recover");
    i6 = InfixToPostfix(value2,hitdef + 0x74,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"fall.recovertime");
    i6 = InfixToPostfix(value2,hitdef + 0x77,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    ConstExpI(hitdef + 0x10a,-0x7ff8);
    value2 = (uint8_t *)TPGetValue(tp,"yaccel");
    i6 = InfixToPostfix(value2,hitdef + 0x10a,player,(uint32_t *)0x0,2);
    if (i6 == 0) {
      return false;
    }
    ConstExpI(hitdef + 0xd7,0);
    ConstExpI(hitdef + 0xda,0x14);
    value2 = (uint8_t *)TPGetValue(tp,"down.velocity");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xdd,hitdef + 0xce);
L_080c6915:
      expcpytrig(hitdef + 0xe0,hitdef + 0xd1);
    }
    else {
      value2 = SCtrlReadExpList(value2,"ff",player,&stk_14,hitdef + 0xdd,hitdef + 0xe0);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      if (value2 == (uint8_t *)0x1) goto L_080c6915;
    }
    value2 = (uint8_t *)TPGetValue(tp,"down.bounce");
    i6 = InfixToPostfix(value2,hitdef + 0xd7,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"down.hittime");
    i6 = InfixToPostfix(value2,hitdef + 0xda,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.slidetime");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xec,hitdef + 0xba);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xec,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.hittime");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xe9,hitdef + 0xb7);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xe9,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.velocity");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xe6,hitdef + 0xbd);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xe6,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.ctrltime");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xef,hitdef + 0xec);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xef,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.dist");
    i6 = InfixToPostfix(value2,hitdef + 0xf2,player,(uint32_t *)0x0,1);
    if (i6 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"ground.cornerpush.veloff");
    if (value2 == (uint8_t *)0x0) {
      if ((*(uint8_t *)(hitdef + 1) & 4) == 0) {
        expcpytrig(hitdef + 0xc3,hitdef + 0xe6);
        ExpMulF(hitdef + 0xc3,((double)1.3));
      }
      else {
        ConstExpF(hitdef + 0xc3,0);
      }
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xc3,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"air.cornerpush.veloff");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xd4,hitdef + 0xc3);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xd4,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"down.cornerpush.veloff");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xe3,hitdef + 0xc3);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xe3,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"guard.cornerpush.veloff");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xfb,hitdef + 0xc3);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0xfb,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"airguard.cornerpush.veloff");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0x107,hitdef + 0xfb);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0x107,player,(uint32_t *)0x0,2);
      if (i6 == 0) {
        return false;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"airguard.velocity");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0xfe,hitdef + 0xce);
      ExpMulF(hitdef + 0xfe,1.5);
      expcpytrig(hitdef + 0x101,hitdef + 0xd1);
L_080c6da9:
      ExpMulF(hitdef + 0x101,0.5);
    }
    else {
      value2 = SCtrlReadExpList(value2,"ff",player,&stk_14,hitdef + 0xfe,hitdef + 0x101);
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
      if (value2 == (uint8_t *)0x1) {
        expcpytrig(hitdef + 0x101,hitdef + 0xd1);
        goto L_080c6da9;
      }
    }
    value2 = (uint8_t *)TPGetValue(tp,"airguard.ctrltime");
    if (value2 == (uint8_t *)0x0) {
      expcpytrig(hitdef + 0x104,hitdef + 0xef);
    }
    else {
      i6 = InfixToPostfix(value2,hitdef + 0x104,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    ConstExpI(hitdef + 0xcb,0);
    value2 = (uint8_t *)TPGetValue(tp,"fall");
    if (value2 != (uint8_t *)0x0) {
      i6 = InfixToPostfix(value2,hitdef + 0x8a,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
      expcpytrig(hitdef + 0xcb,hitdef + 0x8a);
    }
    value2 = (uint8_t *)TPGetValue(tp,"air.fall");
    if (value2 != (uint8_t *)0x0) {
      FreeExpression(hitdef + 0xcb);
      i6 = InfixToPostfix(value2,hitdef + 0xcb,player,(uint32_t *)0x0,1);
      if (i6 == 0) {
        return false;
      }
    }
    value = TPGetValue(tp,"guardflag");
    if (value != (char *)0x0) {
      u4 = ParseHitFlag(value);
      hitdef[0x46] = hitdef[0x46] | u4;
    }
    value = TPGetValue(tp,"hitflag");
    if (value == (char *)0x0) {
      hitdef[0x47] = hitdef[0x47] | 0x3e;
    }
    else {
      u4 = ParseHitFlag(value);
      hitdef[0x47] = hitdef[0x47] | u4;
    }
    hitdef[100] = 0;
    value = TPGetValue(tp,"animtype");
    if (value != (char *)0x0) {
      switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
      case 0x62:
        hitdef[100] = 3;
        break;
      default:
        expr3 = g + G_ERRMSG;
        n = 0x11;
        value = "Invalid animtype";
        goto L_080c72d2;
      case 100:
        hitdef[100] = 5;
        break;
      case 0x68:
        hitdef[100] = 2;
        break;
      case 0x6c:
        hitdef[100] = 0;
        break;
      case 0x6d:
        hitdef[100] = 1;
        break;
      case 0x75:
        hitdef[100] = 4;
      }
    }
    hitdef[199] = hitdef[100];
    value = TPGetValue(tp,"air.animtype");
    if (value != (char *)0x0) {
      switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
      case 0x62:
        hitdef[199] = 3;
        break;
      default:
        expr3 = g + G_ERRMSG;
        n = 0x15;
        value = "Invalid air.animtype";
        goto L_080c72d2;
      case 100:
        hitdef[199] = 5;
        break;
      case 0x68:
        hitdef[199] = 2;
        break;
      case 0x6c:
        hitdef[199] = 0;
        break;
      case 0x6d:
        hitdef[199] = 1;
        break;
      case 0x75:
        hitdef[199] = 4;
      }
    }
    if (hitdef[199] == 4) {
      hitdef[0x6d] = 4;
    }
    else {
      hitdef[0x6d] = (uint32_t)(hitdef[199] == 5) * 2 + 3;
    }
    value = TPGetValue(tp,"fall.animtype");
    if (value != (char *)0x0) {
      switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
      case 0x62:
        hitdef[0x6d] = 3;
        break;
      default:
        expr3 = g + G_ERRMSG;
        n = 0x16;
        value = "Invalid fall.animtype";
        goto L_080c72d2;
      case 100:
        hitdef[0x6d] = 5;
        break;
      case 0x68:
        hitdef[0x6d] = 2;
        break;
      case 0x6c:
        hitdef[0x6d] = 0;
        break;
      case 0x6d:
        hitdef[0x6d] = 1;
        break;
      case 0x75:
        hitdef[0x6d] = 4;
      }
    }
    hitdef[0xb6] = 1;
    value = TPGetValue(tp,"ground.type");
    if (value != (char *)0x0) {
      i6 = *(int *)(__ctype_tolower + *value * 4);
      if (i6 == 0x6c) {
        hitdef[0xb6] = 2;
      }
      else if (i6 < 0x6d) {
        if (i6 != 0x68) {
L_080c7210:
          expr3 = g + G_ERRMSG;
          n = 0x14;
          value = "Invalid ground.type";
          goto L_080c72d2;
        }
        hitdef[0xb6] = 1;
      }
      else if (i6 == 0x6e) {
        hitdef[0xb6] = 0;
      }
      else {
        if (i6 != 0x74) goto L_080c7210;
        hitdef[0xb6] = 3;
      }
    }
    hitdef[0xc6] = hitdef[0xb6];
    value = TPGetValue(tp,"air.type");
    if (value != (char *)0x0) {
      i6 = *(int *)(__ctype_tolower + *value * 4);
      if (i6 == 0x6c) {
        hitdef[0xc6] = 2;
      }
      else if (i6 < 0x6d) {
        if (i6 != 0x68) {
L_080c72c0:
          expr3 = g + G_ERRMSG;
          n = 0x11;
          value = "Invalid air.type";
          goto L_080c72d2;
        }
        hitdef[0xc6] = 1;
      }
      else if (i6 == 0x6e) {
        hitdef[0xc6] = 0;
      }
      else {
        if (i6 != 0x74) goto L_080c72c0;
        hitdef[0xc6] = 3;
      }
    }
    b2 = SCtrlParsePalFX(tp,player,(int)(hitdef + 0x10d),1);
    if (ZEXT8(b2) != 0) {
      hitdef[0x10d] = 0;
      i6 = SCtrlParseEnvShake(tp,player,hitdef + 0x135,"envshake.");
      if (i6 != 0) {
        i6 = SCtrlParseEnvShake(tp,player,hitdef + 0x7a,"fall.envshake.");
        return i6 != 0;
      }
    }
  }
  else {
    i6 = *(int *)(__ctype_tolower + *value * 4);
    if (i6 == 0x65) {
      *hitdef = 2;
      goto L_080c5957;
    }
    if (i6 < 0x66) {
      if (i6 == 0x62) {
        *hitdef = 3;
        goto L_080c5957;
      }
    }
    else if (i6 == 0x66) {
      *hitdef = 1;
      goto L_080c5957;
    }
    expr3 = g + G_ERRMSG;
    n = 0x19;
    value = "Invalid affectteam value";
L_080c72d2:
    memcpy(expr3,value,n);
  }
  return false;
}
#undef stk_14

/* SCtrlInitHitDef @ 0x080c7360, 3018 bytes
 *
 * Evaluates a HitDef block for a player into its active hit definition. It
 * checks the values and applies defaults, and evaluates the embedded PalFX
 * and EnvShake. Warnings: "assigned negative hitID", "specified negative
 * chainID", "specified negative nochainID", ...
 *
 * Parameters:
 *   hitdef_def   uint32_t *
 *   hitdef       int
 *   player       int *
 *
 * Calls: EvalExpressionI, Warn, EvalExpressionF, SCtrlInitPalFX,
 *        SCtrlInitEnvShake
 * Called by: PlayerSCtrlApplyElem, SCtrlInitProjectile
 * Messages:
 *   "assigned negative hitID"
 *   "specified negative chainID"
 *   "specified negative nochainID"
 *   "specified negative nochainID2"
 *   "illegal juggle points"
 *   "specified negative p2shaketime"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 29 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t SCtrlInitHitDef(uint32_t *hitdef_def,int hitdef,int *player)

{
  int value;
  uint32_t value2;
  float80 value3;
  
  *(uint32_t *)(hitdef + 8) = *hitdef_def;
  *(uint32_t *)(hitdef + 0xc) = hitdef_def[1];
  value = EvalExpressionI((int)player,hitdef_def + 2,1);
  *(int *)(hitdef + 0x14) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x14) = 0;
    Warn((int)player,(int)&str_assigned_negative_hitid_bcca);
  }
  value = EvalExpressionI((int)player,hitdef_def + 5,1);
  *(int *)(hitdef + 0x18) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x18) = 0xffffffff;
    Warn((int)player,(int)&str_specified_negative_chainid_bce2);
  }
  value = EvalExpressionI((int)player,hitdef_def + 8,1);
  *(int *)(hitdef + 0x1c) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x1c) = 0xffffffff;
    Warn((int)player,(int)&str_specified_negative_nochainid_bcfd);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xb,1);
  *(int *)(hitdef + 0x20) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x20) = 0xffffffff;
    Warn((int)player,(int)&str_specified_negative_nochainid_bd1a);
  }
  value = *(int *)(hitdef + 0x18);
  if (((value == *(int *)(hitdef + 0x1c)) || (value == *(int *)(hitdef + 0x20))) && (value != -1))
  {
    *(uint32_t *)(hitdef + 0x20) = 0xffffffff;
    *(uint32_t *)(hitdef + 0x1c) = 0xffffffff;
    *(uint32_t *)(hitdef + 0x18) = 0xffffffff;
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xe,1);
  *(uint32_t *)(hitdef + 0x24) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x11,1);
  *(uint32_t *)(hitdef + 0x28) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x14,1);
  *(uint32_t *)(hitdef + 0x2c) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x17,1);
  *(uint32_t *)(hitdef + 0x30) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x1a,1);
  *(int *)(hitdef + 0x34) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x34) = 0xffffffff;
    Warn((int)player,(int)&str_illegal_juggle_points_bd38);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x1d,1);
  *(int *)(hitdef + 0x38) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x20,1);
  *(int *)(hitdef + 0x3c) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x23,0);
  *(int *)(hitdef + 0x40) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x26,0);
  *(int *)(hitdef + 0x44) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x29,0);
  *(int *)(hitdef + 0x48) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x2c,0);
  *(int *)(hitdef + 0x4c) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x2f,1);
  *(int *)(hitdef + 0x50) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x50) = 0;
    Warn((int)player,(int)&str_specified_negative_p2shaketi_c260);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x32,1);
  *(int *)(hitdef + 0x54) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x54) = 0;
    Warn((int)player,(int)&str_specified_negative_pausetime_bd4e);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x35,1);
  *(int *)(hitdef + 0x58) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x38,1);
  *(int *)(hitdef + 0x5c) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x5c) = 0xffffffff;
    Warn((int)player,(int)&str_specified_illegal_sound_grou_bd6b);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x3b,1);
  *(int *)(hitdef + 0x60) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x60) = 0xffffffff;
    Warn((int)player,(int)&str_specified_illegal_sound_no_bd89);
  }
  *(uint32_t *)(hitdef + 100) = hitdef_def[0x3e];
  value = EvalExpressionI((int)player,hitdef_def + 0x3f,1);
  *(int *)(hitdef + 0x68) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x68) = 0xffffffff;
    Warn((int)player,(int)&str_specified_illegal_gsound_gro_c280);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x42,1);
  *(int *)(hitdef + 0x6c) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x6c) = 0xffffffff;
    Warn((int)player,(int)&str_specified_illegal_gsound_no_bda4);
  }
  *(uint32_t *)(hitdef + 0x70) = hitdef_def[0x45];
  *(uint32_t *)(hitdef + 0x74) = hitdef_def[0x46];
  *(uint32_t *)(hitdef + 0x78) = hitdef_def[0x47];
  value = EvalExpressionI((int)player,hitdef_def + 0x48,1);
  *(int *)(hitdef + 0x7c) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x7c) = 0;
    Warn((int)player,(int)&str_specified_negative_hit_prior_c2a0);
  }
  *(uint32_t *)(hitdef + 0x80) = hitdef_def[0x4b];
  value = EvalExpressionI((int)player,hitdef_def + 0x4c,1);
  *(int *)(hitdef + 0x84) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x4f,1);
  *(int *)(hitdef + 0x88) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x52,1);
  *(int *)(hitdef + 0x8c) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x8c) = 0xffffffff;
    Warn((int)player,(int)&str_specified_negative_p1stateno_bdc0);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x55,1);
  *(int *)(hitdef + 0x90) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x90) = 0xffffffff;
    Warn((int)player,(int)&str_specified_negative_p2stateno_bddd);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x58,1);
  *(uint32_t *)(hitdef + 0x94) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x5b,1);
  *(int *)(hitdef + 0x98) = value;
  if (value < -1) {
    *(uint32_t *)(hitdef + 0x98) = 1;
    Warn((int)player,(int)&str_specified_illegal_p2bindtime_bdfa);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x5e,1);
  *(int *)(hitdef + 0x9c) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x61,1);
  *(int *)(hitdef + 0xa0) = value;
  *(uint32_t *)(hitdef + 0xa4) = hitdef_def[100];
  value = EvalExpressionI((int)player,hitdef_def + 0x65,1);
  *(uint32_t *)(hitdef + 0xa8) = (uint32_t)(value != 0);
  *(uint32_t *)(hitdef + 0xac) = hitdef_def[0x69];
  value = EvalExpressionI((int)player,hitdef_def + 0x8a,1);
  if (value != 0) {
    *(uint32_t *)(hitdef + 0x78) = *(uint32_t *)(hitdef + 0x78) | 1;
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x6a,1);
  *(int *)(hitdef + 0xb0) = value;
  *(uint32_t *)(hitdef + 0xb4) = hitdef_def[0x6d];
  value3 = EvalExpressionF(player,hitdef_def + 0x6e);
  *(float *)(hitdef + 0xb8) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0x71);
  *(float *)(hitdef + 0xbc) = value3;
  value = EvalExpressionI((int)player,hitdef_def + 0x74,1);
  *(uint32_t *)(hitdef + 0xc0) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0x77,1);
  *(int *)(hitdef + 0xc4) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0xc4) = 4;
    Warn((int)player,(int)&str_specified_negative_recoverti_c2c0);
  }
  *(uint32_t *)(hitdef + 0xe4) = hitdef_def[0x90];
  value = EvalExpressionI((int)player,hitdef_def + 0x8d,1);
  *(int *)(hitdef + 0xe0) = value;
  if (value < -2) {
    *(uint32_t *)(hitdef + 0xe0) = 0xfffffffe;
    Warn((int)player,(int)&str_illegal_spark_no_be17);
  }
  *(uint32_t *)(hitdef + 0xec) = hitdef_def[0x94];
  value = EvalExpressionI((int)player,hitdef_def + 0x91,1);
  *(int *)(hitdef + 0xe8) = value;
  if (value < -2) {
    *(uint32_t *)(hitdef + 0xe8) = 0xfffffffe;
    Warn((int)player,(int)&str_illegal_gspark_no_be28);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0x95,1);
  *(int *)(hitdef + 0xf0) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0x98,1);
  *(int *)(hitdef + 0xf4) = value;
  value2 = EvalExpressionI((int)player,hitdef_def + 0x9b,1);
  *(uint32_t *)(hitdef + 0xf8) = value2 >> 0x1f;
  value = EvalExpressionI((int)player,hitdef_def + 0x9e,1);
  if (value < 0) {
    value = -1;
  }
  else if (0 < value) {
    value = 1;
  }
  if (value != 0) {
    *(uint32_t *)(hitdef + 0xf8) = 0;
  }
  *(int *)(hitdef + 0xfc) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xa1,1);
  *(int *)(hitdef + 0x100) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xa4,1);
  *(int *)(hitdef + 0x104) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xaa,1);
  *(int *)(hitdef + 0x10c) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xad,1);
  *(int *)(hitdef + 0x110) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xb3,1);
  *(int *)(hitdef + 0x118) = value;
  if (2 < value + 1U) {
    *(uint32_t *)(hitdef + 0x118) = 0;
    Warn((int)player,(int)&str_illegal_p2facing_parameter_be3a);
  }
  *(uint32_t *)(hitdef + 0x11c) = hitdef_def[0xb6];
  value = EvalExpressionI((int)player,hitdef_def + 0xb7,1);
  *(int *)(hitdef + 0x120) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x120) = 0;
    Warn((int)player,(int)&str_negative_ground_p2hittime_be55);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xba,1);
  *(int *)(hitdef + 0x124) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x124) = 0;
    Warn((int)player,(int)&str_negative_ground_p2slidetime_be6f);
  }
  value3 = EvalExpressionF(player,hitdef_def + 0xbd);
  *(float *)(hitdef + 0x128) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xc0);
  *(float *)(hitdef + 300) = value3;
  if ((value3 != 0.0) && (hitdef_def[0x68] == 0)) {
    *(uint32_t *)(hitdef + 0xa8) = 1;
  }
  value3 = EvalExpressionF(player,hitdef_def + 0xc3);
  *(uint32_t *)(hitdef + 0x134) = hitdef_def[0xc6];
  *(uint32_t *)(hitdef + 0x138) = hitdef_def[199];
  *(float *)(hitdef + 0x130) = value3;
  value = EvalExpressionI((int)player,hitdef_def + 200,1);
  *(int *)(hitdef + 0x13c) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x13c) = 0;
    Warn((int)player,(int)&str_negative_air_p2hittime_be8b);
  }
  value3 = EvalExpressionF(player,hitdef_def + 0xcb);
  *(int *)(hitdef + 0x140) = (int)X87_FIST32(value3);
  value3 = EvalExpressionF(player,hitdef_def + 0xce);
  *(float *)(hitdef + 0x144) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xd1);
  *(float *)(hitdef + 0x148) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xd4);
  *(float *)(hitdef + 0x14c) = value3;
  value = EvalExpressionI((int)player,hitdef_def + 0xd7,1);
  *(uint32_t *)(hitdef + 0x150) = (uint32_t)(value != 0);
  value = EvalExpressionI((int)player,hitdef_def + 0xda,1);
  *(int *)(hitdef + 0x154) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x154) = 0;
    Warn((int)player,(int)&str_negative_down_p2hittime_bea2);
  }
  value3 = EvalExpressionF(player,hitdef_def + 0xdd);
  *(float *)(hitdef + 0x158) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xe0);
  *(float *)(hitdef + 0x15c) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xe3);
  *(float *)(hitdef + 0x160) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xe6);
  *(float *)(hitdef + 0x164) = value3;
  value = EvalExpressionI((int)player,hitdef_def + 0xe9,1);
  *(int *)(hitdef + 0x168) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x168) = 0;
    Warn((int)player,(int)&str_negative_guard_p2hittime_beba);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xec,1);
  *(int *)(hitdef + 0x16c) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x16c) = 0;
    Warn((int)player,(int)&str_negative_guard_p2slidetime_bed3);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xef,1);
  *(int *)(hitdef + 0x170) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x170) = 0;
    Warn((int)player,(int)&str_negative_guard_p2ctrltime_beee);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xf2,1);
  *(int *)(hitdef + 0x174) = value;
  value = EvalExpressionI((int)player,hitdef_def + 0xf5,1);
  *(int *)(hitdef + 0x178) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x178) = 0;
    Warn((int)player,(int)&str_negative_guard_p2shaketime_bf08);
  }
  value = EvalExpressionI((int)player,hitdef_def + 0xf8,1);
  *(int *)(hitdef + 0x17c) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x17c) = 0;
    Warn((int)player,(int)&str_negative_guard_p1pausetime_bf23);
  }
  value3 = EvalExpressionF(player,hitdef_def + 0xfb);
  *(float *)(hitdef + 0x180) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0xfe);
  *(float *)(hitdef + 0x184) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0x101);
  *(float *)(hitdef + 0x188) = value3;
  value = EvalExpressionI((int)player,hitdef_def + 0x104,1);
  *(int *)(hitdef + 0x18c) = value;
  if (value < 0) {
    *(uint32_t *)(hitdef + 0x18c) = 0;
    Warn((int)player,(int)&str_negative_airguard_p2ctrltime_bf3e);
  }
  value3 = EvalExpressionF(player,hitdef_def + 0x107);
  *(float *)(hitdef + 400) = value3;
  value3 = EvalExpressionF(player,hitdef_def + 0x10a);
  *(float *)(hitdef + 0x194) = value3;
  SCtrlInitPalFX(hitdef_def + 0x10d,(uint32_t *)(hitdef + 0x198),(int)player);
  SCtrlInitEnvShake(hitdef_def + 0x135,(uint32_t *)(hitdef + 0x1d4),player);
  SCtrlInitEnvShake(hitdef_def + 0x7a,(uint32_t *)(hitdef + 200),player);
  return 1;
}

/* HitDefEFree @ 0x080c7f30, 1129 bytes
 *
 * Frees a HitDef parameter block, including its PalFX and EnvShake blocks.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: FreeExpression, PalFXEFree, EnvShakeEFree
 * Called by: ProjMakeInfoFree, SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void HitDefEFree(int arg1)

{
  FreeExpression((int *)(arg1 + 8));
  FreeExpression((int *)(arg1 + 0x14));
  FreeExpression((int *)(arg1 + 0x20));
  FreeExpression((int *)(arg1 + 0x2c));
  FreeExpression((int *)(arg1 + 0x38));
  FreeExpression((int *)(arg1 + 0x44));
  FreeExpression((int *)(arg1 + 0x50));
  FreeExpression((int *)(arg1 + 0x5c));
  FreeExpression((int *)(arg1 + 0x68));
  FreeExpression((int *)(arg1 + 0x74));
  FreeExpression((int *)(arg1 + 0x80));
  FreeExpression((int *)(arg1 + 0x8c));
  FreeExpression((int *)(arg1 + 0x98));
  FreeExpression((int *)(arg1 + 0xa4));
  FreeExpression((int *)(arg1 + 0xb0));
  FreeExpression((int *)(arg1 + 0xbc));
  FreeExpression((int *)(arg1 + 200));
  FreeExpression((int *)(arg1 + 0xd4));
  FreeExpression((int *)(arg1 + 0xe0));
  FreeExpression((int *)(arg1 + 0xec));
  FreeExpression((int *)(arg1 + 0xfc));
  FreeExpression((int *)(arg1 + 0x108));
  FreeExpression((int *)(arg1 + 0x120));
  FreeExpression((int *)(arg1 + 0x130));
  FreeExpression((int *)(arg1 + 0x13c));
  FreeExpression((int *)(arg1 + 0x148));
  FreeExpression((int *)(arg1 + 0x154));
  FreeExpression((int *)(arg1 + 0x160));
  FreeExpression((int *)(arg1 + 0x16c));
  FreeExpression((int *)(arg1 + 0x178));
  FreeExpression((int *)(arg1 + 0x184));
  FreeExpression((int *)(arg1 + 0x194));
  FreeExpression((int *)(arg1 + 0x1a8));
  FreeExpression((int *)(arg1 + 0x1b8));
  FreeExpression((int *)(arg1 + 0x1c4));
  FreeExpression((int *)(arg1 + 0x1d0));
  FreeExpression((int *)(arg1 + 0x1dc));
  FreeExpression((int *)(arg1 + 0x228));
  FreeExpression((int *)(arg1 + 0x234));
  FreeExpression((int *)(arg1 + 0x244));
  FreeExpression((int *)(arg1 + 0x254));
  FreeExpression((int *)(arg1 + 0x260));
  FreeExpression((int *)(arg1 + 0x26c));
  FreeExpression((int *)(arg1 + 0x278));
  FreeExpression((int *)(arg1 + 0x284));
  FreeExpression((int *)(arg1 + 0x290));
  FreeExpression((int *)(arg1 + 0x29c));
  FreeExpression((int *)(arg1 + 0x2a8));
  FreeExpression((int *)(arg1 + 0x2b4));
  FreeExpression((int *)(arg1 + 0x2c0));
  FreeExpression((int *)(arg1 + 0x2cc));
  FreeExpression((int *)(arg1 + 0x2dc));
  FreeExpression((int *)(arg1 + 0x2e8));
  FreeExpression((int *)(arg1 + 0x2f4));
  FreeExpression((int *)(arg1 + 0x300));
  FreeExpression((int *)(arg1 + 0x30c));
  FreeExpression((int *)(arg1 + 800));
  FreeExpression((int *)(arg1 + 0x32c));
  FreeExpression((int *)(arg1 + 0x338));
  FreeExpression((int *)(arg1 + 0x344));
  FreeExpression((int *)(arg1 + 0x350));
  FreeExpression((int *)(arg1 + 0x35c));
  FreeExpression((int *)(arg1 + 0x368));
  FreeExpression((int *)(arg1 + 0x374));
  FreeExpression((int *)(arg1 + 0x380));
  FreeExpression((int *)(arg1 + 0x38c));
  FreeExpression((int *)(arg1 + 0x398));
  FreeExpression((int *)(arg1 + 0x3a4));
  FreeExpression((int *)(arg1 + 0x3b0));
  FreeExpression((int *)(arg1 + 0x3bc));
  FreeExpression((int *)(arg1 + 0x3ec));
  FreeExpression((int *)(arg1 + 0x3c8));
  FreeExpression((int *)(arg1 + 0x3d4));
  FreeExpression((int *)(arg1 + 0x3e0));
  FreeExpression((int *)(arg1 + 0x3f8));
  FreeExpression((int *)(arg1 + 0x404));
  FreeExpression((int *)(arg1 + 0x410));
  FreeExpression((int *)(arg1 + 0x41c));
  FreeExpression((int *)(arg1 + 0x428));
  PalFXEFree(arg1 + 0x434);
  EnvShakeEFree((int *)(arg1 + 0x4d4));
  EnvShakeEFree((int *)(arg1 + 0x1e8));
  return;
}

/* SCtrlParseProjectile @ 0x080c83a0, 2029 bytes
 *
 * Compiles Projectile parameters: projid, projanim, projhitanim,
 * projremanim, projcancelanim, projscale, projremove, projremovetime,
 * velocity, remvelocity, accel, velmul, projhits, projmisstime,
 * projpriority, projsprpriority, projedgebound, projstagebound,
 * projheightbound, offset, postype, projshadow, supermovetime,
 * pausemovetime, and "afterimage." parameters. The HitDef part is compiled
 * by SCtrlParseHitDef.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *
 * Text keys read: "projid", "projanim", "offset", "postype",
 *                 "projhitanim", "projremanim", "projcancelanim",
 *                 "projsprpriority", "projedgebound", "projstagebound",
 *                 "projheightbound", "velocity", "remvelocity", "velmul",
 *                 "accel", "projscale", "projhits", "projpriority",
 *                 "projremove", "projremovetime", "projmisstime",
 *                 "projshadow", "pausemovetime", "supermovetime", ...
 * Globals read: errmsg
 * Calls: ConstExpF, ConstExpI, TPGetValue, InfixToPostfix,
 *        SCtrlReadExpList, ParsePosType, expcpytrig, ItoP_TPConstI,
 *        SCtrlParseHitDef, ecalloc, SCtrlParseAftImgParams
 * C library: sprintf, strcat
 * Called by: SCtrlParseElemType
 * Messages:
 *   "Illegal postype: %s"
 *   "\nError parsing Hitdef of projectile"
 *   "\nError parsing Afterimage of projectile"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseProjectile(int tp,int player,int *expr)

{
  bool b1;
  uint8_t *value;
  int mem;
  char *value2;
  uint32_t stale_var;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(char **)(frame + 0xc))
  
  expr[9] = 0;
  ConstExpF(expr + 0x3d,0);
  ConstExpF(expr + 0x40,0);
  ConstExpI(expr + 0xd,-1);
  ConstExpI(expr + 0x1f,1);
  ConstExpI(expr + 0x22,1);
  ConstExpI(expr + 0x28,-1);
  ConstExpI(expr + 0x2e,-1);
  ConstExpF(expr + 0x43,0x3f800000);
  ConstExpF(expr + 0x46,0x3f800000);
  ConstExpF(expr + 0x4f,0);
  ConstExpF(expr + 0x52,0);
  ConstExpF(expr + 0x55,0x3f800000);
  ConstExpF(expr + 0x58,0x3f800000);
  ConstExpI(expr + 10,1);
  ConstExpI(expr + 0x13,0x28);
  ConstExpI(expr + 0x16,0x28);
  ConstExpI(expr + 0x19,-0xf0);
  ConstExpI(expr + 0x1c,1);
  ConstExpI(expr + 0x3a,3);
  value = (uint8_t *)TPGetValue(tp,"projid");
  mem = InfixToPostfix(value,expr,player,(uint32_t *)0x0,1);
  if (mem != 0) {
    value = (uint8_t *)TPGetValue(tp,"projanim");
    mem = InfixToPostfix(value,expr + 0x25,player,(uint32_t *)0x0,1);
    if (mem != 0) {
      value = (uint8_t *)TPGetValue(tp,"offset");
      SCtrlReadExpList(value,"ii",player,&stk_14,expr + 3,expr + 6);
      if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
        value2 = TPGetValue(tp,"postype");
        if (value2 != (char *)0x0) {
          mem = ParsePosType(value2);
          expr[9] = mem;
          if (mem == -1) {
            sprintf((char *)(g + G_ERRMSG),"Illegal postype: %s",value2,&stk_14);
            return 0;
          }
        }
        value = (uint8_t *)TPGetValue(tp,"projhitanim");
        mem = InfixToPostfix(value,expr + 0x28,player,(uint32_t *)0x0,1);
        if (mem != 0) {
          value = (uint8_t *)TPGetValue(tp,"projremanim");
          if (value == (uint8_t *)0x0) {
            expcpytrig(expr + 0x2b,expr + 0x28);
          }
          else {
            mem = InfixToPostfix(value,expr + 0x2b,player,(uint32_t *)0x0,1);
            if (mem == 0) {
              return 0;
            }
          }
          value = (uint8_t *)TPGetValue(tp,"projcancelanim");
          if (value == (uint8_t *)0x0) {
            expcpytrig(expr + 0x2e,expr + 0x2b);
          }
          else {
            mem = InfixToPostfix(value,expr + 0x2e,player,(uint32_t *)0x0,1);
            if (mem == 0) {
              return 0;
            }
          }
          value = (uint8_t *)TPGetValue(tp,"projsprpriority");
          mem = InfixToPostfix(value,expr + 0x3a,player,(uint32_t *)0x0,1);
          if (mem != 0) {
            value = (uint8_t *)TPGetValue(tp,"projedgebound");
            mem = InfixToPostfix(value,expr + 0x13,player,(uint32_t *)0x0,1);
            if (mem != 0) {
              value = (uint8_t *)TPGetValue(tp,"projstagebound");
              mem = InfixToPostfix(value,expr + 0x16,player,(uint32_t *)0x0,1);
              if (mem != 0) {
                value = (uint8_t *)TPGetValue(tp,"projheightbound");
                SCtrlReadExpList(value,"ii",player,&stk_14,expr + 0x19,expr + 0x1c);
                if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                  value = (uint8_t *)TPGetValue(tp,"velocity");
                  SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x3d,expr + 0x40);
                  if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                    value = (uint8_t *)TPGetValue(tp,"remvelocity");
                    SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x49,expr + 0x4c);
                    if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                      value = (uint8_t *)TPGetValue(tp,"velmul");
                      SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x43,expr + 0x46);
                      if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                        value = (uint8_t *)TPGetValue(tp,"accel");
                        SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x4f,expr + 0x52
                                        );
                        if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                          value = (uint8_t *)TPGetValue(tp,"projscale");
                          SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x55,
                                           expr + 0x58);
                          if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                            value = (uint8_t *)TPGetValue(tp,"projhits");
                            SCtrlReadExpList(value,"i",player,&stk_14,expr + 0x1f);
                            if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                              value = (uint8_t *)TPGetValue(tp,"projpriority");
                              SCtrlReadExpList(value,"i",player,&stk_14,expr + 0x22);
                              if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                                value = (uint8_t *)TPGetValue(tp,"projremove");
                                SCtrlReadExpList(value,"i",player,&stk_14,expr + 10);
                                if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                                  value = (uint8_t *)TPGetValue(tp,"projremovetime");
                                  SCtrlReadExpList(value,"i",player,&stk_14,expr + 0xd);
                                  if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                                    value = (uint8_t *)TPGetValue(tp,"projmisstime");
                                    SCtrlReadExpList(value,"i",player,&stk_14,expr + 0x10);
                                    if ((value == (uint8_t *)0x0) || (*stk_14 == '\0')) {
                                      value = (uint8_t *)TPGetValue(tp,"projshadow");
                                      SCtrlReadExpList(value,"iii",player,&stk_14,expr + 0x31
                                                       ,expr + 0x34,expr + 0x37);
                                      mem = ItoP_TPConstI(tp,"pausemovetime",expr + 0x5e,
                                                            player,0);
                                      if ((mem != 0) &&
                                         (mem = ItoP_TPConstI(tp,"supermovetime",
                                                                expr + 0x5b,player,0),
                                         mem != 0)) {
                                        b1 = SCtrlParseHitDef(tp,player,expr + 0x61);
                                        if (ZEXT8(b1) == 0) {
                                          value2 = "\nError parsing Hitdef of projectile";
                                        }
                                        else {
                                          value2 = TPGetValue(tp,"afterimage.time");
                                          if (value2 == (char *)0x0) {
                                            return 1;
                                          }
                                          mem = ecalloc(1,0x118);
                                          expr[0x1a6] = mem;
                                          if (mem == 0) {
                                            return 0;
                                          }
                                          mem = SCtrlParseAftImgParams
                                                            (tp,player,(int *)expr[0x1a6],
                                                             "afterimage.");
                                          if (mem != 0) {
                                            return 1;
                                          }
                                          value2 = "\nError parsing Afterimage of projectile";
                                        }
                                        strcat((char *)(g + G_ERRMSG),value2);
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
  return 0;
}
#undef stk_14

/* SCtrlInitProjectile @ 0x080c8b90, 2110 bytes
 *
 * Evaluates a Projectile block for a player and launches the projectile:
 * computes its start position from offset and postype, sets its hit
 * definition (SCtrlInitHitDef), adds it to the player's projectile array
 * (ProjArrayAdd) and starts its afterimage if requested. Warnings: "negative
 * projectile ID", "illegal projremovetime", ...
 *
 * Parameters:
 *   expr         int
 *   player       int *
 *   arg3         int
 *   arg4         int *
 *
 * Player fields read: teamside, facing, pos_x, pos_y, pos_z
 * Globals read: camera_boundleft, camera_boundright
 * Calls: EvalExpressionI, Warn, EvalExpressionF, SCtrlInitHitDef,
 *        ProjArrayAdd, RequestNewAftImg, SCtrlInitAftImgParams
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "negative projectile ID"
 *   "illegal projremovetime"
 *   "illegal shadowcolor"
 *   "negative projectile miss time"
 *   "negative # of projectile hits"
 *   "illegal projhit actionid"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 9 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x310 bytes,
 *       40 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int SCtrlInitProjectile(int expr,int *player,int arg3,int *arg4)

{
  int value;
  int value2;
  int value3;
  int *pi4;
  float80 value4;
  unsigned char frame[0x310] __attribute__((aligned(16)));
#define stk_30c (*(int *)(frame + 0x4))
#define stk_308 (*(int *)(frame + 0x8))
#define stk_2fc (*(int (*)[4])(frame + 0x14))
#define value5 (*(int *)(frame + 0x24))
#define value6 (*(int *)(frame + 0x28))
#define value7 (*(int *)(frame + 0x2c))
#define value8 (*(int *)(frame + 0x30))
#define stk_2dc (*(uint32_t *)(frame + 0x34))
#define stk_2d8 (*(uint32_t *)(frame + 0x38))
#define stk_2d4 (*(uint32_t *)(frame + 0x3c))
#define value9 (*(int *)(frame + 0x44))
#define stk_2c8 (*(int *)(frame + 0x48))
#define stk_2c4 (*(uint32_t *)(frame + 0x4c))
#define value10 (*(int *)(frame + 0x50))
#define stk_2bc (*(uint32_t *)(frame + 0x54))
#define stk_2b8 (*(float *)(frame + 0x58))
#define stk_2b4 (*(float *)(frame + 0x5c))
#define stk_2b0 (*(int *)(frame + 0x60))
#define value11 (*(float *)(frame + 0x68))
#define value12 (*(float *)(frame + 0x6c))
#define value13 (*(float *)(frame + 0x78))
#define value14 (*(float *)(frame + 0x7c))
#define value15 (*(float *)(frame + 0x80))
#define value16 (*(float *)(frame + 0x84))
#define value17 (*(float *)(frame + 0x88))
#define value18 (*(float *)(frame + 0x8c))
#define value19 (*(float *)(frame + 0x90))
#define value20 (*(float *)(frame + 0x94))
#define value21 (*(int *)(frame + 0x98))
#define stk_274 (*(int *)(frame + 0x9c))
#define value22 (*(int *)(frame + 0xa0))
#define stk_26c (*(int *)(frame + 0xa4))
#define value23 (*(int *)(frame + 0xa8))
#define hitdef (*(uint32_t (*)[3])(frame + 0xac))
#define stk_258 (*(int *)(frame + 0xb8))
#define stk_254 (*(int *)(frame + 0xbc))
#define stk_f0 (*(int *)(frame + 0x220))
#define value24 (*(int *)(frame + 0x2d0))
#define stk_2c (*(int *)(frame + 0x2e4))
#define stk_28 (*(int *)(frame + 0x2e8))
  
  pi4 = stk_2fc;
  for (value3 = 0xb7; value3 != 0; value3 = value3 + -1) {
    *pi4 = 0;
    pi4 = pi4 + 1;
  }
  stk_2fc[0] = EvalExpressionI((int)player,expr,1);
  if (stk_2fc[0] < 0) {
    stk_2fc[0] = 0;
    Warn((int)player,(int)&str_negative_projectile_id_c02a);
  }
  stk_2fc[2] = player[PL_TEAMSIDE];
  value3 = EvalExpressionI((int)player,expr + 0x28,1);
  stk_2c4 = (uint32_t)(value3 != 0);
  value10 = EvalExpressionI((int)player,expr + 0x34,1);
  if (value10 < -1) {
    value10 = 1;
    Warn((int)player,(int)&str_illegal_projremovetime_c041);
  }
  value3 = EvalExpressionI((int)player,expr + 0xc4,1);
  value = EvalExpressionI((int)player,expr + 0xd0,1);
  value2 = EvalExpressionI((int)player,expr + 0xdc,1);
  if (((((value3 < -1) || (value < -1)) || (value2 < -1)) || ((0xff < value3 || (0xff < value)))) ||
     (0xff < value2)) {
    stk_2bc = 0xffffffff;
    Warn((int)player,(int)&str_illegal_shadowcolor_c058);
  }
  else if (((value3 == -1) || (value == -1)) || (value2 == -1)) {
    stk_2bc = 0xffffffff;
  }
  else {
    stk_2bc = (value3 >> 3) << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                (value >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                (value2 >> 3) << ((uint8_t)_rgb_b_shift_16 & 0x1f);
  }
  value9 = EvalExpressionI((int)player,expr + 0x40,1);
  if (value9 < 0) {
    value9 = 2;
    Warn((int)player,(int)&str_negative_projectile_miss_tim_c06c);
  }
  value8 = EvalExpressionI((int)player,expr + 0x7c,1);
  if (value8 < 0) {
    value8 = 1;
    Warn((int)player,(int)&str_negative_of_projectile_hits_c08a);
  }
  stk_2fc[3] = EvalExpressionI((int)player,expr + 0x88,1);
  value5 = EvalExpressionI((int)player,expr + 0xa0,1);
  if (value5 < -1) {
    value5 = -1;
    Warn((int)player,(int)&str_illegal_projhit_actionid_c0a8);
  }
  value6 = EvalExpressionI((int)player,expr + 0xac,1);
  if (value6 < -1) {
    Warn((int)player,(int)&str_illegal_projremove_actionid_c0c1);
  }
  value7 = EvalExpressionI((int)player,expr + 0xb8,1);
  if (value7 < -1) {
    Warn((int)player,(int)&str_illegal_projcancel_actionid_c0dd);
  }
  value13 = EvalExpressionF(player,(int *)(expr + 0xf4));
  value14 = EvalExpressionF(player,(int *)(expr + 0x100));
  value17 = EvalExpressionF(player,(int *)(expr + 0x10c));
  value18 = EvalExpressionF(player,(int *)(expr + 0x118));
  value15 = EvalExpressionF(player,(int *)(expr + 0x124));
  value16 = EvalExpressionF(player,(int *)(expr + 0x130));
  value19 = EvalExpressionF(player,(int *)(expr + 0x13c));
  value20 = EvalExpressionF(player,(int *)(expr + 0x148));
  value11 = EvalExpressionF(player,(int *)(expr + 0x154));
  value12 = EvalExpressionF(player,(int *)(expr + 0x160));
  if (player[0x27] != 0) {
    value11 = value11 * BITS_I2F(player[0x1f]);
    value12 = value12 * BITS_I2F(player[0x20]);
  }
  SCtrlInitHitDef((uint32_t *)(expr + 0x184),(int)hitdef,player);
  stk_254 = g[0x74e1];
  g[0x74e1] = g[0x74e1] + 1;
  if (stk_258 != 0) {
    hitdef[0] = 1;
  }
  if (stk_f0 == -1) {
    stk_f0 = player[0x1b];
  }
  stk_2d4 = 0;
  stk_2d8 = 0;
  stk_2dc = 0;
  stk_2fc[1] = 1;
  stk_2c8 = player[PL_FACING];
  value3 = *(int *)(expr + 0x24);
  if (value3 < 5) {
    if (value3 < 1) {
      if (value3 == 0) {
        stk_308 = (int)X87_FIST32(BITS_I2F(player[PL_POS_X]));
        stk_30c = (int)X87_FIST32(BITS_I2F(player[PL_POS_Y]));
      }
    }
    else {
      if ((((value3 == 2) && (player[PL_FACING] == 1)) || ((value3 == 1 && (player[PL_FACING] == -1)))) ||
         (value3 == 3)) {
        stk_308 = g[0x7311];
      }
      else {
        stk_308 = g[0x7311] + 0x140;
      }
      stk_30c = 0;
    }
  }
  else if (value3 == 5) {
    if (arg3 == 0) {
      stk_308 = (int)X87_FIST32(BITS_I2F(player[PL_POS_X]));
      stk_30c = (int)X87_FIST32(BITS_I2F(player[PL_POS_Y]));
    }
    else {
      stk_308 = (int)X87_FIST32(*(float *)(arg3 + 0x19c));
      stk_30c = (int)X87_FIST32(*(float *)(arg3 + 0x1a0));
    }
  }
  value3 = EvalExpressionI((int)player,expr + 0xc,0);
  stk_2b8 = (float)(value3 * player[PL_FACING] + stk_308);
  value3 = EvalExpressionI((int)player,expr + 0x18,0);
  stk_2b4 = (float)(value3 + stk_30c);
  value4 = (float80)player[PL_FACING];
  stk_2b0 = player[PL_POS_Z];
  value13 = value13 * value4;
  value15 = value15 * value4;
  value19 = value19 * value4;
  value24 = EvalExpressionI((int)player,expr + 0xe8,1);
  value3 = EvalExpressionI((int)player,expr + 0x58,0);
  stk_274 = g[G_CAMERA_BOUNDLEFT] - value3;
  stk_26c = value3 + g[G_CAMERA_BOUNDRIGHT] + 0x140;
  value21 = EvalExpressionI((int)player,expr + 0x4c,0);
  value22 = EvalExpressionI((int)player,expr + 100,0);
  value23 = EvalExpressionI((int)player,expr + 0x70,0);
  value3 = EvalExpressionI((int)player,expr + 0x94,1);
  if (value3 < -1) {
    value3 = 0;
    Warn((int)player,(int)&str_illegal_projanim_c0f9);
  }
  value4 = EvalExpressionF(player,(int *)(expr + 0x178));
  stk_2c = (int)X87_FIST32(value4);
  value4 = EvalExpressionF(player,(int *)(expr + 0x16c));
  stk_28 = (int)X87_FIST32(value4);
  value3 = ProjArrayAdd(arg4,(int *)arg4[0x87],stk_2fc,value3);
  if ((value3 != -1) &&
     (value = value3 * *(int *)(*(int *)arg4[0x87] + 4) + *(int *)(*(int *)arg4[0x87] + 0x14),
     *(int *)(expr + 0x698) != 0)) {
    value2 = *(int *)(value + 0x2d8);
    if (value2 == 0) {
      value2 = RequestNewAftImg(g[0x413f]);
      *(int *)(value + 0x2d8) = value2;
    }
    if (value2 != 0) {
      SCtrlInitAftImgParams(*(int *)(expr + 0x698),*(int *)(value + 0x2d8),value + 0x284,player)
      ;
    }
  }
  return value3;
}
#undef stk_30c
#undef stk_308
#undef stk_2fc
#undef value5
#undef value6
#undef value7
#undef value8
#undef stk_2dc
#undef stk_2d8
#undef stk_2d4
#undef value9
#undef stk_2c8
#undef stk_2c4
#undef value10
#undef stk_2bc
#undef stk_2b8
#undef stk_2b4
#undef stk_2b0
#undef value11
#undef value12
#undef value13
#undef value14
#undef value15
#undef value16
#undef value17
#undef value18
#undef value19
#undef value20
#undef value21
#undef stk_274
#undef value22
#undef stk_26c
#undef value23
#undef hitdef
#undef stk_258
#undef stk_254
#undef stk_f0
#undef value24
#undef stk_2c
#undef stk_28

/* ProjMakeInfoFree @ 0x080c93d0, 484 bytes
 *
 * Frees a Projectile parameter block (with its HitDef and AfterImage parts).
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression, HitDefEFree, AftImgParamsEFree
 * C library: free
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void ProjMakeInfoFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 6);
  FreeExpression(expr + 10);
  FreeExpression(expr + 0xd);
  FreeExpression(expr + 0x10);
  FreeExpression(expr + 0x13);
  FreeExpression(expr + 0x16);
  FreeExpression(expr + 0x19);
  FreeExpression(expr + 0x1c);
  FreeExpression(expr + 0x1f);
  FreeExpression(expr + 0x22);
  FreeExpression(expr + 0x25);
  FreeExpression(expr + 0x28);
  FreeExpression(expr + 0x2b);
  FreeExpression(expr + 0x2e);
  FreeExpression(expr + 0x31);
  FreeExpression(expr + 0x34);
  FreeExpression(expr + 0x37);
  FreeExpression(expr + 0x3a);
  FreeExpression(expr + 0x3d);
  FreeExpression(expr + 0x40);
  FreeExpression(expr + 0x43);
  FreeExpression(expr + 0x46);
  FreeExpression(expr + 0x49);
  FreeExpression(expr + 0x4c);
  FreeExpression(expr + 0x4f);
  FreeExpression(expr + 0x52);
  FreeExpression(expr + 0x55);
  FreeExpression(expr + 0x58);
  FreeExpression(expr + 0x5e);
  FreeExpression(expr + 0x5b);
  HitDefEFree((int)(expr + 0x61));
  if ((int *)expr[0x1a6] != (int *)0x0) {
    AftImgParamsEFree((int *)expr[0x1a6]);
    free((void *)expr[0x1a6]);
    return;
  }
  return;
}

/* SCtrlParseHelper @ 0x080c95c0, 1230 bytes
 *
 * Compiles Helper parameters: helpertype ("normal", "player" or "proj"),
 * name (quoted), id, pos, postype, facing, stateno, keyctrl, ownpal,
 * supermovetime, pausemovetime, and the "size." overrides (xscale, yscale,
 * ground/air front and back, height, proj.doscale, head.pos, mid.pos,
 * shadowoffset). "Illegal ..." errors name the bad value.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   arg3         char *
 *
 * Text keys read: "helpertype", "name", "id", "pos", "postype", "facing",
 *                 "stateno", "keyctrl", "ownpal", "pausemovetime",
 *                 "supermovetime", "size.xscale", "size.yscale",
 *                 "size.ground.back", "size.ground.front",
 *                 "size.air.back", "size.air.front", "size.height",
 *                 "size.proj.doscale", "size.head.pos", "size.mid.pos",
 *                 "size.shadowoffset"
 * Globals read: errmsg
 * Calls: TPGetValue, GetQuotedString, InfixToPostfix, SCtrlReadExpList,
 *        ParsePosType, ItoP_TPConstI, ItoP_TPConstF, ConstExpI,
 *        strimatchlen
 * C library: _alemu_stricmp, sprintf
 * Called by: SCtrlParseElemType
 * Messages:
 *   "Illegal postype: %s"
 *   "Illegal helper type: %s"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
bool SCtrlParseHelper(int tp,int player,char *arg3)

{
  char *value;
  int i2;
  uint8_t *value2;
  char *format;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(char **)(frame + 0xc))
  
  value = TPGetValue(tp,"helpertype");
  if (value == (char *)0x0) {
L_080c9656:
    value = TPGetValue(tp,"name");
    if ((value != (char *)0x0) &&
       (i2 = GetQuotedString(tp,"name",arg3,0x2f,(char *)0x0), i2 == 0)) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"id");
    i2 = InfixToPostfix(value2,(int *)(arg3 + 0x30),player,(uint32_t *)0x0,1);
    if (i2 == 0) {
      return false;
    }
    value2 = (uint8_t *)TPGetValue(tp,"pos");
    if (value2 != (uint8_t *)0x0) {
      value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,(int *)(arg3 + 0x40),
                                (int *)(arg3 + 0x4c));
      if (value2 == (uint8_t *)0x0) {
        return false;
      }
      if (*stk_14 != '\0') {
        return false;
      }
    }
    value = TPGetValue(tp,"postype");
    if (value != (char *)0x0) {
      i2 = ParsePosType(value);
      *(int *)(arg3 + 0x58) = i2;
      if (i2 == -1) {
        format = "Illegal postype: %s";
        arg3 = (char *)0x0;
        goto L_080c9738;
      }
    }
    i2 = ItoP_TPConstI(tp,"facing",(int *)(arg3 + 0x5c),player,1);
    if ((((((i2 != 0) &&
           (i2 = ItoP_TPConstI(tp,"stateno",(int *)(arg3 + 0x68),player,0), i2 != 0))
          && (i2 = ItoP_TPConstI(tp,"keyctrl",(int *)(arg3 + 0x74),player,0), i2 != 0
             )) && ((i2 = ItoP_TPConstI(tp,"ownpal",(int *)(arg3 + 0x80),player,0),
                    i2 != 0 &&
                    (i2 = ItoP_TPConstI(tp,"pausemovetime",(int *)(arg3 + 0x98),player,0
                                          ), i2 != 0)))) &&
        ((i2 = ItoP_TPConstI(tp,"supermovetime",(int *)(arg3 + 0x8c),player,0),
         i2 != 0 &&
         ((i2 = ItoP_TPConstF(tp,"size.xscale",(int *)(arg3 + 0xa4),player,-0x39001000),
          i2 != 0 &&
          (i2 = ItoP_TPConstF(tp,"size.yscale",(int *)(arg3 + 0xb0),player,-0x39001000),
          i2 != 0)))))) &&
       ((i2 = ItoP_TPConstI(tp,"size.ground.back",(int *)(arg3 + 0xbc),player,-0x7fef),
        i2 != 0 &&
        ((((i2 = ItoP_TPConstI(tp,"size.ground.front",(int *)(arg3 + 200),player,-0x7fef
                                 ), i2 != 0 &&
           (i2 = ItoP_TPConstI(tp,"size.air.back",(int *)(arg3 + 0xd4),player,-0x7fef),
           i2 != 0)) &&
          (i2 = ItoP_TPConstI(tp,"size.air.front",(int *)(arg3 + 0xe0),player,-0x7fef),
          i2 != 0)) &&
         ((i2 = ItoP_TPConstI(tp,"size.height",(int *)(arg3 + 0xec),player,-0x7fef),
          i2 != 0 &&
          (i2 = ItoP_TPConstI(tp,"size.proj.doscale",(int *)(arg3 + 0xf8),player,-0x7fef
                                ), i2 != 0)))))))) {
      ConstExpI((int *)(arg3 + 0x104),-0x7fef);
      ConstExpI((int *)(arg3 + 0x110),-0x7fef);
      ConstExpI((int *)(arg3 + 0x11c),-0x7fef);
      ConstExpI((int *)(arg3 + 0x128),-0x7fef);
      value2 = (uint8_t *)TPGetValue(tp,"size.head.pos");
      if (((value2 == (uint8_t *)0x0) ||
          ((value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,(int *)(arg3 + 0x104),
                                      (int *)(arg3 + 0x110)), value2 != (uint8_t *)0x0 &&
           (*stk_14 == '\0')))) &&
         ((value2 = (uint8_t *)TPGetValue(tp,"size.mid.pos"), value2 == (uint8_t *)0x0 ||
          ((value2 = SCtrlReadExpList(value2,"ii",player,&stk_14,(int *)(arg3 + 0x11c),
                                      (int *)(arg3 + 0x128)), value2 != (uint8_t *)0x0 &&
           (*stk_14 == '\0')))))) {
        i2 = ItoP_TPConstI(tp,"size.shadowoffset",(int *)(arg3 + 0x134),player,-0x7fef);
        return i2 != 0;
      }
    }
  }
  else {
    i2 = _alemu_stricmp(value,"normal");
    if (i2 == 0) {
      arg3[0x3c] = '\0';
      arg3[0x3d] = '\0';
      arg3[0x3e] = '\0';
      arg3[0x3f] = '\0';
      goto L_080c9656;
    }
    i2 = _alemu_stricmp(value,"player");
    if (i2 == 0) {
      arg3[0x3c] = '\x01';
      arg3[0x3d] = '\0';
      arg3[0x3e] = '\0';
      arg3[0x3f] = '\0';
      goto L_080c9656;
    }
    i2 = strimatchlen((int)value,(int)&str_proj,4);
    if (i2 != 0) {
      arg3[0x3c] = '\x02';
      arg3[0x3d] = '\0';
      arg3[0x3e] = '\0';
      arg3[0x3f] = '\0';
      goto L_080c9656;
    }
    format = "Illegal helper type: %s";
L_080c9738:
    sprintf((char *)(g + G_ERRMSG),format,value,arg3);
  }
  return false;
}
#undef stk_14

/* HelperInfoFree @ 0x080c9a90, 301 bytes
 *
 * Frees a Helper parameter block.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: FreeExpression
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void HelperInfoFree(int arg1)

{
  FreeExpression((int *)(arg1 + 0x30));
  FreeExpression((int *)(arg1 + 0x40));
  FreeExpression((int *)(arg1 + 0x4c));
  FreeExpression((int *)(arg1 + 0x5c));
  FreeExpression((int *)(arg1 + 0x68));
  FreeExpression((int *)(arg1 + 0x74));
  FreeExpression((int *)(arg1 + 0x80));
  FreeExpression((int *)(arg1 + 0x98));
  FreeExpression((int *)(arg1 + 0x8c));
  FreeExpression((int *)(arg1 + 0xa4));
  FreeExpression((int *)(arg1 + 0xb0));
  FreeExpression((int *)(arg1 + 0xbc));
  FreeExpression((int *)(arg1 + 200));
  FreeExpression((int *)(arg1 + 0xd4));
  FreeExpression((int *)(arg1 + 0xe0));
  FreeExpression((int *)(arg1 + 0xec));
  FreeExpression((int *)(arg1 + 0xf8));
  FreeExpression((int *)(arg1 + 0x104));
  FreeExpression((int *)(arg1 + 0x110));
  FreeExpression((int *)(arg1 + 0x11c));
  FreeExpression((int *)(arg1 + 0x128));
  FreeExpression((int *)(arg1 + 0x134));
  return;
}

/* SCtrlParsePause @ 0x080c9bc0, 137 bytes
 *
 * Compiles Pause parameters: time, movetime, endcmdbuftime, pausebg.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *
 * Text keys read: "time", "movetime", "endcmdbuftime", "pausebg"
 * Calls: ItoP_TPConstI
 * Called by: SCtrlParseElemType, SCtrlParseSuperPause
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
bool SCtrlParsePause(int tp,int player,int *expr)

{
  int i1;
  
  i1 = ItoP_TPConstI(tp,"time",expr,player,0);
  if (((i1 != 0) && (i1 = ItoP_TPConstI(tp,"movetime",expr + 3,player,0), i1 != 0)
      ) && (i1 = ItoP_TPConstI(tp,"endcmdbuftime",expr + 6,player,0), i1 != 0)) {
    i1 = ItoP_TPConstI(tp,"pausebg",expr + 9,player,1);
    return i1 != 0;
  }
  return false;
}

/* SCtrlInitPause @ 0x080c9c50, 304 bytes
 *
 * Evaluates Pause parameters and freezes the game. Warnings: "set illegal
 * pausetime", "set illegal pausemovetime", "set illegal endcmdbuftime".
 *
 * Parameters:
 *   expr         int
 *   arg2         int
 *   player       int
 *
 * Calls: EvalExpressionI, Warn
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "set illegal pausetime"
 *   "set illegal pausemovetime"
 *   "set illegal endcmdbuftime"
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 3 data addresses refer to the data image (data/mugen_data.S).
 */
uint32_t SCtrlInitPause(int expr,int arg2,int player)

{
  int *pi1;
  int value;
  int value2;
  
  value = EvalExpressionI(player,expr,1);
  g[arg2 * 9 + 0x74fa] = value;
  if (value < 0) {
    Warn(player,(int)&str_set_illegal_pausetime_c15f);
    g[arg2 * 9 + 0x74fa] = 0;
  }
  value2 = EvalExpressionI(player,expr + 0xc,1);
  value = arg2 * 4 + 0x1d0;
  *(int *)(value + player + 0xc) = value2;
  if ((value2 < 0) || (g[arg2 * 9 + 0x74fa] < value2)) {
    Warn(player,(int)&str_set_illegal_pausemovetime_c175);
    *(uint32_t *)(value + player + 0xc) = 0;
  }
  value = EvalExpressionI(player,expr + 0x24,1);
  g[arg2 * 9 + 0x74fb] = value;
  value = EvalExpressionI(player,expr + 0x18,1);
  pi1 = g;
  g[arg2 * 9 + 0x74fc] = value;
  if ((value < 0) || (pi1[arg2 * 9 + 0x74fa] < value)) {
    Warn(player,(int)&str_set_illegal_endcmdbuftime_c18f);
    g[arg2 * 9 + 0x74fc] = 0;
  }
  return 1;
}

/* PauseInfoFree @ 0x080c9d80, 52 bytes
 *
 * Frees a Pause parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 * Called by: SuperPauseInfoFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void PauseInfoFree(int *expr)

{
  FreeExpression(expr);
  FreeExpression(expr + 3);
  FreeExpression(expr + 6);
  FreeExpression(expr + 9);
  return;
}

/* SCtrlParseSuperPause @ 0x080c9dc0, 389 bytes
 *
 * Compiles SuperPause parameters: the Pause ones plus anim (super spark),
 * sound, pos, darken, p2defmul, poweradd, unhittable.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *   expr         int *
 *
 * Text keys read: "time", "anim", "pos", "darken", "p2defmul", "poweradd",
 *                 "unhittable", "sound"
 * Calls: SCtrlParsePause, ItoP_TPConstI, ConstExpI, TPGetValue, ParseAnim,
 *        SCtrlReadExpList, ItoP_TPConstF, ParseSnd
 * Called by: SCtrlParseElemType
 *
 * Elecbyte file: src/mugen/st-exprn.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
bool SCtrlParseSuperPause(int tp,int player,int *expr)

{
  bool b1;
  int i2;
  uint8_t *value;
  uint32_t stale_var;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(char **)(frame + 0xc))
  
  SCtrlParsePause(tp,player,expr);
  i2 = ItoP_TPConstI(tp,"time",expr,player,0x1e);
  if (i2 != 0) {
    ConstExpI(expr + 0xd,100);
    expr[0xc] = 1;
    value = (uint8_t *)TPGetValue(tp,"anim");
    b1 = ParseAnim(value,expr + 0xd,expr + 0xc,player);
    if (((ZEXT8(b1) != 0) &&
        (((value = (uint8_t *)TPGetValue(tp,"pos"), value == (uint8_t *)0x0 ||
          ((value = SCtrlReadExpList(value,"ff",player,&stk_14,expr + 0x10,expr + 0x13),
           *stk_14 == '\0' && (value != (uint8_t *)0x0)))) &&
         (i2 = ItoP_TPConstI(tp,"darken",expr + 0x16,player,1), i2 != 0)))) &&
       (((i2 = ItoP_TPConstF(tp,"p2defmul",expr + 0x19,player,0), i2 != 0 &&
         (i2 = ItoP_TPConstI(tp,"poweradd",expr + 0x1c,player,0), i2 != 0)) &&
        (i2 = ItoP_TPConstI(tp,"unhittable",expr + 0x1f,player,1), i2 != 0)))) {
      ConstExpI(expr + 0x23,-1);
      expr[0x22] = 1;
      value = (uint8_t *)TPGetValue(tp,"sound");
      i2 = ParseSnd(value,expr + 0x23,expr + 0x26,expr + 0x22,player);
      return i2 != 0;
    }
  }
  return false;
}
#undef stk_14

/* SuperPauseInfoFree @ 0x080c9f50, 124 bytes
 *
 * Frees a SuperPause parameter block.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: PauseInfoFree, FreeExpression
 * Called by: SCtrlRCElemFree
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void SuperPauseInfoFree(int *expr)

{
  PauseInfoFree(expr);
  FreeExpression(expr + 0x16);
  FreeExpression(expr + 0x19);
  FreeExpression(expr + 0x1c);
  FreeExpression(expr + 0x1f);
  FreeExpression(expr + 0xd);
  FreeExpression(expr + 0x10);
  FreeExpression(expr + 0x13);
  FreeExpression(expr + 0x23);
  FreeExpression(expr + 0x26);
  return;
}

/* MoreExpFree @ 0x080c9fd0, 38 bytes
 *
 * Frees a small parameter block of expressions. Not called in this build.
 *
 * Parameters:
 *   expr         int *
 *
 * Calls: FreeExpression
 *
 * Elecbyte file: src/mugen/st-exprn.c
 */
void MoreExpFree(int *expr)

{
  int i1;
  
  i1 = 4;
  do {
    FreeExpression(expr);
    expr = expr + 3;
    i1 = i1 + -1;
  } while (-1 < i1);
  return;
}

