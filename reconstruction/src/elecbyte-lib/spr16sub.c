/*
 * spr16sub.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08072060-0x0807af34, 16 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* W_PutSpriteTransSub8to16 @ 0x08072060, 665 bytes */
void W_PutSpriteTransSub8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  ushort *puVar15;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_30;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_40 = 0;
  iVar10 = param_4 - piVar1[3];
  local_48 = 0;
  iVar12 = param_3 - piVar1[2];
  if ((((iVar10 <= W_y2) && (W_y1 < piVar1[1] + iVar10)) && (iVar12 <= W_x2)) &&
     (W_x1 < *piVar1 + iVar12)) {
    local_3c = iVar10;
    if (iVar10 < W_y1) {
      local_3c = W_y1;
      local_40 = W_y1 - iVar10;
    }
    iVar10 = piVar1[1] + iVar10 + -1;
    if (W_y2 < iVar10) {
      iVar10 = W_y2;
    }
    local_44 = iVar12;
    if (iVar12 < W_x1) {
      local_44 = W_x1;
      local_48 = W_x1 - iVar12;
    }
    iVar12 = *piVar1 + iVar12 + -1;
    if (W_x2 < iVar12) {
      iVar12 = W_x2;
    }
    iVar12 = (iVar12 - local_44) + 1;
    iVar10 = (iVar10 - local_3c) + 1;
    if (((0 < iVar12) && (0 < iVar10)) &&
       (iVar3 = SpriteDecompGetAndLockData(param_1,param_2), iVar3 != 0)) {
      iVar4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar5 = (int *)param_1[5];
      if (piVar5 == (int *)0x0) {
        piVar5 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar1[0xc]);
      }
      else {
        EBPalUpdate(piVar5);
      }
      local_30 = 0;
      if (0 < iVar10) {
        do {
          pbVar6 = (byte *)(iVar3 + *(int *)(piVar1[0xb] + (local_40 + local_30) * 4) + local_48);
          puVar15 = (ushort *)
                    (iVar4 + *(int *)(*(int *)(iVar2 + 0x2c) + (local_3c + local_30) * 4) +
                    local_44 * 2);
          for (iVar13 = iVar12; iVar13 != 0; iVar13 = iVar13 + -1) {
            if (*pbVar6 != 0) {
              uVar14 = (uint)*(short *)((int)piVar5 + (uint)*pbVar6 * 2 + 0x5c);
              uVar8 = (uint)*puVar15;
              iVar7 = (uVar8 & 0xf800) - (uVar14 & 0xf800);
              iVar11 = (uVar8 & 0x7e0) - (uVar14 & 0x7e0);
              iVar9 = (uVar8 & 0x1f) - (uVar14 & 0x1f);
              *puVar15 = (ushort)iVar7 & -(short)(iVar7 >> 0x1f) - 1U |
                         (ushort)iVar11 & -(short)(iVar11 >> 0x1f) - 1U |
                         (ushort)iVar9 & 0xffffU - (short)(iVar9 >> 0x1f);
            }
            puVar15 = puVar15 + 1;
            pbVar6 = pbVar6 + 1;
          }
          local_30 = local_30 + 1;
        } while (local_30 < iVar10);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirH8to16 @ 0x08072300, 685 bytes */
void W_PutSpriteTransSubMirH8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  ushort *puVar15;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_30;
  byte *local_2c;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar3 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = *piVar2;
  local_40 = 0;
  iVar4 = (piVar2[2] - iVar1) + 1 + param_3;
  iVar11 = param_4 - piVar2[3];
  local_48 = 0;
  if ((((iVar11 <= W_y2) && (W_y1 < piVar2[1] + iVar11)) && (iVar4 <= W_x2)) &&
     (W_x1 < iVar1 + iVar4)) {
    local_3c = iVar11;
    if (iVar11 < W_y1) {
      local_3c = W_y1;
      local_40 = W_y1 - iVar11;
    }
    iVar11 = piVar2[1] + iVar11 + -1;
    if (W_y2 < iVar11) {
      iVar11 = W_y2;
    }
    local_44 = iVar4;
    if (iVar4 < W_x1) {
      local_44 = W_x1;
      local_48 = W_x1 - iVar4;
    }
    iVar4 = iVar1 + iVar4 + -1;
    if (W_x2 < iVar4) {
      iVar4 = W_x2;
    }
    iVar4 = (iVar4 - local_44) + 1;
    iVar11 = (iVar11 - local_3c) + 1;
    if (((0 < iVar4) && (0 < iVar11)) &&
       (iVar5 = SpriteDecompGetAndLockData(param_1,param_2), iVar5 != 0)) {
      iVar6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar7 = (int *)param_1[5];
      if (piVar7 == (int *)0x0) {
        piVar7 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar2[0xc]);
      }
      else {
        EBPalUpdate(piVar7);
      }
      local_30 = 0;
      if (0 < iVar11) {
        do {
          local_2c = (byte *)((iVar5 + *(int *)(piVar2[0xb] + (local_40 + local_30) * 4) + iVar1) -
                             local_48);
          puVar15 = (ushort *)
                    (iVar6 + *(int *)(*(int *)(iVar3 + 0x2c) + (local_3c + local_30) * 4) +
                    local_44 * 2);
          for (iVar13 = iVar4; iVar13 != 0; iVar13 = iVar13 + -1) {
            local_2c = local_2c + -1;
            if (*local_2c != 0) {
              uVar9 = (uint)*puVar15;
              uVar14 = (uint)*(short *)((int)piVar7 + (uint)*local_2c * 2 + 0x5c);
              iVar8 = (uVar9 & 0xf800) - (uVar14 & 0xf800);
              iVar12 = (uVar9 & 0x7e0) - (uVar14 & 0x7e0);
              iVar10 = (uVar9 & 0x1f) - (uVar14 & 0x1f);
              *puVar15 = (ushort)iVar8 & -(short)(iVar8 >> 0x1f) - 1U |
                         (ushort)iVar12 & -(short)(iVar12 >> 0x1f) - 1U |
                         (ushort)iVar10 & -(short)(iVar10 >> 0x1f) - 1U;
            }
            puVar15 = puVar15 + 1;
          }
          local_30 = local_30 + 1;
        } while (local_30 < iVar11);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirV8to16 @ 0x080725b0, 685 bytes */
void W_PutSpriteTransSubMirV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_30;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar3 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_40 = 0;
  iVar1 = piVar2[1];
  iVar13 = param_3 - piVar2[2];
  iVar9 = (piVar2[3] - iVar1) + 1 + param_4;
  local_48 = 0;
  if ((((iVar9 <= W_y2) && (W_y1 < iVar1 + iVar9)) && (iVar13 <= W_x2)) && (W_x1 < *piVar2 + iVar13)
     ) {
    local_3c = iVar9;
    if (iVar9 < W_y1) {
      local_3c = W_y1;
      local_40 = W_y1 - iVar9;
    }
    iVar9 = iVar1 + iVar9 + -1;
    if (W_y2 < iVar9) {
      iVar9 = W_y2;
    }
    local_44 = iVar13;
    if (iVar13 < W_x1) {
      local_44 = W_x1;
      local_48 = W_x1 - iVar13;
    }
    iVar13 = *piVar2 + iVar13 + -1;
    if (W_x2 < iVar13) {
      iVar13 = W_x2;
    }
    iVar13 = (iVar13 - local_44) + 1;
    iVar9 = (iVar9 - local_3c) + 1;
    if (((0 < iVar13) && (0 < iVar9)) &&
       (iVar4 = SpriteDecompGetAndLockData(param_1,param_2), iVar4 != 0)) {
      iVar5 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar6 = (int *)param_1[5];
      if (piVar6 == (int *)0x0) {
        piVar6 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar2[0xc]);
      }
      else {
        EBPalUpdate(piVar6);
      }
      local_30 = 0;
      if (0 < iVar9) {
        do {
          pbVar7 = (byte *)(iVar4 + *(int *)(piVar2[0xb] + -4 + ((iVar1 - local_40) - local_30) * 4)
                           + local_48);
          puVar16 = (ushort *)
                    (iVar5 + *(int *)(*(int *)(iVar3 + 0x2c) + (local_3c + local_30) * 4) +
                    local_44 * 2);
          for (iVar14 = iVar13; iVar14 != 0; iVar14 = iVar14 + -1) {
            if (*pbVar7 != 0) {
              uVar15 = (uint)*(short *)((int)piVar6 + (uint)*pbVar7 * 2 + 0x5c);
              uVar10 = (uint)*puVar16;
              iVar8 = (uVar10 & 0xf800) - (uVar15 & 0xf800);
              iVar12 = (uVar10 & 0x7e0) - (uVar15 & 0x7e0);
              iVar11 = (uVar10 & 0x1f) - (uVar15 & 0x1f);
              *puVar16 = (ushort)iVar8 & -(short)(iVar8 >> 0x1f) - 1U |
                         (ushort)iVar12 & -(short)(iVar12 >> 0x1f) - 1U |
                         (ushort)iVar11 & -(short)(iVar11 >> 0x1f) - 1U;
            }
            puVar16 = puVar16 + 1;
            pbVar7 = pbVar7 + 1;
          }
          local_30 = local_30 + 1;
        } while (local_30 < iVar9);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirHV8to16 @ 0x08072860, 713 bytes */
void W_PutSpriteTransSubMirHV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_30;
  byte *local_2c;
  
  piVar3 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar4 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = *piVar3;
  iVar2 = piVar3[1];
  local_40 = 0;
  iVar5 = (piVar3[2] - iVar1) + 1 + param_3;
  local_48 = 0;
  iVar10 = (piVar3[3] - iVar2) + 1 + param_4;
  if ((((iVar10 <= W_y2) && (W_y1 < iVar2 + iVar10)) && (iVar5 <= W_x2)) && (W_x1 < iVar1 + iVar5))
  {
    local_3c = iVar10;
    if (iVar10 < W_y1) {
      local_3c = W_y1;
      local_40 = W_y1 - iVar10;
    }
    iVar10 = iVar2 + iVar10 + -1;
    if (W_y2 < iVar10) {
      iVar10 = W_y2;
    }
    local_44 = iVar5;
    if (iVar5 < W_x1) {
      local_44 = W_x1;
      local_48 = W_x1 - iVar5;
    }
    iVar5 = iVar1 + iVar5 + -1;
    if (W_x2 < iVar5) {
      iVar5 = W_x2;
    }
    iVar5 = (iVar5 - local_44) + 1;
    iVar10 = (iVar10 - local_3c) + 1;
    if (((0 < iVar5) && (0 < iVar10)) &&
       (iVar6 = SpriteDecompGetAndLockData(param_1,param_2), iVar6 != 0)) {
      iVar7 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar8 = (int *)param_1[5];
      if (piVar8 == (int *)0x0) {
        piVar8 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar3[0xc]);
      }
      else {
        EBPalUpdate(piVar8);
      }
      local_30 = 0;
      if (0 < iVar10) {
        do {
          local_2c = (byte *)((iVar6 + *(int *)(piVar3[0xb] + -4 +
                                               ((iVar2 - local_40) - local_30) * 4) + iVar1) -
                             local_48);
          puVar16 = (ushort *)
                    (iVar7 + *(int *)(*(int *)(iVar4 + 0x2c) + (local_3c + local_30) * 4) +
                    local_44 * 2);
          for (iVar14 = iVar5; iVar14 != 0; iVar14 = iVar14 + -1) {
            local_2c = local_2c + -1;
            if (*local_2c != 0) {
              uVar15 = (uint)*(short *)((int)piVar8 + (uint)*local_2c * 2 + 0x5c);
              uVar11 = (uint)*puVar16;
              iVar9 = (uVar11 & 0xf800) - (uVar15 & 0xf800);
              iVar13 = (uVar11 & 0x7e0) - (uVar15 & 0x7e0);
              iVar12 = (uVar11 & 0x1f) - (uVar15 & 0x1f);
              *puVar16 = (ushort)iVar9 & -(short)(iVar9 >> 0x1f) - 1U |
                         (ushort)iVar13 & -(short)(iVar13 >> 0x1f) - 1U |
                         (ushort)iVar12 & -(short)(iVar12 >> 0x1f) - 1U;
            }
            puVar16 = puVar16 + 1;
          }
          local_30 = local_30 + 1;
        } while (local_30 < iVar10);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_ScaleSpriteTransSub8to16 @ 0x08072b30, 2421 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransSub8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  byte *pbVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint *puVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  int local_144;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_54;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar2 = *piVar6;
    iVar10 = piVar6[1];
    if ((((double)0.001) <= ABS((float10)iVar2 - param_5)) || (((double)0.001) <= ABS((float10)iVar10 - param_6))) {
      fVar3 = param_3 - ((float10)piVar6[2] * param_5) / (float10)iVar2;
      fVar4 = param_4 - ((float10)piVar6[3] * param_6) / (float10)iVar10;
      if ((((fVar4 <= (float)W_y2) && ((float)W_y1 < (fVar4 + param_6) - 0.5)) &&
          (fVar3 <= (float)W_x2)) && ((float)W_x1 < (fVar3 + param_5) - 0.5)) {
        local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
        fVar5 = (float)local_f4;
        if (fVar4 <= fVar5) {
          local_ec = 0;
        }
        else {
          if ((float)local_f4 < fVar4 - 0.5) {
            local_f4 = local_f4 + 1;
            fVar5 = (float)local_f4;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar10 * (fVar5 - fVar4)) / param_6) * 65536.0);
          local_ec = local_54;
        }
        if (local_f4 < W_y1) {
          iVar8 = W_y1 - local_f4;
          local_f4 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar8 * iVar10) / param_6) * 65536.0);
          local_ec = local_ec + local_54;
        }
        iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_6) - 0.5));
        if (W_y2 < iVar8) {
          iVar8 = W_y2;
        }
        if (iVar8 - local_f4 != -1 && -1 < (iVar8 - local_f4) + 1) {
          local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
          fVar4 = (float)local_fc;
          if (fVar3 <= fVar4) {
            local_f0 = 0;
          }
          else {
            if ((float)local_fc < fVar3 - 0.5) {
              local_fc = local_fc + 1;
              fVar4 = (float)local_fc;
            }
            local_54 = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar2) / param_5) * 65536.0)
            ;
            local_f0 = local_54;
          }
          if (fVar3 < (float)W_x1) {
            iVar9 = W_x1 - local_fc;
            local_fc = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar9 * iVar2) / param_5) * 65536.0);
            local_f0 = local_f0 + local_144;
          }
          iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_5) - 0.5));
          if (W_x2 < iVar9) {
            iVar9 = W_x2;
          }
          local_54 = (uint)(longlong)ROUND((float)(iVar2 << 0x10) / param_5);
          iVar2 = (int)GHIDRA_FIST32((float)(iVar10 << 0x10) / param_6);
          for (; ((int)local_f0 < 0 && (local_fc <= iVar9)); local_fc = local_fc + 1) {
            local_f0 = local_f0 + local_54;
          }
          iVar10 = (int)local_f0 >> 0x10;
          if (iVar10 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_100 = iVar10;
          }
          for (; ((int)local_ec < 0 && (local_f4 <= iVar8)); local_f4 = local_f4 + 1) {
            local_ec = local_ec + iVar2;
          }
          iVar10 = (int)local_ec >> 0x10;
          if (iVar10 != 0) {
            local_ec = local_ec & 0xffff;
            local_f8 = iVar10;
          }
          iVar10 = (iVar9 - local_fc) + 1;
          iVar8 = (iVar8 - local_f4) + 1;
          if ((0 < iVar10) && (0 < iVar8)) {
            iVar9 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar9 != 0) {
              iVar11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar12 = (int *)param_1[5];
              if (piVar12 == (int *)0x0) {
                piVar12 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
              }
              else {
                EBPalUpdate(piVar12);
              }
              local_d8 = 0;
              if (0 < iVar8) {
                do {
                  pbVar13 = (byte *)(iVar9 + *(int *)(piVar6[0xb] +
                                                     (((int)local_ec >> 0x10) + local_f8) * 4) +
                                    local_100);
                  puVar17 = (uint *)(local_fc * 2 +
                                    iVar11 + *(int *)(*(int *)(iVar7 + 0x2c) +
                                                     (local_f4 + local_d8) * 4));
                  uVar20 = local_f0;
                  for (iVar1 = iVar10; iVar1 != 0; iVar1 = iVar1 + -1) {
                    if (*pbVar13 != 0) {
                      uVar18 = (uint)*(short *)((int)piVar12 + (uint)*pbVar13 * 2 + 0x5c);
                      uVar19 = *puVar17;
                      iVar14 = (uVar19 & 0xf800) - (uVar18 & 0xf800);
                      iVar16 = (uVar19 & 0x7e0) - (uVar18 & 0x7e0);
                      iVar15 = (uVar19 & 0x1f) - (uVar18 & 0x1f);
                      *(ushort *)puVar17 =
                           (ushort)iVar14 & -(short)(iVar14 >> 0x1f) - 1U |
                           (ushort)iVar16 & -(short)(iVar16 >> 0x1f) - 1U |
                           (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U;
                    }
                    uVar19 = uVar20 + local_54;
                    puVar17 = (uint *)((int)puVar17 + 2);
                    uVar20 = uVar19 & 0xffff;
                    pbVar13 = pbVar13 + (uVar19 >> 0x10);
                  }
                  local_d8 = local_d8 + 1;
                  local_ec = local_ec + iVar2;
                } while (local_d8 < iVar8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSub8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirH8to16 @ 0x080734b0, 2429 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransSubMirH8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  byte *pbVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint *puVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  int local_144;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_54;
  
  piVar7 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar2 = *piVar7;
    iVar3 = piVar7[1];
    if ((((double)0.001) <= ABS((float10)iVar2 - param_5)) || (((double)0.001) <= ABS((float10)iVar3 - param_6))) {
      fVar4 = param_3 - ((float)((iVar2 - piVar7[2]) + -1) * param_5) / (float10)iVar2;
      fVar5 = param_4 - ((float10)piVar7[3] * param_6) / (float10)iVar3;
      if ((((fVar5 <= (float)W_y2) && ((float)W_y1 < (fVar5 + param_6) - 0.5)) &&
          (fVar4 <= (float)W_x2)) && ((float)W_x1 < (fVar4 + param_5) - 0.5)) {
        local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar6 = (float)local_f4;
        if (fVar5 <= fVar6) {
          local_ec = 0;
        }
        else {
          if ((float)local_f4 < fVar5 - 0.5) {
            local_f4 = local_f4 + 1;
            fVar6 = (float)local_f4;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar3 * (fVar6 - fVar5)) / param_6) * 65536.0);
          local_ec = local_54;
        }
        if (local_f4 < W_y1) {
          iVar9 = W_y1 - local_f4;
          local_f4 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar9 * iVar3) / param_6) * 65536.0);
          local_ec = local_ec + local_54;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_6) - 0.5));
        if (W_y2 < iVar9) {
          iVar9 = W_y2;
        }
        if (iVar9 - local_f4 != -1 && -1 < (iVar9 - local_f4) + 1) {
          local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
          fVar5 = (float)local_fc;
          if (fVar4 <= fVar5) {
            local_f0 = 0;
          }
          else {
            if ((float)local_fc < fVar4 - 0.5) {
              local_fc = local_fc + 1;
              fVar5 = (float)local_fc;
            }
            local_54 = (uint)(longlong)ROUND((((fVar5 - fVar4) * (float10)iVar2) / param_5) * 65536.0)
            ;
            local_f0 = local_54;
          }
          if (fVar4 < (float)W_x1) {
            iVar10 = W_x1 - local_fc;
            local_fc = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar10 * iVar2) / param_5) * 65536.0);
            local_f0 = local_f0 + local_144;
          }
          iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_5) - 0.5));
          if (W_x2 < iVar10) {
            iVar10 = W_x2;
          }
          local_144 = (int)(longlong)ROUND((float)(iVar2 << 0x10) / param_5);
          iVar3 = (int)GHIDRA_FIST32((float)(iVar3 << 0x10) / param_6);
          for (; ((int)local_f0 < 0 && (local_fc <= iVar10)); local_fc = local_fc + 1) {
            local_f0 = local_f0 + local_144;
          }
          iVar11 = (int)local_f0 >> 0x10;
          if (iVar11 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_100 = iVar11;
          }
          for (; ((int)local_ec < 0 && (local_f4 <= iVar9)); local_f4 = local_f4 + 1) {
            local_ec = local_ec + iVar3;
          }
          iVar11 = (int)local_ec >> 0x10;
          if (iVar11 != 0) {
            local_ec = local_ec & 0xffff;
            local_f8 = iVar11;
          }
          iVar10 = (iVar10 - local_fc) + 1;
          iVar9 = (iVar9 - local_f4) + 1;
          if ((0 < iVar10) && (0 < iVar9)) {
            iVar11 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar11 != 0) {
              iVar12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar13 = (int *)param_1[5];
              if (piVar13 == (int *)0x0) {
                piVar13 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar7[0xc]);
              }
              else {
                EBPalUpdate(piVar13);
              }
              local_d8 = 0;
              if (0 < iVar9) {
                do {
                  pbVar14 = (byte *)(((iVar11 + *(int *)(piVar7[0xb] +
                                                        (((int)local_ec >> 0x10) + local_f8) * 4) +
                                      iVar2) - local_100) + -1);
                  puVar18 = (uint *)(local_fc * 2 +
                                    iVar12 + *(int *)(*(int *)(iVar8 + 0x2c) +
                                                     (local_f4 + local_d8) * 4));
                  uVar21 = local_f0;
                  for (iVar1 = iVar10; iVar1 != 0; iVar1 = iVar1 + -1) {
                    if (*pbVar14 != 0) {
                      uVar19 = (uint)*(short *)((int)piVar13 + (uint)*pbVar14 * 2 + 0x5c);
                      uVar20 = *puVar18;
                      iVar15 = (uVar20 & 0xf800) - (uVar19 & 0xf800);
                      iVar17 = (uVar20 & 0x7e0) - (uVar19 & 0x7e0);
                      iVar16 = (uVar20 & 0x1f) - (uVar19 & 0x1f);
                      *(ushort *)puVar18 =
                           (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U |
                           (ushort)iVar17 & -(short)(iVar17 >> 0x1f) - 1U |
                           (ushort)iVar16 & -(short)(iVar16 >> 0x1f) - 1U;
                    }
                    uVar20 = uVar21 + local_144;
                    puVar18 = (uint *)((int)puVar18 + 2);
                    uVar21 = uVar20 & 0xffff;
                    pbVar14 = pbVar14 + -(uVar20 >> 0x10);
                  }
                  local_d8 = local_d8 + 1;
                  local_ec = local_ec + iVar3;
                } while (local_d8 < iVar9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirH8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirV8to16 @ 0x08073e30, 2445 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransSubMirV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  byte *pbVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint *puVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  int local_144;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_54;
  
  piVar7 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar2 = *piVar7;
    iVar3 = piVar7[1];
    if ((((double)0.001) <= ABS((float10)iVar2 - param_5)) || (((double)0.001) <= ABS((float10)iVar3 - param_6))) {
      fVar4 = param_3 - ((float10)piVar7[2] * param_5) / (float10)iVar2;
      fVar5 = param_4 - ((float)((iVar3 - piVar7[3]) + -1) * param_6) / (float10)iVar3;
      if ((((fVar5 <= (float)W_y2) && ((float)W_y1 < (fVar5 + param_6) - 0.5)) &&
          (fVar4 <= (float)W_x2)) && ((float)W_x1 < (fVar4 + param_5) - 0.5)) {
        local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar6 = (float)local_f4;
        if (fVar5 <= fVar6) {
          local_ec = 0;
        }
        else {
          if ((float)local_f4 < fVar5 - 0.5) {
            local_f4 = local_f4 + 1;
            fVar6 = (float)local_f4;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar3 * (fVar6 - fVar5)) / param_6) * 65536.0);
          local_ec = local_54;
        }
        if (local_f4 < W_y1) {
          iVar9 = W_y1 - local_f4;
          local_f4 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar9 * iVar3) / param_6) * 65536.0);
          local_ec = local_ec + local_54;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_6) - 0.5));
        if (W_y2 < iVar9) {
          iVar9 = W_y2;
        }
        if (iVar9 - local_f4 != -1 && -1 < (iVar9 - local_f4) + 1) {
          local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
          fVar5 = (float)local_fc;
          if (fVar4 <= fVar5) {
            local_f0 = 0;
          }
          else {
            if ((float)local_fc < fVar4 - 0.5) {
              local_fc = local_fc + 1;
              fVar5 = (float)local_fc;
            }
            local_54 = (uint)(longlong)ROUND((((fVar5 - fVar4) * (float10)iVar2) / param_5) * 65536.0)
            ;
            local_f0 = local_54;
          }
          if (fVar4 < (float)W_x1) {
            iVar10 = W_x1 - local_fc;
            local_fc = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar10 * iVar2) / param_5) * 65536.0);
            local_f0 = local_f0 + local_144;
          }
          iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_5) - 0.5));
          if (W_x2 < iVar10) {
            iVar10 = W_x2;
          }
          local_54 = (uint)(longlong)ROUND((float)(iVar2 << 0x10) / param_5);
          iVar2 = (int)GHIDRA_FIST32((float)(iVar3 << 0x10) / param_6);
          for (; ((int)local_f0 < 0 && (local_fc <= iVar10)); local_fc = local_fc + 1) {
            local_f0 = local_f0 + local_54;
          }
          iVar11 = (int)local_f0 >> 0x10;
          if (iVar11 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_100 = iVar11;
          }
          for (; ((int)local_ec < 0 && (local_f4 <= iVar9)); local_f4 = local_f4 + 1) {
            local_ec = local_ec + iVar2;
          }
          iVar11 = (int)local_ec >> 0x10;
          if (iVar11 != 0) {
            local_ec = local_ec & 0xffff;
            local_f8 = iVar11;
          }
          iVar10 = (iVar10 - local_fc) + 1;
          iVar9 = (iVar9 - local_f4) + 1;
          if ((0 < iVar10) && (0 < iVar9)) {
            iVar11 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar11 != 0) {
              iVar12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar13 = (int *)param_1[5];
              if (piVar13 == (int *)0x0) {
                piVar13 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar7[0xc]);
              }
              else {
                EBPalUpdate(piVar13);
              }
              local_d8 = 0;
              if (0 < iVar9) {
                do {
                  pbVar14 = (byte *)(iVar11 + *(int *)(piVar7[0xb] + -4 +
                                                      ((iVar3 - local_f8) - ((int)local_ec >> 0x10))
                                                      * 4) + local_100);
                  puVar18 = (uint *)(local_fc * 2 +
                                    iVar12 + *(int *)(*(int *)(iVar8 + 0x2c) +
                                                     (local_f4 + local_d8) * 4));
                  uVar21 = local_f0;
                  for (iVar1 = iVar10; iVar1 != 0; iVar1 = iVar1 + -1) {
                    if (*pbVar14 != 0) {
                      uVar20 = *puVar18;
                      uVar19 = (uint)*(short *)((int)piVar13 + (uint)*pbVar14 * 2 + 0x5c);
                      iVar15 = (uVar20 & 0xf800) - (uVar19 & 0xf800);
                      iVar17 = (uVar20 & 0x7e0) - (uVar19 & 0x7e0);
                      iVar16 = (uVar20 & 0x1f) - (uVar19 & 0x1f);
                      *(ushort *)puVar18 =
                           (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U |
                           (ushort)iVar17 & -(short)(iVar17 >> 0x1f) - 1U |
                           (ushort)iVar16 & -(short)(iVar16 >> 0x1f) - 1U;
                    }
                    uVar20 = uVar21 + local_54;
                    puVar18 = (uint *)((int)puVar18 + 2);
                    uVar21 = uVar20 & 0xffff;
                    pbVar14 = pbVar14 + (uVar20 >> 0x10);
                  }
                  local_d8 = local_d8 + 1;
                  local_ec = local_ec + iVar2;
                } while (local_d8 < iVar9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirHV8to16 @ 0x080747c0, 2436 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransSubMirHV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  byte *pbVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint *puVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  int local_144;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_54;
  
  piVar8 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar9 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar3 = *piVar8;
    iVar4 = piVar8[1];
    if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar4 - param_6))) {
      fVar5 = param_3 - ((float)((iVar3 - piVar8[2]) + -1) * param_5) / (float10)iVar3;
      fVar6 = param_4 - ((float)((iVar4 - piVar8[3]) + -1) * param_6) / (float10)iVar4;
      if ((((fVar6 <= (float)W_y2) && ((float)W_y1 < (fVar6 + param_6) - 0.5)) &&
          (fVar5 <= (float)W_x2)) && ((float)W_x1 < (fVar5 + param_5) - 0.5)) {
        local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
        fVar7 = (float)local_f4;
        if (fVar6 <= fVar7) {
          local_ec = 0;
        }
        else {
          if ((float)local_f4 < fVar6 - 0.5) {
            local_f4 = local_f4 + 1;
            fVar7 = (float)local_f4;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar4 * (fVar7 - fVar6)) / param_6) * 65536.0);
          local_ec = local_54;
        }
        if (local_f4 < W_y1) {
          iVar10 = W_y1 - local_f4;
          local_f4 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar10 * iVar4) / param_6) * 65536.0);
          local_ec = local_ec + local_54;
        }
        iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_6) - 0.5));
        if (W_y2 < iVar10) {
          iVar10 = W_y2;
        }
        if (iVar10 - local_f4 != -1 && -1 < (iVar10 - local_f4) + 1) {
          local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
          fVar6 = (float)local_fc;
          if (fVar5 <= fVar6) {
            local_f0 = 0;
          }
          else {
            if ((float)local_fc < fVar5 - 0.5) {
              local_fc = local_fc + 1;
              fVar6 = (float)local_fc;
            }
            local_54 = (uint)(longlong)ROUND((((fVar6 - fVar5) * (float10)iVar3) / param_5) * 65536.0)
            ;
            local_f0 = local_54;
          }
          if (fVar5 < (float)W_x1) {
            iVar11 = W_x1 - local_fc;
            local_fc = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar11 * iVar3) / param_5) * 65536.0);
            local_f0 = local_f0 + local_144;
          }
          iVar11 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
          if (W_x2 < iVar11) {
            iVar11 = W_x2;
          }
          local_144 = (int)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
          iVar1 = (int)GHIDRA_FIST32((float)(iVar4 << 0x10) / param_6);
          for (; ((int)local_f0 < 0 && (local_fc <= iVar11)); local_fc = local_fc + 1) {
            local_f0 = local_f0 + local_144;
          }
          iVar12 = (int)local_f0 >> 0x10;
          if (iVar12 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_100 = iVar12;
          }
          for (; ((int)local_ec < 0 && (local_f4 <= iVar10)); local_f4 = local_f4 + 1) {
            local_ec = local_ec + iVar1;
          }
          iVar12 = (int)local_ec >> 0x10;
          if (iVar12 != 0) {
            local_ec = local_ec & 0xffff;
            local_f8 = iVar12;
          }
          iVar11 = (iVar11 - local_fc) + 1;
          iVar10 = (iVar10 - local_f4) + 1;
          if ((0 < iVar11) && (0 < iVar10)) {
            iVar12 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar12 != 0) {
              iVar13 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar14 = (int *)param_1[5];
              if (piVar14 == (int *)0x0) {
                piVar14 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar8[0xc]);
              }
              else {
                EBPalUpdate(piVar14);
              }
              local_d8 = 0;
              if (0 < iVar10) {
                do {
                  pbVar15 = (byte *)(((iVar12 + *(int *)(piVar8[0xb] + -4 +
                                                        ((iVar4 - local_f8) -
                                                        ((int)local_ec >> 0x10)) * 4) + iVar3) -
                                     local_100) + -1);
                  puVar19 = (uint *)(local_fc * 2 +
                                    iVar13 + *(int *)(*(int *)(iVar9 + 0x2c) +
                                                     (local_f4 + local_d8) * 4));
                  uVar22 = local_f0;
                  for (iVar2 = iVar11; iVar2 != 0; iVar2 = iVar2 + -1) {
                    if (*pbVar15 != 0) {
                      uVar20 = (uint)*(short *)((int)piVar14 + (uint)*pbVar15 * 2 + 0x5c);
                      uVar21 = *puVar19;
                      iVar16 = (uVar21 & 0xf800) - (uVar20 & 0xf800);
                      iVar18 = (uVar21 & 0x7e0) - (uVar20 & 0x7e0);
                      iVar17 = (uVar21 & 0x1f) - (uVar20 & 0x1f);
                      *(ushort *)puVar19 =
                           (ushort)iVar16 & -(short)(iVar16 >> 0x1f) - 1U |
                           (ushort)iVar18 & -(short)(iVar18 >> 0x1f) - 1U |
                           (ushort)iVar17 & -(short)(iVar17 >> 0x1f) - 1U;
                    }
                    uVar21 = uVar22 + local_144;
                    puVar19 = (uint *)((int)puVar19 + 2);
                    uVar22 = uVar21 & 0xffff;
                    pbVar15 = pbVar15 + -(uVar21 >> 0x10);
                  }
                  local_d8 = local_d8 + 1;
                  local_ec = local_ec + iVar1;
                } while (local_d8 < iVar10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirHV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_RotateSpriteTransSub8to16_P @ 0x08075150, 3824 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 15 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 13 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransSub8to16_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  int *piVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int *piVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  uint uVar35;
  int iVar36;
  int iVar37;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x90] __attribute__((aligned(16)));
#define local_90 (*(int *)(ghidra_frame + 0x0))
#define local_8c (*(float *)(ghidra_frame + 0x4))
#define local_88 (*(float *)(ghidra_frame + 0x8))
#define local_84 (*(float *)(ghidra_frame + 0xc))
#define local_80 (*(float *)(ghidra_frame + 0x10))
#define local_74 (*(int *)(ghidra_frame + 0x1c))
#define local_70 (*(int *)(ghidra_frame + 0x20))
#define local_64 (*(int *)(ghidra_frame + 0x2c))
#define local_60 (*(int *)(ghidra_frame + 0x30))
#define local_5c (*(int *)(ghidra_frame + 0x34))
#define local_50 (*(int *)(ghidra_frame + 0x40))
#define local_38 (*(ushort **)(ghidra_frame + 0x58))
#define local_20 (*(uint *)(ghidra_frame + 0x70))
  
  piVar18 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar19 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar4 = piVar18[0xb];
  iVar20 = roundfloat(param_3);
  iVar21 = roundfloat(param_4);
  iVar33 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar33 < 0) {
    iVar33 = -iVar33;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar36 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar36 < 0) {
    iVar36 = -iVar36;
    param_5 = param_5 + 180.0;
  }
  if (iVar33 == 0) {
    return local_20;
  }
  if (iVar36 == 0) {
    return local_20;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar9 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar29 = (int)uVar9;
  if (iVar29 == 0) {
LAB_08075442:
    uVar22 = W_ScaleSpriteTransSub_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return uVar22;
  }
  if (iVar29 == 0x5a0) {
    param_7 = -param_7;
    param_6 = -param_6;
    goto LAB_08075442;
  }
  iVar5 = *piVar18;
  iVar6 = piVar18[1];
  iVar7 = piVar18[2];
  iVar8 = piVar18[3];
  fVar10 = (float)SinTable[(iVar29 + 0x2d0) % 0xb40];
  fVar11 = fVar10 * 0.0009765625;
  fVar13 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar29 >> 0x1f) << 0x20 | uVar9 & 0xffffffff) %
                                0xb40)];
  fVar12 = fVar13 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar29 + 0x2d0) % 0xb40] << 0x10) / iVar33) / param_8);
  uVar22 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar29 >> 0x1f) << 0x20 | uVar9 & 0xffffffff) % 0xb40)
                    ] << 0x10) / iVar36;
  iVar2 = (int)GHIDRA_FIST32((float10)(int)uVar22 / param_8);
  if (iVar29 < 0x2d0) {
    iVar29 = -iVar7;
    iVar23 = -iVar8;
    iVar24 = (iVar5 - iVar7) + -1;
    iVar25 = (iVar6 - iVar8) + -1;
LAB_0807568f:
    fVar14 = (float10)iVar29;
    fVar15 = (float10)iVar24;
    local_84 = (float10)iVar23;
    local_8c = (float10)iVar25;
    local_88 = local_8c;
    fVar17 = fVar14;
  }
  else {
    if (iVar29 < 0x5a0) {
      iVar24 = (iVar5 - iVar7) + -1;
      iVar23 = -iVar8;
      iVar29 = (iVar6 - iVar8) + -1;
      iVar25 = -iVar7;
    }
    else {
      if (iVar29 < 0x870) {
        iVar29 = (iVar5 - iVar7) + -1;
        iVar23 = (iVar6 - iVar8) + -1;
        iVar24 = -iVar7;
        iVar25 = -iVar8;
        goto LAB_0807568f;
      }
      if (0xb3f < iVar29) {
        return uVar22;
      }
      iVar24 = -iVar7;
      iVar23 = (iVar6 - iVar8) + -1;
      iVar29 = -iVar8;
      iVar25 = (iVar5 - iVar7) + -1;
    }
    fVar14 = (float10)iVar24;
    local_88 = (float10)iVar29;
    fVar15 = (float10)iVar25;
    local_8c = (float10)iVar23;
    local_84 = local_88;
    fVar17 = fVar15;
  }
  local_80 = (float10)iVar24;
  local_88 = local_88 * param_7;
  fVar14 = fVar14 * param_6;
  fVar16 = (float10)iVar23 * param_7;
  fVar15 = fVar15 * param_6;
  iVar29 = roundfloat((-fVar14 * fVar12 + fVar16 * fVar11) * param_9);
  iVar23 = roundfloat((-fVar15 * fVar12 + local_88 * fVar11) * param_9);
  local_50 = roundfloat((-(local_80 * param_6) * fVar12 + local_84 * param_7 * fVar11) * param_9);
  local_90 = roundfloat((-(fVar17 * param_6) * fVar12 + local_8c * param_7 * fVar11) * param_9);
  if ((local_50 == iVar29) || (local_50 == iVar23)) {
    local_74 = 0;
    local_70 = 0;
    local_60 = (int)GHIDRA_FIST32((fVar14 * fVar11 + fVar16 * fVar12) * 65536.0 * param_8);
    local_64 = (int)GHIDRA_FIST32((fVar15 * fVar11 + local_88 * fVar12) * 65536.0 * param_8);
  }
  else {
    fVar17 = fVar11 * local_80 * param_6 + local_84 * param_7 * fVar12;
    local_70 = (int)GHIDRA_FIST32(((fVar17 - (fVar14 * fVar11 + fVar16 * fVar12)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar29));
    if (local_70 < 0) {
      local_70 = -local_70;
    }
    local_74 = (int)GHIDRA_FIST32((((local_88 * fVar12 + fVar15 * fVar11) - fVar17) * 65536.0 * param_8) /
                          (float)(local_50 - iVar23));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_64 = (int)GHIDRA_FIST32(fVar17 * 65536.0 * param_8);
    local_60 = local_64;
  }
  for (; local_50 < W_y1 - iVar21; local_50 = local_50 + 1) {
    iVar24 = local_74;
    if (local_50 < iVar29) {
      iVar24 = -local_70;
    }
    local_60 = local_60 + iVar24;
    iVar24 = local_74;
    if (iVar23 <= local_50) {
      iVar24 = -local_70;
    }
    local_64 = local_64 + iVar24;
  }
  if (W_y2 - iVar21 < local_90) {
    local_90 = W_y2 - iVar21;
  }
  iVar24 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar24 == 0) {
    return 0;
  }
  iVar25 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar26 = (int *)param_1[5];
  if (piVar26 == (int *)0x0) {
    piVar26 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar18[0xc]);
  }
  else {
    EBPalUpdate(piVar26);
  }
  if (local_50 <= local_90) {
    iVar27 = W_x1 - iVar20;
    do {
      iVar37 = local_60 >> 0x10;
      if (local_60 >> 0x10 < iVar27) {
        iVar37 = iVar27;
      }
      iVar28 = local_64 >> 0x10;
      if (W_x2 - iVar20 < local_64 >> 0x10) {
        iVar28 = W_x2 - iVar20;
      }
      local_5c = (int)GHIDRA_FIST32(((((float10)iVar37 / param_8) * fVar10 -
                             ((float)local_50 / param_9) * fVar13) * 65536.0) / (float10)iVar33) +
                 iVar7 * 0x10000;
      iVar34 = iVar8 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar37 / param_8) * fVar13 +
                           ((float)local_50 / param_9) * fVar10) * 65536.0) / (float10)iVar36);
      local_38 = (ushort *)
                 (iVar25 + *(int *)(*(int *)(iVar19 + 0x2c) + (local_50 + iVar21) * 4) +
                 (iVar20 + iVar37) * 2);
      iVar30 = (iVar28 - iVar37) + 1;
      iVar32 = iVar28 - iVar37;
      iVar31 = iVar2 * iVar30 + iVar34;
      for (iVar30 = local_5c + iVar1 * iVar30;
          (SBORROW4(iVar28,iVar37) == iVar32 < 0 &&
          ((((iVar6 <= iVar31 >> 0x10 || (iVar5 <= iVar30 >> 0x10)) || (iVar31 >> 0x10 < 0)) ||
           (iVar30 >> 0x10 < 0)))); iVar30 = iVar30 - iVar1) {
        iVar28 = iVar28 + -1;
        iVar31 = iVar31 - iVar2;
        iVar32 = iVar28 - iVar37;
      }
      for (; (iVar37 <= iVar28 &&
             (((iVar6 <= iVar34 >> 0x10 || (iVar5 <= local_5c >> 0x10)) ||
              ((iVar34 >> 0x10 < 0 || (local_5c >> 0x10 < 0)))))); local_5c = local_5c + iVar1) {
        local_38 = local_38 + 1;
        iVar37 = iVar37 + 1;
        iVar34 = iVar34 + iVar2;
      }
      iVar37 = (iVar28 - iVar37) + 1;
      if (0 < iVar37) {
        do {
          bVar3 = *(byte *)((local_5c >> 0x10) + iVar24 + *(int *)(iVar4 + (iVar34 >> 0x10) * 4));
          if (bVar3 != 0) {
            uVar35 = (uint)*(ushort *)((int)piVar26 + (uint)bVar3 * 2 + 0x5c);
            uVar22 = (uint)*local_38;
            iVar28 = (uVar22 & 0xf800) - (uVar35 & 0xf800);
            iVar32 = (uVar22 & 0x7e0) - (uVar35 & 0x7e0);
            iVar31 = (uVar22 & 0x1f) - (uVar35 & 0x1f);
            *local_38 = (ushort)iVar28 & -(short)(iVar28 >> 0x1f) - 1U |
                        (ushort)iVar32 & -(short)(iVar32 >> 0x1f) - 1U |
                        (ushort)iVar31 & -(short)(iVar31 >> 0x1f) - 1U;
          }
          local_5c = local_5c + iVar1;
          local_38 = local_38 + 1;
          iVar34 = iVar34 + iVar2;
          iVar37 = iVar37 + -1;
        } while (iVar37 != 0);
      }
      iVar37 = local_74;
      if (local_50 < iVar29) {
        iVar37 = -local_70;
      }
      local_60 = local_60 + iVar37;
      iVar37 = local_74;
      if (iVar23 <= local_50) {
        iVar37 = -local_70;
      }
      local_64 = local_64 + iVar37;
      local_50 = local_50 + 1;
    } while (local_50 <= local_90);
  }
  uVar22 = SpriteDecompUnlockData();
  return uVar22;
}
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_74
#undef local_70
#undef local_64
#undef local_60
#undef local_5c
#undef local_50
#undef local_38
#undef local_20

/* W_RotateSpriteTransSubMirH8to16_P @ 0x08076040, 3760 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 15 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 13 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransSubMirH8to16_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  int *piVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int *piVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  uint uVar34;
  int iVar35;
  int iVar36;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x90] __attribute__((aligned(16)));
#define local_90 (*(int *)(ghidra_frame + 0x0))
#define local_8c (*(float *)(ghidra_frame + 0x4))
#define local_88 (*(float *)(ghidra_frame + 0x8))
#define local_84 (*(float *)(ghidra_frame + 0xc))
#define local_80 (*(float *)(ghidra_frame + 0x10))
#define local_74 (*(int *)(ghidra_frame + 0x1c))
#define local_70 (*(int *)(ghidra_frame + 0x20))
#define local_64 (*(int *)(ghidra_frame + 0x2c))
#define local_60 (*(int *)(ghidra_frame + 0x30))
#define local_5c (*(int *)(ghidra_frame + 0x34))
#define local_50 (*(int *)(ghidra_frame + 0x40))
#define local_38 (*(ushort **)(ghidra_frame + 0x58))
#define local_20 (*(uint *)(ghidra_frame + 0x70))
  
  piVar18 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar19 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar4 = piVar18[0xb];
  iVar20 = roundfloat(param_3);
  iVar21 = roundfloat(param_4);
  iVar31 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar31 < 0) {
    iVar31 = -iVar31;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar35 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar35 < 0) {
    iVar35 = -iVar35;
    param_5 = param_5 + 180.0;
  }
  if (iVar31 == 0) {
    return local_20;
  }
  if (iVar35 == 0) {
    return local_20;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar9 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar27 = (int)uVar9;
  if (iVar27 == 0) {
    param_6 = -param_6;
LAB_0807632d:
    uVar22 = W_ScaleSpriteTransSub_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return uVar22;
  }
  if (iVar27 == 0x5a0) {
    param_7 = -param_7;
    goto LAB_0807632d;
  }
  iVar5 = *piVar18;
  iVar6 = piVar18[1];
  iVar7 = piVar18[2];
  iVar8 = piVar18[3];
  fVar10 = (float)SinTable[(iVar27 + 0x2d0) % 0xb40];
  fVar11 = fVar10 * 0.0009765625;
  fVar13 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar27 >> 0x1f) << 0x20 | uVar9 & 0xffffffff) %
                                0xb40)];
  fVar12 = fVar13 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar27 + 0x2d0) % 0xb40] << 0x10) / iVar31) / param_8);
  uVar22 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar27 >> 0x1f) << 0x20 | uVar9 & 0xffffffff) % 0xb40)
                    ] << 0x10) / iVar35;
  iVar2 = (int)GHIDRA_FIST32((float10)(int)uVar22 / param_8);
  if (iVar27 < 0x2d0) {
    iVar27 = -iVar7;
    iVar23 = -iVar8;
    iVar24 = (iVar5 - iVar7) + -1;
    iVar25 = (iVar6 - iVar8) + -1;
LAB_0807657f:
    fVar14 = (float10)iVar27;
    fVar15 = (float10)iVar24;
    local_84 = (float10)iVar23;
    local_8c = (float10)iVar25;
    local_88 = local_8c;
    fVar17 = fVar14;
  }
  else {
    if (iVar27 < 0x5a0) {
      iVar24 = (iVar5 - iVar7) + -1;
      iVar23 = -iVar8;
      iVar27 = (iVar6 - iVar8) + -1;
      iVar25 = -iVar7;
    }
    else {
      if (iVar27 < 0x870) {
        iVar27 = (iVar5 - iVar7) + -1;
        iVar23 = (iVar6 - iVar8) + -1;
        iVar24 = -iVar7;
        iVar25 = -iVar8;
        goto LAB_0807657f;
      }
      if (0xb3f < iVar27) {
        return uVar22;
      }
      iVar24 = -iVar7;
      iVar23 = (iVar6 - iVar8) + -1;
      iVar27 = -iVar8;
      iVar25 = (iVar5 - iVar7) + -1;
    }
    fVar14 = (float10)iVar24;
    local_88 = (float10)iVar27;
    fVar15 = (float10)iVar25;
    local_8c = (float10)iVar23;
    local_84 = local_88;
    fVar17 = fVar15;
  }
  local_80 = (float10)iVar24;
  local_88 = local_88 * param_7;
  fVar14 = fVar14 * param_6;
  fVar16 = (float10)iVar23 * param_7;
  fVar15 = fVar15 * param_6;
  iVar27 = roundfloat((-fVar14 * fVar12 + fVar16 * fVar11) * param_9);
  iVar24 = roundfloat((-fVar15 * fVar12 + local_88 * fVar11) * param_9);
  local_50 = roundfloat((-(local_80 * param_6) * fVar12 + local_84 * param_7 * fVar11) * param_9);
  local_90 = roundfloat((-(fVar17 * param_6) * fVar12 + local_8c * param_7 * fVar11) * param_9);
  if ((local_50 == iVar27) || (local_50 == iVar24)) {
    local_74 = 0;
    local_70 = 0;
    local_60 = (int)GHIDRA_FIST32((fVar14 * fVar11 + fVar16 * fVar12) * 65536.0 * param_8);
    local_64 = (int)GHIDRA_FIST32((fVar15 * fVar11 + local_88 * fVar12) * 65536.0 * param_8);
  }
  else {
    fVar17 = fVar11 * local_80 * param_6 + local_84 * param_7 * fVar12;
    local_70 = (int)GHIDRA_FIST32(((fVar17 - (fVar14 * fVar11 + fVar16 * fVar12)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar27));
    if (local_70 < 0) {
      local_70 = -local_70;
    }
    local_74 = (int)GHIDRA_FIST32((((local_88 * fVar12 + fVar15 * fVar11) - fVar17) * 65536.0 * param_8) /
                          (float)(local_50 - iVar24));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_64 = (int)GHIDRA_FIST32(fVar17 * 65536.0 * param_8);
    local_60 = local_64;
  }
  for (; local_50 < W_y1 - iVar21; local_50 = local_50 + 1) {
    iVar23 = local_74;
    if (local_50 < iVar27) {
      iVar23 = -local_70;
    }
    local_60 = local_60 + iVar23;
    iVar23 = local_74;
    if (iVar24 <= local_50) {
      iVar23 = -local_70;
    }
    local_64 = local_64 + iVar23;
  }
  if (W_y2 - iVar21 < local_90) {
    local_90 = W_y2 - iVar21;
  }
  iVar23 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar23 == 0) {
    return 0;
  }
  iVar25 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar26 = (int *)param_1[5];
  if (piVar26 == (int *)0x0) {
    piVar26 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar18[0xc]);
  }
  else {
    EBPalUpdate(piVar26);
  }
  if (local_50 <= local_90) {
    do {
      iVar33 = local_60 >> 0x10;
      iVar36 = local_64 >> 0x10;
      if (W_x2 < iVar20 - iVar33) {
        iVar33 = iVar20 - W_x2;
      }
      if (iVar20 - iVar36 < W_x1) {
        iVar36 = iVar20 - W_x1;
      }
      local_5c = (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar10 -
                             ((float)local_50 / param_9) * fVar13) * 65536.0) / (float10)iVar31) +
                 iVar7 * 0x10000;
      iVar32 = iVar8 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar13 +
                           ((float)local_50 / param_9) * fVar10) * 65536.0) / (float10)iVar35);
      local_38 = (ushort *)
                 (iVar25 + *(int *)(*(int *)(iVar19 + 0x2c) + (local_50 + iVar21) * 4) +
                 (iVar20 - iVar33) * 2);
      iVar28 = (iVar36 - iVar33) + 1;
      iVar30 = iVar36 - iVar33;
      iVar29 = iVar2 * iVar28 + iVar32;
      for (iVar28 = local_5c + iVar1 * iVar28;
          (SBORROW4(iVar36,iVar33) == iVar30 < 0 &&
          ((((iVar6 <= iVar29 >> 0x10 || (iVar5 <= iVar28 >> 0x10)) || (iVar29 >> 0x10 < 0)) ||
           (iVar28 >> 0x10 < 0)))); iVar28 = iVar28 - iVar1) {
        iVar36 = iVar36 + -1;
        iVar29 = iVar29 - iVar2;
        iVar30 = iVar36 - iVar33;
      }
      for (; (iVar33 <= iVar36 &&
             (((iVar6 <= iVar32 >> 0x10 || (iVar5 <= local_5c >> 0x10)) ||
              ((iVar32 >> 0x10 < 0 || (local_5c >> 0x10 < 0)))))); local_5c = local_5c + iVar1) {
        local_38 = local_38 + -1;
        iVar33 = iVar33 + 1;
        iVar32 = iVar32 + iVar2;
      }
      iVar33 = (iVar36 - iVar33) + 1;
      if (0 < iVar33) {
        do {
          bVar3 = *(byte *)((local_5c >> 0x10) + iVar23 + *(int *)(iVar4 + (iVar32 >> 0x10) * 4));
          if (bVar3 != 0) {
            uVar34 = (uint)*(ushort *)((int)piVar26 + (uint)bVar3 * 2 + 0x5c);
            uVar22 = (uint)*local_38;
            iVar36 = (uVar22 & 0xf800) - (uVar34 & 0xf800);
            iVar30 = (uVar22 & 0x7e0) - (uVar34 & 0x7e0);
            iVar29 = (uVar22 & 0x1f) - (uVar34 & 0x1f);
            *local_38 = (ushort)iVar36 & -(short)(iVar36 >> 0x1f) - 1U |
                        (ushort)iVar30 & -(short)(iVar30 >> 0x1f) - 1U |
                        (ushort)iVar29 & -(short)(iVar29 >> 0x1f) - 1U;
          }
          local_5c = local_5c + iVar1;
          local_38 = local_38 + -1;
          iVar32 = iVar32 + iVar2;
          iVar33 = iVar33 + -1;
        } while (iVar33 != 0);
      }
      iVar33 = local_74;
      if (local_50 < iVar27) {
        iVar33 = -local_70;
      }
      local_60 = local_60 + iVar33;
      iVar33 = local_74;
      if (iVar24 <= local_50) {
        iVar33 = -local_70;
      }
      local_64 = local_64 + iVar33;
      local_50 = local_50 + 1;
    } while (local_50 <= local_90);
  }
  uVar22 = SpriteDecompUnlockData();
  return uVar22;
}
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_74
#undef local_70
#undef local_64
#undef local_60
#undef local_5c
#undef local_50
#undef local_38
#undef local_20

/* W_ScaleShadowTransSub8to16 @ 0x08076ef0, 2197 bytes
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleShadowTransSub8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  ushort *puVar18;
  int local_134;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_4c;
  
  piVar5 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar6 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if (((0.0 < param_5) && (0.0 < param_6)) && (param_7 != 0)) {
    iVar1 = *piVar5;
    iVar9 = piVar5[1];
    fVar4 = param_3 - ((float10)piVar5[2] * param_5) / (float10)iVar1;
    fVar2 = param_4 - ((float10)piVar5[3] * param_6) / (float10)iVar9;
    if (((fVar2 <= (float)W_y2) && ((float)W_y1 < (fVar2 + param_6) - 0.5)) &&
       ((fVar4 <= (float)W_x2 && ((float)W_x1 < (fVar4 + param_5) - 0.5)))) {
      local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar2));
      fVar3 = (float)local_f4;
      if (fVar2 <= fVar3) {
        local_ec = 0;
      }
      else {
        if ((float)local_f4 < fVar2 - 0.5) {
          local_f4 = local_f4 + 1;
          fVar3 = (float)local_f4;
        }
        local_4c = (uint)(longlong)ROUND((((fVar3 - fVar2) * (float10)iVar9) / param_6) * 65536.0);
        local_ec = local_4c;
      }
      if (local_f4 < W_y1) {
        iVar7 = W_y1 - local_f4;
        local_f4 = W_y1;
        local_4c = (uint)(longlong)ROUND(((float)(iVar7 * iVar9) / param_6) * 65536.0);
        local_ec = local_ec + local_4c;
      }
      iVar7 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar2 + param_6) - 0.5));
      if (W_y2 < iVar7) {
        iVar7 = W_y2;
      }
      if (iVar7 - local_f4 != -1 && -1 < (iVar7 - local_f4) + 1) {
        local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
        fVar2 = (float)local_fc;
        if (fVar4 <= fVar2) {
          local_f0 = 0;
        }
        else {
          if ((float)local_fc < fVar4 - 0.5) {
            local_fc = local_fc + 1;
            fVar2 = (float)local_fc;
          }
          local_4c = (uint)(longlong)ROUND((((fVar2 - fVar4) * (float10)iVar1) / param_5) * 65536.0);
          local_f0 = local_4c;
        }
        if (fVar4 < (float)W_x1) {
          iVar8 = W_x1 - local_fc;
          local_fc = W_x1;
          local_134 = (int)(longlong)ROUND(((float)(iVar8 * iVar1) / param_5) * 65536.0);
          local_f0 = local_f0 + local_134;
        }
        iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_5) - 0.5));
        if (W_x2 < iVar8) {
          iVar8 = W_x2;
        }
        local_4c = (uint)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
        iVar1 = (int)GHIDRA_FIST32((float)(iVar9 << 0x10) / param_6);
        for (; ((int)local_f0 < 0 && (local_fc <= iVar8)); local_fc = local_fc + 1) {
          local_f0 = local_f0 + local_4c;
        }
        iVar9 = (int)local_f0 >> 0x10;
        if (iVar9 != 0) {
          local_f0 = local_f0 & 0xffff;
          local_100 = iVar9;
        }
        for (; ((int)local_ec < 0 && (local_f4 <= iVar7)); local_f4 = local_f4 + 1) {
          local_ec = local_ec + iVar1;
        }
        iVar9 = (int)local_ec >> 0x10;
        if (iVar9 != 0) {
          local_ec = local_ec & 0xffff;
          local_f8 = iVar9;
        }
        iVar9 = (iVar8 - local_fc) + 1;
        iVar7 = (iVar7 - local_f4) + 1;
        if ((0 < iVar9) && (0 < iVar7)) {
          iVar8 = SpriteDecompGetAndLockData(param_1,param_2);
          if (iVar8 != 0) {
            iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)param_1[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)param_1,piVar5[0xc]);
            }
            else {
              EBPalUpdate((int *)param_1[5]);
            }
            for (local_d8 = 0; local_d8 < iVar7; local_d8 = local_d8 + 1) {
              pcVar11 = (char *)(iVar8 + *(int *)(piVar5[0xb] +
                                                 (((int)local_ec >> 0x10) + local_f8) * 4) +
                                local_100);
              puVar18 = (ushort *)
                        (local_fc * 2 +
                        iVar10 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_f4 + local_d8) * 4));
              uVar17 = local_f0;
              for (iVar15 = iVar9; iVar15 != 0; iVar15 = iVar15 + -1) {
                if (*pcVar11 != '\0') {
                  uVar16 = (uint)*puVar18;
                  iVar12 = (uVar16 & 0xf800) - (param_7 & 0xf800);
                  iVar14 = (uVar16 & 0x7e0) - (param_7 & 0x7e0);
                  iVar13 = (uVar16 & 0x1f) - (param_7 & 0x1f);
                  *puVar18 = (ushort)iVar12 & -(short)(iVar12 >> 0x1f) - 1U |
                             (ushort)iVar14 & -(short)(iVar14 >> 0x1f) - 1U |
                             (ushort)iVar13 & -(short)(iVar13 >> 0x1f) - 1U;
                }
                uVar16 = uVar17 + local_4c;
                puVar18 = puVar18 + 1;
                uVar17 = uVar16 & 0xffff;
                pcVar11 = pcVar11 + (uVar16 >> 0x10);
              }
              local_ec = local_ec + iVar1;
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirH8to16 @ 0x08077790, 2209 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleShadowTransSubMirH8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  ushort *puVar19;
  int local_134;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_4c;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if (((0.0 < param_5) && (0.0 < param_6)) && (param_7 != 0)) {
    iVar1 = *piVar6;
    iVar2 = piVar6[1];
    fVar5 = param_3 - ((float)((iVar1 - piVar6[2]) + -1) * param_5) / (float10)iVar1;
    fVar3 = param_4 - ((float10)piVar6[3] * param_6) / (float10)iVar2;
    if (((fVar3 <= (float)W_y2) && ((float)W_y1 < (fVar3 + param_6) - 0.5)) &&
       ((fVar5 <= (float)W_x2 && ((float)W_x1 < (fVar5 + param_5) - 0.5)))) {
      local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
      fVar4 = (float)local_f4;
      if (fVar3 <= fVar4) {
        local_ec = 0;
      }
      else {
        if ((float)local_f4 < fVar3 - 0.5) {
          local_f4 = local_f4 + 1;
          fVar4 = (float)local_f4;
        }
        local_4c = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar2) / param_6) * 65536.0);
        local_ec = local_4c;
      }
      if (local_f4 < W_y1) {
        iVar8 = W_y1 - local_f4;
        local_f4 = W_y1;
        local_4c = (uint)(longlong)ROUND(((float)(iVar8 * iVar2) / param_6) * 65536.0);
        local_ec = local_ec + local_4c;
      }
      iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_6) - 0.5));
      if (W_y2 < iVar8) {
        iVar8 = W_y2;
      }
      if (iVar8 - local_f4 != -1 && -1 < (iVar8 - local_f4) + 1) {
        local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar3 = (float)local_fc;
        if (fVar5 <= fVar3) {
          local_f0 = 0;
        }
        else {
          if ((float)local_fc < fVar5 - 0.5) {
            local_fc = local_fc + 1;
            fVar3 = (float)local_fc;
          }
          local_4c = (uint)(longlong)ROUND((((fVar3 - fVar5) * (float10)iVar1) / param_5) * 65536.0);
          local_f0 = local_4c;
        }
        if (fVar5 < (float)W_x1) {
          iVar9 = W_x1 - local_fc;
          local_fc = W_x1;
          local_134 = (int)(longlong)ROUND(((float)(iVar9 * iVar1) / param_5) * 65536.0);
          local_f0 = local_f0 + local_134;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
        if (W_x2 < iVar9) {
          iVar9 = W_x2;
        }
        local_134 = (int)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
        iVar2 = (int)GHIDRA_FIST32((float)(iVar2 << 0x10) / param_6);
        for (; ((int)local_f0 < 0 && (local_fc <= iVar9)); local_fc = local_fc + 1) {
          local_f0 = local_f0 + local_134;
        }
        iVar10 = (int)local_f0 >> 0x10;
        if (iVar10 != 0) {
          local_f0 = local_f0 & 0xffff;
          local_100 = iVar10;
        }
        for (; ((int)local_ec < 0 && (local_f4 <= iVar8)); local_f4 = local_f4 + 1) {
          local_ec = local_ec + iVar2;
        }
        iVar10 = (int)local_ec >> 0x10;
        if (iVar10 != 0) {
          local_ec = local_ec & 0xffff;
          local_f8 = iVar10;
        }
        iVar9 = (iVar9 - local_fc) + 1;
        iVar8 = (iVar8 - local_f4) + 1;
        if ((0 < iVar9) && (0 < iVar8)) {
          iVar10 = SpriteDecompGetAndLockData(param_1,param_2);
          if (iVar10 != 0) {
            iVar11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)param_1[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
            }
            else {
              EBPalUpdate((int *)param_1[5]);
            }
            local_d8 = 0;
            if (0 < iVar8) {
              do {
                pcVar12 = (char *)(((iVar10 + *(int *)(piVar6[0xb] +
                                                      (((int)local_ec >> 0x10) + local_f8) * 4) +
                                    iVar1) - local_100) + -1);
                puVar19 = (ushort *)
                          (local_fc * 2 +
                          iVar11 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_f4 + local_d8) * 4));
                uVar18 = local_f0;
                for (iVar16 = iVar9; iVar16 != 0; iVar16 = iVar16 + -1) {
                  if (*pcVar12 != '\0') {
                    uVar17 = (uint)*puVar19;
                    iVar13 = (uVar17 & 0xf800) - (param_7 & 0xf800);
                    iVar15 = (uVar17 & 0x7e0) - (param_7 & 0x7e0);
                    iVar14 = (uVar17 & 0x1f) - (param_7 & 0x1f);
                    *puVar19 = (ushort)iVar13 & -(short)(iVar13 >> 0x1f) - 1U |
                               (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U |
                               (ushort)iVar14 & -(short)(iVar14 >> 0x1f) - 1U;
                  }
                  uVar17 = uVar18 + local_134;
                  puVar19 = puVar19 + 1;
                  uVar18 = uVar17 & 0xffff;
                  pcVar12 = pcVar12 + -(uVar17 >> 0x10);
                }
                local_d8 = local_d8 + 1;
                local_ec = local_ec + iVar2;
              } while (local_d8 < iVar8);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirV8to16 @ 0x08078040, 2241 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleShadowTransSubMirV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  ushort *puVar19;
  int local_134;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_4c;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if (((0.0 < param_5) && (0.0 < param_6)) && (param_7 != 0)) {
    iVar1 = *piVar6;
    iVar2 = piVar6[1];
    fVar5 = param_3 - ((float10)piVar6[2] * param_5) / (float10)iVar1;
    fVar3 = param_4 - ((float)((iVar2 - piVar6[3]) + -1) * param_6) / (float10)iVar2;
    if (((fVar3 <= (float)W_y2) && ((float)W_y1 < (fVar3 + param_6) - 0.5)) &&
       ((fVar5 <= (float)W_x2 && ((float)W_x1 < (fVar5 + param_5) - 0.5)))) {
      local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
      fVar4 = (float)local_f4;
      if (fVar3 <= fVar4) {
        local_ec = 0;
      }
      else {
        if ((float)local_f4 < fVar3 - 0.5) {
          local_f4 = local_f4 + 1;
          fVar4 = (float)local_f4;
        }
        local_4c = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar2) / param_6) * 65536.0);
        local_ec = local_4c;
      }
      if (local_f4 < W_y1) {
        iVar8 = W_y1 - local_f4;
        local_f4 = W_y1;
        local_4c = (uint)(longlong)ROUND(((float)(iVar8 * iVar2) / param_6) * 65536.0);
        local_ec = local_ec + local_4c;
      }
      iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_6) - 0.5));
      if (W_y2 < iVar8) {
        iVar8 = W_y2;
      }
      if (iVar8 - local_f4 != -1 && -1 < (iVar8 - local_f4) + 1) {
        local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar3 = (float)local_fc;
        if (fVar5 <= fVar3) {
          local_f0 = 0;
        }
        else {
          if ((float)local_fc < fVar5 - 0.5) {
            local_fc = local_fc + 1;
            fVar3 = (float)local_fc;
          }
          local_4c = (uint)(longlong)ROUND((((fVar3 - fVar5) * (float10)iVar1) / param_5) * 65536.0);
          local_f0 = local_4c;
        }
        if (fVar5 < (float)W_x1) {
          iVar9 = W_x1 - local_fc;
          local_fc = W_x1;
          local_134 = (int)(longlong)ROUND(((float)(iVar9 * iVar1) / param_5) * 65536.0);
          local_f0 = local_f0 + local_134;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
        if (W_x2 < iVar9) {
          iVar9 = W_x2;
        }
        local_4c = (uint)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
        iVar1 = (int)GHIDRA_FIST32((float)(iVar2 << 0x10) / param_6);
        for (; ((int)local_f0 < 0 && (local_fc <= iVar9)); local_fc = local_fc + 1) {
          local_f0 = local_f0 + local_4c;
        }
        iVar10 = (int)local_f0 >> 0x10;
        if (iVar10 != 0) {
          local_f0 = local_f0 & 0xffff;
          local_100 = iVar10;
        }
        for (; ((int)local_ec < 0 && (local_f4 <= iVar8)); local_f4 = local_f4 + 1) {
          local_ec = local_ec + iVar1;
        }
        iVar10 = (int)local_ec >> 0x10;
        if (iVar10 != 0) {
          local_ec = local_ec & 0xffff;
          local_f8 = iVar10;
        }
        iVar9 = (iVar9 - local_fc) + 1;
        iVar8 = (iVar8 - local_f4) + 1;
        if ((0 < iVar9) && (0 < iVar8)) {
          iVar10 = SpriteDecompGetAndLockData(param_1,param_2);
          if (iVar10 != 0) {
            iVar11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)param_1[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
            }
            else {
              EBPalUpdate((int *)param_1[5]);
            }
            local_d8 = 0;
            if (0 < iVar8) {
              do {
                pcVar12 = (char *)(iVar10 + *(int *)(piVar6[0xb] + -4 +
                                                    ((iVar2 - local_f8) - ((int)local_ec >> 0x10)) *
                                                    4) + local_100);
                puVar19 = (ushort *)
                          (local_fc * 2 +
                          iVar11 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_f4 + local_d8) * 4));
                uVar18 = local_f0;
                for (iVar16 = iVar9; iVar16 != 0; iVar16 = iVar16 + -1) {
                  if (*pcVar12 != '\0') {
                    uVar17 = (uint)*puVar19;
                    iVar13 = (uVar17 & 0xf800) - (param_7 & 0xf800);
                    iVar15 = (uVar17 & 0x7e0) - (param_7 & 0x7e0);
                    iVar14 = (uVar17 & 0x1f) - (param_7 & 0x1f);
                    *puVar19 = (ushort)iVar13 & -(short)(iVar13 >> 0x1f) - 1U |
                               (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U |
                               (ushort)iVar14 & -(short)(iVar14 >> 0x1f) - 1U;
                  }
                  uVar17 = uVar18 + local_4c;
                  puVar19 = puVar19 + 1;
                  uVar18 = uVar17 & 0xffff;
                  pcVar12 = pcVar12 + (uVar17 >> 0x10);
                }
                local_d8 = local_d8 + 1;
                local_ec = local_ec + iVar1;
              } while (local_d8 < iVar8);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirHV8to16 @ 0x08078910, 2241 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleShadowTransSubMirHV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  ushort *puVar20;
  int local_134;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  uint local_f0;
  uint local_ec;
  int local_d8;
  uint local_4c;
  
  piVar7 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_f8 = 0;
  local_100 = 0;
  if (((0.0 < param_5) && (0.0 < param_6)) && (param_7 != 0)) {
    iVar2 = *piVar7;
    iVar3 = piVar7[1];
    fVar6 = param_3 - ((float)((iVar2 - piVar7[2]) + -1) * param_5) / (float10)iVar2;
    fVar4 = param_4 - ((float)((iVar3 - piVar7[3]) + -1) * param_6) / (float10)iVar3;
    if (((fVar4 <= (float)W_y2) && ((float)W_y1 < (fVar4 + param_6) - 0.5)) &&
       ((fVar6 <= (float)W_x2 && ((float)W_x1 < (fVar6 + param_5) - 0.5)))) {
      local_f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
      fVar5 = (float)local_f4;
      if (fVar4 <= fVar5) {
        local_ec = 0;
      }
      else {
        if ((float)local_f4 < fVar4 - 0.5) {
          local_f4 = local_f4 + 1;
          fVar5 = (float)local_f4;
        }
        local_4c = (uint)(longlong)ROUND((((fVar5 - fVar4) * (float10)iVar3) / param_6) * 65536.0);
        local_ec = local_4c;
      }
      if (local_f4 < W_y1) {
        iVar9 = W_y1 - local_f4;
        local_f4 = W_y1;
        local_4c = (uint)(longlong)ROUND(((float)(iVar9 * iVar3) / param_6) * 65536.0);
        local_ec = local_ec + local_4c;
      }
      iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_6) - 0.5));
      if (W_y2 < iVar9) {
        iVar9 = W_y2;
      }
      if (iVar9 - local_f4 != -1 && -1 < (iVar9 - local_f4) + 1) {
        local_fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
        fVar4 = (float)local_fc;
        if (fVar6 <= fVar4) {
          local_f0 = 0;
        }
        else {
          if ((float)local_fc < fVar6 - 0.5) {
            local_fc = local_fc + 1;
            fVar4 = (float)local_fc;
          }
          local_4c = (uint)(longlong)ROUND((((fVar4 - fVar6) * (float10)iVar2) / param_5) * 65536.0);
          local_f0 = local_4c;
        }
        if (fVar6 < (float)W_x1) {
          iVar10 = W_x1 - local_fc;
          local_fc = W_x1;
          local_134 = (int)(longlong)ROUND(((float)(iVar10 * iVar2) / param_5) * 65536.0);
          local_f0 = local_f0 + local_134;
        }
        iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_5) - 0.5));
        if (W_x2 < iVar10) {
          iVar10 = W_x2;
        }
        local_134 = (int)(longlong)ROUND((float)(iVar2 << 0x10) / param_5);
        iVar1 = (int)GHIDRA_FIST32((float)(iVar3 << 0x10) / param_6);
        for (; ((int)local_f0 < 0 && (local_fc <= iVar10)); local_fc = local_fc + 1) {
          local_f0 = local_f0 + local_134;
        }
        iVar11 = (int)local_f0 >> 0x10;
        if (iVar11 != 0) {
          local_f0 = local_f0 & 0xffff;
          local_100 = iVar11;
        }
        for (; ((int)local_ec < 0 && (local_f4 <= iVar9)); local_f4 = local_f4 + 1) {
          local_ec = local_ec + iVar1;
        }
        iVar11 = (int)local_ec >> 0x10;
        if (iVar11 != 0) {
          local_ec = local_ec & 0xffff;
          local_f8 = iVar11;
        }
        iVar10 = (iVar10 - local_fc) + 1;
        iVar9 = (iVar9 - local_f4) + 1;
        if ((0 < iVar10) && (0 < iVar9)) {
          iVar11 = SpriteDecompGetAndLockData(param_1,param_2);
          if (iVar11 != 0) {
            iVar12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)param_1[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)param_1,piVar7[0xc]);
            }
            else {
              EBPalUpdate((int *)param_1[5]);
            }
            local_d8 = 0;
            if (0 < iVar9) {
              do {
                pcVar13 = (char *)(((iVar11 + *(int *)(piVar7[0xb] + -4 +
                                                      ((iVar3 - local_f8) - ((int)local_ec >> 0x10))
                                                      * 4) + iVar2) - local_100) + -1);
                puVar20 = (ushort *)
                          (local_fc * 2 +
                          iVar12 + *(int *)(*(int *)(iVar8 + 0x2c) + (local_f4 + local_d8) * 4));
                uVar19 = local_f0;
                for (iVar17 = iVar10; iVar17 != 0; iVar17 = iVar17 + -1) {
                  if (*pcVar13 != '\0') {
                    uVar18 = (uint)*puVar20;
                    iVar14 = (uVar18 & 0xf800) - (param_7 & 0xf800);
                    iVar16 = (uVar18 & 0x7e0) - (param_7 & 0x7e0);
                    iVar15 = (uVar18 & 0x1f) - (param_7 & 0x1f);
                    *puVar20 = (ushort)iVar14 & -(short)(iVar14 >> 0x1f) - 1U |
                               (ushort)iVar16 & -(short)(iVar16 >> 0x1f) - 1U |
                               (ushort)iVar15 & -(short)(iVar15 >> 0x1f) - 1U;
                  }
                  uVar18 = uVar19 + local_134;
                  puVar20 = puVar20 + 1;
                  uVar19 = uVar18 & 0xffff;
                  pcVar13 = pcVar13 + -(uVar18 >> 0x10);
                }
                local_d8 = local_d8 + 1;
                local_ec = local_ec + iVar1;
              } while (local_d8 < iVar9);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_RotateShadowTransSub8to16_P @ 0x080791e0, 3748 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int W_RotateShadowTransSub8to16_P
              (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
              float param_7,float param_8,float param_9,uint param_10)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ulonglong uVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  int *piVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  uint uVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  int local_78;
  int local_74;
  int local_68;
  int local_64;
  int local_60;
  int local_54;
  int local_50;
  ushort *local_38;
  
  piVar16 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar17 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar20 = piVar16[0xb];
  iVar18 = roundfloat(param_3);
  iVar19 = roundfloat(param_4);
  local_54 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (local_54 < 0) {
    local_54 = -local_54;
    param_5 = param_5 + 180.0;
  }
  iVar31 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar31 < 0) {
    iVar31 = -iVar31;
    param_5 = param_5 + 180.0;
  }
  if (local_54 == 0) {
    return 0;
  }
  if (iVar31 == 0) {
    return local_54;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar7 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar26 = (int)uVar7;
  if (iVar26 == 0) {
LAB_08079510:
    iVar20 = W_ScaleShadowTransSub_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9,param_10
                       );
    return iVar20;
  }
  if (iVar26 == 0x5a0) {
    param_7 = -param_7;
    param_6 = -param_6;
    goto LAB_08079510;
  }
  iVar3 = *piVar16;
  iVar4 = piVar16[1];
  iVar5 = piVar16[2];
  iVar6 = piVar16[3];
  fVar8 = (float)SinTable[(iVar26 + 0x2d0) % 0xb40];
  fVar9 = fVar8 * 0.0009765625;
  fVar11 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar26 >> 0x1f) << 0x20 | uVar7 & 0xffffffff) %
                                0xb40)];
  fVar10 = fVar11 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar26 + 0x2d0) % 0xb40] << 0x10) / local_54) / param_8);
  iVar21 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar26 >> 0x1f) << 0x20 | uVar7 & 0xffffffff) % 0xb40)
                    ] << 0x10) / iVar31;
  iVar2 = (int)GHIDRA_FIST32((float10)iVar21 / param_8);
  if (iVar26 < 0x2d0) {
    iVar26 = -iVar5;
    iVar22 = -iVar6;
    iVar21 = (iVar3 - iVar5) + -1;
    iVar23 = (iVar4 - iVar6) + -1;
LAB_0807974f:
    fVar12 = (float10)iVar26;
    fVar13 = (float10)iVar21;
    local_88 = (float10)iVar22;
    local_90 = (float10)iVar23;
    local_8c = local_90;
    fVar15 = fVar12;
  }
  else {
    if (iVar26 < 0x5a0) {
      iVar21 = (iVar3 - iVar5) + -1;
      iVar22 = -iVar6;
      iVar26 = (iVar4 - iVar6) + -1;
      iVar23 = -iVar5;
    }
    else {
      if (iVar26 < 0x870) {
        iVar26 = (iVar3 - iVar5) + -1;
        iVar22 = (iVar4 - iVar6) + -1;
        iVar21 = -iVar5;
        iVar23 = -iVar6;
        goto LAB_0807974f;
      }
      if (0xb3f < iVar26) {
        return iVar21;
      }
      iVar21 = -iVar5;
      iVar22 = (iVar4 - iVar6) + -1;
      iVar26 = -iVar6;
      iVar23 = (iVar3 - iVar5) + -1;
    }
    fVar12 = (float10)iVar21;
    local_8c = (float10)iVar26;
    fVar13 = (float10)iVar23;
    local_90 = (float10)iVar22;
    local_88 = local_8c;
    fVar15 = fVar13;
  }
  local_84 = (float10)iVar21;
  local_8c = local_8c * param_7;
  fVar12 = fVar12 * param_6;
  fVar14 = (float10)iVar22 * param_7;
  fVar13 = fVar13 * param_6;
  iVar26 = roundfloat((-fVar12 * fVar10 + fVar14 * fVar9) * param_9);
  iVar21 = roundfloat((-fVar13 * fVar10 + local_8c * fVar9) * param_9);
  local_50 = roundfloat((-(local_84 * param_6) * fVar10 + local_88 * param_7 * fVar9) * param_9);
  local_94 = roundfloat((-(fVar15 * param_6) * fVar10 + local_90 * param_7 * fVar9) * param_9);
  if ((local_50 == iVar26) || (local_50 == iVar21)) {
    local_78 = 0;
    local_74 = 0;
    local_64 = (int)GHIDRA_FIST32((fVar12 * fVar9 + fVar14 * fVar10) * 65536.0 * param_8);
    local_68 = (int)GHIDRA_FIST32((fVar13 * fVar9 + local_8c * fVar10) * 65536.0 * param_8);
  }
  else {
    fVar15 = fVar9 * local_84 * param_6 + local_88 * param_7 * fVar10;
    local_74 = (int)GHIDRA_FIST32(((fVar15 - (fVar12 * fVar9 + fVar14 * fVar10)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar26));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_78 = (int)GHIDRA_FIST32((((local_8c * fVar10 + fVar13 * fVar9) - fVar15) * 65536.0 * param_8) /
                          (float)(local_50 - iVar21));
    if (local_78 < 0) {
      local_78 = -local_78;
    }
    local_68 = (int)GHIDRA_FIST32(fVar15 * 65536.0 * param_8);
    local_64 = local_68;
  }
  for (; local_50 < W_y1 - iVar19; local_50 = local_50 + 1) {
    iVar22 = local_78;
    if (local_50 < iVar26) {
      iVar22 = -local_74;
    }
    local_64 = local_64 + iVar22;
    iVar22 = local_78;
    if (iVar21 <= local_50) {
      iVar22 = -local_74;
    }
    local_68 = local_68 + iVar22;
  }
  if (W_y2 - iVar19 < local_94) {
    local_94 = W_y2 - iVar19;
  }
  iVar22 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar22 == 0) {
    return 0;
  }
  iVar23 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  if ((int *)param_1[5] == (int *)0x0) {
    SpriteArrayPalUpdateAndAccess((int)param_1,piVar16[0xc]);
  }
  else {
    EBPalUpdate((int *)param_1[5]);
  }
  if (local_50 <= local_94) {
    iVar24 = W_x1 - iVar18;
    do {
      iVar33 = local_64 >> 0x10;
      if (local_64 >> 0x10 < iVar24) {
        iVar33 = iVar24;
      }
      iVar25 = local_68 >> 0x10;
      if (W_x2 - iVar18 < local_68 >> 0x10) {
        iVar25 = W_x2 - iVar18;
      }
      local_60 = (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar8 -
                             ((float)local_50 / param_9) * fVar11) * 65536.0) / (float)local_54) +
                 iVar5 * 0x10000;
      iVar32 = iVar6 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar11 + ((float)local_50 / param_9) * fVar8
                           ) * 65536.0) / (float10)iVar31);
      local_38 = (ushort *)
                 (iVar23 + *(int *)(*(int *)(iVar17 + 0x2c) + (local_50 + iVar19) * 4) +
                 (iVar18 + iVar33) * 2);
      iVar27 = (iVar25 - iVar33) + 1;
      iVar30 = iVar25 - iVar33;
      iVar29 = iVar2 * iVar27 + iVar32;
      for (iVar27 = local_60 + iVar1 * iVar27;
          (SBORROW4(iVar25,iVar33) == iVar30 < 0 &&
          ((((iVar4 <= iVar29 >> 0x10 || (iVar3 <= iVar27 >> 0x10)) || (iVar29 >> 0x10 < 0)) ||
           (iVar27 >> 0x10 < 0)))); iVar27 = iVar27 - iVar1) {
        iVar25 = iVar25 + -1;
        iVar29 = iVar29 - iVar2;
        iVar30 = iVar25 - iVar33;
      }
      for (; (iVar33 <= iVar25 &&
             (((iVar4 <= iVar32 >> 0x10 || (iVar3 <= local_60 >> 0x10)) ||
              ((iVar32 >> 0x10 < 0 || (local_60 >> 0x10 < 0)))))); local_60 = local_60 + iVar1) {
        local_38 = local_38 + 1;
        iVar33 = iVar33 + 1;
        iVar32 = iVar32 + iVar2;
      }
      iVar33 = (iVar25 - iVar33) + 1;
      if (0 < iVar33) {
        do {
          if (*(char *)((local_60 >> 0x10) + iVar22 + *(int *)(iVar20 + (iVar32 >> 0x10) * 4)) !=
              '\0') {
            uVar28 = (uint)*local_38;
            iVar25 = (uVar28 & 0xf800) - (param_10 & 0xf800);
            iVar29 = (uVar28 & 0x1f) - (param_10 & 0x1f);
            iVar30 = (uVar28 & 0x7e0) - (param_10 & 0x7e0);
            *local_38 = (ushort)iVar25 & -(short)(iVar25 >> 0x1f) - 1U |
                        (ushort)iVar30 & -(short)(iVar30 >> 0x1f) - 1U |
                        (ushort)iVar29 & -(short)(iVar29 >> 0x1f) - 1U;
          }
          local_60 = local_60 + iVar1;
          local_38 = local_38 + 1;
          iVar32 = iVar32 + iVar2;
          iVar33 = iVar33 + -1;
        } while (iVar33 != 0);
      }
      iVar33 = local_78;
      if (local_50 < iVar26) {
        iVar33 = -local_74;
      }
      local_64 = local_64 + iVar33;
      iVar33 = local_78;
      if (iVar21 <= local_50) {
        iVar33 = -local_74;
      }
      local_68 = local_68 + iVar33;
      local_50 = local_50 + 1;
    } while (local_50 <= local_94);
  }
  iVar20 = SpriteDecompUnlockData();
  return iVar20;
}

/* W_RotateShadowTransSubMirH8to16_P @ 0x0807a090, 3748 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int W_RotateShadowTransSubMirH8to16_P
              (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
              float param_7,float param_8,float param_9,uint param_10)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ulonglong uVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  int *piVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  uint uVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  int local_78;
  int local_74;
  int local_68;
  int local_64;
  int local_60;
  int local_54;
  int local_50;
  ushort *local_38;
  
  piVar16 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar17 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar20 = piVar16[0xb];
  iVar18 = roundfloat(param_3);
  iVar19 = roundfloat(param_4);
  local_54 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (local_54 < 0) {
    local_54 = -local_54;
    param_5 = param_5 + 180.0;
  }
  iVar29 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar29 < 0) {
    iVar29 = -iVar29;
    param_5 = param_5 + 180.0;
  }
  if (local_54 == 0) {
    return 0;
  }
  if (iVar29 == 0) {
    return local_54;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar7 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar24 = (int)uVar7;
  if (iVar24 == 0) {
    param_6 = -param_6;
LAB_0807a3bd:
    iVar20 = W_ScaleShadowTransSub_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9,param_10
                       );
    return iVar20;
  }
  if (iVar24 == 0x5a0) {
    param_7 = -param_7;
    goto LAB_0807a3bd;
  }
  iVar3 = *piVar16;
  iVar4 = piVar16[1];
  iVar5 = piVar16[2];
  iVar6 = piVar16[3];
  fVar8 = (float)SinTable[(iVar24 + 0x2d0) % 0xb40];
  fVar9 = fVar8 * 0.0009765625;
  fVar11 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar24 >> 0x1f) << 0x20 | uVar7 & 0xffffffff) %
                                0xb40)];
  fVar10 = fVar11 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar24 + 0x2d0) % 0xb40] << 0x10) / local_54) / param_8);
  iVar21 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar24 >> 0x1f) << 0x20 | uVar7 & 0xffffffff) % 0xb40)
                    ] << 0x10) / iVar29;
  iVar2 = (int)GHIDRA_FIST32((float10)iVar21 / param_8);
  if (iVar24 < 0x2d0) {
    iVar24 = -iVar5;
    iVar21 = -iVar6;
    iVar22 = (iVar3 - iVar5) + -1;
    iVar23 = (iVar4 - iVar6) + -1;
LAB_0807a5ff:
    fVar12 = (float10)iVar24;
    fVar13 = (float10)iVar22;
    local_88 = (float10)iVar21;
    local_90 = (float10)iVar23;
    local_8c = local_90;
    fVar15 = fVar12;
  }
  else {
    if (iVar24 < 0x5a0) {
      iVar22 = (iVar3 - iVar5) + -1;
      iVar21 = -iVar6;
      iVar24 = (iVar4 - iVar6) + -1;
      iVar23 = -iVar5;
    }
    else {
      if (iVar24 < 0x870) {
        iVar24 = (iVar3 - iVar5) + -1;
        iVar21 = (iVar4 - iVar6) + -1;
        iVar22 = -iVar5;
        iVar23 = -iVar6;
        goto LAB_0807a5ff;
      }
      if (0xb3f < iVar24) {
        return iVar21;
      }
      iVar22 = -iVar5;
      iVar21 = (iVar4 - iVar6) + -1;
      iVar24 = -iVar6;
      iVar23 = (iVar3 - iVar5) + -1;
    }
    fVar12 = (float10)iVar22;
    local_8c = (float10)iVar24;
    fVar13 = (float10)iVar23;
    local_90 = (float10)iVar21;
    local_88 = local_8c;
    fVar15 = fVar13;
  }
  local_84 = (float10)iVar22;
  local_8c = local_8c * param_7;
  fVar12 = fVar12 * param_6;
  fVar14 = (float10)iVar21 * param_7;
  fVar13 = fVar13 * param_6;
  iVar24 = roundfloat((-fVar12 * fVar10 + fVar14 * fVar9) * param_9);
  iVar21 = roundfloat((-fVar13 * fVar10 + local_8c * fVar9) * param_9);
  local_50 = roundfloat((-(local_84 * param_6) * fVar10 + local_88 * param_7 * fVar9) * param_9);
  local_94 = roundfloat((-(fVar15 * param_6) * fVar10 + local_90 * param_7 * fVar9) * param_9);
  if ((local_50 == iVar24) || (local_50 == iVar21)) {
    local_78 = 0;
    local_74 = 0;
    local_64 = (int)GHIDRA_FIST32((fVar12 * fVar9 + fVar14 * fVar10) * 65536.0 * param_8);
    local_68 = (int)GHIDRA_FIST32((fVar13 * fVar9 + local_8c * fVar10) * 65536.0 * param_8);
  }
  else {
    fVar15 = fVar9 * local_84 * param_6 + local_88 * param_7 * fVar10;
    local_74 = (int)GHIDRA_FIST32(((fVar15 - (fVar12 * fVar9 + fVar14 * fVar10)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar24));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_78 = (int)GHIDRA_FIST32((((local_8c * fVar10 + fVar13 * fVar9) - fVar15) * 65536.0 * param_8) /
                          (float)(local_50 - iVar21));
    if (local_78 < 0) {
      local_78 = -local_78;
    }
    local_68 = (int)GHIDRA_FIST32(fVar15 * 65536.0 * param_8);
    local_64 = local_68;
  }
  for (; local_50 < W_y1 - iVar19; local_50 = local_50 + 1) {
    iVar22 = local_78;
    if (local_50 < iVar24) {
      iVar22 = -local_74;
    }
    local_64 = local_64 + iVar22;
    iVar22 = local_78;
    if (iVar21 <= local_50) {
      iVar22 = -local_74;
    }
    local_68 = local_68 + iVar22;
  }
  if (W_y2 - iVar19 < local_94) {
    local_94 = W_y2 - iVar19;
  }
  iVar22 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar22 == 0) {
    return 0;
  }
  iVar23 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  if ((int *)param_1[5] == (int *)0x0) {
    SpriteArrayPalUpdateAndAccess((int)param_1,piVar16[0xc]);
  }
  else {
    EBPalUpdate((int *)param_1[5]);
  }
  if (local_50 <= local_94) {
    do {
      iVar31 = local_64 >> 0x10;
      iVar32 = local_68 >> 0x10;
      if (W_x2 < iVar18 - iVar31) {
        iVar31 = iVar18 - W_x2;
      }
      if (iVar18 - iVar32 < W_x1) {
        iVar32 = iVar18 - W_x1;
      }
      local_60 = (int)GHIDRA_FIST32(((((float10)iVar31 / param_8) * fVar8 -
                             ((float)local_50 / param_9) * fVar11) * 65536.0) / (float)local_54) +
                 iVar5 * 0x10000;
      iVar30 = iVar6 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar31 / param_8) * fVar11 + ((float)local_50 / param_9) * fVar8
                           ) * 65536.0) / (float10)iVar29);
      local_38 = (ushort *)
                 (iVar23 + *(int *)(*(int *)(iVar17 + 0x2c) + (local_50 + iVar19) * 4) +
                 (iVar18 - iVar31) * 2);
      iVar25 = (iVar32 - iVar31) + 1;
      iVar28 = iVar32 - iVar31;
      iVar27 = iVar2 * iVar25 + iVar30;
      for (iVar25 = local_60 + iVar1 * iVar25;
          (SBORROW4(iVar32,iVar31) == iVar28 < 0 &&
          ((((iVar4 <= iVar27 >> 0x10 || (iVar3 <= iVar25 >> 0x10)) || (iVar27 >> 0x10 < 0)) ||
           (iVar25 >> 0x10 < 0)))); iVar25 = iVar25 - iVar1) {
        iVar32 = iVar32 + -1;
        iVar27 = iVar27 - iVar2;
        iVar28 = iVar32 - iVar31;
      }
      for (; (iVar31 <= iVar32 &&
             (((iVar4 <= iVar30 >> 0x10 || (iVar3 <= local_60 >> 0x10)) ||
              ((iVar30 >> 0x10 < 0 || (local_60 >> 0x10 < 0)))))); local_60 = local_60 + iVar1) {
        local_38 = local_38 + -1;
        iVar31 = iVar31 + 1;
        iVar30 = iVar30 + iVar2;
      }
      iVar31 = (iVar32 - iVar31) + 1;
      if (0 < iVar31) {
        do {
          if (*(char *)((local_60 >> 0x10) + iVar22 + *(int *)(iVar20 + (iVar30 >> 0x10) * 4)) !=
              '\0') {
            uVar26 = (uint)*local_38;
            iVar32 = (uVar26 & 0xf800) - (param_10 & 0xf800);
            iVar27 = (uVar26 & 0x1f) - (param_10 & 0x1f);
            iVar28 = (uVar26 & 0x7e0) - (param_10 & 0x7e0);
            *local_38 = (ushort)iVar32 & -(short)(iVar32 >> 0x1f) - 1U |
                        (ushort)iVar28 & -(short)(iVar28 >> 0x1f) - 1U |
                        (ushort)iVar27 & -(short)(iVar27 >> 0x1f) - 1U;
          }
          local_60 = local_60 + iVar1;
          local_38 = local_38 + -1;
          iVar30 = iVar30 + iVar2;
          iVar31 = iVar31 + -1;
        } while (iVar31 != 0);
      }
      iVar31 = local_78;
      if (local_50 < iVar24) {
        iVar31 = -local_74;
      }
      local_64 = local_64 + iVar31;
      iVar31 = local_78;
      if (iVar21 <= local_50) {
        iVar31 = -local_74;
      }
      local_68 = local_68 + iVar31;
      local_50 = local_50 + 1;
    } while (local_50 <= local_94);
  }
  iVar20 = SpriteDecompUnlockData();
  return iVar20;
}

