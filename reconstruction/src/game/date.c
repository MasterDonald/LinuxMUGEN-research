/*
 * date.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808d830-0x0808d935, 2 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* MDYDateCmp @ 0x0808d830, 51 bytes */
int MDYDateCmp(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  if (param_3 == param_6) {
    param_3 = param_1;
    param_6 = param_4;
    if (param_1 == param_4) {
      param_3 = param_2;
      param_6 = param_5;
      if (param_2 == param_5) {
        return 0;
      }
    }
  }
  return (uint)(param_6 < param_3) * 2 + -1;
}

/* datenotostr @ 0x0808d870, 197 bytes
 * REVIEW: type-prop */
/* WARNING: Type propagation algorithm not settling */

void datenotostr(undefined4 param_1,int param_2,undefined **param_3,char *param_4)

{
  size_t sVar1;
  int iVar2;
  undefined *****pppppuVar3;
  undefined *****pppppuVar4;
  char *pcVar5;
  undefined *****apppppuStack_50 [16];
  
  pppppuVar4 = (undefined *****)apppppuStack_50;
  pppppuVar3 = &PTR_s_January_08287a34;
  for (iVar2 = 0xc; pppppuVar4 = pppppuVar4 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
    *pppppuVar4 = *pppppuVar3;
    pppppuVar3 = pppppuVar3 + 1;
  }
  sprintf(param_4,"%i",param_3);
  if (((int)param_3 % 10 == 1) && (param_3 != (undefined **)0xb)) {
    pcVar5 = "st ";
    apppppuStack_50[0] = (undefined *****)((int)param_3 / 10);
  }
  else if (((int)param_3 % 10 == 2) && (param_3 != (undefined **)0xc)) {
    pcVar5 = "nd ";
    apppppuStack_50[0] = pppppuVar4;
  }
  else {
    pcVar5 = "th ";
    apppppuStack_50[0] = pppppuVar3;
  }
  strcat(param_4,pcVar5);
  if (param_2 - 1U < 0xc) {
    apppppuStack_50[0] = (undefined *****)param_3;
    strcat(param_4,(char *)apppppuStack_50[param_2]);
  }
  pcVar5 = " %i";
  sVar1 = strlen(param_4);
  sprintf(param_4 + sVar1,pcVar5,param_1);
  return;
}

