//
//  DataHandle.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __DataHandle__
#define __DataHandle__

#include "cocos2d.h"
#include "config.h"
#include "DrawSprite.h"

USING_NS_CC;

/**
 
 游戏界面
 
 */

class DataHandle : public cocos2d::CCLayerColor {
    
    //初始化的items
    CCArray * m_drawSpriteArray;
    
    ccColor4F m_currentDrawColor;
    
    //选中的items
    CCArray * m_stackArray;
    
    bool m_drawLine;
    
    bool m_objectHasContina;
    
    bool m_removeAllSameColor;
    
    bool m_toolsDisappear;
    
    bool m_toolsDisappearType;
    
    bool m_canPlaying;
    
    CCPoint m_movePos;
    
public:
    
    DataHandle();
	~DataHandle();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandle);
    
    
    void startAnimtionDisplay();
    
    void startPlaying();
    
    DrawSprite * getCurrentSelectSprite(CCPoint pos);
    
    virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
    
    
    virtual void draw(void);
    
    
    bool touchBegine(CCPoint local);//touch begine
    
    void touchMove(CCPoint local); // touch moved
    
    void touchEnd();// touch 结束
    
    void toolDisappearSelected(CCPoint local);
    int disappearAllSameColorDotsWithSelected();
    
    void disappearEnd();// 消除结束
    
    bool allDrawNodeBeSelected(bool disappearType);//全部选中
    
    void calcDropDown(DrawSprite* drawSprite,CCArray *resultArray);
    
    void cancelAllDrawNodeBeSelected();
    
    //-(void) cancelAllDrawNodeBeSelected;// 取消全部选中的情况
    
    void moveOut();
    void moveIn();
    
    
};

#endif