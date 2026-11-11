/*
 * font-lib.c -- bitmap fonts
 * Loads .fnt fonts (embedded PCX and character map) and draws text with
 * alignment and palette banks.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/font-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* V_FontDrawLine @ 0x08051990, 618 bytes
 *
 * Draws one line of text (up to '\n' or the end) with a fixed-palette font
 * at (x, y): each character's image is cut from the font sprite and drawn,
 * with the font's spacing and colour. Clipped to the window.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: MasterPalConvertCol16, W_Define, W_PutSprite, W_PutSpriteShadow
 * Called by: V_FontDrawAlign_I
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDrawLine(char *arg1,int *arg2,int arg3,int arg4,uint32_t arg5)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  char c6;
  int i7;
  uint32_t u8;
  int i9;
  uint32_t u10;
  uint32_t u11;
  uint32_t u12;
  uint32_t stk_48;
  uint32_t stk_38;
  int stk_20;
  
  i5 = W_y1;
  i4 = W_x2;
  i3 = W_x1;
  i2 = W_y2;
  stk_20 = 0;
  if (arg2 != (int *)0x0) {
    u10 = arg3 + *arg2;
    u1 = ((arg4 - arg2[1]) - arg2[3]) + 1;
    if (((int)u10 <= W_x2) && ((int)u1 <= W_y2)) {
      i7 = MasterPalConvertCol16(arg5);
      c6 = *arg1;
      u12 = u10;
      do {
        if ((c6 == '\0') || (c6 == '\n')) {
          W_Define(i3,i5,i4,i2);
          return;
        }
        if (c6 != '\r') {
          if (c6 < '\x0e') {
            if (c6 == '\t') {
              u12 = (int)(u12 - u10) / (arg2[5] + arg2[2]);
              if ((int)u12 < 0) {
                u12 = u12 + 3;
              }
              u12 = u10 + ((u12 & 0xfffffffc) + 4) * (arg2[5] + arg2[2]);
              goto L_08051ba6;
            }
L_08051a97:
            u11 = (u12 + arg2[c6 + 0x107]) - 1;
            u8 = (u1 + arg2[3]) - 1;
            if ((((i3 <= (int)u11) && (i5 <= (int)u8)) && ((int)u12 <= i4)) &&
               ((int)u1 <= i2)) {
              stk_38 = u12;
              if ((int)u12 < i3) {
                stk_38 = i3;
              }
              stk_48 = u1;
              if ((int)u1 < i5) {
                stk_48 = i5;
              }
              if (i4 < (int)u11) {
                u11 = i4;
              }
              if (i2 < (int)u8) {
                u8 = i2;
              }
              W_Define(stk_38,stk_48,u11,u8);
              if (arg2[c6 + 0x107] != 0) {
                if (i7 == -1) {
                  W_PutSprite((int *)arg2[0x206],0,u12 - arg2[c6 + 8],u1);
                }
                else {
                  W_PutSpriteShadow((int *)arg2[0x206],0,u12 - arg2[c6 + 8],u1,
                                    (short)i7);
                }
              }
            }
            i9 = arg2[5] + arg2[c6 + 0x107];
          }
          else {
            if (c6 != ' ') goto L_08051a97;
            i9 = arg2[5] + arg2[2];
          }
          u12 = u12 + i9;
        }
L_08051ba6:
        stk_20 = stk_20 + 1;
        c6 = arg1[stk_20];
      } while( true );
    }
  }
  return;
}

/* V_FontDrawLineBank @ 0x08051c00, 968 bytes
 *
 * Draws one line of text with a palette-bank font: the same as
 * V_FontDrawLine, but selects colour bank `bank` of the font palette (fonts
 * with several colour sets).
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: SpriteArrayAccess, SpriteArrayNumPals,
 *        SpriteArrayPalUpdateAndAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteDecompUnlockData
 * Called by: V_FontDrawAlign_I
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDrawLineBank(char *arg1,int *arg2,int arg3,int arg4,int arg5)

{
  char c1;
  int i2;
  bool b3;
  int i4;
  int i5;
  int i6;
  int i7;
  int sprite;
  int sprite2;
  int i10;
  int i11;
  int *sprite3;
  int i13;
  uint32_t u14;
  int i15;
  int i16;
  uint8_t *pb17;
  int i18;
  uint16_t *pu19;
  int i20;
  int i21;
  int *sprites;
  int *pi23;
  int stk_58;
  int stk_54;
  int stk_50;
  int stk_4c;
  int stk_48;
  int stk_38;
  int stk_34;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_38 = 0;
  b3 = false;
  if (arg2 != (int *)0x0) {
    sprites = (int *)arg2[0x206];
    sprite2 = SpriteArrayAccess(sprites,0);
    i20 = arg3 + *arg2;
    i10 = ((arg4 - arg2[1]) - arg2[3]) + 1;
    if ((((i20 <= W_x2) && (i10 <= W_y2)) && (-1 < arg5)) &&
       (i11 = SpriteArrayNumPals((int)sprites), arg5 < i11)) {
      sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,arg5);
      i11 = SpriteDecompGetAndLockData(sprites,0);
      if (i11 != 0) {
        i13 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        i7 = W_y1;
        i6 = W_x2;
        i5 = W_x1;
        i4 = W_y2;
        c1 = *arg1;
        i21 = i20;
        do {
          if ((c1 == '\0') || (c1 == '\n')) {
            SpriteDecompUnlockData();
            return;
          }
          if (!b3) {
            stk_4c = 0;
            stk_48 = i10;
            if (i10 < i7) {
              stk_48 = i7;
              stk_4c = i7 - i10;
            }
            stk_50 = i10 + arg2[3] + -1;
            if (i4 < stk_50) {
              stk_50 = i4;
            }
            b3 = true;
          }
          if (c1 != '\r') {
            if (c1 < '\x0e') {
              if (c1 == '\t') {
                u14 = (i21 - i20) / (arg2[5] + arg2[2]);
                if ((int)u14 < 0) {
                  u14 = u14 + 3;
                }
                i21 = i20 + ((u14 & 0xfffffffc) + 4) * (arg2[5] + arg2[2]);
                goto L_08051f80;
              }
L_08051e50:
              stk_58 = 0;
              stk_54 = i21;
              if (i21 < i5) {
                stk_54 = i5;
                stk_58 = i5 - i21;
              }
              i15 = i21 + arg2[c1 + 0x107] + -1;
              if (i6 < i15) {
                i15 = i6;
              }
              i16 = (stk_50 - stk_48) + 1;
              stk_34 = 0;
              if (0 < i16) {
                i2 = arg2[c1 + 8];
                pi23 = (int *)(stk_48 * 4 + *(int *)(sprite + 0x2c));
                sprites = (int *)(stk_4c * 4 + *(int *)(sprite2 + 0x2c));
                do {
                  pb17 = (uint8_t *)(i2 + i11 + *sprites + stk_58);
                  pu19 = (uint16_t *)(i13 + *pi23 + stk_54 * 2);
                  for (i18 = (i15 - stk_54) + 1; 0 < i18; i18 = i18 + -1) {
                    if (*pb17 != 0) {
                      *pu19 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb17 * 2 + 0x5c);
                    }
                    pu19 = pu19 + 1;
                    pb17 = pb17 + 1;
                  }
                  pi23 = pi23 + 1;
                  stk_34 = stk_34 + 1;
                  sprites = sprites + 1;
                } while (stk_34 < i16);
              }
              i15 = arg2[5] + arg2[c1 + 0x107];
            }
            else {
              if (c1 != ' ') goto L_08051e50;
              i15 = arg2[5] + arg2[2];
            }
            i21 = i21 + i15;
          }
L_08051f80:
          stk_38 = stk_38 + 1;
          c1 = arg1[stk_38];
        } while( true );
      }
    }
  }
  return;
}

/* V_FontDraw @ 0x08051fd0, 39 bytes
 *
 * Draws text left-aligned at (x, y) in colour bank `bank`.
 *
 * Parameters:
 *   text         char *
 *   font         int *
 *   x            int
 *   y            int
 *   bank         uint32_t
 *
 * Calls: V_FontDrawAlign
 * Called by: ContinueScreenLoop, EB_GUIDrawClipboard, FontDrawClipboard,
 *            GameLifeBarDraw, GameLoop, InfoTextDraw, KeyConfigScreen,
 *            OptionsScreen, PlayerDrawClsn, ShowDebugInfo,
 *            TrainingMenuDraw, V_FontWrite
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDraw(char *text,int *font,int x,int y,uint32_t bank)

{
  V_FontDrawAlign(text,font,x,y,1,bank);
  return;
}

/* V_FontDrawRight @ 0x08052000, 39 bytes
 *
 * Draws text right-aligned at x.
 *
 * Parameters:
 *   text         char *
 *   font         int *
 *   x            int
 *   y            int
 *   bank         uint32_t
 *
 * Calls: V_FontDrawAlign
 * Called by: ContinueScreenLoop, GameLifeBarDraw, GameReloadStage,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, V_FontWriteRight
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: Returns nothing (the original left only stale register values).
 */
void V_FontDrawRight(char *text,int *font,int x,int y,uint32_t bank)

{
  uint32_t stale_EAX;
  
  V_FontDrawAlign(text,font,x,y,-1,bank);
  return;
}

/* V_FontDrawCenter @ 0x08052030, 39 bytes
 *
 * Draws text centred on x.
 *
 * Parameters:
 *   text         char *
 *   font         int *
 *   x            int
 *   y            int
 *   bank         uint32_t
 *
 * Calls: V_FontDrawAlign
 * Called by: ContinueScreenLoop, KeyConfigScreen, ModeSelect,
 *            OptionsScreen, TrainingMenuDraw
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: Returns nothing (the original left only stale register values).
 */
void V_FontDrawCenter(char *text,int *font,int x,int y,uint32_t bank)

{
  uint32_t stale_EAX;
  
  V_FontDrawAlign(text,font,x,y,0,bank);
  return;
}

/* V_FontDrawBank @ 0x08052060, 39 bytes
 *
 * Draws text left-aligned using palette bank `bank`.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: V_FontDrawAlignBank
 * Called by: ComboDisplay, V_FontWriteBank
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDrawBank(char *arg1,int *arg2,int arg3,int arg4,int arg5)

{
  V_FontDrawAlignBank(arg1,arg2,arg3,arg4,1,arg5);
  return;
}

/* V_FontDrawRightBank @ 0x08052090, 39 bytes
 *
 * Draws text right-aligned using palette bank `bank`.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: V_FontDrawAlignBank
 * Called by: ComboDisplay
 *
 * Elecbyte file: src/lib/font-lib.c
 */
uint32_t V_FontDrawRightBank(char *arg1,int *arg2,int arg3,int arg4,int arg5)

{
  uint32_t u1;
  
  u1 = V_FontDrawAlignBank(arg1,arg2,arg3,arg4,-1,arg5);
  return u1;
}

/* V_FontDrawCenterBank @ 0x080520c0, 39 bytes
 *
 * Draws text centred using palette bank `bank`. Not called in this build.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: V_FontDrawAlignBank
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDrawCenterBank(char *arg1,int *arg2,int arg3,int arg4,int arg5)

{
  V_FontDrawAlignBank(arg1,arg2,arg3,arg4,0,arg5);
  return;
}

/* V_FontWrite @ 0x080520f0, 88 bytes
 *
 * printf-style V_FontDraw (formats into a 4 KB buffer first).
 *
 * Parameters:
 *   font         int *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         char *
 *
 * Calls: V_FontDraw
 * C library: vsprintf
 * Called by: EB_GUIDrawWindow, ModeSelect
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after arg5
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void V_FontWrite(int *font,int arg2,int arg3,uint32_t arg4,char *arg5,...)

{
  va_list va;
  va_start(va, arg5);
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define text (*(char (*)[4108])(frame + 0x4))
  
  vsprintf(text,arg5,va);
  V_FontDraw(text,font,arg2,arg3,arg4);
  return;
}
#undef text

/* V_FontWriteRight @ 0x08052150, 88 bytes
 *
 * printf-style V_FontDrawRight. Not called in this build.
 *
 * Parameters:
 *   font         int *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         char *
 *
 * Calls: V_FontDrawRight
 * C library: vsprintf
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after arg5
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void V_FontWriteRight(int *font,int arg2,int arg3,uint32_t arg4,char *arg5,...)

{
  va_list va;
  va_start(va, arg5);
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define text (*(char (*)[4108])(frame + 0x4))
  
  vsprintf(text,arg5,va);
  V_FontDrawRight(text,font,arg2,arg3,arg4);
  return;
}
#undef text

/* V_FontWriteBank @ 0x080521b0, 88 bytes
 *
 * printf-style V_FontDrawBank.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         char *
 *
 * Calls: V_FontDrawBank
 * C library: vsprintf
 * Called by: ComboDisplay
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after arg5
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void V_FontWriteBank(int *arg1,int arg2,int arg3,int arg4,char *arg5,...)

{
  va_list va;
  va_start(va, arg5);
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define stk_101c (*(char (*)[4108])(frame + 0x4))
  
  vsprintf(stk_101c,arg5,va);
  V_FontDrawBank(stk_101c,arg1,arg2,arg3,arg4);
  return;
}
#undef stk_101c

/* V_FontDrawAlign_I @ 0x08052210, 498 bytes
 *
 * Draws multi-line text: splits it at '\n' and draws each line with the
 * requested alignment (-1 left, 0 centre, 1 right), one font height apart.
 * Uses the bank or fixed-palette line drawer depending on `use_bank`.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         uint32_t
 *   arg7         int
 *
 * Calls: V_FontDrawLine, V_FontDrawLineBank
 * Called by: V_FontDrawAlign, V_FontDrawAlignBank
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
void V_FontDrawAlign_I(char *arg1,int *arg2,int arg3,int arg4,int arg5,uint32_t arg6,
                      int arg7)

{
  int i1;
  int i2;
  uint32_t u3;
  int i4;
  char c5;
  int i6;
  int saved_ESI;
  int stk_20;
  int stk_18;
  
  if (arg2 != (int *)0x0) {
    stk_18 = arg4;
    i6 = 0;
    if (*arg1 != '\0') {
      stk_20 = arg2[3];
      i2 = arg4 - stk_20;
      while (i2 + 1 <= W_y2) {
        i2 = i6;
        if (arg5 == 1) {
          c5 = arg1[i6];
          while ((c5 != '\0' && (c5 != '\n'))) {
            i2 = i2 + 1;
            c5 = arg1[i2];
          }
        }
        else {
          i4 = arg2[5];
          saved_ESI = -i4;
          c5 = arg1[i6];
          while ((c5 != '\0' && (c5 != '\n'))) {
            if (c5 != '\r') {
              if (c5 < '\x0e') {
                if (c5 == '\t') {
                  u3 = saved_ESI / (i4 + arg2[2]);
                  if ((int)u3 < 0) {
                    u3 = u3 + 3;
                  }
                  saved_ESI = ((u3 & 0xfffffffc) + 4) * (i4 + arg2[2]);
                  goto L_08052304;
                }
L_080522f0:
                i1 = arg2[c5 + 0x107];
              }
              else {
                if (c5 != ' ') goto L_080522f0;
                i1 = arg2[2];
              }
              saved_ESI = saved_ESI + i4 + i1;
            }
L_08052304:
            i2 = i2 + 1;
            c5 = arg1[i2];
          }
          if (saved_ESI < 0) {
            saved_ESI = 0;
          }
        }
        if (i6 < i2) {
          if (arg5 == 0) {
            i4 = arg3 - (saved_ESI >> 1);
          }
          else {
            i4 = arg3;
            if (arg5 == -1) {
              i4 = (arg3 - saved_ESI) + 1;
            }
          }
          if (arg7 == -1) {
            V_FontDrawLine(arg1 + i6,arg2,i4,stk_18,arg6);
          }
          else {
            V_FontDrawLineBank(arg1 + i6,arg2,i4,stk_18,arg7);
          }
          stk_20 = arg2[3];
        }
        i6 = i2 + 1;
        stk_18 = stk_18 + stk_20 + arg2[6];
        if (c5 == '\0') {
          return;
        }
        i2 = stk_18 - stk_20;
      }
    }
  }
  return;
}

/* V_FontDrawAlign @ 0x08052410, 44 bytes
 *
 * V_FontDrawAlign_I with fixed-palette drawing.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         uint32_t
 *
 * Calls: V_FontDrawAlign_I
 * Called by: V_FontDraw, V_FontDrawCenter, V_FontDrawRight
 *
 * Elecbyte file: src/lib/font-lib.c
 */
void V_FontDrawAlign(char *arg1,int *arg2,int arg3,int arg4,int arg5,uint32_t arg6)

{
  V_FontDrawAlign_I(arg1,arg2,arg3,arg4,arg5,arg6,-1);
  return;
}

/* V_FontDrawAlignBank @ 0x08052440, 44 bytes
 *
 * V_FontDrawAlign_I with palette-bank drawing.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *
 * Calls: V_FontDrawAlign_I
 * Called by: CharacterSelectScreenDraw, ExplodDraw, ModeSelect,
 *            V_FontDrawBank, V_FontDrawCenterBank, V_FontDrawRightBank,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: Returns nothing (the original left only stale register values).
 */
uint32_t
V_FontDrawAlignBank(char *arg1,int *arg2,int arg3,int arg4,int arg5,int arg6)

{
  uint32_t stale_EAX;
  
  V_FontDrawAlign_I(arg1,arg2,arg3,arg4,arg5,0,arg6);
  return;
}

/* FontReadFile @ 0x08052470, 61 bytes
 *
 * Opens and reads an .fnt font file (FontReadFilePtr).
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: MFfopenFile, FontReadFilePtr, MFfclose
 * Called by: EB_GUIInit, GameLoadFightData, GameLoadSystem,
 *            GameVarLoadFonts
 *
 * Elecbyte file: src/lib/font-lib.c
 */
uint32_t FontReadFile(char *filename)

{
  FILE *mf;
  uint32_t u2;
  
  mf = (FILE *)MFfopenFile(filename,"rb");
  if (mf == (FILE *)0x0) {
    u2 = 0;
  }
  else {
    u2 = FontReadFilePtr(mf);
    MFfclose((int *)mf);
  }
  return u2;
}

/* FontReadFilePtr @ 0x080524b0, 119 bytes
 *
 * Checks the "ElecbyteFnt" signature and version and reads the font
 * (FontReadFilePtr_0_01).
 *
 * Parameters:
 *   arg1         FILE *
 *
 * Calls: MFftell, MFfread, FontReadFilePtr_0_01, MFfseek
 * C library: flag
 * Called by: FontReadFile
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 2
 *       variables), because their address is taken.
 */
void * FontReadFilePtr(FILE *arg1)

{
  int pos;
  void *pv2;
  int i3;
  uint8_t *pb4;
  uint8_t *pb5;
  bool b6;
  bool b7;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(uint8_t (*)[12])(frame + 0x4))
#define stk_50 (*(int *)(frame + 0x10))
  
  pos = MFftell(&arg1->_flags);
  MFfread(stk_5c,0x40,1,&arg1->_flags);
  i3 = 0xc;
  b6 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  b7 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  pb4 = stk_5c;
  pb5 = (uint8_t *)"ElecbyteFnt";
  do {
    if (i3 == 0) break;
    i3 = i3 + -1;
    b6 = *pb4 < *pb5;
    b7 = *pb4 == *pb5;
    pb4 = pb4 + 1;
    pb5 = pb5 + 1;
  } while (b7);
  if (((!b6 && !b7) == b6) && (stk_50 == 0x100)) {
    pv2 = FontReadFilePtr_0_01(arg1,(int)stk_5c);
    MFfseek(&arg1->_flags,pos,0);
  }
  else {
    pv2 = (void *)0x0;
  }
  return pv2;
}
#undef stk_5c
#undef stk_50

/* FontReadFilePtr_0_01 @ 0x08052530, 1086 bytes
 *
 * Reads an .fnt v0.01 file: an embedded PCX image of all characters and an
 * embedded text section. "[Def]" gives "size", "spacing", "colors", "offset"
 * and "type" ("fixed" or "variable"); "[Map]" lists, for variable fonts,
 * each character's position and width in the image. Builds the character
 * table (sprite, x offset, width per character). Returns the font or NULL.
 *
 * Parameters:
 *   arg1         FILE *
 *   arg2         int
 *
 * Text keys read: [def], "size", "spacing", "colors", "offset", "type",
 *                 [map]
 * Calls: MFftell, MFfseek, SpriteReadPCXPtr, TPReadFilePtr, TPGroupSeek,
 *        TPScanf, TPGetValueInt, TPGetValue, TPAccessFirstLine,
 *        TPAccessNextLine, TPFree, SpriteArrayPalAccess, ArrayDelete,
 *        EBPalCopy, EBPalGenerateFPal, SpriteArrayAddPal,
 *        SpriteArrayAccess, FontFree
 * C library: calloc, sscanf
 * Called by: FontReadFilePtr
 * Messages:
 *   "%i %i"
 *
 * Elecbyte file: src/lib/font-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x4f0 bytes,
 *       6 variables), because their address is taken.
 */
void * FontReadFilePtr_0_01(FILE *arg1,int arg2)

{
  uint32_t u1;
  int pos;
  void *pv3;
  int *tp;
  int i5;
  int sprite;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  char c7;
  int i2;
  int i9;
  int *pi10;
  char *line;
  int *pi12;
  unsigned char frame[0x4f0] __attribute__((aligned(16)));
#define stk_4f0 (*(int *)(frame + 0x0))
#define stk_4ec (*(int *)(frame + 0x4))
#define stk_4e0 (*(int *)(frame + 0x10))
#define stk_4dc (*(int (*)[152])(frame + 0x14))
#define stk_27c (*(int (*)[2])(frame + 0x274))
#define stk_274 (*(int *)(frame + 0x27c))
  
  stk_4ec = 0;
  pos = MFftell(&arg1->_flags);
  pv3 = calloc(1,0x81c);
  if (pv3 == (void *)0x0) {
    return (void *)0x0;
  }
  MFfseek(&arg1->_flags,pos + -0x40 + *(int *)(arg2 + 0x10),0);
  tp = SpriteReadPCXPtr(&arg1->_flags,0,0);
  *(int **)((int)pv3 + 0x818) = tp;
  if (tp != (int *)0x0) {
    *(uint32_t *)((int)pv3 + 0x10) = 1;
    MFfseek(&arg1->_flags,pos + -0x40 + *(int *)(arg2 + 0x18),0);
    tp = TPReadFilePtr((FILE *)arg1->_IO_read_ptr,0);
    if (tp != (int *)0x0) {
      line = "def";
      pi10 = tp;
      pi12 = tp;
      i5 = TPGroupSeek((int)tp,"def");
      if (i5 != -1) {
        TPScanf((int)tp,"size","%i,%i",(int)pv3 + 8,(int)pv3 + 0xc,line,pi10,pi12
               );
        TPScanf((int)tp,"spacing","%i,%i",(int)pv3 + 0x14,(int)pv3 + 0x18);
        TPGetValueInt((int)tp,"colors",(uint32_t *)((int)pv3 + 0x1c));
        TPScanf((int)tp,"offset","%i,%i",pv3,(int)pv3 + 4);
        line = TPGetValue((int)tp,"type");
        if ((line != (char *)0x0) && ((*line == 'f' || (*line == 'F')))) {
          *(uint32_t *)((int)pv3 + 0x10) = 0;
        }
        i5 = TPGroupSeek((int)tp,"map");
        if (i5 != -1) {
          line = (char *)TPAccessFirstLine((int)tp);
          u1 = stale_ECX;
          while (line != (char *)0x0) {
            stk_4e0 = (int)*line;
            i9 = 0;
            i5 = 2;
            if (line[1] != '\0') {
              if ((*line == '0') && (line[1] == 'x')) {
                sscanf(line + 2,"%x",&stk_4e0,u1);
                c7 = '\0';
                if (line[2] != '\0') {
                  if (line[2] == ' ') {
                    c7 = ' ';
                  }
                  else {
                    do {
                      i5 = i5 + 1;
                      c7 = line[i5];
                      if (c7 == '\0') break;
                    } while (c7 != ' ');
                  }
                }
                while (c7 == ' ') {
                  i5 = i5 + 1;
                  c7 = line[i5];
                }
              }
              i9 = sscanf(line + i5,"%i %i",(int)pv3 + stk_4e0 * 4 + 0x20,
                             (int)pv3 + stk_4e0 * 4 + 0x41c);
            }
            if (i9 < 1) {
              *(int *)((int)pv3 + stk_4e0 * 4 + 0x20) = stk_4ec;
            }
            if (i9 < 2) {
              *(uint32_t *)((int)pv3 + stk_4e0 * 4 + 0x41c) =
                   *(uint32_t *)((int)pv3 + 8);
            }
            stk_4ec = stk_4ec + *(int *)((int)pv3 + stk_4e0 * 4 + 0x41c);
            line = (char *)TPAccessNextLine((int)tp);
            u1 = stale_ECX_00;
          }
          *(int *)((int)pv3 + 0x49c) = *(int *)((int)pv3 + 8);
          if (((*(int *)((int)pv3 + 8) != 0) && (*(int *)((int)pv3 + 0xc) != 0)) &&
             (*(int *)((int)pv3 + 0x1c) != 0)) {
            TPFree(tp);
            if (1 < *(int *)((int)pv3 + 0x1c)) {
              i5 = *(int *)((int)pv3 + 0x1c) * 2 + -2;
              i9 = 0x1f;
              if (i5 < 0) {
                i5 = -0x80000000;
              }
              else {
                do {
                  i9 = i9 + -1;
                  if (i9 == 0) goto L_08052838;
                } while (i5 >> ((uint8_t)i9 & 0x1f) == 0);
                i5 = 1 << ((uint8_t)i9 & 0x1f);
              }
L_08052838:
              tp = (int *)SpriteArrayPalAccess(*(int *)((int)pv3 + 0x818),0);
              pi10 = stk_4dc;
              for (i9 = 0x97; i9 != 0; i9 = i9 + -1) {
                *pi10 = *tp;
                tp = tp + 1;
                pi10 = pi10 + 1;
              }
              ArrayDelete(*(int *)(*(int *)((int)pv3 + 0x818) + 8),0);
              stk_4f0 = 0;
              i9 = 0x100 - i5;
              if (-1 < i9) {
                do {
                  EBPalCopy(stk_27c,stk_4dc,0);
                  stk_274 = stk_274 + i9 * 4;
                  stk_27c[0] = i5;
                  EBPalGenerateFPal(stk_27c);
                  i2 = stk_4f0 + 1;
                  sprite = SpriteArrayAddPal(*(int *)((int)pv3 + 0x818),stk_27c,0,stk_4f0);
                  if (sprite == 0) goto L_08052901;
                  i9 = i9 - i5;
                  stk_4f0 = i2;
                } while (-1 < i9);
              }
              i9 = SpriteArrayAddPal(*(int *)((int)pv3 + 0x818),stk_4dc,0,stk_4f0);
              if (i9 == 0) goto L_08052901;
              sprite = SpriteArrayAccess(*(int **)((int)pv3 + 0x818),0);
              i2 = 0;
              i9 = *(int *)(sprite + 0x20);
              *(int *)(sprite + 0x14) = i5;
              if (0 < i9) {
                do {
                  c7 = *(char *)(i2 + *(int *)(sprite + 0x24));
                  if (c7 != '\0') {
                    *(char *)(i2 + *(int *)(sprite + 0x24)) = c7 + (char)i5;
                    i9 = *(int *)(sprite + 0x20);
                  }
                  i2 = i2 + 1;
                } while (i2 < i9);
              }
            }
            MFfseek(&arg1->_flags,pos,0);
            return pv3;
          }
        }
      }
    }
  }
L_08052901:
  FontFree(pv3);
  return (void *)0x0;
}
#undef stk_4f0
#undef stk_4ec
#undef stk_4e0
#undef stk_4dc
#undef stk_27c
#undef stk_274

/* FontFree @ 0x08052970, 54 bytes
 *
 * Frees a font and its sprite array.
 *
 * Parameters:
 *   arg1         void *
 *
 * Calls: SpriteArrayFree
 * C library: free
 * Called by: FontReadFilePtr_0_01, GameFreeFightData, GameUnloadSystem,
 *            GameVarDeInit
 *
 * Elecbyte file: src/lib/font-lib.c
 */
uint32_t FontFree(void *arg1)

{
  if (arg1 != (void *)0x0) {
    if (*(int **)((int)arg1 + 0x818) != (int *)0x0) {
      SpriteArrayFree(*(int **)((int)arg1 + 0x818));
    }
    free(arg1);
  }
  return 1;
}

/* FontGetWidth @ 0x080529b0, 85 bytes
 *
 * Returns the pixel width of the widest line of `text` (character widths
 * plus spacing).
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * Called by: ComboDisplay
 *
 * Elecbyte file: src/lib/font-lib.c
 */
int FontGetWidth(int arg1,char *arg2)

{
  int i1;
  int i2;
  
  i2 = 0;
  i1 = 0;
  for (; *arg2 != '\0'; arg2 = arg2 + 1) {
    if (*arg2 == '\n') {
      if (i1 < i2) {
        i1 = i2;
      }
      i2 = 0;
    }
    else {
      i2 = i2 + *(int *)(arg1 + 0x14) + *(int *)(arg1 + 0x41c + *arg2 * 4);
    }
  }
  if (i1 < i2) {
    i1 = i2;
  }
  if (0 < i1) {
    i1 = i1 - *(int *)(arg1 + 0x14);
  }
  return i1;
}

/* FontGetWidthQuick @ 0x08052a10, 60 bytes
 *
 * Returns the pixel width of single-line `text` (no '\n' handling). Not
 * called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * Elecbyte file: src/lib/font-lib.c
 */
int FontGetWidthQuick(int arg1,char *arg2)

{
  char c1;
  int i2;
  
  i2 = 0;
  c1 = *arg2;
  while (c1 != '\0') {
    c1 = *arg2;
    arg2 = arg2 + 1;
    i2 = i2 + *(int *)(arg1 + 0x14) + *(int *)(arg1 + 0x41c + c1 * 4);
    c1 = *arg2;
  }
  if (0 < i2) {
    i2 = i2 - *(int *)(arg1 + 0x14);
  }
  return i2;
}

