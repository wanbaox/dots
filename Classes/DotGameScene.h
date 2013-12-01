#ifndef __DOTGAME_SCENE_H__
#define __DOTGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class DotGameScene : public cocos2d::CCLayer
{
    
    CCLabelTTF * label_gametype_0;
    CCLabelTTF * label_gametype_00;
    CCLabelTTF * label_gametype_1;
    CCLabelTTF * label_gametype_11;
    CCLabelTTF * label_gametype_2;
    CCLabelTTF * label_gametype_22;
    
    //游戏类别菜单
    CCMenuItemImage * m_gameType0;
    CCMenuItemImage * m_gameType1;
    CCMenuItemImage * m_gameType2;
    
    //显示隐藏多余菜单按钮
    CCMenuItemLabel * m_moreMenus;
    
    CCMenuItemImage * m_playnow;
    CCMenuItemLabel * m_multiplayer;
    CCMenuItemLabel * m_highscore;
    CCMenuItemLabel * m_settings;
    CCMenuItemLabel * m_aboutus;
    
    bool isAllMenuShowed = false;
    
    //屏幕尺寸
    CCSize visibleSize;
    CCPoint origin;
    
public:
    
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    virtual void onEnter();
    
    CREATE_FUNC(DotGameScene);
    
    
    // selector callback
    void menuGameType0Callback(CCObject* pSender);
    void menuGameType1Callback(CCObject* pSender);
    void menuGameType2Callback(CCObject* pSender);
    
    void menuPlayNowCallback(CCObject* pSender);
    void menuMultiPlayerCallback(CCObject* pSender);
    void menuHighScoreCallback(CCObject* pSender);
    void menuSettingCallback(CCObject* pSender);
    void menuAboutUsCallback(CCObject* pSender);
    
    void menuShowMoreMenuCallback(CCObject* pSender);
    
    void showAllMenus(bool showAllMenus);
};

#endif // __DOTGAME_SCENE_H__
