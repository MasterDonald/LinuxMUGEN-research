/*
 * time-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0807af40-0x0807b1f1, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int CalculatedFPS __asm__("D_08287a14"); /* file-static 0x08287a14 */
extern int oldtime_0 __asm__("D_08287a18"); /* file-static 0x08287a18 */
extern int CurCall_1 __asm__("D_08287a1c"); /* file-static 0x08287a1c */

/* TimerHandler @ 0x0807af40, 79 bytes */
void TimerHandler(void)

{
  Ticks = Ticks + 1;
  TicksUpdate = 1;
  if ((0 < SyncRate) && (SyncLast = SyncLast + 0x10000, SyncRate <= SyncLast)) {
    SyncLast = SyncLast - SyncRate;
    SyncCur = SyncCur + 1;
  }
  return;
}

/* TimerInit @ 0x0807af90, 107 bytes
 * FIXUP: function addresses written as literals replaced by symbol references */
bool TimerInit(int param_1)

{
  int iVar1;
  
  Ticks = 0;
  TicksPerSecond = param_1;
  TicksUpdate = 0;
  FPSUpdateTicks = 10;
  SyncRate = 0;
  SyncLast = 0;
  install_timer();
  iVar1 = install_int_ex((int)TimerHandler,(int)(0x1234dd / (longlong)param_1));
  return iVar1 == 0;
}

/* TimerDeInit @ 0x0807b000, 21 bytes
 * FIXUP: function addresses written as literals replaced by symbol references */
void TimerDeInit(void)

{
  remove_int((int)TimerHandler);
  remove_timer();
  return;
}

/* TimerChangeSpeed @ 0x0807b020, 32 bytes
 * FIXUP: function addresses written as literals replaced by symbol references */
void TimerChangeSpeed(int param_1)

{
  install_int_ex((int)TimerHandler,(int)(0x1234dd / (longlong)param_1));
  return;
}

/* TimerDelay @ 0x0807b040, 5 bytes
 * REVIEW: calls-missing-in-pid:rest_callback */
undefined4 TimerDelay(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = rest(param_1);
  return uVar1;
}

/* TimerSetTicks @ 0x0807b050, 10 bytes */
void TimerSetTicks(int param_1)

{
  Ticks = param_1;
  return;
}

/* TimerGetFPS @ 0x0807b060, 97 bytes
 * FIXUP: 1 exact-text site patches
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
longdouble TimerGetFPS(void)

{
  int iVar1;
  
  if ((FPSUpdateTicks <= CurCall_1) && (Ticks != oldtime_0)) {
    iVar1 = Ticks - oldtime_0;
    oldtime_0 = Ticks;
    CurCall_1 = 0;
    CalculatedFPS = GHIDRA_F2I(int, (((float)TicksPerSecond * (float)FPSUpdateTicks) / (float10)iVar1));
  }
  CurCall_1 = CurCall_1 + 1;
  return (longdouble)GHIDRA_I2F(CalculatedFPS);
}

/* TimerSetFPSDelay @ 0x0807b0d0, 24 bytes */
void TimerSetFPSDelay(int param_1)

{
  if (-1 < param_1) {
    FPSUpdateTicks = param_1;
  }
  CalculatedFPS = -0x40800000;
  return;
}

/* TimerSyncReset @ 0x0807b0f0, 21 bytes */
void TimerSyncReset(void)

{
  SyncCur = 0;
  SyncLast = 0;
  return;
}

/* TimerSetSyncFPS @ 0x0807b110, 60 bytes */
void TimerSetSyncFPS(int param_1)

{
  if (0 < param_1) {
    TimerFPS = param_1;
    SyncRate = (TicksPerSecond << 0x10) / param_1;
    InSync = 1;
    TimerSyncReset();
    return;
  }
  return;
}

/* TimerGetSync @ 0x0807b150, 14 bytes */
bool TimerGetSync(void)

{
  return InSync == 0;
}

/* TimerWaitSync @ 0x0807b160, 56 bytes */
void TimerWaitSync(void)

{
  do {
  } while (SyncCur < 1);
  if (SyncCur == 1) {
    SyncCur = 0;
    InSync = 1;
    return;
  }
  SyncCur = SyncCur + -1;
  InSync = 0;
  return;
}

/* TimerIsSync @ 0x0807b1a0, 75 bytes */
undefined4 TimerIsSync(void)

{
  bool bVar1;
  
  if (SyncCur < 1) {
    return 0;
  }
  bVar1 = SyncCur == 1;
  SyncCur = SyncCur + -1;
  InSync = (int)bVar1;
  return 1;
}

/* TimerSkipSync @ 0x0807b1f0, 1 bytes */
void TimerSkipSync(void)

{
  return;
}

