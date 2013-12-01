//
//  DotHudController.cpp
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#include "DotHudController.h"
#include "DotPlayingScene.h"

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
    
    m_downStateLayer    = DownStateLayer::create();
    m_upstateLayer      = UpStateLayer::create();
    m_pauseLayer        = PauseLayer::create();
    m_topScoreLayer     = TopScoreLayer::create();
    
    this->addChild(m_downStateLayer,2);
    this->addChild(m_upstateLayer,2);
    this->addChild(m_pauseLayer,1);
    this->addChild(m_topScoreLayer);
    
    
    return true;
}

void DotHudController::onEnter(){
    
    CCNode::onEnter();
    
    m_upstateLayer->startAnimationDisplay();
    m_downStateLayer->startAnimationDisplay();
}

void DotHudController::startGame(){
    
    if (this->getParent()!=NULL) {
        
        DotPlayingScene * dps = (DotPlayingScene*)this->getParent();
        dps->startDotGame();
    }
}

void DotHudController::gamePause(){
    
    if (m_pause) {
        if (this->getParent()!=NULL) {
            
            m_pauseLayer->setVisible(false);
            
            DotPlayingScene * playing = (DotPlayingScene*)this->getParent();
            playing->resumeGame();
            m_pause = false;
        }
    }else{
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


void DotHudController::resetTimeString(CCString *string){
    
    m_upstateLayer->resetTimeString(string);
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