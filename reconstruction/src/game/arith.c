/*
 * arith.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08082880-0x08085231, 21 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ipow @ 0x08082880, 74 bytes */
int ipow(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  
  bVar2 = 1;
  iVar1 = 1;
  if ((param_2 != 0) && (iVar1 = param_1, 1 < param_2)) {
    do {
      iVar1 = iVar1 * iVar1;
      if ((param_2 >> (bVar2 - 1 & 0x1f) & 1U) != 0) {
        iVar1 = iVar1 * param_1;
      }
      bVar2 = bVar2 + 1;
    } while (1 << (bVar2 & 0x1f) <= param_2);
  }
  return iVar1;
}

/* StackErrorExit @ 0x080828d0, 26 bytes */
void StackErrorExit(void)

{
  sprintf((char *)ErrorMessage,"Parser stack overflow error");
  ErrorExit();
  return;
}

/* PriorityCheck @ 0x080828f0, 137 bytes */
undefined4 PriorityCheck(undefined4 param_1)

{
  switch(param_1) {
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

/* OpLength @ 0x08082980, 35 bytes */
undefined4 OpLength(undefined4 param_1)

{
  switch(param_1) {
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

/* OpTypeCheck @ 0x080829b0, 37 bytes */
bool OpTypeCheck(undefined4 param_1,int param_2)

{
  switch(param_1) {
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
    return param_2 == 1;
  default:
    return false;
  }
}

/* OperCode @ 0x080829e0, 228 bytes */
int OperCode(undefined1 *param_1)

{
  switch(*param_1) {
  case 0x21:
    return ((param_1[1] != '=') - 1 & 0xfffffff5) + 0xd;
  default:
    return 0;
  case 0x25:
    return 0x1b;
  case 0x26:
    return (uint)(param_1[1] != '&') * 5 + 0xb;
  case 0x28:
    return 0x1c;
  case 0x29:
    return 0x1d;
  case 0x2a:
    return ((param_1[1] != '*') - 1 & 0xfffffff6) + 0x19;
  case 0x2b:
    return 0x17;
  case 0x2d:
    return 0x18;
  case 0x2f:
    return 0x1a;
  case 0x3a:
    return ((param_1[1] == '=') - 1 & 0xffffffec) + 0x14;
  case 0x3c:
    return (uint)(param_1[1] == '=') * 2 + 4;
  case 0x3d:
    return 1;
  case 0x3e:
    return (uint)(param_1[1] == '=') * 2 + 3;
  case 0x5e:
    return (uint)(param_1[1] != '^') * 4 + 0xe;
  case 0x7c:
    return (uint)(param_1[1] != '|') * 5 + 0xc;
  case 0x7e:
    return 0x16;
  }
}

/* InfToPostArray @ 0x08082ad0, 3243 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: float words copied as bytes: 4 copies, 0 array reads (apply_bits_copies)
 * FIXUP: frame emulation: 16 stack locals placed at their original offsets in a 0x5f0-byte frame (a local's address escapes, see apply_frame_emulation) */
char * InfToPostArray(byte *param_1,float *param_2,void *param_3,int param_4,byte *param_5,
                     undefined4 *param_6,int param_7)

{
  int *piVar1;
  char cVar2;
  size_t sVar3;
  undefined3 extraout_var;
  byte *pbVar4;
  byte *extraout_ECX;
  byte *extraout_ECX_00;
  uint uVar5;
  byte bVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  byte *pbVar11;
  float *pfVar12;
  bool bVar13;
  bool bVar14;
  longdouble lVar15;
  char *pcVar16;
  int vstack [132];
  unsigned char ghidra_frame[0x5f0] __attribute__((aligned(16)));
#define local_5e4 (*(byte **)(ghidra_frame + 0xc))
#define local_5c8 (*(uint *)(ghidra_frame + 0x28))
#define local_5c4 (*(uint *)(ghidra_frame + 0x2c))
#define local_5ac (*(int *)(ghidra_frame + 0x44))
#define local_5a8 (*(int *)(ghidra_frame + 0x48))
#define local_5a4 (*(char **)(ghidra_frame + 0x4c))
#define local_5a0 (*(char **)(ghidra_frame + 0x50))
#define local_59c (*(int *)(ghidra_frame + 0x54))
#define local_598 (*(char **)(ghidra_frame + 0x58))
#define local_594 (*(char **)(ghidra_frame + 0x5c))
#define local_590 (*(byte *(*)[12])(ghidra_frame + 0x60))
#define local_560 (*(float *)(ghidra_frame + 0x90))
#define local_55c (*(byte (*)[64])(ghidra_frame + 0x94))
#define local_51c (*(char (*)[128])(ghidra_frame + 0xd4))
#define local_49c (*(byte (*)[128])(ghidra_frame + 0x154))
#define local_41c (*(float (*)[127])(ghidra_frame + 0x1d4))
  
  local_59c = 0;
  local_5a0 = (char *)0x0;
  local_5a4 = (char *)0x0;
  local_5a8 = -1;
  local_5ac = 0;
  if (param_1 == (byte *)0x0) {
    return (char *)0xffffffff;
  }
  local_5e4 = param_1;
LAB_08083527:
  do {
    sVar3 = strlen((char *)local_5e4);
    pbVar4 = extraout_ECX;
    if ((sVar3 == 0) || ((pbVar4 = local_5e4, param_6 != (undefined4 *)0x0 && (*local_5e4 == 0x2c)))
       ) {
LAB_08083557:
      if (local_5a8 < 0) goto LAB_080835a3;
      pbVar4 = local_55c;
      goto LAB_08083573;
    }
    if ((((*(byte *)(__ctype_b + 1 + (char)*local_5e4 * 2) & 8) != 0) ||
        ((((bVar6 = *local_5e4, bVar6 == 0x2d &&
           ((*(byte *)(__ctype_b + 1 + (char)local_5e4[1] * 2) & 8) != 0)) ||
          ((bVar6 == 0x2e && ((*(byte *)(__ctype_b + 1 + (char)local_5e4[1] * 2) & 8) != 0)))) ||
         (((bVar6 == 0x2d && (local_5e4[1] == 0x2e)) &&
          ((*(byte *)(__ctype_b + 1 + (char)local_5e4[2] * 2) & 8) != 0)))))) &&
       (((local_5ac != 1 && (local_5ac != 4)) && (local_5ac != 6)))) {
      local_5ac = 1;
      if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
      uVar5 = __strtol_internal(local_5e4,local_590,10,0);
      bVar13 = *local_590[0] < 0x2e;
      if (*local_590[0] == 0x2e) {
LAB_08082c18:
        lVar15 = __strtod_internal((int)local_5e4,(int *)local_590,0);
        local_560 = (float)lVar15;
        vstack[(int)(local_5a0 + 1)] = GHIDRA_F2I(int, local_560);
        local_5a0[(int)local_49c] = '\x01';
      }
      else {
        iVar8 = 2;
        bVar14 = false;
        pbVar11 = &DAT_082774ff;
        do {
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          bVar13 = *pbVar4 < *pbVar11;
          bVar14 = *pbVar4 == *pbVar11;
          pbVar4 = pbVar4 + 1;
          pbVar11 = pbVar11 + 1;
        } while (bVar14);
        if ((!bVar13 && !bVar14) == bVar13) goto LAB_08082c18;
        vstack[(int)(local_5a0 + 1)] = uVar5;
        local_5a0[(int)local_49c] = '\0';
      }
      local_5a0 = local_5a0 + 1;
      local_5e4 = local_590[0];
      goto LAB_08083527;
    }
    iVar8 = OperCode(local_5e4);
    if (iVar8 == 0) {
      bVar6 = *local_5e4;
    }
    else {
      bVar13 = false;
      bVar6 = *local_5e4;
      pbVar4 = (byte *)0x0;
      if ((bVar6 == 0x28) || (bVar6 == 0x5b)) {
        pbVar4 = (byte *)0x1;
      }
      if (pbVar4 == (byte *)0x0) {
        pbVar4 = (byte *)0x0;
        if ((bVar6 == 0x29) || (bVar6 == 0x5d)) {
          pbVar4 = (byte *)0x1;
        }
        if (pbVar4 != (byte *)0x0) goto LAB_08082ccc;
      }
      else {
LAB_08082ccc:
        bVar13 = true;
      }
      if (!bVar13) {
        if ((iVar8 == 0x18) && (((local_5ac == 0 || (local_5ac == 5)) || (local_5ac == 2)))) {
          iVar8 = 0x13;
        }
        if (local_5ac == 2) {
          cVar2 = (char)iVar8;
          bVar13 = false;
          if (((cVar2 == '\r') || (cVar2 == '~')) || (cVar2 == '\x13')) {
            bVar13 = true;
          }
          if (!bVar13) goto LAB_0808373b;
        }
        if (iVar8 == 0x14) {
          if (local_5ac != 4) goto LAB_0808373b;
          piVar1 = (int *)vstack[(int)local_5a0];
          if ((1 < *piVar1 - 0x157U) || (piVar1[1] != 0)) goto LAB_0808373b;
          if (*piVar1 == 0x158) {
            iVar8 = 0x15;
          }
          iVar9 = PriorityCheck((int)(char)iVar8);
          if ((((iVar9 < local_59c) && (bVar6 = local_55c[local_5a8], bVar6 != 0x1c)) &&
              (bVar6 != 0x14)) && (bVar6 != 0x15)) goto LAB_0808373b;
          TriggerFree(piVar1);
          local_5a0 = local_5a0 + -1;
        }
        local_5ac = 2;
        do {
          bVar13 = false;
          if (iVar8 == 0x14) {
LAB_08082e51:
            bVar13 = true;
          }
          else {
            bVar14 = false;
            if (((iVar8 == 0xd) || (iVar8 == 0x7e)) || (iVar8 == 0x13)) {
              bVar14 = true;
            }
            if (bVar14) goto LAB_08082e51;
          }
          if ((bVar13) || (iVar9 = PriorityCheck(iVar8), local_59c < iVar9)) {
            bVar13 = false;
            if (iVar8 == 0x14) {
LAB_08082e91:
              bVar13 = true;
            }
            else {
              bVar14 = false;
              if (((iVar8 == 0xd) || (iVar8 == 0x7e)) || (iVar8 == 0x13)) {
                bVar14 = true;
              }
              if (bVar14) goto LAB_08082e91;
            }
            if ((!bVar13) || (iVar9 = PriorityCheck(iVar8), local_59c <= iVar9)) goto LAB_08082e9e;
          }
          if (local_5a8 == -1) goto LAB_08082e9e;
          vstack[(int)(local_5a0 + 1)] = (int)(char)local_55c[local_5a8];
          local_5a0[(int)local_49c] = '\x02';
          local_5a0 = local_5a0 + 1;
          iVar9 = local_5a8 + -1;
          if (iVar9 < 0) {
            local_59c = 0;
            local_5a8 = iVar9;
          }
          else {
            local_59c = PriorityCheck((int)(char)local_55c[local_5a8 + -1]);
            local_5a8 = iVar9;
          }
        } while( true );
      }
    }
    if (bVar6 != 0x5b) {
      if (bVar6 != 0x28) {
        bVar13 = false;
        if ((bVar6 == 0x29) || (bVar6 == 0x5d)) {
          bVar13 = true;
        }
        if (bVar13) {
          if (param_6 != (undefined4 *)0x0) goto LAB_08083557;
          goto LAB_0808373b;
        }
        bVar13 = false;
        if (((*(byte *)(__ctype_b + (char)bVar6 * 2) & 8) != 0) || (bVar6 == 0x5f)) {
          bVar13 = true;
        }
        if (bVar13) {
          pcVar16 = SCtrlParseTrigger((char *)local_5e4,param_4,vstack + (int)(local_5a0 + 1),
                                      local_49c + (int)local_5a0,(int)param_5 - (int)local_5a0,
                                      (int *)local_590);
          if (pcVar16 == (char *)0x0) {
            pcVar16 = "Died parsing %s";
            param_5 = (byte *)0x0;
            goto LAB_0808372e;
          }
          local_5a0 = local_5a0 + (int)pcVar16;
          local_5ac = 4;
          if ((int)param_5 < (int)local_5a0) {
            pcVar16 = "Overabundance.";
            param_1 = param_5;
            goto LAB_0808372e;
          }
          local_5e4 = local_590[0];
        }
        else {
          if ((*(byte *)(__ctype_b + 1 + (char)*local_5e4 * 2) & 0x20) == 0) goto LAB_0808373b;
          local_5e4 = local_5e4 + 1;
        }
        goto LAB_08083527;
      }
      OperCode(local_5e4);
      if (local_5ac == 1) goto LAB_0808373b;
      pcVar16 = InfToPostArray(local_5e4 + 1,local_41c,local_51c,param_4,param_5 + -(int)local_5a0,
                               &local_598,0);
      if (pcVar16 != (char *)0x0) {
        if (*local_598 != ',') {
          if (*local_598 != ')') goto LAB_0808373b;
          pfVar10 = local_41c;
          pfVar12 = (float *)(vstack + (int)(local_5a0 + 1));
          for (uVar5 = (uint)pcVar16 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
            __builtin_memcpy(pfVar12, pfVar10, 4);
            pfVar10 = pfVar10 + 1;
            pfVar12 = pfVar12 + 1;
          }
          pbVar4 = local_49c + (int)local_5a0;
          local_5a0 = local_5a0 + (int)pcVar16;
          memcpy(pbVar4,local_51c,(size_t)pcVar16);
          local_5e4 = (byte *)(local_598 + 1);
          local_5ac = 6;
          goto LAB_08083527;
        }
        local_5a4 = InfToPostArray((byte *)(local_598 + 1),local_41c + (int)pcVar16,
                                   local_51c + (int)pcVar16,param_4,
                                   param_5 + -(int)local_5a0 + -(int)pcVar16,&local_598,0);
        if (local_5a4 == (char *)0x0) goto LAB_0808373b;
        bVar13 = false;
        if ((*local_598 == ')') || (*local_598 == ']')) {
          bVar13 = true;
        }
        if (!bVar13) goto LAB_0808373b;
        pcVar7 = local_598 + 1;
        bVar6 = *(byte *)(__ctype_b + 1 + local_598[1] * 2);
        while ((bVar6 & 0x20) != 0) {
          pcVar7 = pcVar7 + 1;
          bVar6 = *(byte *)(__ctype_b + 1 + *pcVar7 * 2);
        }
        if ((*pcVar7 != ')') && (*pcVar7 != '\0')) goto LAB_0808373b;
      }
      if ((local_5ac - 5U < 2) || ((local_5a8 == -1 || (1 < (int)(char)local_55c[local_5a8] - 1U))))
      goto LAB_0808373b;
      local_5ac = 3;
      local_5c8 = (uint)(*local_598 != ')');
      while (iVar8 = PriorityCheck(local_5c8 + 7), iVar8 <= local_59c) {
        if (local_5a8 == -1) {
          local_59c = 0;
          break;
        }
        iVar8 = local_5a8 + -1;
        if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
        vstack[(int)(local_5a0 + 1)] = (int)(char)local_55c[local_5a8];
        local_5a0[(int)local_49c] = '\x02';
        local_5a0 = local_5a0 + 1;
        if (iVar8 < 0) {
          local_59c = 0;
          local_5a8 = iVar8;
        }
        else {
          local_59c = PriorityCheck((int)(char)local_55c[local_5a8 + -1]);
          local_5a8 = iVar8;
        }
      }
      pcVar16 = local_5a4 + (int)pcVar16;
      pfVar10 = local_41c;
      pfVar12 = (float *)(vstack + (int)(local_5a0 + 1));
      for (uVar5 = (uint)pcVar16 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
        __builtin_memcpy(pfVar12, pfVar10, 4);
        pfVar10 = pfVar10 + 1;
        pfVar12 = pfVar12 + 1;
      }
      memcpy(local_5a0 + (int)local_49c,local_51c,(size_t)pcVar16);
      local_5a0 = local_5a0 + (int)pcVar16;
      local_5e4 = (byte *)(local_598 + 1);
      if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
      vstack[(int)(local_5a0 + 1)] = local_5c8 + 7;
      local_5a0[(int)local_49c] = '\x02';
      local_5a0 = local_5a0 + 1;
      goto LAB_08083527;
    }
    bVar13 = false;
    if (((local_5ac != 2) || (local_5a8 == -1)) || (1 < (int)(char)local_55c[local_5a8] - 1U))
    goto LAB_0808373b;
    local_5ac = 3;
    pcVar16 = InfToPostArray(local_5e4 + 1,local_41c,local_51c,param_4,param_5 + -(int)local_5a0,
                             &local_594,0);
    if (((pcVar16 == (char *)0x0) || (*local_594 != ',')) ||
       (local_5a4 = InfToPostArray((byte *)(local_594 + 1),local_41c + (int)pcVar16,
                                   pcVar16 + (int)local_51c,param_4,
                                   param_5 + -(int)local_5a0 + -(int)pcVar16,&local_594,0),
       local_5a4 == (char *)0x0)) goto LAB_0808373b;
    bVar14 = false;
    if ((*local_594 == ')') || (*local_594 == ']')) {
      bVar14 = true;
    }
    if (bVar14) {
      pcVar7 = local_594 + 1;
      if ((*(byte *)(__ctype_b + 1 + local_594[1] * 2) & 0x20) == 0) {
        cVar2 = local_594[1];
      }
      else {
        cVar2 = '\0';
        if (local_594[1] != '\0') {
          do {
            pcVar7 = pcVar7 + 1;
            if ((*(byte *)(__ctype_b + 1 + *pcVar7 * 2) & 0x20) == 0) {
              cVar2 = *pcVar7;
              goto LAB_08083017;
            }
          } while (*pcVar7 != '\0');
          cVar2 = '\0';
        }
      }
LAB_08083017:
      if ((cVar2 != ')') && (cVar2 != '\0')) goto LAB_0808301f;
      local_5c4 = (uint)(*local_594 != ')');
      while (iVar8 = PriorityCheck(local_5c4 + 9), iVar8 <= local_59c) {
        if (local_5a8 == -1) {
          local_59c = 0;
          break;
        }
        iVar8 = local_5a8 + -1;
        if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
        vstack[(int)(local_5a0 + 1)] = (int)(char)local_55c[local_5a8];
        local_5a0[(int)local_49c] = '\x02';
        local_5a0 = local_5a0 + 1;
        if (iVar8 < 0) {
          local_59c = 0;
          local_5a8 = iVar8;
        }
        else {
          local_59c = PriorityCheck((int)(char)local_55c[local_5a8 + -1]);
          local_5a8 = iVar8;
        }
      }
      pcVar16 = local_5a4 + (int)pcVar16;
      pfVar10 = local_41c;
      pfVar12 = (float *)(vstack + (int)(local_5a0 + 1));
      for (uVar5 = (uint)pcVar16 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
        __builtin_memcpy(pfVar12, pfVar10, 4);
        pfVar10 = pfVar10 + 1;
        pfVar12 = pfVar12 + 1;
      }
      memcpy(local_5a0 + (int)local_49c,local_51c,(size_t)pcVar16);
      local_5a0 = local_5a0 + (int)pcVar16;
      if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
      vstack[(int)(local_5a0 + 1)] = local_5c4 + 9;
      local_5a0[(int)local_49c] = '\x02';
      local_5a0 = local_5a0 + 1;
      local_5e4 = (byte *)(local_594 + 1);
    }
    else {
LAB_0808301f:
      bVar13 = true;
    }
    if (bVar13) goto LAB_0808373b;
  } while( true );
LAB_08082e9e:
  if (0x3f < local_5a8 + 1) {
    StackErrorExit();
  }
  local_55c[local_5a8 + 1] = (byte)iVar8;
  local_59c = PriorityCheck(iVar8);
  iVar8 = OpLength(iVar8);
  local_5e4 = local_5e4 + iVar8;
  local_5a8 = local_5a8 + 1;
  goto LAB_08083527;
  while( true ) {
    vstack[(int)(local_5a0 + 1)] = (int)(char)pbVar4[local_5a8];
    local_5a0[(int)local_49c] = '\x02';
    local_5a0 = local_5a0 + 1;
    local_5a8 = local_5a8 + -1;
    if (local_5a8 < 0) break;
LAB_08083573:
    if ((int)param_5 <= (int)local_5a0) goto LAB_0808373b;
  }
LAB_080835a3:
  if (local_5a0 == (char *)0x0) goto LAB_0808373b;
  if ((local_49c[0] < 2) && (local_5a0 == (char *)0x1)) {
    if ((param_7 == 2) && (local_49c[0] == 0)) {
      local_49c[0] = 1;
      vstack[1] = GHIDRA_F2I(int, (float)vstack[1]);
      goto LAB_08083610;
    }
    if ((param_7 != 1) || (local_49c[0] != 1)) goto LAB_08083610;
    pcVar16 = "Expected int value and read float.";
    param_1 = pbVar4;
    param_5 = pbVar4;
  }
  else {
LAB_08083610:
    iVar9 = 0;
    iVar8 = 0;
    if (0 < (int)local_5a0) {
      do {
        bVar6 = local_49c[iVar9];
        if (bVar6 < 2) {
LAB_080836a4:
          iVar8 = iVar8 + 1;
        }
        else {
          if (bVar6 != 2) {
            if (bVar6 == 3) {
              cVar2 = SCtrlTrigArity(*(int *)vstack[iVar9 + 1]);
              iVar8 = iVar8 - GHIDRA_ZEXT8(cVar2);
              pbVar4 = extraout_ECX_00;
              if (-1 < iVar8) goto LAB_080836a4;
            }
            goto switchD_08083643_default;
          }
          switch(vstack[iVar9 + 1]) {
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
            if (iVar8 < 2) goto switchD_08083643_default;
            iVar8 = iVar8 + -1;
            break;
          case 7:
          case 8:
          case 9:
          case 10:
            if (iVar8 < 3) goto switchD_08083643_default;
            iVar8 = iVar8 + -2;
            iVar9 = iVar9 + 1;
            break;
          case 0xd:
          case 0x13:
          case 0x16:
            if (iVar8 == 0) goto switchD_08083643_default;
            break;
          default:
            goto switchD_08083643_default;
          }
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < (int)local_5a0);
    }
    if (iVar8 == 1) {
      if (param_6 != (undefined4 *)0x0) {
        *param_6 = local_5e4;
      }
      pfVar10 = (float *)vstack;
      for (uVar5 = (uint)local_5a0 & 0x3fffffff; pfVar10 = pfVar10 + 1, uVar5 != 0;
          uVar5 = uVar5 - 1) {
        __builtin_memcpy(param_2, pfVar10, 4);
        param_2 = param_2 + 1;
      }
      memcpy(param_3,local_49c,(size_t)local_5a0);
      return local_5a0;
    }
switchD_08083643_default:
    pcVar16 = "Malformed expression encountered: %s";
    param_5 = pbVar4;
  }
LAB_0808372e:
  sprintf((char *)ErrorMessage,pcVar16,param_1,param_5);
LAB_0808373b:
  iVar8 = 0;
  if (0 < (int)local_5a0) {
    do {
      if (local_49c[iVar8] == 3) {
        TriggerFree((void *)vstack[iVar8 + 1]);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < (int)local_5a0);
  }
  return (char *)0x0;
}
#undef local_5e4
#undef local_5c8
#undef local_5c4
#undef local_5ac
#undef local_5a8
#undef local_5a4
#undef local_5a0
#undef local_59c
#undef local_598
#undef local_594
#undef local_590
#undef local_560
#undef local_55c
#undef local_51c
#undef local_49c
#undef local_41c

/* InfixToPostfix @ 0x08083780, 225 bytes
 * FIXUP: float words copied as bytes: 1 copies, 1 array reads (apply_bits_copies)
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x2a0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 InfixToPostfix(byte *param_1,int *param_2,int param_3,undefined4 *param_4,int param_5)

{
  undefined4 uVar1;
  char *__n;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  float *pfVar5;
  unsigned char ghidra_frame[0x2a0] __attribute__((aligned(16)));
#define local_29c (*(byte (*)[128])(ghidra_frame + 0x4))
#define local_21c (*(float (*)[131])(ghidra_frame + 0x84))
  
  uVar1 = 1;
  if (param_1 != (byte *)0x0) {
    __n = InfToPostArray(param_1,local_21c,local_29c,param_3,(byte *)0x80,param_4,param_5);
    if (__n == (char *)0x0) {
      uVar1 = 0;
    }
    else {
      if ((__n == (char *)0x1) && (local_29c[0] < 2)) {
        param_2[1] = 0;
        param_2[2] = GHIDRA_F2I_LV(int, local_21c[0]);
        *param_2 = (int)(char)local_29c[0];
      }
      else {
        iVar2 = ecalloc((size_t)__n,4);
        *param_2 = iVar2;
        iVar2 = ecalloc((size_t)__n,1);
        param_2[1] = iVar2;
        param_2[2] = (int)__n;
        pfVar4 = local_21c;
        pfVar5 = (float *)*param_2;
        for (uVar3 = (uint)__n & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          __builtin_memcpy(pfVar5, pfVar4, 4);
          pfVar4 = pfVar4 + 1;
          pfVar5 = pfVar5 + 1;
        }
        memcpy((void *)param_2[1],local_29c,(size_t)__n);
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}
#undef local_29c
#undef local_21c

/* FreeExpression @ 0x08083870, 114 bytes */
undefined4 FreeExpression(int *param_1)

{
  int iVar1;
  undefined4 in_EDX;
  int iVar2;
  int iVar3;
  
  iVar1 = param_1[1];
  if (iVar1 != 0) {
    iVar3 = 0;
    iVar2 = param_1[2];
    if (0 < iVar2) {
      while( true ) {
        if (*(char *)(iVar3 + iVar1) == '\x03') {
          TriggerFree(*(void **)(*param_1 + iVar3 * 4));
          iVar2 = param_1[2];
        }
        iVar3 = iVar3 + 1;
        if (iVar2 <= iVar3) break;
        iVar1 = param_1[1];
      }
    }
    free((void *)param_1[1]);
    free((void *)*param_1);
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return in_EDX;
}

/* FreeExpNoTrig @ 0x080838f0, 59 bytes */
void FreeExpNoTrig(undefined4 *param_1)

{
  if ((void *)param_1[1] != (void *)0x0) {
    free((void *)param_1[1]);
    free((void *)*param_1);
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

/* FreeExpArray @ 0x08083930, 68 bytes
 * REVIEW: pid-unaff_ */
undefined4 FreeExpArray(void *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 unaff_EBX;
  
  if (param_1 != (void *)0x0) {
    piVar1 = (int *)ArrayScanFirst((int)param_1);
    while (piVar1 != (int *)0x0) {
      FreeExpression(piVar1);
      piVar1 = (int *)ArrayScanNext((int)param_1);
    }
    uVar2 = ArrayFree(param_1);
    return uVar2;
  }
  return unaff_EBX;
}

/* ConstExpI @ 0x08083980, 50 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void ConstExpI(int *param_1,int param_2)

{
  undefined4 unaff_EBX;
  
  if (param_1[1] != 0) {
    FreeExpression(param_1);
    param_1[1] = 0;
  }
  *param_1 = 0;
  param_1[2] = param_2;
  return;
}

/* ConstExpF @ 0x080839c0, 52 bytes */
void ConstExpF(int *param_1,int param_2)

{
  if (param_1[1] != 0) {
    FreeExpression(param_1);
    param_1[1] = 0;
  }
  *param_1 = 1;
  param_1[2] = param_2;
  return;
}

/* expcpy @ 0x08083a00, 157 bytes */
undefined4 expcpy(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  FreeExpression(param_1);
  if (param_2[1] == 0) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
LAB_08083a90:
    uVar2 = 1;
  }
  else {
    iVar1 = ecalloc(param_2[2],4);
    *param_1 = iVar1;
    if (iVar1 != 0) {
      iVar1 = ecalloc(param_2[2],1);
      param_1[1] = iVar1;
      if (iVar1 != 0) {
        param_1[2] = param_2[2];
        puVar4 = (undefined4 *)*param_2;
        puVar5 = (undefined4 *)*param_1;
        for (uVar3 = param_2[2] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        memcpy((void *)param_1[1],(void *)param_2[1],param_2[2]);
        goto LAB_08083a90;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

/* expcpytrig @ 0x08083aa0, 148 bytes */
undefined4 expcpytrig(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  expcpy(param_1,param_2);
  iVar1 = param_1[1];
  if (iVar1 != 0) {
    iVar4 = 0;
    iVar3 = param_1[2];
    if (0 < iVar3) {
      while( true ) {
        if (*(char *)(iVar4 + iVar1) == '\x03') {
          piVar2 = (int *)ecalloc(1,0x38);
          if (piVar2 == (int *)0x0) {
            sprintf((char *)ErrorMessage,"Uh-oh. Alloc error",0,0);
            ErrorExit();
            return 0;
          }
          trigcpy(piVar2,*(int **)(*param_1 + iVar4 * 4));
          *(int **)(*param_1 + iVar4 * 4) = piVar2;
          iVar3 = param_1[2];
        }
        iVar4 = iVar4 + 1;
        if (iVar3 <= iVar4) break;
        iVar1 = param_1[1];
      }
    }
  }
  return 1;
}

/* ExpMulF @ 0x08083b40, 184 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
float ExpMulF(int *param_1,float param_2)

{
  void *pvVar1;
  float10 fVar2;
  int iVar3;
  
  if (param_1[1] == 0) {
    if (*param_1 == 0) {
      fVar2 = (float10)param_1[2] * param_2;
      *param_1 = 1;
      param_1[2] = GHIDRA_F2I(int, fVar2);
    }
    else {
      fVar2 = param_2 * GHIDRA_I2F(param_1[2]);
      param_1[2] = GHIDRA_F2I(int, fVar2);
    }
  }
  else {
    iVar3 = param_1[2];
    param_1[2] = iVar3 + 2;
    pvVar1 = realloc((void *)*param_1,(iVar3 + 2) * 4);
    *param_1 = (int)pvVar1;
    pvVar1 = realloc((void *)param_1[1],param_1[2]);
    iVar3 = *param_1;
    param_1[1] = (int)pvVar1;
    if ((iVar3 == 0) || (pvVar1 == (void *)0x0)) {
      ErrorExit();
      iVar3 = *param_1;
    }
    *(float *)(iVar3 + -8 + param_1[2] * 4) = param_2;
    *(undefined4 *)(iVar3 + -4 + param_1[2] * 4) = 0x19;
    *(undefined1 *)(param_1[2] + param_1[1] + -2) = 1;
    fVar2 = GHIDRA_I2F((param_1[2] + param_1[1]));
    *(undefined1 *)(GHIDRA_F2I(int, fVar2) + -1) = 2;
  }
  return fVar2;
}

/* ExpDivI @ 0x08083c00, 204 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
float ExpDivI(int *param_1,int param_2)

{
  int iVar1;
  float10 fVar2;
  void *pvVar3;
  int iVar4;
  
  if (param_1[1] == 0) {
    if (*param_1 == 0) {
      fVar2 = GHIDRA_I2F((param_1[2] / param_2));
    }
    else {
      fVar2 = GHIDRA_I2F(param_1[2]) / (float)param_2;
    }
    param_1[2] = GHIDRA_F2I(int, fVar2);
    *param_1 = 1;
  }
  else {
    iVar4 = param_1[2];
    param_1[2] = iVar4 + 2;
    pvVar3 = realloc((void *)*param_1,(iVar4 + 2) * 4);
    *param_1 = (int)pvVar3;
    pvVar3 = realloc((void *)param_1[1],param_1[2] << 2);
    iVar4 = *param_1;
    param_1[1] = (int)pvVar3;
    if ((iVar4 == 0) || (pvVar3 == (void *)0x0)) {
      sprintf((char *)ErrorMessage,"Can\'t realloc memory.",pvVar3,pvVar3);
      ErrorExit();
      iVar4 = *param_1;
    }
    *(int *)(iVar4 + -8 + param_1[2] * 4) = param_2;
    iVar1 = param_1[1];
    *(undefined4 *)(iVar4 + -4 + param_1[2] * 4) = 0x1a;
    *(undefined1 *)(param_1[2] + iVar1 + -2) = 0;
    fVar2 = GHIDRA_I2F((param_1[2] + param_1[1]));
    *(undefined1 *)(GHIDRA_F2I(int, fVar2) + -1) = 2;
  }
  return fVar2;
}

/* ShowExp @ 0x08083cd0, 360 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0xb0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ShowExp(char *param_1,int *param_2,int *param_3)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  char *pcVar4;
  float10 dVar5;
  unsigned char ghidra_frame[0xb0] __attribute__((aligned(16)));
#define local_a4 (*(int *)(ghidra_frame + 0xc))
#define local_a0 (*(float (*)[5])(ghidra_frame + 0x10))
#define local_8c (*(char *(*)[4])(ghidra_frame + 0x24))
#define local_7c (*(char **)(ghidra_frame + 0x34))
#define local_6c (*(char (*)[92])(ghidra_frame + 0x44))
  
  local_8c[0] = "int";
  local_8c[1] = "float";
  local_8c[2] = "oper";
  local_8c[3] = "trig";
  local_7c = "SC";
  if (param_2[1] == 0) {
    iVar2 = EvalExpression(param_3,param_2,&local_a4,(int *)local_a0);
    if (iVar2 == 1) {
      dVar5 = GHIDRA_L2D(CONCAT44(1,local_a4));
      pcVar4 = "%d (int)";
    }
    else {
      if (iVar2 != 2) {
        return;
      }
      dVar5 = (double)local_a0[0];
      pcVar4 = "%f (float)";
    }
    sprintf(param_1,pcVar4,dVar5);
  }
  else {
    iVar2 = 0;
    sprintf(param_1,"\nData: ");
    uVar3 = extraout_EDX;
    if (0 < param_2[2]) {
      do {
        cVar1 = *(char *)(iVar2 + param_2[1]);
        if (cVar1 == '\x01') {
          dVar5 = (double)*(float *)(*param_2 + iVar2 * 4);
          pcVar4 = "%f,";
        }
        else {
          if (cVar1 == '\x03') {
            dVar5 = GHIDRA_L2D(CONCAT44(CONCAT31((int3)((uint)param_2[1] >> 8),cVar1),
                                     **(undefined4 **)(*param_2 + iVar2 * 4)));
          }
          else {
            dVar5 = GHIDRA_L2D(CONCAT44(uVar3,*(undefined4 *)(*param_2 + iVar2 * 4)));
          }
          pcVar4 = "%d,";
        }
        sprintf(local_6c,pcVar4,dVar5);
        iVar2 = iVar2 + 1;
        strcat(param_1,local_6c);
        uVar3 = extraout_EDX_00;
      } while (iVar2 < param_2[2]);
    }
    sprintf(local_6c,"\nTypes: ",uVar3,uVar3);
    for (iVar2 = 0; strcat(param_1,local_6c), iVar2 < param_2[2]; iVar2 = iVar2 + 1) {
      sprintf(local_6c,"%s,",local_8c[*(char *)(iVar2 + param_2[1])],extraout_ECX);
    }
  }
  return;
}
#undef local_a4
#undef local_a0
#undef local_8c
#undef local_7c
#undef local_6c

/* EvalExpressionI @ 0x08083e40, 283 bytes
 * FIXUP: removed 1 x87 control-word save statements
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
int EvalExpressionI(int param_1,int *param_2,int param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(int *)(ghidra_frame + 0xc))
#define local_10 (*(float *)(ghidra_frame + 0x10))
#define local_c (*(int *)(ghidra_frame + 0x14))
#define local_8 (*(undefined2 *)(ghidra_frame + 0x18))
#define uStack_6 (*(undefined2 *)(ghidra_frame + 0x1a))
  
  iVar1 = EvalExpression((int *)param_1,param_2,&local_14,(int *)&local_10);
  if (iVar1 == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0xbf4),
            extraout_ECX,extraout_ECX);
    ErrorExit();
  }
  else if (iVar1 == 2) {
    local_14 = (int)GHIDRA_FIST32(local_10);
    if (param_3 != 0) {
      local_c = local_14;
      ClipboardAppend((int *)g[0x81d1],
                      "%i Warning: expression truncated to integer:\nplayer %s (%i) in state %i: %f"
                      ,g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),
                      *(undefined4 *)(param_1 + 0xbf4),(double)local_10);
    }
  }
  else if (iVar1 == 3) {
    ClipboardAppend((int *)g[0x81d1],
                    "%i Warning: expression short-circuited, returning 0:\nplayer %s (%i) in state %i"
                    ,g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),
                    *(undefined4 *)(param_1 + 0xbf4),extraout_ECX,extraout_ECX);
    local_14 = 0;
  }
  return local_14;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8
#undef uStack_6

/* EvalExpressionF @ 0x08083f60, 182 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
float EvalExpressionF(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  float in_EDX;
  undefined4 extraout_EDX;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_c (*(float *)(ghidra_frame + 0x4))
#define local_8 (*(float *)(ghidra_frame + 0x8))
  
  local_c = in_EDX;
  local_8 = in_EDX;
  iVar1 = EvalExpression(param_1,param_2,(int *)&local_c,(int *)&local_8);
  if (iVar1 == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[0x7304],param_1 + 8,param_1[1],param_1[0x2fd],extraout_ECX,extraout_ECX);
    ErrorExit();
  }
  else if (iVar1 == 1) {
    local_8 = (float10)GHIDRA_F2I(int, local_c);
  }
  else if (iVar1 == 3) {
    ClipboardAppend((int *)g[0x81d1],
                    "%i Warning: expression short-circuited, returning 0: player %s (%i) in state %i"
                    ,g[0x7304],param_1 + 8,param_1[1],param_1[0x2fd],extraout_EDX,extraout_EDX);
    local_8 = 0.0;
  }
  return local_8;
}
#undef local_c
#undef local_8

/* EvalExpression @ 0x08084020, 4625 bytes
 * REVIEW: pid-unaff_
 * FIXUP: 2 data addresses written as literals replaced by data-image references
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 32-bit operand words fVar8, fVar4, unaff_EDI kept as raw words (ghidra_word32), see WORD32_OPERANDS
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 EvalExpression(int *param_1,int *param_2,int *param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  ghidra_word32 fVar4;
  int iVar5;
  bool bVar6;
  undefined3 extraout_var;
  int iVar7;
  ghidra_word32 fVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  int unaff_EBP;
  ghidra_word32 unaff_EDI;
  float10 dVar12;
  char *pcVar13;
  int local_144;
  float local_140;
  float local_120;
  float local_11c;
  float local_118;
  int local_114;
  
  piVar2 = MyStackIdx;
  local_118 = 0.0;
  local_11c = 0.0;
  local_120 = 0.0;
  iVar7 = param_2[1];
  if (iVar7 == 0) {
    if (*param_2 == 0) {
      *param_3 = param_2[2];
      return 1;
    }
    if (*param_2 != 1) {
      return 0;
    }
    *param_4 = param_2[2];
    return 2;
  }
  local_114 = 0;
  if (0 < param_2[2]) {
    do {
      cVar3 = *(char *)(local_114 + iVar7);
      if (cVar3 != '\x02') {
        if (cVar3 < '\x03') {
          if (cVar3 < '\0') {
LAB_08084ff7:
            local_144 = *param_2;
            goto LAB_08085004;
          }
          iVar7 = *(int *)(*param_2 + local_114 * 4);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          piVar9 = (int *)((int)MyStackIdx + 1);
          MyStackIdx = piVar9;
          MyStack[(int)piVar9] = iVar7;
          cVar3 = *(char *)(local_114 + param_2[1]);
          if (0x7e < (int)piVar9) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = (int)cVar3;
        }
        else {
          if (cVar3 != '\x03') goto LAB_08084ff7;
          SCtrlTrigEval(param_1,*(int **)(*param_2 + local_114 * 4));
        }
        goto switchD_0808437f_default;
      }
      piVar9 = MyStackIdx;
      if ((int)MyStackIdx < 0) goto LAB_080851e2;
      piVar9 = (int *)((int)MyStackIdx + -1);
      if ((int)piVar9 < 0) goto LAB_080851e2;
      piVar1 = (int *)((int)MyStackIdx + -2);
      fVar8.i = (MyStack[(int)piVar9]);
      unaff_EBP = 1;
      if (MyStack[(int)MyStackIdx] == 1) {
        unaff_EBP = 2;
        local_118 = fVar8.f;
      }
      local_144 = *param_2;
      iVar7 = *(int *)(local_144 + local_114 * 4);
      bVar6 = false;
      if (((iVar7 == 0xd) || (iVar7 == 0x7e)) || (iVar7 == 0x13)) {
        bVar6 = true;
      }
      if (!bVar6) {
        piVar9 = piVar1;
        if ((int)piVar1 < 0) goto LAB_080851e2;
        piVar9 = (int *)((int)MyStackIdx + -3);
        if ((int)piVar9 < 0) goto LAB_080851e2;
        unaff_EDI.i = (MyStack[(int)piVar9]);
        if ((unaff_EBP == 2) || (MyStack[(int)piVar1] == 1)) {
          local_11c = unaff_EDI.f;
          if (unaff_EBP == 2) {
            if (MyStack[(int)piVar1] == 0) {
              local_11c = (float)((int)unaff_EDI.i);
            }
          }
          else {
            local_118 = (float)((int)fVar8.i);
            unaff_EBP = 2;
          }
        }
        local_144 = *param_2;
        piVar1 = MyStackIdx + -1;
      }
      MyStackIdx = piVar1;
      bVar6 = OpTypeCheck(*(undefined4 *)(local_144 + local_114 * 4),unaff_EBP);
      if (GHIDRA_ZEXT8(bVar6) == 0) {
        sprintf((char *)(g + 0x81d2),"Type mismatch detected: %d",
                *(undefined4 *)(*param_2 + local_114 * 4));
        ShowExp((char *)ErrorMessage,param_2,param_1);
        ErrorExit();
      }
      local_144 = *param_2;
      switch(*(undefined4 *)(local_144 + local_114 * 4)) {
      case 1:
      case 2:
        if (unaff_EBP == 1) {
          bVar6 = unaff_EDI.i == fVar8.i;
        }
        else {
          bVar6 = local_11c == local_118;
        }
        uVar10 = (uint)bVar6;
        if (*(int *)(local_144 + local_114 * 4) != 1) {
          uVar10 = (uint)(uVar10 == 0);
        }
        goto LAB_08084bab;
      case 3:
      case 6:
        if (unaff_EBP == 1) {
          bVar6 = ((int)fVar8.i) < ((int)unaff_EDI.i);
        }
        else {
          bVar6 = local_118 < local_11c;
        }
        uVar10 = (uint)bVar6;
        if (*(int *)(local_144 + local_114 * 4) != 3) {
          uVar10 = (uint)(uVar10 == 0);
        }
        goto LAB_0808488f;
      case 4:
      case 5:
        if (unaff_EBP == 1) {
          bVar6 = ((int)unaff_EDI.i) < ((int)fVar8.i);
        }
        else {
          bVar6 = local_11c < local_118;
        }
        uVar10 = (uint)bVar6;
        if (*(int *)(local_144 + local_114 * 4) != 4) {
          uVar10 = (uint)(uVar10 == 0);
        }
        goto LAB_08084bab;
      case 7:
      case 8:
      case 9:
      case 10:
        piVar9 = MyStackIdx;
        if (((*(char *)(local_114 + 1 + param_2[1]) != '\x02') ||
            (1 < *(int *)(local_144 + 4 + local_114 * 4) - 1U)) || ((int)MyStackIdx < 0))
        goto LAB_080851e2;
        iVar7 = MyStack[(int)MyStackIdx];
        piVar9 = (int *)((int)MyStackIdx + -1);
        if ((int)piVar9 < 0) goto LAB_080851e2;
        fVar4.i = (MyStack[(int)piVar9]);
        MyStackIdx = (int *)((int)MyStackIdx + -2);
        if (iVar7 == 4) goto LAB_08084ff7;
        iVar5 = *param_2;
        uVar10 = (uint)(*(int *)(iVar5 + 4 + local_114 * 4) == 1);
        uVar11 = uVar10 ^ 1;
        if (iVar7 == 1) {
          local_120 = fVar4.f;
        }
        if ((unaff_EBP == 1) && (iVar7 == 1)) {
          unaff_EBP = 2;
          local_118 = (float)((int)fVar8.i);
          local_11c = (float)((int)unaff_EDI.i);
        }
        else if ((unaff_EBP == 2) && (iVar7 == 0)) {
          local_120 = (float)((int)fVar4.i);
        }
        if (unaff_EBP == 1) {
          iVar7 = *(int *)(iVar5 + local_114 * 4);
          if (iVar7 == 8) {
            if ((((int)fVar4.i) <= ((int)unaff_EDI.i)) || (((int)fVar8.i) < ((int)fVar4.i))) {
LAB_08084f06:
              uVar10 = uVar11;
            }
          }
          else if (iVar7 < 9) {
            if (iVar7 != 7) goto LAB_08084fac;
            if ((((int)fVar4.i) <= ((int)unaff_EDI.i)) || (((int)fVar8.i) <= ((int)fVar4.i))) {
LAB_08084f40:
              uVar10 = uVar11;
            }
          }
          else if (iVar7 == 9) {
            if ((((int)fVar4.i) < ((int)unaff_EDI.i)) || (((int)fVar8.i) <= ((int)fVar4.i))) goto LAB_08084f71;
          }
          else {
            if (iVar7 != 10) goto LAB_08084fac;
            if ((((int)fVar4.i) < ((int)unaff_EDI.i)) || (((int)fVar8.i) < ((int)fVar4.i))) goto LAB_08084f40;
          }
joined_r0x08084f11:
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = uVar10;
        }
        else {
          iVar7 = *(int *)(iVar5 + local_114 * 4);
          if (iVar7 == 8) {
            if ((local_120 <= local_11c) || (local_118 < local_120)) goto LAB_08084f06;
            goto joined_r0x08084f11;
          }
          if (iVar7 < 9) {
            if (iVar7 == 7) {
              if (local_11c < local_120) {
                bVar6 = local_118 <= local_120;
LAB_08084f6b:
                if (!bVar6) goto joined_r0x08084f11;
              }
LAB_08084f71:
              uVar10 = uVar11;
              goto joined_r0x08084f11;
            }
          }
          else {
            if (iVar7 == 9) {
              if ((local_120 < local_11c) || (local_118 <= local_120)) goto LAB_08084f40;
              goto joined_r0x08084f11;
            }
            if (iVar7 == 10) {
              if (local_11c <= local_120) {
                bVar6 = local_118 < local_120;
                goto LAB_08084f6b;
              }
              goto LAB_08084f71;
            }
          }
        }
LAB_08084fac:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        local_114 = local_114 + 1;
        MyStack[(int)MyStackIdx] = 0;
        break;
      case 0xb:
        if (unaff_EBP == 1) {
          iVar7 = 0;
          if ((unaff_EDI.i != 0) && (fVar8.i != 0)) {
            iVar7 = 1;
          }
        }
        else {
          iVar7 = 0;
          if ((local_11c != 0.0) && (local_118 != 0.0)) {
            iVar7 = 1;
          }
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = iVar7;
        goto joined_r0x08084b76;
      case 0xc:
        if (unaff_EBP == 1) {
          iVar7 = 0;
          if ((unaff_EDI.i != 0) || (fVar8.i != 0)) {
            iVar7 = 1;
          }
        }
        else {
          iVar7 = 0;
          if ((local_11c != 0.0) || (local_118 != 0.0)) {
            iVar7 = 1;
          }
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = iVar7;
        goto joined_r0x08084b76;
      case 0xd:
        if (unaff_EBP == 1) {
          uVar10 = (uint)(fVar8.i == 0);
        }
        else {
          uVar10 = (uint)(local_118 == 0.0);
        }
        goto joined_r0x08084b1a;
      case 0xe:
        if (unaff_EBP == 1) {
          uVar10 = 0;
          if (((unaff_EDI.i != 0) || (fVar8.i != 0)) && ((fVar8.i == 0 || (unaff_EDI.i == 0)))) {
            uVar10 = 1;
          }
        }
        else {
          uVar10 = 0;
          if (local_11c == 0.0) {
            if (local_118 != 0.0) {
              if (local_11c != 0.0) goto LAB_08084a22;
              goto LAB_08084a33;
            }
          }
          else {
LAB_08084a22:
            if (local_118 == 0.0) {
LAB_08084a33:
              uVar10 = 1;
            }
          }
        }
joined_r0x08084b1a:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = uVar10;
joined_r0x08084b76:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        goto LAB_08084c4d;
      case 0xf:
        if (unaff_EBP == 1) {
          if (-1 < ((int)fVar8.i)) {
            uVar10 = ipow(((int)unaff_EDI.i),((int)fVar8.i));
            goto LAB_08084bf6;
          }
          local_11c = (float)((int)unaff_EDI.i);
          local_118 = (float)((int)fVar8.i);
        }
        dVar12 = pow((double)local_11c,(double)local_118);
        fVar8.f = (float)dVar12;
        iVar7 = isnan((double)fVar8.f);
        local_120 = fVar8.f;
        if (iVar7 != 0) goto LAB_08084ff7;
        goto LAB_08084c76;
      case 0x10:
        uVar10 = ((uint)fVar8.i) & ((uint)unaff_EDI.i);
        goto LAB_08084bf6;
      case 0x11:
        uVar10 = ((uint)fVar8.i) | ((uint)unaff_EDI.i);
LAB_08084bf6:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = uVar10;
        goto joined_r0x08084c2c;
      case 0x12:
        uVar10 = ((uint)fVar8.i) ^ ((uint)unaff_EDI.i);
        goto LAB_08084bab;
      case 0x13:
        if (unaff_EBP == 1) {
          uVar10 = -((int)fVar8.i);
          goto LAB_08084bf6;
        }
        fVar8.f = -local_118;
LAB_08084c76:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = ((int)fVar8.i);
joined_r0x08084498:
        if (0x7e < (int)piVar9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 1;
        break;
      case 0x14:
        if (unaff_EBP == 1) {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)fVar8.i);
        }
        else {
          fVar8.i = ((int)GHIDRA_FIST32(local_118));
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",local_144);
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)fVar8.i);
          Warn((int)param_1,(int)&DAT_082777c0);
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 0;
        if (unaff_EBP == 2) {
          unaff_EDI.i = ((int)GHIDRA_FIST32(local_11c));
        }
        if (((uint)unaff_EDI.i) < 0x3d) {
          param_1[((int)unaff_EDI.i) + 0x390] = ((int)fVar8.i);
        }
        else {
LAB_080847dc:
          Warn((int)param_1,(int)&DAT_08277800);
        }
        break;
      case 0x15:
        if (unaff_EBP == 1) {
          local_118 = (float)((int)fVar8.i);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = GHIDRA_F2I(int, local_118);
        }
        else {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.");
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          MyStack[(int)MyStackIdx] = ((int)fVar8.i);
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 1;
        if (unaff_EBP == 2) {
          unaff_EDI.i = ((int)GHIDRA_FIST32(local_11c));
        }
        if (0x28 < ((uint)unaff_EDI.i)) goto LAB_080847dc;
        param_1[((int)unaff_EDI.i) + 0x3cc] = GHIDRA_F2I(int, local_118);
        break;
      case 0x16:
        uVar10 = ((uint)fVar8.i) ^ 0xffffffff;
LAB_08084bab:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = uVar10;
joined_r0x08084c2c:
        if (0x7e < (int)piVar9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
LAB_08084c4d:
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 0;
        break;
      case 0x17:
        if (unaff_EBP == 1) {
          uVar10 = ((int)unaff_EDI.i) + ((int)fVar8.i);
          goto LAB_0808488f;
        }
        local_140 = local_118 + local_11c;
        bVar6 = (int)MyStackIdx + -0x7e < 0;
LAB_08084465:
        if (MyStackIdx != (int *)0x7e && SBORROW4((int)MyStackIdx,0x7e) == bVar6) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = GHIDRA_F2I(int, local_140);
        goto joined_r0x08084498;
      case 0x18:
        if (unaff_EBP != 1) {
          local_140 = local_11c - local_118;
LAB_08084452:
          bVar6 = (int)MyStackIdx + -0x7e < 0;
          goto LAB_08084465;
        }
        uVar10 = ((int)unaff_EDI.i) - ((int)fVar8.i);
        goto LAB_0808488f;
      case 0x19:
        if (unaff_EBP != 1) {
          local_140 = local_118 * local_11c;
          bVar6 = (int)MyStackIdx + -0x7e < 0;
          goto LAB_08084465;
        }
        uVar10 = ((int)fVar8.i) * ((int)unaff_EDI.i);
LAB_0808488f:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = uVar10;
        goto joined_r0x08084c2c;
      case 0x1a:
        if (unaff_EBP == 1) {
          if (fVar8.i != 0) {
            uVar10 = ((int)unaff_EDI.i) / ((int)fVar8.i);
            goto LAB_0808488f;
          }
        }
        else if (local_118 != 0.0) {
          local_140 = local_11c / local_118;
          goto LAB_08084452;
        }
        goto LAB_08085004;
      case 0x1b:
        if (fVar8.i != 0) {
          uVar10 = ((int)unaff_EDI.i) % ((int)fVar8.i);
          goto LAB_08084bf6;
        }
LAB_08085004:
        switch(*(undefined4 *)(local_144 + local_114 * 4)) {
        case 7:
        case 8:
        case 9:
        case 10:
          local_114 = local_114 + 1;
        default:
          goto switchD_08085017_caseD_b;
        case 0xf:
          pcVar13 = "Invalid exponentiation";
          break;
        case 0x14:
        case 0x15:
          pcVar13 = "Short-circuited var assign ignored";
          break;
        case 0x1a:
          pcVar13 = "Divison by zero";
          break;
        case 0x1b:
          pcVar13 = "Modulus by zero";
        }
        Warn((int)param_1,(int)pcVar13);
switchD_08085017_caseD_b:
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        piVar9 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar9;
        MyStack[(int)piVar9] = 0;
        if (0x7e < (int)piVar9) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.");
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        MyStack[(int)MyStackIdx] = 4;
      }
switchD_0808437f_default:
      local_114 = local_114 + 1;
      if (param_2[2] <= local_114) break;
      iVar7 = param_2[1];
    } while( true );
  }
  piVar9 = MyStackIdx;
  if ((int)MyStackIdx - (int)piVar2 == 2) {
    if (-1 < (int)MyStackIdx) {
      unaff_EBP = MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if (unaff_EBP == 0) {
      bVar6 = false;
      if (-1 < (int)MyStackIdx) {
        *param_3 = MyStack[(int)MyStackIdx];
        bVar6 = true;
        MyStackIdx = (int *)((int)MyStackIdx + -1);
      }
    }
    else {
      if (unaff_EBP == 1) {
        piVar9 = MyStackIdx;
        if (-1 < (int)MyStackIdx) {
          piVar2 = MyStack + (int)MyStackIdx;
          MyStackIdx = (int *)((int)MyStackIdx + -1);
          *param_4 = *piVar2;
          return 2;
        }
        goto LAB_080851e2;
      }
      if (unaff_EBP != 4) {
        return 0;
      }
      bVar6 = false;
      if (-1 < (int)MyStackIdx) {
        bVar6 = true;
        *param_3 = MyStack[(int)MyStackIdx];
        MyStackIdx = (int *)((int)MyStackIdx + -1);
      }
    }
    piVar9 = MyStackIdx;
    if (bVar6) {
      return 1;
    }
  }
LAB_080851e2:
  MyStackIdx = piVar9;
  sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
          g[0x7304],param_1 + 8,param_1[1],param_1[0x2fd],unaff_EDI.i,unaff_EDI.i);
  ErrorExit();
  return 0;
}

