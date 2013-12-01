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

USING_NS_CC;

class DotHudController : public cocos2d::CCNode
{
    
    UpStateLayer * m_upstateLayer;
    DownStateLayer * m_downStateLayer;
    PauseLayer * m_pauseLayer;
    
    TopScoreLayer * m_topScoreLayer;
    
    bool m_pause;
    
public:
    DotHudController();
	~DotHudController();
    
    virtual bool init();
    virtual void onEnter();
    
    CREATE_FUNC(DotHudController);
    
    
    void gamePause();
    void currentGameOver(int score);
    void resetTimeString(CCString* string);
    void resetScoreString(CCString* string);
    void startGame();
    void playerUseSkill(PLAYERTOOLTYPE skillTpye);
    
};



#endif /* defined(__PlayThePlane__DotHudController__) */
