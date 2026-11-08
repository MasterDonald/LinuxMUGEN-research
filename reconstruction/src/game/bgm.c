/*
 * bgm.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08085240-0x08085c27, 17 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* BGMParse @ 0x08085240, 103 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
bool BGMParse(int param_1,undefined1 *param_2,char *param_3)

{
  int iVar1;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[80])(ghidra_frame + 0x4))
  
  *(undefined4 *)(param_2 + 0x1000) = 1;
  *param_2 = 0;
  iVar1 = TPScanf(param_1,param_3,"%s",param_2);
  if (iVar1 == 1) {
    sprintf(local_5c,"%s.loop",param_3,0);
    TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 0x1000));
  }
  return iVar1 == 1;
}
#undef local_5c

/* BGMStart @ 0x080852b0, 259 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
void BGMStart(int *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  long lVar3;
  int iVar4;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(uint *)(ghidra_frame + 0x0))
#define local_c (*(uint *)(ghidra_frame + 0x4))
  
  if (g[0x6ef3] != 0) {
    iVar4 = *param_1;
    if (iVar4 == 1) {
      SndMidiPlayLoop((int *)param_1[1],0,0xffffffff);
      iVar4 = *param_1;
    }
    if (iVar4 == 2) {
      MODPlay((int *)param_1[2],-1);
      iVar4 = *param_1;
    }
    if (iVar4 == 4) {
      local_10 = 1;
      local_c = 1;
      uVar2 = param_1[3];
      if ((uVar2 == 0) &&
         (bVar1 = CDAGetTrackRange(&local_10,&local_c), GHIDRA_ZEXT8(bVar1) != 0)) {
        while ((uVar2 = CDATrackIsAudio((char)local_10), uVar2 == 0 &&
               ((int)local_10 < (int)local_c))) {
          local_10 = local_10 + 1;
        }
        if ((int)local_10 < (int)local_c) {
          lVar3 = random();
          uVar2 = local_10 + lVar3 % (int)((local_c - local_10) + 1);
        }
        else {
          uVar2 = 1;
        }
      }
      iVar4 = CDAPlay(uVar2,1);
      if (iVar4 == 0) {
        return;
      }
    }
    param_1[7] = 1;
  }
  return;
}
#undef local_10
#undef local_c

/* BGMPause @ 0x080853c0, 119 bytes */
void BGMPause(int *param_1)

{
  int iVar1;
  
  if ((g[0x6ef3] != 0) && (iVar1 = BGMGetPause((int)param_1), iVar1 == 0)) {
    iVar1 = *param_1;
    if (iVar1 == 2) {
      MODPause();
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        midi_pause();
      }
    }
    else if (iVar1 == 3) {
      MP3SetVol(0);
      MP3Pause();
    }
    else if (iVar1 == 4) {
      CDAPause();
    }
    param_1[4] = 1;
  }
  return;
}

/* BGMSysPause @ 0x08085440, 119 bytes */
void BGMSysPause(int *param_1)

{
  int iVar1;
  
  if ((g[0x6ef3] != 0) && (iVar1 = BGMGetPause((int)param_1), iVar1 == 0)) {
    iVar1 = *param_1;
    if (iVar1 == 2) {
      MODPause();
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        midi_pause();
      }
    }
    else if (iVar1 == 3) {
      MP3SetVol(0);
      MP3Pause();
    }
    else if (iVar1 == 4) {
      CDAPause();
    }
    param_1[5] = 1;
  }
  return;
}

/* BGMGetPause @ 0x080854c0, 26 bytes */
undefined4 BGMGetPause(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((*(int *)(param_1 + 0x10) != 0) || (*(int *)(param_1 + 0x14) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}

/* BGMResume @ 0x080854e0, 144 bytes */
undefined4 BGMResume(int *param_1)

{
  int iVar1;
  undefined4 in_EDX;
  
  if (((g[0x6ef3] != 0) && (param_1[4] != 0)) && (param_1[5] == 0)) {
    iVar1 = *param_1;
    if (iVar1 == 2) {
      MODResume();
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        midi_resume();
      }
    }
    else if (iVar1 == 3) {
      MP3Resume();
      iVar1 = SndCorrectVolOff(param_1[6]);
      MP3SetVol(iVar1 + g[0x6ef8]);
    }
    else if (iVar1 == 4) {
      CDAResume();
    }
    param_1[4] = 0;
  }
  return in_EDX;
}

/* BGMSysResume @ 0x08085570, 144 bytes */
void BGMSysResume(int *param_1)

{
  int iVar1;
  
  if (((g[0x6ef3] != 0) && (param_1[4] == 0)) && (param_1[5] != 0)) {
    iVar1 = *param_1;
    if (iVar1 == 2) {
      MODResume();
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        midi_resume();
      }
    }
    else if (iVar1 == 3) {
      MP3Resume();
      iVar1 = SndCorrectVolOff(param_1[6]);
      MP3SetVol(iVar1 + g[0x6ef8]);
    }
    else if (iVar1 == 4) {
      CDAResume();
    }
    param_1[5] = 0;
  }
  return;
}

/* BGMGetVolume @ 0x08085600, 86 bytes */
int BGMGetVolume(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 2) {
    iVar1 = MODGetVol();
    return iVar1;
  }
  if (iVar1 < 3) {
    if (iVar1 == 1) {
      return g[0x6ef7];
    }
  }
  else {
    if (iVar1 == 3) {
      iVar1 = MP3GetVol();
      return iVar1;
    }
    if (iVar1 == 4) {
      iVar1 = CDAGetVol();
      return iVar1;
    }
  }
  return 0;
}

/* BGMSetVolume @ 0x08085660, 116 bytes */
void BGMSetVolume(int *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 2) {
    MODSetVol(param_2);
    return;
  }
  if (iVar1 < 3) {
    if (iVar1 == 1) {
      g[0x6ef7] = param_2;
    }
  }
  else {
    if (iVar1 == 3) {
      MP3SetVol(param_2);
      return;
    }
    if (iVar1 == 4) {
      CDASetVol(param_2);
      return;
    }
  }
  return;
}

/* BGMPoll @ 0x080856e0, 116 bytes */
void BGMPoll(int *param_1)

{
  if (g[0x6ef3] != 0) {
    if (g[0x756e] != 0) {
      if ((g[0x74e7] == 0) && (param_1[5] == 0)) {
        BGMSysPause(param_1);
      }
      else if ((g[0x74e7] != 0) && (param_1[5] != 0)) {
        BGMSysResume(param_1);
      }
    }
    BGMPollIgnoreDefocus(param_1);
    return;
  }
  return;
}

/* BGMPollIgnoreDefocus @ 0x08085760, 148 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void BGMPollIgnoreDefocus(int *param_1)

{
  int iVar1;
  undefined4 unaff_EBX;
  
  if (g[0x6ef3] != 0) {
    if (*param_1 == 3) {
      MP3Poll();
      iVar1 = BGMGetPause((int)param_1);
      if ((iVar1 != 0) && (iVar1 = MP3GetVol(), 0 < iVar1)) {
        iVar1 = MP3GetVol();
        MP3SetVol((iVar1 * 10) / 0xb + -4);
      }
    }
    else if ((*param_1 == 4) && (g[0x7304] % 6 == 0)) {
      CDAPoll();
    }
  }
  return;
}

/* BGMCheckExtension @ 0x08085800, 5 bytes
 * REVIEW: calls-missing-in-pid:_alemu_stricmp,strlen */
undefined4 BGMCheckExtension(char *param_1)

{
  undefined4 uVar1;
  
  uVar1 = CheckExtension(param_1);
  return uVar1;
}

/* BGMLoad @ 0x08085810, 584 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 BGMLoad(int *param_1,byte *param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint *puVar3;
  undefined3 extraout_var;
  uint uVar4;
  int *piVar5;
  
  if ((g[0x6ef3] != 0) && (g[0x755f] == 0)) {
    BGMFree(param_1);
    *param_1 = 0;
    param_1[9] = param_3;
    if ((*param_2 != 0) && (g[0x6ef3] != 0)) {
      iVar2 = BGMCheckExtension((char *)param_2);
      if (iVar2 == 6) {
        if (g[0x7561] == 0) {
          return 1;
        }
        puVar3 = SndMidiReadFile(param_2);
        param_1[1] = (int)puVar3;
        if (puVar3 == (uint *)0x0) {
          return 1;
        }
        *param_1 = 1;
      }
      else if (iVar2 < 7) {
        if (iVar2 != 5) {
          return 1;
        }
        if (g[0x7560] == 0) {
          return 1;
        }
        iVar2 = SndCorrectVolOff(param_1[6]);
        MP3SetVol(iVar2 + g[0x6ef8]);
        iVar2 = MP3LoadAndPlay((char *)param_2,param_3);
        if (iVar2 == 0) {
          return 1;
        }
        *param_1 = 3;
      }
      else {
        if (iVar2 != 7) {
          if (iVar2 != 8) {
            return 1;
          }
          if (g[0x7563] == 0) {
            return 1;
          }
          if ((char)g[0x7564] == '\0') {
            piVar5 = (int *)0x0;
          }
          else {
            piVar5 = g + 0x7564;
          }
          CDAInit((char *)piVar5);
          uVar4 = __strtol_internal(param_2,(undefined4 *)0x0,10,0);
          if ((int)uVar4 < 0) {
            return 1;
          }
          if (g[0x6ef6] != -1) {
            CDASetVol(g[0x6ef6] + param_1[6]);
          }
          *param_1 = 4;
          param_1[3] = uVar4;
          return 1;
        }
        if (g[0x7562] == 0) {
          return 1;
        }
        bVar1 = MODInit(g[0x755e]);
        if (GHIDRA_ZEXT8(bVar1) == 0) {
          ClipboardAppend((int *)g[0x81d1],"Warning: could not allocate mod voices\n",param_1,
                          param_1);
          return 1;
        }
        param_1[2] = 0;
        iVar2 = MODLoad(param_2);
        param_1[2] = iVar2;
        if (iVar2 == 0) {
          return 1;
        }
        *param_1 = 2;
        iVar2 = SndCorrectVolOff(param_1[6]);
        MODSetVol(iVar2 + g[0x6ef9]);
      }
      strcpy((char *)(param_1 + 10),(char *)param_2);
    }
  }
  return 1;
}

/* BGMLoadAndStart @ 0x08085a60, 221 bytes */
undefined4 BGMLoadAndStart(int *param_1,byte *param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  bVar1 = false;
  if ((g[0x6ef3] != 0) && (g[0x755f] == 0)) {
    if ((param_2 == (byte *)0x0) || (*param_2 == 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      BGMFree(param_1);
    }
    else if ((((param_1[7] == 0) ||
              (iVar2 = _alemu_stricmp((char *)(param_1 + 10),(char *)param_2), iVar2 != 0)) ||
             (param_1[9] == 0)) || (param_3 == 0)) {
      GameSetVol(g[0x6ef5],g[0x6ef7]);
      param_1[6] = param_4;
      iVar2 = BGMLoad(param_1,param_2,param_3);
      if (iVar2 == 0) {
        sprintf((char *)(g + 0x81d2),"Error loading BGM: %s",param_2,extraout_ECX);
        return 0;
      }
      BGMStart(param_1);
    }
  }
  return 1;
}

/* BGMFree @ 0x08085b40, 152 bytes */
int * BGMFree(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = param_1[6];
  piVar2 = g;
  if (g[0x6ef3] != 0) {
    iVar3 = *param_1;
    if (iVar3 == 2) {
      MODStop();
      MODUnload((undefined4 *)param_1[2]);
      MODDeInit();
    }
    else if (iVar3 < 3) {
      if (iVar3 == 1) {
        SndMidiFree((void *)param_1[1]);
      }
    }
    else if (iVar3 == 3) {
      MP3Unload();
    }
    else if (iVar3 == 4) {
      CDAStop();
    }
    piVar2 = (int *)0x0;
    piVar4 = param_1;
    for (iVar3 = 0x40a; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    *param_1 = 0;
    param_1[6] = iVar1;
    param_1[7] = 0;
  }
  return piVar2;
}

/* BGMPlayForScene @ 0x08085be0, 35 bytes */
void BGMPlayForScene(byte *param_1,int param_2)

{
  BGMLoadAndStart(g + 0x6efa,param_1,param_2,0);
  return;
}

/* BGMStopForScene @ 0x08085c10, 23 bytes */
void BGMStopForScene(void)

{
  BGMFree(g + 0x6efa);
  return;
}

