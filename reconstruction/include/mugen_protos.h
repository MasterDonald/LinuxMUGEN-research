/* Prototypes recovered by Ghidra Decompiler Parameter ID for every
 * Elecbyte function and every library function the game calls.
 * Generated; types are decompiler types, not original declarations. */
#pragma once
#include "ghidra_compat.h"

/* ---- Elecbyte functions ---- */
int * AnimRCReadFile(char *param_1); /* 0x08048200 anim-lib.c */
int * AnimRCReadFileTP(int param_1); /* 0x08048290 anim-lib.c */
bool AnimElemParseLine(char *param_1,int param_2,undefined4 param_3,int param_4); /* 0x08048830 anim-lib.c */
uint AnimElemProcessFlipFlags(char *param_1); /* 0x080489b0 anim-lib.c */
undefined4 AnimElemProcessDrawFlags(char *param_1,uint *param_2,uint *param_3); /* 0x08048a00 anim-lib.c */
undefined4 AnimRCFree(int *param_1); /* 0x08048b40 anim-lib.c */
undefined4 * AnimNew(undefined4 param_1,undefined4 param_2); /* 0x08048bf0 anim-lib.c */
void AnimSet(undefined4 *param_1,undefined4 param_2,undefined4 param_3); /* 0x08048c40 anim-lib.c */
void AnimCopy(undefined4 *param_1,undefined4 *param_2); /* 0x08048c70 anim-lib.c */
undefined4 AnimFree(void *param_1); /* 0x08048c90 anim-lib.c */
undefined4 AnimUpdate(undefined4 *param_1); /* 0x08048cd0 anim-lib.c */
int AnimUpdateElemptr(undefined4 *param_1); /* 0x08048d70 anim-lib.c */
void AnimResetAction(int *param_1); /* 0x08048dd0 anim-lib.c */
undefined4 AnimChangeAction(int *param_1,int param_2,int param_3); /* 0x08048e10 anim-lib.c */
undefined4 AnimChangeActionTime(int *param_1,int param_2,int param_3,int param_4); /* 0x08048e30 anim-lib.c */
undefined4 AnimChangeActionElem(int *param_1,int param_2,int param_3,int param_4); /* 0x08048ec0 anim-lib.c */
void AnimDraw(undefined4 *param_1,int param_2,int param_3); /* 0x08048f60 anim-lib.c */
void AnimDrawFlip(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x08048f80 anim-lib.c */
void AnimDrawScale(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5); /* 0x080491e0 anim-lib.c */
void AnimDrawScaleFlip(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5, uint param_6); /* 0x08049210 anim-lib.c */
void AnimDrawRotateFlip(undefined4 *param_1,int param_2,int param_3,float param_4,float param_5, float param_6,uint param_7); /* 0x08049540 anim-lib.c */
void AnimCurIDGrp(undefined4 *param_1); /* 0x08049880 anim-lib.c */
undefined4 AnimCurIDno(undefined4 *param_1); /* 0x080498a0 anim-lib.c */
undefined4 AnimCurElemStartTime(undefined4 *param_1,int param_2); /* 0x080498c0 anim-lib.c */
int AnimElemNo(undefined4 *param_1,int param_2); /* 0x08049900 anim-lib.c */
void AnimIdxToIDGrp(undefined4 *param_1,int param_2); /* 0x080499a0 anim-lib.c */
void AnimIdxToIDno(undefined4 *param_1,int param_2); /* 0x080499c0 anim-lib.c */
uint AnimGrpNoToIdx(undefined4 *param_1,int param_2,int param_3); /* 0x080499e0 anim-lib.c */
undefined4 AnimGetLooptime(undefined4 *param_1); /* 0x08049a00 anim-lib.c */
undefined4 AnimGetLooptimeID(undefined4 *param_1,int param_2,int param_3); /* 0x08049a20 anim-lib.c */
undefined4 AnimGetLoopstarttime(undefined4 *param_1); /* 0x08049a50 anim-lib.c */
undefined4 AnimGetLoopstarttimeID(undefined4 *param_1,int param_2,int param_3); /* 0x08049a70 anim-lib.c */
undefined4 AnimGetTime(int param_1); /* 0x08049aa0 anim-lib.c */
int AnimGetCorrectedTime(undefined4 *param_1); /* 0x08049ab0 anim-lib.c */
undefined4 AnimCurSpriteIdx(int param_1); /* 0x08049ae0 anim-lib.c */
undefined4 * PRSprArrayNew(size_t param_1); /* 0x08049af0 anim-lib.c */
undefined4 PRSprArrayFree(undefined4 *param_1); /* 0x08049b70 anim-lib.c */
void PRSprArrayClear(int *param_1); /* 0x08049bb0 anim-lib.c */
undefined4 PRSprAdd(int *param_1,int *param_2); /* 0x08049bc0 anim-lib.c */
void PRSprDraw(int param_1); /* 0x08049c60 anim-lib.c */
void PRSprArrayDraw(int *param_1); /* 0x08049dd0 anim-lib.c */
int PRSprArrayScale(int *param_1,float param_2); /* 0x08049e10 anim-lib.c */
byte AnimPerUpdate(int param_1); /* 0x08049ef0 anim-lib.c */
void AnimPerDraw(int *param_1,int param_2,int param_3); /* 0x08049f20 anim-lib.c */
void AnimPerDrawScale(int *param_1,int param_2,int param_3,float param_4); /* 0x08049f60 anim-lib.c */
undefined4 * AnimPerArrayNew(size_t param_1); /* 0x0804a000 anim-lib.c */
void AnimPerArrayFree(undefined4 *param_1); /* 0x0804a050 anim-lib.c */
uint AnimPerArrayAdd(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9); /* 0x0804a080 anim-lib.c */
void AnimPerArraySetNo(int *param_1,int param_2,undefined4 param_3); /* 0x0804a150 anim-lib.c */
void AnimPerArrayDelete(int *param_1,int param_2); /* 0x0804a170 anim-lib.c */
void AnimPerArrayClear(int *param_1); /* 0x0804a180 anim-lib.c */
undefined4 AnimPerArrayUpdate(int *param_1); /* 0x0804a190 anim-lib.c */
void AnimPerArrayUpdateGrp(int *param_1,uint param_2); /* 0x0804a1e0 anim-lib.c */
void AnimPerArrayDraw(int *param_1,int param_2,int param_3); /* 0x0804a250 anim-lib.c */
void AnimPerArrayDrawGrp(int *param_1,uint param_2,int param_3,int param_4); /* 0x0804a290 anim-lib.c */
void AnimPerArrayDrawScaleGrp(int *param_1,uint param_2,int param_3,int param_4,float param_5); /* 0x0804a2f0 anim-lib.c */
uint FlipFlagMix(uint param_1,uint param_2); /* 0x0804a350 anim-lib.c */
void AnimDrawSprFlip(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6 ,int param_7,int param_8); /* 0x0804a360 anim-lib.c */
void AnimScaleSpr_S(int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6, undefined4 param_7,int param_8,int param_9); /* 0x0804a650 anim-lib.c */
void AnimRotateSpr(int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6, float param_7,float param_8,float param_9,undefined4 param_10,int param_11, int param_12); /* 0x0804a790 anim-lib.c */
int AlphaMixSrc(int param_1,int param_2); /* 0x0804a900 anim-lib.c */
int AlphaMixDest(int param_1,int param_2); /* 0x0804a910 anim-lib.c */
undefined4 * ArrayNew(size_t param_1,size_t param_2,undefined4 param_3); /* 0x0804a930 array.c */
undefined4 * ArrayCopy(undefined4 *param_1); /* 0x0804a9c0 array.c */
undefined4 * ArrayCopyOnto(undefined4 *param_1,undefined4 *param_2); /* 0x0804aa80 array.c */
undefined4 ArrayFree(void *param_1); /* 0x0804ab00 array.c */
bool ArrayHasSpace(int param_1); /* 0x0804ab50 array.c */
int ArrayAdd(int param_1,void *param_2,undefined4 param_3,undefined4 param_4); /* 0x0804ab60 array.c */
uint ArrayAddUnique(int param_1,void *param_2,int param_3,int param_4); /* 0x0804abf0 array.c */
int ArrayAddResize(int param_1,void *param_2,undefined4 param_3,undefined4 param_4); /* 0x0804ac50 array.c */
uint ArrayAddUniqueResize(int param_1,void *param_2,int param_3,int param_4); /* 0x0804acb0 array.c */
void ArrayDelete(int param_1,int param_2); /* 0x0804ad10 array.c */
void ArrayClear(int param_1); /* 0x0804ada0 array.c */
undefined4 ArrayResize(int param_1,int param_2); /* 0x0804adf0 array.c */
int ArrayFindEmpty(int param_1); /* 0x0804aea0 array.c */
int ArrayAccessSafe(int param_1,int param_2); /* 0x0804af20 array.c */
uint ArrayFind(int param_1,int param_2,int param_3); /* 0x0804af40 array.c */
int ArrayAccessGrpItem(int param_1,int param_2,int param_3); /* 0x0804afe0 array.c */
undefined4 ArrayIdxToGrp(int param_1,int param_2); /* 0x0804b020 array.c */
undefined4 ArrayIdxToItem(int param_1,int param_2); /* 0x0804b040 array.c */
int ArrayScanFirst(int param_1); /* 0x0804b060 array.c */
int ArrayScanNext(int param_1); /* 0x0804b090 array.c */
int ArrayAccessUnsafe(int param_1,int param_2); /* 0x0804b0d0 array.c */
void BGArrayReadFile(char *param_1,char *param_2); /* 0x0804b0f0 bg-lib.c */
char * BGArrayReadFileSA(char *param_1,char *param_2,int param_3,int param_4); /* 0x0804b110 bg-lib.c */
char * BGArrayReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5); /* 0x0804b1d0 bg-lib.c */
undefined4 BGArrayReadCtrlTP(int param_1,int param_2,undefined4 param_3); /* 0x0804bcf0 bg-lib.c */
int BGArrayNew(size_t param_1,undefined4 param_2); /* 0x0804c350 bg-lib.c */
undefined4 BGArrayFree(int param_1); /* 0x0804c3c0 bg-lib.c */
int BGArrayAdd(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9, undefined4 param_10,undefined4 param_11,int param_12,int param_13); /* 0x0804c580 bg-lib.c */
int BGArrayAddAnim(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,int param_7); /* 0x0804c6d0 bg-lib.c */
void BGArraySetViewScale(int param_1,undefined4 param_2); /* 0x0804c7b0 bg-lib.c */
void BGArrayMove(int *param_1,float param_2,float param_3); /* 0x0804c7f0 bg-lib.c */
void BGArrayMoveOffset(int *param_1,float param_2,float param_3,int param_4,int param_5); /* 0x0804c810 bg-lib.c */
void BGArrayDraw(int param_1); /* 0x0804ca00 bg-lib.c */
void BGArrayDrawLayer(int param_1,int param_2); /* 0x0804ca60 bg-lib.c */
void BGArrayUpdate(int param_1); /* 0x0804cad0 bg-lib.c */
void BGArrayCtrlUpdate(int param_1); /* 0x0804cbb0 bg-lib.c */
void BGArrayReset(int param_1); /* 0x0804ce80 bg-lib.c */
undefined4 BGAccess(int param_1,int param_2); /* 0x0804cf70 bg-lib.c */
int BGAccessID(int param_1,int param_2); /* 0x0804cf90 bg-lib.c */
undefined4 BGParalSetup(int param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5, undefined4 param_6,uint param_7,undefined4 param_8); /* 0x0804cfd0 bg-lib.c */
void BGDraw(int param_1,int *param_2); /* 0x0804d1f0 bg-lib.c */
void BGNormalDrawTile(int param_1,int param_2); /* 0x0804d510 bg-lib.c */
void BGAnimDrawTile(undefined4 param_1,int param_2); /* 0x0804d890 bg-lib.c */
void BGParalDraw(int param_1,int param_2); /* 0x0804da00 bg-lib.c */
void BGParalDrawScale(int param_1,int param_2,int param_3); /* 0x0804da20 bg-lib.c */
void BGParalDraw8to16(int param_1,int param_2,int param_3); /* 0x0804dab0 bg-lib.c */
void BGParalDraw8to16_2X(void); /* 0x0804dfb0 bg-lib.c */
void BGParalDraw8to16Flat(int param_1,int param_2,int param_3); /* 0x0804dfc0 bg-lib.c */
void BGParalDraw8to16Flat2X(void); /* 0x0804e420 bg-lib.c */
void BGParalDraw16(void); /* 0x0804e430 bg-lib.c */
int * ClipboardNew(int param_1,size_t param_2); /* 0x0804e440 clipbrd.c */
void ClipboardFree(undefined4 *param_1); /* 0x0804e4e0 clipbrd.c */
void ClipboardClear(undefined4 *param_1); /* 0x0804e530 clipbrd.c */
void ClipboardPrint(int *param_1,char *param_2,...); /* 0x0804e550 clipbrd.c */
size_t ClipboardAppend(int *param_1,char *param_2,...); /* 0x0804e5a0 clipbrd.c */
undefined4 ClsnArrayNew(size_t param_1); /* 0x0804e660 clsn-lib.c */
undefined4 ClsnArrayFree(void *param_1); /* 0x0804e6c0 clsn-lib.c */
undefined4 * ClsnArrayCopy(undefined4 *param_1); /* 0x0804e700 clsn-lib.c */
int ClsnArrayInstance(int param_1); /* 0x0804e750 clsn-lib.c */
bool ClsnArrayAdd(int param_1,undefined4 *param_2); /* 0x0804e760 clsn-lib.c */
void ClsnArrayAddRect(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5); /* 0x0804e7b0 clsn-lib.c */
void * ClsnParseLine(int param_1,int param_2); /* 0x0804e800 clsn-lib.c */
undefined4 ClsnMixDetectRectIndiv(int param_1,int param_2,int param_3,int param_4); /* 0x0804ec00 clsn-lib.c */
undefined4 ClsnMixDetectRect(int param_1,int param_2,int param_3,int param_4); /* 0x0804ec80 clsn-lib.c */
undefined4 ClsnMixDetectRectHFlip1(int param_1,int param_2,int param_3,int param_4); /* 0x0804ed00 clsn-lib.c */
undefined4 ClsnMixDetectRectHFlipAll(int param_1,int param_2,int param_3,int param_4); /* 0x0804eda0 clsn-lib.c */
undefined4 ClsnArrayDetectRect(int *param_1,int *param_2,int param_3,int param_4); /* 0x0804ee40 clsn-lib.c */
undefined4 ClsnArrayDetectRectFlip(int *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6); /* 0x0804eec0 clsn-lib.c */
undefined4 ClsnDetectRect(int param_1,int param_2,int param_3,int param_4); /* 0x0804f030 clsn-lib.c */
undefined4 ClsnDetectRectHFlip1(int param_1,int param_2,int param_3,int param_4); /* 0x0804f080 clsn-lib.c */
undefined4 ClsnDetectRectHFlipAll(int param_1,int param_2,int param_3,int param_4); /* 0x0804f0e0 clsn-lib.c */
void KBUpdateHold(int param_1,int param_2); /* 0x0804f140 cmd-dtct.c */
undefined4 KBFillBuffer(int param_1,int param_2,uint param_3,int param_4); /* 0x0804f160 cmd-dtct.c */
void KBClearCommandValidTimes(undefined4 *param_1); /* 0x0804f3a0 cmd-dtct.c */
void KBClearCommandLastTimes(int param_1); /* 0x0804f3c0 cmd-dtct.c */
void KBCountdownCommandValidTimes(int param_1,char param_2,int param_3); /* 0x0804f3e0 cmd-dtct.c */
bool KBCommandIsValid(int param_1,int param_2); /* 0x0804f420 cmd-dtct.c */
void KBGetCommand(int param_1,int *param_2,int param_3,undefined4 param_4); /* 0x0804f440 cmd-dtct.c */
undefined4 KBGetCommandSpecial(int param_1,int *param_2,int param_3,undefined4 param_4,uint param_5); /* 0x0804f470 cmd-dtct.c */
uint KBGetHoldFlag(int param_1); /* 0x0804f5b0 cmd-dtct.c */
uint KBKeyMap(undefined4 param_1,uint param_2); /* 0x0804f660 cmd-dtct.c */
int KBKeyIndex(int param_1); /* 0x0804f700 cmd-dtct.c */
undefined4 CharMatch(int param_1,int param_2,uint param_3); /* 0x0804f720 cmd-dtct.c */
undefined4 PatternMatch(int param_1,int *param_2,undefined4 *param_3); /* 0x0804f830 cmd-dtct.c */
void KBTimeStuffBuf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x0804f960 cmd-dtct.c */
undefined4 * SceneReadFile(char *param_1,char *param_2,int param_3,int param_4); /* 0x0804f9e0 cutscene.c */
undefined4 * SceneReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5); /* 0x0804faa0 cutscene.c */
int * SiSceneReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5); /* 0x0804fb50 cutscene.c */
void SceneRegisterBGMFn(int *param_1,undefined4 param_2,undefined4 param_3); /* 0x080503b0 cutscene.c */
void SceneReset(int *param_1); /* 0x080503e0 cutscene.c */
void SiSceneReset(int param_1); /* 0x08050410 cutscene.c */
undefined4 SceneUpdate(int *param_1); /* 0x080504b0 cutscene.c */
undefined4 SiSceneUpdate(int *param_1); /* 0x080504e0 cutscene.c */
void SceneUpdatePal(int *param_1); /* 0x08050830 cutscene.c */
void SiSceneUpdatePal(int *param_1); /* 0x08050860 cutscene.c */
void SceneDraw(int *param_1); /* 0x08050970 cutscene.c */
void SiSceneDraw(int *param_1); /* 0x080509a0 cutscene.c */
void SceneFree(void *param_1); /* 0x08050b80 cutscene.c */
undefined4 SiSceneFree(int *param_1); /* 0x08050bd0 cutscene.c */
void * ecalloc(size_t param_1,size_t param_2); /* 0x08050cd0 ebcommon.c */
int ErrorSet(int param_1); /* 0x08050d00 ebcommon.c */
int ErrorGet(void); /* 0x08050d10 ebcommon.c */
char * ErrorGetStr(void); /* 0x08050d20 ebcommon.c */
undefined4 CheckExtension(char *param_1); /* 0x08050d70 ebcommon.c */
uint igetw(_IO_FILE *param_1); /* 0x08050f00 ebcommon.c */
uint igetl(_IO_FILE *param_1); /* 0x08050f40 ebcommon.c */
undefined4 strimatch(char *param_1,char *param_2); /* 0x08050fb0 ebcommon.c */
undefined4 strimatchlen(int param_1,int param_2,int param_3); /* 0x08051000 ebcommon.c */
undefined4 strmatchlen(int param_1,int param_2,int param_3); /* 0x08051050 ebcommon.c */
void strtoupper(undefined1 *param_1,char *param_2); /* 0x08051090 ebcommon.c */
char * splitdirfile(char *param_1,char *param_2,char *param_3); /* 0x080510c0 ebcommon.c */
char * joindirfile(char *param_1,char *param_2,char *param_3); /* 0x08051140 ebcommon.c */
undefined4 isabsolutedir(char *param_1); /* 0x080511c0 ebcommon.c */
long ffilelength(FILE *param_1); /* 0x080511f0 ebcommon.c */
void strcpyslash(int param_1,char *param_2); /* 0x08051230 ebcommon.c */
void IntSwap(undefined4 *param_1,undefined4 *param_2); /* 0x08051260 ebcommon.c */
int IntMin(int param_1,int param_2); /* 0x08051280 ebcommon.c */
int IntMax(int param_1,int param_2); /* 0x08051290 ebcommon.c */
void DebugErrorExit(int param_1); /* 0x080512a0 ebcommon.c */
uint MFgetc(int *param_1); /* 0x08051300 ebcommon.c */
char * MFfgets(char *s,int n,int *mf); /* 0x08051350 ebcommon.c */
size_t MFfread(void *ptr,size_t size,size_t n,int *mf); /* 0x080513f0 ebcommon.c */
int MFfeof(int *param_1); /* 0x080514a0 ebcommon.c */
undefined4 * MFfopenFile(char *param_1,char *param_2); /* 0x080514e0 ebcommon.c */
undefined4 * MFfopenMem(int param_1,int param_2); /* 0x08051540 ebcommon.c */
undefined4 MFzopen(int *param_1,char *param_2); /* 0x08051580 ebcommon.c */
void MFzclose(int param_1); /* 0x08051650 ebcommon.c */
int * MFfopenZip(char *param_1,char *param_2); /* 0x08051660 ebcommon.c */
undefined4 MFfclose(int *param_1); /* 0x080516d0 ebcommon.c */
undefined4 MFfseek(int *param_1,int param_2,int param_3); /* 0x08051770 ebcommon.c */
int MFftell(int *param_1); /* 0x08051810 ebcommon.c */
uint MFigetw(int *param_1); /* 0x08051850 ebcommon.c */
uint MFigetl(int *param_1); /* 0x08051890 ebcommon.c */
int roundfloat(float param_1); /* 0x08051900 ebcommon.c */
char * _getfileonly(char *param_1); /* 0x08051960 ebcommon.c */
void V_FontDrawLine(char *param_1,int *param_2,int param_3,int param_4,uint param_5); /* 0x08051990 font-lib.c */
void V_FontDrawLineBank(char *param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x08051c00 font-lib.c */
void V_FontDraw(char *param_1,int *param_2,int param_3,int param_4,uint param_5); /* 0x08051fd0 font-lib.c */
void V_FontDrawRight(char *param_1,int *param_2,int param_3,int param_4,uint param_5); /* 0x08052000 font-lib.c */
void V_FontDrawCenter(char *param_1,int *param_2,int param_3,int param_4,uint param_5); /* 0x08052030 font-lib.c */
void V_FontDrawBank(char *param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x08052060 font-lib.c */
undefined4 V_FontDrawRightBank(char *param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x08052090 font-lib.c */
void V_FontDrawCenterBank(char *param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x080520c0 font-lib.c */
void V_FontWrite(int *param_1,int param_2,int param_3,uint param_4,char *param_5,...); /* 0x080520f0 font-lib.c */
void V_FontWriteRight(int *param_1,int param_2,int param_3,uint param_4,char *param_5,...); /* 0x08052150 font-lib.c */
void V_FontWriteBank(int *param_1,int param_2,int param_3,int param_4,char *param_5,...); /* 0x080521b0 font-lib.c */
void V_FontDrawAlign_I(char *param_1,int *param_2,int param_3,int param_4,int param_5,uint param_6, int param_7); /* 0x08052210 font-lib.c */
void V_FontDrawAlign(char *param_1,int *param_2,int param_3,int param_4,int param_5,uint param_6); /* 0x08052410 font-lib.c */
undefined4 V_FontDrawAlignBank(char *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08052440 font-lib.c */
undefined4 FontReadFile(char *param_1); /* 0x08052470 font-lib.c */
void * FontReadFilePtr(FILE *param_1); /* 0x080524b0 font-lib.c */
void * FontReadFilePtr_0_01(FILE *param_1,int param_2); /* 0x08052530 font-lib.c */
undefined4 FontFree(void *param_1); /* 0x08052970 font-lib.c */
int FontGetWidth(int param_1,char *param_2); /* 0x080529b0 font-lib.c */
int FontGetWidthQuick(int param_1,char *param_2); /* 0x08052a10 font-lib.c */
bool G_Init(void); /* 0x08052a50 g-lib.c */
undefined4 G_DeInit(void); /* 0x08052aa0 g-lib.c */
undefined4 G_SetRenderMode(int param_1); /* 0x08052b00 g-lib.c */
undefined4 G_SetMode(uint param_1,int param_2,int param_3,int param_4); /* 0x08052b20 g-lib.c */
undefined4 G_MakeColor(undefined4 param_1,int param_2,int param_3); /* 0x08052cc0 g-lib.c */
void G_SetRGBtoBGR(int param_1); /* 0x08052cd0 g-lib.c */
undefined4 G_SetBlitMode(int param_1,uint param_2); /* 0x08052d10 g-lib.c */
void G_PageFlip(void); /* 0x08052e50 g-lib.c */
void VGA_Cls(void); /* 0x08052ea0 g-lib.c */
undefined4 VRetrace(void); /* 0x08052ec0 g-lib.c */
int sgn(uint param_1); /* 0x08052ed0 g-lib.c */
undefined4 GetDrawType(char *param_1,undefined4 *param_2,undefined4 *param_3); /* 0x08052ef0 g-lib.c */
undefined4 Trig_Init(void); /* 0x08052fc0 g-lib.c */
undefined4 Trig_DeInit(void); /* 0x08053080 g-lib.c */
void V_DoubleRes(uint *param_1,int param_2); /* 0x080530b0 g-lib.c */
void V_DoubleResDiag(int *param_1,int param_2); /* 0x08053150 g-lib.c */
void V_DoubleResBlur(int *param_1,int param_2); /* 0x08053410 g-lib.c */
void V_DoubleResLines(uint *param_1,int param_2); /* 0x08053880 g-lib.c */
bool ElecInit(void); /* 0x08053910 init-lib.c */
undefined4 ElecDeInit(void); /* 0x08053960 init-lib.c */
void KBIClearKeyflags(int param_1); /* 0x08053970 inp-kbi.c */
void KBIRefreshKeyflags(int param_1,int param_2); /* 0x08053990 inp-kbi.c */
void KBISetFlip(int param_1,int param_2); /* 0x08053a10 inp-kbi.c */
undefined4 KBIUpdate(int param_1,int param_2,uint param_3); /* 0x08053ab0 inp-kbi.c */
undefined4 KBIStuffBuf(int param_1,uint param_2); /* 0x08053af0 inp-kbi.c */
uint KBIStuffBufNoFlip(int param_1,uint param_2); /* 0x08053b20 inp-kbi.c */
undefined4 KBIGetch(int param_1); /* 0x08053b90 inp-kbi.c */
undefined4 KBIClearAll(int param_1); /* 0x08053bc0 inp-kbi.c */
undefined4 KBIIs6Button(uint param_1,int param_2); /* 0x08053c00 inp-kbi.c */
bool KBIIs6ButtonOrStart(uint param_1,int param_2); /* 0x08053c40 inp-kbi.c */
uint KBIKeyMap(int param_1,uint param_2); /* 0x08053c80 inp-kbi.c */
uint KBIFlippedKey(int param_1,uint param_2); /* 0x08053cf0 inp-kbi.c */
uint * KBIMenuGetKey(uint *param_1,int param_2,int param_3,int param_4); /* 0x08053d30 inp-menu.c */
undefined4 UInpKBHook(uint param_1,int param_2); /* 0x08053ee0 input-lb.c */
void UInpPadHook(int param_1,int param_2); /* 0x08053f60 input-lb.c */
undefined4 UInpInit(void); /* 0x08053fe0 input-lb.c */
undefined4 UInpReInit(void); /* 0x08054070 input-lb.c */
void UInpDeInit(void); /* 0x08054090 input-lb.c */
void UInpRefreshFlags(void); /* 0x080540c0 input-lb.c */
undefined4 UInpSetKeyMap(undefined4 *param_1); /* 0x080541a0 input-lb.c */
undefined4 UInpGetKeyMap(undefined4 *param_1); /* 0x080541f0 input-lb.c */
void UInpResetKeyMap(void); /* 0x08054230 input-lb.c */
undefined4 UInpStuff(undefined4 param_1); /* 0x08054260 input-lb.c */
undefined4 UInpGet(void); /* 0x080542a0 input-lb.c */
bool UInpHit(void); /* 0x08054300 input-lb.c */
void UInpBufClear(void); /* 0x08054340 input-lb.c */
uint KBToUInp(uint param_1); /* 0x08054360 input-lb.c */
uint PadToUInp(uint param_1); /* 0x080543c0 input-lb.c */
bool IntCircBufInit(undefined4 *param_1,int param_2); /* 0x08054420 input-lb.c */
undefined4 IntCircBufDeInit(undefined4 *param_1); /* 0x08054470 input-lb.c */
bool IntCircBufIsValid(int *param_1); /* 0x080544b0 input-lb.c */
void IntCircBufStuff(int *param_1,undefined4 param_2); /* 0x080544c0 input-lb.c */
undefined4 IntCircBufGet(int *param_1); /* 0x08054500 input-lb.c */
bool IntCircBufIsEmpty(int param_1); /* 0x08054540 input-lb.c */
void IntCircBufClear(int param_1); /* 0x08054550 input-lb.c */
undefined4 KBBufferRawHook(uint param_1); /* 0x08054570 kbll-lib.c */
undefined4 KBInit(void); /* 0x08054630 kbll-lib.c */
void KBPoll(void); /* 0x080546b0 kbll-lib.c */
void KBDeInit(void); /* 0x080546c0 kbll-lib.c */
void KBSuspend(void); /* 0x08054700 kbll-lib.c */
void KBResume(void); /* 0x08054710 kbll-lib.c */
void KBRefreshflags(void); /* 0x08054720 kbll-lib.c */
undefined4 KBReset(void); /* 0x08054790 kbll-lib.c */
void KBRepeatSet(int param_1,int param_2); /* 0x080547c0 kbll-lib.c */
undefined4 KBInstallHitHook(int *param_1); /* 0x08054810 kbll-lib.c */
void KBRemoveHitHook(void); /* 0x08054830 kbll-lib.c */
void KBLEDLockSet(int param_1); /* 0x08054840 kbll-lib.c */
void KBLEDSet(uint param_1); /* 0x08054860 kbll-lib.c */
void KBBufferChange(int param_1); /* 0x08054890 kbll-lib.c */
void KBBufferClear(void); /* 0x080548a0 kbll-lib.c */
void KBungetchraw(undefined4 param_1); /* 0x080548d0 kbll-lib.c */
undefined4 KBgetchraw(void); /* 0x08054940 kbll-lib.c */
bool KBkbhit(void); /* 0x080549b0 kbll-lib.c */
int KBRawToChar(int param_1); /* 0x080549d0 kbll-lib.c */
byte KBGetNumLock(void); /* 0x08054a20 kbll-lib.c */
byte KBGetCapsLock(void); /* 0x08054a30 kbll-lib.c */
byte KBGetScrollLock(void); /* 0x08054a40 kbll-lib.c */
undefined4 * KBRawToName(byte param_1); /* 0x08054a50 kbll-lib.c */
void KBInitAllegRemap(void); /* 0x08054a70 kbll-lib.c */
void KBLockVarFunc(void); /* 0x08054e60 kbll-lib.c */
undefined4 KBAllegRemap(int param_1); /* 0x08054e70 kbll-lib.c */
int PadInit(int param_1,int param_2); /* 0x08054e80 pad-lib.c */
undefined4 DeviceInit(void); /* 0x08054f20 pad-lib.c */
undefined4 PadReset(void); /* 0x08054f30 pad-lib.c */
void PadDeInit(void); /* 0x08054f80 pad-lib.c */
int PadPoll(void); /* 0x08054fe0 pad-lib.c */
void PadStuff(undefined4 param_1); /* 0x08055280 pad-lib.c */
undefined4 PadGet(void); /* 0x080552e0 pad-lib.c */
bool PadHit(void); /* 0x08055340 pad-lib.c */
void PadBufClear(void); /* 0x08055370 pad-lib.c */
undefined4 PadInstallHitHook(int *param_1); /* 0x08055390 pad-lib.c */
void PadRemoveHitHook(void); /* 0x080553b0 pad-lib.c */
undefined4 EBPalInit(int *param_1,int param_2,void *param_3,int param_4); /* 0x080553c0 pal-lib.c */
void EBPalDeInit(int param_1); /* 0x08055460 pal-lib.c */
uint EBPalReset(int param_1); /* 0x080554a0 pal-lib.c */
undefined4 EBPalCopy(int *param_1,int *param_2,int param_3); /* 0x080554d0 pal-lib.c */
void EBPalGenerateFPal(int *param_1); /* 0x08055540 pal-lib.c */
void EBPalUpdate(int *param_1); /* 0x08055570 pal-lib.c */
undefined4 EBPalSetDataptr(int *param_1,int param_2,int param_3); /* 0x08055660 pal-lib.c */
undefined4 EBPalGetDataptr(int param_1); /* 0x080556b0 pal-lib.c */
undefined4 EBPalGetNumcols(undefined4 *param_1); /* 0x080556c0 pal-lib.c */
void EBPalMarkDataChanged(int param_1); /* 0x080556d0 pal-lib.c */
void EBPalSettingsReset(undefined4 *param_1); /* 0x080556e0 pal-lib.c */
void EBPalSettingsCopy(undefined4 *param_1,undefined4 *param_2); /* 0x08055710 pal-lib.c */
void EBPalSettingsMix(int *param_1,int *param_2,int *param_3); /* 0x08055730 pal-lib.c */
bool EBPalSettingsAreSame(byte *param_1,byte *param_2); /* 0x080557b0 pal-lib.c */
uint EBPalAdd(int param_1,int param_2,int param_3,int param_4); /* 0x080557e0 pal-lib.c */
void EBPalMul(int param_1,int param_2,int param_3,int param_4); /* 0x08055830 pal-lib.c */
void EBPalInvertAll(int param_1,int param_2); /* 0x08055890 pal-lib.c */
int EBPalColorBal(int param_1,int param_2); /* 0x080558c0 pal-lib.c */
bool MasterPalInit(void); /* 0x080558f0 pal-lib.c */
void MasterPalDeInit(void); /* 0x08055950 pal-lib.c */
void MasterPalProcessChanges(void); /* 0x08055980 pal-lib.c */
void MasterPalFinishedDraw(void); /* 0x080559d0 pal-lib.c */
void MasterPalReset(void); /* 0x08055a00 pal-lib.c */
int * MasterPalAdd(int param_1,int param_2,int param_3); /* 0x08055a30 pal-lib.c */
int * MasterPalMul(int param_1,int param_2,int param_3); /* 0x08055a70 pal-lib.c */
void MasterPalInvertAll(int param_1); /* 0x08055ab0 pal-lib.c */
void MasterPalColorBal(int param_1); /* 0x08055ad0 pal-lib.c */
uint MasterPalConvertCol16(uint param_1); /* 0x08055af0 pal-lib.c */
void Pal3toPal4(undefined1 *param_1,undefined1 *param_2,int param_3,int param_4); /* 0x08055b80 pal-lib.c */
void Pal4Copy(int param_1,int param_2,int param_3,int param_4); /* 0x08055be0 pal-lib.c */
void Pal4SetSingle(int param_1,int param_2,undefined1 param_3,undefined1 param_4,undefined1 param_5); /* 0x08055c30 pal-lib.c */
void Pal4Contrast(int param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08055c60 pal-lib.c */
void Pal4ContrastRGB(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7); /* 0x08055d00 pal-lib.c */
void Pal4Brightness(int param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08055dd0 pal-lib.c */
void Pal4BrightnessRGB(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7); /* 0x08055ea0 pal-lib.c */
void Pal4ColorBal(int param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08055f90 pal-lib.c */
void Pal4InvertAll(int param_1,int param_2,int param_3,int param_4); /* 0x080560d0 pal-lib.c */
undefined4 Pal4Read3File(int param_1,char *param_2); /* 0x08056120 pal-lib.c */
undefined4 Pal4Read3FilePtr(int param_1,int *param_2); /* 0x080561c0 pal-lib.c */
void Pal4ToFpal(int param_1,int param_2,int param_3,int param_4); /* 0x08056260 pal-lib.c */
void Pal4SettingsToFpal(int param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x080562c0 pal-lib.c */
void SndSetMode(int param_1); /* 0x08056760 snd-lib.c */
int GetSndMode(void); /* 0x08056770 snd-lib.c */
void SndSetBufReadMode(undefined4 param_1); /* 0x08056780 snd-lib.c */
int GetNumVoices(void); /* 0x08056790 snd-lib.c */
undefined4 SndInit(uint param_1,uint param_2,int param_3); /* 0x080567a0 snd-lib.c */
void SndDeInit(void); /* 0x08056a30 snd-lib.c */
undefined4 SndDetectWavDevice(int param_1); /* 0x08056ab0 snd-lib.c */
undefined4 SndDetectMidiDevice(int param_1); /* 0x08056af0 snd-lib.c */
void SndSetReverseStereo(int param_1); /* 0x08056b30 snd-lib.c */
void SndFree(void *param_1); /* 0x08056b50 snd-lib.c */
undefined4 SndMidiFree(void *param_1); /* 0x08056b70 snd-lib.c */
undefined4 * SndArrayNew(size_t param_1); /* 0x08056b80 snd-lib.c */
bool SndArrayAdd(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x08056bd0 snd-lib.c */
undefined4 SndArrayFree(undefined4 *param_1); /* 0x08056c00 snd-lib.c */
void SndPlay(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x08056c60 snd-lib.c */
void SndPlayLoop(int *param_1,int param_2,int param_3,undefined4 param_4); /* 0x08056cb0 snd-lib.c */
void SndPlayPanFreq(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6); /* 0x08056d00 snd-lib.c */
void SndMidiPlay(int *param_1); /* 0x08056d70 snd-lib.c */
void SndMidiPlayLoop(int *param_1,undefined4 param_2,undefined4 param_3); /* 0x08056da0 snd-lib.c */
void SndMidiStop(void); /* 0x08056dc0 snd-lib.c */
void SndMidiPause(void); /* 0x08056de0 snd-lib.c */
void SndMidiResume(void); /* 0x08056e00 snd-lib.c */
void SndMidiSeek(int param_1); /* 0x08056e20 snd-lib.c */
undefined4 SndVoiceReserve(int param_1); /* 0x08056e40 snd-lib.c */
undefined4 SndVoiceReserveAuto(void); /* 0x08056ec0 snd-lib.c */
void SndVoiceUnreserve(int param_1); /* 0x08056f20 snd-lib.c */
undefined4 SndVoiceUnreserveAll(void); /* 0x08056f80 snd-lib.c */
undefined4 SndVoiceIsReserved(int param_1); /* 0x08056fb0 snd-lib.c */
undefined4 SndVoiceGetVoiceno(int param_1); /* 0x08056fd0 snd-lib.c */
uint SndVoiceIsPlaying(int param_1); /* 0x08056ff0 snd-lib.c */
undefined4 SndVoiceIsFree(int param_1); /* 0x08057040 snd-lib.c */
int SndVoiceGetFree(void); /* 0x08057090 snd-lib.c */
undefined4 SndVoicePlay(int param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x080570d0 snd-lib.c */
int SndVoicePrepare(int param_1,int *param_2,int param_3,int param_4); /* 0x08057130 snd-lib.c */
undefined4 SndVoiceStart(int param_1); /* 0x080571f0 snd-lib.c */
void SndVoiceStop(int param_1); /* 0x08057230 snd-lib.c */
undefined4 SndVoiceStopAll(void); /* 0x08057290 snd-lib.c */
void SndVoiceSetVol(int param_1,int param_2); /* 0x080572c0 snd-lib.c */
int SndVoiceGetVol(int param_1); /* 0x08057300 snd-lib.c */
void SndVoiceSetFreq(int param_1,int param_2); /* 0x08057340 snd-lib.c */
undefined4 SndVoiceGetFreq(int param_1); /* 0x08057380 snd-lib.c */
void SndVoiceSetPan(int param_1,int param_2); /* 0x080573c0 snd-lib.c */
int SndVoiceGetPan(int param_1); /* 0x08057410 snd-lib.c */
void SndVoiceSetLoop(int param_1,int param_2); /* 0x08057460 snd-lib.c */
int * SndVoiceCleanup(void); /* 0x080574b0 snd-lib.c */
int SndIDPlay(int param_1,int *param_2,int param_3,int param_4,undefined4 param_5); /* 0x08057540 snd-lib.c */
int SndIDPrepare(int param_1,int *param_2,int param_3,int param_4); /* 0x080575a0 snd-lib.c */
void SndIDStart(int param_1); /* 0x08057600 snd-lib.c */
void SndIDStop(int param_1); /* 0x08057640 snd-lib.c */
uint SndIDIsPlaying(int param_1); /* 0x08057690 snd-lib.c */
int SndIDGetChannel(int param_1); /* 0x080576d0 snd-lib.c */
int SndIDGetChannelOrFree(int param_1); /* 0x08057720 snd-lib.c */
int * SndReadFile(char *param_1); /* 0x08057750 snd-lib.c */
uint * SndMidiReadFile(byte *param_1); /* 0x080578f0 snd-lib.c */
int * SndReadFileWAVPtr(int *param_1); /* 0x08057900 snd-lib.c */
int * SndReadFileSNDPtr(int *param_1); /* 0x08057be0 snd-lib.c */
undefined4 SndSetVol(uint param_1,uint param_2); /* 0x08057d00 snd-lib.c */
int SndGetVoiceVol(void); /* 0x08057d60 snd-lib.c */
int SndGetMidiVol(void); /* 0x08057d70 snd-lib.c */
int SndCorrectVolOff(int param_1); /* 0x08057d80 snd-lib.c */
int SndParseWavDevice(char *param_1); /* 0x08057db0 snd-lib.c */
undefined4 * SndWavDeviceString(int param_1); /* 0x08057e40 snd-lib.c */
int SndParseMidiDevice(char *param_1); /* 0x08057e90 snd-lib.c */
undefined4 * SndMidiDeviceString(int param_1); /* 0x08057f20 snd-lib.c */
bool MP3Init(void); /* 0x08057f80 snd-lib.c */
void MP3DeInit(void); /* 0x08057fb0 snd-lib.c */
undefined4 MP3LoadAndPlay(char *param_1,undefined4 param_2); /* 0x08057fd0 snd-lib.c */
void MP3Unload(void); /* 0x08057ff0 snd-lib.c */
void MP3Poll(void); /* 0x08058010 snd-lib.c */
void MP3SetVol(int param_1); /* 0x08058040 snd-lib.c */
undefined4 MP3GetVol(void); /* 0x08058060 snd-lib.c */
void MP3Pause(void); /* 0x08058080 snd-lib.c */
void MP3Resume(void); /* 0x08058090 snd-lib.c */
bool MODInit(int param_1); /* 0x080580a0 snd-lib.c */
void MODDeInit(void); /* 0x080580d0 snd-lib.c */
undefined4 MODLoad(byte *param_1); /* 0x080580f0 snd-lib.c */
undefined4 MODUnload(undefined4 *param_1); /* 0x08058150 snd-lib.c */
void MODPlay(int *param_1,int param_2); /* 0x08058190 snd-lib.c */
void MODStop(void); /* 0x080581c0 snd-lib.c */
void MODPause(void); /* 0x080581e0 snd-lib.c */
void MODResume(void); /* 0x08058200 snd-lib.c */
void MODSetVol(int param_1); /* 0x08058220 snd-lib.c */
undefined4 MODGetVol(void); /* 0x08058240 snd-lib.c */
uint CDAInit(char *param_1); /* 0x08058260 snd-lib.c */
void CDADeInit(void); /* 0x08058290 snd-lib.c */
undefined4 CDAPlay(uint param_1,int param_2); /* 0x080582c0 snd-lib.c */
void CDAStop(void); /* 0x08058340 snd-lib.c */
void CDAPause(void); /* 0x08058380 snd-lib.c */
void CDAResume(void); /* 0x080583c0 snd-lib.c */
void CDAPoll(void); /* 0x08058400 snd-lib.c */
bool CDAIsPlaying(void); /* 0x08058460 snd-lib.c */
bool CDAIsPaused(void); /* 0x08058490 snd-lib.c */
uint CDATrackIsAudio(undefined1 param_1); /* 0x080584c0 snd-lib.c */
undefined1 CDACurrentTrack(void); /* 0x080584e0 snd-lib.c */
bool CDAGetTrackRange(uint *param_1,uint *param_2); /* 0x08058510 snd-lib.c */
void CDASetVol(uint param_1); /* 0x08058550 snd-lib.c */
int CDAGetVol(void); /* 0x08058590 snd-lib.c */
void CDAEject(void); /* 0x080585d0 snd-lib.c */
void CDAClose(void); /* 0x080585f0 snd-lib.c */
bool SpriteInit(int *param_1,int param_2,void *param_3,size_t param_4,int param_5,int param_6, int param_7,int param_8,int param_9,int param_10); /* 0x08058610 spr-lib.c */
void SpriteDeInit(int param_1); /* 0x080586e0 spr-lib.c */
undefined4 SpriteCopy(undefined4 *param_1,undefined4 *param_2,int param_3); /* 0x08058740 spr-lib.c */
int SpriteInitLine(int *param_1,void *param_2); /* 0x08058810 spr-lib.c */
undefined4 SpriteUsePal(int param_1,int param_2,int param_3,int param_4); /* 0x08058880 spr-lib.c */
void SpriteSetAxis(int param_1,undefined4 param_2,undefined4 param_3); /* 0x080588d0 spr-lib.c */
void SpriteArrayNew(void); /* 0x080588f0 spr-lib.c */
undefined4 * SpriteArrayNewSize(size_t param_1,size_t param_2); /* 0x08058900 spr-lib.c */
int * SpriteArrayNewInstance(int *param_1); /* 0x08058960 spr-lib.c */
int * SpriteArrayNewInstanceOnto(int *param_1,int *param_2); /* 0x08058a20 spr-lib.c */
uint SpriteArrayAddSprite(int *param_1,void *param_2,undefined4 param_3,undefined4 param_4); /* 0x08058af0 spr-lib.c */
uint SpriteArrayAddPal(int param_1,void *param_2,undefined4 param_3,undefined4 param_4); /* 0x08058b40 spr-lib.c */
undefined4 SpriteArrayNumImages(int *param_1); /* 0x08058ba0 spr-lib.c */
undefined4 SpriteArrayNumPals(int param_1); /* 0x08058bb0 spr-lib.c */
undefined4 SpriteArrayFree(int *param_1); /* 0x08058bc0 spr-lib.c */
undefined4 SpriteArrayClear(int *param_1); /* 0x08058c90 spr-lib.c */
uint SpriteArrayGetNum(int *param_1,int param_2,int param_3); /* 0x08058d70 spr-lib.c */
uint SpriteArrayPalGetNum(int param_1,int param_2,int param_3); /* 0x08058d80 spr-lib.c */
int SpriteArrayAccess(int *param_1,int param_2); /* 0x08058d90 spr-lib.c */
undefined4 SpriteArrayAccessGrpItem(int *param_1,int param_2,int param_3); /* 0x08058db0 spr-lib.c */
int SpriteArrayPalAccess(int param_1,int param_2); /* 0x08058dc0 spr-lib.c */
void SpriteArrayPalAccessGrpItem(int param_1,int param_2,int param_3); /* 0x08058de0 spr-lib.c */
int * SpriteArrayPalUpdateAndAccess(int param_1,int param_2); /* 0x08058df0 spr-lib.c */
bool SpriteArrayPalRemapFromRoot(int param_1,int param_2,int param_3); /* 0x08058e20 spr-lib.c */
bool SpriteArrayPalRemapFromRootGrpItem (int *param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08058e70 spr-lib.c */
int ColDepthToBytesPerPixel(int param_1); /* 0x08058ee0 spr-lib.c */
undefined4 SpriteDecompGetData(int *param_1,int param_2); /* 0x08058ef0 spr-lib.c */
undefined4 SpriteDecompGetAndLockData(int *param_1,int param_2); /* 0x08058f30 spr-lib.c */
undefined4 SpriteDecompUnlockData(void); /* 0x08058f40 spr-lib.c */
void W_PutSurface(void); /* 0x08058f50 spr-lib.c */
undefined4 W_PutSprite(int *param_1,int param_2,int param_3,int param_4); /* 0x08058f60 spr-lib.c */
void W_PutSpriteA(int *param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08058ff0 spr-lib.c */
void W_PutSpriteAMirH(int *param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08059040 spr-lib.c */
void W_PutSpriteAPal(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6 ); /* 0x08059090 spr-lib.c */
void W_PutSpriteAMirHPal(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5, int param_6); /* 0x08059100 spr-lib.c */
void W_PutSpriteFlat(int *param_1,int param_2,int param_3,int param_4); /* 0x08059170 spr-lib.c */
undefined4 W_PutSpriteMirH(int *param_1,int param_2,int param_3,int param_4); /* 0x080591d0 spr-lib.c */
undefined4 W_PutSpriteMirV(int *param_1,int param_2,int param_3,int param_4); /* 0x08059230 spr-lib.c */
undefined4 W_PutSpriteMirHV(int *param_1,int param_2,int param_3,int param_4); /* 0x08059290 spr-lib.c */
void W_PutSpriteShadow(int *param_1,int param_2,int param_3,int param_4,undefined2 param_5); /* 0x080592f0 spr-lib.c */
void W_ScaleSprite(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08059390 spr-lib.c */
void W_ScaleSpriteFlat(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6); /* 0x08059480 spr-lib.c */
void W_ScaleSpriteMirH(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6); /* 0x08059500 spr-lib.c */
void W_ScaleSpriteMirV(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6); /* 0x08059590 spr-lib.c */
void W_ScaleSpriteMirHV(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6); /* 0x08059620 spr-lib.c */
undefined4 W_ScaleSprite_S(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080596b0 spr-lib.c */
void W_ScaleSpriteFlat_S(int *param_1,int param_2,int param_3,int param_4,float param_5, float param_6); /* 0x08059800 spr-lib.c */
void W_ScaleSpriteMirH_S(int *param_1,int param_2,int param_3,int param_4,float param_5, float param_6); /* 0x080598b0 spr-lib.c */
void W_ScaleSpriteMirV_S(int *param_1,int param_2,int param_3,int param_4,float param_5, float param_6); /* 0x080598f0 spr-lib.c */
void W_ScaleSpriteMirHV_S (int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6); /* 0x08059920 spr-lib.c */
void W_RotateSprite(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6 ,float param_7); /* 0x08059960 spr-lib.c */
void W_RotateSpriteMirH(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6,float param_7); /* 0x080599a0 spr-lib.c */
undefined4 W_RotateSprite_P(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x080599e0 spr-lib.c */
void W_RotateSpriteMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08059c00 spr-lib.c */
undefined4 W_PutSpriteTransAdd(int *param_1,int param_2,int param_3,int param_4); /* 0x08059c30 spr-lib.c */
undefined4 W_PutSpriteTransAddMirH(int *param_1,int param_2,int param_3,int param_4); /* 0x08059ca0 spr-lib.c */
undefined4 W_PutSpriteTransAddMirV(int *param_1,int param_2,int param_3,int param_4); /* 0x08059d10 spr-lib.c */
undefined4 W_PutSpriteTransAddMirHV(int *param_1,int param_2,int param_3,int param_4); /* 0x08059d80 spr-lib.c */
void W_PutSpriteTransAddFlip(int *param_1,int param_2,int param_3,int param_4,int param_5); /* 0x08059df0 spr-lib.c */
undefined4 W_PutSpriteTransAdd_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08059e90 spr-lib.c */
undefined4 W_PutSpriteTransAddMirH_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08059f20 spr-lib.c */
undefined4 W_PutSpriteTransAddMirV_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x08059fb0 spr-lib.c */
undefined4 W_PutSpriteTransAddMirHV_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x0805a040 spr-lib.c */
void W_PutSpriteTransAddFlip_B (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7 ); /* 0x0805a0d0 spr-lib.c */
undefined4 W_ScaleSpriteTransAdd (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a1c0 spr-lib.c */
undefined4 W_ScaleSpriteTransAdd_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a250 spr-lib.c */
void W_ScaleSpriteTransAddMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a3a0 spr-lib.c */
void W_ScaleSpriteTransAddMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a430 spr-lib.c */
void W_ScaleSpriteTransAddMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805a4c0 spr-lib.c */
void W_ScaleSpriteTransAdd_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a550 spr-lib.c */
undefined4 W_ScaleSpriteTransAdd_B_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a600 spr-lib.c */
void W_ScaleSpriteTransAddMirH_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a790 spr-lib.c */
void W_ScaleSpriteTransAddMirV_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a840 spr-lib.c */
void W_ScaleSpriteTransAddMirHV_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, int param_7,int param_8); /* 0x0805a8f0 spr-lib.c */
void W_RotateSpriteTransAdd (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805a9a0 spr-lib.c */
void W_RotateSpriteTransAddMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805a9e0 spr-lib.c */
uint W_RotateSpriteTransAdd_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805aa20 spr-lib.c */
void W_RotateSpriteTransAddMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805ac40 spr-lib.c */
void W_RotateSpriteTransAdd_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,int param_8,int param_9); /* 0x0805ac70 spr-lib.c */
void W_RotateSpriteTransAddMirH_B (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,int param_8,int param_9); /* 0x0805acc0 spr-lib.c */
uint W_RotateSpriteTransAdd_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0805ad10 spr-lib.c */
void W_RotateSpriteTransAddMirH_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0805af90 spr-lib.c */
undefined4 W_PutSpriteTransSub(int *param_1,int param_2,int param_3,int param_4); /* 0x0805afc0 spr-lib.c */
undefined4 W_PutSpriteTransSubMirH(int *param_1,int param_2,int param_3,int param_4); /* 0x0805b030 spr-lib.c */
void W_PutSpriteTransSubMirV(int *param_1,int param_2,int param_3,int param_4); /* 0x0805b0a0 spr-lib.c */
undefined4 W_PutSpriteTransSubMirHV(int *param_1,int param_2,int param_3,int param_4); /* 0x0805b110 spr-lib.c */
undefined4 W_ScaleSpriteTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b180 spr-lib.c */
undefined4 W_ScaleSpriteTransSub_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b210 spr-lib.c */
void W_ScaleSpriteTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b360 spr-lib.c */
void W_ScaleSpriteTransSubMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b3f0 spr-lib.c */
void W_ScaleSpriteTransSubMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805b480 spr-lib.c */
void W_RotateSpriteTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805b510 spr-lib.c */
void W_RotateSpriteTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7); /* 0x0805b550 spr-lib.c */
uint W_RotateSpriteTransSub_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805b590 spr-lib.c */
void W_RotateSpriteTransSubMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0805b7b0 spr-lib.c */
void W_ScaleShadowTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x0805b7e0 spr-lib.c */
undefined4 W_ScaleShadowTransSub_S (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x0805b880 spr-lib.c */
void W_ScaleShadowTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x0805b9f0 spr-lib.c */
void W_ScaleShadowTransSubMirV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x0805ba90 spr-lib.c */
void W_ScaleShadowTransSubMirHV (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x0805bb30 spr-lib.c */
void W_RotateShadowTransSub (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,uint param_8); /* 0x0805bbd0 spr-lib.c */
void W_RotateShadowTransSubMirH (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,uint param_8); /* 0x0805bc10 spr-lib.c */
int W_RotateShadowTransSub_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint param_10); /* 0x0805bc50 spr-lib.c */
void W_RotateShadowTransSubMirH_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint param_10); /* 0x0805beb0 spr-lib.c */
int HFlipToSgn(uint param_1); /* 0x0805bee0 spr-lib.c */
int VFlipToSgn(uint param_1); /* 0x0805bf00 spr-lib.c */
void SpriteSetReadMode(int param_1); /* 0x0805bf20 spr-read.c */
void SpriteSetBufReadMode(int param_1); /* 0x0805bf30 spr-read.c */
int * SpriteReadFile(char *param_1); /* 0x0805bf40 spr-read.c */
int * SpriteReadSFFPtr(int *param_1); /* 0x0805c080 spr-read.c */
int * SpriteReadSFFPtr_1_01(int *param_1,int param_2); /* 0x0805c140 spr-read.c */
undefined4 SpriteReadSFFPtr_2_00(void); /* 0x0805c3a0 spr-read.c */
int * SpriteReadSFFList(char *param_1,int *param_2); /* 0x0805c3b0 spr-read.c */
int * SpriteReadSFFListPtr(int *param_1,int *param_2); /* 0x0805c410 spr-read.c */
int * SpriteReadSFFListPtr_1_01(int *param_1,int param_2,int *param_3); /* 0x0805c4c0 spr-read.c */
undefined4 SpriteReadSFFListPtr_2_00(void); /* 0x0805c7b0 spr-read.c */
void * SpriteReadPCXRawPtr(int *param_1,int *param_2,int *param_3,int *param_4,size_t *param_5, int *param_6); /* 0x0805c7c0 spr-read.c */
int * SpriteReadPCXPtr(int *param_1,int param_2,int param_3); /* 0x0805cc80 spr-read.c */
void W_PutSprite8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x0805cd70 spr16-lb.c */
void W_PutSpriteFlat8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x0805cfa0 spr16-lb.c */
void W_PutSpriteMirH8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x0805d1c0 spr16-lb.c */
void W_PutSpriteMirV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x0805d420 spr16-lb.c */
void W_PutSpriteMirHV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x0805d660 spr16-lb.c */
void W_ScaleSprite8to16(int *param_1,int param_2,float param_3,float param_4,float param_5, float param_6); /* 0x0805d8b0 spr16-lb.c */
void W_ScaleSpriteFlat8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805e190 spr16-lb.c */
void W_ScaleSpriteMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805ea80 spr16-lb.c */
void W_ScaleSpriteMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805f370 spr16-lb.c */
void W_ScaleSpriteMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x0805fc70 spr16-lb.c */
undefined4 W_RotateSprite8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08060570 spr16-lb.c */
undefined4 W_RotateSpriteMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08061400 spr16-lb.c */
void W_PutSpriteShadow8to16(int *param_1,int param_2,int param_3,int param_4,undefined2 param_5); /* 0x08062250 spr16-lb.c */
void W_PutSpriteShadow16(void); /* 0x08062430 spr16-lb.c */
void W_PutSpriteTransAdd8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08062440 spr16add.c */
void W_PutSpriteTransAddMirH8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08062710 spr16add.c */
void W_PutSpriteTransAddMirV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x080629f0 spr16add.c */
void W_PutSpriteTransAddMirHV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08062ce0 spr16add.c */
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
uint W_RotateSpriteTransAdd8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0806c100 spr16add.c */
uint W_RotateSpriteTransAddMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x0806d020 spr16add.c */
uint W_RotateSpriteTransAdd8to16_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0806df40 spr16add.c */
uint W_RotateSpriteTransAddMirH8to16_B_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,int param_10,int param_11); /* 0x0806fff0 spr16add.c */
void W_PutSpriteTransSub8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08072060 spr16sub.c */
void W_PutSpriteTransSubMirH8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08072300 spr16sub.c */
void W_PutSpriteTransSubMirV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x080725b0 spr16sub.c */
void W_PutSpriteTransSubMirHV8to16(int *param_1,int param_2,int param_3,int param_4); /* 0x08072860 spr16sub.c */
void W_ScaleSpriteTransSub8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08072b30 spr16sub.c */
void W_ScaleSpriteTransSubMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080734b0 spr16sub.c */
void W_ScaleSpriteTransSubMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x08073e30 spr16sub.c */
void W_ScaleSpriteTransSubMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6); /* 0x080747c0 spr16sub.c */
uint W_RotateSpriteTransSub8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08075150 spr16sub.c */
uint W_RotateSpriteTransSubMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9); /* 0x08076040 spr16sub.c */
void W_ScaleShadowTransSub8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x08076ef0 spr16sub.c */
void W_ScaleShadowTransSubMirH8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x08077790 spr16sub.c */
void W_ScaleShadowTransSubMirV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x08078040 spr16sub.c */
void W_ScaleShadowTransSubMirHV8to16 (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, uint param_7); /* 0x08078910 spr16sub.c */
int W_RotateShadowTransSub8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint param_10); /* 0x080791e0 spr16sub.c */
int W_RotateShadowTransSubMirH8to16_P (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8,float param_9,uint param_10); /* 0x0807a090 spr16sub.c */
void TimerHandler(void); /* 0x0807af40 time-lib.c */
bool TimerInit(int param_1); /* 0x0807af90 time-lib.c */
void TimerDeInit(void); /* 0x0807b000 time-lib.c */
void TimerChangeSpeed(int param_1); /* 0x0807b020 time-lib.c */
undefined4 TimerDelay(undefined4 param_1); /* 0x0807b040 time-lib.c */
void TimerSetTicks(int param_1); /* 0x0807b050 time-lib.c */
longdouble TimerGetFPS(void); /* 0x0807b060 time-lib.c */
void TimerSetFPSDelay(int param_1); /* 0x0807b0d0 time-lib.c */
void TimerSyncReset(void); /* 0x0807b0f0 time-lib.c */
void TimerSetSyncFPS(int param_1); /* 0x0807b110 time-lib.c */
bool TimerGetSync(void); /* 0x0807b150 time-lib.c */
void TimerWaitSync(void); /* 0x0807b160 time-lib.c */
undefined4 TimerIsSync(void); /* 0x0807b1a0 time-lib.c */
void TimerSkipSync(void); /* 0x0807b1f0 time-lib.c */
undefined4 TPFree(undefined4 *param_1); /* 0x0807b200 txtparse.c */
undefined4 * TPReadMFPtr(int *param_1,int param_2); /* 0x0807b2f0 txtparse.c */
int * TPReadMF(int *param_1,int param_2); /* 0x0807b780 txtparse.c */
void * TPReadFile(char *param_1); /* 0x0807b7c0 txtparse.c */
undefined4 * TPClone(undefined4 *param_1); /* 0x0807b800 txtparse.c */
void * TPReadFileForWrite(char *param_1); /* 0x0807b840 txtparse.c */
int * TPReadFilePtr(FILE *param_1,int param_2); /* 0x0807b880 txtparse.c */
undefined4 TPWriteFile(int param_1,char *param_2); /* 0x0807bd10 txtparse.c */
undefined4 TPGroupSeek(int param_1,char *param_2); /* 0x0807bd80 txtparse.c */
undefined4 TPGroupSeekIdx(int param_1,int param_2); /* 0x0807be50 txtparse.c */
void TPGroupReset(int param_1); /* 0x0807beb0 txtparse.c */
undefined4 TPGroupScanFirst(int param_1); /* 0x0807bef0 txtparse.c */
undefined4 TPGroupScanNext(int param_1); /* 0x0807bf00 txtparse.c */
int TPGroupMatchCount(int param_1,char *param_2); /* 0x0807bf70 txtparse.c */
int TPGetLineNo(int param_1,char *param_2); /* 0x0807bfc0 txtparse.c */
int TPGetLineNo_Skip(int param_1,char *param_2,int param_3); /* 0x0807bfe0 txtparse.c */
char * TPGetValue(int param_1,char *param_2); /* 0x0807c0a0 txtparse.c */
int TPSeekValue(int param_1,char *param_2); /* 0x0807c1c0 txtparse.c */
int TPSeekEog(int param_1); /* 0x0807c210 txtparse.c */
char * TPGetValueNewStr(int param_1,char *param_2); /* 0x0807c250 txtparse.c */
char * TPGetValueNext(int param_1,char *param_2); /* 0x0807c2b0 txtparse.c */
bool TPGetValueFloat(int param_1,char *param_2,float *param_3); /* 0x0807c3e0 txtparse.c */
bool TPGetValueInt(int param_1,char *param_2,uint *param_3); /* 0x0807c420 txtparse.c */
int TPScanf(int param_1,char *param_2,char *param_3,...); /* 0x0807c460 txtparse.c */
void TPAccessReset(int param_1); /* 0x0807c4a0 txtparse.c */
undefined4 TPAccessFirstLine(int param_1); /* 0x0807c4d0 txtparse.c */
undefined4 TPReaccessCurLine(int param_1); /* 0x0807c4f0 txtparse.c */
undefined4 TPAccessNextLine(int param_1); /* 0x0807c510 txtparse.c */
undefined4 TPAccessPrevLine(int param_1); /* 0x0807c550 txtparse.c */
bool TPGetLine(int param_1,char *param_2); /* 0x0807c580 txtparse.c */
int TPGetGroupText(int param_1,int param_2,int param_3); /* 0x0807c5c0 txtparse.c */
int TPWLineNo(int param_1,int param_2); /* 0x0807c670 txtparse.c */
undefined4 TPGroupRename(int param_1,char *param_2,...); /* 0x0807c6e0 txtparse.c */
undefined4 TPPrintf(int param_1,char *param_2,char *param_3,...); /* 0x0807c850 txtparse.c */
undefined4 TPPrintf_Skip(int param_1,char *param_2,int param_3,char *param_4,...); /* 0x0807ca00 txtparse.c */
undefined4 TPInsertLine(int param_1,char *param_2); /* 0x0807cbc0 txtparse.c */
undefined4 TPDeleteLine(int param_1); /* 0x0807cca0 txtparse.c */
void TPDeleteAllLines(int param_1); /* 0x0807cd50 txtparse.c */
undefined4 TPWExpandLinespace(int param_1); /* 0x0807cd80 txtparse.c */
void strgetto(char *param_1,char *param_2,int param_3,char param_4); /* 0x0807cdd0 txtparse.c */
undefined4 TPisspace(char param_1); /* 0x0807ce20 txtparse.c */
undefined4 V_Alloc(int param_1,int param_2); /* 0x0807ce40 vbuf.c */
int * V_AllocDepth(int param_1,int param_2,int param_3); /* 0x0807ce60 vbuf.c */
int * V_AllocDepthAry(int param_1,int param_2,int param_3,size_t param_4); /* 0x0807ce80 vbuf.c */
undefined4 V_DeAlloc(int param_1); /* 0x0807cf60 vbuf.c */
undefined4 V_SetBuf(int *param_1,int param_2); /* 0x0807cfa0 vbuf.c */
undefined4 V_BufGetSurface(int *param_1,int param_2); /* 0x0807d030 vbuf.c */
undefined4 V_BufLock(int *param_1,int param_2); /* 0x0807d060 vbuf.c */
void V_BufUnlock(int *param_1,int param_2); /* 0x0807d0a0 vbuf.c */
void V_BufLockCurrent(void); /* 0x0807d0e0 vbuf.c */
void V_BufUnlockCurrent(void); /* 0x0807d100 vbuf.c */
void V_BufToScreen(int *param_1,int param_2); /* 0x0807d120 vbuf.c */
void V_BufToScreenXY(int *param_1,int param_2,int param_3,int param_4); /* 0x0807d200 vbuf.c */
void V_BufToScreenStretch(int *param_1,int param_2); /* 0x0807d350 vbuf.c */
void blit_32to16_RGBtoBGR (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7 ,int param_8); /* 0x0807d470 vbuf.c */
void stretch_blit_32to16_RGBtoBGR (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10); /* 0x0807d690 vbuf.c */
int W_Define(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807da70 vbuf.c */
void W_DefineV(uint *param_1); /* 0x0807db40 vbuf.c */
void W_GetV(undefined4 *param_1); /* 0x0807db60 vbuf.c */
void W_Cls(uint param_1); /* 0x0807db90 vbuf.c */
void W_PutPixel(int param_1,int param_2,uint param_3); /* 0x0807dc40 vbuf.c */
void W_PutPixelTransAdd16(int param_1,int param_2,uint param_3); /* 0x0807dd30 vbuf.c */
void W_PutPixelXor16(int param_1,int param_2); /* 0x0807de20 vbuf.c */
void W_Line(float param_1,float param_2,float param_3,float param_4,uint param_5); /* 0x0807de90 vbuf.c */
void DoDrawLine(int param_1,int param_2,float param_3,float param_4,float param_5,float param_6, undefined2 param_7); /* 0x0807e020 vbuf.c */
longdouble CyrusT(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6, float param_7,float param_8); /* 0x0807e660 vbuf.c */
uint TrivialTestPoint(int param_1,int param_2); /* 0x0807e6a0 vbuf.c */
void DoDrawClippedLine(int param_1,int param_2,float param_3,float param_4,float param_5, float param_6,undefined2 param_7); /* 0x0807e6f0 vbuf.c */
void W_HLine(uint param_1,uint param_2,int param_3,uint param_4); /* 0x0807ec50 vbuf.c */
void W_VLine(int param_1,uint param_2,uint param_3,uint param_4); /* 0x0807ed10 vbuf.c */
void W_HLineTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807ede0 vbuf.c */
void W_HLineTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807ef20 vbuf.c */
void W_VLineTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f060 vbuf.c */
void W_VLineTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f1b0 vbuf.c */
void W_HLineTransSub16(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f300 vbuf.c */
void W_HLineTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f430 vbuf.c */
void W_VLineTransSub16(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f560 vbuf.c */
void W_VLineTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x0807f6a0 vbuf.c */
void W_Box(int param_1,int param_2,int param_3,int param_4,uint param_5); /* 0x0807f7e0 vbuf.c */
void W_BoxTransAdd16(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5); /* 0x0807f900 vbuf.c */
void W_BoxTransAdd16_B50(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5); /* 0x0807f970 vbuf.c */
void W_BoxTransSub16(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5); /* 0x0807f9e0 vbuf.c */
void W_BoxTransSub16_B50(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5); /* 0x0807fa50 vbuf.c */
void W_BoxFill(int param_1,int param_2,int param_3,int param_4,uint param_5); /* 0x0807fac0 vbuf.c */
void W_BoxFillTransAdd16(uint param_1,int param_2,uint param_3,int param_4,uint param_5); /* 0x0807fbf0 vbuf.c */
void W_BoxFillTransAdd16_B50(uint param_1,int param_2,uint param_3,int param_4,uint param_5); /* 0x0807fdb0 vbuf.c */
void W_BoxFillTransSub16(uint param_1,int param_2,uint param_3,int param_4,uint param_5); /* 0x0807ff60 vbuf.c */
void W_BoxFillTransSub16_B50(uint param_1,int param_2,uint param_3,int param_4,uint param_5); /* 0x08080120 vbuf.c */
int unzlocal_getByte(_IO_FILE *param_1, uint *param_2); /* 0x080802e0 unzip.c */
int unzlocal_getShort(_IO_FILE *param_1,uint *param_2); /* 0x08080330 unzip.c */
int unzlocal_getLong(_IO_FILE *param_1,uint *param_2); /* 0x08080390 unzip.c */
int strcmpcasenosensitive_internal(char *param_1,char *param_2); /* 0x08080420 unzip.c */
int unzStringFileNameCompare(char *param_1,char *param_2,int param_3); /* 0x08080480 unzip.c */
int unzlocal_SearchCentralDir(FILE *param_1); /* 0x080804c0 unzip.c */
undefined4 * unzOpen(char *param_1); /* 0x080805e0 unzip.c */
undefined4 unzClose(void *param_1); /* 0x080807a0 unzip.c */
undefined4 unzGetGlobalInfo(int param_1,undefined4 *param_2); /* 0x080807e0 unzip.c */
void unzlocal_DosDateToTmuDate(uint param_1,int *param_2); /* 0x08080810 unzip.c */
uint unzlocal_GetCurrentFileInfoInternal (undefined4 *param_1,uint *param_2,uint *param_3,size_t param_4,uint param_5, size_t param_6,void *param_7,size_t param_8,void *param_9); /* 0x08080870 unzip.c */
uint unzGetCurrentFileInfo (undefined4 *param_1,uint *param_2,size_t param_3,uint param_4,size_t param_5, void *param_6,size_t param_7,void *param_8); /* 0x08080c30 unzip.c */
uint unzGoToFirstFile(undefined4 *param_1); /* 0x08080c70 unzip.c */
uint unzGoToNextFile(undefined4 *param_1); /* 0x08080cc0 unzip.c */
uint unzLocateFile(undefined4 *param_1,char *param_2,int param_3); /* 0x08080d40 unzip.c */
uint unzlocal_CheckCurrentFileCoherencyHeader (undefined4 *param_1,int *param_2,int *param_3,uint *param_4); /* 0x08080e10 unzip.c */
undefined4 unzOpenCurrentFile(undefined4 *param_1); /* 0x08081040 unzip.c */
uint unzReadCurrentFile(int param_1,int param_2,uint param_3); /* 0x080811a0 unzip.c */
undefined4 unztell(int param_1); /* 0x080813a0 unzip.c */
uint unzeof(int param_1); /* 0x080813c0 unzip.c */
uint unzGetLocalExtrafield(int param_1,size_t param_2,uint param_3); /* 0x080813e0 unzip.c */
undefined4 unzCloseCurrentFile(int param_1); /* 0x08081480 unzip.c */
uint unzGetGlobalComment(undefined4 *param_1,undefined1 *param_2,uint param_3); /* 0x08081500 unzip.c */
undefined4 NewListNode(void); /* 0x08081580 gui-lib.c */
void AddNodeToEnd(int *param_1); /* 0x08081590 gui-lib.c */
void MoveNodeToEnd(int *param_1); /* 0x080815b0 gui-lib.c */
void MoveNodeToStart(void); /* 0x080815f0 gui-lib.c */
undefined4 EB_GUIInit(int param_1); /* 0x08081600 gui-lib.c */
void EB_GUIDeInit(void); /* 0x08081730 gui-lib.c */
void EB_GUISetWinAttr(int param_1,uint param_2); /* 0x08081740 gui-lib.c */
int * EB_GUINewWindow(char *param_1,int param_2,int param_3,int param_4,int *param_5); /* 0x08081760 gui-lib.c */
void EB_GUICloseWindow(void *param_1); /* 0x08081970 gui-lib.c */
void EB_GUIDrawClipboard(int *param_1,int param_2,int param_3,uint param_4); /* 0x080819b0 gui-lib.c */
void EB_GUIPutSurface(void); /* 0x08081ab0 gui-lib.c */
undefined4 EB_GUIRaiseWindow(int *param_1); /* 0x08081ac0 gui-lib.c */
void EB_GUIPutSprite(int param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x08081ae0 gui-lib.c */
void EB_GUIClearWindow(int param_1); /* 0x08081b50 gui-lib.c */
void EB_GUIDrawWindow(uint *param_1); /* 0x08081b90 gui-lib.c */
void EB_DrawWindows(void); /* 0x08081dd0 gui-lib.c */
void EB_GUIMoveWindow(int *param_1,int param_2,int param_3); /* 0x08081e00 gui-lib.c */
int * DetermineFocus(int param_1,int *param_2); /* 0x08081e60 gui-lib.c */
void EB_GUIUpdate(void); /* 0x08081eb0 gui-lib.c */
int EBT_ThreadCreate(pthread_t *param_1,undefined4 param_2,__start_routine *param_3,void *param_4); /* 0x08081ff0 lthreads.c */
int EBT_MutexInit(void); /* 0x08082020 lthreads.c */
int EBT_MutexDestroy(pthread_mutex_t *__mutex); /* 0x08082040 lthreads.c */
int EBT_MutexLock(pthread_mutex_t *m); /* 0x08082050 lthreads.c */
int EBT_MutexUnlock(pthread_mutex_t *m); /* 0x08082060 lthreads.c */
int * AftImgNew(int param_1); /* 0x08082070 afterimg.c */
undefined4 AftImgInit(int *param_1,int param_2); /* 0x080820c0 afterimg.c */
undefined4 AftImgFree(int *param_1); /* 0x08082150 afterimg.c */
void AftImgDeInit(int *param_1); /* 0x08082180 afterimg.c */
void AftImgSetup(int param_1,undefined4 *param_2,undefined4 param_3); /* 0x080821f0 afterimg.c */
undefined4 AftImgUpdate(int *param_1,float param_2,float param_3,float param_4,undefined4 param_5,float param_6 ,uint param_7,int param_8); /* 0x08082230 afterimg.c */
void AftImgDraw(int *param_1,int param_2,int param_3,int param_4); /* 0x080823f0 afterimg.c */
int ipow(int param_1,int param_2); /* 0x08082880 arith.c */
void StackErrorExit(void); /* 0x080828d0 arith.c */
undefined4 PriorityCheck(undefined4 param_1); /* 0x080828f0 arith.c */
undefined4 OpLength(undefined4 param_1); /* 0x08082980 arith.c */
bool OpTypeCheck(undefined4 param_1,int param_2); /* 0x080829b0 arith.c */
int OperCode(undefined1 *param_1); /* 0x080829e0 arith.c */
char * InfToPostArray(byte *param_1,float *param_2,void *param_3,int param_4,byte *param_5, undefined4 *param_6,int param_7); /* 0x08082ad0 arith.c */
undefined4 InfixToPostfix(byte *param_1,int *param_2,int param_3,undefined4 *param_4,int param_5); /* 0x08083780 arith.c */
undefined4 FreeExpression(int *param_1); /* 0x08083870 arith.c */
void FreeExpNoTrig(undefined4 *param_1); /* 0x080838f0 arith.c */
undefined4 FreeExpArray(void *param_1); /* 0x08083930 arith.c */
void ConstExpI(int *param_1,int param_2); /* 0x08083980 arith.c */
void ConstExpF(int *param_1,int param_2); /* 0x080839c0 arith.c */
undefined4 expcpy(int *param_1,int *param_2); /* 0x08083a00 arith.c */
undefined4 expcpytrig(int *param_1,int *param_2); /* 0x08083aa0 arith.c */
float ExpMulF(int *param_1,float param_2); /* 0x08083b40 arith.c */
float ExpDivI(int *param_1,int param_2); /* 0x08083c00 arith.c */
void ShowExp(char *param_1,int *param_2,int *param_3); /* 0x08083cd0 arith.c */
int EvalExpressionI(int param_1,int *param_2,int param_3); /* 0x08083e40 arith.c */
float EvalExpressionF(int *param_1,int *param_2); /* 0x08083f60 arith.c */
undefined4 EvalExpression(int *param_1,int *param_2,int *param_3,int *param_4); /* 0x08084020 arith.c */
bool BGMParse(int param_1,undefined1 *param_2,char *param_3); /* 0x08085240 bgm.c */
void BGMStart(int *param_1); /* 0x080852b0 bgm.c */
void BGMPause(int *param_1); /* 0x080853c0 bgm.c */
void BGMSysPause(int *param_1); /* 0x08085440 bgm.c */
undefined4 BGMGetPause(int param_1); /* 0x080854c0 bgm.c */
undefined4 BGMResume(int *param_1); /* 0x080854e0 bgm.c */
void BGMSysResume(int *param_1); /* 0x08085570 bgm.c */
int BGMGetVolume(int *param_1); /* 0x08085600 bgm.c */
void BGMSetVolume(int *param_1,uint param_2); /* 0x08085660 bgm.c */
void BGMPoll(int *param_1); /* 0x080856e0 bgm.c */
void BGMPollIgnoreDefocus(int *param_1); /* 0x08085760 bgm.c */
undefined4 BGMCheckExtension(char *param_1); /* 0x08085800 bgm.c */
undefined4 BGMLoad(int *param_1,byte *param_2,int param_3); /* 0x08085810 bgm.c */
undefined4 BGMLoadAndStart(int *param_1,byte *param_2,int param_3,int param_4); /* 0x08085a60 bgm.c */
int * BGMFree(int *param_1); /* 0x08085b40 bgm.c */
void BGMPlayForScene(byte *param_1,int param_2); /* 0x08085be0 bgm.c */
void BGMStopForScene(void); /* 0x08085c10 bgm.c */
bool InitSelectScreenMatrix(char *param_1); /* 0x08085c30 charsel.c */
void FreeSelectScreenMatrix(void); /* 0x08085cd0 charsel.c */
bool CharInfoInit(void); /* 0x08085d00 charsel.c */
void CharInfoFree(void); /* 0x08085db0 charsel.c */
undefined4 FindCharacters(void); /* 0x08085df0 charsel.c */
undefined4 CharacterSelectScreen(undefined4 param_1,int param_2); /* 0x08087150 charsel.c */
undefined4 CharacterSelectScreenDraw(int param_1); /* 0x08088630 charsel.c */
int BuildSelectList(int param_1,undefined4 param_2,int param_3); /* 0x08089810 charsel.c */
void InitSelectDisp(int param_1); /* 0x08089da0 charsel.c */
void UpdateSelectDisp(int *param_1); /* 0x08089e00 charsel.c */
void SelectDispState(undefined4 *param_1,undefined4 param_2); /* 0x08089e50 charsel.c */
void FlashBox(int param_1,undefined4 param_2,undefined4 param_3); /* 0x08089e70 charsel.c */
int CharacterSelectScreenKey(uint param_1,int param_2,int *param_3,int *param_4,int param_5); /* 0x08089ec0 charsel.c */
bool CharacterSelectStageKey(uint param_1,int param_2,uint *param_3,int param_4); /* 0x0808a230 charsel.c */
undefined4 CharacterSelectMenuKey(uint param_1,undefined4 param_2,int param_3,int param_4); /* 0x0808a2a0 charsel.c */
void CharselResetCursor(void); /* 0x0808a3a0 charsel.c */
void CharselSaveCursor(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4, int param_5); /* 0x0808a3e0 charsel.c */
void CharselRestoreCursor(int param_1,int param_2,int param_3); /* 0x0808a410 charsel.c */
void CharselResetMenuPos(void); /* 0x0808a4c0 charsel.c */
void CharselSaveMenuPos(int param_1,undefined4 *param_2,int param_3); /* 0x0808a4e0 charsel.c */
void CharselRestoreMenuPos(int param_1,int *param_2,int param_3); /* 0x0808a520 charsel.c */
bool CharselReadConfig(int param_1); /* 0x0808a560 charsel.c */
uint VersusScreen(void); /* 0x0808af70 charsel.c */
undefined4 ArcadeListBuild(void); /* 0x0808b9f0 charsel.c */
void ArcadeListBuildSet(int *param_1,int param_2,int param_3); /* 0x0808ba60 charsel.c */
int ArcadeListGetCurrent(void); /* 0x0808bd80 charsel.c */
int ArcadeListGet(int param_1); /* 0x0808bd90 charsel.c */
int ArcadeListGetCurSize(void); /* 0x0808bf70 charsel.c */
void ArcadeListPeekCur(int param_1); /* 0x0808bff0 charsel.c */
void ArcadeListPeekNext(int param_1); /* 0x0808c010 charsel.c */
int ArcadeListPeek(int param_1,int param_2); /* 0x0808c030 charsel.c */
int ArcadeListEnemiesLeft(void); /* 0x0808c100 charsel.c */
void SurvivalBuildRandomTeam(undefined4 *param_1,int param_2,int param_3); /* 0x0808c120 charsel.c */
undefined4 GetPlayerRowCol(int param_1,int *param_2,int *param_3); /* 0x0808c390 charsel.c */
undefined4 SlctStateListChanged(int param_1); /* 0x0808c410 charsel.c */
int SlctStateListNextItem(int param_1); /* 0x0808c430 charsel.c */
void SlctStateListUpdate(int param_1); /* 0x0808c470 charsel.c */
void BuildSlctCtrl(int param_1,int param_2,int param_3); /* 0x0808c490 charsel.c */
void BuildSlctTeamForArcade(int param_1,int param_2,int param_3,undefined4 param_4,int param_5); /* 0x0808c630 charsel.c */
void BuildMenuCtrl(int param_1,int param_2,int param_3); /* 0x0808c6d0 charsel.c */
void MenuItemVal(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x0808c8a0 charsel.c */
uint CharReservePal(uint param_1,int param_2); /* 0x0808c8e0 charsel.c */
void CharStopUsingPal(byte param_1,int param_2); /* 0x0808c9b0 charsel.c */
void CharStopUsingPalAll(void); /* 0x0808ca00 charsel.c */
void ParseCmdLine(MugenCmdLine *opts,int argc,char **argv); /* 0x0808ca40 cmdline.c */
undefined4 PrintHelp(void); /* 0x0808d090 cmdline.c */
void GlobalInputUpdate(void); /* 0x0808d0f0 common.c */
undefined4 Warn(int param_1,int param_2); /* 0x0808d100 common.c */
undefined4 VWarn(int param_1,char *param_2,...); /* 0x0808d150 common.c */
int WarnR(int param_1,int param_2,int param_3); /* 0x0808d1c0 common.c */
void StripDoublePercent(char *param_1); /* 0x0808d220 common.c */
void FontDrawClipboard(int *param_1,int *param_2,int param_3,int param_4,uint param_5); /* 0x0808d250 common.c */
undefined4 ErrorExit(void); /* 0x0808d300 common.c */
undefined4 ErrorExitM(char *param_1,...); /* 0x0808d3d0 common.c */
bool fileexist(char *param_1); /* 0x0808d400 common.c */
undefined4 ChangeFileDir(char *param_1,char *param_2,char *param_3); /* 0x0808d440 common.c */
undefined4 FindFileDir(char *param_1,char *param_2,char *param_3); /* 0x0808d5c0 common.c */
undefined4 FindFileDirEx(char *param_1,char *param_2,char *param_3,undefined4 *param_4); /* 0x0808d5e0 common.c */
undefined4 GetQuotedString(int param_1,char *param_2,char *param_3,size_t param_4,char *param_5); /* 0x0808d750 common.c */
int MDYDateCmp(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x0808d830 date.c */
void datenotostr(undefined4 param_1,int param_2,undefined **param_3,char *param_4); /* 0x0808d870 date.c */
void FrameSkipReset(void); /* 0x0808d940 display.c */
void FrameSkipUpdate(void); /* 0x0808d960 display.c */
void DrawToScreen(void); /* 0x0808da20 display.c */
void ScreenSnap(void); /* 0x0808dbb0 display.c */
int * ExplodArrayNew(size_t param_1,undefined4 param_2); /* 0x0808dc30 explod.c */
void ExplodArrayFree(int *param_1); /* 0x0808dcb0 explod.c */
void ExplodArrayUpdate(int *param_1); /* 0x0808dd20 explod.c */
int * ExplodUpdate(int *param_1,int param_2); /* 0x0808dd50 explod.c */
void ExplodArrayDraw(int *param_1,int param_2); /* 0x0808ded0 explod.c */
void ExplodDraw(int param_1); /* 0x0808df40 explod.c */
void ExplodArrayDrawShadow(int *param_1); /* 0x0808e210 explod.c */
void ExplodDrawShadow(int param_1,int *param_2,uint param_3,int *param_4); /* 0x0808e2b0 explod.c */
void ExplodArrayReset(undefined4 *param_1); /* 0x0808e840 explod.c */
void ExplodDefault(undefined4 *param_1); /* 0x0808e870 explod.c */
void ExplodMakeFromInfo(int *param_1,int param_2,int *param_3); /* 0x0808e990 explod.c */
void ExplodModifyFromInfo(int *param_1,int param_2,int *param_3); /* 0x0808ea70 explod.c */
void ExplodSetParams(int *param_1,int param_2,int param_3,int *param_4,int param_5); /* 0x0808eb10 explod.c */
int ExplodAdd(undefined4 *param_1,int param_2,int *param_3,int param_4); /* 0x0808f300 explod.c */
int ExplodAddSprite(undefined4 *param_1,int param_2,int param_3,int *param_4); /* 0x0808f3c0 explod.c */
int ExplodAddText(int *param_1,char *param_2,int param_3,int param_4,int param_5); /* 0x0808f460 explod.c */
void ExplodRemove(int *param_1,int param_2); /* 0x0808f4f0 explod.c */
void ExplodRemoveID(undefined4 *param_1,int param_2,int param_3); /* 0x0808f520 explod.c */
void ExplodRemoveGetHit(undefined4 *param_1,int param_2); /* 0x0808f580 explod.c */
int ExplodAccessID(undefined4 *param_1,int param_2,int param_3); /* 0x0808f5d0 explod.c */
int ExplodGetUniqID(void); /* 0x0808f620 explod.c */
void ExplodBindChange(undefined4 *param_1,int param_2,int param_3,int param_4); /* 0x0808f630 explod.c */
int ExplodCount(int *param_1,int param_2,int param_3); /* 0x0808f680 explod.c */
undefined4 SysExplodParse(int param_1,int *param_2,undefined4 param_3); /* 0x0808f6d0 explod.c */
undefined4 SysExplodParseGetSprGrpImgNo(int *param_1,int *param_2,int *param_3); /* 0x0808f900 explod.c */
void SysExplodCreateDraw(int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6 ,int param_7,int param_8); /* 0x0808f930 explod.c */
int SysExplodCreateDrawPal (int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6, int param_7,int param_8); /* 0x0808f940 explod.c */
int SysExplodCreate(int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6, int param_7); /* 0x0808fa20 explod.c */
void SysExplodCreate_Fight(int *param_1,int param_2,int param_3); /* 0x0808fc90 explod.c */
void SysExplodCreate_Sys(int *param_1,int param_2,int param_3); /* 0x0808fcd0 explod.c */
void SysExplodCreateDraw_Fight(int *param_1,int param_2,int param_3,int param_4); /* 0x0808fd20 explod.c */
void SysExplodCreateDraw_Sys(int *param_1,int param_2,int param_3,int param_4); /* 0x0808fd70 explod.c */
undefined4 GameLoop(int param_1); /* 0x0808fdc0 gameloop.c */
undefined4 GameUpdate(void); /* 0x08091100 gameloop.c */
void GameWinScreenUpdate(void); /* 0x08091e30 gameloop.c */
void GameSurvivalResultsUpdate(void); /* 0x08091fc0 gameloop.c */
undefined4 GameDemoUpdate(void); /* 0x08092180 gameloop.c */
undefined4 GameRoundUpdate(void); /* 0x08092250 gameloop.c */
void GameRoundDraw(void); /* 0x08093540 gameloop.c */
undefined4 GameInputUpdate(void); /* 0x08093900 gameloop.c */
int CameraMoveAbs(float param_1,float param_2); /* 0x08094350 gameloop.c */
void CameraMoveP(void); /* 0x080943d0 gameloop.c */
void ComboAdd(int param_1,int param_2); /* 0x08094d00 gameloop.c */
void ComboClear(int param_1); /* 0x08094d70 gameloop.c */
void ComboDisplay(int param_1); /* 0x08094d90 gameloop.c */
void ComboDisplayUpdate(int param_1); /* 0x08095050 gameloop.c */
void PlayerComboCountCheck(int param_1); /* 0x08095110 gameloop.c */
void GameBGDraw(void); /* 0x080951b0 gameloop.c */
void GameFGDraw(void); /* 0x080952f0 gameloop.c */
void GameBarsDraw(int param_1); /* 0x08095310 gameloop.c */
void GameLifeBarDraw(undefined4 param_1,int param_2,int *param_3,int param_4); /* 0x08096400 gameloop.c */
void GameBarsUpdate(void); /* 0x080968c0 gameloop.c */
void GameLifeBarUpdate(int param_1); /* 0x08096930 gameloop.c */
undefined4 GamePowerBarDraw(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6); /* 0x08096ab0 gameloop.c */
int GamePowerBarUpdate(int param_1); /* 0x08096c10 gameloop.c */
int RequestNewAftImg(int param_1); /* 0x08096d00 gameloop.c */
void GameAftImgReset(int param_1); /* 0x08096d30 gameloop.c */
int GameAftImgCount(int param_1); /* 0x08096d70 gameloop.c */
void PlayerAftImgUpdate(int param_1); /* 0x08096db0 gameloop.c */
void PlayerAftImgDraw(int param_1); /* 0x08096e80 gameloop.c */
void ProjArrayAftImgUpdate(int *param_1); /* 0x08096ed0 gameloop.c */
void ProjAftImgUpdate(int param_1); /* 0x08096f00 gameloop.c */
void ProjArrayAftImgDraw(int *param_1); /* 0x08096fa0 gameloop.c */
void ProjAftImgDraw(int param_1); /* 0x08096fd0 gameloop.c */
void GameClsnDraw(int param_1,float param_2,float param_3,float param_4,float param_5,uint param_6, uint param_7,int param_8); /* 0x08097020 gameloop.c */
int TeamLifeBack(int param_1); /* 0x08097210 gameloop.c */
void WinIconCheckTeam(int param_1,int param_2,uint param_3); /* 0x080972e0 gameloop.c */
void WinIconCheck(int param_1,uint param_2,int param_3); /* 0x08097360 gameloop.c */
undefined4 TeamHasFullLife(int param_1); /* 0x08097420 gameloop.c */
void ShowDebugInfo(int param_1); /* 0x080974b0 gameloop.c */
byte ContinueScreenLoop(void); /* 0x08097940 gameloop.c */
int * HelperMake(int *param_1,char *param_2,int *param_3); /* 0x080980d0 helper.c */
void HelperDestroy(int param_1); /* 0x08098930 helper.c */
uint HelperParent(int param_1); /* 0x08098ad0 helper.c */
undefined4 HelperRoot(int param_1); /* 0x08098b00 helper.c */
int HelperCount(int param_1,int param_2); /* 0x08098b10 helper.c */
undefined4 HelperAccessID(int param_1,int param_2); /* 0x08098bb0 helper.c */
void CloseAllFunc(void); /* 0x08098c50 init.c */
void GameInit(MugenCmdLine opts, int *mode); /* 0x08098c60 init.c */
void GameDeInit(int param_1); /* 0x08099350 init.c */
void GameInitPads(void); /* 0x08099490 init.c */
void GameDefKeyInit(void); /* 0x080995f0 init.c */
bool GameInputSetup(void); /* 0x08099640 init.c */
bool GfxResize(int param_1,int param_2,undefined4 param_3,int param_4); /* 0x080997c0 init.c */
undefined4 GameLoadFightData(FILE *param_1); /* 0x08099880 init.c */
void GameFreeFightData(void); /* 0x0809bc20 init.c */
undefined4 GameVarInit(void); /* 0x0809bcf0 init.c */
undefined4 GameVarLoadFonts(void); /* 0x0809c160 init.c */
undefined4 GameVarDeInit(void); /* 0x0809c200 init.c */
undefined4 * GameAftImgArrayNew(size_t param_1,int param_2); /* 0x0809c320 init.c */
undefined4 GameAftImgArrayFree(void *param_1); /* 0x0809c3b0 init.c */
void SwitchCallbacksInit(void); /* 0x0809c400 init.c */
void SwitchCallbacksDeInit(void); /* 0x0809c410 init.c */
void SwitchAwayCallback(void); /* 0x0809c420 init.c */
void SwitchBackCallback(void); /* 0x0809c440 init.c */
int _mangled_main(int argc, char **argv); /* 0x0809c470 main.c */
void QuickVSSetup(MugenCmdLine *opts); /* 0x0809c6f0 main.c */
void MainLoop(int param_1); /* 0x0809cb60 main.c */
undefined4 GamePlay(void); /* 0x0809d120 main.c */
void ArcadeWinScreen(void); /* 0x0809d630 main.c */
void SurvivalResultsScreen(void); /* 0x0809d830 main.c */
void DemoFightSetup(void); /* 0x0809da60 main.c */
byte ContinueScreen(void); /* 0x0809dc00 main.c */
bool GameModeInFightScreen(void); /* 0x0809dc10 main.c */
bool GameModeInPassiveFightScreen(void); /* 0x0809dc30 main.c */
undefined4 GameLoadStage(void); /* 0x0809dc50 match.c */
bool GameBGLoad(void); /* 0x0809e630 match.c */
void GameUnloadStage(void); /* 0x0809e730 match.c */
undefined4 GameStgInitFightData(void); /* 0x0809e8d0 match.c */
void GameStgDeInitFightData(void); /* 0x0809eb00 match.c */
void GameNextRound(void); /* 0x0809eb60 match.c */
undefined4 GameReloadStage(void); /* 0x0809ece0 match.c */
void GameMatchReset(void); /* 0x0809edf0 match.c */
void GameRoundReset(void); /* 0x0809f210 match.c */
int GameRoundResetPlayerPos(void); /* 0x0809f880 match.c */
int GameRoundWinner(void); /* 0x0809f960 match.c */
int GameMatchWinner(void); /* 0x0809f970 match.c */
void LogPreMatch(void); /* 0x0809fa40 match.c */
void LogMatch(void); /* 0x0809fc40 match.c */
void IntroScreen(void); /* 0x0809fd70 menus.c */
void PlayCutscene(char *param_1,char *param_2); /* 0x0809fd90 menus.c */
void ModeSelect(void); /* 0x080a01b0 menus.c */
void OptionsScreen(void); /* 0x080a1830 menus.c */
int KeyConfigScreen(int param_1,int param_2); /* 0x080a3aa0 menus.c */
undefined4 TrainingMenuUpdate(uint param_1); /* 0x080a4ff0 menus.c */
uint TrainingMenuReset(void); /* 0x080a5480 menus.c */
void TrainingMenuDraw(void); /* 0x080a54b0 menus.c */
void InfoTextDraw(char *param_1,int param_2,int param_3); /* 0x080a5b70 menus.c */
undefined4 PlayerAIInit(int param_1,int param_2); /* 0x080a5d70 p-ai.c */
void PlayerAIDeInit(int param_1); /* 0x080a5dd0 p-ai.c */
undefined4 AILearnDataLoad(char *param_1,undefined4 *param_2); /* 0x080a5e00 p-ai.c */
undefined4 AILearnDataSave(char *param_1,int param_2); /* 0x080a6080 p-ai.c */
undefined4 AIStateSetInit(int param_1); /* 0x080a61d0 p-ai.c */
void AIStateSetDeInit(undefined4 *param_1); /* 0x080a6230 p-ai.c */
void AIStateSetClear(int param_1); /* 0x080a6270 p-ai.c */
undefined4 AIStateSetMerge(int param_1,int param_2); /* 0x080a62a0 p-ai.c */
void AIStateSetCopy(int param_1,int param_2); /* 0x080a6380 p-ai.c */
void PlayerAISetLevel(int param_1,undefined4 param_2); /* 0x080a63b0 p-ai.c */
void PlayerResetAI(int param_1); /* 0x080a63c0 p-ai.c */
void PlayerAI(int param_1); /* 0x080a6440 p-ai.c */
void PlayerAIProcessCommands(int param_1); /* 0x080a6570 p-ai.c */
undefined4 AIInsertCommand(int *param_1,int param_2); /* 0x080a65c0 p-ai.c */
void AICopyCommands(int param_1,int *param_2); /* 0x080a6600 p-ai.c */
void AIClearCommands(undefined4 *param_1); /* 0x080a6630 p-ai.c */
int AICountCommands(int *param_1); /* 0x080a6640 p-ai.c */
undefined4 PlayerAILearnMoveStart(int param_1); /* 0x080a6660 p-ai.c */
void PlayerAILearnMoveUpdate(int param_1,int param_2); /* 0x080a67f0 p-ai.c */
int AILearnClsnUpdate(int param_1,int param_2); /* 0x080a71f0 p-ai.c */
void AILearnIdleClsnUpdate(int param_1); /* 0x080a7460 p-ai.c */
int AIIdleClsnMatchState(int param_1); /* 0x080a7620 p-ai.c */
undefined4 PlayerAILearnMoveEnd(int param_1,int param_2); /* 0x080a7670 p-ai.c */
undefined4 PlayerAIGetAIPLHS(int param_1); /* 0x080a79d0 p-ai.c */
undefined4 AIFetchLearnDataArray(int param_1,int param_2); /* 0x080a7a20 p-ai.c */
void PlayerAIMsgAttack(int param_1); /* 0x080a7a50 p-ai.c */
void PlayerAIMsgAttackEnd(int param_1); /* 0x080a7ad0 p-ai.c */
int PlayerAIBroadcastMsg (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5); /* 0x080a7b20 p-ai.c */
int PlayerAIFindMsg(int param_1,int param_2,int param_3); /* 0x080a7bf0 p-ai.c */
undefined4 * PlayerAIGetMsg(undefined4 *param_1,int param_2,int param_3,int param_4); /* 0x080a7c40 p-ai.c */
undefined4 * PlayerAIGetAndRemoveMsg(undefined4 *param_1,int param_2,int param_3,int param_4); /* 0x080a7ce0 p-ai.c */
void PlayerAIClearMsg(int param_1); /* 0x080a7d80 p-ai.c */
void PlayerAIMsgStateUpdate(int param_1); /* 0x080a7d90 p-ai.c */
void PlayerAISctrlProjectile(int param_1,undefined4 *param_2); /* 0x080a7de0 p-ai.c */
void AIForNormal(int param_1,int param_2); /* 0x080a7e00 p-ai.c */
undefined4 AIForNormalDecisions(int param_1,int param_2); /* 0x080a7f30 p-ai.c */
undefined4 AIMovePlanRoute(int param_1,undefined4 param_2,int param_3,int param_4); /* 0x080a86d0 p-ai.c */
undefined4 AIMoveReachedDest(int param_1); /* 0x080a88d0 p-ai.c */
undefined4 AIMoveReachedDestIdx(int param_1,int param_2); /* 0x080a8910 p-ai.c */
undefined4 AIForNormalIdle(int param_1); /* 0x080a8a10 p-ai.c */
void AISetIdleAction(int param_1,undefined4 param_2); /* 0x080a8ad0 p-ai.c */
undefined4 AIForNormalMove(int param_1); /* 0x080a8ae0 p-ai.c */
undefined4 AIForNormalAttack(int param_1,int param_2); /* 0x080a8dd0 p-ai.c */
undefined4 AIAttackSetupAttack(int param_1,undefined4 param_2,undefined4 param_3); /* 0x080a8fb0 p-ai.c */
undefined4 AIForNormalGuard(int param_1,int param_2); /* 0x080a8fe0 p-ai.c */
int AIAttackInRange(int param_1,undefined4 param_2,int param_3,int param_4); /* 0x080a90c0 p-ai.c */
int AIBuildCounterAttackList(int param_1,undefined4 param_2); /* 0x080a93a0 p-ai.c */
undefined4 AIForNormalRandom(int param_1,int param_2,int param_3); /* 0x080a9640 p-ai.c */
void AIForTrainingMode(int param_1,int param_2); /* 0x080a9e50 p-ai.c */
undefined4 AICheckForAttacks(int param_1); /* 0x080aa560 p-ai.c */
void AIValMake(float *param_1,float param_2); /* 0x080aa600 p-ai.c */
float * AIValMerge(float *param_1,float param_2,float param_3,float param_4,float param_5, float param_6,float param_7,float param_8); /* 0x080aa650 p-ai.c */
void AIValMergeR(float *param_1,float param_2,float param_3,float param_4,int param_5); /* 0x080aa720 p-ai.c */
undefined4 AILearnStopRecord(int param_1); /* 0x080aa780 p-ai.c */
void AIMergeLearnData(int *param_1,int param_2,int param_3); /* 0x080aa7b0 p-ai.c */
undefined4 AIChangeState(int param_1,undefined4 param_2); /* 0x080ab080 p-ai.c */
void AIKBReleaseDir(int param_1); /* 0x080ab0a0 p-ai.c */
void AIKBReleaseDirExcept(int param_1,uint param_2); /* 0x080ab0e0 p-ai.c */
void AIKBReleaseAll(int param_1); /* 0x080ab130 p-ai.c */
void AIKBReleaseAllExcept(int param_1,uint param_2); /* 0x080ab170 p-ai.c */
int PlayerNearestEnemy(int param_1); /* 0x080ab1c0 p-info.c */
int PartnerAccess(int param_1,int param_2); /* 0x080ab3b0 p-info.c */
int PartnerCount(int param_1); /* 0x080ab430 p-info.c */
int EnemyAccess(int param_1,int param_2); /* 0x080ab4b0 p-info.c */
int EnemyCount(int param_1); /* 0x080ab540 p-info.c */
undefined4 EnemyAccessNear(int param_1,int param_2); /* 0x080ab5d0 p-info.c */
int PlayerAccessID(int param_1); /* 0x080ab6d0 p-info.c */
int PlayerGetDamagedLife(int param_1); /* 0x080ab740 p-info.c */
undefined4 PlayerInCorner(int param_1); /* 0x080ab760 p-info.c */
int PlayerDistX(int param_1,int param_2); /* 0x080ab7e0 p-info.c */
int PlayerBodyDistX(int param_1,int param_2); /* 0x080ab830 p-info.c */
undefined4 PlayerInAnyGuardDist(int param_1); /* 0x080ab930 p-info.c */
undefined4 PlayerInGuardDist(int param_1,int param_2); /* 0x080ab9f0 p-info.c */
bool HitdefAffectTeam(int param_1,int param_2,uint param_3); /* 0x080abab0 p-info.c */
undefined4 PlayerAreEnemies(int param_1,int param_2); /* 0x080abae0 p-info.c */
int PlayerGetWidth(int param_1,int param_2,uint param_3); /* 0x080abb10 p-info.c */
bool PlayerAnimExist(int param_1,int param_2); /* 0x080abbf0 p-info.c */
bool PlayerSelfAnimExist(int *param_1,int param_2); /* 0x080abc20 p-info.c */
undefined4 PlayerLyingDead(int param_1); /* 0x080abc70 p-info.c */
int * PlayerFindTarget(int param_1,int param_2); /* 0x080abc90 p-info.c */
undefined4 TargetAccessID(int param_1,int param_2); /* 0x080abcc0 p-info.c */
int TargetCount(int param_1,int param_2); /* 0x080abd00 p-info.c */
void PlayerKBUpdate(int *param_1); /* 0x080abd40 p-input.c */
int PlayerCacheLoad(int param_1); /* 0x080ac660 p-make.c */
void PlayerCacheFree(int param_1); /* 0x080ac930 p-make.c */
int PlayerCacheFreePriority(int param_1,int param_2); /* 0x080ac950 p-make.c */
void PlayerCacheChangePriority(int param_1,int param_2); /* 0x080ac9b0 p-make.c */
bool PlayerIsCached(int param_1); /* 0x080aca00 p-make.c */
void PlayerCacheClear(void); /* 0x080aca40 p-make.c */
undefined4 PlayerCacheHasUnused(void); /* 0x080acb40 p-make.c */
void * PlayerDefLoad(char *param_1,char *param_2); /* 0x080acba0 p-make.c */
int * PlayerDefLoadZip(char *param_1,int *param_2); /* 0x080acc70 p-make.c */
char * PlayerDefLoadPtr(char *param_1,FILE *param_2); /* 0x080ada90 p-make.c */
undefined4 PlayerCNSLoadTP(int param_1,int param_2); /* 0x080ae4a0 p-make.c */
bool PlayerSTLoadTP(int param_1,int param_2); /* 0x080aeca0 p-make.c */
undefined4 PlayerSTLoadAppend(int param_1,char *param_2); /* 0x080aecd0 p-make.c */
undefined4 PlayerCMDLoad(char *param_1,uint *param_2); /* 0x080aed20 p-make.c */
undefined4 PlayerCMDLoadTP(uint param_1,uint *param_2); /* 0x080aed90 p-make.c */
undefined4 ParseCMD(int *param_1,char *param_2,undefined4 *param_3); /* 0x080af400 p-make.c */
undefined4 ParseCMDElem(undefined1 *param_1,undefined4 *param_2,undefined4 *param_3); /* 0x080af680 p-make.c */
void CmdSetFreeLabel(int param_1); /* 0x080af780 p-make.c */
void StringArrayFree(void *param_1,int param_2); /* 0x080af7b0 p-make.c */
void CmdSetDeInit(int *param_1); /* 0x080af800 p-make.c */
void PlayerRCFree(void *param_1); /* 0x080af870 p-make.c */
int * PlayerNew(int param_1); /* 0x080af8f0 p-make.c */
int GetRampedAILevel(void); /* 0x080afcc0 p-make.c */
undefined4 PlayerChangePal(int param_1,int param_2); /* 0x080afdd0 p-make.c */
void PlayerFree(int *param_1); /* 0x080aff80 p-make.c */
undefined4 PlayerCheck(int *param_1); /* 0x080b0090 p-make.c */
void ResetPersistVar(undefined4 *param_1); /* 0x080b02d0 p-make.c */
void GameResetPersistVars(void); /* 0x080b02f0 p-make.c */
void TeamResetPersistVars(int param_1); /* 0x080b0310 p-make.c */
void PlayerSavePersistVars(int param_1,undefined4 *param_2); /* 0x080b03a0 p-make.c */
void PlayerRestorePersistVars(int param_1,int param_2); /* 0x080b0410 p-make.c */
void GameLoadAndActivateTeam(int param_1); /* 0x080b0470 p-make.c */
void GameActivateAI(void); /* 0x080b0560 p-make.c */
undefined4 GameLoadAndCreateChars(int param_1); /* 0x080b0610 p-make.c */
undefined4 GameFreeChars(int param_1); /* 0x080b09d0 p-make.c */
undefined4 GameFreePlayerDependencies(int *param_1); /* 0x080b0b50 p-make.c */
int TeamReorderAll(int param_1); /* 0x080b0cb0 p-make.c */
void PlayerReset(int *param_1); /* 0x080b0fe0 p-update.c */
int PlayerEnableSet(int param_1,int param_2); /* 0x080b15d0 p-update.c */
byte PlayerChangeState(int param_1,int param_2); /* 0x080b1730 p-update.c */
int * PlayerLifeSet(int param_1,uint param_2); /* 0x080b17d0 p-update.c */
void PlayerLifeSetNoIcon(int param_1,uint param_2); /* 0x080b18d0 p-update.c */
void PlayerPowerSet(int param_1,uint param_2); /* 0x080b1950 p-update.c */
void PlayerChangeAnim(int *param_1,int param_2); /* 0x080b1990 p-update.c */
void PlayerChangeAnimElem(int *param_1,int param_2,int param_3); /* 0x080b1a10 p-update.c */
void PlayerSelfAnim(int *param_1,int param_2); /* 0x080b1ac0 p-update.c */
void PlayerSelfAnimElem(int *param_1,int param_2,int param_3); /* 0x080b1ae0 p-update.c */
undefined4 PlayerAutoTurn(int param_1,int param_2,int param_3); /* 0x080b1b00 p-update.c */
void PlayerTurnAround(int param_1); /* 0x080b1bc0 p-update.c */
void PlayerUpdate(int *player); /* 0x080b1bf0 p-update.c */
undefined4 PlayerUpdateBindTo(int param_1); /* 0x080b2cf0 p-update.c */
void ScreenBound(int param_1); /* 0x080b2db0 p-update.c */
void StageBound(int param_1); /* 0x080b2f00 p-update.c */
void GameClsnUpdate(void); /* 0x080b2fa0 p-update.c */
void PlayerPushCheck(int param_1,int param_2,int param_3); /* 0x080b3430 p-update.c */
void PlayerCheckOverlap(int param_1,int param_2); /* 0x080b36a0 p-update.c */
undefined4 PlayerCheckP1HitP2(int param_1,int param_2); /* 0x080b37d0 p-update.c */
bool PlayerCheckHit(int param_1,int param_2); /* 0x080b3830 p-update.c */
void Player1HitP2(int *param_1,int *param_2); /* 0x080b3b40 p-update.c */
undefined4 PlayerGetHit(int *param_1,int *param_2,int param_3,float param_4,float param_5,float param_6, int param_7,int param_8,int param_9); /* 0x080b4400 p-update.c */
void PlayerTakeDamage(int param_1,int param_2,int param_3,int param_4); /* 0x080b4f10 p-update.c */
int PlayerGetCorrectedDamage(int param_1,int param_2,int param_3); /* 0x080b4fa0 p-update.c */
undefined4 PlayerGetHitG(int *param_1,int *param_2,int param_3,int param_4); /* 0x080b5040 p-update.c */
undefined4 PlayerCheckReversal(int param_1,int param_2); /* 0x080b5310 p-update.c */
void Player1ReverseP2(int *param_1,int *param_2); /* 0x080b5510 p-update.c */
void PlayerCheckHitProj(int param_1,int *param_2); /* 0x080b5a90 p-update.c */
void PlayerCheckProjHit(int *param_1,int *param_2); /* 0x080b5db0 p-update.c */
undefined4 PlayerProjDoHit(int param_1); /* 0x080b6760 p-update.c */
undefined4 CheckProjHitProj(int param_1,int param_2); /* 0x080b67e0 p-update.c */
undefined4 PlayerCheckFlagHit(int param_1,uint param_2); /* 0x080b6a60 p-update.c */
undefined4 PlayerCheckAttrHit(int param_1,uint param_2); /* 0x080b6b00 p-update.c */
bool AttrMatch(uint param_1,uint param_2); /* 0x080b6b20 p-update.c */
void PlayerAttrStateSet(int param_1); /* 0x080b6b40 p-update.c */
void PlayerDropBoundTargets(int param_1,int *param_2); /* 0x080b6ba0 p-update.c */
int PlayerSparkCreate(int *param_1,int param_2,int param_3,int param_4,int param_5, undefined4 param_6,int param_7); /* 0x080b6c60 p-update.c */
int PlayerMakeDust(int param_1); /* 0x080b6da0 p-update.c */
int PlayerCalcDraw(int param_1); /* 0x080b6f40 p-update.c */
void PlayerDrawAnim(int param_1,float param_2); /* 0x080b71c0 p-update.c */
void PlayerDrawShadow(int param_1,int *param_2,int *param_3); /* 0x080b73c0 p-update.c */
void PlayerDrawClsn(int param_1,float param_2); /* 0x080b79b0 p-update.c */
undefined4 PalGrpAdd(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x080b8460 pal.c */
void PalGrpRemove(PalGrpFlag f); /* 0x080b8610 pal.c */
undefined4 PalGrpAddSpr(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x080b86d0 pal.c */
void PalGrpBuildFight(void); /* 0x080b8730 pal.c */
undefined4 * PalGrpClear(void); /* 0x080b8960 pal.c */
void PalGrpResetPalette(void); /* 0x080b89e0 pal.c */
void PalGrpSetAdd(PalGrpFlag f,int r,int g_local,int b); /* 0x080b8a20 pal.c */
void PalGrpSetMul(PalGrpFlag f,int r,int g_local,int b); /* 0x080b8ac0 pal.c */
void PalGrpSetInvertAll(PalGrpFlag f,int invert); /* 0x080b8b70 pal.c */
void PalGrpSetColorBal(PalGrpFlag f,int colorbal); /* 0x080b8c00 pal.c */
void PalGrpSetClear(PalGrpFlag f); /* 0x080b8c90 pal.c */
PalGrpFlag * PalGrpMakeFlag(PalGrpFlag *__return_storage_ptr__,uint group,int unused); /* 0x080b8d10 pal.c */
PalGrpFlag * PalGrpMakeFlagALL(PalGrpFlag *__return_storage_ptr__); /* 0x080b8d80 pal.c */
PalGrpFlag * PalGrpOrFlag(PalGrpFlag *__return_storage_ptr__,PalGrpFlag a,PalGrpFlag b); /* 0x080b8dd0 pal.c */
PalGrpFlag * PalGrpXorFlag(PalGrpFlag *__return_storage_ptr__,PalGrpFlag a,PalGrpFlag b); /* 0x080b8e20 pal.c */
int PalGrpAndFlagZero(PalGrpFlag a,PalGrpFlag b); /* 0x080b8e70 pal.c */
int PalGrpFlagEqual(PalGrpFlag a,PalGrpFlag b); /* 0x080b8e90 pal.c */
int PalGrpFlagIsNonZero(PalGrpFlag a); /* 0x080b8eb0 pal.c */
void PalFXReset(undefined4 *param_1); /* 0x080b8ed0 pal.c */
void PalFXUpdate(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7,int param_8); /* 0x080b8f10 pal.c */
undefined4 * ProjArrayNew(size_t param_1,undefined4 param_2,undefined4 param_3); /* 0x080b9170 projctl.c */
void ProjArrayFree(undefined4 *param_1); /* 0x080b91e0 projctl.c */
int ProjArrayAdd(int *param_1,int *param_2,void *param_3,int param_4); /* 0x080b9210 projctl.c */
void ProjArrayDelete(int *param_1,int param_2); /* 0x080b92b0 projctl.c */
void ProjArrayUpdate(int *param_1); /* 0x080b9310 projctl.c */
void ProjArrayCalcDraw(int *param_1); /* 0x080b9670 projctl.c */
int ProjArrayCountActive(int *param_1); /* 0x080b97a0 projctl.c */
int ProjArrayCountActiveID(int *param_1,int param_2); /* 0x080b97e0 projctl.c */
undefined4 ProjClsnDetect(int *param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x080b9830 projctl.c */
undefined4 ProjArrayDraw(int *param_1); /* 0x080b9910 projctl.c */
void ProjArrayDrawShadow(int *param_1); /* 0x080b9980 projctl.c */
void ProjDrawShadow(int param_1,int *param_2,uint param_3,int *param_4); /* 0x080b9a00 projctl.c */
void ProjArrayClsnDraw(int *param_1,float param_2); /* 0x080b9ea0 projctl.c */
void ProjClsnDraw(int param_1,float param_2); /* 0x080b9ee0 projctl.c */
void GameSndPlay(int *param_1,int param_2,int param_3,int param_4); /* 0x080b9fd0 sound.c */
void GameSndPlayID(int param_1,int *param_2,int param_3,int param_4,int param_5); /* 0x080ba000 sound.c */
int GameSndPlayIDPos(int param_1,int param_2,int *param_3,int param_4,int param_5,int param_6); /* 0x080ba090 sound.c */
int ScrPositionToPan(int param_1); /* 0x080ba180 sound.c */
uint PanVolumeAdjust(int param_1,int param_2); /* 0x080ba230 sound.c */
void GameSetVol(int param_1,uint param_2); /* 0x080ba2a0 sound.c */
int PlayerSndID(int param_1,int param_2); /* 0x080ba330 sound.c */
void ParseSndGI(int param_1,char *param_2,undefined4 *param_3,int param_4); /* 0x080ba360 sound.c */
undefined4 SCtrlParseElemType(int param_1,int param_2,int param_3); /* 0x080ba390 st-ctrl.c */
bool SCtrlParseElem(int param_1,int *param_2,undefined4 param_3,int param_4); /* 0x080bee10 st-ctrl.c */
undefined4 PlayerDoSCtrlApplyElem(int *param_1,int param_2,int *param_3); /* 0x080bf1d0 st-ctrl.c */
undefined4 PlayerSCtrlApplyElem(int *player,int param_2,int *param_3); /* 0x080bf290 st-ctrl.c */
undefined4 SCtrlRCElemFree(undefined4 *param_1); /* 0x080c3630 st-ctrl.c */
char * TPGetValuePrefix(int param_1,undefined4 param_2,undefined4 param_3); /* 0x080c3810 st-exprn.c */
char * StringAdd(char *param_1,undefined4 param_2,undefined4 param_3); /* 0x080c3850 st-exprn.c */
undefined4 SCtrlParseAftImgParams(int param_1,int param_2,int *param_3,undefined4 param_4); /* 0x080c3880 st-exprn.c */
undefined4 SCtrlInitAftImgParams(int param_1,int param_2,undefined4 param_3,int *param_4); /* 0x080c3e20 st-exprn.c */
void AftImgParamsEFree(int *param_1); /* 0x080c40c0 st-exprn.c */
undefined4 SCtrlParseEnvShake(int param_1,int param_2,int *param_3,undefined4 param_4); /* 0x080c41f0 st-exprn.c */
undefined4 SCtrlInitEnvShake(int *player,undefined4 *param_2,int *param_3); /* 0x080c4310 st-exprn.c */
void EnvShakeEFree(int *param_1); /* 0x080c43e0 st-exprn.c */
undefined4 SCtrlParseExplod(int param_1,int param_2,int *param_3,int param_4); /* 0x080c4420 st-exprn.c */
void ExplodInfoFree(int *param_1); /* 0x080c4b10 st-exprn.c */
bool SCtrlParsePalFX(int param_1,int param_2,int param_3,int param_4); /* 0x080c4c90 st-exprn.c */
undefined4 SCtrlInitPalFX(int *param_1,undefined4 *param_2,int param_3); /* 0x080c4e80 st-exprn.c */
void PalFXEFree(int param_1); /* 0x080c5020 st-exprn.c */
undefined4 SCtrlParsePlaySndInfo(int param_1,int param_2,int *param_3); /* 0x080c50c0 st-exprn.c */
int SCtrlDoPlaySndInfo(int *player,int param_2); /* 0x080c52a0 st-exprn.c */
void PlaySndInfoFree(int *param_1); /* 0x080c55f0 st-exprn.c */
bool SCtrlParseHitOverride(int param_1,int param_2,int *param_3); /* 0x080c5650 st-exprn.c */
undefined4 SCtrlInitHitOverride(undefined4 *param_1,undefined4 *param_2,int param_3); /* 0x080c5740 st-exprn.c */
void HitOverrideEFree(int param_1); /* 0x080c57e0 st-exprn.c */
bool SCtrlParseHitDef(int param_1,int param_2,undefined4 *param_3); /* 0x080c5810 st-exprn.c */
undefined4 SCtrlInitHitDef(undefined4 *param_1,int param_2,int *param_3); /* 0x080c7360 st-exprn.c */
void HitDefEFree(int param_1); /* 0x080c7f30 st-exprn.c */
undefined4 SCtrlParseProjectile(int param_1,int param_2,int *param_3); /* 0x080c83a0 st-exprn.c */
int SCtrlInitProjectile(int param_1,int *param_2,int param_3,int *param_4); /* 0x080c8b90 st-exprn.c */
void ProjMakeInfoFree(int *param_1); /* 0x080c93d0 st-exprn.c */
bool SCtrlParseHelper(int param_1,int param_2,char *param_3); /* 0x080c95c0 st-exprn.c */
void HelperInfoFree(int param_1); /* 0x080c9a90 st-exprn.c */
bool SCtrlParsePause(int param_1,int param_2,int *param_3); /* 0x080c9bc0 st-exprn.c */
undefined4 SCtrlInitPause(int param_1,int param_2,int param_3); /* 0x080c9c50 st-exprn.c */
void PauseInfoFree(int *param_1); /* 0x080c9d80 st-exprn.c */
bool SCtrlParseSuperPause(int param_1,int param_2,int *param_3); /* 0x080c9dc0 st-exprn.c */
void SuperPauseInfoFree(int *param_1); /* 0x080c9f50 st-exprn.c */
void MoreExpFree(int *param_1); /* 0x080c9fd0 st-exprn.c */
char * SCtrlParseTrigger(char *param_1,int param_2,undefined4 *param_3,void *param_4,int param_5, int *param_6); /* 0x080ca000 st-trig.c */
undefined4 SCtrlParseTriggerCMD(char *param_1,int param_2,int param_3,undefined4 *param_4); /* 0x080ccef0 st-trig.c */
undefined4 SCtrlParseTriggerRange(char *param_1,int param_2,int *param_3); /* 0x080ccfc0 st-trig.c */
char SCtrlTrigArity(int param_1); /* 0x080cd2b0 st-trig.c */
undefined4 SCtrlTrigArrayTest(int *param_1,int param_2,int param_3); /* 0x080cd2f0 st-trig.c */
bool SCtrlTrigTest(int *param_1,int *param_2); /* 0x080cd3c0 st-trig.c */
void SCtrlTrigEval(int *param_1,int *param_2); /* 0x080cd450 st-trig.c */
void TriggerFree(void *param_1); /* 0x080d0740 st-trig.c */
undefined4 trigcpy(int *param_1,int *param_2); /* 0x080d0780 st-trig.c */
char SPopI(int param_1,int *param_2); /* 0x080d0830 state-i.c */
char SPopF(undefined4 param_1,float *param_2); /* 0x080d0900 state-i.c */
undefined4 StackUnderflow(void); /* 0x080d09a0 state-i.c */
undefined4 ItoP_TPConstI(int param_1,char *param_2,int *param_3,int param_4,int param_5); /* 0x080d09c0 state-i.c */
undefined4 ItoP_TPConstF(int param_1,char *param_2,int *param_3,int param_4,int param_5); /* 0x080d0a30 state-i.c */
byte * SCtrlReadExpList(byte *param_1,char *param_2,int param_3,undefined4 *param_4,...); /* 0x080d0aa0 state-i.c */
int SCtrlReadExpListArray (byte *param_1,char *param_2,int param_3,undefined4 *param_4,int param_5,int param_6, int *param_7,int param_8); /* 0x080d0c90 state-i.c */
int ParsePosType(char *param_1); /* 0x080d0e80 state-i.c */
undefined4 ParseSpecialFlag(char *param_1,undefined4 *param_2,undefined4 *param_3); /* 0x080d0ee0 state-i.c */
bool ParseAnim(byte *param_1,int *param_2,undefined4 *param_3,int param_4); /* 0x080d12f0 state-i.c */
uint ParseSnd(byte *param_1,int *param_2,int *param_3,undefined4 *param_4,int param_5); /* 0x080d1370 state-i.c */
bool ParseVel(byte *param_1,int *param_2,int *param_3,int param_4); /* 0x080d13f0 state-i.c */
uint ParseHitAttr(int param_1,int param_2); /* 0x080d1530 state-i.c */
uint ParseHitFlag(char *param_1); /* 0x080d1850 state-i.c */
void PlayerGetRedirInfo(int param_1,undefined4 *param_2); /* 0x080d18e0 state-i.c */
int * SctrlReadFileTP(int param_1,int param_2); /* 0x080d19b0 state.c */
undefined4 SctrlAddFileTP(int *param_1,int param_2,int param_3); /* 0x080d1b30 state.c */
undefined4 SCtrlParseState(int param_1,int *param_2,int *param_3,int param_4); /* 0x080d1c90 state.c */
undefined4 SCtrlInit(undefined4 *param_1,undefined4 param_2); /* 0x080d2460 state.c */
void SCtrlRCFree(undefined4 *param_1); /* 0x080d2480 state.c */
undefined4 PlayerSCtrlUpdate(int *player); /* 0x080d2590 state.c */
void PlayerSCtrlUpdateSpec(int *player,int param_2,uint param_3); /* 0x080d2a60 state.c */
undefined4 GameLoadSystem(void); /* 0x080d2b60 system.c */
void GameUnloadSystem(void); /* 0x080d39b0 system.c */
int GameReloadSystemSprSnd(void); /* 0x080d3b40 system.c */
void GameUnloadSystemSprSnd(void); /* 0x080d3dd0 system.c */
undefined4 GameConfigRead(char *param_1); /* 0x080d3e70 system.c */
void GameResetOptions(void); /* 0x080d4ea0 system.c */
undefined4 GameLoadOptions(void); /* 0x080d4ef0 system.c */
void GameSaveOptions(void); /* 0x080d51e0 system.c */
bool PlayerLoadKeys(int param_1,int param_2,char *param_3); /* 0x080d5480 system.c */
void PlayerSaveKeys(int param_1,int param_2,char *param_3); /* 0x080d5580 system.c */
void PlayerKeysRemoveZero(int param_1,undefined4 param_2); /* 0x080d56a0 system.c */
void PlayerKeysConvertToZero(int param_1,int param_2); /* 0x080d56d0 system.c */
uint PrecacheInit(int param_1); /* 0x080d5700 precache.c */
undefined4 PrecacheRequestTeam(int param_1); /* 0x080d5770 precache.c */
void PrecacheRequestCurArcadeTeam(void); /* 0x080d57f0 precache.c */
void PrecacheRequestNextArcadeTeam(void); /* 0x080d5800 precache.c */
undefined4 PrecacheRequestArcadeTeam(int param_1); /* 0x080d5810 precache.c */
bool PrecacheRequestChar(int param_1); /* 0x080d58a0 precache.c */
undefined4 PrecacheStart(void); /* 0x080d5900 precache.c */
void PrecacheRequestCancel(void); /* 0x080d59f0 precache.c */
int PrecacheIsRunning(void); /* 0x080d5a30 precache.c */
undefined4 PrecacheIsDone(void); /* 0x080d5a70 precache.c */
void PrecacheFinish(void); /* 0x080d5ad0 precache.c */
void PrecacheWorkerThread(void); /* 0x080d5b60 precache.c */
bool IntQueueAddUnique(int *param_1,int param_2,int param_3); /* 0x080d5d90 precache.c */
bool IntQueueIsEmpty(int *param_1); /* 0x080d5df0 precache.c */
undefined4 IntQueuePeekTop(int *param_1,int *param_2); /* 0x080d5e00 precache.c */
undefined4 IntQueueDequeue(int *param_1,int *param_2); /* 0x080d5e20 precache.c */
undefined4 * IntQueueClear(undefined4 *param_1); /* 0x080d5e60 precache.c */

/* ---- library functions called by the game (non-libc) ---- */
undefined4 install_mod(int param_1); /* 0x080d5e70 mod.c */
undefined1 * load_mod(byte * param_1); /* 0x080d60e0 mod.c */
undefined4 play_mod(int param_1, int param_2); /* 0x080d62a0 mod.c */
undefined4 destroy_mod(void * param_1); /* 0x080d6ab0 mod.c */
undefined4 remove_mod(void); /* 0x080d6f40 mod.c */
undefined4 stop_mod(void); /* 0x080d7100 mod.c */
undefined4 pause_mod(void); /* 0x080d71c0 mod.c */
undefined4 resume_mod(void); /* 0x080d7240 mod.c */
undefined4 set_mod_volume(int param_1); /* 0x080d7310 mod.c */
undefined4 get_mod_volume(void); /* 0x080d7390 mod.c */
undefined4 load_amp(char * param_1, undefined4 param_2); /* 0x080e0b10 audiolib.c */
undefined4 poll_amp(void); /* 0x080e0f80 audiolib.c */
int install_amp(void); /* 0x080e14f0 audiolib.c */
undefined4 unload_amp(void); /* 0x080e1640 audiolib.c */
undefined4 set_volume_mp3(int param_1); /* 0x080e17c0 audiolib.c */
undefined4 get_volume_mp3(void); /* 0x080e17d0 audiolib.c */
undefined4 install_allegro(uint param_1, int * param_2, undefined * param_3); /* 0x080ed330 allegro.c */
undefined4 allegro_exit(void); /* 0x080ed610 allegro.c */
undefined4 blit(int * param_1, int * param_2, int param_3, int param_4, int param_5, int param_6, uint param_7, int param_8); /* 0x080f2d60 blit.c */
undefined4 makecol(undefined4 param_1, int param_2, int param_3); /* 0x080f3340 color.c */
undefined4 override_config_data(int param_1, int param_2); /* 0x080f6570 config.c */
undefined4 vsync(void); /* 0x080fc150 gfx.c */
undefined4 rect(int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 param_6); /* 0x080fd050 gfx.c */
undefined4 set_color_depth(undefined4 param_1); /* 0x080fecb0 graphics.c */
undefined4 set_gfx_mode(uint param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, uint param_5); /* 0x080fef00 graphics.c */
int * create_bitmap_ex(int param_1, int param_2, int param_3); /* 0x080ffbb0 graphics.c */
int * create_video_bitmap(uint param_1, uint param_2); /* 0x081001b0 graphics.c */
undefined4 destroy_bitmap(int * param_1); /* 0x08100370 graphics.c */
undefined4 set_clip(uint * param_1, uint param_2, uint param_3, uint param_4, uint param_5); /* 0x08100440 graphics.c */
uint show_video_bitmap(int * param_1); /* 0x08100730 graphics.c */
undefined4 install_joystick(int param_1); /* 0x08100b40 joystick.c */
undefined4 remove_joystick(void); /* 0x08100d50 joystick.c */
undefined4 poll_joystick(void); /* 0x08100da0 joystick.c */
undefined4 set_leds(int param_1); /* 0x081014e0 keyboard.c */
undefined4 set_keyboard_rate(int param_1, undefined4 param_2); /* 0x08101530 keyboard.c */
undefined4 install_keyboard(void); /* 0x08101e50 keyboard.c */
undefined4 remove_keyboard(void); /* 0x08101f50 keyboard.c */
undefined4 _alemu_strlwr(char * param_1); /* 0x08102020 libc.c */
int _alemu_stricmp(char * param_1, char * param_2); /* 0x08102080 libc.c */
uint * load_midi(byte * param_1); /* 0x08102850 midi.c */
undefined4 destroy_midi(void * param_1); /* 0x08102d20 midi.c */
undefined4 play_midi(int * param_1, undefined4 param_2); /* 0x08104db0 midi.c */
undefined4 play_looped_midi(int * param_1, undefined4 param_2, undefined4 param_3); /* 0x08104ed0 midi.c */
undefined4 stop_midi(void); /* 0x08104f10 midi.c */
undefined4 midi_pause(void); /* 0x08104f20 midi.c */
undefined4 midi_resume(void); /* 0x08104fb0 midi.c */
undefined4 midi_seek(int param_1); /* 0x08104fe0 midi.c */
undefined4 poll_mouse(void); /* 0x081063a0 mouse.c */
undefined4 mouse_needs_poll(void); /* 0x081063d0 mouse.c */
uint install_mouse(void); /* 0x081064b0 mouse.c */
undefined4 save_pcx(byte * param_1, uint * param_2, undefined1 * param_3); /* 0x081070a0 pcx.c */
undefined4 detect_digi_driver(int param_1); /* 0x08107ee0 sound.c */
undefined4 detect_midi_driver(int param_1); /* 0x08107fa0 sound.c */
undefined4 reserve_voices(undefined4 param_1, undefined4 param_2); /* 0x08108060 sound.c */
int install_sound(int digi, int midi, char *cfg_path);  /* corrected from the library header */ /* 0x08108080 sound.c */
undefined4 remove_sound(void); /* 0x08108ef0 sound.c */
undefined4 set_volume(int param_1, int param_2); /* 0x081090b0 sound.c */
void lock_sample(void *spl);  /* corrected from the library header */ /* 0x08109160 sound.c */
int * create_sample(int param_1, int param_2, int param_3, size_t param_4); /* 0x08109a20 sound.c */
undefined4 destroy_sample(void * param_1); /* 0x08109ae0 sound.c */
int play_sample(int param_1, undefined4 param_2, int param_3, int param_4, int param_5); /* 0x08109b20 sound.c */
int allocate_voice(int param_1); /* 0x08109da0 sound.c */
undefined4 deallocate_voice(int param_1); /* 0x0810a530 sound.c */
undefined4 reallocate_voice(int param_1, int param_2); /* 0x0810a5a0 sound.c */
undefined4 voice_start(int param_1); /* 0x0810a6b0 sound.c */
undefined4 voice_stop(int param_1); /* 0x0810a6f0 sound.c */
undefined4 voice_check(int param_1); /* 0x0810a740 sound.c */
undefined4 voice_get_position(int param_1); /* 0x0810a790 sound.c */
undefined4 voice_set_position(int param_1, undefined4 param_2); /* 0x0810a7c0 sound.c */
undefined4 voice_set_playmode(int param_1, uint param_2); /* 0x0810a7f0 sound.c */
int voice_get_volume(int param_1); /* 0x0810a860 sound.c */
undefined4 voice_set_volume(int param_1, int param_2); /* 0x0810a8d0 sound.c */
undefined4 voice_get_frequency(int param_1); /* 0x0810aa30 sound.c */
undefined4 voice_set_frequency(int param_1, int param_2); /* 0x0810aa60 sound.c */
int voice_get_pan(int param_1); /* 0x0810ab80 sound.c */
undefined4 voice_set_pan(int param_1, int param_2); /* 0x0810abd0 sound.c */
undefined4 rest(undefined4 param_1); /* 0x0810d140 timer.c */
undefined4 install_int_ex(int param_1, int param_2); /* 0x0810d460 timer.c */
undefined4 remove_int(int param_1); /* 0x0810d4d0 timer.c */
undefined4 install_timer(void); /* 0x0810d5a0 timer.c */
undefined4 remove_timer(void); /* 0x0810d810 timer.c */
undefined4 stretch_blit(int param_1, int param_2, int param_3, undefined4 param_4, int param_5, int param_6, uint param_7, int param_8, int param_9, int param_10); /* 0x0811e420 istretch.c */
int __pthread_yield(void); /* 0x0814cf80 lvga.c */
int __pthread_create_2_1(pthread_t * __newthread, pthread_attr_t * __attr, __start_routine * __start_routine, void * __arg); /* 0x0814cf90 lvga.c */
undefined4 cd_init(char * param_1); /* 0x081bbac0 linux.c */
undefined cd_exit(void); /* 0x081bbb30 linux.c */
undefined4 cd_play(uint param_1); /* 0x081bbb60 linux.c */
undefined4 cd_play_now(uint param_1); /* 0x081bbc10 linux.c */
undefined4 cd_play_loop(uint param_1); /* 0x081bbcc0 linux.c */
bool cd_is_playing(void); /* 0x081bbef0 linux.c */
undefined1 cd_current_track(void); /* 0x081bbf10 linux.c */
undefined cd_pause(void); /* 0x081bbf40 linux.c */
undefined cd_resume(void); /* 0x081bbf60 linux.c */
bool cd_is_paused(void); /* 0x081bbf90 linux.c */
undefined cd_stop(void); /* 0x081bbfb0 linux.c */
undefined4 cd_get_tracks(uint * param_1, uint * param_2); /* 0x081bbfd0 linux.c */
uint cd_is_audio(undefined1 param_1); /* 0x081bc040 linux.c */
undefined cd_get_volume(uint * param_1, uint * param_2); /* 0x081bc0b0 linux.c */
void cd_set_volume(int l, int r); /* 0x081bc100 linux.c */
undefined cd_eject(void); /* 0x081bc170 linux.c */
undefined cd_close(void); /* 0x081bc190 linux.c */
uint crc32(uint param_1, byte * param_2, uint param_3); /* 0x081bc1b0 crc32.c */
undefined8 inflateInit2_(int param_1, int param_2, char * param_3, int param_4); /* 0x081bc2a0 inflate.c */
uint inflate(int * param_1, int param_2); /* 0x081bc450 inflate.c */
undefined4 inflateEnd(int param_1); /* 0x081bc920 inflate.c */
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
