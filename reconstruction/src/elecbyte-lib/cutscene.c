/*
 * cutscene.c -- storyboards
 * Loads and plays storyboard .def files (intro, logo, endings): scenes with
 * backgrounds, layered animations, fades and music.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/cutscene.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SceneReadFile @ 0x0804f9e0, 180 bytes
 *
 * Opens a storyboard .def file (intro, ending, select-screen story) and
 * reads it (SceneReadTP). Errors: "TXTPARSE error opening <file>" or
 * "Cutscene error reading <file>".
 *
 * Parameters:
 *   filename     char *
 *   arg2         char *
 *   arg3         int
 *   arg4         int
 *
 * Calls: TPReadFile, splitdirfile, SceneReadTP, TPFree
 * C library: strcat
 * Called by: PlayCutscene
 * Messages:
 *   "\nTXTPARSE error opening "
 *   "\nCutscene error reading "
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1010 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t * SceneReadFile(char *filename,char *arg2,int arg3,int arg4)

{
  char *tp;
  uint32_t *pu2;
  unsigned char frame[0x1010] __attribute__((aligned(16)));
#define dirname (*(char (*)[4096])(frame + 0x4))
  
  tp = TPReadFile(filename);
  if (tp == (char *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,filename);
    pu2 = (uint32_t *)0x0;
  }
  else {
    splitdirfile(filename,dirname,(char *)0x0);
    pu2 = SceneReadTP(tp,dirname,arg2,arg3,arg4);
    if (pu2 == (uint32_t *)0x0) {
      strcat((char *)ErrorMessage,"\nCutscene error reading ");
      strcat((char *)ErrorMessage,filename);
    }
    TPFree((uint32_t *)tp);
  }
  return pu2;
}
#undef dirname

/* SceneReadTP @ 0x0804faa0, 169 bytes
 *
 * Creates a storyboard from its "[SceneDef]" group and scenes
 * (SiSceneReadTP). Error: "Can't access group %s". Returns the storyboard or
 * NULL.
 *
 * Parameters:
 *   tp           char *
 *   dirname      char *
 *   arg3         char *
 *   arg4         int
 *   arg5         int
 *
 * Calls: TPGroupSeek, ecalloc, SiSceneReadTP, SceneFree
 * C library: strcpy, strcat, sprintf
 * Called by: SceneReadFile
 * Messages:
 *   "Can\'t access group %s"
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t * SceneReadTP(char *tp,char *dirname,char *arg3,int arg4,int arg5)

{
  int i1;
  uint32_t *mem;
  int *pi3;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define group (*(char (*)[80])(frame + 0x4))
  
  strcpy(group,arg3);
  strcat(group,"def");
  i1 = TPGroupSeek((int)tp,group);
  if (i1 == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",group,arg3);
  }
  else {
    mem = (uint32_t *)ecalloc(1,8);
    if (mem == (uint32_t *)0x0) {
      return (uint32_t *)0x0;
    }
    *mem = 0;
    pi3 = SiSceneReadTP(tp,dirname,arg3,arg4,arg5);
    mem[1] = pi3;
    if (pi3 != (int *)0x0) {
      return mem;
    }
    SceneFree(mem);
  }
  return (uint32_t *)0x0;
}
#undef group

/* SiSceneReadTP @ 0x0804fb50, 2140 bytes
 *
 * Reads a storyboard: "spr", "startscene" and the "[Scene n]" groups. Each
 * scene has "end.time" (required: "end.time not specified"),
 * "fadein.time/col", "fadeout.time/col", "clearcolor", "bg.name" (background
 * set), "layerall.pos", "bgm" with "bgm.loop", "window" and layers
 * ("layer%i.anim", "layer%i.offset", "layer%i.starttime"). Animations come
 * from the "[Begin Action n]" groups of the same file.
 *
 * Parameters:
 *   tp           char *
 *   dirname      char *
 *   arg3         char *
 *   arg4         int
 *   arg5         int
 *
 * Text keys read: "spr", "startscene", "bgm", "bgm.loop", "fadein.time",
 *                 "fadein.col", "fadeout.time", "fadeout.col",
 *                 "clearcolor", "window", "bg.name", "layerall.pos",
 *                 "end.time"
 * Calls: TPGroupSeek, ecalloc, TPGetValue, joindirfile, SpriteReadFile,
 *        TPGetValueInt, TPGroupScanFirst, strimatch, TPGroupScanNext,
 *        AnimRCReadFileTP, TPGroupMatchCount, ArrayNew, TPScanf,
 *        BGArrayReadTP, TPGroupSeekIdx, ArrayAdd, AnimNew, SiSceneReset,
 *        SiSceneFree
 * C library: strcpy, strcat, sprintf, memcpy, strlen, strncpy
 * Called by: SceneReadTP
 * Messages:
 *   "Can\'t access group %s"
 *   "Error: sff file must be specified"
 *   "Error reading sprite %s"
 *   "begin action "
 *   "\nError loading anim."
 *   "Need at least one [%s] type act"
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x1370 bytes,
 *       38 variables), because their address is taken.
 */
int * SiSceneReadTP(char *tp,char *dirname,char *arg3,int arg4,int arg5)

{
  bool b1;
  int count;
  int *mem;
  char *value;
  int *sprites;
  size_t s6;
  int count2;
  uint32_t *array;
  char *group;
  char *value2;
  uint32_t stale_var;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t u11;
  uint32_t stale_ECX_01;
  char *stale_EDX;
  char *stale_EDX_00;
  size_t s12;
  int i2;
  char *pc14;
  unsigned char frame[0x1370] __attribute__((aligned(16)));
#define stk_1368 (*(int *)(frame + 0x8))
#define stk_1364 (*(int *)(frame + 0xc))
#define group2 (*(char (*)[48])(frame + 0x14))
#define group3 (*(char (*)[48])(frame + 0x44))
#define keyname (*(char (*)[4096])(frame + 0x74))
#define stk_2fc (*(uint32_t (*)[38])(frame + 0x1074))
#define stk_264 (*(uint32_t *)(frame + 0x110c))
#define stk_260 (*(uint32_t *)(frame + 0x1110))
#define stk_25c (*(uint32_t *)(frame + 0x1114))
#define stk_258 (*(uint32_t *)(frame + 0x1118))
#define stk_254 (*(int *)(frame + 0x111c))
#define stk_250 (*(uint32_t *)(frame + 0x1120))
#define stk_24c (*(int *)(frame + 0x1124))
#define stk_248 (*(uint32_t *)(frame + 0x1128))
#define stk_1a0 (*(uint32_t *)(frame + 0x11d0))
#define stk_19c (*(uint32_t *)(frame + 0x11d4))
#define stk_18c (*(char (*)[128])(frame + 0x11e4))
#define stk_10c (*(uint32_t (*)[3])(frame + 0x1264))
#define stk_100 (*(uint32_t *)(frame + 0x1270))
#define stk_fc (*(uint32_t *)(frame + 0x1274))
#define stk_f8 (*(uint32_t *)(frame + 0x1278))
#define stk_f4 (*(uint32_t *)(frame + 0x127c))
#define stk_f0 (*(uint32_t *)(frame + 0x1280))
#define stk_ec (*(uint32_t *)(frame + 0x1284))
#define stk_e8 (*(uint32_t *)(frame + 0x1288))
#define stk_e4 (*(int *)(frame + 0x128c))
#define stk_e0 (*(uint32_t *)(frame + 0x1290))
#define stk_dc (*(int *)(frame + 0x1294))
#define stk_d8 (*(uint32_t *)(frame + 0x1298))
#define stk_d4 (*(char **)(frame + 0x129c))
#define stk_d0 (*(uint32_t *)(frame + 0x12a0))
#define buf_cc (*(uint8_t (*)[4])(frame + 0x12a4))
#define buf_c8 (*(uint8_t (*)[4])(frame + 0x12a8))
#define buf_c4 (*(uint32_t (*)[33])(frame + 0x12ac))
#define stk_40 (*(uint32_t (*)[4])(frame + 0x1330))
#define stk_30 (*(uint32_t *)(frame + 0x1340))
#define stk_2c (*(uint32_t *)(frame + 0x1344))
#define stk_28 (*(uint32_t (*)[6])(frame + 0x1348))
  
  group = keyname;
  strcpy(group,arg3);
  strcat(group,"def");
  count = TPGroupSeek((int)tp,group);
  if (count == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",group,stale_ECX);
    return (int *)0x0;
  }
  mem = (int *)ecalloc(1,0x10e8);
  if (mem == (int *)0x0) {
    return (int *)0x0;
  }
  strcpy((char *)(mem + 6),dirname);
  count = TPGroupSeek((int)tp,group);
  if (count == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",group,arg4);
  }
  else {
    value = TPGetValue((int)tp,"spr");
    if (value == (char *)0x0) {
      if (arg4 == 0) {
        memcpy(ErrorMessage,"Error: sff file must be specified",0x22);
        goto L_0804fe88;
      }
      mem[2] = arg4;
      mem[3] = 0;
    }
    else {
      joindirfile(group,dirname,value);
      sprites = SpriteReadFile(group);
      mem[2] = (int)sprites;
      if (sprites == (int *)0x0) {
        sprintf((char *)ErrorMessage,"Error reading sprite %s",value,group);
        goto L_0804fe88;
      }
      mem[3] = 1;
    }
    TPGetValueInt((int)tp,"startscene",(uint32_t *)(mem + 0x439));
    if (arg5 == 0) {
      count = TPGroupScanFirst((int)tp);
      value = stale_EDX;
      do {
        count2 = strimatch((char *)(count + 1),"begin action ");
        group = value;
        if (count2 != 0) break;
        count = TPGroupScanNext((int)tp);
        value = stale_EDX_00;
      } while (count != 0);
      if (count != 0) {
        sprites = AnimRCReadFileTP((int)tp);
        mem[4] = (int)sprites;
        if (sprites == (int *)0x0) {
          strcat((char *)ErrorMessage,"\nError loading anim.");
          goto L_0804fe88;
        }
        mem[5] = 1;
      }
    }
    else {
      mem[4] = arg5;
      mem[5] = 0;
    }
    s6 = strlen(arg3);
    sprintf(group3,"%s ",arg3,group);
    group = group2;
    sprintf(group2,"%s]",arg3);
    count = TPGroupMatchCount((int)tp,group3);
    count2 = TPGroupMatchCount((int)tp,group2);
    s12 = count + count2;
    if (s12 == 0) {
      sprintf((char *)ErrorMessage,"Need at least one [%s] type act",arg3,group);
    }
    else {
      mem[1] = s12;
      array = ArrayNew(s12,0x168,0);
      *mem = (int)array;
      if (array != (uint32_t *)0x0) {
        stk_1364 = TPGroupScanFirst((int)tp);
        stk_1368 = 0;
        if (0 < (int)s12) {
          do {
            while ((*(int *)(tp + 0x18) != *(int *)(tp + 0x2c) &&
                   ((count = strimatch((char *)(stk_1364 + 1),arg3), count == 0 ||
                    (((*(uint8_t *)(__ctype_b + 1 + *(char *)(s6 + 1 + stk_1364) * 2) & 0x20) == 0
                     && (*(char *)(s6 + 1 + stk_1364) != ']'))))))) {
              stk_1364 = TPGroupScanNext((int)tp);
            }
            if (0 < stk_1368) {
              group = stk_18c;
              array = stk_2fc;
              for (count = 0x5a; count != 0; count = count + -1) {
                *array = *(uint32_t *)group;
                group = group + 4;
                array = array + 1;
              }
            }
            group = stk_18c;
            for (count = 0x5a; count != 0; count = count + -1) {
              group[0] = '\0';
              group[1] = '\0';
              group[2] = '\0';
              group[3] = '\0';
              group = group + 4;
            }
            count = 9;
            array = stk_40;
            do {
              *array = 0xffffffff;
              array = array + -4;
              count = count + -1;
            } while (-1 < count);
            stk_10c[0] = 1;
            if (stk_1368 == 0) {
              stk_f4 = 0xffffffff;
            }
            else {
              stk_f4 = stk_264;
              stk_f0 = stk_260;
              stk_ec = stk_25c;
              stk_e4 = stk_254;
              stk_e0 = stk_250;
              stk_dc = stk_24c;
              stk_d8 = stk_248;
              stk_e8 = stk_258;
              stk_30 = stk_1a0;
              stk_2c = stk_19c;
            }
            group = TPGetValue((int)tp,"bgm");
            if (group != (char *)0x0) {
              stk_10c[1] = 1;
              strncpy(stk_18c,group,0x7f);
            }
            TPGetValueInt((int)tp,"bgm.loop",stk_10c);
            TPGetValueInt((int)tp,"fadein.time",stk_10c + 2);
            TPGetValueInt((int)tp,"fadein.col",&stk_100);
            TPGetValueInt((int)tp,"fadeout.time",&stk_fc);
            TPGetValueInt((int)tp,"fadeout.col",&stk_f8);
            TPScanf((int)tp,"clearcolor","%i,%i,%i",&stk_f4,&stk_f0,&stk_ec);
            count = TPScanf((int)tp,"window","%i,%i,%i,%i",&stk_e4,&stk_e0,&stk_dc,
                            &stk_d8);
            if (count == 4) {
              stk_e8 = 1;
            }
            if ((stk_e4 == -1) || (stk_dc < stk_e4)) {
              stk_e8 = 0;
            }
            group = "bg.name";
            value = tp;
            pc14 = tp;
            value2 = TPGetValue((int)tp,"bg.name");
            if ((value2 != (char *)0x0) && (*value2 != '\0')) {
              group = *(char **)(tp + 0x18);
              stk_d4 = BGArrayReadTP(tp,dirname,value2,mem[2],mem[4]);
              if (stk_d4 == (char *)0x0) goto L_0804fe88;
              value = tp;
              pc14 = tp;
              TPGroupSeekIdx((int)tp,(int)group);
            }
            TPScanf((int)tp,"layerall.pos","%i,%i",&stk_30,&stk_2c,group,value,pc14);
            u11 = stale_ECX_00;
            count = 0;
            do {
              sprintf(keyname,"layer%i.anim",count,u11);
              TPGetValueInt((int)tp,keyname,&stk_d0 + count * 4);
              sprintf(keyname,"layer%i.offset",count);
              TPScanf((int)tp,keyname,"%i,%i",buf_cc + count * 0x10,
                      buf_c8 + count * 0x10);
              count2 = count + 1;
              sprintf(keyname,"layer%i.starttime",count);
              TPGetValueInt((int)tp,keyname,buf_c4 + count * 4);
              u11 = stale_ECX_01;
              count = count2;
            } while (count2 < 10);
            b1 = TPGetValueInt((int)tp,"end.time",stk_28);
            if (ZEXT8(b1) == 0) {
              sprintf((char *)ErrorMessage,"\nIn %s: end.time not specified.",stk_1364,stk_18c);
              goto L_0804fe88;
            }
            ArrayAdd(*mem,stk_18c,0,stk_1368);
            stk_1364 = TPGroupScanNext((int)tp);
            stk_1368 = stk_1368 + 1;
          } while (stk_1368 < (int)s12);
        }
        count = 0;
        stk_1368 = 0;
        do {
          i2 = 0;
          count2 = count + 0x1010;
          do {
            array = AnimNew(mem[4],mem[2]);
            *(uint32_t **)((int)mem + count2 + 0xc) = array;
            if (array == (uint32_t *)0x0) goto L_0804fe88;
            i2 = i2 + 1;
            count2 = count2 + 4;
          } while (i2 < 10);
          count = count + 0x60;
          stk_1368 = stk_1368 + 1;
          if (1 < stk_1368) {
            SiSceneReset((int)mem);
            return mem;
          }
        } while( true );
      }
    }
  }
L_0804fe88:
  SiSceneFree(mem);
  return (int *)0x0;
}
#undef stk_1368
#undef stk_1364
#undef group2
#undef group3
#undef keyname
#undef stk_2fc
#undef stk_264
#undef stk_260
#undef stk_25c
#undef stk_258
#undef stk_254
#undef stk_250
#undef stk_24c
#undef stk_248
#undef stk_1a0
#undef stk_19c
#undef stk_18c
#undef stk_10c
#undef stk_100
#undef stk_fc
#undef stk_f8
#undef stk_f4
#undef stk_f0
#undef stk_ec
#undef stk_e8
#undef stk_e4
#undef stk_e0
#undef stk_dc
#undef stk_d8
#undef stk_d4
#undef stk_d0
#undef buf_cc
#undef buf_c8
#undef buf_c4
#undef stk_40
#undef stk_30
#undef stk_2c
#undef stk_28

/* SceneRegisterBGMFn @ 0x080503b0, 34 bytes
 *
 * Registers the callbacks the storyboard uses to start and stop music.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SceneRegisterBGMFn(int *arg1,uint32_t arg2,uint32_t arg3)

{
  int i1;
  
  if (*arg1 == 0) {
    i1 = arg1[1];
    *(uint32_t *)(i1 + 0x10d8) = arg2;
    *(uint32_t *)(i1 + 0x10dc) = arg3;
  }
  return;
}

/* SceneReset @ 0x080503e0, 36 bytes
 *
 * Restarts a storyboard at its start scene (SiSceneReset).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: SiSceneReset
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SceneReset(int *arg1)

{
  if (*arg1 == 0) {
    SiSceneReset(arg1[1]);
    return;
  }
  return;
}

/* SiSceneReset @ 0x08050410, 149 bytes
 *
 * Resets the storyboard clock and current scene.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: SceneReset, SiSceneReadTP
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SiSceneReset(int arg1)

{
  uint32_t *pu1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  
  i4 = 0;
  i6 = 0x1010;
  i3 = 0x1060;
  i5 = arg1;
  do {
    i2 = 9;
    pu1 = (uint32_t *)(i5 + 0x1068);
    do {
      *pu1 = 0;
      pu1 = pu1 + -1;
      i2 = i2 + -1;
    } while (-1 < i2);
    *(uint32_t *)(i3 + 0x10 + arg1) = 0;
    *(uint32_t *)(arg1 + 0xc + i3) = 0;
    i4 = i4 + 1;
    *(uint32_t *)(arg1 + 0x14 + i3) = *(uint32_t *)(arg1 + 0x10e4);
    i3 = i3 + 0x60;
    *(uint32_t *)(i6 + 8 + arg1) = 0;
    i5 = i5 + 0x60;
    i6 = i6 + 0x60;
  } while (i4 < 2);
  *(uint32_t *)(arg1 + 0x1018) = 1;
  if ((*(generic_fn **)(arg1 + 0x10dc) != (generic_fn *)0x0) && (*(int *)(arg1 + 0x10e0) != 0)) {
    (**(generic_fn **)(arg1 + 0x10dc))();
  }
  return;
}

/* SceneUpdate @ 0x080504b0, 41 bytes
 *
 * Advances a storyboard by one tick (SiSceneUpdate). Returns nonzero when it
 * has finished.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: SiSceneUpdate
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/lib/cutscene.c
 */
uint32_t SceneUpdate(int *arg1)

{
  uint32_t u1;
  
  if (*arg1 == 0) {
    u1 = SiSceneUpdate((int *)arg1[1]);
    return u1;
  }
  return 1;
}

/* SiSceneUpdate @ 0x080504e0, 838 bytes
 *
 * Advances the current scene's clock, starts its background music and layer
 * animations at their start times, moves the background, and switches to the
 * next scene when "end.time" is reached. Returns nonzero after the last
 * scene.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayAccessGrpItem, BGArrayReset, joindirfile, AnimChangeAction,
 *        AnimUpdate, BGArrayUpdate, BGArrayMove
 * Called by: SceneUpdate
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1040 bytes,
 *       7 variables), because their address is taken.
 */
uint32_t SiSceneUpdate(int *arg1)

{
  char *item;
  int *pi2;
  uint32_t u3;
  int i4;
  int stale_ECX;
  int stale_ECX_00;
  int *pi5;
  int i2;
  char *pc7;
  unsigned char frame[0x1040] __attribute__((aligned(16)));
#define stk_1038 (*(int **)(frame + 0x8))
#define stk_1034 (*(int **)(frame + 0xc))
#define stk_1030 (*(int **)(frame + 0x10))
#define stk_102c (*(int *)(frame + 0x14))
#define stk_1028 (*(int *)(frame + 0x18))
#define stk_1024 (*(int (*)[2])(frame + 0x1c))
#define stk_101c (*(char (*)[4108])(frame + 0x24))
  
  stk_1024[0] = 0;
  stk_1024[1] = 0;
  do {
    if (((arg1[0x406] == 0) || (stk_1024[0] != 0)) &&
       ((arg1[0x41e] == 0 || (stk_1024[1] != 0)))) {
      i4 = 0x1060;
      stk_1028 = 1;
      do {
        *(int *)((int)arg1 + i4 + 0x10) = *(int *)((int)arg1 + i4 + 0x10) + 1;
        i4 = i4 + 0x60;
        stk_1028 = stk_1028 + -1;
      } while (-1 < stk_1028);
      return 0;
    }
    stk_1034 = arg1 + 0x407;
    stk_1038 = arg1 + 0x406;
    stk_1028 = 0;
    pi5 = arg1 + 0x409;
    stk_1030 = stk_1034;
    do {
      if (pi5[-3] != 0) {
        item = (char *)ArrayAccessGrpItem(*arg1,0,pi5[0x14]);
        if ((*(int *)(item + 0x164) <= pi5[0x12]) && (*(int *)(item + 0x164) != -1)) {
          i4 = pi5[0x14] + 1;
          pi5[0x14] = i4;
          if (arg1[1] <= i4) {
            return 1;
          }
          item = (char *)ArrayAccessGrpItem(*arg1,0,i4);
          pi5[0x12] = 0;
        }
        if (pi5[0x12] == 0) {
          i4 = arg1[4];
          if (i4 != 0) {
            i2 = 9;
            pi2 = stk_1038 + 0x14;
            do {
              *pi2 = 0;
              pi2 = pi2 + -1;
              i2 = i2 + -1;
            } while (-1 < i2);
          }
          if (*(int *)(item + 0xb8) != 0) {
            BGArrayReset(*(int *)(item + 0xb8));
            i4 = stale_ECX;
          }
          if ((((generic_fn *)arg1[0x437] != (generic_fn *)0x0) && (arg1[0x438] != 0)) &&
             (*(int *)(item + 0x84) != 0)) {
            (*(generic_fn *)arg1[0x437])();
            arg1[0x438] = 0;
            i4 = stale_ECX_00;
          }
          if ((arg1[0x436] != 0) && (*item != '\0')) {
            pc7 = item;
            joindirfile(stk_101c,(char *)(arg1 + 6),item);
            (*(generic_fn *)arg1[0x436])(stk_101c,*(uint32_t *)(item + 0x80),pc7,i4);
            arg1[0x438] = 1;
          }
        }
        i4 = 0;
        if (arg1[4] != 0) {
          i4 = 0xb0;
          stk_102c = 0x20;
          i2 = 0;
          do {
            if ((-1 < *(int *)(item + i4 + 0xc)) &&
               (*(int *)(item + i4 + 0x18) == pi5[0x12])) {
              u3 = AnimChangeAction((int *)stk_1034[i2],0,*(int *)(item + i4 + 0xc));
              *(uint32_t *)(stk_102c + (int)pi5) = u3;
            }
            i2 = i2 + 1;
            stk_102c = stk_102c + 4;
            i4 = i4 + 0x10;
          } while (i2 < 10);
          i4 = arg1[4];
        }
        if (i4 != 0) {
          i4 = 0;
          i2 = 9;
          do {
            if (*(int *)((int)stk_1038 + i4 + 0x2c) != 0) {
              AnimUpdate(*(uint32_t **)(i4 + (int)stk_1030));
            }
            i4 = i4 + 4;
            i2 = i2 + -1;
          } while (-1 < i2);
        }
        if (*(int *)(item + 0xb8) != 0) {
          BGArrayUpdate(*(int *)(item + 0xb8));
          BGArrayMove(*(int **)(item + 0xb8),0.0,0.0);
        }
        i4 = pi5[0x12];
        pi5[0x12] = i4 + 1;
        if (((*(int *)(item + 0x164) <= i4 + 1) && (*(int *)(item + 0x164) != -1)) &&
           (arg1[1] <= pi5[0x14] + 1)) {
          return 1;
        }
        stk_1024[stk_1028] = 1;
      }
      stk_1028 = stk_1028 + 1;
      stk_1030 = stk_1030 + 0x18;
      stk_1034 = stk_1034 + 0x18;
      stk_1038 = stk_1038 + 0x18;
      pi5 = pi5 + 0x18;
    } while (stk_1028 < 2);
  } while( true );
}
#undef stk_1038
#undef stk_1034
#undef stk_1030
#undef stk_102c
#undef stk_1028
#undef stk_1024
#undef stk_101c

/* SceneUpdatePal @ 0x08050830, 36 bytes
 *
 * Applies the current scene's fade to the master palette (SiSceneUpdatePal).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: SiSceneUpdatePal
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SceneUpdatePal(int *arg1)

{
  if (*arg1 == 0) {
    SiSceneUpdatePal((int *)arg1[1]);
    return;
  }
  return;
}

/* SiSceneUpdatePal @ 0x08050860, 271 bytes
 *
 * Computes the fade-in/fade-out factor of the current scene from its clock
 * and applies it with MasterPalMul/MasterPalAdd (fade to or from the fade
 * colour).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayAccessGrpItem, MasterPalMul, MasterPalAdd
 * Called by: SceneUpdatePal
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
void SiSceneUpdatePal(int *arg1)

{
  int i1;
  bool b2;
  int item;
  int i4;
  int saved_EBX;
  int *pi5;
  int stk_14;
  
  stk_14 = 1;
  pi5 = arg1;
  do {
    if (pi5[0x406] != 0) {
      b2 = false;
      item = ArrayAccessGrpItem(*arg1,0,pi5[0x41d]);
      i1 = *(int *)(item + 0x88);
      if (pi5[0x41b] + -1 <= i1) {
        if (i1 < 1) {
          saved_EBX = 0x100;
        }
        else {
          saved_EBX = ((pi5[0x41b] + -1) * 0x100) / i1;
          if (0x7f < *(int *)(item + 0x8c)) {
            saved_EBX = 0x200 - saved_EBX;
          }
        }
        b2 = true;
      }
      i1 = *(int *)(item + 0x90);
      i4 = *(int *)(item + 0x164) - pi5[0x41b];
      if ((i4 < i1) && (0 < i1)) {
        saved_EBX = (i4 * 0x100) / i1;
        if (0x7f < *(int *)(item + 0x94)) {
          saved_EBX = 0x200 - saved_EBX;
        }
        b2 = true;
      }
      if (b2) {
        if (saved_EBX < 0x101) {
          MasterPalMul(saved_EBX,saved_EBX,saved_EBX);
        }
        else {
          i1 = saved_EBX + -0x100;
          MasterPalAdd(i1,i1,i1);
        }
      }
    }
    pi5 = pi5 + 0x18;
    stk_14 = stk_14 + -1;
  } while (-1 < stk_14);
  return;
}

/* SceneDraw @ 0x08050970, 36 bytes
 *
 * Draws the current scene (SiSceneDraw).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: SiSceneDraw
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SceneDraw(int *arg1)

{
  if (*arg1 == 0) {
    SiSceneDraw((int *)arg1[1]);
    return;
  }
  return;
}

/* SiSceneDraw @ 0x080509a0, 480 bytes
 *
 * Clears to the scene's clear colour, draws its background set and its layer
 * animations within the scene window.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayAccessGrpItem, W_Cls, W_Define, BGArrayDrawLayer, AnimDraw
 * C library: makecol
 * Called by: SceneDraw
 *
 * Elecbyte file: src/lib/cutscene.c
 */
void SiSceneDraw(int *arg1)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int item;
  uint32_t u6;
  int i7;
  int i8;
  int i5;
  int *stk_30;
  int *stk_2c;
  int *stk_28;
  int stk_24;
  
  i4 = W_y1;
  i3 = W_x2;
  i2 = W_x1;
  i1 = W_y2;
  stk_28 = arg1 + 0x407;
  stk_2c = arg1 + 0x409;
  stk_30 = arg1 + 0x406;
  stk_24 = 1;
  do {
    if (*stk_30 != 0) {
      item = ArrayAccessGrpItem(*arg1,0,stk_30[0x17]);
      if (*(int *)(item + 0x98) != -1) {
        u6 = makecol(*(uint32_t *)(item + 0x98),*(int *)(item + 0x9c),*(int *)(item + 0xa0))
        ;
        W_Cls(u6);
      }
      if (*(int *)(item + 0xa4) != 0) {
        W_Define(*(uint32_t *)(item + 0xa8),*(uint32_t *)(item + 0xac),*(uint32_t *)(item + 0xb0),
                 *(uint32_t *)(item + 0xb4));
      }
      if (*(int *)(item + 0xb8) != 0) {
        BGArrayDrawLayer(*(int *)(item + 0xb8),0);
      }
      if (arg1[4] != 0) {
        i5 = 0;
        i7 = 0x20;
        i8 = 0xb0;
        do {
          if (*(int *)(i7 + (int)stk_2c) != 0) {
            AnimDraw((uint32_t *)stk_28[i5],
                     *(int *)(item + 0x10 + i8) + *(int *)(item + 0x15c),
                     *(int *)(item + 0x14 + i8) + *(int *)(item + 0x160));
          }
          i5 = i5 + 1;
          i8 = i8 + 0x10;
          i7 = i7 + 4;
        } while (i5 < 10);
      }
      if (*(int *)(item + 0xb8) != 0) {
        BGArrayDrawLayer(*(int *)(item + 0xb8),1);
      }
      if (*(int *)(item + 0xa4) != 0) {
        W_Define(i2,i4,i3,i1);
      }
    }
    stk_28 = stk_28 + 0x18;
    stk_2c = stk_2c + 0x18;
    stk_30 = stk_30 + 0x18;
    stk_24 = stk_24 + -1;
  } while (-1 < stk_24);
  return;
}

/* SceneFree @ 0x08050b80, 71 bytes
 *
 * Frees a storyboard (SiSceneFree).
 *
 * Parameters:
 *   arg1         void *
 *
 * Calls: SiSceneFree
 * C library: free
 * Called by: PlayCutscene, SceneReadTP
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void SceneFree(void *arg1)

{
  int i1;
  uint32_t stale_EAX;
  uint32_t saved_EBX;
  
  if (arg1 != (void *)0x0) {
    i1 = *(int *)((int)arg1 + 4);
    if (i1 != 0) {
      if ((*(generic_fn **)(i1 + 0x10dc) != (generic_fn *)0x0) && (*(int *)(i1 + 0x10e0) != 0)) {
        (**(generic_fn **)(i1 + 0x10dc))();
      }
      SiSceneFree(*(int **)((int)arg1 + 4));
    }
    free(arg1);
    return;
  }
  return;
}

/* SiSceneFree @ 0x08050bd0, 248 bytes
 *
 * Frees a storyboard's scenes, background sets, animations, AnimRC and
 * sprite array.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, BGArrayFree, ArrayScanNext, ArrayFree, AnimFree,
 *        AnimRCFree, SpriteArrayFree
 * C library: free
 * Called by: SceneFree, SiSceneReadTP
 *
 * Elecbyte file: src/lib/cutscene.c
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: written by hand from the assembly at 0x08050bd0-0x08050cc8. Reason: same
 *       loop shape as BGArrayFree (entry jump into the middle of the scan loop
 *       at 0x8050bf2 -> 0x8050c17); Ghidra lost the stack depth. Layout
 *       (VERIFIED in the listing): s[0] (0x00) Array of scenes; each scene has a
 *       BG array at +0xb8 0x08 sprites, freed if 0x0c != 0;  0x10 anim RC, freed
 *       if 0x14 != 0 0x101c + i*0x60 + k*4 (i = 0..1, k = 0..9) animations
 *       (address = s + 0xc + 0x1010 + i*0x60 + k*4; the loop counts k down from
 *       9) Ends with a tail call to free(s).
 */
uint32_t SiSceneFree(int *arg1)
{
  int arr, i, k, scene;

  if (arg1 == 0)
    return 0;
  arr = arg1[0];
  scene = arr ? ArrayScanFirst(arr) : 0;                       /* 0x8050bed */
  while (scene != 0) {
    if (*(int *)(scene + 0xb8) != 0)
      BGArrayFree(*(int *)(scene + 0xb8));                     /* 0x8050c06 */
    scene = ArrayScanNext(arr);                                /* 0x8050c12 */
  }
  ArrayFree((void *)arg1[0]);
  for (i = 0; i <= 1; i++)
    for (k = 0; k < 10; k++) {
      void *a = *(void **)((char *)arg1 + 0x101c + i * 0x60 + k * 4);
      if (a != 0)
        AnimFree(a);
    }
  if (arg1[5] != 0)                                         /* 0x14 */
    AnimRCFree((int *)arg1[4]);                             /* 0x10 */
  if (arg1[3] != 0)                                         /* 0x0c */
    SpriteArrayFree((int *)arg1[2]);                        /* 0x08 */
  free(arg1);                                               /* tail call 0x8050cbb */
  return 0;
}

