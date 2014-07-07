//
//  AudioHelper.cpp
//  dots
//
//  Created by 谢元潮 on 13-11-30.
//
//

#include "AudioHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void AudioHelper::loadEffectSounds(){
    
    //都用mp3 或者wav
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("1.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("2.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("3.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("4.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("5.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("6.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("7.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("8.mp3");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("button_release.wav");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sign_falls_in1.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("woosh.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("info_swoop_out.wav");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("info_swoop_in.wav");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("normal_end.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("start.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("fail.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tap.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("goal_finished.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_by_number.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_4_hide_all_same.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("stage_clear.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tick.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("power_up_time.mp3");
    
    
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_1.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_2.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_3.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_4.mp3");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("announcer_5.mp3");
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.3);
    
    
}

void AudioHelper::playTimeUp(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tick.mp3");
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("power_up_time.mp3");
        
    }
    
}

void AudioHelper::playStageClear(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("stage_clear.mp3");
    }
    
}

void AudioHelper::playGoalFinished(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("goal_finished.mp3");
    }
    
}

void AudioHelper::playAnnouncer4HideAllSame(){
    
//    if (SettingHelper::isAudioOn()) {
//        
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_4_hide_all_same.mp3");
//    }
    
}

void AudioHelper::playAnnouncerByNumber(){
    
//    if (SettingHelper::isAudioOn()) {
//        
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_by_number.mp3");
//    }
    
}

void AudioHelper::playItemTaped(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tap.wav");
    }
    
}

void AudioHelper::playAnnouncer(Announcer anncouncer){
    
//    if (SettingHelper::isAudioOn()) {
//        
//        switch (anncouncer) {
//            case Announcer1:
//                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_1.mp3");
//                break;
//                
//            case Announcer2:
//                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_2.mp3");
//                break;
//                
//            case Announcer3:
//                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_3.mp3");
//                break;
//                
//            case Announcer4:
//                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_4.mp3");
//                break;
//                
//            case Announcer5:
//                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("announcer_5.mp3");
//                break;
//                
//            default:
//                break;
//                
//        }
//    }
   
    
}

void AudioHelper::playGameStart(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("start.mp3");
    }
    
}

void AudioHelper::playGameFailed(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("fail.mp3");
    }
    
}

//void AudioHelper::playGameOver(){
//    
//    if (SettingHelper::isAudioOn()) {
//        
//        
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("normal_end.mp3");
//    }
//    
//}


void AudioHelper::playMenuIn(){
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("info_swoop_in.wav");
    
}

void AudioHelper::playMenuOut(){
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("info_swoop_out.wav");
    
}

void AudioHelper::playMenuPress(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("button_release.wav");
    }
}

void AudioHelper::playingSound(int count){
    
    if (SettingHelper::isAudioOn()) {
        
        
        //1,2,3,4,5,6,7,8,7,6,5,4,3,2,1,
        
        if (count>8) {
            
            count=(count/8)/2==0?8-count%8:count%8+1;
        }
        
        CCString * soundName = CCString::createWithFormat("%d.mp3",count);
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundName->getCString());
    }
    
}

void AudioHelper::playButtonPress(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("button_release.wav");
    }
    
}

void AudioHelper::playGameTypeSwitch(){
    
    if (SettingHelper::isAudioOn()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("woosh.mp3");
    }
    
}