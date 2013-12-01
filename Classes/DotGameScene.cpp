#include "DotGameScene.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    
    //菜单
    
    //游戏类别选择
    m_gameType0 = CCMenuItemImage::create("game_type0.png", "game_type0_selected.png", "game_type0_selected.png",this, menu_selector(DotGameScene::menuGameType0Callback));
    
    m_gameType1 = CCMenuItemImage::create("game_type1.png", "game_type1_selected.png", "game_type1_selected.png",this, menu_selector(DotGameScene::menuGameType1Callback));
    
    m_gameType2 = CCMenuItemImage::create("game_type2.png", "game_type2_selected.png", "game_type2_selected.png",this, menu_selector(DotGameScene::menuGameType2Callback));
    
    //显示隐藏其余菜单
    m_moreMenus = CCMenuItemLabel::create(CCLabelTTF::create("Menu","MarkerFelt-Thin",18),this, menu_selector(DotGameScene::menuShowMoreMenuCallback));
    
    m_playnow = CCMenuItemImage::create("play_now.png", "play_now.png", "play_now.png",this, menu_selector(DotGameScene::menuPlayNowCallback));
    
    m_multiplayer = CCMenuItemLabel::create(CCLabelTTF::create("Multiplayer","MarkerFelt-Thin",18),this, menu_selector(DotGameScene::menuMultiPlayerCallback));
    
    m_highscore = CCMenuItemLabel::create(CCLabelTTF::create("Scores & Trophies","MarkerFelt-Thin",18),this, menu_selector(DotGameScene::menuHighScoreCallback));
    
    m_settings = CCMenuItemLabel::create(CCLabelTTF::create("Setting","MarkerFelt-Thin",18),this, menu_selector(DotGameScene::menuSettingCallback));
    
    m_aboutus = CCMenuItemLabel::create(CCLabelTTF::create("About","MarkerFelt-Thin",18),this, menu_selector(DotGameScene::menuAboutUsCallback));
    
    
    m_gameType0->setPosition(ccp((origin.x+visibleSize.width)*1/4, 180));
    m_gameType1->setPosition(ccp((origin.x+visibleSize.width)*2/4, 180));
    m_gameType2->setPosition(ccp((origin.x+visibleSize.width)*3/4, 180));
    
    m_playnow->setPosition(ccp((origin.x+visibleSize.width)/2, m_gameType0->getPosition().y-m_gameType0->getContentSize().height-menuPadding));
    m_moreMenus->setPosition(ccp((origin.x+visibleSize.width)/2, 2*menuPadding));
    
    m_multiplayer->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_highscore->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_settings->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    m_aboutus->setPosition(ccp((origin.x+visibleSize.width)/2,-100));
    
    CCMenu *menu = CCMenu::create(m_gameType0, m_gameType1, m_gameType2, m_playnow, m_multiplayer, m_moreMenus, m_highscore, m_settings, m_aboutus, NULL);
    
//    menu->alignItemsVertically();
    
    menu->setPosition(ccp(0,0));
    
    this->addChild(menu, 1);
    
    
    //背景色
    CCLayerColor * backGroundLayer = CCLayerColor::create(ccc4(100, 100, 100, 255));
    backGroundLayer->setAnchorPoint(ccp(0, 0));
    this->addChild(backGroundLayer);
    
    //logo
    CCSprite *logo = CCSprite::create("main_logo.png");
    logo->setPosition(ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)*3/4));
    this->addChild(logo);
    
    return true;
    
}

void DotGameScene::menuGameType0Callback(CCObject* pSender)
{

    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_0==NULL) {
        
        label_gametype_0 = CCLabelTTF::create("Timed","MarkerFelt-Thin",20);
        
        this->addChild(label_gametype_0);
        
        label_gametype_00 = CCLabelTTF::create("60 Seconds","MarkerFelt-Thin",14);
        
        this->addChild(label_gametype_00);
    }
    
    label_gametype_0->stopAllActions();
    label_gametype_0->setPosition(ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height));
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
    label_gametype_0->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    label_gametype_00->stopAllActions();
    label_gametype_00->setPosition(ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2));
    CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
    label_gametype_00->runAction(CCSequence::create(CCFadeIn::create(0),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    switch (SettingHelper::getGameType()) {
        case GAMETYPE0:
        {
            break;
        }
        case GAMETYPE1:
        {
            
            if (label_gametype_1!=NULL) {
                
                label_gametype_1->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                label_gametype_1->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_11->stopAllActions();
                CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_11->runAction(CCSequence::create(CCDelayTime::create(0.1),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }
            break;
        }
        case GAMETYPE2:
        {
            
            if (label_gametype_2!=NULL) {
                
                label_gametype_2->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
                label_gametype_2->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_22->stopAllActions();
                CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_22->runAction(CCSequence::create(CCDelayTime::create(0.1),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }
            break;
        }
        default:
            break;
    }
    
    SettingHelper::setGameType(GAMETYPE0);
}

void DotGameScene::menuGameType1Callback(CCObject* pSender)
{
    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_1==NULL) {
        
        label_gametype_1 = CCLabelTTF::create("游戏类别1","MarkerFelt-Thin",20);
        this->addChild(label_gametype_1);
        
        label_gametype_11 = CCLabelTTF::create("消除模式","MarkerFelt-Thin",14);
        this->addChild(label_gametype_11);
    }
    
    
    switch (SettingHelper::getGameType()) {
        case GAMETYPE0:
        {
            label_gametype_1->stopAllActions();
            label_gametype_1->setPosition(ccp(origin.x+visibleSize.width+label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height));
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
            label_gametype_1->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_11->stopAllActions();
            label_gametype_11->setPosition(ccp(origin.x+visibleSize.width+label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2));
            CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
            label_gametype_11->runAction(CCSequence::create(CCFadeIn::create(0),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            
            
            if (label_gametype_0!=NULL) {
                
                label_gametype_0->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                label_gametype_0->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_00->stopAllActions();
                CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_00->runAction(CCSequence::create(CCDelayTime::create(0.1),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }
            
            break;
        }
        case GAMETYPE1:
        {
            
            
            break;
        }
        case GAMETYPE2:
        {
            
            label_gametype_1->stopAllActions();
            label_gametype_1->setPosition(ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height));
            CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
            label_gametype_1->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            label_gametype_11->stopAllActions();
            label_gametype_11->setPosition(ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2));
            CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
            label_gametype_11->runAction(CCSequence::create(CCFadeIn::create(0),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            
            
            
            if (label_gametype_2!=NULL) {
                
                label_gametype_2->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
                label_gametype_2->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_22->stopAllActions();
                CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_22->runAction(CCSequence::create(CCDelayTime::create(0.1),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }
            break;
        }
        default:
            break;
    }
    
    SettingHelper::setGameType(GAMETYPE1);
}

void DotGameScene::menuGameType2Callback(CCObject* pSender)
{
    if (isAllMenuShowed) {
        
        this->showAllMenus(false);
    }
    
    if (label_gametype_2==NULL) {
        
        label_gametype_2 = CCLabelTTF::create("游戏类别2","MarkerFelt-Thin",18);
        this->addChild(label_gametype_2);
        
        label_gametype_22 = CCLabelTTF::create("wahaha","MarkerFelt-Thin",14);
        this->addChild(label_gametype_22);
    }
    
    
    label_gametype_2->stopAllActions();
    label_gametype_2->setPosition(ccp(origin.x+visibleSize.width+label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height));
    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
    label_gametype_2->runAction(CCSequence::create(CCFadeIn::create(0),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    label_gametype_22->stopAllActions();
    label_gametype_22->setPosition(ccp(origin.x+visibleSize.width+label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2));
    CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2)));
    label_gametype_22->runAction(CCSequence::create(CCFadeIn::create(0),action22,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
    
    switch (SettingHelper::getGameType()) {
        case GAMETYPE0:
        {
            if (label_gametype_0!=NULL) {
                
                label_gametype_0->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                label_gametype_0->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_00->stopAllActions();
                CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_00->runAction(CCSequence::create(CCDelayTime::create(0.1),action00,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }

            break;
        }
        case GAMETYPE1:
        {
            
            if (label_gametype_1!=NULL) {
                
                label_gametype_1->stopAllActions();
                CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                label_gametype_1->runAction(CCSequence::create(CCDelayTime::create(0.1),action,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
                
                label_gametype_11->stopAllActions();
                CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
                label_gametype_11->runAction(CCSequence::create(CCDelayTime::create(0.1),action11,CCDelayTime::create(1),CCFadeOut::create(5),NULL));
            }
            break;
        }
        case GAMETYPE2:
        {
            
            break;
        }
        default:
            break;
    }
    
    SettingHelper::setGameType(GAMETYPE2);
}

void DotGameScene::menuPlayNowCallback(CCObject* pSender)
{

    CCScene * playingScene = DotPlayingScene::scene();
    
    CCTransitionMoveInR* transitionScene = CCTransitionMoveInR::create(0.2, playingScene);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
}

void DotGameScene::menuMultiPlayerCallback(CCObject* pSender)
{

}

void DotGameScene::menuHighScoreCallback(CCObject* pSender)
{

}

void DotGameScene::menuSettingCallback(CCObject* pSender)
{

}

void DotGameScene::menuAboutUsCallback(CCObject* pSender)
{

}

void DotGameScene::showAllMenus(bool showAllMenus)
{

    
    if (showAllMenus) {
        
        //显示所有菜单
        
        CCLabelTTF *label = CCLabelTTF::create("Hide Menu","MarkerFelt-Thin",18);
        m_moreMenus->setLabel(label);
        
        switch (SettingHelper::getGameType()) {
            case GAMETYPE0:
            {
                if (label_gametype_0!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_0->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_0->getContentSize().height)));
                    label_gametype_0->runAction(action);
                    
                    CCEaseBackOut * action00 = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_00->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_00->runAction(action00);
                }
                
                
                break;
            }
            case GAMETYPE1:
            {
                if (label_gametype_1!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_1->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_1->getContentSize().height)));
                    label_gametype_1->runAction(action);
                    
                    CCEaseBackOut * action11 = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_11->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_11->runAction(action11);
                }
                
                break;
            }
            case GAMETYPE2:
            {
                if (label_gametype_2!=NULL) {
                    
                    CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_2->getContentSize().width, (origin.y+visibleSize.height)/2+label_gametype_2->getContentSize().height)));
                    label_gametype_2->runAction(action);
                    
                    CCEaseBackOut * action22 = CCEaseBackOut::create(CCMoveTo::create(0.2, ccp(-label_gametype_22->getContentSize().width, (origin.y+visibleSize.height)/2)));
                    label_gametype_22->runAction(action22);
                }
                
                break;
            }
            default:
                break;
        }
        
        //游戏类别
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*1/4, 260)));
//        m_gameType0->runAction(action);
        m_gameType0->runAction(CCEaseSineOut::create(action));
        
        CCEaseBackOut * action1 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*2/4, 260)));
//        m_gameType1->runAction(action1);
        m_gameType1->runAction(CCEaseSineOut::create(action1));
        
        CCEaseBackOut * action2 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*3/4, 260)));
//        m_gameType2->runAction(action2);
        m_gameType2->runAction(CCEaseSineOut::create(action2));
        
        //开始游戏
        CCEaseBackOut * action3 = CCEaseBackOut::create(CCMoveTo::create(0.5, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-menuPadding)));
//        m_playnow->runAction(action3);
        m_playnow->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action3),NULL));
        
        //more
        CCEaseBackOut * action4 = CCEaseBackOut::create(CCMoveTo::create(0.8, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-menuPadding*5/3)));
//        m_moreMenus->runAction(CCEaseSineOut::create(action4));
        m_moreMenus->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action4),NULL));
        
        m_multiplayer->setPosition(ccp((origin.x+visibleSize.width)/2, -40));
        m_highscore->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-menuPadding));
        m_settings->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-2*menuPadding));
        m_aboutus->setPosition(ccp((origin.x+visibleSize.width)/2, -40-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-3*menuPadding));
        
        //其他菜单
        CCEaseBackOut * action5 = CCEaseBackOut::create(CCMoveTo::create(0.9, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-3*menuPadding)));
//        m_multiplayer->runAction(CCEaseSineOut::create(action5));
        m_multiplayer->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action5),NULL));
        
        CCEaseBackOut * action6 = CCEaseBackOut::create(CCMoveTo::create(1.0, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-4*menuPadding)));
//        m_highscore->runAction(CCEaseSineOut::create(action6));
        m_highscore->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action6),NULL));
        
        CCEaseBackOut * action7 = CCEaseBackOut::create(CCMoveTo::create(1.1, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-5*menuPadding)));
//        m_settings->runAction(CCEaseSineOut::create(action7));
        m_settings->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action7),NULL));
        
        CCEaseBackOut * action8 = CCEaseBackOut::create(CCMoveTo::create(1.2, ccp((origin.x+visibleSize.width)/2, 260-m_gameType2->getContentSize().height-m_playnow->getContentSize().height-m_moreMenus->getContentSize().height-m_multiplayer->getContentSize().height-m_highscore->getContentSize().height-m_settings->getContentSize().height-6*menuPadding)));
//        m_aboutus->runAction(CCEaseSineOut::create(action8));
        m_aboutus->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action8),NULL));
        
    }else{
    
        //隐藏菜单
        CCLabelTTF *label = CCLabelTTF::create("Menu","MarkerFelt-Thin",18);
        m_moreMenus->setLabel(label);
        
        //游戏类别
        CCEaseBackOut * action = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*1/4, 180)));
        m_gameType0->runAction(action);
        
        CCEaseBackOut * action1 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*2/4, 180)));
        m_gameType1->runAction(action1);
        
        CCEaseBackOut * action2 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)*3/4, 180)));
        m_gameType2->runAction(action2);
        
        
        //开始游戏
        CCEaseBackOut * action3 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, 180-m_gameType2->getContentSize().height-menuPadding)));
        m_playnow->runAction(action3);
        
        //more
        CCEaseBackOut * action4 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, 2*menuPadding)));
        m_moreMenus->runAction(action4);
        
        //其他菜单
        CCEaseBackOut * action5 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -40)));
        m_multiplayer->runAction(action5);
        
        CCEaseBackOut * action6 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -40)));
        m_highscore->runAction(action6);
        
        CCEaseBackOut * action7 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -40)));
        m_settings->runAction(action7);
        
        CCEaseBackOut * action8 = CCEaseBackOut::create(CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -40)));
        m_aboutus->runAction(action8);
    }
    
    isAllMenuShowed = !isAllMenuShowed;
}

void DotGameScene::menuShowMoreMenuCallback(CCObject* pSender)
{
    
    
    this->showAllMenus(!isAllMenuShowed);
    
}

void DotGameScene::onEnter()
{
    
    CCLayer::onEnter();
}



