/*
 * spr16add.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08062440-0x0807205d, 20 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* W_PutSpriteTransAdd8to16 @ 0x08062440, 712 bytes */
void W_PutSpriteTransAdd8to16(int *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  byte *pbVar8;
  uint uVar9;
  ushort uVar10;
  ushort uVar11;
  int iVar13;
  int iVar14;
  uint *puVar15;
  uint uVar16;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_34;
  uint uVar12;
  
  piVar3 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar4 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_44 = 0;
  iVar13 = param_4 - piVar3[3];
  local_4c = 0;
  iVar14 = param_3 - piVar3[2];
  if ((((iVar13 <= W_y2) && (W_y1 < piVar3[1] + iVar13)) && (iVar14 <= W_x2)) &&
     (W_x1 < *piVar3 + iVar14)) {
    local_40 = iVar13;
    if (iVar13 < W_y1) {
      local_40 = W_y1;
      local_44 = W_y1 - iVar13;
    }
    iVar13 = piVar3[1] + iVar13 + -1;
    if (W_y2 < iVar13) {
      iVar13 = W_y2;
    }
    local_48 = iVar14;
    if (iVar14 < W_x1) {
      local_48 = W_x1;
      local_4c = W_x1 - iVar14;
    }
    iVar14 = *piVar3 + iVar14 + -1;
    if (W_x2 < iVar14) {
      iVar14 = W_x2;
    }
    iVar14 = (iVar14 - local_48) + 1;
    iVar13 = (iVar13 - local_40) + 1;
    if (((0 < iVar14) && (0 < iVar13)) &&
       (iVar5 = SpriteDecompGetAndLockData(param_1,param_2), iVar5 != 0)) {
      iVar6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar7 = (int *)param_1[5];
      if (piVar7 == (int *)0x0) {
        piVar7 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar3[0xc]);
      }
      else {
        EBPalUpdate(piVar7);
      }
      local_34 = 0;
      if (0 < iVar13) {
        do {
          pbVar8 = (byte *)(iVar5 + *(int *)(piVar3[0xb] + (local_44 + local_34) * 4) + local_4c);
          puVar15 = (uint *)(iVar6 + *(int *)(*(int *)(iVar4 + 0x2c) + (local_40 + local_34) * 4) +
                            local_48 * 2);
          for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
            if (*pbVar8 != 0) {
              uVar9 = (uint)*(ushort *)((int)piVar7 + (uint)*pbVar8 * 2 + 0x5c);
              uVar12 = *puVar15;
              uVar16 = (uVar12 & 0xf800) + (uVar9 & 0xf800);
              if (0xf800 < uVar16) {
                uVar16 = 0xf800;
              }
              uVar1 = (uVar12 & 0x7e0) + (uVar9 & 0x7e0);
              uVar10 = (ushort)uVar1;
              if (0x7e0 < uVar1) {
                uVar10 = 0x7e0;
              }
              uVar12 = (uVar9 & 0x1f) + (uVar12 & 0x1f);
              uVar11 = (ushort)uVar12;
              if (0x1f < uVar12) {
                uVar11 = 0x1f;
              }
              *(ushort *)puVar15 = (ushort)uVar16 | uVar10 | uVar11;
            }
            puVar15 = (uint *)((int)puVar15 + 2);
            pbVar8 = pbVar8 + 1;
          }
          local_34 = local_34 + 1;
        } while (local_34 < iVar13);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirH8to16 @ 0x08062710, 735 bytes */
void W_PutSpriteTransAddMirH8to16(int *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  ushort uVar11;
  ushort uVar12;
  int iVar14;
  uint *puVar15;
  uint uVar16;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_34;
  byte *local_2c;
  uint uVar13;
  
  piVar4 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar5 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar3 = *piVar4;
  local_44 = 0;
  iVar6 = (piVar4[2] - iVar3) + 1 + param_3;
  iVar14 = param_4 - piVar4[3];
  local_4c = 0;
  if ((((iVar14 <= W_y2) && (W_y1 < piVar4[1] + iVar14)) && (iVar6 <= W_x2)) &&
     (W_x1 < iVar3 + iVar6)) {
    local_40 = iVar14;
    if (iVar14 < W_y1) {
      local_40 = W_y1;
      local_44 = W_y1 - iVar14;
    }
    iVar14 = piVar4[1] + iVar14 + -1;
    if (W_y2 < iVar14) {
      iVar14 = W_y2;
    }
    local_48 = iVar6;
    if (iVar6 < W_x1) {
      local_48 = W_x1;
      local_4c = W_x1 - iVar6;
    }
    iVar6 = iVar3 + iVar6 + -1;
    if (W_x2 < iVar6) {
      iVar6 = W_x2;
    }
    iVar6 = (iVar6 - local_48) + 1;
    iVar14 = (iVar14 - local_40) + 1;
    if (((0 < iVar6) && (0 < iVar14)) &&
       (iVar7 = SpriteDecompGetAndLockData(param_1,param_2), iVar7 != 0)) {
      iVar8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar9 = (int *)param_1[5];
      if (piVar9 == (int *)0x0) {
        piVar9 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar4[0xc]);
      }
      else {
        EBPalUpdate(piVar9);
      }
      local_34 = 0;
      if (0 < iVar14) {
        do {
          local_2c = (byte *)((iVar7 + *(int *)(piVar4[0xb] + (local_44 + local_34) * 4) + iVar3) -
                             local_4c);
          puVar15 = (uint *)(iVar8 + *(int *)(*(int *)(iVar5 + 0x2c) + (local_40 + local_34) * 4) +
                            local_48 * 2);
          for (iVar2 = iVar6; iVar2 != 0; iVar2 = iVar2 + -1) {
            local_2c = local_2c + -1;
            if (*local_2c != 0) {
              uVar10 = (uint)*(ushort *)((int)piVar9 + (uint)*local_2c * 2 + 0x5c);
              uVar13 = *puVar15;
              uVar16 = (uVar13 & 0xf800) + (uVar10 & 0xf800);
              if (0xf800 < uVar16) {
                uVar16 = 0xf800;
              }
              uVar1 = (uVar13 & 0x7e0) + (uVar10 & 0x7e0);
              uVar11 = (ushort)uVar1;
              if (0x7e0 < uVar1) {
                uVar11 = 0x7e0;
              }
              uVar13 = (uVar10 & 0x1f) + (uVar13 & 0x1f);
              uVar12 = (ushort)uVar13;
              if (0x1f < uVar13) {
                uVar12 = 0x1f;
              }
              *(ushort *)puVar15 = (ushort)uVar16 | uVar11 | uVar12;
            }
            puVar15 = (uint *)((int)puVar15 + 2);
          }
          local_34 = local_34 + 1;
        } while (local_34 < iVar14);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirV8to16 @ 0x080629f0, 744 bytes */
void W_PutSpriteTransAddMirV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  byte *pbVar9;
  uint uVar10;
  ushort uVar11;
  ushort uVar12;
  int iVar13;
  int iVar15;
  uint *puVar16;
  uint uVar17;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_34;
  uint uVar14;
  
  piVar4 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar5 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_44 = 0;
  iVar3 = piVar4[1];
  iVar15 = param_3 - piVar4[2];
  iVar13 = (piVar4[3] - iVar3) + 1 + param_4;
  local_4c = 0;
  if ((((iVar13 <= W_y2) && (W_y1 < iVar3 + iVar13)) && (iVar15 <= W_x2)) &&
     (W_x1 < *piVar4 + iVar15)) {
    local_40 = iVar13;
    if (iVar13 < W_y1) {
      local_40 = W_y1;
      local_44 = W_y1 - iVar13;
    }
    iVar13 = iVar3 + iVar13 + -1;
    if (W_y2 < iVar13) {
      iVar13 = W_y2;
    }
    local_48 = iVar15;
    if (iVar15 < W_x1) {
      local_48 = W_x1;
      local_4c = W_x1 - iVar15;
    }
    iVar15 = *piVar4 + iVar15 + -1;
    if (W_x2 < iVar15) {
      iVar15 = W_x2;
    }
    iVar15 = (iVar15 - local_48) + 1;
    iVar13 = (iVar13 - local_40) + 1;
    if (((0 < iVar15) && (0 < iVar13)) &&
       (iVar6 = SpriteDecompGetAndLockData(param_1,param_2), iVar6 != 0)) {
      iVar7 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar8 = (int *)param_1[5];
      if (piVar8 == (int *)0x0) {
        piVar8 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar4[0xc]);
      }
      else {
        EBPalUpdate(piVar8);
      }
      local_34 = 0;
      if (0 < iVar13) {
        do {
          pbVar9 = (byte *)(iVar6 + *(int *)(piVar4[0xb] + -4 + ((iVar3 - local_44) - local_34) * 4)
                           + local_4c);
          puVar16 = (uint *)(iVar7 + *(int *)(*(int *)(iVar5 + 0x2c) + (local_40 + local_34) * 4) +
                            local_48 * 2);
          for (iVar2 = iVar15; iVar2 != 0; iVar2 = iVar2 + -1) {
            if (*pbVar9 != 0) {
              uVar10 = (uint)*(ushort *)((int)piVar8 + (uint)*pbVar9 * 2 + 0x5c);
              uVar14 = *puVar16;
              uVar17 = (uVar14 & 0xf800) + (uVar10 & 0xf800);
              if (0xf800 < uVar17) {
                uVar17 = 0xf800;
              }
              uVar1 = (uVar14 & 0x7e0) + (uVar10 & 0x7e0);
              uVar11 = (ushort)uVar1;
              if (0x7e0 < uVar1) {
                uVar11 = 0x7e0;
              }
              uVar14 = (uVar10 & 0x1f) + (uVar14 & 0x1f);
              uVar12 = (ushort)uVar14;
              if (0x1f < uVar14) {
                uVar12 = 0x1f;
              }
              *(ushort *)puVar16 = (ushort)uVar17 | uVar11 | uVar12;
            }
            puVar16 = (uint *)((int)puVar16 + 2);
            pbVar9 = pbVar9 + 1;
          }
          local_34 = local_34 + 1;
        } while (local_34 < iVar13);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirHV8to16 @ 0x08062ce0, 760 bytes */
void W_PutSpriteTransAddMirHV8to16(int *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  ushort uVar12;
  ushort uVar13;
  int iVar14;
  uint *puVar16;
  uint uVar17;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_34;
  byte *local_2c;
  uint uVar15;
  
  piVar5 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar6 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar3 = *piVar5;
  iVar4 = piVar5[1];
  local_44 = 0;
  iVar7 = (piVar5[2] - iVar3) + 1 + param_3;
  local_4c = 0;
  iVar14 = (piVar5[3] - iVar4) + 1 + param_4;
  if ((((iVar14 <= W_y2) && (W_y1 < iVar4 + iVar14)) && (iVar7 <= W_x2)) && (W_x1 < iVar3 + iVar7))
  {
    local_40 = iVar14;
    if (iVar14 < W_y1) {
      local_40 = W_y1;
      local_44 = W_y1 - iVar14;
    }
    iVar14 = iVar4 + iVar14 + -1;
    if (W_y2 < iVar14) {
      iVar14 = W_y2;
    }
    local_48 = iVar7;
    if (iVar7 < W_x1) {
      local_48 = W_x1;
      local_4c = W_x1 - iVar7;
    }
    iVar7 = iVar3 + iVar7 + -1;
    if (W_x2 < iVar7) {
      iVar7 = W_x2;
    }
    iVar7 = (iVar7 - local_48) + 1;
    iVar14 = (iVar14 - local_40) + 1;
    if (((0 < iVar7) && (0 < iVar14)) &&
       (iVar8 = SpriteDecompGetAndLockData(param_1,param_2), iVar8 != 0)) {
      iVar9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar10 = (int *)param_1[5];
      if (piVar10 == (int *)0x0) {
        piVar10 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar5[0xc]);
      }
      else {
        EBPalUpdate(piVar10);
      }
      local_34 = 0;
      if (0 < iVar14) {
        do {
          local_2c = (byte *)((iVar8 + *(int *)(piVar5[0xb] + -4 +
                                               ((iVar4 - local_44) - local_34) * 4) + iVar3) -
                             local_4c);
          puVar16 = (uint *)(iVar9 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_40 + local_34) * 4) +
                            local_48 * 2);
          for (iVar2 = iVar7; iVar2 != 0; iVar2 = iVar2 + -1) {
            local_2c = local_2c + -1;
            if (*local_2c != 0) {
              uVar11 = (uint)*(ushort *)((int)piVar10 + (uint)*local_2c * 2 + 0x5c);
              uVar15 = *puVar16;
              uVar17 = (uVar15 & 0xf800) + (uVar11 & 0xf800);
              if (0xf800 < uVar17) {
                uVar17 = 0xf800;
              }
              uVar1 = (uVar15 & 0x7e0) + (uVar11 & 0x7e0);
              uVar12 = (ushort)uVar1;
              if (0x7e0 < uVar1) {
                uVar12 = 0x7e0;
              }
              uVar15 = (uVar11 & 0x1f) + (uVar15 & 0x1f);
              uVar13 = (ushort)uVar15;
              if (0x1f < uVar15) {
                uVar13 = 0x1f;
              }
              *(ushort *)puVar16 = (ushort)uVar17 | uVar12 | uVar13;
            }
            puVar16 = (uint *)((int)puVar16 + 2);
          }
          local_34 = local_34 + 1;
        } while (local_34 < iVar14);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAdd8to16_B @ 0x08062fe0, 2267 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x250-byte frame (a local's address escapes, see apply_frame_emulation) */
void W_PutSpriteTransAdd8to16_B
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  byte *pbVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  unsigned char ghidra_frame[0x250] __attribute__((aligned(16)));
#define local_250 (*(ushort **)(ghidra_frame + 0x0))
#define local_24c (*(int *)(ghidra_frame + 0x4))
#define local_248 (*(int *)(ghidra_frame + 0x8))
#define local_244 (*(int *)(ghidra_frame + 0xc))
#define local_240 (*(int *)(ghidra_frame + 0x10))
#define local_234 (*(int *)(ghidra_frame + 0x1c))
#define local_230 (*(int *)(ghidra_frame + 0x20))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x34))
  
  piVar5 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar6 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_244 = 0;
  local_24c = 0;
  if ((param_5 == 0x100) && (param_6 == 0)) {
    W_PutSprite8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 == 0x100) && (param_6 == 0x100)) {
    W_PutSpriteTransAdd8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 != 0) || (param_6 != 0x100)) {
    iVar12 = param_4 - piVar5[3];
    iVar14 = param_3 - piVar5[2];
    if ((iVar12 <= W_y2) &&
       (((W_y1 < piVar5[1] + iVar12 && (iVar14 <= W_x2)) && (W_x1 < *piVar5 + iVar14)))) {
      local_240 = iVar12;
      if (iVar12 < W_y1) {
        local_240 = W_y1;
        local_244 = W_y1 - iVar12;
      }
      iVar12 = piVar5[1] + iVar12 + -1;
      if (W_y2 < iVar12) {
        iVar12 = W_y2;
      }
      local_248 = iVar14;
      if (iVar14 < W_x1) {
        local_248 = W_x1;
        local_24c = W_x1 - iVar14;
      }
      iVar14 = *piVar5 + iVar14 + -1;
      if (W_x2 < iVar14) {
        iVar14 = W_x2;
      }
      iVar14 = (iVar14 - local_248) + 1;
      iVar12 = (iVar12 - local_240) + 1;
      if (((0 < iVar14) && (0 < iVar12)) &&
         (iVar7 = SpriteDecompGetAndLockData(param_1,param_2), iVar7 != 0)) {
        iVar8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        piVar9 = (int *)param_1[5];
        if (piVar9 == (int *)0x0) {
          piVar9 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar5[0xc]);
        }
        else {
          EBPalUpdate(piVar9);
        }
        puVar16 = (ushort *)(piVar9 + 0x17);
        local_250 = puVar16;
        if (param_5 != 0x100) {
          local_250 = local_21c;
          if (param_5 == 0) {
            memset(local_21c,0,piVar5[5] * 2);
          }
          else if (param_5 == 0x80) {
            local_230 = 1;
            iVar2 = piVar5[5];
            if (1 < iVar2) {
              do {
                local_21c[local_230] = puVar16[local_230] >> 1 & 0xfbef;
                local_230 = local_230 + 1;
              } while (local_230 < iVar2);
            }
          }
          else {
            local_230 = 1;
            iVar2 = piVar5[5];
            if (1 < iVar2) {
              do {
                uVar15 = (uint)puVar16[local_230];
                local_21c[local_230] =
                     (ushort)((uVar15 & 0xf800) * param_5 >> 8) & 0xf800 |
                     (ushort)((uVar15 & 0x7e0) * param_5 >> 8) & 0x7e0 |
                     (ushort)((uVar15 & 0x1f) * param_5 >> 8) & 0x1f;
                local_230 = local_230 + 1;
              } while (local_230 < iVar2);
            }
          }
        }
        if (param_6 == 0) {
          local_234 = 0;
          if (0 < iVar12) {
            piVar9 = (int *)(local_240 * 4 + *(int *)(iVar6 + 0x2c));
            piVar5 = (int *)(local_244 * 4 + piVar5[0xb]);
            do {
              pbVar13 = (byte *)(local_24c + iVar7 + *piVar5);
              puVar16 = (ushort *)(local_248 * 2 + iVar8 + *piVar9);
              for (iVar6 = iVar14; iVar6 != 0; iVar6 = iVar6 + -1) {
                if (*pbVar13 != 0) {
                  *puVar16 = local_250[*pbVar13];
                }
                puVar16 = puVar16 + 1;
                pbVar13 = pbVar13 + 1;
              }
              local_234 = local_234 + 1;
              piVar9 = piVar9 + 1;
              piVar5 = piVar5 + 1;
            } while (local_234 < iVar12);
          }
        }
        else if ((param_5 + param_6 < 0x101) && (param_6 == 0x80)) {
          local_234 = 0;
          if (0 < iVar12) {
            do {
              pbVar13 = (byte *)(local_24c +
                                iVar7 + *(int *)(piVar5[0xb] + (local_244 + local_234) * 4));
              puVar16 = (ushort *)
                        (iVar8 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                if (*pbVar13 != 0) {
                  uVar4 = local_250[*pbVar13];
                  uVar3 = *puVar16 >> 1;
                  *puVar16 = (uVar3 & 0x3e0) + (uVar4 & 0x7e0) | (uVar3 & 0x7800) + (uVar4 & 0xf800)
                             | (uVar3 & 0xf) + (uVar4 & 0x1f);
                }
                puVar16 = puVar16 + 1;
                pbVar13 = pbVar13 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar12);
          }
        }
        else if (param_5 + param_6 < 0x101) {
          local_234 = 0;
          if (0 < iVar12) {
            do {
              pbVar13 = (byte *)(local_24c +
                                iVar7 + *(int *)(piVar5[0xb] + (local_244 + local_234) * 4));
              puVar16 = (ushort *)
                        (iVar8 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                if (*pbVar13 != 0) {
                  uVar4 = local_250[*pbVar13];
                  uVar15 = (uint)*puVar16;
                  *puVar16 = ((ushort)((uVar15 & 0x7e0) * param_6 >> 8) & 0x7e0) + (uVar4 & 0x7e0) |
                             ((ushort)((uVar15 & 0xf800) * param_6 >> 8) & 0xf800) +
                             (uVar4 & 0xf800) |
                             ((ushort)((uVar15 & 0x1f) * param_6 >> 8) & 0x1f) + (uVar4 & 0x1f);
                }
                puVar16 = puVar16 + 1;
                pbVar13 = pbVar13 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar12);
          }
        }
        else if (param_6 == 0x80) {
          local_234 = 0;
          if (0 < iVar12) {
            do {
              pbVar13 = (byte *)(local_24c +
                                iVar7 + *(int *)(piVar5[0xb] + (local_244 + local_234) * 4));
              puVar16 = (ushort *)
                        (iVar8 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                if (*pbVar13 != 0) {
                  uVar10 = (uint)local_250[*pbVar13];
                  uVar11 = (uint)(*puVar16 >> 1);
                  uVar15 = (uVar11 & 0x7800) + (uVar10 & 0xf800);
                  if (0xf800 < uVar15) {
                    uVar15 = 0xf800;
                  }
                  uVar1 = (uVar11 & 0x3e0) + (uVar10 & 0x7e0);
                  uVar4 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar4 = 0x7e0;
                  }
                  uVar10 = (uVar11 & 0xf) + (uVar10 & 0x1f);
                  uVar3 = (ushort)uVar10;
                  if (0x1f < uVar10) {
                    uVar3 = 0x1f;
                  }
                  *puVar16 = uVar4 | (ushort)uVar15 | uVar3;
                }
                puVar16 = puVar16 + 1;
                pbVar13 = pbVar13 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar12);
          }
        }
        else {
          local_234 = 0;
          if (0 < iVar12) {
            do {
              pbVar13 = (byte *)(local_24c +
                                iVar7 + *(int *)(piVar5[0xb] + (local_244 + local_234) * 4));
              puVar16 = (ushort *)
                        (iVar8 + *(int *)(*(int *)(iVar6 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                if (*pbVar13 != 0) {
                  uVar10 = (uint)local_250[*pbVar13];
                  uVar11 = (uint)*puVar16;
                  uVar15 = ((uVar11 & 0xf800) * param_6 >> 8 & 0xf800) + (uVar10 & 0xf800);
                  if (0xf800 < uVar15) {
                    uVar15 = 0xf800;
                  }
                  uVar1 = ((uVar11 & 0x7e0) * param_6 >> 8 & 0x7e0) + (uVar10 & 0x7e0);
                  uVar4 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar4 = 0x7e0;
                  }
                  uVar10 = ((uVar11 & 0x1f) * param_6 >> 8 & 0x1f) + (uVar10 & 0x1f);
                  uVar3 = (ushort)uVar10;
                  if (0x1f < uVar10) {
                    uVar3 = 0x1f;
                  }
                  *puVar16 = uVar4 | (ushort)uVar15 | uVar3;
                }
                puVar16 = puVar16 + 1;
                pbVar13 = pbVar13 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar12);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef local_250
#undef local_24c
#undef local_248
#undef local_244
#undef local_240
#undef local_234
#undef local_230
#undef local_21c

/* W_PutSpriteTransAddMirH8to16_B @ 0x080638c0, 2323 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x260-byte frame (a local's address escapes, see apply_frame_emulation) */
void W_PutSpriteTransAddMirH8to16_B
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  byte *pbVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  ushort *puVar17;
  unsigned char ghidra_frame[0x260] __attribute__((aligned(16)));
#define local_254 (*(ushort **)(ghidra_frame + 0xc))
#define local_24c (*(int *)(ghidra_frame + 0x14))
#define local_248 (*(int *)(ghidra_frame + 0x18))
#define local_244 (*(int *)(ghidra_frame + 0x1c))
#define local_240 (*(int *)(ghidra_frame + 0x20))
#define local_234 (*(int *)(ghidra_frame + 0x2c))
#define local_230 (*(int *)(ghidra_frame + 0x30))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x44))
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_244 = 0;
  local_24c = 0;
  if ((param_5 == 0x100) && (param_6 == 0)) {
    W_PutSpriteMirH8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 == 0x100) && (param_6 == 0x100)) {
    W_PutSpriteTransAddMirH8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 != 0) || (param_6 != 0x100)) {
    iVar3 = *piVar6;
    iVar8 = (piVar6[2] - iVar3) + 1 + param_3;
    iVar15 = param_4 - piVar6[3];
    if ((iVar15 <= W_y2) &&
       (((W_y1 < piVar6[1] + iVar15 && (iVar8 <= W_x2)) && (W_x1 < iVar3 + iVar8)))) {
      local_240 = iVar15;
      if (iVar15 < W_y1) {
        local_240 = W_y1;
        local_244 = W_y1 - iVar15;
      }
      iVar15 = piVar6[1] + iVar15 + -1;
      if (W_y2 < iVar15) {
        iVar15 = W_y2;
      }
      local_248 = iVar8;
      if (iVar8 < W_x1) {
        local_248 = W_x1;
        local_24c = W_x1 - iVar8;
      }
      iVar8 = iVar3 + iVar8 + -1;
      if (W_x2 < iVar8) {
        iVar8 = W_x2;
      }
      iVar8 = (iVar8 - local_248) + 1;
      iVar15 = (iVar15 - local_240) + 1;
      if (((0 < iVar8) && (0 < iVar15)) &&
         (iVar9 = SpriteDecompGetAndLockData(param_1,param_2), iVar9 != 0)) {
        iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        piVar11 = (int *)param_1[5];
        if (piVar11 == (int *)0x0) {
          piVar11 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
        }
        else {
          EBPalUpdate(piVar11);
        }
        puVar17 = (ushort *)(piVar11 + 0x17);
        local_254 = puVar17;
        if (param_5 != 0x100) {
          local_254 = local_21c;
          if (param_5 == 0) {
            memset(local_21c,0,piVar6[5] * 2);
          }
          else if (param_5 == 0x80) {
            local_230 = 1;
            iVar2 = piVar6[5];
            if (1 < iVar2) {
              do {
                local_21c[local_230] = puVar17[local_230] >> 1 & 0xfbef;
                local_230 = local_230 + 1;
              } while (local_230 < iVar2);
            }
          }
          else {
            local_230 = 1;
            iVar2 = piVar6[5];
            if (1 < iVar2) {
              do {
                uVar16 = (uint)puVar17[local_230];
                local_21c[local_230] =
                     (ushort)((uVar16 & 0xf800) * param_5 >> 8) & 0xf800 |
                     (ushort)((uVar16 & 0x7e0) * param_5 >> 8) & 0x7e0 |
                     (ushort)((uVar16 & 0x1f) * param_5 >> 8) & 0x1f;
                local_230 = local_230 + 1;
              } while (local_230 < iVar2);
            }
          }
        }
        if (param_6 == 0) {
          local_234 = 0;
          if (0 < iVar15) {
            piVar6 = (int *)(local_244 * 4 + piVar6[0xb]);
            piVar11 = (int *)(local_240 * 4 + *(int *)(iVar7 + 0x2c));
            do {
              pbVar12 = (byte *)((iVar9 + *piVar6 + iVar3) - local_24c);
              puVar17 = (ushort *)(iVar10 + *piVar11 + local_248 * 2);
              for (iVar7 = iVar8; iVar7 != 0; iVar7 = iVar7 + -1) {
                pbVar12 = pbVar12 + -1;
                if (*pbVar12 != 0) {
                  *puVar17 = local_254[*pbVar12];
                }
                puVar17 = puVar17 + 1;
              }
              local_234 = local_234 + 1;
              piVar6 = piVar6 + 1;
              piVar11 = piVar11 + 1;
            } while (local_234 < iVar15);
          }
        }
        else if ((param_5 + param_6 < 0x101) && (param_6 == 0x80)) {
          local_234 = 0;
          if (0 < iVar15) {
            do {
              pbVar12 = (byte *)((iVar9 + *(int *)(piVar6[0xb] + (local_244 + local_234) * 4) +
                                 iVar3) - local_24c);
              puVar17 = (ushort *)
                        (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar8; iVar2 != 0; iVar2 = iVar2 + -1) {
                pbVar12 = pbVar12 + -1;
                if (*pbVar12 != 0) {
                  uVar5 = local_254[*pbVar12];
                  uVar4 = *puVar17 >> 1;
                  *puVar17 = (uVar4 & 0x3e0) + (uVar5 & 0x7e0) | (uVar4 & 0x7800) + (uVar5 & 0xf800)
                             | (uVar4 & 0xf) + (uVar5 & 0x1f);
                }
                puVar17 = puVar17 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar15);
          }
        }
        else if (param_5 + param_6 < 0x101) {
          local_234 = 0;
          if (0 < iVar15) {
            do {
              pbVar12 = (byte *)((iVar9 + *(int *)(piVar6[0xb] + (local_244 + local_234) * 4) +
                                 iVar3) - local_24c);
              puVar17 = (ushort *)
                        (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar8; iVar2 != 0; iVar2 = iVar2 + -1) {
                pbVar12 = pbVar12 + -1;
                if (*pbVar12 != 0) {
                  uVar5 = local_254[*pbVar12];
                  uVar16 = (uint)*puVar17;
                  *puVar17 = ((ushort)((uVar16 & 0x7e0) * param_6 >> 8) & 0x7e0) + (uVar5 & 0x7e0) |
                             ((ushort)((uVar16 & 0xf800) * param_6 >> 8) & 0xf800) +
                             (uVar5 & 0xf800) |
                             ((ushort)((uVar16 & 0x1f) * param_6 >> 8) & 0x1f) + (uVar5 & 0x1f);
                }
                puVar17 = puVar17 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar15);
          }
        }
        else if (param_6 == 0x80) {
          local_234 = 0;
          if (0 < iVar15) {
            do {
              pbVar12 = (byte *)((iVar9 + *(int *)(piVar6[0xb] + (local_244 + local_234) * 4) +
                                 iVar3) - local_24c);
              puVar17 = (ushort *)
                        (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar8; iVar2 != 0; iVar2 = iVar2 + -1) {
                pbVar12 = pbVar12 + -1;
                if (*pbVar12 != 0) {
                  uVar13 = (uint)local_254[*pbVar12];
                  uVar14 = (uint)(*puVar17 >> 1);
                  uVar16 = (uVar14 & 0x7800) + (uVar13 & 0xf800);
                  if (0xf800 < uVar16) {
                    uVar16 = 0xf800;
                  }
                  uVar1 = (uVar14 & 0x3e0) + (uVar13 & 0x7e0);
                  uVar5 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar5 = 0x7e0;
                  }
                  uVar13 = (uVar14 & 0xf) + (uVar13 & 0x1f);
                  uVar4 = (ushort)uVar13;
                  if (0x1f < uVar13) {
                    uVar4 = 0x1f;
                  }
                  *puVar17 = uVar5 | (ushort)uVar16 | uVar4;
                }
                puVar17 = puVar17 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar15);
          }
        }
        else {
          local_234 = 0;
          if (0 < iVar15) {
            do {
              pbVar12 = (byte *)((iVar9 + *(int *)(piVar6[0xb] + (local_244 + local_234) * 4) +
                                 iVar3) - local_24c);
              puVar17 = (ushort *)
                        (iVar10 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar8; iVar2 != 0; iVar2 = iVar2 + -1) {
                pbVar12 = pbVar12 + -1;
                if (*pbVar12 != 0) {
                  uVar13 = (uint)local_254[*pbVar12];
                  uVar14 = (uint)*puVar17;
                  uVar16 = ((uVar14 & 0xf800) * param_6 >> 8 & 0xf800) + (uVar13 & 0xf800);
                  if (0xf800 < uVar16) {
                    uVar16 = 0xf800;
                  }
                  uVar1 = ((uVar14 & 0x7e0) * param_6 >> 8 & 0x7e0) + (uVar13 & 0x7e0);
                  uVar5 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar5 = 0x7e0;
                  }
                  uVar13 = ((uVar14 & 0x1f) * param_6 >> 8 & 0x1f) + (uVar13 & 0x1f);
                  uVar4 = (ushort)uVar13;
                  if (0x1f < uVar13) {
                    uVar4 = 0x1f;
                  }
                  *puVar17 = uVar5 | (ushort)uVar16 | uVar4;
                }
                puVar17 = puVar17 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar15);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef local_254
#undef local_24c
#undef local_248
#undef local_244
#undef local_240
#undef local_234
#undef local_230
#undef local_21c

/* W_PutSpriteTransAddMirV8to16_B @ 0x080641e0, 2323 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x260-byte frame (a local's address escapes, see apply_frame_emulation) */
void W_PutSpriteTransAddMirV8to16_B
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  byte *pbVar14;
  int iVar15;
  uint uVar16;
  ushort *puVar17;
  unsigned char ghidra_frame[0x260] __attribute__((aligned(16)));
#define local_254 (*(ushort **)(ghidra_frame + 0xc))
#define local_24c (*(int *)(ghidra_frame + 0x14))
#define local_248 (*(int *)(ghidra_frame + 0x18))
#define local_244 (*(int *)(ghidra_frame + 0x1c))
#define local_240 (*(int *)(ghidra_frame + 0x20))
#define local_234 (*(int *)(ghidra_frame + 0x2c))
#define local_230 (*(int *)(ghidra_frame + 0x30))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x44))
  
  piVar6 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar7 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_244 = 0;
  local_24c = 0;
  if ((param_5 == 0x100) && (param_6 == 0)) {
    W_PutSpriteMirV8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 == 0x100) && (param_6 == 0x100)) {
    W_PutSpriteTransAddMirV8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 != 0) || (param_6 != 0x100)) {
    iVar2 = piVar6[1];
    iVar15 = param_3 - piVar6[2];
    iVar13 = (piVar6[3] - iVar2) + 1 + param_4;
    if ((iVar13 <= W_y2) &&
       (((W_y1 < iVar2 + iVar13 && (iVar15 <= W_x2)) && (W_x1 < *piVar6 + iVar15)))) {
      local_240 = iVar13;
      if (iVar13 < W_y1) {
        local_240 = W_y1;
        local_244 = W_y1 - iVar13;
      }
      iVar13 = iVar2 + iVar13 + -1;
      if (W_y2 < iVar13) {
        iVar13 = W_y2;
      }
      local_248 = iVar15;
      if (iVar15 < W_x1) {
        local_248 = W_x1;
        local_24c = W_x1 - iVar15;
      }
      iVar15 = *piVar6 + iVar15 + -1;
      if (W_x2 < iVar15) {
        iVar15 = W_x2;
      }
      iVar15 = (iVar15 - local_248) + 1;
      iVar13 = (iVar13 - local_240) + 1;
      if (((0 < iVar15) && (0 < iVar13)) &&
         (iVar8 = SpriteDecompGetAndLockData(param_1,param_2), iVar8 != 0)) {
        iVar9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        piVar10 = (int *)param_1[5];
        if (piVar10 == (int *)0x0) {
          piVar10 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar6[0xc]);
        }
        else {
          EBPalUpdate(piVar10);
        }
        puVar17 = (ushort *)(piVar10 + 0x17);
        local_254 = puVar17;
        if (param_5 != 0x100) {
          local_254 = local_21c;
          if (param_5 == 0) {
            memset(local_21c,0,piVar6[5] * 2);
          }
          else if (param_5 == 0x80) {
            local_230 = 1;
            iVar3 = piVar6[5];
            if (1 < iVar3) {
              do {
                local_21c[local_230] = puVar17[local_230] >> 1 & 0xfbef;
                local_230 = local_230 + 1;
              } while (local_230 < iVar3);
            }
          }
          else {
            local_230 = 1;
            iVar3 = piVar6[5];
            if (1 < iVar3) {
              do {
                uVar16 = (uint)puVar17[local_230];
                local_21c[local_230] =
                     (ushort)((uVar16 & 0xf800) * param_5 >> 8) & 0xf800 |
                     (ushort)((uVar16 & 0x7e0) * param_5 >> 8) & 0x7e0 |
                     (ushort)((uVar16 & 0x1f) * param_5 >> 8) & 0x1f;
                local_230 = local_230 + 1;
              } while (local_230 < iVar3);
            }
          }
        }
        if (param_6 == 0) {
          local_234 = 0;
          if (0 < iVar13) {
            iVar3 = piVar6[0xb];
            piVar6 = (int *)(local_240 * 4 + *(int *)(iVar7 + 0x2c));
            do {
              pbVar14 = (byte *)(local_24c +
                                iVar8 + *(int *)(iVar3 + -4 + ((iVar2 - local_244) - local_234) * 4)
                                );
              puVar17 = (ushort *)(iVar9 + *piVar6 + local_248 * 2);
              for (iVar7 = iVar15; iVar7 != 0; iVar7 = iVar7 + -1) {
                if (*pbVar14 != 0) {
                  *puVar17 = local_254[*pbVar14];
                }
                puVar17 = puVar17 + 1;
                pbVar14 = pbVar14 + 1;
              }
              local_234 = local_234 + 1;
              piVar6 = piVar6 + 1;
            } while (local_234 < iVar13);
          }
        }
        else if ((param_5 + param_6 < 0x101) && (param_6 == 0x80)) {
          local_234 = 0;
          if (0 < iVar13) {
            do {
              pbVar14 = (byte *)(local_24c +
                                iVar8 + *(int *)(piVar6[0xb] + -4 +
                                                ((iVar2 - local_244) - local_234) * 4));
              puVar17 = (ushort *)
                        (iVar9 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                if (*pbVar14 != 0) {
                  uVar5 = local_254[*pbVar14];
                  uVar4 = *puVar17 >> 1;
                  *puVar17 = (uVar4 & 0x3e0) + (uVar5 & 0x7e0) | (uVar4 & 0x7800) + (uVar5 & 0xf800)
                             | (uVar4 & 0xf) + (uVar5 & 0x1f);
                }
                puVar17 = puVar17 + 1;
                pbVar14 = pbVar14 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar13);
          }
        }
        else if (param_5 + param_6 < 0x101) {
          local_234 = 0;
          if (0 < iVar13) {
            do {
              pbVar14 = (byte *)(local_24c +
                                iVar8 + *(int *)(piVar6[0xb] + -4 +
                                                ((iVar2 - local_244) - local_234) * 4));
              puVar17 = (ushort *)
                        (iVar9 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                if (*pbVar14 != 0) {
                  uVar5 = local_254[*pbVar14];
                  uVar16 = (uint)*puVar17;
                  *puVar17 = ((ushort)((uVar16 & 0x7e0) * param_6 >> 8) & 0x7e0) + (uVar5 & 0x7e0) |
                             ((ushort)((uVar16 & 0xf800) * param_6 >> 8) & 0xf800) +
                             (uVar5 & 0xf800) |
                             ((ushort)((uVar16 & 0x1f) * param_6 >> 8) & 0x1f) + (uVar5 & 0x1f);
                }
                puVar17 = puVar17 + 1;
                pbVar14 = pbVar14 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar13);
          }
        }
        else if (param_6 == 0x80) {
          local_234 = 0;
          if (0 < iVar13) {
            do {
              pbVar14 = (byte *)(local_24c +
                                iVar8 + *(int *)(piVar6[0xb] + -4 +
                                                ((iVar2 - local_244) - local_234) * 4));
              puVar17 = (ushort *)
                        (iVar9 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                if (*pbVar14 != 0) {
                  uVar11 = (uint)local_254[*pbVar14];
                  uVar12 = (uint)(*puVar17 >> 1);
                  uVar16 = (uVar12 & 0x7800) + (uVar11 & 0xf800);
                  if (0xf800 < uVar16) {
                    uVar16 = 0xf800;
                  }
                  uVar1 = (uVar12 & 0x3e0) + (uVar11 & 0x7e0);
                  uVar5 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar5 = 0x7e0;
                  }
                  uVar11 = (uVar12 & 0xf) + (uVar11 & 0x1f);
                  uVar4 = (ushort)uVar11;
                  if (0x1f < uVar11) {
                    uVar4 = 0x1f;
                  }
                  *puVar17 = uVar5 | (ushort)uVar16 | uVar4;
                }
                puVar17 = puVar17 + 1;
                pbVar14 = pbVar14 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar13);
          }
        }
        else {
          local_234 = 0;
          if (0 < iVar13) {
            do {
              pbVar14 = (byte *)(local_24c +
                                iVar8 + *(int *)(piVar6[0xb] + -4 +
                                                ((iVar2 - local_244) - local_234) * 4));
              puVar17 = (ushort *)
                        (iVar9 + *(int *)(*(int *)(iVar7 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                if (*pbVar14 != 0) {
                  uVar11 = (uint)local_254[*pbVar14];
                  uVar12 = (uint)*puVar17;
                  uVar16 = ((uVar12 & 0xf800) * param_6 >> 8 & 0xf800) + (uVar11 & 0xf800);
                  if (0xf800 < uVar16) {
                    uVar16 = 0xf800;
                  }
                  uVar1 = ((uVar12 & 0x7e0) * param_6 >> 8 & 0x7e0) + (uVar11 & 0x7e0);
                  uVar5 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar5 = 0x7e0;
                  }
                  uVar11 = ((uVar12 & 0x1f) * param_6 >> 8 & 0x1f) + (uVar11 & 0x1f);
                  uVar4 = (ushort)uVar11;
                  if (0x1f < uVar11) {
                    uVar4 = 0x1f;
                  }
                  *puVar17 = uVar5 | (ushort)uVar16 | uVar4;
                }
                puVar17 = puVar17 + 1;
                pbVar14 = pbVar14 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar13);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef local_254
#undef local_24c
#undef local_248
#undef local_244
#undef local_240
#undef local_234
#undef local_230
#undef local_21c

/* W_PutSpriteTransAddMirHV8to16_B @ 0x08064b00, 2355 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x260-byte frame (a local's address escapes, see apply_frame_emulation) */
void W_PutSpriteTransAddMirHV8to16_B
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  ushort uVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  byte *pbVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  uint uVar18;
  ushort *puVar19;
  unsigned char ghidra_frame[0x260] __attribute__((aligned(16)));
#define local_258 (*(ushort **)(ghidra_frame + 0x8))
#define local_24c (*(int *)(ghidra_frame + 0x14))
#define local_248 (*(int *)(ghidra_frame + 0x18))
#define local_244 (*(int *)(ghidra_frame + 0x1c))
#define local_240 (*(int *)(ghidra_frame + 0x20))
#define local_234 (*(int *)(ghidra_frame + 0x2c))
#define local_230 (*(int *)(ghidra_frame + 0x30))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x44))
  
  piVar8 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar9 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_244 = 0;
  local_24c = 0;
  if ((param_5 == 0x100) && (param_6 == 0)) {
    W_PutSpriteMirHV8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 == 0x100) && (param_6 == 0x100)) {
    W_PutSpriteTransAddMirHV8to16(param_1,param_2,param_3,param_4);
  }
  else if ((param_5 != 0) || (param_6 != 0x100)) {
    iVar3 = *piVar8;
    iVar4 = piVar8[1];
    iVar10 = (piVar8[2] - iVar3) + 1 + param_3;
    iVar17 = (piVar8[3] - iVar4) + 1 + param_4;
    if ((iVar17 <= W_y2) &&
       (((W_y1 < iVar4 + iVar17 && (iVar10 <= W_x2)) && (W_x1 < iVar3 + iVar10)))) {
      local_240 = iVar17;
      if (iVar17 < W_y1) {
        local_240 = W_y1;
        local_244 = W_y1 - iVar17;
      }
      iVar17 = iVar4 + iVar17 + -1;
      if (W_y2 < iVar17) {
        iVar17 = W_y2;
      }
      local_248 = iVar10;
      if (iVar10 < W_x1) {
        local_248 = W_x1;
        local_24c = W_x1 - iVar10;
      }
      iVar10 = iVar3 + iVar10 + -1;
      if (W_x2 < iVar10) {
        iVar10 = W_x2;
      }
      iVar10 = (iVar10 - local_248) + 1;
      iVar17 = (iVar17 - local_240) + 1;
      if (((0 < iVar10) && (0 < iVar17)) &&
         (iVar11 = SpriteDecompGetAndLockData(param_1,param_2), iVar11 != 0)) {
        iVar12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        piVar13 = (int *)param_1[5];
        if (piVar13 == (int *)0x0) {
          piVar13 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar8[0xc]);
        }
        else {
          EBPalUpdate(piVar13);
        }
        puVar19 = (ushort *)(piVar13 + 0x17);
        local_258 = puVar19;
        if (param_5 != 0x100) {
          local_258 = local_21c;
          if (param_5 == 0) {
            memset(local_21c,0,piVar8[5] * 2);
          }
          else if (param_5 == 0x80) {
            local_230 = 1;
            iVar5 = piVar8[5];
            if (1 < iVar5) {
              do {
                local_21c[local_230] = puVar19[local_230] >> 1 & 0xfbef;
                local_230 = local_230 + 1;
              } while (local_230 < iVar5);
            }
          }
          else {
            local_230 = 1;
            iVar5 = piVar8[5];
            if (1 < iVar5) {
              do {
                uVar18 = (uint)puVar19[local_230];
                local_21c[local_230] =
                     (ushort)((uVar18 & 0xf800) * param_5 >> 8) & 0xf800 |
                     (ushort)((uVar18 & 0x7e0) * param_5 >> 8) & 0x7e0 |
                     (ushort)((uVar18 & 0x1f) * param_5 >> 8) & 0x1f;
                local_230 = local_230 + 1;
              } while (local_230 < iVar5);
            }
          }
        }
        if (param_6 == 0) {
          local_234 = 0;
          if (0 < iVar17) {
            iVar5 = piVar8[0xb];
            do {
              pbVar14 = (byte *)((iVar11 + *(int *)(iVar5 + -4 +
                                                   ((iVar4 - local_244) - local_234) * 4) + iVar3) -
                                local_24c);
              puVar19 = (ushort *)
                        (iVar12 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar2 = iVar10; iVar2 != 0; iVar2 = iVar2 + -1) {
                pbVar14 = pbVar14 + -1;
                if (*pbVar14 != 0) {
                  *puVar19 = local_258[*pbVar14];
                }
                puVar19 = puVar19 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar17);
          }
        }
        else if ((param_5 + param_6 < 0x101) && (param_6 == 0x80)) {
          local_234 = 0;
          if (0 < iVar17) {
            do {
              pbVar14 = (byte *)((iVar11 + *(int *)(piVar8[0xb] + -4 +
                                                   ((iVar4 - local_244) - local_234) * 4) + iVar3) -
                                local_24c);
              puVar19 = (ushort *)
                        (iVar12 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar5 = iVar10; iVar5 != 0; iVar5 = iVar5 + -1) {
                pbVar14 = pbVar14 + -1;
                if (*pbVar14 != 0) {
                  uVar7 = local_258[*pbVar14];
                  uVar6 = *puVar19 >> 1;
                  *puVar19 = (uVar6 & 0x3e0) + (uVar7 & 0x7e0) | (uVar6 & 0x7800) + (uVar7 & 0xf800)
                             | (uVar6 & 0xf) + (uVar7 & 0x1f);
                }
                puVar19 = puVar19 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar17);
          }
        }
        else if (param_5 + param_6 < 0x101) {
          local_234 = 0;
          if (0 < iVar17) {
            do {
              pbVar14 = (byte *)((iVar11 + *(int *)(piVar8[0xb] + -4 +
                                                   ((iVar4 - local_244) - local_234) * 4) + iVar3) -
                                local_24c);
              puVar19 = (ushort *)
                        (iVar12 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar5 = iVar10; iVar5 != 0; iVar5 = iVar5 + -1) {
                pbVar14 = pbVar14 + -1;
                if (*pbVar14 != 0) {
                  uVar7 = local_258[*pbVar14];
                  uVar18 = (uint)*puVar19;
                  *puVar19 = ((ushort)((uVar18 & 0x7e0) * param_6 >> 8) & 0x7e0) + (uVar7 & 0x7e0) |
                             ((ushort)((uVar18 & 0xf800) * param_6 >> 8) & 0xf800) +
                             (uVar7 & 0xf800) |
                             ((ushort)((uVar18 & 0x1f) * param_6 >> 8) & 0x1f) + (uVar7 & 0x1f);
                }
                puVar19 = puVar19 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar17);
          }
        }
        else if (param_6 == 0x80) {
          local_234 = 0;
          if (0 < iVar17) {
            do {
              pbVar14 = (byte *)((iVar11 + *(int *)(piVar8[0xb] + -4 +
                                                   ((iVar4 - local_244) - local_234) * 4) + iVar3) -
                                local_24c);
              puVar19 = (ushort *)
                        (iVar12 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar5 = iVar10; iVar5 != 0; iVar5 = iVar5 + -1) {
                pbVar14 = pbVar14 + -1;
                if (*pbVar14 != 0) {
                  uVar15 = (uint)local_258[*pbVar14];
                  uVar16 = (uint)(*puVar19 >> 1);
                  uVar18 = (uVar16 & 0x7800) + (uVar15 & 0xf800);
                  if (0xf800 < uVar18) {
                    uVar18 = 0xf800;
                  }
                  uVar1 = (uVar16 & 0x3e0) + (uVar15 & 0x7e0);
                  uVar7 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar7 = 0x7e0;
                  }
                  uVar15 = (uVar16 & 0xf) + (uVar15 & 0x1f);
                  uVar6 = (ushort)uVar15;
                  if (0x1f < uVar15) {
                    uVar6 = 0x1f;
                  }
                  *puVar19 = uVar7 | (ushort)uVar18 | uVar6;
                }
                puVar19 = puVar19 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar17);
          }
        }
        else {
          local_234 = 0;
          if (0 < iVar17) {
            do {
              pbVar14 = (byte *)((iVar11 + *(int *)(piVar8[0xb] + -4 +
                                                   ((iVar4 - local_244) - local_234) * 4) + iVar3) -
                                local_24c);
              puVar19 = (ushort *)
                        (iVar12 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_240 + local_234) * 4) +
                        local_248 * 2);
              for (iVar5 = iVar10; iVar5 != 0; iVar5 = iVar5 + -1) {
                pbVar14 = pbVar14 + -1;
                if (*pbVar14 != 0) {
                  uVar15 = (uint)local_258[*pbVar14];
                  uVar16 = (uint)*puVar19;
                  uVar18 = ((uVar16 & 0xf800) * param_6 >> 8 & 0xf800) + (uVar15 & 0xf800);
                  if (0xf800 < uVar18) {
                    uVar18 = 0xf800;
                  }
                  uVar1 = ((uVar16 & 0x7e0) * param_6 >> 8 & 0x7e0) + (uVar15 & 0x7e0);
                  uVar7 = (ushort)uVar1;
                  if (0x7e0 < uVar1) {
                    uVar7 = 0x7e0;
                  }
                  uVar15 = ((uVar16 & 0x1f) * param_6 >> 8 & 0x1f) + (uVar15 & 0x1f);
                  uVar6 = (ushort)uVar15;
                  if (0x1f < uVar15) {
                    uVar6 = 0x1f;
                  }
                  *puVar19 = uVar7 | (ushort)uVar18 | uVar6;
                }
                puVar19 = puVar19 + 1;
              }
              local_234 = local_234 + 1;
            } while (local_234 < iVar17);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef local_258
#undef local_24c
#undef local_248
#undef local_244
#undef local_240
#undef local_234
#undef local_230
#undef local_21c

/* W_ScaleSpriteTransAdd8to16 @ 0x08065440, 2478 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAdd8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  uint uVar1;
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
  ushort *puVar15;
  uint uVar16;
  ushort uVar17;
  ushort uVar18;
  uint uVar20;
  uint uVar21;
  int local_144;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  uint local_f4;
  uint local_f0;
  int local_dc;
  uint local_54;
  uint uVar19;
  
  piVar7 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_fc = 0;
  local_104 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar3 = *piVar7;
    iVar11 = piVar7[1];
    if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar11 - param_6))) {
      fVar4 = param_3 - ((float10)piVar7[2] * param_5) / (float10)iVar3;
      fVar5 = param_4 - ((float10)piVar7[3] * param_6) / (float10)iVar11;
      if ((((fVar5 <= (float)W_y2) && ((float)W_y1 < (fVar5 + param_6) - 0.5)) &&
          (fVar4 <= (float)W_x2)) && ((float)W_x1 < (fVar4 + param_5) - 0.5)) {
        local_f8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
        fVar6 = (float)local_f8;
        if (fVar5 <= fVar6) {
          local_f0 = 0;
        }
        else {
          if ((float)local_f8 < fVar5 - 0.5) {
            local_f8 = local_f8 + 1;
            fVar6 = (float)local_f8;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar11 * (fVar6 - fVar5)) / param_6) * 65536.0);
          local_f0 = local_54;
        }
        if (local_f8 < W_y1) {
          iVar9 = W_y1 - local_f8;
          local_f8 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar9 * iVar11) / param_6) * 65536.0);
          local_f0 = local_f0 + local_54;
        }
        iVar9 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_6) - 0.5));
        if (W_y2 < iVar9) {
          iVar9 = W_y2;
        }
        if (iVar9 - local_f8 != -1 && -1 < (iVar9 - local_f8) + 1) {
          local_100 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar4));
          fVar5 = (float)local_100;
          if (fVar4 <= fVar5) {
            local_f4 = 0;
          }
          else {
            if ((float)local_100 < fVar4 - 0.5) {
              local_100 = local_100 + 1;
              fVar5 = (float)local_100;
            }
            local_54 = (uint)(longlong)ROUND((((fVar5 - fVar4) * (float10)iVar3) / param_5) * 65536.0)
            ;
            local_f4 = local_54;
          }
          if (fVar4 < (float)W_x1) {
            iVar10 = W_x1 - local_100;
            local_100 = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar10 * iVar3) / param_5) * 65536.0);
            local_f4 = local_f4 + local_144;
          }
          iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar4 + param_5) - 0.5));
          if (W_x2 < iVar10) {
            iVar10 = W_x2;
          }
          local_54 = (uint)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
          iVar3 = (int)GHIDRA_FIST32((float)(iVar11 << 0x10) / param_6);
          for (; ((int)local_f4 < 0 && (local_100 <= iVar10)); local_100 = local_100 + 1) {
            local_f4 = local_f4 + local_54;
          }
          iVar11 = (int)local_f4 >> 0x10;
          if (iVar11 != 0) {
            local_f4 = local_f4 & 0xffff;
            local_104 = iVar11;
          }
          for (; ((int)local_f0 < 0 && (local_f8 <= iVar9)); local_f8 = local_f8 + 1) {
            local_f0 = local_f0 + iVar3;
          }
          iVar11 = (int)local_f0 >> 0x10;
          if (iVar11 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_fc = iVar11;
          }
          iVar11 = (iVar10 - local_100) + 1;
          iVar9 = (iVar9 - local_f8) + 1;
          if ((0 < iVar11) && (0 < iVar9)) {
            iVar10 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar10 != 0) {
              iVar12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar13 = (int *)param_1[5];
              if (piVar13 == (int *)0x0) {
                piVar13 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar7[0xc]);
              }
              else {
                EBPalUpdate(piVar13);
              }
              local_dc = 0;
              if (0 < iVar9) {
                do {
                  pbVar14 = (byte *)(iVar10 + *(int *)(piVar7[0xb] +
                                                      (((int)local_f0 >> 0x10) + local_fc) * 4) +
                                    local_104);
                  puVar15 = (ushort *)
                            (iVar12 + *(int *)(*(int *)(iVar8 + 0x2c) + (local_f8 + local_dc) * 4) +
                            local_100 * 2);
                  uVar20 = local_f4;
                  for (iVar2 = iVar11; iVar2 != 0; iVar2 = iVar2 + -1) {
                    if (*pbVar14 != 0) {
                      uVar19 = (uint)*(ushort *)((int)piVar13 + (uint)*pbVar14 * 2 + 0x5c);
                      uVar16 = (uint)*puVar15;
                      uVar21 = (uVar16 & 0xf800) + (uVar19 & 0xf800);
                      if (0xf800 < uVar21) {
                        uVar21 = 0xf800;
                      }
                      uVar1 = (uVar16 & 0x7e0) + (uVar19 & 0x7e0);
                      uVar17 = (ushort)uVar1;
                      if (0x7e0 < uVar1) {
                        uVar17 = 0x7e0;
                      }
                      uVar19 = (uVar19 & 0x1f) + (uVar16 & 0x1f);
                      uVar18 = (ushort)uVar19;
                      if (0x1f < uVar19) {
                        uVar18 = 0x1f;
                      }
                      *puVar15 = (ushort)uVar21 | uVar17 | uVar18;
                    }
                    puVar15 = puVar15 + 1;
                    pbVar14 = pbVar14 + (uVar20 + local_54 >> 0x10);
                    uVar20 = uVar20 + local_54 & 0xffff;
                  }
                  local_dc = local_dc + 1;
                  local_f0 = local_f0 + iVar3;
                } while (local_dc < iVar9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAdd8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirH8to16 @ 0x08065df0, 2480 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirH8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  uint uVar1;
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
  ushort *puVar16;
  uint uVar17;
  ushort uVar18;
  ushort uVar19;
  uint uVar21;
  uint uVar22;
  int local_144;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  uint local_f4;
  uint local_f0;
  int local_dc;
  uint local_54;
  uint uVar20;
  
  piVar8 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar9 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_fc = 0;
  local_104 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar3 = *piVar8;
    iVar4 = piVar8[1];
    if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar4 - param_6))) {
      fVar5 = param_3 - ((float)((iVar3 - piVar8[2]) + -1) * param_5) / (float10)iVar3;
      fVar6 = param_4 - ((float10)piVar8[3] * param_6) / (float10)iVar4;
      if ((((fVar6 <= (float)W_y2) && ((float)W_y1 < (fVar6 + param_6) - 0.5)) &&
          (fVar5 <= (float)W_x2)) && ((float)W_x1 < (fVar5 + param_5) - 0.5)) {
        local_f8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
        fVar7 = (float)local_f8;
        if (fVar6 <= fVar7) {
          local_f0 = 0;
        }
        else {
          if ((float)local_f8 < fVar6 - 0.5) {
            local_f8 = local_f8 + 1;
            fVar7 = (float)local_f8;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar4 * (fVar7 - fVar6)) / param_6) * 65536.0);
          local_f0 = local_54;
        }
        if (local_f8 < W_y1) {
          iVar10 = W_y1 - local_f8;
          local_f8 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar10 * iVar4) / param_6) * 65536.0);
          local_f0 = local_f0 + local_54;
        }
        iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_6) - 0.5));
        if (W_y2 < iVar10) {
          iVar10 = W_y2;
        }
        if (iVar10 - local_f8 != -1 && -1 < (iVar10 - local_f8) + 1) {
          local_100 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
          fVar6 = (float)local_100;
          if (fVar5 <= fVar6) {
            local_f4 = 0;
          }
          else {
            if ((float)local_100 < fVar5 - 0.5) {
              local_100 = local_100 + 1;
              fVar6 = (float)local_100;
            }
            local_54 = (uint)(longlong)ROUND((((fVar6 - fVar5) * (float10)iVar3) / param_5) * 65536.0)
            ;
            local_f4 = local_54;
          }
          if (fVar5 < (float)W_x1) {
            iVar11 = W_x1 - local_100;
            local_100 = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar11 * iVar3) / param_5) * 65536.0);
            local_f4 = local_f4 + local_144;
          }
          iVar11 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
          if (W_x2 < iVar11) {
            iVar11 = W_x2;
          }
          local_144 = (int)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
          iVar4 = (int)GHIDRA_FIST32((float)(iVar4 << 0x10) / param_6);
          for (; ((int)local_f4 < 0 && (local_100 <= iVar11)); local_100 = local_100 + 1) {
            local_f4 = local_f4 + local_144;
          }
          iVar12 = (int)local_f4 >> 0x10;
          if (iVar12 != 0) {
            local_f4 = local_f4 & 0xffff;
            local_104 = iVar12;
          }
          for (; ((int)local_f0 < 0 && (local_f8 <= iVar10)); local_f8 = local_f8 + 1) {
            local_f0 = local_f0 + iVar4;
          }
          iVar12 = (int)local_f0 >> 0x10;
          if (iVar12 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_fc = iVar12;
          }
          iVar11 = (iVar11 - local_100) + 1;
          iVar10 = (iVar10 - local_f8) + 1;
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
              local_dc = 0;
              if (0 < iVar10) {
                do {
                  pbVar15 = (byte *)(((iVar12 + *(int *)(piVar8[0xb] +
                                                        (((int)local_f0 >> 0x10) + local_fc) * 4) +
                                      iVar3) - local_104) + -1);
                  puVar16 = (ushort *)
                            (iVar13 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_f8 + local_dc) * 4) +
                            local_100 * 2);
                  uVar21 = local_f4;
                  for (iVar2 = iVar11; iVar2 != 0; iVar2 = iVar2 + -1) {
                    if (*pbVar15 != 0) {
                      uVar20 = (uint)*(ushort *)((int)piVar14 + (uint)*pbVar15 * 2 + 0x5c);
                      uVar17 = (uint)*puVar16;
                      uVar22 = (uVar17 & 0xf800) + (uVar20 & 0xf800);
                      if (0xf800 < uVar22) {
                        uVar22 = 0xf800;
                      }
                      uVar1 = (uVar17 & 0x7e0) + (uVar20 & 0x7e0);
                      uVar18 = (ushort)uVar1;
                      if (0x7e0 < uVar1) {
                        uVar18 = 0x7e0;
                      }
                      uVar20 = (uVar20 & 0x1f) + (uVar17 & 0x1f);
                      uVar19 = (ushort)uVar20;
                      if (0x1f < uVar20) {
                        uVar19 = 0x1f;
                      }
                      *puVar16 = (ushort)uVar22 | uVar18 | uVar19;
                    }
                    uVar22 = uVar21 + local_144;
                    uVar21 = uVar22 & 0xffff;
                    puVar16 = puVar16 + 1;
                    pbVar15 = pbVar15 + -(uVar22 >> 0x10);
                  }
                  local_dc = local_dc + 1;
                  local_f0 = local_f0 + iVar4;
                } while (local_dc < iVar10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirH8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirV8to16 @ 0x080667a0, 2497 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  uint uVar1;
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
  ushort *puVar16;
  uint uVar17;
  ushort uVar18;
  ushort uVar19;
  uint uVar21;
  uint uVar22;
  int local_144;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  uint local_f4;
  uint local_f0;
  int local_dc;
  uint local_54;
  uint uVar20;
  
  piVar8 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar9 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_fc = 0;
  local_104 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar3 = *piVar8;
    iVar4 = piVar8[1];
    if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar4 - param_6))) {
      fVar5 = param_3 - ((float10)piVar8[2] * param_5) / (float10)iVar3;
      fVar6 = param_4 - ((float)((iVar4 - piVar8[3]) + -1) * param_6) / (float10)iVar4;
      if ((((fVar6 <= (float)W_y2) && ((float)W_y1 < (fVar6 + param_6) - 0.5)) &&
          (fVar5 <= (float)W_x2)) && ((float)W_x1 < (fVar5 + param_5) - 0.5)) {
        local_f8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
        fVar7 = (float)local_f8;
        if (fVar6 <= fVar7) {
          local_f0 = 0;
        }
        else {
          if ((float)local_f8 < fVar6 - 0.5) {
            local_f8 = local_f8 + 1;
            fVar7 = (float)local_f8;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar4 * (fVar7 - fVar6)) / param_6) * 65536.0);
          local_f0 = local_54;
        }
        if (local_f8 < W_y1) {
          iVar10 = W_y1 - local_f8;
          local_f8 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar10 * iVar4) / param_6) * 65536.0);
          local_f0 = local_f0 + local_54;
        }
        iVar10 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_6) - 0.5));
        if (W_y2 < iVar10) {
          iVar10 = W_y2;
        }
        if (iVar10 - local_f8 != -1 && -1 < (iVar10 - local_f8) + 1) {
          local_100 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
          fVar6 = (float)local_100;
          if (fVar5 <= fVar6) {
            local_f4 = 0;
          }
          else {
            if ((float)local_100 < fVar5 - 0.5) {
              local_100 = local_100 + 1;
              fVar6 = (float)local_100;
            }
            local_54 = (uint)(longlong)ROUND((((fVar6 - fVar5) * (float10)iVar3) / param_5) * 65536.0)
            ;
            local_f4 = local_54;
          }
          if (fVar5 < (float)W_x1) {
            iVar11 = W_x1 - local_100;
            local_100 = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar11 * iVar3) / param_5) * 65536.0);
            local_f4 = local_f4 + local_144;
          }
          iVar11 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
          if (W_x2 < iVar11) {
            iVar11 = W_x2;
          }
          local_54 = (uint)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
          iVar3 = (int)GHIDRA_FIST32((float)(iVar4 << 0x10) / param_6);
          for (; ((int)local_f4 < 0 && (local_100 <= iVar11)); local_100 = local_100 + 1) {
            local_f4 = local_f4 + local_54;
          }
          iVar12 = (int)local_f4 >> 0x10;
          if (iVar12 != 0) {
            local_f4 = local_f4 & 0xffff;
            local_104 = iVar12;
          }
          for (; ((int)local_f0 < 0 && (local_f8 <= iVar10)); local_f8 = local_f8 + 1) {
            local_f0 = local_f0 + iVar3;
          }
          iVar12 = (int)local_f0 >> 0x10;
          if (iVar12 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_fc = iVar12;
          }
          iVar11 = (iVar11 - local_100) + 1;
          iVar10 = (iVar10 - local_f8) + 1;
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
              local_dc = 0;
              if (0 < iVar10) {
                do {
                  pbVar15 = (byte *)(iVar12 + *(int *)(piVar8[0xb] + -4 +
                                                      ((iVar4 - local_fc) - ((int)local_f0 >> 0x10))
                                                      * 4) + local_104);
                  puVar16 = (ushort *)
                            (iVar13 + *(int *)(*(int *)(iVar9 + 0x2c) + (local_f8 + local_dc) * 4) +
                            local_100 * 2);
                  uVar21 = local_f4;
                  for (iVar2 = iVar11; iVar2 != 0; iVar2 = iVar2 + -1) {
                    if (*pbVar15 != 0) {
                      uVar20 = (uint)*(ushort *)((int)piVar14 + (uint)*pbVar15 * 2 + 0x5c);
                      uVar17 = (uint)*puVar16;
                      uVar22 = (uVar17 & 0xf800) + (uVar20 & 0xf800);
                      if (0xf800 < uVar22) {
                        uVar22 = 0xf800;
                      }
                      uVar1 = (uVar17 & 0x7e0) + (uVar20 & 0x7e0);
                      uVar18 = (ushort)uVar1;
                      if (0x7e0 < uVar1) {
                        uVar18 = 0x7e0;
                      }
                      uVar20 = (uVar20 & 0x1f) + (uVar17 & 0x1f);
                      uVar19 = (ushort)uVar20;
                      if (0x1f < uVar20) {
                        uVar19 = 0x1f;
                      }
                      *puVar16 = (ushort)uVar22 | uVar18 | uVar19;
                    }
                    uVar22 = uVar21 + local_54;
                    uVar21 = uVar22 & 0xffff;
                    puVar16 = puVar16 + 1;
                    pbVar15 = pbVar15 + (uVar22 >> 0x10);
                  }
                  local_dc = local_dc + 1;
                  local_f0 = local_f0 + iVar3;
                } while (local_dc < iVar10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV8to16 @ 0x08067170, 2494 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirHV8to16
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  byte *pbVar16;
  ushort *puVar17;
  uint uVar18;
  ushort uVar19;
  ushort uVar20;
  uint uVar22;
  uint uVar23;
  int local_144;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  uint local_f4;
  uint local_f0;
  int local_dc;
  uint local_54;
  uint uVar21;
  
  piVar9 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar10 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_fc = 0;
  local_104 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    iVar4 = *piVar9;
    iVar5 = piVar9[1];
    if ((((double)0.001) <= ABS((float10)iVar4 - param_5)) || (((double)0.001) <= ABS((float10)iVar5 - param_6))) {
      fVar6 = param_3 - ((float)((iVar4 - piVar9[2]) + -1) * param_5) / (float10)iVar4;
      fVar7 = param_4 - ((float)((iVar5 - piVar9[3]) + -1) * param_6) / (float10)iVar5;
      if ((((fVar7 <= (float)W_y2) && ((float)W_y1 < (fVar7 + param_6) - 0.5)) &&
          (fVar6 <= (float)W_x2)) && ((float)W_x1 < (fVar6 + param_5) - 0.5)) {
        local_f8 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar7));
        fVar8 = (float)local_f8;
        if (fVar7 <= fVar8) {
          local_f0 = 0;
        }
        else {
          if ((float)local_f8 < fVar7 - 0.5) {
            local_f8 = local_f8 + 1;
            fVar8 = (float)local_f8;
          }
          local_54 = (uint)(longlong)ROUND((((float10)iVar5 * (fVar8 - fVar7)) / param_6) * 65536.0);
          local_f0 = local_54;
        }
        if (local_f8 < W_y1) {
          iVar11 = W_y1 - local_f8;
          local_f8 = W_y1;
          local_54 = (uint)(longlong)ROUND(((float)(iVar11 * iVar5) / param_6) * 65536.0);
          local_f0 = local_f0 + local_54;
        }
        iVar11 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar7 + param_6) - 0.5));
        if (W_y2 < iVar11) {
          iVar11 = W_y2;
        }
        if (iVar11 - local_f8 != -1 && -1 < (iVar11 - local_f8) + 1) {
          local_100 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
          fVar7 = (float)local_100;
          if (fVar6 <= fVar7) {
            local_f4 = 0;
          }
          else {
            if ((float)local_100 < fVar6 - 0.5) {
              local_100 = local_100 + 1;
              fVar7 = (float)local_100;
            }
            local_54 = (uint)(longlong)ROUND((((fVar7 - fVar6) * (float10)iVar4) / param_5) * 65536.0)
            ;
            local_f4 = local_54;
          }
          if (fVar6 < (float)W_x1) {
            iVar12 = W_x1 - local_100;
            local_100 = W_x1;
            local_144 = (int)(longlong)ROUND(((float)(iVar12 * iVar4) / param_5) * 65536.0);
            local_f4 = local_f4 + local_144;
          }
          iVar12 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_5) - 0.5));
          if (W_x2 < iVar12) {
            iVar12 = W_x2;
          }
          local_144 = (int)(longlong)ROUND((float)(iVar4 << 0x10) / param_5);
          iVar2 = (int)GHIDRA_FIST32((float)(iVar5 << 0x10) / param_6);
          for (; ((int)local_f4 < 0 && (local_100 <= iVar12)); local_100 = local_100 + 1) {
            local_f4 = local_f4 + local_144;
          }
          iVar13 = (int)local_f4 >> 0x10;
          if (iVar13 != 0) {
            local_f4 = local_f4 & 0xffff;
            local_104 = iVar13;
          }
          for (; ((int)local_f0 < 0 && (local_f8 <= iVar11)); local_f8 = local_f8 + 1) {
            local_f0 = local_f0 + iVar2;
          }
          iVar13 = (int)local_f0 >> 0x10;
          if (iVar13 != 0) {
            local_f0 = local_f0 & 0xffff;
            local_fc = iVar13;
          }
          iVar12 = (iVar12 - local_100) + 1;
          iVar11 = (iVar11 - local_f8) + 1;
          if ((0 < iVar12) && (0 < iVar11)) {
            iVar13 = SpriteDecompGetAndLockData(param_1,param_2);
            if (iVar13 != 0) {
              iVar14 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              piVar15 = (int *)param_1[5];
              if (piVar15 == (int *)0x0) {
                piVar15 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar9[0xc]);
              }
              else {
                EBPalUpdate(piVar15);
              }
              local_dc = 0;
              if (0 < iVar11) {
                do {
                  pbVar16 = (byte *)(((iVar13 + *(int *)(piVar9[0xb] + -4 +
                                                        ((iVar5 - local_fc) -
                                                        ((int)local_f0 >> 0x10)) * 4) + iVar4) -
                                     local_104) + -1);
                  puVar17 = (ushort *)
                            (iVar14 + *(int *)(*(int *)(iVar10 + 0x2c) + (local_f8 + local_dc) * 4)
                            + local_100 * 2);
                  uVar22 = local_f4;
                  for (iVar3 = iVar12; iVar3 != 0; iVar3 = iVar3 + -1) {
                    if (*pbVar16 != 0) {
                      uVar21 = (uint)*(ushort *)((int)piVar15 + (uint)*pbVar16 * 2 + 0x5c);
                      uVar18 = (uint)*puVar17;
                      uVar23 = (uVar18 & 0xf800) + (uVar21 & 0xf800);
                      if (0xf800 < uVar23) {
                        uVar23 = 0xf800;
                      }
                      uVar1 = (uVar18 & 0x7e0) + (uVar21 & 0x7e0);
                      uVar19 = (ushort)uVar1;
                      if (0x7e0 < uVar1) {
                        uVar19 = 0x7e0;
                      }
                      uVar21 = (uVar21 & 0x1f) + (uVar18 & 0x1f);
                      uVar20 = (ushort)uVar21;
                      if (0x1f < uVar21) {
                        uVar20 = 0x1f;
                      }
                      *puVar17 = (ushort)uVar23 | uVar19 | uVar20;
                    }
                    uVar23 = uVar22 + local_144;
                    uVar22 = uVar23 & 0xffff;
                    puVar17 = puVar17 + 1;
                    pbVar16 = pbVar16 + -(uVar23 >> 0x10);
                  }
                  local_f0 = local_f0 + iVar2;
                  local_dc = local_dc + 1;
                } while (local_dc < iVar11);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirHV8to16(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
    }
  }
  return;
}

/* W_ScaleSpriteTransAdd8to16_B @ 0x08067b30, 4291 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x350-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAdd8to16_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  ushort uVar8;
  ushort uVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  byte *pbVar17;
  uint uVar18;
  ushort *puVar19;
  uint *puVar20;
  uint uVar21;
  uint uVar22;
  unsigned char ghidra_frame[0x350] __attribute__((aligned(16)));
#define local_344 (*(int *)(ghidra_frame + 0xc))
#define local_308 (*(ushort **)(ghidra_frame + 0x48))
#define local_300 (*(int *)(ghidra_frame + 0x50))
#define local_2fc (*(int *)(ghidra_frame + 0x54))
#define local_2f8 (*(int *)(ghidra_frame + 0x58))
#define local_2f4 (*(int *)(ghidra_frame + 0x5c))
#define local_2f0 (*(uint *)(ghidra_frame + 0x60))
#define local_2ec (*(uint *)(ghidra_frame + 0x64))
#define local_2d8 (*(int *)(ghidra_frame + 0x78))
#define local_2d4 (*(int *)(ghidra_frame + 0x7c))
#define local_254 (*(uint *)(ghidra_frame + 0xfc))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x134))
  
  piVar10 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar11 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_2f8 = 0;
  local_300 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    if ((param_7 == 0x100) && (param_8 == 0)) {
      W_ScaleSprite8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 == 0x100) && (param_8 == 0x100)) {
      W_ScaleSpriteTransAdd8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 != 0) || (param_8 != 0x100)) {
      iVar3 = *piVar10;
      iVar14 = piVar10[1];
      if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar14 - param_6))) {
        fVar5 = param_3 - ((float10)piVar10[2] * param_5) / (float10)iVar3;
        fVar6 = param_4 - ((float10)piVar10[3] * param_6) / (float10)iVar14;
        if ((fVar6 <= (float)W_y2) &&
           ((((float)W_y1 < (fVar6 + param_6) - 0.5 && (fVar5 <= (float)W_x2)) &&
            ((float)W_x1 < (fVar5 + param_5) - 0.5)))) {
          local_2f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
          fVar7 = (float)local_2f4;
          if (fVar6 <= fVar7) {
            local_2ec = 0;
          }
          else {
            if ((float)local_2f4 < fVar6 - 0.5) {
              local_2f4 = local_2f4 + 1;
              fVar7 = (float)local_2f4;
            }
            local_254 = (uint)(longlong)
                              ROUND((((float10)iVar14 * (fVar7 - fVar6)) / param_6) * 65536.0);
            local_2ec = local_254;
          }
          if (local_2f4 < W_y1) {
            iVar12 = W_y1 - local_2f4;
            local_2f4 = W_y1;
            local_254 = (uint)(longlong)ROUND(((float)(iVar12 * iVar14) / param_6) * 65536.0);
            local_2ec = local_2ec + local_254;
          }
          iVar12 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_6) - 0.5));
          if (W_y2 < iVar12) {
            iVar12 = W_y2;
          }
          if (iVar12 - local_2f4 != -1 && -1 < (iVar12 - local_2f4) + 1) {
            local_2fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar5));
            fVar6 = (float)local_2fc;
            if (fVar5 <= fVar6) {
              local_2f0 = 0;
            }
            else {
              if ((float)local_2fc < fVar5 - 0.5) {
                local_2fc = local_2fc + 1;
                fVar6 = (float)local_2fc;
              }
              local_254 = (uint)(longlong)
                                ROUND((((fVar6 - fVar5) * (float10)iVar3) / param_5) * 65536.0);
              local_2f0 = local_254;
            }
            if (fVar5 < (float)W_x1) {
              iVar13 = W_x1 - local_2fc;
              local_2fc = W_x1;
              local_344 = (int)(longlong)ROUND(((float)(iVar13 * iVar3) / param_5) * 65536.0);
              local_2f0 = local_2f0 + local_344;
            }
            iVar13 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar5 + param_5) - 0.5));
            if (W_x2 < iVar13) {
              iVar13 = W_x2;
            }
            local_344 = (int)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
            iVar3 = (int)GHIDRA_FIST32((float)(iVar14 << 0x10) / param_6);
            for (; ((int)local_2f0 < 0 && (local_2fc <= iVar13)); local_2fc = local_2fc + 1) {
              local_2f0 = local_2f0 + local_344;
            }
            iVar14 = (int)local_2f0 >> 0x10;
            if (iVar14 != 0) {
              local_2f0 = local_2f0 & 0xffff;
              local_300 = iVar14;
            }
            for (; ((int)local_2ec < 0 && (local_2f4 <= iVar12)); local_2f4 = local_2f4 + 1) {
              local_2ec = local_2ec + iVar3;
            }
            iVar14 = (int)local_2ec >> 0x10;
            if (iVar14 != 0) {
              local_2ec = local_2ec & 0xffff;
              local_2f8 = iVar14;
            }
            iVar14 = (iVar13 - local_2fc) + 1;
            iVar12 = (iVar12 - local_2f4) + 1;
            if ((0 < iVar14) && (0 < iVar12)) {
              local_2fc = local_2fc * 2;
              iVar13 = SpriteDecompGetAndLockData(param_1,param_2);
              if (iVar13 != 0) {
                iVar15 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                piVar16 = (int *)param_1[5];
                if (piVar16 == (int *)0x0) {
                  piVar16 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar10[0xc]);
                }
                else {
                  EBPalUpdate(piVar16);
                }
                puVar19 = (ushort *)(piVar16 + 0x17);
                local_308 = puVar19;
                if (param_7 != 0x100) {
                  local_308 = local_21c;
                  if (param_7 == 0) {
                    memset(local_21c,0,piVar10[5] * 2);
                  }
                  else if (param_7 == 0x80) {
                    local_2d4 = 1;
                    iVar2 = piVar10[5];
                    if (1 < iVar2) {
                      do {
                        local_21c[local_2d4] = puVar19[local_2d4] >> 1 & 0xfbef;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                  else {
                    local_2d4 = 1;
                    iVar2 = piVar10[5];
                    if (1 < iVar2) {
                      do {
                        uVar22 = (uint)puVar19[local_2d4];
                        local_21c[local_2d4] =
                             (ushort)((uVar22 & 0xf800) * param_7 >> 8) & 0xf800 |
                             (ushort)((uVar22 & 0x7e0) * param_7 >> 8) & 0x7e0 |
                             (ushort)((uVar22 & 0x1f) * param_7 >> 8) & 0x1f;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                }
                if (param_8 == 0) {
                  local_2d8 = 0;
                  if (0 < iVar12) {
                    do {
                      pbVar17 = (byte *)(iVar13 + *(int *)(piVar10[0xb] +
                                                          (((int)local_2ec >> 0x10) + local_2f8) * 4
                                                          ) + local_300);
                      puVar19 = (ushort *)
                                (local_2fc +
                                iVar15 + *(int *)(*(int *)(iVar11 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar22 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar17 != 0) {
                          *puVar19 = local_308[*pbVar17];
                        }
                        uVar21 = uVar22 + local_344;
                        puVar19 = puVar19 + 1;
                        uVar22 = uVar21 & 0xffff;
                        pbVar17 = pbVar17 + (uVar21 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar12);
                  }
                }
                else if ((param_8 + param_7 < 0x101) && (param_8 == 0x80)) {
                  local_2d8 = 0;
                  if (0 < iVar12) {
                    do {
                      pbVar17 = (byte *)(iVar13 + *(int *)(piVar10[0xb] +
                                                          (((int)local_2ec >> 0x10) + local_2f8) * 4
                                                          ) + local_300);
                      puVar19 = (ushort *)
                                (local_2fc +
                                iVar15 + *(int *)(*(int *)(iVar11 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar22 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar17 != 0) {
                          uVar9 = local_308[*pbVar17];
                          uVar8 = (ushort)*(undefined4 *)puVar19 >> 1;
                          *puVar19 = (uVar8 & 0x3e0) + (uVar9 & 0x7e0) |
                                     (uVar8 & 0x7800) + (uVar9 & 0xf800) |
                                     (uVar8 & 0xf) + (uVar9 & 0x1f);
                        }
                        uVar21 = uVar22 + local_344;
                        puVar19 = puVar19 + 1;
                        uVar22 = uVar21 & 0xffff;
                        pbVar17 = pbVar17 + (uVar21 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar12);
                  }
                }
                else if (param_8 + param_7 < 0x101) {
                  local_2d8 = 0;
                  if (0 < iVar12) {
                    do {
                      pbVar17 = (byte *)(iVar13 + *(int *)(piVar10[0xb] +
                                                          (((int)local_2ec >> 0x10) + local_2f8) * 4
                                                          ) + local_300);
                      puVar20 = (uint *)(local_2fc +
                                        iVar15 + *(int *)(*(int *)(iVar11 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar22 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar17 != 0) {
                          uVar9 = local_308[*pbVar17];
                          uVar21 = *puVar20;
                          *(ushort *)puVar20 =
                               ((ushort)((uVar21 & 0x7e0) * param_8 >> 8) & 0x7e0) + (uVar9 & 0x7e0)
                               | ((ushort)((uVar21 & 0xf800) * param_8 >> 8) & 0xf800) +
                                 (uVar9 & 0xf800) |
                               ((ushort)((uVar21 & 0x1f) * param_8 >> 8) & 0x1f) + (uVar9 & 0x1f);
                        }
                        uVar21 = uVar22 + local_344;
                        puVar20 = (uint *)((int)puVar20 + 2);
                        uVar22 = uVar21 & 0xffff;
                        pbVar17 = pbVar17 + (uVar21 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar12);
                  }
                }
                else if (param_8 == 0x80) {
                  local_2d8 = 0;
                  if (0 < iVar12) {
                    do {
                      pbVar17 = (byte *)(iVar13 + *(int *)(piVar10[0xb] +
                                                          (((int)local_2ec >> 0x10) + local_2f8) * 4
                                                          ) + local_300);
                      puVar20 = (uint *)(local_2fc +
                                        iVar15 + *(int *)(*(int *)(iVar11 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar22 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar17 != 0) {
                          uVar18 = (uint)local_308[*pbVar17];
                          uVar4 = *puVar20 >> 1;
                          uVar21 = (uVar4 & 0x7800) + (uVar18 & 0xf800);
                          if (0xf800 < uVar21) {
                            uVar21 = 0xf800;
                          }
                          uVar1 = (uVar4 & 0x3e0) + (uVar18 & 0x7e0);
                          uVar9 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar9 = 0x7e0;
                          }
                          uVar4 = (uVar4 & 0xf) + (uVar18 & 0x1f);
                          uVar8 = (ushort)uVar4;
                          if (0x1f < uVar4) {
                            uVar8 = 0x1f;
                          }
                          *(ushort *)puVar20 = uVar9 | (ushort)uVar21 | uVar8;
                        }
                        uVar21 = uVar22 + local_344;
                        puVar20 = (uint *)((int)puVar20 + 2);
                        uVar22 = uVar21 & 0xffff;
                        pbVar17 = pbVar17 + (uVar21 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar12);
                  }
                }
                else {
                  local_2d8 = 0;
                  if (0 < iVar12) {
                    do {
                      pbVar17 = (byte *)(iVar13 + *(int *)(piVar10[0xb] +
                                                          (((int)local_2ec >> 0x10) + local_2f8) * 4
                                                          ) + local_300);
                      puVar20 = (uint *)(local_2fc +
                                        iVar15 + *(int *)(*(int *)(iVar11 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar22 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar17 != 0) {
                          uVar18 = (uint)local_308[*pbVar17];
                          uVar4 = *puVar20;
                          uVar21 = ((uVar4 & 0xf800) * param_8 >> 8 & 0xf800) + (uVar18 & 0xf800);
                          if (0xf800 < uVar21) {
                            uVar21 = 0xf800;
                          }
                          uVar1 = ((uVar4 & 0x7e0) * param_8 >> 8 & 0x7e0) + (uVar18 & 0x7e0);
                          uVar9 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar9 = 0x7e0;
                          }
                          uVar4 = ((uVar4 & 0x1f) * param_8 >> 8 & 0x1f) + (uVar18 & 0x1f);
                          uVar8 = (ushort)uVar4;
                          if (0x1f < uVar4) {
                            uVar8 = 0x1f;
                          }
                          *(ushort *)puVar20 = uVar9 | (ushort)uVar21 | uVar8;
                        }
                        uVar21 = uVar22 + local_344;
                        puVar20 = (uint *)((int)puVar20 + 2);
                        uVar22 = uVar21 & 0xffff;
                        pbVar17 = pbVar17 + (uVar21 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar12);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAdd8to16_B
                  (param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4),param_7,param_8);
      }
    }
  }
  return;
}
#undef local_344
#undef local_308
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2f0
#undef local_2ec
#undef local_2d8
#undef local_2d4
#undef local_254
#undef local_21c

/* W_ScaleSpriteTransAddMirH8to16_B @ 0x08068c00, 4331 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x350-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirH8to16_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  ushort uVar9;
  ushort uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  byte *pbVar18;
  uint uVar19;
  ushort *puVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  unsigned char ghidra_frame[0x350] __attribute__((aligned(16)));
#define local_344 (*(int *)(ghidra_frame + 0xc))
#define local_308 (*(ushort **)(ghidra_frame + 0x48))
#define local_300 (*(int *)(ghidra_frame + 0x50))
#define local_2fc (*(int *)(ghidra_frame + 0x54))
#define local_2f8 (*(int *)(ghidra_frame + 0x58))
#define local_2f4 (*(int *)(ghidra_frame + 0x5c))
#define local_2f0 (*(uint *)(ghidra_frame + 0x60))
#define local_2ec (*(uint *)(ghidra_frame + 0x64))
#define local_2d8 (*(int *)(ghidra_frame + 0x78))
#define local_2d4 (*(int *)(ghidra_frame + 0x7c))
#define local_254 (*(uint *)(ghidra_frame + 0xfc))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x134))
  
  piVar11 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar12 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_2f8 = 0;
  local_300 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    if ((param_7 == 0x100) && (param_8 == 0)) {
      W_ScaleSpriteMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 == 0x100) && (param_8 == 0x100)) {
      W_ScaleSpriteTransAddMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 != 0) || (param_8 != 0x100)) {
      iVar3 = *piVar11;
      iVar4 = piVar11[1];
      if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar4 - param_6))) {
        fVar6 = param_3 - ((float)((iVar3 - piVar11[2]) + -1) * param_5) / (float10)iVar3;
        fVar7 = param_4 - ((float10)piVar11[3] * param_6) / (float10)iVar4;
        if ((fVar7 <= (float)W_y2) &&
           ((((float)W_y1 < (fVar7 + param_6) - 0.5 && (fVar6 <= (float)W_x2)) &&
            ((float)W_x1 < (fVar6 + param_5) - 0.5)))) {
          local_2f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar7));
          fVar8 = (float)local_2f4;
          if (fVar7 <= fVar8) {
            local_2ec = 0;
          }
          else {
            if ((float)local_2f4 < fVar7 - 0.5) {
              local_2f4 = local_2f4 + 1;
              fVar8 = (float)local_2f4;
            }
            local_254 = (uint)(longlong)
                              ROUND((((float10)iVar4 * (fVar8 - fVar7)) / param_6) * 65536.0);
            local_2ec = local_254;
          }
          if (local_2f4 < W_y1) {
            iVar13 = W_y1 - local_2f4;
            local_2f4 = W_y1;
            local_254 = (uint)(longlong)ROUND(((float)(iVar13 * iVar4) / param_6) * 65536.0);
            local_2ec = local_2ec + local_254;
          }
          iVar13 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar7 + param_6) - 0.5));
          if (W_y2 < iVar13) {
            iVar13 = W_y2;
          }
          if (iVar13 - local_2f4 != -1 && -1 < (iVar13 - local_2f4) + 1) {
            local_2fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
            fVar7 = (float)local_2fc;
            if (fVar6 <= fVar7) {
              local_2f0 = 0;
            }
            else {
              if ((float)local_2fc < fVar6 - 0.5) {
                local_2fc = local_2fc + 1;
                fVar7 = (float)local_2fc;
              }
              local_254 = (uint)(longlong)
                                ROUND((((fVar7 - fVar6) * (float10)iVar3) / param_5) * 65536.0);
              local_2f0 = local_254;
            }
            if (fVar6 < (float)W_x1) {
              iVar14 = W_x1 - local_2fc;
              local_2fc = W_x1;
              local_344 = (int)(longlong)ROUND(((float)(iVar14 * iVar3) / param_5) * 65536.0);
              local_2f0 = local_2f0 + local_344;
            }
            iVar14 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_5) - 0.5));
            if (W_x2 < iVar14) {
              iVar14 = W_x2;
            }
            local_344 = (int)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
            iVar4 = (int)GHIDRA_FIST32((float)(iVar4 << 0x10) / param_6);
            for (; ((int)local_2f0 < 0 && (local_2fc <= iVar14)); local_2fc = local_2fc + 1) {
              local_2f0 = local_2f0 + local_344;
            }
            iVar15 = (int)local_2f0 >> 0x10;
            if (iVar15 != 0) {
              local_2f0 = local_2f0 & 0xffff;
              local_300 = iVar15;
            }
            for (; ((int)local_2ec < 0 && (local_2f4 <= iVar13)); local_2f4 = local_2f4 + 1) {
              local_2ec = local_2ec + iVar4;
            }
            iVar15 = (int)local_2ec >> 0x10;
            if (iVar15 != 0) {
              local_2ec = local_2ec & 0xffff;
              local_2f8 = iVar15;
            }
            iVar14 = (iVar14 - local_2fc) + 1;
            iVar13 = (iVar13 - local_2f4) + 1;
            if ((0 < iVar14) && (0 < iVar13)) {
              local_2fc = local_2fc * 2;
              iVar15 = SpriteDecompGetAndLockData(param_1,param_2);
              if (iVar15 != 0) {
                iVar16 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                piVar17 = (int *)param_1[5];
                if (piVar17 == (int *)0x0) {
                  piVar17 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar11[0xc]);
                }
                else {
                  EBPalUpdate(piVar17);
                }
                puVar20 = (ushort *)(piVar17 + 0x17);
                local_308 = puVar20;
                if (param_7 != 0x100) {
                  local_308 = local_21c;
                  if (param_7 == 0) {
                    memset(local_21c,0,piVar11[5] * 2);
                  }
                  else if (param_7 == 0x80) {
                    local_2d4 = 1;
                    iVar2 = piVar11[5];
                    if (1 < iVar2) {
                      do {
                        local_21c[local_2d4] = puVar20[local_2d4] >> 1 & 0xfbef;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                  else {
                    local_2d4 = 1;
                    iVar2 = piVar11[5];
                    if (1 < iVar2) {
                      do {
                        uVar23 = (uint)puVar20[local_2d4];
                        local_21c[local_2d4] =
                             (ushort)((uVar23 & 0xf800) * param_7 >> 8) & 0xf800 |
                             (ushort)((uVar23 & 0x7e0) * param_7 >> 8) & 0x7e0 |
                             (ushort)((uVar23 & 0x1f) * param_7 >> 8) & 0x1f;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                }
                if (param_8 == 0) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(((iVar15 + *(int *)(piVar11[0xb] +
                                                            (((int)local_2ec >> 0x10) + local_2f8) *
                                                            4) + iVar3) - local_300) + -1);
                      puVar20 = (ushort *)
                                (local_2fc +
                                iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          *puVar20 = local_308[*pbVar18];
                        }
                        uVar22 = uVar23 + local_344;
                        puVar20 = puVar20 + 1;
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + -(uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar4;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if ((param_8 + param_7 < 0x101) && (param_8 == 0x80)) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(((iVar15 + *(int *)(piVar11[0xb] +
                                                            (((int)local_2ec >> 0x10) + local_2f8) *
                                                            4) + iVar3) - local_300) + -1);
                      puVar20 = (ushort *)
                                (local_2fc +
                                iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar10 = local_308[*pbVar18];
                          uVar9 = (ushort)*(undefined4 *)puVar20 >> 1;
                          *puVar20 = (uVar9 & 0x3e0) + (uVar10 & 0x7e0) |
                                     (uVar9 & 0x7800) + (uVar10 & 0xf800) |
                                     (uVar9 & 0xf) + (uVar10 & 0x1f);
                        }
                        uVar22 = uVar23 + local_344;
                        puVar20 = puVar20 + 1;
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + -(uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar4;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if (param_8 + param_7 < 0x101) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(((iVar15 + *(int *)(piVar11[0xb] +
                                                            (((int)local_2ec >> 0x10) + local_2f8) *
                                                            4) + iVar3) - local_300) + -1);
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar10 = local_308[*pbVar18];
                          uVar22 = *puVar21;
                          *(ushort *)puVar21 =
                               ((ushort)((uVar22 & 0x7e0) * param_8 >> 8) & 0x7e0) +
                               (uVar10 & 0x7e0) |
                               ((ushort)((uVar22 & 0xf800) * param_8 >> 8) & 0xf800) +
                               (uVar10 & 0xf800) |
                               ((ushort)((uVar22 & 0x1f) * param_8 >> 8) & 0x1f) + (uVar10 & 0x1f);
                        }
                        uVar22 = uVar23 + local_344;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + -(uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar4;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if (param_8 == 0x80) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(((iVar15 + *(int *)(piVar11[0xb] +
                                                            (((int)local_2ec >> 0x10) + local_2f8) *
                                                            4) + iVar3) - local_300) + -1);
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar19 = (uint)local_308[*pbVar18];
                          uVar5 = *puVar21 >> 1;
                          uVar22 = (uVar5 & 0x7800) + (uVar19 & 0xf800);
                          if (0xf800 < uVar22) {
                            uVar22 = 0xf800;
                          }
                          uVar1 = (uVar5 & 0x3e0) + (uVar19 & 0x7e0);
                          uVar10 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar10 = 0x7e0;
                          }
                          uVar5 = (uVar5 & 0xf) + (uVar19 & 0x1f);
                          uVar9 = (ushort)uVar5;
                          if (0x1f < uVar5) {
                            uVar9 = 0x1f;
                          }
                          *(ushort *)puVar21 = uVar10 | (ushort)uVar22 | uVar9;
                        }
                        uVar22 = uVar23 + local_344;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + -(uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar4;
                    } while (local_2d8 < iVar13);
                  }
                }
                else {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(((iVar15 + *(int *)(piVar11[0xb] +
                                                            (((int)local_2ec >> 0x10) + local_2f8) *
                                                            4) + iVar3) - local_300) + -1);
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar19 = (uint)local_308[*pbVar18];
                          uVar5 = *puVar21;
                          uVar22 = ((uVar5 & 0xf800) * param_8 >> 8 & 0xf800) + (uVar19 & 0xf800);
                          if (0xf800 < uVar22) {
                            uVar22 = 0xf800;
                          }
                          uVar1 = ((uVar5 & 0x7e0) * param_8 >> 8 & 0x7e0) + (uVar19 & 0x7e0);
                          uVar10 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar10 = 0x7e0;
                          }
                          uVar5 = ((uVar5 & 0x1f) * param_8 >> 8 & 0x1f) + (uVar19 & 0x1f);
                          uVar9 = (ushort)uVar5;
                          if (0x1f < uVar5) {
                            uVar9 = 0x1f;
                          }
                          *(ushort *)puVar21 = uVar10 | (ushort)uVar22 | uVar9;
                        }
                        uVar22 = uVar23 + local_344;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + -(uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar4;
                    } while (local_2d8 < iVar13);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirH8to16_B
                  (param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4),param_7,param_8);
      }
    }
  }
  return;
}
#undef local_344
#undef local_308
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2f0
#undef local_2ec
#undef local_2d8
#undef local_2d4
#undef local_254
#undef local_21c

/* W_ScaleSpriteTransAddMirV8to16_B @ 0x08069cf0, 4592 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x360-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirV8to16_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  ushort uVar9;
  ushort uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  byte *pbVar18;
  uint uVar19;
  ushort *puVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  unsigned char ghidra_frame[0x360] __attribute__((aligned(16)));
#define local_354 (*(int *)(ghidra_frame + 0xc))
#define local_308 (*(ushort **)(ghidra_frame + 0x58))
#define local_300 (*(int *)(ghidra_frame + 0x60))
#define local_2fc (*(int *)(ghidra_frame + 0x64))
#define local_2f8 (*(int *)(ghidra_frame + 0x68))
#define local_2f4 (*(int *)(ghidra_frame + 0x6c))
#define local_2f0 (*(uint *)(ghidra_frame + 0x70))
#define local_2ec (*(uint *)(ghidra_frame + 0x74))
#define local_2d8 (*(int *)(ghidra_frame + 0x88))
#define local_2d4 (*(int *)(ghidra_frame + 0x8c))
#define local_254 (*(uint *)(ghidra_frame + 0x10c))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x144))
  
  piVar11 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar12 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_2f8 = 0;
  local_300 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    if ((param_7 == 0x100) && (param_8 == 0)) {
      W_ScaleSpriteMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 == 0x100) && (param_8 == 0x100)) {
      W_ScaleSpriteTransAddMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 != 0) || (param_8 != 0x100)) {
      iVar3 = *piVar11;
      iVar4 = piVar11[1];
      if ((((double)0.001) <= ABS((float10)iVar3 - param_5)) || (((double)0.001) <= ABS((float10)iVar4 - param_6))) {
        fVar6 = param_3 - ((float10)piVar11[2] * param_5) / (float10)iVar3;
        fVar7 = param_4 - ((float)((iVar4 - piVar11[3]) + -1) * param_6) / (float10)iVar4;
        if ((fVar7 <= (float)W_y2) &&
           ((((float)W_y1 < (fVar7 + param_6) - 0.5 && (fVar6 <= (float)W_x2)) &&
            ((float)W_x1 < (fVar6 + param_5) - 0.5)))) {
          local_2f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar7));
          fVar8 = (float)local_2f4;
          if (fVar7 <= fVar8) {
            local_2ec = 0;
          }
          else {
            if ((float)local_2f4 < fVar7 - 0.5) {
              local_2f4 = local_2f4 + 1;
              fVar8 = (float)local_2f4;
            }
            local_254 = (uint)(longlong)
                              ROUND((((float10)iVar4 * (fVar8 - fVar7)) / param_6) * 65536.0);
            local_2ec = local_254;
          }
          if (local_2f4 < W_y1) {
            iVar13 = W_y1 - local_2f4;
            local_2f4 = W_y1;
            local_254 = (uint)(longlong)ROUND(((float)(iVar13 * iVar4) / param_6) * 65536.0);
            local_2ec = local_2ec + local_254;
          }
          iVar13 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar7 + param_6) - 0.5));
          if (W_y2 < iVar13) {
            iVar13 = W_y2;
          }
          if (iVar13 - local_2f4 != -1 && -1 < (iVar13 - local_2f4) + 1) {
            local_2fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar6));
            fVar7 = (float)local_2fc;
            if (fVar6 <= fVar7) {
              local_2f0 = 0;
            }
            else {
              if ((float)local_2fc < fVar6 - 0.5) {
                local_2fc = local_2fc + 1;
                fVar7 = (float)local_2fc;
              }
              local_254 = (uint)(longlong)
                                ROUND((((fVar7 - fVar6) * (float10)iVar3) / param_5) * 65536.0);
              local_2f0 = local_254;
            }
            if (fVar6 < (float)W_x1) {
              iVar14 = W_x1 - local_2fc;
              local_2fc = W_x1;
              local_354 = (int)(longlong)ROUND(((float)(iVar14 * iVar3) / param_5) * 65536.0);
              local_2f0 = local_2f0 + local_354;
            }
            iVar14 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar6 + param_5) - 0.5));
            if (W_x2 < iVar14) {
              iVar14 = W_x2;
            }
            local_254 = (uint)(longlong)ROUND((float)(iVar3 << 0x10) / param_5);
            iVar3 = (int)GHIDRA_FIST32((float)(iVar4 << 0x10) / param_6);
            for (; ((int)local_2f0 < 0 && (local_2fc <= iVar14)); local_2fc = local_2fc + 1) {
              local_2f0 = local_2f0 + local_254;
            }
            iVar15 = (int)local_2f0 >> 0x10;
            if (iVar15 != 0) {
              local_2f0 = local_2f0 & 0xffff;
              local_300 = iVar15;
            }
            for (; ((int)local_2ec < 0 && (local_2f4 <= iVar13)); local_2f4 = local_2f4 + 1) {
              local_2ec = local_2ec + iVar3;
            }
            iVar15 = (int)local_2ec >> 0x10;
            if (iVar15 != 0) {
              local_2ec = local_2ec & 0xffff;
              local_2f8 = iVar15;
            }
            iVar14 = (iVar14 - local_2fc) + 1;
            iVar13 = (iVar13 - local_2f4) + 1;
            if ((0 < iVar14) && (0 < iVar13)) {
              local_2fc = local_2fc * 2;
              iVar15 = SpriteDecompGetAndLockData(param_1,param_2);
              if (iVar15 != 0) {
                iVar16 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                piVar17 = (int *)param_1[5];
                if (piVar17 == (int *)0x0) {
                  piVar17 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar11[0xc]);
                }
                else {
                  EBPalUpdate(piVar17);
                }
                puVar20 = (ushort *)(piVar17 + 0x17);
                local_308 = puVar20;
                if (param_7 != 0x100) {
                  local_308 = local_21c;
                  if (param_7 == 0) {
                    memset(local_21c,0,piVar11[5] * 2);
                  }
                  else if (param_7 == 0x80) {
                    local_2d4 = 1;
                    iVar2 = piVar11[5];
                    if (1 < iVar2) {
                      do {
                        local_21c[local_2d4] = puVar20[local_2d4] >> 1 & 0xfbef;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                  else {
                    local_2d4 = 1;
                    iVar2 = piVar11[5];
                    if (1 < iVar2) {
                      do {
                        uVar23 = (uint)puVar20[local_2d4];
                        local_21c[local_2d4] =
                             (ushort)((uVar23 & 0xf800) * param_7 >> 8) & 0xf800 |
                             (ushort)((uVar23 & 0x7e0) * param_7 >> 8) & 0x7e0 |
                             (ushort)((uVar23 & 0x1f) * param_7 >> 8) & 0x1f;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar2);
                    }
                  }
                }
                if (param_8 == 0) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(iVar15 + *(int *)(piVar11[0xb] + -4 +
                                                          ((iVar4 - local_2f8) -
                                                          ((int)local_2ec >> 0x10)) * 4) + local_300
                                        );
                      puVar20 = (ushort *)
                                (local_2fc +
                                iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          *puVar20 = local_308[*pbVar18];
                        }
                        uVar22 = uVar23 + local_254;
                        puVar20 = puVar20 + 1;
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + (uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if ((param_8 + param_7 < 0x101) && (param_8 == 0x80)) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(iVar15 + *(int *)(piVar11[0xb] + -4 +
                                                          ((iVar4 - local_2f8) -
                                                          ((int)local_2ec >> 0x10)) * 4) + local_300
                                        );
                      puVar20 = (ushort *)
                                (local_2fc +
                                iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar10 = local_308[*pbVar18];
                          uVar9 = (ushort)*(undefined4 *)puVar20 >> 1;
                          *puVar20 = (uVar9 & 0x3e0) + (uVar10 & 0x7e0) |
                                     (uVar9 & 0x7800) + (uVar10 & 0xf800) |
                                     (uVar9 & 0xf) + (uVar10 & 0x1f);
                        }
                        uVar22 = uVar23 + local_254;
                        puVar20 = puVar20 + 1;
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + (uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if (param_8 + param_7 < 0x101) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(iVar15 + *(int *)(piVar11[0xb] + -4 +
                                                          ((iVar4 - local_2f8) -
                                                          ((int)local_2ec >> 0x10)) * 4) + local_300
                                        );
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar10 = local_308[*pbVar18];
                          uVar22 = *puVar21;
                          *(ushort *)puVar21 =
                               ((ushort)((uVar22 & 0x7e0) * param_8 >> 8) & 0x7e0) +
                               (uVar10 & 0x7e0) |
                               ((ushort)((uVar22 & 0xf800) * param_8 >> 8) & 0xf800) +
                               (uVar10 & 0xf800) |
                               ((ushort)((uVar22 & 0x1f) * param_8 >> 8) & 0x1f) + (uVar10 & 0x1f);
                        }
                        uVar22 = uVar23 + local_254;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + (uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar13);
                  }
                }
                else if (param_8 == 0x80) {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(iVar15 + *(int *)(piVar11[0xb] + -4 +
                                                          ((iVar4 - local_2f8) -
                                                          ((int)local_2ec >> 0x10)) * 4) + local_300
                                        );
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar19 = (uint)local_308[*pbVar18];
                          uVar5 = *puVar21 >> 1;
                          uVar22 = (uVar5 & 0x7800) + (uVar19 & 0xf800);
                          if (0xf800 < uVar22) {
                            uVar22 = 0xf800;
                          }
                          uVar1 = (uVar5 & 0x3e0) + (uVar19 & 0x7e0);
                          uVar10 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar10 = 0x7e0;
                          }
                          uVar5 = (uVar5 & 0xf) + (uVar19 & 0x1f);
                          uVar9 = (ushort)uVar5;
                          if (0x1f < uVar5) {
                            uVar9 = 0x1f;
                          }
                          *(ushort *)puVar21 = uVar10 | (ushort)uVar22 | uVar9;
                        }
                        uVar22 = uVar23 + local_254;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + (uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar13);
                  }
                }
                else {
                  local_2d8 = 0;
                  if (0 < iVar13) {
                    do {
                      pbVar18 = (byte *)(iVar15 + *(int *)(piVar11[0xb] + -4 +
                                                          ((iVar4 - local_2f8) -
                                                          ((int)local_2ec >> 0x10)) * 4) + local_300
                                        );
                      puVar21 = (uint *)(local_2fc +
                                        iVar16 + *(int *)(*(int *)(iVar12 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar23 = local_2f0;
                      for (iVar2 = iVar14; iVar2 != 0; iVar2 = iVar2 + -1) {
                        if (*pbVar18 != 0) {
                          uVar19 = (uint)local_308[*pbVar18];
                          uVar5 = *puVar21;
                          uVar22 = ((uVar5 & 0xf800) * param_8 >> 8 & 0xf800) + (uVar19 & 0xf800);
                          if (0xf800 < uVar22) {
                            uVar22 = 0xf800;
                          }
                          uVar1 = ((uVar5 & 0x7e0) * param_8 >> 8 & 0x7e0) + (uVar19 & 0x7e0);
                          uVar10 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar10 = 0x7e0;
                          }
                          uVar5 = ((uVar5 & 0x1f) * param_8 >> 8 & 0x1f) + (uVar19 & 0x1f);
                          uVar9 = (ushort)uVar5;
                          if (0x1f < uVar5) {
                            uVar9 = 0x1f;
                          }
                          *(ushort *)puVar21 = uVar10 | (ushort)uVar22 | uVar9;
                        }
                        uVar22 = uVar23 + local_254;
                        puVar21 = (uint *)((int)puVar21 + 2);
                        uVar23 = uVar22 & 0xffff;
                        pbVar18 = pbVar18 + (uVar22 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar3;
                    } while (local_2d8 < iVar13);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirV8to16_B
                  (param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4),param_7,param_8);
      }
    }
  }
  return;
}
#undef local_354
#undef local_308
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2f0
#undef local_2ec
#undef local_2d8
#undef local_2d4
#undef local_254
#undef local_21c

/* W_ScaleSpriteTransAddMirHV8to16_B @ 0x0806aee0, 4626 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x360-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void W_ScaleSpriteTransAddMirHV8to16_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  ushort uVar10;
  ushort uVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  byte *pbVar19;
  uint uVar20;
  ushort *puVar21;
  uint *puVar22;
  uint uVar23;
  uint uVar24;
  unsigned char ghidra_frame[0x360] __attribute__((aligned(16)));
#define local_354 (*(int *)(ghidra_frame + 0xc))
#define local_30c (*(ushort **)(ghidra_frame + 0x54))
#define local_300 (*(int *)(ghidra_frame + 0x60))
#define local_2fc (*(int *)(ghidra_frame + 0x64))
#define local_2f8 (*(int *)(ghidra_frame + 0x68))
#define local_2f4 (*(int *)(ghidra_frame + 0x6c))
#define local_2f0 (*(uint *)(ghidra_frame + 0x70))
#define local_2ec (*(uint *)(ghidra_frame + 0x74))
#define local_2d8 (*(int *)(ghidra_frame + 0x88))
#define local_2d4 (*(int *)(ghidra_frame + 0x8c))
#define local_254 (*(uint *)(ghidra_frame + 0x10c))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x144))
  
  piVar12 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar13 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_2f8 = 0;
  local_300 = 0;
  if ((0.0 < param_5) && (0.0 < param_6)) {
    if ((param_7 == 0x100) && (param_8 == 0)) {
      W_ScaleSpriteMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 == 0x100) && (param_8 == 0x100)) {
      W_ScaleSpriteTransAddMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if ((param_7 != 0) || (param_8 != 0x100)) {
      iVar4 = *piVar12;
      iVar5 = piVar12[1];
      if ((((double)0.001) <= ABS((float10)iVar4 - param_5)) || (((double)0.001) <= ABS((float10)iVar5 - param_6))) {
        fVar7 = param_3 - ((float)((iVar4 - piVar12[2]) + -1) * param_5) / (float10)iVar4;
        fVar8 = param_4 - ((float)((iVar5 - piVar12[3]) + -1) * param_6) / (float10)iVar5;
        if ((fVar8 <= (float)W_y2) &&
           ((((float)W_y1 < (fVar8 + param_6) - 0.5 && (fVar7 <= (float)W_x2)) &&
            ((float)W_x1 < (fVar7 + param_5) - 0.5)))) {
          local_2f4 = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar8));
          fVar9 = (float)local_2f4;
          if (fVar8 <= fVar9) {
            local_2ec = 0;
          }
          else {
            if ((float)local_2f4 < fVar8 - 0.5) {
              local_2f4 = local_2f4 + 1;
              fVar9 = (float)local_2f4;
            }
            local_254 = (uint)(longlong)
                              ROUND((((float10)iVar5 * (fVar9 - fVar8)) / param_6) * 65536.0);
            local_2ec = local_254;
          }
          if (local_2f4 < W_y1) {
            iVar14 = W_y1 - local_2f4;
            local_2f4 = W_y1;
            local_254 = (uint)(longlong)ROUND(((float)(iVar14 * iVar5) / param_6) * 65536.0);
            local_2ec = local_2ec + local_254;
          }
          iVar14 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar8 + param_6) - 0.5));
          if (W_y2 < iVar14) {
            iVar14 = W_y2;
          }
          if (iVar14 - local_2f4 != -1 && -1 < (iVar14 - local_2f4) + 1) {
            local_2fc = (int)GHIDRA_FIST32(GHIDRA_FLOOR(fVar7));
            fVar8 = (float)local_2fc;
            if (fVar7 <= fVar8) {
              local_2f0 = 0;
            }
            else {
              if ((float)local_2fc < fVar7 - 0.5) {
                local_2fc = local_2fc + 1;
                fVar8 = (float)local_2fc;
              }
              local_254 = (uint)(longlong)
                                ROUND((((fVar8 - fVar7) * (float10)iVar4) / param_5) * 65536.0);
              local_2f0 = local_254;
            }
            if (fVar7 < (float)W_x1) {
              iVar15 = W_x1 - local_2fc;
              local_2fc = W_x1;
              local_354 = (int)(longlong)ROUND(((float)(iVar15 * iVar4) / param_5) * 65536.0);
              local_2f0 = local_2f0 + local_354;
            }
            iVar15 = (int)GHIDRA_FIST32(GHIDRA_FLOOR((fVar7 + param_5) - 0.5));
            if (W_x2 < iVar15) {
              iVar15 = W_x2;
            }
            local_354 = (int)(longlong)ROUND((float)(iVar4 << 0x10) / param_5);
            iVar2 = (int)GHIDRA_FIST32((float)(iVar5 << 0x10) / param_6);
            for (; ((int)local_2f0 < 0 && (local_2fc <= iVar15)); local_2fc = local_2fc + 1) {
              local_2f0 = local_2f0 + local_354;
            }
            iVar16 = (int)local_2f0 >> 0x10;
            if (iVar16 != 0) {
              local_2f0 = local_2f0 & 0xffff;
              local_300 = iVar16;
            }
            for (; ((int)local_2ec < 0 && (local_2f4 <= iVar14)); local_2f4 = local_2f4 + 1) {
              local_2ec = local_2ec + iVar2;
            }
            iVar16 = (int)local_2ec >> 0x10;
            if (iVar16 != 0) {
              local_2ec = local_2ec & 0xffff;
              local_2f8 = iVar16;
            }
            iVar15 = (iVar15 - local_2fc) + 1;
            iVar14 = (iVar14 - local_2f4) + 1;
            if ((0 < iVar15) && (0 < iVar14)) {
              local_2fc = local_2fc * 2;
              iVar16 = SpriteDecompGetAndLockData(param_1,param_2);
              if (iVar16 != 0) {
                iVar17 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                piVar18 = (int *)param_1[5];
                if (piVar18 == (int *)0x0) {
                  piVar18 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar12[0xc]);
                }
                else {
                  EBPalUpdate(piVar18);
                }
                puVar21 = (ushort *)(piVar18 + 0x17);
                local_30c = puVar21;
                if (param_7 != 0x100) {
                  local_30c = local_21c;
                  if (param_7 == 0) {
                    memset(local_21c,0,piVar12[5] * 2);
                  }
                  else if (param_7 == 0x80) {
                    local_2d4 = 1;
                    iVar3 = piVar12[5];
                    if (1 < iVar3) {
                      do {
                        local_21c[local_2d4] = puVar21[local_2d4] >> 1 & 0xfbef;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar3);
                    }
                  }
                  else {
                    local_2d4 = 1;
                    iVar3 = piVar12[5];
                    if (1 < iVar3) {
                      do {
                        uVar24 = (uint)puVar21[local_2d4];
                        local_21c[local_2d4] =
                             (ushort)((uVar24 & 0xf800) * param_7 >> 8) & 0xf800 |
                             (ushort)((uVar24 & 0x7e0) * param_7 >> 8) & 0x7e0 |
                             (ushort)((uVar24 & 0x1f) * param_7 >> 8) & 0x1f;
                        local_2d4 = local_2d4 + 1;
                      } while (local_2d4 < iVar3);
                    }
                  }
                }
                if (param_8 == 0) {
                  local_2d8 = 0;
                  if (0 < iVar14) {
                    do {
                      pbVar19 = (byte *)(((iVar16 + *(int *)(piVar12[0xb] + -4 +
                                                            ((iVar5 - local_2f8) -
                                                            ((int)local_2ec >> 0x10)) * 4) + iVar4)
                                         - local_300) + -1);
                      puVar21 = (ushort *)
                                (local_2fc +
                                iVar17 + *(int *)(*(int *)(iVar13 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar24 = local_2f0;
                      for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                        if (*pbVar19 != 0) {
                          *puVar21 = local_30c[*pbVar19];
                        }
                        uVar23 = uVar24 + local_354;
                        puVar21 = puVar21 + 1;
                        uVar24 = uVar23 & 0xffff;
                        pbVar19 = pbVar19 + -(uVar23 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar2;
                    } while (local_2d8 < iVar14);
                  }
                }
                else if ((param_8 + param_7 < 0x101) && (param_8 == 0x80)) {
                  local_2d8 = 0;
                  if (0 < iVar14) {
                    do {
                      pbVar19 = (byte *)(((iVar16 + *(int *)(piVar12[0xb] + -4 +
                                                            ((iVar5 - local_2f8) -
                                                            ((int)local_2ec >> 0x10)) * 4) + iVar4)
                                         - local_300) + -1);
                      puVar21 = (ushort *)
                                (local_2fc +
                                iVar17 + *(int *)(*(int *)(iVar13 + 0x2c) +
                                                 (local_2f4 + local_2d8) * 4));
                      uVar24 = local_2f0;
                      for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                        if (*pbVar19 != 0) {
                          uVar11 = local_30c[*pbVar19];
                          uVar10 = (ushort)*(undefined4 *)puVar21 >> 1;
                          *puVar21 = (uVar10 & 0x3e0) + (uVar11 & 0x7e0) |
                                     (uVar10 & 0x7800) + (uVar11 & 0xf800) |
                                     (uVar10 & 0xf) + (uVar11 & 0x1f);
                        }
                        uVar23 = uVar24 + local_354;
                        puVar21 = puVar21 + 1;
                        uVar24 = uVar23 & 0xffff;
                        pbVar19 = pbVar19 + -(uVar23 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar2;
                    } while (local_2d8 < iVar14);
                  }
                }
                else if (param_8 + param_7 < 0x101) {
                  local_2d8 = 0;
                  if (0 < iVar14) {
                    do {
                      pbVar19 = (byte *)(((iVar16 + *(int *)(piVar12[0xb] + -4 +
                                                            ((iVar5 - local_2f8) -
                                                            ((int)local_2ec >> 0x10)) * 4) + iVar4)
                                         - local_300) + -1);
                      puVar22 = (uint *)(local_2fc +
                                        iVar17 + *(int *)(*(int *)(iVar13 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar24 = local_2f0;
                      for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                        if (*pbVar19 != 0) {
                          uVar11 = local_30c[*pbVar19];
                          uVar23 = *puVar22;
                          *(ushort *)puVar22 =
                               ((ushort)((uVar23 & 0x7e0) * param_8 >> 8) & 0x7e0) +
                               (uVar11 & 0x7e0) |
                               ((ushort)((uVar23 & 0xf800) * param_8 >> 8) & 0xf800) +
                               (uVar11 & 0xf800) |
                               ((ushort)((uVar23 & 0x1f) * param_8 >> 8) & 0x1f) + (uVar11 & 0x1f);
                        }
                        uVar23 = uVar24 + local_354;
                        puVar22 = (uint *)((int)puVar22 + 2);
                        uVar24 = uVar23 & 0xffff;
                        pbVar19 = pbVar19 + -(uVar23 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar2;
                    } while (local_2d8 < iVar14);
                  }
                }
                else if (param_8 == 0x80) {
                  local_2d8 = 0;
                  if (0 < iVar14) {
                    do {
                      pbVar19 = (byte *)(((iVar16 + *(int *)(piVar12[0xb] + -4 +
                                                            ((iVar5 - local_2f8) -
                                                            ((int)local_2ec >> 0x10)) * 4) + iVar4)
                                         - local_300) + -1);
                      puVar22 = (uint *)(local_2fc +
                                        iVar17 + *(int *)(*(int *)(iVar13 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar24 = local_2f0;
                      for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                        if (*pbVar19 != 0) {
                          uVar20 = (uint)local_30c[*pbVar19];
                          uVar6 = *puVar22 >> 1;
                          uVar23 = (uVar6 & 0x7800) + (uVar20 & 0xf800);
                          if (0xf800 < uVar23) {
                            uVar23 = 0xf800;
                          }
                          uVar1 = (uVar6 & 0x3e0) + (uVar20 & 0x7e0);
                          uVar11 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar11 = 0x7e0;
                          }
                          uVar6 = (uVar6 & 0xf) + (uVar20 & 0x1f);
                          uVar10 = (ushort)uVar6;
                          if (0x1f < uVar6) {
                            uVar10 = 0x1f;
                          }
                          *(ushort *)puVar22 = uVar11 | (ushort)uVar23 | uVar10;
                        }
                        uVar23 = uVar24 + local_354;
                        puVar22 = (uint *)((int)puVar22 + 2);
                        uVar24 = uVar23 & 0xffff;
                        pbVar19 = pbVar19 + -(uVar23 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar2;
                    } while (local_2d8 < iVar14);
                  }
                }
                else {
                  local_2d8 = 0;
                  if (0 < iVar14) {
                    do {
                      pbVar19 = (byte *)(((iVar16 + *(int *)(piVar12[0xb] + -4 +
                                                            ((iVar5 - local_2f8) -
                                                            ((int)local_2ec >> 0x10)) * 4) + iVar4)
                                         - local_300) + -1);
                      puVar22 = (uint *)(local_2fc +
                                        iVar17 + *(int *)(*(int *)(iVar13 + 0x2c) +
                                                         (local_2f4 + local_2d8) * 4));
                      uVar24 = local_2f0;
                      for (iVar3 = iVar15; iVar3 != 0; iVar3 = iVar3 + -1) {
                        if (*pbVar19 != 0) {
                          uVar20 = (uint)local_30c[*pbVar19];
                          uVar6 = *puVar22;
                          uVar23 = ((uVar6 & 0xf800) * param_8 >> 8 & 0xf800) + (uVar20 & 0xf800);
                          if (0xf800 < uVar23) {
                            uVar23 = 0xf800;
                          }
                          uVar1 = ((uVar6 & 0x7e0) * param_8 >> 8 & 0x7e0) + (uVar20 & 0x7e0);
                          uVar11 = (ushort)uVar1;
                          if (0x7e0 < uVar1) {
                            uVar11 = 0x7e0;
                          }
                          uVar6 = ((uVar6 & 0x1f) * param_8 >> 8 & 0x1f) + (uVar20 & 0x1f);
                          uVar10 = (ushort)uVar6;
                          if (0x1f < uVar6) {
                            uVar10 = 0x1f;
                          }
                          *(ushort *)puVar22 = uVar11 | (ushort)uVar23 | uVar10;
                        }
                        uVar23 = uVar24 + local_354;
                        puVar22 = (uint *)((int)puVar22 + 2);
                        uVar24 = uVar23 & 0xffff;
                        pbVar19 = pbVar19 + -(uVar23 >> 0x10);
                      }
                      local_2d8 = local_2d8 + 1;
                      local_2ec = local_2ec + iVar2;
                    } while (local_2d8 < iVar14);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirHV8to16_B
                  (param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4),param_7,param_8);
      }
    }
  }
  return;
}
#undef local_354
#undef local_30c
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2f0
#undef local_2ec
#undef local_2d8
#undef local_2d4
#undef local_254
#undef local_21c

/* W_RotateSpriteTransAdd8to16_P @ 0x0806c100, 3861 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 15 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 14 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAdd8to16_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  ulonglong uVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  int *piVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int *piVar28;
  int iVar29;
  uint uVar30;
  ushort uVar31;
  int iVar32;
  ushort uVar33;
  int iVar34;
  int iVar35;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  undefined2 in_FPUControlWord;
  uint uVar36;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define local_94 (*(int *)(ghidra_frame + 0xc))
#define local_90 (*(float *)(ghidra_frame + 0x10))
#define local_8c (*(float *)(ghidra_frame + 0x14))
#define local_88 (*(float *)(ghidra_frame + 0x18))
#define local_84 (*(float *)(ghidra_frame + 0x1c))
#define local_78 (*(int *)(ghidra_frame + 0x28))
#define local_74 (*(int *)(ghidra_frame + 0x2c))
#define local_68 (*(int *)(ghidra_frame + 0x38))
#define local_64 (*(int *)(ghidra_frame + 0x3c))
#define local_60 (*(int *)(ghidra_frame + 0x40))
#define local_54 (*(int *)(ghidra_frame + 0x4c))
#define local_50 (*(int *)(ghidra_frame + 0x50))
#define local_38 (*(ushort **)(ghidra_frame + 0x68))
#define local_20 (*(uint *)(ghidra_frame + 0x80))
  
  piVar20 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar21 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar5 = piVar20[0xb];
  iVar22 = roundfloat(param_3);
  iVar23 = roundfloat(param_4);
  iVar37 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar37 < 0) {
    iVar37 = -iVar37;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar40 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar40 < 0) {
    iVar40 = -iVar40;
    param_5 = param_5 + 180.0;
  }
  if (iVar37 == 0) {
    return local_20;
  }
  if (iVar40 == 0) {
    return local_20;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar11 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar34 = (int)uVar11;
  if (iVar34 == 0) {
LAB_0806c3f2:
    uVar24 = W_ScaleSpriteTransAdd_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return uVar24;
  }
  if (iVar34 == 0x5a0) {
    param_7 = -param_7;
    param_6 = -param_6;
    goto LAB_0806c3f2;
  }
  iVar6 = *piVar20;
  iVar7 = piVar20[1];
  iVar8 = piVar20[2];
  iVar9 = piVar20[3];
  fVar12 = (float)SinTable[(iVar34 + 0x2d0) % 0xb40];
  fVar13 = fVar12 * 0.0009765625;
  fVar15 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar34 >> 0x1f) << 0x20 | uVar11 & 0xffffffff) %
                                0xb40)];
  fVar14 = fVar15 * 0.0009765625;
  iVar2 = (int)GHIDRA_FIST32((float)((SinTable[(iVar34 + 0x2d0) % 0xb40] << 0x10) / iVar37) / param_8);
  uVar24 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar34 >> 0x1f) << 0x20 | uVar11 & 0xffffffff) % 0xb40
                          )] << 0x10) / iVar40;
  iVar3 = (int)GHIDRA_FIST32((float10)(int)uVar24 / param_8);
  if (iVar34 < 0x2d0) {
    iVar34 = -iVar8;
    iVar25 = -iVar9;
    iVar26 = (iVar6 - iVar8) + -1;
    iVar27 = (iVar7 - iVar9) + -1;
LAB_0806c63f:
    fVar16 = (float10)iVar34;
    fVar17 = (float10)iVar26;
    local_88 = (float10)iVar25;
    local_90 = (float10)iVar27;
    local_8c = local_90;
    fVar19 = fVar16;
  }
  else {
    if (iVar34 < 0x5a0) {
      iVar26 = (iVar6 - iVar8) + -1;
      iVar25 = -iVar9;
      iVar34 = (iVar7 - iVar9) + -1;
      iVar27 = -iVar8;
    }
    else {
      if (iVar34 < 0x870) {
        iVar34 = (iVar6 - iVar8) + -1;
        iVar25 = (iVar7 - iVar9) + -1;
        iVar26 = -iVar8;
        iVar27 = -iVar9;
        goto LAB_0806c63f;
      }
      if (0xb3f < iVar34) {
        return uVar24;
      }
      iVar26 = -iVar8;
      iVar25 = (iVar7 - iVar9) + -1;
      iVar34 = -iVar9;
      iVar27 = (iVar6 - iVar8) + -1;
    }
    fVar16 = (float10)iVar26;
    local_8c = (float10)iVar34;
    fVar17 = (float10)iVar27;
    local_90 = (float10)iVar25;
    local_88 = local_8c;
    fVar19 = fVar17;
  }
  local_84 = (float10)iVar26;
  local_8c = local_8c * param_7;
  fVar16 = fVar16 * param_6;
  fVar18 = (float10)iVar25 * param_7;
  fVar17 = fVar17 * param_6;
  iVar34 = roundfloat((-fVar16 * fVar14 + fVar18 * fVar13) * param_9);
  iVar26 = roundfloat((-fVar17 * fVar14 + local_8c * fVar13) * param_9);
  local_54 = roundfloat((-(local_84 * param_6) * fVar14 + local_88 * param_7 * fVar13) * param_9);
  local_94 = roundfloat((-(fVar19 * param_6) * fVar14 + local_90 * param_7 * fVar13) * param_9);
  if ((local_54 == iVar34) || (local_54 == iVar26)) {
    local_78 = 0;
    local_74 = 0;
    local_64 = (int)GHIDRA_FIST32((fVar16 * fVar13 + fVar18 * fVar14) * 65536.0 * param_8);
    local_68 = (int)GHIDRA_FIST32((fVar17 * fVar13 + local_8c * fVar14) * 65536.0 * param_8);
  }
  else {
    fVar19 = fVar13 * local_84 * param_6 + local_88 * param_7 * fVar14;
    local_74 = (int)GHIDRA_FIST32(((fVar19 - (fVar16 * fVar13 + fVar18 * fVar14)) * 65536.0 * param_8) /
                          (float)(local_54 - iVar34));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_78 = (int)GHIDRA_FIST32((((local_8c * fVar14 + fVar17 * fVar13) - fVar19) * 65536.0 * param_8) /
                          (float)(local_54 - iVar26));
    if (local_78 < 0) {
      local_78 = -local_78;
    }
    local_68 = (int)GHIDRA_FIST32(fVar19 * 65536.0 * param_8);
    local_64 = local_68;
  }
  for (; local_54 < W_y1 - iVar23; local_54 = local_54 + 1) {
    iVar25 = local_78;
    if (local_54 < iVar34) {
      iVar25 = -local_74;
    }
    local_64 = local_64 + iVar25;
    iVar25 = local_78;
    if (iVar26 <= local_54) {
      iVar25 = -local_74;
    }
    local_68 = local_68 + iVar25;
  }
  if (W_y2 - iVar23 < local_94) {
    local_94 = W_y2 - iVar23;
  }
  iVar25 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar25 == 0) {
    return 0;
  }
  iVar27 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar28 = (int *)param_1[5];
  if (piVar28 == (int *)0x0) {
    piVar28 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar20[0xc]);
  }
  else {
    EBPalUpdate(piVar28);
  }
  if (local_54 <= local_94) {
    iVar29 = W_x1 - iVar22;
    do {
      iVar39 = local_64 >> 0x10;
      if (local_64 >> 0x10 < iVar29) {
        iVar39 = iVar29;
      }
      iVar41 = local_68 >> 0x10;
      if (W_x2 - iVar22 < local_68 >> 0x10) {
        iVar41 = W_x2 - iVar22;
      }
      local_60 = (int)GHIDRA_FIST32(((((float10)iVar39 / param_8) * fVar12 -
                             ((float)local_54 / param_9) * fVar15) * 65536.0) / (float10)iVar37) +
                 iVar8 * 0x10000;
      iVar38 = iVar9 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar39 / param_8) * fVar15 +
                           ((float)local_54 / param_9) * fVar12) * 65536.0) / (float10)iVar40);
      local_38 = (ushort *)
                 (iVar27 + *(int *)(*(int *)(iVar21 + 0x2c) + (local_54 + iVar23) * 4) +
                 (iVar22 + iVar39) * 2);
      iVar35 = (iVar41 - iVar39) + 1;
      iVar10 = iVar41 - iVar39;
      iVar32 = iVar3 * iVar35 + iVar38;
      for (iVar35 = local_60 + iVar2 * iVar35;
          (SBORROW4(iVar41,iVar39) == iVar10 < 0 &&
          ((((iVar7 <= iVar32 >> 0x10 || (iVar6 <= iVar35 >> 0x10)) || (iVar32 >> 0x10 < 0)) ||
           (iVar35 >> 0x10 < 0)))); iVar35 = iVar35 - iVar2) {
        iVar41 = iVar41 + -1;
        iVar32 = iVar32 - iVar3;
        iVar10 = iVar41 - iVar39;
      }
      for (; (iVar39 <= iVar41 &&
             (((iVar7 <= iVar38 >> 0x10 || (iVar6 <= local_60 >> 0x10)) ||
              ((iVar38 >> 0x10 < 0 || (local_60 >> 0x10 < 0)))))); local_60 = local_60 + iVar2) {
        local_38 = local_38 + 1;
        iVar39 = iVar39 + 1;
        iVar38 = iVar38 + iVar3;
      }
      local_50 = (iVar41 - iVar39) + 1;
      if (0 < local_50) {
        do {
          bVar4 = *(byte *)((local_60 >> 0x10) + iVar25 + *(int *)(iVar5 + (iVar38 >> 0x10) * 4));
          if (bVar4 != 0) {
            uVar36 = (uint)*(ushort *)((int)piVar28 + (uint)bVar4 * 2 + 0x5c);
            uVar30 = (uint)*local_38;
            uVar24 = (uVar30 & 0xf800) + (uVar36 & 0xf800);
            if (0xf800 < uVar24) {
              uVar24 = 0xf800;
            }
            uVar1 = (uVar30 & 0x7e0) + (uVar36 & 0x7e0);
            uVar31 = (ushort)uVar1;
            if (0x7e0 < uVar1) {
              uVar31 = 0x7e0;
            }
            uVar36 = (uVar36 & 0x1f) + (uVar30 & 0x1f);
            uVar33 = (ushort)uVar36;
            if (0x1f < uVar36) {
              uVar33 = 0x1f;
            }
            *local_38 = (ushort)uVar24 | uVar31 | uVar33;
          }
          local_60 = local_60 + iVar2;
          local_38 = local_38 + 1;
          iVar38 = iVar38 + iVar3;
          local_50 = local_50 + -1;
        } while (local_50 != 0);
      }
      iVar39 = local_78;
      if (local_54 < iVar34) {
        iVar39 = -local_74;
      }
      local_64 = local_64 + iVar39;
      iVar39 = local_78;
      if (iVar26 <= local_54) {
        iVar39 = -local_74;
      }
      local_68 = local_68 + iVar39;
      local_54 = local_54 + 1;
    } while (local_54 <= local_94);
  }
  uVar24 = SpriteDecompUnlockData();
  return uVar24;
}
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_78
#undef local_74
#undef local_68
#undef local_64
#undef local_60
#undef local_54
#undef local_50
#undef local_38
#undef local_20

/* W_RotateSpriteTransAddMirH8to16_P @ 0x0806d020, 3861 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 15 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 14 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAddMirH8to16_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  ulonglong uVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  int *piVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int *piVar28;
  uint uVar29;
  ushort uVar30;
  int iVar31;
  ushort uVar32;
  int iVar33;
  int iVar34;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  undefined2 in_FPUControlWord;
  uint uVar35;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define local_94 (*(int *)(ghidra_frame + 0xc))
#define local_90 (*(float *)(ghidra_frame + 0x10))
#define local_8c (*(float *)(ghidra_frame + 0x14))
#define local_88 (*(float *)(ghidra_frame + 0x18))
#define local_84 (*(float *)(ghidra_frame + 0x1c))
#define local_78 (*(int *)(ghidra_frame + 0x28))
#define local_74 (*(int *)(ghidra_frame + 0x2c))
#define local_68 (*(int *)(ghidra_frame + 0x38))
#define local_64 (*(int *)(ghidra_frame + 0x3c))
#define local_60 (*(int *)(ghidra_frame + 0x40))
#define local_54 (*(int *)(ghidra_frame + 0x4c))
#define local_50 (*(int *)(ghidra_frame + 0x50))
#define local_38 (*(ushort **)(ghidra_frame + 0x68))
#define local_20 (*(uint *)(ghidra_frame + 0x80))
  
  piVar20 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar21 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar5 = piVar20[0xb];
  iVar22 = roundfloat(param_3);
  iVar23 = roundfloat(param_4);
  iVar36 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (iVar36 < 0) {
    iVar36 = -iVar36;
    param_5 = param_5 + 180.0;
  }
  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
  iVar39 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (iVar39 < 0) {
    iVar39 = -iVar39;
    param_5 = param_5 + 180.0;
  }
  if (iVar36 == 0) {
    return local_20;
  }
  if (iVar39 == 0) {
    return local_20;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar11 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar33 = (int)uVar11;
  if (iVar33 == 0) {
    param_6 = -param_6;
LAB_0806d313:
    uVar24 = W_ScaleSpriteTransAdd_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9);
    return uVar24;
  }
  if (iVar33 == 0x5a0) {
    param_7 = -param_7;
    goto LAB_0806d313;
  }
  iVar6 = *piVar20;
  iVar7 = piVar20[1];
  iVar8 = piVar20[2];
  iVar9 = piVar20[3];
  fVar12 = (float)SinTable[(iVar33 + 0x2d0) % 0xb40];
  fVar13 = fVar12 * 0.0009765625;
  fVar15 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar33 >> 0x1f) << 0x20 | uVar11 & 0xffffffff) %
                                0xb40)];
  fVar14 = fVar15 * 0.0009765625;
  iVar2 = (int)GHIDRA_FIST32((float)((SinTable[(iVar33 + 0x2d0) % 0xb40] << 0x10) / iVar36) / param_8);
  uVar24 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar33 >> 0x1f) << 0x20 | uVar11 & 0xffffffff) % 0xb40
                          )] << 0x10) / iVar39;
  iVar3 = (int)GHIDRA_FIST32((float10)(int)uVar24 / param_8);
  if (iVar33 < 0x2d0) {
    iVar33 = -iVar8;
    iVar25 = -iVar9;
    iVar26 = (iVar6 - iVar8) + -1;
    iVar27 = (iVar7 - iVar9) + -1;
LAB_0806d55f:
    fVar16 = (float10)iVar33;
    fVar17 = (float10)iVar26;
    local_88 = (float10)iVar25;
    local_90 = (float10)iVar27;
    local_8c = local_90;
    fVar19 = fVar16;
  }
  else {
    if (iVar33 < 0x5a0) {
      iVar26 = (iVar6 - iVar8) + -1;
      iVar25 = -iVar9;
      iVar33 = (iVar7 - iVar9) + -1;
      iVar27 = -iVar8;
    }
    else {
      if (iVar33 < 0x870) {
        iVar33 = (iVar6 - iVar8) + -1;
        iVar25 = (iVar7 - iVar9) + -1;
        iVar26 = -iVar8;
        iVar27 = -iVar9;
        goto LAB_0806d55f;
      }
      if (0xb3f < iVar33) {
        return uVar24;
      }
      iVar26 = -iVar8;
      iVar25 = (iVar7 - iVar9) + -1;
      iVar33 = -iVar9;
      iVar27 = (iVar6 - iVar8) + -1;
    }
    fVar16 = (float10)iVar26;
    local_8c = (float10)iVar33;
    fVar17 = (float10)iVar27;
    local_90 = (float10)iVar25;
    local_88 = local_8c;
    fVar19 = fVar17;
  }
  local_84 = (float10)iVar26;
  local_8c = local_8c * param_7;
  fVar16 = fVar16 * param_6;
  fVar18 = (float10)iVar25 * param_7;
  fVar17 = fVar17 * param_6;
  iVar33 = roundfloat((-fVar16 * fVar14 + fVar18 * fVar13) * param_9);
  iVar26 = roundfloat((-fVar17 * fVar14 + local_8c * fVar13) * param_9);
  local_54 = roundfloat((-(local_84 * param_6) * fVar14 + local_88 * param_7 * fVar13) * param_9);
  local_94 = roundfloat((-(fVar19 * param_6) * fVar14 + local_90 * param_7 * fVar13) * param_9);
  if ((local_54 == iVar33) || (local_54 == iVar26)) {
    local_78 = 0;
    local_74 = 0;
    local_64 = (int)GHIDRA_FIST32((fVar16 * fVar13 + fVar18 * fVar14) * 65536.0 * param_8);
    local_68 = (int)GHIDRA_FIST32((fVar17 * fVar13 + local_8c * fVar14) * 65536.0 * param_8);
  }
  else {
    fVar19 = fVar13 * local_84 * param_6 + local_88 * param_7 * fVar14;
    local_74 = (int)GHIDRA_FIST32(((fVar19 - (fVar16 * fVar13 + fVar18 * fVar14)) * 65536.0 * param_8) /
                          (float)(local_54 - iVar33));
    if (local_74 < 0) {
      local_74 = -local_74;
    }
    local_78 = (int)GHIDRA_FIST32((((local_8c * fVar14 + fVar17 * fVar13) - fVar19) * 65536.0 * param_8) /
                          (float)(local_54 - iVar26));
    if (local_78 < 0) {
      local_78 = -local_78;
    }
    local_68 = (int)GHIDRA_FIST32(fVar19 * 65536.0 * param_8);
    local_64 = local_68;
  }
  for (; local_54 < W_y1 - iVar23; local_54 = local_54 + 1) {
    iVar25 = local_78;
    if (local_54 < iVar33) {
      iVar25 = -local_74;
    }
    local_64 = local_64 + iVar25;
    iVar25 = local_78;
    if (iVar26 <= local_54) {
      iVar25 = -local_74;
    }
    local_68 = local_68 + iVar25;
  }
  if (W_y2 - iVar23 < local_94) {
    local_94 = W_y2 - iVar23;
  }
  iVar25 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar25 == 0) {
    return 0;
  }
  iVar27 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar28 = (int *)param_1[5];
  if (piVar28 == (int *)0x0) {
    piVar28 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar20[0xc]);
  }
  else {
    EBPalUpdate(piVar28);
  }
  if (local_54 <= local_94) {
    do {
      iVar38 = local_64 >> 0x10;
      iVar40 = local_68 >> 0x10;
      if (W_x2 < iVar22 - iVar38) {
        iVar38 = iVar22 - W_x2;
      }
      if (iVar22 - iVar40 < W_x1) {
        iVar40 = iVar22 - W_x1;
      }
      local_60 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar12 -
                             ((float)local_54 / param_9) * fVar15) * 65536.0) / (float10)iVar36) +
                 iVar8 * 0x10000;
      iVar37 = iVar9 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar15 +
                           ((float)local_54 / param_9) * fVar12) * 65536.0) / (float10)iVar39);
      local_38 = (ushort *)
                 (iVar27 + *(int *)(*(int *)(iVar21 + 0x2c) + (local_54 + iVar23) * 4) +
                 (iVar22 - iVar38) * 2);
      iVar34 = (iVar40 - iVar38) + 1;
      iVar10 = iVar40 - iVar38;
      iVar31 = iVar3 * iVar34 + iVar37;
      for (iVar34 = local_60 + iVar2 * iVar34;
          (SBORROW4(iVar40,iVar38) == iVar10 < 0 &&
          ((((iVar7 <= iVar31 >> 0x10 || (iVar6 <= iVar34 >> 0x10)) || (iVar31 >> 0x10 < 0)) ||
           (iVar34 >> 0x10 < 0)))); iVar34 = iVar34 - iVar2) {
        iVar40 = iVar40 + -1;
        iVar31 = iVar31 - iVar3;
        iVar10 = iVar40 - iVar38;
      }
      for (; (iVar38 <= iVar40 &&
             (((iVar7 <= iVar37 >> 0x10 || (iVar6 <= local_60 >> 0x10)) ||
              ((iVar37 >> 0x10 < 0 || (local_60 >> 0x10 < 0)))))); local_60 = local_60 + iVar2) {
        local_38 = local_38 + -1;
        iVar38 = iVar38 + 1;
        iVar37 = iVar37 + iVar3;
      }
      local_50 = (iVar40 - iVar38) + 1;
      if (0 < local_50) {
        do {
          bVar4 = *(byte *)((local_60 >> 0x10) + iVar25 + *(int *)(iVar5 + (iVar37 >> 0x10) * 4));
          if (bVar4 != 0) {
            uVar35 = (uint)*(ushort *)((int)piVar28 + (uint)bVar4 * 2 + 0x5c);
            uVar29 = (uint)*local_38;
            uVar24 = (uVar29 & 0xf800) + (uVar35 & 0xf800);
            if (0xf800 < uVar24) {
              uVar24 = 0xf800;
            }
            uVar1 = (uVar29 & 0x7e0) + (uVar35 & 0x7e0);
            uVar30 = (ushort)uVar1;
            if (0x7e0 < uVar1) {
              uVar30 = 0x7e0;
            }
            uVar35 = (uVar35 & 0x1f) + (uVar29 & 0x1f);
            uVar32 = (ushort)uVar35;
            if (0x1f < uVar35) {
              uVar32 = 0x1f;
            }
            *local_38 = (ushort)uVar24 | uVar30 | uVar32;
          }
          local_60 = local_60 + iVar2;
          local_38 = local_38 + -1;
          iVar37 = iVar37 + iVar3;
          local_50 = local_50 + -1;
        } while (local_50 != 0);
      }
      iVar38 = local_78;
      if (local_54 < iVar33) {
        iVar38 = -local_74;
      }
      local_64 = local_64 + iVar38;
      iVar38 = local_78;
      if (iVar26 <= local_54) {
        iVar38 = -local_74;
      }
      local_68 = local_68 + iVar38;
      local_54 = local_54 + 1;
    } while (local_54 <= local_94);
  }
  uVar24 = SpriteDecompUnlockData();
  return uVar24;
}
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_78
#undef local_74
#undef local_68
#undef local_64
#undef local_60
#undef local_54
#undef local_50
#undef local_38
#undef local_20

/* W_RotateSpriteTransAdd8to16_B_P @ 0x0806df40, 8365 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 21 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 17 stack locals placed at their original offsets in a 0x2b0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAdd8to16_B_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9,int param_10,int param_11)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ulonglong uVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  float10 fVar20;
  ushort uVar21;
  ushort uVar22;
  int *piVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  uint uVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int *piVar31;
  int iVar32;
  uint uVar33;
  uint uVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x2b0] __attribute__((aligned(16)));
#define local_2a4 (*(ushort **)(ghidra_frame + 0xc))
#define local_298 (*(int *)(ghidra_frame + 0x18))
#define local_294 (*(float *)(ghidra_frame + 0x1c))
#define local_290 (*(float *)(ghidra_frame + 0x20))
#define local_28c (*(float *)(ghidra_frame + 0x24))
#define local_288 (*(float *)(ghidra_frame + 0x28))
#define local_27c (*(int *)(ghidra_frame + 0x34))
#define local_278 (*(int *)(ghidra_frame + 0x38))
#define local_26c (*(int *)(ghidra_frame + 0x44))
#define local_268 (*(int *)(ghidra_frame + 0x48))
#define local_264 (*(int *)(ghidra_frame + 0x4c))
#define local_258 (*(int *)(ghidra_frame + 0x58))
#define local_254 (*(int *)(ghidra_frame + 0x5c))
#define local_250 (*(int *)(ghidra_frame + 0x60))
#define local_238 (*(ushort **)(ghidra_frame + 0x78))
#define local_220 (*(uint *)(ghidra_frame + 0x90))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x94))
  
  piVar23 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar24 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar6 = piVar23[0xb];
  iVar25 = roundfloat(param_3);
  iVar26 = roundfloat(param_4);
  if ((param_10 == 0x100) && (param_11 == 0)) {
    uVar27 = W_RotateSprite8to16_P
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar27;
  }
  if ((param_10 == 0x100) && (param_11 == 0x100)) {
    uVar27 = W_RotateSpriteTransAdd8to16_P
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar27;
  }
  if ((param_10 == 0) && (param_11 == 0x100)) {
    return 0;
  }
  local_254 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (local_254 < 0) {
    local_254 = -local_254;
    param_5 = param_5 + 180.0;
  }
  local_220 = CONCAT22((*(ushort *)((char *)&local_220 + 2)),in_FPUControlWord);
  local_258 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (local_258 < 0) {
    local_258 = -local_258;
    param_5 = param_5 + 180.0;
  }
  if (local_254 == 0) {
    return local_220;
  }
  if (local_258 == 0) {
    return local_220;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar12 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar36 = (int)uVar12;
  if (iVar36 == 0) {
LAB_0806e335:
    uVar27 = W_ScaleSpriteTransAdd_B_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9,param_10
                        ,param_11);
    return uVar27;
  }
  if (iVar36 == 0x5a0) {
    param_7 = -param_7;
    param_6 = -param_6;
    goto LAB_0806e335;
  }
  iVar7 = *piVar23;
  iVar8 = piVar23[1];
  iVar9 = piVar23[2];
  iVar10 = piVar23[3];
  fVar13 = (float)SinTable[(iVar36 + 0x2d0) % 0xb40];
  fVar14 = fVar13 * 0.0009765625;
  fVar16 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar36 >> 0x1f) << 0x20 | uVar12 & 0xffffffff) %
                                0xb40)];
  fVar15 = fVar16 * 0.0009765625;
  iVar3 = (int)GHIDRA_FIST32((float)((SinTable[(iVar36 + 0x2d0) % 0xb40] << 0x10) / local_254) / param_8);
  uVar27 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar36 >> 0x1f) << 0x20 | uVar12 & 0xffffffff) % 0xb40
                          )] << 0x10) / local_258;
  iVar4 = (int)GHIDRA_FIST32((float10)(int)uVar27 / param_8);
  if (iVar36 < 0x2d0) {
    iVar36 = -iVar9;
    iVar28 = -iVar10;
    iVar29 = (iVar7 - iVar9) + -1;
    iVar30 = (iVar8 - iVar10) + -1;
LAB_0806e57f:
    fVar17 = (float10)iVar36;
    fVar18 = (float10)iVar29;
    local_28c = (float10)iVar28;
    local_294 = (float10)iVar30;
    local_290 = local_294;
    fVar20 = fVar17;
  }
  else {
    if (iVar36 < 0x5a0) {
      iVar29 = (iVar7 - iVar9) + -1;
      iVar28 = -iVar10;
      iVar36 = (iVar8 - iVar10) + -1;
      iVar30 = -iVar9;
    }
    else {
      if (iVar36 < 0x870) {
        iVar36 = (iVar7 - iVar9) + -1;
        iVar28 = (iVar8 - iVar10) + -1;
        iVar29 = -iVar9;
        iVar30 = -iVar10;
        goto LAB_0806e57f;
      }
      if (0xb3f < iVar36) {
        return uVar27;
      }
      iVar29 = -iVar9;
      iVar28 = (iVar8 - iVar10) + -1;
      iVar36 = -iVar10;
      iVar30 = (iVar7 - iVar9) + -1;
    }
    fVar17 = (float10)iVar29;
    local_290 = (float10)iVar36;
    fVar18 = (float10)iVar30;
    local_294 = (float10)iVar28;
    local_28c = local_290;
    fVar20 = fVar18;
  }
  local_288 = (float10)iVar29;
  local_290 = local_290 * param_7;
  fVar17 = fVar17 * param_6;
  fVar19 = (float10)iVar28 * param_7;
  fVar18 = fVar18 * param_6;
  iVar36 = roundfloat((-fVar17 * fVar15 + fVar19 * fVar14) * param_9);
  iVar28 = roundfloat((-fVar18 * fVar15 + local_290 * fVar14) * param_9);
  local_250 = roundfloat((-(local_288 * param_6) * fVar15 + local_28c * param_7 * fVar14) * param_9)
  ;
  local_298 = roundfloat((-(fVar20 * param_6) * fVar15 + local_294 * param_7 * fVar14) * param_9);
  if ((local_250 == iVar36) || (local_250 == iVar28)) {
    local_27c = 0;
    local_278 = 0;
    local_268 = (int)GHIDRA_FIST32((fVar17 * fVar14 + fVar19 * fVar15) * 65536.0 * param_8);
    local_26c = (int)GHIDRA_FIST32((fVar18 * fVar14 + local_290 * fVar15) * 65536.0 * param_8);
  }
  else {
    fVar20 = fVar14 * local_288 * param_6 + local_28c * param_7 * fVar15;
    local_278 = (int)GHIDRA_FIST32(((fVar20 - (fVar17 * fVar14 + fVar19 * fVar15)) * 65536.0 * param_8) /
                           (float)(local_250 - iVar36));
    if (local_278 < 0) {
      local_278 = -local_278;
    }
    local_27c = (int)GHIDRA_FIST32((((local_290 * fVar15 + fVar18 * fVar14) - fVar20) * 65536.0 * param_8) /
                           (float)(local_250 - iVar28));
    if (local_27c < 0) {
      local_27c = -local_27c;
    }
    local_26c = (int)GHIDRA_FIST32(fVar20 * 65536.0 * param_8);
    local_268 = local_26c;
  }
  for (; local_250 < W_y1 - iVar26; local_250 = local_250 + 1) {
    iVar29 = local_27c;
    if (local_250 < iVar36) {
      iVar29 = -local_278;
    }
    local_268 = local_268 + iVar29;
    iVar29 = local_27c;
    if (iVar28 <= local_250) {
      iVar29 = -local_278;
    }
    local_26c = local_26c + iVar29;
  }
  if (W_y2 - iVar26 < local_298) {
    local_298 = W_y2 - iVar26;
  }
  iVar29 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar29 == 0) {
    return 0;
  }
  iVar30 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar31 = (int *)param_1[5];
  if (piVar31 == (int *)0x0) {
    piVar31 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar23[0xc]);
  }
  else {
    EBPalUpdate(piVar31);
  }
  puVar1 = (ushort *)(piVar31 + 0x17);
  local_2a4 = puVar1;
  if (param_10 != 0x100) {
    local_2a4 = local_21c;
    if (param_10 == 0) {
      memset(local_21c,0,piVar23[5] * 2);
    }
    else if (param_10 == 0x80) {
      iVar40 = 1;
      iVar32 = piVar23[5];
      if (1 < iVar32) {
        do {
          local_21c[iVar40] = puVar1[iVar40] >> 1 & 0xfbef;
          iVar40 = iVar40 + 1;
        } while (iVar40 < iVar32);
      }
    }
    else {
      iVar40 = 1;
      iVar32 = piVar23[5];
      if (1 < iVar32) {
        do {
          uVar27 = (uint)puVar1[iVar40];
          local_21c[iVar40] =
               (ushort)((uVar27 & 0xf800) * param_10 >> 8) & 0xf800 |
               (ushort)((uVar27 & 0x7e0) * param_10 >> 8) & 0x7e0 |
               (ushort)((uVar27 & 0x1f) * param_10 >> 8) & 0x1f;
          iVar40 = iVar40 + 1;
        } while (iVar40 < iVar32);
      }
    }
  }
  if (param_11 == 0) {
    if (local_250 <= local_298) {
      iVar32 = W_x1 - iVar25;
      do {
        iVar40 = local_268 >> 0x10;
        if (local_268 >> 0x10 < iVar32) {
          iVar40 = iVar32;
        }
        iVar39 = local_26c >> 0x10;
        if (W_x2 - iVar25 < local_26c >> 0x10) {
          iVar39 = W_x2 - iVar25;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar38 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 + iVar40) * 2);
        iVar37 = (iVar39 - iVar40) + 1;
        iVar11 = iVar39 - iVar40;
        iVar35 = iVar4 * iVar37 + iVar38;
        for (iVar37 = local_264 + iVar3 * iVar37;
            (SBORROW4(iVar39,iVar40) == iVar11 < 0 &&
            (((iVar8 <= iVar35 >> 0x10 || (iVar7 <= iVar37 >> 0x10)) ||
             ((iVar35 >> 0x10 < 0 || (iVar37 >> 0x10 < 0)))))); iVar37 = iVar37 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar35 = iVar35 - iVar4;
          iVar11 = iVar39 - iVar40;
        }
        for (; (iVar40 <= iVar39 &&
               ((((iVar8 <= iVar38 >> 0x10 || (iVar7 <= local_264 >> 0x10)) || (iVar38 >> 0x10 < 0))
                || (local_264 >> 0x10 < 0)))); local_264 = local_264 + iVar3) {
          local_238 = local_238 + 1;
          iVar40 = iVar40 + 1;
          iVar38 = iVar38 + iVar4;
        }
        iVar40 = (iVar39 - iVar40) + 1;
        if (0 < iVar40) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar29 + *(int *)(iVar6 + (iVar38 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              *local_238 = local_2a4[bVar5];
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + 1;
            iVar38 = iVar38 + iVar4;
            iVar40 = iVar40 + -1;
          } while (iVar40 != 0);
        }
        iVar40 = local_27c;
        if (local_250 < iVar36) {
          iVar40 = -local_278;
        }
        local_268 = local_268 + iVar40;
        iVar40 = local_27c;
        if (iVar28 <= local_250) {
          iVar40 = -local_278;
        }
        local_26c = local_26c + iVar40;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if ((param_10 + param_11 < 0x101) && (param_11 == 0x80)) {
    if (local_250 <= local_298) {
      iVar32 = W_x1 - iVar25;
      do {
        iVar40 = local_268 >> 0x10;
        if (local_268 >> 0x10 < iVar32) {
          iVar40 = iVar32;
        }
        iVar39 = local_26c >> 0x10;
        if (W_x2 - iVar25 < local_26c >> 0x10) {
          iVar39 = W_x2 - iVar25;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar38 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 + iVar40) * 2);
        iVar37 = (iVar39 - iVar40) + 1;
        iVar11 = iVar39 - iVar40;
        iVar35 = iVar4 * iVar37 + iVar38;
        for (iVar37 = local_264 + iVar3 * iVar37;
            (SBORROW4(iVar39,iVar40) == iVar11 < 0 &&
            ((((iVar8 <= iVar35 >> 0x10 || (iVar7 <= iVar37 >> 0x10)) || (iVar35 >> 0x10 < 0)) ||
             (iVar37 >> 0x10 < 0)))); iVar37 = iVar37 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar35 = iVar35 - iVar4;
          iVar11 = iVar39 - iVar40;
        }
        for (; (iVar40 <= iVar39 &&
               (((iVar8 <= iVar38 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
                ((iVar38 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3)
        {
          local_238 = local_238 + 1;
          iVar40 = iVar40 + 1;
          iVar38 = iVar38 + iVar4;
        }
        iVar40 = (iVar39 - iVar40) + 1;
        if (0 < iVar40) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar29 + *(int *)(iVar6 + (iVar38 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar22 = local_2a4[bVar5];
              uVar21 = *local_238 >> 1;
              *local_238 = (uVar21 & 0x3e0) + (uVar22 & 0x7e0) |
                           (uVar21 & 0x7800) + (uVar22 & 0xf800) | (uVar21 & 0xf) + (uVar22 & 0x1f);
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + 1;
            iVar38 = iVar38 + iVar4;
            iVar40 = iVar40 + -1;
          } while (iVar40 != 0);
        }
        iVar40 = local_27c;
        if (local_250 < iVar36) {
          iVar40 = -local_278;
        }
        local_268 = local_268 + iVar40;
        iVar40 = local_27c;
        if (iVar28 <= local_250) {
          iVar40 = -local_278;
        }
        local_26c = local_26c + iVar40;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (param_10 + param_11 < 0x101) {
    if (local_250 <= local_298) {
      iVar32 = W_x1 - iVar25;
      do {
        iVar40 = local_268 >> 0x10;
        if (local_268 >> 0x10 < iVar32) {
          iVar40 = iVar32;
        }
        iVar39 = local_26c >> 0x10;
        if (W_x2 - iVar25 < local_26c >> 0x10) {
          iVar39 = W_x2 - iVar25;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar38 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 + iVar40) * 2);
        iVar37 = (iVar39 - iVar40) + 1;
        iVar11 = iVar39 - iVar40;
        iVar35 = iVar4 * iVar37 + iVar38;
        for (iVar37 = local_264 + iVar3 * iVar37;
            (SBORROW4(iVar39,iVar40) == iVar11 < 0 &&
            (((iVar8 <= iVar35 >> 0x10 || (iVar7 <= iVar37 >> 0x10)) ||
             ((iVar35 >> 0x10 < 0 || (iVar37 >> 0x10 < 0)))))); iVar37 = iVar37 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar35 = iVar35 - iVar4;
          iVar11 = iVar39 - iVar40;
        }
        for (; (iVar40 <= iVar39 &&
               (((iVar8 <= iVar38 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
                ((iVar38 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3)
        {
          local_238 = local_238 + 1;
          iVar40 = iVar40 + 1;
          iVar38 = iVar38 + iVar4;
        }
        iVar40 = (iVar39 - iVar40) + 1;
        if (0 < iVar40) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar29 + *(int *)(iVar6 + (iVar38 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar22 = local_2a4[bVar5];
              uVar27 = (uint)*local_238;
              *local_238 = ((ushort)((uVar27 & 0x7e0) * param_11 >> 8) & 0x7e0) + (uVar22 & 0x7e0) |
                           ((ushort)((uVar27 & 0xf800) * param_11 >> 8) & 0xf800) +
                           (uVar22 & 0xf800) |
                           ((ushort)((uVar27 & 0x1f) * param_11 >> 8) & 0x1f) + (uVar22 & 0x1f);
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + 1;
            iVar38 = iVar38 + iVar4;
            iVar40 = iVar40 + -1;
          } while (iVar40 != 0);
        }
        iVar40 = local_27c;
        if (local_250 < iVar36) {
          iVar40 = -local_278;
        }
        local_268 = local_268 + iVar40;
        iVar40 = local_27c;
        if (iVar28 <= local_250) {
          iVar40 = -local_278;
        }
        local_26c = local_26c + iVar40;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (param_11 == 0x80) {
    if (local_250 <= local_298) {
      iVar32 = W_x1 - iVar25;
      do {
        iVar40 = local_268 >> 0x10;
        if (local_268 >> 0x10 < iVar32) {
          iVar40 = iVar32;
        }
        iVar39 = local_26c >> 0x10;
        if (W_x2 - iVar25 < local_26c >> 0x10) {
          iVar39 = W_x2 - iVar25;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar38 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 + iVar40) * 2);
        iVar37 = (iVar39 - iVar40) + 1;
        iVar11 = iVar39 - iVar40;
        iVar35 = iVar4 * iVar37 + iVar38;
        for (iVar37 = local_264 + iVar3 * iVar37;
            (SBORROW4(iVar39,iVar40) == iVar11 < 0 &&
            (((iVar8 <= iVar35 >> 0x10 || (iVar7 <= iVar37 >> 0x10)) ||
             ((iVar35 >> 0x10 < 0 || (iVar37 >> 0x10 < 0)))))); iVar37 = iVar37 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar35 = iVar35 - iVar4;
          iVar11 = iVar39 - iVar40;
        }
        for (; (iVar40 <= iVar39 &&
               ((((iVar8 <= iVar38 >> 0x10 || (iVar7 <= local_264 >> 0x10)) || (iVar38 >> 0x10 < 0))
                || (local_264 >> 0x10 < 0)))); local_264 = local_264 + iVar3) {
          local_238 = local_238 + 1;
          iVar40 = iVar40 + 1;
          iVar38 = iVar38 + iVar4;
        }
        iVar40 = (iVar39 - iVar40) + 1;
        if (0 < iVar40) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar29 + *(int *)(iVar6 + (iVar38 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar33 = (uint)local_2a4[bVar5];
              uVar34 = (uint)(*local_238 >> 1);
              uVar27 = (uVar34 & 0x7800) + (uVar33 & 0xf800);
              if (0xf800 < uVar27) {
                uVar27 = 0xf800;
              }
              uVar2 = (uVar34 & 0x3e0) + (uVar33 & 0x7e0);
              uVar22 = (ushort)uVar2;
              if (0x7e0 < uVar2) {
                uVar22 = 0x7e0;
              }
              uVar33 = (uVar34 & 0xf) + (uVar33 & 0x1f);
              uVar21 = (ushort)uVar33;
              if (0x1f < uVar33) {
                uVar21 = 0x1f;
              }
              *local_238 = uVar22 | (ushort)uVar27 | uVar21;
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + 1;
            iVar38 = iVar38 + iVar4;
            iVar40 = iVar40 + -1;
          } while (iVar40 != 0);
        }
        iVar40 = local_27c;
        if (local_250 < iVar36) {
          iVar40 = -local_278;
        }
        local_268 = local_268 + iVar40;
        iVar40 = local_27c;
        if (iVar28 <= local_250) {
          iVar40 = -local_278;
        }
        local_26c = local_26c + iVar40;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (local_250 <= local_298) {
    iVar32 = W_x1 - iVar25;
    do {
      iVar40 = local_268 >> 0x10;
      if (local_268 >> 0x10 < iVar32) {
        iVar40 = iVar32;
      }
      iVar39 = local_26c >> 0x10;
      if (W_x2 - iVar25 < local_26c >> 0x10) {
        iVar39 = W_x2 - iVar25;
      }
      local_264 = (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar13 -
                              ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254)
                  + iVar9 * 0x10000;
      iVar38 = iVar10 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar40 / param_8) * fVar16 +
                           ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
      local_238 = (ushort *)
                  (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                  (iVar25 + iVar40) * 2);
      iVar37 = (iVar39 - iVar40) + 1;
      iVar11 = iVar39 - iVar40;
      iVar35 = iVar4 * iVar37 + iVar38;
      for (iVar37 = local_264 + iVar3 * iVar37;
          (SBORROW4(iVar39,iVar40) == iVar11 < 0 &&
          ((((iVar8 <= iVar35 >> 0x10 || (iVar7 <= iVar37 >> 0x10)) || (iVar35 >> 0x10 < 0)) ||
           (iVar37 >> 0x10 < 0)))); iVar37 = iVar37 - iVar3) {
        iVar39 = iVar39 + -1;
        iVar35 = iVar35 - iVar4;
        iVar11 = iVar39 - iVar40;
      }
      for (; (iVar40 <= iVar39 &&
             (((iVar8 <= iVar38 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
              ((iVar38 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3) {
        local_238 = local_238 + 1;
        iVar40 = iVar40 + 1;
        iVar38 = iVar38 + iVar4;
      }
      iVar40 = (iVar39 - iVar40) + 1;
      if (0 < iVar40) {
        do {
          bVar5 = *(byte *)((local_264 >> 0x10) + iVar29 + *(int *)(iVar6 + (iVar38 >> 0x10) * 4));
          if (bVar5 != 0) {
            uVar33 = (uint)local_2a4[bVar5];
            uVar34 = (uint)*local_238;
            uVar27 = ((uVar34 & 0xf800) * param_11 >> 8 & 0xf800) + (uVar33 & 0xf800);
            if (0xf800 < uVar27) {
              uVar27 = 0xf800;
            }
            uVar2 = ((uVar34 & 0x7e0) * param_11 >> 8 & 0x7e0) + (uVar33 & 0x7e0);
            uVar22 = (ushort)uVar2;
            if (0x7e0 < uVar2) {
              uVar22 = 0x7e0;
            }
            uVar33 = ((uVar34 & 0x1f) * param_11 >> 8 & 0x1f) + (uVar33 & 0x1f);
            uVar21 = (ushort)uVar33;
            if (0x1f < uVar33) {
              uVar21 = 0x1f;
            }
            *local_238 = uVar22 | (ushort)uVar27 | uVar21;
          }
          local_264 = local_264 + iVar3;
          local_238 = local_238 + 1;
          iVar38 = iVar38 + iVar4;
          iVar40 = iVar40 + -1;
        } while (iVar40 != 0);
      }
      iVar40 = local_27c;
      if (local_250 < iVar36) {
        iVar40 = -local_278;
      }
      local_268 = local_268 + iVar40;
      iVar40 = local_27c;
      if (iVar28 <= local_250) {
        iVar40 = -local_278;
      }
      local_26c = local_26c + iVar40;
      local_250 = local_250 + 1;
    } while (local_250 <= local_298);
  }
  uVar27 = SpriteDecompUnlockData();
  return uVar27;
}
#undef local_2a4
#undef local_298
#undef local_294
#undef local_290
#undef local_28c
#undef local_288
#undef local_27c
#undef local_278
#undef local_26c
#undef local_268
#undef local_264
#undef local_258
#undef local_254
#undef local_250
#undef local_238
#undef local_220
#undef local_21c

/* W_RotateSpriteTransAddMirH8to16_B_P @ 0x0806fff0, 8301 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 21 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 17 stack locals placed at their original offsets in a 0x2b0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 8 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAddMirH8to16_B_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9,int param_10,int param_11)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ulonglong uVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  float10 fVar20;
  ushort uVar21;
  ushort uVar22;
  int *piVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  uint uVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int *piVar31;
  uint uVar32;
  uint uVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x2b0] __attribute__((aligned(16)));
#define local_2a4 (*(ushort **)(ghidra_frame + 0xc))
#define local_298 (*(int *)(ghidra_frame + 0x18))
#define local_294 (*(float *)(ghidra_frame + 0x1c))
#define local_290 (*(float *)(ghidra_frame + 0x20))
#define local_28c (*(float *)(ghidra_frame + 0x24))
#define local_288 (*(float *)(ghidra_frame + 0x28))
#define local_27c (*(int *)(ghidra_frame + 0x34))
#define local_278 (*(int *)(ghidra_frame + 0x38))
#define local_26c (*(int *)(ghidra_frame + 0x44))
#define local_268 (*(int *)(ghidra_frame + 0x48))
#define local_264 (*(int *)(ghidra_frame + 0x4c))
#define local_258 (*(int *)(ghidra_frame + 0x58))
#define local_254 (*(int *)(ghidra_frame + 0x5c))
#define local_250 (*(int *)(ghidra_frame + 0x60))
#define local_238 (*(ushort **)(ghidra_frame + 0x78))
#define local_220 (*(uint *)(ghidra_frame + 0x90))
#define local_21c (*(ushort (*)[262])(ghidra_frame + 0x94))
  
  piVar23 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar24 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  iVar6 = piVar23[0xb];
  iVar25 = roundfloat(param_3);
  iVar26 = roundfloat(param_4);
  if ((param_10 == 0x100) && (param_11 == 0)) {
    uVar27 = W_RotateSpriteMirH8to16_P
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar27;
  }
  if ((param_10 == 0x100) && (param_11 == 0x100)) {
    uVar27 = W_RotateSpriteTransAddMirH8to16_P
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar27;
  }
  if ((param_10 == 0) && (param_11 == 0x100)) {
    return 0;
  }
  local_254 = (int)GHIDRA_FIST32(param_6 * 1024.0);
  if (local_254 < 0) {
    local_254 = -local_254;
    param_5 = param_5 + 180.0;
  }
  local_220 = CONCAT22((*(ushort *)((char *)&local_220 + 2)),in_FPUControlWord);
  local_258 = (int)GHIDRA_FIST32(param_7 * 1024.0);
  if (local_258 < 0) {
    local_258 = -local_258;
    param_5 = param_5 + 180.0;
  }
  if (local_254 == 0) {
    return local_220;
  }
  if (local_258 == 0) {
    return local_220;
  }
  if (param_5 < 0.0) {
    param_5 = (float)((int)GHIDRA_FIST32(-param_5 * ((float)0.0027777778f)) * 0x168 + 0x168) + param_5;
  }
  uVar12 = (longlong)(int)GHIDRA_FIST32(param_5 * 8.0) % 0xb40;
  iVar35 = (int)uVar12;
  if (iVar35 == 0) {
    param_6 = -param_6;
LAB_080703e8:
    uVar27 = W_ScaleSpriteTransAdd_B_S
                       (param_1,param_2,param_3,param_4,param_6 * param_8,param_7 * param_9,param_10
                        ,param_11);
    return uVar27;
  }
  if (iVar35 == 0x5a0) {
    param_7 = -param_7;
    goto LAB_080703e8;
  }
  iVar7 = *piVar23;
  iVar8 = piVar23[1];
  iVar9 = piVar23[2];
  iVar10 = piVar23[3];
  fVar13 = (float)SinTable[(iVar35 + 0x2d0) % 0xb40];
  fVar14 = fVar13 * 0.0009765625;
  fVar16 = (float)SinTable[(int)((longlong)
                                 ((ulonglong)(uint)(iVar35 >> 0x1f) << 0x20 | uVar12 & 0xffffffff) %
                                0xb40)];
  fVar15 = fVar16 * 0.0009765625;
  iVar3 = (int)GHIDRA_FIST32((float)((SinTable[(iVar35 + 0x2d0) % 0xb40] << 0x10) / local_254) / param_8);
  uVar27 = (SinTable[(int)((longlong)
                           ((ulonglong)(uint)(iVar35 >> 0x1f) << 0x20 | uVar12 & 0xffffffff) % 0xb40
                          )] << 0x10) / local_258;
  iVar4 = (int)GHIDRA_FIST32((float10)(int)uVar27 / param_8);
  if (iVar35 < 0x2d0) {
    iVar35 = -iVar9;
    iVar28 = -iVar10;
    iVar29 = (iVar7 - iVar9) + -1;
    iVar30 = (iVar8 - iVar10) + -1;
LAB_08070625:
    fVar17 = (float10)iVar35;
    fVar18 = (float10)iVar29;
    local_28c = (float10)iVar28;
    local_294 = (float10)iVar30;
    local_290 = local_294;
    fVar20 = fVar17;
  }
  else {
    if (iVar35 < 0x5a0) {
      iVar29 = (iVar7 - iVar9) + -1;
      iVar28 = -iVar10;
      iVar35 = (iVar8 - iVar10) + -1;
      iVar30 = -iVar9;
    }
    else {
      if (iVar35 < 0x870) {
        iVar35 = (iVar7 - iVar9) + -1;
        iVar28 = (iVar8 - iVar10) + -1;
        iVar29 = -iVar9;
        iVar30 = -iVar10;
        goto LAB_08070625;
      }
      if (0xb3f < iVar35) {
        return uVar27;
      }
      iVar29 = -iVar9;
      iVar28 = (iVar8 - iVar10) + -1;
      iVar35 = -iVar10;
      iVar30 = (iVar7 - iVar9) + -1;
    }
    fVar17 = (float10)iVar29;
    local_290 = (float10)iVar35;
    fVar18 = (float10)iVar30;
    local_294 = (float10)iVar28;
    local_28c = local_290;
    fVar20 = fVar18;
  }
  local_288 = (float10)iVar29;
  local_290 = local_290 * param_7;
  fVar17 = fVar17 * param_6;
  fVar19 = (float10)iVar28 * param_7;
  fVar18 = fVar18 * param_6;
  iVar35 = roundfloat((-fVar17 * fVar15 + fVar19 * fVar14) * param_9);
  iVar29 = roundfloat((-fVar18 * fVar15 + local_290 * fVar14) * param_9);
  local_250 = roundfloat((-(local_288 * param_6) * fVar15 + local_28c * param_7 * fVar14) * param_9)
  ;
  local_298 = roundfloat((-(fVar20 * param_6) * fVar15 + local_294 * param_7 * fVar14) * param_9);
  if ((local_250 == iVar35) || (local_250 == iVar29)) {
    local_27c = 0;
    local_278 = 0;
    local_268 = (int)GHIDRA_FIST32((fVar17 * fVar14 + fVar19 * fVar15) * 65536.0 * param_8);
    local_26c = (int)GHIDRA_FIST32((fVar18 * fVar14 + local_290 * fVar15) * 65536.0 * param_8);
  }
  else {
    fVar20 = fVar14 * local_288 * param_6 + local_28c * param_7 * fVar15;
    local_278 = (int)GHIDRA_FIST32(((fVar20 - (fVar17 * fVar14 + fVar19 * fVar15)) * 65536.0 * param_8) /
                           (float)(local_250 - iVar35));
    if (local_278 < 0) {
      local_278 = -local_278;
    }
    local_27c = (int)GHIDRA_FIST32((((local_290 * fVar15 + fVar18 * fVar14) - fVar20) * 65536.0 * param_8) /
                           (float)(local_250 - iVar29));
    if (local_27c < 0) {
      local_27c = -local_27c;
    }
    local_26c = (int)GHIDRA_FIST32(fVar20 * 65536.0 * param_8);
    local_268 = local_26c;
  }
  for (; local_250 < W_y1 - iVar26; local_250 = local_250 + 1) {
    iVar28 = local_27c;
    if (local_250 < iVar35) {
      iVar28 = -local_278;
    }
    local_268 = local_268 + iVar28;
    iVar28 = local_27c;
    if (iVar29 <= local_250) {
      iVar28 = -local_278;
    }
    local_26c = local_26c + iVar28;
  }
  if (W_y2 - iVar26 < local_298) {
    local_298 = W_y2 - iVar26;
  }
  iVar28 = SpriteDecompGetAndLockData(param_1,param_2);
  if (iVar28 == 0) {
    return 0;
  }
  iVar30 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  piVar31 = (int *)param_1[5];
  if (piVar31 == (int *)0x0) {
    piVar31 = SpriteArrayPalUpdateAndAccess((int)param_1,piVar23[0xc]);
  }
  else {
    EBPalUpdate(piVar31);
  }
  puVar1 = (ushort *)(piVar31 + 0x17);
  local_2a4 = puVar1;
  if (param_10 != 0x100) {
    local_2a4 = local_21c;
    if (param_10 == 0) {
      memset(local_21c,0,piVar23[5] * 2);
    }
    else if (param_10 == 0x80) {
      iVar39 = 1;
      iVar38 = piVar23[5];
      if (1 < iVar38) {
        do {
          local_21c[iVar39] = puVar1[iVar39] >> 1 & 0xfbef;
          iVar39 = iVar39 + 1;
        } while (iVar39 < iVar38);
      }
    }
    else {
      iVar39 = 1;
      iVar38 = piVar23[5];
      if (1 < iVar38) {
        do {
          uVar27 = (uint)puVar1[iVar39];
          local_21c[iVar39] =
               (ushort)((uVar27 & 0xf800) * param_10 >> 8) & 0xf800 |
               (ushort)((uVar27 & 0x7e0) * param_10 >> 8) & 0x7e0 |
               (ushort)((uVar27 & 0x1f) * param_10 >> 8) & 0x1f;
          iVar39 = iVar39 + 1;
        } while (iVar39 < iVar38);
      }
    }
  }
  if (param_11 == 0) {
    if (local_250 <= local_298) {
      do {
        iVar38 = local_268 >> 0x10;
        iVar39 = local_26c >> 0x10;
        if (W_x2 < iVar25 - iVar38) {
          iVar38 = iVar25 - W_x2;
        }
        if (iVar25 - iVar39 < W_x1) {
          iVar39 = iVar25 - W_x1;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar37 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 - iVar38) * 2);
        iVar36 = (iVar39 - iVar38) + 1;
        iVar11 = iVar39 - iVar38;
        iVar34 = iVar4 * iVar36 + iVar37;
        for (iVar36 = local_264 + iVar3 * iVar36;
            (SBORROW4(iVar39,iVar38) == iVar11 < 0 &&
            (((iVar8 <= iVar34 >> 0x10 || (iVar7 <= iVar36 >> 0x10)) ||
             ((iVar34 >> 0x10 < 0 || (iVar36 >> 0x10 < 0)))))); iVar36 = iVar36 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar34 = iVar34 - iVar4;
          iVar11 = iVar39 - iVar38;
        }
        for (; (iVar38 <= iVar39 &&
               ((((iVar8 <= iVar37 >> 0x10 || (iVar7 <= local_264 >> 0x10)) || (iVar37 >> 0x10 < 0))
                || (local_264 >> 0x10 < 0)))); local_264 = local_264 + iVar3) {
          local_238 = local_238 + -1;
          iVar38 = iVar38 + 1;
          iVar37 = iVar37 + iVar4;
        }
        iVar38 = (iVar39 - iVar38) + 1;
        if (0 < iVar38) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar28 + *(int *)(iVar6 + (iVar37 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              *local_238 = local_2a4[bVar5];
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + -1;
            iVar37 = iVar37 + iVar4;
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
        }
        iVar38 = local_27c;
        if (local_250 < iVar35) {
          iVar38 = -local_278;
        }
        local_268 = local_268 + iVar38;
        iVar38 = local_27c;
        if (iVar29 <= local_250) {
          iVar38 = -local_278;
        }
        local_26c = local_26c + iVar38;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if ((param_10 + param_11 < 0x101) && (param_11 == 0x80)) {
    if (local_250 <= local_298) {
      do {
        iVar38 = local_268 >> 0x10;
        iVar39 = local_26c >> 0x10;
        if (W_x2 < iVar25 - iVar38) {
          iVar38 = iVar25 - W_x2;
        }
        if (iVar25 - iVar39 < W_x1) {
          iVar39 = iVar25 - W_x1;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar37 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 - iVar38) * 2);
        iVar36 = (iVar39 - iVar38) + 1;
        iVar11 = iVar39 - iVar38;
        iVar34 = iVar4 * iVar36 + iVar37;
        for (iVar36 = local_264 + iVar3 * iVar36;
            (SBORROW4(iVar39,iVar38) == iVar11 < 0 &&
            ((((iVar8 <= iVar34 >> 0x10 || (iVar7 <= iVar36 >> 0x10)) || (iVar34 >> 0x10 < 0)) ||
             (iVar36 >> 0x10 < 0)))); iVar36 = iVar36 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar34 = iVar34 - iVar4;
          iVar11 = iVar39 - iVar38;
        }
        for (; (iVar38 <= iVar39 &&
               (((iVar8 <= iVar37 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
                ((iVar37 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3)
        {
          local_238 = local_238 + -1;
          iVar38 = iVar38 + 1;
          iVar37 = iVar37 + iVar4;
        }
        iVar38 = (iVar39 - iVar38) + 1;
        if (0 < iVar38) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar28 + *(int *)(iVar6 + (iVar37 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar22 = local_2a4[bVar5];
              uVar21 = *local_238 >> 1;
              *local_238 = (uVar21 & 0x3e0) + (uVar22 & 0x7e0) |
                           (uVar21 & 0x7800) + (uVar22 & 0xf800) | (uVar21 & 0xf) + (uVar22 & 0x1f);
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + -1;
            iVar37 = iVar37 + iVar4;
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
        }
        iVar38 = local_27c;
        if (local_250 < iVar35) {
          iVar38 = -local_278;
        }
        local_268 = local_268 + iVar38;
        iVar38 = local_27c;
        if (iVar29 <= local_250) {
          iVar38 = -local_278;
        }
        local_26c = local_26c + iVar38;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (param_10 + param_11 < 0x101) {
    if (local_250 <= local_298) {
      do {
        iVar38 = local_268 >> 0x10;
        iVar39 = local_26c >> 0x10;
        if (W_x2 < iVar25 - iVar38) {
          iVar38 = iVar25 - W_x2;
        }
        if (iVar25 - iVar39 < W_x1) {
          iVar39 = iVar25 - W_x1;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar37 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 - iVar38) * 2);
        iVar36 = (iVar39 - iVar38) + 1;
        iVar11 = iVar39 - iVar38;
        iVar34 = iVar4 * iVar36 + iVar37;
        for (iVar36 = local_264 + iVar3 * iVar36;
            (SBORROW4(iVar39,iVar38) == iVar11 < 0 &&
            (((iVar8 <= iVar34 >> 0x10 || (iVar7 <= iVar36 >> 0x10)) ||
             ((iVar34 >> 0x10 < 0 || (iVar36 >> 0x10 < 0)))))); iVar36 = iVar36 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar34 = iVar34 - iVar4;
          iVar11 = iVar39 - iVar38;
        }
        for (; (iVar38 <= iVar39 &&
               (((iVar8 <= iVar37 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
                ((iVar37 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3)
        {
          local_238 = local_238 + -1;
          iVar38 = iVar38 + 1;
          iVar37 = iVar37 + iVar4;
        }
        iVar38 = (iVar39 - iVar38) + 1;
        if (0 < iVar38) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar28 + *(int *)(iVar6 + (iVar37 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar22 = local_2a4[bVar5];
              uVar27 = (uint)*local_238;
              *local_238 = ((ushort)((uVar27 & 0x7e0) * param_11 >> 8) & 0x7e0) + (uVar22 & 0x7e0) |
                           ((ushort)((uVar27 & 0xf800) * param_11 >> 8) & 0xf800) +
                           (uVar22 & 0xf800) |
                           ((ushort)((uVar27 & 0x1f) * param_11 >> 8) & 0x1f) + (uVar22 & 0x1f);
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + -1;
            iVar37 = iVar37 + iVar4;
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
        }
        iVar38 = local_27c;
        if (local_250 < iVar35) {
          iVar38 = -local_278;
        }
        local_268 = local_268 + iVar38;
        iVar38 = local_27c;
        if (iVar29 <= local_250) {
          iVar38 = -local_278;
        }
        local_26c = local_26c + iVar38;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (param_11 == 0x80) {
    if (local_250 <= local_298) {
      do {
        iVar38 = local_268 >> 0x10;
        iVar39 = local_26c >> 0x10;
        if (W_x2 < iVar25 - iVar38) {
          iVar38 = iVar25 - W_x2;
        }
        if (iVar25 - iVar39 < W_x1) {
          iVar39 = iVar25 - W_x1;
        }
        local_264 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar13 -
                                ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254
                              ) + iVar9 * 0x10000;
        iVar37 = iVar10 * 0x10000 +
                 (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar16 +
                             ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
        local_238 = (ushort *)
                    (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                    (iVar25 - iVar38) * 2);
        iVar36 = (iVar39 - iVar38) + 1;
        iVar11 = iVar39 - iVar38;
        iVar34 = iVar4 * iVar36 + iVar37;
        for (iVar36 = local_264 + iVar3 * iVar36;
            (SBORROW4(iVar39,iVar38) == iVar11 < 0 &&
            (((iVar8 <= iVar34 >> 0x10 || (iVar7 <= iVar36 >> 0x10)) ||
             ((iVar34 >> 0x10 < 0 || (iVar36 >> 0x10 < 0)))))); iVar36 = iVar36 - iVar3) {
          iVar39 = iVar39 + -1;
          iVar34 = iVar34 - iVar4;
          iVar11 = iVar39 - iVar38;
        }
        for (; (iVar38 <= iVar39 &&
               ((((iVar8 <= iVar37 >> 0x10 || (iVar7 <= local_264 >> 0x10)) || (iVar37 >> 0x10 < 0))
                || (local_264 >> 0x10 < 0)))); local_264 = local_264 + iVar3) {
          local_238 = local_238 + -1;
          iVar38 = iVar38 + 1;
          iVar37 = iVar37 + iVar4;
        }
        iVar38 = (iVar39 - iVar38) + 1;
        if (0 < iVar38) {
          do {
            bVar5 = *(byte *)((local_264 >> 0x10) + iVar28 + *(int *)(iVar6 + (iVar37 >> 0x10) * 4))
            ;
            if (bVar5 != 0) {
              uVar32 = (uint)local_2a4[bVar5];
              uVar33 = (uint)(*local_238 >> 1);
              uVar27 = (uVar33 & 0x7800) + (uVar32 & 0xf800);
              if (0xf800 < uVar27) {
                uVar27 = 0xf800;
              }
              uVar2 = (uVar33 & 0x3e0) + (uVar32 & 0x7e0);
              uVar22 = (ushort)uVar2;
              if (0x7e0 < uVar2) {
                uVar22 = 0x7e0;
              }
              uVar32 = (uVar33 & 0xf) + (uVar32 & 0x1f);
              uVar21 = (ushort)uVar32;
              if (0x1f < uVar32) {
                uVar21 = 0x1f;
              }
              *local_238 = uVar22 | (ushort)uVar27 | uVar21;
            }
            local_264 = local_264 + iVar3;
            local_238 = local_238 + -1;
            iVar37 = iVar37 + iVar4;
            iVar38 = iVar38 + -1;
          } while (iVar38 != 0);
        }
        iVar38 = local_27c;
        if (local_250 < iVar35) {
          iVar38 = -local_278;
        }
        local_268 = local_268 + iVar38;
        iVar38 = local_27c;
        if (iVar29 <= local_250) {
          iVar38 = -local_278;
        }
        local_26c = local_26c + iVar38;
        local_250 = local_250 + 1;
      } while (local_250 <= local_298);
    }
  }
  else if (local_250 <= local_298) {
    do {
      iVar38 = local_268 >> 0x10;
      iVar39 = local_26c >> 0x10;
      if (W_x2 < iVar25 - iVar38) {
        iVar38 = iVar25 - W_x2;
      }
      if (iVar25 - iVar39 < W_x1) {
        iVar39 = iVar25 - W_x1;
      }
      local_264 = (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar13 -
                              ((float)local_250 / param_9) * fVar16) * 65536.0) / (float)local_254)
                  + iVar9 * 0x10000;
      iVar37 = iVar10 * 0x10000 +
               (int)GHIDRA_FIST32(((((float10)iVar38 / param_8) * fVar16 +
                           ((float)local_250 / param_9) * fVar13) * 65536.0) / (float)local_258);
      local_238 = (ushort *)
                  (iVar30 + *(int *)(*(int *)(iVar24 + 0x2c) + (local_250 + iVar26) * 4) +
                  (iVar25 - iVar38) * 2);
      iVar36 = (iVar39 - iVar38) + 1;
      iVar11 = iVar39 - iVar38;
      iVar34 = iVar4 * iVar36 + iVar37;
      for (iVar36 = local_264 + iVar3 * iVar36;
          (SBORROW4(iVar39,iVar38) == iVar11 < 0 &&
          ((((iVar8 <= iVar34 >> 0x10 || (iVar7 <= iVar36 >> 0x10)) || (iVar34 >> 0x10 < 0)) ||
           (iVar36 >> 0x10 < 0)))); iVar36 = iVar36 - iVar3) {
        iVar39 = iVar39 + -1;
        iVar34 = iVar34 - iVar4;
        iVar11 = iVar39 - iVar38;
      }
      for (; (iVar38 <= iVar39 &&
             (((iVar8 <= iVar37 >> 0x10 || (iVar7 <= local_264 >> 0x10)) ||
              ((iVar37 >> 0x10 < 0 || (local_264 >> 0x10 < 0)))))); local_264 = local_264 + iVar3) {
        local_238 = local_238 + -1;
        iVar38 = iVar38 + 1;
        iVar37 = iVar37 + iVar4;
      }
      iVar38 = (iVar39 - iVar38) + 1;
      if (0 < iVar38) {
        do {
          bVar5 = *(byte *)((local_264 >> 0x10) + iVar28 + *(int *)(iVar6 + (iVar37 >> 0x10) * 4));
          if (bVar5 != 0) {
            uVar32 = (uint)local_2a4[bVar5];
            uVar33 = (uint)*local_238;
            uVar27 = ((uVar33 & 0xf800) * param_11 >> 8 & 0xf800) + (uVar32 & 0xf800);
            if (0xf800 < uVar27) {
              uVar27 = 0xf800;
            }
            uVar2 = ((uVar33 & 0x7e0) * param_11 >> 8 & 0x7e0) + (uVar32 & 0x7e0);
            uVar22 = (ushort)uVar2;
            if (0x7e0 < uVar2) {
              uVar22 = 0x7e0;
            }
            uVar32 = ((uVar33 & 0x1f) * param_11 >> 8 & 0x1f) + (uVar32 & 0x1f);
            uVar21 = (ushort)uVar32;
            if (0x1f < uVar32) {
              uVar21 = 0x1f;
            }
            *local_238 = uVar22 | (ushort)uVar27 | uVar21;
          }
          local_264 = local_264 + iVar3;
          local_238 = local_238 + -1;
          iVar37 = iVar37 + iVar4;
          iVar38 = iVar38 + -1;
        } while (iVar38 != 0);
      }
      iVar38 = local_27c;
      if (local_250 < iVar35) {
        iVar38 = -local_278;
      }
      local_268 = local_268 + iVar38;
      iVar38 = local_27c;
      if (iVar29 <= local_250) {
        iVar38 = -local_278;
      }
      local_26c = local_26c + iVar38;
      local_250 = local_250 + 1;
    } while (local_250 <= local_298);
  }
  uVar27 = SpriteDecompUnlockData();
  return uVar27;
}
#undef local_2a4
#undef local_298
#undef local_294
#undef local_290
#undef local_28c
#undef local_288
#undef local_27c
#undef local_278
#undef local_26c
#undef local_268
#undef local_264
#undef local_258
#undef local_254
#undef local_250
#undef local_238
#undef local_220
#undef local_21c

