/*
 * vbuf.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0807ce40-0x080802da, 47 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* V_Alloc @ 0x0807ce40, 29 bytes */
undefined4 V_Alloc(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = V_AllocDepth(param_1,param_2,G_ColDepth);
  return uVar1;
}

/* V_AllocDepth @ 0x0807ce60, 29 bytes */
int * V_AllocDepth(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = V_AllocDepthAry(param_1,param_2,param_3,1);
  return piVar1;
}

/* V_AllocDepthAry @ 0x0807ce80, 215 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
int * V_AllocDepthAry(int param_1,int param_2,int param_3,size_t param_4)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define aiStack_5c (*(int (*)[6])(ghidra_frame + 0x4))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x1c))
  
  piVar1 = SpriteArrayNewSize(param_4,1);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    iVar3 = 0;
    if (0 < (int)param_4) {
      do {
        puVar2 = (uint *)create_bitmap_ex(param_3,param_1,param_2);
        if (puVar2 == (uint *)0x0) {
          SpriteArrayFree(piVar1);
          return (int *)0x0;
        }
        set_clip(puVar2,0,0,param_1 - 1,param_2 - 1);
        set_color_depth(param_3);
        SpriteInit(aiStack_5c,1,puVar2,0x40,0,param_1,param_2,param_3,0,0);
        local_44 = 1;
        iVar4 = iVar3 + 1;
        SpriteArrayAddSprite(piVar1,aiStack_5c,0,iVar3);
        iVar3 = iVar4;
      } while (iVar4 < (int)param_4);
    }
  }
  return piVar1;
}
#undef aiStack_5c
#undef local_44

/* V_DeAlloc @ 0x0807cf60, 60 bytes */
undefined4 V_DeAlloc(int param_1)

{
  if (param_1 != 0) {
    if (V_Current == (int *)param_1) {
      V_Current = (int *)0x0;
      V_CurrentIdx = 0;
    }
    SpriteArrayFree((int *)param_1);
  }
  return 1;
}

/* V_SetBuf @ 0x0807cfa0, 144 bytes */
undefined4 V_SetBuf(int *param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  if ((piVar1 == (int *)0x0) || (1 < (uint)piVar1[7])) {
    uVar2 = 0;
  }
  else {
    V_Current = param_1;
    V_Width = *piVar1;
    V_Height = piVar1[1];
    V_ColDepth = piVar1[4];
    V_Size = V_Width * V_Height;
    V_BytesPerPixel = V_ColDepth + 7 >> 3;
    V_CurrentIdx = param_2;
    W_Skip = 0;
    W_Define(0,0,V_Width - 1,V_Height - 1);
    set_color_depth(V_ColDepth);
    uVar2 = 1;
  }
  return uVar2;
}

/* V_BufGetSurface @ 0x0807d030, 42 bytes */
undefined4 V_BufGetSurface(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((iVar1 == 0) || (*(int *)(iVar1 + 0x1c) != 1)) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x24);
  }
  return uVar2;
}

/* V_BufLock @ 0x0807d060, 59 bytes */
undefined4 V_BufLock(int *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = V_BufGetSurface(param_1,param_2);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    pcVar1 = *(code **)(*(int *)(iVar2 + 0x1c) + 0x10);
    if (pcVar1 != (code *)0x0) {
      (*pcVar1)(iVar2);
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* V_BufUnlock @ 0x0807d0a0, 50 bytes */
void V_BufUnlock(int *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = V_BufGetSurface(param_1,param_2);
  if ((iVar2 != 0) && (pcVar1 = *(code **)(*(int *)(iVar2 + 0x1c) + 0x14), pcVar1 != (code *)0x0)) {
    (*pcVar1)(iVar2);
  }
  return;
}

/* V_BufLockCurrent @ 0x0807d0e0, 25 bytes */
void V_BufLockCurrent(void)

{
  V_BufLock(V_Current,V_CurrentIdx);
  return;
}

/* V_BufUnlockCurrent @ 0x0807d100, 26 bytes */
void V_BufUnlockCurrent(void)

{
  V_BufUnlock(V_Current,V_CurrentIdx);
  return;
}

/* V_BufToScreen @ 0x0807d120, 211 bytes */
void V_BufToScreen(int *param_1,int param_2)

{
  int *piVar1;
  code *pcVar2;
  uint *puVar3;
  
  puVar3 = (uint *)SpriteArrayAccess(param_1,param_2);
  if ((puVar3 != (uint *)0x0) && (puVar3[7] == 1)) {
    piVar1 = (int *)puVar3[9];
    pcVar2 = *(code **)(*(int *)(screen + 0x1c) + 0x10);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(screen);
    }
    if (((puVar3[4] == 0x10) && (*(int *)G_Screenptr[7] == 0x20)) && (scrRGB16toBGR32 != 0)) {
      blit_32to16_RGBtoBGR(piVar1,(int)G_Screenptr,0,0,0,0,*puVar3,puVar3[1]);
    }
    else {
      blit(piVar1,G_Screenptr,0,0,0,0,*puVar3,puVar3[1]);
    }
    pcVar2 = *(code **)(*(int *)(screen + 0x1c) + 0x14);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(screen);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* V_BufToScreenXY @ 0x0807d200, 325 bytes */
void V_BufToScreenXY(int *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  code *pcVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = (uint *)SpriteArrayAccess(param_1,param_2);
  if ((puVar3 != (uint *)0x0) && (puVar3[7] == 1)) {
    piVar1 = (int *)puVar3[9];
    if ((param_3 < 0) ||
       (((param_4 < 0 || (S_Width < (int)(param_3 + *puVar3))) ||
        (S_Height < (int)(param_4 + puVar3[1]))))) {
      uVar5 = S_Height - 1;
      uVar4 = S_Width - 1;
    }
    else {
      uVar5 = 0;
      uVar4 = 0;
    }
    set_clip((uint *)G_Screenptr,0,0,uVar4,uVar5);
    pcVar2 = *(code **)(*(int *)(screen + 0x1c) + 0x10);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(screen);
    }
    if (((puVar3[4] == 0x10) && (*(int *)G_Screenptr[7] == 0x20)) && (scrRGB16toBGR32 != 0)) {
      blit_32to16_RGBtoBGR(piVar1,(int)G_Screenptr,0,0,param_3,param_4,*puVar3,puVar3[1]);
    }
    else {
      blit(piVar1,G_Screenptr,0,0,param_3,param_4,*puVar3,puVar3[1]);
    }
    pcVar2 = *(code **)(*(int *)(screen + 0x1c) + 0x14);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(screen);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* V_BufToScreenStretch @ 0x0807d350, 283 bytes
 * FIXUP: 4 word-indexed accesses to Allegro screen cast to int * */
void V_BufToScreenStretch(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *piVar3;
  int *extraout_EDX;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  if ((piVar2 != (int *)0x0) && (piVar2[7] == 1)) {
    iVar1 = piVar2[9];
    if ((*piVar2 == S_Width) && (piVar2[1] == S_Height)) {
      V_BufToScreen(param_1,param_2);
      return;
    }
    piVar3 = extraout_ECX;
    piVar4 = screen;
    if (*(code **)(((int *)screen)[7] + 0x10) != (code *)0x0) {
      (**(code **)(((int *)screen)[7] + 0x10))(screen);
      piVar3 = extraout_ECX_00;
      piVar4 = extraout_EDX;
    }
    iVar5 = S_Height;
    if (((piVar2[4] == 0x10) && (piVar4 = G_Screenptr, *(int *)G_Screenptr[7] == 0x20)) &&
       (scrRGB16toBGR32 != 0)) {
      piVar6 = piVar3;
      stretch_blit_32to16_RGBtoBGR
                (iVar1,(int)G_Screenptr,0,0,*piVar2,piVar2[1],0,0,S_Width,S_Height);
      piVar4 = piVar3;
    }
    else {
      piVar6 = piVar4;
      stretch_blit(iVar1,(int)G_Screenptr,0,0,*piVar2,piVar2[1],0,0,S_Width,S_Height);
    }
    if (*(code **)(((int *)screen)[7] + 0x14) != (code *)0x0) {
      (**(code **)(((int *)screen)[7] + 0x14))(screen,iVar5,piVar4,piVar6);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* blit_32to16_RGBtoBGR @ 0x0807d470, 544 bytes
 * FIXUP: 4 exact-text site patches */
void blit_32to16_RGBtoBGR
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
               ,int param_8)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  ushort *puVar7;
  
  iVar5 = *param_1;
  if ((((param_3 < iVar5) && (iVar4 = param_1[1], param_4 < iVar4)) &&
      (iVar2 = *(int *)(param_2 + 0x10), param_5 < iVar2)) &&
     (iVar3 = *(int *)(param_2 + 0x18), param_6 < iVar3)) {
    if (param_3 < 0) {
      param_7 = param_7 + param_3;
      param_5 = param_5 - param_3;
      param_3 = 0;
    }
    if (param_4 < 0) {
      param_8 = param_8 + param_4;
      param_6 = param_6 - param_4;
      param_4 = 0;
    }
    if (iVar5 < param_3 + param_7) {
      param_7 = iVar5 - param_3;
    }
    if (iVar4 < param_4 + param_8) {
      param_8 = iVar4 - param_4;
    }
    iVar5 = *(int *)(param_2 + 0xc);
    if (param_5 < iVar5) {
      param_7 = param_7 + (param_5 - iVar5);
      param_3 = param_3 - (param_5 - iVar5);
      param_5 = iVar5;
    }
    iVar5 = *(int *)(param_2 + 0x14);
    if (param_6 < iVar5) {
      param_8 = param_8 + (param_6 - iVar5);
      param_6 = iVar5;
    }
    if (iVar2 < param_5 + param_7) {
      param_7 = iVar2 - param_5;
    }
    if (iVar3 < param_6 + param_8) {
      param_8 = iVar3 - param_6;
    }
    if ((0 < param_7) && (0 < param_8)) {
      iVar5 = 0;
      if (0 < param_8) {
        do {
          iVar4 = ALG_bmp_read_line(param_1, param_4 + iVar5);
          puVar7 = (ushort *)(iVar4 + param_3 * 2);
          iVar4 = ALG_bmp_write_line((void *)param_2, param_6 + iVar5);
          puVar6 = (uint *)(iVar4 + param_5 * 4);
          iVar4 = param_7;
          if (0 < param_7) {
            do {
              uVar1 = *puVar7;
              puVar7 = puVar7 + 1;
              *puVar6 = (uVar1 & 0x1f) << 3 | (uVar1 & 0x7e0) << 5 | (uint)(uVar1 >> 0xb) << 0x13;
              puVar6 = puVar6 + 1;
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < param_8);
      }
      ALG_bmp_unwrite_line(param_1);
      ALG_bmp_unwrite_line((void *)param_2);
    }
  }
  return;
}

/* stretch_blit_32to16_RGBtoBGR @ 0x0807d690, 978 bytes
 * FIXUP: 2 exact-text site patches */
void stretch_blit_32to16_RGBtoBGR
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
               int param_8,int param_9,int param_10)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  ushort *puVar14;
  int local_94;
  int local_90;
  int local_60;
  int local_54;
  int local_50;
  int local_4c;
  int local_40;
  
  if (param_5 < 1) {
    return;
  }
  if (param_6 < 1) {
    return;
  }
  if (param_9 < 1) {
    return;
  }
  if (0 < param_10) {
    if (*(int *)(param_2 + 8) == 0) {
      local_50 = param_8;
      local_94 = param_9 + param_7;
      local_54 = param_8 + param_10;
      iVar9 = param_7;
    }
    else {
      local_50 = *(int *)(param_2 + 0x14);
      if (local_50 < param_8) {
        local_50 = param_8;
      }
      local_54 = *(int *)(param_2 + 0x18);
      if (param_8 + param_10 < *(int *)(param_2 + 0x18)) {
        local_54 = param_8 + param_10;
      }
      if (local_54 <= local_50) {
        return;
      }
      iVar9 = *(int *)(param_2 + 0xc);
      if (*(int *)(param_2 + 0xc) < param_7) {
        iVar9 = param_7;
      }
      local_94 = *(int *)(param_2 + 0x10);
      if (param_9 + param_7 < *(int *)(param_2 + 0x10)) {
        local_94 = param_9 + param_7;
      }
      if (local_94 <= iVar9) {
        return;
      }
    }
    param_6 = param_6 + -1;
    iVar4 = param_10 + -1;
    iVar13 = param_5 + -1;
    iVar5 = param_9 + -1;
    if (iVar5 == 0) {
      local_90 = 0;
    }
    else {
      local_90 = iVar13 / iVar5;
      iVar13 = iVar13 % iVar5;
    }
    local_4c = 0;
    if (iVar4 != 0) {
      local_4c = param_6 / iVar4;
      param_6 = param_6 % iVar4;
    }
    iVar13 = iVar13 * 2;
    iVar11 = iVar13 - iVar5;
    local_40 = param_3;
    iVar5 = iVar11 - iVar5;
    if (param_7 < iVar9) {
      iVar6 = iVar9 - param_7;
      do {
        iVar2 = iVar13;
        if (-1 < iVar11) {
          local_40 = local_40 + 1;
          iVar2 = iVar5;
        }
        iVar11 = iVar11 + iVar2;
        local_40 = local_40 + local_90;
        iVar6 = iVar6 + -1;
        param_7 = iVar9;
      } while (iVar6 != 0);
    }
    iVar6 = param_6 * 2;
    iVar2 = local_40 * 2;
    iVar12 = iVar6 - iVar4;
    iVar4 = iVar12 - iVar4;
    local_40 = param_4;
    if (param_8 < local_50) {
      iVar7 = local_50 - param_8;
      do {
        iVar3 = iVar6;
        if (-1 < iVar12) {
          local_40 = local_40 + 1;
          iVar3 = iVar4;
        }
        iVar12 = iVar12 + iVar3;
        local_40 = local_40 + local_4c;
        iVar7 = iVar7 + -1;
        param_8 = local_50;
      } while (iVar7 != 0);
    }
    for (; param_8 < local_54; param_8 = param_8 + 1) {
      puVar14 = (ushort *)(iVar2 + *(int *)(param_1 + 0x40 + local_40 * 4));
      iVar7 = ALG_bmp_write_line((void *)param_2, param_8);
      puVar10 = (uint *)(param_7 * 4 + iVar7);
      puVar8 = puVar10 + (local_94 - iVar9);
      local_60 = iVar11;
      for (; puVar10 < puVar8; puVar10 = puVar10 + 1) {
        uVar1 = *puVar14;
        *puVar10 = (uVar1 & 0x1f) << 3 | (uVar1 & 0x7e0) << 5 | (uint)(uVar1 >> 0xb) << 0x13;
        iVar7 = iVar13;
        if (-1 < local_60) {
          puVar14 = puVar14 + 1;
          iVar7 = iVar5;
        }
        local_60 = local_60 + iVar7;
        puVar14 = puVar14 + local_90;
      }
      iVar7 = iVar6;
      if (-1 < iVar12) {
        local_40 = local_40 + 1;
        iVar7 = iVar4;
      }
      iVar12 = iVar12 + iVar7;
      local_40 = local_40 + local_4c;
    }
    ALG_bmp_unwrite_line((void *)param_2);
    return;
  }
  return;
}

/* W_Define @ 0x0807da70, 200 bytes */
int W_Define(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  W_x2 = param_3;
  if ((int)param_3 < (int)param_1) {
    W_x2 = param_1;
    param_1 = param_3;
  }
  uVar2 = param_2;
  if ((int)param_4 < (int)param_2) {
    uVar2 = param_4;
    param_4 = param_2;
  }
  W_x1 = param_1 & 0xffffffffU - ((int)param_1 >> 0x1f);
  W_y1 = uVar2 & 0xffffffffU - ((int)uVar2 >> 0x1f);
  if (V_Width <= W_x2) {
    W_x2 = V_Width - 1;
  }
  if (V_Height <= (int)param_4) {
    param_4 = V_Height - 1;
  }
  W_Height = (param_4 - W_y1) + 1;
  W_Width = (W_x2 - W_x1) + 1;
  W_Skip = V_Width - W_Width;
  W_y2 = param_4;
  if (*(int *)(iVar1 + 0x1c) == 1) {
    iVar1 = set_clip(*(uint **)(iVar1 + 0x24),W_x1,W_y1,W_x2,param_4);
  }
  return iVar1;
}

/* W_DefineV @ 0x0807db40, 31 bytes */
void W_DefineV(uint *param_1)

{
  W_Define(*param_1,param_1[1],param_1[2],param_1[3]);
  return;
}

/* W_GetV @ 0x0807db60, 36 bytes */
void W_GetV(undefined4 *param_1)

{
  *param_1 = W_x1;
  param_1[1] = W_y1;
  param_1[2] = W_x2;
  param_1[3] = W_y2;
  return;
}

/* W_Cls @ 0x0807db90, 175 bytes */
void W_Cls(uint param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  piVar2 = (int *)SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar3 = MasterPalConvertCol16(param_1);
  if (piVar2[7] == 1) {
    (**(code **)(*(int *)(piVar2[9] + 0x1c) + 0x94))(piVar2[9],uVar3,piVar2,piVar2);
  }
  else {
    iVar4 = ColDepthToBytesPerPixel(piVar2[4]);
    if (iVar4 == 1) {
      memset((void *)piVar2[9],uVar3 & 0xff,piVar2[8]);
    }
    else if (iVar4 == 2) {
      iVar4 = *piVar2 * piVar2[1];
      if (iVar4 != 0) {
        iVar1 = piVar2[9];
        do {
          *(short *)(iVar1 + iVar4 * 2) = (short)uVar3;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    else if ((iVar4 == 4) && (iVar4 = *piVar2 * piVar2[1], iVar4 != 0)) {
      iVar1 = piVar2[9];
      do {
        *(uint *)(iVar1 + iVar4 * 4) = uVar3;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  return;
}

/* W_PutPixel @ 0x0807dc40, 233 bytes */
void W_PutPixel(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar2 = MasterPalConvertCol16(param_3);
  if (*(int *)(iVar1 + 0x1c) == 1) {
    (**(code **)(*(int *)(*(int *)(iVar1 + 0x24) + 0x1c) + 0x24))
              (*(int *)(iVar1 + 0x24),param_1,param_2,uVar2);
  }
  else {
    iVar4 = *(int *)(iVar1 + 0x24);
  }
  if ((((iVar4 != 0) && (W_x1 <= param_1)) && (param_1 <= W_x2)) &&
     ((W_y1 <= param_2 && (param_2 <= W_y2)))) {
    iVar3 = ColDepthToBytesPerPixel(*(int *)(iVar1 + 0x10));
    if (iVar3 == 2) {
      *(short *)(iVar4 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4) + param_1 * 2) =
           (short)uVar2;
    }
    else if (iVar3 < 3) {
      if (iVar3 == 1) {
        *(char *)(param_1 + iVar4 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4)) = (char)uVar2;
      }
    }
    else if (iVar3 == 4) {
      *(undefined4 *)(iVar4 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4) + param_1 * 4) = uVar2;
    }
  }
  return;
}

/* W_PutPixelTransAdd16 @ 0x0807dd30, 240 bytes */
void W_PutPixelTransAdd16(int param_1,int param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  
  iVar4 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar5 = MasterPalConvertCol16(param_3);
  if (*(int *)(iVar4 + 0x1c) == 1) {
    iVar8 = *(int *)(*(int *)(iVar4 + 0x24) + 0x28);
  }
  else {
    iVar8 = *(int *)(iVar4 + 0x24);
  }
  if ((((iVar8 != 0) && (W_x1 <= param_1)) && (param_1 <= W_x2)) &&
     ((W_y1 <= param_2 && (param_2 <= W_y2)))) {
    puVar1 = (uint *)(iVar8 + *(int *)(*(int *)(iVar4 + 0x2c) + param_2 * 4) + param_1 * 2);
    uVar3 = *puVar1;
    uVar9 = (uVar3 & 0xf800) + (uVar5 & 0xf800);
    if (0xf800 < uVar9) {
      uVar9 = 0xf800;
    }
    uVar2 = (uVar3 & 0x7e0) + (uVar5 & 0x7e0);
    uVar6 = (ushort)uVar2;
    if (0x7e0 < uVar2) {
      uVar6 = 0x7e0;
    }
    uVar5 = (uVar3 & 0x1f) + (uVar5 & 0x1f);
    uVar7 = (ushort)uVar5;
    if (0x1f < uVar5) {
      uVar7 = 0x1f;
    }
    *(ushort *)puVar1 = (ushort)uVar9 | uVar6 | uVar7;
  }
  return;
}

/* W_PutPixelXor16 @ 0x0807de20, 106 bytes */
void W_PutPixelXor16(int param_1,int param_2)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if (*(int *)(iVar2 + 0x1c) == 1) {
    iVar3 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
  }
  else {
    iVar3 = *(int *)(iVar2 + 0x24);
  }
  if ((((iVar3 != 0) && (W_x1 <= param_1)) && (param_1 <= W_x2)) &&
     ((W_y1 <= param_2 && (param_2 <= W_y2)))) {
    puVar1 = (ushort *)(iVar3 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
    *puVar1 = *puVar1 ^ 0xffff;
  }
  return;
}

/* W_Line @ 0x0807de90, 386 bytes */
void W_Line(float param_1,float param_2,float param_3,float param_4,uint param_5)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar1 = (uint)GHIDRA_FIST32(param_2);
  if (uVar1 == (int)GHIDRA_FIST32(param_4)) {
    W_HLine((int)GHIDRA_FIST32(param_1),(int)GHIDRA_FIST32(param_3),uVar1,param_5);
  }
  else if ((int)GHIDRA_FIST32(param_1) == (int)GHIDRA_FIST32(param_3)) {
    W_VLine((int)GHIDRA_FIST32(param_1),uVar1,(int)GHIDRA_FIST32(param_4),param_5);
  }
  else {
    uVar3 = MasterPalConvertCol16(param_5);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar4 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar4 = *(int *)(iVar2 + 0x24);
    }
    if (iVar4 != 0) {
      DoDrawClippedLine(iVar4,*(int *)(iVar2 + 0x2c),param_1,param_2,param_3,param_4,(short)uVar3);
    }
  }
  return;
}

/* DoDrawLine @ 0x0807e020, 1598 bytes
 * FIXUP: 16 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 5 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void DoDrawLine(int param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               undefined2 param_7)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  fVar1 = param_3;
  fVar5 = param_4;
  if (param_5 < param_3) {
    fVar1 = param_5;
    fVar5 = param_6;
    param_6 = param_4;
    param_5 = param_3;
  }
  iVar8 = (int)GHIDRA_FIST32(fVar1);
  iVar6 = (int)GHIDRA_FIST32(param_5);
  iVar7 = (int)GHIDRA_FIST32(fVar5);
  iVar9 = (int)GHIDRA_FIST32(param_6);
  fVar2 = param_5 - fVar1;
  fVar4 = param_6 - fVar5;
  if (iVar8 == iVar6) {
    if (iVar7 <= iVar9) {
      do {
        iVar6 = iVar7 * 4;
        iVar7 = iVar7 + 1;
        *(undefined2 *)(iVar8 * 2 + param_1 + *(int *)(param_2 + iVar6)) = param_7;
      } while (iVar7 <= iVar9);
    }
  }
  else if (iVar7 == iVar9) {
    if (iVar8 <= iVar6) {
      iVar7 = *(int *)(param_2 + iVar7 * 4);
      do {
        *(undefined2 *)(param_1 + iVar7 + iVar8 * 2) = param_7;
        iVar8 = iVar8 + 1;
      } while (iVar8 <= iVar6);
    }
  }
  else {
    *(undefined2 *)(param_1 + *(int *)(param_2 + iVar7 * 4) + iVar8 * 2) = param_7;
    if (0.0 < fVar2) {
      if ((fVar4 <= 0.0) || (fVar2 < fVar4)) {
        if (0.0 < fVar2) {
          if ((fVar4 <= 0.0) || (fVar4 <= fVar2)) {
            if (0.0 < fVar2) {
              if ((0.0 <= fVar4) || (fVar2 < -fVar4)) {
                if (((0.0 < fVar2) && (fVar4 < 0.0)) && (fVar2 < -fVar4)) {
                  fVar4 = fVar4 * -1.0;
                  fVar3 = fVar2 + fVar2;
                  fVar1 = (fVar1 - (float10)iVar8) * fVar4 + fVar2 * (fVar5 - (float10)iVar7);
                  fVar1 = fVar1 + fVar1 + (fVar3 - fVar4);
                  iVar6 = (int)GHIDRA_FIST32(fVar4);
                  if (-1 < iVar6 + -1) {
                    do {
                      iVar9 = (int)GHIDRA_FIST32(fVar1);
                      iVar7 = iVar7 + -1;
                      if (iVar9 < 0) {
                        fVar1 = (float10)iVar9 + fVar3;
                      }
                      else {
                        iVar8 = iVar8 + 1;
                        fVar1 = ((fVar3 - fVar4) - fVar4) + (float10)iVar9;
                      }
                      iVar6 = iVar6 + -1;
                      *(undefined2 *)(param_1 + *(int *)(param_2 + iVar7 * 4) + iVar8 * 2) = param_7
                      ;
                    } while (iVar6 != 0);
                  }
                }
              }
              else {
                fVar4 = fVar4 * -1.0;
                fVar3 = fVar4 + fVar4;
                fVar1 = -fVar4 * (fVar1 - (float10)iVar8) - (fVar5 - (float10)iVar7) * fVar2;
                fVar1 = fVar1 + fVar1 + (fVar3 - fVar2);
                iVar6 = 0;
                if ((int)GHIDRA_FIST32(fVar2) - 1U < 0x80000000) {
                  do {
                    iVar9 = (int)GHIDRA_FIST32(fVar1);
                    iVar8 = iVar8 + 1;
                    if (iVar9 < 0) {
                      fVar1 = (float10)iVar9 + fVar3;
                    }
                    else {
                      iVar7 = iVar7 + -1;
                      fVar1 = ((fVar3 - fVar2) - fVar2) + (float10)iVar9;
                    }
                    iVar6 = iVar6 + 1;
                    *(undefined2 *)(param_1 + *(int *)(param_2 + iVar7 * 4) + iVar8 * 2) = param_7;
                  } while (iVar6 <= (int)((int)GHIDRA_FIST32(fVar2) - 1U));
                }
              }
            }
          }
          else {
            fVar3 = fVar2 + fVar2;
            fVar1 = (fVar1 - (float10)iVar8) * fVar4 - fVar2 * (fVar5 - (float10)iVar7);
            fVar1 = fVar1 + fVar1 + (fVar3 - fVar4);
            iVar6 = 0;
            if ((int)GHIDRA_FIST32(fVar4) - 1U < 0x80000000) {
              do {
                iVar9 = (int)GHIDRA_FIST32(fVar1);
                iVar7 = iVar7 + 1;
                if (iVar9 < 0) {
                  fVar1 = (float10)iVar9 + fVar3;
                }
                else {
                  iVar8 = iVar8 + 1;
                  fVar1 = ((fVar3 - fVar4) - fVar4) + (float10)iVar9;
                }
                iVar6 = iVar6 + 1;
                *(undefined2 *)(param_1 + *(int *)(param_2 + iVar7 * 4) + iVar8 * 2) = param_7;
              } while (iVar6 <= (int)((int)GHIDRA_FIST32(fVar4) - 1U));
            }
          }
        }
      }
      else {
        fVar3 = fVar4 + fVar4;
        fVar1 = -fVar4 * (fVar1 - (float10)iVar8) + (fVar5 - (float10)iVar7) * fVar2;
        fVar1 = fVar1 + fVar1 + (fVar3 - fVar2);
        iVar6 = 0;
        if ((int)GHIDRA_FIST32(fVar2) - 1U < 0x80000000) {
          do {
            iVar9 = (int)GHIDRA_FIST32(fVar1);
            iVar8 = iVar8 + 1;
            if (iVar9 < 0) {
              fVar1 = (float10)iVar9 + fVar3;
            }
            else {
              iVar7 = iVar7 + 1;
              fVar1 = ((fVar3 - fVar2) - fVar2) + (float10)iVar9;
            }
            iVar6 = iVar6 + 1;
            *(undefined2 *)(param_1 + *(int *)(param_2 + iVar7 * 4) + iVar8 * 2) = param_7;
          } while (iVar6 <= (int)((int)GHIDRA_FIST32(fVar2) - 1U));
        }
      }
    }
  }
  return;
}

/* CyrusT @ 0x0807e660, 59 bytes */
longdouble
CyrusT(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
      float param_7,float param_8)

{
  return (((longdouble)param_1 - (longdouble)param_7) * (longdouble)param_5 +
         ((longdouble)param_2 - (longdouble)param_8) * (longdouble)param_6) /
         -((longdouble)param_6 * (longdouble)param_4 + (longdouble)param_5 * (longdouble)param_3);
}

/* TrivialTestPoint @ 0x0807e6a0, 76 bytes */
uint TrivialTestPoint(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 < W_x1) {
    uVar1 = 1;
  }
  else if (W_x2 < param_1) {
    uVar1 = 2;
  }
  if (param_2 < W_y1) {
    return uVar1 | 4;
  }
  if (W_y2 < param_2) {
    uVar1 = uVar1 | 8;
  }
  return uVar1;
}

/* DoDrawClippedLine @ 0x0807e6f0, 1363 bytes
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void DoDrawClippedLine(int param_1,int param_2,float param_3,float param_4,float param_5,
                      float param_6,undefined2 param_7)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  longdouble lVar10;
  longdouble lVar11;
  longdouble lVar12;
  longdouble lVar13;
  longdouble lVar14;
  
  fVar2 = param_5 - param_3;
  fVar3 = param_6 - param_4;
  uVar4 = TrivialTestPoint((int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
  uVar5 = TrivialTestPoint((int)GHIDRA_FIST32(param_5),(int)GHIDRA_FIST32(param_6));
  if ((uVar5 & uVar4) == 0) {
    lVar10 = CyrusT(param_3,param_4,fVar2,fVar3,-1.0,0.0,(float)W_x1,(float)W_y2);
    fVar1 = (float)lVar10;
    if ((lVar10 < (longdouble)0.0) || (1.0 < fVar1)) {
      iVar9 = 0;
    }
    else {
      iVar9 = (uint)(fVar2 * -1.0 < 0.0) * 2 + -1;
    }
    lVar10 = CyrusT(param_3,param_4,fVar2,fVar3,1.0,0.0,(float)W_x2,(float)W_y1);
    if ((lVar10 < (longdouble)0.0) || ((longdouble)1.0 < lVar10)) {
      iVar8 = 0;
    }
    else {
      iVar8 = (uint)(fVar2 < 0.0) * 2 + -1;
    }
    lVar11 = CyrusT(param_3,param_4,fVar2,fVar3,0.0,-1.0,(float)W_x1,(float)W_y1);
    if ((lVar11 < (longdouble)0.0) || ((longdouble)1 < lVar11)) {
      iVar7 = 0;
    }
    else {
      iVar7 = (uint)(fVar3 * -1.0 < 0.0) * 2 + -1;
    }
    lVar12 = CyrusT(param_3,param_4,fVar2,fVar3,0.0,1.0,(float)W_x2,(float)W_y2);
    if ((lVar12 < (longdouble)0.0) || ((longdouble)1.0 < lVar12)) {
      iVar6 = 0;
    }
    else {
      iVar6 = (uint)(fVar3 < 0.0) * 2 + -1;
    }
    lVar14 = (longdouble)1;
    if ((iVar9 == -1) && ((longdouble)fVar1 < lVar14)) {
      lVar14 = (longdouble)fVar1;
    }
    if ((iVar8 == -1) && (lVar13 = (longdouble)(float)lVar10, lVar13 < lVar14)) {
      lVar14 = lVar13;
    }
    if ((iVar7 == -1) && (lVar11 < lVar14)) {
      lVar14 = lVar11;
    }
    if ((iVar6 == -1) && (lVar12 < lVar14)) {
      lVar14 = lVar12;
    }
    lVar13 = (longdouble)0;
    if ((iVar9 == 1) && (lVar13 < (longdouble)fVar1)) {
      lVar13 = (longdouble)fVar1;
    }
    if ((iVar8 == 1) && (lVar10 = (longdouble)(float)lVar10, lVar13 < lVar10)) {
      lVar13 = lVar10;
    }
    lVar10 = lVar13;
    if ((iVar7 == 1) && (lVar10 = lVar11, lVar11 <= lVar13)) {
      lVar10 = lVar13;
    }
    if ((iVar6 == 1) && (lVar10 < lVar12)) {
      lVar10 = lVar12;
    }
    if (lVar10 <= lVar14) {
      lVar12 = lVar10 * (longdouble)fVar2 + (longdouble)param_3;
      lVar11 = lVar14 * (longdouble)fVar2 + (longdouble)param_3;
      lVar14 = lVar14 * (longdouble)fVar3 + (longdouble)param_4;
      lVar10 = (longdouble)fVar3 * lVar10 + (longdouble)param_4;
      if (lVar12 < (longdouble)W_x1) {
        lVar12 = (longdouble)W_x1;
      }
      if ((longdouble)W_x2 < lVar12) {
        lVar12 = (longdouble)W_x2;
      }
      if (lVar11 < (longdouble)W_x1) {
        lVar11 = (longdouble)W_x1;
      }
      if ((longdouble)W_x2 < lVar11) {
        lVar11 = (longdouble)W_x2;
      }
      if (lVar10 < (longdouble)W_y1) {
        lVar10 = (longdouble)W_y1;
      }
      if ((longdouble)W_y2 < lVar10) {
        lVar10 = (longdouble)W_y2;
      }
      if (lVar14 < (longdouble)W_y1) {
        lVar14 = (longdouble)W_y1;
      }
      if ((longdouble)W_y2 < lVar14) {
        lVar14 = (longdouble)W_y2;
      }
      DoDrawLine(param_1,param_2,(float)lVar12,(float)lVar10,(float)lVar11,(float)lVar14,param_7);
    }
  }
  return;
}

/* W_HLine @ 0x0807ec50, 177 bytes */
void W_HLine(uint param_1,uint param_2,int param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar5 = param_2;
  if ((int)param_2 < (int)param_1) {
    uVar5 = param_1;
    param_1 = param_2;
  }
  if ((((W_y1 <= param_3) && (param_3 <= W_y2)) && (W_x1 <= (int)uVar5)) && ((int)param_1 <= W_x2))
  {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)uVar5) {
      uVar5 = W_x2;
    }
    uVar2 = MasterPalConvertCol16(param_4);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar3 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar3 = *(int *)(iVar1 + 0x24);
    }
    if (iVar3 != 0) {
      puVar4 = (undefined2 *)(iVar3 + *(int *)(*(int *)(iVar1 + 0x2c) + param_3 * 4) + param_1 * 2);
      for (iVar1 = (uVar5 - param_1) + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = (short)uVar2;
        puVar4 = puVar4 + 1;
      }
    }
  }
  return;
}

/* W_VLine @ 0x0807ed10, 196 bytes */
void W_VLine(int param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  uint uVar6;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = V_Width;
  uVar6 = param_3;
  if ((int)param_3 < (int)param_2) {
    uVar6 = param_2;
    param_2 = param_3;
  }
  if ((((W_x1 <= param_1) && (param_1 <= W_x2)) && (W_y1 <= (int)uVar6)) && ((int)param_2 <= W_y2))
  {
    if ((int)param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < (int)uVar6) {
      uVar6 = W_y2;
    }
    uVar3 = MasterPalConvertCol16(param_4);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar4 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar4 = *(int *)(iVar2 + 0x24);
    }
    if (iVar4 != 0) {
      puVar5 = (undefined2 *)(iVar4 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
      for (iVar2 = (uVar6 - param_2) + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = (short)uVar3;
        puVar5 = puVar5 + iVar1;
      }
    }
  }
  return;
}

/* W_HLineTransAdd16 @ 0x0807ede0, 312 bytes */
void W_HLineTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar4;
  
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar2 = param_2;
  if ((int)param_2 < (int)param_1) {
    uVar2 = param_1;
    param_1 = param_2;
  }
  if ((((W_y1 <= (int)param_3) && ((int)param_3 <= W_y2)) && (W_x1 <= (int)uVar2)) &&
     ((int)param_1 <= W_x2)) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)uVar2) {
      uVar2 = W_x2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar6 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar6 = *(int *)(iVar1 + 0x24);
    }
    if (iVar6 != 0) {
      puVar8 = (ushort *)(iVar6 + *(int *)(*(int *)(iVar1 + 0x2c) + param_3 * 4) + param_1 * 2);
      for (iVar1 = (uVar2 - param_1) + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
        uVar2 = (uint)*puVar8;
        uVar7 = (param_4 & 0xf800) + (uVar2 & 0xf800);
        if (0xf800 < uVar7) {
          uVar7 = 0xf800;
        }
        uVar4 = (param_4 & 0x7e0) + (uVar2 & 0x7e0);
        uVar3 = (ushort)uVar4;
        if (0x7e0 < uVar4) {
          uVar3 = 0x7e0;
        }
        uVar2 = (uVar2 & 0x1f) + (param_4 & 0x1f);
        uVar5 = (ushort)uVar2;
        if (0x1f < uVar2) {
          uVar5 = 0x1f;
        }
        *puVar8 = (ushort)uVar7 | uVar3 | uVar5;
        puVar8 = puVar8 + 1;
      }
    }
  }
  return;
}

/* W_HLineTransAdd16_B50 @ 0x0807ef20, 310 bytes */
void W_HLineTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  ushort *puVar8;
  uint uVar4;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar3 = param_2;
  if ((int)param_2 < (int)param_1) {
    uVar3 = param_1;
    param_1 = param_2;
  }
  if ((((W_y1 <= (int)param_3) && ((int)param_3 <= W_y2)) && (W_x1 <= (int)uVar3)) &&
     ((int)param_1 <= W_x2)) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)uVar3) {
      uVar3 = W_x2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar7 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar7 = *(int *)(iVar2 + 0x24);
    }
    if (iVar7 != 0) {
      puVar8 = (ushort *)(iVar7 + *(int *)(*(int *)(iVar2 + 0x2c) + param_3 * 4) + param_1 * 2);
      for (iVar2 = (uVar3 - param_1) + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = (uint)(*puVar8 >> 1);
        uVar5 = (param_4 & 0xf800) + (uVar3 & 0x7800);
        if (0xf800 < uVar5) {
          uVar5 = 0xf800;
        }
        uVar4 = (uVar3 & 0x3e0) + (param_4 & 0x7e0);
        uVar1 = (ushort)uVar4;
        if (0x7e0 < uVar4) {
          uVar1 = 0x7e0;
        }
        uVar3 = (uVar3 & 0xf) + (param_4 & 0x1f);
        uVar6 = (ushort)uVar3;
        if (0x1f < uVar3) {
          uVar6 = 0x1f;
        }
        *puVar8 = uVar1 | (ushort)uVar5 | uVar6;
        puVar8 = puVar8 + 1;
      }
    }
  }
  return;
}

/* W_VLineTransAdd16 @ 0x0807f060, 330 bytes */
void W_VLineTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  uint uVar5;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = V_Width;
  uVar3 = param_3;
  if ((int)param_3 < (int)param_2) {
    uVar3 = param_2;
    param_2 = param_3;
  }
  if ((((W_x1 <= (int)param_1) && ((int)param_1 <= W_x2)) && (W_y1 <= (int)uVar3)) &&
     ((int)param_2 <= W_y2)) {
    if ((int)param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < (int)uVar3) {
      uVar3 = W_y2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar7 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar7 = *(int *)(iVar2 + 0x24);
    }
    if (iVar7 != 0) {
      puVar9 = (ushort *)(iVar7 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
      for (iVar2 = (uVar3 - param_2) + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = (uint)*puVar9;
        uVar8 = (param_4 & 0xf800) + (uVar3 & 0xf800);
        if (0xf800 < uVar8) {
          uVar8 = 0xf800;
        }
        uVar5 = (param_4 & 0x7e0) + (uVar3 & 0x7e0);
        uVar4 = (ushort)uVar5;
        if (0x7e0 < uVar5) {
          uVar4 = 0x7e0;
        }
        uVar3 = (uVar3 & 0x1f) + (param_4 & 0x1f);
        uVar6 = (ushort)uVar3;
        if (0x1f < uVar3) {
          uVar6 = 0x1f;
        }
        *puVar9 = (ushort)uVar8 | uVar4 | uVar6;
        puVar9 = puVar9 + iVar1;
      }
    }
  }
  return;
}

/* W_VLineTransAdd16_B50 @ 0x0807f1b0, 328 bytes */
void W_VLineTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar6;
  ushort uVar7;
  int iVar8;
  ushort *puVar9;
  uint uVar5;
  
  iVar3 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = V_Width;
  uVar4 = param_3;
  if ((int)param_3 < (int)param_2) {
    uVar4 = param_2;
    param_2 = param_3;
  }
  if ((((W_x1 <= (int)param_1) && ((int)param_1 <= W_x2)) && (W_y1 <= (int)uVar4)) &&
     ((int)param_2 <= W_y2)) {
    if ((int)param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < (int)uVar4) {
      uVar4 = W_y2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar3 + 0x1c) == 1) {
      iVar8 = *(int *)(*(int *)(iVar3 + 0x24) + 0x28);
    }
    else {
      iVar8 = *(int *)(iVar3 + 0x24);
    }
    if (iVar8 != 0) {
      puVar9 = (ushort *)(iVar8 + *(int *)(*(int *)(iVar3 + 0x2c) + param_2 * 4) + param_1 * 2);
      for (iVar3 = (uVar4 - param_2) + 1; iVar3 != 0; iVar3 = iVar3 + -1) {
        uVar4 = (uint)(*puVar9 >> 1);
        uVar6 = (param_4 & 0xf800) + (uVar4 & 0x7800);
        if (0xf800 < uVar6) {
          uVar6 = 0xf800;
        }
        uVar5 = (uVar4 & 0x3e0) + (param_4 & 0x7e0);
        uVar2 = (ushort)uVar5;
        if (0x7e0 < uVar5) {
          uVar2 = 0x7e0;
        }
        uVar4 = (uVar4 & 0xf) + (param_4 & 0x1f);
        uVar7 = (ushort)uVar4;
        if (0x1f < uVar4) {
          uVar7 = 0x1f;
        }
        *puVar9 = uVar2 | (ushort)uVar6 | uVar7;
        puVar9 = puVar9 + iVar1;
      }
    }
  }
  return;
}

/* W_HLineTransSub16 @ 0x0807f300, 299 bytes */
void W_HLineTransSub16(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar2 = param_2;
  if ((int)param_2 < (int)param_1) {
    uVar2 = param_1;
    param_1 = param_2;
  }
  if ((((W_y1 <= (int)param_3) && ((int)param_3 <= W_y2)) && (W_x1 <= (int)uVar2)) &&
     ((int)param_1 <= W_x2)) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)uVar2) {
      uVar2 = W_x2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar3 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar3 = *(int *)(iVar1 + 0x24);
    }
    if (iVar3 != 0) {
      puVar6 = (ushort *)(iVar3 + *(int *)(*(int *)(iVar1 + 0x2c) + param_3 * 4) + param_1 * 2);
      for (iVar1 = (uVar2 - param_1) + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
        uVar2 = (uint)*puVar6;
        iVar5 = (uVar2 & 0xf800) - (param_4 & 0xf800);
        iVar4 = (uVar2 & 0x7e0) - (param_4 & 0x7e0);
        iVar3 = (uVar2 & 0x1f) - (param_4 & 0x1f);
        *puVar6 = (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U |
                  (ushort)iVar4 & -(short)(iVar4 >> 0x1f) - 1U |
                  (ushort)iVar3 & -(short)(iVar3 >> 0x1f) - 1U;
        puVar6 = puVar6 + 1;
      }
    }
  }
  return;
}

/* W_HLineTransSub16_B50 @ 0x0807f430, 302 bytes */
void W_HLineTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  uVar2 = param_2;
  if ((int)param_2 < (int)param_1) {
    uVar2 = param_1;
    param_1 = param_2;
  }
  if ((((W_y1 <= (int)param_3) && ((int)param_3 <= W_y2)) && (W_x1 <= (int)uVar2)) &&
     ((int)param_1 <= W_x2)) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)uVar2) {
      uVar2 = W_x2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar3 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar3 = *(int *)(iVar1 + 0x24);
    }
    if (iVar3 != 0) {
      puVar6 = (ushort *)(iVar3 + *(int *)(*(int *)(iVar1 + 0x2c) + param_3 * 4) + param_1 * 2);
      for (iVar1 = (uVar2 - param_1) + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
        uVar2 = (uint)(*puVar6 >> 1);
        iVar5 = (uVar2 & 0x7800) - (param_4 & 0xf800);
        iVar4 = (uVar2 & 0x3e0) - (param_4 & 0x7e0);
        iVar3 = (uVar2 & 0xf) - (param_4 & 0x1f);
        *puVar6 = (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U |
                  (ushort)iVar4 & -(short)(iVar4 >> 0x1f) - 1U |
                  (ushort)iVar3 & -(short)(iVar3 >> 0x1f) - 1U;
        puVar6 = puVar6 + 1;
      }
    }
  }
  return;
}

/* W_VLineTransSub16 @ 0x0807f560, 314 bytes */
void W_VLineTransSub16(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = V_Width;
  uVar3 = param_3;
  if ((int)param_3 < (int)param_2) {
    uVar3 = param_2;
    param_2 = param_3;
  }
  if ((((W_x1 <= (int)param_1) && ((int)param_1 <= W_x2)) && (W_y1 <= (int)uVar3)) &&
     ((int)param_2 <= W_y2)) {
    if ((int)param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < (int)uVar3) {
      uVar3 = W_y2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar4 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar4 = *(int *)(iVar2 + 0x24);
    }
    if (iVar4 != 0) {
      puVar7 = (ushort *)(iVar4 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
      for (iVar2 = (uVar3 - param_2) + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = (uint)*puVar7;
        iVar6 = (uVar3 & 0xf800) - (param_4 & 0xf800);
        iVar5 = (uVar3 & 0x7e0) - (param_4 & 0x7e0);
        iVar4 = (uVar3 & 0x1f) - (param_4 & 0x1f);
        *puVar7 = (ushort)iVar6 & -(short)(iVar6 >> 0x1f) - 1U |
                  (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U |
                  (ushort)iVar4 & -(short)(iVar4 >> 0x1f) - 1U;
        puVar7 = puVar7 + iVar1;
      }
    }
  }
  return;
}

/* W_VLineTransSub16_B50 @ 0x0807f6a0, 317 bytes */
void W_VLineTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = V_Width;
  uVar3 = param_3;
  if ((int)param_3 < (int)param_2) {
    uVar3 = param_2;
    param_2 = param_3;
  }
  if ((((W_x1 <= (int)param_1) && ((int)param_1 <= W_x2)) && (W_y1 <= (int)uVar3)) &&
     ((int)param_2 <= W_y2)) {
    if ((int)param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < (int)uVar3) {
      uVar3 = W_y2;
    }
    MasterPalConvertCol16(param_4);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar4 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar4 = *(int *)(iVar2 + 0x24);
    }
    if (iVar4 != 0) {
      puVar7 = (ushort *)(iVar4 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
      for (iVar2 = (uVar3 - param_2) + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = (uint)(*puVar7 >> 1);
        iVar6 = (uVar3 & 0x7800) - (param_4 & 0xf800);
        iVar5 = (uVar3 & 0x3e0) - (param_4 & 0x7e0);
        iVar4 = (uVar3 & 0xf) - (param_4 & 0x1f);
        *puVar7 = (ushort)iVar6 & -(short)(iVar6 >> 0x1f) - 1U |
                  (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U |
                  (ushort)iVar4 & -(short)(iVar4 >> 0x1f) - 1U;
        puVar7 = puVar7 + iVar1;
      }
    }
  }
  return;
}

/* W_Box @ 0x0807f7e0, 280 bytes
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_Box(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  int iVar5;
  uint uVar6;
  undefined4 local_1c;
  
  iVar5 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_1c = 0;
  uVar6 = MasterPalConvertCol16(param_5);
  if (*(int *)(iVar5 + 0x1c) == 1) {
    rect(*(int *)(iVar5 + 0x24),param_1,param_2,param_3,param_4,uVar6);
  }
  else {
    local_1c = *(int *)(iVar5 + 0x24);
  }
  if (local_1c != 0) {
    fVar1 = (float)param_4;
    fVar2 = (float)param_1;
    fVar3 = (float)param_2;
    W_Line(fVar2,fVar3,fVar2,fVar1,uVar6);
    fVar4 = (float)param_3;
    W_Line(fVar2,fVar1,fVar4,fVar1,uVar6);
    W_Line(fVar4,fVar1,fVar4,fVar3,uVar6);
    W_Line(fVar4,fVar3,fVar2,fVar3,uVar6);
    return;
  }
  return;
}

/* W_BoxTransAdd16 @ 0x0807f900, 100 bytes */
void W_BoxTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  W_HLineTransAdd16(param_1,param_3,param_2,param_5);
  W_HLineTransAdd16(param_1,param_3,param_4,param_5);
  W_VLineTransAdd16(param_1,param_2,param_4,param_5);
  W_VLineTransAdd16(param_3,param_2,param_4,param_5);
  return;
}

/* W_BoxTransAdd16_B50 @ 0x0807f970, 100 bytes */
void W_BoxTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  W_HLineTransAdd16_B50(param_1,param_3,param_2,param_5);
  W_HLineTransAdd16_B50(param_1,param_3,param_4,param_5);
  W_VLineTransAdd16_B50(param_1,param_2,param_4,param_5);
  W_VLineTransAdd16_B50(param_3,param_2,param_4,param_5);
  return;
}

/* W_BoxTransSub16 @ 0x0807f9e0, 100 bytes */
void W_BoxTransSub16(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  W_HLineTransSub16(param_1,param_3,param_2,param_5);
  W_HLineTransSub16(param_1,param_3,param_4,param_5);
  W_VLineTransSub16(param_1,param_2,param_4,param_5);
  W_VLineTransSub16(param_3,param_2,param_4,param_5);
  return;
}

/* W_BoxTransSub16_B50 @ 0x0807fa50, 100 bytes */
void W_BoxTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  W_HLineTransSub16_B50(param_1,param_3,param_2,param_5);
  W_HLineTransSub16_B50(param_1,param_3,param_4,param_5);
  W_VLineTransSub16_B50(param_1,param_2,param_4,param_5);
  W_VLineTransSub16_B50(param_3,param_2,param_4,param_5);
  return;
}

/* W_BoxFill @ 0x0807fac0, 301 bytes */
void W_BoxFill(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined4 extraout_EDX;
  int iVar4;
  int iVar5;
  int local_18;
  
  iVar5 = param_3;
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_18 = 0;
  uVar2 = MasterPalConvertCol16(param_5);
  if (*(int *)(iVar1 + 0x1c) == 1) {
    (**(code **)(*(int *)(*(int *)(iVar1 + 0x24) + 0x1c) + 0x34))
              (*(int *)(iVar1 + 0x24),param_1,param_2,param_3,param_4,uVar2,extraout_EDX,
               extraout_EDX);
  }
  else {
    local_18 = *(int *)(iVar1 + 0x24);
  }
  if (local_18 != 0) {
    if (param_3 < param_1) {
      param_3 = param_1;
      param_1 = iVar5;
    }
    iVar5 = param_4;
    if (param_4 < param_2) {
      iVar5 = param_2;
      param_2 = param_4;
    }
    if ((((W_x1 <= param_3) && (param_1 <= W_x2)) && (W_y1 <= iVar5)) && (param_2 <= W_y2)) {
      if (param_1 < W_x1) {
        param_1 = W_x1;
      }
      if (W_x2 < param_3) {
        param_3 = W_x2;
      }
      if (param_2 < W_y1) {
        param_2 = W_y1;
      }
      if (W_y2 < iVar5) {
        iVar5 = W_y2;
      }
      if (param_2 <= iVar5) {
        iVar1 = *(int *)(iVar1 + 0x2c);
        do {
          puVar3 = (undefined2 *)(local_18 + *(int *)(iVar1 + param_2 * 4) + param_1 * 2);
          for (iVar4 = (param_3 - param_1) + 1; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar3 = (short)uVar2;
            puVar3 = puVar3 + 1;
          }
          param_2 = param_2 + 1;
        } while (param_2 <= iVar5);
      }
    }
  }
  return;
}

/* W_BoxFillTransAdd16 @ 0x0807fbf0, 443 bytes */
void W_BoxFillTransAdd16(uint param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar5;
  uint uVar7;
  ushort *puVar8;
  int iVar9;
  uint uVar4;
  uint uVar6;
  
  iVar2 = param_4;
  uVar6 = param_1;
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)param_3 < (int)param_1) {
    param_1 = param_3;
    param_3 = uVar6;
  }
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  if ((((W_x1 <= (int)param_3) && ((int)param_1 <= W_x2)) && (W_y1 <= param_4)) && (param_2 <= W_y2)
     ) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)param_3) {
      param_3 = W_x2;
    }
    if (param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < param_4) {
      param_4 = W_y2;
    }
    MasterPalConvertCol16(param_5);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar2 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar2 = *(int *)(iVar1 + 0x24);
    }
    if (iVar2 != 0) {
      for (; param_2 <= param_4; param_2 = param_2 + 1) {
        puVar8 = (ushort *)(iVar2 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4) + param_1 * 2);
        for (iVar9 = (param_3 - param_1) + 1; iVar9 != 0; iVar9 = iVar9 + -1) {
          uVar6 = (uint)*puVar8;
          uVar7 = (param_5 & 0xf800) + (uVar6 & 0xf800);
          if (0xf800 < uVar7) {
            uVar7 = 0xf800;
          }
          uVar4 = (param_5 & 0x7e0) + (uVar6 & 0x7e0);
          uVar3 = (ushort)uVar4;
          if (0x7e0 < uVar4) {
            uVar3 = 0x7e0;
          }
          uVar6 = (param_5 & 0x1f) + (uVar6 & 0x1f);
          uVar5 = (ushort)uVar6;
          if (0x1f < uVar6) {
            uVar5 = 0x1f;
          }
          *puVar8 = (ushort)uVar7 | uVar3 | uVar5;
          puVar8 = puVar8 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransAdd16_B50 @ 0x0807fdb0, 432 bytes */
void W_BoxFillTransAdd16_B50(uint param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar5;
  ushort uVar6;
  ushort *puVar8;
  int iVar9;
  uint uVar4;
  uint uVar7;
  
  iVar3 = param_4;
  uVar7 = param_3;
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)param_3 < (int)param_1) {
    param_3 = param_1;
    param_1 = uVar7;
  }
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar3;
  }
  if ((((W_x1 <= (int)param_3) && ((int)param_1 <= W_x2)) && (W_y1 <= param_4)) && (param_2 <= W_y2)
     ) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)param_3) {
      param_3 = W_x2;
    }
    if (param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < param_4) {
      param_4 = W_y2;
    }
    MasterPalConvertCol16(param_5);
    if (*(int *)(iVar2 + 0x1c) == 1) {
      iVar3 = *(int *)(*(int *)(iVar2 + 0x24) + 0x28);
    }
    else {
      iVar3 = *(int *)(iVar2 + 0x24);
    }
    if (iVar3 != 0) {
      for (; param_2 <= param_4; param_2 = param_2 + 1) {
        puVar8 = (ushort *)(iVar3 + *(int *)(*(int *)(iVar2 + 0x2c) + param_2 * 4) + param_1 * 2);
        for (iVar9 = (param_3 - param_1) + 1; iVar9 != 0; iVar9 = iVar9 + -1) {
          uVar7 = (uint)(*puVar8 >> 1);
          uVar5 = (param_5 & 0xf800) + (uVar7 & 0x7800);
          if (0xf800 < uVar5) {
            uVar5 = 0xf800;
          }
          uVar4 = (uVar7 & 0x3e0) + (param_5 & 0x7e0);
          uVar1 = (ushort)uVar4;
          if (0x7e0 < uVar4) {
            uVar1 = 0x7e0;
          }
          uVar7 = (uVar7 & 0xf) + (param_5 & 0x1f);
          uVar6 = (ushort)uVar7;
          if (0x1f < uVar7) {
            uVar6 = 0x1f;
          }
          *puVar8 = uVar1 | (ushort)uVar5 | uVar6;
          puVar8 = puVar8 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransSub16 @ 0x0807ff60, 439 bytes */
void W_BoxFillTransSub16(uint param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  
  iVar2 = param_4;
  uVar4 = param_1;
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)param_3 < (int)param_1) {
    param_1 = param_3;
    param_3 = uVar4;
  }
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  if ((((W_x1 <= (int)param_3) && ((int)param_1 <= W_x2)) && (W_y1 <= param_4)) && (param_2 <= W_y2)
     ) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)param_3) {
      param_3 = W_x2;
    }
    if (param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < param_4) {
      param_4 = W_y2;
    }
    MasterPalConvertCol16(param_5);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar2 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar2 = *(int *)(iVar1 + 0x24);
    }
    if (iVar2 != 0) {
      for (; param_2 <= param_4; param_2 = param_2 + 1) {
        puVar7 = (ushort *)(iVar2 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4) + param_1 * 2);
        for (iVar8 = (param_3 - param_1) + 1; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar4 = (uint)*puVar7;
          iVar3 = (uVar4 & 0xf800) - (param_5 & 0xf800);
          iVar6 = (uVar4 & 0x7e0) - (param_5 & 0x7e0);
          iVar5 = (uVar4 & 0x1f) - (param_5 & 0x1f);
          *puVar7 = (ushort)iVar3 & -(short)(iVar3 >> 0x1f) - 1U |
                    (ushort)iVar6 & -(short)(iVar6 >> 0x1f) - 1U |
                    (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U;
          puVar7 = puVar7 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransSub16_B50 @ 0x08080120, 442 bytes */
void W_BoxFillTransSub16_B50(uint param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  
  iVar2 = param_4;
  uVar4 = param_1;
  iVar1 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)param_3 < (int)param_1) {
    param_1 = param_3;
    param_3 = uVar4;
  }
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  if ((((W_x1 <= (int)param_3) && ((int)param_1 <= W_x2)) && (W_y1 <= param_4)) && (param_2 <= W_y2)
     ) {
    if ((int)param_1 < W_x1) {
      param_1 = W_x1;
    }
    if (W_x2 < (int)param_3) {
      param_3 = W_x2;
    }
    if (param_2 < W_y1) {
      param_2 = W_y1;
    }
    if (W_y2 < param_4) {
      param_4 = W_y2;
    }
    MasterPalConvertCol16(param_5);
    if (*(int *)(iVar1 + 0x1c) == 1) {
      iVar2 = *(int *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
    else {
      iVar2 = *(int *)(iVar1 + 0x24);
    }
    if (iVar2 != 0) {
      for (; param_2 <= param_4; param_2 = param_2 + 1) {
        puVar7 = (ushort *)(iVar2 + *(int *)(*(int *)(iVar1 + 0x2c) + param_2 * 4) + param_1 * 2);
        for (iVar8 = (param_3 - param_1) + 1; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar4 = (uint)(*puVar7 >> 1);
          iVar3 = (uVar4 & 0x7800) - (param_5 & 0xf800);
          iVar6 = (uVar4 & 0x3e0) - (param_5 & 0x7e0);
          iVar5 = (uVar4 & 0xf) - (param_5 & 0x1f);
          *puVar7 = (ushort)iVar3 & -(short)(iVar3 >> 0x1f) - 1U |
                    (ushort)iVar6 & -(short)(iVar6 >> 0x1f) - 1U |
                    (ushort)iVar5 & -(short)(iVar5 >> 0x1f) - 1U;
          puVar7 = puVar7 + 1;
        }
      }
    }
  }
  return;
}

