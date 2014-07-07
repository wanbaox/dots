#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class SettingScene : public cocos2d::CCLayerColor
{
    
    
    CCLayerColor * m_bgTop;
    CCLayerColor * m_bgBottom;
    
    CCLabelTTF * m_labelTitle;
    CCMenuItemImage * m_menuBack;
    CCMenuItemLabel * m_menuClear;
    CCMenuItemToggle * m_menuAudio;
    CCMenuItemToggle * m_menuDarkTheme;
    CCLabelTTF * m_labelClearTitle;
    CCLabelTTF * m_labelAudioTitle;
    CCLabelTTF * m_labelDarkThemeTitle;
    
    CCLayerColor * m_diliver0;
    CCLayerColor * m_diliver1;
    CCLayerColor * m_diliver2;

    
public:
    
    SettingScene();
	~SettingScene();
    
    virtual bool init();  

    void onEnter();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(SettingScene);
    
    void moveIn();
    void moveOut();
    void moveOutSchedule();
    
    void themeChanged();
    
    //manu callback
    void menuBackCallback(CCObject* pSender);
    
    void menuAudioCallback(CCObject* pSender);
    
    void menuThemeCallback(CCObject* pSender);
    
    void menuClearCallback(CCObject* pSender);
};

#endif // __SETTING_SCENE_H__
