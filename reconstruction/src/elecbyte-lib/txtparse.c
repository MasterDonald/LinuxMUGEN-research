/*
 * txtparse.c -- text parser
 * Reads "[Group] / key = value" text files (all MUGEN definition files) into
 * memory and looks up groups and keys; can rewrite values and save the file
 * keeping its comments.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/txtparse.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* TPFree @ 0x0807b200, 233 bytes
 *
 * Releases a TP object. The text buffer, line table and group table are
 * freed only when the shared reference count is 1 (the last clone).
 * Otherwise the count is decremented. The write-back data (raw lines and
 * line map) is freed too, then the header. Accepts NULL.
 *
 * Parameters:
 *   tp           uint32_t *
 *
 * C library: free
 * Called by: AnimRCReadFile, BGArrayReadFileSA, FindCharacters,
 *            FontReadFilePtr_0_01, GameBGLoad, GameConfigRead,
 *            GameLoadFightData, GameLoadOptions, GameLoadStage,
 *            GameLoadSystem, GameReloadSystemSprSnd, GameSaveOptions,
 *            GameStgInitFightData, PlayerCMDLoad, PlayerDefLoadPtr,
 *            PlayerDefLoadZip, ... (21 callers)
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPFree(uint32_t *tp)

{
  uint32_t *ptr;
  void *ptr_00;
  uint32_t entry_EAX;
  int i1;
  uint32_t stale_EAX;
  int i2;
  int i3;
  
  if (tp != (uint32_t *)0x0) {
    ptr = (uint32_t *)tp[0xc];
    i1 = *(int *)*tp;
    if (i1 == 1) {
      if ((void *)tp[1] != (void *)0x0) {
        free((void *)tp[1]);
      }
      if ((void *)tp[8] != (void *)0x0) {
        free((void *)tp[8]);
      }
      if ((void *)tp[10] != (void *)0x0) {
        free((void *)tp[10]);
      }
      if (ptr != (uint32_t *)0x0) {
        if ((void *)*ptr != (void *)0x0) {
          free((void *)*ptr);
        }
        i1 = ptr[1];
        if (i1 != 0) {
          i3 = 0;
          i2 = ptr[2];
          if (0 < i2) {
            while( true ) {
              ptr_00 = *(void **)(i1 + i3 * 4);
              if (ptr_00 != (void *)0x0) {
                free(ptr_00);
                i2 = ptr[2];
              }
              i3 = i3 + 1;
              if (i2 <= i3) break;
              i1 = ptr[1];
            }
          }
          free((void *)ptr[1]);
        }
        free(ptr);
      }
      free((void *)*tp);
    }
    else {
      *(int *)*tp = i1 + -1;
    }
    free(tp);
    return stale_EAX;
  }
  return entry_EAX;
}

/* TPReadMFPtr @ 0x0807b2f0, 1161 bytes
 *
 * Same parsing as TPReadFilePtr, but reads from an MF stream (MFfgets), so
 * files can come from memory or from a zip archive.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int
 *
 * Calls: MFftell, ecalloc, MFfgets, TPisspace, TPFree
 * C library: realloc, malloc, strcpy, strlen, builtin_strncpy
 * Called by: TPReadMF
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: decompiler flag: type propagation did not settle
 */
uint32_t * TPReadMFPtr(int *mf,int arg2)

{
  char c1;
  int *pi2;
  uint32_t *mem;
  uint32_t *mem2;
  int mem3;
  char *pc6;
  void *pv7;
  int i8;
  size_t s9;
  int i2;
  uint32_t u11;
  uint32_t u12;
  uint32_t *pu13;
  uint32_t *pu14;
  size_t stk_144;
  char *stk_140;
  int stk_13c;
  int stk_138;
  int stk_134;
  int *mem4;
  char line [256];
  
  stk_138 = 0x100;
  stk_13c = 0x40;
  MFftell(mf);
  mem = (uint32_t *)ecalloc(1,0x34);
  if (mem == (uint32_t *)0x0) {
    return (uint32_t *)0x0;
  }
  mem2 = (uint32_t *)ecalloc(1,4);
  *mem = mem2;
  if (mem2 == (uint32_t *)0x0) {
    return (uint32_t *)0x0;
  }
  *mem2 = 1;
  if (arg2 == 1) {
    mem4 = (int *)ecalloc(1,0x10);
    mem[0xc] = mem4;
    if (mem4 == (int *)0x0) {
      return (uint32_t *)0x0;
    }
    mem4[3] = 0x100;
    mem3 = ecalloc(1,0x400);
    mem4[1] = mem3;
    if (mem3 == 0) goto L_0807b414;
  }
  mem3 = mf[4];
  i2 = mf[3];
  mem[2] = mem3 - i2;
  mem3 = ecalloc(1,(mem3 - i2) + 0x10);
  mem[1] = mem3;
  if (mem3 != 0) {
    mem3 = ecalloc(0x101,4);
    mem[8] = mem3;
    if (mem3 != 0) {
      mem3 = ecalloc(0x41,4);
      mem[10] = mem3;
      if (mem3 != 0) {
        if (arg2 == 1) {
          mem3 = ecalloc(0x101,4);
          *mem4 = mem3;
          if (mem3 == 0) goto L_0807b414;
        }
        stk_140 = (char *)mem[1];
        pc6 = MFfgets(line,0x100,mf);
        if (pc6 != (char *)0x0) {
          stk_144 = 0x800;
          do {
            if (arg2 == 1) {
              if (mem4[3] <= mem4[2] + 1) {
                pv7 = realloc((void *)mem4[1],mem4[3] * 4 + 0x400);
                if (pv7 == (void *)0x0) goto L_0807b414;
                mem4[1] = (int)pv7;
                mem4[3] = mem4[3] + 0x100;
              }
              mem3 = 0;
              c1 = line[0];
              while ((c1 != '\0' && (c1 != '\n'))) {
                c1 = line[mem3 + 1];
                mem3 = mem3 + 1;
              }
              pv7 = malloc(mem3 + 1);
              *(void **)(mem4[1] + mem4[2] * 4) = pv7;
              if (pv7 == (void *)0x0) goto L_0807b414;
              i2 = 0;
              if (0 < mem3) {
                do {
                  *(char *)(i2 + (int)pv7) = line[i2];
                  i2 = i2 + 1;
                } while (i2 < mem3);
              }
              *(uint8_t *)(i2 + (int)pv7) = 0;
              mem4[2] = mem4[2] + 1;
            }
            if (line[0] != '\0') {
              mem3 = 0;
              if (line[0] == ';') {
                line[0] = '\0';
              }
              else {
                do {
                  i2 = mem3;
                  if (line[i2 + 1] == '\0') goto L_0807b54a;
                  mem3 = i2 + 1;
                } while (line[i2 + 1] != ';');
                line[i2 + 1] = '\0';
              }
            }
L_0807b54a:
            pu14 = (uint32_t *)line;
            do {
              pu13 = pu14;
              pu14 = pu13 + 1;
              u11 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u12 = u11 & 0x80808080;
            } while (u12 == 0);
            if ((u11 & 0x8080) == 0) {
              u12 = u12 >> 0x10;
              pu14 = (uint32_t *)((int)pu13 + 6);
            }
            mem3 = (int)pu14 + ((-3 - (uint32_t)CARRY1((uint8_t)u12,(uint8_t)u12)) - (int)line);
            if ((line[0] != '\0') && (line[mem3 + -1] == '\n')) {
              line[mem3 + -1] = '\0';
              mem3 = mem3 + -1;
            }
            i2 = mem3;
            if (line[0] != '\0') {
              while ((-1 < i2 + -1 && (i8 = TPisspace(line[i2 + -1]), i8 != 0))) {
                line[i2 + -1] = '\0';
                mem3 = mem3 + -1;
                i2 = i2 + -1;
              }
            }
            i2 = 0;
            stk_134 = 0;
            while ((line[i2] != '\0' && (i8 = TPisspace(line[i2]), i8 != 0))) {
              stk_134 = stk_134 + 1;
              i2 = i2 + 1;
            }
            if (line[stk_134] != '\0') {
              strcpy(stk_140,line + stk_134);
              if (arg2 == 1) {
                *(int *)(*mem4 + mem[9] * 4) = mem4[2] + -1;
              }
              i2 = mem[9];
              *(char **)(mem[8] + i2 * 4) = stk_140;
              i2 = i2 + 1;
              mem[9] = i2;
              if (stk_138 <= i2) {
                pv7 = realloc((void *)mem[8],stk_144);
                pi2 = mem4;
                if (pv7 == (void *)0x0) goto L_0807b414;
                mem[8] = pv7;
                if (arg2 == 1) {
                  pv7 = realloc((void *)*mem4,stk_144);
                  if (pv7 == (void *)0x0) goto L_0807b414;
                  *pi2 = (int)pv7;
                }
                stk_144 = stk_144 + 0x400;
                stk_138 = stk_138 + 0x100;
              }
              if ((line[stk_134] == '[') && (line[mem3 + -1] == ']')) {
                *(int *)(mem[10] + mem[0xb] * 4) = mem[9] + -1;
                mem3 = mem[0xb];
                mem[0xb] = mem3 + 1;
                if (stk_13c <= mem3 + 1) {
                  pv7 = realloc((void *)mem[10],stk_13c * 4 + 0x100);
                  if (pv7 == (void *)0x0) goto L_0807b414;
                  mem[10] = pv7;
                  stk_13c = stk_13c + 0x40;
                }
              }
              s9 = strlen(line + stk_134);
              stk_140 = stk_140 + s9 + 1;
            }
            pc6 = MFfgets(line,0x100,mf);
          } while (pc6 != (char *)0x0);
        }
        builtin_strncpy(stk_140,"[TPEnd]",8);
        return mem;
      }
    }
  }
L_0807b414:
  TPFree(mem);
  return (uint32_t *)0x0;
}

/* TPReadMF @ 0x0807b780, 61 bytes
 *
 * Reads a TP object from an MF stream: stdio-backed streams go to
 * TPReadFilePtr, memory and zip streams to TPReadMFPtr. Returns NULL for an
 * invalid stream.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int
 *
 * Calls: TPReadFilePtr, TPReadMFPtr
 * Called by: FindCharacters, PlayerDefLoadZip
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int * TPReadMF(int *mf,int arg2)

{
  int i1;
  int *tp;
  
  i1 = *mf;
  if (i1 == 1) {
    tp = TPReadFilePtr((FILE *)mf[1],arg2);
    return tp;
  }
  if ((0 < i1) && (i1 < 4)) {
    tp = TPReadMFPtr(mf,arg2);
    return tp;
  }
  return (int *)0x0;
}

/* TPReadFile @ 0x0807b7c0, 62 bytes
 *
 * Opens `filename` in text mode, parses it (TPReadFilePtr, read-only) and
 * closes it. Returns the TP object or NULL.
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: TPReadFilePtr
 * C library: fopen, fclose
 * Called by: AnimRCReadFile, BGArrayReadFileSA, FindCharacters,
 *            GameBGLoad, GameConfigRead, GameLoadFightData,
 *            GameLoadOptions, GameLoadStage, GameLoadSystem,
 *            GameReloadSystemSprSnd, GameStgInitFightData,
 *            InitSelectScreenMatrix, PlayerCMDLoad, PlayerDefLoadPtr,
 *            PlayerSTLoadAppend, QuickVSSetup, ... (17 callers)
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void * TPReadFile(char *filename)

{
  FILE *fp;
  int *tp;
  
  fp = fopen(filename,"rt");
  if (fp == (FILE *)0x0) {
    tp = (int *)0x0;
  }
  else {
    tp = TPReadFilePtr(fp,0);
    fclose(fp);
  }
  return tp;
}

/* TPClone @ 0x0807b800, 55 bytes
 *
 * Makes a second TP header that shares the text, line and group tables of
 * `tp` (copies the 13 header words and increments the shared reference
 * count). Each clone has its own cursor. Not called in this build.
 *
 * Parameters:
 *   tp           uint32_t *
 *
 * Calls: ecalloc
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t * TPClone(uint32_t *tp)

{
  uint32_t *mem;
  int i2;
  uint32_t *pu3;
  
  mem = (uint32_t *)ecalloc(1,0x34);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    pu3 = mem;
    for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
      *pu3 = *tp;
      tp = tp + 1;
      pu3 = pu3 + 1;
    }
    *(int *)*mem = *(int *)*mem + 1;
  }
  return mem;
}

/* TPReadFileForWrite @ 0x0807b840, 62 bytes
 *
 * Opens `filename` and parses it with write-back data (TPReadFilePtr with
 * for_write = 1), so that values can be changed and the file saved with
 * TPWriteFile. Used for mugen.cfg (GameSaveOptions).
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: TPReadFilePtr
 * C library: fopen, fclose
 * Called by: GameConfigRead, GameSaveOptions
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void * TPReadFileForWrite(char *filename)

{
  FILE *fp;
  int *tp;
  
  fp = fopen(filename,"rt");
  if (fp == (FILE *)0x0) {
    tp = (int *)0x0;
  }
  else {
    tp = TPReadFilePtr(fp,1);
    fclose(fp);
  }
  return tp;
}

/* TPReadFilePtr @ 0x0807b880, 1161 bytes
 *
 * Reads a whole text file from an open stdio FILE into a new TP object.
 * Returns NULL on any allocation failure.
 *
 * Each line is read with fgets (lines longer than 255 characters are split).
 * Everything from the first ';' is a comment and is cut off. The newline and
 * trailing and leading blanks (space, tab, CR) are removed, and empty lines
 * are dropped. The remaining lines are packed into one buffer and indexed in
 * the line table. Lines that start with '[' and end with ']' are group
 * headers and are also recorded in the group table. A final "[TPEnd]" line
 * acts as a sentinel group.
 *
 * With `for_write` = 1, every raw line (comments and blank lines included)
 * is also kept, with the mapping from kept lines to raw lines, so that
 * TPPrintf can edit values and TPWriteFile can save the file with its
 * comments (used for mugen.cfg and key configuration).
 *
 * Parameters:
 *   fp           FILE *
 *   arg2         int
 *
 * Calls: ecalloc, ffilelength, TPisspace, TPFree
 * C library: ftell, fgets, realloc, malloc, strcpy, strlen,
 *            builtin_strncpy
 * Called by: FontReadFilePtr_0_01, PlayerDefLoadPtr, TPReadFile,
 *            TPReadFileForWrite, TPReadMF
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: decompiler flag: type propagation did not settle
 */
int * TPReadFilePtr(FILE *fp,int arg2)

{
  char c1;
  int *pi2;
  int *mem;
  uint32_t *mem2;
  int mem3;
  long l6;
  char *pc7;
  void *pv8;
  int i9;
  size_t s10;
  int i2;
  uint32_t u12;
  uint32_t u13;
  uint32_t *pu14;
  uint32_t *pu15;
  size_t stk_144;
  char *stk_140;
  int stk_13c;
  int stk_138;
  int stk_134;
  int *mem4;
  char line [256];
  
  stk_138 = 0x100;
  stk_13c = 0x40;
  ftell(fp);
  mem = (int *)ecalloc(1,0x34);
  if (mem == (int *)0x0) {
    return (int *)0x0;
  }
  mem2 = (uint32_t *)ecalloc(1,4);
  *mem = (int)mem2;
  if (mem2 == (uint32_t *)0x0) {
    return (int *)0x0;
  }
  *mem2 = 1;
  if (arg2 == 1) {
    mem4 = (int *)ecalloc(1,0x10);
    mem[0xc] = (int)mem4;
    if (mem4 == (int *)0x0) {
      return (int *)0x0;
    }
    mem4[3] = 0x100;
    mem3 = ecalloc(1,0x400);
    mem4[1] = mem3;
    if (mem3 == 0) goto L_0807b9a5;
  }
  l6 = ffilelength(fp);
  mem[2] = l6;
  mem3 = ecalloc(1,l6 + 0x10);
  mem[1] = mem3;
  if (mem3 != 0) {
    mem3 = ecalloc(0x101,4);
    mem[8] = mem3;
    if (mem3 != 0) {
      mem3 = ecalloc(0x41,4);
      mem[10] = mem3;
      if (mem3 != 0) {
        if (arg2 == 1) {
          mem3 = ecalloc(0x101,4);
          *mem4 = mem3;
          if (mem3 == 0) goto L_0807b9a5;
        }
        stk_140 = (char *)mem[1];
        pc7 = fgets(line,0x100,fp);
        if (pc7 != (char *)0x0) {
          stk_144 = 0x800;
          do {
            if (arg2 == 1) {
              if (mem4[3] <= mem4[2] + 1) {
                pv8 = realloc((void *)mem4[1],mem4[3] * 4 + 0x400);
                if (pv8 == (void *)0x0) goto L_0807b9a5;
                mem4[1] = (int)pv8;
                mem4[3] = mem4[3] + 0x100;
              }
              mem3 = 0;
              c1 = line[0];
              while ((c1 != '\0' && (c1 != '\n'))) {
                c1 = line[mem3 + 1];
                mem3 = mem3 + 1;
              }
              pv8 = malloc(mem3 + 1);
              *(void **)(mem4[1] + mem4[2] * 4) = pv8;
              if (pv8 == (void *)0x0) goto L_0807b9a5;
              i2 = 0;
              if (0 < mem3) {
                do {
                  *(char *)(i2 + (int)pv8) = line[i2];
                  i2 = i2 + 1;
                } while (i2 < mem3);
              }
              *(uint8_t *)(i2 + (int)pv8) = 0;
              mem4[2] = mem4[2] + 1;
            }
            if (line[0] != '\0') {
              mem3 = 0;
              if (line[0] == ';') {
                line[0] = '\0';
              }
              else {
                do {
                  i2 = mem3;
                  if (line[i2 + 1] == '\0') goto L_0807bada;
                  mem3 = i2 + 1;
                } while (line[i2 + 1] != ';');
                line[i2 + 1] = '\0';
              }
            }
L_0807bada:
            pu15 = (uint32_t *)line;
            do {
              pu14 = pu15;
              pu15 = pu14 + 1;
              u12 = *pu14 + 0xfefefeff & (*pu14 ^ 0xffffffff);
              u13 = u12 & 0x80808080;
            } while (u13 == 0);
            if ((u12 & 0x8080) == 0) {
              u13 = u13 >> 0x10;
              pu15 = (uint32_t *)((int)pu14 + 6);
            }
            mem3 = (int)pu15 + ((-3 - (uint32_t)CARRY1((uint8_t)u13,(uint8_t)u13)) - (int)line);
            if ((line[0] != '\0') && (line[mem3 + -1] == '\n')) {
              line[mem3 + -1] = '\0';
              mem3 = mem3 + -1;
            }
            i2 = mem3;
            if (line[0] != '\0') {
              while ((-1 < i2 + -1 && (i9 = TPisspace(line[i2 + -1]), i9 != 0))) {
                line[i2 + -1] = '\0';
                mem3 = mem3 + -1;
                i2 = i2 + -1;
              }
            }
            i2 = 0;
            stk_134 = 0;
            while ((line[i2] != '\0' && (i9 = TPisspace(line[i2]), i9 != 0))) {
              stk_134 = stk_134 + 1;
              i2 = i2 + 1;
            }
            if (line[stk_134] != '\0') {
              strcpy(stk_140,line + stk_134);
              if (arg2 == 1) {
                *(int *)(*mem4 + mem[9] * 4) = mem4[2] + -1;
              }
              i2 = mem[9];
              *(char **)(mem[8] + i2 * 4) = stk_140;
              i2 = i2 + 1;
              mem[9] = i2;
              if (stk_138 <= i2) {
                pv8 = realloc((void *)mem[8],stk_144);
                pi2 = mem4;
                if (pv8 == (void *)0x0) goto L_0807b9a5;
                mem[8] = (int)pv8;
                if (arg2 == 1) {
                  pv8 = realloc((void *)*mem4,stk_144);
                  if (pv8 == (void *)0x0) goto L_0807b9a5;
                  *pi2 = (int)pv8;
                }
                stk_144 = stk_144 + 0x400;
                stk_138 = stk_138 + 0x100;
              }
              if ((line[stk_134] == '[') && (line[mem3 + -1] == ']')) {
                *(int *)(mem[10] + mem[0xb] * 4) = mem[9] + -1;
                mem3 = mem[0xb];
                mem[0xb] = mem3 + 1;
                if (stk_13c <= mem3 + 1) {
                  pv8 = realloc((void *)mem[10],stk_13c * 4 + 0x100);
                  if (pv8 == (void *)0x0) goto L_0807b9a5;
                  mem[10] = (int)pv8;
                  stk_13c = stk_13c + 0x40;
                }
              }
              s10 = strlen(line + stk_134);
              stk_140 = stk_140 + s10 + 1;
            }
            pc7 = fgets(line,0x100,fp);
          } while (pc7 != (char *)0x0);
        }
        builtin_strncpy(stk_140,"[TPEnd]",8);
        return mem;
      }
    }
  }
L_0807b9a5:
  TPFree(mem);
  return (int *)0x0;
}

/* TPWriteFile @ 0x0807bd10, 104 bytes
 *
 * Writes the raw lines of a TP object opened for write back to `filename`,
 * one per line. Returns nonzero on success, 0 if the object has no
 * write-back data or the file cannot be created.
 *
 * Parameters:
 *   tp           int
 *   filename     char *
 *
 * C library: fopen, fprintf, fclose
 * Called by: GameConfigRead, GameSaveOptions
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPWriteFile(int tp,char *filename)

{
  int i1;
  int i2;
  FILE *stream;
  uint32_t stale_EDX;
  uint32_t u3;
  uint32_t stale_EDX_00;
  int i3;
  
  i2 = *(int *)(tp + 0x30);
  if ((i2 != 0) && (stream = fopen(filename,"wt"), stream != (FILE *)0x0)) {
    i3 = 0;
    u3 = stale_EDX;
    if (0 < *(int *)(i2 + 8)) {
      do {
        i1 = i3 * 4;
        i3 = i3 + 1;
        fprintf(stream,"%s\n",*(uint32_t *)(*(int *)(i2 + 4) + i1),u3);
        u3 = stale_EDX_00;
      } while (i3 < *(int *)(i2 + 8));
    }
    fclose(stream);
    return 1;
  }
  return 0;
}

/* TPGroupSeek @ 0x0807bd80, 196 bytes
 *
 * Makes the group "[`group`]" current and resets the cursor to its first
 * line. Every group header is compared case-insensitively with the string
 * "[" + group + "]" over that string's length; header text after it is
 * ignored. When several groups match, the last one wins. Returns the group's
 * byte offset (TPGroupSeekIdx), or -1 when no group matches.
 *
 * Parameters:
 *   tp           int
 *   group        char *
 *
 * Calls: strimatchlen, TPGroupSeekIdx
 * C library: strcpy, strcat
 * Called by: BGArrayReadTP, FindCharacters, FontReadFilePtr_0_01,
 *            GameBGLoad, GameConfigRead, GameLoadFightData,
 *            GameLoadOptions, GameLoadStage, GameLoadSystem,
 *            GameSaveOptions, GameStgInitFightData, PlayerCMDLoadTP,
 *            PlayerCNSLoadTP, PlayerDefLoadPtr, PlayerDefLoadZip,
 *            PlayerLoadKeys, ... (21 callers)
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: Locals live in `frame`, laid out as on the original stack (0x120 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t TPGroupSeek(int tp,char *group)

{
  int i1;
  int i2;
  int i3;
  uint32_t u4;
  uint32_t u5;
  uint32_t u6;
  uint32_t *pu7;
  uint32_t *pu8;
  int group2;
  unsigned char frame[0x120] __attribute__((aligned(16)));
#define stk_11c (*(uint32_t *)(frame + 0x4))
  
  i1 = *(int *)(tp + 0x20);
  i2 = *(int *)(tp + 0x28);
  (*(uint8_t *)((char *)&stk_11c + 0)) = 0x5b;
  strcpy((char *)((int)&stk_11c + 1),group);
  strcat((char *)&stk_11c,"]");
  pu8 = &stk_11c;
  do {
    pu7 = pu8;
    pu8 = pu7 + 1;
    u5 = *pu7 + 0xfefefeff & (*pu7 ^ 0xffffffff);
    u6 = u5 & 0x80808080;
  } while (u6 == 0);
  if ((u5 & 0x8080) == 0) {
    u6 = u6 >> 0x10;
    pu8 = (uint32_t *)((int)pu7 + 6);
  }
  if (0 < *(int *)(tp + 0x2c)) {
    group2 = 0;
    do {
      i3 = strimatchlen(*(int *)(i1 + *(int *)(i2 + group2 * 4) * 4),(int)&stk_11c,
                           (int)((int)pu8 +
                                ((-3 - (uint32_t)CARRY1((uint8_t)u6,(uint8_t)u6)) - (int)&stk_11c)));
      if (i3 != 0) {
        u4 = TPGroupSeekIdx(tp,group2);
        return u4;
      }
      group2 = group2 + 1;
    } while (group2 < *(int *)(tp + 0x2c));
  }
  return 0xffffffff;
}
#undef stk_11c

/* TPGroupSeekIdx @ 0x0807be50, 85 bytes
 *
 * Makes group number `group` current: sets the group index, puts the cursor
 * on its first line and sets the end-of-group flag if the group is empty.
 * Returns the byte offset of the first line, or -1 if `group` is out of
 * range.
 *
 * Parameters:
 *   tp           int
 *   group        int
 *
 * Called by: SiSceneReadTP, TPGroupSeek
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPGroupSeekIdx(int tp,int group)

{
  char *pc1;
  uint32_t u2;
  int i3;
  
  if ((group < 0) || (*(int *)(tp + 0x2c) <= group)) {
    u2 = 0xffffffff;
  }
  else {
    *(int *)(tp + 0x18) = group;
    i3 = *(int *)(*(int *)(tp + 0x28) + group * 4) + 1;
    *(int *)(tp + 0xc) = i3;
    *(int *)(tp + 0x14) = i3;
    pc1 = *(char **)(*(int *)(tp + 0x20) + i3 * 4);
    *(uint32_t *)(tp + 0x1c) = 0;
    *(int *)(tp + 0x10) = (int)pc1 - *(int *)(tp + 4);
    if ((*(int *)(tp + 0x24) <= i3) || (*pc1 == '[')) {
      *(uint32_t *)(tp + 0x1c) = 1;
    }
    u2 = *(uint32_t *)(tp + 0x10);
  }
  return u2;
}

/* TPGroupReset @ 0x0807beb0, 61 bytes
 *
 * Moves the cursor back to the first line of the current group and clears or
 * sets the end-of-group flag.
 *
 * Parameters:
 *   tp           int
 *
 * Called by: FindCharacters, SCtrlParseElem, TPDeleteAllLines,
 *            TPGetGroupText
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void TPGroupReset(int tp)

{
  char *pc1;
  int i2;
  
  i2 = *(int *)(*(int *)(tp + 0x28) + *(int *)(tp + 0x18) * 4) + 1;
  *(int *)(tp + 0xc) = i2;
  *(int *)(tp + 0x14) = i2;
  pc1 = *(char **)(*(int *)(tp + 0x20) + i2 * 4);
  *(uint32_t *)(tp + 0x1c) = 0;
  *(int *)(tp + 0x10) = (int)pc1 - *(int *)(tp + 4);
  if ((*(int *)(tp + 0x24) <= i2) || (*pc1 == '[')) {
    *(uint32_t *)(tp + 0x1c) = 1;
  }
  return;
}

/* TPGroupScanFirst @ 0x0807bef0, 16 bytes
 *
 * Starts a scan over all groups: sets the current group to -1 and returns
 * TPGroupScanNext(tp).
 *
 * Parameters:
 *   tp           int
 *
 * Calls: TPGroupScanNext
 * Called by: AnimRCReadFileTP, BGArrayReadCtrlTP, BGArrayReadTP,
 *            GameLoadFightData, GameLoadSystem, PlayerCMDLoadTP,
 *            SctrlAddFileTP, SctrlReadFileTP, SiSceneReadTP,
 *            TPGroupMatchCount
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPGroupScanFirst(int tp)

{
  uint32_t u1;
  
  *(uint32_t *)(tp + 0x18) = 0xffffffff;
  u1 = TPGroupScanNext(tp);
  return u1;
}

/* TPGroupScanNext @ 0x0807bf00, 98 bytes
 *
 * Moves to the next group, puts the cursor on its first line and returns the
 * group's header line (for example "[Begin Action 200]"). Returns NULL after
 * the last group. Loaders use the pair to visit every group of a file (AIR
 * actions, background elements, state definitions).
 *
 * Parameters:
 *   tp           int
 *
 * Called by: AnimRCReadFileTP, BGArrayReadCtrlTP, BGArrayReadTP,
 *            GameLoadFightData, GameLoadSystem, PlayerCMDLoadTP,
 *            SCtrlParseState, SctrlAddFileTP, SctrlReadFileTP,
 *            SiSceneReadTP, TPGroupMatchCount, TPGroupScanFirst
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPGroupScanNext(int tp)

{
  char *pc1;
  uint32_t u2;
  int i3;
  int i4;
  
  i4 = *(int *)(tp + 0x18) + 1;
  *(int *)(tp + 0x18) = i4;
  if (i4 < *(int *)(tp + 0x2c)) {
    i3 = *(int *)(*(int *)(tp + 0x28) + i4 * 4) + 1;
    *(int *)(tp + 0xc) = i3;
    *(int *)(tp + 0x14) = i3;
    pc1 = *(char **)(*(int *)(tp + 0x20) + i3 * 4);
    *(uint32_t *)(tp + 0x1c) = 0;
    *(int *)(tp + 0x10) = (int)pc1 - *(int *)(tp + 4);
    u2 = *(uint32_t *)
             (*(int *)(tp + 0x20) + *(int *)(*(int *)(tp + 0x28) + i4 * 4) * 4);
    if (i3 < *(int *)(tp + 0x24)) {
      if (*pc1 == '[') {
        *(uint32_t *)(tp + 0x1c) = 1;
      }
    }
    else {
      *(uint32_t *)(tp + 0x1c) = 1;
    }
  }
  else {
    u2 = 0;
  }
  return u2;
}

/* TPGroupMatchCount @ 0x0807bf70, 79 bytes
 *
 * Counts the groups whose name (the header after '[') matches `group` by
 * strimatch, i.e. case-insensitively by prefix ("begin action " counts every
 * "[Begin Action n]"). The current group is restored afterwards. Used to
 * size arrays before loading, such as the number of animations or background
 * elements.
 *
 * Parameters:
 *   tp           int
 *   group        char *
 *
 * Calls: TPGroupScanFirst, strimatch, TPGroupScanNext
 * Called by: AnimRCReadFileTP, BGArrayReadCtrlTP, BGArrayReadTP,
 *            PlayerCMDLoadTP, SctrlAddFileTP, SctrlReadFileTP,
 *            SiSceneReadTP
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPGroupMatchCount(int tp,char *group)

{
  uint32_t u1;
  int i2;
  int i3;
  
  i3 = 0;
  u1 = *(uint32_t *)(tp + 0x18);
  i2 = TPGroupScanFirst(tp);
  while (i2 != 0) {
    i2 = strimatch((char *)(i2 + 1),group);
    if (i2 != 0) {
      i3 = i3 + 1;
    }
    i2 = TPGroupScanNext(tp);
  }
  *(uint32_t *)(tp + 0x18) = u1;
  return i3;
}

/* TPGetLineNo @ 0x0807bfc0, 24 bytes
 *
 * TPGetLineNo_Skip with no skipping: the line number of the first `keyname`
 * line in the current group.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * Calls: TPGetLineNo_Skip
 * Called by: TPPrintf
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPGetLineNo(int arg1,char *arg2)

{
  int i1;
  
  i1 = TPGetLineNo_Skip(arg1,arg2,0);
  return i1;
}

/* TPGetLineNo_Skip @ 0x0807bfe0, 184 bytes
 *
 * Returns the line number of the (skip+1)-th line in the current group whose
 * key is `keyname`, or -1 if there is none. The key must be followed by a
 * blank or '='; the comparison obeys TPCaseSensitive.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *   arg3         int
 *
 * Calls: strimatchlen, strmatchlen, TPisspace
 * C library: strlen
 * Called by: TPGetLineNo, TPPrintf_Skip
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPGetLineNo_Skip(int arg1,char *arg2,int arg3)

{
  char c1;
  int i2;
  char *pc3;
  size_t s4;
  int i5;
  int i6;
  
  s4 = strlen(arg2);
  i2 = *(int *)(arg1 + 0x20);
  i6 = *(int *)(arg1 + 0xc);
  if (i6 < *(int *)(arg1 + 0x24)) {
    pc3 = *(char **)(i2 + i6 * 4);
    c1 = *pc3;
    while (c1 != '[') {
      if (TPCaseSensitive == 0) {
        i5 = strimatchlen((int)pc3,(int)arg2,s4);
      }
      else {
        i5 = strmatchlen((int)pc3,(int)arg2,s4);
      }
      if ((i5 != 0) && ((i5 = TPisspace(pc3[s4]), i5 != 0 || (pc3[s4] == '=')))
         ) {
        if (arg3 < 1) {
          return i6;
        }
        arg3 = arg3 + -1;
      }
      i6 = i6 + 1;
      if (*(int *)(arg1 + 0x24) <= i6) {
        return -1;
      }
      pc3 = *(char **)(i2 + i6 * 4);
      c1 = *pc3;
    }
  }
  return -1;
}

/* TPGetValue @ 0x0807c0a0, 281 bytes
 *
 * Finds `keyname` in the current group and returns a pointer to its value:
 * the text after '=', without leading blanks. Returns NULL when the key is
 * missing. The search starts at the group's first line, so the order of keys
 * does not matter. The key comparison is case-insensitive unless
 * TPCaseSensitive is set, and the key must be followed by a blank or '='.
 * After a match, the cursor is left on the next line (TPGetValueNext
 * continues from there).
 *
 * This is the routine behind every "key = value" read in the engine.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *
 * Calls: strimatchlen, strmatchlen, TPisspace
 * C library: strlen
 * Called by: BGArrayReadCtrlTP, BGArrayReadTP, FindCharacters,
 *            FontReadFilePtr_0_01, GameBGLoad, GameConfigRead,
 *            GameLoadFightData, GameLoadStage, GameLoadSystem,
 *            GameStgInitFightData, GetQuotedString, ItoP_TPConstF,
 *            ItoP_TPConstI, PlayerCMDLoadTP, PlayerDefLoadPtr,
 *            PlayerDefLoadZip, ... (36 callers)
 *
 * Elecbyte file: src/lib/txtparse.c
 */
char * TPGetValue(int tp,char *keyname)

{
  char c1;
  int i2;
  char *pc3;
  size_t s4;
  int i5;
  int i6;
  
  s4 = strlen(keyname);
  i2 = *(int *)(tp + 0x20);
  i6 = *(int *)(tp + 0xc);
  if (i6 < *(int *)(tp + 0x24)) {
    pc3 = *(char **)(i2 + i6 * 4);
    c1 = *pc3;
    while (c1 != '[') {
      if (TPCaseSensitive == 0) {
        i5 = strimatchlen((int)pc3,(int)keyname,s4);
      }
      else {
        i5 = strmatchlen((int)pc3,(int)keyname,s4);
      }
      if ((i5 != 0) && ((i5 = TPisspace(pc3[s4]), i5 != 0 || (pc3[s4] == '=')))
         ) {
        i6 = i6 + 1;
        *(int *)(tp + 0x14) = i6;
        if ((*(int *)(tp + 0x24) <= i6) ||
           (**(char **)(*(int *)(tp + 0x20) + i6 * 4) == '[')) {
          *(uint32_t *)(tp + 0x1c) = 1;
        }
        for (; (c1 = pc3[s4], c1 != '=' && (c1 != '\0')); s4 = s4 + 1) {
        }
        if (c1 == '\0') goto L_0807c171;
        do {
          s4 = s4 + 1;
L_0807c171:
          i6 = TPisspace(pc3[s4]);
        } while ((i6 != 0) && (pc3[s4] != '\0'));
        return pc3 + s4;
      }
      i6 = i6 + 1;
      if (*(int *)(tp + 0x24) <= i6) {
        return (char *)0x0;
      }
      pc3 = *(char **)(i2 + i6 * 4);
      c1 = *pc3;
    }
  }
  return (char *)0x0;
}

/* TPSeekValue @ 0x0807c1c0, 77 bytes
 *
 * Moves the cursor onto the line of `keyname` in the current group, without
 * consuming it. Returns the line number, or -1 when the key is missing (the
 * cursor is then left unchanged). With a NULL key it seeks to the end of the
 * group (TPSeekEog). Not called in this build.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *
 * Calls: TPSeekEog, TPGetValue
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPSeekValue(int tp,char *keyname)

{
  uint32_t u1;
  uint32_t u2;
  int i3;
  char *value;
  
  u1 = *(uint32_t *)(tp + 0x1c);
  u2 = *(uint32_t *)(tp + 0x14);
  if (keyname == (char *)0x0) {
    i3 = TPSeekEog(tp);
    return i3;
  }
  value = TPGetValue(tp,keyname);
  if (value == (char *)0x0) {
    *(uint32_t *)(tp + 0x1c) = u1;
    *(uint32_t *)(tp + 0x14) = u2;
    i3 = -1;
  }
  else {
    *(uint32_t *)(tp + 0x1c) = u1;
    i3 = *(int *)(tp + 0x14) + -1;
    *(int *)(tp + 0x14) = i3;
  }
  return i3;
}

/* TPSeekEog @ 0x0807c210, 53 bytes
 *
 * Moves the cursor to the end of the current group (the next "[" line) and
 * sets the end-of-group flag. Returns the new cursor.
 *
 * Parameters:
 *   tp           int
 *
 * Called by: TPSeekValue
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPSeekEog(int tp)

{
  int entry_EDX;
  
  if (*(int *)(tp + 0x1c) == 0) {
    entry_EDX = *(int *)(tp + 0x14);
    *(uint32_t *)(tp + 0x1c) = 1;
    while ((entry_EDX < *(int *)(tp + 0x24) &&
           (**(char **)(*(int *)(tp + 0x20) + entry_EDX * 4) != '['))) {
      entry_EDX = entry_EDX + 1;
    }
  }
  *(int *)(tp + 0x14) = entry_EDX;
  return entry_EDX;
}

/* TPGetValueNewStr @ 0x0807c250, 82 bytes
 *
 * TPGetValue that returns a malloc'd copy of the value (caller frees it), or
 * NULL. Not called in this build.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *
 * Calls: TPGetValue
 * C library: strlen, malloc, strcpy
 *
 * Elecbyte file: src/lib/txtparse.c
 */
char * TPGetValueNewStr(int tp,char *keyname)

{
  char *value;
  size_t s1;
  char *dest;
  
  value = TPGetValue(tp,keyname);
  if (value != (char *)0x0) {
    s1 = strlen(value);
    dest = malloc(s1 + 1);
    if (dest != (char *)0x0) {
      strcpy(dest,value);
      return dest;
    }
  }
  return (char *)0x0;
}

/* TPGetValueNext @ 0x0807c2b0, 297 bytes
 *
 * Like TPGetValue, but searches from the cursor instead of the start of the
 * group. Used where a key may appear several times in one group, such as the
 * trigger1/trigger2... lines of a state controller (SCtrlParseElem).
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *
 * Calls: strimatchlen, strmatchlen, TPisspace
 * C library: strlen
 * Called by: SCtrlParseElem
 *
 * Elecbyte file: src/lib/txtparse.c
 */
char * TPGetValueNext(int tp,char *keyname)

{
  char c1;
  char *pc2;
  size_t s3;
  int i4;
  int i5;
  int i6;
  
  s3 = strlen(keyname);
  i5 = *(int *)(tp + 0x20);
  if ((*(int *)(tp + 0x1c) == 0) &&
     (i6 = *(int *)(tp + 0x14), i6 < *(int *)(tp + 0x24))) {
    pc2 = *(char **)(i5 + i6 * 4);
    c1 = *pc2;
    while (c1 != '[') {
      if (TPCaseSensitive == 0) {
        i4 = strimatchlen((int)pc2,(int)keyname,s3);
      }
      else {
        i4 = strmatchlen((int)pc2,(int)keyname,s3);
      }
      if ((i4 != 0) && ((i4 = TPisspace(pc2[s3]), i4 != 0 || (pc2[s3] == '=')))
         ) {
        i6 = i6 + 1;
        *(int *)(tp + 0x14) = i6;
        if ((*(int *)(tp + 0x24) <= i6) ||
           (**(char **)(*(int *)(tp + 0x20) + i6 * 4) == '[')) {
          *(uint32_t *)(tp + 0x1c) = 1;
        }
        for (; (c1 = pc2[s3], c1 != '=' && (c1 != '\0')); s3 = s3 + 1) {
        }
        if (c1 == '\0') goto L_0807c391;
        do {
          s3 = s3 + 1;
L_0807c391:
          i5 = TPisspace(pc2[s3]);
        } while ((i5 != 0) && (pc2[s3] != '\0'));
        return pc2 + s3;
      }
      i6 = i6 + 1;
      if (*(int *)(tp + 0x24) <= i6) {
        return (char *)0x0;
      }
      pc2 = *(char **)(i5 + i6 * 4);
      c1 = *pc2;
    }
  }
  return (char *)0x0;
}

/* TPGetValueFloat @ 0x0807c3e0, 58 bytes
 *
 * Reads `keyname` as a float (strtod) into `out`. Returns true if the key
 * exists; `out` is left unchanged otherwise.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   out          float *
 *
 * Calls: TPGetValue
 * C library: __strtod_internal
 * Called by: BGArrayReadCtrlTP, BGArrayReadTP, GameConfigRead,
 *            GameLoadStage, PlayerCNSLoadTP
 *
 * Elecbyte file: src/lib/txtparse.c
 */
bool TPGetValueFloat(int tp,char *keyname,float *out)

{
  char *value;
  float80 l2;
  
  value = TPGetValue(tp,keyname);
  if (value != (char *)0x0) {
    l2 = __strtod_internal((int)value,(int *)0x0,0);
    *out = (float)l2;
  }
  return value != (char *)0x0;
}

/* TPGetValueInt @ 0x0807c420, 59 bytes
 *
 * Reads `keyname` as a decimal int (strtol) into `out`. Returns true if the
 * key exists; `out` is left unchanged otherwise.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   out          uint32_t *
 *
 * Calls: TPGetValue
 * C library: __strtol_internal
 * Called by: BGArrayReadCtrlTP, BGArrayReadTP, BGMParse,
 *            CharselReadConfig, FontReadFilePtr_0_01, GameConfigRead,
 *            GameLoadFightData, GameLoadOptions, GameLoadStage,
 *            GameLoadSystem, PlayerCMDLoadTP, PlayerCNSLoadTP,
 *            PlayerLoadKeys, SCtrlParseElem, SiSceneReadTP, SysExplodParse
 *
 * Elecbyte file: src/lib/txtparse.c
 */
bool TPGetValueInt(int tp,char *keyname,uint32_t *out)

{
  uint8_t *value;
  uint32_t u2;
  
  value = (uint8_t *)TPGetValue(tp,keyname);
  if (value != (uint8_t *)0x0) {
    u2 = __strtol_internal(value,(uint32_t *)0x0,10,0);
    *out = u2;
  }
  return value != (uint8_t *)0x0;
}

/* TPScanf @ 0x0807c460, 56 bytes
 *
 * Reads `keyname` and parses its value with vsscanf(value, fmt, ...).
 * Returns the number of fields converted, or 0 when the key is missing. Used
 * for multi-value keys such as "pos = 10, 20".
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   fmt          char *
 *
 * Calls: TPGetValue
 * C library: vsscanf
 * Called by: BGArrayReadCtrlTP, BGArrayReadTP, BGMParse,
 *            CharselReadConfig, FindCharacters, FontReadFilePtr_0_01,
 *            GameConfigRead, GameLoadFightData, GameLoadOptions,
 *            GameLoadStage, GameLoadSystem, ParseSndGI, PlayerCNSLoadTP,
 *            PlayerDefLoadPtr, PlayerDefLoadZip, QuickVSSetup, ... (18
 *            callers)
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 */
int TPScanf(int tp,char *keyname,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  char *value;
  int i1;
  
  value = TPGetValue(tp,keyname);
  if (value == (char *)0x0) {
    i1 = 0;
  }
  else {
    i1 = vsscanf(value,fmt,va);
  }
  return i1;
}

/* TPAccessReset @ 0x0807c4a0, 42 bytes
 *
 * Puts the cursor on the first line of the current group and clears the
 * end-of-group flag.
 *
 * Parameters:
 *   tp           int
 *
 * Called by: AnimRCReadFileTP, TPAccessFirstLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void TPAccessReset(int tp)

{
  int i1;
  
  i1 = *(int *)(*(int *)(tp + 0x28) + *(int *)(tp + 0x18) * 4) + 1;
  *(int *)(tp + 0xc) = i1;
  *(int *)(tp + 0x14) = i1;
  *(int *)(tp + 0x10) = *(int *)(*(int *)(tp + 0x20) + i1 * 4) - *(int *)(tp + 4);
  *(uint32_t *)(tp + 0x1c) = 0;
  return;
}

/* TPAccessFirstLine @ 0x0807c4d0, 27 bytes
 *
 * TPAccessReset, then returns the first line of the group
 * (TPAccessNextLine).
 *
 * Parameters:
 *   tp           int
 *
 * Calls: TPAccessReset, TPAccessNextLine
 * Called by: AnimRCReadFileTP, FontReadFilePtr_0_01, SCtrlParseElemType,
 *            TPGetGroupText
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPAccessFirstLine(int tp)

{
  uint32_t line;
  
  TPAccessReset(tp);
  line = TPAccessNextLine(tp);
  return line;
}

/* TPReaccessCurLine @ 0x0807c4f0, 24 bytes
 *
 * Returns the line before the cursor again, i.e. the line last returned by
 * TPAccessNextLine. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPReaccessCurLine(int arg1)

{
  if (*(int *)(arg1 + 0x14) == 0) {
    return 0;
  }
  return *(uint32_t *)(*(int *)(arg1 + 0x20) + -4 + *(int *)(arg1 + 0x14) * 4);
}

/* TPAccessNextLine @ 0x0807c510, 53 bytes
 *
 * Returns the line under the cursor and advances. Returns NULL when the
 * end-of-group flag is set. Used to read groups line by line: animation
 * frames, font maps, storyboard text.
 *
 * Parameters:
 *   tp           int
 *
 * Called by: AnimRCReadFileTP, ClsnParseLine, FindCharacters,
 *            FontReadFilePtr_0_01, SCtrlParseElemType, TPAccessFirstLine,
 *            TPGetGroupText, TPGetLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPAccessNextLine(int tp)

{
  uint32_t u1;
  int i2;
  
  if (*(int *)(tp + 0x1c) == 0) {
    u1 = *(uint32_t *)(*(int *)(tp + 0x20) + *(int *)(tp + 0x14) * 4);
    i2 = *(int *)(tp + 0x14) + 1;
    *(int *)(tp + 0x14) = i2;
    if ((*(int *)(tp + 0x24) <= i2) ||
       (**(char **)(*(int *)(tp + 0x20) + i2 * 4) == '[')) {
      *(uint32_t *)(tp + 0x1c) = 1;
    }
  }
  else {
    u1 = 0;
  }
  return u1;
}

/* TPAccessPrevLine @ 0x0807c550, 34 bytes
 *
 * Moves the cursor back one line, clears the end-of-group flag and returns
 * that line. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPAccessPrevLine(int arg1)

{
  int i1;
  
  i1 = *(int *)(arg1 + 0x14) + -1;
  *(uint32_t *)(arg1 + 0x1c) = 0;
  if (i1 == *(int *)(arg1 + 0xc)) {
    return 0;
  }
  *(int *)(arg1 + 0x14) = i1;
  return *(uint32_t *)(*(int *)(arg1 + 0x20) + -4 + i1 * 4);
}

/* TPGetLine @ 0x0807c580, 54 bytes
 *
 * Copies the next line of the current group into a 256-byte buffer. Returns
 * true on success, false at the end of the group. Not called in this build.
 *
 * Parameters:
 *   tp           int
 *   arg2         char *
 *
 * Calls: TPAccessNextLine, strgetto
 *
 * Elecbyte file: src/lib/txtparse.c
 */
bool TPGetLine(int tp,char *arg2)

{
  char *line;
  
  line = (char *)TPAccessNextLine(tp);
  if (line != (char *)0x0) {
    strgetto(arg2,line,0xff,'\0');
  }
  return line != (char *)0x0;
}

/* TPGetGroupText @ 0x0807c5c0, 162 bytes
 *
 * Copies the lines of the current group into a buffer of `size` bytes,
 * separated by '\n', truncating at the size. Returns the number of
 * characters written. Not called in this build.
 *
 * Parameters:
 *   tp           int
 *   arg2         int
 *   arg3         int
 *
 * Calls: TPGroupReset, TPAccessFirstLine, TPAccessNextLine
 * C library: strlen, strncpy, strcpy
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPGetGroupText(int tp,int arg2,int arg3)

{
  char *line;
  size_t n;
  int i2;
  
  i2 = 0;
  TPGroupReset(tp);
  line = (char *)TPAccessFirstLine(tp);
  do {
    if (line == (char *)0x0) break;
    n = strlen(line);
    if (arg3 < (int)(n + i2)) {
      n = arg3 - i2;
      strncpy((char *)(arg2 + i2),line,n);
    }
    else {
      strcpy((char *)(arg2 + i2),line);
    }
    i2 = i2 + n;
    line = (char *)TPAccessNextLine(tp);
    if ((line != (char *)0x0) && (i2 < arg3)) {
      *(uint8_t *)(i2 + arg2) = 10;
      i2 = i2 + 1;
    }
  } while (i2 <= arg3);
  *(uint8_t *)(i2 + arg2) = 0;
  return i2;
}

/* TPWLineNo @ 0x0807c670, 112 bytes
 *
 * For a TP object opened for write, converts kept-line number `line` into
 * the matching raw-line number. At the end of a group it returns the raw
 * line after the group's last non-blank raw line, so that inserted lines
 * land inside the group. Returns -1 if out of range or without write-back
 * data.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: TPDeleteLine, TPInsertLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
int TPWLineNo(int arg1,int arg2)

{
  char c1;
  int *pi2;
  int i3;
  int i4;
  
  pi2 = *(int **)(arg1 + 0x30);
  if (((arg2 < 0) || (*(int *)(arg1 + 0x24) <= arg2)) || (pi2 == (int *)0x0)) {
    i4 = -1;
  }
  else if ((arg2 < 1) || (*(int *)(arg1 + 0x1c) == 0)) {
    i4 = *(int *)(*pi2 + arg2 * 4);
  }
  else {
    i3 = *pi2;
    i4 = *(int *)(i3 + -4 + arg2 * 4) + 1;
    if ((i4 < pi2[2]) && (i4 < *(int *)(i3 + arg2 * 4))) {
      c1 = **(char **)(pi2[1] + i4 * 4);
      while (((c1 != '\0' && (i4 = i4 + 1, i4 < pi2[2])) &&
             (i4 < *(int *)(i3 + arg2 * 4)))) {
        c1 = **(char **)(pi2[1] + i4 * 4);
      }
    }
  }
  return i4;
}

/* TPGroupRename @ 0x0807c6e0, 354 bytes
 *
 * Replaces the header line of the current group with the printf-formatted
 * text, keeping any comment on that line (write-back files only). Returns -1
 * without write-back data. Not called in this build.
 *
 * Parameters:
 *   tp           int
 *   fmt          char *
 *
 * C library: vsprintf, malloc, strcpy, free
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x830 bytes,
 *       3 variables), because their address is taken.
 */
uint32_t TPGroupRename(int tp,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  char c1;
  int *pi2;
  int i3;
  char *ptr;
  uint32_t u4;
  char *dest;
  int i5;
  int i6;
  unsigned char frame[0x830] __attribute__((aligned(16)));
#define stk_824 (*(int *)(frame + 0xc))
#define stk_81c (*(char (*)[1024])(frame + 0x14))
#define stk_41c (*(char (*)[1036])(frame + 0x414))
  
  pi2 = *(int **)(tp + 0x30);
  stk_824 = -1;
  if (pi2 == (int *)0x0) {
    u4 = 0xffffffff;
  }
  else {
    vsprintf(stk_41c,fmt,va);
    i3 = *(int *)(*pi2 + (*(int *)(tp + 0xc) + -1) * 4);
    i5 = 0;
    ptr = *(char **)(pi2[1] + i3 * 4);
    i6 = stk_824;
    if (*ptr != '\0') {
      if (*ptr == ';') {
        stk_824 = 0;
        i6 = stk_824;
      }
      else {
        do {
          i5 = i5 + 1;
          i6 = stk_824;
          if (ptr[i5] == '\0') break;
          i6 = i5;
        } while (ptr[i5] != ';');
      }
    }
    stk_824 = i6;
    i6 = 1;
    stk_81c[0] = '[';
    i5 = 0;
    while (stk_41c[0] != '\0') {
      stk_81c[i6] = stk_41c[i5];
      i6 = i6 + 1;
      stk_41c[0] = stk_41c[i5 + 1];
      i5 = i5 + 1;
    }
    stk_81c[i6] = ']';
    i6 = i6 + 1;
    if (stk_824 != -1) {
      for (; i6 < stk_824; i6 = i6 + 1) {
        stk_81c[i6] = ' ';
      }
      c1 = ptr[stk_824];
      while (c1 != '\0') {
        stk_824 = stk_824 + 1;
        stk_81c[i6] = c1;
        i6 = i6 + 1;
        c1 = ptr[stk_824];
      }
    }
    stk_81c[i6] = '\0';
    dest = malloc(i6 + 1);
    if (dest == (char *)0x0) {
      u4 = 0;
    }
    else {
      strcpy(dest,stk_81c);
      free(ptr);
      *(char **)(pi2[1] + i3 * 4) = dest;
      u4 = 1;
    }
  }
  return u4;
}
#undef stk_824
#undef stk_81c
#undef stk_41c

/* TPPrintf @ 0x0807c850, 418 bytes
 *
 * Rewrites the value of `keyname` in the current group with the
 * printf-formatted text. The raw line keeps its key, its spacing up to the
 * value, and any trailing comment (write-back files only). Returns 0 on
 * success, -1 if the key or the write-back data is missing. GameSaveOptions
 * and PlayerSaveKeys use it to save mugen.cfg.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   fmt          char *
 *
 * Calls: TPGetLineNo, TPisspace
 * C library: vsprintf, malloc, strcpy, free
 * Called by: GameConfigRead, GameSaveOptions, PlayerSaveKeys
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x830 bytes,
 *       3 variables), because their address is taken.
 */
uint32_t TPPrintf(int tp,char *keyname,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  int *pi1;
  char *ptr;
  char c2;
  uint32_t u3;
  int i4;
  int i5;
  char *dest;
  int i6;
  int i2;
  unsigned char frame[0x830] __attribute__((aligned(16)));
#define stk_824 (*(int *)(frame + 0xc))
#define stk_81c (*(char (*)[1024])(frame + 0x14))
#define stk_41c (*(char (*)[1036])(frame + 0x414))
  
  pi1 = *(int **)(tp + 0x30);
  stk_824 = -1;
  if (pi1 == (int *)0x0) {
L_0807c874:
    u3 = 0xffffffff;
  }
  else {
    vsprintf(stk_41c,fmt,va);
    i4 = TPGetLineNo(tp,keyname);
    if (i4 != -1) {
      i6 = 0;
      i4 = *(int *)(*pi1 + i4 * 4);
      ptr = *(char **)(pi1[1] + i4 * 4);
      c2 = *ptr;
      while (c2 != '=') {
        if (c2 == '\0') goto L_0807c874;
        i6 = i6 + 1;
        c2 = ptr[i6];
      }
      do {
        i6 = i6 + 1;
        i5 = TPisspace(ptr[i6]);
        i2 = i6;
        if (i5 == 0) {
          c2 = ptr[i6];
          goto L_0807c91b;
        }
      } while (ptr[i6] != '\0');
      c2 = '\0';
L_0807c91b:
      while ((i5 = stk_824, c2 != '\0' && (i5 = i2, c2 != ';'))) {
        c2 = ptr[i2 + 1];
        i2 = i2 + 1;
      }
      stk_824 = i5;
      i2 = 0;
      if (0 < i6) {
        do {
          stk_81c[i2] = ptr[i2];
          i2 = i2 + 1;
        } while (i2 < i6);
      }
      i6 = 0;
      while (stk_41c[0] != '\0') {
        stk_81c[i2] = stk_41c[i6];
        i2 = i2 + 1;
        stk_41c[0] = stk_41c[i6 + 1];
        i6 = i6 + 1;
      }
      if (stk_824 != -1) {
        for (; i2 < stk_824; i2 = i2 + 1) {
          stk_81c[i2] = ' ';
        }
        c2 = ptr[stk_824];
        while (c2 != '\0') {
          stk_824 = stk_824 + 1;
          stk_81c[i2] = c2;
          i2 = i2 + 1;
          c2 = ptr[stk_824];
        }
      }
      stk_81c[i2] = '\0';
      dest = malloc(i2 + 1);
      if (dest != (char *)0x0) {
        strcpy(dest,stk_81c);
        free(ptr);
        *(char **)(pi1[1] + i4 * 4) = dest;
        return 1;
      }
    }
    u3 = 0;
  }
  return u3;
}
#undef stk_824
#undef stk_81c
#undef stk_41c

/* TPPrintf_Skip @ 0x0807ca00, 434 bytes
 *
 * TPPrintf for the (skip+1)-th occurrence of `keyname` in the group. Not
 * called in this build.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   skip         int
 *   fmt          char *
 *
 * Calls: TPGetLineNo_Skip, TPisspace
 * C library: vsprintf, malloc, strcpy, free
 *
 * Elecbyte file: src/lib/txtparse.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x830 bytes,
 *       3 variables), because their address is taken.
 */
uint32_t TPPrintf_Skip(int tp,char *keyname,int skip,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  int *pi1;
  char *ptr;
  char c2;
  uint32_t u3;
  int i4;
  int i5;
  char *dest;
  int i6;
  int i2;
  unsigned char frame[0x830] __attribute__((aligned(16)));
#define stk_824 (*(int *)(frame + 0xc))
#define stk_81c (*(char (*)[1024])(frame + 0x14))
#define stk_41c (*(char (*)[1036])(frame + 0x414))
  
  pi1 = *(int **)(tp + 0x30);
  stk_824 = -1;
  if (pi1 == (int *)0x0) {
L_0807ca24:
    u3 = 0xffffffff;
  }
  else {
    vsprintf(stk_41c,fmt,va);
    i4 = TPGetLineNo_Skip(tp,keyname,skip);
    if (i4 != -1) {
      i6 = 0;
      i4 = *(int *)(*pi1 + i4 * 4);
      ptr = *(char **)(pi1[1] + i4 * 4);
      c2 = *ptr;
      while (c2 != '=') {
        if (c2 == '\0') goto L_0807ca24;
        i6 = i6 + 1;
        c2 = ptr[i6];
      }
      do {
        i6 = i6 + 1;
        i5 = TPisspace(ptr[i6]);
        i2 = i6;
        if (i5 == 0) {
          c2 = ptr[i6];
          goto L_0807cadb;
        }
      } while (ptr[i6] != '\0');
      c2 = '\0';
L_0807cadb:
      while ((i5 = stk_824, c2 != '\0' && (i5 = i2, c2 != ';'))) {
        c2 = ptr[i2 + 1];
        i2 = i2 + 1;
      }
      stk_824 = i5;
      i2 = 0;
      if (0 < i6) {
        do {
          stk_81c[i2] = ptr[i2];
          i2 = i2 + 1;
        } while (i2 < i6);
      }
      i6 = 0;
      while (stk_41c[0] != '\0') {
        stk_81c[i2] = stk_41c[i6];
        i2 = i2 + 1;
        stk_41c[0] = stk_41c[i6 + 1];
        i6 = i6 + 1;
      }
      if (stk_824 != -1) {
        for (; i2 < stk_824; i2 = i2 + 1) {
          stk_81c[i2] = ' ';
        }
        c2 = ptr[stk_824];
        while (c2 != '\0') {
          stk_824 = stk_824 + 1;
          stk_81c[i2] = c2;
          i2 = i2 + 1;
          c2 = ptr[stk_824];
        }
      }
      stk_81c[i2] = '\0';
      dest = malloc(i2 + 1);
      if (dest != (char *)0x0) {
        strcpy(dest,stk_81c);
        free(ptr);
        *(char **)(pi1[1] + i4 * 4) = dest;
        return 1;
      }
    }
    u3 = 0;
  }
  return u3;
}
#undef stk_824
#undef stk_81c
#undef stk_41c

/* TPInsertLine @ 0x0807cbc0, 218 bytes
 *
 * Inserts a copy of `text` as a raw line at the cursor position (write-back
 * files only), growing the raw-line table when needed. Not called in this
 * build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * Calls: TPWLineNo, TPWExpandLinespace
 * C library: strlen, malloc, strcpy, free
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPInsertLine(int arg1,char *arg2)

{
  int *pi1;
  int i2;
  size_t s3;
  char *dest;
  int i4;
  uint32_t *pu5;
  int i6;
  
  pi1 = *(int **)(arg1 + 0x30);
  i6 = *(int *)(arg1 + 0x14);
  if ((pi1 != (int *)0x0) && (i2 = TPWLineNo(arg1,i6), i2 != -1)) {
    s3 = strlen(arg2);
    dest = malloc(s3 + 1);
    if (dest != (char *)0x0) {
      strcpy(dest,arg2);
      i4 = TPWExpandLinespace(arg1);
      if (i4 != 0) {
        i4 = pi1[2];
        if (i2 < i4) {
          pu5 = (uint32_t *)(i4 * 4 + pi1[1]);
          do {
            i4 = i4 + -1;
            *pu5 = pu5[-1];
            pu5 = pu5 + -1;
          } while (i2 < i4);
          i4 = pi1[2];
        }
        pi1[2] = i4 + 1;
        *(char **)(pi1[1] + i2 * 4) = dest;
        if (i6 < *(int *)(arg1 + 0x24)) {
          i2 = *pi1;
          do {
            *(int *)(i2 + i6 * 4) = *(int *)(i2 + i6 * 4) + 1;
            i6 = i6 + 1;
          } while (i6 < *(int *)(arg1 + 0x24));
        }
        return 1;
      }
      free(dest);
    }
  }
  return 0;
}

/* TPDeleteLine @ 0x0807cca0, 176 bytes
 *
 * Removes the raw line at the cursor (write-back files only), frees it and
 * renumbers the following lines. Used by TPDeleteAllLines.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: TPWLineNo
 * C library: free
 * Called by: TPDeleteAllLines
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPDeleteLine(int arg1)

{
  int *pi1;
  int i2;
  void *ptr;
  int i3;
  int i4;
  int i5;
  
  pi1 = *(int **)(arg1 + 0x30);
  i4 = *(int *)(arg1 + 0x14);
  if (((pi1 != (int *)0x0) && (*(int *)(arg1 + 0x1c) == 0)) &&
     (i3 = TPWLineNo(arg1,i4), i3 != -1)) {
    i4 = i4 + 1;
    if (i4 < *(int *)(arg1 + 0x24)) {
      i2 = *pi1;
      do {
        *(int *)(i2 + i4 * 4) = *(int *)(i2 + i4 * 4) + -1;
        i4 = i4 + 1;
      } while (i4 < *(int *)(arg1 + 0x24));
    }
    ptr = *(void **)(pi1[1] + i3 * 4);
    if (ptr != (void *)0x0) {
      free(ptr);
    }
    i4 = pi1[2];
    if (i3 < i4 + -1) {
      i2 = pi1[1];
      i5 = i3;
      do {
        *(uint32_t *)(i2 + i5 * 4) = *(uint32_t *)(i2 + 4 + i5 * 4);
        i5 = i5 + 1;
      } while (i5 < i4 + -1);
      i4 = pi1[2];
    }
    pi1[2] = i4 + -1;
    i4 = *(int *)(arg1 + 0x14) + 1;
    *(int *)(arg1 + 0x14) = i4;
    if ((pi1[2] <= i3) || (**(char **)(*(int *)(arg1 + 0x20) + i4 * 4) == '[')) {
      *(uint32_t *)(arg1 + 0x1c) = 1;
    }
    return 1;
  }
  return 0;
}

/* TPDeleteAllLines @ 0x0807cd50, 37 bytes
 *
 * Deletes every line of the current group (write-back files only). Not
 * called in this build.
 *
 * Parameters:
 *   tp           int
 *
 * Calls: TPGroupReset, TPDeleteLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void TPDeleteAllLines(int tp)

{
  int i1;
  
  TPGroupReset(tp);
  do {
    i1 = TPDeleteLine(tp);
  } while (i1 != 0);
  return;
}

/* TPWExpandLinespace @ 0x0807cd80, 72 bytes
 *
 * Makes room for one more raw line in the write-back table (realloc by 64
 * entries when full). Returns 0 if realloc fails.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: realloc
 * Called by: TPInsertLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPWExpandLinespace(int arg1)

{
  int i1;
  void *pv2;
  
  i1 = *(int *)(arg1 + 0x30);
  if (*(int *)(i1 + 0xc) <= *(int *)(i1 + 8) + 1) {
    pv2 = realloc(*(void **)(i1 + 4),*(int *)(i1 + 0xc) * 4 + 0x100);
    if (pv2 == (void *)0x0) {
      return 0;
    }
    *(void **)(i1 + 4) = pv2;
    *(int *)(i1 + 0xc) = *(int *)(i1 + 0xc) + 0x40;
  }
  return 1;
}

/* strgetto @ 0x0807cdd0, 65 bytes
 *
 * Copies characters from `src` to `dest` until `stop`, the end of `src` or
 * `max` characters, then NUL-terminates `dest`. The stop character itself is
 * copied.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         char *
 *   arg3         int
 *   arg4         char
 *
 * Called by: TPGetLine
 *
 * Elecbyte file: src/lib/txtparse.c
 */
void strgetto(char *arg1,char *arg2,int arg3,char arg4)

{
  char c1;
  int i2;
  
  i2 = 0;
  if ((0 < arg3) && (*arg2 != '\0')) {
    *arg1 = *arg2;
    c1 = *arg2;
    while (((c1 != arg4 && (i2 = i2 + 1, i2 < arg3)) && (arg2[i2] != '\0')))
    {
      arg1[i2] = arg2[i2];
      c1 = arg2[i2];
    }
  }
  arg1[i2] = '\0';
  return;
}

/* TPisspace @ 0x0807ce20, 27 bytes
 *
 * The parser's blank test: true for space, tab and carriage return (not
 * newline).
 *
 * Parameters:
 *   ch           char
 *
 * Called by: TPGetLineNo_Skip, TPGetValue, TPGetValueNext, TPPrintf,
 *            TPPrintf_Skip, TPReadFilePtr, TPReadMFPtr
 *
 * Elecbyte file: src/lib/txtparse.c
 */
uint32_t TPisspace(char ch)

{
  uint32_t u1;
  
  u1 = 0;
  if (((ch == ' ') || (ch == '\t')) || (ch == '\r')) {
    u1 = 1;
  }
  return u1;
}

