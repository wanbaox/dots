//
//  UpStateLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __UpStateLayer__
#define __UpStateLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class UpStateLayer : public cocos2d::CCLayerColor {
    
    CCLabelTTF * m_labelTime;
    CCLabelTTF * m_labelScore;
    
    CCMenuItemImage * m_scoreItem;
    CCMenuItemImage * m_timeItem;
    
public:
    
    UpStateLayer();
	~UpStateLayer();
    
    virtual bool init();
    
    CREATE_FUNC(UpStateLayer);
    
    void menuBePressed(CCObject* sender);
    void resetTimeString(CCString * string);
    void resetScoreString(CCString * string);
    
    void startAnimationDisplay();
    
    void callBack0(CCObject* sender);
};

#endif