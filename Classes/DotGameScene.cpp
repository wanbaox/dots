#include "DotGameScene.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "CCLocalizedString.h"
#include "SimpleAudioEngine.h"
#include "AudioHelper.h"
#include "SettingScene.h"
#include "CCGrade.h"
#include "CCGrade.h"
#include "CCiAd.h"

#define GameTypeMneuY 180
#define MenuHideMoveDistance -280

int m_totalX;
int m_totalY;

float m_duringTime = 0.4;

float animDuring_game_type=0.4;


CCScene* DotGameScene::scene()
{
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DotGameScene *layer = DotGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DotGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(Color_Bg))
    {
        return false;
    }
    
    isAllMenuShowed = false;
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    //菜单
    
    //游戏类别选择
    
    
    m_gameType0 = CCMenuItemImage::create("game_type0.png", SettingHelper::isDarkTheme()?"game_type0_selected_white.png":"game_type0_selected.png", SettingHelper::isDarkTheme()?"game_type0_selected_white.png":"game_type0_selected.png",this, menu_selector(DotGameScene::menuGameType0Callback));
    
    m_gameType1 = CCMenuItemImage::create("game_type1.png", SettingHelper::isDarkTheme()?"game_type1_selected_white.png":"game_type1_selected.png", SettingHelper::isDarkTheme()?"game_type1_selected_white.png":"game_type1_selected.png",this, menu_selector(DotGameScene::menuGameType1Callback));
    
    m_gameType2 = CCMenuItemImage::create("game_type2.png", SettingHelper::isDarkTheme()?"game_type2_selected_white.png":"game_type2_selected.png", SettingHelper::isDarkTheme()?"game_type2_selected_white.png":"game_type2_selected.png",this, menu_selector(DotGameScene::menuGameType2Callback));
    
    //显示隐藏其余菜单
    m_moreMenus = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_show_menu", "Menu"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuShowMoreMenuCallback));
    
    
    m_playnow = CCMenuItemImage::create(CCLocalizedString("pic_play_now", ""), CCLocalizedString("pic_play_now_select", ""), CCLocalizedString("pic_play_now_select", ""),this, menu_selector(DotGameScene::menuPlayNowCallback));
    
    m_multiplayer = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_multiplayer", "Multiplayer"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuContinueCallback));
    
    m_highscore = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_scores", "Scores & Trophies"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuHighScoreCallback));
    
    m_settings = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_setting", "Setting"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuSettingCallback));
    
    m_aboutus = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_about", "About"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuAboutUsCallback));
    
    m_exit = CCMenuItemLabel::create(CCLabelTTF::create(CCLocalizedString("menu_exit", "exit"),"fonts/Josefin Sans Bold.ttf",18),this, menu_selector(DotGameScene::menuExitCallback));
    
    m_gameType1->setPosition(ccp((origin.x+visibleSize.width)*1/2, GameTypeMneuY+MenuHideMoveDistance));
    m_gameType0->setPosition(ccp(m_gameType1->getPosition().x-45, GameTypeMneuY+MenuHideMoveDistance));
    m_gameType2->setPosition(ccp(m_gameType1->getPosition().x+45, GameTypeMneuY+MenuHideMoveDistance));
    
    m_playnow->setPosition(ccp((origin.x+visibleSize.width)/2, m_gameType0->getPosition().y-m_gameType0->getContentSize().height-menuPadding));
    m_moreMenus->setPosition(ccp((origin.x+visibleSize.width)/2, 2*menuPadding+MenuHideMoveDistance));
    
    m_multiplayer->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_highscore->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_settings->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_aboutus->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_exit->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    
    m_multiplayer->setColor(Color_Text);
    m_highscore->setColor(Color_Text);
    m_settings->setColor(Color_Text);
    m_aboutus->setColor(Color_Text);
    m_exit->setColor(Color_Text);
    m_moreMenus->setColor(Color_Text);
    
    
    CCMenu *menu = CCMenu::create(m_gameType0, m_gameType1, m_gameType2, m_playnow, m_multiplayer, m_moreMenus, m_highscore, m_settings, m_aboutus, m_exit, NULL);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    m_exit->setVisible(false);
#endif
    
    menu->setPosition(ccp(0,0));
    
    this->addChild(menu, 1);
    
    this->setGameType();
    
    //logo
    logo = CCSprite::create("main_logo.png");
    logo->setPosition(ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)*3/4-MenuHideMoveDistance));
    this->addChild(logo);
    
    this->animInitMenuAndLogo();
    
    
//    CCiAd::addAdFullScreen();
    
    return true;
    
}
void DotGameScene::animInitMenuAndLogo()
{
    
    //logo
    CCEaseBackOut * actionlogo = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)*3/4)));
    logo->runAction(actionlogo);
    
    //游戏类别
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(m_gameType1->getPosition().x-45, GameTypeMneuY)));
    m_gameType0->runAction(action);
    
    CCEaseBackOut * action1 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)*2/4, GameTypeMneuY)));
    m_gameType1->runAction(action1);
    
    CCEaseBackOut * action2 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(m_gameType1->getPosition().x+45, GameTypeMneuY)));
    m_gameType2->runAction(action2);
    
    
    //开始游戏
    CCEaseBackOut * action3 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, GameTypeMneuY-m_gameType2->getContentSize().height-menuPadding)));
    m_playnow->runAction(action3);
    
    //more
    CCEaseBackOut * action4 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, 2*menuPadding)));
    m_moreMenus->runAction(action4);
    
    //游戏类别
    {
        switch (SettingHelper::getGameType()) {
            case GAME_TYPE_CLASSIC:
            {
            
                if (label_gametype_0==NULL) {
                    
                    label_gametype_0 = CCLabelTTF::create(CCLocalizedString("game_type_classic_title", "Classic"),"fonts/Josefin Sans Bold.ttf",18);
                    label_gametype_0->setColor(Color_Text);
                    this->addChild(label_gametype_0);
                    
                    label_gametype_00 = CCLabelTTF::create(CCLocalizedString("game_type_classic_msg", "60 Seconds"),"fonts/Josefin Sans Bold.ttf",14);
                    label_gametype_00->setColor(Color_Text);
                    this->addChild(label_gametype_00);
                }
                
                label_gametype_0->stopAllActions();
                label_gametype_0->setPosition(ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height));
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                label_gametype_0->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_00->stopAllActions();
                label_gametype_00->setPosition(ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2));
                CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
                label_gametype_00->runAction(CCSequence::create(CCFadeIn::create(0),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                break;
            }
            case GAME_TYPE_CLASSIC_LEVEL:
            {
                
                if (label_gametype_0==NULL) {
                    
                    label_gametype_0 = CCLabelTTF::create(CCLocalizedString("game_type_classic_level_title", "Classic"),"fonts/Josefin Sans Bold.ttf",18);
                    label_gametype_0->setColor(Color_Text);
                    this->addChild(label_gametype_0);
                    
                    label_gametype_00 = CCLabelTTF::create(CCLocalizedString("game_type_classic_level_msg", "60 Seconds"),"fonts/Josefin Sans Bold.ttf",14);
                    label_gametype_00->setColor(Color_Text);
                    this->addChild(label_gametype_00);
                }
                
                label_gametype_0->stopAllActions();
                label_gametype_0->setPosition(ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height));
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                label_gametype_0->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_00->stopAllActions();
                label_gametype_00->setPosition(ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2));
                CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
                label_gametype_00->runAction(CCSequence::create(CCFadeIn::create(0),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                break;
            }
            case GAME_TYPE_SPEED:
            {
            
                if (label_gametype_1==NULL) {
                    
                    label_gametype_1 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_title", "Speed"),"fonts/Josefin Sans Bold.ttf",18);
                    label_gametype_1->setColor(Color_Text);
                    this->addChild(label_gametype_1);
                    
                    label_gametype_11 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_msg", "60 seconds"),"fonts/Josefin Sans Bold.ttf",14);
                    label_gametype_11->setColor(Color_Text);
                    this->addChild(label_gametype_11);
                }
                
                label_gametype_1->stopAllActions();
                CCPoint pos = ccp(-label_gametype_1->getContentSize().width,(origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height);
                label_gametype_1->setPosition(pos);
                
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                label_gametype_1->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_11->stopAllActions();
                
                CCPoint pos11 = ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2);
                
                label_gametype_11->setPosition(pos11);
                CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
                label_gametype_11->runAction(CCSequence::create(CCFadeIn::create(0),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));

                break;
            }
            case GAME_TYPE_SPEED_LEVEL:
            {
                
                if (label_gametype_1==NULL) {
                    
                    label_gametype_1 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_level_title", "Speed"),"fonts/Josefin Sans Bold.ttf",18);
                    label_gametype_1->setColor(Color_Text);
                    this->addChild(label_gametype_1);
                    
                    label_gametype_11 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_level_msg", "60 seconds"),"fonts/Josefin Sans Bold.ttf",14);
                    label_gametype_11->setColor(Color_Text);
                    this->addChild(label_gametype_11);
                }
                
                label_gametype_1->stopAllActions();
                CCPoint pos = ccp(-label_gametype_1->getContentSize().width,(origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height);
                label_gametype_1->setPosition(pos);
                
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                label_gametype_1->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_11->stopAllActions();
                
                CCPoint pos11 = ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2);
                
                label_gametype_11->setPosition(pos11);
                CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
                label_gametype_11->runAction(CCSequence::create(CCFadeIn::create(0),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                break;
            }
            case GAME_TYPE_NOTIMELIMIT:
            {
            
                if (label_gametype_2==NULL) {
                    
                    label_gametype_2 = CCLabelTTF::create(CCLocalizedString("game_type_endless_title", "Endless"),"fonts/Josefin Sans Bold.ttf",18);
                    label_gametype_2->setColor(Color_Text);
                    this->addChild(label_gametype_2);
                    
                    label_gametype_22 = CCLabelTTF::create(CCLocalizedString("game_type_endless_msg", "no time limit"),"fonts/Josefin Sans Bold.ttf",14);
                    label_gametype_22->setColor(Color_Text);
                    this->addChild(label_gametype_22);
                }
                
                
                label_gametype_2->stopAllActions();
                label_gametype_2->setPosition(ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height));
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
                label_gametype_2->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_22->stopAllActions();
                label_gametype_22->setPosition(ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2));
                CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
                label_gametype_22->runAction(CCSequence::create(CCFadeIn::create(0),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                break;
            }
                
            default:
                break;
        }
        
    }
    
}

void DotGameScene::setGameType()
{

    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC:
        {
            
            m_gameType0->selected();
            m_gameType1->unselected();
            m_gameType2->unselected();
            break;
        }
        case GAME_TYPE_CLASSIC_LEVEL:
        {
            m_gameType0->selected();
            m_gameType1->unselected();
            m_gameType2->unselected();
            break;
        }
        case GAME_TYPE_SPEED:
        {
            
            m_gameType0->unselected();
            m_gameType1->selected();
            m_gameType2->unselected();
            break;
        }
        case GAME_TYPE_SPEED_LEVEL:
        {
            
            m_gameType0->unselected();
            m_gameType1->selected();
            m_gameType2->unselected();
            break;
        }
        case GAME_TYPE_NOTIMELIMIT:
        {
            
            m_gameType0->unselected();
            m_gameType1->unselected();
            m_gameType2->selected();
            break;
        }
        default:
            break;
    }
}
void DotGameScene::menuGameType0Callback(CCObject* pSender)
{
    AudioHelper::playMenuPress();
    AudioHelper::playGameTypeSwitch();
    
    
    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_0==NULL) {
       
        label_gametype_0 = CCLabelTTF::create(CCLocalizedString("game_type_classic_title", "Classic"),"fonts/Josefin Sans Bold.ttf",18);
        label_gametype_0->setColor(Color_Text);
        this->addChild(label_gametype_0);
        
        label_gametype_00 = CCLabelTTF::create(CCLocalizedString("game_type_classic_msg", "60 Seconds"),"fonts/Josefin Sans Bold.ttf",14);
        label_gametype_00->setColor(Color_Text);
        this->addChild(label_gametype_00);
    }
    
    label_gametype_0->stopAllActions();
    label_gametype_0->setPosition(ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height));
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
    label_gametype_0->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    label_gametype_00->stopAllActions();
    label_gametype_00->setPosition(ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2));
    CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
    label_gametype_00->runAction(CCSequence::create(CCFadeIn::create(0),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    if (SettingHelper::getGameType()==GAME_TYPE_SPEED || SettingHelper::getGameType()==GAME_TYPE_SPEED_LEVEL) {
        
        label_gametype_0->setString(CCLocalizedString("game_type_classic_title", "Classic"));
        
        label_gametype_00->setString(CCLocalizedString("game_type_classic_msg", "Classic"));
        
        if (label_gametype_1!=NULL) {
            
            label_gametype_1->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
            label_gametype_1->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_11->stopAllActions();
            CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_11->runAction(CCSequence::create(CCDelayTime::create(0.1),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
        
        SettingHelper::setGameType(GAME_TYPE_CLASSIC);
    }else if(SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT){
        
        label_gametype_0->setString(CCLocalizedString("game_type_classic_title", "Classic"));
        
        label_gametype_00->setString(CCLocalizedString("game_type_classic_msg", "Classic"));
        
        if (label_gametype_2!=NULL) {
            
            label_gametype_2->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
            label_gametype_2->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_22->stopAllActions();
            CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_22->runAction(CCSequence::create(CCDelayTime::create(0.1),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
        
        SettingHelper::setGameType(GAME_TYPE_CLASSIC);
    }else if(SettingHelper::getGameType()==GAME_TYPE_CLASSIC){
        
        
        label_gametype_0->setString(CCLocalizedString("game_type_classic_level_title", "Classic"));
        
        label_gametype_00->setString(CCLocalizedString("game_type_classic_level_msg", "Classic"));
        
        SettingHelper::setGameType(GAME_TYPE_CLASSIC_LEVEL);
    }else if(SettingHelper::getGameType()==GAME_TYPE_CLASSIC_LEVEL){
        
        
        label_gametype_0->setString(CCLocalizedString("game_type_classic_title", "Classic"));
        
        label_gametype_00->setString(CCLocalizedString("game_type_classic_msg", "Classic"));
        
        SettingHelper::setGameType(GAME_TYPE_CLASSIC);
    }
    
    
    this->setGameType();
}

void DotGameScene::menuGameType1Callback(CCObject* pSender)
{
    
    AudioHelper::playMenuPress();
    AudioHelper::playGameTypeSwitch();
    
    
    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_1==NULL) {
        
        label_gametype_1 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_title", "Speed"),"fonts/Josefin Sans Bold.ttf",18);
        label_gametype_1->setColor(Color_Text);
        this->addChild(label_gametype_1);
        
        label_gametype_11 = CCLabelTTF::create(CCLocalizedString("game_type_one_tap_msg", "60 seconds"),"fonts/Josefin Sans Bold.ttf",14);
        label_gametype_11->setColor(Color_Text);
        this->addChild(label_gametype_11);
    }
    
    label_gametype_1->stopAllActions();
    CCPoint pos = ccp(SettingHelper::getGameType()!=GAME_TYPE_NOTIMELIMIT?(origin.x+visibleSize.width+label_gametype_1->getContentSize().width):(-label_gametype_1->getContentSize().width),(origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height);
    label_gametype_1->setPosition(pos);
    
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
    label_gametype_1->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    label_gametype_11->stopAllActions();
    
    CCPoint pos11 = ccp(SettingHelper::getGameType()!=GAME_TYPE_NOTIMELIMIT?(origin.x+visibleSize.width+label_gametype_1->getContentSize().width):(-label_gametype_1->getContentSize().width), (origin.y+visibleSize.height)/2);
    
    label_gametype_11->setPosition(pos11);
    CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
    label_gametype_11->runAction(CCSequence::create(CCFadeIn::create(0),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    if (SettingHelper::getGameType()==GAME_TYPE_CLASSIC || SettingHelper::getGameType()==GAME_TYPE_CLASSIC_LEVEL) {
        
        label_gametype_1->setString(CCLocalizedString("game_type_one_tap_title", "Classic"));
        
        label_gametype_11->setString(CCLocalizedString("game_type_one_tap_msg", "Classic"));
        
        if (label_gametype_0!=NULL) {
            
            label_gametype_0->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
            label_gametype_0->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_00->stopAllActions();
            CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_00->runAction(CCSequence::create(CCDelayTime::create(0.1),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
        
        SettingHelper::setGameType(GAME_TYPE_SPEED);
    }else if(SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT){
        
        label_gametype_1->setString(CCLocalizedString("game_type_one_tap_title", "Classic"));
        
        label_gametype_11->setString(CCLocalizedString("game_type_one_tap_msg", "Classic"));
        
        if (label_gametype_2!=NULL) {
            
            label_gametype_2->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
            label_gametype_2->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_22->stopAllActions();
            CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_22->runAction(CCSequence::create(CCDelayTime::create(0.1),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
        
        SettingHelper::setGameType(GAME_TYPE_SPEED);
    }else if(SettingHelper::getGameType()==GAME_TYPE_SPEED){
        
        label_gametype_1->setString(CCLocalizedString("game_type_one_tap_level_title", "Classic"));
        
        label_gametype_11->setString(CCLocalizedString("game_type_one_tap_level_msg", "Classic"));
        
        SettingHelper::setGameType(GAME_TYPE_SPEED_LEVEL);
    }else if(SettingHelper::getGameType()==GAME_TYPE_SPEED_LEVEL){
        
        label_gametype_1->setString(CCLocalizedString("game_type_one_tap_title", "Classic"));
        
        label_gametype_11->setString(CCLocalizedString("game_type_one_tap_msg", "Classic"));
        
        SettingHelper::setGameType(GAME_TYPE_SPEED);
    }
    
    this->setGameType();
}

void DotGameScene::menuGameType2Callback(CCObject* pSender)
{
    
    AudioHelper::playMenuPress();
    AudioHelper::playGameTypeSwitch();
    
    
    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_2==NULL) {
        
        label_gametype_2 = CCLabelTTF::create(CCLocalizedString("game_type_endless_title", "Endless"),"fonts/Josefin Sans Bold.ttf",18);
        label_gametype_2->setColor(Color_Text);
        this->addChild(label_gametype_2);
        
        label_gametype_22 = CCLabelTTF::create(CCLocalizedString("game_type_endless_msg", "no time limit"),"fonts/Josefin Sans Bold.ttf",14);
        label_gametype_22->setColor(Color_Text);
        this->addChild(label_gametype_22);
    }
    
    
    label_gametype_2->stopAllActions();
    label_gametype_2->setPosition(ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height));
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
    label_gametype_2->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    label_gametype_22->stopAllActions();
    label_gametype_22->setPosition(ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2));
    CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
    label_gametype_22->runAction(CCSequence::create(CCFadeIn::create(0),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    
    if (SettingHelper::getGameType()==GAME_TYPE_CLASSIC || SettingHelper::getGameType()==GAME_TYPE_CLASSIC_LEVEL) {
        
        if (label_gametype_0!=NULL) {
            
            label_gametype_0->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
            label_gametype_0->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_00->stopAllActions();
            CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_00->runAction(CCSequence::create(CCDelayTime::create(0.1),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
    }else if(SettingHelper::getGameType()==GAME_TYPE_SPEED || SettingHelper::getGameType()==GAME_TYPE_SPEED_LEVEL){
    
        if (label_gametype_1!=NULL) {
            
            label_gametype_1->stopAllActions();
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
            label_gametype_1->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_11->stopAllActions();
            CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
            label_gametype_11->runAction(CCSequence::create(CCDelayTime::create(0.1),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
        }
    }else if(SettingHelper::getGameType()==GAME_TYPE_NOTIMELIMIT){
        
    }
    
    SettingHelper::setGameType(GAME_TYPE_NOTIMELIMIT);
    this->setGameType();
}

void DotGameScene::hideAllItems()
{

    AudioHelper::playMenuPress();
    
    
    SettingHelper::clearData4NewGame();
    
    if (label_gametype_0!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
        label_gametype_0->runAction(action);
        
    }
    if (label_gametype_00!=NULL) {
        
        CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
        label_gametype_00->runAction(action00);
    }
    if (label_gametype_1!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
        label_gametype_1->runAction(action);
        
        
    }
    if (label_gametype_11!=NULL) {
        
        CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
        label_gametype_11->runAction(action11);
        
    }
    if (label_gametype_2!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
        label_gametype_2->runAction(action);
        
        
    }
    if (label_gametype_22!=NULL) {
        
        CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
        label_gametype_22->runAction(action22);
    }
    
    if (m_gameType0!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_gameType0->runAction(action);
    }
    if (m_gameType1!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_gameType1->runAction(action);
    }
    if (m_gameType2!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_gameType2->runAction(action);
    }
    
    if (m_moreMenus!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_moreMenus->runAction(action);
    }
    if (m_playnow!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_playnow->runAction(action);
    }
    if (m_multiplayer!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_multiplayer->runAction(action);
    }
    if (m_highscore!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_highscore->runAction(action);
    }
    if (m_settings!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_settings->runAction(action);
    }
    if (m_aboutus!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_aboutus->runAction(action);
    }
    
    if (m_exit!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, MenuHideMoveDistance)));
        m_exit->runAction(action);
    }
    
    if (logo!=NULL) {
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveBy::create(animDuring_game_type, ccp(0, -MenuHideMoveDistance)));
        logo->runAction(action);
    }
}
void DotGameScene::menuPlayNowCallback(CCObject* pSender)
{

    
    
    hideAllItems();
    this->scheduleOnce(schedule_selector(DotGameScene::playNowSchedule), animDuring_game_type-0.1);
    
}

void DotGameScene::playNowSchedule()
{
    
    CCScene * playingScene = DotPlayingScene::scene(false);
    CCDirector::sharedDirector()->replaceScene(playingScene);
    
    
}

void DotGameScene::menuContinueCallback(CCObject* pSender)
{

    
    hideAllItems();
    
    this->scheduleOnce(schedule_selector(DotGameScene::continueSchedule), animDuring_game_type-0.1);
    
    
}

void DotGameScene::continueSchedule()
{
    
    CCScene * playingScene = DotPlayingScene::scene(true);
    CCDirector::sharedDirector()->replaceScene(playingScene);
    
    
}

void DotGameScene::menuHighScoreCallback(CCObject* pSender)
{

    CCGrade::rate();
}

void DotGameScene::menuSettingCallback(CCObject* pSender)
{
    
    hideAllItems();
    
    this->scheduleOnce(schedule_selector(DotGameScene::settingSchedule), animDuring_game_type-0.1);
    
}

void DotGameScene::settingSchedule()
{
    
    CCScene * settingScene = SettingScene::scene();
    CCDirector::sharedDirector()->replaceScene(settingScene);
    
}

void DotGameScene::menuAboutUsCallback(CCObject* pSender)
{

    CCGrade::gotoMyQQ();
}

void DotGameScene::menuExitCallback(CCObject* pSender)
{
    
    CCDirector::sharedDirector()->end();
}

void DotGameScene::showAllMenus(bool showAllMenus)
{
    
    AudioHelper::playMenuPress();
    
    
    if (showAllMenus) {
        
        //显示所有菜单
        
        CCLabelTTF *label = CCLabelTTF::create(CCLocalizedString("menu_hide_menu", "Hide Menu"),"fonts/Josefin Sans Bold.ttf",18);
        label->setColor(Color_Text);
        m_moreMenus->setLabel(label);
        
        switch (SettingHelper::getGameType()) {
            case GAME_TYPE_CLASSIC:
            {
                if (label_gametype_0!=NULL) {
                    
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                    label_gametype_0->runAction(action);
                    
                    CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_00->runAction(action00);
                }
                
                
                break;
            }
            case GAME_TYPE_CLASSIC_LEVEL:
            {
                if (label_gametype_0!=NULL) {
                    
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                    label_gametype_0->runAction(action);
                    
                    CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_00->runAction(action00);
                }
                
                
                break;
            }
            case GAME_TYPE_SPEED:
            {
                if (label_gametype_1!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                    label_gametype_1->runAction(action);
                    
                    CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_11->runAction(action11);
                }
                
                break;
            }
            case GAME_TYPE_SPEED_LEVEL:
            {
                if (label_gametype_1!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                    label_gametype_1->runAction(action);
                    
                    CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_11->runAction(action11);
                }
                
                break;
            }
            case GAME_TYPE_NOTIMELIMIT:
            {
                if (label_gametype_2!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
                    label_gametype_2->runAction(action);
                    
                    CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp(-label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_22->runAction(action22);
                }
                
                break;
            }
            default:
                break;
        }
        
        
        int heightFor = 260;
        
        //游戏类别
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp((origin.x+visibleSize.width)*1/4, 260)));
//        m_gameType0->runAction(action);
        m_gameType0->runAction(CCEaseSineOut::create(action));
        
        CCEaseBackOut * action1 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp((origin.x+visibleSize.width)*2/4, 260)));
//        m_gameType1->runAction(action1);
        m_gameType1->runAction(CCEaseSineOut::create(action1));
        
        CCEaseBackOut * action2 = CCEaseBackOut::create(CCMoveTo::create(m_duringTime, ccp((origin.x+visibleSize.width)*3/4, 260)));
//        m_gameType2->runAction(action2);
        m_gameType2->runAction(CCEaseSineOut::create(action2));
        
        //开始游戏
        CCEaseBackOut * action3 = CCEaseBackOut::create(CCMoveTo::create(0.5, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-menuPadding)));
//        m_playnow->runAction(action3);
        m_playnow->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action3),NULL));
        
        //more
        CCEaseBackOut * action4 = CCEaseBackOut::create(CCMoveTo::create(0.5, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-menuPadding*5/3-4)));
//        m_moreMenus->runAction(CCEaseSineOut::create(action4));
        m_moreMenus->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action4),NULL));
        
        m_multiplayer->setPosition(ccp((origin.x+visibleSize.width)/2, -40));
        m_highscore->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-menuPadding));
        m_settings->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-2*menuPadding));
        m_aboutus->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-3*menuPadding));
        
         m_exit->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-m_aboutus->getContentSize().height-4*menuPadding));
        
        //其他菜单
        CCEaseBackOut * action5 = CCEaseBackOut::create(CCMoveTo::create(0.55, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-3*menuPadding)));
//        m_multiplayer->runAction(CCEaseSineOut::create(action5));
        m_multiplayer->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action5),NULL));
        
        CCEaseBackOut * action6 = CCEaseBackOut::create(CCMoveTo::create(0.6, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-4*menuPadding)));
//        m_highscore->runAction(CCEaseSineOut::create(action6));
        m_highscore->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action6),NULL));
        
        CCEaseBackOut * action7 = CCEaseBackOut::create(CCMoveTo::create(0.65, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-5*menuPadding)));
//        m_settings->runAction(CCEaseSineOut::create(action7));
        m_settings->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action7),NULL));
        
        CCEaseBackOut * action8 = CCEaseBackOut::create(CCMoveTo::create(0.7, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-6*menuPadding)));
//        m_aboutus->runAction(CCEaseSineOut::create(action8));
        m_aboutus->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action8),NULL));
        
        CCEaseBackOut * action9 = CCEaseBackOut::create(CCMoveTo::create(0.7, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-m_aboutus->getContentSize().height-7*menuPadding)));
        //        m_aboutus->runAction(CCEaseSineOut::create(action8));
        m_exit->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action9),NULL));
    }else{
    
        //隐藏菜单
        CCLabelTTF *label = CCLabelTTF::create(CCLocalizedString("menu_show_menu", "Menu"),"fonts/Josefin Sans Bold.ttf",18);
        label->setColor(Color_Text);
        m_moreMenus->setLabel(label);
        
        //游戏类别
        CCEaseBackOut * action1 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)*1/2, GameTypeMneuY)));
        m_gameType1->runAction(action1);
        
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(m_gameType1->getPosition().x-45, GameTypeMneuY)));
        m_gameType0->runAction(action);
        
        CCEaseBackOut * action2 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp(m_gameType1->getPosition().x+45, GameTypeMneuY)));
        m_gameType2->runAction(action2);
        
        
        //开始游戏
        CCEaseBackOut * action3 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, GameTypeMneuY-m_gameType2->getContentSize().height-menuPadding)));
        m_playnow->runAction(action3);
        
        //more
        CCEaseBackOut * action4 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, 2*menuPadding)));
        m_moreMenus->runAction(action4);
        
        //其他菜单
        CCEaseBackOut * action5 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, -40)));
        m_multiplayer->runAction(action5);
        
        CCEaseBackOut * action6 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, -40)));
        m_highscore->runAction(action6);
        
        CCEaseBackOut * action7 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, -40)));
        m_settings->runAction(action7);
        
        CCEaseBackOut * action8 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, -40)));
        m_aboutus->runAction(action8);
    
    
        CCEaseBackOut * action9 = CCEaseBackOut::create(CCMoveTo::create(animDuring_game_type, ccp((origin.x+visibleSize.width)/2, -40)));
        m_exit->runAction(action9);
    }

    isAllMenuShowed = !isAllMenuShowed;
}

void DotGameScene::menuShowMoreMenuCallback(CCObject* pSender)
{
    
    AudioHelper::playMenuPress();
    
    this->showAllMenus(!isAllMenuShowed);
    
}

void DotGameScene::onEnter()
{
    
    CCLayer::onEnter();
    
}

void animGameType0()
{

    
}

void animGameType1()
{

    
}

void animGameType2()
{

    
}

