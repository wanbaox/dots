//
//  DataHandleClassic.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __DataHandleClassic__
#define __DataHandleClassic__

#include "cocos2d.h"
#include "config.h"
#include "DrawSprite.h"
#include "DataHandle.h"
USING_NS_CC;

/**
 
 游戏界面
 
 */

class DataHandleClassic : public DataHandle {
    
    
public:
    
    DataHandleClassic();
	~DataHandleClassic();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandleClassic);


    
    bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
    
    bool touchBegine(CCPoint local);//touch begine
    
    void touchMove(CCPoint local); // touch moved
    
    void touchEnd(CCPoint local);// touch 结束
    
    
};

#endif