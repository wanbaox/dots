//
//  config.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright (c) 2013年 CpyShine. All rights reserved.
//

#ifndef disappear_config_h
#define disappear_config_h

#include "cocos2d.h"
#include "SettingHelper.h"

//-------theme--------

#define Color_Bg (SettingHelper::isDarkTheme()?ccc4(0, 0, 0, 255):ccc4(235, 255, 255, 255))
#define Color_Bg3B (SettingHelper::isDarkTheme()?ccc3(0, 0, 0):ccc3(235, 255, 255))
#define Color_Up_Down (SettingHelper::isDarkTheme()?ccc4(14, 14, 14, 255):ccc4(245, 245, 245, 255))
#define Color_Up_Down3B (SettingHelper::isDarkTheme()?ccc3(14, 14, 14):ccc3(245, 245, 245))
#define Color_Pause (SettingHelper::isDarkTheme()?ccc4(22, 22, 22, 255):ccc4(235, 235, 235, 255))
#define Color_Text (!SettingHelper::isDarkTheme()?ccc3(0, 0, 0):ccc3(255, 255, 255))

//不限时间 闯关模式 碰碰狗，对角模式
//限制时间 闯关 消除模式 candy crush
#define GAME_TYPE_CLASSIC       0     // 60秒 经典模式
#define GAME_TYPE_SPEED         1     // 60秒 一次点击就消除
#define GAME_TYPE_NOTIMELIMIT   2     // endless
#define GAME_TYPE_CLASSIC_LEVEL 3     // 60秒 经典模式 闯关
#define GAME_TYPE_SPEED_LEVEL   4     // 60秒 一次点击就消除 闯关

#define menuPadding 10

//#define TOTALX DataHandle::GetXNumber()
//#define TOTALY DataHandle::GetYNumber()
//#define TOTALS DataHandle::GetXNumber()*DataHandle::GetYNumber()

#define SPAWN_DROPDOWN_TIME 0.4

#define RESET_DROPDOWN_TIME (SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT?0.4:0.2)

#define DRAWSPRITE_RADIUES 11
#define DRAWSPRITE_WIDTH (SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT?15.0:24.0)
#define DRAWSPRITE_HEIGH (SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT?15.0:24.0)

#define TIME4ONELEVEL 60  //一局花费的时间秒钟
#define TIME4ONELEVELHalf 30  //classic和taptaptap一局花费的时间秒钟

#define BottomHeight 42 //bottomHeight

#define UpHeight 60

#define Height4MiddleAlert 120

#define TOTAL_TYPE 5

#define ccc4fBlue ccc4f(0.549,0.7412,0.9921,1)
#define ccc4fOrange ccc4f(1,0.6745,0,1)
#define ccc4fRed ccc4f(0.9137,0.3686,0.298,1)
#define ccc4fPurple ccc4f(0.6,0.3765,0.7019,1)
#define ccc4fGreen ccc4f(0.5529,0.9098,0.5803,1)
#define ccc4fYellow ccc4f(0.902,0.851,0.2391,1)

typedef enum {
    tooltime = 0,
    toolDisappearAll = 1,
    toolDisappearOne = 2,
}PLAYERTOOLTYPE;

static const long int expArray[] = {0,100,150,225,338,506,759,1139,1709,2563,3844,5767,8650,12975,19462,29192,43789,65684,98526,147789,184736,230921,288651,360813,451017,563771,704714,880892,1101115,1376394,1720493,2150616,2688270,3360337,4200421,5250527,6563158,8203948,10254935,12818669,14421002,16223628,18251581,20533029,23099657,25987114,29235504,32889942,37001184,41626332,46829624,52683327,59268743,66677336,75012003,84388503,94937066,106804199,120154724,135174064,143622443,152598846,162136247,172269791,183036653,194476444,206631222,219545673,233267277,247846482,263336887,279795443,297282658,315862824,335604251,356579516,378865736,402544845,427703898,454435391};

#define AnnoucerByNumber        5      //每次消除（classic和speed）超过这个数就播放一个声音，“矮油”

enum Announcer {
    
    Announcer1 = 7,
    Announcer2 = 8,
    Announcer3 = 9,
    Announcer4 = 10,
    Announcer5 = 11
    
};


#endif
