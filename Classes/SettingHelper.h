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
    
    static void setGameType(int gameType);
    static int getGameType();
    
    
    
};


#endif
