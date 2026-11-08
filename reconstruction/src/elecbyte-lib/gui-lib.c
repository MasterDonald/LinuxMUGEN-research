/*
 * gui-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08081580-0x08081fe2, 19 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* NewListNode @ 0x08081580, 16 bytes */
undefined4 NewListNode(void)

{
  undefined4 uVar1;
  
  uVar1 = ecalloc(1,0xc);
  return uVar1;
}

/* AddNodeToEnd @ 0x08081590, 32 bytes */
void AddNodeToEnd(int *param_1)

{
  if (param_1 != (int *)0x0) {
    *param_1 = (int)EB_ListTail;
    param_1[1] = 0;
    EB_ListTail[1] = (int)param_1;
    EB_ListTail = param_1;
  }
  return;
}

/* MoveNodeToEnd @ 0x080815b0, 53 bytes */
void MoveNodeToEnd(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 != EB_ListTail) && (param_1 != EB_ListHead)) {
    iVar1 = *param_1;
    piVar2 = (int *)param_1[1];
    *(int **)(iVar1 + 4) = piVar2;
    *piVar2 = iVar1;
    param_1[1] = 0;
    *param_1 = (int)EB_ListTail;
    EB_ListTail[1] = (int)param_1;
    EB_ListTail = param_1;
  }
  return;
}

/* MoveNodeToStart @ 0x080815f0, 1 bytes */
void MoveNodeToStart(void)

{
  return;
}

/* EB_GUIInit @ 0x08081600, 302 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_) */
undefined4 EB_GUIInit(int param_1)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  char *__format;
  undefined4 uVar2;
  
  GUI_root = (int *)0x0;
  GUI_globalfont = (int *)0x0;
  num_windows = 0;
  GUI_root = (int *)ecalloc(1,0x48);
  if (GUI_root == (int *)0x0) {
    __format = "Not enough memory to init Root window\n";
    uVar2 = extraout_EDX;
  }
  else {
    GUI_globalfont = (int *)FontReadFile("font/f-4x6.fnt");
    piVar1 = GUI_root;
    if (GUI_globalfont != (int *)0x0) {
      GUI_root[2] = S_Width;
      piVar1[3] = S_Height;
      piVar1[0x10] = 0;
      piVar1[0x11] = 0;
      piVar1[1] = 0;
      *piVar1 = 0;
      piVar1[10] = param_1;
      piVar1[8] = 0;
      piVar1[9] = 0;
      piVar1[0xc] = 0;
      piVar1[0xd] = 0;
      has_focus = piVar1;
      (*(uint *)((char *)&window_order + 0)) = piVar1;
      num_windows = 0;
      EB_ListTail = (int *)NewListNode();
      EB_ListHead = EB_ListTail;
      EB_ListTail[2] = (int)GUI_root;
      *EB_ListTail = 0;
      EB_ListTail[1] = 0;
      num_windows = num_windows + 1;
      GUI_state = 0;
      EB_ListCurrent = (int)EB_ListTail;
      return 0;
    }
    __format = "Could not find font/f-4x6.fnt.\n";
    GUI_globalfont = (int *)0x0;
    uVar2 = extraout_ECX;
  }
  fprintf((FILE *)stderr,__format,uVar2,uVar2);
  return 0xffffffff;
}

/* EB_GUIDeInit @ 0x08081730, 1 bytes */
void EB_GUIDeInit(void)

{
  return;
}

/* EB_GUISetWinAttr @ 0x08081740, 17 bytes */
void EB_GUISetWinAttr(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | param_2;
  return;
}

/* EB_GUINewWindow @ 0x08081760, 524 bytes */
int * EB_GUINewWindow(char *param_1,int param_2,int param_3,int param_4,int *param_5)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  size_t sVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *extraout_ECX;
  int *extraout_EDX;
  char *pcVar8;
  
  piVar2 = (int *)ecalloc(1,0x48);
  if (piVar2 == (int *)0x0) {
    pcVar8 = "Not enough memory to create a new window\n";
    piVar2 = extraout_EDX;
  }
  else {
    *piVar2 = param_2;
    piVar2[1] = param_3;
    piVar2[3] = (int)param_5;
    piVar2[2] = param_4;
    piVar2[6] = 0;
    piVar2[8] = 1;
    piVar3 = ClipboardNew(0x50,0x14);
    if (piVar3 == (int *)0x0) {
      pcVar8 = "Not enough memory to create clipboard\n";
      piVar2 = param_5;
    }
    else {
      ClipboardClear(piVar3);
      pcVar8 = (char *)ecalloc(0x100,1);
      if (pcVar8 == (char *)0x0) {
        pcVar8 = "Not enough memory to create window title buffer.\n";
        piVar2 = param_5;
      }
      else {
        strncpy(pcVar8,param_1,0x100);
        sVar4 = strlen(param_1);
        if (0xff < sVar4) {
          pcVar8[0xff] = '\0';
        }
        piVar5 = (int *)V_Alloc(param_4,(int)param_5);
        if (piVar5 == (int *)0x0) {
          pcVar8 = "Not enough memory to create window content screen.\n";
        }
        else {
          iVar6 = ClsnArrayNew(5);
          if (iVar6 != 0) {
            ClsnArrayAddRect(iVar6,param_2,param_3,param_2 + param_4,param_3 + (int)param_5);
            ClsnArrayAddRect(iVar6,param_2,param_3 + -10,param_2 + param_4,param_3);
            iVar7 = G_MakeColor(0,0,0x40);
            piVar1 = V_Current;
            piVar2[7] = iVar7;
            V_SetBuf(piVar5,0);
            W_Cls(piVar2[7]);
            V_SetBuf(piVar1,0);
            piVar2[10] = (int)piVar5;
            piVar2[0xe] = iVar6;
            piVar2[0xc] = (int)piVar3;
            piVar2[9] = (int)pcVar8;
            piVar2[0xb] = 0;
            *(int **)(window_order + num_windows * 4) = piVar2;
            num_windows = num_windows + 1;
            piVar3 = (int *)NewListNode();
            if (piVar3 == (int *)0x0) {
              return (int *)0x0;
            }
            piVar3[2] = (int)piVar2;
            AddNodeToEnd(piVar3);
            return piVar2;
          }
          pcVar8 = "Error setting up window bounding boxes.\n";
          piVar2 = extraout_ECX;
        }
      }
    }
  }
  fprintf((FILE *)stderr,pcVar8,piVar2,piVar2);
  return (int *)0x0;
}

/* EB_GUICloseWindow @ 0x08081970, 57 bytes */
void EB_GUICloseWindow(void *param_1)

{
  *(undefined4 *)((int)param_1 + 0x20) = 0;
  ClipboardFree(*(undefined4 **)((int)param_1 + 0x30));
  V_DeAlloc(*(int *)((int)param_1 + 0x28));
  free(*(void **)((int)param_1 + 0x24));
  free(param_1);
  return;
}

/* EB_GUIDrawClipboard @ 0x080819b0, 249 bytes */
void EB_GUIDrawClipboard(int *param_1,int param_2,int param_3,uint param_4)

{
  int *piVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int local_14;
  
  local_14 = 0;
  piVar7 = (int *)param_1[0xd];
  if ((int *)param_1[0xd] == (int *)0x0) {
    piVar7 = GUI_globalfont;
  }
  piVar1 = (int *)param_1[0xc];
  uVar2 = piVar1[3];
  uVar4 = param_1[3] / piVar7[3] - 1;
  if ((int)uVar2 <= (int)uVar4) {
    uVar4 = uVar2;
  }
  uVar6 = piVar1[5];
  for (; (uVar6 != piVar1[4] && (local_14 < (int)uVar4)); local_14 = local_14 + 1) {
    uVar5 = uVar2;
    if (-1 < (int)uVar6) {
      uVar5 = uVar6 - 1;
    }
    uVar6 = uVar5;
  }
  if (uVar6 != piVar1[5]) {
    do {
      pcVar3 = *(char **)(*piVar1 + uVar6 * 4);
      if (pcVar3 == (char *)0x0) {
        return;
      }
      V_FontDraw(pcVar3,piVar7,param_2 + *param_1,param_3 + param_1[1],param_4);
      param_3 = param_3 + piVar7[6] + piVar7[3];
      uVar6 = uVar6 + 1 & (piVar1[3] <= (int)(uVar6 + 1)) - 1;
    } while (uVar6 != piVar1[5]);
  }
  if (**(char **)(*piVar1 + uVar6 * 4) != '\0') {
    V_FontDraw(*(char **)(*piVar1 + uVar6 * 4),piVar7,param_2 + *param_1,param_3 + param_1[1],
               param_4);
  }
  return;
}

/* EB_GUIPutSurface @ 0x08081ab0, 1 bytes */
void EB_GUIPutSurface(void)

{
  return;
}

/* EB_GUIRaiseWindow @ 0x08081ac0, 19 bytes */
undefined4 EB_GUIRaiseWindow(int *param_1)

{
  MoveNodeToEnd(param_1);
  return 0;
}

/* EB_GUIPutSprite @ 0x08081ae0, 107 bytes */
void EB_GUIPutSprite(int param_1,int *param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  
  piVar1 = V_Current;
  V_SetBuf(*(int **)(param_1 + 0x28),0);
  if (param_5 == 0) {
    W_PutSprite8to16(param_2,0,param_3,param_4);
  }
  else {
    W_PutSprite(param_2,0,param_3,param_4);
  }
  V_SetBuf(piVar1,0);
  return;
}

/* EB_GUIClearWindow @ 0x08081b50, 52 bytes */
void EB_GUIClearWindow(int param_1)

{
  int *piVar1;
  
  piVar1 = V_Current;
  V_SetBuf(*(int **)(param_1 + 0x28),0);
  W_Cls(*(uint *)(param_1 + 0x1c));
  V_SetBuf(piVar1,0);
  return;
}

/* EB_GUIDrawWindow @ 0x08081b90, 562 bytes */
void EB_GUIDrawWindow(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 extraout_EDX;
  uint uVar9;
  
  uVar5 = G_MakeColor(0xff,0xff,0xff);
  uVar6 = G_MakeColor(0xff,0,0);
  uVar7 = G_MakeColor(0x3a,0x6e,0xa5);
  uVar8 = G_MakeColor(0x80,0x80,0x80);
  uVar1 = *param_1;
  if (param_1 == (uint *)has_focus) {
    uVar9 = param_1[1];
    uVar2 = param_1[2];
    uVar8 = uVar7;
  }
  else {
    uVar9 = param_1[1];
    uVar2 = param_1[2];
  }
  W_BoxFill(uVar1 - 1 & 0xffffffffU - ((int)uVar1 >> 0x1f),param_1[1] - 10,uVar1 + uVar2 + 1,uVar9,
            uVar8);
  W_BoxTransAdd16(*(int *)(*(int *)(param_1[0xe] + 8) + 4) - 1,
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 8),
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 0xc),
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 0x10),uVar5);
  W_BoxTransAdd16(*(int *)(*(int *)(param_1[0xe] + 8) + 0x18) - 1,
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 0x1c),
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 0x20),
                  *(uint *)(*(int *)(param_1[0xe] + 8) + 0x24),uVar6);
  V_FontWrite(GUI_globalfont,*param_1 + 10,param_1[1] - 3,uVar5,"%s",param_1[9]);
  iVar4 = V_CurrentIdx;
  piVar3 = V_Current;
  if ((param_1[6] & 1) == 0) {
    W_BoxFill(*param_1,param_1[1],param_1[2] + *param_1 + -1,param_1[3] + param_1[1] + -1,param_1[7]
             );
  }
  else {
    W_BoxFillTransAdd16_B50
              (*param_1,param_1[1],param_1[2] + *param_1,param_1[3] + param_1[1],param_1[7]);
  }
  W_Define(*param_1,param_1[1],param_1[2] + *param_1,param_1[3] + param_1[1]);
  EB_GUIDrawClipboard((int *)param_1,10,10,uVar5);
  if ((GUI_state == 1) && ((uint *)has_focus == param_1)) {
    V_FontWrite(GUI_globalfont,((int)param_1[2] >> 1) + *param_1 + GUI_globalfont[2] * -6,
                ((int)param_1[3] >> 1) + param_1[1],uVar5,"(%d, %d)",*param_1,param_1[1],
                extraout_EDX);
  }
  V_SetBuf(piVar3,iVar4);
  return;
}

/* EB_DrawWindows @ 0x08081dd0, 42 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void EB_DrawWindows(void)

{
  int iVar1;
  undefined4 unaff_EBX;
  
  for (iVar1 = EB_ListHead[1]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    EB_GUIDrawWindow(*(uint **)(iVar1 + 8));
  }
  return;
}

/* EB_GUIMoveWindow @ 0x08081e00, 86 bytes */
void EB_GUIMoveWindow(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  param_1[1] = param_3;
  *param_1 = param_2;
  iVar1 = *(int *)(param_1[0xe] + 8);
  *(int *)(iVar1 + 4) = param_2;
  *(int *)(iVar1 + 8) = param_1[1];
  *(int *)(iVar1 + 0xc) = param_1[2] + *param_1;
  *(int *)(iVar1 + 0x10) = param_1[3] + param_1[1];
  *(int *)(iVar1 + 0x18) = *param_1;
  *(int *)(iVar1 + 0x1c) = param_1[1] + -10;
  *(int *)(iVar1 + 0x20) = param_1[2] + *param_1;
  *(int *)(iVar1 + 0x24) = param_1[1];
  return;
}

/* DetermineFocus @ 0x08081e60, 79 bytes */
int * DetermineFocus(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = EB_ListTail;
  if (EB_ListTail != EB_ListHead) {
    do {
      iVar1 = ClsnMixDetectRectIndiv(param_1,*(int *)(piVar2[2] + 0x38),0,0);
      *param_2 = iVar1;
      if (-1 < iVar1) {
        return piVar2;
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != EB_ListHead);
  }
  return EB_ListHead;
}

/* EB_GUIUpdate @ 0x08081eb0, 306 bytes
 * REVIEW: pid-unaff_
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
void EB_GUIUpdate(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *unaff_ESI;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_40 (*(uint *)(ghidra_frame + 0x0))
#define local_3c (*(undefined1 (*)[4])(ghidra_frame + 0x4))
#define local_38 (*(int *)(ghidra_frame + 0x8))
#define local_34 (*(int *)(ghidra_frame + 0xc))
#define local_30 (*(int *)(ghidra_frame + 0x10))
#define local_2c (*(int *)(ghidra_frame + 0x14))
  
  iVar5 = mouse_needs_poll();
  if (iVar5 != 0) {
    poll_mouse();
  }
  uVar3 = mouse_b;
  iVar2 = mouse_y;
  iVar5 = mouse_x;
  local_30 = mouse_x;
  local_38 = mouse_x;
  local_2c = mouse_y;
  local_34 = mouse_y;
  if (GUI_state == 0) {
    unaff_ESI = (int *)DetermineFocus((int)local_3c,(int *)&local_40);
    if (unaff_ESI != EB_ListHead) {
      has_focus = (int *)unaff_ESI[2];
    }
  }
  if (((uVar3 & 1) != 0) && (GUI_state == 0)) {
    GUI_state = 2;
  }
  if (uVar3 == 0) {
    GUI_state = 0;
  }
  if (((GUI_state == 2) && (has_focus != GUI_root)) && (local_40 < 2)) {
    GUI_state = 3;
    EB_GUIRaiseWindow(unaff_ESI);
  }
  piVar4 = has_focus;
  if ((GUI_state == 3) && (unaff_ESI != EB_ListHead)) {
    piVar1 = has_focus + 1;
    has_focus[4] = iVar5 - *has_focus;
    piVar4[5] = iVar2 - *piVar1;
    GUI_state = 1;
  }
  if ((GUI_state == 1) && (has_focus != GUI_root)) {
    EB_GUIMoveWindow(has_focus,iVar5 - has_focus[4],iVar2 - has_focus[5]);
  }
  EB_DrawWindows();
  return;
}
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c

