//
//  DotHudController.cpp
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#include "DotHudController.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"

DotHudController::DotHudController()
{
    
}

DotHudController::~DotHudController()
{
    
}

bool DotHudController::init()
{
    
    if ( !CCNode::init() )
    {
        return false;
    }
    
    m_failLayer             = FailLayer::create();
    m_downStateLayer        = DownStateLayer::create();
    m_upstateLayer          = UpStateLayer::create();
    m_pauseLayer            = PauseLayer::create();
    m_topScoreLayer         = TopScoreLayer::create();
    m_levelGoalAlertLayer   = LevelGoalAlertLayer::create();
    m_normalEndLayer        = NormalEndLayer::create();
    
    this->addChild(m_downStateLayer,2);
    this->addChild(m_upstateLayer,2);
    this->addChild(m_pauseLayer,1);
    this->addChild(m_topScoreLayer);
    this->addChild(m_levelGoalAlertLayer,3);
    this->addChild(m_failLayer,3);
    this->addChild(m_normalEndLayer,3);
    
    m_pause = true;
    
    
    
    return true;
}

void DotHudController::onEnter(){
    
    CCNode::onEnter();
    
    
    DotPlayingScene * dps = (DotPlayingScene*)this->getParent();
    
    
    m_upstateLayer->startAnimationDisplay(dps->m_level, dps->getCurrrentGoal(dps->m_level));
    m_downStateLayer->startAnimationDisplay();
    
    if (SettingHelper::getGameType() != GAME_TYPE_CLASSIC && SettingHelper::getGameType() != GAME_TYPE_SPEED) {
        
        m_levelGoalAlertLayer->startAnimationDisplay(dps->m_level, dps->getCurrrentGoal(dps->m_level));
    }else{
    
        this->scheduleOnce(schedule_selector(DotHudController::startGame), 0.5);
        
    }
    
    
}

void DotHudController::gotoNextLevel(){
    
    
    DotPlayingScene * dps = (DotPlayingScene*)this->getParent();
    
    m_levelGoalAlertLayer->startAnimationDisplay4NextLevel(dps->m_level, dps->getCurrrentGoal(dps->m_level));
    
    m_upstateLayer->m_labelGoal->setString(CCString::createWithFormat("%li",dps->getCurrrentGoal(dps->m_level))->getCString());
    
    m_upstateLayer->m_labelLevel->setString(CCString::createWithFormat("%i",dps->m_level)->getCString());
}

void DotHudController::restartGame(bool isRestart){
    
    if (this->getParent()!=NULL) {
        
        DotPlayingScene * dps = (DotPlayingScene*)this->getParent();
        if (isRestart) {
            
            m_failLayer->moveOut();
            m_normalEndLayer->moveOut();
            m_pauseLayer->moveOut(false);
            
            dps->m_data->scheduleOnce(schedule_selector(DataHandle::moveIn), 0.5);
            
            
            
            //            dps->m_data->moveOutForRestart();//隐藏所有items
            
            m_upstateLayer->resetScoreString(CCString::createWithFormat("%i",SettingHelper::getLastScore()));
            
            
            
            if (SettingHelper::getGameType()==GAME_TYPE_CLASSIC) {
                
                m_upstateLayer->resetToppestScore(CCString::createWithFormat("%i",SettingHelper::getToppestScore4Classic()));
            }else{
                
                m_upstateLayer->resetToppestScore(CCString::createWithFormat("%i",SettingHelper::getToppestScore4Tap()));
            }
        }
        
        dps->startDotGame(isRestart);
        
        m_pause = false;
    }
}

void DotHudController::startGame(){
    
    this->restartGame(false);
    
}

void DotHudController::moveOut4NewLevel(){
    
    if (this->getParent()!=NULL) {
        
        DotPlayingScene * dps = (DotPlayingScene*)this->getParent();
        dps->m_data->moveIn();
        
        dps->startDotGame(false);
        
        m_pause = false;
    }
}

void DotHudController::gameFailed(){

    m_failLayer->startAnimationDisplay();
}

void DotHudController::gameNormalEned(bool success){
    
    m_normalEndLayer->startAnimationDisplay(success);
}

void DotHudController::exitGame(){
    
    //推出到主界面
    
    m_upstateLayer->moveOut();
    m_downStateLayer->moveOut();
    m_pauseLayer->moveOut(true);
    m_failLayer->moveOut();
    m_normalEndLayer->moveOut();
    
}

void DotHudController::gamePause(){
    
    if (m_pause) {
        
//        m_downStateLayer->setColor(Color_Bg3B);
        
        if (this->getParent()!=NULL) {
            
//            m_pauseLayer->setVisible(false);

            m_failLayer->moveOut();
            m_normalEndLayer->moveOut();
            m_pauseLayer->moveOut(false);
            
            DotPlayingScene * playing = (DotPlayingScene*)this->getParent();
            playing->resumeGame();
            m_pause = false;
        }
    }else{
        
//        m_downStateLayer->setColor(Color_Up_Down3B);
        
        if (this->getParent()!=NULL) {
            
            m_pauseLayer->startAnimationDisplay();
            DotPlayingScene * playing = (DotPlayingScene*)this->getParent();
            playing->pauseGame();
            m_pause = true;
        }
    }
}

void DotHudController::currentGameOver(int score){
    
    m_downStateLayer->setVisible(false);
    m_upstateLayer->setVisible(false);
    m_pauseLayer->setVisible(false);
    m_topScoreLayer->startAnimationDisplay(score);
    
}


void DotHudController::resetTimeString(int currentTime){
    
    m_upstateLayer->resetTimeString(CCString::createWithFormat("%d",currentTime));
    if (currentTime>=0) {
        
        m_upstateLayer->resetProgressBar(currentTime);
    }
}

void DotHudController::resetScoreString(CCString *string){
    
    m_upstateLayer->resetScoreString(string);
    
}


void DotHudController::playerUseSkill(PLAYERTOOLTYPE skillTpye){
    
    if (this->getParent()!=NULL) {
        DotPlayingScene * playing = (DotPlayingScene*)this->getParent();
        if (playing) {
            
            playing->playerUsedToolDisappear(skillTpye);
        }
    }
}