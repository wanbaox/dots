

#include "NormalEndLayer.h"
#include "DotGameScene.h"
#include "CCLocalizedString.h"
#include "DotHudController.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

NormalEndLayer::NormalEndLayer()
{
    
}

NormalEndLayer::~NormalEndLayer()
{
    
}

bool NormalEndLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Up_Down,origin.x+visibleSize.width,Height4MiddleAlert)) {
        
        return false;
    }
    
    m_reTry = CCMenuItemImage::create(CCLocalizedString("pic_restart", ""), CCLocalizedString("pic_restart_select", ""),this, menu_selector(NormalEndLayer::callBackReTry));
    
    m_exitGame = CCMenuItemImage::create(CCLocalizedString("pic_exit", ""), CCLocalizedString("pic_exit_select", ""),this, menu_selector(NormalEndLayer::callBackExitGame));
    
    CCMenu * menu = CCMenu::create(m_reTry,m_exitGame,NULL);
    
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(menu);
    this->setVisible(false);
    
    return true;
}

/**
 success表示是否超过上次
 */
void NormalEndLayer::startAnimationDisplay(bool success){
    
    AudioHelper::playStageClear();
    
    this->setVisible(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    m_reTry->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert*3/4-5));
    m_exitGame->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert/4+5));
    
    this->setPosition(ccp((origin.x+visibleSize.width)/2, -this->getContentSize().height));
    
    AudioHelper::playMenuIn();
    CCMoveTo * movein = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    
    this->runAction(CCEaseBackOut::create(movein));
    
}

void NormalEndLayer::callBackReTry(CCObject* sender){
    
    AudioHelper::playMenuPress();
    AudioHelper::playMenuOut();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
//        dhc->gamePause();
        dhc->restartGame(true);
        
    }
}

void NormalEndLayer::callBackExitGame(CCObject* sender){
    
    
    AudioHelper::playMenuPress();
    AudioHelper::playMenuOut();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
        dhc->exitGame();
    }
}

void NormalEndLayer::moveOut(){

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCMoveTo * moveout = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -this->getContentSize().height));
    
    this->runAction(CCEaseBackIn::create(moveout));
    
}



