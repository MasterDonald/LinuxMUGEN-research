/* Prototypes recovered by Ghidra Decompiler Parameter ID for every
 * Elecbyte function and every library function the game calls.
 * Generated; types are decompiler types, not original declarations. */
#pragma once
#include "compat.h"

/* ---- Elecbyte functions ---- */
int * AnimRCReadFile(char *filename); /* 0x08048200 anim-lib.c */
int * AnimRCReadFileTP(int tp); /* 0x08048290 anim-lib.c */
bool AnimElemParseLine(char *arg1,int arg2,uint32_t arg3,int arg4); /* 0x08048830 anim-lib.c */
uint32_t AnimElemProcessFlipFlags(char *arg1); /* 0x080489b0 anim-lib.c */
uint32_t AnimElemProcessDrawFlags(char *arg1,uint32_t *arg2,uint32_t *arg3); /* 0x08048a00 anim-lib.c */
uint32_t AnimRCFree(int *animrc); /* 0x08048b40 anim-lib.c */
uint32_t * AnimNew(uint32_t arg1,uint32_t arg2); /* 0x08048bf0 anim-lib.c */
void AnimSet(uint32_t *anim,uint32_t arg2,uint32_t arg3); /* 0x08048c40 anim-lib.c */
void AnimCopy(uint32_t *anim,uint32_t *src); /* 0x08048c70 anim-lib.c */
uint32_t AnimFree(void *anim); /* 0x08048c90 anim-lib.c */
uint32_t AnimUpdate(uint32_t *anim); /* 0x08048cd0 anim-lib.c */
int AnimUpdateElemptr(uint32_t *anim); /* 0x08048d70 anim-lib.c */
void AnimResetAction(int *anim); /* 0x08048dd0 anim-lib.c */
uint32_t AnimChangeAction(int *anim,int grpno,int actionno); /* 0x08048e10 anim-lib.c */
uint32_t AnimChangeActionTime(int *anim,int grpno,int actionno,int time); /* 0x08048e30 anim-lib.c */
uint32_t AnimChangeActionElem(int *anim,int grpno,int actionno,int elem); /* 0x08048ec0 anim-lib.c */
void AnimDraw(uint32_t *anim,int x,int y); /* 0x08048f60 anim-lib.c */
void AnimDrawFlip(uint32_t *anim,int x,int y,uint32_t flip); /* 0x08048f80 anim-lib.c */
void AnimDrawScale(uint32_t *anim,int x,int y,float xscale,float yscale); /* 0x080491e0 anim-lib.c */
void AnimDrawScaleFlip(uint32_t *anim,int x,int y,float xscale,float yscale,uint32_t flip); /* 0x08049210 anim-lib.c */
void AnimDrawRotateFlip(uint32_t *arg1,int arg2,int arg3,float arg4,float arg5,float arg6,uint32_t arg7); /* 0x08049540 anim-lib.c */
void AnimCurIDGrp(uint32_t *anim); /* 0x08049880 anim-lib.c */
uint32_t AnimCurIDno(uint32_t *anim); /* 0x080498a0 anim-lib.c */
uint32_t AnimCurElemStartTime(uint32_t *anim,int elem); /* 0x080498c0 anim-lib.c */
int AnimElemNo(uint32_t *anim,int offset); /* 0x08049900 anim-lib.c */
void AnimIdxToIDGrp(uint32_t *anim,int index); /* 0x080499a0 anim-lib.c */
void AnimIdxToIDno(uint32_t *anim,int index); /* 0x080499c0 anim-lib.c */
uint32_t AnimGrpNoToIdx(uint32_t *anim,int grpno,int actionno); /* 0x080499e0 anim-lib.c */
uint32_t AnimGetLooptime(uint32_t *anim); /* 0x08049a00 anim-lib.c */
uint32_t AnimGetLooptimeID(uint32_t *anim,int arg2,int arg3); /* 0x08049a20 anim-lib.c */
uint32_t AnimGetLoopstarttime(uint32_t *anim); /* 0x08049a50 anim-lib.c */
uint32_t AnimGetLoopstarttimeID(uint32_t *anim,int arg2,int arg3); /* 0x08049a70 anim-lib.c */
uint32_t AnimGetTime(int anim); /* 0x08049aa0 anim-lib.c */
int AnimGetCorrectedTime(uint32_t *anim); /* 0x08049ab0 anim-lib.c */
uint32_t AnimCurSpriteIdx(int anim); /* 0x08049ae0 anim-lib.c */
uint32_t * PRSprArrayNew(size_t arg1); /* 0x08049af0 anim-lib.c */
uint32_t PRSprArrayFree(uint32_t *arg1); /* 0x08049b70 anim-lib.c */
void PRSprArrayClear(int *arg1); /* 0x08049bb0 anim-lib.c */
uint32_t PRSprAdd(int *arg1,int *arg2); /* 0x08049bc0 anim-lib.c */
void PRSprDraw(int arg1); /* 0x08049c60 anim-lib.c */
void PRSprArrayDraw(int *arg1); /* 0x08049dd0 anim-lib.c */
int PRSprArrayScale(int *arg1,float arg2); /* 0x08049e10 anim-lib.c */
uint8_t AnimPerUpdate(int arg1); /* 0x08049ef0 anim-lib.c */
void AnimPerDraw(int *arg1,int arg2,int arg3); /* 0x08049f20 anim-lib.c */
void AnimPerDrawScale(int *arg1,int arg2,int arg3,float arg4); /* 0x08049f60 anim-lib.c */
uint32_t * AnimPerArrayNew(size_t arg1); /* 0x0804a000 anim-lib.c */
void AnimPerArrayFree(uint32_t *arg1); /* 0x0804a050 anim-lib.c */
uint32_t AnimPerArrayAdd(int *arg1,uint32_t arg2,uint32_t arg3,int arg4,int arg5,uint32_t arg6,uint32_t arg7,uint32_t arg8,uint32_t arg9); /* 0x0804a080 anim-lib.c */
void AnimPerArraySetNo(int *arg1,int arg2,uint32_t arg3); /* 0x0804a150 anim-lib.c */
void AnimPerArrayDelete(int *arg1,int arg2); /* 0x0804a170 anim-lib.c */
void AnimPerArrayClear(int *arg1); /* 0x0804a180 anim-lib.c */
uint32_t AnimPerArrayUpdate(int *arg1); /* 0x0804a190 anim-lib.c */
void AnimPerArrayUpdateGrp(int *arg1,uint32_t arg2); /* 0x0804a1e0 anim-lib.c */
void AnimPerArrayDraw(int *arg1,int arg2,int arg3); /* 0x0804a250 anim-lib.c */
void AnimPerArrayDrawGrp(int *arg1,uint32_t arg2,int arg3,int arg4); /* 0x0804a290 anim-lib.c */
void AnimPerArrayDrawScaleGrp(int *arg1,uint32_t arg2,int arg3,int arg4,float arg5); /* 0x0804a2f0 anim-lib.c */
uint32_t FlipFlagMix(uint32_t arg1,uint32_t arg2); /* 0x0804a350 anim-lib.c */
void AnimDrawSprFlip(int *sprites,int arg2,int arg3,int arg4,int arg5,uint32_t arg6,int arg7,int arg8); /* 0x0804a360 anim-lib.c */
void AnimScaleSpr_S(int *sprites,int arg2,int arg3,int arg4,float arg5,float arg6,uint32_t arg7,int arg8,int arg9); /* 0x0804a650 anim-lib.c */
void AnimRotateSpr(int *sprites,int arg2,int arg3,int arg4,float arg5,float arg6,float arg7,float arg8,float arg9,uint32_t arg10,int arg11,int arg12); /* 0x0804a790 anim-lib.c */
int AlphaMixSrc(int arg1,int arg2); /* 0x0804a900 anim-lib.c */
int AlphaMixDest(int arg1,int arg2); /* 0x0804a910 anim-lib.c */
uint32_t * ArrayNew(size_t capacity,size_t elem_size,uint32_t flags); /* 0x0804a930 array.c */
uint32_t * ArrayCopy(uint32_t *array); /* 0x0804a9c0 array.c */
uint32_t * ArrayCopyOnto(uint32_t *array,uint32_t *arg2); /* 0x0804aa80 array.c */
uint32_t ArrayFree(void *array); /* 0x0804ab00 array.c */
bool ArrayHasSpace(int array); /* 0x0804ab50 array.c */
int ArrayAdd(int array,void *item,uint32_t grpno,uint32_t itemno); /* 0x0804ab60 array.c */
uint32_t ArrayAddUnique(int array,void *item,int grpno,int itemno); /* 0x0804abf0 array.c */
int ArrayAddResize(int array,void *item,uint32_t grpno,uint32_t itemno); /* 0x0804ac50 array.c */
uint32_t ArrayAddUniqueResize(int array,void *item,int grpno,int itemno); /* 0x0804acb0 array.c */
void ArrayDelete(int array,int index); /* 0x0804ad10 array.c */
void ArrayClear(int array); /* 0x0804ada0 array.c */
uint32_t ArrayResize(int array,int capacity); /* 0x0804adf0 array.c */
int ArrayFindEmpty(int array); /* 0x0804aea0 array.c */
int ArrayAccessSafe(int array,int index); /* 0x0804af20 array.c */
uint32_t ArrayFind(int array,int grpno,int itemno); /* 0x0804af40 array.c */
int ArrayAccessGrpItem(int array,int grpno,int itemno); /* 0x0804afe0 array.c */
uint32_t ArrayIdxToGrp(int array,int index); /* 0x0804b020 array.c */
uint32_t ArrayIdxToItem(int array,int index); /* 0x0804b040 array.c */
int ArrayScanFirst(int array); /* 0x0804b060 array.c */
int ArrayScanNext(int array); /* 0x0804b090 array.c */
int ArrayAccessUnsafe(int array,int index); /* 0x0804b0d0 array.c */
void BGArrayReadFile(char *filename,char *group); /* 0x0804b0f0 bg-lib.c */
char * BGArrayReadFileSA(char *filename,char *group,int arg3,int arg4); /* 0x0804b110 bg-lib.c */
char * BGArrayReadTP(char *tp,char *dirname,char *group,int arg4,int arg5); /* 0x0804b1d0 bg-lib.c */
uint32_t BGArrayReadCtrlTP(int arg1,int tp,uint32_t arg3); /* 0x0804bcf0 bg-lib.c */
int BGArrayNew(size_t arg1,uint32_t arg2); /* 0x0804c350 bg-lib.c */
uint32_t BGArrayFree(int bgs); /* 0x0804c3c0 bg-lib.c */
int BGArrayAdd(int arg1,uint32_t arg2,int arg3,uint32_t arg4,uint32_t arg5,uint32_t arg6,uint32_t arg7,uint32_t arg8,uint32_t arg9,uint32_t arg10,uint32_t arg11,int group,int arg13); /* 0x0804c580 bg-lib.c */
int BGArrayAddAnim(int arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5,uint32_t arg6,int arg7); /* 0x0804c6d0 bg-lib.c */
void BGArraySetViewScale(int arg1,uint32_t arg2); /* 0x0804c7b0 bg-lib.c */
void BGArrayMove(int *arg1,float arg2,float arg3); /* 0x0804c7f0 bg-lib.c */
void BGArrayMoveOffset(int *arg1,float arg2,float arg3,int arg4,int arg5); /* 0x0804c810 bg-lib.c */
void BGArrayDraw(int arg1); /* 0x0804ca00 bg-lib.c */
void BGArrayDrawLayer(int bgs,int layer); /* 0x0804ca60 bg-lib.c */
void BGArrayUpdate(int arg1); /* 0x0804cad0 bg-lib.c */
void BGArrayCtrlUpdate(int arg1); /* 0x0804cbb0 bg-lib.c */
void BGArrayReset(int arg1); /* 0x0804ce80 bg-lib.c */
uint32_t BGAccess(int arg1,int arg2); /* 0x0804cf70 bg-lib.c */
int BGAccessID(int arg1,int arg2); /* 0x0804cf90 bg-lib.c */
uint32_t BGParalSetup(int arg1,uint32_t *arg2,int arg3,int arg4,uint32_t arg5,uint32_t arg6,uint32_t arg7,uint32_t arg8); /* 0x0804cfd0 bg-lib.c */
void BGDraw(int arg1,int *arg2); /* 0x0804d1f0 bg-lib.c */
void BGNormalDrawTile(int arg1,int arg2); /* 0x0804d510 bg-lib.c */
void BGAnimDrawTile(uint32_t arg1,int arg2); /* 0x0804d890 bg-lib.c */
void BGParalDraw(int arg1,int arg2); /* 0x0804da00 bg-lib.c */
void BGParalDrawScale(int arg1,int arg2,int arg3); /* 0x0804da20 bg-lib.c */
void BGParalDraw8to16(int arg1,int arg2,int arg3); /* 0x0804dab0 bg-lib.c */
void BGParalDraw8to16_2X(void); /* 0x0804dfb0 bg-lib.c */
void BGParalDraw8to16Flat(int arg1,int arg2,int arg3); /* 0x0804dfc0 bg-lib.c */
void BGParalDraw8to16Flat2X(void); /* 0x0804e420 bg-lib.c */
void BGParalDraw16(void); /* 0x0804e430 bg-lib.c */
int * ClipboardNew(int arg1,size_t arg2); /* 0x0804e440 clipbrd.c */
void ClipboardFree(uint32_t *clipboard); /* 0x0804e4e0 clipbrd.c */
void ClipboardClear(uint32_t *clipboard); /* 0x0804e530 clipbrd.c */
void ClipboardPrint(int *clipboard,char *fmt,...); /* 0x0804e550 clipbrd.c */
size_t ClipboardAppend(int *clipboard,char *fmt,...); /* 0x0804e5a0 clipbrd.c */
uint32_t ClsnArrayNew(size_t arg1); /* 0x0804e660 clsn-lib.c */
uint32_t ClsnArrayFree(void *clsn); /* 0x0804e6c0 clsn-lib.c */
uint32_t * ClsnArrayCopy(uint32_t *arg1); /* 0x0804e700 clsn-lib.c */
int ClsnArrayInstance(int clsn); /* 0x0804e750 clsn-lib.c */
bool ClsnArrayAdd(int clsn,uint32_t *box); /* 0x0804e760 clsn-lib.c */
void ClsnArrayAddRect(int clsn,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5); /* 0x0804e7b0 clsn-lib.c */
void * ClsnParseLine(int arg1,int tp); /* 0x0804e800 clsn-lib.c */
uint32_t ClsnMixDetectRectIndiv(int arg1,int arg2,int arg3,int arg4); /* 0x0804ec00 clsn-lib.c */
uint32_t ClsnMixDetectRect(int arg1,int arg2,int arg3,int arg4); /* 0x0804ec80 clsn-lib.c */
uint32_t ClsnMixDetectRectHFlip1(int arg1,int arg2,int arg3,int arg4); /* 0x0804ed00 clsn-lib.c */
uint32_t ClsnMixDetectRectHFlipAll(int arg1,int arg2,int arg3,int arg4); /* 0x0804eda0 clsn-lib.c */
uint32_t ClsnArrayDetectRect(int *arg1,int *arg2,int arg3,int arg4); /* 0x0804ee40 clsn-lib.c */
uint32_t ClsnArrayDetectRectFlip(int *arg1,int *arg2,int arg3,int arg4,int arg5,int arg6); /* 0x0804eec0 clsn-lib.c */
uint32_t ClsnDetectRect(int arg1,int arg2,int arg3,int arg4); /* 0x0804f030 clsn-lib.c */
uint32_t ClsnDetectRectHFlip1(int arg1,int arg2,int arg3,int arg4); /* 0x0804f080 clsn-lib.c */
uint32_t ClsnDetectRectHFlipAll(int arg1,int arg2,int arg3,int arg4); /* 0x0804f0e0 clsn-lib.c */
void KBUpdateHold(int arg1,int arg2); /* 0x0804f140 cmd-dtct.c */
uint32_t KBFillBuffer(int arg1,int arg2,uint32_t arg3,int arg4); /* 0x0804f160 cmd-dtct.c */
void KBClearCommandValidTimes(uint32_t *arg1); /* 0x0804f3a0 cmd-dtct.c */
void KBClearCommandLastTimes(int arg1); /* 0x0804f3c0 cmd-dtct.c */
void KBCountdownCommandValidTimes(int arg1,char arg2,int arg3); /* 0x0804f3e0 cmd-dtct.c */
bool KBCommandIsValid(int arg1,int arg2); /* 0x0804f420 cmd-dtct.c */
void KBGetCommand(int arg1,int *arg2,int arg3,uint32_t arg4); /* 0x0804f440 cmd-dtct.c */
uint32_t KBGetCommandSpecial(int arg1,int *arg2,int arg3,uint32_t arg4,uint32_t arg5); /* 0x0804f470 cmd-dtct.c */
uint32_t KBGetHoldFlag(int arg1); /* 0x0804f5b0 cmd-dtct.c */
uint32_t KBKeyMap(uint32_t arg1,uint32_t arg2); /* 0x0804f660 cmd-dtct.c */
int KBKeyIndex(int arg1); /* 0x0804f700 cmd-dtct.c */
uint32_t CharMatch(int arg1,int arg2,uint32_t arg3); /* 0x0804f720 cmd-dtct.c */
uint32_t PatternMatch(int arg1,int *arg2,uint32_t *arg3); /* 0x0804f830 cmd-dtct.c */
void KBTimeStuffBuf(int arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0804f960 cmd-dtct.c */
uint32_t * SceneReadFile(char *filename,char *arg2,int arg3,int arg4); /* 0x0804f9e0 cutscene.c */
uint32_t * SceneReadTP(char *tp,char *dirname,char *arg3,int arg4,int arg5); /* 0x0804faa0 cutscene.c */
int * SiSceneReadTP(char *tp,char *dirname,char *arg3,int arg4,int arg5); /* 0x0804fb50 cutscene.c */
void SceneRegisterBGMFn(int *arg1,uint32_t arg2,uint32_t arg3); /* 0x080503b0 cutscene.c */
void SceneReset(int *arg1); /* 0x080503e0 cutscene.c */
void SiSceneReset(int arg1); /* 0x08050410 cutscene.c */
uint32_t SceneUpdate(int *arg1); /* 0x080504b0 cutscene.c */
uint32_t SiSceneUpdate(int *arg1); /* 0x080504e0 cutscene.c */
void SceneUpdatePal(int *arg1); /* 0x08050830 cutscene.c */
void SiSceneUpdatePal(int *arg1); /* 0x08050860 cutscene.c */
void SceneDraw(int *arg1); /* 0x08050970 cutscene.c */
void SiSceneDraw(int *arg1); /* 0x080509a0 cutscene.c */
void SceneFree(void *arg1); /* 0x08050b80 cutscene.c */
uint32_t SiSceneFree(int *arg1); /* 0x08050bd0 cutscene.c */
void * ecalloc(size_t count,size_t size); /* 0x08050cd0 ebcommon.c */
int ErrorSet(int arg1); /* 0x08050d00 ebcommon.c */
int ErrorGet(void); /* 0x08050d10 ebcommon.c */
char * ErrorGetStr(void); /* 0x08050d20 ebcommon.c */
uint32_t CheckExtension(char *arg1); /* 0x08050d70 ebcommon.c */
uint32_t igetw(_IO_FILE *arg1); /* 0x08050f00 ebcommon.c */
uint32_t igetl(_IO_FILE *arg1); /* 0x08050f40 ebcommon.c */
uint32_t strimatch(char *str,char *pattern); /* 0x08050fb0 ebcommon.c */
uint32_t strimatchlen(int str,int pattern,int len); /* 0x08051000 ebcommon.c */
uint32_t strmatchlen(int str,int pattern,int len); /* 0x08051050 ebcommon.c */
void strtoupper(uint8_t *arg1,char *arg2); /* 0x08051090 ebcommon.c */
char * splitdirfile(char *path,char *dirname,char *filename); /* 0x080510c0 ebcommon.c */
char * joindirfile(char *dest,char *dirname,char *filename); /* 0x08051140 ebcommon.c */
uint32_t isabsolutedir(char *path); /* 0x080511c0 ebcommon.c */
long ffilelength(FILE *arg1); /* 0x080511f0 ebcommon.c */
void strcpyslash(int arg1,char *arg2); /* 0x08051230 ebcommon.c */
void IntSwap(uint32_t *arg1,uint32_t *arg2); /* 0x08051260 ebcommon.c */
int IntMin(int arg1,int arg2); /* 0x08051280 ebcommon.c */
int IntMax(int arg1,int arg2); /* 0x08051290 ebcommon.c */
void DebugErrorExit(int arg1); /* 0x080512a0 ebcommon.c */
uint32_t MFgetc(int *mf); /* 0x08051300 ebcommon.c */
char * MFfgets(char *buf,int size,int *mf); /* 0x08051350 ebcommon.c */
size_t MFfread(void *ptr,size_t size,size_t n,int *mf); /* 0x080513f0 ebcommon.c */
int MFfeof(int *mf); /* 0x080514a0 ebcommon.c */
uint32_t * MFfopenFile(char *filename,char *mode2); /* 0x080514e0 ebcommon.c */
uint32_t * MFfopenMem(int data,int size); /* 0x08051540 ebcommon.c */
uint32_t MFzopen(int *mf,char *filename); /* 0x08051580 ebcommon.c */
void MFzclose(int arg1); /* 0x08051650 ebcommon.c */
int * MFfopenZip(char *path,char *filename); /* 0x08051660 ebcommon.c */
uint32_t MFfclose(int *mf); /* 0x080516d0 ebcommon.c */
uint32_t MFfseek(int *mf,int offset,int whence); /* 0x08051770 ebcommon.c */
int MFftell(int *mf); /* 0x08051810 ebcommon.c */
uint32_t MFigetw(int *mf); /* 0x08051850 ebcommon.c */
uint32_t MFigetl(int *mf); /* 0x08051890 ebcommon.c */
int roundfloat(float x); /* 0x08051900 ebcommon.c */
char * _getfileonly(char *arg1); /* 0x08051960 ebcommon.c */
void V_FontDrawLine(char *arg1,int *arg2,int arg3,int arg4,uint32_t arg5); /* 0x08051990 font-lib.c */
void V_FontDrawLineBank(char *arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x08051c00 font-lib.c */
void V_FontDraw(char *text,int *font,int x,int y,uint32_t bank); /* 0x08051fd0 font-lib.c */
void V_FontDrawRight(char *text,int *font,int x,int y,uint32_t bank); /* 0x08052000 font-lib.c */
void V_FontDrawCenter(char *text,int *font,int x,int y,uint32_t bank); /* 0x08052030 font-lib.c */
void V_FontDrawBank(char *arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x08052060 font-lib.c */
uint32_t V_FontDrawRightBank(char *arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x08052090 font-lib.c */
void V_FontDrawCenterBank(char *arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x080520c0 font-lib.c */
void V_FontWrite(int *font,int arg2,int arg3,uint32_t arg4,char *arg5,...); /* 0x080520f0 font-lib.c */
void V_FontWriteRight(int *font,int arg2,int arg3,uint32_t arg4,char *arg5,...); /* 0x08052150 font-lib.c */
void V_FontWriteBank(int *arg1,int arg2,int arg3,int arg4,char *arg5,...); /* 0x080521b0 font-lib.c */
void V_FontDrawAlign_I(char *arg1,int *arg2,int arg3,int arg4,int arg5,uint32_t arg6,int arg7); /* 0x08052210 font-lib.c */
void V_FontDrawAlign(char *arg1,int *arg2,int arg3,int arg4,int arg5,uint32_t arg6); /* 0x08052410 font-lib.c */
uint32_t V_FontDrawAlignBank(char *arg1,int *arg2,int arg3,int arg4,int arg5,int arg6); /* 0x08052440 font-lib.c */
uint32_t FontReadFile(char *filename); /* 0x08052470 font-lib.c */
void * FontReadFilePtr(FILE *arg1); /* 0x080524b0 font-lib.c */
void * FontReadFilePtr_0_01(FILE *arg1,int arg2); /* 0x08052530 font-lib.c */
uint32_t FontFree(void *arg1); /* 0x08052970 font-lib.c */
int FontGetWidth(int arg1,char *arg2); /* 0x080529b0 font-lib.c */
int FontGetWidthQuick(int arg1,char *arg2); /* 0x08052a10 font-lib.c */
bool G_Init(void); /* 0x08052a50 g-lib.c */
uint32_t G_DeInit(void); /* 0x08052aa0 g-lib.c */
uint32_t G_SetRenderMode(int arg1); /* 0x08052b00 g-lib.c */
uint32_t G_SetMode(uint32_t arg1,int arg2,int arg3,int arg4); /* 0x08052b20 g-lib.c */
uint32_t G_MakeColor(uint32_t arg1,int arg2,int arg3); /* 0x08052cc0 g-lib.c */
void G_SetRGBtoBGR(int arg1); /* 0x08052cd0 g-lib.c */
uint32_t G_SetBlitMode(int arg1,uint32_t arg2); /* 0x08052d10 g-lib.c */
void G_PageFlip(void); /* 0x08052e50 g-lib.c */
void VGA_Cls(void); /* 0x08052ea0 g-lib.c */
uint32_t VRetrace(void); /* 0x08052ec0 g-lib.c */
int sgn(uint32_t arg1); /* 0x08052ed0 g-lib.c */
uint32_t GetDrawType(char *arg1,uint32_t *arg2,uint32_t *arg3); /* 0x08052ef0 g-lib.c */
uint32_t Trig_Init(void); /* 0x08052fc0 g-lib.c */
uint32_t Trig_DeInit(void); /* 0x08053080 g-lib.c */
void V_DoubleRes(uint32_t *arg1,int arg2); /* 0x080530b0 g-lib.c */
void V_DoubleResDiag(int *arg1,int arg2); /* 0x08053150 g-lib.c */
void V_DoubleResBlur(int *arg1,int arg2); /* 0x08053410 g-lib.c */
void V_DoubleResLines(uint32_t *arg1,int arg2); /* 0x08053880 g-lib.c */
bool ElecInit(void); /* 0x08053910 init-lib.c */
uint32_t ElecDeInit(void); /* 0x08053960 init-lib.c */
void KBIClearKeyflags(int kbi); /* 0x08053970 inp-kbi.c */
void KBIRefreshKeyflags(int kbi,int keycfg); /* 0x08053990 inp-kbi.c */
void KBISetFlip(int kbi,int flip); /* 0x08053a10 inp-kbi.c */
uint32_t KBIUpdate(int keycfg,int kbi,uint32_t uinp); /* 0x08053ab0 inp-kbi.c */
uint32_t KBIStuffBuf(int kbi,uint32_t code); /* 0x08053af0 inp-kbi.c */
uint32_t KBIStuffBufNoFlip(int kbi,uint32_t code); /* 0x08053b20 inp-kbi.c */
uint32_t KBIGetch(int kbi); /* 0x08053b90 inp-kbi.c */
uint32_t KBIClearAll(int kbi); /* 0x08053bc0 inp-kbi.c */
uint32_t KBIIs6Button(uint32_t uinp,int keycfg); /* 0x08053c00 inp-kbi.c */
bool KBIIs6ButtonOrStart(uint32_t uinp,int keycfg); /* 0x08053c40 inp-kbi.c */
uint32_t KBIKeyMap(int keycfg,uint32_t uinp); /* 0x08053c80 inp-kbi.c */
uint32_t KBIFlippedKey(int kbi,uint32_t key2); /* 0x08053cf0 inp-kbi.c */
uint32_t * KBIMenuGetKey(uint32_t *arg1,int arg2,int arg3,int arg4); /* 0x08053d30 inp-menu.c */
uint32_t UInpKBHook(uint32_t arg1,int arg2); /* 0x08053ee0 input-lb.c */
void UInpPadHook(int arg1,int arg2); /* 0x08053f60 input-lb.c */
uint32_t UInpInit(void); /* 0x08053fe0 input-lb.c */
uint32_t UInpReInit(void); /* 0x08054070 input-lb.c */
void UInpDeInit(void); /* 0x08054090 input-lb.c */
void UInpRefreshFlags(void); /* 0x080540c0 input-lb.c */
uint32_t UInpSetKeyMap(uint32_t *arg1); /* 0x080541a0 input-lb.c */
uint32_t UInpGetKeyMap(uint32_t *arg1); /* 0x080541f0 input-lb.c */
void UInpResetKeyMap(void); /* 0x08054230 input-lb.c */
uint32_t UInpStuff(uint32_t arg1); /* 0x08054260 input-lb.c */
uint32_t UInpGet(void); /* 0x080542a0 input-lb.c */
bool UInpHit(void); /* 0x08054300 input-lb.c */
void UInpBufClear(void); /* 0x08054340 input-lb.c */
uint32_t KBToUInp(uint32_t keycode); /* 0x08054360 input-lb.c */
uint32_t PadToUInp(uint32_t arg1); /* 0x080543c0 input-lb.c */
bool IntCircBufInit(uint32_t *buf,int size); /* 0x08054420 input-lb.c */
uint32_t IntCircBufDeInit(uint32_t *buf); /* 0x08054470 input-lb.c */
bool IntCircBufIsValid(int *buf); /* 0x080544b0 input-lb.c */
void IntCircBufStuff(int *buf,uint32_t value); /* 0x080544c0 input-lb.c */
uint32_t IntCircBufGet(int *buf); /* 0x08054500 input-lb.c */
bool IntCircBufIsEmpty(int buf); /* 0x08054540 input-lb.c */
void IntCircBufClear(int buf); /* 0x08054550 input-lb.c */
uint32_t KBBufferRawHook(uint32_t arg1); /* 0x08054570 kbll-lib.c */
uint32_t KBInit(void); /* 0x08054630 kbll-lib.c */
void KBPoll(void); /* 0x080546b0 kbll-lib.c */
void KBDeInit(void); /* 0x080546c0 kbll-lib.c */
void KBSuspend(void); /* 0x08054700 kbll-lib.c */
void KBResume(void); /* 0x08054710 kbll-lib.c */
void KBRefreshflags(void); /* 0x08054720 kbll-lib.c */
uint32_t KBReset(void); /* 0x08054790 kbll-lib.c */
void KBRepeatSet(int arg1,int arg2); /* 0x080547c0 kbll-lib.c */
uint32_t KBInstallHitHook(int *arg1); /* 0x08054810 kbll-lib.c */
void KBRemoveHitHook(void); /* 0x08054830 kbll-lib.c */
void KBLEDLockSet(int arg1); /* 0x08054840 kbll-lib.c */
void KBLEDSet(uint32_t arg1); /* 0x08054860 kbll-lib.c */
void KBBufferChange(int arg1); /* 0x08054890 kbll-lib.c */
void KBBufferClear(void); /* 0x080548a0 kbll-lib.c */
void KBungetchraw(uint32_t arg1); /* 0x080548d0 kbll-lib.c */
uint32_t KBgetchraw(void); /* 0x08054940 kbll-lib.c */
bool KBkbhit(void); /* 0x080549b0 kbll-lib.c */
int KBRawToChar(int arg1); /* 0x080549d0 kbll-lib.c */
uint8_t KBGetNumLock(void); /* 0x08054a20 kbll-lib.c */
uint8_t KBGetCapsLock(void); /* 0x08054a30 kbll-lib.c */
uint8_t KBGetScrollLock(void); /* 0x08054a40 kbll-lib.c */
uint32_t * KBRawToName(uint8_t arg1); /* 0x08054a50 kbll-lib.c */
void KBInitAllegRemap(void); /* 0x08054a70 kbll-lib.c */
void KBLockVarFunc(void); /* 0x08054e60 kbll-lib.c */
uint32_t KBAllegRemap(int arg1); /* 0x08054e70 kbll-lib.c */
int PadInit(int arg1,int arg2); /* 0x08054e80 pad-lib.c */
uint32_t DeviceInit(void); /* 0x08054f20 pad-lib.c */
uint32_t PadReset(void); /* 0x08054f30 pad-lib.c */
void PadDeInit(void); /* 0x08054f80 pad-lib.c */
int PadPoll(void); /* 0x08054fe0 pad-lib.c */
void PadStuff(uint32_t arg1); /* 0x08055280 pad-lib.c */
uint32_t PadGet(void); /* 0x080552e0 pad-lib.c */
bool PadHit(void); /* 0x08055340 pad-lib.c */
void PadBufClear(void); /* 0x08055370 pad-lib.c */
uint32_t PadInstallHitHook(int *arg1); /* 0x08055390 pad-lib.c */
void PadRemoveHitHook(void); /* 0x080553b0 pad-lib.c */
uint32_t EBPalInit(int *arg1,int arg2,void *arg3,int arg4); /* 0x080553c0 pal-lib.c */
void EBPalDeInit(int arg1); /* 0x08055460 pal-lib.c */
uint32_t EBPalReset(int arg1); /* 0x080554a0 pal-lib.c */
uint32_t EBPalCopy(int *arg1,int *arg2,int arg3); /* 0x080554d0 pal-lib.c */
void EBPalGenerateFPal(int *arg1); /* 0x08055540 pal-lib.c */
void EBPalUpdate(int *arg1); /* 0x08055570 pal-lib.c */
uint32_t EBPalSetDataptr(int *arg1,int arg2,int arg3); /* 0x08055660 pal-lib.c */
uint32_t EBPalGetDataptr(int arg1); /* 0x080556b0 pal-lib.c */
uint32_t EBPalGetNumcols(uint32_t *arg1); /* 0x080556c0 pal-lib.c */
void EBPalMarkDataChanged(int arg1); /* 0x080556d0 pal-lib.c */
void EBPalSettingsReset(uint32_t *arg1); /* 0x080556e0 pal-lib.c */
void EBPalSettingsCopy(uint32_t *arg1,uint32_t *arg2); /* 0x08055710 pal-lib.c */
void EBPalSettingsMix(int *arg1,int *arg2,int *arg3); /* 0x08055730 pal-lib.c */
bool EBPalSettingsAreSame(uint8_t *arg1,uint8_t *arg2); /* 0x080557b0 pal-lib.c */
uint32_t EBPalAdd(int arg1,int arg2,int arg3,int arg4); /* 0x080557e0 pal-lib.c */
void EBPalMul(int arg1,int arg2,int arg3,int arg4); /* 0x08055830 pal-lib.c */
void EBPalInvertAll(int arg1,int arg2); /* 0x08055890 pal-lib.c */
int EBPalColorBal(int arg1,int arg2); /* 0x080558c0 pal-lib.c */
bool MasterPalInit(void); /* 0x080558f0 pal-lib.c */
void MasterPalDeInit(void); /* 0x08055950 pal-lib.c */
void MasterPalProcessChanges(void); /* 0x08055980 pal-lib.c */
void MasterPalFinishedDraw(void); /* 0x080559d0 pal-lib.c */
void MasterPalReset(void); /* 0x08055a00 pal-lib.c */
int * MasterPalAdd(int arg1,int arg2,int arg3); /* 0x08055a30 pal-lib.c */
int * MasterPalMul(int r,int g2,int b); /* 0x08055a70 pal-lib.c */
void MasterPalInvertAll(int arg1); /* 0x08055ab0 pal-lib.c */
void MasterPalColorBal(int arg1); /* 0x08055ad0 pal-lib.c */
uint32_t MasterPalConvertCol16(uint32_t arg1); /* 0x08055af0 pal-lib.c */
void Pal3toPal4(uint8_t *arg1,uint8_t *arg2,int arg3,int arg4); /* 0x08055b80 pal-lib.c */
void Pal4Copy(int arg1,int arg2,int arg3,int arg4); /* 0x08055be0 pal-lib.c */
void Pal4SetSingle(int arg1,int arg2,uint8_t arg3,uint8_t arg4,uint8_t arg5); /* 0x08055c30 pal-lib.c */
void Pal4Contrast(int arg1,int arg2,int arg3,int arg4,int arg5); /* 0x08055c60 pal-lib.c */
void Pal4ContrastRGB(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7); /* 0x08055d00 pal-lib.c */
void Pal4Brightness(int arg1,int arg2,int arg3,int arg4,int arg5); /* 0x08055dd0 pal-lib.c */
void Pal4BrightnessRGB(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7); /* 0x08055ea0 pal-lib.c */
void Pal4ColorBal(int arg1,int arg2,int arg3,int arg4,int arg5); /* 0x08055f90 pal-lib.c */
void Pal4InvertAll(int arg1,int arg2,int arg3,int arg4); /* 0x080560d0 pal-lib.c */
uint32_t Pal4Read3File(int arg1,char *arg2); /* 0x08056120 pal-lib.c */
uint32_t Pal4Read3FilePtr(int arg1,int *mf); /* 0x080561c0 pal-lib.c */
void Pal4ToFpal(int arg1,int arg2,int arg3,int arg4); /* 0x08056260 pal-lib.c */
void Pal4SettingsToFpal(int arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x080562c0 pal-lib.c */
void SndSetMode(int arg1); /* 0x08056760 snd-lib.c */
int GetSndMode(void); /* 0x08056770 snd-lib.c */
void SndSetBufReadMode(uint32_t arg1); /* 0x08056780 snd-lib.c */
int GetNumVoices(void); /* 0x08056790 snd-lib.c */
uint32_t SndInit(uint32_t arg1,uint32_t arg2,int arg3); /* 0x080567a0 snd-lib.c */
void SndDeInit(void); /* 0x08056a30 snd-lib.c */
uint32_t SndDetectWavDevice(int arg1); /* 0x08056ab0 snd-lib.c */
uint32_t SndDetectMidiDevice(int arg1); /* 0x08056af0 snd-lib.c */
void SndSetReverseStereo(int arg1); /* 0x08056b30 snd-lib.c */
void SndFree(void *arg1); /* 0x08056b50 snd-lib.c */
uint32_t SndMidiFree(void *arg1); /* 0x08056b70 snd-lib.c */
uint32_t * SndArrayNew(size_t arg1); /* 0x08056b80 snd-lib.c */
bool SndArrayAdd(int *sounds,uint32_t sample,uint32_t grpno,uint32_t itemno); /* 0x08056bd0 snd-lib.c */
uint32_t SndArrayFree(uint32_t *sounds); /* 0x08056c00 snd-lib.c */
void SndPlay(int *sounds,int grpno,int itemno,uint32_t vol); /* 0x08056c60 snd-lib.c */
void SndPlayLoop(int *arg1,int arg2,int arg3,uint32_t arg4); /* 0x08056cb0 snd-lib.c */
void SndPlayPanFreq(int *arg1,int arg2,int arg3,uint32_t arg4,int arg5,int arg6); /* 0x08056d00 snd-lib.c */
void SndMidiPlay(int *arg1); /* 0x08056d70 snd-lib.c */
void SndMidiPlayLoop(int *arg1,uint32_t arg2,uint32_t arg3); /* 0x08056da0 snd-lib.c */
void SndMidiStop(void); /* 0x08056dc0 snd-lib.c */
void SndMidiPause(void); /* 0x08056de0 snd-lib.c */
void SndMidiResume(void); /* 0x08056e00 snd-lib.c */
void SndMidiSeek(int arg1); /* 0x08056e20 snd-lib.c */
uint32_t SndVoiceReserve(int ch); /* 0x08056e40 snd-lib.c */
uint32_t SndVoiceReserveAuto(void); /* 0x08056ec0 snd-lib.c */
void SndVoiceUnreserve(int ch); /* 0x08056f20 snd-lib.c */
uint32_t SndVoiceUnreserveAll(void); /* 0x08056f80 snd-lib.c */
uint32_t SndVoiceIsReserved(int arg1); /* 0x08056fb0 snd-lib.c */
uint32_t SndVoiceGetVoiceno(int arg1); /* 0x08056fd0 snd-lib.c */
uint32_t SndVoiceIsPlaying(int ch); /* 0x08056ff0 snd-lib.c */
uint32_t SndVoiceIsFree(int ch); /* 0x08057040 snd-lib.c */
int SndVoiceGetFree(void); /* 0x08057090 snd-lib.c */
uint32_t SndVoicePlay(int ch,int *sounds,int grpno,int itemno,int vol); /* 0x080570d0 snd-lib.c */
int SndVoicePrepare(int ch,int *sounds,int grpno,int itemno); /* 0x08057130 snd-lib.c */
uint32_t SndVoiceStart(int ch); /* 0x080571f0 snd-lib.c */
void SndVoiceStop(int ch); /* 0x08057230 snd-lib.c */
uint32_t SndVoiceStopAll(void); /* 0x08057290 snd-lib.c */
void SndVoiceSetVol(int ch,int vol); /* 0x080572c0 snd-lib.c */
int SndVoiceGetVol(int arg1); /* 0x08057300 snd-lib.c */
void SndVoiceSetFreq(int ch,int freq); /* 0x08057340 snd-lib.c */
uint32_t SndVoiceGetFreq(int arg1); /* 0x08057380 snd-lib.c */
void SndVoiceSetPan(int ch,int pan); /* 0x080573c0 snd-lib.c */
int SndVoiceGetPan(int arg1); /* 0x08057410 snd-lib.c */
void SndVoiceSetLoop(int ch,int loop); /* 0x08057460 snd-lib.c */
int * SndVoiceCleanup(void); /* 0x080574b0 snd-lib.c */
int SndIDPlay(int id,int *sounds,int grpno,int itemno,uint32_t vol); /* 0x08057540 snd-lib.c */
int SndIDPrepare(int id,int *sounds,int grpno,int itemno); /* 0x080575a0 snd-lib.c */
void SndIDStart(int id); /* 0x08057600 snd-lib.c */
void SndIDStop(int id); /* 0x08057640 snd-lib.c */
uint32_t SndIDIsPlaying(int id); /* 0x08057690 snd-lib.c */
int SndIDGetChannel(int id); /* 0x080576d0 snd-lib.c */
int SndIDGetChannelOrFree(int id); /* 0x08057720 snd-lib.c */
int * SndReadFile(char *filename); /* 0x08057750 snd-lib.c */
uint32_t * SndMidiReadFile(uint8_t *arg1); /* 0x080578f0 snd-lib.c */
int * SndReadFileWAVPtr(int *mf); /* 0x08057900 snd-lib.c */
int * SndReadFileSNDPtr(int *mf); /* 0x08057be0 snd-lib.c */
uint32_t SndSetVol(uint32_t wav_vol,uint32_t midi_vol); /* 0x08057d00 snd-lib.c */
int SndGetVoiceVol(void); /* 0x08057d60 snd-lib.c */
int SndGetMidiVol(void); /* 0x08057d70 snd-lib.c */
int SndCorrectVolOff(int arg1); /* 0x08057d80 snd-lib.c */
int SndParseWavDevice(char *arg1); /* 0x08057db0 snd-lib.c */
uint32_t * SndWavDeviceString(int arg1); /* 0x08057e40 snd-lib.c */
int SndParseMidiDevice(char *arg1); /* 0x08057e90 snd-lib.c */
uint32_t * SndMidiDeviceString(int arg1); /* 0x08057f20 snd-lib.c */
bool MP3Init(void); /* 0x08057f80 snd-lib.c */
void MP3DeInit(void); /* 0x08057fb0 snd-lib.c */
uint32_t MP3LoadAndPlay(char *arg1,uint32_t arg2); /* 0x08057fd0 snd-lib.c */
void MP3Unload(void); /* 0x08057ff0 snd-lib.c */
void MP3Poll(void); /* 0x08058010 snd-lib.c */
void MP3SetVol(int arg1); /* 0x08058040 snd-lib.c */
uint32_t MP3GetVol(void); /* 0x08058060 snd-lib.c */
void MP3Pause(void); /* 0x08058080 snd-lib.c */
void MP3Resume(void); /* 0x08058090 snd-lib.c */
bool MODInit(int arg1); /* 0x080580a0 snd-lib.c */
void MODDeInit(void); /* 0x080580d0 snd-lib.c */
uint32_t MODLoad(uint8_t *arg1); /* 0x080580f0 snd-lib.c */
uint32_t MODUnload(uint32_t *arg1); /* 0x08058150 snd-lib.c */
void MODPlay(int *arg1,int arg2); /* 0x08058190 snd-lib.c */
void MODStop(void); /* 0x080581c0 snd-lib.c */
void MODPause(void); /* 0x080581e0 snd-lib.c */
void MODResume(void); /* 0x08058200 snd-lib.c */
void MODSetVol(int arg1); /* 0x08058220 snd-lib.c */
uint32_t MODGetVol(void); /* 0x08058240 snd-lib.c */
uint32_t CDAInit(char *arg1); /* 0x08058260 snd-lib.c */
void CDADeInit(void); /* 0x08058290 snd-lib.c */
uint32_t CDAPlay(uint32_t arg1,int arg2); /* 0x080582c0 snd-lib.c */
void CDAStop(void); /* 0x08058340 snd-lib.c */
void CDAPause(void); /* 0x08058380 snd-lib.c */
void CDAResume(void); /* 0x080583c0 snd-lib.c */
void CDAPoll(void); /* 0x08058400 snd-lib.c */
bool CDAIsPlaying(void); /* 0x08058460 snd-lib.c */
bool CDAIsPaused(void); /* 0x08058490 snd-lib.c */
uint32_t CDATrackIsAudio(uint8_t arg1); /* 0x080584c0 snd-lib.c */
uint8_t CDACurrentTrack(void); /* 0x080584e0 snd-lib.c */
bool CDAGetTrackRange(uint32_t *arg1,uint32_t *arg2); /* 0x08058510 snd-lib.c */
void CDASetVol(uint32_t arg1); /* 0x08058550 snd-lib.c */
int CDAGetVol(void); /* 0x08058590 snd-lib.c */
void CDAEject(void); /* 0x080585d0 snd-lib.c */
void CDAClose(void); /* 0x080585f0 snd-lib.c */
bool SpriteInit(int *arg1,int arg2,void *arg3,size_t arg4,int arg5,int arg6,int arg7,int arg8,int arg9,int arg10); /* 0x08058610 spr-lib.c */
void SpriteDeInit(int arg1); /* 0x080586e0 spr-lib.c */
uint32_t SpriteCopy(uint32_t *arg1,uint32_t *arg2,int arg3); /* 0x08058740 spr-lib.c */
int SpriteInitLine(int *arg1,void *arg2); /* 0x08058810 spr-lib.c */
uint32_t SpriteUsePal(int arg1,int arg2,int arg3,int arg4); /* 0x08058880 spr-lib.c */
void SpriteSetAxis(int arg1,uint32_t arg2,uint32_t arg3); /* 0x080588d0 spr-lib.c */
void SpriteArrayNew(void); /* 0x080588f0 spr-lib.c */
uint32_t * SpriteArrayNewSize(size_t arg1,size_t arg2); /* 0x08058900 spr-lib.c */
int * SpriteArrayNewInstance(int *arg1); /* 0x08058960 spr-lib.c */
int * SpriteArrayNewInstanceOnto(int *arg1,int *arg2); /* 0x08058a20 spr-lib.c */
uint32_t SpriteArrayAddSprite(int *arg1,void *arg2,uint32_t arg3,uint32_t arg4); /* 0x08058af0 spr-lib.c */
uint32_t SpriteArrayAddPal(int arg1,void *arg2,uint32_t arg3,uint32_t arg4); /* 0x08058b40 spr-lib.c */
uint32_t SpriteArrayNumImages(int *arg1); /* 0x08058ba0 spr-lib.c */
uint32_t SpriteArrayNumPals(int arg1); /* 0x08058bb0 spr-lib.c */
uint32_t SpriteArrayFree(int *sprites); /* 0x08058bc0 spr-lib.c */
uint32_t SpriteArrayClear(int *arg1); /* 0x08058c90 spr-lib.c */
uint32_t SpriteArrayGetNum(int *sprites,int group,int number); /* 0x08058d70 spr-lib.c */
uint32_t SpriteArrayPalGetNum(int arg1,int arg2,int arg3); /* 0x08058d80 spr-lib.c */
int SpriteArrayAccess(int *sprites,int index); /* 0x08058d90 spr-lib.c */
uint32_t SpriteArrayAccessGrpItem(int *arg1,int arg2,int arg3); /* 0x08058db0 spr-lib.c */
int SpriteArrayPalAccess(int arg1,int arg2); /* 0x08058dc0 spr-lib.c */
void SpriteArrayPalAccessGrpItem(int arg1,int arg2,int arg3); /* 0x08058de0 spr-lib.c */
int * SpriteArrayPalUpdateAndAccess(int sprites,int index); /* 0x08058df0 spr-lib.c */
bool SpriteArrayPalRemapFromRoot(int arg1,int arg2,int arg3); /* 0x08058e20 spr-lib.c */
bool SpriteArrayPalRemapFromRootGrpItem (int *param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08058e70 spr-lib.c */
int ColDepthToBytesPerPixel(int arg1); /* 0x08058ee0 spr-lib.c */
uint32_t SpriteDecompGetData(int *sprites,int arg2); /* 0x08058ef0 spr-lib.c */
uint32_t SpriteDecompGetAndLockData(int *sprites,int arg2); /* 0x08058f30 spr-lib.c */
uint32_t SpriteDecompUnlockData(void); /* 0x08058f40 spr-lib.c */
void W_PutSurface(void); /* 0x08058f50 spr-lib.c */
uint32_t W_PutSprite(int *sprites,int index,int x,int y); /* 0x08058f60 spr-lib.c */
void W_PutSpriteA(int *sprites,int index,int x,int y,int arg5); /* 0x08058ff0 spr-lib.c */
void W_PutSpriteAMirH(int *sprites,int index,int x,int y,int arg5); /* 0x08059040 spr-lib.c */
void W_PutSpriteAPal(int *sprites,int index,int x,uint32_t y,int arg5,int arg6); /* 0x08059090 spr-lib.c */
void W_PutSpriteAMirHPal(int *sprites,int index,int x,uint32_t y,int arg5,int arg6); /* 0x08059100 spr-lib.c */
void W_PutSpriteFlat(int *sprites,int index,int x,int y); /* 0x08059170 spr-lib.c */
uint32_t W_PutSpriteMirH(int *sprites,int index,int x,int y); /* 0x080591d0 spr-lib.c */
uint32_t W_PutSpriteMirV(int *sprites,int index,int x,int y); /* 0x08059230 spr-lib.c */
uint32_t W_PutSpriteMirHV(int *sprites,int index,int x,int y); /* 0x08059290 spr-lib.c */
void W_PutSpriteShadow(int *sprites,int index,int x,int y,uint16_t arg5); /* 0x080592f0 spr-lib.c */
void W_ScaleSprite(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x08059390 spr-lib.c */
void W_ScaleSpriteFlat(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x08059480 spr-lib.c */
void W_ScaleSpriteMirH(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x08059500 spr-lib.c */
void W_ScaleSpriteMirV(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x08059590 spr-lib.c */
void W_ScaleSpriteMirHV(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x08059620 spr-lib.c */
uint32_t W_ScaleSprite_S(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x080596b0 spr-lib.c */
void W_ScaleSpriteFlat_S(int *sprites,int index,int x,int y,float arg5,float arg6); /* 0x08059800 spr-lib.c */
void W_ScaleSpriteMirH_S(int *sprites,int index,int x,int y,float arg5,float arg6); /* 0x080598b0 spr-lib.c */
void W_ScaleSpriteMirV_S(int *sprites,int index,int x,int y,float arg5,float arg6); /* 0x080598f0 spr-lib.c */
void W_ScaleSpriteMirHV_S (int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6); /* 0x08059920 spr-lib.c */
void W_RotateSprite(int *sprites,int index,float x,float y,float arg5,float arg6,float arg7); /* 0x08059960 spr-lib.c */
void W_RotateSpriteMirH(int *sprites,int index,float x,float y,float arg5,float arg6,float arg7); /* 0x080599a0 spr-lib.c */
uint32_t W_RotateSprite_P(int *sprites,int index,float x,float y,float arg5,float arg6,float arg7,float arg8,float arg9); /* 0x080599e0 spr-lib.c */
void W_RotateSpriteMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08059c00 spr-lib.c */
uint32_t W_PutSpriteTransAdd(int *sprites,int index,int x,int y); /* 0x08059c30 spr-lib.c */
uint32_t W_PutSpriteTransAddMirH(int *sprites,int index,int x,int y); /* 0x08059ca0 spr-lib.c */
uint32_t W_PutSpriteTransAddMirV(int *sprites,int index,int x,int y); /* 0x08059d10 spr-lib.c */
uint32_t W_PutSpriteTransAddMirHV(int *sprites,int index,int x,int y); /* 0x08059d80 spr-lib.c */
void W_PutSpriteTransAddFlip(int *sprites,int index,int x,int y,int arg5); /* 0x08059df0 spr-lib.c */
uint32_t W_PutSpriteTransAdd_B(int *sprites,int index,int x,int y,int arg5,int arg6); /* 0x08059e90 spr-lib.c */
uint32_t W_PutSpriteTransAddMirH_B(int *sprites,int index,int x,int y,int arg5,int arg6); /* 0x08059f20 spr-lib.c */
uint32_t W_PutSpriteTransAddMirV_B(int *sprites,int index,int x,int y,int arg5,int arg6); /* 0x08059fb0 spr-lib.c */
uint32_t W_PutSpriteTransAddMirHV_B(int *sprites,int index,int x,int y,int arg5,int arg6); /* 0x0805a040 spr-lib.c */
void W_PutSpriteTransAddFlip_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7 ); /* 0x0805a0d0 spr-lib.c */
uint32_t W_ScaleSpriteTransAdd (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a1c0 spr-lib.c */
uint32_t W_ScaleSpriteTransAdd_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a250 spr-lib.c */
void W_ScaleSpriteTransAddMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a3a0 spr-lib.c */
void W_ScaleSpriteTransAddMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a430 spr-lib.c */
void W_ScaleSpriteTransAddMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a4c0 spr-lib.c */
void W_ScaleSpriteTransAdd_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a550 spr-lib.c */
uint32_t W_ScaleSpriteTransAdd_B_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a600 spr-lib.c */
void W_ScaleSpriteTransAddMirH_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a790 spr-lib.c */
void W_ScaleSpriteTransAddMirV_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a840 spr-lib.c */
void W_ScaleSpriteTransAddMirHV_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a8f0 spr-lib.c */
void W_RotateSpriteTransAdd (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805a9a0 spr-lib.c */
void W_RotateSpriteTransAddMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805a9e0 spr-lib.c */
uint32_t W_RotateSpriteTransAdd_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805aa20 spr-lib.c */
void W_RotateSpriteTransAddMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805ac40 spr-lib.c */
void W_RotateSpriteTransAdd_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,int param_8,int param_9); /* 0x0805ac70 spr-lib.c */
void W_RotateSpriteTransAddMirH_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,int param_8,int param_9); /* 0x0805acc0 spr-lib.c */
uint32_t W_RotateSpriteTransAdd_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0805ad10 spr-lib.c */
void W_RotateSpriteTransAddMirH_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0805af90 spr-lib.c */
uint32_t W_PutSpriteTransSub(int *sprites,int index,int x,int y); /* 0x0805afc0 spr-lib.c */
uint32_t W_PutSpriteTransSubMirH(int *sprites,int index,int x,int y); /* 0x0805b030 spr-lib.c */
void W_PutSpriteTransSubMirV(int *sprites,int index,int x,int y); /* 0x0805b0a0 spr-lib.c */
uint32_t W_PutSpriteTransSubMirHV(int *sprites,int index,int x,int y); /* 0x0805b110 spr-lib.c */
uint32_t W_ScaleSpriteTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b180 spr-lib.c */
uint32_t W_ScaleSpriteTransSub_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b210 spr-lib.c */
void W_ScaleSpriteTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b360 spr-lib.c */
void W_ScaleSpriteTransSubMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b3f0 spr-lib.c */
void W_ScaleSpriteTransSubMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b480 spr-lib.c */
void W_RotateSpriteTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805b510 spr-lib.c */
void W_RotateSpriteTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805b550 spr-lib.c */
uint32_t W_RotateSpriteTransSub_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805b590 spr-lib.c */
void W_RotateSpriteTransSubMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805b7b0 spr-lib.c */
void W_ScaleShadowTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x0805b7e0 spr-lib.c */
uint32_t W_ScaleShadowTransSub_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x0805b880 spr-lib.c */
void W_ScaleShadowTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x0805b9f0 spr-lib.c */
void W_ScaleShadowTransSubMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x0805ba90 spr-lib.c */
void W_ScaleShadowTransSubMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x0805bb30 spr-lib.c */
void W_RotateShadowTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,uint32_t param_8); /* 0x0805bbd0 spr-lib.c */
void W_RotateShadowTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,uint32_t param_8); /* 0x0805bc10 spr-lib.c */
int W_RotateShadowTransSub_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint32_t param_10); /* 0x0805bc50 spr-lib.c */
void W_RotateShadowTransSubMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint32_t param_10); /* 0x0805beb0 spr-lib.c */
int HFlipToSgn(uint32_t arg1); /* 0x0805bee0 spr-lib.c */
int VFlipToSgn(uint32_t arg1); /* 0x0805bf00 spr-lib.c */
void SpriteSetReadMode(int arg1); /* 0x0805bf20 spr-read.c */
void SpriteSetBufReadMode(int arg1); /* 0x0805bf30 spr-read.c */
int * SpriteReadFile(char *filename); /* 0x0805bf40 spr-read.c */
int * SpriteReadSFFPtr(int *mf); /* 0x0805c080 spr-read.c */
int * SpriteReadSFFPtr_1_01(int *mf,int arg2); /* 0x0805c140 spr-read.c */
uint32_t SpriteReadSFFPtr_2_00(void); /* 0x0805c3a0 spr-read.c */
int * SpriteReadSFFList(char *filename,int *arg2); /* 0x0805c3b0 spr-read.c */
int * SpriteReadSFFListPtr(int *mf,int *arg2); /* 0x0805c410 spr-read.c */
int * SpriteReadSFFListPtr_1_01(int *mf,int arg2,int *arg3); /* 0x0805c4c0 spr-read.c */
uint32_t SpriteReadSFFListPtr_2_00(void); /* 0x0805c7b0 spr-read.c */
void * SpriteReadPCXRawPtr(int *mf,int *arg2,int *arg3,int *arg4,size_t *arg5,int *arg6); /* 0x0805c7c0 spr-read.c */
int * SpriteReadPCXPtr(int *mf,int arg2,int arg3); /* 0x0805cc80 spr-read.c */
void W_PutSprite8to16(int *sprites,int index,int x,int y); /* 0x0805cd70 spr16-lb.c */
void W_PutSpriteFlat8to16(int *sprites,int index,int x,int y); /* 0x0805cfa0 spr16-lb.c */
void W_PutSpriteMirH8to16(int *sprites,int index,int x,int y); /* 0x0805d1c0 spr16-lb.c */
void W_PutSpriteMirV8to16(int *sprites,int index,int x,int y); /* 0x0805d420 spr16-lb.c */
void W_PutSpriteMirHV8to16(int *sprites,int index,int x2,int y); /* 0x0805d660 spr16-lb.c */
void W_ScaleSprite8to16(int *sprites,int index,float x,float y,float arg5,float arg6); /* 0x0805d8b0 spr16-lb.c */
void W_ScaleSpriteFlat8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805e190 spr16-lb.c */
void W_ScaleSpriteMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805ea80 spr16-lb.c */
void W_ScaleSpriteMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805f370 spr16-lb.c */
void W_ScaleSpriteMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805fc70 spr16-lb.c */
uint32_t W_RotateSprite8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08060570 spr16-lb.c */
uint32_t W_RotateSpriteMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08061400 spr16-lb.c */
void W_PutSpriteShadow8to16(int *sprites,int index,int x,int y,uint16_t arg5); /* 0x08062250 spr16-lb.c */
void W_PutSpriteShadow16(void); /* 0x08062430 spr16-lb.c */
void W_PutSpriteTransAdd8to16(int *sprites,int index,int x,int y); /* 0x08062440 spr16add.c */
void W_PutSpriteTransAddMirH8to16(int *sprites,int index,int x,int y); /* 0x08062710 spr16add.c */
void W_PutSpriteTransAddMirV8to16(int *sprites,int index,int x,int y); /* 0x080629f0 spr16add.c */
void W_PutSpriteTransAddMirHV8to16(int *sprites,int index,int x,int y); /* 0x08062ce0 spr16add.c */
void W_PutSpriteTransAdd8to16_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08062fe0 spr16add.c */
void W_PutSpriteTransAddMirH8to16_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x080638c0 spr16add.c */
void W_PutSpriteTransAddMirV8to16_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x080641e0 spr16add.c */
void W_PutSpriteTransAddMirHV8to16_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08064b00 spr16add.c */
void W_ScaleSpriteTransAdd8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08065440 spr16add.c */
void W_ScaleSpriteTransAddMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08065df0 spr16add.c */
void W_ScaleSpriteTransAddMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080667a0 spr16add.c */
void W_ScaleSpriteTransAddMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08067170 spr16add.c */
void W_ScaleSpriteTransAdd8to16_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x08067b30 spr16add.c */
void W_ScaleSpriteTransAddMirH8to16_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x08068c00 spr16add.c */
void W_ScaleSpriteTransAddMirV8to16_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x08069cf0 spr16add.c */
void W_ScaleSpriteTransAddMirHV8to16_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0806aee0 spr16add.c */
uint32_t W_RotateSpriteTransAdd8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0806c100 spr16add.c */
uint32_t W_RotateSpriteTransAddMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0806d020 spr16add.c */
uint32_t W_RotateSpriteTransAdd8to16_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0806df40 spr16add.c */
uint32_t W_RotateSpriteTransAddMirH8to16_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0806fff0 spr16add.c */
void W_PutSpriteTransSub8to16(int *sprites,int index,int x,int y); /* 0x08072060 spr16sub.c */
void W_PutSpriteTransSubMirH8to16(int *sprites,int index,int x,int y); /* 0x08072300 spr16sub.c */
void W_PutSpriteTransSubMirV8to16(int *sprites,int index,int x,int y); /* 0x080725b0 spr16sub.c */
void W_PutSpriteTransSubMirHV8to16(int *sprites,int index,int x,int y); /* 0x08072860 spr16sub.c */
void W_ScaleSpriteTransSub8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08072b30 spr16sub.c */
void W_ScaleSpriteTransSubMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080734b0 spr16sub.c */
void W_ScaleSpriteTransSubMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08073e30 spr16sub.c */
void W_ScaleSpriteTransSubMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080747c0 spr16sub.c */
uint32_t W_RotateSpriteTransSub8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08075150 spr16sub.c */
uint32_t W_RotateSpriteTransSubMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08076040 spr16sub.c */
void W_ScaleShadowTransSub8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x08076ef0 spr16sub.c */
void W_ScaleShadowTransSubMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x08077790 spr16sub.c */
void W_ScaleShadowTransSubMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x08078040 spr16sub.c */
void W_ScaleShadowTransSubMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint32_t param_7); /* 0x08078910 spr16sub.c */
int W_RotateShadowTransSub8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint32_t param_10); /* 0x080791e0 spr16sub.c */
int W_RotateShadowTransSubMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint32_t param_10); /* 0x0807a090 spr16sub.c */
void TimerHandler(void); /* 0x0807af40 time-lib.c */
bool TimerInit(int ticks_per_second); /* 0x0807af90 time-lib.c */
void TimerDeInit(void); /* 0x0807b000 time-lib.c */
void TimerChangeSpeed(int ticks_per_second); /* 0x0807b020 time-lib.c */
uint32_t TimerDelay(uint32_t ms); /* 0x0807b040 time-lib.c */
void TimerSetTicks(int ticks); /* 0x0807b050 time-lib.c */
float80 TimerGetFPS(void); /* 0x0807b060 time-lib.c */
void TimerSetFPSDelay(int calls); /* 0x0807b0d0 time-lib.c */
void TimerSyncReset(void); /* 0x0807b0f0 time-lib.c */
void TimerSetSyncFPS(int fps); /* 0x0807b110 time-lib.c */
bool TimerGetSync(void); /* 0x0807b150 time-lib.c */
void TimerWaitSync(void); /* 0x0807b160 time-lib.c */
uint32_t TimerIsSync(void); /* 0x0807b1a0 time-lib.c */
void TimerSkipSync(void); /* 0x0807b1f0 time-lib.c */
uint32_t TPFree(uint32_t *tp); /* 0x0807b200 txtparse.c */
uint32_t * TPReadMFPtr(int *mf,int arg2); /* 0x0807b2f0 txtparse.c */
int * TPReadMF(int *mf,int arg2); /* 0x0807b780 txtparse.c */
void * TPReadFile(char *filename); /* 0x0807b7c0 txtparse.c */
uint32_t * TPClone(uint32_t *tp); /* 0x0807b800 txtparse.c */
void * TPReadFileForWrite(char *filename); /* 0x0807b840 txtparse.c */
int * TPReadFilePtr(FILE *fp,int arg2); /* 0x0807b880 txtparse.c */
uint32_t TPWriteFile(int tp,char *filename); /* 0x0807bd10 txtparse.c */
uint32_t TPGroupSeek(int tp,char *group); /* 0x0807bd80 txtparse.c */
uint32_t TPGroupSeekIdx(int tp,int group); /* 0x0807be50 txtparse.c */
void TPGroupReset(int tp); /* 0x0807beb0 txtparse.c */
uint32_t TPGroupScanFirst(int tp); /* 0x0807bef0 txtparse.c */
uint32_t TPGroupScanNext(int tp); /* 0x0807bf00 txtparse.c */
int TPGroupMatchCount(int tp,char *group); /* 0x0807bf70 txtparse.c */
int TPGetLineNo(int arg1,char *arg2); /* 0x0807bfc0 txtparse.c */
int TPGetLineNo_Skip(int arg1,char *arg2,int arg3); /* 0x0807bfe0 txtparse.c */
char * TPGetValue(int tp,char *keyname); /* 0x0807c0a0 txtparse.c */
int TPSeekValue(int tp,char *keyname); /* 0x0807c1c0 txtparse.c */
int TPSeekEog(int tp); /* 0x0807c210 txtparse.c */
char * TPGetValueNewStr(int tp,char *keyname); /* 0x0807c250 txtparse.c */
char * TPGetValueNext(int tp,char *keyname); /* 0x0807c2b0 txtparse.c */
bool TPGetValueFloat(int tp,char *keyname,float *out); /* 0x0807c3e0 txtparse.c */
bool TPGetValueInt(int tp,char *keyname,uint32_t *out); /* 0x0807c420 txtparse.c */
int TPScanf(int tp,char *keyname,char *fmt,...); /* 0x0807c460 txtparse.c */
void TPAccessReset(int tp); /* 0x0807c4a0 txtparse.c */
uint32_t TPAccessFirstLine(int tp); /* 0x0807c4d0 txtparse.c */
uint32_t TPReaccessCurLine(int arg1); /* 0x0807c4f0 txtparse.c */
uint32_t TPAccessNextLine(int tp); /* 0x0807c510 txtparse.c */
uint32_t TPAccessPrevLine(int arg1); /* 0x0807c550 txtparse.c */
bool TPGetLine(int tp,char *arg2); /* 0x0807c580 txtparse.c */
int TPGetGroupText(int tp,int arg2,int arg3); /* 0x0807c5c0 txtparse.c */
int TPWLineNo(int arg1,int arg2); /* 0x0807c670 txtparse.c */
uint32_t TPGroupRename(int tp,char *fmt,...); /* 0x0807c6e0 txtparse.c */
uint32_t TPPrintf(int tp,char *keyname,char *fmt,...); /* 0x0807c850 txtparse.c */
uint32_t TPPrintf_Skip(int tp,char *keyname,int skip,char *fmt,...); /* 0x0807ca00 txtparse.c */
uint32_t TPInsertLine(int arg1,char *arg2); /* 0x0807cbc0 txtparse.c */
uint32_t TPDeleteLine(int arg1); /* 0x0807cca0 txtparse.c */
void TPDeleteAllLines(int tp); /* 0x0807cd50 txtparse.c */
uint32_t TPWExpandLinespace(int arg1); /* 0x0807cd80 txtparse.c */
void strgetto(char *arg1,char *arg2,int arg3,char arg4); /* 0x0807cdd0 txtparse.c */
uint32_t TPisspace(char ch); /* 0x0807ce20 txtparse.c */
uint32_t V_Alloc(int arg1,int arg2); /* 0x0807ce40 vbuf.c */
int * V_AllocDepth(int arg1,int arg2,int arg3); /* 0x0807ce60 vbuf.c */
int * V_AllocDepthAry(int arg1,int arg2,int arg3,size_t arg4); /* 0x0807ce80 vbuf.c */
uint32_t V_DeAlloc(int sprites); /* 0x0807cf60 vbuf.c */
uint32_t V_SetBuf(int *buffer,int index); /* 0x0807cfa0 vbuf.c */
uint32_t V_BufGetSurface(int *buffer,int index); /* 0x0807d030 vbuf.c */
uint32_t V_BufLock(int *buffer,int index); /* 0x0807d060 vbuf.c */
void V_BufUnlock(int *buffer,int index); /* 0x0807d0a0 vbuf.c */
void V_BufLockCurrent(void); /* 0x0807d0e0 vbuf.c */
void V_BufUnlockCurrent(void); /* 0x0807d100 vbuf.c */
void V_BufToScreen(int *buffer,int index); /* 0x0807d120 vbuf.c */
void V_BufToScreenXY(int *buffer,int index,int x,int y); /* 0x0807d200 vbuf.c */
void V_BufToScreenStretch(int *buffer,int index); /* 0x0807d350 vbuf.c */
void blit_32to16_RGBtoBGR (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7 ,int param_8); /* 0x0807d470 vbuf.c */
void stretch_blit_32to16_RGBtoBGR (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10); /* 0x0807d690 vbuf.c */
int W_Define(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2); /* 0x0807da70 vbuf.c */
void W_DefineV(uint32_t *arg1); /* 0x0807db40 vbuf.c */
void W_GetV(uint32_t *arg1); /* 0x0807db60 vbuf.c */
void W_Cls(uint32_t col); /* 0x0807db90 vbuf.c */
void W_PutPixel(int x,int y,uint32_t col); /* 0x0807dc40 vbuf.c */
void W_PutPixelTransAdd16(int arg1,int arg2,uint32_t arg3); /* 0x0807dd30 vbuf.c */
void W_PutPixelXor16(int x,int y); /* 0x0807de20 vbuf.c */
void W_Line(float x1,float y1,float x2,float y2,uint32_t col); /* 0x0807de90 vbuf.c */
void DoDrawLine(int arg1,int arg2,float arg3,float arg4,float arg5,float arg6,uint16_t arg7); /* 0x0807e020 vbuf.c */
float80 CyrusT(float arg1,float arg2,float arg3,float arg4,float arg5,float arg6,float arg7,float arg8); /* 0x0807e660 vbuf.c */
uint32_t TrivialTestPoint(int arg1,int arg2); /* 0x0807e6a0 vbuf.c */
void DoDrawClippedLine(int arg1,int arg2,float arg3,float arg4,float arg5,float arg6,uint16_t arg7); /* 0x0807e6f0 vbuf.c */
void W_HLine(uint32_t x1,uint32_t x2,int y,uint32_t col); /* 0x0807ec50 vbuf.c */
void W_VLine(int x,uint32_t y1,uint32_t y2,uint32_t col); /* 0x0807ed10 vbuf.c */
void W_HLineTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807ede0 vbuf.c */
void W_HLineTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807ef20 vbuf.c */
void W_VLineTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f060 vbuf.c */
void W_VLineTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f1b0 vbuf.c */
void W_HLineTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f300 vbuf.c */
void W_HLineTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f430 vbuf.c */
void W_VLineTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f560 vbuf.c */
void W_VLineTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0807f6a0 vbuf.c */
void W_Box(int x1,int y1,int x2,int y2,uint32_t col); /* 0x0807f7e0 vbuf.c */
void W_BoxTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5); /* 0x0807f900 vbuf.c */
void W_BoxTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5); /* 0x0807f970 vbuf.c */
void W_BoxTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5); /* 0x0807f9e0 vbuf.c */
void W_BoxTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5); /* 0x0807fa50 vbuf.c */
void W_BoxFill(int x1,int y1,int x2,int y2,uint32_t col); /* 0x0807fac0 vbuf.c */
void W_BoxFillTransAdd16(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5); /* 0x0807fbf0 vbuf.c */
void W_BoxFillTransAdd16_B50(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5); /* 0x0807fdb0 vbuf.c */
void W_BoxFillTransSub16(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5); /* 0x0807ff60 vbuf.c */
void W_BoxFillTransSub16_B50(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5); /* 0x08080120 vbuf.c */
int unzlocal_getByte(_IO_FILE *fin,uint32_t *pi); /* 0x080802e0 unzip.c */
int unzlocal_getShort(_IO_FILE *fin,uint32_t *pX); /* 0x08080330 unzip.c */
int unzlocal_getLong(_IO_FILE *fin,uint32_t *pX); /* 0x08080390 unzip.c */
int strcmpcasenosensitive_internal(char *fileName1,char *fileName2); /* 0x08080420 unzip.c */
int unzStringFileNameCompare(char *fileName1,char *fileName2,int iCaseSensitivity); /* 0x08080480 unzip.c */
int unzlocal_SearchCentralDir(FILE *fin); /* 0x080804c0 unzip.c */
uint32_t * unzOpen(char *path); /* 0x080805e0 unzip.c */
uint32_t unzClose(void *zipfile); /* 0x080807a0 unzip.c */
uint32_t unzGetGlobalInfo(int zipfile,uint32_t *pglobal_info); /* 0x080807e0 unzip.c */
void unzlocal_DosDateToTmuDate(uint32_t ulDosDate,int *ptm); /* 0x08080810 unzip.c */
uint32_t unzlocal_GetCurrentFileInfoInternal (uint32_t *param_1,uint32_t *param_2,uint32_t *param_3,size_t param_4,uint32_t param_5, size_t param_6,void *param_7,size_t param_8,void *param_9); /* 0x08080870 unzip.c */
uint32_t unzGetCurrentFileInfo (uint32_t *param_1,uint32_t *param_2,size_t param_3,uint32_t param_4,size_t param_5, void *param_6,size_t param_7,void *param_8); /* 0x08080c30 unzip.c */
uint32_t unzGoToFirstFile(uint32_t *zipfile); /* 0x08080c70 unzip.c */
uint32_t unzGoToNextFile(uint32_t *zipfile); /* 0x08080cc0 unzip.c */
uint32_t unzLocateFile(uint32_t *zipfile,char *szFileName,int iCaseSensitivity); /* 0x08080d40 unzip.c */
uint32_t unzlocal_CheckCurrentFileCoherencyHeader (uint32_t *param_1,int *param_2,int *param_3,uint32_t *param_4); /* 0x08080e10 unzip.c */
uint32_t unzOpenCurrentFile(uint32_t *zipfile); /* 0x08081040 unzip.c */
uint32_t unzReadCurrentFile(int zipfile,int buf,uint32_t len); /* 0x080811a0 unzip.c */
uint32_t unztell(int zipfile); /* 0x080813a0 unzip.c */
uint32_t unzeof(int zipfile); /* 0x080813c0 unzip.c */
uint32_t unzGetLocalExtrafield(int zipfile,size_t buf,uint32_t len); /* 0x080813e0 unzip.c */
uint32_t unzCloseCurrentFile(int zipfile); /* 0x08081480 unzip.c */
uint32_t unzGetGlobalComment(uint32_t *zipfile,uint8_t *szComment,uint32_t uSizeBuf); /* 0x08081500 unzip.c */
uint32_t NewListNode(void); /* 0x08081580 gui-lib.c */
void AddNodeToEnd(int *arg1); /* 0x08081590 gui-lib.c */
void MoveNodeToEnd(int *arg1); /* 0x080815b0 gui-lib.c */
void MoveNodeToStart(void); /* 0x080815f0 gui-lib.c */
uint32_t EB_GUIInit(int arg1); /* 0x08081600 gui-lib.c */
void EB_GUIDeInit(void); /* 0x08081730 gui-lib.c */
void EB_GUISetWinAttr(int arg1,uint32_t arg2); /* 0x08081740 gui-lib.c */
int * EB_GUINewWindow(char *arg1,int arg2,int arg3,int arg4,int *arg5); /* 0x08081760 gui-lib.c */
void EB_GUICloseWindow(void *arg1); /* 0x08081970 gui-lib.c */
void EB_GUIDrawClipboard(int *arg1,int arg2,int arg3,uint32_t arg4); /* 0x080819b0 gui-lib.c */
void EB_GUIPutSurface(void); /* 0x08081ab0 gui-lib.c */
uint32_t EB_GUIRaiseWindow(int *arg1); /* 0x08081ac0 gui-lib.c */
void EB_GUIPutSprite(int arg1,int *sprites,int arg3,int arg4,int arg5); /* 0x08081ae0 gui-lib.c */
void EB_GUIClearWindow(int arg1); /* 0x08081b50 gui-lib.c */
void EB_GUIDrawWindow(uint32_t *arg1); /* 0x08081b90 gui-lib.c */
void EB_DrawWindows(void); /* 0x08081dd0 gui-lib.c */
void EB_GUIMoveWindow(int *arg1,int arg2,int arg3); /* 0x08081e00 gui-lib.c */
int * DetermineFocus(int arg1,int *arg2); /* 0x08081e60 gui-lib.c */
void EB_GUIUpdate(void); /* 0x08081eb0 gui-lib.c */
int EBT_ThreadCreate(pthread_t *arg1,uint32_t arg2,__start_routine *arg3,void *arg4); /* 0x08081ff0 lthreads.c */
int EBT_MutexInit(void); /* 0x08082020 lthreads.c */
int EBT_MutexDestroy(pthread_mutex_t *mutex); /* 0x08082040 lthreads.c */
int EBT_MutexLock(pthread_mutex_t *m); /* 0x08082050 lthreads.c */
int EBT_MutexUnlock(pthread_mutex_t *m); /* 0x08082060 lthreads.c */
int * AftImgNew(int arg1); /* 0x08082070 afterimg.c */
uint32_t AftImgInit(int *arg1,int arg2); /* 0x080820c0 afterimg.c */
uint32_t AftImgFree(int *arg1); /* 0x08082150 afterimg.c */
void AftImgDeInit(int *arg1); /* 0x08082180 afterimg.c */
void AftImgSetup(int arg1,uint32_t *arg2,uint32_t arg3); /* 0x080821f0 afterimg.c */
uint32_t AftImgUpdate(int *arg1,float arg2,float arg3,float arg4,uint32_t arg5,float arg6,uint32_t arg7,int arg8); /* 0x08082230 afterimg.c */
void AftImgDraw(int *arg1,int arg2,int arg3,int arg4); /* 0x080823f0 afterimg.c */
int ipow(int arg1,int arg2); /* 0x08082880 arith.c */
void StackErrorExit(void); /* 0x080828d0 arith.c */
uint32_t PriorityCheck(uint32_t arg1); /* 0x080828f0 arith.c */
uint32_t OpLength(uint32_t arg1); /* 0x08082980 arith.c */
bool OpTypeCheck(uint32_t arg1,int arg2); /* 0x080829b0 arith.c */
int OperCode(uint8_t *arg1); /* 0x080829e0 arith.c */
char * InfToPostArray(uint8_t *text,float *values,void *types,int player,uint8_t *max_tokens,uint32_t *end,int want_type); /* 0x08082ad0 arith.c */
uint32_t InfixToPostfix(uint8_t *text,int *expr,int player,uint32_t *end,int want_type); /* 0x08083780 arith.c */
uint32_t FreeExpression(int *expr); /* 0x08083870 arith.c */
void FreeExpNoTrig(uint32_t *arg1); /* 0x080838f0 arith.c */
uint32_t FreeExpArray(void *array); /* 0x08083930 arith.c */
void ConstExpI(int *expr,int value); /* 0x08083980 arith.c */
void ConstExpF(int *expr,int value_bits); /* 0x080839c0 arith.c */
uint32_t expcpy(int *dest,int *src); /* 0x08083a00 arith.c */
uint32_t expcpytrig(int *dest,int *src); /* 0x08083aa0 arith.c */
float ExpMulF(int *arg1,float arg2); /* 0x08083b40 arith.c */
float ExpDivI(int *arg1,int arg2); /* 0x08083c00 arith.c */
void ShowExp(char *arg1,int *expr,int *player); /* 0x08083cd0 arith.c */
int EvalExpressionI(int player,int *expr,int warn); /* 0x08083e40 arith.c */
float EvalExpressionF(int *player,int *expr); /* 0x08083f60 arith.c */
uint32_t EvalExpression(int *player,int *expr,int *out_int,int *out_float); /* 0x08084020 arith.c */
bool BGMParse(int tp,uint8_t *bgmdef,char *keyname); /* 0x08085240 bgm.c */
void BGMStart(int *bgm); /* 0x080852b0 bgm.c */
void BGMPause(int *bgm); /* 0x080853c0 bgm.c */
void BGMSysPause(int *bgm); /* 0x08085440 bgm.c */
uint32_t BGMGetPause(int bgm); /* 0x080854c0 bgm.c */
uint32_t BGMResume(int *bgm); /* 0x080854e0 bgm.c */
void BGMSysResume(int *bgm); /* 0x08085570 bgm.c */
int BGMGetVolume(int *bgm); /* 0x08085600 bgm.c */
void BGMSetVolume(int *bgm,uint32_t vol); /* 0x08085660 bgm.c */
void BGMPoll(int *bgm); /* 0x080856e0 bgm.c */
void BGMPollIgnoreDefocus(int *bgm); /* 0x08085760 bgm.c */
uint32_t BGMCheckExtension(char *arg1); /* 0x08085800 bgm.c */
uint32_t BGMLoad(int *bgm,uint8_t *filename,int loop); /* 0x08085810 bgm.c */
uint32_t BGMLoadAndStart(int *bgm,uint8_t *filename,int arg3,int arg4); /* 0x08085a60 bgm.c */
int * BGMFree(int *bgm); /* 0x08085b40 bgm.c */
void BGMPlayForScene(uint8_t *filename,int arg2); /* 0x08085be0 bgm.c */
void BGMStopForScene(void); /* 0x08085c10 bgm.c */
bool InitSelectScreenMatrix(char *path); /* 0x08085c30 charsel.c */
void FreeSelectScreenMatrix(void); /* 0x08085cd0 charsel.c */
bool CharInfoInit(void); /* 0x08085d00 charsel.c */
void CharInfoFree(void); /* 0x08085db0 charsel.c */
uint32_t FindCharacters(void); /* 0x08085df0 charsel.c */
uint32_t CharacterSelectScreen(uint32_t arg1,int arg2); /* 0x08087150 charsel.c */
uint32_t CharacterSelectScreenDraw(int arg1); /* 0x08088630 charsel.c */
int BuildSelectList(int arg1,uint32_t arg2,int arg3); /* 0x08089810 charsel.c */
void InitSelectDisp(int arg1); /* 0x08089da0 charsel.c */
void UpdateSelectDisp(int *arg1); /* 0x08089e00 charsel.c */
void SelectDispState(uint32_t *arg1,uint32_t arg2); /* 0x08089e50 charsel.c */
void FlashBox(int arg1,uint32_t arg2,uint32_t arg3); /* 0x08089e70 charsel.c */
int CharacterSelectScreenKey(uint32_t arg1,int arg2,int *arg3,int *arg4,int arg5); /* 0x08089ec0 charsel.c */
bool CharacterSelectStageKey(uint32_t arg1,int arg2,uint32_t *arg3,int arg4); /* 0x0808a230 charsel.c */
uint32_t CharacterSelectMenuKey(uint32_t arg1,uint32_t arg2,int arg3,int arg4); /* 0x0808a2a0 charsel.c */
void CharselResetCursor(void); /* 0x0808a3a0 charsel.c */
void CharselSaveCursor(uint32_t arg1,uint32_t arg2,uint32_t arg3,int arg4,int arg5); /* 0x0808a3e0 charsel.c */
void CharselRestoreCursor(int arg1,int arg2,int arg3); /* 0x0808a410 charsel.c */
void CharselResetMenuPos(void); /* 0x0808a4c0 charsel.c */
void CharselSaveMenuPos(int arg1,uint32_t *arg2,int arg3); /* 0x0808a4e0 charsel.c */
void CharselRestoreMenuPos(int arg1,int *arg2,int arg3); /* 0x0808a520 charsel.c */
bool CharselReadConfig(int tp); /* 0x0808a560 charsel.c */
uint32_t VersusScreen(void); /* 0x0808af70 charsel.c */
uint32_t ArcadeListBuild(void); /* 0x0808b9f0 charsel.c */
void ArcadeListBuildSet(int *arg1,int arg2,int arg3); /* 0x0808ba60 charsel.c */
int ArcadeListGetCurrent(void); /* 0x0808bd80 charsel.c */
int ArcadeListGet(int arg1); /* 0x0808bd90 charsel.c */
int ArcadeListGetCurSize(void); /* 0x0808bf70 charsel.c */
void ArcadeListPeekCur(int arg1); /* 0x0808bff0 charsel.c */
void ArcadeListPeekNext(int arg1); /* 0x0808c010 charsel.c */
int ArcadeListPeek(int arg1,int arg2); /* 0x0808c030 charsel.c */
int ArcadeListEnemiesLeft(void); /* 0x0808c100 charsel.c */
void SurvivalBuildRandomTeam(uint32_t *arg1,int arg2,int arg3); /* 0x0808c120 charsel.c */
uint32_t GetPlayerRowCol(int arg1,int *arg2,int *arg3); /* 0x0808c390 charsel.c */
uint32_t SlctStateListChanged(int arg1); /* 0x0808c410 charsel.c */
int SlctStateListNextItem(int arg1); /* 0x0808c430 charsel.c */
void SlctStateListUpdate(int arg1); /* 0x0808c470 charsel.c */
void BuildSlctCtrl(int arg1,int arg2,int arg3); /* 0x0808c490 charsel.c */
void BuildSlctTeamForArcade(int arg1,int arg2,int arg3,uint32_t arg4,int arg5); /* 0x0808c630 charsel.c */
void BuildMenuCtrl(int arg1,int arg2,int arg3); /* 0x0808c6d0 charsel.c */
void MenuItemVal(uint32_t *arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4); /* 0x0808c8a0 charsel.c */
uint32_t CharReservePal(uint32_t charno,int pal); /* 0x0808c8e0 charsel.c */
void CharStopUsingPal(uint8_t charno,int pal); /* 0x0808c9b0 charsel.c */
void CharStopUsingPalAll(void); /* 0x0808ca00 charsel.c */
void ParseCmdLine(MugenCmdLine *opts,int argc,char **argv); /* 0x0808ca40 cmdline.c */
uint32_t PrintHelp(void); /* 0x0808d090 cmdline.c */
void GlobalInputUpdate(void); /* 0x0808d0f0 common.c */
uint32_t Warn(int player,int msg); /* 0x0808d100 common.c */
uint32_t VWarn(int player,char *fmt,...); /* 0x0808d150 common.c */
int WarnR(int player,int msg,int arg3); /* 0x0808d1c0 common.c */
void StripDoublePercent(char *arg1); /* 0x0808d220 common.c */
void FontDrawClipboard(int *arg1,int *font,int arg3,int arg4,uint32_t arg5); /* 0x0808d250 common.c */
uint32_t ErrorExit(void); /* 0x0808d300 common.c */
uint32_t ErrorExitM(char *fmt,...); /* 0x0808d3d0 common.c */
bool fileexist(char *arg1); /* 0x0808d400 common.c */
uint32_t ChangeFileDir(char *path,char *arg2,char *arg3); /* 0x0808d440 common.c */
uint32_t FindFileDir(char *path,char *arg2,char *arg3); /* 0x0808d5c0 common.c */
uint32_t FindFileDirEx(char *path,char *arg2,char *arg3,uint32_t *arg4); /* 0x0808d5e0 common.c */
uint32_t GetQuotedString(int tp,char *keyname,char *buf,size_t size,char *defval); /* 0x0808d750 common.c */
int MDYDateCmp(int m1,int d1,int y1,int m2,int d2,int y2); /* 0x0808d830 date.c */
void datenotostr(uint32_t arg1,int arg2,uint8_t **arg3,char *arg4); /* 0x0808d870 date.c */
void FrameSkipReset(void); /* 0x0808d940 display.c */
void FrameSkipUpdate(void); /* 0x0808d960 display.c */
void DrawToScreen(void); /* 0x0808da20 display.c */
void ScreenSnap(void); /* 0x0808dbb0 display.c */
int * ExplodArrayNew(size_t arg1,uint32_t arg2); /* 0x0808dc30 explod.c */
void ExplodArrayFree(int *arg1); /* 0x0808dcb0 explod.c */
void ExplodArrayUpdate(int *arg1); /* 0x0808dd20 explod.c */
int * ExplodUpdate(int *arg1,int arg2); /* 0x0808dd50 explod.c */
void ExplodArrayDraw(int *arg1,int arg2); /* 0x0808ded0 explod.c */
void ExplodDraw(int arg1); /* 0x0808df40 explod.c */
void ExplodArrayDrawShadow(int *arg1); /* 0x0808e210 explod.c */
void ExplodDrawShadow(int arg1,int *arg2,uint32_t arg3,int *arg4); /* 0x0808e2b0 explod.c */
void ExplodArrayReset(uint32_t *arg1); /* 0x0808e840 explod.c */
void ExplodDefault(uint32_t *arg1); /* 0x0808e870 explod.c */
void ExplodMakeFromInfo(int *player,int expr,int *arg3); /* 0x0808e990 explod.c */
void ExplodModifyFromInfo(int *player,int expr,int *arg3); /* 0x0808ea70 explod.c */
void ExplodSetParams(int *player,int arg2,int expr,int *arg4,int arg5); /* 0x0808eb10 explod.c */
int ExplodAdd(uint32_t *arg1,int arg2,int *arg3,int arg4); /* 0x0808f300 explod.c */
int ExplodAddSprite(uint32_t *arg1,int group,int arg3,int *sprites); /* 0x0808f3c0 explod.c */
int ExplodAddText(int *arg1,char *arg2,int arg3,int arg4,int arg5); /* 0x0808f460 explod.c */
void ExplodRemove(int *arg1,int arg2); /* 0x0808f4f0 explod.c */
void ExplodRemoveID(uint32_t *arg1,int arg2,int arg3); /* 0x0808f520 explod.c */
void ExplodRemoveGetHit(uint32_t *arg1,int arg2); /* 0x0808f580 explod.c */
int ExplodAccessID(uint32_t *arg1,int arg2,int arg3); /* 0x0808f5d0 explod.c */
int ExplodGetUniqID(void); /* 0x0808f620 explod.c */
void ExplodBindChange(uint32_t *arg1,int arg2,int arg3,int arg4); /* 0x0808f630 explod.c */
int ExplodCount(int *arg1,int arg2,int arg3); /* 0x0808f680 explod.c */
uint32_t SysExplodParse(int tp,int *sysexplod,uint32_t prefix); /* 0x0808f6d0 explod.c */
uint32_t SysExplodParseGetSprGrpImgNo(int *arg1,int *arg2,int *arg3); /* 0x0808f900 explod.c */
void SysExplodCreateDraw(int *arg1,int *arg2,int *sprites,int *arg4,int arg5,int arg6,int arg7,int arg8); /* 0x0808f930 explod.c */
int SysExplodCreateDrawPal (int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6, int param_7,int param_8); /* 0x0808f940 explod.c */
int SysExplodCreate(int *arg1,int *arg2,int *sprites,int *arg4,int arg5,int arg6,int arg7); /* 0x0808fa20 explod.c */
void SysExplodCreate_Fight(int *arg1,int arg2,int arg3); /* 0x0808fc90 explod.c */
void SysExplodCreate_Sys(int *arg1,int arg2,int arg3); /* 0x0808fcd0 explod.c */
void SysExplodCreateDraw_Fight(int *sysexplod,int arg2,int arg3,int arg4); /* 0x0808fd20 explod.c */
void SysExplodCreateDraw_Sys(int *arg1,int arg2,int arg3,int arg4); /* 0x0808fd70 explod.c */
uint32_t GameLoop(int arg1); /* 0x0808fdc0 gameloop.c */
uint32_t GameUpdate(void); /* 0x08091100 gameloop.c */
void GameWinScreenUpdate(void); /* 0x08091e30 gameloop.c */
void GameSurvivalResultsUpdate(void); /* 0x08091fc0 gameloop.c */
uint32_t GameDemoUpdate(void); /* 0x08092180 gameloop.c */
uint32_t GameRoundUpdate(void); /* 0x08092250 gameloop.c */
void GameRoundDraw(void); /* 0x08093540 gameloop.c */
uint32_t GameInputUpdate(void); /* 0x08093900 gameloop.c */
int CameraMoveAbs(float arg1,float arg2); /* 0x08094350 gameloop.c */
void CameraMoveP(void); /* 0x080943d0 gameloop.c */
void ComboAdd(int arg1,int arg2); /* 0x08094d00 gameloop.c */
void ComboClear(int arg1); /* 0x08094d70 gameloop.c */
void ComboDisplay(int arg1); /* 0x08094d90 gameloop.c */
void ComboDisplayUpdate(int arg1); /* 0x08095050 gameloop.c */
void PlayerComboCountCheck(int arg1); /* 0x08095110 gameloop.c */
void GameBGDraw(void); /* 0x080951b0 gameloop.c */
void GameFGDraw(void); /* 0x080952f0 gameloop.c */
void GameBarsDraw(int arg1); /* 0x08095310 gameloop.c */
void GameLifeBarDraw(uint32_t arg1,int arg2,int *arg3,int arg4); /* 0x08096400 gameloop.c */
void GameBarsUpdate(void); /* 0x080968c0 gameloop.c */
void GameLifeBarUpdate(int player); /* 0x08096930 gameloop.c */
uint32_t GamePowerBarDraw(int arg1,int arg2,int arg3,uint32_t arg4,int arg5,int arg6); /* 0x08096ab0 gameloop.c */
int GamePowerBarUpdate(int arg1); /* 0x08096c10 gameloop.c */
int RequestNewAftImg(int array); /* 0x08096d00 gameloop.c */
void GameAftImgReset(int array); /* 0x08096d30 gameloop.c */
int GameAftImgCount(int array); /* 0x08096d70 gameloop.c */
void PlayerAftImgUpdate(int arg1); /* 0x08096db0 gameloop.c */
void PlayerAftImgDraw(int arg1); /* 0x08096e80 gameloop.c */
void ProjArrayAftImgUpdate(int *arg1); /* 0x08096ed0 gameloop.c */
void ProjAftImgUpdate(int arg1); /* 0x08096f00 gameloop.c */
void ProjArrayAftImgDraw(int *arg1); /* 0x08096fa0 gameloop.c */
void ProjAftImgDraw(int arg1); /* 0x08096fd0 gameloop.c */
void GameClsnDraw(int arg1,float arg2,float arg3,float arg4,float arg5,uint32_t arg6,uint32_t arg7,int arg8); /* 0x08097020 gameloop.c */
int TeamLifeBack(int arg1); /* 0x08097210 gameloop.c */
void WinIconCheckTeam(int arg1,int arg2,uint32_t arg3); /* 0x080972e0 gameloop.c */
void WinIconCheck(int side,uint32_t arg2,int icon); /* 0x08097360 gameloop.c */
uint32_t TeamHasFullLife(int arg1); /* 0x08097420 gameloop.c */
void ShowDebugInfo(int arg1); /* 0x080974b0 gameloop.c */
uint8_t ContinueScreenLoop(void); /* 0x08097940 gameloop.c */
int * HelperMake(int *player,char *arg2,int *arg3); /* 0x080980d0 helper.c */
void HelperDestroy(int arg1); /* 0x08098930 helper.c */
uint32_t HelperParent(int player); /* 0x08098ad0 helper.c */
uint32_t HelperRoot(int player); /* 0x08098b00 helper.c */
int HelperCount(int player,int helper_id); /* 0x08098b10 helper.c */
uint32_t HelperAccessID(int player,int id); /* 0x08098bb0 helper.c */
void CloseAllFunc(void); /* 0x08098c50 init.c */
void GameInit(MugenCmdLine opts,int *mode); /* 0x08098c60 init.c */
void GameDeInit(int arg1); /* 0x08099350 init.c */
void GameInitPads(void); /* 0x08099490 init.c */
void GameDefKeyInit(void); /* 0x080995f0 init.c */
bool GameInputSetup(void); /* 0x08099640 init.c */
bool GfxResize(int arg1,int arg2,uint32_t arg3,int arg4); /* 0x080997c0 init.c */
uint32_t GameLoadFightData(FILE *value); /* 0x08099880 init.c */
void GameFreeFightData(void); /* 0x0809bc20 init.c */
uint32_t GameVarInit(void); /* 0x0809bcf0 init.c */
uint32_t GameVarLoadFonts(void); /* 0x0809c160 init.c */
uint32_t GameVarDeInit(void); /* 0x0809c200 init.c */
uint32_t * GameAftImgArrayNew(size_t arg1,int arg2); /* 0x0809c320 init.c */
uint32_t GameAftImgArrayFree(void *array); /* 0x0809c3b0 init.c */
void SwitchCallbacksInit(void); /* 0x0809c400 init.c */
void SwitchCallbacksDeInit(void); /* 0x0809c410 init.c */
void SwitchAwayCallback(void); /* 0x0809c420 init.c */
void SwitchBackCallback(void); /* 0x0809c440 init.c */
int _mangled_main(int argc,char **argv); /* 0x0809c470 main.c */
void QuickVSSetup(MugenCmdLine *opts); /* 0x0809c6f0 main.c */
void MainLoop(int arg1); /* 0x0809cb60 main.c */
uint32_t GamePlay(void); /* 0x0809d120 main.c */
void ArcadeWinScreen(void); /* 0x0809d630 main.c */
void SurvivalResultsScreen(void); /* 0x0809d830 main.c */
void DemoFightSetup(void); /* 0x0809da60 main.c */
uint8_t ContinueScreen(void); /* 0x0809dc00 main.c */
bool GameModeInFightScreen(void); /* 0x0809dc10 main.c */
bool GameModeInPassiveFightScreen(void); /* 0x0809dc30 main.c */
uint32_t GameLoadStage(void); /* 0x0809dc50 match.c */
bool GameBGLoad(void); /* 0x0809e630 match.c */
void GameUnloadStage(void); /* 0x0809e730 match.c */
uint32_t GameStgInitFightData(void); /* 0x0809e8d0 match.c */
void GameStgDeInitFightData(void); /* 0x0809eb00 match.c */
void GameNextRound(void); /* 0x0809eb60 match.c */
uint32_t GameReloadStage(void); /* 0x0809ece0 match.c */
void GameMatchReset(void); /* 0x0809edf0 match.c */
void GameRoundReset(void); /* 0x0809f210 match.c */
int GameRoundResetPlayerPos(void); /* 0x0809f880 match.c */
int GameRoundWinner(void); /* 0x0809f960 match.c */
int GameMatchWinner(void); /* 0x0809f970 match.c */
void LogPreMatch(void); /* 0x0809fa40 match.c */
void LogMatch(void); /* 0x0809fc40 match.c */
void IntroScreen(void); /* 0x0809fd70 menus.c */
void PlayCutscene(char *path,char *arg2); /* 0x0809fd90 menus.c */
void ModeSelect(void); /* 0x080a01b0 menus.c */
void OptionsScreen(void); /* 0x080a1830 menus.c */
int KeyConfigScreen(int arg1,int arg2); /* 0x080a3aa0 menus.c */
uint32_t TrainingMenuUpdate(uint32_t arg1); /* 0x080a4ff0 menus.c */
uint32_t TrainingMenuReset(void); /* 0x080a5480 menus.c */
void TrainingMenuDraw(void); /* 0x080a54b0 menus.c */
void InfoTextDraw(char *arg1,int arg2,int arg3); /* 0x080a5b70 menus.c */
uint32_t PlayerAIInit(int arg1,int arg2); /* 0x080a5d70 p-ai.c */
void PlayerAIDeInit(int arg1); /* 0x080a5dd0 p-ai.c */
uint32_t AILearnDataLoad(char *arg1,uint32_t *arg2); /* 0x080a5e00 p-ai.c */
uint32_t AILearnDataSave(char *arg1,int arg2); /* 0x080a6080 p-ai.c */
uint32_t AIStateSetInit(int arg1); /* 0x080a61d0 p-ai.c */
void AIStateSetDeInit(uint32_t *arg1); /* 0x080a6230 p-ai.c */
void AIStateSetClear(int arg1); /* 0x080a6270 p-ai.c */
uint32_t AIStateSetMerge(int arg1,int arg2); /* 0x080a62a0 p-ai.c */
void AIStateSetCopy(int arg1,int arg2); /* 0x080a6380 p-ai.c */
void PlayerAISetLevel(int arg1,uint32_t arg2); /* 0x080a63b0 p-ai.c */
void PlayerResetAI(int player); /* 0x080a63c0 p-ai.c */
void PlayerAI(int player); /* 0x080a6440 p-ai.c */
void PlayerAIProcessCommands(int arg1); /* 0x080a6570 p-ai.c */
uint32_t AIInsertCommand(int *cmdqueue,int cmd); /* 0x080a65c0 p-ai.c */
void AICopyCommands(int arg1,int *arg2); /* 0x080a6600 p-ai.c */
void AIClearCommands(uint32_t *cmdqueue); /* 0x080a6630 p-ai.c */
int AICountCommands(int *cmdqueue); /* 0x080a6640 p-ai.c */
uint32_t PlayerAILearnMoveStart(int player); /* 0x080a6660 p-ai.c */
void PlayerAILearnMoveUpdate(int player,int arg2); /* 0x080a67f0 p-ai.c */
int AILearnClsnUpdate(int player,int arg2); /* 0x080a71f0 p-ai.c */
void AILearnIdleClsnUpdate(int player); /* 0x080a7460 p-ai.c */
int AIIdleClsnMatchState(int arg1); /* 0x080a7620 p-ai.c */
uint32_t PlayerAILearnMoveEnd(int player,int arg2); /* 0x080a7670 p-ai.c */
uint32_t PlayerAIGetAIPLHS(int arg1); /* 0x080a79d0 p-ai.c */
uint32_t AIFetchLearnDataArray(int arg1,int arg2); /* 0x080a7a20 p-ai.c */
void PlayerAIMsgAttack(int player); /* 0x080a7a50 p-ai.c */
void PlayerAIMsgAttackEnd(int arg1); /* 0x080a7ad0 p-ai.c */
int PlayerAIBroadcastMsg (int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4, uint32_t param_5); /* 0x080a7b20 p-ai.c */
int PlayerAIFindMsg(int arg1,int arg2,int arg3); /* 0x080a7bf0 p-ai.c */
uint32_t * PlayerAIGetMsg(uint32_t *arg1,int arg2,int arg3,int arg4); /* 0x080a7c40 p-ai.c */
uint32_t * PlayerAIGetAndRemoveMsg(uint32_t *arg1,int arg2,int arg3,int arg4); /* 0x080a7ce0 p-ai.c */
void PlayerAIClearMsg(int arg1); /* 0x080a7d80 p-ai.c */
void PlayerAIMsgStateUpdate(int player); /* 0x080a7d90 p-ai.c */
void PlayerAISctrlProjectile(int arg1,uint32_t *arg2); /* 0x080a7de0 p-ai.c */
void AIForNormal(int player,int arg2); /* 0x080a7e00 p-ai.c */
uint32_t AIForNormalDecisions(int player,int arg2); /* 0x080a7f30 p-ai.c */
uint32_t AIMovePlanRoute(int arg1,uint32_t arg2,int arg3,int arg4); /* 0x080a86d0 p-ai.c */
uint32_t AIMoveReachedDest(int arg1); /* 0x080a88d0 p-ai.c */
uint32_t AIMoveReachedDestIdx(int arg1,int arg2); /* 0x080a8910 p-ai.c */
uint32_t AIForNormalIdle(int arg1); /* 0x080a8a10 p-ai.c */
void AISetIdleAction(int arg1,uint32_t arg2); /* 0x080a8ad0 p-ai.c */
uint32_t AIForNormalMove(int player); /* 0x080a8ae0 p-ai.c */
uint32_t AIForNormalAttack(int player,int arg2); /* 0x080a8dd0 p-ai.c */
uint32_t AIAttackSetupAttack(int arg1,uint32_t arg2,uint32_t arg3); /* 0x080a8fb0 p-ai.c */
uint32_t AIForNormalGuard(int player,int arg2); /* 0x080a8fe0 p-ai.c */
int AIAttackInRange(int player,uint32_t arg2,int player2,int arg4); /* 0x080a90c0 p-ai.c */
int AIBuildCounterAttackList(int player,uint32_t arg2); /* 0x080a93a0 p-ai.c */
uint32_t AIForNormalRandom(int player,int player2,int arg3); /* 0x080a9640 p-ai.c */
void AIForTrainingMode(int player,int arg2); /* 0x080a9e50 p-ai.c */
uint32_t AICheckForAttacks(int arg1); /* 0x080aa560 p-ai.c */
void AIValMake(float *arg1,float arg2); /* 0x080aa600 p-ai.c */
float * AIValMerge(float *arg1,float arg2,float arg3,float arg4,float arg5,float arg6,float arg7,float arg8); /* 0x080aa650 p-ai.c */
void AIValMergeR(float *arg1,float arg2,float arg3,float arg4,int arg5); /* 0x080aa720 p-ai.c */
uint32_t AILearnStopRecord(int arg1); /* 0x080aa780 p-ai.c */
void AIMergeLearnData(int *arg1,int arg2,int arg3); /* 0x080aa7b0 p-ai.c */
uint32_t AIChangeState(int arg1,uint32_t arg2); /* 0x080ab080 p-ai.c */
void AIKBReleaseDir(int arg1); /* 0x080ab0a0 p-ai.c */
void AIKBReleaseDirExcept(int arg1,uint32_t arg2); /* 0x080ab0e0 p-ai.c */
void AIKBReleaseAll(int arg1); /* 0x080ab130 p-ai.c */
void AIKBReleaseAllExcept(int arg1,uint32_t arg2); /* 0x080ab170 p-ai.c */
int PlayerNearestEnemy(int player); /* 0x080ab1c0 p-info.c */
int PartnerAccess(int player,int n); /* 0x080ab3b0 p-info.c */
int PartnerCount(int player); /* 0x080ab430 p-info.c */
int EnemyAccess(int player,int n); /* 0x080ab4b0 p-info.c */
int EnemyCount(int player); /* 0x080ab540 p-info.c */
uint32_t EnemyAccessNear(int player,int n); /* 0x080ab5d0 p-info.c */
int PlayerAccessID(int id); /* 0x080ab6d0 p-info.c */
int PlayerGetDamagedLife(int player); /* 0x080ab740 p-info.c */
uint32_t PlayerInCorner(int player); /* 0x080ab760 p-info.c */
int PlayerDistX(int player,int player2); /* 0x080ab7e0 p-info.c */
int PlayerBodyDistX(int player,int player2); /* 0x080ab830 p-info.c */
uint32_t PlayerInAnyGuardDist(int arg1); /* 0x080ab930 p-info.c */
uint32_t PlayerInGuardDist(int arg1,int player); /* 0x080ab9f0 p-info.c */
bool HitdefAffectTeam(int arg1,int arg2,uint32_t arg3); /* 0x080abab0 p-info.c */
uint32_t PlayerAreEnemies(int player,int player2); /* 0x080abae0 p-info.c */
int PlayerGetWidth(int player,int arg2,uint32_t arg3); /* 0x080abb10 p-info.c */
bool PlayerAnimExist(int player,int action); /* 0x080abbf0 p-info.c */
bool PlayerSelfAnimExist(int *player,int action); /* 0x080abc20 p-info.c */
uint32_t PlayerLyingDead(int player); /* 0x080abc70 p-info.c */
int * PlayerFindTarget(int array,int arg2); /* 0x080abc90 p-info.c */
uint32_t TargetAccessID(int array,int arg2); /* 0x080abcc0 p-info.c */
int TargetCount(int array,int arg2); /* 0x080abd00 p-info.c */
void PlayerKBUpdate(int *player); /* 0x080abd40 p-input.c */
int PlayerCacheLoad(int charno); /* 0x080ac660 p-make.c */
void PlayerCacheFree(int arg1); /* 0x080ac930 p-make.c */
int PlayerCacheFreePriority(int arg1,int arg2); /* 0x080ac950 p-make.c */
void PlayerCacheChangePriority(int arg1,int arg2); /* 0x080ac9b0 p-make.c */
bool PlayerIsCached(int charno); /* 0x080aca00 p-make.c */
void PlayerCacheClear(void); /* 0x080aca40 p-make.c */
uint32_t PlayerCacheHasUnused(void); /* 0x080acb40 p-make.c */
void * PlayerDefLoad(char *dirname,char *filename); /* 0x080acba0 p-make.c */
int * PlayerDefLoadZip(char *dirname,int *mf); /* 0x080acc70 p-make.c */
char * PlayerDefLoadPtr(char *dirname,FILE *fp); /* 0x080ada90 p-make.c */
uint32_t PlayerCNSLoadTP(int chardef,int tp); /* 0x080ae4a0 p-make.c */
bool PlayerSTLoadTP(int player,int tp); /* 0x080aeca0 p-make.c */
uint32_t PlayerSTLoadAppend(int player,char *filename); /* 0x080aecd0 p-make.c */
uint32_t PlayerCMDLoad(char *filename,uint32_t *arg2); /* 0x080aed20 p-make.c */
uint32_t PlayerCMDLoadTP(uint32_t tp,uint32_t *arg2); /* 0x080aed90 p-make.c */
uint32_t ParseCMD(int *arg1,char *arg2,uint32_t *arg3); /* 0x080af400 p-make.c */
uint32_t ParseCMDElem(uint8_t *arg1,uint32_t *arg2,uint32_t *arg3); /* 0x080af680 p-make.c */
void CmdSetFreeLabel(int arg1); /* 0x080af780 p-make.c */
void StringArrayFree(void *arg1,int arg2); /* 0x080af7b0 p-make.c */
void CmdSetDeInit(int *arg1); /* 0x080af800 p-make.c */
void PlayerRCFree(void *arg1); /* 0x080af870 p-make.c */
int * PlayerNew(int chardef); /* 0x080af8f0 p-make.c */
int GetRampedAILevel(void); /* 0x080afcc0 p-make.c */
uint32_t PlayerChangePal(int player,int palno); /* 0x080afdd0 p-make.c */
void PlayerFree(int *player); /* 0x080aff80 p-make.c */
uint32_t PlayerCheck(int *arg1); /* 0x080b0090 p-make.c */
void ResetPersistVar(uint32_t *arg1); /* 0x080b02d0 p-make.c */
void GameResetPersistVars(void); /* 0x080b02f0 p-make.c */
void TeamResetPersistVars(int arg1); /* 0x080b0310 p-make.c */
void PlayerSavePersistVars(int arg1,uint32_t *arg2); /* 0x080b03a0 p-make.c */
void PlayerRestorePersistVars(int arg1,int arg2); /* 0x080b0410 p-make.c */
void GameLoadAndActivateTeam(int arg1); /* 0x080b0470 p-make.c */
void GameActivateAI(void); /* 0x080b0560 p-make.c */
uint32_t GameLoadAndCreateChars(int arg1); /* 0x080b0610 p-make.c */
uint32_t GameFreeChars(int arg1); /* 0x080b09d0 p-make.c */
uint32_t GameFreePlayerDependencies(int *arg1); /* 0x080b0b50 p-make.c */
int TeamReorderAll(int arg1); /* 0x080b0cb0 p-make.c */
void PlayerReset(int *player); /* 0x080b0fe0 p-update.c */
int PlayerEnableSet(int player,int enable); /* 0x080b15d0 p-update.c */
uint8_t PlayerChangeState(int player,int stateno); /* 0x080b1730 p-update.c */
int * PlayerLifeSet(int player,uint32_t life); /* 0x080b17d0 p-update.c */
void PlayerLifeSetNoIcon(int player,uint32_t life); /* 0x080b18d0 p-update.c */
void PlayerPowerSet(int player,uint32_t power); /* 0x080b1950 p-update.c */
void PlayerChangeAnim(int *player,int action); /* 0x080b1990 p-update.c */
void PlayerChangeAnimElem(int *player,int action,int elem); /* 0x080b1a10 p-update.c */
void PlayerSelfAnim(int *player,int action); /* 0x080b1ac0 p-update.c */
void PlayerSelfAnimElem(int *player,int action,int elem); /* 0x080b1ae0 p-update.c */
uint32_t PlayerAutoTurn(int player,int opponent,int arg3); /* 0x080b1b00 p-update.c */
void PlayerTurnAround(int player); /* 0x080b1bc0 p-update.c */
void PlayerUpdate(int *player); /* 0x080b1bf0 p-update.c */
uint32_t PlayerUpdateBindTo(int player); /* 0x080b2cf0 p-update.c */
void ScreenBound(int player); /* 0x080b2db0 p-update.c */
void StageBound(int player); /* 0x080b2f00 p-update.c */
void GameClsnUpdate(void); /* 0x080b2fa0 p-update.c */
void PlayerPushCheck(int player,int player2,int arg3); /* 0x080b3430 p-update.c */
void PlayerCheckOverlap(int player,int player2); /* 0x080b36a0 p-update.c */
uint32_t PlayerCheckP1HitP2(int player,int player2); /* 0x080b37d0 p-update.c */
bool PlayerCheckHit(int player,int player2); /* 0x080b3830 p-update.c */
void Player1HitP2(int *player,int *player2); /* 0x080b3b40 p-update.c */
uint32_t PlayerGetHit(int *arg1,int *player,int arg3,float arg4,float arg5,float arg6,int arg7,int arg8,int arg9); /* 0x080b4400 p-update.c */
void PlayerTakeDamage(int player,int arg2,int arg3,int arg4); /* 0x080b4f10 p-update.c */
int PlayerGetCorrectedDamage(int arg1,int arg2,int player); /* 0x080b4fa0 p-update.c */
uint32_t PlayerGetHitG(int *arg1,int *player,int arg3,int arg4); /* 0x080b5040 p-update.c */
uint32_t PlayerCheckReversal(int player,int player2); /* 0x080b5310 p-update.c */
void Player1ReverseP2(int *player,int *player2); /* 0x080b5510 p-update.c */
void PlayerCheckHitProj(int player,int *arg2); /* 0x080b5a90 p-update.c */
void PlayerCheckProjHit(int *player,int *player2); /* 0x080b5db0 p-update.c */
uint32_t PlayerProjDoHit(int player); /* 0x080b6760 p-update.c */
uint32_t CheckProjHitProj(int arg1,int arg2); /* 0x080b67e0 p-update.c */
uint32_t PlayerCheckFlagHit(int player,uint32_t arg2); /* 0x080b6a60 p-update.c */
uint32_t PlayerCheckAttrHit(int arg1,uint32_t arg2); /* 0x080b6b00 p-update.c */
bool AttrMatch(uint32_t arg1,uint32_t arg2); /* 0x080b6b20 p-update.c */
void PlayerAttrStateSet(int player); /* 0x080b6b40 p-update.c */
void PlayerDropBoundTargets(int arg1,int *arg2); /* 0x080b6ba0 p-update.c */
int PlayerSparkCreate(int *arg1,int arg2,int arg3,int arg4,int arg5,uint32_t arg6,int arg7); /* 0x080b6c60 p-update.c */
int PlayerMakeDust(int player); /* 0x080b6da0 p-update.c */
int PlayerCalcDraw(int player); /* 0x080b6f40 p-update.c */
void PlayerDrawAnim(int player,float arg2); /* 0x080b71c0 p-update.c */
void PlayerDrawShadow(int player,int *arg2,int *arg3); /* 0x080b73c0 p-update.c */
void PlayerDrawClsn(int player,float arg2); /* 0x080b79b0 p-update.c */
uint32_t PalGrpAdd(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6); /* 0x080b8460 pal.c */
void PalGrpRemove(PalGrpFlag f); /* 0x080b8610 pal.c */
uint32_t PalGrpAddSpr(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6); /* 0x080b86d0 pal.c */
void PalGrpBuildFight(void); /* 0x080b8730 pal.c */
uint32_t * PalGrpClear(void); /* 0x080b8960 pal.c */
void PalGrpResetPalette(void); /* 0x080b89e0 pal.c */
void PalGrpSetAdd(PalGrpFlag f,int r,int g_local,int b); /* 0x080b8a20 pal.c */
void PalGrpSetMul(PalGrpFlag f,int r,int g_local,int b); /* 0x080b8ac0 pal.c */
void PalGrpSetInvertAll(PalGrpFlag f,int invert); /* 0x080b8b70 pal.c */
void PalGrpSetColorBal(PalGrpFlag f,int colorbal); /* 0x080b8c00 pal.c */
void PalGrpSetClear(PalGrpFlag f); /* 0x080b8c90 pal.c */
PalGrpFlag * PalGrpMakeFlag(PalGrpFlag *ret_storage,uint32_t group,int unused); /* 0x080b8d10 pal.c */
PalGrpFlag * PalGrpMakeFlagALL(PalGrpFlag *ret_storage); /* 0x080b8d80 pal.c */
PalGrpFlag * PalGrpOrFlag(PalGrpFlag *ret_storage,PalGrpFlag a,PalGrpFlag b); /* 0x080b8dd0 pal.c */
PalGrpFlag * PalGrpXorFlag(PalGrpFlag *ret_storage,PalGrpFlag a,PalGrpFlag b); /* 0x080b8e20 pal.c */
int PalGrpAndFlagZero(PalGrpFlag a,PalGrpFlag b); /* 0x080b8e70 pal.c */
int PalGrpFlagEqual(PalGrpFlag a,PalGrpFlag b); /* 0x080b8e90 pal.c */
int PalGrpFlagIsNonZero(PalGrpFlag a); /* 0x080b8eb0 pal.c */
void PalFXReset(uint32_t *arg1); /* 0x080b8ed0 pal.c */
void PalFXUpdate(int *arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7,int arg8); /* 0x080b8f10 pal.c */
uint32_t * ProjArrayNew(size_t arg1,uint32_t arg2,uint32_t arg3); /* 0x080b9170 projctl.c */
void ProjArrayFree(uint32_t *arg1); /* 0x080b91e0 projctl.c */
int ProjArrayAdd(int *arg1,int *arg2,void *arg3,int arg4); /* 0x080b9210 projctl.c */
void ProjArrayDelete(int *arg1,int arg2); /* 0x080b92b0 projctl.c */
void ProjArrayUpdate(int *arg1); /* 0x080b9310 projctl.c */
void ProjArrayCalcDraw(int *arg1); /* 0x080b9670 projctl.c */
int ProjArrayCountActive(int *arg1); /* 0x080b97a0 projctl.c */
int ProjArrayCountActiveID(int *arg1,int arg2); /* 0x080b97e0 projctl.c */
uint32_t ProjClsnDetect(int *arg1,int *arg2,int arg3,int arg4,int arg5); /* 0x080b9830 projctl.c */
uint32_t ProjArrayDraw(int *arg1); /* 0x080b9910 projctl.c */
void ProjArrayDrawShadow(int *arg1); /* 0x080b9980 projctl.c */
void ProjDrawShadow(int arg1,int *arg2,uint32_t arg3,int *arg4); /* 0x080b9a00 projctl.c */
void ProjArrayClsnDraw(int *arg1,float arg2); /* 0x080b9ea0 projctl.c */
void ProjClsnDraw(int arg1,float arg2); /* 0x080b9ee0 projctl.c */
void GameSndPlay(int *sounds,int group,int number,int arg4); /* 0x080b9fd0 sound.c */
void GameSndPlayID(int arg1,int *sounds,int arg3,int arg4,int arg5); /* 0x080ba000 sound.c */
int GameSndPlayIDPos(int arg1,int arg2,int *sounds,int arg4,int arg5,int arg6); /* 0x080ba090 sound.c */
int ScrPositionToPan(int x); /* 0x080ba180 sound.c */
uint32_t PanVolumeAdjust(int vol,int pan); /* 0x080ba230 sound.c */
void GameSetVol(int arg1,uint32_t arg2); /* 0x080ba2a0 sound.c */
int PlayerSndID(int player,int channel); /* 0x080ba330 sound.c */
void ParseSndGI(int tp,char *keyname,uint32_t *out,int defval); /* 0x080ba360 sound.c */
uint32_t SCtrlParseElemType(int tp,int elem2,int player); /* 0x080ba390 st-ctrl.c */
bool SCtrlParseElem(int tp,int *elems,uint32_t arg3,int player); /* 0x080bee10 st-ctrl.c */
uint32_t PlayerDoSCtrlApplyElem(int *player,int elem,int *arg3); /* 0x080bf1d0 st-ctrl.c */
uint32_t PlayerSCtrlApplyElem(int *player,int elem,int *arg3); /* 0x080bf290 st-ctrl.c */
uint32_t SCtrlRCElemFree(uint32_t *arg1); /* 0x080c3630 st-ctrl.c */
char * TPGetValuePrefix(int tp,uint32_t arg2,uint32_t arg3); /* 0x080c3810 st-exprn.c */
char * StringAdd(char *arg1,uint32_t arg2,uint32_t arg3); /* 0x080c3850 st-exprn.c */
uint32_t SCtrlParseAftImgParams(int tp,int player,int *expr,uint32_t arg4); /* 0x080c3880 st-exprn.c */
uint32_t SCtrlInitAftImgParams(int expr,int arg2,uint32_t arg3,int *player); /* 0x080c3e20 st-exprn.c */
void AftImgParamsEFree(int *expr); /* 0x080c40c0 st-exprn.c */
uint32_t SCtrlParseEnvShake(int tp,int player,int *expr,uint32_t arg4); /* 0x080c41f0 st-exprn.c */
uint32_t SCtrlInitEnvShake(int *expr,uint32_t *arg2,int *player); /* 0x080c4310 st-exprn.c */
void EnvShakeEFree(int *expr); /* 0x080c43e0 st-exprn.c */
uint32_t SCtrlParseExplod(int tp,int player,int *expr,int arg4); /* 0x080c4420 st-exprn.c */
void ExplodInfoFree(int *expr); /* 0x080c4b10 st-exprn.c */
bool SCtrlParsePalFX(int tp,int player,int arg3,int arg4); /* 0x080c4c90 st-exprn.c */
uint32_t SCtrlInitPalFX(int *arg1,uint32_t *arg2,int player); /* 0x080c4e80 st-exprn.c */
void PalFXEFree(int arg1); /* 0x080c5020 st-exprn.c */
uint32_t SCtrlParsePlaySndInfo(int tp,int player,int *expr); /* 0x080c50c0 st-exprn.c */
int SCtrlDoPlaySndInfo(int *player,int expr); /* 0x080c52a0 st-exprn.c */
void PlaySndInfoFree(int *expr); /* 0x080c55f0 st-exprn.c */
bool SCtrlParseHitOverride(int tp,int player,int *arg3); /* 0x080c5650 st-exprn.c */
uint32_t SCtrlInitHitOverride(uint32_t *arg1,uint32_t *arg2,int player); /* 0x080c5740 st-exprn.c */
void HitOverrideEFree(int arg1); /* 0x080c57e0 st-exprn.c */
bool SCtrlParseHitDef(int tp,int player,uint32_t *hitdef); /* 0x080c5810 st-exprn.c */
uint32_t SCtrlInitHitDef(uint32_t *hitdef_def,int hitdef,int *player); /* 0x080c7360 st-exprn.c */
void HitDefEFree(int arg1); /* 0x080c7f30 st-exprn.c */
uint32_t SCtrlParseProjectile(int tp,int player,int *expr); /* 0x080c83a0 st-exprn.c */
int SCtrlInitProjectile(int expr,int *player,int arg3,int *arg4); /* 0x080c8b90 st-exprn.c */
void ProjMakeInfoFree(int *expr); /* 0x080c93d0 st-exprn.c */
bool SCtrlParseHelper(int tp,int player,char *arg3); /* 0x080c95c0 st-exprn.c */
void HelperInfoFree(int arg1); /* 0x080c9a90 st-exprn.c */
bool SCtrlParsePause(int tp,int player,int *expr); /* 0x080c9bc0 st-exprn.c */
uint32_t SCtrlInitPause(int expr,int arg2,int player); /* 0x080c9c50 st-exprn.c */
void PauseInfoFree(int *expr); /* 0x080c9d80 st-exprn.c */
bool SCtrlParseSuperPause(int tp,int player,int *expr); /* 0x080c9dc0 st-exprn.c */
void SuperPauseInfoFree(int *expr); /* 0x080c9f50 st-exprn.c */
void MoreExpFree(int *expr); /* 0x080c9fd0 st-exprn.c */
char * SCtrlParseTrigger(char *text,int player,uint32_t *arg3,void *arg4,int arg5,int *arg6); /* 0x080ca000 st-trig.c */
uint32_t SCtrlParseTriggerCMD(char *arg1,int arg2,int arg3,uint32_t *arg4); /* 0x080ccef0 st-trig.c */
uint32_t SCtrlParseTriggerRange(char *arg1,int arg2,int *arg3); /* 0x080ccfc0 st-trig.c */
char SCtrlTrigArity(int trigger); /* 0x080cd2b0 st-trig.c */
uint32_t SCtrlTrigArrayTest(int *player,int triggers,int num_groups); /* 0x080cd2f0 st-trig.c */
bool SCtrlTrigTest(int *player,int *expr); /* 0x080cd3c0 st-trig.c */
void SCtrlTrigEval(int *player,int *trigger); /* 0x080cd450 st-trig.c */
void TriggerFree(void *arg1); /* 0x080d0740 st-trig.c */
uint32_t trigcpy(int *arg1,int *arg2); /* 0x080d0780 st-trig.c */
char SPopI(int player,int *out); /* 0x080d0830 state-i.c */
char SPopF(uint32_t arg1,float *out); /* 0x080d0900 state-i.c */
uint32_t StackUnderflow(void); /* 0x080d09a0 state-i.c */
uint32_t ItoP_TPConstI(int tp,char *keyname,int *expr,int player,int defval); /* 0x080d09c0 state-i.c */
uint32_t ItoP_TPConstF(int tp,char *keyname,int *expr,int player,int defval); /* 0x080d0a30 state-i.c */
uint8_t * SCtrlReadExpList(uint8_t *text,char *types,int player,uint32_t *end,...); /* 0x080d0aa0 state-i.c */
int SCtrlReadExpListArray (uint8_t *param_1,char *param_2,int param_3,uint32_t *param_4,int param_5,int param_6, int *param_7,int param_8); /* 0x080d0c90 state-i.c */
int ParsePosType(char *arg1); /* 0x080d0e80 state-i.c */
uint32_t ParseSpecialFlag(char *arg1,uint32_t *arg2,uint32_t *arg3); /* 0x080d0ee0 state-i.c */
bool ParseAnim(uint8_t *text,int *arg2,uint32_t *arg3,int player); /* 0x080d12f0 state-i.c */
uint32_t ParseSnd(uint8_t *text,int *arg2,int *arg3,uint32_t *arg4,int player); /* 0x080d1370 state-i.c */
bool ParseVel(uint8_t *text,int *expr,int *expr2,int player); /* 0x080d13f0 state-i.c */
uint32_t ParseHitAttr(int arg1,int arg2); /* 0x080d1530 state-i.c */
uint32_t ParseHitFlag(char *arg1); /* 0x080d1850 state-i.c */
void PlayerGetRedirInfo(int player,uint32_t *arg2); /* 0x080d18e0 state-i.c */
int * SctrlReadFileTP(int tp,int player); /* 0x080d19b0 state.c */
uint32_t SctrlAddFileTP(int *arg1,int tp,int player); /* 0x080d1b30 state.c */
uint32_t SCtrlParseState(int tp,int *elems,int *expr,int player); /* 0x080d1c90 state.c */
uint32_t SCtrlInit(uint32_t *arg1,uint32_t arg2); /* 0x080d2460 state.c */
void SCtrlRCFree(uint32_t *arg1); /* 0x080d2480 state.c */
uint32_t PlayerSCtrlUpdate(int *player); /* 0x080d2590 state.c */
void PlayerSCtrlUpdateSpec(int *player,int arg2,uint32_t arg3); /* 0x080d2a60 state.c */
uint32_t GameLoadSystem(void); /* 0x080d2b60 system.c */
void GameUnloadSystem(void); /* 0x080d39b0 system.c */
int GameReloadSystemSprSnd(void); /* 0x080d3b40 system.c */
void GameUnloadSystemSprSnd(void); /* 0x080d3dd0 system.c */
uint32_t GameConfigRead(char *filename); /* 0x080d3e70 system.c */
void GameResetOptions(void); /* 0x080d4ea0 system.c */
uint32_t GameLoadOptions(void); /* 0x080d4ef0 system.c */
void GameSaveOptions(void); /* 0x080d51e0 system.c */
bool PlayerLoadKeys(int tp,int keycfg,char *group); /* 0x080d5480 system.c */
void PlayerSaveKeys(int tp,int keycfg,char *group); /* 0x080d5580 system.c */
void PlayerKeysRemoveZero(int keycfg,uint32_t value); /* 0x080d56a0 system.c */
void PlayerKeysConvertToZero(int keycfg,int value); /* 0x080d56d0 system.c */
uint32_t PrecacheInit(int arg1); /* 0x080d5700 precache.c */
uint32_t PrecacheRequestTeam(int arg1); /* 0x080d5770 precache.c */
void PrecacheRequestCurArcadeTeam(void); /* 0x080d57f0 precache.c */
void PrecacheRequestNextArcadeTeam(void); /* 0x080d5800 precache.c */
uint32_t PrecacheRequestArcadeTeam(int arg1); /* 0x080d5810 precache.c */
bool PrecacheRequestChar(int arg1); /* 0x080d58a0 precache.c */
uint32_t PrecacheStart(void); /* 0x080d5900 precache.c */
void PrecacheRequestCancel(void); /* 0x080d59f0 precache.c */
int PrecacheIsRunning(void); /* 0x080d5a30 precache.c */
uint32_t PrecacheIsDone(void); /* 0x080d5a70 precache.c */
void PrecacheFinish(void); /* 0x080d5ad0 precache.c */
void PrecacheWorkerThread(void); /* 0x080d5b60 precache.c */
bool IntQueueAddUnique(int *queue,int value,int size); /* 0x080d5d90 precache.c */
bool IntQueueIsEmpty(int *queue); /* 0x080d5df0 precache.c */
uint32_t IntQueuePeekTop(int *queue,int *out); /* 0x080d5e00 precache.c */
uint32_t IntQueueDequeue(int *queue,int *out); /* 0x080d5e20 precache.c */
uint32_t * IntQueueClear(uint32_t *queue); /* 0x080d5e60 precache.c */

/* ---- library functions called by the game (non-libc) ---- */
uint32_t install_mod(int param_1); /* 0x080d5e70 mod.c */
uint8_t * load_mod(uint8_t * param_1); /* 0x080d60e0 mod.c */
uint32_t play_mod(int param_1, int param_2); /* 0x080d62a0 mod.c */
uint32_t destroy_mod(void * param_1); /* 0x080d6ab0 mod.c */
uint32_t remove_mod(void); /* 0x080d6f40 mod.c */
uint32_t stop_mod(void); /* 0x080d7100 mod.c */
uint32_t pause_mod(void); /* 0x080d71c0 mod.c */
uint32_t resume_mod(void); /* 0x080d7240 mod.c */
uint32_t set_mod_volume(int param_1); /* 0x080d7310 mod.c */
uint32_t get_mod_volume(void); /* 0x080d7390 mod.c */
uint32_t load_amp(char * param_1, uint32_t param_2); /* 0x080e0b10 audiolib.c */
uint32_t poll_amp(void); /* 0x080e0f80 audiolib.c */
int install_amp(void); /* 0x080e14f0 audiolib.c */
uint32_t unload_amp(void); /* 0x080e1640 audiolib.c */
uint32_t set_volume_mp3(int param_1); /* 0x080e17c0 audiolib.c */
uint32_t get_volume_mp3(void); /* 0x080e17d0 audiolib.c */
uint32_t install_allegro(uint32_t param_1, int * param_2, uint8_t * param_3); /* 0x080ed330 allegro.c */
uint32_t allegro_exit(void); /* 0x080ed610 allegro.c */
uint32_t blit(int * param_1, int * param_2, int param_3, int param_4, int param_5, int param_6, uint32_t param_7, int param_8); /* 0x080f2d60 blit.c */
uint32_t makecol(uint32_t param_1, int param_2, int param_3); /* 0x080f3340 color.c */
uint32_t override_config_data(int param_1, int param_2); /* 0x080f6570 config.c */
uint32_t vsync(void); /* 0x080fc150 gfx.c */
uint32_t rect(int param_1, int param_2, int param_3, int param_4, int param_5, uint32_t param_6); /* 0x080fd050 gfx.c */
uint32_t set_color_depth(uint32_t param_1); /* 0x080fecb0 graphics.c */
uint32_t set_gfx_mode(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5); /* 0x080fef00 graphics.c */
int * create_bitmap_ex(int param_1, int param_2, int param_3); /* 0x080ffbb0 graphics.c */
int * create_video_bitmap(uint32_t param_1, uint32_t param_2); /* 0x081001b0 graphics.c */
uint32_t destroy_bitmap(int * param_1); /* 0x08100370 graphics.c */
uint32_t set_clip(uint32_t * param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5); /* 0x08100440 graphics.c */
uint32_t show_video_bitmap(int * param_1); /* 0x08100730 graphics.c */
uint32_t install_joystick(int param_1); /* 0x08100b40 joystick.c */
uint32_t remove_joystick(void); /* 0x08100d50 joystick.c */
uint32_t poll_joystick(void); /* 0x08100da0 joystick.c */
uint32_t set_leds(int param_1); /* 0x081014e0 keyboard.c */
uint32_t set_keyboard_rate(int param_1, uint32_t param_2); /* 0x08101530 keyboard.c */
uint32_t install_keyboard(void); /* 0x08101e50 keyboard.c */
uint32_t remove_keyboard(void); /* 0x08101f50 keyboard.c */
uint32_t _alemu_strlwr(char * param_1); /* 0x08102020 libc.c */
int _alemu_stricmp(char * param_1, char * param_2); /* 0x08102080 libc.c */
uint32_t * load_midi(uint8_t * param_1); /* 0x08102850 midi.c */
uint32_t destroy_midi(void * param_1); /* 0x08102d20 midi.c */
uint32_t play_midi(int * param_1, uint32_t param_2); /* 0x08104db0 midi.c */
uint32_t play_looped_midi(int * param_1, uint32_t param_2, uint32_t param_3); /* 0x08104ed0 midi.c */
uint32_t stop_midi(void); /* 0x08104f10 midi.c */
uint32_t midi_pause(void); /* 0x08104f20 midi.c */
uint32_t midi_resume(void); /* 0x08104fb0 midi.c */
uint32_t midi_seek(int param_1); /* 0x08104fe0 midi.c */
uint32_t poll_mouse(void); /* 0x081063a0 mouse.c */
uint32_t mouse_needs_poll(void); /* 0x081063d0 mouse.c */
uint32_t install_mouse(void); /* 0x081064b0 mouse.c */
uint32_t save_pcx(uint8_t * param_1, uint32_t * param_2, uint8_t * param_3); /* 0x081070a0 pcx.c */
uint32_t detect_digi_driver(int param_1); /* 0x08107ee0 sound.c */
uint32_t detect_midi_driver(int param_1); /* 0x08107fa0 sound.c */
uint32_t reserve_voices(uint32_t param_1, uint32_t param_2); /* 0x08108060 sound.c */
int install_sound(int digi, int midi, char *cfg_path);  /* corrected from the library header */ /* 0x08108080 sound.c */
uint32_t remove_sound(void); /* 0x08108ef0 sound.c */
uint32_t set_volume(int param_1, int param_2); /* 0x081090b0 sound.c */
void lock_sample(void *spl);  /* corrected from the library header */ /* 0x08109160 sound.c */
int * create_sample(int param_1, int param_2, int param_3, size_t param_4); /* 0x08109a20 sound.c */
uint32_t destroy_sample(void * param_1); /* 0x08109ae0 sound.c */
int play_sample(int param_1, uint32_t param_2, int param_3, int param_4, int param_5); /* 0x08109b20 sound.c */
int allocate_voice(int param_1); /* 0x08109da0 sound.c */
uint32_t deallocate_voice(int param_1); /* 0x0810a530 sound.c */
uint32_t reallocate_voice(int param_1, int param_2); /* 0x0810a5a0 sound.c */
uint32_t voice_start(int param_1); /* 0x0810a6b0 sound.c */
uint32_t voice_stop(int param_1); /* 0x0810a6f0 sound.c */
uint32_t voice_check(int param_1); /* 0x0810a740 sound.c */
uint32_t voice_get_position(int param_1); /* 0x0810a790 sound.c */
uint32_t voice_set_position(int param_1, uint32_t param_2); /* 0x0810a7c0 sound.c */
uint32_t voice_set_playmode(int param_1, uint32_t param_2); /* 0x0810a7f0 sound.c */
int voice_get_volume(int param_1); /* 0x0810a860 sound.c */
uint32_t voice_set_volume(int param_1, int param_2); /* 0x0810a8d0 sound.c */
uint32_t voice_get_frequency(int param_1); /* 0x0810aa30 sound.c */
uint32_t voice_set_frequency(int param_1, int param_2); /* 0x0810aa60 sound.c */
int voice_get_pan(int param_1); /* 0x0810ab80 sound.c */
uint32_t voice_set_pan(int param_1, int param_2); /* 0x0810abd0 sound.c */
uint32_t rest(uint32_t param_1); /* 0x0810d140 timer.c */
uint32_t install_int_ex(int param_1, int param_2); /* 0x0810d460 timer.c */
uint32_t remove_int(int param_1); /* 0x0810d4d0 timer.c */
uint32_t install_timer(void); /* 0x0810d5a0 timer.c */
uint32_t remove_timer(void); /* 0x0810d810 timer.c */
uint32_t stretch_blit(int param_1, int param_2, int param_3, uint32_t param_4, int param_5, int param_6, uint32_t param_7, int param_8, int param_9, int param_10); /* 0x0811e420 istretch.c */
int __pthread_yield(void); /* 0x0814cf80 lvga.c */
int __pthread_create_2_1(pthread_t * __newthread, pthread_attr_t * __attr, __start_routine * __start_routine, void * __arg); /* 0x0814cf90 lvga.c */
uint32_t cd_init(char * param_1); /* 0x081bbac0 linux.c */
uint8_t cd_exit(void); /* 0x081bbb30 linux.c */
uint32_t cd_play(uint32_t param_1); /* 0x081bbb60 linux.c */
uint32_t cd_play_now(uint32_t param_1); /* 0x081bbc10 linux.c */
uint32_t cd_play_loop(uint32_t param_1); /* 0x081bbcc0 linux.c */
bool cd_is_playing(void); /* 0x081bbef0 linux.c */
uint8_t cd_current_track(void); /* 0x081bbf10 linux.c */
uint8_t cd_pause(void); /* 0x081bbf40 linux.c */
uint8_t cd_resume(void); /* 0x081bbf60 linux.c */
bool cd_is_paused(void); /* 0x081bbf90 linux.c */
uint8_t cd_stop(void); /* 0x081bbfb0 linux.c */
uint32_t cd_get_tracks(uint32_t * param_1, uint32_t * param_2); /* 0x081bbfd0 linux.c */
uint32_t cd_is_audio(uint8_t param_1); /* 0x081bc040 linux.c */
uint8_t cd_get_volume(uint32_t * param_1, uint32_t * param_2); /* 0x081bc0b0 linux.c */
void cd_set_volume(int l, int r); /* 0x081bc100 linux.c */
uint8_t cd_eject(void); /* 0x081bc170 linux.c */
uint8_t cd_close(void); /* 0x081bc190 linux.c */
uint32_t crc32(uint32_t param_1, uint8_t * param_2, uint32_t param_3); /* 0x081bc1b0 crc32.c */
uint64_t inflateInit2_(int param_1, int param_2, char * param_3, int param_4); /* 0x081bc2a0 inflate.c */
uint32_t inflate(int * param_1, int param_2); /* 0x081bc450 inflate.c */
uint32_t inflateEnd(int param_1); /* 0x081bc920 inflate.c */
long __random(void); /* 0x081c57e0 zutil.c */
int _IO_fprintf(FILE * __stream, char * __format, ...); /* 0x081d4db0 zutil.c */
int _IO_printf(char * __format, ...); /* 0x081d4dd0 zutil.c */
int _IO_sscanf(char * __s, char * __format, ...); /* 0x081d4e60 zutil.c */
int __new_fclose(FILE * stream); /* 0x081d4ed0 zutil.c */
char * _IO_fgets(char * s, int n, FILE * stream); /* 0x081d50f0 zutil.c */
FILE * __new_fopen(char * __filename, char * __modes); /* 0x081d5210 zutil.c */
int _IO_vsprintf(char * __s, char * __format, __gnuc_va_list __arg); /* 0x081d5ae0 zutil.c */
int _IO_vsscanf(char * __s, char * __format, __gnuc_va_list __arg); /* 0x081d5b80 zutil.c */
int _IO_feof(FILE * __stream); /* 0x081d7f30 zutil.c */
void * __libc_malloc(size_t __size); /* 0x081dc150 zutil.c */
void * __realloc(void * __ptr, size_t __size); /* 0x081dcfd0 zutil.c */
void * __libc_calloc(size_t __nmemb, size_t __size); /* 0x081ddbb0 zutil.c */
int __access(char * __name, int __type); /* 0x081e5c10 zutil.c */
int __chdir(char * __path); /* 0x081e5ec0 zutil.c */
