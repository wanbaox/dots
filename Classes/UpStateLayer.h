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
    
private:
    cocos2d::CCProgressTimer *progresstime1;
    
public:
    
    int m_scoreShowed;
    int m_score;
    
    
    CCMenuItem * m_Level_bg;
    CCMenuItem * m_Top_bg;
    CCMenuItem * m_Score_bg;
    
    CCLabelTTF * m_labelScore;
    CCLabelTTF * m_labelLevel;
    CCLabelTTF * m_labelGoal;
    CCLabelTTF * m_labelTop;
    
    CCLabelTTF * title_score;
    CCLabelTTF * title_level;
    CCLabelTTF * title_top;
    CCLabelTTF * title_goal;
    
public:
    
    UpStateLayer();
	~UpStateLayer();
    
    virtual bool init();
    
    CREATE_FUNC(UpStateLayer);
    
    void menuBePressed(CCObject* sender);
    void resetTimeString(CCString * string);
    void resetScoreString(CCString * string);
    void scoreAdded(int score);
    void resetToppestScore(CCString * string);
    
    void startAnimationDisplay(int level,long goal);
    void resetProgressBar(int currentTime);
    void resetItemPosition();
    
    void moveOut();
    
    void callBack0(CCObject* sender);
    
    void update(float time);
};

#endif