//
//  SettingHelper.cpp
//  dots
//
//  Created by 谢元潮 on 13-11-30.
//
//

#include "SettingHelper.h"

USING_NS_CC;

void SettingHelper::setDarkTheme(bool value){
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("key_game_dark_theme", value);
    CCUserDefault::sharedUserDefault()->flush();
}

bool SettingHelper::isDarkTheme(){
    
    return CCUserDefault::sharedUserDefault()->getBoolForKey("key_game_dark_theme",false);
}

void SettingHelper::setAudio(bool value){
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("key_game_audio", value);
    CCUserDefault::sharedUserDefault()->flush();
}

bool SettingHelper::isAudioOn(){
    
    return CCUserDefault::sharedUserDefault()->getBoolForKey("key_game_audio",true);
}

void SettingHelper::setToppestScore4ClassicLevel(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_top_4_classic_level", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getToppestScore4ClassicLevel(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_top_4_classic_level",0);
}

void SettingHelper::setToppestScore4NoLimit(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_top_4_nolimit", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getToppestScore4NoLimit(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_top_4_nolimit",0);
}

void SettingHelper::setToppestScore4TapLevel(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_top_4_tap_level", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getToppestScore4TapLevel(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_top_4_tap_level",0);
}

void SettingHelper::setToppestScore4Tap(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_top_4_tap", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getToppestScore4Tap(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_top_4_tap",0);
}

void SettingHelper::setToppestScore4Classic(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_top_4_classic", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getToppestScore4Classic(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_top_4_classic",0);
}

void SettingHelper::setGameType(int gameType){

    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_type", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getGameType(){

    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_type", GAME_TYPE_CLASSIC);
}


void SettingHelper::clearData4NewGame()
{

//    setLastTime(TIME4ONELEVEL);
    setLastLevel(1);
    setLastScore(0);
    
}

void SettingHelper::setLastScore(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_last_score", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getLastScore(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_last_score", 0);
    
}



void SettingHelper::setLastLevel(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_last_level", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getLastLevel(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_last_level", 1);
    
}



//void SettingHelper::setLastTime(int gameType){
//    
//    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_last_time", gameType);
//    CCUserDefault::sharedUserDefault()->flush();
//}
//
//int SettingHelper::getLastTime(){
//    
//    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_last_time", TIME4ONELEVEL);
//    
//}



void SettingHelper::setLastGameType(int gameType){
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("key_game_last_game_type", gameType);
    CCUserDefault::sharedUserDefault()->flush();
}

int SettingHelper::getLastGameType(){
    
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("key_game_last_game_type", GAME_TYPE_CLASSIC);
    
}

