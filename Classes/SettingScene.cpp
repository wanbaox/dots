#include "SettingScene.h"
#include "CCLocalizedString.h"
#include "DotGameScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

USING_NS_CC;

float during = 0.4f;
int paddingTitleWithContent = 20;
float topHeight = 75.0f;

//int padding4Items = 60;

SettingScene::SettingScene()
{
    
}

SettingScene::~SettingScene()
{
    
}

CCScene* SettingScene::scene()
{
    
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SettingScene *layer = SettingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
    
}

bool SettingScene::init()
{
    
    if (!CCLayerColor::initWithColor(Color_Bg))
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    m_menuBack = CCMenuItemImage::create(SettingHelper::isDarkTheme()?"btn_back_white.png":"btn_back.png", SettingHelper::isDarkTheme()?"btn_back.png":"btn_back_white.png", SettingHelper::isDarkTheme()?"btn_back_white.png":"btn_back.png",this, menu_selector(SettingScene::menuBackCallback));
    
    //dark theme
    CCLabelTTF * darkThemeON = CCLabelTTF::create(CCLocalizedString("open", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    darkThemeON->setColor(ccc3(247, 142, 33));
    CCMenuItemLabel *themeitem1 = CCMenuItemLabel::create(darkThemeON,this, NULL);
    CCLabelTTF * darkThemeOff =CCLabelTTF::create(CCLocalizedString("close", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    darkThemeOff->setColor(ccc3(247, 142, 33));
    CCMenuItemLabel *themeitem2 = CCMenuItemLabel::create(darkThemeOff,this, NULL);
    m_menuDarkTheme = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingScene::menuThemeCallback), themeitem1, themeitem2, NULL);
    
    m_menuDarkTheme->setSelectedIndex(SettingHelper::isDarkTheme()?0:1);
    
    //声音
    CCLabelTTF * audioON = CCLabelTTF::create(CCLocalizedString("open", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    audioON->setColor(ccc3(247, 142, 33));
    CCMenuItemLabel *item1 = CCMenuItemLabel::create(audioON,this, NULL);
    CCLabelTTF * audioOff =CCLabelTTF::create(CCLocalizedString("close", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    audioOff->setColor(ccc3(247, 142, 33));
    CCMenuItemLabel *item2 = CCMenuItemLabel::create(audioOff,this,NULL);
    m_menuAudio = CCMenuItemToggle::createWithTarget(this,  menu_selector(SettingScene::menuAudioCallback), item1, item2, NULL);
    
    m_menuAudio->setSelectedIndex(SettingHelper::isAudioOn()?0:1);
    
    //clear
    CCLabelTTF * clear = CCLabelTTF::create(CCLocalizedString("clear", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    clear->setColor(ccc3(247, 142, 33));
    m_menuClear = CCMenuItemLabel::create(clear,this, menu_selector(SettingScene::menuClearCallback));
    
    //clear audio title
    m_labelClearTitle = CCLabelTTF::create(CCLocalizedString("clear_title", "Clear_title"),"fonts/Josefin Sans Bold.ttf",14);
    m_labelClearTitle->setColor(Color_Text);
    
    m_labelAudioTitle = CCLabelTTF::create(CCLocalizedString("audio_title", "Audio_title"),"fonts/Josefin Sans Bold.ttf",14);
    m_labelAudioTitle->setColor(Color_Text);
    
    m_labelDarkThemeTitle = CCLabelTTF::create(CCLocalizedString("dark_theme", "Audio_title"),"fonts/Josefin Sans Bold.ttf",14);
    m_labelDarkThemeTitle->setColor(Color_Text);
    
    m_labelTitle = CCLabelTTF::create(CCLocalizedString("setting", "Setting"),"fonts/Josefin Sans Bold.ttf",24);
    m_labelTitle->setColor(Color_Text);
    
    m_bgTop = CCLayerColor::create(Color_Up_Down, origin.x+visibleSize.width, (origin.y+visibleSize.height)/2);
    m_bgBottom = CCLayerColor::create(Color_Up_Down, origin.x+visibleSize.width, (origin.y+visibleSize.height)/2);
    
    m_diliver0 = CCLayerColor::create(ccc4(100, 255, 255, 255), (origin.x+visibleSize.width)*2/3, 0.5);
    m_diliver1 = CCLayerColor::create(ccc4(100, 255, 255, 255), (origin.x+visibleSize.width)*2/3, 0.5);
    m_diliver2 = CCLayerColor::create(ccc4(100, 255, 255, 255), (origin.x+visibleSize.width)*2/3, 0.5);
    
    CCMenu *menu = CCMenu::create(m_menuBack, m_menuClear, m_menuAudio, m_menuDarkTheme, NULL);
    menu->setPosition(ccp(0,0));
    
    this->addChild(m_bgBottom);
    this->addChild(m_bgTop);
    this->addChild(m_labelAudioTitle);
    this->addChild(m_labelClearTitle);
    this->addChild(menu);
    this->addChild(m_labelTitle);
    this->addChild(m_labelDarkThemeTitle);
    this->addChild(m_diliver0);
    this->addChild(m_diliver1);
    this->addChild(m_diliver2);

    return true;
}

void SettingScene::onEnter()
{
    
    CCLayer::onEnter();
    
    moveIn();
    
}


void SettingScene::moveIn()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    m_labelTitle->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_labelTitle->setAnchorPoint(ccp(0.5f, 0));
    m_labelTitle->setPosition(ccp((origin.x+visibleSize.width)/2, origin.y+visibleSize.height));
    
    m_bgTop->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_bgTop->setAnchorPoint(ccp(0.5f, 0));
    m_bgTop->setPosition(ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    
    m_bgBottom->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_bgBottom->setAnchorPoint(ccp(0.5f, 1));
    m_bgBottom->setPosition(ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    
    m_menuBack->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_menuBack->setAnchorPoint(ccp(0.5f, 0.5f));
    m_menuBack->setPosition(ccp(-m_menuBack->getContentSize().width/2, origin.y+visibleSize.height-topHeight/2));
    
    
    int sumOfAllItemHeight = m_labelAudioTitle->getContentSize().height+m_labelClearTitle->getContentSize().height+m_labelDarkThemeTitle->getContentSize().height+m_menuDarkTheme->getContentSize().height+m_menuAudio->getContentSize().height+m_menuClear->getContentSize().height;
    
    
    
    
    
    paddingTitleWithContent = 0;
    int padding4Items = (origin.y+visibleSize.height-2*topHeight-sumOfAllItemHeight-3*paddingTitleWithContent)/6;
    
    CCLOG("padding4Items:%i",padding4Items);
    m_labelAudioTitle->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_labelAudioTitle->setAnchorPoint(ccp(0.5f, 1));
    m_labelAudioTitle->setPosition(ccp(origin.x+visibleSize.width+m_labelAudioTitle->getContentSize().width/2, (origin.y+visibleSize.height)-topHeight-padding4Items));
    
    
    
    m_menuAudio->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_menuAudio->setAnchorPoint(ccp(0.5f, 1));
    m_menuAudio->setPosition(ccp(origin.x+visibleSize.width+m_menuAudio->getContentSize().width/2, m_labelAudioTitle->getPosition().y-m_labelAudioTitle->getContentSize().height-paddingTitleWithContent));
    
    
    m_diliver0->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_diliver0->setAnchorPoint(ccp(0.5f, 1));
    m_diliver0->setPosition(ccp(origin.x+visibleSize.width+m_diliver0->getContentSize().width/2, m_menuAudio->getPosition().y-m_menuAudio->getContentSize().height-padding4Items));
    
    m_labelClearTitle->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_labelClearTitle->setAnchorPoint(ccp(0.5f, 1));
    m_labelClearTitle->setPosition(ccp(origin.x+visibleSize.width+m_labelClearTitle->getContentSize().width/2, m_diliver0->getPosition().y-m_diliver0->getContentSize().height-padding4Items));

    
    m_menuClear->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_menuClear->setAnchorPoint(ccp(0.5f, 1));
    m_menuClear->setPosition(ccp(origin.x+visibleSize.width+m_menuClear->getContentSize().width/2, m_labelClearTitle->getPosition().y-m_labelClearTitle->getContentSize().height-paddingTitleWithContent));
    
    m_diliver1->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_diliver1->setAnchorPoint(ccp(0.5f, 1));
    m_diliver1->setPosition(ccp(origin.x+visibleSize.width+m_diliver1->getContentSize().width/2, m_menuClear->getPosition().y-m_menuClear->getContentSize().height-padding4Items));
    
    m_labelDarkThemeTitle->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_labelDarkThemeTitle->setAnchorPoint(ccp(0.5f, 1));
    m_labelDarkThemeTitle->setPosition(ccp(origin.x+visibleSize.width+m_labelDarkThemeTitle->getContentSize().width/2, m_diliver1->getPosition().y-m_diliver1->getContentSize().height-padding4Items));
    
    m_menuDarkTheme->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_menuDarkTheme->setAnchorPoint(ccp(0.5f, 1));
    m_menuDarkTheme->setPosition(ccp(origin.x+visibleSize.width+m_menuDarkTheme->getContentSize().width/2, m_labelDarkThemeTitle->getPosition().y-m_labelDarkThemeTitle->getContentSize().height-paddingTitleWithContent));
    
    m_diliver2->ignoreAnchorPointForPosition(false);//cclayer设置anchor之前必须要先调用这个
    m_diliver2->setAnchorPoint(ccp(0.5f, 1));
    m_diliver2->setPosition(ccp(origin.x+visibleSize.width+m_diliver2->getContentSize().width/2, m_menuDarkTheme->getPosition().y-m_menuDarkTheme->getContentSize().height-padding4Items));
    
    //m_labelTitle
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(0, -topHeight/2-m_labelTitle->getContentSize().height/2));
        
        m_labelTitle->runAction(CCEaseBackOut::create(moveBy));
    }
    
    //m_bgtop/m_btbottom
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(0,(origin.y+visibleSize.height)/2-topHeight));
        m_bgTop->runAction(CCEaseSineOut::create(CCEaseBackOut::create(moveBy)));
        
        CCMoveBy * moveBy1 = CCMoveBy::create(during, ccp(0,-(origin.y+visibleSize.height)/2+topHeight));
        m_bgBottom->runAction(CCEaseSineOut::create(CCEaseBackOut::create(moveBy1)));
    }
    
    //m_menuBack
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(paddingTitleWithContent/2+m_menuBack->getContentSize().width,0));
        
        m_menuBack->runAction(CCEaseSineOut::create(moveBy));
        
    }
    
    //menu
    {
        
        CCMoveBy * moveBy0 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelAudioTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy1 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelClearTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy2 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuAudio->getContentSize().width/2, 0));
        CCMoveBy * moveBy3 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuClear->getContentSize().width/2, 0));
        
        CCSequence * sequence0 = CCSequence::create(CCDelayTime::create(0.1),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy0))),NULL);
        CCSequence * sequence1 = CCSequence::create(CCDelayTime::create(0.15),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy1))),NULL);
        CCSequence * sequence2 = CCSequence::create(CCDelayTime::create(0.1),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy2))),NULL);
        CCSequence * sequence3 = CCSequence::create(CCDelayTime::create(0.15),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy3))),NULL);
        
        m_labelAudioTitle->runAction(sequence0);
        m_labelClearTitle->runAction(sequence1);
        m_menuAudio->runAction(sequence2);
        m_menuClear->runAction(sequence3);
        
        
        
        CCMoveBy * moveBy4 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelDarkThemeTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy5 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuDarkTheme->getContentSize().width/2, 0));
        CCSequence * sequence4 = CCSequence::create(CCDelayTime::create(0.2),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy4))),NULL);
        CCSequence * sequence5 = CCSequence::create(CCDelayTime::create(0.2),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy5))),NULL);
        
        m_labelDarkThemeTitle->runAction(sequence4);
        m_menuDarkTheme->runAction(sequence5);
        
        
        
        CCMoveBy * moveBy6 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver0->getContentSize().width/2, 0));
        CCMoveBy * moveBy7 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver1->getContentSize().width/2, 0));
        CCMoveBy * moveBy8 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver2->getContentSize().width/2, 0));
        CCSequence * sequence6 = CCSequence::create(CCDelayTime::create(0.1),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy6))),NULL);
        CCSequence * sequence7 = CCSequence::create(CCDelayTime::create(0.15),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy7))),NULL);
        CCSequence * sequence8 = CCSequence::create(CCDelayTime::create(0.15),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy8))),NULL);
        
        m_diliver0->runAction(sequence6);
        m_diliver1->runAction(sequence7);
        m_diliver2->runAction(sequence8);
        
    }
}

void SettingScene::moveOut()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //m_labelTitle
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(0, -topHeight/2-m_labelTitle->getContentSize().height/2));
        
        m_labelTitle->runAction(CCEaseBackIn::create(moveBy->reverse()));
    }
    
    //m_bgtop/m_btbottom
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(0,(origin.y+visibleSize.height)/2-topHeight));
        CCSequence * se0 = CCSequence::create(CCDelayTime::create(0.1),(CCEaseSineOut::create(CCEaseBackIn::create(moveBy->reverse()))),NULL);
        m_bgTop->runAction(se0);
        
        CCMoveBy * moveBy1 = CCMoveBy::create(during, ccp(0,-(origin.y+visibleSize.height)/2+topHeight));
        CCSequence * se1 = CCSequence::create(CCDelayTime::create(0.1),(CCEaseSineOut::create(CCEaseBackIn::create(moveBy1->reverse()))),NULL);
        m_bgBottom->runAction(se1);
    }
    
    //m_menuBack
    {
        
        CCMoveBy * moveBy = CCMoveBy::create(during, ccp(paddingTitleWithContent+m_menuBack->getContentSize().width,0));
        
        m_menuBack->runAction(CCEaseSineOut::create(moveBy->reverse()));
        
    }
    
    //menu
    {
        
        CCMoveBy * moveBy0 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelAudioTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy1 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelClearTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy2 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuAudio->getContentSize().width/2, 0));
        CCMoveBy * moveBy3 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuClear->getContentSize().width/2, 0));
        
        CCSequence * sequence0 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy0->reverse()))),NULL);
        CCSequence * sequence1 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy1->reverse()))),NULL);
        CCSequence * sequence2 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy2->reverse()))),NULL);
        CCSequence * sequence3 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy3->reverse()))),NULL);
        
        m_labelAudioTitle->runAction(sequence0);
        m_labelClearTitle->runAction(sequence1);
        m_menuAudio->runAction(sequence2);
        m_menuClear->runAction(sequence3);
        
        
        
        CCMoveBy * moveBy4 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_labelDarkThemeTitle->getContentSize().width/2, 0));
        CCMoveBy * moveBy5 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_menuDarkTheme->getContentSize().width/2, 0));
        CCSequence * sequence4 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy4->reverse()))),NULL);
        CCSequence * sequence5 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy5->reverse()))),NULL);
        
        m_labelDarkThemeTitle->runAction(sequence4);
        m_menuDarkTheme->runAction(sequence5);
        
        
        
        CCMoveBy * moveBy6 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver0->getContentSize().width/2, 0));
        CCMoveBy * moveBy7 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver1->getContentSize().width/2, 0));
        CCMoveBy * moveBy8 = CCMoveBy::create(during, ccp(-(origin.x+visibleSize.width)/2-m_diliver2->getContentSize().width/2, 0));
        CCSequence * sequence6 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy6->reverse()))),NULL);
        CCSequence * sequence7 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy7->reverse()))),NULL);
        CCSequence * sequence8 = CCSequence::create(CCDelayTime::create(0),(CCEaseSineOut::create(CCEaseBackOut::create(moveBy8)->reverse())),NULL);
        
        m_diliver0->runAction(sequence6);
        m_diliver1->runAction(sequence7);
        m_diliver2->runAction(sequence8);
        
    }
    
    this->scheduleOnce(schedule_selector(SettingScene::moveOutSchedule), during);
    

}

void SettingScene::moveOutSchedule()
{
    
    CCScene *pScene = DotGameScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void SettingScene::menuClearCallback(CCObject* pSender)
{
    
    CCLabelTTF *label = CCLabelTTF::create(CCLocalizedString("cleared", "Menu"),"fonts/Josefin Sans Bold.ttf",30);
    label->setColor(ccc3(247, 142, 33));
    m_menuClear->setLabel(label);
    
    AudioHelper::playButtonPress();
    
    SettingHelper::setToppestScore4Classic(0);
    SettingHelper::setToppestScore4Tap(0);
    SettingHelper::setToppestScore4ClassicLevel(0);
    SettingHelper::setToppestScore4TapLevel(0);
    SettingHelper::setToppestScore4NoLimit(0);
}

void SettingScene::menuAudioCallback(CCObject* pSender)
{
    
    AudioHelper::playButtonPress();
    
    SettingHelper::setAudio(((CCMenuItemToggle*)pSender)->getSelectedIndex()==0?true:false);
}

void SettingScene::menuBackCallback(CCObject* pSender)
{
    
    AudioHelper::playButtonPress();
    
    moveOut();
}

void SettingScene::menuThemeCallback(CCObject* pSender)
{
    AudioHelper::playButtonPress();
    
    SettingHelper::setDarkTheme(((CCMenuItemToggle*)pSender)->getSelectedIndex()==0?true:false);
    
    themeChanged();
}

void SettingScene::themeChanged()
{

    this->setColor(Color_Bg3B);
    m_bgTop->setColor(Color_Up_Down3B);
    m_bgBottom->setColor(Color_Up_Down3B);
    
    m_labelTitle->setColor(Color_Text);
    m_labelClearTitle->setColor(Color_Text);
    m_labelAudioTitle->setColor(Color_Text);
    m_labelDarkThemeTitle->setColor(Color_Text);
    

    if (m_menuBack->isSelected()) {
        
        m_menuBack->unselected();
    }else{
        
        m_menuBack->selected();
    }
}


