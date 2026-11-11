/*
 * gui-lib.c -- debug GUI
 * Small movable windows with text clipboards drawn over the game in debug
 * mode, driven by the mouse.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/gui-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* NewListNode @ 0x08081580, 16 bytes
 *
 * Allocates a node of the GUI window list.
 *
 * Calls: ecalloc
 * Called by: EB_GUIInit, EB_GUINewWindow
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
uint32_t NewListNode(void)

{
  uint32_t mem;
  
  mem = ecalloc(1,0xc);
  return mem;
}

/* AddNodeToEnd @ 0x08081590, 32 bytes
 *
 * Appends a node to the end of the GUI window list (topmost window).
 *
 * Parameters:
 *   arg1         int *
 *
 * Called by: EB_GUINewWindow
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void AddNodeToEnd(int *arg1)

{
  if (arg1 != (int *)0x0) {
    *arg1 = (int)EB_ListTail;
    arg1[1] = 0;
    EB_ListTail[1] = (int)arg1;
    EB_ListTail = arg1;
  }
  return;
}

/* MoveNodeToEnd @ 0x080815b0, 53 bytes
 *
 * Moves a window's node to the end of the list (brings it to the front).
 *
 * Parameters:
 *   arg1         int *
 *
 * Called by: EB_GUIRaiseWindow
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void MoveNodeToEnd(int *arg1)

{
  int i1;
  int *pi2;
  
  if ((arg1 != EB_ListTail) && (arg1 != EB_ListHead)) {
    i1 = *arg1;
    pi2 = (int *)arg1[1];
    *(int **)(i1 + 4) = pi2;
    *pi2 = i1;
    arg1[1] = 0;
    *arg1 = (int)EB_ListTail;
    EB_ListTail[1] = (int)arg1;
    EB_ListTail = arg1;
  }
  return;
}

/* MoveNodeToStart @ 0x080815f0, 1 bytes
 *
 * Empty in this build.
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void MoveNodeToStart(void)

{
  return;
}

/* EB_GUIInit @ 0x08081600, 302 bytes
 *
 * Initialises the debug GUI: creates the root window covering the screen and
 * loads the small font "font/f-4x6.fnt". Messages: "Not enough memory to
 * init Root window", "Could not find font/f-4x6.fnt.".
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ecalloc, FontReadFile, NewListNode
 * C library: fprintf
 * Called by: _mangled_main
 * Messages:
 *   "Not enough memory to init Root window\n"
 *   "Could not find font/f-4x6.fnt.\n"
 *
 * Elecbyte file: src/lib/gui-lib.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 */
uint32_t EB_GUIInit(int arg1)

{
  int *pi1;
  uint32_t stale_ECX;
  uint32_t stale_EDX;
  char *format;
  uint32_t u2;
  
  GUI_root = (int *)0x0;
  GUI_globalfont = (int *)0x0;
  num_windows = 0;
  GUI_root = (int *)ecalloc(1,0x48);
  if (GUI_root == (int *)0x0) {
    format = "Not enough memory to init Root window\n";
    u2 = stale_EDX;
  }
  else {
    GUI_globalfont = (int *)FontReadFile("font/f-4x6.fnt");
    pi1 = GUI_root;
    if (GUI_globalfont != (int *)0x0) {
      GUI_root[2] = S_Width;
      pi1[3] = S_Height;
      pi1[0x10] = 0;
      pi1[0x11] = 0;
      pi1[1] = 0;
      *pi1 = 0;
      pi1[10] = arg1;
      pi1[8] = 0;
      pi1[9] = 0;
      pi1[0xc] = 0;
      pi1[0xd] = 0;
      has_focus = pi1;
      (*(uint32_t *)((char *)&window_order + 0)) = pi1;
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
    format = "Could not find font/f-4x6.fnt.\n";
    GUI_globalfont = (int *)0x0;
    u2 = stale_ECX;
  }
  fprintf((FILE *)stderr,format,u2,u2);
  return 0xffffffff;
}

/* EB_GUIDeInit @ 0x08081730, 1 bytes
 *
 * Empty in this build.
 *
 * Called by: _mangled_main
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIDeInit(void)

{
  return;
}

/* EB_GUISetWinAttr @ 0x08081740, 17 bytes
 *
 * Sets the GUI's global window attributes.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Called by: _mangled_main
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUISetWinAttr(int arg1,uint32_t arg2)

{
  *(uint32_t *)(arg1 + 0x18) = *(uint32_t *)(arg1 + 0x18) | arg2;
  return;
}

/* EB_GUINewWindow @ 0x08081760, 524 bytes
 *
 * Creates a debug window with a title, position, size and parent: a text
 * clipboard (20 lines of 80 characters), its own drawing buffer, a title bar
 * box for mouse hit tests, and colours. Adds it to the window list. Message:
 * "Not enough memory to create a new window".
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int *
 *
 * Calls: ecalloc, ClipboardNew, ClipboardClear, V_Alloc, ClsnArrayNew,
 *        ClsnArrayAddRect, G_MakeColor, V_SetBuf, W_Cls, NewListNode,
 *        AddNodeToEnd
 * C library: strncpy, strlen, fprintf
 * Called by: _mangled_main
 * Messages:
 *   "Not enough memory to create a new window\n"
 *   "Not enough memory to create clipboard\n"
 *   "Not enough memory to create window title buffer.\n"
 *   "Not enough memory to create window content screen.\n"
 *   "Error setting up window bounding boxes.\n"
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
int * EB_GUINewWindow(char *arg1,int arg2,int arg3,int arg4,int *arg5)

{
  int *pi1;
  int *mem;
  int *clipboard;
  size_t s4;
  int *pi5;
  int clsn;
  int i7;
  int *stale_ECX;
  int *stale_EDX;
  char *mem2;
  
  mem = (int *)ecalloc(1,0x48);
  if (mem == (int *)0x0) {
    mem2 = "Not enough memory to create a new window\n";
    mem = stale_EDX;
  }
  else {
    *mem = arg2;
    mem[1] = arg3;
    mem[3] = (int)arg5;
    mem[2] = arg4;
    mem[6] = 0;
    mem[8] = 1;
    clipboard = ClipboardNew(0x50,0x14);
    if (clipboard == (int *)0x0) {
      mem2 = "Not enough memory to create clipboard\n";
      mem = arg5;
    }
    else {
      ClipboardClear(clipboard);
      mem2 = (char *)ecalloc(0x100,1);
      if (mem2 == (char *)0x0) {
        mem2 = "Not enough memory to create window title buffer.\n";
        mem = arg5;
      }
      else {
        strncpy(mem2,arg1,0x100);
        s4 = strlen(arg1);
        if (0xff < s4) {
          mem2[0xff] = '\0';
        }
        pi5 = (int *)V_Alloc(arg4,(int)arg5);
        if (pi5 == (int *)0x0) {
          mem2 = "Not enough memory to create window content screen.\n";
        }
        else {
          clsn = ClsnArrayNew(5);
          if (clsn != 0) {
            ClsnArrayAddRect(clsn,arg2,arg3,arg2 + arg4,arg3 + (int)arg5);
            ClsnArrayAddRect(clsn,arg2,arg3 + -10,arg2 + arg4,arg3);
            i7 = G_MakeColor(0,0,0x40);
            pi1 = V_Current;
            mem[7] = i7;
            V_SetBuf(pi5,0);
            W_Cls(mem[7]);
            V_SetBuf(pi1,0);
            mem[10] = (int)pi5;
            mem[0xe] = clsn;
            mem[0xc] = (int)clipboard;
            mem[9] = (int)mem2;
            mem[0xb] = 0;
            *(int **)(window_order + num_windows * 4) = mem;
            num_windows = num_windows + 1;
            clipboard = (int *)NewListNode();
            if (clipboard == (int *)0x0) {
              return (int *)0x0;
            }
            clipboard[2] = (int)mem;
            AddNodeToEnd(clipboard);
            return mem;
          }
          mem2 = "Error setting up window bounding boxes.\n";
          mem = stale_ECX;
        }
      }
    }
  }
  fprintf((FILE *)stderr,mem2,mem,mem);
  return (int *)0x0;
}

/* EB_GUICloseWindow @ 0x08081970, 57 bytes
 *
 * Frees a window's clipboard and drawing buffer.
 *
 * Parameters:
 *   arg1         void *
 *
 * Calls: ClipboardFree, V_DeAlloc
 * C library: free
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUICloseWindow(void *arg1)

{
  *(uint32_t *)((int)arg1 + 0x20) = 0;
  ClipboardFree(*(uint32_t **)((int)arg1 + 0x30));
  V_DeAlloc(*(int *)((int)arg1 + 0x28));
  free(*(void **)((int)arg1 + 0x24));
  free(arg1);
  return;
}

/* EB_GUIDrawClipboard @ 0x080819b0, 249 bytes
 *
 * Draws the visible lines of a window's clipboard with the window font (or
 * the global font).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *
 * Calls: V_FontDraw
 * Called by: EB_GUIDrawWindow
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIDrawClipboard(int *arg1,int arg2,int arg3,uint32_t arg4)

{
  int *pi1;
  uint32_t u2;
  char *text;
  uint32_t u4;
  uint32_t u5;
  uint32_t u6;
  int *font;
  int stk_14;
  
  stk_14 = 0;
  font = (int *)arg1[0xd];
  if ((int *)arg1[0xd] == (int *)0x0) {
    font = GUI_globalfont;
  }
  pi1 = (int *)arg1[0xc];
  u2 = pi1[3];
  u4 = arg1[3] / font[3] - 1;
  if ((int)u2 <= (int)u4) {
    u4 = u2;
  }
  u6 = pi1[5];
  for (; (u6 != pi1[4] && (stk_14 < (int)u4)); stk_14 = stk_14 + 1) {
    u5 = u2;
    if (-1 < (int)u6) {
      u5 = u6 - 1;
    }
    u6 = u5;
  }
  if (u6 != pi1[5]) {
    do {
      text = *(char **)(*pi1 + u6 * 4);
      if (text == (char *)0x0) {
        return;
      }
      V_FontDraw(text,font,arg2 + *arg1,arg3 + arg1[1],arg4);
      arg3 = arg3 + font[6] + font[3];
      u6 = u6 + 1 & (pi1[3] <= (int)(u6 + 1)) - 1;
    } while (u6 != pi1[5]);
  }
  if (**(char **)(*pi1 + u6 * 4) != '\0') {
    V_FontDraw(*(char **)(*pi1 + u6 * 4),font,arg2 + *arg1,arg3 + arg1[1],
               arg4);
  }
  return;
}

/* EB_GUIPutSurface @ 0x08081ab0, 1 bytes
 *
 * Empty in this build.
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIPutSurface(void)

{
  return;
}

/* EB_GUIRaiseWindow @ 0x08081ac0, 19 bytes
 *
 * Brings a window to the front.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: MoveNodeToEnd
 * Called by: EB_GUIUpdate
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
uint32_t EB_GUIRaiseWindow(int *arg1)

{
  MoveNodeToEnd(arg1);
  return 0;
}

/* EB_GUIPutSprite @ 0x08081ae0, 107 bytes
 *
 * Draws a sprite into a window's buffer. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   sprites      int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: V_SetBuf, W_PutSprite8to16, W_PutSprite
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIPutSprite(int arg1,int *sprites,int arg3,int arg4,int arg5)

{
  int *pi1;
  
  pi1 = V_Current;
  V_SetBuf(*(int **)(arg1 + 0x28),0);
  if (arg5 == 0) {
    W_PutSprite8to16(sprites,0,arg3,arg4);
  }
  else {
    W_PutSprite(sprites,0,arg3,arg4);
  }
  V_SetBuf(pi1,0);
  return;
}

/* EB_GUIClearWindow @ 0x08081b50, 52 bytes
 *
 * Clears a window's buffer. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: V_SetBuf, W_Cls
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIClearWindow(int arg1)

{
  int *pi1;
  
  pi1 = V_Current;
  V_SetBuf(*(int **)(arg1 + 0x28),0);
  W_Cls(*(uint32_t *)(arg1 + 0x1c));
  V_SetBuf(pi1,0);
  return;
}

/* EB_GUIDrawWindow @ 0x08081b90, 562 bytes
 *
 * Draws one window: frame, title bar with its position "(x, y)", translucent
 * background and clipboard text.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: G_MakeColor, W_BoxFill, W_BoxTransAdd16, V_FontWrite,
 *        W_BoxFillTransAdd16_B50, W_Define, EB_GUIDrawClipboard, V_SetBuf
 * Called by: EB_DrawWindows
 * Messages:
 *   "(%d, %d)"
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIDrawWindow(uint32_t *arg1)

{
  uint32_t u1;
  uint32_t u2;
  int *pi3;
  int i4;
  uint32_t u5;
  uint32_t u6;
  uint32_t u7;
  uint32_t u8;
  uint32_t stale_EDX;
  uint32_t u9;
  
  u5 = G_MakeColor(0xff,0xff,0xff);
  u6 = G_MakeColor(0xff,0,0);
  u7 = G_MakeColor(0x3a,0x6e,0xa5);
  u8 = G_MakeColor(0x80,0x80,0x80);
  u1 = *arg1;
  if (arg1 == (uint32_t *)has_focus) {
    u9 = arg1[1];
    u2 = arg1[2];
    u8 = u7;
  }
  else {
    u9 = arg1[1];
    u2 = arg1[2];
  }
  W_BoxFill(u1 - 1 & 0xffffffffU - ((int)u1 >> 0x1f),arg1[1] - 10,u1 + u2 + 1,u9,
            u8);
  W_BoxTransAdd16(*(int *)(*(int *)(arg1[0xe] + 8) + 4) - 1,
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 8),
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 0xc),
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 0x10),u5);
  W_BoxTransAdd16(*(int *)(*(int *)(arg1[0xe] + 8) + 0x18) - 1,
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 0x1c),
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 0x20),
                  *(uint32_t *)(*(int *)(arg1[0xe] + 8) + 0x24),u6);
  V_FontWrite(GUI_globalfont,*arg1 + 10,arg1[1] - 3,u5,"%s",arg1[9]);
  i4 = V_CurrentIdx;
  pi3 = V_Current;
  if ((arg1[6] & 1) == 0) {
    W_BoxFill(*arg1,arg1[1],arg1[2] + *arg1 + -1,arg1[3] + arg1[1] + -1,arg1[7]
             );
  }
  else {
    W_BoxFillTransAdd16_B50
              (*arg1,arg1[1],arg1[2] + *arg1,arg1[3] + arg1[1],arg1[7]);
  }
  W_Define(*arg1,arg1[1],arg1[2] + *arg1,arg1[3] + arg1[1]);
  EB_GUIDrawClipboard((int *)arg1,10,10,u5);
  if ((GUI_state == 1) && ((uint32_t *)has_focus == arg1)) {
    V_FontWrite(GUI_globalfont,((int)arg1[2] >> 1) + *arg1 + GUI_globalfont[2] * -6,
                ((int)arg1[3] >> 1) + arg1[1],u5,"(%d, %d)",*arg1,arg1[1],
                stale_EDX);
  }
  V_SetBuf(pi3,i4);
  return;
}

/* EB_DrawWindows @ 0x08081dd0, 42 bytes
 *
 * Draws every window in list order (back to front).
 *
 * Calls: EB_GUIDrawWindow
 * Called by: EB_GUIUpdate
 *
 * Elecbyte file: src/lib/gui-lib.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void EB_DrawWindows(void)

{
  int i1;
  uint32_t saved_EBX;
  
  for (i1 = EB_ListHead[1]; i1 != 0; i1 = *(int *)(i1 + 4)) {
    EB_GUIDrawWindow(*(uint32_t **)(i1 + 8));
  }
  return;
}

/* EB_GUIMoveWindow @ 0x08081e00, 86 bytes
 *
 * Moves a window by (dx, dy).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Called by: EB_GUIUpdate
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
void EB_GUIMoveWindow(int *arg1,int arg2,int arg3)

{
  int i1;
  
  arg1[1] = arg3;
  *arg1 = arg2;
  i1 = *(int *)(arg1[0xe] + 8);
  *(int *)(i1 + 4) = arg2;
  *(int *)(i1 + 8) = arg1[1];
  *(int *)(i1 + 0xc) = arg1[2] + *arg1;
  *(int *)(i1 + 0x10) = arg1[3] + arg1[1];
  *(int *)(i1 + 0x18) = *arg1;
  *(int *)(i1 + 0x1c) = arg1[1] + -10;
  *(int *)(i1 + 0x20) = arg1[2] + *arg1;
  *(int *)(i1 + 0x24) = arg1[1];
  return;
}

/* DetermineFocus @ 0x08081e60, 79 bytes
 *
 * Returns the topmost window under the mouse position.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *
 * Calls: ClsnMixDetectRectIndiv
 * Called by: EB_GUIUpdate
 *
 * Elecbyte file: src/lib/gui-lib.c
 */
int * DetermineFocus(int arg1,int *arg2)

{
  int i1;
  int *pi2;
  
  pi2 = EB_ListTail;
  if (EB_ListTail != EB_ListHead) {
    do {
      i1 = ClsnMixDetectRectIndiv(arg1,*(int *)(pi2[2] + 0x38),0,0);
      *arg2 = i1;
      if (-1 < i1) {
        return pi2;
      }
      pi2 = (int *)*pi2;
    } while (pi2 != EB_ListHead);
  }
  return EB_ListHead;
}

/* EB_GUIUpdate @ 0x08081eb0, 306 bytes
 *
 * Debug GUI frame update: polls the mouse, focuses and raises the window
 * under the cursor on click, drags it while the button is held, and draws
 * all windows. Called by the debug display.
 *
 * Calls: DetermineFocus, EB_GUIRaiseWindow, EB_GUIMoveWindow,
 *        EB_DrawWindows
 * C library: mouse_needs_poll, poll_mouse
 * Called by: ShowDebugInfo
 *
 * Elecbyte file: src/lib/gui-lib.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 6
 *       variables), because their address is taken.
 */
void EB_GUIUpdate(void)

{
  int *pi1;
  int i2;
  uint32_t u3;
  int *pi4;
  int i5;
  int *saved_ESI;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_40 (*(uint32_t *)(frame + 0x0))
#define stk_3c (*(uint8_t (*)[4])(frame + 0x4))
#define stk_38 (*(int *)(frame + 0x8))
#define stk_34 (*(int *)(frame + 0xc))
#define stk_30 (*(int *)(frame + 0x10))
#define stk_2c (*(int *)(frame + 0x14))
  
  i5 = mouse_needs_poll();
  if (i5 != 0) {
    poll_mouse();
  }
  u3 = mouse_b;
  i2 = mouse_y;
  i5 = mouse_x;
  stk_30 = mouse_x;
  stk_38 = mouse_x;
  stk_2c = mouse_y;
  stk_34 = mouse_y;
  if (GUI_state == 0) {
    saved_ESI = (int *)DetermineFocus((int)stk_3c,(int *)&stk_40);
    if (saved_ESI != EB_ListHead) {
      has_focus = (int *)saved_ESI[2];
    }
  }
  if (((u3 & 1) != 0) && (GUI_state == 0)) {
    GUI_state = 2;
  }
  if (u3 == 0) {
    GUI_state = 0;
  }
  if (((GUI_state == 2) && (has_focus != GUI_root)) && (stk_40 < 2)) {
    GUI_state = 3;
    EB_GUIRaiseWindow(saved_ESI);
  }
  pi4 = has_focus;
  if ((GUI_state == 3) && (saved_ESI != EB_ListHead)) {
    pi1 = has_focus + 1;
    has_focus[4] = i5 - *has_focus;
    pi4[5] = i2 - *pi1;
    GUI_state = 1;
  }
  if ((GUI_state == 1) && (has_focus != GUI_root)) {
    EB_GUIMoveWindow(has_focus,i5 - has_focus[4],i2 - has_focus[5]);
  }
  EB_DrawWindows();
  return;
}
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c

