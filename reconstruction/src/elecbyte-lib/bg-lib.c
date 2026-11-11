/*
 * bg-lib.c -- backgrounds
 * Stage, title and screen backgrounds from .def files: normal, parallax and
 * animated elements with layers, tiling, parallax deltas, velocities, sine
 * motion and windows, plus background controllers. Draws them relative to
 * the camera, including perspective floors.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/bg-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern uint8_t GlobalTemp[16] __asm__("D_082a6298"); /* file-static 0x082a6298 */

/* BGArrayReadFile @ 0x0804b0f0, 26 bytes
 *
 * BGArrayReadFileSA for a file with no extra sprite and animation sources.
 * Not called in this build.
 *
 * Parameters:
 *   filename     char *
 *   group        char *
 *
 * Calls: BGArrayReadFileSA
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayReadFile(char *filename,char *group)

{
  BGArrayReadFileSA(filename,group,0,0);
  return;
}

/* BGArrayReadFileSA @ 0x0804b110, 180 bytes
 *
 * Opens a .def file, splits its directory off (sprite paths are relative to
 * it) and reads the background group `group` (BGArrayReadTP). Errors:
 * "TXTPARSE error opening <file>" or "BG error reading <file>".
 *
 * Parameters:
 *   filename     char *
 *   group        char *
 *   arg3         int
 *   arg4         int
 *
 * Calls: TPReadFile, splitdirfile, BGArrayReadTP, TPFree
 * C library: strcat
 * Called by: BGArrayReadFile
 * Messages:
 *   "\nTXTPARSE error opening "
 *   "\nBG error reading "
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1010 bytes,
 *       1 variables), because their address is taken.
 */
char * BGArrayReadFileSA(char *filename,char *group,int arg3,int arg4)

{
  char *tp;
  char *pc2;
  unsigned char frame[0x1010] __attribute__((aligned(16)));
#define dirname (*(char (*)[4096])(frame + 0x4))
  
  tp = TPReadFile(filename);
  if (tp == (char *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,filename);
    pc2 = (char *)0x0;
  }
  else {
    splitdirfile(filename,dirname,(char *)0x0);
    pc2 = BGArrayReadTP(tp,dirname,group,arg3,arg4);
    if (pc2 == (char *)0x0) {
      strcat((char *)ErrorMessage,"\nBG error reading ");
      strcat((char *)ErrorMessage,filename);
    }
    TPFree((uint32_t *)tp);
  }
  return pc2;
}
#undef dirname

/* BGArrayReadTP @ 0x0804b1d0, 2838 bytes
 *
 * Builds a background set from the "[<group>Def]" group and its "[<group>
 * ...]" element groups of a parsed .def file. At least one element is
 * required ("Need at least one [%s] type bg"). The definition group gives
 * "spr" (the sprite file, loaded relative to `dirname` unless a sprite array
 * is supplied), "debugbg" and "bgclearcolor".
 *
 * Each element group is read for: "type" (by first letter: normal, parallax,
 * anim, dummy, and an 'h' type), "spriteno", "actionno", "layerno", "start",
 * "delta", "velocity", "tile", "tilespacing", "trans" and "alpha", "mask",
 * "window" and "windowdelta", "sin.x"/"sin.y", "width", "xscale",
 * "yscalestart"/"yscaledelta" (parallax floors), "id" and "positionlink".
 * Animated elements use the "[Begin Action n]" groups of the same file.
 * Errors name the element: "Missing type in %s", "Invalid type", "Invalid or
 * missing spriteno", "Missing actionno", "Invalid argument: trans = %s",
 * "Missing or invalid width or xscale for parallax". Background controllers
 * are read last (BGArrayReadCtrlTP). Returns the set or NULL.
 *
 * Parameters:
 *   tp           char *
 *   dirname      char *
 *   group        char *
 *   arg4         int
 *   arg5         int
 *
 * Text keys read: "spr", "debugbg", "bgclearcolor", "layerno", "type",
 *                 "start", "delta", "velocity", "actionno", "spriteno",
 *                 "trans", "alpha", "mask", "id", "tile", "tilespacing",
 *                 "window", "windowdelta", "positionlink", "sin.x",
 *                 "sin.y", "width", "xscale", "yscalestart", ...
 * Calls: TPGroupMatchCount, BGArrayNew, TPGroupSeek, TPGetValue,
 *        joindirfile, SpriteReadFile, TPGetValueInt, TPScanf,
 *        TPGroupScanFirst, strimatch, TPGroupScanNext, AnimRCReadFileTP,
 *        GetDrawType, BGArrayAddAnim, BGArrayAdd, BGAccess,
 *        SpriteArrayAccessGrpItem, TPGetValueFloat, BGParalSetup,
 *        BGArrayReadCtrlTP, BGArrayFree
 * C library: strlen, sprintf, strcpy, strcat, memcpy
 * Called by: BGArrayReadFileSA, GameBGLoad, GameLoadSystem,
 *            GameReloadSystemSprSnd, SiSceneReadTP
 * Messages:
 *   "Need at least one [%s] type bg"
 *   "Can\'t access group %s"
 *   "Error: sff file must be specified"
 *   "Error reading sprite %s"
 *   "begin action "
 *   "\nError loading anim."
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: removed 2 x87 control-word save statements
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       3 calls, 0 returns
 * Note: Locals live in `frame`, laid out as on the original stack (0x10f0 bytes,
 *       31 variables), because their address is taken.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
char * BGArrayReadTP(char *tp,char *dirname,char *group,int arg4,int arg5)

{
  float80 f1;
  bool b2;
  size_t s3;
  int count;
  int count2;
  char *bgs;
  int *sprites;
  uint32_t stale_var;
  char *value;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  int i9;
  uint32_t u10;
  uint32_t *pu11;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t stale_ECX_01;
  uint32_t stale_ECX_02;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t u12;
  size_t s13;
  float80 f14;
  uint32_t u15;
  uint16_t entry_FPUControlWord;
  int i16;
  char *value2;
  char *pc18;
  char *group2;
  uint32_t *pu20;
  uint32_t *pu21;
  unsigned char frame[0x10f0] __attribute__((aligned(16)));
#define stk_10f0 (*(int *)(frame + 0x0))
#define stk_10ec (*(int *)(frame + 0x4))
#define value3 (*(char **)(frame + 0x8))
#define stk_10dc (*(float *)(frame + 0x14))
#define stk_10d8 (*(float *)(frame + 0x18))
#define stk_10d4 (*(float *)(frame + 0x1c))
#define stk_10d0 (*(int *)(frame + 0x20))
#define stk_10cc (*(int *)(frame + 0x24))
#define stk_10c8 (*(float *)(frame + 0x28))
#define stk_10c4 (*(uint32_t *)(frame + 0x2c))
#define stk_10c0 (*(int *)(frame + 0x30))
#define stk_10bc (*(uint32_t *)(frame + 0x34))
#define stk_10b8 (*(uint32_t *)(frame + 0x38))
#define stk_10b4 (*(uint32_t *)(frame + 0x3c))
#define stk_10b0 (*(uint32_t *)(frame + 0x40))
#define group3 (*(int *)(frame + 0x44))
#define stk_10a8 (*(int *)(frame + 0x48))
#define stk_10a4 (*(float *)(frame + 0x4c))
#define stk_10a0 (*(float *)(frame + 0x50))
#define stk_109c (*(uint32_t *)(frame + 0x54))
#define stk_1098 (*(float *)(frame + 0x58))
#define stk_1094 (*(uint32_t *)(frame + 0x5c))
#define stk_1090 (*(uint32_t *)(frame + 0x60))
#define stk_108c (*(uint32_t *)(frame + 0x64))
#define stk_1088 (*(uint32_t *)(frame + 0x68))
#define stk_1084 (*(int *)(frame + 0x6c))
#define stk_1080 (*(uint16_t *)(frame + 0x70))
#define stk_107e (*(uint16_t *)(frame + 0x72))
#define group4 (*(char (*)[48])(frame + 0x74))
#define group5 (*(char (*)[48])(frame + 0xa4))
#define stk_101c (*(char (*)[4108])(frame + 0xd4))
  
  s3 = strlen(group);
  sprintf(group5,"%s ",group);
  sprintf(group4,"%s]",group);
  count = TPGroupMatchCount((int)tp,group5);
  count2 = TPGroupMatchCount((int)tp,group4);
  s13 = count + count2;
  if (s13 == 0) {
    sprintf((char *)ErrorMessage,"Need at least one [%s] type bg",group,0);
    return (char *)0x0;
  }
  bgs = (char *)BGArrayNew(s13,0);
  if (bgs == (char *)0x0) {
    return (char *)0x0;
  }
  group2 = stk_101c;
  strcpy(group2,group);
  strcat(group2,"def");
  count = TPGroupSeek((int)tp,group2);
  if (count == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",group2,tp);
  }
  else {
    value3 = TPGetValue((int)tp,"spr");
    if (value3 == (char *)0x0) {
      if (arg4 == 0) {
        memcpy(ErrorMessage,"Error: sff file must be specified",0x22);
        goto L_0804bccb;
      }
      *(int *)(bgs + 0x28) = arg4;
      bgs[0x2c] = '\0';
      bgs[0x2d] = '\0';
      bgs[0x2e] = '\0';
      bgs[0x2f] = '\0';
    }
    else {
      joindirfile(group2,dirname,value3);
      sprites = SpriteReadFile(group2);
      *(int **)(bgs + 0x28) = sprites;
      if (sprites == (int *)0x0) {
        value2 = "Error reading sprite %s";
L_0804bcbb:
        sprintf((char *)ErrorMessage,value2,value3,group2);
        goto L_0804bccb;
      }
      bgs[0x2c] = '\x01';
      bgs[0x2d] = '\0';
      bgs[0x2e] = '\0';
      bgs[0x2f] = '\0';
    }
    b2 = TPGetValueInt((int)tp,"debugbg",&stk_1088);
    if (ZEXT8(b2) == 0) {
      TPScanf((int)tp,"bgclearcolor","%i,%i,%i",bgs + 0x3c,bgs + 0x40,bgs + 0x44,
              stale_ECX,stale_ECX);
    }
    else if (stk_1088 != 0) {
      bgs[0x44] = -1;
      bgs[0x45] = '\0';
      bgs[0x46] = '\0';
      bgs[0x47] = '\0';
      bgs[0x3c] = -1;
      bgs[0x3d] = '\0';
      bgs[0x3e] = '\0';
      bgs[0x3f] = '\0';
      bgs[0x40] = '\0';
      bgs[0x41] = '\0';
      bgs[0x42] = '\0';
      bgs[0x43] = '\0';
    }
    if (arg5 == 0) {
      count = TPGroupScanFirst((int)tp);
      do {
        count2 = strimatch((char *)(count + 1),"begin action ");
        if (count2 != 0) break;
        count = TPGroupScanNext((int)tp);
      } while (count != 0);
      if (count != 0) {
        sprites = AnimRCReadFileTP((int)tp);
        *(int **)(bgs + 0x20) = sprites;
        if (sprites == (int *)0x0) {
          strcat((char *)ErrorMessage,"\nError loading anim.");
          goto L_0804bccb;
        }
        bgs[0x24] = '\x01';
        bgs[0x25] = '\0';
        bgs[0x26] = '\0';
        bgs[0x27] = '\0';
      }
    }
    else {
      *(int *)(bgs + 0x20) = arg5;
      bgs[0x24] = '\0';
      bgs[0x25] = '\0';
      bgs[0x26] = '\0';
      bgs[0x27] = '\0';
    }
    value3 = (char *)TPGroupScanFirst((int)tp);
    stk_1088 = 0;
    if (0 < (int)s13) {
      do {
        while ((*(int *)(tp + 0x18) != *(int *)(tp + 0x2c) &&
               ((count = strimatch(value3 + 1,group), count == 0 ||
                (((*(uint8_t *)(__ctype_b + 1 + value3[s3 + 1] * 2) & 0x20) == 0 &&
                 (value3[s3 + 1] != ']'))))))) {
          value3 = (char *)TPGroupScanNext((int)tp);
        }
        stk_10a8 = -1;
        group3 = -1;
        stk_10b0 = 0xffffffff;
        stk_1098 = 0.0;
        stk_109c = 0;
        stk_10a0 = 1.0;
        stk_10a4 = 1.0;
        stk_108c = 0;
        stk_1090 = 0;
        stk_10f0 = 0;
        stk_10bc = 0;
        stk_10c0 = 0;
        stk_10c4 = 0;
        stk_10b8 = 0x100;
        stk_10b4 = 0;
        stk_1094 = 0;
        pu20 = &stk_1094;
        value2 = group2;
        TPGetValueInt((int)tp,"layerno",&stk_1094);
        pc18 = "type";
        value = TPGetValue((int)tp,"type");
        if (value == (char *)0x0) {
          sprintf((char *)ErrorMessage,"Missing type in %s",value3,stale_ECX_00);
          goto L_0804bccb;
        }
        switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
        case 0x61:
          stk_10ec = 3;
          break;
        default:
          sprintf((char *)ErrorMessage,"Invalid type: %s\n\tin %s",value,value3);
          goto L_0804bccb;
        case 100:
          stk_10ec = 10;
          break;
        case 0x68:
          stk_10ec = 2;
          break;
        case 0x6e:
          stk_10ec = 0;
          break;
        case 0x70:
          stk_10ec = 1;
        }
        TPScanf((int)tp,"start","%i,%i",&stk_109c,&stk_1098,pc18,pu20,value2);
        TPScanf((int)tp,"delta","%f,%f",&stk_10a4,&stk_10a0);
        stk_10a4 = stk_10a4 * -1.0;
        stk_10a0 = stk_10a0 * -1.0;
        TPScanf((int)tp,"velocity","%f,%f",&stk_1090,&stk_108c);
        if ((stk_10ec == 3) || (stk_10ec == 10)) {
          if ((stk_10ec == 3) &&
             (b2 = TPGetValueInt((int)tp,"actionno",&stk_10b0),
             ZEXT8(b2) == 0)) {
            value2 = "Missing actionno in %s";
            goto L_0804bcbb;
          }
        }
        else {
          count = TPScanf((int)tp,"spriteno","%i,%i",&group3,&stk_10a8);
          if (count != 2) {
            sprintf((char *)ErrorMessage,"Invalid or missing spriteno: %i,%i\n\tin %s",group3,
                    stk_10a8,value3);
            goto L_0804bccb;
          }
        }
        value2 = TPGetValue((int)tp,"trans");
        if (value2 != (char *)0x0) {
          pu11 = &stk_10b8;
          pu21 = &stk_10b4;
          stk_10f0 = GetDrawType(value2,&stk_10b8,&stk_10b4);
          if (stk_10f0 == -2) {
            sprintf((char *)ErrorMessage,"Invalid argument: trans = %s\nin %s",value2,value3);
            goto L_0804bccb;
          }
          TPScanf((int)tp,"alpha","%i,%i",&stk_10b8,&stk_10b4,pu11,pu21,group2);
        }
        b2 = TPGetValueInt((int)tp,"mask",&stk_10bc);
        f1 = stk_1098;
        f14 = stk_10a0;
        if (ZEXT8(b2) != 0) {
          if (stk_10bc == 0) {
            stk_10bc = 0;
          }
          else if (stk_10bc == 1) {
            stk_10bc = 1;
          }
        }
        if (stk_10ec == 3) {
          count = BGArrayAddAnim((int)bgs,stk_1088,stk_109c,BITS_F2I(uint32_t, stk_1098),BITS_F2I(uint32_t, stk_10a4),BITS_F2I(uint32_t, stk_10a0),stk_10b0);
          if (count == -1) {
            strcat((char *)ErrorMessage,"Error adding anim for ");
            strcat((char *)ErrorMessage,value3);
            goto L_0804bccb;
          }
        }
        else {
          count = BGArrayAdd((int)bgs,stk_1088,stk_10ec,stk_109c,BITS_F2I(uint32_t, stk_1098),BITS_F2I(uint32_t, stk_10a4),BITS_F2I(uint32_t, stk_10a0),stk_10f0,stk_10b8,stk_10b4,stk_10bc,group3,stk_10a8);
          f14 = f1;
          if (count == -1) {
            strcat((char *)ErrorMessage,"\nError in ");
            strcat((char *)ErrorMessage,value3);
            goto L_0804bccb;
          }
        }
        count = BGAccess((int)bgs,stk_1088);
        *(uint32_t *)(count + 0x80) = stk_1094;
        *(uint32_t *)(count + 0x24) = stk_1090;
        *(uint32_t *)(count + 0x28) = stk_108c;
        pu20 = (uint32_t *)(count + 0xb4);
        group2 = "id";
        TPGetValueInt((int)tp,"id",pu20);
        TPScanf((int)tp,"tile","%i,%i",&stk_10c4,&stk_10c0,group2,pu20,f14);
        *(uint32_t *)(count + 0x2c) = stk_10c4;
        *(int *)(count + 0x30) = stk_10c0;
        TPScanf((int)tp,"tilespacing","%i,%i",count + 0x34,count + 0x38);
        if (stk_10ec == 3) {
          if (*(int *)(count + 0x34) < 1) {
            *(uint32_t *)(count + 0x34) = 1;
          }
          if (*(int *)(count + 0x38) < 1) {
            *(uint32_t *)(count + 0x38) = 1;
          }
        }
        *(uint32_t *)(count + 0x4c) = 0;
        count2 = count + 0x5c;
        i16 = count + 0x54;
        u15 = stale_ECX_01;
        i9 = TPScanf((int)tp,"window","%i,%i,%i,%i",count + 0x50,count + 0x58,i16,count2,
                        stale_ECX_01);
        u12 = stale_EDX;
        if (3 < i9) {
          *(uint32_t *)(count + 0x4c) = 1;
          TPScanf((int)tp,"windowdelta","%f,%f",count + 0x60,count + 100,i16,count2,u15);
          u12 = stale_EDX_00;
        }
        pu20 = (uint32_t *)(count + 0xd0);
        group2 = tp;
        TPGetValueInt((int)tp,"positionlink",pu20);
        TPScanf((int)tp,"sin.x","%f, %f, %f",count + 0xd4,count + 0xdc,count + 0xe4,pu20,
                u12);
        count2 = count + 0xe8;
        TPScanf((int)tp,"sin.y","%f, %f, %f",count + 0xd8,count + 0xe0,count2);
        if (stk_10ec == 1) {
          u15 = 0;
          stk_10dc = 100.0;
          stk_10c8 = 0.0;
          count = TPScanf((int)tp,"width","%i,%i",&stk_10d0,&stk_10cc,count2,pu20,u12)
          ;
          if (count == 2) {
            u15 = 1;
          }
          else {
            count = TPScanf((int)tp,"xscale","%f,%f",&stk_10d8,&stk_10d4,count2,pu20,
                            u12);
            if (count != 2) {
              sprintf((char *)ErrorMessage,"Missing or invalid width or xscale for parallax in %s.",
                      value3,stale_ECX_02);
              goto L_0804bccb;
            }
            sprites = (int *)SpriteArrayAccessGrpItem(*(int **)(bgs + 0x28),group3,stk_10a8)
            ;
            stk_10d0 = (int)X87_FIST32((float)*sprites * stk_10d8);
            stk_10cc = (int)X87_FIST32((float)*sprites * stk_10d4);
            stk_1084 = stk_10cc;
          }
          TPGetValueFloat((int)tp,"yscalestart",&stk_10dc);
          TPGetValueFloat((int)tp,"yscaledelta",&stk_10c8);
          u10 = stk_10c0 * 2 | stk_10c4;
          f14 = stk_10c8 * 10.0;
          count = (int)X87_FIST32(stk_10dc * 10.0);
          count2 = stk_10d0;
          i16 = stk_10cc;
          stk_1084 = count;
          pu11 = (uint32_t *)BGAccess((int)bgs,stk_1088);
          count = BGParalSetup((int)bgs,pu11,count2,i16,count,BITS_F2I(uint32_t, f14),u10,u15);
          group2 = bgs;
          if (count == 0) {
            value2 = "Can\'t init parallax in %s.";
            goto L_0804bcbb;
          }
        }
        value3 = (char *)TPGroupScanNext((int)tp);
        stk_1088 = stk_1088 + 1;
      } while ((int)stk_1088 < (int)s13);
    }
    count = BGArrayReadCtrlTP((int)bgs,(int)tp,group);
    if (count != 0) {
      return bgs;
    }
    strcat((char *)ErrorMessage,"\nError reading bg control data");
  }
L_0804bccb:
  BGArrayFree((int)bgs);
  return (char *)0x0;
}
#undef stk_10f0
#undef stk_10ec
#undef value3
#undef stk_10dc
#undef stk_10d8
#undef stk_10d4
#undef stk_10d0
#undef stk_10cc
#undef stk_10c8
#undef stk_10c4
#undef stk_10c0
#undef stk_10bc
#undef stk_10b8
#undef stk_10b4
#undef stk_10b0
#undef group3
#undef stk_10a8
#undef stk_10a4
#undef stk_10a0
#undef stk_109c
#undef stk_1098
#undef stk_1094
#undef stk_1090
#undef stk_108c
#undef stk_1088
#undef stk_1084
#undef stk_1080
#undef stk_107e
#undef group4
#undef group5
#undef stk_101c

/* BGArrayReadCtrlTP @ 0x0804bcf0, 1620 bytes
 *
 * Reads the background controllers ("[<group>CtrlDef]" groups, such as
 * [BGCtrlDef], with "looptime" and "ctrlid", each followed by
 * "[<group>Ctrl]" groups). A controller has a "type" (null, visible, enable,
 * velset, veladd, posset, posadd, anim, sinx, siny), "time" range,
 * "x"/"y"/"value" parameters and the element ids it acts on ("ctrlid").
 * Returns the controller table, or NULL.
 *
 * Parameters:
 *   arg1         int
 *   tp           int
 *   arg3         uint32_t
 *
 * Text keys read: "looptime", "eventID", "ctrlid", "type", "time", "x",
 *                 "y", "value"
 * Calls: TPGroupMatchCount, ecalloc, TPGroupScanFirst, strimatchlen,
 *        TPGetValueInt, TPScanf, strimatch, TPGroupScanNext, TPGetValue,
 *        TPGetValueFloat
 * C library: sprintf, _alemu_stricmp
 * Called by: BGArrayReadTP
 * Messages:
 *   "\n%i/%i %s: Missing \"type\" parameter."
 *   "\n%s: Invalid type: "
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 2 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0xf0 bytes,
 *       16 variables), because their address is taken.
 */
uint32_t BGArrayReadCtrlTP(int arg1,int tp,uint32_t arg3)

{
  int count;
  int count2;
  float *pf3;
  float *pf4;
  float *value;
  float *stale_ECX;
  uint32_t u6;
  uint32_t u7;
  size_t s8;
  int *pi9;
  float *pf10;
  int *pi11;
  int *pi12;
  uint32_t *pu13;
  char *pc14;
  float *pf15;
  uint32_t u16;
  unsigned char frame[0xf0] __attribute__((aligned(16)));
#define stk_e8 (*(int *)(frame + 0x8))
#define stk_e4 (*(uint32_t **)(frame + 0xc))
#define group (*(char (*)[48])(frame + 0x14))
#define group2 (*(uint32_t (*)[12])(frame + 0x44))
#define stk_7c (*(int *)(frame + 0x74))
#define stk_78 (*(uint8_t (*)[4])(frame + 0x78))
#define stk_74 (*(uint8_t (*)[4])(frame + 0x7c))
#define stk_70 (*(uint8_t (*)[4])(frame + 0x80))
#define stk_6c (*(uint8_t (*)[4])(frame + 0x84))
#define stk_68 (*(uint8_t (*)[4])(frame + 0x88))
#define stk_64 (*(uint8_t (*)[4])(frame + 0x8c))
#define stk_60 (*(uint8_t (*)[4])(frame + 0x90))
#define stk_5c (*(uint8_t (*)[4])(frame + 0x94))
#define stk_58 (*(uint8_t (*)[8])(frame + 0x98))
#define stk_50 (*(uint32_t (*)[4])(frame + 0xa0))
#define stk_40 (*(uint32_t (*)[12])(frame + 0xb0))
  
  sprintf((char *)group2,"%sctrl",arg3);
  sprintf(group,"%sctrldef",arg3);
  pu13 = group2;
  do {
    stk_e4 = pu13;
    u6 = *stk_e4 + 0xfefefeff & (*stk_e4 ^ 0xffffffff);
    u7 = u6 & 0x80808080;
    pu13 = stk_e4 + 1;
  } while (u7 == 0);
  if ((u6 & 0x8080) == 0) {
    u7 = u7 >> 0x10;
    pu13 = (uint32_t *)((int)stk_e4 + 6);
  }
  stk_e4 = pu13;
  pf10 = (float *)((int)stk_e4 + ((-3 - (uint32_t)CARRY1((uint8_t)u7,(uint8_t)u7)) - (int)group2)
                     );
  count = TPGroupMatchCount(tp,(char *)group2);
  count2 = TPGroupMatchCount(tp,group);
  s8 = count - count2;
  if (s8 != 0) {
    *(size_t *)(arg1 + 0x38) = s8;
    pu13 = (uint32_t *)0x54;
    pf4 = pf10;
    pf15 = pf10;
    count = ecalloc(s8,0x54);
    *(int *)(arg1 + 0x34) = count;
    if (count == 0) {
      return 0;
    }
    pi11 = &stk_7c;
    for (count = 0x15; count != 0; count = count + -1) {
      *pi11 = 0;
      pi11 = pi11 + 1;
    }
    stk_50[1] = 0;
    stk_40[0] = 0xffffffff;
    stk_7c = -1;
    stk_50[0] = 0xffffffff;
    pf3 = (float *)TPGroupScanFirst(tp);
    stk_e8 = 0;
    if (0 < (int)s8) {
      do {
        if (*(int *)(tp + 0x18) != *(int *)(tp + 0x2c)) {
          do {
            count = strimatchlen((int)pf3 + 1,(int)group,(int)pf10 + 3);
            pf4 = (float *)0x0;
            if ((count != 0) &&
               (((*(uint8_t *)((int)__ctype_b + *(char *)((int)(pf10 + 1) + (int)pf3) * 2 + 1) &
                 0x20) != 0 ||
                (pf4 = __ctype_b, *(char *)((int)(pf10 + 1) + (int)pf3) == ']')))) {
              pi11 = &stk_7c;
              for (count = 0x15; count != 0; count = count + -1) {
                *pi11 = 0;
                pi11 = pi11 + 1;
              }
              stk_50[1] = 0;
              stk_40[0] = 0xffffffff;
              stk_7c = -1;
              stk_50[0] = 0xffffffff;
              u16 = 0;
              TPGetValueInt(tp,"looptime",stk_40);
              pu13 = stk_50;
              pc14 = "eventID";
              TPGetValueInt(tp,"eventID",pu13);
              pf4 = (float *)TPScanf(tp,"ctrlid","%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",&stk_7c,
                                        stk_78,stk_74,stk_70,stk_6c,stk_68,stk_64,
                                        stk_60,stk_5c,stk_58,pc14,pu13,u16);
              (&stk_7c)[(int)pf4] = -1;
            }
            pu13 = group2;
            pf15 = pf4;
            count = strimatch((char *)((int)pf3 + 1),(char *)pu13);
          } while (((count == 0) ||
                   (((*(uint8_t *)((int)__ctype_b + *(char *)((int)pf10 + 1 + (int)pf3) * 2 + 1)
                     & 0x20) == 0 && (*(char *)((int)pf10 + 1 + (int)pf3) != ']')))) &&
                  (pf3 = (float *)TPGroupScanNext(tp),
                  *(int *)(tp + 0x18) != *(int *)(tp + 0x2c)));
        }
        pi11 = (int *)(*(int *)(arg1 + 0x34) + stk_e8 * 0x54);
        pi9 = &stk_7c;
        pi12 = pi11;
        for (count = 0x15; count != 0; count = count + -1) {
          *pi12 = *pi9;
          pi9 = pi9 + 1;
          pi12 = pi12 + 1;
        }
        count = TPScanf(tp,"ctrlid","%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",pi11,pi11 + 1,
                        pi11 + 2,pi11 + 3,pi11 + 4,pi11 + 5,pi11 + 6,pi11 + 7,
                        pi11 + 8,pi11 + 9,pu13,pf4,pf15);
        pi11[count] = -1;
        if (*pi11 == -1) {
          pi9 = &stk_7c;
          pi12 = pi11;
          for (count = 0xb; count != 0; count = count + -1) {
            *pi12 = *pi9;
            pi9 = pi9 + 1;
            pi12 = pi12 + 1;
          }
        }
        pc14 = "type";
        pi12 = pi9;
        value = (float *)TPGetValue(tp,"type");
        if (value == (float *)0x0) {
          sprintf((char *)ErrorMessage,"\n%i/%i %s: Missing \"type\" parameter.",stk_e8,s8,
                  pf3,pc14,pi9,pi12);
          return 0;
        }
        count = _alemu_stricmp((char *)value,"visible");
        if (count == 0) {
          pi11[0xc] = 1;
        }
        else {
          count = _alemu_stricmp((char *)value,"enable");
          if (count == 0) {
            pi11[0xc] = 2;
          }
          else {
            count = _alemu_stricmp((char *)value,"velset");
            if (count == 0) {
              pi11[0xc] = 4;
            }
            else {
              count = _alemu_stricmp((char *)value,"veladd");
              if (count == 0) {
                pi11[0xc] = 6;
              }
              else {
                count = _alemu_stricmp((char *)value,"posset");
                if (count == 0) {
                  pi11[0xc] = 3;
                }
                else {
                  count = _alemu_stricmp((char *)value,"posadd");
                  if (count == 0) {
                    pi11[0xc] = 5;
                  }
                  else {
                    count = _alemu_stricmp((char *)value,"anim");
                    if (count == 0) {
                      pi11[0xc] = 8;
                    }
                    else {
                      count = _alemu_stricmp((char *)value,"sinx");
                      if (count == 0) {
                        pi11[0xc] = 0xb;
                      }
                      else {
                        count = _alemu_stricmp((char *)value,"siny");
                        if (count == 0) {
                          pi11[0xc] = 0xc;
                        }
                        else {
                          count = _alemu_stricmp((char *)value,"null");
                          if (count == 0) {
                            pi11[0xc] = 0;
                          }
                          else {
                            count = _alemu_stricmp((char *)value,"dummy");
                            if (count != 0) {
                              sprintf((char *)ErrorMessage,"\n%s: Invalid type: ",value,count);
                              return 0;
                            }
                            pi11[0xc] = 0x14;
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
        pu13 = (uint32_t *)(pi11 + 0xf);
        pf4 = pf3;
        pf15 = pf3;
        count = TPScanf(tp,"time","%i,%i,%i",pi11 + 0xd,pi11 + 0xe);
        if (count < 2) {
          pi11[0xe] = pi11[0xd];
        }
        switch(pi11[0xc]) {
        case 1:
        case 2:
          pf15 = value;
          goto L_0804c2d2;
        case 3:
        case 4:
        case 5:
        case 6:
          pi11[0x12] = -0x39001000;
          pi11[0x11] = -0x39001000;
          pf15 = stale_ECX;
          TPGetValueFloat(tp,"x",(float *)(pi11 + 0x11));
          pf4 = (float *)(pi11 + 0x12);
          pu13 = (uint32_t *)(int)&str_y;
          TPGetValueFloat(tp,"y",pf4);
          break;
        case 8:
          pf15 = pf3;
L_0804c2d2:
          pf4 = (float *)(pi11 + 0x10);
          pu13 = (uint32_t *)(int)&str_value;
          TPGetValueInt(tp,"value",(uint32_t *)pf4);
          break;
        case 0xb:
        case 0xc:
          pu13 = (uint32_t *)(pi11 + 0x13);
          pf15 = value;
          TPScanf(tp,"value","%f,%f,%f",pi11 + 0x11,pi11 + 0x12);
          pf4 = value;
        }
        pf3 = (float *)TPGroupScanNext(tp);
        stk_e8 = stk_e8 + 1;
      } while (stk_e8 < (int)s8);
    }
  }
  return 1;
}
#undef stk_e8
#undef stk_e4
#undef group
#undef group2
#undef stk_7c
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_58
#undef stk_50
#undef stk_40

/* BGArrayNew @ 0x0804c350, 107 bytes
 *
 * Creates an empty background set with room for `capacity` elements.
 *
 * Parameters:
 *   arg1         size_t
 *   arg2         uint32_t
 *
 * Calls: ecalloc, ArrayNew, BGArrayFree
 * Called by: BGArrayReadTP
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
int BGArrayNew(size_t arg1,uint32_t arg2)

{
  int mem;
  uint32_t *array;
  
  mem = ecalloc(1,0x54);
  if (mem == 0) {
    mem = 0;
  }
  else {
    array = ArrayNew(arg1,0x100,0);
    *(uint32_t **)(mem + 0x30) = array;
    if (array == (uint32_t *)0x0) {
      BGArrayFree(mem);
      mem = 0;
    }
    else {
      *(uint32_t *)(mem + 0x28) = arg2;
      *(uint32_t *)(mem + 0x48) = 0xffffffff;
      *(uint32_t *)(mem + 0x3c) = 0xffffffff;
    }
  }
  return mem;
}

/* BGArrayFree @ 0x0804c3c0, 442 bytes
 *
 * Frees a background set: element animations, the element array, the
 * controllers, and the AnimRC and sprite array when the set owns them.
 *
 * Parameters:
 *   bgs          int
 *
 * Calls: ArrayScanFirst, AnimFree, ArrayScanNext, ArrayFree, AnimRCFree,
 *        SpriteArrayFree
 * C library: free
 * Called by: BGArrayNew, BGArrayReadTP, GameUnloadStage, GameUnloadSystem,
 *            GameUnloadSystemSprSnd, SiSceneFree
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: written by hand from the assembly at 0x0804c3c0-0x0804c57a. Reason: the
 *       loop is entered by a jump into its middle (0x804c3e7 -> 0x804c507);
 *       Ghidra lost the stack depth there, inverted the entry test and left
 *       "&stack0xffffffd4" (the scan loop never ran). Layout (VERIFIED, each
 *       offset is in the listing): bga+0x20 anim RC, freed if bga+0x24
 *       bga+0x28 sprites, if bga+0x2c bga+0x30 element Array
 *       bga+0x34 malloc'd block element: [0] type (1 = parallax/tiled), [0x10]
 *       count (0x40), [0x27] 0x9c block, [0x28]/[0x29] 0xa0 table + "owns
 *       entries" flag, [0x2a]/[0x2b] 0xa8 table + flag, [0x2c] 0xb0 table
 *       (always owns), [0x3b] 0xec animation. The function ends with a tail call
 *       to free(bga); the value left in EAX is not used by either caller
 *       (0x804c... BGRead error path, BGFree).
 */
uint32_t BGArrayFree(int bgs)
{
  int arr, i;
  int *e;

  if (bgs == 0)
    return 0;
  arr = *(int *)(bgs + 0x30);
  e = arr ? (int *)ArrayScanFirst(arr) : (int *)0;          /* 0x804c3e2 */
  while (e != 0) {
    if (e[0] == 1) {
      if (e[0x27] != 0)
        free((void *)e[0x27]);
      if (e[0x28] != 0) {
        if (e[0x29] != 0)
          for (i = 0; i < e[0x10]; i++)
            if (((int *)e[0x28])[i] != 0)
              free((void *)((int *)e[0x28])[i]);
        free((void *)e[0x28]);
      }
      if (e[0x2a] != 0) {
        if (e[0x2b] != 0)
          for (i = 0; i < e[0x10]; i++)
            if (((int *)e[0x2a])[i] != 0)
              free((void *)((int *)e[0x2a])[i]);
        free((void *)e[0x2a]);
      }
      if (e[0x2c] != 0) {
        for (i = 0; i < e[0x10]; i++)
          if (((int *)e[0x2c])[i] != 0)
            free((void *)((int *)e[0x2c])[i]);
        free((void *)e[0x2c]);
      }
    }
    AnimFree((void *)e[0x3b]);                                /* 0x804c4f7 */
    e = (int *)ArrayScanNext(arr);                            /* 0x804c502 */
  }
  ArrayFree(*(void **)(bgs + 0x30));
  if (*(int *)(bgs + 0x24) != 0)
    AnimRCFree(*(int **)(bgs + 0x20));
  if (*(int *)(bgs + 0x2c) != 0)
    SpriteArrayFree(*(int **)(bgs + 0x28));
  if (*(int *)(bgs + 0x34) != 0)
    free(*(void **)(bgs + 0x34));
  free((void *)bgs);                                      /* tail call 0x804c56d */
  return 0;
}

/* BGArrayAdd @ 0x0804c580, 323 bytes
 *
 * Adds a sprite-based element (normal or parallax) to a background set. It
 * copies the parameters (type, sprite, layer, start position, delta,
 * velocity, tiling, blend, window, id) and checks the sprite exists ("Sprite
 * doesn't exist: %i,%i"). Parallax elements are prepared with BGParalSetup.
 * Returns the slot, or -1.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         uint32_t
 *   arg6         uint32_t
 *   arg7         uint32_t
 *   arg8         uint32_t
 *   arg9         uint32_t
 *   arg10        uint32_t
 *   arg11        uint32_t
 *   group        int
 *   arg13        int
 *
 * Calls: SpriteArrayGetNum, SpriteArrayAccess, ArrayAdd
 * C library: sprintf
 * Called by: BGArrayReadTP
 * Messages:
 *   "Sprite doesn\'t exist: %i,%i"
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x120 bytes,
 *       13 variables), because their address is taken.
 */
int BGArrayAdd(int arg1,uint32_t arg2,int arg3,uint32_t arg4,uint32_t arg5,
              uint32_t arg6,uint32_t arg7,uint32_t arg8,uint32_t arg9,
              uint32_t arg10,uint32_t arg11,int group,int arg13)

{
  int index;
  uint32_t *sprite;
  int *pi3;
  unsigned char frame[0x120] __attribute__((aligned(16)));
#define stk_11c (*(int (*)[7])(frame + 0x4))
#define stk_100 (*(uint32_t *)(frame + 0x20))
#define stk_fc (*(uint32_t *)(frame + 0x24))
#define stk_e0 (*(uint32_t *)(frame + 0x40))
#define stk_dc (*(uint32_t *)(frame + 0x44))
#define stk_ac (*(uint32_t *)(frame + 0x74))
#define stk_a8 (*(uint32_t *)(frame + 0x78))
#define stk_a4 (*(uint32_t *)(frame + 0x7c))
#define stk_a0 (*(uint32_t *)(frame + 0x80))
#define stk_98 (*(uint32_t *)(frame + 0x88))
#define stk_64 (*(uint32_t *)(frame + 0xbc))
#define stk_60 (*(uint32_t *)(frame + 0xc0))
#define stk_28 (*(int *)(frame + 0xf8))
  
  if (arg3 == 3) {
    index = -1;
  }
  else {
    pi3 = stk_11c;
    for (index = 0x40; index != 0; index = index + -1) {
      *pi3 = 0;
      pi3 = pi3 + 1;
    }
    stk_11c[0] = arg3;
    stk_11c[1] = arg4;
    stk_11c[2] = arg5;
    stk_100 = arg6;
    stk_fc = arg7;
    stk_ac = arg8;
    stk_a8 = arg9;
    stk_a4 = arg10;
    stk_a0 = arg11;
    stk_98 = 1;
    if (arg3 != 10) {
      index = SpriteArrayGetNum(*(int **)(arg1 + 0x28),group,arg13);
      if (index == -1) {
        sprintf((char *)ErrorMessage,"Sprite doesn\'t exist: %i,%i",group,arg13);
        return -1;
      }
      stk_28 = index;
      sprite = (uint32_t *)SpriteArrayAccess(*(int **)(arg1 + 0x28),index);
      stk_e0 = *sprite;
      index = SpriteArrayAccess(*(int **)(arg1 + 0x28),index);
      stk_dc = *(uint32_t *)(index + 4);
    }
    stk_64 = 1;
    stk_60 = 1;
    index = ArrayAdd(*(int *)(arg1 + 0x30),stk_11c,0,arg2);
  }
  return index;
}
#undef stk_11c
#undef stk_100
#undef stk_fc
#undef stk_e0
#undef stk_dc
#undef stk_ac
#undef stk_a8
#undef stk_a4
#undef stk_a0
#undef stk_98
#undef stk_64
#undef stk_60
#undef stk_28

/* BGArrayAddAnim @ 0x0804c6d0, 223 bytes
 *
 * Adds an animated element: creates an animation instance on action `action`
 * of the set's AnimRC and stores the element with its parameters. Returns
 * the slot, or -1 ("Error adding anim for ...").
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *   arg6         uint32_t
 *   arg7         int
 *
 * Calls: AnimNew, AnimChangeAction, ArrayAdd
 * Called by: BGArrayReadTP
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x120 bytes,
 *       8 variables), because their address is taken.
 */
int BGArrayAddAnim(int arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,
                  uint32_t arg5,uint32_t arg6,int arg7)

{
  int index;
  uint32_t *pu2;
  unsigned char frame[0x120] __attribute__((aligned(16)));
#define stk_11c (*(uint32_t (*)[7])(frame + 0x4))
#define stk_100 (*(uint32_t *)(frame + 0x20))
#define stk_fc (*(uint32_t *)(frame + 0x24))
#define stk_98 (*(uint32_t *)(frame + 0x88))
#define stk_64 (*(uint32_t *)(frame + 0xbc))
#define stk_60 (*(uint32_t *)(frame + 0xc0))
#define anim (*(int **)(frame + 0xf0))
#define stk_2c (*(int *)(frame + 0xf4))
  
  pu2 = stk_11c;
  for (index = 0x40; index != 0; index = index + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  stk_11c[1] = arg3;
  stk_11c[0] = 3;
  stk_11c[2] = arg4;
  stk_100 = arg5;
  stk_fc = arg6;
  stk_98 = 1;
  anim = AnimNew(*(uint32_t *)(arg1 + 0x20),*(uint32_t *)(arg1 + 0x28));
  if ((anim != (int *)0x0) && (index = AnimChangeAction(anim,0,arg7), index != 0)) {
    stk_2c = arg7;
    stk_64 = 1;
    stk_60 = 1;
    index = ArrayAdd(*(int *)(arg1 + 0x30),stk_11c,0,arg2);
    return index;
  }
  return -1;
}
#undef stk_11c
#undef stk_100
#undef stk_fc
#undef stk_98
#undef stk_64
#undef stk_60
#undef anim
#undef stk_2c

/* BGArraySetViewScale @ 0x0804c7b0, 50 bytes
 *
 * Sets the camera zoom factor of every element.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArraySetViewScale(int arg1,uint32_t arg2)

{
  int array;
  int item;
  
  array = *(int *)(arg1 + 0x30);
  item = ArrayScanFirst(array);
  while (item != 0) {
    *(uint32_t *)(item + 0x84) = arg2;
    item = ArrayScanNext(array);
  }
  return;
}

/* BGArrayMove @ 0x0804c7f0, 31 bytes
 *
 * Moves the camera of a background set to (x, y) (BGArrayMoveOffset with no
 * extra offset).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *   arg3         float
 *
 * Calls: BGArrayMoveOffset
 * Called by: CharacterSelectScreenDraw, KeyConfigScreen, ModeSelect,
 *            OptionsScreen, SiSceneUpdate, VersusScreen
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: Returns nothing (the original left only stale register values).
 */
void BGArrayMove(int *arg1,float arg2,float arg3)

{
  uint32_t stale_EAX;
  
  BGArrayMoveOffset(arg1,arg2,arg3,0,0);
  return;
}

/* BGArrayMoveOffset @ 0x0804c810, 489 bytes
 *
 * Sets the camera position of a background set and recomputes every
 * element's screen position. Each element moves by its "delta" (parallax
 * factor) times the camera offset, plus its own velocity, sine motion and
 * position link. Parallax elements also get their top and bottom widths for
 * the floor perspective.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *   arg3         float
 *   arg4         int
 *   arg5         int
 *
 * Calls: ArrayScanFirst, roundfloat, ArrayScanNext
 * C library: fsin
 * Called by: BGArrayMove, GameBGDraw
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void BGArrayMoveOffset(int *arg1,float arg2,float arg3,int arg4,int arg5)

{
  int array;
  int *item;
  int i3;
  float80 l4;
  float80 l5;
  float stk_20;
  float stk_1c;
  
  array = arg1[0xc];
  stk_20 = 0.0;
  stk_1c = 0.0;
  *arg1 = BITS_F2I(int, arg2);
  arg1[1] = BITS_F2I(int, arg3);
  item = (int *)ArrayScanFirst(array);
  if (item != (int *)0x0) {
    do {
      l5 = (float80)0;
      l4 = l5;
      if ((float80)BITS_I2F(item[0x37]) != l5) {
        l4 = ((float80)BITS_I2F(item[0x39]) / (float80)BITS_I2F(item[0x37])) *
                (float80)((double)3.14159);
        l4 = (float80)fsin(l4 + l4);
        l4 = (float80)(float)(l4 * (float80)BITS_I2F(item[0x35]));
      }
      if ((float80)BITS_I2F(item[0x38]) != l5) {
        l5 = ((float80)BITS_I2F(item[0x3a]) / (float80)BITS_I2F(item[0x38])) *
                (float80)((double)3.14159);
        l5 = (float80)fsin(l5 + l5);
        l5 = (float80)(float)(l5 * (float80)BITS_I2F(item[0x36]));
      }
      if (item[0x34] == 0) {
        i3 = arg1[7];
        l4 = (float80)BITS_I2F(item[9]) * (float80)i3 +
                (float80)item[1] + (float80)BITS_I2F(item[7]) * (float80)arg2 + l4;
        item[5] = BITS_F2I(int, (float)l4);
        stk_1c = (float)l4;
        l5 = (float80)BITS_I2F(item[8]) * (float80)arg3 + (float80)item[2] +
                (float80)BITS_I2F(item[10]) * (float80)i3 + l5;
        item[6] = BITS_F2I(int, (float)l5);
        stk_20 = (float)l5;
      }
      else {
        item[5] = BITS_F2I(int, (float)((float80)item[1] + l4 + (float80)stk_1c));
        item[6] = BITS_F2I(int, (float)((float80)item[2] + l5 + (float80)stk_20));
      }
      item[5] = BITS_F2I(int, (BITS_I2F(item[0x30]) + (float)arg4 + BITS_I2F(item[5])));
      item[6] = BITS_F2I(int, (BITS_I2F(item[0x31]) + (float)arg5 + BITS_I2F(item[6])));
      if (item[0x13] != 0) {
        i3 = roundfloat(BITS_I2F(item[0x18]) * arg2);
        item[0x1a] = i3;
        i3 = roundfloat(BITS_I2F(item[0x19]) * arg3);
        item[0x1b] = i3;
      }
      if (*item == 1) {
        item[0x24] = (int)X87_FIST32(BITS_I2F(item[0x25]) * arg3 + (float80)item[0x23]);
      }
      i3 = roundfloat(BITS_I2F(item[5]));
      item[3] = i3;
      i3 = roundfloat(BITS_I2F(item[6]));
      item[4] = i3;
      item = (int *)ArrayScanNext(array);
    } while (item != (int *)0x0);
  }
  return;
}

/* BGArrayDraw @ 0x0804ca00, 92 bytes
 *
 * Clears the buffer with the clear colour (if set) and draws every element.
 * Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: W_Cls, ArrayScanFirst, BGDraw, ArrayScanNext
 * C library: makecol
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayDraw(int arg1)

{
  int array;
  uint32_t u2;
  int *item;
  
  array = *(int *)(arg1 + 0x30);
  if (*(int *)(arg1 + 0x48) != -1) {
    u2 = makecol(*(uint32_t *)(arg1 + 0x48),*(int *)(arg1 + 0x4c),
                    *(int *)(arg1 + 0x50));
    W_Cls(u2);
  }
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    BGDraw(arg1,item);
    item = (int *)ArrayScanNext(array);
  }
  return;
}

/* BGArrayDrawLayer @ 0x0804ca60, 107 bytes
 *
 * Draws the elements of layer `layer` (0 = background, 1 = foreground),
 * clearing the buffer with the clear colour first when drawing layer 0 and a
 * clear colour is set.
 *
 * Parameters:
 *   bgs          int
 *   layer        int
 *
 * Calls: W_Cls, ArrayScanFirst, BGDraw, ArrayScanNext
 * C library: makecol
 * Called by: CharacterSelectScreenDraw, GameBGDraw, GameFGDraw,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, SiSceneDraw,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayDrawLayer(int bgs,int layer)

{
  int array;
  uint32_t u2;
  int *item;
  
  array = *(int *)(bgs + 0x30);
  if ((*(int *)(bgs + 0x48) != -1) && (layer == 0)) {
    u2 = makecol(*(uint32_t *)(bgs + 0x48),*(int *)(bgs + 0x4c),
                    *(int *)(bgs + 0x50));
    W_Cls(u2);
  }
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    if (item[0x20] == layer) {
      BGDraw(bgs,item);
    }
    item = (int *)ArrayScanNext(array);
  }
  return;
}

/* BGArrayUpdate @ 0x0804cad0, 222 bytes
 *
 * Advances a background set by one tick: runs the background controllers
 * (BGArrayCtrlUpdate), moves elements by their velocities and advances
 * animated elements.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: BGArrayCtrlUpdate, ArrayScanFirst, AnimUpdate, ArrayScanNext
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, SiSceneUpdate,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayUpdate(int arg1)

{
  int array;
  int *item;
  
  array = *(int *)(arg1 + 0x30);
  *(uint32_t *)(arg1 + 0x48) = *(uint32_t *)(arg1 + 0x3c);
  *(uint32_t *)(arg1 + 0x4c) = *(uint32_t *)(arg1 + 0x40);
  *(uint32_t *)(arg1 + 0x50) = *(uint32_t *)(arg1 + 0x44);
  BGArrayCtrlUpdate(arg1);
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    if (item[0x2e] != 0) {
      if (*item == 3) {
        AnimUpdate((uint32_t *)item[0x3b]);
      }
      if (BITS_I2F(item[0x37]) != 0.0) {
        item[0x39] = BITS_F2I(int, (BITS_I2F(item[0x39]) + 1.0));
      }
      if (BITS_I2F(item[0x38]) != 0.0) {
        item[0x3a] = BITS_F2I(int, (BITS_I2F(item[0x3a]) + 1.0));
      }
    }
    item[0x30] = BITS_F2I(int, (BITS_I2F(item[0x30]) + BITS_I2F(item[0x32])));
    item[0x31] = BITS_F2I(int, (BITS_I2F(item[0x31]) + BITS_I2F(item[0x33])));
    item = (int *)ArrayScanNext(array);
  }
  *(int *)(arg1 + 0x1c) = *(int *)(arg1 + 0x1c) + 1;
  return;
}

/* BGArrayCtrlUpdate @ 0x0804cbb0, 707 bytes
 *
 * Runs the background controllers. Each controller whose time window
 * contains the controller clock acts on the elements whose id it lists: show
 * or hide, enable or disable, set or add velocity or position, change
 * animation, or start sine motion. The clocks wrap at their loop time.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArrayScanFirst, AnimChangeAction, AnimResetAction, ArrayScanNext
 * Called by: BGArrayUpdate
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayCtrlUpdate(int arg1)

{
  int *pi1;
  int array;
  int *item;
  int *pi4;
  int i5;
  int i6;
  bool b7;
  
  array = *(int *)(arg1 + 0x30);
  i5 = *(int *)(arg1 + 0x34);
  if ((i5 != 0) && (i6 = 0, 0 < *(int *)(arg1 + 0x38))) {
    while( true ) {
      pi1 = (int *)(i5 + i6 * 0x54);
      i5 = pi1[0x14];
      if ((((pi1[0xd] <= i5) && (i5 <= pi1[0xe])) ||
          ((pi1[0xd] == -1 && (*(int *)(arg1 + 0x1c) == 0)))) && (pi1[0xc] < 100)) {
        item = (int *)ArrayScanFirst(array);
        while (item != (int *)0x0) {
          b7 = *pi1 == -1;
          if (!b7) {
            pi4 = pi1;
            do {
              if (item[0x2d] == *pi4) {
                b7 = true;
              }
              pi4 = pi4 + 1;
            } while (*pi4 != -1);
          }
          if (b7) {
            switch(pi1[0xc]) {
            case 1:
              item[0x2f] = pi1[0x10];
              break;
            case 2:
              item[0x2e] = pi1[0x10];
              break;
            case 3:
              if (BITS_I2F(pi1[0x11]) != -32760.0) {
                item[0x30] = pi1[0x11];
              }
              if (BITS_I2F(pi1[0x12]) != -32760.0) {
                item[0x31] = pi1[0x12];
              }
              break;
            case 4:
              if (BITS_I2F(pi1[0x11]) != -32760.0) {
                item[0x32] = pi1[0x11];
              }
              if (BITS_I2F(pi1[0x12]) != -32760.0) {
                item[0x33] = pi1[0x12];
              }
              break;
            case 5:
              if (BITS_I2F(pi1[0x11]) != -32760.0) {
                item[0x30] = BITS_F2I(int, (BITS_I2F(item[0x30]) + BITS_I2F(pi1[0x11])));
              }
              if (BITS_I2F(pi1[0x12]) != -32760.0) {
                item[0x31] = BITS_F2I(int, (BITS_I2F(item[0x31]) + BITS_I2F(pi1[0x12])));
              }
              break;
            case 6:
              if (BITS_I2F(pi1[0x11]) != -32760.0) {
                item[0x32] = BITS_F2I(int, (BITS_I2F(item[0x32]) + BITS_I2F(pi1[0x11])));
              }
              if (BITS_I2F(pi1[0x12]) != -32760.0) {
                item[0x33] = BITS_F2I(int, (BITS_I2F(item[0x33]) + BITS_I2F(pi1[0x12])));
              }
              break;
            case 8:
              if ((*item == 3) && (item[0x3b] != 0)) {
                AnimChangeAction((int *)item[0x3b],0,pi1[0x10]);
                AnimResetAction((int *)item[0x3b]);
              }
              break;
            case 0xb:
              item[0x35] = pi1[0x11];
              item[0x37] = pi1[0x12];
              item[0x39] = pi1[0x13];
              break;
            case 0xc:
              item[0x36] = pi1[0x11];
              item[0x38] = pi1[0x12];
              item[0x3a] = pi1[0x13];
            }
          }
          item = (int *)ArrayScanNext(array);
        }
        i5 = pi1[0x14];
      }
      pi1[0x14] = i5 + 1;
      if ((pi1[0xf] <= i5 + 1) && (pi1[0xf] != -1)) {
        pi1[0x14] = 0;
      }
      i6 = i6 + 1;
      if (*(int *)(arg1 + 0x38) <= i6) break;
      i5 = *(int *)(arg1 + 0x34);
    }
  }
  return;
}

/* BGArrayReset @ 0x0804ce80, 236 bytes
 *
 * Resets a background set to its initial state: clear colour, controller
 * clocks, element positions, velocities and animations. Called at the start
 * of each round and screen.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArrayScanFirst, AnimChangeAction, AnimResetAction, ArrayScanNext
 * Called by: CharacterSelectScreen, GameMatchReset, GameRoundReset,
 *            ModeSelect, OptionsScreen, SiSceneUpdate, VersusScreen
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGArrayReset(int arg1)

{
  int array;
  uint32_t *pu2;
  int *item;
  int i2;
  
  i2 = 0;
  array = *(int *)(arg1 + 0x30);
  *(uint32_t *)(arg1 + 0x48) = *(uint32_t *)(arg1 + 0x3c);
  *(uint32_t *)(arg1 + 0x4c) = *(uint32_t *)(arg1 + 0x40);
  *(uint32_t *)(arg1 + 0x50) = *(uint32_t *)(arg1 + 0x44);
  if (0 < *(int *)(arg1 + 0x38)) {
    pu2 = (uint32_t *)(*(int *)(arg1 + 0x34) + 0x50);
    do {
      *pu2 = 0;
      pu2 = pu2 + 0x15;
      i2 = i2 + 1;
    } while (i2 < *(int *)(arg1 + 0x38));
  }
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    if (*item == 3) {
      AnimChangeAction((int *)item[0x3b],0,item[0x3c]);
      AnimResetAction((int *)item[0x3b]);
    }
    item[0x2f] = 1;
    item[0x2e] = 1;
    item[0x33] = 0;
    item[0x32] = 0;
    item[0x31] = 0;
    item[0x30] = 0;
    item[0x3a] = 0;
    item[0x39] = 0;
    item = (int *)ArrayScanNext(array);
  }
  *(uint32_t *)(arg1 + 0x1c) = 0;
  return;
}

/* BGAccess @ 0x0804cf70, 27 bytes
 *
 * Returns the element in slot (group, index) of a background set.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: ArrayAccessGrpItem
 * Called by: BGArrayReadTP
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
uint32_t BGAccess(int arg1,int arg2)

{
  uint32_t item;
  
  item = ArrayAccessGrpItem(*(int *)(arg1 + 0x30),0,arg2);
  return item;
}

/* BGAccessID @ 0x0804cf90, 57 bytes
 *
 * Returns the first element whose "id" is `id`, or NULL.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: GameBGDraw
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
int BGAccessID(int arg1,int arg2)

{
  int item;
  
  item = ArrayScanFirst(*(int *)(arg1 + 0x30));
  while( true ) {
    if (item == 0) {
      return 0;
    }
    if (*(int *)(item + 0xb4) == arg2) break;
    item = ArrayScanNext(*(int *)(arg1 + 0x30));
  }
  return item;
}

/* BGParalSetup @ 0x0804cfd0, 530 bytes
 *
 * Prepares a parallax element: records its sprite, the top and bottom
 * widths, and the scale steps used to draw it row by row as a perspective
 * floor.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t *
 *   arg3         int
 *   arg4         int
 *   arg5         uint32_t
 *   arg6         uint32_t
 *   arg7         uint32_t
 *   arg8         uint32_t
 *
 * Calls: SpriteArrayAccess, ecalloc
 * Called by: BGArrayReadTP
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 1 assignments,
 *       0 calls, 0 returns
 */
uint32_t
BGParalSetup(int arg1,uint32_t *arg2,int arg3,int arg4,uint32_t arg5,
            uint32_t arg6,uint32_t arg7,uint32_t arg8)

{
  size_t s1;
  int *sprite;
  int mem;
  int mem2;
  int i5;
  int i2;
  int stk_30;
  int stk_2c;
  
  sprite = (int *)SpriteArrayAccess(*(int **)(arg1 + 0x28),arg2[0x3d]);
  s1 = sprite[4];
  if (sprite[7] == 0) {
    *arg2 = 1;
    arg2[0xf] = arg3;
    arg2[0x23] = arg5;
    arg2[0xb] = arg7 & 1;
    arg2[0xc] = 0;
    arg2[0x25] = arg6;
    arg2[0x22] = arg8;
    arg2[0x26] = BITS_F2I(uint32_t, (float)arg4 / (float)arg3);
    mem = ecalloc(arg2[0x10],4);
    arg2[0x27] = mem;
    if (mem != 0) {
      mem = ecalloc(arg2[0x10],4);
      arg2[0x28] = mem;
      if (mem != 0) {
        i2 = 0;
        mem = sprite[9];
        mem2 = arg2[0x10];
        if (0 < mem2) {
          do {
            if (arg2[0x22] == 0) {
              i5 = arg2[0x27];
              mem2 = *sprite;
            }
            else {
              i5 = arg2[0x27];
              mem2 = (int)X87_FIST32(((float)(arg4 - arg3) * (float80)i2) / (float)(mem2 + -1) +
                                 (float)arg3);
            }
            *(int *)(i5 + i2 * 4) = mem2;
            if (arg2[0x22] == 0) {
              *(int *)(arg2[0x28] + i2 * 4) = mem + *(int *)(sprite[0xb] + i2 * 4);
              arg2[0x29] = 0;
            }
            else {
              mem2 = ecalloc(*(int *)(arg2[0x27] + i2 * 4) + 4,s1);
              *(int *)(arg2[0x28] + i2 * 4) = mem2;
              if (mem2 == 0) {
                return 0;
              }
              stk_2c = arg2[0x27];
              mem2 = 0;
              if (0 < *(int *)(stk_2c + i2 * 4)) {
                do {
                  stk_30 = stk_2c;
                  if (s1 == 8) {
                    *(uint8_t *)(mem2 + *(int *)(arg2[0x28] + i2 * 4)) =
                         *(uint8_t *)
                          ((*sprite * mem2) / *(int *)(stk_2c + i2 * 4) +
                           *(int *)(sprite[0xb] + i2 * 4) + mem);
                    stk_30 = arg2[0x27];
                  }
                  mem2 = mem2 + 1;
                  stk_2c = stk_30;
                } while (mem2 < *(int *)(stk_30 + i2 * 4));
              }
              arg2[0x29] = 1;
            }
            i2 = i2 + 1;
            mem2 = arg2[0x10];
          } while (i2 < mem2);
        }
        return 1;
      }
    }
  }
  return 0;
}

/* BGDraw @ 0x0804d1f0, 798 bytes
 *
 * Draws one background element at its current position relative to the
 * camera, with tiling, window clipping and blend mode. Normal sprites go to
 * BGNormalDrawTile, animated ones to BGAnimDrawTile and parallax ones to
 * BGParalDrawScale. Invisible or disabled elements are skipped.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *
 * Calls: roundfloat, W_Define, BGParalDrawScale, W_PutSpriteTransSub,
 *        W_ScaleSpriteTransAdd_S, W_ScaleSpriteTransAdd_B_S,
 *        W_ScaleSprite_S, W_ScaleSpriteFlat_S, BGNormalDrawTile,
 *        AnimDrawScale, BGAnimDrawTile
 * Called by: BGArrayDraw, BGArrayDrawLayer
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 15 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 */
void BGDraw(int arg1,int *arg2)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  
  i5 = W_y1;
  i4 = W_x2;
  i3 = W_x1;
  i2 = W_y2;
  i8 = V_Width / 2;
  i6 = roundfloat((float80)arg2[0x21] * BITS_I2F(arg2[5]));
  i7 = roundfloat((float80)arg2[0x21] * BITS_I2F(arg2[6]));
  if (arg2[0x2e] == 0) {
    return;
  }
  if (arg2[0x2f] == 0) {
    return;
  }
  if (arg2[0x13] != 0) {
    W_Define((arg2[0x14] - arg2[0x1a]) * arg2[0x21],
             (arg2[0x16] - arg2[0x1b]) * arg2[0x21],
             (arg2[0x15] - arg2[0x1a]) * arg2[0x21],
             (arg2[0x17] - arg2[0x1b]) * arg2[0x21]);
  }
  i1 = *arg2;
  if (i1 == 1) {
    BGParalDrawScale(arg1,(int)arg2,arg2[0x24]);
  }
  else if (i1 < 2) {
    if (i1 == 0) {
      if ((arg2[0xb] == 0) && (arg2[0xc] == 0)) {
        i1 = arg2[0x1c];
        if (i1 == 2) {
          W_PutSpriteTransSub(*(int **)(arg1 + 0x28),arg2[0x3d],i8 + i6,i7);
        }
        else {
          if (i1 < 3) {
            if (i1 == 1) {
              W_ScaleSpriteTransAdd_S
                        (*(int **)(arg1 + 0x28),arg2[0x3d],(float)(i8 + i6),(float80)i7
                         ,(float80)arg2[0x21],(float80)arg2[0x21]);
              goto L_0804d4ea;
            }
          }
          else if (i1 == 3) {
            W_ScaleSpriteTransAdd_B_S
                      (*(int **)(arg1 + 0x28),arg2[0x3d],(float)(i8 + i6),(float80)i7,
                       (float80)arg2[0x21],(float80)arg2[0x21],arg2[0x1d],arg2[0x1e]);
            goto L_0804d4ea;
          }
          if (arg2[0x1f] == 1) {
            W_ScaleSprite_S(*(int **)(arg1 + 0x28),arg2[0x3d],(float)(i8 + i6),
                            (float80)i7,(float80)arg2[0x21],(float80)arg2[0x21]);
          }
          else {
            W_ScaleSpriteFlat_S(*(int **)(arg1 + 0x28),arg2[0x3d],i8 + i6,i7,
                                (float80)arg2[0x21],(float80)arg2[0x21]);
          }
        }
      }
      else {
        BGNormalDrawTile(arg1,(int)arg2);
      }
    }
  }
  else if (i1 == 3) {
    if ((arg2[0xb] == 0) && (arg2[0xc] == 0)) {
      AnimDrawScale((uint32_t *)arg2[0x3b],i8 + i6,i7,(float80)arg2[0x21],
                    (float80)arg2[0x21]);
    }
    else {
      BGAnimDrawTile(arg1,(int)arg2);
    }
  }
L_0804d4ea:
  W_Define(i3,i5,i4,i2);
  return;
}

/* BGNormalDrawTile @ 0x0804d510, 890 bytes
 *
 * Draws a sprite element tiled across the window: repeats it horizontally
 * and/or vertically with the tile spacing, choosing the scaled, opaque
 * (masked off), additive or subtractive blitter.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransSub, W_ScaleSpriteTransAdd_S,
 *        W_ScaleSprite_S, W_ScaleSpriteFlat_S, W_ScaleSpriteTransAdd_B_S
 * Called by: BGDraw
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 */
void BGNormalDrawTile(int arg1,int arg2)

{
  int sprite;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int stk_34;
  int stk_30;
  int stk_2c;
  int stk_28;
  
  sprite = SpriteArrayAccess(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
  i3 = *(int *)(arg2 + 0x84);
  stk_30 = 0;
  stk_34 = 0;
  i5 = V_Width / 2 + *(int *)(arg2 + 0xc) * i3;
  i4 = (*(int *)(arg2 + 0x34) + *(int *)(arg2 + 0x3c)) * i3;
  i2 = (*(int *)(arg2 + 0x34) + *(int *)(arg2 + 0x40)) * i3;
  i8 = *(int *)(arg2 + 0x10) * i3;
  if (sprite != 0) {
    stk_30 = *(int *)(sprite + 8) * i3;
    stk_34 = i3 * *(int *)(sprite + 0xc);
  }
  stk_28 = *(int *)(arg2 + 0x2c);
  stk_2c = *(int *)(arg2 + 0x30);
  i3 = stk_2c;
  if (stk_28 == 1) {
    *(int *)(arg2 + 0xc) = *(int *)(arg2 + 0xc) - stk_30;
    if ((i5 < -i4) || (0 < i5)) {
      i5 = i5 % i4;
    }
    if (0 < i5) {
      i5 = i5 - i4;
    }
    *(int *)(arg2 + 0xc) = *(int *)(arg2 + 0xc) + stk_30;
    stk_28 = -1;
    i3 = *(int *)(arg2 + 0x30);
  }
  if (stk_28 == 0) {
    stk_28 = 1;
  }
  if (stk_2c == 0) {
    stk_2c = 1;
  }
  if (i3 == 1) {
    i8 = i8 - stk_34;
    if ((i8 < -i2) || (0 < i8)) {
      i8 = i8 % i2;
    }
    if (0 < i8) {
      i8 = i8 - i2;
    }
    i8 = i8 + stk_34;
    stk_2c = -1;
  }
  i3 = V_Height;
  sprite = V_Width;
  if (i8 - stk_34 < V_Height) {
    do {
      if (stk_2c == 0) {
        return;
      }
      i6 = i5;
      i7 = stk_28;
      if (i5 - stk_30 < sprite) {
        do {
          if (i7 == 0) break;
          i3 = *(int *)(arg2 + 0x70);
          if (i3 == 2) {
            W_PutSpriteTransSub(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4),i6,i8);
          }
          else if (i3 < 3) {
            if (i3 == 1) {
              W_ScaleSpriteTransAdd_S
                        (*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4),(float80)i6,
                         (float80)i8,(float80)*(int *)(arg2 + 0x84),
                         (float80)*(int *)(arg2 + 0x84));
            }
            else {
L_0804d7b0:
              if (*(int *)(arg2 + 0x7c) == 1) {
                W_ScaleSprite_S(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4),(float80)i6,
                                (float80)i8,(float80)*(int *)(arg2 + 0x84),
                                (float80)*(int *)(arg2 + 0x84));
              }
              else {
                W_ScaleSpriteFlat_S(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4),i6,i8,
                                    (float80)*(int *)(arg2 + 0x84),(float80)*(int *)(arg2 + 0x84))
                ;
              }
            }
          }
          else {
            if (i3 != 3) goto L_0804d7b0;
            W_ScaleSpriteTransAdd_B_S
                      (*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4),(float80)i6,(float80)i8,
                       (float80)*(int *)(arg2 + 0x84),(float80)*(int *)(arg2 + 0x84),
                       *(int *)(arg2 + 0x74),*(int *)(arg2 + 0x78));
          }
          i6 = i6 + i4;
          if (0 < i7) {
            i7 = i7 + -1;
          }
          sprite = V_Width;
          i3 = V_Height;
        } while (i6 - stk_30 < V_Width);
      }
      i8 = i8 + i2;
      if (0 < stk_2c) {
        stk_2c = stk_2c + -1;
      }
    } while (i8 - stk_34 < i3);
  }
  return;
}

/* BGAnimDrawTile @ 0x0804d890, 361 bytes
 *
 * Draws an animated element, tiled like BGNormalDrawTile, through
 * AnimDrawScale.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *
 * Calls: AnimDrawScale
 * Called by: BGDraw
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void BGAnimDrawTile(uint32_t arg1,int arg2)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int stk_24;
  int stk_20;
  int stk_18;
  
  i5 = *(int *)(arg2 + 0x84);
  stk_24 = V_Width;
  i2 = V_Width / 2 + *(int *)(arg2 + 0xc) * i5;
  stk_18 = *(int *)(arg2 + 0x34) * i5;
  i6 = *(int *)(arg2 + 0x10) * i5;
  if (stk_18 == 0) {
    stk_18 = i5;
  }
  stk_20 = *(int *)(arg2 + 0x2c);
  i5 = *(int *)(arg2 + 0x30);
  if (stk_20 == 1) {
    if ((i2 < -stk_18) || (0 < i2)) {
      i2 = i2 % stk_18;
    }
    if (0 < i2) {
      i2 = i2 - stk_18;
    }
    stk_20 = -1;
  }
  if (stk_20 == 0) {
    stk_20 = 1;
  }
  i4 = i5;
  if (i5 == 0) {
    i4 = 1;
  }
  i1 = V_Height;
  if (i5 == 1) {
    if ((i6 < -stk_18) || (0 < i6)) {
      i6 = i6 % stk_18;
    }
    if (0 < i6) {
      i6 = i6 - stk_18;
    }
    i4 = -1;
  }
  do {
    if ((i1 <= i6) || (i4 == 0)) {
      return;
    }
    i5 = i2;
    i3 = stk_20;
    if (i2 < stk_24) {
      do {
        if (i3 == 0) break;
        AnimDrawScale(*(uint32_t **)(arg2 + 0xec),i5,i6,(float80)*(int *)(arg2 + 0x84),
                      (float80)*(int *)(arg2 + 0x84));
        i5 = i5 + stk_18;
        if (0 < i3) {
          i3 = i3 + -1;
        }
        stk_24 = V_Width;
        i1 = V_Height;
      } while (i5 < V_Width);
    }
    i6 = i6 + stk_18;
    if (0 < i4) {
      i4 = i4 + -1;
    }
  } while( true );
}

/* BGParalDraw @ 0x0804da00, 27 bytes
 *
 * BGParalDrawScale at scale 1. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGParalDraw(int arg1,int arg2)

{
  BGParalDrawScale(arg1,arg2,1000);
  return;
}

/* BGParalDrawScale @ 0x0804da20, 144 bytes
 *
 * Draws a parallax element: picks the pixel loop for the buffer depth and
 * masking (BGParalDraw8to16 or BGParalDraw8to16Flat; the 2X and 16-bit
 * variants are empty).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: SpriteArrayAccess, BGParalDraw8to16_2X, BGParalDraw8to16,
 *        BGParalDraw8to16Flat2X, BGParalDraw8to16Flat, BGParalDraw16
 * Called by: BGDraw, BGParalDraw
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGParalDrawScale(int arg1,int arg2,int arg3)

{
  int sprite;
  
  sprite = SpriteArrayAccess(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
  if (V_ColDepth - 0xfU < 2) {
    if (*(int *)(sprite + 0x10) == 8) {
      if (*(int *)(arg2 + 0x7c) == 1) {
        if (*(int *)(arg2 + 0x84) == 2) {
          BGParalDraw8to16_2X();
        }
        else {
          BGParalDraw8to16(arg1,arg2,arg3);
        }
      }
      else if (*(int *)(arg2 + 0x84) == 2) {
        BGParalDraw8to16Flat2X();
      }
      else {
        BGParalDraw8to16Flat(arg1,arg2,arg3);
      }
    }
    else {
      BGParalDraw16();
    }
  }
  return;
}

/* BGParalDraw8to16 @ 0x0804dab0, 1276 bytes
 *
 * Pixel loop for parallax floors: draws the 8-bit sprite onto a 16-bit
 * buffer one row at a time, stretching each row from the top width to the
 * bottom width. Colour 0 is transparent.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: SpriteArrayAccess, roundfloat, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess,
 *        SpriteDecompUnlockData
 * Called by: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void BGParalDraw8to16(int arg1,int arg2,int arg3)

{
  float80 f1;
  int i2;
  int i3;
  int i4;
  int sprite;
  int sprite2;
  int i7;
  int i8;
  int i9;
  int *sprite3;
  int i11;
  int i12;
  int i13;
  uint8_t *pb14;
  uint16_t *pu15;
  int stk_60;
  int stk_5c;
  int stk_58;
  int stk_44;
  int stk_40;
  float stk_38;
  int stk_34;
  int stk_30;
  int stk_18;
  
  sprite = SpriteArrayAccess(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_38 = *(float *)(arg2 + 0x14);
  stk_40 = 500;
  stk_44 = 0;
  if ((sprite != 0) && (0 < arg3)) {
    if ((*(int *)(arg2 + 0x2c) != 0) &&
       ((stk_38 < (float)-*(int *)(arg2 + 0x3c) || (0.0 < stk_38)))) {
      stk_38 = (stk_38 - (float80)(int)X87_FIST32(stk_38)) +
                 (float)((int)X87_FIST32(stk_38) % *(int *)(arg2 + 0x3c));
      if (0.0 < stk_38) {
        stk_38 = stk_38 - (float80)*(int *)(arg2 + 0x3c);
      }
    }
    i7 = roundfloat(*(float *)(arg2 + 0x18) -
                       (float)((*(int *)(sprite + 0xc) * 1000) / arg3));
    i8 = SpriteDecompGetAndLockData(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
    if (i8 != 0) {
      i9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = SpriteArrayPalUpdateAndAccess(*(int *)(arg1 + 0x28),*(int *)(sprite + 0x30));
      i4 = W_y1;
      i3 = W_x2;
      i2 = W_x1;
      i8 = W_y2;
      stk_30 = 0;
      if ((i7 <= W_y2) && (i11 = *(int *)(arg2 + 0x40), 0 < i11)) {
        i12 = V_Width / 2;
        do {
          if (i4 <= i7 + stk_30) {
            if (*(int *)(arg2 + 0x88) == 0) {
              f1 = (((*(float *)(arg2 + 0x98) - 1.0) * (float)(stk_44 + 1)) / (float80)i11
                      + 1.0) * stk_38 + (float)(i12 - *(int *)(sprite + 8));
            }
            else {
              i11 = **(int **)(arg2 + 0x9c);
              f1 = ((float)(*(int **)(arg2 + 0x9c))[stk_44] *
                      (stk_38 - (float)(i11 / 2))) / (float80)i11 + (float80)i12;
            }
            stk_18 = (int)X87_FIST32(f1);
            if (*(int *)(arg2 + 0x2c) == 0) {
              stk_58 = *(int *)(arg2 + 0x9c);
            }
            else {
              stk_58 = *(int *)(arg2 + 0x9c);
              i11 = *(int *)(stk_58 + stk_44 * 4);
              if ((stk_18 < -i11) || (0 < stk_18)) {
                stk_18 = stk_18 % i11;
              }
              if (0 < stk_18) {
                stk_18 = stk_18 - *(int *)(stk_58 + stk_44 * 4);
              }
            }
            i13 = 0;
            i11 = stk_18 + *(int *)(stk_58 + stk_44 * 4) + -1;
            if (stk_18 < i2) {
              i13 = i2 - stk_18;
              stk_18 = i2;
            }
            if (i3 < i11) {
              i11 = i3;
            }
            stk_5c = *(int *)(sprite2 + 0x2c);
            stk_60 = *(int *)(arg2 + 0xa0);
            pu15 = (uint16_t *)
                      (i9 + *(int *)(stk_5c + (i7 + stk_30) * 4) + stk_18 * 2);
            pb14 = (uint8_t *)(i13 + *(int *)(stk_60 + stk_44 * 4));
            i13 = (i11 - stk_18) + 1;
            stk_34 = i3;
            if (*(int *)(arg2 + 0x2c) == 0) {
              stk_34 = i11;
            }
            if (stk_18 <= stk_34) {
              do {
                if (-1 < i13) {
                  stk_18 = stk_18 + i13;
                  if (i3 + 1 < stk_18) {
                    i13 = (i3 - stk_18) + 1 + i13;
                  }
                  if (i13 != 0) {
                    do {
                      if (*pb14 != 0) {
                        *pu15 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb14 * 2 + 0x5c);
                      }
                      pu15 = pu15 + 1;
                      pb14 = pb14 + 1;
                      i13 = i13 + -1;
                    } while (i13 != 0);
                    stk_58 = *(int *)(arg2 + 0x9c);
                    stk_5c = *(int *)(sprite2 + 0x2c);
                    stk_60 = *(int *)(arg2 + 0xa0);
                  }
                }
                pb14 = *(uint8_t **)(stk_60 + stk_44 * 4);
                i13 = *(int *)(stk_58 + stk_44 * 4);
                pu15 = (uint16_t *)
                          (i9 + *(int *)(stk_5c + (i7 + stk_30) * 4) + stk_18 * 2);
              } while (stk_18 <= stk_34);
            }
          }
          for (stk_40 = stk_40 + arg3; 999 < stk_40; stk_40 = stk_40 + -1000) {
            stk_44 = stk_44 + 1;
          }
          stk_30 = stk_30 + 1;
        } while ((i7 + stk_30 <= i8) &&
                (i11 = *(int *)(arg2 + 0x40), stk_44 < i11));
      }
      SpriteDecompUnlockData();
    }
  }
  return;
}

/* BGParalDraw8to16_2X @ 0x0804dfb0, 1 bytes
 *
 * Empty in this build.
 *
 * Called by: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGParalDraw8to16_2X(void)

{
  return;
}

/* BGParalDraw8to16Flat @ 0x0804dfc0, 1117 bytes
 *
 * BGParalDraw8to16 without transparency (mask = 0).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, roundfloat,
 *        SpriteDecompUnlockData
 * Called by: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void BGParalDraw8to16Flat(int arg1,int arg2,int arg3)

{
  float80 f1;
  float80 f2;
  uint8_t b3;
  int i4;
  int i5;
  int i6;
  int sprite;
  int sprite2;
  int i9;
  int i10;
  int *sprite3;
  int i12;
  int i13;
  int i14;
  int i15;
  uint16_t *pu16;
  uint8_t *pb17;
  int stk_64;
  int stk_60;
  int stk_4c;
  int stk_48;
  int stk_38;
  int stk_34;
  int stk_30;
  int stk_18;
  
  sprite = SpriteArrayAccess(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  f1 = *(float *)(arg2 + 0x14);
  stk_48 = 500;
  f2 = *(float *)(arg2 + 0x18);
  stk_4c = 0;
  if ((sprite != 0) && (0 < arg3)) {
    i4 = *(int *)(sprite + 0xc);
    i9 = SpriteDecompGetAndLockData(*(int **)(arg1 + 0x28),*(int *)(arg2 + 0xf4));
    if (i9 != 0) {
      i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = SpriteArrayPalUpdateAndAccess(*(int *)(arg1 + 0x28),*(int *)(sprite + 0x30));
      sprite3 = sprite3 + 0x17;
      i12 = roundfloat(f2 - (float)((i4 * 1000) / arg3));
      i6 = W_y1;
      i5 = W_x2;
      i9 = W_x1;
      i4 = W_y2;
      stk_30 = 0;
      if ((i12 <= W_y2) && (i14 = *(int *)(arg2 + 0x40), 0 < i14)) {
        i13 = V_Width / 2;
        do {
          if (i6 <= i12 + stk_30) {
            if (*(int *)(arg2 + 0x88) == 0) {
              f2 = (((*(float *)(arg2 + 0x98) - 1.0) * (float)(stk_4c + 1)) / (float80)i14
                      + 1.0) * f1 + (float)(i13 - *(int *)(sprite + 8));
            }
            else {
              i14 = **(int **)(arg2 + 0x9c);
              f2 = ((float)(*(int **)(arg2 + 0x9c))[stk_4c] * (f1 - (float)(i14 / 2)))
                      / (float80)i14 + (float80)i13;
            }
            stk_18 = (int)X87_FIST32(f2);
            if (*(int *)(arg2 + 0x2c) == 0) {
              stk_60 = *(int *)(arg2 + 0x9c);
            }
            else {
              stk_60 = *(int *)(arg2 + 0x9c);
              i14 = *(int *)(stk_60 + stk_4c * 4);
              if ((stk_18 < -i14) || (0 < stk_18)) {
                stk_18 = stk_18 % i14;
              }
              if (0 < stk_18) {
                stk_18 = stk_18 - *(int *)(stk_60 + stk_4c * 4);
              }
            }
            i14 = 0;
            stk_34 = stk_18 + *(int *)(stk_60 + stk_4c * 4) + -1;
            if (stk_18 < i9) {
              i14 = i9 - stk_18;
              stk_18 = i9;
            }
            if (i5 < stk_34) {
              stk_34 = i5;
            }
            stk_64 = *(int *)(sprite2 + 0x2c);
            pu16 = (uint16_t *)
                      (i10 + *(int *)(stk_64 + (i12 + stk_30) * 4) + stk_18 * 2);
            i15 = *(int *)(arg2 + 0xa0);
            pb17 = (uint8_t *)(*(int *)(i15 + stk_4c * 4) + i14);
            i14 = (stk_34 - stk_18) + 1;
            stk_38 = i5;
            if (*(int *)(arg2 + 0x2c) == 0) {
              stk_38 = stk_34;
            }
            if (stk_18 <= stk_38) {
              do {
                if (-1 < i14) {
                  stk_18 = stk_18 + i14;
                  (*(uint32_t *)((char *)&GlobalTemp + 0)) = sprite3;
                  if (i5 + 1 < stk_18) {
                    i14 = (i5 - stk_18) + 1 + i14;
                  }
                  for (; i14 != 0; i14 = i14 + -1) {
                    b3 = *pb17;
                    pb17 = pb17 + 1;
                    *pu16 = *(uint16_t *)((int)sprite3 + (uint32_t)b3 * 2);
                    pu16 = pu16 + 1;
                  }
                  stk_60 = *(int *)(arg2 + 0x9c);
                  stk_64 = *(int *)(sprite2 + 0x2c);
                  i15 = *(int *)(arg2 + 0xa0);
                }
                i14 = *(int *)(stk_60 + stk_4c * 4);
                pb17 = *(uint8_t **)(i15 + stk_4c * 4);
                pu16 = (uint16_t *)
                          (i10 + *(int *)(stk_64 + (i12 + stk_30) * 4) + stk_18 * 2);
              } while (stk_18 <= stk_38);
            }
          }
          for (stk_48 = stk_48 + arg3; 999 < stk_48; stk_48 = stk_48 + -1000) {
            stk_4c = stk_4c + 1;
          }
          stk_30 = stk_30 + 1;
        } while ((i12 + stk_30 <= i4) &&
                (i14 = *(int *)(arg2 + 0x40), stk_4c < i14));
      }
      SpriteDecompUnlockData();
    }
  }
  return;
}

/* BGParalDraw8to16Flat2X @ 0x0804e420, 1 bytes
 *
 * Empty in this build.
 *
 * Called by: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGParalDraw8to16Flat2X(void)

{
  return;
}

/* BGParalDraw16 @ 0x0804e430, 1 bytes
 *
 * Empty in this build.
 *
 * Called by: BGParalDrawScale
 *
 * Elecbyte file: src/lib/bg-lib.c
 */
void BGParalDraw16(void)

{
  return;
}

