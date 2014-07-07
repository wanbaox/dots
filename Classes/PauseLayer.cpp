

#include "PauseLayer.h"
#include "DotGameScene.h"
#include "DotHudController.h"
#include "SettingHelper.h"
#include "SimpleAudioEngine.h"
#include "AudioHelper.h"
#include "CCLocalizedString.h"

PauseLayer::PauseLayer()
{
    
}

PauseLayer::~PauseLayer()
{
    
}

bool PauseLayer::init()
{
    
    
    if (!CCLayerColor::initWithColor(Color_Pause)) {
        
        return false;
    }
    
    m_resume = CCMenuItemImage::create(CCLocalizedString("pic_resume", ""), CCLocalizedString("pic_resume_select", ""),this, menu_selector(PauseLayer::resumeDotGame));
    
    m_restart = CCMenuItemImage::create(CCLocalizedString("pic_restart", ""), CCLocalizedString("pic_restart_select", ""),this, menu_selector(PauseLayer::restartDotGame));
    
    m_exittomain = CCMenuItemImage::create(CCLocalizedString("pic_exit", ""), CCLocalizedString("pic_exit_select", ""),this, menu_selector(PauseLayer::exitToMainScnen));
    
    CCMenu * menu = CCMenu::create(m_resume,m_restart,m_exittomain,NULL);
    
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    
    this->addChild(menu);
    this->setVisible(false);

    return true;
}

void PauseLayer::startAnimationDisplay(){
    
    this->setVisible(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    this->setAnchorPoint(ccp(0,0));
    this->setPosition(ccp(this->getContentSize().width, 0));
    
    
    
    //bg
    CCMoveBy * moveby = CCMoveBy::create(0.6, ccp(-this->getContentSize().width, 0));
    CCEaseExponentialOut * action0 = CCEaseExponentialOut::create(moveby);
    this->runAction(action0);
    
    //menu
    m_resume->setPosition(ccp(origin.x+visibleSize.width+m_resume->getContentSize().width, (origin.y+visibleSize.height)/2+50));
    m_restart->setPosition(ccp(origin.x+visibleSize.width+m_restart->getContentSize().width, (origin.y+visibleSize.height)/2));
    m_exittomain->setPosition(ccp(origin.x+visibleSize.width+m_exittomain->getContentSize().width, (origin.y+visibleSize.height)/2-50));
    
    
    CCMoveTo * moveTo12 = CCMoveTo::create(0.3, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+50));
    
    
    CCMoveTo * moveTo22 = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    
    
    CCMoveTo * moveTo32 = CCMoveTo::create(0.5, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2-50));
    
    CCEaseBackOut * action1 = CCEaseBackOut::create(moveTo12);
    CCEaseBackOut * action2 = CCEaseBackOut::create(moveTo22);
    CCEaseBackOut * action3 = CCEaseBackOut::create(moveTo32);
    
    
    
//    (CCEaseSineOut::create(action))
    
    m_resume->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action1),NULL));
    m_restart->runAction(CCSequence::create(CCDelayTime::create(0.1),CCEaseSineOut::create(action2),NULL));
    m_exittomain->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseSineOut::create(action3),NULL));
    
}

//isExitToMainPage标志是否退出游戏，到主界面
void PauseLayer::moveOut(bool isExitToMainPage){
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //bg
    CCMoveBy * moveby = CCMoveBy::create(0.6, ccp(this->getContentSize().width, 0));
    CCEaseExponentialOut * action0 = CCEaseExponentialOut::create(moveby);
    this->runAction(action0);
    
    //menu
    CCMoveTo * moveTo12 = CCMoveTo::create(0.3, ccp(origin.x+visibleSize.width+m_resume->getContentSize().width, (origin.y+visibleSize.height)/2+50));
    
    CCMoveTo * moveTo22 = CCMoveTo::create(0.4, ccp(origin.x+visibleSize.width+m_restart->getContentSize().width, (origin.y+visibleSize.height)/2));
    
    CCMoveTo * moveTo32 = CCMoveTo::create(0.5, ccp(origin.x+visibleSize.width+m_exittomain->getContentSize().width, (origin.y+visibleSize.height)/2-50));
    
    CCEaseBackOut * action1 = CCEaseBackOut::create(moveTo12);
    CCEaseBackOut * action2 = CCEaseBackOut::create(moveTo22);
    CCEaseBackOut * action3 = CCEaseBackOut::create(moveTo32);
    
    m_resume->runAction(CCSequence::create(CCDelayTime::create(0.05),CCEaseSineOut::create(action1),NULL));
    m_restart->runAction(CCSequence::create(CCDelayTime::create(0.1),CCEaseSineOut::create(action2),NULL));
    
    CCSequence * seq;
    if (isExitToMainPage) {
        
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(PauseLayer::replaceScene));
        seq = CCSequence::create(CCDelayTime::create(0.15),CCEaseSineOut::create(action3),call,NULL);
    }else{
    
        seq = CCSequence::create(CCDelayTime::create(0.15),CCEaseSineOut::create(action3),NULL);
    }
    
    m_exittomain->runAction(seq);
    
}

void PauseLayer::replaceScene(){
    
    CCScene * scene = DotGameScene::scene();
    
//    CCTransitionProgressOutIn* transitionScene = CCTransitionProgressOutIn::create(0.2, scene);
    
    CCDirector::sharedDirector()->replaceScene(scene);
    
}

void PauseLayer::resumeDotGame(){
    
    AudioHelper::playMenuPress();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->gamePause();
        
    }
}

void PauseLayer::restartDotGame(){
    
    AudioHelper::playMenuPress();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
//        dhc->gamePause();
        dhc->restartGame(true);
        
    }
}

void PauseLayer::exitToMainScnen(){
    
    AudioHelper::playMenuPress();
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        
        dhc->exitGame();
        
    }
    
}

