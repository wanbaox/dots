

#include "FailLayer.h"
#include "DotGameScene.h"
#include "CCLocalizedString.h"
#include "DotHudController.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

FailLayer::FailLayer()
{
    
}

FailLayer::~FailLayer()
{
    
}

bool FailLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Up_Down,origin.x+visibleSize.width,Height4MiddleAlert)) {
        
        return false;
    }
    
    m_reTry = CCMenuItemImage::create(CCLocalizedString("pic_restart", ""), CCLocalizedString("pic_restart_select", ""),this, menu_selector(FailLayer::callBackReTry));
    
    m_exitGame = CCMenuItemImage::create(CCLocalizedString("pic_exit", ""), CCLocalizedString("pic_exit_select", ""),this, menu_selector(FailLayer::callBackExitGame));
    
    CCMenu * menu = CCMenu::create(m_reTry,m_exitGame,NULL);
    
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(menu);
    this->setVisible(false);
    
    return true;
}

void FailLayer::startAnimationDisplay(){
    
    AudioHelper::playGameFailed();
    
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

void FailLayer::callBackReTry(CCObject* sender){
    
    AudioHelper::playMenuPress();
    AudioHelper::playMenuOut();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
//        moveOut();
        
//        dhc->gamePause();
        dhc->restartGame(true);
        
    }
}

void FailLayer::callBackExitGame(CCObject* sender){
    
    
    AudioHelper::playMenuPress();
    AudioHelper::playMenuOut();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
        dhc->exitGame();
    }
}

void FailLayer::moveOut(){

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCMoveTo * moveout = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -this->getContentSize().height));
    
    this->runAction(CCEaseBackIn::create(moveout));
    
}



