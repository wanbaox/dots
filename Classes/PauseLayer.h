//
//  PauseLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __PauseLayer__
#define __PauseLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class PauseLayer : public cocos2d::CCLayerColor {
    
//    CCLayerColor*bgLayer;
    CCMenuItemImage * m_resume;
    CCMenuItemImage * m_restart;
    CCMenuItemImage * m_exittomain;
    
public:
    
    PauseLayer();
	~PauseLayer();
    
    virtual bool init();
    
    CREATE_FUNC(PauseLayer);
    
    void startAnimationDisplay();
    void moveOut(bool isExitToMainPage);
    
    void exitToMainScnen();
    void restartDotGame();
    void resumeDotGame();
    
    void replaceScene();
};

#endif