//
//  SettingHelper.cpp
//  dots
//
//  Created by 谢元潮 on 13-11-30.
//
//

#include "SettingHelper.h"

USING_NS_CC;

void SettingHelper::setGameType(int gameType){

    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_type", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getGameType(){

    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_type", GAMETYPE0);
    
}

