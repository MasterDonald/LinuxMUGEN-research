/*
 * spr16-lb.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0805cd70-0x08062431, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern byte GlobalTemp[32] __asm__("D_082a6b80"); /* file-static 0x082a6b80 */

/* W_PutSprite8to16 @ 0x0805cd70, 552 bytes */
void W_PutSprite8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  byte *pbVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int local_4c;
  int local_3c;
  int local_38;
  int local_34;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_38 = 0;
  iVar6 = param_4 - piVar1[3];
  local_3c = 0;
  iVar8 = param_3 - piVar1[2];
  if ((((iVar6 <= W_y2) && (W_y1 < piVar1[1] + iVar6)) && (iVar8 <= W_x2)) &&
     (W_x1 < *piVar1 + iVar8)) {
    local_34 = iVar6;
    if (iVar6 < W_y1) {
      local_34 = W_y1;
      local_38 = W_y1 - iVar6;
    }
    iVar6 = piVar1[1] + iVar6 + -1;
    if (W_y2 < iVar6) {
      iVar6 = W_y2;
    }
    iVar9 = iVar8;
    if (iVar8 < W_x1) {
      local_3c = W_x1 - iVar8;
      iVar9 = W_x1;
    }
    iVar8 = *piVar1 + iVar8 + -1;
    if (W_x2 < iVar8) {
      iVar8 = W_x2;
    }
    iVar8 = (iVar8 - iVar9) + 1;
    local_4c = (iVar6 - local_34) + 1;
    if (((0 < iVar8) && (0 < local_4c)) &&
       (iVar6 = SpriteDecompGetAndLockData(param_1,param_2), iVar6 != 0)) {
      iVar3 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar4 = (int *)param_1[5];
      if (piVar4 == (int *)0x0) {
        piVar4 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar1[0xc]);
      }
      else {
        EBPalUpdate(piVar4);
      }
      if (0 < local_4c) {
        piVar10 = (int *)(local_34 * 4 + *(int *)(iVar2 + 0x2c));
        piVar1 = (int *)(local_38 * 4 + piVar1[0xb]);
        do {
          pbVar5 = (byte *)(local_3c + iVar6 + *piVar1);
          puVar7 = (undefined2 *)(iVar9 * 2 + iVar3 + *piVar10);
          for (iVar2 = iVar8; iVar2 != 0; iVar2 = iVar2 + -1) {
            if (*pbVar5 != 0) {
              *puVar7 = *(undefined2 *)((int)piVar4 + (uint)*pbVar5 * 2 + 0x5c);
            }
            puVar7 = puVar7 + 1;
            pbVar5 = pbVar5 + 1;
          }
          piVar10 = piVar10 + 1;
          piVar1 = piVar1 + 1;
          local_4c = local_4c + -1;
        } while (local_4c != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteFlat8to16 @ 0x0805cfa0, 536 bytes */
void W_PutSpriteFlat8to16(int *param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined2 *puVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int local_48;
  int local_38;
  int local_34;
  int local_30;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar3 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_34 = 0;
  iVar7 = param_4 - piVar2[3];
  local_38 = 0;
  iVar9 = param_3 - piVar2[2];
  if ((((iVar7 <= W_y2) && (W_y1 < piVar2[1] + iVar7)) && (iVar9 <= W_x2)) &&
     (W_x1 < *piVar2 + iVar9)) {
    local_30 = iVar7;
    if (iVar7 < W_y1) {
      local_30 = W_y1;
      local_34 = W_y1 - iVar7;
    }
    iVar7 = piVar2[1] + iVar7 + -1;
    if (W_y2 < iVar7) {
      iVar7 = W_y2;
    }
    iVar10 = iVar9;
    if (iVar9 < W_x1) {
      local_38 = W_x1 - iVar9;
      iVar10 = W_x1;
    }
    iVar9 = *piVar2 + iVar9 + -1;
    if (W_x2 < iVar9) {
      iVar9 = W_x2;
    }
    iVar9 = (iVar9 - iVar10) + 1;
    local_48 = (iVar7 - local_30) + 1;
    if (((0 < iVar9) && (0 < local_48)) &&
       (iVar7 = SpriteDecompGetAndLockData(param_1,param_2), iVar7 != 0)) {
      iVar4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar5 = (int *)param_1[5];
      if (piVar5 == (int *)0x0) {
        piVar5 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar2[0xc]);
      }
      else {
        EBPalUpdate(piVar5);
      }
      if (0 < local_48) {
        piVar11 = (int *)(local_30 * 4 + *(int *)(iVar3 + 0x2c));
        piVar2 = (int *)(local_34 * 4 + piVar2[0xb]);
        do {
          pbVar8 = (byte *)(local_38 + iVar7 + *piVar2);
          puVar6 = (undefined2 *)(iVar10 * 2 + iVar4 + *piVar11);
          for (iVar3 = iVar9; iVar3 != 0; iVar3 = iVar3 + -1) {
            bVar1 = *pbVar8;
            pbVar8 = pbVar8 + 1;
            *puVar6 = *(undefined2 *)((int)piVar5 + (uint)bVar1 * 2 + 0x5c);
            puVar6 = puVar6 + 1;
          }
          piVar11 = piVar11 + 1;
          piVar2 = piVar2 + 1;
          local_48 = local_48 + -1;
        } while (local_48 != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirH8to16 @ 0x0805d1c0, 600 bytes */
void W_PutSpriteMirH8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  byte *pbVar8;
  int iVar9;
  undefined2 *puVar10;
  int iVar11;
  int *piVar12;
  int local_50;
  int local_3c;
  int local_38;
  int local_34;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar3 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = *piVar2;
  local_38 = 0;
  iVar4 = (piVar2[2] - iVar1) + 1 + param_3;
  iVar9 = param_4 - piVar2[3];
  local_3c = 0;
  if ((((iVar9 <= W_y2) && (W_y1 < piVar2[1] + iVar9)) && (iVar4 <= W_x2)) && (W_x1 < iVar1 + iVar4)
     ) {
    local_34 = iVar9;
    if (iVar9 < W_y1) {
      local_34 = W_y1;
      local_38 = W_y1 - iVar9;
    }
    iVar9 = piVar2[1] + iVar9 + -1;
    if (W_y2 < iVar9) {
      iVar9 = W_y2;
    }
    iVar11 = iVar4;
    if (iVar4 < W_x1) {
      local_3c = W_x1 - iVar4;
      iVar11 = W_x1;
    }
    iVar4 = iVar1 + iVar4 + -1;
    if (W_x2 < iVar4) {
      iVar4 = W_x2;
    }
    iVar4 = (iVar4 - iVar11) + 1;
    iVar9 = (iVar9 - local_34) + 1;
    if (((0 < iVar4) && (0 < iVar9)) &&
       (iVar5 = SpriteDecompGetAndLockData(param_1,param_2), iVar5 != 0)) {
      iVar6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar7 = (int *)param_1[5];
      if (piVar7 == (int *)0x0) {
        piVar7 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar2[0xc]);
      }
      else {
        EBPalUpdate(piVar7);
      }
      local_50 = 0;
      if (0 < iVar9) {
        piVar12 = (int *)(local_38 * 4 + piVar2[0xb]);
        piVar2 = (int *)(local_34 * 4 + *(int *)(iVar3 + 0x2c));
        do {
          pbVar8 = (byte *)((iVar5 + *piVar12 + iVar1) - local_3c);
          puVar10 = (undefined2 *)(iVar11 * 2 + iVar6 + *piVar2);
          for (iVar3 = iVar4; iVar3 != 0; iVar3 = iVar3 + -1) {
            pbVar8 = pbVar8 + -1;
            if (*pbVar8 != 0) {
              *puVar10 = *(undefined2 *)((int)piVar7 + (uint)*pbVar8 * 2 + 0x5c);
            }
            puVar10 = puVar10 + 1;
          }
          local_50 = local_50 + 1;
          piVar12 = piVar12 + 1;
          piVar2 = piVar2 + 1;
        } while (local_50 < iVar9);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirV8to16 @ 0x0805d420, 568 bytes */
void W_PutSpriteMirV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  byte *pbVar9;
  undefined2 *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int local_3c;
  int local_38;
  int local_34;
  
  piVar3 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar4 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_38 = 0;
  iVar1 = piVar3[1];
  iVar11 = param_3 - piVar3[2];
  iVar8 = (piVar3[3] - iVar1) + 1 + param_4;
  local_3c = 0;
  if ((((iVar8 <= W_y2) && (W_y1 < iVar1 + iVar8)) && (iVar11 <= W_x2)) && (W_x1 < *piVar3 + iVar11)
     ) {
    local_34 = iVar8;
    if (iVar8 < W_y1) {
      local_34 = W_y1;
      local_38 = W_y1 - iVar8;
    }
    iVar8 = iVar1 + iVar8 + -1;
    if (W_y2 < iVar8) {
      iVar8 = W_y2;
    }
    iVar12 = iVar11;
    if (iVar11 < W_x1) {
      local_3c = W_x1 - iVar11;
      iVar12 = W_x1;
    }
    iVar11 = *piVar3 + iVar11 + -1;
    if (W_x2 < iVar11) {
      iVar11 = W_x2;
    }
    iVar11 = (iVar11 - iVar12) + 1;
    iVar8 = (iVar8 - local_34) + 1;
    if (((0 < iVar11) && (0 < iVar8)) &&
       (iVar5 = SpriteDecompGetAndLockData(param_1,param_2), iVar5 != 0)) {
      iVar6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar7 = (int *)param_1[5];
      if (piVar7 == (int *)0x0) {
        piVar7 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar3[0xc]);
      }
      else {
        EBPalUpdate(piVar7);
      }
      iVar13 = 0;
      if (0 < iVar8) {
        iVar2 = piVar3[0xb];
        piVar3 = (int *)(local_34 * 4 + *(int *)(iVar4 + 0x2c));
        do {
          pbVar9 = (byte *)(iVar5 + *(int *)(iVar2 + -4 + ((iVar1 - local_38) - iVar13) * 4) +
                           local_3c);
          puVar10 = (undefined2 *)(iVar12 * 2 + iVar6 + *piVar3);
          for (iVar4 = iVar11; iVar4 != 0; iVar4 = iVar4 + -1) {
            if (*pbVar9 != 0) {
              *puVar10 = *(undefined2 *)((int)piVar7 + (uint)*pbVar9 * 2 + 0x5c);
            }
            puVar10 = puVar10 + 1;
            pbVar9 = pbVar9 + 1;
          }
          iVar13 = iVar13 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar13 < iVar8);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirHV8to16 @ 0x0805d660, 584 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_) */
void W_PutSpriteMirHV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  byte *pbVar10;
  undefined2 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int local_3c;
  int local_38;
  int local_34;
  
  piVar4 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar5 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar1 = *piVar4;
  iVar2 = piVar4[1];
  local_38 = 0;
  iVar6 = (piVar4[2] - iVar1) + 1 + param_3;
  local_3c = 0;
  iVar12 = (piVar4[3] - iVar2) + 1 + param_4;
  if ((((iVar12 <= W_y2) && (W_y1 < iVar2 + iVar12)) && (iVar6 <= W_x2)) && (W_x1 < iVar1 + iVar6))
  {
    local_34 = iVar12;
    if (iVar12 < W_y1) {
      local_34 = W_y1;
      local_38 = W_y1 - iVar12;
    }
    iVar12 = iVar2 + iVar12 + -1;
    if (W_y2 < iVar12) {
      iVar12 = W_y2;
    }
    iVar14 = iVar6;
    if (iVar6 < W_x1) {
      local_3c = W_x1 - iVar6;
      iVar14 = W_x1;
    }
    iVar6 = iVar1 + iVar6 + -1;
    if (W_x2 < iVar6) {
      iVar6 = W_x2;
    }
    iVar6 = (iVar6 - iVar14) + 1;
    iVar12 = (iVar12 - local_34) + 1;
    if (((0 < iVar6) && (0 < iVar12)) &&
       (iVar7 = SpriteDecompGetAndLockData(param_1,param_2), iVar7 != 0)) {
      iVar8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar9 = (int *)param_1[5];
      if (piVar9 == (int *)0x0) {
        piVar9 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar4[0xc]);
      }
      else {
        EBPalUpdate(piVar9);
      }
      if (0 < iVar12) {
        iVar3 = piVar4[0xb];
        iVar15 = 0;
        do {
          pbVar10 = (byte *)((iVar7 + *(int *)(iVar3 + -4 + ((iVar2 - local_38) - iVar15) * 4) +
                             iVar1) - local_3c);
          puVar11 = (undefined2 *)
                    (iVar8 + *(int *)(*(int *)(iVar5 + 0x2c) + (local_34 + iVar15) * 4) + iVar14 * 2
                    );
          (*(uint *)((char *)&GlobalTemp + 0)) = piVar9 + 0x17;
          for (iVar13 = iVar6; iVar13 != 0; iVar13 = iVar13 + -1) {
            pbVar10 = pbVar10 + -1;
            if (*pbVar10 != 0) {
              *puVar11 = *(undefined2 *)((int)(piVar9 + 0x17) + (uint)*pbVar10 * 2);
            }
            puVar11 = puVar11 + 1;
          }
          iVar15 = iVar15 + 1;
        } while (iVar15 < iVar12);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_ScaleSprite8to16 @ 0x0805d8b0, 2262 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 11 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSprite8to16(int *param_1,int param_2,float param_3,float param_4,float param_5,
                       float param_6)

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
  int *piVar11;
  undefined2 *puVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  byte *pbVar16;
  uint uVar17;
  int iVar18;
  int local_13c;
  int local_e8;
  int local_e4;
  int local_e0;
  uint local_dc;
  int local_d0;
  uint local_54;
  
  piVar5 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar6 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_e4 = 0;
  local_e8 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar1 = *piVar5;
    iVar8 = piVar5[1];
    if ((((double)0.001) <= ABS((float10)iVar1 - param_5)) || (((double)0.001) <= ABS((float10)iVar8 - param_6))) {
      fVar2 = param_3 - ((float10)piVar5[2] * param_5) / (float10)iVar1;
      fVar3 = param_4 - ((float10)piVar5[3] * param_6) / (float10)iVar8;
      if ((((fVar3 <= (float)W_y2) && ((float)W_y1 < (fVar3 + param_6) - 0.5)) &&
          (fVar2 <= (float)W_x2)) && ((float)W_x1 < (fVar2 + param_5) - 0.5)) {
        local_e0 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
        fVar4 = (float)local_e0;
        if (fVar3 <= fVar4) {
          local_dc = 0;
        }
        else {
          if ((float)local_e0 < fVar3 - 0.5) {
            local_e0 = local_e0 + 1;
            fVar4 = (float)local_e0;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar8 * (fVar4 - fVar3)) / param_6) * 65536.0);
          local_dc = local_54;
        }
        if (local_e0 < W_y1) {
          iVar7 = W_y1 - local_e0;
          local_e0 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar7 * iVar8) / param_6) * 65536.0);
          local_dc = local_dc + local_54;
        }
        iVar7 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_6) - 0.5));
        if (W_y2 < iVar7) {
          iVar7 = W_y2;
        }
        if (iVar7 - local_e0 != -1 && -1 < (iVar7 - local_e0) + 1) {
          iVar18 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar2));
          fVar3 = (float10)iVar18;
          if (fVar2 <= fVar3) {
            uVar17 = 0;
          }
          else {
            if ((float10)iVar18 < fVar2 - 0.5) {
              iVar18 = iVar18 + 1;
              fVar3 = (float10)iVar18;
            }
            local_54 = (uint)(longlong)ROUND((((fVar3 - fVar2) * (float10)iVar1) / param_5) * 65536.0)
            ;
            uVar17 = local_54;
          }
          if (fVar2 < (float)W_x1) {
            local_54 = (uint)(longlong)ROUND(((float)((W_x1 - iVar18) * iVar1) / param_5) * 65536.0)
            ;
            uVar17 = uVar17 + local_54;
            iVar18 = W_x1;
          }
          iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar2 + param_5) - 0.5));
          if (W_x2 < iVar9) {
            iVar9 = W_x2;
          }
          local_13c = (int)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
          iVar1 = (int)GHIDRA_FIST32((float)(iVar8 << 0x10) / param_6);
          for (; ((int)uVar17 < 0 && (iVar18 <= iVar9)); iVar18 = iVar18 + 1) {
            uVar17 = uVar17 + local_13c;
          }
          iVar8 = (int)uVar17 >> 0x10;
          if (iVar8 != 0) {
            uVar17 = uVar17 & 0xffff;
            local_e8 = iVar8;
          }
          for (; ((int)local_dc < 0 && (local_e0 <= iVar7)); local_e0 = local_e0 + 1) {
            local_dc = local_dc + iVar1;
          }
          iVar8 = (int)local_dc >> 0x10;
          if (iVar8 != 0) {
            local_dc = local_dc & 0xffff;
            local_e4 = iVar8;
          }
          iVar8 = (iVar9 - iVar18) + 1;
          iVar7 = (iVar7 - local_e0) + 1;
          if ((0 < iVar8) && (0 < iVar7)) {
            iVar9 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar9 != 0) {
              iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar11 = (int *)param_1[5];
              if (piVar11 == (int *)0x0) {
                piVar11 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar5[0xc]);
              }
              else {
                EBPalUpdate(piVar11);
              }
              local_d0 = 0;
              if (0 < iVar7) {
                do {
                  pbVar16 = (byte *)(local_e8 +
                                    iVar9 + *(int *)(piVar5[0xb] +
                                                    (((int)local_dc >> 0x10) + local_e4) * 4));
                  puVar12 = (undefined2 *)
                            (iVar10 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_e0 + local_d0) * 4) +
                            iVar18 * 2);
                  uVar15 = uVar17;
                  for (iVar13 = iVar8; iVar13 != 0; iVar13 = iVar13 + -1) {
                    if (*pbVar16 != 0) {
                      *puVar12 = *(undefined2 *)((int)piVar11 + (uint)*pbVar16 * 2 + 0x5c);
                    }
                    puVar12 = puVar12 + 1;
                    uVar14 = uVar15 + local_13c;
                    uVar15 = uVar14 & 0xffff;
                    pbVar16 = pbVar16 + (uVar14 >> 0x10);
                  }
                  local_dc = local_dc + iVar1;
                  local_d0 = local_d0 + 1;
                } while (local_d0 < iVar7);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSprite8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteFlat8to16 @ 0x0805e190, 2288 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteFlat8to16
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
  int *piVar11;
  uint uVar12;
  uint uVar13;
  undefined2 *puVar14;
  int iVar15;
  int iVar16;
  byte *pbVar17;
  int iVar18;
  int *local_138;
  int local_134;
  int local_e8;
  int local_e4;
  uint local_e0;
  uint local_dc;
  int local_d0;
  uint local_54;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_e4 = 0;
  local_e8 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar1 = *piVar6;
    iVar8 = piVar6[1];
    if ((((double)0.001) <= ABS((float10)iVar1 - param_5)) || (((double)0.001) <= ABS((float10)iVar8 - param_6))) {
      fVar3 = param_3 - ((float10)piVar6[2] * param_5) / (float10)iVar1;
      fVar4 = param_4 - ((float10)piVar6[3] * param_6) / (float10)iVar8;
      if ((((fVar4 <= (float)W_y2) && ((float)W_y1 < (fVar4 + param_6) - 0.5)) &&
          (fVar3 <= (float)W_x2)) && ((float)W_x1 < (fVar3 + param_5) - 0.5)) {
        iVar16 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
        fVar5 = (float10)iVar16;
        if (fVar4 <= fVar5) {
          local_dc = 0;
        }
        else {
          if ((float10)iVar16 < fVar4 - 0.5) {
            iVar16 = iVar16 + 1;
            fVar5 = (float10)iVar16;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar8 * (fVar5 - fVar4)) / param_6) * 65536.0);
          local_dc = local_54;
        }
        if (iVar16 < W_y1) {
          local_54 = (uint)(longlong)ROUND(((float)((W_y1 - iVar16) * iVar8) / param_6) * 65536.0);
          local_dc = local_dc + local_54;
          iVar16 = W_y1;
        }
        iVar18 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_6) - 0.5));
        if (W_y2 < iVar18) {
          iVar18 = W_y2;
        }
        if (iVar18 - iVar16 != -1 && -1 < (iVar18 - iVar16) + 1) {
          iVar15 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
          fVar4 = (float10)iVar15;
          if (fVar3 <= fVar4) {
            local_e0 = 0;
          }
          else {
            if ((float10)iVar15 < fVar3 - 0.5) {
              iVar15 = iVar15 + 1;
              fVar4 = (float10)iVar15;
            }
            local_54 = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar1) / param_5) * 65536.0)
            ;
            local_e0 = local_54;
          }
          if (fVar3 < (float)W_x1) {
            local_54 = (uint)(longlong)ROUND(((float)((W_x1 - iVar15) * iVar1) / param_5) * 65536.0)
            ;
            local_e0 = local_e0 + local_54;
            iVar15 = W_x1;
          }
          iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_5) - 0.5));
          if (W_x2 < iVar9) {
            iVar9 = W_x2;
          }
          local_134 = (int)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
          iVar1 = (int)GHIDRA_FIST32((float)(iVar8 << 0x10) / param_6);
          for (; ((int)local_e0 < 0 && (iVar15 <= iVar9)); iVar15 = iVar15 + 1) {
            local_e0 = local_e0 + local_134;
          }
          iVar8 = (int)local_e0 >> 0x10;
          if (iVar8 != 0) {
            local_e0 = local_e0 & 0xffff;
            local_e8 = iVar8;
          }
          for (; ((int)local_dc < 0 && (iVar16 <= iVar18)); iVar16 = iVar16 + 1) {
            local_dc = local_dc + iVar1;
          }
          iVar8 = (int)local_dc >> 0x10;
          if (iVar8 != 0) {
            local_dc = local_dc & 0xffff;
            local_e4 = iVar8;
          }
          iVar8 = (iVar9 - iVar15) + 1;
          iVar18 = (iVar18 - iVar16) + 1;
          if ((0 < iVar8) && (0 < iVar18)) {
            iVar9 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar9 != 0) {
              iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar11 = (int *)param_1[5];
              if (piVar11 == (int *)0x0) {
                piVar11 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
              }
              else {
                EBPalUpdate(piVar11);
              }
              local_d0 = 0;
              if (0 < iVar18) {
                iVar2 = piVar6[0xb];
                local_138 = (int *)(iVar16 * 4 + *(int *)(iVar7 + 0x2c));
                do {
                  pbVar17 = (byte *)(local_e8 +
                                    iVar9 + *(int *)(iVar2 + (((int)local_dc >> 0x10) + local_e4) *
                                                             4));
                  puVar14 = (undefined2 *)(iVar15 * 2 + iVar10 + *local_138);
                  uVar13 = local_e0;
                  for (iVar7 = iVar8; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *puVar14 = *(undefined2 *)((int)piVar11 + (uint)*pbVar17 * 2 + 0x5c);
                    puVar14 = puVar14 + 1;
                    uVar12 = uVar13 + local_134;
                    uVar13 = uVar12 & 0xffff;
                    pbVar17 = pbVar17 + (uVar12 >> 0x10);
                  }
                  local_d0 = local_d0 + 1;
                  local_138 = local_138 + 1;
                  local_dc = local_dc + iVar1;
                } while (local_d0 < iVar18);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteFlat8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteMirH8to16 @ 0x0805ea80, 2284 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 10 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteMirH8to16
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
  int *piVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  byte *pbVar17;
  uint uVar18;
  int iVar19;
  int local_13c;
  int local_e8;
  int local_e4;
  int local_e0;
  uint local_dc;
  int local_d0;
  uint local_54;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_e4 = 0;
  local_e8 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar1 = *piVar6;
    iVar2 = piVar6[1];
    if ((((double)0.001) <= ABS((float10)iVar1 - param_5)) || (((double)0.001) <= ABS((float10)iVar2 - param_6))) {
      fVar3 = param_3 - ((float)((iVar1 - piVar6[2]) + -1) * param_5) / (float10)iVar1;
      fVar4 = param_4 - ((float10)piVar6[3] * param_6) / (float10)iVar2;
      if ((((fVar4 <= (float)W_y2) && ((float)W_y1 < (fVar4 + param_6) - 0.5)) &&
          (fVar3 <= (float)W_x2)) && ((float)W_x1 < (fVar3 + param_5) - 0.5)) {
        local_e0 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
        fVar5 = (float)local_e0;
        if (fVar4 <= fVar5) {
          local_dc = 0;
        }
        else {
          if ((float)local_e0 < fVar4 - 0.5) {
            local_e0 = local_e0 + 1;
            fVar5 = (float)local_e0;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar2 * (fVar5 - fVar4)) / param_6) * 65536.0);
          local_dc = local_54;
        }
        if (local_e0 < W_y1) {
          iVar8 = W_y1 - local_e0;
          local_e0 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar8 * iVar2) / param_6) * 65536.0);
          local_dc = local_dc + local_54;
        }
        iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_6) - 0.5));
        if (W_y2 < iVar8) {
          iVar8 = W_y2;
        }
        if (iVar8 - local_e0 != -1 && -1 < (iVar8 - local_e0) + 1) {
          iVar19 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
          fVar4 = (float10)iVar19;
          if (fVar3 <= fVar4) {
            uVar18 = 0;
          }
          else {
            if ((float10)iVar19 < fVar3 - 0.5) {
              iVar19 = iVar19 + 1;
              fVar4 = (float10)iVar19;
            }
            local_54 = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar1) / param_5) * 65536.0)
            ;
            uVar18 = local_54;
          }
          if (fVar3 < (float)W_x1) {
            local_54 = (uint)(longlong)ROUND(((float)((W_x1 - iVar19) * iVar1) / param_5) * 65536.0)
            ;
            uVar18 = uVar18 + local_54;
            iVar19 = W_x1;
          }
          iVar13 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_5) - 0.5));
          if (W_x2 < iVar13) {
            iVar13 = W_x2;
          }
          local_13c = (int)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
          iVar2 = (int)GHIDRA_FIST32((float)(iVar2 << 0x10) / param_6);
          for (; ((int)uVar18 < 0 && (iVar19 <= iVar13)); iVar19 = iVar19 + 1) {
            uVar18 = uVar18 + local_13c;
          }
          iVar9 = (int)uVar18 >> 0x10;
          if (iVar9 != 0) {
            uVar18 = uVar18 & 0xffff;
            local_e8 = iVar9;
          }
          for (; ((int)local_dc < 0 && (local_e0 <= iVar8)); local_e0 = local_e0 + 1) {
            local_dc = local_dc + iVar2;
          }
          iVar9 = (int)local_dc >> 0x10;
          if (iVar9 != 0) {
            local_dc = local_dc & 0xffff;
            local_e4 = iVar9;
          }
          iVar13 = (iVar13 - iVar19) + 1;
          iVar8 = (iVar8 - local_e0) + 1;
          if ((0 < iVar13) && (0 < iVar8)) {
            iVar9 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar9 != 0) {
              iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar11 = (int *)param_1[5];
              if (piVar11 == (int *)0x0) {
                piVar11 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
              }
              else {
                EBPalUpdate(piVar11);
              }
              local_d0 = 0;
              if (0 < iVar8) {
                do {
                  pbVar17 = (byte *)(((iVar9 + *(int *)(piVar6[0xb] +
                                                       (((int)local_dc >> 0x10) + local_e4) * 4) +
                                      iVar1) - local_e8) + -1);
                  puVar12 = (undefined2 *)
                            (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_e0 + local_d0) * 4) +
                            iVar19 * 2);
                  uVar16 = uVar18;
                  for (iVar14 = iVar13; iVar14 != 0; iVar14 = iVar14 + -1) {
                    if (*pbVar17 != 0) {
                      *puVar12 = *(undefined2 *)((int)piVar11 + (uint)*pbVar17 * 2 + 0x5c);
                    }
                    puVar12 = puVar12 + 1;
                    uVar15 = uVar16 + local_13c;
                    uVar16 = uVar15 & 0xffff;
                    pbVar17 = pbVar17 + -(uVar15 >> 0x10);
                  }
                  local_d0 = local_d0 + 1;
                  local_dc = local_dc + iVar2;
                } while (local_d0 < iVar8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirH8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteMirV8to16 @ 0x0805f370, 2294 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 10 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteMirV8to16
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
  int *piVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  byte *pbVar17;
  uint uVar18;
  int iVar19;
  int local_13c;
  int local_e8;
  int local_e4;
  int local_e0;
  uint local_dc;
  int local_d0;
  uint local_54;
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_e4 = 0;
  local_e8 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar1 = *piVar6;
    iVar2 = piVar6[1];
    if ((((double)0.001) <= ABS((float10)iVar1 - param_5)) || (((double)0.001) <= ABS((float10)iVar2 - param_6))) {
      fVar3 = param_3 - ((float10)piVar6[2] * param_5) / (float10)iVar1;
      fVar4 = param_4 - ((float)((iVar2 - piVar6[3]) + -1) * param_6) / (float10)iVar2;
      if ((((fVar4 <= (float)W_y2) && ((float)W_y1 < (fVar4 + param_6) - 0.5)) &&
          (fVar3 <= (float)W_x2)) && ((float)W_x1 < (fVar3 + param_5) - 0.5)) {
        local_e0 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
        fVar5 = (float)local_e0;
        if (fVar4 <= fVar5) {
          local_dc = 0;
        }
        else {
          if ((float)local_e0 < fVar4 - 0.5) {
            local_e0 = local_e0 + 1;
            fVar5 = (float)local_e0;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar2 * (fVar5 - fVar4)) / param_6) * 65536.0);
          local_dc = local_54;
        }
        if (local_e0 < W_y1) {
          iVar8 = W_y1 - local_e0;
          local_e0 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar8 * iVar2) / param_6) * 65536.0);
          local_dc = local_dc + local_54;
        }
        iVar8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_6) - 0.5));
        if (W_y2 < iVar8) {
          iVar8 = W_y2;
        }
        if (iVar8 - local_e0 != -1 && -1 < (iVar8 - local_e0) + 1) {
          iVar19 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar3));
          fVar4 = (float10)iVar19;
          if (fVar3 <= fVar4) {
            uVar18 = 0;
          }
          else {
            if ((float10)iVar19 < fVar3 - 0.5) {
              iVar19 = iVar19 + 1;
              fVar4 = (float10)iVar19;
            }
            local_54 = (uint)(longlong)ROUND((((fVar4 - fVar3) * (float10)iVar1) / param_5) * 65536.0)
            ;
            uVar18 = local_54;
          }
          if (fVar3 < (float)W_x1) {
            local_54 = (uint)(longlong)ROUND(((float)((W_x1 - iVar19) * iVar1) / param_5) * 65536.0)
            ;
            uVar18 = uVar18 + local_54;
            iVar19 = W_x1;
          }
          iVar13 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar3 + param_5) - 0.5));
          if (W_x2 < iVar13) {
            iVar13 = W_x2;
          }
          local_13c = (int)(longlong)ROUND((float)(iVar1 << 0x10) / param_5);
          iVar1 = (int)GHIDRA_FIST32((float)(iVar2 << 0x10) / param_6);
          for (; ((int)uVar18 < 0 && (iVar19 <= iVar13)); iVar19 = iVar19 + 1) {
            uVar18 = uVar18 + local_13c;
          }
          iVar9 = (int)uVar18 >> 0x10;
          if (iVar9 != 0) {
            uVar18 = uVar18 & 0xffff;
            local_e8 = iVar9;
          }
          for (; ((int)local_dc < 0 && (local_e0 <= iVar8)); local_e0 = local_e0 + 1) {
            local_dc = local_dc + iVar1;
          }
          iVar9 = (int)local_dc >> 0x10;
          if (iVar9 != 0) {
            local_dc = local_dc & 0xffff;
            local_e4 = iVar9;
          }
          iVar13 = (iVar13 - iVar19) + 1;
          iVar8 = (iVar8 - local_e0) + 1;
          if ((0 < iVar13) && (0 < iVar8)) {
            iVar9 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar9 != 0) {
              iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar11 = (int *)param_1[5];
              if (piVar11 == (int *)0x0) {
                piVar11 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
              }
              else {
                EBPalUpdate(piVar11);
              }
              local_d0 = 0;
              if (0 < iVar8) {
                do {
                  pbVar17 = (byte *)(local_e8 +
                                    iVar9 + *(int *)(piVar6[0xb] + -4 +
                                                    ((iVar2 - local_e4) - ((int)local_dc >> 0x10)) *
                                                    4));
                  puVar12 = (undefined2 *)
                            (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_e0 + local_d0) * 4) +
                            iVar19 * 2);
                  uVar16 = uVar18;
                  for (iVar14 = iVar13; iVar14 != 0; iVar14 = iVar14 + -1) {
                    if (*pbVar17 != 0) {
                      *puVar12 = *(undefined2 *)((int)piVar11 + (uint)*pbVar17 * 2 + 0x5c);
                    }
                    puVar12 = puVar12 + 1;
                    uVar15 = uVar16 + local_13c;
                    uVar16 = uVar15 & 0xffff;
                    pbVar17 = pbVar17 + (uVar15 >> 0x10);
                  }
                  local_d0 = local_d0 + 1;
                  local_dc = local_dc + iVar1;
                } while (local_d0 < iVar8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteMirHV8to16 @ 0x0805fc70, 2301 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 9 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteMirHV8to16
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
  int *piVar12;
  undefined2 *puVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  byte *pbVar18;
  uint uVar19;
  int iVar20;
  int local_13c;
  int local_e8;
  int local_e4;
  int local_e0;
  uint local_dc;
  int local_d0;
  uint local_54;
  
  piVar7 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_e4 = 0;
  local_e8 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar2 = *piVar7;
    iVar3 = piVar7[1];
    if ((((double)0.001) <= ABS((float10)iVar2 - param_5)) || (((double)0.001) <= ABS((float10)iVar3 - param_6))) {
      fVar4 = param_3 - ((float)((iVar2 - piVar7[2]) + -1) * param_5) / (float10)iVar2;
      fVar5 = param_4 - ((float)((iVar3 - piVar7[3]) + -1) * param_6) / (float10)iVar3;
      if ((((fVar5 <= (float)W_y2) && ((float)W_y1 < (fVar5 + param_6) - 0.5)) &&
          (fVar4 <= (float)W_x2)) && ((float)W_x1 < (fVar4 + param_5) - 0.5)) {
        local_e0 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar6 = (float)local_e0;
        if (fVar5 <= fVar6) {
          local_dc = 0;
        }
        else {
          if ((float)local_e0 < fVar5 - 0.5) {
            local_e0 = local_e0 + 1;
            fVar6 = (float)local_e0;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar3 * (fVar6 - fVar5)) / param_6) * 65536.0);
          local_dc = local_54;
        }
        if (local_e0 < W_y1) {
          iVar9 = W_y1 - local_e0;
          local_e0 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar9 * iVar3) / param_6) * 65536.0);
          local_dc = local_dc + local_54;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_6) - 0.5));
        if (W_y2 < iVar9) {
          iVar9 = W_y2;
        }
        if (iVar9 - local_e0 != -1 && -1 < (iVar9 - local_e0) + 1) {
          iVar20 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
          fVar5 = (float10)iVar20;
          if (fVar4 <= fVar5) {
            uVar19 = 0;
          }
          else {
            if ((float10)iVar20 < fVar4 - 0.5) {
              iVar20 = iVar20 + 1;
              fVar5 = (float10)iVar20;
            }
            local_54 = (uint)(longlong)ROUND((((fVar5 - fVar4) * (float10)iVar2) / param_5) * 65536.0)
            ;
            uVar19 = local_54;
          }
          if (fVar4 < (float)W_x1) {
            local_54 = (uint)(longlong)ROUND(((float)((W_x1 - iVar20) * iVar2) / param_5) * 65536.0)
            ;
            uVar19 = uVar19 + local_54;
            iVar20 = W_x1;
          }
          iVar14 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_5) - 0.5));
          if (W_x2 < iVar14) {
            iVar14 = W_x2;
          }
          local_13c = (int)(longlong)ROUND((float)(iVar2 << 0x10) / param_5);
          iVar1 = (int)GHIDRA_FIST32((float)(iVar3 << 0x10) / param_6);
          for (; ((int)uVar19 < 0 && (iVar20 <= iVar14)); iVar20 = iVar20 + 1) {
            uVar19 = uVar19 + local_13c;
          }
          iVar10 = (int)uVar19 >> 0x10;
          if (iVar10 != 0) {
            uVar19 = uVar19 & 0xffff;
            local_e8 = iVar10;
          }
          for (; ((int)local_dc < 0 && (local_e0 <= iVar9)); local_e0 = local_e0 + 1) {
            local_dc = local_dc + iVar1;
          }
          iVar10 = (int)local_dc >> 0x10;
          if (iVar10 != 0) {
            local_dc = local_dc & 0xffff;
            local_e4 = iVar10;
          }
          iVar14 = (iVar14 - iVar20) + 1;
          iVar9 = (iVar9 - local_e0) + 1;
          if ((0 < iVar14) && (0 < iVar9)) {
            iVar10 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar10 != 0) {
              iVar11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar12 = (int *)param_1[5];
              if (piVar12 == (int *)0x0) {
                piVar12 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar7[0xc]);
              }
              else {
                EBPalUpdate(piVar12);
              }
              local_d0 = 0;
              if (0 < iVar9) {
                do {
                  pbVar18 = (byte *)(((iVar10 + *(int *)(piVar7[0xb] + -4 +
                                                        ((iVar3 - local_e4) -
                                                        ((int)local_dc >> 0x10)) * 4) + iVar2) -
                                     local_e8) + -1);
                  puVar13 = (undefined2 *)
                            (iVar11 + *(int *)(*(int *)(iVar8 + 0x2c) + (local_e0 + local_d0) * 4) +
                            iVar20 * 2);
                  uVar17 = uVar19;
                  for (iVar15 = iVar14; iVar15 != 0; iVar15 = iVar15 + -1) {
                    if (*pbVar18 != 0) {
                      *puVar13 = *(undefined2 *)((int)piVar12 + (uint)*pbVar18 * 2 + 0x5c);
                    }
                    puVar13 = puVar13 + 1;
                    uVar16 = uVar17 + local_13c;
                    uVar17 = uVar16 & 0xffff;
                    pbVar18 = pbVar18 + -(uVar16 >> 0x10);
                  }
                  local_d0 = local_d0 + 1;
                  local_dc = local_dc + iVar1;
                } while (local_d0 < iVar9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirHV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_RotateSprite8to16_P @ 0x08060570, 3728 bytes
 * FIXUP: rewrote 2 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 0 calls, 5 returns
 * FIXUP: frame emulation: 13 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4
W_RotateSprite8to16_P
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
  int iVar9;
  ulonglong uVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  int *piVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  undefined4 uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int *piVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
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
#define local_38 (*(undefined2 **)(ghidra_frame + 0x58))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x70))
  
  piVar19 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar20 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar4 = piVar19[0xb];
  iVar21 = roundfloat(param_3);
  iVar22 = roundfloat(param_4);
  iVar33 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar33 < 0) {
    iVar33 = -iVar33;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar35 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar35 < 0) {
    iVar35 = -iVar35;
    param_5 = param_5 + 180.0;
  }
  if (iVar33 == 0) {
    return GHIDRA_I2F(local_20);
  }
  if (iVar35 == 0) {
    return GHIDRA_I2F(local_20);
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar10 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar30 = (int)uVar10;
  if (iVar30 == 0) {
LAB_08060862:
    uVar23 = W_ScaleSprite_S(param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return GHIDRA_I2F(uVar23);
  }
  if (iVar30 == 0x5a0) {
    param_7 = -param_7;
    param_6 = -param_6;
    goto LAB_08060862;
  }
  iVar5 = *piVar19;
  iVar6 = piVar19[1];
  iVar7 = piVar19[2];
  iVar8 = piVar19[3];
  fVar11 = (float)SinTable[(iVar30 + 0x2d0) % 0xb40];
  fVar12 = fVar11 * 0.0009765625;
  fVar14 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar30 >> 0x1f) << 0x20 | uVar10 & 0xffffffff) %
                                0xb40)];
  fVar13 = fVar14 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar30 + 0x2d0) % 0xb40] << 0x10) / iVar33) / param_8);
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar2 = (int)GHIDRA_FIST32((float)((SinTable[(int)((longlong)
                                             ((ulonglong)(uint)(iVar30 >> 0x1f) << 0x20 |
                                             uVar10 & 0xffffffff) % 0xb40)] << 0x10) / iVar35) /
                     param_8);
  if (iVar30 < 0x2d0) {
    iVar30 = -iVar7;
    iVar24 = -iVar8;
    iVar25 = (iVar5 - iVar7) + -1;
    iVar26 = (iVar6 - iVar8) + -1;
LAB_08060aaf:
    fVar15 = (float10)iVar30;
    fVar16 = (float10)iVar25;
    local_84 = (float10)iVar24;
    local_8c = (float10)iVar26;
    local_88 = local_8c;
    fVar18 = fVar15;
  }
  else {
    if (iVar30 < 0x5a0) {
      iVar25 = (iVar5 - iVar7) + -1;
      iVar24 = -iVar8;
      iVar30 = (iVar6 - iVar8) + -1;
      iVar26 = -iVar7;
    }
    else {
      if (iVar30 < 0x870) {
        iVar30 = (iVar5 - iVar7) + -1;
        iVar24 = (iVar6 - iVar8) + -1;
        iVar25 = -iVar7;
        iVar26 = -iVar8;
        goto LAB_08060aaf;
      }
      if (0xb3f < iVar30) {
        return GHIDRA_I2F(local_20);
      }
      iVar25 = -iVar7;
      iVar24 = (iVar6 - iVar8) + -1;
      iVar30 = -iVar8;
      iVar26 = (iVar5 - iVar7) + -1;
    }
    fVar15 = (float10)iVar25;
    local_88 = (float10)iVar30;
    fVar16 = (float10)iVar26;
    local_8c = (float10)iVar24;
    local_84 = local_88;
    fVar18 = fVar16;
  }
  local_80 = (float10)iVar25;
  local_88 = local_88 * param_7;
  fVar15 = fVar15 * param_6;
  fVar17 = (float10)iVar24 * param_7;
  fVar16 = fVar16 * param_6;
  iVar30 = roundfloat((-fVar15 * fVar13 + fVar17 * fVar12) * param_9);
  iVar25 = roundfloat((-fVar16 * fVar13 + local_88 * fVar12) * param_9);
  local_50 = roundfloat((-(local_80 * param_6) * fVar13 + local_84 * param_7 * fVar12) * param_9);
  local_90 = roundfloat((-(fVar18 * param_6) * fVar13 + local_8c * param_7 * fVar12) * param_9);
  if ((local_50 == iVar30) || (local_50 == iVar25)) {
    local_74 = 0;
    local_70 = 0;
    local_60 = (int)GHIDRA_FIST32((fVar15 * fVar12 + fVar17 * fVar13) * 65536.0 * param_8);
    local_64 = (int)GHIDRA_FIST32((fVar16 * fVar12 + local_88 * fVar13) * 65536.0 * param_8);
  }
  else {
    fVar18 = fVar12 * local_80 * param_6 + local_84 * param_7 * fVar13;
    local_70 = (int)GHIDRA_FIST32(((fVar18 - (fVar15 * fVar12 + fVar17 * fVar13)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar30));
    if (local_70 < 0) {
      local_70 = -local_70;
    }
    local_74 = (int)GHIDRA_FIST32((((local_88 * fVar13 + fVar16 * fVar12) - fVar18) * 65536.0 * param_8) /
                          (float)(local_50 - iVar25));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_64 = (int)GHIDRA_FIST32(fVar18 * 65536.0 * param_8);
    local_60 = local_64;
  }
  for (; local_50 < W_y1 - iVar22; local_50 = local_50 + 1) {
    iVar24 = local_74;
    if (local_50 < iVar30) {
      iVar24 = -local_70;
    }
    local_60 = local_60 + iVar24;
    iVar24 = local_74;
    if (iVar25 <= local_50) {
      iVar24 = -local_70;
    }
    local_64 = local_64 + iVar24;
  }
  if (W_y2 - iVar22 < local_90) {
    local_90 = W_y2 - iVar22;
  }
  iVar24 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar24 == 0) {
    return 0;
  }
  iVar26 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar27 = (int *)param_1[5];
  if (piVar27 == (int *)0x0) {
    piVar27 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar19[0xc]);
  }
  else {
    EBPalUpdate(piVar27);
  }
  if (local_50 <= local_90) {
    iVar28 = W_x1 - iVar21;
    do {
      iVar32 = local_60 >> 0x10;
      if (local_60 >> 0x10 < iVar28) {
        iVar32 = iVar28;
      }
      iVar36 = local_64 >> 0x10;
      if (W_x2 - iVar21 < local_64 >> 0x10) {
        iVar36 = W_x2 - iVar21;
      }
      local_5c = (int)GHIDRA_FIST32(((((float10)iVar32 / param_8) * fVar11 -
                             ((float)local_50 / param_9) * fVar14) * 65536.0) / (float10)iVar33) +
                 iVar7 * 0x10000;
      iVar34 = iVar8 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar32 / param_8) * fVar14 +
                           ((float)local_50 / param_9) * fVar11) * 65536.0) / (float10)iVar35);
      local_38 = (undefined2 *)
                 (iVar26 + *(int *)(*(int *)(iVar20 + 0x2c) + (local_50 + iVar22) * 4) +
                 (iVar21 + iVar32) * 2);
      iVar31 = (iVar36 - iVar32) + 1;
      iVar9 = iVar36 - iVar32;
      iVar29 = iVar2 * iVar31 + iVar34;
      for (iVar31 = local_5c + iVar1 * iVar31;
          (SBORROW4(iVar36,iVar32) == iVar9 < 0 &&
          ((((iVar6 <= iVar29 >> 0x10 || (iVar5 <= iVar31 >> 0x10)) || (iVar29 >> 0x10 < 0)) ||
           (iVar31 >> 0x10 < 0)))); iVar31 = iVar31 - iVar1) {
        iVar36 = iVar36 + -1;
        iVar29 = iVar29 - iVar2;
        iVar9 = iVar36 - iVar32;
      }
      for (; (iVar32 <= iVar36 &&
             (((iVar6 <= iVar34 >> 0x10 || (iVar5 <= local_5c >> 0x10)) ||
              ((iVar34 >> 0x10 < 0 || (local_5c >> 0x10 < 0)))))); local_5c = local_5c + iVar1) {
        local_38 = local_38 + 1;
        iVar32 = iVar32 + 1;
        iVar34 = iVar34 + iVar2;
      }
      iVar32 = (iVar36 - iVar32) + 1;
      if (0 < iVar32) {
        do {
          bVar3 = *(byte *)((local_5c >> 0x10) + iVar24 + *(int *)(iVar4 + (iVar34 >> 0x10) * 4));
          if (bVar3 != 0) {
            *local_38 = *(undefined2 *)((int)piVar27 + (uint)bVar3 * 2 + 0x5c);
          }
          local_5c = local_5c + iVar1;
          local_38 = local_38 + 1;
          iVar34 = iVar34 + iVar2;
          iVar32 = iVar32 + -1;
        } while (iVar32 != 0);
      }
      iVar32 = local_74;
      if (local_50 < iVar30) {
        iVar32 = -local_70;
      }
      local_60 = local_60 + iVar32;
      iVar32 = local_74;
      if (iVar25 <= local_50) {
        iVar32 = -local_70;
      }
      local_64 = local_64 + iVar32;
      local_50 = local_50 + 1;
    } while (local_50 <= local_90);
  }
  uVar23 = SpriteDecompUnlockData();
  return GHIDRA_I2F(uVar23);
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

/* W_RotateSpriteMirH8to16_P @ 0x08061400, 3664 bytes
 * FIXUP: rewrote 2 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 0 calls, 5 returns
 * FIXUP: frame emulation: 13 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4
W_RotateSpriteMirH8to16_P
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
  int iVar9;
  ulonglong uVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  int *piVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  undefined4 uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int *piVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
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
#define local_38 (*(undefined2 **)(ghidra_frame + 0x58))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x70))
  
  piVar19 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar20 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar4 = piVar19[0xb];
  iVar21 = roundfloat(param_3);
  iVar22 = roundfloat(param_4);
  iVar31 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar31 < 0) {
    iVar31 = -iVar31;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar34 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar34 < 0) {
    iVar34 = -iVar34;
    param_5 = param_5 + 180.0;
  }
  if (iVar31 == 0) {
    return GHIDRA_I2F(local_20);
  }
  if (iVar34 == 0) {
    return GHIDRA_I2F(local_20);
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar10 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar29 = (int)uVar10;
  if (iVar29 == 0) {
    param_6 = -param_6;
LAB_080616ed:
    uVar23 = W_ScaleSprite_S(param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return GHIDRA_I2F(uVar23);
  }
  if (iVar29 == 0x5a0) {
    param_7 = -param_7;
    goto LAB_080616ed;
  }
  iVar5 = *piVar19;
  iVar6 = piVar19[1];
  iVar7 = piVar19[2];
  iVar8 = piVar19[3];
  fVar11 = (float)SinTable[(iVar29 + 0x2d0) % 0xb40];
  fVar12 = fVar11 * 0.0009765625;
  fVar14 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar29 >> 0x1f) << 0x20 | uVar10 & 0xffffffff) %
                                0xb40)];
  fVar13 = fVar14 * 0.0009765625;
  iVar1 = (int)GHIDRA_FIST32((float)((SinTable[(iVar29 + 0x2d0) % 0xb40] << 0x10) / iVar31) / param_8);
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar2 = (int)GHIDRA_FIST32((float)((SinTable[(int)((longlong)
                                             ((ulonglong)(uint)(iVar29 >> 0x1f) << 0x20 |
                                             uVar10 & 0xffffffff) % 0xb40)] << 0x10) / iVar34) /
                     param_8);
  if (iVar29 < 0x2d0) {
    iVar29 = -iVar7;
    iVar24 = -iVar8;
    iVar25 = (iVar5 - iVar7) + -1;
    iVar26 = (iVar6 - iVar8) + -1;
LAB_0806193f:
    fVar15 = (float10)iVar29;
    fVar16 = (float10)iVar25;
    local_84 = (float10)iVar24;
    local_8c = (float10)iVar26;
    local_88 = local_8c;
    fVar18 = fVar15;
  }
  else {
    if (iVar29 < 0x5a0) {
      iVar25 = (iVar5 - iVar7) + -1;
      iVar24 = -iVar8;
      iVar29 = (iVar6 - iVar8) + -1;
      iVar26 = -iVar7;
    }
    else {
      if (iVar29 < 0x870) {
        iVar29 = (iVar5 - iVar7) + -1;
        iVar24 = (iVar6 - iVar8) + -1;
        iVar25 = -iVar7;
        iVar26 = -iVar8;
        goto LAB_0806193f;
      }
      if (0xb3f < iVar29) {
        return GHIDRA_I2F(local_20);
      }
      iVar25 = -iVar7;
      iVar24 = (iVar6 - iVar8) + -1;
      iVar29 = -iVar8;
      iVar26 = (iVar5 - iVar7) + -1;
    }
    fVar15 = (float10)iVar25;
    local_88 = (float10)iVar29;
    fVar16 = (float10)iVar26;
    local_8c = (float10)iVar24;
    local_84 = local_88;
    fVar18 = fVar16;
  }
  local_80 = (float10)iVar25;
  local_88 = local_88 * param_7;
  fVar15 = fVar15 * param_6;
  fVar17 = (float10)iVar24 * param_7;
  fVar16 = fVar16 * param_6;
  iVar29 = roundfloat((-fVar15 * fVar13 + fVar17 * fVar12) * param_9);
  iVar24 = roundfloat((-fVar16 * fVar13 + local_88 * fVar12) * param_9);
  local_50 = roundfloat((-(local_80 * param_6) * fVar13 + local_84 * param_7 * fVar12) * param_9);
  local_90 = roundfloat((-(fVar18 * param_6) * fVar13 + local_8c * param_7 * fVar12) * param_9);
  if ((local_50 == iVar29) || (local_50 == iVar24)) {
    local_74 = 0;
    local_70 = 0;
    local_60 = (int)GHIDRA_FIST32((fVar15 * fVar12 + fVar17 * fVar13) * 65536.0 * param_8);
    local_64 = (int)GHIDRA_FIST32((fVar16 * fVar12 + local_88 * fVar13) * 65536.0 * param_8);
  }
  else {
    fVar18 = fVar12 * local_80 * param_6 + local_84 * param_7 * fVar13;
    local_70 = (int)GHIDRA_FIST32(((fVar18 - (fVar15 * fVar12 + fVar17 * fVar13)) * 65536.0 * param_8) /
                          (float)(local_50 - iVar29));
    if (local_70 < 0) {
      local_70 = -local_70;
    }
    local_74 = (int)GHIDRA_FIST32((((local_88 * fVar13 + fVar16 * fVar12) - fVar18) * 65536.0 * param_8) /
                          (float)(local_50 - iVar24));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_64 = (int)GHIDRA_FIST32(fVar18 * 65536.0 * param_8);
    local_60 = local_64;
  }
  for (; local_50 < W_y1 - iVar22; local_50 = local_50 + 1) {
    iVar25 = local_74;
    if (local_50 < iVar29) {
      iVar25 = -local_70;
    }
    local_60 = local_60 + iVar25;
    iVar25 = local_74;
    if (iVar24 <= local_50) {
      iVar25 = -local_70;
    }
    local_64 = local_64 + iVar25;
  }
  if (W_y2 - iVar22 < local_90) {
    local_90 = W_y2 - iVar22;
  }
  iVar25 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar25 == 0) {
    return 0;
  }
  iVar26 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar27 = (int *)param_1[5];
  if (piVar27 == (int *)0x0) {
    piVar27 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar19[0xc]);
  }
  else {
    EBPalUpdate(piVar27);
  }
  if (local_50 <= local_90) {
    do {
      iVar33 = local_60 >> 0x10;
      iVar35 = local_64 >> 0x10;
      if (W_x2 < iVar21 - iVar33) {
        iVar33 = iVar21 - W_x2;
      }
      if (iVar21 - iVar35 < W_x1) {
        iVar35 = iVar21 - W_x1;
      }
      local_5c = (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar11 -
                             ((float)local_50 / param_9) * fVar14) * 65536.0) / (float10)iVar31) +
                 iVar7 * 0x10000;
      iVar32 = iVar8 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar33 / param_8) * fVar14 +
                           ((float)local_50 / param_9) * fVar11) * 65536.0) / (float10)iVar34);
      local_38 = (undefined2 *)
                 (iVar26 + *(int *)(*(int *)(iVar20 + 0x2c) + (local_50 + iVar22) * 4) +
                 (iVar21 - iVar33) * 2);
      iVar30 = (iVar35 - iVar33) + 1;
      iVar9 = iVar35 - iVar33;
      iVar28 = iVar2 * iVar30 + iVar32;
      for (iVar30 = local_5c + iVar1 * iVar30;
          (SBORROW4(iVar35,iVar33) == iVar9 < 0 &&
          ((((iVar6 <= iVar28 >> 0x10 || (iVar5 <= iVar30 >> 0x10)) || (iVar28 >> 0x10 < 0)) ||
           (iVar30 >> 0x10 < 0)))); iVar30 = iVar30 - iVar1) {
        iVar35 = iVar35 + -1;
        iVar28 = iVar28 - iVar2;
        iVar9 = iVar35 - iVar33;
      }
      for (; (iVar33 <= iVar35 &&
             (((iVar6 <= iVar32 >> 0x10 || (iVar5 <= local_5c >> 0x10)) ||
              ((iVar32 >> 0x10 < 0 || (local_5c >> 0x10 < 0)))))); local_5c = local_5c + iVar1) {
        local_38 = local_38 + -1;
        iVar33 = iVar33 + 1;
        iVar32 = iVar32 + iVar2;
      }
      iVar33 = (iVar35 - iVar33) + 1;
      if (0 < iVar33) {
        do {
          bVar3 = *(byte *)((local_5c >> 0x10) + iVar25 + *(int *)(iVar4 + (iVar32 >> 0x10) * 4));
          if (bVar3 != 0) {
            *local_38 = *(undefined2 *)((int)piVar27 + (uint)bVar3 * 2 + 0x5c);
          }
          local_5c = local_5c + iVar1;
          local_38 = local_38 + -1;
          iVar32 = iVar32 + iVar2;
          iVar33 = iVar33 + -1;
        } while (iVar33 != 0);
      }
      iVar33 = local_74;
      if (local_50 < iVar29) {
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
  uVar23 = SpriteDecompUnlockData();
  return GHIDRA_I2F(uVar23);
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

/* W_PutSpriteShadow8to16 @ 0x08062250, 477 bytes */
void W_PutSpriteShadow8to16(int *param_1,int param_2,int param_3,int param_4,undefined2 param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int local_38;
  int local_34;
  int local_30;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_34 = 0;
  iVar7 = param_4 - piVar1[3];
  local_38 = 0;
  iVar9 = param_3 - piVar1[2];
  if ((((iVar7 <= W_y2) && (W_y1 < piVar1[1] + iVar7)) && (iVar9 <= W_x2)) &&
     (W_x1 < *piVar1 + iVar9)) {
    local_30 = iVar7;
    if (iVar7 < W_y1) {
      local_30 = W_y1;
      local_34 = W_y1 - iVar7;
    }
    iVar7 = piVar1[1] + iVar7 + -1;
    if (W_y2 < iVar7) {
      iVar7 = W_y2;
    }
    iVar8 = iVar9;
    if (iVar9 < W_x1) {
      local_38 = W_x1 - iVar9;
      iVar8 = W_x1;
    }
    iVar9 = *piVar1 + iVar9 + -1;
    if (W_x2 < iVar9) {
      iVar9 = W_x2;
    }
    iVar9 = (iVar9 - iVar8) + 1;
    iVar7 = (iVar7 - local_30) + 1;
    if (((0 < iVar9) && (0 < iVar7)) &&
       (iVar3 = SpriteDecompGetAndLockData(param_1,param_2), iVar3 != 0)) {
      iVar4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      if (0 < iVar7) {
        piVar10 = (int *)(local_30 * 4 + *(int *)(iVar2 + 0x2c));
        piVar1 = (int *)(local_34 * 4 + piVar1[0xb]);
        do {
          pcVar6 = (char *)(local_38 + iVar3 + *piVar1);
          puVar5 = (undefined2 *)(iVar4 + *piVar10 + iVar8 * 2);
          for (iVar2 = iVar9; iVar2 != 0; iVar2 = iVar2 + -1) {
            if (*pcVar6 != '\0') {
              *puVar5 = param_5;
            }
            puVar5 = puVar5 + 1;
            pcVar6 = pcVar6 + 1;
          }
          piVar10 = piVar10 + 1;
          piVar1 = piVar1 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteShadow16 @ 0x08062430, 1 bytes */
void W_PutSpriteShadow16(void)

{
  return;
}

