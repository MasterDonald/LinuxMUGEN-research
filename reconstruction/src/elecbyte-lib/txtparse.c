/*
 * txtparse.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0807b200-0x0807ce3b, 41 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* TPFree @ 0x0807b200, 233 bytes */
undefined4 TPFree(undefined4 *param_1)

{
  undefined4 *__ptr;
  void *__ptr_00;
  undefined4 in_EAX;
  int iVar1;
  undefined4 extraout_EAX;
  int iVar2;
  int iVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    __ptr = (undefined4 *)param_1[0xc];
    iVar1 = *(int *)*param_1;
    if (iVar1 == 1) {
      if ((void *)param_1[1] != (void *)0x0) {
        free((void *)param_1[1]);
      }
      if ((void *)param_1[8] != (void *)0x0) {
        free((void *)param_1[8]);
      }
      if ((void *)param_1[10] != (void *)0x0) {
        free((void *)param_1[10]);
      }
      if (__ptr != (undefined4 *)0x0) {
        if ((void *)*__ptr != (void *)0x0) {
          free((void *)*__ptr);
        }
        iVar1 = __ptr[1];
        if (iVar1 != 0) {
          iVar3 = 0;
          iVar2 = __ptr[2];
          if (0 < iVar2) {
            while( true ) {
              __ptr_00 = *(void **)(iVar1 + iVar3 * 4);
              if (__ptr_00 != (void *)0x0) {
                free(__ptr_00);
                iVar2 = __ptr[2];
              }
              iVar3 = iVar3 + 1;
              if (iVar2 <= iVar3) break;
              iVar1 = __ptr[1];
            }
          }
          free((void *)__ptr[1]);
        }
        free(__ptr);
      }
      free((void *)*param_1);
    }
    else {
      *(int *)*param_1 = iVar1 + -1;
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_EAX;
}

/* TPReadMFPtr @ 0x0807b2f0, 1161 bytes
 * REVIEW: type-prop */
/* WARNING: Type propagation algorithm not settling */

undefined4 * TPReadMFPtr(int *param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  char *pcVar6;
  void *pvVar7;
  int iVar8;
  size_t sVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint *puVar13;
  uint *puVar14;
  size_t local_144;
  char *local_140;
  int local_13c;
  int local_138;
  int local_134;
  int *extra;
  char line [256];
  
  local_138 = 0x100;
  local_13c = 0x40;
  MFftell(param_1);
  puVar3 = (undefined4 *)ecalloc(1,0x34);
  if (puVar3 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar4 = (undefined4 *)ecalloc(1,4);
  *puVar3 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *puVar4 = 1;
  if (param_2 == 1) {
    extra = (int *)ecalloc(1,0x10);
    puVar3[0xc] = extra;
    if (extra == (int *)0x0) {
      return (undefined4 *)0x0;
    }
    extra[3] = 0x100;
    iVar5 = ecalloc(1,0x400);
    extra[1] = iVar5;
    if (iVar5 == 0) goto LAB_0807b414;
  }
  iVar5 = param_1[4];
  iVar10 = param_1[3];
  puVar3[2] = iVar5 - iVar10;
  iVar5 = ecalloc(1,(iVar5 - iVar10) + 0x10);
  puVar3[1] = iVar5;
  if (iVar5 != 0) {
    iVar5 = ecalloc(0x101,4);
    puVar3[8] = iVar5;
    if (iVar5 != 0) {
      iVar5 = ecalloc(0x41,4);
      puVar3[10] = iVar5;
      if (iVar5 != 0) {
        if (param_2 == 1) {
          iVar5 = ecalloc(0x101,4);
          *extra = iVar5;
          if (iVar5 == 0) goto LAB_0807b414;
        }
        local_140 = (char *)puVar3[1];
        pcVar6 = MFfgets(line,0x100,param_1);
        if (pcVar6 != (char *)0x0) {
          local_144 = 0x800;
          do {
            if (param_2 == 1) {
              if (extra[3] <= extra[2] + 1) {
                pvVar7 = realloc((void *)extra[1],extra[3] * 4 + 0x400);
                if (pvVar7 == (void *)0x0) goto LAB_0807b414;
                extra[1] = (int)pvVar7;
                extra[3] = extra[3] + 0x100;
              }
              iVar5 = 0;
              cVar1 = line[0];
              while ((cVar1 != '\0' && (cVar1 != '\n'))) {
                cVar1 = line[iVar5 + 1];
                iVar5 = iVar5 + 1;
              }
              pvVar7 = malloc(iVar5 + 1);
              *(void **)(extra[1] + extra[2] * 4) = pvVar7;
              if (pvVar7 == (void *)0x0) goto LAB_0807b414;
              iVar10 = 0;
              if (0 < iVar5) {
                do {
                  *(char *)(iVar10 + (int)pvVar7) = line[iVar10];
                  iVar10 = iVar10 + 1;
                } while (iVar10 < iVar5);
              }
              *(undefined1 *)(iVar10 + (int)pvVar7) = 0;
              extra[2] = extra[2] + 1;
            }
            if (line[0] != '\0') {
              iVar5 = 0;
              if (line[0] == ';') {
                line[0] = '\0';
              }
              else {
                do {
                  iVar10 = iVar5;
                  if (line[iVar10 + 1] == '\0') goto LAB_0807b54a;
                  iVar5 = iVar10 + 1;
                } while (line[iVar10 + 1] != ';');
                line[iVar10 + 1] = '\0';
              }
            }
LAB_0807b54a:
            puVar14 = (uint *)line;
            do {
              puVar13 = puVar14;
              puVar14 = puVar13 + 1;
              uVar11 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar12 = uVar11 & 0x80808080;
            } while (uVar12 == 0);
            if ((uVar11 & 0x8080) == 0) {
              uVar12 = uVar12 >> 0x10;
              puVar14 = (uint *)((int)puVar13 + 6);
            }
            iVar5 = (int)puVar14 + ((-3 - (uint)CARRY1((byte)uVar12,(byte)uVar12)) - (int)line);
            if ((line[0] != '\0') && (line[iVar5 + -1] == '\n')) {
              line[iVar5 + -1] = '\0';
              iVar5 = iVar5 + -1;
            }
            iVar10 = iVar5;
            if (line[0] != '\0') {
              while ((-1 < iVar10 + -1 && (iVar8 = TPisspace(line[iVar10 + -1]), iVar8 != 0))) {
                line[iVar10 + -1] = '\0';
                iVar5 = iVar5 + -1;
                iVar10 = iVar10 + -1;
              }
            }
            iVar10 = 0;
            local_134 = 0;
            while ((line[iVar10] != '\0' && (iVar8 = TPisspace(line[iVar10]), iVar8 != 0))) {
              local_134 = local_134 + 1;
              iVar10 = iVar10 + 1;
            }
            if (line[local_134] != '\0') {
              strcpy(local_140,line + local_134);
              if (param_2 == 1) {
                *(int *)(*extra + puVar3[9] * 4) = extra[2] + -1;
              }
              iVar10 = puVar3[9];
              *(char **)(puVar3[8] + iVar10 * 4) = local_140;
              iVar10 = iVar10 + 1;
              puVar3[9] = iVar10;
              if (local_138 <= iVar10) {
                pvVar7 = realloc((void *)puVar3[8],local_144);
                piVar2 = extra;
                if (pvVar7 == (void *)0x0) goto LAB_0807b414;
                puVar3[8] = pvVar7;
                if (param_2 == 1) {
                  pvVar7 = realloc((void *)*extra,local_144);
                  if (pvVar7 == (void *)0x0) goto LAB_0807b414;
                  *piVar2 = (int)pvVar7;
                }
                local_144 = local_144 + 0x400;
                local_138 = local_138 + 0x100;
              }
              if ((line[local_134] == '[') && (line[iVar5 + -1] == ']')) {
                *(int *)(puVar3[10] + puVar3[0xb] * 4) = puVar3[9] + -1;
                iVar5 = puVar3[0xb];
                puVar3[0xb] = iVar5 + 1;
                if (local_13c <= iVar5 + 1) {
                  pvVar7 = realloc((void *)puVar3[10],local_13c * 4 + 0x100);
                  if (pvVar7 == (void *)0x0) goto LAB_0807b414;
                  puVar3[10] = pvVar7;
                  local_13c = local_13c + 0x40;
                }
              }
              sVar9 = strlen(line + local_134);
              local_140 = local_140 + sVar9 + 1;
            }
            pcVar6 = MFfgets(line,0x100,param_1);
          } while (pcVar6 != (char *)0x0);
        }
        builtin_strncpy(local_140,"[TPEnd]",8);
        return puVar3;
      }
    }
  }
LAB_0807b414:
  TPFree(puVar3);
  return (undefined4 *)0x0;
}

/* TPReadMF @ 0x0807b780, 61 bytes */
int * TPReadMF(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  if (iVar1 == 1) {
    piVar2 = TPReadFilePtr((FILE *)param_1[1],param_2);
    return piVar2;
  }
  if ((0 < iVar1) && (iVar1 < 4)) {
    piVar2 = TPReadMFPtr(param_1,param_2);
    return piVar2;
  }
  return (int *)0x0;
}

/* TPReadFile @ 0x0807b7c0, 62 bytes */
void * TPReadFile(char *param_1)

{
  FILE *stream;
  int *piVar1;
  
  stream = fopen(param_1,"rt");
  if (stream == (FILE *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = TPReadFilePtr(stream,0);
    fclose(stream);
  }
  return piVar1;
}

/* TPClone @ 0x0807b800, 55 bytes */
undefined4 * TPClone(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)ecalloc(1,0x34);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar3 = puVar1;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *param_1;
      param_1 = param_1 + 1;
      puVar3 = puVar3 + 1;
    }
    *(int *)*puVar1 = *(int *)*puVar1 + 1;
  }
  return puVar1;
}

/* TPReadFileForWrite @ 0x0807b840, 62 bytes */
void * TPReadFileForWrite(char *param_1)

{
  FILE *stream;
  int *piVar1;
  
  stream = fopen(param_1,"rt");
  if (stream == (FILE *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = TPReadFilePtr(stream,1);
    fclose(stream);
  }
  return piVar1;
}

/* TPReadFilePtr @ 0x0807b880, 1161 bytes
 * REVIEW: type-prop */
/* WARNING: Type propagation algorithm not settling */

int * TPReadFilePtr(FILE *param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  long lVar6;
  char *pcVar7;
  void *pvVar8;
  int iVar9;
  size_t sVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  uint *puVar15;
  size_t local_144;
  char *local_140;
  int local_13c;
  int local_138;
  int local_134;
  int *extra;
  char line [256];
  
  local_138 = 0x100;
  local_13c = 0x40;
  ftell(param_1);
  piVar3 = (int *)ecalloc(1,0x34);
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  puVar4 = (undefined4 *)ecalloc(1,4);
  *piVar3 = (int)puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    return (int *)0x0;
  }
  *puVar4 = 1;
  if (param_2 == 1) {
    extra = (int *)ecalloc(1,0x10);
    piVar3[0xc] = (int)extra;
    if (extra == (int *)0x0) {
      return (int *)0x0;
    }
    extra[3] = 0x100;
    iVar5 = ecalloc(1,0x400);
    extra[1] = iVar5;
    if (iVar5 == 0) goto LAB_0807b9a5;
  }
  lVar6 = ffilelength(param_1);
  piVar3[2] = lVar6;
  iVar5 = ecalloc(1,lVar6 + 0x10);
  piVar3[1] = iVar5;
  if (iVar5 != 0) {
    iVar5 = ecalloc(0x101,4);
    piVar3[8] = iVar5;
    if (iVar5 != 0) {
      iVar5 = ecalloc(0x41,4);
      piVar3[10] = iVar5;
      if (iVar5 != 0) {
        if (param_2 == 1) {
          iVar5 = ecalloc(0x101,4);
          *extra = iVar5;
          if (iVar5 == 0) goto LAB_0807b9a5;
        }
        local_140 = (char *)piVar3[1];
        pcVar7 = fgets(line,0x100,param_1);
        if (pcVar7 != (char *)0x0) {
          local_144 = 0x800;
          do {
            if (param_2 == 1) {
              if (extra[3] <= extra[2] + 1) {
                pvVar8 = realloc((void *)extra[1],extra[3] * 4 + 0x400);
                if (pvVar8 == (void *)0x0) goto LAB_0807b9a5;
                extra[1] = (int)pvVar8;
                extra[3] = extra[3] + 0x100;
              }
              iVar5 = 0;
              cVar1 = line[0];
              while ((cVar1 != '\0' && (cVar1 != '\n'))) {
                cVar1 = line[iVar5 + 1];
                iVar5 = iVar5 + 1;
              }
              pvVar8 = malloc(iVar5 + 1);
              *(void **)(extra[1] + extra[2] * 4) = pvVar8;
              if (pvVar8 == (void *)0x0) goto LAB_0807b9a5;
              iVar11 = 0;
              if (0 < iVar5) {
                do {
                  *(char *)(iVar11 + (int)pvVar8) = line[iVar11];
                  iVar11 = iVar11 + 1;
                } while (iVar11 < iVar5);
              }
              *(undefined1 *)(iVar11 + (int)pvVar8) = 0;
              extra[2] = extra[2] + 1;
            }
            if (line[0] != '\0') {
              iVar5 = 0;
              if (line[0] == ';') {
                line[0] = '\0';
              }
              else {
                do {
                  iVar11 = iVar5;
                  if (line[iVar11 + 1] == '\0') goto LAB_0807bada;
                  iVar5 = iVar11 + 1;
                } while (line[iVar11 + 1] != ';');
                line[iVar11 + 1] = '\0';
              }
            }
LAB_0807bada:
            puVar15 = (uint *)line;
            do {
              puVar14 = puVar15;
              puVar15 = puVar14 + 1;
              uVar12 = *puVar14 + 0xfefefeff & (*puVar14 ^ 0xffffffff);
              uVar13 = uVar12 & 0x80808080;
            } while (uVar13 == 0);
            if ((uVar12 & 0x8080) == 0) {
              uVar13 = uVar13 >> 0x10;
              puVar15 = (uint *)((int)puVar14 + 6);
            }
            iVar5 = (int)puVar15 + ((-3 - (uint)CARRY1((byte)uVar13,(byte)uVar13)) - (int)line);
            if ((line[0] != '\0') && (line[iVar5 + -1] == '\n')) {
              line[iVar5 + -1] = '\0';
              iVar5 = iVar5 + -1;
            }
            iVar11 = iVar5;
            if (line[0] != '\0') {
              while ((-1 < iVar11 + -1 && (iVar9 = TPisspace(line[iVar11 + -1]), iVar9 != 0))) {
                line[iVar11 + -1] = '\0';
                iVar5 = iVar5 + -1;
                iVar11 = iVar11 + -1;
              }
            }
            iVar11 = 0;
            local_134 = 0;
            while ((line[iVar11] != '\0' && (iVar9 = TPisspace(line[iVar11]), iVar9 != 0))) {
              local_134 = local_134 + 1;
              iVar11 = iVar11 + 1;
            }
            if (line[local_134] != '\0') {
              strcpy(local_140,line + local_134);
              if (param_2 == 1) {
                *(int *)(*extra + piVar3[9] * 4) = extra[2] + -1;
              }
              iVar11 = piVar3[9];
              *(char **)(piVar3[8] + iVar11 * 4) = local_140;
              iVar11 = iVar11 + 1;
              piVar3[9] = iVar11;
              if (local_138 <= iVar11) {
                pvVar8 = realloc((void *)piVar3[8],local_144);
                piVar2 = extra;
                if (pvVar8 == (void *)0x0) goto LAB_0807b9a5;
                piVar3[8] = (int)pvVar8;
                if (param_2 == 1) {
                  pvVar8 = realloc((void *)*extra,local_144);
                  if (pvVar8 == (void *)0x0) goto LAB_0807b9a5;
                  *piVar2 = (int)pvVar8;
                }
                local_144 = local_144 + 0x400;
                local_138 = local_138 + 0x100;
              }
              if ((line[local_134] == '[') && (line[iVar5 + -1] == ']')) {
                *(int *)(piVar3[10] + piVar3[0xb] * 4) = piVar3[9] + -1;
                iVar5 = piVar3[0xb];
                piVar3[0xb] = iVar5 + 1;
                if (local_13c <= iVar5 + 1) {
                  pvVar8 = realloc((void *)piVar3[10],local_13c * 4 + 0x100);
                  if (pvVar8 == (void *)0x0) goto LAB_0807b9a5;
                  piVar3[10] = (int)pvVar8;
                  local_13c = local_13c + 0x40;
                }
              }
              sVar10 = strlen(line + local_134);
              local_140 = local_140 + sVar10 + 1;
            }
            pcVar7 = fgets(line,0x100,param_1);
          } while (pcVar7 != (char *)0x0);
        }
        builtin_strncpy(local_140,"[TPEnd]",8);
        return piVar3;
      }
    }
  }
LAB_0807b9a5:
  TPFree(piVar3);
  return (int *)0x0;
}

/* TPWriteFile @ 0x0807bd10, 104 bytes */
undefined4 TPWriteFile(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  FILE *__stream;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  undefined4 extraout_EDX_00;
  int iVar4;
  
  iVar2 = *(int *)(param_1 + 0x30);
  if ((iVar2 != 0) && (__stream = fopen(param_2,"wt"), __stream != (FILE *)0x0)) {
    iVar4 = 0;
    uVar3 = extraout_EDX;
    if (0 < *(int *)(iVar2 + 8)) {
      do {
        iVar1 = iVar4 * 4;
        iVar4 = iVar4 + 1;
        fprintf(__stream,"%s\n",*(undefined4 *)(*(int *)(iVar2 + 4) + iVar1),uVar3);
        uVar3 = extraout_EDX_00;
      } while (iVar4 < *(int *)(iVar2 + 8));
    }
    fclose(__stream);
    return 1;
  }
  return 0;
}

/* TPGroupSeek @ 0x0807bd80, 196 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x120-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 TPGroupSeek(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  unsigned char ghidra_frame[0x120] __attribute__((aligned(16)));
#define local_11c (*(undefined4 *)(ghidra_frame + 0x4))
  
  iVar1 = *(int *)(param_1 + 0x20);
  iVar2 = *(int *)(param_1 + 0x28);
  (*(uchar *)((char *)&local_11c + 0)) = 0x5b;
  strcpy((char *)((int)&local_11c + 1),param_2);
  strcat((char *)&local_11c,"]");
  puVar8 = &local_11c;
  do {
    puVar7 = puVar8;
    puVar8 = puVar7 + 1;
    uVar5 = *puVar7 + 0xfefefeff & (*puVar7 ^ 0xffffffff);
    uVar6 = uVar5 & 0x80808080;
  } while (uVar6 == 0);
  if ((uVar5 & 0x8080) == 0) {
    uVar6 = uVar6 >> 0x10;
    puVar8 = (uint *)((int)puVar7 + 6);
  }
  if (0 < *(int *)(param_1 + 0x2c)) {
    iVar9 = 0;
    do {
      iVar3 = strimatchlen(*(int *)(iVar1 + *(int *)(iVar2 + iVar9 * 4) * 4),(int)&local_11c,
                           (int)((int)puVar8 +
                                ((-3 - (uint)CARRY1((byte)uVar6,(byte)uVar6)) - (int)&local_11c)));
      if (iVar3 != 0) {
        uVar4 = TPGroupSeekIdx(param_1,iVar9);
        return uVar4;
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < *(int *)(param_1 + 0x2c));
  }
  return 0xffffffff;
}
#undef local_11c

/* TPGroupSeekIdx @ 0x0807be50, 85 bytes */
undefined4 TPGroupSeekIdx(int param_1,int param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((param_2 < 0) || (*(int *)(param_1 + 0x2c) <= param_2)) {
    uVar2 = 0xffffffff;
  }
  else {
    *(int *)(param_1 + 0x18) = param_2;
    iVar3 = *(int *)(*(int *)(param_1 + 0x28) + param_2 * 4) + 1;
    *(int *)(param_1 + 0xc) = iVar3;
    *(int *)(param_1 + 0x14) = iVar3;
    pcVar1 = *(char **)(*(int *)(param_1 + 0x20) + iVar3 * 4);
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(int *)(param_1 + 0x10) = (int)pcVar1 - *(int *)(param_1 + 4);
    if ((*(int *)(param_1 + 0x24) <= iVar3) || (*pcVar1 == '[')) {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    uVar2 = *(undefined4 *)(param_1 + 0x10);
  }
  return uVar2;
}

/* TPGroupReset @ 0x0807beb0, 61 bytes */
void TPGroupReset(int param_1)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x18) * 4) + 1;
  *(int *)(param_1 + 0xc) = iVar2;
  *(int *)(param_1 + 0x14) = iVar2;
  pcVar1 = *(char **)(*(int *)(param_1 + 0x20) + iVar2 * 4);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(int *)(param_1 + 0x10) = (int)pcVar1 - *(int *)(param_1 + 4);
  if ((*(int *)(param_1 + 0x24) <= iVar2) || (*pcVar1 == '[')) {
    *(undefined4 *)(param_1 + 0x1c) = 1;
  }
  return;
}

/* TPGroupScanFirst @ 0x0807bef0, 16 bytes */
undefined4 TPGroupScanFirst(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  uVar1 = TPGroupScanNext(param_1);
  return uVar1;
}

/* TPGroupScanNext @ 0x0807bf00, 98 bytes */
undefined4 TPGroupScanNext(int param_1)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x18) + 1;
  *(int *)(param_1 + 0x18) = iVar4;
  if (iVar4 < *(int *)(param_1 + 0x2c)) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x28) + iVar4 * 4) + 1;
    *(int *)(param_1 + 0xc) = iVar3;
    *(int *)(param_1 + 0x14) = iVar3;
    pcVar1 = *(char **)(*(int *)(param_1 + 0x20) + iVar3 * 4);
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(int *)(param_1 + 0x10) = (int)pcVar1 - *(int *)(param_1 + 4);
    uVar2 = *(undefined4 *)
             (*(int *)(param_1 + 0x20) + *(int *)(*(int *)(param_1 + 0x28) + iVar4 * 4) * 4);
    if (iVar3 < *(int *)(param_1 + 0x24)) {
      if (*pcVar1 == '[') {
        *(undefined4 *)(param_1 + 0x1c) = 1;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* TPGroupMatchCount @ 0x0807bf70, 79 bytes */
int TPGroupMatchCount(int param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  iVar2 = TPGroupScanFirst(param_1);
  while (iVar2 != 0) {
    iVar2 = strimatch((char *)(iVar2 + 1),param_2);
    if (iVar2 != 0) {
      iVar3 = iVar3 + 1;
    }
    iVar2 = TPGroupScanNext(param_1);
  }
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  return iVar3;
}

/* TPGetLineNo @ 0x0807bfc0, 24 bytes */
int TPGetLineNo(int param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = TPGetLineNo_Skip(param_1,param_2,0);
  return iVar1;
}

/* TPGetLineNo_Skip @ 0x0807bfe0, 184 bytes */
int TPGetLineNo_Skip(int param_1,char *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  int iVar5;
  int iVar6;
  
  sVar4 = strlen(param_2);
  iVar2 = *(int *)(param_1 + 0x20);
  iVar6 = *(int *)(param_1 + 0xc);
  if (iVar6 < *(int *)(param_1 + 0x24)) {
    pcVar3 = *(char **)(iVar2 + iVar6 * 4);
    cVar1 = *pcVar3;
    while (cVar1 != '[') {
      if (TPCaseSensitive == 0) {
        iVar5 = strimatchlen((int)pcVar3,(int)param_2,sVar4);
      }
      else {
        iVar5 = strmatchlen((int)pcVar3,(int)param_2,sVar4);
      }
      if ((iVar5 != 0) && ((iVar5 = TPisspace(pcVar3[sVar4]), iVar5 != 0 || (pcVar3[sVar4] == '=')))
         ) {
        if (param_3 < 1) {
          return iVar6;
        }
        param_3 = param_3 + -1;
      }
      iVar6 = iVar6 + 1;
      if (*(int *)(param_1 + 0x24) <= iVar6) {
        return -1;
      }
      pcVar3 = *(char **)(iVar2 + iVar6 * 4);
      cVar1 = *pcVar3;
    }
  }
  return -1;
}

/* TPGetValue @ 0x0807c0a0, 281 bytes */
char * TPGetValue(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  int iVar5;
  int iVar6;
  
  sVar4 = strlen(param_2);
  iVar2 = *(int *)(param_1 + 0x20);
  iVar6 = *(int *)(param_1 + 0xc);
  if (iVar6 < *(int *)(param_1 + 0x24)) {
    pcVar3 = *(char **)(iVar2 + iVar6 * 4);
    cVar1 = *pcVar3;
    while (cVar1 != '[') {
      if (TPCaseSensitive == 0) {
        iVar5 = strimatchlen((int)pcVar3,(int)param_2,sVar4);
      }
      else {
        iVar5 = strmatchlen((int)pcVar3,(int)param_2,sVar4);
      }
      if ((iVar5 != 0) && ((iVar5 = TPisspace(pcVar3[sVar4]), iVar5 != 0 || (pcVar3[sVar4] == '=')))
         ) {
        iVar6 = iVar6 + 1;
        *(int *)(param_1 + 0x14) = iVar6;
        if ((*(int *)(param_1 + 0x24) <= iVar6) ||
           (**(char **)(*(int *)(param_1 + 0x20) + iVar6 * 4) == '[')) {
          *(undefined4 *)(param_1 + 0x1c) = 1;
        }
        for (; (cVar1 = pcVar3[sVar4], cVar1 != '=' && (cVar1 != '\0')); sVar4 = sVar4 + 1) {
        }
        if (cVar1 == '\0') goto LAB_0807c171;
        do {
          sVar4 = sVar4 + 1;
LAB_0807c171:
          iVar6 = TPisspace(pcVar3[sVar4]);
        } while ((iVar6 != 0) && (pcVar3[sVar4] != '\0'));
        return pcVar3 + sVar4;
      }
      iVar6 = iVar6 + 1;
      if (*(int *)(param_1 + 0x24) <= iVar6) {
        return (char *)0x0;
      }
      pcVar3 = *(char **)(iVar2 + iVar6 * 4);
      cVar1 = *pcVar3;
    }
  }
  return (char *)0x0;
}

/* TPSeekValue @ 0x0807c1c0, 77 bytes */
int TPSeekValue(int param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  uVar2 = *(undefined4 *)(param_1 + 0x14);
  if (param_2 == (char *)0x0) {
    iVar3 = TPSeekEog(param_1);
    return iVar3;
  }
  pcVar4 = TPGetValue(param_1,param_2);
  if (pcVar4 == (char *)0x0) {
    *(undefined4 *)(param_1 + 0x1c) = uVar1;
    *(undefined4 *)(param_1 + 0x14) = uVar2;
    iVar3 = -1;
  }
  else {
    *(undefined4 *)(param_1 + 0x1c) = uVar1;
    iVar3 = *(int *)(param_1 + 0x14) + -1;
    *(int *)(param_1 + 0x14) = iVar3;
  }
  return iVar3;
}

/* TPSeekEog @ 0x0807c210, 53 bytes */
int TPSeekEog(int param_1)

{
  int in_EDX;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    in_EDX = *(int *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x1c) = 1;
    while ((in_EDX < *(int *)(param_1 + 0x24) &&
           (**(char **)(*(int *)(param_1 + 0x20) + in_EDX * 4) != '['))) {
      in_EDX = in_EDX + 1;
    }
  }
  *(int *)(param_1 + 0x14) = in_EDX;
  return in_EDX;
}

/* TPGetValueNewStr @ 0x0807c250, 82 bytes */
char * TPGetValueNewStr(int param_1,char *param_2)

{
  char *__s;
  size_t sVar1;
  char *__dest;
  
  __s = TPGetValue(param_1,param_2);
  if (__s != (char *)0x0) {
    sVar1 = strlen(__s);
    __dest = malloc(sVar1 + 1);
    if (__dest != (char *)0x0) {
      strcpy(__dest,__s);
      return __dest;
    }
  }
  return (char *)0x0;
}

/* TPGetValueNext @ 0x0807c2b0, 297 bytes */
char * TPGetValueNext(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  size_t sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  sVar3 = strlen(param_2);
  iVar5 = *(int *)(param_1 + 0x20);
  if ((*(int *)(param_1 + 0x1c) == 0) &&
     (iVar6 = *(int *)(param_1 + 0x14), iVar6 < *(int *)(param_1 + 0x24))) {
    pcVar2 = *(char **)(iVar5 + iVar6 * 4);
    cVar1 = *pcVar2;
    while (cVar1 != '[') {
      if (TPCaseSensitive == 0) {
        iVar4 = strimatchlen((int)pcVar2,(int)param_2,sVar3);
      }
      else {
        iVar4 = strmatchlen((int)pcVar2,(int)param_2,sVar3);
      }
      if ((iVar4 != 0) && ((iVar4 = TPisspace(pcVar2[sVar3]), iVar4 != 0 || (pcVar2[sVar3] == '=')))
         ) {
        iVar6 = iVar6 + 1;
        *(int *)(param_1 + 0x14) = iVar6;
        if ((*(int *)(param_1 + 0x24) <= iVar6) ||
           (**(char **)(*(int *)(param_1 + 0x20) + iVar6 * 4) == '[')) {
          *(undefined4 *)(param_1 + 0x1c) = 1;
        }
        for (; (cVar1 = pcVar2[sVar3], cVar1 != '=' && (cVar1 != '\0')); sVar3 = sVar3 + 1) {
        }
        if (cVar1 == '\0') goto LAB_0807c391;
        do {
          sVar3 = sVar3 + 1;
LAB_0807c391:
          iVar5 = TPisspace(pcVar2[sVar3]);
        } while ((iVar5 != 0) && (pcVar2[sVar3] != '\0'));
        return pcVar2 + sVar3;
      }
      iVar6 = iVar6 + 1;
      if (*(int *)(param_1 + 0x24) <= iVar6) {
        return (char *)0x0;
      }
      pcVar2 = *(char **)(iVar5 + iVar6 * 4);
      cVar1 = *pcVar2;
    }
  }
  return (char *)0x0;
}

/* TPGetValueFloat @ 0x0807c3e0, 58 bytes */
bool TPGetValueFloat(int param_1,char *param_2,float *param_3)

{
  char *pcVar1;
  longdouble lVar2;
  
  pcVar1 = TPGetValue(param_1,param_2);
  if (pcVar1 != (char *)0x0) {
    lVar2 = __strtod_internal((int)pcVar1,(int *)0x0,0);
    *param_3 = (float)lVar2;
  }
  return pcVar1 != (char *)0x0;
}

/* TPGetValueInt @ 0x0807c420, 59 bytes */
bool TPGetValueInt(int param_1,char *param_2,uint *param_3)

{
  byte *pbVar1;
  uint uVar2;
  
  pbVar1 = (byte *)TPGetValue(param_1,param_2);
  if (pbVar1 != (byte *)0x0) {
    uVar2 = __strtol_internal(pbVar1,(undefined4 *)0x0,10,0);
    *param_3 = uVar2;
  }
  return pbVar1 != (byte *)0x0;
}

/* TPScanf @ 0x0807c460, 56 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_3 */
int TPScanf(int param_1,char *param_2,char *param_3,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_3);
  char *__s;
  int iVar1;
  
  __s = TPGetValue(param_1,param_2);
  if (__s == (char *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = vsscanf(__s,param_3,ghidra_va);
  }
  return iVar1;
}

/* TPAccessReset @ 0x0807c4a0, 42 bytes */
void TPAccessReset(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x18) * 4) + 1;
  *(int *)(param_1 + 0xc) = iVar1;
  *(int *)(param_1 + 0x14) = iVar1;
  *(int *)(param_1 + 0x10) = *(int *)(*(int *)(param_1 + 0x20) + iVar1 * 4) - *(int *)(param_1 + 4);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}

/* TPAccessFirstLine @ 0x0807c4d0, 27 bytes */
undefined4 TPAccessFirstLine(int param_1)

{
  undefined4 uVar1;
  
  TPAccessReset(param_1);
  uVar1 = TPAccessNextLine(param_1);
  return uVar1;
}

/* TPReaccessCurLine @ 0x0807c4f0, 24 bytes */
undefined4 TPReaccessCurLine(int param_1)

{
  if (*(int *)(param_1 + 0x14) == 0) {
    return 0;
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x20) + -4 + *(int *)(param_1 + 0x14) * 4);
}

/* TPAccessNextLine @ 0x0807c510, 53 bytes */
undefined4 TPAccessNextLine(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x14) * 4);
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    if ((*(int *)(param_1 + 0x24) <= iVar2) ||
       (**(char **)(*(int *)(param_1 + 0x20) + iVar2 * 4) == '[')) {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* TPAccessPrevLine @ 0x0807c550, 34 bytes */
undefined4 TPAccessPrevLine(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x14) + -1;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  if (iVar1 == *(int *)(param_1 + 0xc)) {
    return 0;
  }
  *(int *)(param_1 + 0x14) = iVar1;
  return *(undefined4 *)(*(int *)(param_1 + 0x20) + -4 + iVar1 * 4);
}

/* TPGetLine @ 0x0807c580, 54 bytes */
bool TPGetLine(int param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = (char *)TPAccessNextLine(param_1);
  if (pcVar1 != (char *)0x0) {
    strgetto(param_2,pcVar1,0xff,'\0');
  }
  return pcVar1 != (char *)0x0;
}

/* TPGetGroupText @ 0x0807c5c0, 162 bytes */
int TPGetGroupText(int param_1,int param_2,int param_3)

{
  char *__s;
  size_t __n;
  int iVar1;
  
  iVar1 = 0;
  TPGroupReset(param_1);
  __s = (char *)TPAccessFirstLine(param_1);
  do {
    if (__s == (char *)0x0) break;
    __n = strlen(__s);
    if (param_3 < (int)(__n + iVar1)) {
      __n = param_3 - iVar1;
      strncpy((char *)(param_2 + iVar1),__s,__n);
    }
    else {
      strcpy((char *)(param_2 + iVar1),__s);
    }
    iVar1 = iVar1 + __n;
    __s = (char *)TPAccessNextLine(param_1);
    if ((__s != (char *)0x0) && (iVar1 < param_3)) {
      *(undefined1 *)(iVar1 + param_2) = 10;
      iVar1 = iVar1 + 1;
    }
  } while (iVar1 <= param_3);
  *(undefined1 *)(iVar1 + param_2) = 0;
  return iVar1;
}

/* TPWLineNo @ 0x0807c670, 112 bytes */
int TPWLineNo(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = *(int **)(param_1 + 0x30);
  if (((param_2 < 0) || (*(int *)(param_1 + 0x24) <= param_2)) || (piVar2 == (int *)0x0)) {
    iVar4 = -1;
  }
  else if ((param_2 < 1) || (*(int *)(param_1 + 0x1c) == 0)) {
    iVar4 = *(int *)(*piVar2 + param_2 * 4);
  }
  else {
    iVar3 = *piVar2;
    iVar4 = *(int *)(iVar3 + -4 + param_2 * 4) + 1;
    if ((iVar4 < piVar2[2]) && (iVar4 < *(int *)(iVar3 + param_2 * 4))) {
      cVar1 = **(char **)(piVar2[1] + iVar4 * 4);
      while (((cVar1 != '\0' && (iVar4 = iVar4 + 1, iVar4 < piVar2[2])) &&
             (iVar4 < *(int *)(iVar3 + param_2 * 4)))) {
        cVar1 = **(char **)(piVar2[1] + iVar4 * 4);
      }
    }
  }
  return iVar4;
}

/* TPGroupRename @ 0x0807c6e0, 354 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_2
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x830-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 TPGroupRename(int param_1,char *param_2,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_2);
  char cVar1;
  int *piVar2;
  int iVar3;
  char *__ptr;
  undefined4 uVar4;
  char *__dest;
  int iVar5;
  int iVar6;
  unsigned char ghidra_frame[0x830] __attribute__((aligned(16)));
#define local_824 (*(int *)(ghidra_frame + 0xc))
#define local_81c (*(char (*)[1024])(ghidra_frame + 0x14))
#define local_41c (*(char (*)[1036])(ghidra_frame + 0x414))
  
  piVar2 = *(int **)(param_1 + 0x30);
  local_824 = -1;
  if (piVar2 == (int *)0x0) {
    uVar4 = 0xffffffff;
  }
  else {
    vsprintf(local_41c,param_2,ghidra_va);
    iVar3 = *(int *)(*piVar2 + (*(int *)(param_1 + 0xc) + -1) * 4);
    iVar5 = 0;
    __ptr = *(char **)(piVar2[1] + iVar3 * 4);
    iVar6 = local_824;
    if (*__ptr != '\0') {
      if (*__ptr == ';') {
        local_824 = 0;
        iVar6 = local_824;
      }
      else {
        do {
          iVar5 = iVar5 + 1;
          iVar6 = local_824;
          if (__ptr[iVar5] == '\0') break;
          iVar6 = iVar5;
        } while (__ptr[iVar5] != ';');
      }
    }
    local_824 = iVar6;
    iVar6 = 1;
    local_81c[0] = '[';
    iVar5 = 0;
    while (local_41c[0] != '\0') {
      local_81c[iVar6] = local_41c[iVar5];
      iVar6 = iVar6 + 1;
      local_41c[0] = local_41c[iVar5 + 1];
      iVar5 = iVar5 + 1;
    }
    local_81c[iVar6] = ']';
    iVar6 = iVar6 + 1;
    if (local_824 != -1) {
      for (; iVar6 < local_824; iVar6 = iVar6 + 1) {
        local_81c[iVar6] = ' ';
      }
      cVar1 = __ptr[local_824];
      while (cVar1 != '\0') {
        local_824 = local_824 + 1;
        local_81c[iVar6] = cVar1;
        iVar6 = iVar6 + 1;
        cVar1 = __ptr[local_824];
      }
    }
    local_81c[iVar6] = '\0';
    __dest = malloc(iVar6 + 1);
    if (__dest == (char *)0x0) {
      uVar4 = 0;
    }
    else {
      strcpy(__dest,local_81c);
      free(__ptr);
      *(char **)(piVar2[1] + iVar3 * 4) = __dest;
      uVar4 = 1;
    }
  }
  return uVar4;
}
#undef local_824
#undef local_81c
#undef local_41c

/* TPPrintf @ 0x0807c850, 418 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_3
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x830-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 TPPrintf(int param_1,char *param_2,char *param_3,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_3);
  int *piVar1;
  char *__ptr;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *__dest;
  int iVar6;
  int iVar7;
  unsigned char ghidra_frame[0x830] __attribute__((aligned(16)));
#define local_824 (*(int *)(ghidra_frame + 0xc))
#define local_81c (*(char (*)[1024])(ghidra_frame + 0x14))
#define local_41c (*(char (*)[1036])(ghidra_frame + 0x414))
  
  piVar1 = *(int **)(param_1 + 0x30);
  local_824 = -1;
  if (piVar1 == (int *)0x0) {
LAB_0807c874:
    uVar3 = 0xffffffff;
  }
  else {
    vsprintf(local_41c,param_3,ghidra_va);
    iVar4 = TPGetLineNo(param_1,param_2);
    if (iVar4 != -1) {
      iVar6 = 0;
      iVar4 = *(int *)(*piVar1 + iVar4 * 4);
      __ptr = *(char **)(piVar1[1] + iVar4 * 4);
      cVar2 = *__ptr;
      while (cVar2 != '=') {
        if (cVar2 == '\0') goto LAB_0807c874;
        iVar6 = iVar6 + 1;
        cVar2 = __ptr[iVar6];
      }
      do {
        iVar6 = iVar6 + 1;
        iVar5 = TPisspace(__ptr[iVar6]);
        iVar7 = iVar6;
        if (iVar5 == 0) {
          cVar2 = __ptr[iVar6];
          goto LAB_0807c91b;
        }
      } while (__ptr[iVar6] != '\0');
      cVar2 = '\0';
LAB_0807c91b:
      while ((iVar5 = local_824, cVar2 != '\0' && (iVar5 = iVar7, cVar2 != ';'))) {
        cVar2 = __ptr[iVar7 + 1];
        iVar7 = iVar7 + 1;
      }
      local_824 = iVar5;
      iVar7 = 0;
      if (0 < iVar6) {
        do {
          local_81c[iVar7] = __ptr[iVar7];
          iVar7 = iVar7 + 1;
        } while (iVar7 < iVar6);
      }
      iVar6 = 0;
      while (local_41c[0] != '\0') {
        local_81c[iVar7] = local_41c[iVar6];
        iVar7 = iVar7 + 1;
        local_41c[0] = local_41c[iVar6 + 1];
        iVar6 = iVar6 + 1;
      }
      if (local_824 != -1) {
        for (; iVar7 < local_824; iVar7 = iVar7 + 1) {
          local_81c[iVar7] = ' ';
        }
        cVar2 = __ptr[local_824];
        while (cVar2 != '\0') {
          local_824 = local_824 + 1;
          local_81c[iVar7] = cVar2;
          iVar7 = iVar7 + 1;
          cVar2 = __ptr[local_824];
        }
      }
      local_81c[iVar7] = '\0';
      __dest = malloc(iVar7 + 1);
      if (__dest != (char *)0x0) {
        strcpy(__dest,local_81c);
        free(__ptr);
        *(char **)(piVar1[1] + iVar4 * 4) = __dest;
        return 1;
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}
#undef local_824
#undef local_81c
#undef local_41c

/* TPPrintf_Skip @ 0x0807ca00, 434 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_4
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x830-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 TPPrintf_Skip(int param_1,char *param_2,int param_3,char *param_4,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_4);
  int *piVar1;
  char *__ptr;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *__dest;
  int iVar6;
  int iVar7;
  unsigned char ghidra_frame[0x830] __attribute__((aligned(16)));
#define local_824 (*(int *)(ghidra_frame + 0xc))
#define local_81c (*(char (*)[1024])(ghidra_frame + 0x14))
#define local_41c (*(char (*)[1036])(ghidra_frame + 0x414))
  
  piVar1 = *(int **)(param_1 + 0x30);
  local_824 = -1;
  if (piVar1 == (int *)0x0) {
LAB_0807ca24:
    uVar3 = 0xffffffff;
  }
  else {
    vsprintf(local_41c,param_4,ghidra_va);
    iVar4 = TPGetLineNo_Skip(param_1,param_2,param_3);
    if (iVar4 != -1) {
      iVar6 = 0;
      iVar4 = *(int *)(*piVar1 + iVar4 * 4);
      __ptr = *(char **)(piVar1[1] + iVar4 * 4);
      cVar2 = *__ptr;
      while (cVar2 != '=') {
        if (cVar2 == '\0') goto LAB_0807ca24;
        iVar6 = iVar6 + 1;
        cVar2 = __ptr[iVar6];
      }
      do {
        iVar6 = iVar6 + 1;
        iVar5 = TPisspace(__ptr[iVar6]);
        iVar7 = iVar6;
        if (iVar5 == 0) {
          cVar2 = __ptr[iVar6];
          goto LAB_0807cadb;
        }
      } while (__ptr[iVar6] != '\0');
      cVar2 = '\0';
LAB_0807cadb:
      while ((iVar5 = local_824, cVar2 != '\0' && (iVar5 = iVar7, cVar2 != ';'))) {
        cVar2 = __ptr[iVar7 + 1];
        iVar7 = iVar7 + 1;
      }
      local_824 = iVar5;
      iVar7 = 0;
      if (0 < iVar6) {
        do {
          local_81c[iVar7] = __ptr[iVar7];
          iVar7 = iVar7 + 1;
        } while (iVar7 < iVar6);
      }
      iVar6 = 0;
      while (local_41c[0] != '\0') {
        local_81c[iVar7] = local_41c[iVar6];
        iVar7 = iVar7 + 1;
        local_41c[0] = local_41c[iVar6 + 1];
        iVar6 = iVar6 + 1;
      }
      if (local_824 != -1) {
        for (; iVar7 < local_824; iVar7 = iVar7 + 1) {
          local_81c[iVar7] = ' ';
        }
        cVar2 = __ptr[local_824];
        while (cVar2 != '\0') {
          local_824 = local_824 + 1;
          local_81c[iVar7] = cVar2;
          iVar7 = iVar7 + 1;
          cVar2 = __ptr[local_824];
        }
      }
      local_81c[iVar7] = '\0';
      __dest = malloc(iVar7 + 1);
      if (__dest != (char *)0x0) {
        strcpy(__dest,local_81c);
        free(__ptr);
        *(char **)(piVar1[1] + iVar4 * 4) = __dest;
        return 1;
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}
#undef local_824
#undef local_81c
#undef local_41c

/* TPInsertLine @ 0x0807cbc0, 218 bytes */
undefined4 TPInsertLine(int param_1,char *param_2)

{
  int *piVar1;
  int iVar2;
  size_t sVar3;
  char *__dest;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  piVar1 = *(int **)(param_1 + 0x30);
  iVar6 = *(int *)(param_1 + 0x14);
  if ((piVar1 != (int *)0x0) && (iVar2 = TPWLineNo(param_1,iVar6), iVar2 != -1)) {
    sVar3 = strlen(param_2);
    __dest = malloc(sVar3 + 1);
    if (__dest != (char *)0x0) {
      strcpy(__dest,param_2);
      iVar4 = TPWExpandLinespace(param_1);
      if (iVar4 != 0) {
        iVar4 = piVar1[2];
        if (iVar2 < iVar4) {
          puVar5 = (undefined4 *)(iVar4 * 4 + piVar1[1]);
          do {
            iVar4 = iVar4 + -1;
            *puVar5 = puVar5[-1];
            puVar5 = puVar5 + -1;
          } while (iVar2 < iVar4);
          iVar4 = piVar1[2];
        }
        piVar1[2] = iVar4 + 1;
        *(char **)(piVar1[1] + iVar2 * 4) = __dest;
        if (iVar6 < *(int *)(param_1 + 0x24)) {
          iVar2 = *piVar1;
          do {
            *(int *)(iVar2 + iVar6 * 4) = *(int *)(iVar2 + iVar6 * 4) + 1;
            iVar6 = iVar6 + 1;
          } while (iVar6 < *(int *)(param_1 + 0x24));
        }
        return 1;
      }
      free(__dest);
    }
  }
  return 0;
}

/* TPDeleteLine @ 0x0807cca0, 176 bytes */
undefined4 TPDeleteLine(int param_1)

{
  int *piVar1;
  int iVar2;
  void *__ptr;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = *(int **)(param_1 + 0x30);
  iVar4 = *(int *)(param_1 + 0x14);
  if (((piVar1 != (int *)0x0) && (*(int *)(param_1 + 0x1c) == 0)) &&
     (iVar3 = TPWLineNo(param_1,iVar4), iVar3 != -1)) {
    iVar4 = iVar4 + 1;
    if (iVar4 < *(int *)(param_1 + 0x24)) {
      iVar2 = *piVar1;
      do {
        *(int *)(iVar2 + iVar4 * 4) = *(int *)(iVar2 + iVar4 * 4) + -1;
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 0x24));
    }
    __ptr = *(void **)(piVar1[1] + iVar3 * 4);
    if (__ptr != (void *)0x0) {
      free(__ptr);
    }
    iVar4 = piVar1[2];
    if (iVar3 < iVar4 + -1) {
      iVar2 = piVar1[1];
      iVar5 = iVar3;
      do {
        *(undefined4 *)(iVar2 + iVar5 * 4) = *(undefined4 *)(iVar2 + 4 + iVar5 * 4);
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar4 + -1);
      iVar4 = piVar1[2];
    }
    piVar1[2] = iVar4 + -1;
    iVar4 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar4;
    if ((piVar1[2] <= iVar3) || (**(char **)(*(int *)(param_1 + 0x20) + iVar4 * 4) == '[')) {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    return 1;
  }
  return 0;
}

/* TPDeleteAllLines @ 0x0807cd50, 37 bytes */
void TPDeleteAllLines(int param_1)

{
  int iVar1;
  
  TPGroupReset(param_1);
  do {
    iVar1 = TPDeleteLine(param_1);
  } while (iVar1 != 0);
  return;
}

/* TPWExpandLinespace @ 0x0807cd80, 72 bytes */
undefined4 TPWExpandLinespace(int param_1)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (*(int *)(iVar1 + 0xc) <= *(int *)(iVar1 + 8) + 1) {
    pvVar2 = realloc(*(void **)(iVar1 + 4),*(int *)(iVar1 + 0xc) * 4 + 0x100);
    if (pvVar2 == (void *)0x0) {
      return 0;
    }
    *(void **)(iVar1 + 4) = pvVar2;
    *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 0x40;
  }
  return 1;
}

/* strgetto @ 0x0807cdd0, 65 bytes */
void strgetto(char *param_1,char *param_2,int param_3,char param_4)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((0 < param_3) && (*param_2 != '\0')) {
    *param_1 = *param_2;
    cVar1 = *param_2;
    while (((cVar1 != param_4 && (iVar2 = iVar2 + 1, iVar2 < param_3)) && (param_2[iVar2] != '\0')))
    {
      param_1[iVar2] = param_2[iVar2];
      cVar1 = param_2[iVar2];
    }
  }
  param_1[iVar2] = '\0';
  return;
}

/* TPisspace @ 0x0807ce20, 27 bytes */
undefined4 TPisspace(char param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (((param_1 == ' ') || (param_1 == '\t')) || (param_1 == '\r')) {
    uVar1 = 1;
  }
  return uVar1;
}

