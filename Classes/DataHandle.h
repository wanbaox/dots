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

//奖励

extern int m_totalX;
extern int m_totalY;

class DataHandle : public cocos2d::CCLayerColor {
    
    
public:
    
    
    int count4Continue;//连续多次消除，播放不同是声音
    
    long lastTimeDismiss;//最后一次消除的时间
    
    //初始化的items
    CCArray * m_drawSpriteArray;
    
    ItemType m_currentDrawColor;
//    ccColor4F m_currentDrawColor;
    
    //选中的items
    CCArray * m_stackArray;
    
    bool m_drawLine;
    
    bool m_objectHasContina;
    
    bool m_removeAllSameColor;
    
    bool m_toolsDisappear;
    
    bool m_toolsDisappearType;
    
    
    CCPoint m_movePos;
    
    
    bool m_canPlaying;
    
    bool m_stageCleared;
    
public:
    
    DataHandle();
	~DataHandle();
    
    virtual bool init();
    
    CREATE_FUNC(DataHandle);
    
    
    void startAnimtionDisplay();
    
    void startPlaying();
    
    DrawSprite * getCurrentSelectSprite(CCPoint pos);
    
    virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent){return true;}
    virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent){}
    virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent){}
    virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){}
    virtual bool touchBegine(CCPoint local){return true;}//touch begine
    
    virtual void touchMove(CCPoint local){} // touch moved
    
    virtual void touchEnd(){}// touch 结束
    
    
    
    virtual void draw(void);
    
    void toolDisappearSelected(CCPoint local);
    int disappearAllSameColorDotsWithSelected();
    
    void disappearEnd();// 消除结束
    
    bool allDrawNodeBeSelected(bool disappearType);//全部选中
    
    void calcDropDown(DrawSprite* drawSprite,CCArray *resultArray);
    
    void cancelAllDrawNodeBeSelected();
    
    //-(void) cancelAllDrawNodeBeSelected;// 取消全部选中的情况
    
    void moveOutForNextLevel(); //在进入下一个level之前，先隐藏items
    void moveOutForRestart();   
    
    void moveOut();
    void moveOutCallBack();
    void moveIn();
    void moveInCallBack();
    
    void removeSprite(CCNode * node);
    
    void checkEmptyColumn();//判断是否有空列
    
    void showGotScore(CCPoint position, int score);
    
    int getCurrentScore(int count);
    CCPoint calcMidPos(CCPoint currentPressed);//计算选中的items的中间位置
    
    
    virtual bool hasMoreMatched(){return true;}//是否还存在可以消除的item
    
    void showAnnouncer(int anncouncer);
    
    virtual void alert(){};//给用户提示
    
    static int GetXNumber(){
        
        switch (SettingHelper::getGameType()) {
            case GAME_TYPE_CLASSIC:
                
                return 6;
                break;
            case GAME_TYPE_CLASSIC_LEVEL:
                
                return 6;
                break;
            case GAME_TYPE_SPEED:
                
                return 7;
                break;
            case GAME_TYPE_SPEED_LEVEL:
                
                return 7;
                break;
            case GAME_TYPE_NOTIMELIMIT:
                
                return 10;
                break;
            default:
                break;
        }
        
        return 0;
    }
    
    static int GetYNumber(){
        
        switch (SettingHelper::getGameType()) {
            case GAME_TYPE_CLASSIC:
                
                return 6;
                break;
            case GAME_TYPE_CLASSIC_LEVEL:
                
                return 6;
                break;
            case GAME_TYPE_SPEED:
                
                return 8;
                break;
            case GAME_TYPE_SPEED_LEVEL:
                
                return 8;
                break;
            case GAME_TYPE_NOTIMELIMIT:
                
                return 10;
                break;
            default:
                break;
        }
        
        return 0;
    }
};

#endif