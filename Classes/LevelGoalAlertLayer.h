//
//  LevelGoalAlertLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __LevelGoalAlertLayer__
#define __LevelGoalAlertLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class LevelGoalAlertLayer : public cocos2d::CCLayerColor {
    
    CCLabelTTF * m_labelLevel;
    CCLabelTTF * m_labelGoal;
//    CCSprite * m_spriteBg;
    
public:
    
    LevelGoalAlertLayer();
	~LevelGoalAlertLayer();
    
    virtual bool init();
    
    CREATE_FUNC(LevelGoalAlertLayer);
    
    void startAnimationDisplay(int level,long goal);
    void startAnimationDisplay4NextLevel(int level,long goal);
    
    
    void callBackMenuOut(CCObject* sender);
    void callBack0(CCObject* sender);
    void callBack1(CCObject* sender);
};

#endif