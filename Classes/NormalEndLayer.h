//
//  NormalEndLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __NormalEndLayer__
#define __NormalEndLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class NormalEndLayer : public cocos2d::CCLayerColor {
    
    CCMenuItemImage * m_reTry;
    CCMenuItemImage * m_exitGame;
    
public:
    
    NormalEndLayer();
	~NormalEndLayer();
    
    virtual bool init();
    
    CREATE_FUNC(NormalEndLayer);
    
    void startAnimationDisplay(bool success);
    
    void callBackReTry(CCObject* sender);
    
    void callBackExitGame(CCObject* sender);
    
    void moveOut();
};

#endif