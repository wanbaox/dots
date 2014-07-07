//
//  AudioHelper.h
//  dots
//
//  Created by 谢元潮 on 13-11-30.
//
//

#ifndef dots_AudioHelper_h
#define dots_AudioHelper_h

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class AudioHelper : public cocos2d::CCObject
{
    
public:
    
    static void loadEffectSounds();
    
    static void playingSound(int count);
    static void playButtonPress();
    static void playGameTypeSwitch();
    static void playMenuPress();
    static void playMenuOut();
    static void playMenuIn();
//    static void playGameOver();
    static void playGameFailed();
    static void playGameStart();
    static void playItemTaped();
    static void playAnnouncerByNumber();
    static void playAnnouncer4HideAllSame();
    static void playStageClear();
    static void playGoalFinished();
    static void playTimeUp();
    static void playAnnouncer(Announcer anncouncer);
    
};


#endif
