//
//  TopScoreLayer.h
//  disappear
//
//  游戏结束后显示分数
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __TopScoreLayer__
#define __TopScoreLayer__

#include "cocos2d.h"
#include "config.h"
#include "TableLayer.h"

USING_NS_CC;

class TopScoreLayer : public cocos2d::CCLayerColor {
    
    
    CCLabelTTF * m_logoLabel;
    
    CCLabelTTF * m_levelLabel;
    
    CCLabelTTF * m_goldlabel;
    
    CCLabelTTF * m_highScore;
    
    CCLabelTTF * m_thisRound;
    
    CCProgressTimer * m_expProgress;
    
    TableLayer * m_tableLayer;
    
    CCMenuItemImage * m_imageItem;
    
    CCPoint m_touchStartLocation;
    
    bool m_imageButtonResponseType;
    
    bool m_canTriggerAction;
    
public:
    
    TopScoreLayer();
	~TopScoreLayer();
    
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(TopScoreLayer);
    
    void startAnimationDisplay(int score);
    
    void startAnimationDisplay();
    
    void imageItemPressed();
    
    void loadAnimation(int score ,CCArray* array);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    virtual void onExit	();

    //callback
    void callback0(CCInteger score);
    
};

#endif