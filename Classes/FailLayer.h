//
//  FailLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __FailLayer__
#define __FailLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class FailLayer : public cocos2d::CCLayerColor {
    
    CCMenuItemImage * m_reTry;
    CCMenuItemImage * m_exitGame;
    
public:
    
    FailLayer();
	~FailLayer();
    
    virtual bool init();
    
    CREATE_FUNC(FailLayer);
    
    void startAnimationDisplay();
    
    void callBackReTry(CCObject* sender);
    
    void callBackExitGame(CCObject* sender);
    
    void moveOut();
};

#endif