//
//  DataHandle4Tap.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//
#ifndef __DataHandle4Tap__
#define __DataHandle4Tap__

#include "cocos2d.h"
#include "config.h"
#include "DrawSprite.h"
#include "SettingHelper.h"
#include "DataHandle.h"

USING_NS_CC;

/**
 
 游戏界面
 点一下就消除，一个也会消除
 根据个数，播放不同的声音(或者根据连击（3个以上）一次次播放高分贝的声音)
 规定多长时间内发生第二次消除（个数大于3）
 
 */

class DataHandle4Tap : public DataHandle {
    
    
    CCArray * array4Remain;//checkSurround4里用
    
public:
    
    DataHandle4Tap();
	~DataHandle4Tap();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandle4Tap);

    bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
    void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
    
    bool touchBegine(CCPoint local);//touch begine
    
    void touchMove(CCPoint local); // touch moved
    
    void touchEnd(CCPoint local);// touch 结束
    
    void checkSurround(DrawSprite *drawSprite);//判断周围是否包含相同的
    void hideSelected();//隐藏选中的items

    void checkSurround4(DrawSprite *drawSprite);//判断剩下的是否还有matched可以消除
    
//    void giveMoreMatched();
    
    bool hasMoreMatched();
    
    //没有可以消除的，给出一些可以消除的
    void giveMoreMatch(int scage);
    
    void alert();//给用户提示
};

#endif