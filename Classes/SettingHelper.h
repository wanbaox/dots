//
//  SettingHelper.h
//  dots
//
//  Created by 谢元潮 on 13-11-30.
//
//

#ifndef dots_SettingHelper_h
#define dots_SettingHelper_h

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class SettingHelper : public cocos2d::CCObject
{
    
public:
    
    static void setDarkTheme(bool object);
    static bool isDarkTheme();
    
    static void setAudio(bool object);
    static bool isAudioOn();
    
    static void setToppestScore4NoLimit(int object);
    static int getToppestScore4NoLimit();
    
    static void setToppestScore4TapLevel(int object);
    static int getToppestScore4TapLevel();
    
    static void setToppestScore4Tap(int object);
    static int getToppestScore4Tap();
    
    static void setToppestScore4ClassicLevel(int object);
    static int getToppestScore4ClassicLevel();
    
    static void setToppestScore4Classic(int object);
    static int getToppestScore4Classic();
    
    static void setGameType(int gameType);
    static int getGameType();
    
    
    static void clearData4NewGame();
    
    static void setLastScore(int object);
    static int getLastScore();
    
    static void setLastLevel(int object);
    static int getLastLevel();
    
//    static void setLastTime(int object);
//    static int getLastTime();
    
    static void setLastGameType(int object);
    static int getLastGameType();
};


#endif
