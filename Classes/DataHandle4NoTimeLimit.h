//
//  DataHandle4NoTimeLimit.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __DataHandle4NoTimeLimit__
#define __DataHandle4NoTimeLimit__

#include "cocos2d.h"
#include "config.h"
#include "DrawSprite.h"
#include "DataHandle.h"

USING_NS_CC;

/**
 
 游戏界面,在点击第二次的时候才会消除，ppgou
 
 */

class DataHandle4NoTimeLimit : public DataHandle {

//    CCArray * m_Suggestion;
public:
    
    DataHandle4NoTimeLimit();
	~DataHandle4NoTimeLimit();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandle4NoTimeLimit);

    
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