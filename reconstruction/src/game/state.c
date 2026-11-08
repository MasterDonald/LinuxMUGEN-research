/*
 * state.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080d19b0-0x080d2b53, 7 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SctrlReadFileTP @ 0x080d19b0, 370 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0xd0-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SctrlReadFileTP(int param_1,int param_2)

{
  size_t sVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *__src;
  int iVar4;
  uint uVar5;
  int iVar6;
  unsigned char ghidra_frame[0xd0] __attribute__((aligned(16)));
#define local_cc (*(int (*)[47])(ghidra_frame + 0x4))
  
  sVar1 = TPGroupMatchCount(param_1,"statedef ");
  if (sVar1 == 0) {
    sprintf((char *)(g + 0x81d2),"Need at least one statedef");
  }
  else {
    piVar2 = (int *)ecalloc(1,4);
    if (piVar2 != (int *)0x0) {
      puVar3 = ArrayNew(sVar1,0xa4,0);
      *piVar2 = (int)puVar3;
      if (puVar3 != (undefined4 *)0x0) {
        iVar6 = 0;
        __src = (int *)TPGroupScanFirst(param_1);
        if ((int)sVar1 < 1) {
          return piVar2;
        }
        while( true ) {
          while (iVar4 = strimatch((char *)((int)__src + 1),"statedef "), iVar4 == 0) {
            __src = (int *)TPGroupScanNext(param_1);
          }
          uVar5 = __strtol_internal((byte *)((int)__src + 10),(undefined4 *)0x0,10,0);
          iVar4 = SCtrlParseState(param_1,local_cc,__src,param_2);
          if (iVar4 == 0) break;
          iVar6 = iVar6 + 1;
          ArrayAdd(*piVar2,local_cc,uVar5,0);
          __src = (int *)TPGroupScanNext(param_1);
          if ((int)sVar1 <= iVar6) {
            return piVar2;
          }
        }
        strcat((char *)(g + 0x81d2),"\nError in ");
        strcat((char *)(g + 0x81d2),(char *)__src);
      }
    }
  }
  return (int *)0x0;
}
#undef local_cc

/* SctrlAddFileTP @ 0x080d1b30, 339 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0xd0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SctrlAddFileTP(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *__src;
  int iVar4;
  uint uVar5;
  unsigned char ghidra_frame[0xd0] __attribute__((aligned(16)));
#define local_cc (*(int (*)[47])(ghidra_frame + 0x4))
  
  iVar1 = TPGroupMatchCount(param_2,"statedef ");
  if ((iVar1 == 0) || (iVar2 = ArrayResize(*param_1,iVar1 + *(int *)(*param_1 + 8)), iVar2 == 0)) {
LAB_080d1bb1:
    uVar3 = 0;
  }
  else {
    iVar2 = 0;
    __src = (int *)TPGroupScanFirst(param_2);
    if (0 < iVar1) {
      do {
        while (iVar4 = strimatch((char *)((int)__src + 1),"statedef "), iVar4 == 0) {
          __src = (int *)TPGroupScanNext(param_2);
        }
        uVar5 = __strtol_internal((byte *)((int)__src + 10),(undefined4 *)0x0,10,0);
        iVar4 = SCtrlParseState(param_2,local_cc,__src,param_3);
        if (iVar4 == 0) {
          strcat((char *)(g + 0x81d2),"\nError in ");
          strcat((char *)(g + 0x81d2),(char *)__src);
          goto LAB_080d1bb1;
        }
        iVar2 = iVar2 + 1;
        ArrayAdd(*param_1,local_cc,uVar5,0);
        __src = (int *)TPGroupScanNext(param_2);
      } while (iVar2 < iVar1);
    }
    uVar3 = 1;
  }
  return uVar3;
}
#undef local_cc

/* SCtrlParseState @ 0x080d1c90, 1998 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0xb0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseState(int param_1,int *param_2,int *param_3,int param_4)

{
  undefined4 uVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  char *pcVar7;
  byte *pbVar8;
  undefined3 extraout_var;
  uint *puVar9;
  uint *puVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  unsigned char ghidra_frame[0xb0] __attribute__((aligned(16)));
#define local_a4 (*(size_t *)(ghidra_frame + 0xc))
#define local_a0 (*(char **)(ghidra_frame + 0x10))
#define local_9c (*(char (*)[60])(ghidra_frame + 0x14))
#define acStack_60 (*(char (*)[4])(ghidra_frame + 0x50))
#define local_5c (*(uint (*)[19])(ghidra_frame + 0x54))
  
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  uVar3 = __strtol_internal((byte *)((int)param_3 + 10),(undefined4 *)0x0,10,0);
  strcpy((char *)local_5c,(char *)((int)param_3 + 1));
  puVar10 = local_5c;
  do {
    puVar9 = puVar10;
    puVar10 = puVar9 + 1;
    uVar12 = *puVar9 + 0xfefefeff & (*puVar9 ^ 0xffffffff);
    uVar13 = uVar12 & 0x80808080;
  } while (uVar13 == 0);
  if ((uVar12 & 0x8080) == 0) {
    uVar13 = uVar13 >> 0x10;
    puVar10 = (uint *)((int)puVar9 + 6);
  }
  uVar14 = uVar13 & 0xffffff00;
  *(char *)((int)puVar10 +
           (int)(acStack_60 + (-(int)local_5c - (uint)CARRY1((byte)uVar13,(byte)uVar13)))) = '\0';
  uVar12 = uVar14;
  iVar4 = TPGroupSeek(param_1,(char *)local_5c);
  if (iVar4 == -1) {
    sprintf((char *)(g + 0x81d2),"Can\'t access %s",param_3,uVar3);
    return 0;
  }
  local_a4 = 0;
  iVar4 = TPGroupScanNext(param_1);
  sprintf(local_9c,"state ",uVar14,uVar12);
  while ((iVar4 != 0 && (iVar5 = strimatch((char *)(iVar4 + 1),local_9c), iVar5 != 0))) {
    local_a4 = local_a4 + 1;
    iVar4 = TPGroupScanNext(param_1);
  }
  TPGroupSeek(param_1,(char *)local_5c);
  if ((int)local_a4 < 1) {
    sprintf((char *)(g + 0x81d2),"Need at least one state controller",param_3,param_3);
    return 0;
  }
  memset(param_2,0,0xa4);
  puVar6 = ArrayNew(local_a4,100,0);
  *param_2 = (int)puVar6;
  if (puVar6 == (undefined4 *)0x0) {
    return 0;
  }
  if (-1 < (int)uVar3) {
    param_2[1] = 1;
    pcVar7 = TPGetValue(param_1,"type");
    if (pcVar7 != (char *)0x0) {
      switch(*(undefined4 *)(__ctype_tolower + *pcVar7 * 4)) {
      case 0x61:
        param_2[1] = 3;
        break;
      default:
        sprintf((char *)(g + 0x81d2),"State type \"%s\" not valid",pcVar7,param_2);
        return 0;
      case 99:
        param_2[1] = 2;
        break;
      case 0x6c:
        param_2[1] = 4;
        break;
      case 0x73:
        param_2[1] = 1;
        break;
      case 0x75:
        param_2[1] = -1;
      }
    }
    param_2[2] = 0;
    pcVar7 = TPGetValue(param_1,"movetype");
    if (pcVar7 != (char *)0x0) {
      iVar5 = *(int *)(__ctype_tolower + *pcVar7 * 4);
      if (iVar5 == 0x68) {
        param_2[2] = 2;
      }
      else if (iVar5 < 0x69) {
        if (iVar5 != 0x61) {
LAB_080d1f60:
          sprintf((char *)(g + 0x81d2),"State movetype \"%s\" not valid",pcVar7,iVar4);
          return 0;
        }
        param_2[2] = 1;
      }
      else if (iVar5 == 0x69) {
        param_2[2] = 0;
      }
      else {
        if (iVar5 != 0x75) goto LAB_080d1f60;
        param_2[2] = -1;
      }
    }
    ConstExpI(param_2 + 4,-1);
    pbVar8 = (byte *)TPGetValue(param_1,"juggle");
    iVar4 = InfixToPostfix(pbVar8,param_2 + 4,param_4,(undefined4 *)0x0,1);
    if (iVar4 != 0) {
      ConstExpI(param_2 + 7,0);
      pbVar8 = (byte *)TPGetValue(param_1,"facep2");
      iVar4 = InfixToPostfix(pbVar8,param_2 + 7,param_4,(undefined4 *)0x0,1);
      if ((((iVar4 != 0) &&
           (iVar4 = ItoP_TPConstI(param_1,"hitdefpersist",param_2 + 10,param_4,0), iVar4 != 0)) &&
          (iVar4 = ItoP_TPConstI(param_1,"hitcountpersist",param_2 + 0xd,param_4,0), iVar4 != 0)) &&
         (iVar4 = ItoP_TPConstI(param_1,"movehitpersist",param_2 + 0x10,param_4,0), iVar4 != 0)) {
        pbVar8 = (byte *)TPGetValue(param_1,"sprpriority");
        if (pbVar8 != (byte *)0x0) {
          iVar4 = InfixToPostfix(pbVar8,param_2 + 0x14,param_4,(undefined4 *)0x0,1);
          if (iVar4 == 0) {
            return 0;
          }
          param_2[0x13] = 1;
        }
        param_2[3] = 0;
        pcVar7 = TPGetValue(param_1,"physics");
        if (pcVar7 != (char *)0x0) {
          switch(*(undefined4 *)(__ctype_tolower + *pcVar7 * 4)) {
          case 0x61:
            param_2[3] = 3;
            break;
          default:
            sprintf((char *)(g + 0x81d2),"State physics \"%s\" not valid",pcVar7,param_4);
            return 0;
          case 99:
            param_2[3] = 2;
            break;
          case 0x6e:
            param_2[3] = 0;
            break;
          case 0x73:
            param_2[3] = 1;
            break;
          case 0x75:
            param_2[3] = -1;
          }
        }
        param_3 = param_2 + 0x1a;
        ConstExpF(param_2 + 0x17,-0x39001000);
        ConstExpF(param_3,-0x39001000);
        ConstExpF(param_2 + 0x1d,-0x39001000);
        ConstExpI(param_2 + 0x20,-1);
        ConstExpI(param_2 + 0x23,-1);
        ConstExpI(param_2 + 0x26,0);
        pbVar8 = (byte *)TPGetValue(param_1,"velset");
        if ((pbVar8 == (byte *)0x0) ||
           ((pbVar8 = SCtrlReadExpList(pbVar8,"fff",param_4,&local_a0,param_2 + 0x17,param_3,
                                       param_2 + 0x1d), pbVar8 != (byte *)0x0 && (*local_a0 == '\0')
            ))) {
          pbVar8 = (byte *)TPGetValue(param_1,"ctrl");
          iVar4 = InfixToPostfix(pbVar8,param_2 + 0x20,param_4,(undefined4 *)0x0,1);
          if (iVar4 != 0) {
            pbVar8 = (byte *)TPGetValue(param_1,"anim");
            iVar4 = InfixToPostfix(pbVar8,param_2 + 0x23,param_4,(undefined4 *)0x0,1);
            if (iVar4 != 0) {
              pbVar8 = (byte *)TPGetValue(param_1,"poweradd");
              iVar4 = InfixToPostfix(pbVar8,param_2 + 0x26,param_4,(undefined4 *)0x0,1);
              if (iVar4 != 0) goto LAB_080d2369;
            }
          }
        }
      }
    }
    return 0;
  }
LAB_080d2369:
  iVar4 = 0;
  sprintf(local_9c,"state ",param_3,param_3);
  if (0 < (int)local_a4) {
    do {
      pcVar7 = (char *)TPGroupScanNext(param_1);
      if (pcVar7 == (char *)0x0) {
        sprintf((char *)(g + 0x81d2),"Can\'t access [%s] controller %i",local_9c,iVar4 + 1);
        return 0;
      }
      iVar5 = strimatch(pcVar7 + 1,local_9c);
      if (iVar5 == 0) {
        sprintf((char *)(g + 0x81d2),"Can\'t access [%s] controller %i",local_9c,iVar4 + 1);
        return 0;
      }
      iVar5 = 7;
      cVar11 = ',';
      if (pcVar7[7] != ',') {
        if (pcVar7[7] == '\0') {
          cVar11 = '\0';
        }
        else {
          do {
            iVar5 = iVar5 + 1;
            cVar11 = pcVar7[iVar5];
            if (cVar11 == ',') break;
          } while (cVar11 != '\0');
        }
      }
      if (cVar11 == '\0') {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = __strtol_internal((byte *)(pcVar7 + iVar5 + 1),(undefined4 *)0x0,10,0);
      }
      bVar2 = SCtrlParseElem(param_1,param_2,uVar3,param_4);
      if (GHIDRA_ZEXT8(bVar2) == 0) {
        strcat((char *)(g + 0x81d2),"\nError parsing ");
        strcat((char *)(g + 0x81d2),pcVar7);
        return 0;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)local_a4);
  }
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  return 1;
}
#undef local_a4
#undef local_a0
#undef local_9c
#undef acStack_60
#undef local_5c

/* SCtrlInit @ 0x080d2460, 32 bytes */
undefined4 SCtrlInit(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x104; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *param_1 = param_2;
  return 1;
}

/* SCtrlRCFree @ 0x080d2480, 257 bytes */
void SCtrlRCFree(undefined4 *param_1)

{
  void *pvVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  pvVar1 = (void *)*param_1;
  piVar2 = (int *)ArrayScanFirst((int)pvVar1);
  while (piVar2 != (int *)0x0) {
    puVar3 = (undefined4 *)ArrayScanFirst(*piVar2);
    while (puVar3 != (undefined4 *)0x0) {
      SCtrlRCElemFree(puVar3);
      puVar3 = (undefined4 *)ArrayScanNext(*piVar2);
    }
    FreeExpression(piVar2 + 4);
    FreeExpression(piVar2 + 7);
    FreeExpression(piVar2 + 10);
    FreeExpression(piVar2 + 0xd);
    FreeExpression(piVar2 + 0x10);
    FreeExpression(piVar2 + 0x14);
    FreeExpression(piVar2 + 0x17);
    FreeExpression(piVar2 + 0x1a);
    FreeExpression(piVar2 + 0x1d);
    FreeExpression(piVar2 + 0x20);
    FreeExpression(piVar2 + 0x23);
    FreeExpression(piVar2 + 0x26);
    ArrayFree((void *)*piVar2);
    piVar2 = (int *)ArrayScanNext((int)pvVar1);
  }
  ArrayFree(pvVar1);
  free(param_1);
  return;
}

/* PlayerSCtrlUpdate @ 0x080d2590, 1225 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 4 data addresses written as literals replaced by data-image references
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 PlayerSCtrlUpdate(int *player)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_3c (*(int *)(ghidra_frame + 0x4))
#define local_38 (*(int *)(ghidra_frame + 0x8))
  
  PlayerGetRedirInfo((int)player,&local_3c);
  if ((int *)player[0x2fb] == (int *)0x0) {
    iVar3 = player[0x2fd];
    iVar5 = *(int *)player[0x2fa];
  }
  else {
    iVar3 = player[0x2fd];
    iVar5 = *(int *)player[0x2fb];
  }
  piVar2 = (int *)ArrayAccessGrpItem(iVar5,iVar3,0);
  if (player[0x386] < 1) {
    if (piVar2 == (int *)0x0) {
      player[0x38f] = 0;
      if (player[0x37f] != 0) {
        return 0;
      }
      player[0x4e8] = 0;
      player[0x4e7] = 0;
      player[0x38c] = 0;
      player[0x38d] = 0;
      player[0x459] = 0;
      return 0;
    }
    iVar3 = player[0x37f];
    player[0x38f] = 1;
    if (iVar3 == 0) {
      iVar3 = EvalExpressionI((int)player,piVar2 + 0xd,1);
      if (iVar3 == 0) {
        player[0x4e7] = 0;
        player[0x4e8] = 0;
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 0x10,1);
      if (iVar3 == 0) {
        player[0x38c] = 0;
        player[0x38d] = 0;
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 10,1);
      if (iVar3 == 0) {
        player[0x459] = 0;
        player[0x456] = 0;
      }
      if (piVar2[0x13] != 0) {
        iVar3 = EvalExpressionI((int)player,piVar2 + 0x14,1);
        player[0x73] = iVar3;
      }
      iVar3 = player[0x37f];
    }
    if (iVar3 == 0) {
      iVar3 = *piVar2;
      iVar5 = 0;
      if (0 < *(int *)(iVar3 + 8)) {
        do {
          *(undefined1 *)((int)player + iVar5 + 0xbfc) = 0;
          iVar3 = *piVar2;
          iVar5 = iVar5 + 1;
        } while (iVar5 < *(int *)(iVar3 + 8));
      }
      if (0x200 < *(int *)(iVar3 + 8)) {
        sprintf((char *)(g + 0x81d2),"state %i can only have max of %i controllers",player[0x2fd],
                0x200);
        ErrorExit();
      }
      if (piVar2[1] != -1) {
        player[0x380] = piVar2[1];
      }
      if (piVar2[2] != -1) {
        player[0x381] = piVar2[2];
      }
      if (piVar2[3] != -1) {
        player[0x382] = piVar2[3];
      }
      if (((local_3c != 0) && (iVar3 = EvalExpressionI((int)player,piVar2 + 7,1), iVar3 != 0)) &&
         (iVar3 = PlayerDistX((int)player,local_3c), iVar3 < 0)) {
        PlayerTurnAround((int)player);
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 4,1);
      if (iVar3 < -1) {
        iVar3 = -1;
        Warn((int)player,(int)&DAT_0827cf33);
      }
      if (iVar3 != -1) {
        player[0x463] = iVar3;
      }
      player[0x4b3] = player[0x1a];
      fVar6 = EvalExpressionF(player,piVar2 + 0x17);
      if (fVar6 != -32760.0) {
        player[0x6d] = GHIDRA_F2I(int, ((float10)player[100] * fVar6));
      }
      fVar6 = EvalExpressionF(player,piVar2 + 0x1a);
      if (fVar6 != -32760.0) {
        player[0x6e] = GHIDRA_F2I(int, fVar6);
      }
      fVar6 = EvalExpressionF(player,piVar2 + 0x1d);
      if (fVar6 != -32760.0) {
        player[0x6f] = GHIDRA_F2I(int, fVar6);
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 0x23,1);
      if (iVar3 < -1) {
        iVar3 = -1;
        Warn((int)player,(int)&DAT_0827cf49);
      }
      if (iVar3 != -1) {
        PlayerSelfAnim(player,iVar3);
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 0x20,1);
      if (iVar3 < -1) {
        iVar3 = -1;
        Warn((int)player,(int)&DAT_0827d000);
      }
      if (1 < iVar3) {
        iVar3 = 1;
        Warn((int)player,(int)&DAT_0827d000);
      }
      if (iVar3 != -1) {
        player[899] = iVar3;
      }
      iVar3 = EvalExpressionI((int)player,piVar2 + 0x26,1);
      PlayerPowerSet(local_38,iVar3 + **(int **)(local_38 + 0x170));
    }
  }
  if ((piVar2 != (int *)0x0) && (piVar4 = (int *)ArrayScanFirst(*piVar2), piVar4 != (int *)0x0)) {
    iVar3 = 0x10;
    do {
      if ((*(char *)((int)player + iVar3 + 0xbec) == '\0') &&
         ((player[0x386] == 0 || (piVar4[3] != 0)))) {
        AIClearCommands(player + 0xcef);
        iVar5 = SCtrlTrigArrayTest(player,*piVar4,piVar4[1]);
        if (iVar5 != 0) {
          if (piVar4[2] < 1) {
            *(undefined1 *)((int)player + iVar3 + 0xbec) = 1;
          }
          else {
            *(char *)((int)player + iVar3 + 0xbec) = (char)piVar4[2];
          }
          iVar5 = PlayerDoSCtrlApplyElem(player,(int)piVar4,&local_3c);
          if (iVar5 != 0) {
            return 1;
          }
        }
      }
      if ((0 < piVar4[2]) &&
         (((player[0x386] == 0 || (piVar4[3] != 0)) &&
          (cVar1 = *(char *)((int)player + iVar3 + 0xbec) + -1,
          *(char *)((int)player + iVar3 + 0xbec) = cVar1, cVar1 < '\0')))) {
        *(undefined1 *)((int)player + iVar3 + 0xbec) = 0;
      }
      iVar3 = iVar3 + 1;
      piVar4 = (int *)ArrayScanNext(*piVar2);
    } while (piVar4 != (int *)0x0);
  }
  return 0;
}
#undef local_3c
#undef local_38

/* PlayerSCtrlUpdateSpec @ 0x080d2a60, 243 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
void PlayerSCtrlUpdateSpec(int *player,int param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define aiStack_3c (*(int (*)[11])(ghidra_frame + 0x4))
  
  PlayerGetRedirInfo((int)player,aiStack_3c);
  piVar1 = (int *)player[0x2fb];
  if ((piVar1 == (int *)0x0) || ((param_3 & 1) != 0)) {
    piVar1 = (int *)player[0x2fa];
  }
  if ((((piVar1 != (int *)0x0) && (((param_3 & 2) != 0 || (player[0x2fb] != 0)))) &&
      (((param_3 & 4) != 0 || (player[0x2fb] == 0)))) &&
     (piVar1 = (int *)ArrayAccessGrpItem(*piVar1,param_2,0), piVar1 != (int *)0x0)) {
    piVar2 = (int *)ArrayScanFirst(*piVar1);
    while (piVar2 != (int *)0x0) {
      if ((player[0x386] == 0) || (piVar2[3] != 0)) {
        AIClearCommands(player + 0xcef);
        iVar3 = SCtrlTrigArrayTest(player,*piVar2,piVar2[1]);
        if ((iVar3 != 0) &&
           (iVar3 = PlayerDoSCtrlApplyElem(player,(int)piVar2,aiStack_3c), iVar3 != 0)) {
          return;
        }
      }
      piVar2 = (int *)ArrayScanNext(*piVar1);
    }
  }
  return;
}
#undef aiStack_3c

