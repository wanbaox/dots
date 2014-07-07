//
//  DotHudController.h
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#ifndef __PlayThePlane__DotHudController__
#define __PlayThePlane__DotHudController__

#include "cocos2d.h"
#include "config.h"
#include "UpStateLayer.h"
#include "DownStateLayer.h"
#include "PauseLayer.h"
#include "TopScoreLayer.h"
#include "LevelGoalAlertLayer.h"
#include "FailLayer.h"
#include "NormalEndLayer.h"

USING_NS_CC;

class DotHudController : public cocos2d::CCNode
{
    
public:
    
    NormalEndLayer * m_normalEndLayer;
    FailLayer * m_failLayer;
    UpStateLayer * m_upstateLayer;
    DownStateLayer * m_downStateLayer;
    PauseLayer * m_pauseLayer;
    LevelGoalAlertLayer * m_levelGoalAlertLayer;
    
    TopScoreLayer * m_topScoreLayer;
    
    bool m_pause;
    
public:
    DotHudController();
	~DotHudController();
    
    virtual bool init();
    virtual void onEnter();
    
    CREATE_FUNC(DotHudController);
    
    void gotoNextLevel();
    
    void gameNormalEned(bool success);
    void moveOut4NewLevel();
    void gameFailed();
    void exitGame();
    void gamePause();
    void currentGameOver(int score);
    void resetTimeString(int currentTime);
    void resetScoreString(CCString* string);
    void startGame();
    void restartGame(bool isRestart);
    void playerUseSkill(PLAYERTOOLTYPE skillTpye);
    
};



#endif /* defined(__PlayThePlane__DotHudController__) */
