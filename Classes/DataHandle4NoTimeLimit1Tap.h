//
//  DataHandle4NoTimeLimit1Tap.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __DataHandle4NoTimeLimit1Tap__
#define __DataHandle4NoTimeLimit1Tap__

#include "cocos2d.h"
#include "config.h"
#include "DrawSprite.h"
#include "DataHandle.h"

USING_NS_CC;

/**
 
 这个只需要点一下就会消除
 
 */

class DataHandle4NoTimeLimit1Tap : public DataHandle {

//    CCArray * m_Suggestion;
public:
    
    DataHandle4NoTimeLimit1Tap();
	~DataHandle4NoTimeLimit1Tap();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandle4NoTimeLimit1Tap);

    
    bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
    
    bool touchBegine(CCPoint local);//touch begine
    
    void touchMove(CCPoint local); // touch moved
    
    void touchEnd(CCPoint local);// touch 结束

    
    void checkSurround(DrawSprite *drawSprite);//判断周围是否包含相同的
    void hideSelected();//隐藏选中的items
    
    bool hasMoreMatched();
    
    bool checkSurround(DrawSprite *drawSprite,CCArray* remainArray);
};

#endif