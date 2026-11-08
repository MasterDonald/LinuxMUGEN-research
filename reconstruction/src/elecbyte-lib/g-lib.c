/*
 * g-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08052a50-0x08053905, 18 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* G_Init @ 0x08052a50, 69 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
bool G_Init(void)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  TempStore = (int)malloc(0x1000);
  if (((void *)TempStore != (void *)0x0) && (iVar2 = Trig_Init(), iVar2 != 0)) {
    bVar1 = MasterPalInit();
    return GHIDRA_ZEXT8(bVar1) != 0;
  }
  ErrorSet(3);
  return false;
}

/* G_DeInit @ 0x08052aa0, 95 bytes */
undefined4 G_DeInit(void)

{
  if (G_ScreenPage[0] != 0) {
    destroy_bitmap((int *)G_ScreenPage[0]);
  }
  if (G_ScreenPage[1] != 0) {
    destroy_bitmap((int *)G_ScreenPage[1]);
  }
  MasterPalDeInit();
  if (TempStore != 0) {
    free((void *)TempStore);
  }
  TempStore = 0;
  Trig_DeInit();
  return 1;
}

/* G_SetRenderMode @ 0x08052b00, 29 bytes */
undefined4 G_SetRenderMode(int param_1)

{
  if ((param_1 < 3) && (-1 < param_1)) {
    G_RenderMode = param_1;
    return 1;
  }
  return 0;
}

/* G_SetMode @ 0x08052b20, 405 bytes */
undefined4 G_SetMode(uint param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (G_ScreenPage[0] != 0) {
    destroy_bitmap((int *)G_ScreenPage[0]);
  }
  if (G_ScreenPage[1] != 0) {
    destroy_bitmap((int *)G_ScreenPage[1]);
  }
  G_ScreenPage[1] = 0;
  G_ScreenPage[0] = 0;
  G_Screenptr = (int *)0x0;
  G_BlitMode = 0;
  G_BlitModeAuto = 0;
  set_color_depth(8);
  if (param_1 != 0xffffffff) {
    set_color_depth(param_4);
  }
  iVar1 = set_gfx_mode(param_1,param_2,param_3,0,0);
  if (iVar1 < 0) {
    ErrorSet(4);
    uVar2 = 0;
  }
  else {
    G_Capabilities = (int)((gfx_capabilities & 1) != 0);
    if ((gfx_capabilities & 2) != 0) {
      G_Capabilities = G_Capabilities | 2;
    }
    S_Width = param_2;
    S_Size = param_2 * param_3;
    S_Height = param_3;
    G_ColDepth = param_4;
    switch(param_4) {
    case 8:
      G_BytesPerPixel = 1;
      break;
    default:
      G_BytesPerPixel = 2;
      break;
    case 0x18:
      G_BytesPerPixel = 3;
      break;
    case 0x20:
      G_BytesPerPixel = 4;
    }
    G_CurMode = param_1;
    V_ColDepth = param_4;
    V_BytesPerPixel = G_BytesPerPixel;
    G_Screenptr = screen;
    uVar2 = 1;
    scrRGB16toBGR32 = 0;
  }
  return uVar2;
}

/* G_MakeColor @ 0x08052cc0, 5 bytes
 * REVIEW: calls-missing-in-pid:makecol_depth */
undefined4 G_MakeColor(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = makecol(param_1,param_2,param_3);
  return uVar1;
}

/* G_SetRGBtoBGR @ 0x08052cd0, 56 bytes */
void G_SetRGBtoBGR(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = _rgb_r_shift_16;
  if ((scrRGB16toBGR32 == 0) != (param_1 == 0)) {
    scrRGB16toBGR32 = param_1;
    _rgb_r_shift_16 = _rgb_b_shift_16;
    _rgb_b_shift_16 = uVar1;
  }
  return;
}

/* G_SetBlitMode @ 0x08052d10, 310 bytes */
undefined4 G_SetBlitMode(int param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  
  if (param_1 != G_BlitMode) {
    if (G_ScreenPage[0] != 0) {
      destroy_bitmap((int *)G_ScreenPage[0]);
    }
    if (G_ScreenPage[1] != 0) {
      destroy_bitmap((int *)G_ScreenPage[1]);
    }
    G_Screenptr = screen;
    G_ScreenPage[1] = 0;
    G_ScreenPage[0] = 0;
    if (param_1 != 0) {
      if ((param_1 != 1) || (piVar1 = create_video_bitmap(S_Width,S_Height), piVar1 == (int *)0x0))
      {
        return 0;
      }
      piVar2 = create_video_bitmap(S_Width,S_Height);
      if (piVar2 == (int *)0x0) {
        destroy_bitmap(piVar1);
        return 0;
      }
      G_Screenptr = piVar2;
      G_ScreenPage[0] = (int)piVar1;
      G_ScreenPage[1] = (int)piVar2;
      (**(code **)(piVar1[7] + 0x94))(piVar1,0,piVar2,piVar2);
      (**(code **)(piVar2[7] + 0x94))(piVar2,0);
    }
    G_BlitMode = param_1;
    G_BlitModeAuto = param_2 & (param_1 == 0) - 1;
  }
  return 1;
}

/* G_PageFlip @ 0x08052e50, 76 bytes */
void G_PageFlip(void)

{
  bool bVar1;
  
  if (G_BlitMode == 1) {
    if ((G_Screenptr == (int *)G_ScreenPage[0]) || (G_Screenptr == (int *)G_ScreenPage[1])) {
      show_video_bitmap(G_Screenptr);
    }
    bVar1 = G_Screenptr == (int *)G_ScreenPage[0];
    G_Screenptr = (int *)G_ScreenPage[0];
    if (bVar1) {
      G_Screenptr = (int *)G_ScreenPage[1];
    }
  }
  return;
}

/* VGA_Cls @ 0x08052ea0, 24 bytes */
void VGA_Cls(void)

{
  (**(code **)(*(int *)(screen + 0x1c) + 0x94))(screen,0);
  return;
}

/* VRetrace @ 0x08052ec0, 5 bytes */
undefined4 VRetrace(void)

{
  undefined4 uVar1;
  
  uVar1 = vsync();
  return uVar1;
}

/* sgn @ 0x08052ed0, 24 bytes */
int sgn(uint param_1)

{
  if (0 < (int)param_1) {
    return 1;
  }
  return -1 - ((int)(param_1 ^ 0xffffffff) >> 0x1f);
}

/* GetDrawType @ 0x08052ef0, 205 bytes */
undefined4 GetDrawType(char *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = _alemu_stricmp(param_1,"none");
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = _alemu_stricmp(param_1,"add");
    uVar2 = 1;
    if (iVar1 != 0) {
      iVar1 = _alemu_stricmp(param_1,"addalpha");
      uVar2 = 3;
      if (iVar1 != 0) {
        iVar1 = _alemu_stricmp(param_1,"add1");
        if (iVar1 == 0) {
          uVar2 = 3;
          *param_2 = 0x100;
          *param_3 = 0x80;
        }
        else {
          iVar1 = _alemu_stricmp(param_1,"sub");
          uVar2 = 2;
          if (iVar1 != 0) {
            if ((*param_1 == '\0') || (iVar1 = _alemu_stricmp(param_1,"default"), iVar1 == 0)) {
              uVar2 = 0xffffffff;
            }
            else {
              uVar2 = 0xfffffffe;
            }
          }
        }
      }
    }
  }
  return uVar2;
}

/* Trig_Init @ 0x08052fc0, 183 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts) */
undefined4 Trig_Init(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  longdouble lVar4;
  
  if (SinTable == (int *)0x0) {
    SinTable = malloc(0x3840);
  }
  iVar3 = 0;
  if (SinTable == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    do {
      lVar4 = (longdouble)
              fsin((longdouble)iVar3 * (longdouble)((double)0.01745329238474369) * (longdouble)0.125);
      SinTable[iVar3] = (int)GHIDRA_FIST32(lVar4 * (longdouble)1024.0);
      piVar1 = SinTable;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xe10);
    *SinTable = 0;
    piVar1[0x2d0] = 0x400;
    piVar1[0x5a0] = 0;
    piVar1[0x870] = -0x400;
    piVar1[0xb40] = 0;
    uVar2 = 1;
  }
  return uVar2;
}

/* Trig_DeInit @ 0x08053080, 33 bytes */
undefined4 Trig_DeInit(void)

{
  if (SinTable != (int *)0x0) {
    free(SinTable);
  }
  return 1;
}

/* V_DoubleRes @ 0x080530b0, 154 bytes */
void V_DoubleRes(uint *param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  uVar5 = param_1[1];
  iVar4 = *(int *)param_1[7];
  if ((((iVar4 == 0xf) || (iVar4 == 0x10)) &&
      ((iVar3 = **(int **)(param_2 + 0x1c), iVar3 == 0xf || (iVar3 == 0x10)))) &&
     ((iVar4 == iVar3 && ((*param_1 & 3) == 0)))) {
    puVar11 = *(undefined4 **)(param_2 + 0x28);
    uVar6 = *param_1 >> 2;
    puVar8 = (undefined2 *)param_1[10];
    uVar7 = uVar6;
    do {
      do {
        uVar1 = *puVar8;
        uVar2 = puVar8[1];
        puVar9 = puVar8 + 4;
        *(undefined2 *)puVar11 = uVar1;
        *(undefined2 *)((int)puVar11 + 2) = uVar1;
        uVar1 = puVar8[2];
        *(undefined2 *)(puVar11 + 1) = uVar2;
        *(undefined2 *)((int)puVar11 + 6) = uVar2;
        uVar2 = puVar8[3];
        *(undefined2 *)(puVar11 + 2) = uVar1;
        *(undefined2 *)((int)puVar11 + 10) = uVar1;
        *(undefined2 *)(puVar11 + 3) = uVar2;
        *(undefined2 *)((int)puVar11 + 0xe) = uVar2;
        puVar11 = puVar11 + 4;
        uVar6 = uVar6 - 1;
        puVar8 = puVar9;
      } while (uVar6 != 0);
      puVar10 = puVar11 + uVar7 * -4;
      for (iVar4 = uVar7 * 4; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      uVar6 = uVar7 & 0xfffffff;
      uVar5 = uVar5 - 1;
      uVar7 = uVar6;
    } while (uVar5 != 0);
  }
  return;
}

/* V_DoubleResDiag @ 0x08053150, 698 bytes
 * FIXUP: 2 exact-text site patches*/
void V_DoubleResDiag(int *param_1,int param_2)

{
  undefined2 uVar1;
  short sVar2;
  undefined2 *puVar3;
  short *psVar4;
  short *puVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *(int *)param_1[7];
  if ((((iVar7 == 0xf) || (iVar7 == 0x10)) &&
      ((iVar8 = **(int **)(param_2 + 0x1c), iVar8 == 0xf || (iVar8 == 0x10)))) && (iVar7 == iVar8))
  {
    puVar5 = (short *)param_1[10];
    puVar3 = *(undefined2 **)(param_2 + 0x28);
    uVar1 = *puVar5;
    *puVar3 = uVar1;
    puVar3[1] = uVar1;
    puVar3[0x280] = uVar1;
    puVar3[0x281] = uVar1;
    if (puVar5[1] == puVar5[0x140]) {
      puVar3[0x281] = puVar5[1];
    }
    puVar5 = puVar5 + 1;
    puVar3 = puVar3 + 2;
    if (1 < *param_1 + -1) {
      iVar7 = *param_1 + -2;
      do {
        uVar1 = *puVar5;
        *puVar3 = uVar1;
        puVar3[1] = uVar1;
        puVar3[0x280] = uVar1;
        puVar3[0x281] = uVar1;
        sVar2 = puVar5[0x140];
        if (puVar5[-1] == sVar2) {
          puVar3[0x280] = puVar5[-1];
          sVar2 = puVar5[0x140];
        }
        if (puVar5[1] == sVar2) {
          puVar3[0x281] = puVar5[1];
        }
        puVar5 = puVar5 + 1;
        puVar3 = puVar3 + 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    uVar1 = *puVar5;
    *puVar3 = uVar1;
    puVar3[1] = uVar1;
    puVar3[0x280] = uVar1;
    puVar3[0x281] = uVar1;
    if (puVar5[-1] == puVar5[0x140]) {
      puVar3[0x280] = puVar5[-1];
    }
    psVar6 = puVar5 + 1;
    psVar4 = puVar3 + 0x282;
    if (1 < param_1[1] + -1) {
      iVar7 = param_1[1] + -2;
      do {
        sVar2 = *psVar6;
        *psVar4 = sVar2;
        psVar4[1] = sVar2;
        psVar4[0x280] = sVar2;
        psVar4[0x281] = sVar2;
        sVar2 = psVar6[1];
        if (sVar2 == psVar6[-0x140]) {
          psVar4[1] = sVar2;
        }
        if (sVar2 == psVar6[0x140]) {
          psVar4[0x281] = sVar2;
        }
        psVar6 = psVar6 + 1;
        psVar4 = psVar4 + 2;
        if (1 < *param_1 + -1) {
          iVar8 = *param_1 + -2;
          do {
            sVar2 = *psVar6;
            *psVar4 = sVar2;
            psVar4[1] = sVar2;
            psVar4[0x280] = sVar2;
            psVar4[0x281] = sVar2;
            sVar2 = psVar6[-1];
            if (sVar2 == psVar6[-0x140]) {
              *psVar4 = sVar2;
            }
            if (sVar2 == psVar6[0x140]) {
              psVar4[0x280] = sVar2;
            }
            sVar2 = psVar6[1];
            if (sVar2 == psVar6[-0x140]) {
              psVar4[1] = sVar2;
            }
            if (sVar2 == psVar6[0x140]) {
              psVar4[0x281] = sVar2;
            }
            psVar6 = psVar6 + 1;
            psVar4 = psVar4 + 2;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        sVar2 = *psVar6;
        *psVar4 = sVar2;
        psVar4[1] = sVar2;
        psVar4[0x280] = sVar2;
        psVar4[0x281] = sVar2;
        sVar2 = psVar6[-1];
        if (sVar2 == psVar6[-0x140]) {
          *psVar4 = sVar2;
        }
        if (sVar2 == psVar6[0x140]) {
          psVar4[0x280] = sVar2;
        }
        psVar6 = psVar6 + 1;
        psVar4 = psVar4 + 0x282;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    sVar2 = *psVar6;
    *psVar4 = sVar2;
    psVar4[1] = sVar2;
    psVar4[0x280] = sVar2;
    psVar4[0x281] = sVar2;
    if (psVar6[1] == psVar6[-0x140]) {
      psVar4[1] = psVar6[1];
    }
    psVar6 = psVar6 + 1;
    psVar4 = psVar4 + 2;
    if (1 < *param_1 + -1) {
      iVar7 = *param_1 + -2;
      do {
        sVar2 = *psVar6;
        *psVar4 = sVar2;
        psVar4[1] = sVar2;
        psVar4[0x280] = sVar2;
        psVar4[0x281] = sVar2;
        sVar2 = psVar6[-0x140];
        if (psVar6[-1] == sVar2) {
          *psVar4 = psVar6[-1];
          sVar2 = psVar6[-0x140];
        }
        if (psVar6[1] == sVar2) {
          psVar4[1] = psVar6[1];
        }
        psVar6 = psVar6 + 1;
        psVar4 = psVar4 + 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    sVar2 = *psVar6;
    *psVar4 = sVar2;
    psVar4[1] = sVar2;
    psVar4[0x280] = sVar2;
    psVar4[0x281] = sVar2;
    if (psVar6[-1] == psVar6[-0x140]) {
      *psVar4 = psVar6[-1];
    }
  }
  return;
}

/* V_DoubleResBlur @ 0x08053410, 1131 bytes */
void V_DoubleResBlur(int *param_1,int param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short *psVar8;
  short *psVar9;
  short *local_1c;
  int local_18;
  int local_14;
  
  iVar3 = *(int *)param_1[7];
  if ((((iVar3 == 0xf) || (iVar3 == 0x10)) &&
      ((iVar4 = **(int **)(param_2 + 0x1c), iVar4 == 0xf || (iVar4 == 0x10)))) && (iVar3 == iVar4))
  {
    local_1c = *(short **)(param_2 + 0x28);
    psVar9 = (short *)param_1[10];
    sVar1 = psVar9[1];
    sVar2 = psVar9[0x140];
    psVar8 = psVar9 + 1;
    sVar5 = (short)((int)((int)*psVar9 & 0xf7deU) >> 1);
    *local_1c = sVar5 * 2;
    sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
    local_1c[1] = sVar5 + sVar1 * 2;
    sVar2 = (short)((int)((int)sVar2 & 0xe79cU) >> 2);
    local_1c[0x280] = sVar5 + sVar2 * 2;
    local_1c[0x281] = sVar1 + sVar5 + sVar2;
    local_1c = local_1c + 2;
    if (1 < *param_1 + -1) {
      local_14 = *param_1 + -2;
      do {
        sVar1 = psVar8[1];
        sVar2 = psVar8[0x140];
        sVar6 = (short)((int)((int)psVar8[-1] & 0xe79cU) >> 2);
        sVar5 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
        *local_1c = sVar5 + sVar6 * 2;
        sVar7 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
        local_1c[1] = sVar5 + sVar7 * 2;
        psVar8 = psVar8 + 1;
        sVar1 = (short)((int)((int)sVar2 & 0xe79cU) >> 2);
        local_1c[0x280] = sVar6 + sVar5 + sVar1;
        local_1c[0x281] = sVar7 + sVar5 + sVar1;
        local_1c = local_1c + 2;
        local_14 = local_14 + -1;
      } while (local_14 != 0);
    }
    sVar1 = psVar8[-1];
    sVar2 = psVar8[0x140];
    sVar5 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
    *local_1c = sVar5 * 2;
    sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
    local_1c[1] = sVar5 + sVar1 * 2;
    sVar2 = (short)((int)((int)sVar2 & 0xe79cU) >> 2);
    local_1c[0x280] = sVar5 + sVar2 * 2;
    psVar8 = psVar8 + 1;
    local_1c[0x281] = sVar1 + sVar5 + sVar2;
    local_1c = local_1c + 0x282;
    if (1 < param_1[1] + -1) {
      local_18 = param_1[1] + -2;
      iVar3 = *param_1;
      do {
        sVar1 = psVar8[1];
        sVar2 = psVar8[0x140];
        sVar6 = (short)((int)((int)psVar8[-0x140] & 0xe79cU) >> 2);
        sVar5 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
        *local_1c = sVar5 + sVar6 * 2;
        sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
        psVar8 = psVar8 + 1;
        local_1c[1] = sVar1 + sVar5 + sVar6;
        sVar2 = (short)((int)((int)sVar2 & 0xe79cU) >> 2);
        local_1c[0x280] = sVar5 + sVar2 * 2;
        local_1c[0x281] = sVar2 + sVar5 + sVar1;
        local_1c = local_1c + 2;
        if (1 < iVar3 + -1) {
          local_14 = iVar3 + -2;
          do {
            sVar1 = psVar8[0x140];
            sVar2 = psVar8[1];
            psVar9 = psVar8 + -0x140;
            sVar6 = (short)((int)((int)psVar8[-1] & 0xe79cU) >> 2);
            sVar7 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
            psVar8 = psVar8 + 1;
            sVar5 = (short)((int)((int)*psVar9 & 0xe79cU) >> 2);
            *local_1c = sVar6 + sVar7 + sVar5;
            sVar2 = (short)((int)((int)sVar2 & 0xe79cU) >> 2);
            local_1c[1] = sVar2 + sVar7 + sVar5;
            sVar7 = (short)((int)((int)sVar1 & 0xe79cU) >> 2) + sVar7;
            local_1c[0x280] = sVar6 + sVar7;
            local_1c[0x281] = sVar7 + sVar2;
            local_1c = local_1c + 2;
            local_14 = local_14 + -1;
          } while (local_14 != 0);
        }
        sVar1 = psVar8[0x140];
        sVar5 = (short)((int)((int)psVar8[-1] & 0xe79cU) >> 2);
        sVar6 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
        sVar2 = (short)((int)((int)psVar8[-0x140] & 0xe79cU) >> 2);
        psVar8 = psVar8 + 1;
        *local_1c = sVar5 + sVar6 + sVar2;
        local_1c[1] = sVar6 + sVar2 * 2;
        sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
        local_1c[0x280] = sVar1 + sVar6 + sVar5;
        local_1c[0x281] = sVar6 + sVar1 * 2;
        local_1c = local_1c + 0x282;
        local_18 = local_18 + -1;
      } while (local_18 != 0);
    }
    sVar1 = psVar8[1];
    psVar9 = psVar8 + 1;
    sVar5 = (short)((int)((int)psVar8[-0x140] & 0xe79cU) >> 2);
    sVar2 = (short)((int)((int)*psVar8 & 0xf7deU) >> 1);
    *local_1c = sVar2 + sVar5 * 2;
    sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
    local_1c[1] = sVar1 + sVar2 + sVar5;
    local_1c[0x280] = sVar2 * 2;
    local_1c[0x281] = sVar2 + sVar1 * 2;
    local_1c = local_1c + 2;
    if (1 < *param_1 + -1) {
      local_14 = *param_1 + -2;
      do {
        sVar1 = psVar9[1];
        sVar5 = (short)((int)((int)psVar9[-1] & 0xe79cU) >> 2);
        sVar6 = (short)((int)((int)*psVar9 & 0xf7deU) >> 1);
        sVar2 = (short)((int)((int)psVar9[-0x140] & 0xe79cU) >> 2);
        psVar9 = psVar9 + 1;
        *local_1c = sVar5 + sVar6 + sVar2;
        sVar1 = (short)((int)((int)sVar1 & 0xe79cU) >> 2);
        local_1c[1] = sVar1 + sVar6 + sVar2;
        local_1c[0x280] = sVar6 + sVar5 * 2;
        local_1c[0x281] = sVar6 + sVar1 * 2;
        local_1c = local_1c + 2;
        local_14 = local_14 + -1;
      } while (local_14 != 0);
    }
    sVar2 = (short)((int)((int)psVar9[-1] & 0xe79cU) >> 2);
    sVar5 = (short)((int)((int)*psVar9 & 0xf7deU) >> 1);
    sVar1 = (short)((int)((int)psVar9[-0x140] & 0xe79cU) >> 2);
    *local_1c = sVar2 + sVar5 + sVar1;
    local_1c[1] = sVar5 + sVar1 * 2;
    local_1c[0x280] = sVar5 + sVar2 * 2;
    local_1c[0x281] = sVar5 * 2;
  }
  return;
}

/* V_DoubleResLines @ 0x08053880, 133 bytes */
void V_DoubleResLines(uint *param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  
  iVar3 = *(int *)param_1[7];
  if ((((iVar3 == 0xf) || (iVar3 == 0x10)) &&
      ((iVar4 = **(int **)(param_2 + 0x1c), iVar4 == 0xf || (iVar4 == 0x10)))) && (iVar3 == iVar4))
  {
    uVar5 = *param_1;
    uVar7 = param_1[1];
    uVar6 = uVar5 >> 2;
    puVar8 = (undefined2 *)param_1[10];
    puVar9 = *(undefined2 **)(param_2 + 0x28);
    do {
      do {
        puVar10 = puVar9;
        uVar1 = *puVar8;
        uVar2 = puVar8[1];
        puVar9 = puVar8 + 4;
        *puVar10 = uVar1;
        puVar10[1] = uVar1;
        uVar1 = puVar8[2];
        puVar10[2] = uVar2;
        puVar10[3] = uVar2;
        uVar2 = puVar8[3];
        puVar10[4] = uVar1;
        puVar10[5] = uVar1;
        puVar10[6] = uVar2;
        puVar10[7] = uVar2;
        uVar6 = uVar6 - 1;
        puVar8 = puVar9;
        puVar9 = puVar10 + 8;
      } while (uVar6 != 0);
      uVar7 = uVar7 - 1;
      uVar6 = uVar5 >> 2;
      puVar9 = puVar10 + 0x288;
    } while (uVar7 != 0);
  }
  return;
}

