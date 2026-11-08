/*
 * anim-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08048200-0x0804a928, 62 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* AnimRCReadFile @ 0x08048200, 133 bytes */
int * AnimRCReadFile(char *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  
  puVar1 = TPReadFile(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,param_1);
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = AnimRCReadFileTP((int)puVar1);
    if (piVar2 == (int *)0x0) {
      strcat((char *)ErrorMessage,"\nAnim error reading ");
      strcat((char *)ErrorMessage,param_1);
    }
    TPFree(puVar1);
  }
  return piVar2;
}

/* AnimRCReadFileTP @ 0x08048290, 1428 bytes
 * FIXUP: 3 data addresses written as literals replaced by data-image references
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 15 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
int * AnimRCReadFileTP(int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  undefined3 extraout_var;
  int iVar8;
  char cVar9;
  int *piVar10;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_7c (*(void **)(ghidra_frame + 0x4))
#define local_78 (*(void **)(ghidra_frame + 0x8))
#define local_74 (*(int *)(ghidra_frame + 0xc))
#define local_6c (*(int *)(ghidra_frame + 0x14))
#define local_68 (*(int *)(ghidra_frame + 0x18))
#define local_54 (*(uint *)(ghidra_frame + 0x2c))
#define local_4c (*(undefined4 *)(ghidra_frame + 0x34))
#define local_48 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_44 (*(void **)(ghidra_frame + 0x3c))
#define local_40 (*(void **)(ghidra_frame + 0x40))
#define local_3c (*(undefined4 **)(ghidra_frame + 0x44))
#define local_38 (*(size_t *)(ghidra_frame + 0x48))
#define local_34 (*(int *)(ghidra_frame + 0x4c))
#define local_30 (*(int *)(ghidra_frame + 0x50))
#define local_2c (*(int *)(ghidra_frame + 0x54))
  
  piVar2 = (int *)ecalloc(1,8);
  if (piVar2 != (int *)0x0) {
    iVar3 = TPGroupMatchCount(param_1,"begin action ");
    piVar2[1] = iVar3;
    if (iVar3 < 1) {
      sprintf((char *)ErrorMessage,"Need at least one action");
    }
    else {
      puVar4 = ArrayNew(piVar2[1],0x14,0);
      *piVar2 = (int)puVar4;
      if (puVar4 == (undefined4 *)0x0) {
        sprintf((char *)ErrorMessage,"Out of memory.",piVar2,piVar2);
      }
      else {
        iVar3 = TPGroupScanFirst(param_1);
        local_74 = 0;
        while( true ) {
          if (piVar2[1] <= local_74) {
            return piVar2;
          }
          local_3c = (undefined4 *)0x0;
          local_38 = 0;
          local_34 = 0;
          local_30 = 0;
          local_2c = 0;
          while (iVar5 = strimatch((char *)(iVar3 + 1),"begin action "), iVar5 == 0) {
            iVar3 = TPGroupScanNext(param_1);
          }
          uVar6 = __strtol_internal((byte *)(iVar3 + 0xe),(undefined4 *)0x0,10,0);
          local_30 = 0;
          local_2c = 0;
          local_38 = 0;
          pcVar7 = (char *)TPAccessFirstLine(param_1);
          while (pcVar7 != (char *)0x0) {
            cVar9 = *pcVar7;
            if (((byte)(cVar9 - 0x30U) < 10) || (cVar9 == '-')) {
              local_38 = local_38 + 1;
              cVar9 = *pcVar7;
            }
            if (((cVar9 == 'L') || (cVar9 == 'l')) && ((byte)(pcVar7[1] - 0x30U) < 10)) {
              local_38 = local_38 + 1;
            }
            pcVar7 = (char *)TPAccessNextLine(param_1);
          }
          TPAccessReset(param_1);
          local_3c = ArrayNew(local_38,0x30,0);
          if (local_3c == (undefined4 *)0x0) break;
          local_34 = 0;
          local_78 = (void *)0x0;
          local_7c = (void *)0x0;
          if (0 < (int)local_38) {
            iVar5 = 0;
            do {
              bVar1 = false;
              piVar10 = &local_6c;
              for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
                *piVar10 = 0;
                piVar10 = piVar10 + 1;
              }
              local_4c = 0x100;
              local_48 = 0;
              do {
                pcVar7 = (char *)TPAccessNextLine(param_1);
                if (pcVar7 == (char *)0x0) {
                  sprintf((char *)ErrorMessage,"Error reading line in %s elem %i",iVar3,iVar5 + 1);
                  goto LAB_08048408;
                }
                iVar8 = strimatchlen((int)pcVar7,(int)&DAT_08276a34,9);
                if (iVar8 != 0) {
                  bVar1 = true;
                }
                iVar8 = strimatchlen((int)pcVar7,(int)&DAT_08276a3e,5);
                if (iVar8 != 0) {
                  local_44 = ClsnParseLine((int)pcVar7,param_1);
                  if (local_44 == (void *)0x0) {
                    sprintf((char *)ErrorMessage,"Error in clsn1 in %s elem %i",iVar3,iVar5);
                    goto LAB_08048408;
                  }
                  if ((pcVar7[5] == 'd') || (pcVar7[5] == 'D')) {
                    local_54 = local_54 | 4;
                    local_78 = local_44;
                  }
                }
                iVar8 = strimatchlen((int)pcVar7,(int)&DAT_08276a61,5);
                if (iVar8 != 0) {
                  local_40 = ClsnParseLine((int)pcVar7,param_1);
                  if (local_40 == (void *)0x0) {
                    sprintf((char *)ErrorMessage,"Error in clsn2 in %s elem %i",iVar3,iVar5);
                    goto LAB_08048408;
                  }
                  if ((pcVar7[5] == 'd') || (pcVar7[5] == 'D')) {
                    local_54 = local_54 | 8;
                    local_7c = local_40;
                  }
                }
                cVar9 = *pcVar7;
              } while ((((cVar9 != 'L') && (cVar9 != 'l')) || (9 < (byte)(pcVar7[1] - 0x30U))) &&
                      ((9 < (byte)(cVar9 - 0x30U) && (cVar9 != '-'))));
              if ((local_78 != (void *)0x0) &&
                 ((local_44 == (void *)0x0 &&
                  (local_44 = (void *)ClsnArrayInstance((int)local_78), local_44 == (void *)0x0))))
              {
                sprintf((char *)ErrorMessage,"Internal lib error in %s elem %i",iVar3,iVar5);
                goto LAB_08048408;
              }
              if (((local_7c != (void *)0x0) && (local_40 == (void *)0x0)) &&
                 (local_40 = (void *)ClsnArrayInstance((int)local_7c), local_40 == (void *)0x0)) {
                sprintf((char *)ErrorMessage,"Internal lib error in %s elem %i",iVar3,iVar5);
                goto LAB_08048408;
              }
              if (iVar5 == 0) {
                local_6c = 0;
              }
              else {
                piVar10 = (int *)((iVar5 + -1) * local_3c[1] + local_3c[5]);
                local_6c = piVar10[1] + *piVar10;
              }
              if (bVar1) {
                local_30 = local_6c;
                local_2c = iVar5;
              }
              iVar8 = 0;
              cVar9 = *pcVar7;
              while ((9 < (byte)(cVar9 - 0x30U) && (cVar9 != '-'))) {
                if (cVar9 == '\0') {
                  sprintf((char *)ErrorMessage,"Syntax error in %s elem %i",iVar3,iVar5 + 1);
                  goto LAB_08048408;
                }
                iVar8 = iVar8 + 1;
                cVar9 = pcVar7[iVar8];
              }
              bVar1 = AnimElemParseLine(pcVar7 + iVar8,(int)&local_6c,iVar3,iVar5);
              if (GHIDRA_ZEXT8(bVar1) == 0) goto LAB_08048408;
              if (local_68 == -1) {
                local_34 = local_68;
              }
              else {
                local_34 = local_34 + local_68;
              }
              iVar8 = iVar5 + 1;
              ArrayAdd((int)local_3c,&local_6c,0,iVar5);
              iVar5 = iVar8;
            } while (iVar8 < (int)local_38);
          }
          if (local_2c == -1) {
            local_2c = 0;
          }
          ArrayAdd(*piVar2,&local_3c,0,uVar6);
          iVar3 = TPGroupScanNext(param_1);
          local_74 = local_74 + 1;
        }
        sprintf((char *)ErrorMessage,"Out of memory.",0,0);
      }
    }
LAB_08048408:
    AnimRCFree(piVar2);
  }
  return (int *)0x0;
}
#undef local_7c
#undef local_78
#undef local_74
#undef local_6c
#undef local_68
#undef local_54
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c

/* AnimElemParseLine @ 0x08048830, 383 bytes
 * FIXUP: 1 call results that the caller reads as extraout_EAX assigned explicitly */
bool AnimElemParseLine(char *param_1,int param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined4 extraout_EAX;
  int iVar4;
  int local_14;
  
  iVar4 = 0;
  local_14 = 0;
  if (*param_1 != '\0') {
    while( true ) {
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[iVar4] * 2);
      while ((bVar1 & 0x20) != 0) {
        iVar4 = iVar4 + 1;
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[iVar4] * 2);
      }
      cVar2 = param_1[iVar4];
      if (cVar2 == '\0') break;
      switch(local_14) {
      case 0:
        uVar3 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 8) = uVar3;
        break;
      case 1:
        uVar3 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 0xc) = uVar3;
        break;
      case 2:
        uVar3 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 0x10) = uVar3;
        break;
      case 3:
        uVar3 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 0x14) = uVar3;
        break;
      case 4:
        uVar3 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 4) = uVar3;
        break;
      case 5:
        uVar3 = AnimElemProcessFlipFlags(param_1 + iVar4);
        *(uint *)(param_2 + 0x18) = *(uint *)(param_2 + 0x18) | uVar3;
        break;
      case 6:
        extraout_EAX = AnimElemProcessDrawFlags(param_1 + iVar4,(uint *)(param_2 + 0x20),(uint *)(param_2 + 0x24));
        *(undefined4 *)(param_2 + 0x1c) = extraout_EAX;
        break;
      default:
        goto switchD_08048889_default;
      }
      cVar2 = param_1[iVar4];
switchD_08048889_default:
      local_14 = local_14 + 1;
      while ((cVar2 != ',' && (cVar2 != '\0'))) {
        iVar4 = iVar4 + 1;
        cVar2 = param_1[iVar4];
      }
      if ((cVar2 == '\0') || (iVar4 = iVar4 + 1, param_1[iVar4] == '\0')) break;
    }
  }
  if (4 >= local_14) {
    sprintf((char *)ErrorMessage,"Too few arguments on element %i of %s:\n%s (%i)",param_4 + 1,
            param_3,param_1,local_14,iVar4,iVar4);
  }
  return 4 < local_14;
}

/* AnimElemProcessFlipFlags @ 0x080489b0, 76 bytes */
uint AnimElemProcessFlipFlags(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = 0;
  iVar4 = 0;
  cVar1 = *param_1;
  while ((cVar1 != '\0' && (cVar1 != ','))) {
    iVar2 = *(int *)(__ctype_tolower + param_1[iVar4] * 4);
    if (iVar2 == 0x68) {
      uVar3 = uVar3 | 1;
    }
    else if (iVar2 == 0x76) {
      uVar3 = uVar3 | 2;
    }
    iVar4 = iVar4 + 1;
    cVar1 = param_1[iVar4];
  }
  return uVar3;
}

/* AnimElemProcessDrawFlags @ 0x08048a00, 309 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: Ghidra output of 0x08048a00-0x08048b35 with the return values
 * restored. Reason: Ghidra merged three return paths with a stack temporary
 * and printed "return in_stack_ffffffec"; the subtractive-transparency flag
 * "S" was therefore lost and no sprite was drawn with subtraction (found by
 * the call-count comparison: W_PutSpriteTransSub* 50 calls vs 0).
 * VERIFIED return values: empty string and no 'a'/'s' found -> 0
 * (0x08048b2b xor %eax,%eax); 's' -> 2 (0x08048b16 mov $0x2,%eax);
 * "a1" -> 3; "a" not followed by 's' -> 1; "as<n>d<m>" -> 3 (0x8(%esp)).
 * Draw flags: 1 = add, 2 = subtract, 3 = add with source/destination alpha
 * (param_2 = source, param_3 = destination, 0..256). */
undefined4 AnimElemProcessDrawFlags(char *param_1,uint *param_2,uint *param_3)
{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar4 = 0;
  if (*param_1 == '\0') {
    return 0;
  }
  while (iVar5 = *(int *)(__ctype_tolower + param_1[iVar4] * 4), iVar5 != 0x61) {
    if (iVar5 == 0x73) {
      return 2;
    }
    iVar4 = iVar4 + 1;
    if (param_1[iVar4] == '\0') {
      return 0;
    }
  }
  if (param_1[iVar4 + 1] == '1') {
    *param_2 = 0x100;
    *param_3 = 0x80;
    return 3;
  }
  if (*(int *)(__ctype_tolower + param_1[iVar4 + 1] * 4) != 0x73) {
    return 1;
  }
  iVar4 = iVar4 + 2;
  iVar5 = (int)param_1[iVar4];
  iVar3 = __ctype_tolower;
  if ((*(byte *)(__ctype_b + 1 + iVar5 * 2) & 8) != 0) {
    uVar2 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
    iVar3 = __ctype_tolower;
    *param_2 = uVar2;
    iVar5 = (int)param_1[iVar4];
  }
  if (param_1[iVar4] != '\0') {
    bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    while ((bVar1 & 8) != 0) {
      iVar4 = iVar4 + 1;
      if (param_1[iVar4] == '\0') {
        iVar5 = 0;
        break;
      }
      iVar5 = (int)param_1[iVar4];
      bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    }
  }
  if ((*(int *)(iVar3 + iVar5 * 4) == 100) &&
     ((*(byte *)(__ctype_b + 1 + param_1[iVar4 + 1] * 2) & 8) != 0)) {
    uVar2 = __strtol_internal((byte *)(param_1 + iVar4 + 1),(undefined4 *)0x0,10,0);
    *param_3 = uVar2;
  }
  return 3;
}

/* AnimRCFree @ 0x08048b40, 168 bytes */
undefined4 AnimRCFree(int *param_1)

{
  void *pvVar1;
  undefined4 in_EAX;
  int iVar2;
  undefined4 extraout_EAX;
  int iVar3;
  int iVar4;
  
  if (param_1 == (int *)0x0) {
    return in_EAX;
  }
  iVar2 = *param_1;
  if (iVar2 != 0) {
    iVar4 = 0;
    iVar3 = param_1[1];
    if (0 < iVar3) {
      while( true ) {
        pvVar1 = *(void **)(iVar4 * *(int *)(iVar2 + 4) + *(int *)(iVar2 + 0x14));
        if (pvVar1 != (void *)0x0) {
          iVar2 = ArrayScanFirst((int)pvVar1);
          while (iVar2 != 0) {
            ClsnArrayFree(*(void **)(iVar2 + 0x28));
            ClsnArrayFree(*(void **)(iVar2 + 0x2c));
            iVar2 = ArrayScanNext((int)pvVar1);
          }
          ArrayFree(pvVar1);
          iVar3 = param_1[1];
        }
        iVar4 = iVar4 + 1;
        if (iVar3 <= iVar4) break;
        iVar2 = *param_1;
      }
    }
    ArrayFree((void *)*param_1);
  }
  free(param_1);
  return extraout_EAX;
}

/* AnimNew @ 0x08048bf0, 72 bytes */
undefined4 * AnimNew(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)ecalloc(1,0x38);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = param_1;
    puVar1[1] = param_2;
    puVar1[8] = 0xffffffff;
    puVar1[9] = 0x100;
    puVar1[10] = 0x100;
  }
  return puVar1;
}

/* AnimSet @ 0x08048c40, 36 bytes */
void AnimSet(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = param_2;
  param_1[1] = param_3;
  return;
}

/* AnimCopy @ 0x08048c70, 21 bytes */
void AnimCopy(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}

/* AnimFree @ 0x08048c90, 52 bytes */
undefined4 AnimFree(void *param_1)

{
  undefined4 extraout_EAX;
  undefined4 in_ECX;
  
  if (param_1 != (void *)0x0) {
    if (*(int *)((int)param_1 + 8) != 0) {
      SpriteArrayFree(*(int **)((int)param_1 + 4));
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_ECX;
}

/* AnimUpdate @ 0x08048cd0, 156 bytes */
undefined4 AnimUpdate(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = param_1[3] * *(int *)(*(int *)*param_1 + 4) + *(int *)(*(int *)*param_1 + 0x14);
  uVar4 = 0;
  AnimUpdateElemptr(param_1);
  iVar1 = *(int *)(iVar3 + 8);
  if ((iVar1 <= (int)param_1[7]) && (iVar1 != -1)) {
    param_1[7] = *(undefined4 *)(iVar3 + 0xc);
    uVar4 = 1;
    iVar1 = *(int *)(*(int *)*param_1 + 4);
    iVar3 = *(int *)(*(int *)*param_1 + 0x14);
    param_1[5] = 0;
    param_1[4] = *(undefined4 *)(*(int *)(iVar1 * param_1[3] + iVar3) + 0x14);
    AnimUpdateElemptr(param_1);
  }
  uVar2 = SpriteArrayGetNum((int *)param_1[1],*(int *)(param_1[4] + 8),*(int *)(param_1[4] + 0xc));
  param_1[0xb] = uVar2;
  param_1[6] = param_1[6] + 1;
  param_1[7] = param_1[7] + 1;
  return uVar4;
}

/* AnimUpdateElemptr @ 0x08048d70, 88 bytes */
int AnimUpdateElemptr(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar2 = param_1[5];
  iVar1 = *(int *)(*(int *)*param_1 + 0x14);
  piVar4 = (int *)(param_1[3] * *(int *)(*(int *)*param_1 + 4) + iVar1);
  if (iVar2 < piVar4[1]) {
    piVar3 = (int *)(iVar2 * *(int *)(*piVar4 + 4) + *(int *)(*piVar4 + 0x14));
    iVar1 = param_1[7];
    if (*piVar3 <= iVar1) {
      param_1[4] = piVar3;
      while (iVar2 = iVar2 + 1, iVar2 < piVar4[1]) {
        piVar3 = (int *)(iVar2 * *(int *)(*piVar4 + 4) + *(int *)(*piVar4 + 0x14));
        iVar1 = param_1[7];
        if (iVar1 < *piVar3) {
          return iVar1;
        }
        param_1[4] = piVar3;
        param_1[5] = iVar2;
      }
    }
  }
  return iVar1;
}

/* AnimResetAction @ 0x08048dd0, 62 bytes */
void AnimResetAction(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1[3];
  if (((int *)*param_1)[1] < iVar3) {
    param_1[3] = 0;
    iVar3 = 0;
  }
  iVar1 = *(int *)*param_1;
  iVar2 = *(int *)(iVar1 + 4);
  iVar1 = *(int *)(iVar1 + 0x14);
  param_1[6] = 0;
  iVar3 = *(int *)(iVar3 * iVar2 + iVar1);
  param_1[7] = 0;
  param_1[4] = *(int *)(iVar3 + 0x14);
  param_1[5] = 0;
  return;
}

/* AnimChangeAction @ 0x08048e10, 29 bytes */
undefined4 AnimChangeAction(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = AnimChangeActionTime(param_1,param_2,param_3,0);
  return uVar1;
}

/* AnimChangeActionTime @ 0x08048e30, 141 bytes */
undefined4 AnimChangeActionTime(int *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (((int *)*param_1)[1] < param_1[3]) {
    iVar3 = *(int *)*param_1;
    param_1[3] = 0;
    piVar1 = *(int **)(iVar3 + 0x14);
    param_1[5] = 0;
    param_1[4] = *(int *)(*piVar1 + 0x14);
  }
  iVar3 = AnimGrpNoToIdx(param_1,param_2,param_3);
  if (iVar3 == -1) {
    uVar4 = 0;
  }
  else {
    if (param_1[3] != iVar3) {
      param_1[3] = iVar3;
      if (param_4 != -1) {
        param_1[6] = param_4;
        param_1[7] = param_4;
      }
      iVar3 = *(int *)(*(int *)*param_1 + 4);
      iVar2 = *(int *)(*(int *)*param_1 + 0x14);
      param_1[5] = 0;
      param_1[4] = *(int *)(*(int *)(iVar3 * param_1[3] + iVar2) + 0x14);
    }
    uVar4 = 1;
  }
  return uVar4;
}

/* AnimChangeActionElem @ 0x08048ec0, 157 bytes */
undefined4 AnimChangeActionElem(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = AnimChangeAction(param_1,param_2,param_3);
  if (iVar1 != 0) {
    AnimResetAction(param_1);
    if ((-1 < param_4) &&
       (param_4 < *(int *)(*(int *)(*(int *)*param_1 + 4) * param_1[3] +
                           *(int *)(*(int *)*param_1 + 0x14) + 4))) {
      if (param_4 == 0) {
        return 1;
      }
      AnimUpdateElemptr(param_1);
      iVar1 = param_1[5];
      while( true ) {
        if (iVar1 == param_4) {
          param_1[6] = param_1[6] + -1;
          param_1[7] = param_1[7] + -1;
          return 1;
        }
        iVar1 = AnimUpdate(param_1);
        if (iVar1 != 0) break;
        iVar1 = param_1[5];
      }
    }
  }
  return 0;
}

/* AnimDraw @ 0x08048f60, 29 bytes */
void AnimDraw(undefined4 *param_1,int param_2,int param_3)

{
  AnimDrawFlip(param_1,param_2,param_3,0);
  return;
}

/* AnimDrawFlip @ 0x08048f80, 601 bytes
 * FIXUP: frame emulation: 16 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
void AnimDrawFlip(undefined4 *param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_78 (*(int *)(ghidra_frame + 0x8))
#define local_74 (*(int *)(ghidra_frame + 0xc))
#define local_70 (*(int *)(ghidra_frame + 0x10))
#define local_5c (*(int *)(ghidra_frame + 0x24))
#define local_58 (*(undefined4 *)(ghidra_frame + 0x28))
#define local_54 (*(int *)(ghidra_frame + 0x2c))
#define local_50 (*(undefined4 *)(ghidra_frame + 0x30))
#define local_4c (*(int *)(ghidra_frame + 0x34))
#define local_48 (*(int *)(ghidra_frame + 0x38))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_40 (*(int *)(ghidra_frame + 0x40))
#define local_3c (*(int *)(ghidra_frame + 0x44))
#define local_38 (*(int *)(ghidra_frame + 0x48))
#define local_34 (*(undefined4 *)(ghidra_frame + 0x4c))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x50))
#define local_28 (*(uint *)(ghidra_frame + 0x58))
  
  piVar2 = (int *)(*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14));
  local_74 = 0;
  if (0 < piVar2[1]) {
    iVar3 = param_1[7];
    do {
      piVar8 = (int *)(local_74 * *(int *)(*piVar2 + 4) + *(int *)(*piVar2 + 0x14));
      if ((*piVar8 <= iVar3 + -1) && ((iVar3 + -1 < *piVar8 + piVar8[1] || (piVar8[1] == -1)))) {
        iVar3 = HFlipToSgn(param_4);
        iVar3 = iVar3 * piVar8[4] + param_2;
        iVar4 = VFlipToSgn(param_4);
        iVar4 = iVar4 * piVar8[5] + param_3;
        uVar5 = FlipFlagMix(param_4,piVar8[6] & 3);
        local_70 = param_1[8];
        if (local_70 == -1) {
          local_70 = piVar8[7];
          local_78 = piVar8[8];
          iVar6 = piVar8[9];
        }
        else {
          local_78 = AlphaMixSrc(param_1[9],piVar8[8]);
          iVar6 = AlphaMixDest(param_1[10],piVar8[9]);
        }
        iVar1 = param_1[0xb];
        if (iVar1 == -1) {
          iVar3 = param_1[7];
        }
        else {
          SpriteArrayAccess((int *)param_1[1],iVar1);
          if (param_1[0xc] == 0) {
            AnimDrawSprFlip((int *)param_1[1],iVar1,iVar3,iVar4,uVar5,local_70,local_78,iVar6);
          }
          else {
            piVar9 = &local_5c;
            for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
              *piVar9 = 0;
              piVar9 = piVar9 + 1;
            }
            local_50 = 0;
            local_5c = param_1[0xd];
            local_58 = param_1[1];
            local_30 = 0x3f800000;
            local_34 = 0x3f800000;
            local_40 = local_70;
            local_3c = local_78;
            local_44 = 1;
            local_54 = iVar1;
            local_4c = iVar3;
            local_48 = iVar4;
            local_38 = iVar6;
            local_28 = uVar5;
            PRSprAdd((int *)param_1[0xc],&local_5c);
          }
          iVar3 = param_1[7];
        }
      }
    } while ((*piVar8 <= iVar3 + -1) && (local_74 = local_74 + 1, local_74 < piVar2[1]));
  }
  return;
}
#undef local_78
#undef local_74
#undef local_70
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_28

/* AnimDrawScale @ 0x080491e0, 39 bytes */
void AnimDrawScale(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5)

{
  AnimDrawScaleFlip(param_1,param_2,param_3,param_4,param_5,0);
  return;
}

/* AnimDrawScaleFlip @ 0x08049210, 811 bytes
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 16 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void AnimDrawScaleFlip(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5,
                      uint param_6)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  float10 fVar10;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_78 (*(int *)(ghidra_frame + 0x8))
#define local_74 (*(int *)(ghidra_frame + 0xc))
#define local_70 (*(int *)(ghidra_frame + 0x10))
#define local_5c (*(int *)(ghidra_frame + 0x24))
#define local_58 (*(undefined4 *)(ghidra_frame + 0x28))
#define local_54 (*(int *)(ghidra_frame + 0x2c))
#define local_50 (*(undefined4 *)(ghidra_frame + 0x30))
#define local_4c (*(int *)(ghidra_frame + 0x34))
#define local_48 (*(int *)(ghidra_frame + 0x38))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_40 (*(int *)(ghidra_frame + 0x40))
#define local_3c (*(int *)(ghidra_frame + 0x44))
#define local_38 (*(int *)(ghidra_frame + 0x48))
#define local_34 (*(float *)(ghidra_frame + 0x4c))
#define local_30 (*(float *)(ghidra_frame + 0x50))
#define local_28 (*(uint *)(ghidra_frame + 0x58))
  
  piVar2 = (int *)(*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14));
  if ((param_4 == 1.0) && (param_5 == 1.0)) {
    AnimDrawFlip(param_1,param_2,param_3,param_6);
  }
  else {
    local_70 = 0;
    if (0 < piVar2[1]) {
      iVar3 = param_1[7];
      do {
        piVar8 = (int *)(local_70 * *(int *)(*piVar2 + 4) + *(int *)(*piVar2 + 0x14));
        if ((*piVar8 <= iVar3 + -1) && ((iVar3 + -1 < *piVar8 + piVar8[1] || (piVar8[1] == -1)))) {
          iVar3 = HFlipToSgn(param_6);
          iVar3 = roundfloat((float10)iVar3 * (float10)piVar8[4] * param_4);
          iVar4 = VFlipToSgn(param_6);
          iVar4 = roundfloat((float10)iVar4 * (float10)piVar8[5] * param_5);
          uVar5 = FlipFlagMix(param_6,piVar8[6] & 3);
          local_74 = param_1[8];
          if (local_74 == -1) {
            local_74 = piVar8[7];
            local_78 = piVar8[8];
            iVar6 = piVar8[9];
          }
          else {
            local_78 = AlphaMixSrc(param_1[9],piVar8[8]);
            iVar6 = AlphaMixDest(param_1[10],piVar8[9]);
          }
          iVar1 = param_1[0xb];
          if (iVar1 != -1) {
            SpriteArrayAccess((int *)param_1[1],iVar1);
            if (param_1[0xc] != 0) {
              piVar9 = &local_5c;
              for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
                *piVar9 = 0;
                piVar9 = piVar9 + 1;
              }
              local_5c = param_1[0xd];
              local_58 = param_1[1];
              local_40 = local_74;
              local_3c = local_78;
              local_50 = 0;
              local_44 = 2;
              local_34 = param_4;
              local_30 = param_5;
              local_54 = iVar1;
              local_4c = iVar3 + param_2;
              local_48 = iVar4 + param_3;
              local_38 = iVar6;
              local_28 = uVar5;
              PRSprAdd((int *)param_1[0xc],&local_5c);
              iVar3 = param_1[7];
              goto LAB_08049512;
            }
            iVar7 = VFlipToSgn(uVar5);
            fVar10 = (float10)iVar7 * param_5;
            iVar7 = HFlipToSgn(uVar5);
            AnimScaleSpr_S((int *)param_1[1],iVar1,iVar3 + param_2,iVar4 + param_3,
                           (float10)iVar7 * param_4,fVar10,local_74,local_78,iVar6);
          }
          iVar3 = param_1[7];
        }
LAB_08049512: ;
      } while ((*piVar8 <= iVar3 + -1) && (local_70 = local_70 + 1, local_70 < piVar2[1]));
    }
  }
  return;
}
#undef local_78
#undef local_74
#undef local_70
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_28

/* AnimDrawRotateFlip @ 0x08049540, 819 bytes
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 16 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void AnimDrawRotateFlip(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5,
                       float param_6,uint param_7)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_7c (*(int *)(ghidra_frame + 0x4))
#define local_78 (*(int *)(ghidra_frame + 0x8))
#define local_5c (*(int *)(ghidra_frame + 0x24))
#define local_58 (*(undefined4 *)(ghidra_frame + 0x28))
#define local_54 (*(int *)(ghidra_frame + 0x2c))
#define local_50 (*(undefined4 *)(ghidra_frame + 0x30))
#define local_4c (*(int *)(ghidra_frame + 0x34))
#define local_48 (*(int *)(ghidra_frame + 0x38))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_40 (*(undefined4 *)(ghidra_frame + 0x40))
#define local_3c (*(int *)(ghidra_frame + 0x44))
#define local_38 (*(int *)(ghidra_frame + 0x48))
#define local_34 (*(float *)(ghidra_frame + 0x4c))
#define local_30 (*(float *)(ghidra_frame + 0x50))
#define local_2c (*(float *)(ghidra_frame + 0x54))
#define local_28 (*(uint *)(ghidra_frame + 0x58))
  
  piVar1 = (int *)(*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14));
  local_78 = 0;
  if (0 < piVar1[1]) {
    iVar2 = param_1[7];
    do {
      piVar9 = (int *)(local_78 * *(int *)(*piVar1 + 4) + *(int *)(*piVar1 + 0x14));
      if ((*piVar9 <= iVar2 + -1) && ((iVar2 + -1 < *piVar9 + piVar9[1] || (piVar9[1] == -1)))) {
        iVar2 = HFlipToSgn(param_7);
        iVar2 = (int)GHIDRA_FIST32((float10)iVar2 * (float10)piVar9[4] * param_5 + (float)param_2);
        iVar3 = VFlipToSgn(param_7);
        iVar3 = (int)GHIDRA_FIST32((float10)iVar3 * (float10)piVar9[5] * param_6 + (float)param_3);
        uVar4 = FlipFlagMix(param_7,piVar9[6] & 3);
        iVar8 = param_1[8];
        if (iVar8 == -1) {
          local_7c = piVar9[8];
          iVar8 = piVar9[7];
          iVar5 = piVar9[9];
        }
        else {
          local_7c = AlphaMixSrc(param_1[9],piVar9[8]);
          iVar5 = AlphaMixDest(param_1[10],piVar9[9]);
        }
        iVar6 = HFlipToSgn(param_7);
        param_4 = (float10)iVar6 * param_4;
        iVar6 = param_1[0xb];
        if (iVar6 != -1) {
          SpriteArrayAccess((int *)param_1[1],iVar6);
          if (param_1[0xc] != 0) {
            piVar10 = &local_5c;
            for (iVar8 = 0xe; iVar8 != 0; iVar8 = iVar8 + -1) {
              *piVar10 = 0;
              piVar10 = piVar10 + 1;
            }
            local_50 = 0;
            local_5c = param_1[0xd];
            local_34 = param_5;
            local_58 = param_1[1];
            local_44 = 3;
            local_30 = param_6;
            local_40 = param_1[8];
            local_3c = local_7c;
            local_54 = iVar6;
            local_4c = iVar2;
            local_48 = iVar3;
            local_38 = iVar5;
            local_2c = param_4;
            local_28 = uVar4;
            PRSprAdd((int *)param_1[0xc],&local_5c);
            iVar2 = param_1[7];
            goto LAB_0804984a;
          }
          fVar13 = 1.0;
          fVar12 = 1.0;
          iVar7 = VFlipToSgn(uVar4);
          fVar11 = (float10)iVar7 * param_6;
          iVar7 = HFlipToSgn(uVar4);
          AnimRotateSpr((int *)param_1[1],iVar6,iVar2,iVar3,param_4,(float10)iVar7 * param_5,fVar11,
                        fVar12,fVar13,iVar8,local_7c,iVar5);
        }
        iVar2 = param_1[7];
      }
LAB_0804984a: ;
    } while ((*piVar9 <= iVar2 + -1) && (local_78 = local_78 + 1, local_78 < piVar1[1]));
  }
  return;
}
#undef local_7c
#undef local_78
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28

/* AnimCurIDGrp @ 0x08049880, 25 bytes */
void AnimCurIDGrp(undefined4 *param_1)

{
  ArrayIdxToGrp(*(int *)*param_1,param_1[3]);
  return;
}

/* AnimCurIDno @ 0x080498a0, 25 bytes */
undefined4 AnimCurIDno(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = ArrayIdxToItem(*(int *)*param_1,param_1[3]);
  return uVar1;
}

/* AnimCurElemStartTime @ 0x080498c0, 52 bytes */
undefined4 AnimCurElemStartTime(undefined4 *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar2 = (int *)(*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14));
  if (param_2 < piVar2[1]) {
    iVar1 = *piVar2;
    uVar3 = *(undefined4 *)(param_2 * *(int *)(iVar1 + 4) + *(int *)(iVar1 + 0x14));
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

/* AnimElemNo @ 0x08049900, 150 bytes */
int AnimElemNo(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar4 = param_1[7];
  piVar5 = (int *)(param_1[3] * *(int *)(*(int *)*param_1 + 4) + *(int *)(*(int *)*param_1 + 0x14));
  iVar3 = piVar5[2] - piVar5[3];
  iVar2 = iVar4 + param_2;
  if (iVar2 < 0) {
    if (iVar4 < piVar5[2]) {
      return 0xffffffff;
    }
    iVar2 = (iVar3 - param_2) + iVar4;
  }
  if ((piVar5[2] <= iVar2) && (piVar5[2] != -1)) {
    iVar2 = (iVar2 - piVar5[3]) % iVar3 + piVar5[3];
  }
  iVar4 = 0;
  if (0 < piVar5[1]) {
    iVar3 = *piVar5;
    iVar1 = **(int **)(iVar3 + 0x14);
    while ((iVar1 <= iVar2 && (iVar4 = iVar4 + 1, iVar4 < piVar5[1]))) {
      iVar1 = *(int *)(iVar4 * *(int *)(iVar3 + 4) + *(int *)(iVar3 + 0x14));
    }
  }
  return iVar4;
}

/* AnimIdxToIDGrp @ 0x080499a0, 17 bytes */
void AnimIdxToIDGrp(undefined4 *param_1,int param_2)

{
  ArrayIdxToGrp(*(int *)*param_1,param_2);
  return;
}

/* AnimIdxToIDno @ 0x080499c0, 17 bytes */
void AnimIdxToIDno(undefined4 *param_1,int param_2)

{
  ArrayIdxToItem(*(int *)*param_1,param_2);
  return;
}

/* AnimGrpNoToIdx @ 0x080499e0, 17 bytes */
uint AnimGrpNoToIdx(undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = ArrayFind(*(int *)*param_1,param_2,param_3);
  return uVar1;
}

/* AnimGetLooptime @ 0x08049a00, 24 bytes */
undefined4 AnimGetLooptime(undefined4 *param_1)

{
  return *(undefined4 *)
          (*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14) + 8);
}

/* AnimGetLooptimeID @ 0x08049a20, 47 bytes */
undefined4 AnimGetLooptimeID(undefined4 *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  iVar2 = AnimGrpNoToIdx(param_1,param_2,param_3);
  return *(undefined4 *)(iVar2 * *(int *)(*piVar1 + 4) + *(int *)(*piVar1 + 0x14) + 8);
}

/* AnimGetLoopstarttime @ 0x08049a50, 24 bytes */
undefined4 AnimGetLoopstarttime(undefined4 *param_1)

{
  return *(undefined4 *)
          (*(int *)(*(int *)*param_1 + 4) * param_1[3] + *(int *)(*(int *)*param_1 + 0x14) + 0xc);
}

/* AnimGetLoopstarttimeID @ 0x08049a70, 47 bytes */
undefined4 AnimGetLoopstarttimeID(undefined4 *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  iVar2 = AnimGrpNoToIdx(param_1,param_2,param_3);
  return *(undefined4 *)(iVar2 * *(int *)(*piVar1 + 4) + *(int *)(*piVar1 + 0x14) + 0xc);
}

/* AnimGetTime @ 0x08049aa0, 8 bytes */
undefined4 AnimGetTime(int param_1)

{
  return *(undefined4 *)(param_1 + 0x1c);
}

/* AnimGetCorrectedTime @ 0x08049ab0, 44 bytes */
int AnimGetCorrectedTime(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AnimGetLooptime(param_1);
  if ((int)param_1[7] < iVar1) {
    return param_1[7];
  }
  uVar2 = AnimGetLoopstarttime(param_1);
  return uVar2;
}

/* AnimCurSpriteIdx @ 0x08049ae0, 8 bytes */
undefined4 AnimCurSpriteIdx(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}

/* PRSprArrayNew @ 0x08049af0, 122 bytes */
undefined4 * PRSprArrayNew(size_t param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 extraout_EDX;
  
  puVar1 = (undefined4 *)ecalloc(1,8);
  if (puVar1 != (undefined4 *)0x0) {
    puVar2 = ArrayNew(param_1,0x38,0);
    *puVar1 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      sprintf((char *)ErrorMessage,"Out of memory.",extraout_EDX,extraout_EDX);
    }
    else {
      iVar3 = ecalloc(param_1,4);
      puVar1[1] = iVar3;
      if (iVar3 != 0) {
        return puVar1;
      }
    }
    PRSprArrayFree(puVar1);
  }
  return (undefined4 *)0x0;
}

/* PRSprArrayFree @ 0x08049b70, 60 bytes */
undefined4 PRSprArrayFree(undefined4 *param_1)

{
  undefined4 extraout_EAX;
  undefined4 in_EDX;
  
  if (param_1 != (undefined4 *)0x0) {
    ArrayFree((void *)*param_1);
    if ((void *)param_1[1] != (void *)0x0) {
      free((void *)param_1[1]);
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_EDX;
}

/* PRSprArrayClear @ 0x08049bb0, 15 bytes */
void PRSprArrayClear(int *param_1)

{
  ArrayClear(*param_1);
  return;
}

/* PRSprAdd @ 0x08049bc0, 145 bytes */
undefined4 PRSprAdd(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  
  iVar1 = *param_2;
  iVar2 = *param_1;
  iVar3 = param_1[1];
  iVar4 = ArrayAdd(iVar2,param_2,0,iVar1);
  if (iVar4 == -1) {
    uVar5 = 0;
  }
  else {
    iVar6 = *(int *)(iVar2 + 8);
    iVar8 = 0;
    if (0 < iVar6 + -1) {
      do {
        if (iVar1 <= *(int *)(*(int *)(iVar2 + 0x18) + 0xc + *(int *)(iVar3 + iVar8 * 4) * 0x10)) {
          iVar6 = iVar6 + -1;
          if (iVar8 < iVar6) {
            puVar7 = (undefined4 *)(iVar3 + iVar6 * 4);
            do {
              iVar6 = iVar6 + -1;
              *puVar7 = puVar7[-1];
              puVar7 = puVar7 + -1;
            } while (iVar8 < iVar6);
          }
          break;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < iVar6 + -1);
    }
    *(int *)(iVar3 + iVar8 * 4) = iVar4;
    uVar5 = 1;
  }
  return uVar5;
}

/* PRSprDraw @ 0x08049c60, 356 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PRSprDraw(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  int iVar7;
  float10 fVar8;
  
  uVar2 = 0;
  if ((*(int *)(param_1 + 0xc) != 0) && (iVar7 = *(int *)(param_1 + 4), iVar7 != 0)) {
    uVar2 = *(undefined4 *)(iVar7 + 0x14);
    *(int *)(iVar7 + 0x14) = *(int *)(param_1 + 0xc);
  }
  iVar7 = *(int *)(param_1 + 0x18);
  if (iVar7 == 2) {
    if (*(int *)(param_1 + 4) != 0) {
      iVar7 = *(int *)(param_1 + 0x24);
      iVar5 = *(int *)(param_1 + 0x20);
      uVar4 = *(undefined4 *)(param_1 + 0x1c);
      iVar1 = VFlipToSgn(*(uint *)(param_1 + 0x34));
      fVar3 = (float10)iVar1 * *(float *)(param_1 + 0x2c);
      iVar1 = HFlipToSgn(*(uint *)(param_1 + 0x34));
      AnimScaleSpr_S(*(int **)(param_1 + 4),*(int *)(param_1 + 8),*(int *)(param_1 + 0x10),
                     *(int *)(param_1 + 0x14),(float10)iVar1 * *(float *)(param_1 + 0x28),fVar3,uVar4,
                     iVar5,iVar7);
    }
  }
  else if (iVar7 < 3) {
    if ((iVar7 == 1) && (*(int *)(param_1 + 4) != 0)) {
      AnimDrawSprFlip(*(int **)(param_1 + 4),*(int *)(param_1 + 8),*(int *)(param_1 + 0x10),
                      *(int *)(param_1 + 0x14),*(int *)(param_1 + 0x34),
                      *(undefined4 *)(param_1 + 0x1c),*(int *)(param_1 + 0x20),
                      *(int *)(param_1 + 0x24));
    }
  }
  else if ((iVar7 == 3) && (*(int *)(param_1 + 4) != 0)) {
    iVar7 = *(int *)(param_1 + 0x24);
    iVar5 = *(int *)(param_1 + 0x20);
    uVar4 = *(undefined4 *)(param_1 + 0x1c);
    fVar8 = 1.0;
    fVar6 = 1.0;
    iVar1 = VFlipToSgn(*(uint *)(param_1 + 0x34));
    fVar3 = (float10)iVar1 * *(float *)(param_1 + 0x2c);
    iVar1 = HFlipToSgn(*(uint *)(param_1 + 0x34));
    AnimRotateSpr(*(int **)(param_1 + 4),*(int *)(param_1 + 8),*(int *)(param_1 + 0x10),
                  *(int *)(param_1 + 0x14),*(float *)(param_1 + 0x30),
                  (float10)iVar1 * *(float *)(param_1 + 0x28),fVar3,fVar6,fVar8,uVar4,iVar5,iVar7);
  }
  if ((*(int *)(param_1 + 0xc) != 0) && (*(int *)(param_1 + 4) != 0)) {
    *(undefined4 *)(*(int *)(param_1 + 4) + 0x14) = uVar2;
  }
  return;
}

/* PRSprArrayDraw @ 0x08049dd0, 57 bytes */
void PRSprArrayDraw(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = *param_1;
  iVar3 = *(int *)(iVar1 + 8);
  if (0 < iVar3) {
    do {
      iVar2 = *(int *)(iVar1 + 4) * *(int *)(param_1[1] + iVar4 * 4) + *(int *)(iVar1 + 0x14);
      if (iVar2 != 0) {
        PRSprDraw(iVar2);
        iVar3 = *(int *)(iVar1 + 8);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar3);
  }
  return;
}

/* PRSprArrayScale @ 0x08049e10, 212 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int PRSprArrayScale(int *param_1,float param_2)

{
  float10 fVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_14;
  
  iVar2 = *param_1;
  iVar3 = *(int *)(iVar2 + 8);
  local_14 = in_EAX;
  if (0 < iVar3) {
    iVar5 = 0;
    do {
      iVar4 = *(int *)(iVar2 + 0x14) + *(int *)(iVar2 + 4) * *(int *)(param_1[1] + iVar5 * 4);
      if (iVar4 != 0) {
        *(int *)(iVar4 + 0x10) = (int)GHIDRA_FIST32((float10)*(int *)(iVar4 + 0x10) * param_2);
        local_14 = (int)GHIDRA_FIST32((float10)*(int *)(iVar4 + 0x14) * param_2);
        *(int *)(iVar4 + 0x14) = local_14;
        if (*(int *)(iVar4 + 0x18) - 1U < 2) {
          fVar1 = *(float *)(iVar4 + 0x28);
          *(undefined4 *)(iVar4 + 0x18) = 2;
          iVar3 = *(int *)(iVar2 + 8);
        }
        else {
          if (*(int *)(iVar4 + 0x18) != 3) {
            iVar3 = *(int *)(iVar2 + 8);
            goto LAB_08049ed3;
          }
          fVar1 = *(float *)(iVar4 + 0x28);
          iVar3 = *(int *)(iVar2 + 8);
        }
        *(float *)(iVar4 + 0x28) = fVar1 * param_2;
        *(float *)(iVar4 + 0x2c) = *(float *)(iVar4 + 0x2c) * param_2;
      }
LAB_08049ed3:
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar3);
  }
  return local_14;
}

/* AnimPerUpdate @ 0x08049ef0, 33 bytes */
byte AnimPerUpdate(int param_1)

{
  int iVar1;
  
  iVar1 = AnimUpdate((undefined4 *)(param_1 + 0x14));
  return (iVar1 != 0) - 1U & 1;
}

/* AnimPerDraw @ 0x08049f20, 51 bytes */
void AnimPerDraw(int *param_1,int param_2,int param_3)

{
  AnimDrawScaleFlip(param_1 + 5,*param_1 + param_2,param_1[1] + param_3,GHIDRA_I2F(param_1[3]),
                    GHIDRA_I2F(param_1[4]),param_1[2]);
  return;
}

/* AnimPerDrawScale @ 0x08049f60, 146 bytes */
void AnimPerDrawScale(int *param_1,int param_2,int param_3,float param_4)

{
  AnimDrawScaleFlip(param_1 + 5,(int)GHIDRA_FIST32((float)(*param_1 + param_2) * param_4),
                    (int)GHIDRA_FIST32((float)(param_3 + param_1[1]) * param_4),GHIDRA_I2F(param_1[3]) * param_4,
                    GHIDRA_I2F(param_1[4]) * param_4,param_1[2]);
  return;
}

/* AnimPerArrayNew @ 0x0804a000, 78 bytes */
undefined4 * AnimPerArrayNew(size_t param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)ecalloc(1,4);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar2 = ArrayNew(param_1,0x4c,0);
    *puVar1 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      AnimPerArrayFree(puVar1);
      puVar1 = (undefined4 *)0x0;
    }
  }
  return puVar1;
}

/* AnimPerArrayFree @ 0x0804a050, 39 bytes */
void AnimPerArrayFree(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    ArrayFree((void *)*param_1);
    free(param_1);
    return;
  }
  return;
}

/* AnimPerArrayAdd @ 0x0804a080, 197 bytes
 * FIXUP: frame emulation: 9 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation) */
uint AnimPerArrayAdd(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                    undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
  int iVar1;
  uint uVar2;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_6c (*(undefined4 *)(ghidra_frame + 0x4))
#define local_68 (*(undefined4 *)(ghidra_frame + 0x8))
#define local_64 (*(undefined4 *)(ghidra_frame + 0xc))
#define local_60 (*(undefined4 *)(ghidra_frame + 0x10))
#define local_5c (*(undefined4 *)(ghidra_frame + 0x14))
#define local_58 (*(int (*)[8])(ghidra_frame + 0x18))
#define local_38 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_34 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x40))
  
  local_6c = param_6;
  local_68 = param_7;
  local_64 = param_8;
  local_5c = 0x3f800000;
  local_60 = 0x3f800000;
  AnimSet(local_58,param_2,param_3);
  local_38 = param_9;
  local_30 = 0x100;
  local_34 = 0x100;
  iVar1 = AnimChangeAction(local_58,param_4,param_5);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    AnimResetAction(local_58);
    uVar2 = ArrayAdd(*param_1,&local_6c,1,0);
    uVar2 = (uVar2 != 0xffffffff) - 1 | uVar2;
  }
  return uVar2;
}
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_38
#undef local_34
#undef local_30

/* AnimPerArraySetNo @ 0x0804a150, 25 bytes */
void AnimPerArraySetNo(int *param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(*(int *)(*param_1 + 0x18) + 8 + param_2 * 0x10) = param_3;
  return;
}

/* AnimPerArrayDelete @ 0x0804a170, 15 bytes */
void AnimPerArrayDelete(int *param_1,int param_2)

{
  ArrayDelete(*param_1,param_2);
  return;
}

/* AnimPerArrayClear @ 0x0804a180, 15 bytes */
void AnimPerArrayClear(int *param_1)

{
  ArrayClear(*param_1);
  return;
}

/* AnimPerArrayUpdate @ 0x0804a190, 70 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 AnimPerArrayUpdate(int *param_1)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined4 uStack_c;
  
  iVar1 = *param_1;
  iVar3 = ArrayScanFirst(iVar1);
  while (iVar3 != 0) {
    bVar2 = AnimPerUpdate(iVar3);
    if (GHIDRA_ZEXT8(bVar2) == 0) {
      AnimPerArrayDelete(param_1,*(int *)(iVar1 + 0x1c));
    }
    iVar3 = ArrayScanNext(iVar1);
  }
  return uStack_c;
}

/* AnimPerArrayUpdateGrp @ 0x0804a1e0, 108 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void AnimPerArrayUpdateGrp(int *param_1,uint param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  undefined3 extraout_var;
  
  iVar1 = *param_1;
  iVar3 = ArrayScanFirst(iVar1);
  while (iVar3 != 0) {
    uVar4 = ArrayIdxToGrp(iVar1,*(int *)(iVar1 + 0x1c));
    if ((param_2 & uVar4) != 0) {
      bVar2 = AnimPerUpdate(iVar3);
      if (GHIDRA_ZEXT8(bVar2) == 0) {
        AnimPerArrayDelete(param_1,*(int *)(iVar1 + 0x1c));
      }
    }
    iVar3 = ArrayScanNext(iVar1);
  }
  return;
}

/* AnimPerArrayDraw @ 0x0804a250, 60 bytes */
void AnimPerArrayDraw(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  piVar2 = (int *)ArrayScanFirst(iVar1);
  while (piVar2 != (int *)0x0) {
    AnimPerDraw(piVar2,param_2,param_3);
    piVar2 = (int *)ArrayScanNext(iVar1);
  }
  return;
}

/* AnimPerArrayDrawGrp @ 0x0804a290, 91 bytes */
void AnimPerArrayDrawGrp(int *param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  piVar2 = (int *)ArrayScanFirst(iVar1);
  while (piVar2 != (int *)0x0) {
    uVar3 = ArrayIdxToGrp(iVar1,*(int *)(iVar1 + 0x1c));
    if ((param_2 & uVar3) != 0) {
      AnimPerDraw(piVar2,param_3,param_4);
    }
    piVar2 = (int *)ArrayScanNext(iVar1);
  }
  return;
}

/* AnimPerArrayDrawScaleGrp @ 0x0804a2f0, 95 bytes */
void AnimPerArrayDrawScaleGrp(int *param_1,uint param_2,int param_3,int param_4,float param_5)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  piVar2 = (int *)ArrayScanFirst(iVar1);
  while (piVar2 != (int *)0x0) {
    uVar3 = ArrayIdxToGrp(iVar1,*(int *)(iVar1 + 0x1c));
    if ((param_2 & uVar3) != 0) {
      AnimPerDrawScale(piVar2,param_3,param_4,param_5);
    }
    piVar2 = (int *)ArrayScanNext(iVar1);
  }
  return;
}

/* FlipFlagMix @ 0x0804a350, 11 bytes */
uint FlipFlagMix(uint param_1,uint param_2)

{
  return param_2 ^ param_1;
}

/* AnimDrawSprFlip @ 0x0804a360, 744 bytes */
void AnimDrawSprFlip(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6
                    ,int param_7,int param_8)

{
  if (param_5 == 1) {
    switch(param_6) {
    case 1:
      W_PutSpriteTransAddMirH(param_1,param_2,param_3,param_4);
      return;
    case 2:
      W_PutSpriteTransSubMirH(param_1,param_2,param_3,param_4);
      return;
    case 3:
      W_PutSpriteTransAddMirH_B(param_1,param_2,param_3,param_4,param_7,param_8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirH(param_1,param_2,param_3,param_4);
      return;
    }
  }
  else if (param_5 < 2) {
    if (param_5 == 0) {
      switch(param_6) {
      case 1:
        W_PutSpriteTransAdd(param_1,param_2,param_3,param_4);
        return;
      case 2:
        W_PutSpriteTransSub(param_1,param_2,param_3,param_4);
        return;
      case 3:
        W_PutSpriteTransAdd_B(param_1,param_2,param_3,param_4,param_7,param_8);
        return;
      case 0xffffffff:
      case 0:
        W_PutSprite(param_1,param_2,param_3,param_4);
        return;
      }
    }
  }
  else if (param_5 == 2) {
    switch(param_6) {
    case 1:
      W_PutSpriteTransAddMirV(param_1,param_2,param_3,param_4);
      return;
    case 2:
      W_PutSpriteTransSubMirHV(param_1,param_2,param_3,param_4);
      return;
    case 3:
      W_PutSpriteTransAddMirV_B(param_1,param_2,param_3,param_4,param_7,param_8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirV(param_1,param_2,param_3,param_4);
      return;
    }
  }
  else if (param_5 == 3) {
    switch(param_6) {
    case 1:
      W_PutSpriteTransAddMirHV(param_1,param_2,param_3,param_4);
      return;
    case 2:
      W_PutSpriteTransSubMirHV(param_1,param_2,param_3,param_4);
      return;
    case 3:
      W_PutSpriteTransAddMirHV_B(param_1,param_2,param_3,param_4,param_7,param_8);
      return;
    case 0xffffffff:
    case 0:
      W_PutSpriteMirHV(param_1,param_2,param_3,param_4);
      return;
    }
  }
  return;
}

/* AnimScaleSpr_S @ 0x0804a650, 312 bytes */
void AnimScaleSpr_S(int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
                   undefined4 param_7,int param_8,int param_9)

{
  switch(param_7) {
  case 1:
    W_ScaleSpriteTransAdd_S(param_1,param_2,(float)param_3,(float)param_4,param_5,param_6);
    return;
  case 2:
    W_ScaleSpriteTransSub_S(param_1,param_2,(float)param_3,(float)param_4,param_5,param_6);
    return;
  case 3:
    W_ScaleSpriteTransAdd_B_S
              (param_1,param_2,(float)param_3,(float)param_4,param_5,param_6,param_8,param_9);
    return;
  case 0xffffffff:
  case 0:
    W_ScaleSprite_S(param_1,param_2,(float)param_3,(float)param_4,param_5,param_6);
    return;
  default:
    return;
  }
}

/* AnimRotateSpr @ 0x0804a790, 368 bytes */
void AnimRotateSpr(int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
                  float param_7,float param_8,float param_9,undefined4 param_10,int param_11,
                  int param_12)

{
  switch(param_10) {
  case 1:
    W_RotateSpriteTransAdd_P
              (param_1,param_2,(float)param_3,(float)param_4,param_5,param_6,param_7,param_8,param_9
              );
    return;
  case 2:
    W_RotateSpriteTransSub_P
              (param_1,param_2,(float)param_3,(float)param_4,param_5,param_6,param_7,param_8,param_9
              );
    return;
  case 3:
    W_RotateSpriteTransAdd_B_P
              (param_1,param_2,(float)param_3,(float)param_4,param_5,param_6,param_7,param_8,param_9
               ,param_11,param_12);
    return;
  case 0xffffffff:
  case 0:
    W_RotateSprite_P(param_1,param_2,(float)param_3,(float)param_4,param_5,param_6,param_7,param_8,
                     param_9);
    return;
  default:
    return;
  }
}

/* AlphaMixSrc @ 0x0804a900, 15 bytes */
int AlphaMixSrc(int param_1,int param_2)

{
  return param_2 * param_1 >> 8;
}

/* AlphaMixDest @ 0x0804a910, 24 bytes */
int AlphaMixDest(int param_1,int param_2)

{
  return param_1 + ((0x100 - param_1) * param_2 >> 8);
}

