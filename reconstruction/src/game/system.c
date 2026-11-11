/*
 * system.c -- motif, configuration and options
 * Loading and unloading the motif (system.def), reading mugen.cfg, the
 * in-game options and the player key configurations.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/system.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* GameLoadSystem @ 0x080d2b60, 3650 bytes
 *
 * Loads the motif (system.def). "[Files]" gives spr, snd, fight, select,
 * logo.storyboard, intro.storyboard and font1..n. "[Music]" gives title.bgm,
 * select.bgm, vs.bgm. The "[Title Info]" menu (menu.pos, menu.item.font,
 * menu.itemname.<mode> for arcade, versus, teamarcade, teamversus, teamcoop,
 * survival, survivalcoop, training, watch, options, exit...) and the
 * "[Select Info]", "[VS Screen]", "[Option Info]", demo mode, continue
 * screen, game over, win screen, default ending, end credits and survival
 * results settings are read too.
 *
 * It then loads the system sprites and sounds, the screen backgrounds
 * (TitleBG, SelectBG, VersusBG, OptionBG), the fight screen (fight.def) and
 * the character select data. Missing groups or files stop the engine ("Can't
 * access [Files] group", "Can't open %s%s", "Error loading TitleBG", ...).
 *
 * Text keys read: [Files], "spr", "snd", "fight", "select",
 *                 "logo.storyboard", "intro.storyboard", [Music], [title
 *                 info], "fadein.time", "fadeout.time", "menu.pos",
 *                 "menu.item.font", "menu.item.active.font",
 *                 "menu.item.spacing", "menu.window.margins.y",
 *                 "menu.window.visibleitems", "menu.boxcursor.visible",
 *                 "menu.boxcursor.coords", "cursor.move.snd",
 *                 "cursor.done.snd", "cancel.snd", [option info], [select
 *                 info], ...
 * Globals read: errmsg, files_select, files_logo_storyboard,
 *               files_intro_storyboard, title_info_fadein_time,
 *               demo_mode_select_enabled, demo_mode_vsscreen_enabled,
 *               demo_mode_fight_endtime, demo_mode_fight_playbgm,
 *               demo_mode_fight_bars_display, demo_mode_intro_waitcycles,
 *               debuginfo, continue_screen_storyboard,
 *               continue_screen_enabled, game_over_screen_storyboard,
 *               game_over_screen_enabled
 * Globals written: sys_sounds, demo_mode_title_waittime
 * Calls: joindirfile, TPReadFile, TPGroupSeek, TPGetValue, FindFileDir,
 *        SpriteReadFile, SndReadFile, TPScanf, FontReadFile,
 *        TPGroupScanFirst, strimatch, TPGroupScanNext, AnimRCReadFileTP,
 *        BGMParse, TPGetValueInt, GetQuotedString, ParseSndGI,
 *        CharselReadConfig, SysExplodParse, BGArrayReadTP, TPFree,
 *        GameLoadFightData
 * C library: strcpy, sprintf, strcat
 * Called by: GameInit
 * Messages:
 *   "Can\'t open %s%s"
 *   "Can\'t access [Files] group"
 *   "Missing spr specification in [Files]"
 *   "Can\'t load %s"
 *   "Can\'t read font %s"
 *   "begin action "
 *
 * Elecbyte file: src/mugen/system.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x2180 bytes,
 *       20 variables), because their address is taken.
 */
uint32_t GameLoadSystem(void)

{
  uint32_t *pu1;
  uint32_t *pu2;
  bool b3;
  FILE *tp;
  int i5;
  FILE *value;
  int *sprites;
  int i8;
  uint32_t *pu9;
  uint32_t stale_var;
  int *pi10;
  FILE *stale_ECX;
  FILE *stale_ECX_00;
  FILE *stale_EDX;
  FILE *stale_EDX_00;
  char *value2;
  uint32_t *pu12;
  uint32_t *pu13;
  FILE *filename;
  unsigned char frame[0x2180] __attribute__((aligned(16)));
#define stk_2180 (*(uint32_t **)(frame + 0x0))
#define stk_217c (*(char *(*)[4])(frame + 0x4))
#define stk_216c (*(char **)(frame + 0x14))
#define stk_2168 (*(char **)(frame + 0x18))
#define stk_2164 (*(char **)(frame + 0x1c))
#define stk_2160 (*(char **)(frame + 0x20))
#define stk_215c (*(char **)(frame + 0x24))
#define stk_2158 (*(char **)(frame + 0x28))
#define stk_2154 (*(uint8_t **)(frame + 0x2c))
#define stk_214c (*(char *(*)[4])(frame + 0x34))
#define stk_213c (*(char **)(frame + 0x44))
#define stk_2138 (*(char **)(frame + 0x48))
#define stk_2134 (*(char **)(frame + 0x4c))
#define stk_2130 (*(char **)(frame + 0x50))
#define stk_212c (*(char **)(frame + 0x54))
#define stk_2128 (*(char **)(frame + 0x58))
#define stk_2124 (*(uint8_t **)(frame + 0x5c))
#define path (*(char (*)[4096])(frame + 0x64))
#define filename2 (*(FILE (*)[27])(frame + 0x1064))
#define keyname (*(int (*)[67])(frame + 0x2064))
  
  filename = filename2;
  joindirfile((char *)filename,(char *)((int)g + 0x15aff),(char *)(g + 0x52c0));
  tp = TPReadFile((char *)filename);
  if (tp == (FILE *)0x0) {
    pi10 = g + G_ERRMSG;
    value2 = "Can\'t open %s%s";
    value = (FILE *)((int)g + 0x15aff);
    filename = (FILE *)(g + 0x52c0);
  }
  else {
    i5 = TPGroupSeek((int)tp,"Files");
    if (i5 == -1) {
      pi10 = g + G_ERRMSG;
      value2 = "Can\'t access [Files] group";
      value = stale_EDX;
      filename = stale_EDX;
    }
    else {
      value = (FILE *)TPGetValue((int)tp,"spr");
      if (value == (FILE *)0x0) {
        pi10 = g + G_ERRMSG;
        value2 = "Missing spr specification in [Files]";
        value = filename;
      }
      else {
        i5 = FindFileDir((char *)value,(char *)filename,(char *)0x0);
        if (i5 == 0) {
          return 0;
        }
        sprites = SpriteReadFile((char *)filename);
        pi10 = g;
        g[0x5ac0] = (int)sprites;
        if (sprites == (int *)0x0) {
          pi10 = pi10 + 0x81d2;
          value2 = "Can\'t load %s";
          filename = tp;
        }
        else {
          strcpy((char *)(pi10 + 0x5ac1),(char *)filename);
          value = (FILE *)TPGetValue((int)tp,"snd");
          if (value != (FILE *)0x0) {
            i5 = FindFileDir((char *)value,(char *)filename,(char *)0x0);
            if (i5 == 0) {
              return 0;
            }
            sprites = SndReadFile((char *)filename);
            pi10 = g;
            g[G_SYS_SOUNDS] = (int)sprites;
            if (sprites == (int *)0x0) {
              pi10 = pi10 + 0x81d2;
              value2 = "Can\'t load %s";
              goto L_080d3985;
            }
            strcpy((char *)(pi10 + 0x5ec2),(char *)filename);
          }
          value2 = TPGetValue((int)tp,"fight");
          if (value2 == (char *)0x0) {
            return 0;
          }
          strcpy(path,value2);
          i5 = TPScanf((int)tp,"select","%s",g + G_FILES_SELECT);
          if (i5 < 1) {
            return 0;
          }
          TPScanf((int)tp,"logo.storyboard","%s",g + G_FILES_LOGO_STORYBOARD);
          TPScanf((int)tp,"intro.storyboard","%s",g + G_FILES_INTRO_STORYBOARD);
          stk_2180 = (uint32_t *)0x0;
          do {
            g[(int)stk_2180 + 0x62c3] = g[0x413a];
            sprintf((char *)keyname,"font%i",stk_2180,filename2);
            value = (FILE *)TPGetValue((int)tp,(char *)keyname);
            if (value != (FILE *)0x0) {
              i5 = FindFileDir((char *)value,(char *)filename2,(char *)0x0);
              if (i5 == 0) {
                return 0;
              }
              i5 = FontReadFile((char *)filename2);
              pi10 = g;
              g[(int)stk_2180 + 0x62c3] = i5;
              if (i5 == 0) {
                pi10 = pi10 + 0x81d2;
                value2 = "Can\'t read font %s";
                filename = (FILE *)0x0;
                goto L_080d3985;
              }
            }
            stk_2180 = (uint32_t *)((int)stk_2180 + 1);
          } while ((int)stk_2180 < 10);
          i5 = TPGroupScanFirst((int)tp);
          do {
            i8 = strimatch((char *)(i5 + 1),"begin action ");
            if (i8 != 0) break;
            i5 = TPGroupScanNext((int)tp);
          } while (i5 != 0);
          if (i5 != 0) {
            sprites = AnimRCReadFileTP((int)tp);
            pi10 = g;
            g[0x62c2] = (int)sprites;
            if (sprites == (int *)0x0) {
              pi10 = pi10 + 0x81d2;
              value2 = "Error loading anim";
              value = tp;
              filename = tp;
              goto L_080d3985;
            }
          }
          i5 = TPGroupSeek((int)tp,"Music");
          if (i5 != -1) {
            BGMParse((int)tp,(uint8_t *)(g + 0x62d1),"title.bgm");
            BGMParse((int)tp,(uint8_t *)(g + 0x6ad3),"select.bgm");
            BGMParse((int)tp,(uint8_t *)(g + 0x66d2),"vs.bgm");
          }
          i5 = TPGroupSeek((int)tp,"title info");
          pi10 = g;
          pu9 = (uint32_t *)(i5 + 1);
          if (pu9 == (uint32_t *)0x0) {
            pi10 = g + G_ERRMSG;
            value2 = "Can\'t access [Title Info] group";
            value = stale_EDX_00;
            filename = stale_EDX_00;
          }
          else {
            stk_214c[0] = "arcade";
            pu1 = (uint32_t *)(g + G_TITLE_INFO_FADEIN_TIME);
            g[0x100d] = 0x9f;
            pi10[0x100e] = 0x9e;
            pi10[0x1016] = 0xd;
            stk_214c[1] = "versus";
            stk_214c[2] = "teamarcade";
            stk_214c[3] = "teamversus";
            stk_213c = "teamcoop";
            stk_2138 = "survival";
            stk_2134 = "survivalcoop";
            stk_2130 = "training";
            stk_212c = "watch";
            stk_2128 = "options";
            stk_2124 = &str_exit_d0db;
            stk_217c[0] = "Arcade";
            stk_217c[1] = "VS Mode";
            stk_217c[2] = "Team Arcade";
            stk_217c[3] = "Team Versus";
            stk_216c = "Team Co-op";
            stk_2168 = "Survival";
            stk_2164 = "Survival Co-op";
            stk_2160 = "Training";
            pi10[0x106f] = 0xc;
            pi10[0x1070] = 8;
            pi10[0x1071] = 5;
            pi10[0x1072] = 1;
            pi10[0x1073] = -0x20;
            pi10[0x1074] = -10;
            pi10[0x1075] = 0x20;
            pi10[0x1076] = 2;
            pi10[0x1012] = -1;
            pi10[0x100f] = -1;
            stk_215c = "Watch";
            stk_2158 = "Options";
            stk_2154 = &str_exit;
            TPGetValueInt((int)tp,"fadein.time",pu1);
            pu12 = (uint32_t *)(pi10 + 0x1006);
            value2 = "fadeout.time";
            TPGetValueInt((int)tp,"fadeout.time",pu12);
            pu2 = (uint32_t *)pi10[0x1005];
            if ((int)pu2 < 1) {
              pi10[0x1005] = 1;
            }
            if (pi10[0x1006] < 1) {
              pi10[0x1006] = 1;
            }
            TPScanf((int)tp,"menu.pos","%i,%i",pi10 + 0x100d,pi10 + 0x100e,value2,pu12
                    ,pu9);
            TPScanf((int)tp,"menu.item.font","%i,%i,%i",pi10 + 0x100f,pi10 + 0x1011,
                    pi10 + 0x1010);
            sprites = pi10 + 0x1013;
            TPScanf((int)tp,"menu.item.active.font","%i,%i,%i",pi10 + 0x1012,pi10 + 0x1014
                    ,sprites);
            TPScanf((int)tp,"menu.item.spacing","%i,%i",pi10 + 0x1015,pi10 + 0x1016);
            stk_2180 = (uint32_t *)0x0;
            do {
              pu13 = (uint32_t *)stk_214c[(int)stk_2180];
              if ((char)*pu13 != '\0') {
                pu9 = stk_2180;
                sprintf((char *)keyname,"menu.itemname.%s",pu13,stk_2180);
                sprites = keyname;
                value2 = TPGetValue((int)tp,(char *)keyname);
                if (value2 == (char *)0x0) {
                  sprites = (int *)stk_217c[(int)stk_2180];
                  pu12 = pu2;
                  pu9 = pu2;
                  strcpy((char *)(pu1 + (int)stk_2180 * 8 + 0x12),(char *)sprites);
                }
                else {
                  GetQuotedString((int)tp,(char *)keyname,
                                  (char *)(pu1 + (int)stk_2180 * 8 + 0x12),0x1f,(char *)0x0);
                  pu12 = pu13;
                }
              }
              stk_2180 = (uint32_t *)((int)stk_2180 + 1);
            } while ((int)stk_2180 < 0xb);
            TPScanf((int)tp,"menu.window.margins.y","%i,%i",pi10 + 0x106f,pi10 + 0x1070,
                    sprites,pu12,pu9);
            TPGetValueInt((int)tp,"menu.window.visibleitems",(uint32_t *)(pi10 + 0x1071));
            TPGetValueInt((int)tp,"menu.boxcursor.visible",(uint32_t *)(pi10 + 0x1072));
            TPScanf((int)tp,"menu.boxcursor.coords","%i,%i,%i,%i",pi10 + 0x1073,
                    pi10 + 0x1074,pi10 + 0x1075,pi10 + 0x1076);
            ParseSndGI((int)tp,"cursor.move.snd",pi10 + 0x1007,(int)(pi10 + 0x1008));
            ParseSndGI((int)tp,"cursor.done.snd",pi10 + 0x1009,(int)(pi10 + 0x100a));
            ParseSndGI((int)tp,"cancel.snd",pi10 + 0x100b,(int)(pi10 + 0x100c));
            i5 = TPGroupSeek((int)tp,"option info");
            pi10 = g;
            if (i5 == -1) {
              value2 = "Can\'t access [Option Info] group";
              pi10 = g + G_ERRMSG;
              value = (FILE *)0x0;
              filename = (FILE *)0x0;
            }
            else {
              ParseSndGI((int)tp,"cursor.move.snd",g + 0x1079,(int)(g + 0x107a));
              ParseSndGI((int)tp,"cursor.done.snd",pi10 + 0x107b,(int)(pi10 + 0x107c));
              value = (FILE *)(pi10 + 0x107d);
              ParseSndGI((int)tp,"cancel.snd",(uint32_t *)value,(int)(pi10 + 0x107e));
              i5 = TPGroupSeek((int)tp,"select info");
              if (i5 == -1) {
                pi10 = g + G_ERRMSG;
                value2 = "Can\'t access [Select Info] group";
                filename = value;
              }
              else {
                b3 = CharselReadConfig((int)tp);
                if (ZEXT8(b3) == 0) {
                  return 0;
                }
                i5 = TPGroupSeek((int)tp,"vs screen");
                pi10 = g;
                if (i5 == -1) {
                  pi10 = g + G_ERRMSG;
                  value2 = "Can\'t access [VS Screen] group\n";
                  value = tp;
                  filename = tp;
                }
                else {
                  g[0x3395] = 0x96;
                  pu9 = (uint32_t *)(pi10 + 0x3395);
                  TPGetValueInt((int)tp,"time",pu9);
                  TPGetValueInt((int)tp,"fadein.time",(uint32_t *)(pi10 + 0x3396));
                  TPGetValueInt((int)tp,"fadeout.time",(uint32_t *)(pi10 + 0x3397));
                  stk_2180 = (uint32_t *)0x0;
                  do {
                    pu9[(int)stk_2180 * 10 + 5] = 0xffffffff;
                    pu9[(int)stk_2180 * 10 + 10] = (uint32_t)(stk_2180 == (uint32_t *)0x0) * 2 - 1;
                    pu9[(int)stk_2180 * 10 + 0xc] = 0x3f800000;
                    pu9[(int)stk_2180 * 10 + 0xb] = 0x3f800000;
                    sprintf((char *)keyname,"p%i.pos",(int)stk_2180 + 1,0x3f800000);
                    TPScanf((int)tp,(char *)keyname,"%i,%i",pu9 + (int)stk_2180 * 10 + 3,
                            pu9 + (int)stk_2180 * 10 + 4);
                    sprintf((char *)keyname,"p%i.facing",(int)stk_2180 + 1);
                    TPScanf((int)tp,(char *)keyname,"%i",
                            pi10 + (int)stk_2180 * 10 + 0x339f);
                    sprintf((char *)keyname,"p%i.scale",(int)stk_2180 + 1);
                    TPScanf((int)tp,(char *)keyname,"%f,%f",
                            pu9 + (int)stk_2180 * 10 + 0xb,pu9 + (int)stk_2180 * 10 + 0xc)
                    ;
                    sprintf((char *)keyname,"p%i.name.pos",(int)stk_2180 + 1);
                    TPScanf((int)tp,(char *)keyname,"%i,%i",pu9 + (int)stk_2180 * 10 + 8,
                            pu9 + (int)stk_2180 * 10 + 9);
                    sprintf((char *)keyname,"p%i.name.font",(int)stk_2180 + 1);
                    TPScanf((int)tp,(char *)keyname,"%i,%i,%i",
                            pu9 + (int)stk_2180 * 10 + 5,pu9 + (int)stk_2180 * 10 + 6,
                            pu9 + (int)stk_2180 * 10 + 7);
                    stk_2180 = (uint32_t *)((int)stk_2180 + 1);
                  } while ((int)stk_2180 < 2);
                  g[G_DEMO_MODE_TITLE_WAITTIME] = -1;
                  i5 = TPGroupSeek((int)tp,"demo mode");
                  if (i5 != -1) {
                    stk_2180 = (uint32_t *)0x0;
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)&stk_2180);
                    if (stk_2180 != (uint32_t *)0x0) {
                      TPGetValueInt((int)tp,"title.waittime",(uint32_t *)(g + G_DEMO_MODE_TITLE_WAITTIME));
                    }
                    TPGetValueInt((int)tp,"select.enabled",(uint32_t *)(g + G_DEMO_MODE_SELECT_ENABLED));
                    TPGetValueInt((int)tp,"vsscreen.enabled",(uint32_t *)(g + G_DEMO_MODE_VSSCREEN_ENABLED));
                    TPGetValueInt((int)tp,"fight.endtime",(uint32_t *)(g + G_DEMO_MODE_FIGHT_ENDTIME));
                    TPGetValueInt((int)tp,"fight.playbgm",(uint32_t *)(g + G_DEMO_MODE_FIGHT_PLAYBGM));
                    TPGetValueInt((int)tp,"fight.bars.display",(uint32_t *)(g + G_DEMO_MODE_FIGHT_BARS_DISPLAY));
                    TPGetValueInt((int)tp,"intro.waitcycles",(uint32_t *)(g + G_DEMO_MODE_INTRO_WAITCYCLES));
                    TPGetValueInt((int)tp,"debuginfo",(uint32_t *)(g + G_DEBUGINFO));
                  }
                  i5 = TPGroupSeek((int)tp,"continue screen");
                  if (i5 != -1) {
                    pi10 = g + G_CONTINUE_SCREEN_STORYBOARD;
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_CONTINUE_SCREEN_ENABLED));
                    TPScanf((int)tp,"storyboard","%s",pi10);
                  }
                  i5 = TPGroupSeek((int)tp,"game over screen");
                  if (i5 != -1) {
                    pi10 = g + G_GAME_OVER_SCREEN_STORYBOARD;
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_GAME_OVER_SCREEN_ENABLED));
                    TPScanf((int)tp,"storyboard","%s",pi10);
                  }
                  i5 = TPGroupSeek((int)tp,"win screen");
                  pi10 = g;
                  if (i5 != -1) {
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_WIN_SCREEN_ENABLED));
                    SysExplodParse((int)tp,pi10 + 0x2b55,"wintext");
                    TPGetValueInt((int)tp,"fadein.time",(uint32_t *)(pi10 + 0x2b71));
                    TPGetValueInt((int)tp,"pose.time",(uint32_t *)(pi10 + 0x2b70));
                    TPGetValueInt((int)tp,"fadeout.time",(uint32_t *)(pi10 + 0x2b72));
                  }
                  i5 = TPGroupSeek((int)tp,"survival results screen");
                  pi10 = g;
                  if (i5 != -1) {
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_SURVIVAL_RESULTS_SCREEN_ENABLED));
                    SysExplodParse((int)tp,pi10 + 0x2b74,"winstext");
                    TPGetValueInt((int)tp,"fadein.time",(uint32_t *)(pi10 + 0x2b90));
                    TPGetValueInt((int)tp,"show.time",(uint32_t *)(pi10 + 0x2b8f));
                    TPGetValueInt((int)tp,"fadeout.time",(uint32_t *)(pi10 + 0x2b91));
                    TPGetValueInt((int)tp,"roundstowin",(uint32_t *)(pi10 + 0x2b92));
                  }
                  i5 = TPGroupSeek((int)tp,"default ending");
                  if (i5 != -1) {
                    pi10 = g + G_DEFAULT_ENDING_STORYBOARD;
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_DEFAULT_ENDING_ENABLED));
                    TPScanf((int)tp,"storyboard","%s",pi10);
                  }
                  i5 = TPGroupSeek((int)tp,"end credits");
                  if (i5 != -1) {
                    pi10 = g + G_END_CREDITS_STORYBOARD;
                    TPGetValueInt((int)tp,"enabled",(uint32_t *)(g + G_END_CREDITS_ENABLED));
                    TPScanf((int)tp,"storyboard","%s",pi10);
                  }
                  value2 = BGArrayReadTP((char *)tp,(char *)((int)g + 0x15aff),"TitleBG",
                                          g[0x5ac0],g[0x62c2]);
                  pi10 = g;
                  g[0x62ce] = (int)value2;
                  if (value2 == (char *)0x0) {
                    pi10 = pi10 + 0x81d2;
                    value2 = "Error loading TitleBG";
                    value = stale_ECX;
                    filename = stale_ECX;
                  }
                  else {
                    value2 = BGArrayReadTP((char *)tp,(char *)((int)pi10 + 0x15aff),
                                            "VersusBG",pi10[0x5ac0],pi10[0x62c2]);
                    pi10 = g;
                    g[0x62cd] = (int)value2;
                    if (value2 == (char *)0x0) {
                      pi10 = pi10 + 0x81d2;
                      value2 = "Error loading VersusBG";
                      value = tp;
                      filename = tp;
                    }
                    else {
                      value = (FILE *)pi10[0x62c2];
                      value2 = BGArrayReadTP((char *)tp,(char *)((int)pi10 + 0x15aff),
                                              "SelectBG",pi10[0x5ac0],(int)value);
                      pi10 = g;
                      g[0x62cf] = (int)value2;
                      if (value2 == (char *)0x0) {
                        pi10 = pi10 + 0x81d2;
                        value2 = "Error loading SelectBG";
                        value = stale_ECX_00;
                        filename = stale_ECX_00;
                      }
                      else {
                        value2 = BGArrayReadTP((char *)tp,(char *)((int)pi10 + 0x15aff),
                                                "OptionBG",pi10[0x5ac0],pi10[0x62c2]);
                        pi10 = g;
                        g[0x62d0] = (int)value2;
                        if (value2 != (char *)0x0) {
                          TPFree(&tp->_flags);
                          i5 = FindFileDir(path,(char *)filename2,(char *)0x0);
                          if (i5 == 0) {
                            return 0;
                          }
                          i5 = GameLoadFightData(filename2);
                          if (i5 == 0) {
                            strcat((char *)(g + G_ERRMSG),"\nError loading fight data: ");
                            strcat((char *)(g + G_ERRMSG),path);
                            return 0;
                          }
                          return 1;
                        }
                        pi10 = pi10 + 0x81d2;
                        value2 = "Error loading OptionBG";
                        filename = value;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
L_080d3985:
  sprintf((char *)pi10,value2,value,filename);
  return 0;
}
#undef stk_2180
#undef stk_217c
#undef stk_216c
#undef stk_2168
#undef stk_2164
#undef stk_2160
#undef stk_215c
#undef stk_2158
#undef stk_2154
#undef stk_214c
#undef stk_213c
#undef stk_2138
#undef stk_2134
#undef stk_2130
#undef stk_212c
#undef stk_2128
#undef stk_2124
#undef path
#undef filename2
#undef keyname

/* GameUnloadSystem @ 0x080d39b0, 393 bytes
 *
 * Frees everything GameLoadSystem loaded: backgrounds, sprites, fonts,
 * animations and sounds.
 *
 * Globals read: sys_sounds
 * Calls: BGArrayFree, SpriteArrayFree, FontFree, AnimRCFree, SndArrayFree
 * C library: free
 * Called by: GameDeInit
 *
 * Elecbyte file: src/mugen/system.c
 */
void GameUnloadSystem(void)

{
  void *pv1;
  int *pi2;
  int *sprites;
  int i2;
  int i5;
  
  BGArrayFree(g[0x62d0]);
  sprites = g;
  g[0x62d0] = 0;
  BGArrayFree(sprites[0x62cf]);
  sprites = g;
  g[0x62cf] = 0;
  BGArrayFree(sprites[0x62cd]);
  sprites = g;
  g[0x62cd] = 0;
  BGArrayFree(sprites[0x62ce]);
  pi2 = g;
  sprites = g + 0x1b50;
  g[0x62ce] = 0;
  if (*sprites != 0) {
    i2 = 0;
    if (0 < pi2[0x18e5] * pi2[0x18e4]) {
      i5 = 0;
      do {
        sprites = *(int **)(pi2[0x1b50] + 0x2034 + i5);
        if (sprites != (int *)0x0) {
          SpriteArrayFree(sprites);
          pi2 = g;
        }
        i2 = i2 + 1;
        i5 = i5 + 0x2038;
      } while (i2 < pi2[0x18e5] * pi2[0x18e4]);
    }
    free((void *)pi2[0x1b50]);
  }
  i5 = 0x18b00;
  i2 = 9;
  sprites = g;
  do {
    pv1 = *(void **)(i5 + 0xc + (int)sprites);
    if (pv1 != (void *)sprites[0x413a]) {
      FontFree(pv1);
      sprites = g;
    }
    i5 = i5 + 4;
    i2 = i2 + -1;
  } while (-1 < i2);
  AnimRCFree((int *)sprites[0x62c2]);
  SndArrayFree((uint32_t *)g[G_SYS_SOUNDS]);
  sprites = g;
  *(uint8_t *)(g + 0x5ec2) = 0;
  sprites[0x5ec1] = 0;
  SpriteArrayFree((int *)g[0x5ac0]);
  sprites = g;
  g[0x5ac0] = 0;
  *(uint8_t *)(sprites + 0x5ac1) = 0;
  return;
}

/* GameReloadSystemSprSnd @ 0x080d3b40, 651 bytes
 *
 * Reloads the system sprites, sounds and screen backgrounds after a match
 * (they are unloaded during matches when misc.unloadsystem is set). Errors:
 * "Out of memory loading system file %s", "Error reloading TitleBG"...
 *
 * Globals written: sys_sounds
 * Calls: SpriteReadFile, ErrorExitM, SndReadFile, joindirfile, TPReadFile,
 *        BGArrayReadTP, TPFree
 * Called by: GamePlay, SysExplodCreateDraw_Sys, SysExplodCreate_Sys
 * Messages:
 *   "Out of memory loading system file %s"
 *   "Error reloading TitleBG"
 *   "Error reloading VersusBG"
 *   "Error reloading SelectBG"
 *   "Error reloading OptionBG"
 *
 * Elecbyte file: src/mugen/system.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1010 bytes,
 *       1 variables), because their address is taken.
 */
int GameReloadSystemSprSnd(void)

{
  int *sprites;
  int *sounds;
  int *tp;
  char *pc4;
  int i5;
  int *stale_ECX;
  int *stale_ECX_00;
  int *dirname;
  int *pi7;
  unsigned char frame[0x1010] __attribute__((aligned(16)));
#define filename (*(char (*)[4104])(frame + 0x4))
  
  dirname = g;
  if ((g[0x5ac0] == 0) && ((char)g[0x5ac1] != '\0')) {
    sprites = SpriteReadFile((char *)(g + 0x5ac1));
    dirname = g;
    g[0x5ac0] = (int)sprites;
    if (sprites == (int *)0x0) {
      ErrorExitM("Out of memory loading system file %s",dirname + 0x5ac1);
      dirname = g;
    }
  }
  sprites = (int *)dirname[0x5ec1];
  if ((sprites == (int *)0x0) && ((char)dirname[0x5ec2] != '\0')) {
    sounds = SndReadFile((char *)(dirname + 0x5ec2));
    dirname = g;
    g[G_SYS_SOUNDS] = (int)sounds;
    sprites = stale_ECX;
    if (sounds == (int *)0x0) {
      ErrorExitM("Out of memory loading system file %s",dirname + 0x5ec2,0,0);
      sprites = stale_ECX_00;
      dirname = g;
    }
  }
  if ((((dirname[0x62ce] == 0) || (sprites = (int *)dirname[0x62cd], sprites == (int *)0x0)) ||
      (i5 = dirname[0x62cf], i5 == 0)) || (dirname[0x62d0] == 0)) {
    sounds = dirname + 0x52c0;
    dirname = (int *)((int)dirname + 0x15aff);
    joindirfile(filename,(char *)dirname,(char *)sounds);
    tp = TPReadFile(filename);
    if (tp == (int *)0x0) {
      dirname = g + 0x52c0;
      sounds = tp;
      sprites = tp;
      ErrorExitM("Out of memory loading system file %s",dirname,0,0);
    }
    pi7 = g;
    if (g[0x62ce] == 0) {
      pc4 = BGArrayReadTP((char *)tp,(char *)((int)g + 0x15aff),"TitleBG",g[0x5ac0],g[0x62c2]
                            );
      pi7 = g;
      g[0x62ce] = (int)pc4;
      if (pc4 == (char *)0x0) {
        ErrorExitM("Error reloading TitleBG",dirname,sounds,sprites);
        pi7 = g;
      }
    }
    if (pi7[0x62cd] == 0) {
      pc4 = BGArrayReadTP((char *)tp,(char *)((int)pi7 + 0x15aff),"VersusBG",
                             pi7[0x5ac0],pi7[0x62c2]);
      pi7 = g;
      g[0x62cd] = (int)pc4;
      if (pc4 == (char *)0x0) {
        ErrorExitM("Error reloading VersusBG",dirname,sounds,sprites);
        pi7 = g;
      }
    }
    if (pi7[0x62cf] == 0) {
      pc4 = BGArrayReadTP((char *)tp,(char *)((int)pi7 + 0x15aff),"SelectBG",
                             pi7[0x5ac0],pi7[0x62c2]);
      pi7 = g;
      g[0x62cf] = (int)pc4;
      if (pc4 == (char *)0x0) {
        ErrorExitM("Error reloading SelectBG");
        pi7 = g;
      }
    }
    if (pi7[0x62d0] == 0) {
      pc4 = BGArrayReadTP((char *)tp,(char *)((int)pi7 + 0x15aff),"OptionBG",
                             pi7[0x5ac0],pi7[0x62c2]);
      g[0x62d0] = (int)pc4;
      if (pc4 == (char *)0x0) {
        ErrorExitM("Error reloading OptionBG");
      }
    }
    i5 = TPFree(tp);
  }
  return i5;
}
#undef filename

/* GameUnloadSystemSprSnd @ 0x080d3dd0, 151 bytes
 *
 * Frees the system sprites and screen backgrounds before a match (when
 * misc.unloadsystem is set) to save memory.
 *
 * Calls: BGArrayFree, SpriteArrayFree
 * Called by: GamePlay
 *
 * Elecbyte file: src/mugen/system.c
 */
void GameUnloadSystemSprSnd(void)

{
  int *pi1;
  
  BGArrayFree(g[0x62d0]);
  pi1 = g;
  g[0x62d0] = 0;
  BGArrayFree(pi1[0x62cf]);
  pi1 = g;
  g[0x62cf] = 0;
  BGArrayFree(pi1[0x62cd]);
  pi1 = g;
  g[0x62cd] = 0;
  BGArrayFree(pi1[0x62ce]);
  pi1 = g;
  g[0x62ce] = 0;
  SpriteArrayFree((int *)pi1[0x5ac0]);
  g[0x5ac0] = 0;
  return;
}

/* GameConfigRead @ 0x080d3e70, 4132 bytes
 *
 * Reads mugen.cfg (the file must exist: "Can't open %s. Make sure you have
 * extracted with directories"). Groups and keys:
 * - "[Rules]": gametype, default.attack.lifetopowermul,
 * default.gethit.lifetopowermul, super.targetdefencemul;
 * - "[Config]": gamespeed, drawshadows, afterimagemax, layeredspritemax,
 * explodmax, sysexplodmax, helpermax, playerprojectilemax, firstrun;
 * - "[Debug]": debug, allowdebugmode, allowdebugkeys, speedup, startstage;
 * - "[Video Linux]": width, height, depth, vretrace, fullscreen, doubleres,
 * stretch, blitmode;
 * - "[Sound]" / "[Sound Linux]": sound, wavdevice, mididevice, wavchannels,
 * masterwavvolume, wavvolume, midivolume, playmidi, playmod, modvoices,
 * modvolume, playmp3, mp3volume, playcda, cdadevice, cdavolume,
 * stereoeffects, panningwidth, reversestereo;
 * - "[Misc]": playercache, precache, bufferedread, unloadsystem,
 * pauseondefocus, pausebgmondefocus, playerpalmax, psxdelay;
 * - "[Arcade]": ai.randomcolor, arcade/team/survival AI settings;
 * - "[Input]": p1/p2.usekeyboard, p1/p2.joystick.type, forcefeedback; plus
 * "[P1 Keys]", "[P1 Joystick]", "[P2 Keys]", "[P2 Joystick]"
 * (PlayerLoadKeys).
 *
 * Missing groups are fatal ("Can't load rules.", "Can't load sound config:
 * [%s]"...); unknown devices give "Invalid wav device: %s" / "Invalid midi
 * device: %s".
 *
 * Parameters:
 *   filename     char *
 *
 * Text keys read: [Rules], "gametype", "default.attack.lifetopowermul",
 *                 "default.gethit.lifetopowermul",
 *                 "super.targetdefencemul", [config], "gamespeed",
 *                 "drawshadows", "afterimagemax", "layeredspritemax",
 *                 "explodmax", "sysexplodmax", "helpermax",
 *                 "playerprojectilemax", "playerpalmax", "firstrun",
 *                 [Debug], "debug", "allowdebugmode", "allowdebugkeys",
 *                 "speedup", "startstage", [video linux], "width", ...
 * Globals read: errmsg, rules_default_gethit_lifetopowermul,
 *               rules_super_targetdefencemul, config_drawshadows,
 *               debug_display, debug_allowdebugkeys, video_linux_width,
 *               video_linux_height, video_linux_vretrace,
 *               sound_linux_stereoeffects, sound_linux_panningwidth,
 *               sound_linux_masterwavvolume, sound_linux_midivolume,
 *               sound_linux_mp3volume, sound_linux_modvolume,
 *               sound_linux_cdavolume
 * Globals written: rules_default_attack_lifetopowermul,
 *                  config_afterimagemax, config_layeredspritemax,
 *                  config_explodmax, config_sysexplodmax,
 *                  config_helpermax, config_playerprojectilemax,
 *                  playerpalmax, debug_allowdebugmode,
 *                  video_linux_doubleres, video_linux_depth,
 *                  sound_linux_wavvolume, sound_linux_playmod,
 *                  sound_linux_wavchannels, sound_linux_pausebgmondefocus
 * Calls: TPReadFile, TPGroupSeek, TPGetValue, TPGetValueFloat,
 *        TPGetValueInt, SndSetReverseStereo, SndParseWavDevice,
 *        SndParseMidiDevice, SpriteSetBufReadMode, SndSetBufReadMode,
 *        TPScanf, PlayerLoadKeys, PlayerKeysRemoveZero, TPFree,
 *        TPReadFileForWrite, TPPrintf, TPWriteFile
 * C library: strncpy, sprintf, printf
 * Called by: GameInit
 * Messages:
 *   "Can\'t open %s. Make sure you have extracted with directories"
 *   "Can\'t load rules."
 *   "Can\'t get game type."
 *   "Can\'t access config."
 *   "video linux"
 *   "Can\'t load video config: [%s]"
 *
 * Elecbyte file: src/mugen/system.c
 * Note: 10 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: shared sprintf() call: 19 formats, arguments recovered for 6, others
 *       passed as 0
 * Note: Locals live in `frame`, laid out as on the original stack (0x140 bytes,
 *       7 variables), because their address is taken.
 */
uint32_t GameConfigRead(char *filename)

{
  void *fmt_args[1] = {0};
  char c1;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  uint32_t *tp;
  int i7;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t stale_var_02;
  uint32_t stale_var_03;
  uint32_t stale_var_04;
  uint32_t stale_var_05;
  uint32_t stale_var_06;
  int *pi8;
  uint32_t stale_var_07;
  uint32_t stale_var_08;
  void *tp2;
  int i10;
  int i11;
  int *pi12;
  char *value;
  void *pv14;
  unsigned char frame[0x140] __attribute__((aligned(16)));
#define stk_134 (*(int **)(frame + 0xc))
#define stk_130 (*(int **)(frame + 0x10))
#define stk_12c (*(uint32_t *)(frame + 0x14))
#define stk_128 (*(uint32_t *)(frame + 0x18))
#define stk_124 (*(int *)(frame + 0x1c))
#define stk_120 (*(int **)(frame + 0x20))
#define keyname (*(char (*)[268])(frame + 0x24))
  
  tp = TPReadFile(filename);
  if ((tp == (uint32_t *)0x0) && (tp = TPReadFile(filename), tp == (uint32_t *)0x0))
  {
    pi8 = g + G_ERRMSG;
    fmt_args[0] = (void *)(filename);
    value = "Can\'t open %s. Make sure you have extracted with directories";
    goto L_080d4c73;
  }
  i7 = TPGroupSeek((int)tp,"Rules");
  if (i7 == -1) {
    pi8 = g + G_ERRMSG;
    value = "Can\'t load rules.";
    goto L_080d4c73;
  }
  value = TPGetValue((int)tp,"gametype");
  if (value == (char *)0x0) {
    pi8 = g + G_ERRMSG;
    value = "Can\'t get game type.";
    goto L_080d4c73;
  }
  i7 = *(int *)(__ctype_tolower + *value * 4);
  if (i7 == 0x6d) {
    g[0x731d] = 1;
  }
  else {
    if (i7 != 0x76) {
      pi8 = g + G_ERRMSG;
      value = "Can\'t get game type.";
      goto L_080d4c73;
    }
    g[0x731d] = 0;
  }
  pi8 = g;
  g[G_RULES_DEFAULT_ATTACK_LIFETOPOWERMUL] = 0x40400000;
  pi8[0x731f] = 0x40000000;
  pi8[0x7320] = 0x3f800000;
  TPGetValueFloat((int)tp,"default.attack.lifetopowermul",(float *)(pi8 + 0x731e));
  TPGetValueFloat((int)tp,"default.gethit.lifetopowermul",(float *)(g + G_RULES_DEFAULT_GETHIT_LIFETOPOWERMUL));
  TPGetValueFloat((int)tp,"super.targetdefencemul",(float *)(g + G_RULES_SUPER_TARGETDEFENCEMUL));
  i7 = TPGroupSeek((int)tp,"config");
  pi8 = g;
  if (i7 == -1) {
    pi8 = g + G_ERRMSG;
    value = "Can\'t access config.";
    goto L_080d4c73;
  }
  g[0x756f] = 0x3c;
  pi8[0x7570] = 1;
  TPGetValueInt((int)tp,"gamespeed",(uint32_t *)(pi8 + 0x756f));
  TPGetValueInt((int)tp,"drawshadows",(uint32_t *)(g + G_CONFIG_DRAWSHADOWS));
  TPGetValueInt((int)tp,"afterimagemax",(uint32_t *)(g + G_CONFIG_AFTERIMAGEMAX));
  pi8 = g;
  if (g[G_CONFIG_AFTERIMAGEMAX] < 1) {
    g[G_CONFIG_AFTERIMAGEMAX] = 1;
  }
  TPGetValueInt((int)tp,"layeredspritemax",(uint32_t *)(pi8 + 0x7572));
  pi8 = g;
  if (g[G_CONFIG_LAYEREDSPRITEMAX] < 0x20) {
    g[G_CONFIG_LAYEREDSPRITEMAX] = 0x20;
  }
  TPGetValueInt((int)tp,"explodmax",(uint32_t *)(pi8 + 0x7573));
  pi8 = g;
  if (g[G_CONFIG_EXPLODMAX] < 8) {
    g[G_CONFIG_EXPLODMAX] = 8;
  }
  TPGetValueInt((int)tp,"sysexplodmax",(uint32_t *)(pi8 + 0x7574));
  pi8 = g;
  if (g[G_CONFIG_SYSEXPLODMAX] < 8) {
    g[G_CONFIG_SYSEXPLODMAX] = 8;
  }
  TPGetValueInt((int)tp,"helpermax",(uint32_t *)(pi8 + 0x7575));
  pi8 = g;
  if (g[G_CONFIG_HELPERMAX] < 4) {
    g[G_CONFIG_HELPERMAX] = 4;
  }
  if (0x38 < pi8[0x7575]) {
    pi8[0x7575] = 0x38;
    pi8 = g;
  }
  TPGetValueInt((int)tp,"playerprojectilemax",(uint32_t *)(pi8 + 0x7576));
  pi8 = g;
  if (g[G_CONFIG_PLAYERPROJECTILEMAX] < 5) {
    g[G_CONFIG_PLAYERPROJECTILEMAX] = 5;
  }
  TPGetValueInt((int)tp,"playerpalmax",(uint32_t *)(pi8 + 0x7577));
  pi8 = g;
  if (g[G_PLAYERPALMAX] < 0xc) {
    g[G_PLAYERPALMAX] = 0xc;
  }
  TPGetValueInt((int)tp,"firstrun",(uint32_t *)(pi8 + 0x7578));
  i7 = TPGroupSeek((int)tp,"Debug");
  if (i7 != -1) {
    TPGetValueInt((int)tp,"debug",(uint32_t *)(g + G_DEBUG_DISPLAY));
    TPGetValueInt((int)tp,"allowdebugmode",(uint32_t *)(g + G_DEBUG_ALLOWDEBUGMODE));
    TPGetValueInt((int)tp,"allowdebugkeys",(uint32_t *)(g + G_DEBUG_ALLOWDEBUGKEYS));
    pi8 = g;
    if (g[G_DEBUG_DISPLAY] != 0) {
      g[G_DEBUG_ALLOWDEBUGMODE] = 1;
      TPGetValueInt((int)tp,"speedup",(uint32_t *)(pi8 + 0x82d2));
    }
    value = TPGetValue((int)tp,"startstage");
    if (value != (char *)0x0) {
      strncpy((char *)(g + 0x7dc4),value,0xfff);
    }
  }
  i7 = TPGroupSeek((int)tp,"video linux");
  if (i7 == -1) {
    pi8 = g + G_ERRMSG;
    fmt_args[0] = (void *)("video linux");
    value = "Can\'t load video config: [%s]";
    goto L_080d4c73;
  }
  b2 = TPGetValueInt((int)tp,"width",(uint32_t *)(g + G_VIDEO_LINUX_WIDTH));
  b3 = TPGetValueInt((int)tp,"height",(uint32_t *)(g + G_VIDEO_LINUX_HEIGHT));
  b4 = TPGetValueInt((int)tp,"depth",(uint32_t *)(g + G_VIDEO_LINUX_DEPTH));
  b5 = TPGetValueInt((int)tp,"vretrace",(uint32_t *)(g + G_VIDEO_LINUX_VRETRACE));
  pi8 = g;
  if ((ZEXT8(b2) & ZEXT8(b3) &
       ZEXT8(b4) & ZEXT8(b5)) != 1) {
    pi8 = g + G_ERRMSG;
    value = "Can\'t read video config.";
    goto L_080d4c73;
  }
  g[0x7558] = 0;
  TPGetValueInt((int)tp,"stretch",(uint32_t *)(pi8 + 0x7558));
  pi8 = g;
  g[G_VIDEO_LINUX_DOUBLERES] = 0;
  TPGetValueInt((int)tp,"doubleres",(uint32_t *)(pi8 + 0x7559));
  pi8 = g;
  if (g[G_VIDEO_LINUX_DOUBLERES] < 0) {
    g[G_VIDEO_LINUX_DOUBLERES] = 0;
  }
  if (4 < pi8[0x7559]) {
    pi8[0x7559] = 4;
    pi8 = g;
  }
  pi8[0x7556] = 1;
  value = TPGetValue((int)tp,"fullscreen");
  pi8 = g;
  if (value != (char *)0x0) {
    c1 = *value;
    i7 = *(int *)(__ctype_tolower + c1 * 4);
    if (i7 == 0x30) {
      g[0x7556] = 2;
    }
    else if (i7 == 0x31) {
      g[0x7556] = 1;
    }
    else {
      g[0x7556] = 0;
      sprintf((char *)(pi8 + 0x81d2),"Unrecognised option: %s.  Trying to autodetect...",value,
              (int)c1);
    }
  }
  if (*(generic_fn **)(system_driver + 0x6c) == (generic_fn *)0x0) {
    stk_130 = (int *)0x0;
  }
  else {
    stk_130 = (int *)(**(generic_fn **)(system_driver + 0x6c))();
  }
  pi8 = g;
  if (((stk_130 != (int *)0x0) && (stk_130 != (int *)g[G_VIDEO_LINUX_DEPTH])) && (g[0x7556] == 2)) {
    g[G_VIDEO_LINUX_DEPTH] = (int)stk_130;
  }
  pi8[0x7557] = 0;
  value = TPGetValue((int)tp,"blitmode");
  if (value != (char *)0x0) {
    i7 = *(int *)(__ctype_tolower + *value * 4);
    if (i7 == 0x70) {
      g[0x7557] = 1;
    }
    else if (i7 < 0x71) {
      if (i7 != 0x6e) {
L_080d44f2:
        pi8 = g + G_ERRMSG;
        fmt_args[0] = (void *)(value);
        value = "Unrecognised BlitMode: %s";
        goto L_080d4c73;
      }
      g[0x7557] = 0;
    }
    else {
      if (i7 != 0x74) goto L_080d44f2;
      g[0x7557] = 2;
    }
  }
  i7 = TPGroupSeek((int)tp,"sound linux");
  pi8 = g;
  if (i7 == -1) {
    pi8 = g + G_ERRMSG;
    fmt_args[0] = (void *)("sound linux");
    value = "Can\'t load sound config: [%s]";
  }
  else {
    g[G_SOUND_LINUX_WAVVOLUME] = 0xaf;
    pi8[0x6ef5] = 200;
    pi8[0x6ef9] = 0xaf;
    pi8[0x6ef8] = 0xaf;
    pi8[0x6ef6] = -1;
    pi8[0x6ef3] = 1;
    pi8[0x756c] = 1;
    pi8[0x756d] = 0xa0;
    TPGetValueInt((int)tp,"sound",(uint32_t *)(pi8 + 0x6ef3));
    TPGetValueInt((int)tp,"stereoeffects",(uint32_t *)(g + G_SOUND_LINUX_STEREOEFFECTS));
    TPGetValueInt((int)tp,"panningwidth",(uint32_t *)(g + G_SOUND_LINUX_PANNINGWIDTH));
    b2 = TPGetValueInt((int)tp,"reversestereo",(uint32_t *)&stk_130);
    if (ZEXT8(b2) != 0) {
      SndSetReverseStereo((int)stk_130);
    }
    TPGetValueInt((int)tp,"pausebgmondefocus",(uint32_t *)(g + G_SOUND_LINUX_PAUSEBGMONDEFOCUS));
    TPGetValueInt((int)tp,"masterwavvolume",(uint32_t *)(g + G_SOUND_LINUX_MASTERWAVVOLUME));
    TPGetValueInt((int)tp,"wavvolume",(uint32_t *)(g + G_SOUND_LINUX_WAVVOLUME));
    TPGetValueInt((int)tp,"midivolume",(uint32_t *)(g + G_SOUND_LINUX_MIDIVOLUME));
    TPGetValueInt((int)tp,"mp3volume",(uint32_t *)(g + G_SOUND_LINUX_MP3VOLUME));
    TPGetValueInt((int)tp,"modvolume",(uint32_t *)(g + G_SOUND_LINUX_MODVOLUME));
    TPGetValueInt((int)tp,"cdavolume",(uint32_t *)(g + G_SOUND_LINUX_CDAVOLUME));
    pi8 = g;
    g[G_SOUND_LINUX_PLAYMOD] = 1;
    pi8[0x7561] = 1;
    pi8[0x7560] = 1;
    pi8[0x7563] = 1;
    TPGetValueInt((int)tp,"playcda",(uint32_t *)(pi8 + 0x7563));
    TPGetValueInt((int)tp,"playmp3",(uint32_t *)(g + G_SOUND_LINUX_PLAYMP3));
    TPGetValueInt((int)tp,"playmidi",(uint32_t *)(g + G_SOUND_LINUX_PLAYMIDI));
    TPGetValueInt((int)tp,"playmod",(uint32_t *)(g + G_SOUND_LINUX_PLAYMOD));
    value = TPGetValue((int)tp,"cdadevice");
    if (value != (char *)0x0) {
      strncpy((char *)(g + 0x7564),value,0x1f);
    }
    g[0x755b] = -1;
    value = TPGetValue((int)tp,"wavdevice");
    if (value != (char *)0x0) {
      i7 = SndParseWavDevice(value);
      pi8 = g;
      g[0x755b] = i7;
      if (i7 == -2) {
        pi8 = pi8 + 0x81d2;
        fmt_args[0] = (void *)(value);
        value = "Invalid wav device: %s";
        goto L_080d4c73;
      }
    }
    pi8 = g;
    g[G_SOUND_LINUX_WAVCHANNELS] = 8;
    TPGetValueInt((int)tp,"wavchannels",(uint32_t *)(pi8 + 0x755d));
    TPGetValueInt((int)tp,"modvoices",(uint32_t *)(g + G_SOUND_LINUX_MODVOICES));
    g[0x755c] = -1;
    value = TPGetValue((int)tp,"mididevice");
    if (value != (char *)0x0) {
      i7 = SndParseMidiDevice(value);
      pi8 = g;
      g[0x755c] = i7;
      if (i7 == -2) {
        pi8 = pi8 + 0x81d2;
        fmt_args[0] = (void *)(value);
        value = "Invalid midi device: %s";
        goto L_080d4c73;
      }
    }
    i7 = TPGroupSeek((int)tp,"Misc");
    pi8 = g;
    if (i7 == -1) {
      pi8 = g + G_ERRMSG;
      value = "Can\'t load misc config.";
    }
    else {
      g[0x7579] = 0;
      TPGetValueInt((int)tp,"playercache",(uint32_t *)(pi8 + 0x7579));
      pi8 = g;
      g[0x7579] = g[0x7579] + 2;
      pi8[0x757a] = 0;
      TPGetValueInt((int)tp,"precache",(uint32_t *)(pi8 + 0x757a));
      b2 = TPGetValueInt((int)tp,"bufferedread",(uint32_t *)&stk_130);
      if (ZEXT8(b2) != 0) {
        SpriteSetBufReadMode(stk_130);
        SndSetBufReadMode(stk_130);
        g[0x757b] = (int)stk_130;
      }
      TPGetValueInt((int)tp,"unloadsystem",(uint32_t *)(g + G_MISC_UNLOADSYSTEM));
      TPGetValueInt((int)tp,"pauseondefocus",(uint32_t *)(g + G_MISC_PAUSEONDEFOCUS));
      pi8 = g;
      if (g[G_MISC_PAUSEONDEFOCUS] != 0) {
        g[G_SOUND_LINUX_PAUSEBGMONDEFOCUS] = 1;
      }
      i7 = TPScanf((int)tp,"expires","%i,%i,%i,%x",&stk_128,&stk_12c,&stk_124,
                      &stk_120,pi8);
      if ((i7 == 4) &&
         (stk_130 = (int *)((int)((stk_12c ^ stk_128) * stk_124 -
                                    (MUGENDATE_M ^ MUGENDATE_D) ^ MUGENDATE_Y) % 0x10000),
         stk_120 == stk_130)) {
        MUGENEXPDATE_D = stk_12c;
        MUGENEXPDATE_M = stk_128;
        MUGENEXPDATE_Y = stk_124;
      }
      i7 = TPGroupSeek((int)tp,"Arcade");
      if (i7 == -1) {
        pi8 = g + G_ERRMSG;
        value = "Can\'t load arcade config.";
      }
      else {
        TPGetValueInt((int)tp,"ai.randomcolor",(uint32_t *)(g + G_ARCADE_AI_RANDOMCOLOR));
        stk_130 = (int *)0x0;
        do {
          if (stk_130 == (int *)0x1) {
            value = "team";
            stk_134 = g + 0x7584;
            pi8 = stk_134;
          }
          else {
            pi8 = stk_130;
            if ((int)stk_130 < 2) {
              if (stk_130 == (int *)0x0) {
                value = "arcade";
                stk_134 = g + 0x7580;
                pi8 = stk_134;
              }
            }
            else if (stk_130 == (int *)0x2) {
              value = "survival";
              stk_134 = g + 0x7588;
              pi8 = stk_134;
            }
          }
          sprintf(keyname,"%s.AIramp.start",value,pi8);
          TPScanf((int)tp,keyname,"%i,%i",stk_134,stk_134 + 1);
          sprintf(keyname,"%s.AIramp.end",value);
          TPScanf((int)tp,keyname,"%i,%i",stk_134 + 2,stk_134 + 3);
          stk_130 = (int *)((int)stk_130 + 1);
        } while ((int)stk_130 < 3);
        i7 = TPGroupSeek((int)tp,"Input");
        if (i7 == -1) {
          pi8 = g + G_ERRMSG;
          value = "Can\'t load input config.";
        }
        else {
          TPGetValueInt((int)tp,"p1.usekeyboard",(uint32_t *)(g + G_INPUT_P1_USEKEYBOARD));
          TPGetValueInt((int)tp,"p2.usekeyboard",(uint32_t *)(g + G_INPUT_P2_USEKEYBOARD));
          TPGetValueInt((int)tp,"p1.joystick.type",(uint32_t *)(g + G_INPUT_P1_JOYSTICK_TYPE_1CE34));
          TPGetValueInt((int)tp,"p2.joystick.type",(uint32_t *)(g + G_INPUT_P2_JOYSTICK_TYPE_1CE38));
          pi8 = g;
          i7 = g[G_INPUT_P2_JOYSTICK_TYPE_1CE38];
          i10 = g[G_INPUT_P1_JOYSTICK_TYPE_1CE34];
          g[0x738b] = (uint32_t)(i10 != 0);
          pi8[0x738c] = (uint32_t)(i7 != 0);
          i11 = 0;
          if (((i10 != 0) != 0) || ((i7 != 0) != 0)) {
            i11 = 1;
          }
          pi8[0x738f] = i11;
          TPGetValueInt((int)tp,"forcefeedback",(uint32_t *)(g + G_INPUT_FORCEFEEDBACK));
          TPGetValueInt((int)tp,"psxdelay",(uint32_t *)(g + G_PSXDELAY));
          if ((g[G_INPUT_P1_USEKEYBOARD] == 0) ||
             (b2 = PlayerLoadKeys((int)tp,(int)(g + 0x7321),"p1 keys"),
             ZEXT8(b2) != 0)) {
            PlayerKeysRemoveZero((int)(g + 0x7321),0x100);
            if ((g[G_INPUT_P2_USEKEYBOARD] == 0) ||
               (b2 = PlayerLoadKeys((int)tp,(int)(g + 0x732e),"p2 keys"),
               ZEXT8(b2) != 0)) {
              i7 = i11;
              PlayerKeysRemoveZero((int)(g + 0x732e),0x100);
              pi8 = g;
              g[0x7370] = 1;
              pi8[0x7372] = 2;
              pi8[0x7373] = 3;
              pi8[0x7371] = 4;
              pi12 = pi8 + 0x736f;
              pi8 = pi8 + 0x737c;
              for (i10 = 0xd; i10 != 0; i10 = i10 + -1) {
                *pi8 = *pi12;
                pi12 = pi12 + 1;
                pi8 = pi8 + 1;
              }
              sprintf(keyname,"P1 joystick",i11,i7);
              b2 = PlayerLoadKeys((int)tp,(int)(g + 0x736f),keyname);
              i7 = ZEXT8(b2);
              if (i7 != 0) {
                printf("Loading button config for %s.\n",keyname,i7,i7);
              }
              sprintf(keyname,"P2 joystick",pi8,pi8);
              b2 = PlayerLoadKeys((int)tp,(int)(g + 0x737c),keyname);
              if (ZEXT8(b2) != 0) {
                printf("Loading button config for %s.\n",keyname,pi12,pi12);
              }
              pi8 = g + 0x736f;
              pi12 = g + 0x7355;
              for (i7 = 0xd; i7 != 0; i7 = i7 + -1) {
                *pi12 = *pi8;
                pi8 = pi8 + 1;
                pi12 = pi12 + 1;
              }
              pi8 = g + 0x737c;
              pi12 = g + 0x7362;
              for (i7 = 0xd; i7 != 0; i7 = i7 + -1) {
                *pi12 = *pi8;
                pi8 = pi8 + 1;
                pi12 = pi12 + 1;
              }
              if (g[0x738b] == 0) {
                pi8 = g + 0x7355;
                for (i7 = 0xd; i7 != 0; i7 = i7 + -1) {
                  *pi8 = 0;
                  pi8 = pi8 + 1;
                }
              }
              if (g[0x738c] == 0) {
                pi8 = g + 0x7362;
                for (i7 = 0xd; i7 != 0; i7 = i7 + -1) {
                  *pi8 = 0;
                  pi8 = pi8 + 1;
                }
              }
              PlayerKeysRemoveZero((int)(g + 0x7355),0x80);
              PlayerKeysRemoveZero((int)(g + 0x7362),0x80);
              PlayerKeysRemoveZero((int)(g + 0x736f),0x80);
              PlayerKeysRemoveZero((int)(g + 0x737c),0x80);
              TPFree(tp);
              if ((g[G_CONFIG_FIRSTRUN] != 0) && (tp2 = TPReadFileForWrite(filename), tp2 != (void *)0x0))
              {
                pv14 = tp2;
                TPGroupSeek((int)tp2,"Config");
                TPPrintf((int)tp2,"FirstRun","0",pv14);
                TPWriteFile((int)tp2,filename);
              }
              return 1;
            }
            pi8 = g + G_ERRMSG;
            value = "Can\'t read p2 key config.";
          }
          else {
            pi8 = g + G_ERRMSG;
            value = "Can\'t read p1 key config.";
          }
        }
      }
    }
  }
L_080d4c73:
  sprintf((char *)pi8,value,fmt_args[0]);
  return 0;
}
#undef stk_134
#undef stk_130
#undef stk_12c
#undef stk_128
#undef stk_124
#undef stk_120
#undef keyname

/* GameResetOptions @ 0x080d4ea0, 66 bytes
 *
 * Resets the in-game options to their defaults: difficulty 4, life 100%,
 * time 99, game speed 0, sound and music volume 50.
 *
 * Globals written: difficulty
 * Called by: GameInit, OptionsScreen
 *
 * Elecbyte file: src/mugen/system.c
 */
void GameResetOptions(void)

{
  int *pi1;
  
  pi1 = g;
  g[G_DIFFICULTY] = 4;
  pi1[0x799f] = 100;
  pi1[0x79a0] = 99;
  pi1[0x79a1] = 0;
  pi1[0x79a2] = 0x32;
  pi1[0x79a3] = 0x32;
  return;
}

/* GameLoadOptions @ 0x080d4ef0, 745 bytes
 *
 * Reads data/mugen.cfg "[Options]" (Difficulty, Life, Time, GameSpeed,
 * WavVolume, MidiVolume, Team.1VS2Life, Team.LoseOnKO, motif, default
 * "data/system.def") and the player key and joystick configurations. Errors:
 * "Error loading options", "Cannot init input".
 *
 * Text keys read: [Options], "Difficulty", "Life", "Time", "GameSpeed",
 *                 "WavVolume", "MidiVolume", "motif", "Team.1VS2Life",
 *                 "Team.LoseOnKO", [Input], "p1.joystick.type",
 *                 "p2.joystick.type"
 * Globals read: errmsg, difficulty, options_life, options_time, gamespeed,
 *               options_wavvolume, options_midivolume, options_motif,
 *               options_team_1vs2life, options_team_loseonko,
 *               input_p1_joystick_type_1e6ac, input_p2_joystick_type_1e6c0
 * Globals written: input_p1_joystick_type_1ce34
 * Calls: TPReadFile, ErrorExit, TPGroupSeek, TPGetValueInt, TPScanf,
 *        splitdirfile, PlayerLoadKeys, PlayerKeysRemoveZero, TPFree,
 *        GameInitPads, GameInputSetup, ErrorExitM
 * C library: sprintf, memcpy
 * Called by: GameInit, OptionsScreen
 * Messages:
 *   "Error loading options"
 *   "p1 keys"
 *   "p2 keys"
 *   "P1 joystick"
 *   "P2 joystick"
 *   "Cannot init input"
 *
 * Elecbyte file: src/mugen/system.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t GameLoadOptions(void)

{
  int *pi1;
  int *pi2;
  bool b3;
  uint32_t *tp;
  int i5;
  uint32_t stale_var;
  uint32_t stk_c;
  
  tp = TPReadFile("data/mugen.cfg");
  if (tp == (uint32_t *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"Error loading options",0,0);
    ErrorExit();
  }
  i5 = TPGroupSeek((int)tp,"Options");
  if (i5 != -1) {
    TPGetValueInt((int)tp,"Difficulty",(uint32_t *)(g + G_DIFFICULTY));
    TPGetValueInt((int)tp,"Life",(uint32_t *)(g + G_OPTIONS_LIFE));
    TPGetValueInt((int)tp,"Time",(uint32_t *)(g + G_OPTIONS_TIME));
    TPGetValueInt((int)tp,"GameSpeed",(uint32_t *)(g + G_GAMESPEED));
    TPGetValueInt((int)tp,"WavVolume",(uint32_t *)(g + G_OPTIONS_WAVVOLUME));
    TPGetValueInt((int)tp,"MidiVolume",(uint32_t *)(g + G_OPTIONS_MIDIVOLUME));
    TPScanf((int)tp,"motif","%s",g + G_OPTIONS_MOTIF);
    if ((char)g[G_OPTIONS_MOTIF] == '\0') {
      memcpy(g + G_OPTIONS_MOTIF,"data/system.def",0x10);
    }
    splitdirfile((char *)(g + G_OPTIONS_MOTIF),(char *)((int)g + 0x15aff),(char *)(g + 0x52c0));
    TPGetValueInt((int)tp,"Team.1VS2Life",(uint32_t *)(g + G_OPTIONS_TEAM_1VS2LIFE));
    TPGetValueInt((int)tp,"Team.LoseOnKO",(uint32_t *)(g + G_OPTIONS_TEAM_LOSEONKO));
  }
  pi1 = g;
  g[0x79a9] = 1;
  PlayerLoadKeys((int)tp,(int)(pi1 + 0x7321),"p1 keys");
  PlayerLoadKeys((int)tp,(int)(g + 0x732e),"p2 keys");
  PlayerKeysRemoveZero((int)(g + 0x7321),0x100);
  PlayerKeysRemoveZero((int)(g + 0x732e),0x100);
  i5 = TPGroupSeek((int)tp,"Input");
  if (i5 != -1) {
    TPGetValueInt((int)tp,"p1.joystick.type",(uint32_t *)(g + G_INPUT_P1_JOYSTICK_TYPE_1E6AC));
    TPGetValueInt((int)tp,"p2.joystick.type",(uint32_t *)(g + G_INPUT_P2_JOYSTICK_TYPE_1E6C0));
  }
  pi2 = g;
  pi1 = g + G_INPUT_P1_JOYSTICK_TYPE_1E6AC;
  i5 = g[G_INPUT_P2_JOYSTICK_TYPE_1E6C0];
  g[G_INPUT_P1_JOYSTICK_TYPE_1CE34] = *pi1;
  pi2[0x738b] = (uint32_t)(*pi1 != 0);
  pi2[0x738e] = i5;
  pi2[0x738c] = (uint32_t)(i5 != 0);
  PlayerLoadKeys((int)tp,(int)(pi2 + 0x736f),"P1 joystick");
  PlayerLoadKeys((int)tp,(int)(g + 0x737c),"P2 joystick");
  PlayerKeysRemoveZero((int)(g + 0x736f),0x80);
  PlayerKeysRemoveZero((int)(g + 0x737c),0x80);
  TPFree(tp);
  GameInitPads();
  b3 = GameInputSetup();
  if (ZEXT8(b3) == 0) {
    ErrorExitM("Cannot init input");
  }
  return stk_c;
}

/* GameSaveOptions @ 0x080d51e0, 667 bytes
 *
 * Writes the current options and both players' key configurations back into
 * mugen.cfg, keeping its comments (TPReadFileForWrite, TPPrintf,
 * TPWriteFile). "Error saving options" on failure.
 *
 * Text keys read: [Options], [Input]
 * Globals read: errmsg, difficulty, options_life, options_time, gamespeed,
 *               options_wavvolume, options_midivolume,
 *               options_team_1vs2life, options_team_loseonko,
 *               input_p1_joystick_type_1e6ac, input_p2_joystick_type_1e6c0
 * Calls: TPReadFileForWrite, ErrorExit, TPGroupSeek, TPPrintf,
 *        PlayerKeysConvertToZero, PlayerSaveKeys, TPWriteFile, TPFree
 * C library: sprintf
 * Called by: OptionsScreen
 * Messages:
 *   "Error saving options"
 *   "p1 keys"
 *   "p2 keys"
 *   "p1 joystick"
 *   "p2 joystick"
 *
 * Elecbyte file: src/mugen/system.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
void GameSaveOptions(void)

{
  uint32_t *tp;
  int i2;
  uint32_t stale_EDX;
  int *pi3;
  int *pi4;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define buf_5c (*(int (*)[19])(frame + 0x4))
  
  tp = TPReadFileForWrite("data/mugen.cfg");
  if (tp == (uint32_t *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"Error saving options");
    ErrorExit();
  }
  i2 = TPGroupSeek((int)tp,"Options");
  if (i2 != -1) {
    TPPrintf((int)tp,"Difficulty","%i",g[G_DIFFICULTY]);
    TPPrintf((int)tp,"Life","%i",g[G_OPTIONS_LIFE]);
    TPPrintf((int)tp,"Time","%i",g[G_OPTIONS_TIME]);
    TPPrintf((int)tp,"GameSpeed","%i",g[G_GAMESPEED]);
    TPPrintf((int)tp,"WavVolume","%i",g[G_OPTIONS_WAVVOLUME]);
    TPPrintf((int)tp,"MidiVolume","%i",g[G_OPTIONS_MIDIVOLUME]);
    TPPrintf((int)tp,"Team.1VS2Life","%i",g[G_OPTIONS_TEAM_1VS2LIFE]);
    TPPrintf((int)tp,"Team.LoseOnKO","%i",g[G_OPTIONS_TEAM_LOSEONKO]);
  }
  i2 = TPGroupSeek((int)tp,"Input");
  if (i2 != -1) {
    TPPrintf((int)tp,"p1.joystick.type","%i",g[G_INPUT_P1_JOYSTICK_TYPE_1E6AC]);
    TPPrintf((int)tp,"p2.joystick.type","%i",g[G_INPUT_P2_JOYSTICK_TYPE_1E6C0]);
  }
  pi3 = g + 0x7321;
  pi4 = buf_5c;
  for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  PlayerKeysConvertToZero((int)buf_5c,0x100);
  PlayerSaveKeys((int)tp,buf_5c,"p1 keys");
  pi3 = g + 0x732e;
  pi4 = buf_5c;
  for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  PlayerKeysConvertToZero((int)buf_5c,0x100);
  PlayerSaveKeys((int)tp,buf_5c,"p2 keys");
  pi3 = g + 0x736f;
  pi4 = buf_5c;
  for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  PlayerKeysConvertToZero((int)buf_5c,0x80);
  PlayerSaveKeys((int)tp,buf_5c,"p1 joystick");
  pi3 = g + 0x737c;
  pi4 = buf_5c;
  for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  PlayerKeysConvertToZero((int)buf_5c,0x80);
  PlayerSaveKeys((int)tp,buf_5c,"p2 joystick");
  i2 = TPWriteFile((int)tp,"data/mugen.cfg");
  if (i2 == 0) {
    sprintf((char *)(g + G_ERRMSG),"Error saving options",stale_EDX,stale_EDX);
    ErrorExit();
  }
  TPFree(tp);
  return;
}
#undef buf_5c

/* PlayerLoadKeys @ 0x080d5480, 246 bytes
 *
 * Reads one player's key configuration group ("[P1 Keys]", "[P1
 * Joystick]"...): Jump, Crouch, Left, Right, A, B, C, X, Y, Z, Start into
 * key slots 1, 3, 4, 2, 5-10, 11. Returns false if the group is missing.
 *
 * Parameters:
 *   tp           int
 *   keycfg       int
 *   group        char *
 *
 * Text keys read: "Jump", "Crouch", "Left", "Right", "A", "B", "C", "X",
 *                 "Y", "Z", "Start"
 * Calls: TPGroupSeek, TPGetValueInt
 * Called by: GameConfigRead, GameLoadOptions
 *
 * Elecbyte file: src/mugen/system.c
 */
bool PlayerLoadKeys(int tp,int keycfg,char *group)

{
  int i1;
  
  i1 = TPGroupSeek(tp,group);
  if (i1 != -1) {
    TPGetValueInt(tp,"Jump",(uint32_t *)(keycfg + 4));
    TPGetValueInt(tp,"Crouch",(uint32_t *)(keycfg + 0xc));
    TPGetValueInt(tp,"Left",(uint32_t *)(keycfg + 0x10));
    TPGetValueInt(tp,"Right",(uint32_t *)(keycfg + 8));
    TPGetValueInt(tp,"A",(uint32_t *)(keycfg + 0x14));
    TPGetValueInt(tp,"B",(uint32_t *)(keycfg + 0x18));
    TPGetValueInt(tp,"C",(uint32_t *)(keycfg + 0x1c));
    TPGetValueInt(tp,"X",(uint32_t *)(keycfg + 0x20));
    TPGetValueInt(tp,"Y",(uint32_t *)(keycfg + 0x24));
    TPGetValueInt(tp,"Z",(uint32_t *)(keycfg + 0x28));
    TPGetValueInt(tp,"Start",(uint32_t *)(keycfg + 0x2c));
  }
  return i1 != -1;
}

/* PlayerSaveKeys @ 0x080d5580, 276 bytes
 *
 * Writes one player's key configuration back into its group (TPPrintf).
 *
 * Parameters:
 *   tp           int
 *   keycfg       int
 *   group        char *
 *
 * Calls: TPGroupSeek, TPPrintf
 * Called by: GameSaveOptions
 *
 * Elecbyte file: src/mugen/system.c
 */
void PlayerSaveKeys(int tp,int keycfg,char *group)

{
  int i1;
  
  i1 = TPGroupSeek(tp,group);
  if (i1 != -1) {
    TPPrintf(tp,"Jump","%i",*(uint32_t *)(keycfg + 4));
    TPPrintf(tp,"Crouch","%i",*(uint32_t *)(keycfg + 0xc));
    TPPrintf(tp,"Left","%i",*(uint32_t *)(keycfg + 0x10));
    TPPrintf(tp,"Right","%i",*(uint32_t *)(keycfg + 8));
    TPPrintf(tp,"A","%i",*(uint32_t *)(keycfg + 0x14));
    TPPrintf(tp,"B","%i",*(uint32_t *)(keycfg + 0x18));
    TPPrintf(tp,"C","%i",*(uint32_t *)(keycfg + 0x1c));
    TPPrintf(tp,"X","%i",*(uint32_t *)(keycfg + 0x20));
    TPPrintf(tp,"Y","%i",*(uint32_t *)(keycfg + 0x24));
    TPPrintf(tp,"Z","%i",*(uint32_t *)(keycfg + 0x28));
    TPPrintf(tp,"Start","%i",*(uint32_t *)(keycfg + 0x2c));
  }
  return;
}

/* PlayerKeysRemoveZero @ 0x080d56a0, 36 bytes
 *
 * Replaces unassigned (0) key slots by `value` (the "not used" code).
 *
 * Parameters:
 *   keycfg       int
 *   value        uint32_t
 *
 * Called by: GameConfigRead, GameInitPads, GameLoadOptions, OptionsScreen
 *
 * Elecbyte file: src/mugen/system.c
 */
void PlayerKeysRemoveZero(int keycfg,uint32_t value)

{
  int i1;
  int i2;
  
  i1 = 4;
  i2 = 0xb;
  do {
    if (*(int *)(keycfg + i1) == 0) {
      *(uint32_t *)(keycfg + i1) = value;
    }
    i1 = i1 + 4;
    i2 = i2 + -1;
  } while (-1 < i2);
  return;
}

/* PlayerKeysConvertToZero @ 0x080d56d0, 39 bytes
 *
 * Replaces key slots equal to `value` (the "not used" code) by 0 before
 * saving.
 *
 * Parameters:
 *   keycfg       int
 *   value        int
 *
 * Called by: GameSaveOptions
 *
 * Elecbyte file: src/mugen/system.c
 */
void PlayerKeysConvertToZero(int keycfg,int value)

{
  int i1;
  int i2;
  
  i1 = 4;
  i2 = 0xb;
  do {
    if (*(int *)(keycfg + i1) == value) {
      *(uint32_t *)(keycfg + i1) = 0;
    }
    i1 = i1 + 4;
    i2 = i2 + -1;
  } while (-1 < i2);
  return;
}

