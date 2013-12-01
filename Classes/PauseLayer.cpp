

#include "PauseLayer.h"
#include "DotGameScene.h"

PauseLayer::PauseLayer()
{
    
}

PauseLayer::~PauseLayer()
{
    
}

bool PauseLayer::init()
{
    
    
    if (!CCLayerColor::initWithColor(ccc4(198, 203, 206, 255))) {
        
        return false;
    }
    
    this->setAnchorPoint(ccp(0,0));
    this->setPosition(ccp(0, 0));
                         
    
    m_resume = CCMenuItemImage::create("resume.png", "resume_unselect.png",this, menu_selector(PauseLayer::resumeDotGame));
    
    m_restart = CCMenuItemImage::create("restart.png", "restart_unselect.png",this, menu_selector(PauseLayer::restartDotGame));
    
    m_exittomain = CCMenuItemImage::create("exit.png", "exit_unselect.png",this, menu_selector(PauseLayer::exitToMainScnen));
    
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
    
    m_resume->setPosition(ccp(origin.x+visibleSize.width, (origin.y+visibleSize.height)/2+50));
    m_restart->setPosition(ccp(origin.x+visibleSize.width, (origin.y+visibleSize.height)/2));
    m_exittomain->setPosition(ccp(origin.x+visibleSize.width, (origin.y+visibleSize.height)/2-50));
    
    CCMoveTo * moveTo1 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2-15, (origin.y+visibleSize.height)/2+50));
    
    CCMoveTo * moveTo12 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+50));
    
    CCMoveTo * moveTo2 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2-35, (origin.y+visibleSize.height)/2));
    
    CCMoveTo * moveTo22 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    
    CCMoveTo * moveTo3 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2-45, (origin.y+visibleSize.height)/2-50));
    
    CCMoveTo * moveTo32 = CCMoveTo::create(0.2, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2-50));
    
    
    m_resume->runAction(CCSequence::create(moveTo1,moveTo12,NULL));
    m_restart->runAction(CCSequence::create(moveTo2,moveTo22,NULL));
    m_exittomain->runAction(CCSequence::create(moveTo3,moveTo32,NULL));
    
}

void PauseLayer::resumeDotGame(){
    
}

void PauseLayer::restartDotGame(){
    
    
}

void PauseLayer::exitToMainScnen(){
    
    
    CCScene * scene = DotGameScene::scene();
    
    CCTransitionProgressOutIn* transitionScene = CCTransitionProgressOutIn::create(0.2, scene);
    CCDirector::sharedDirector()->replaceScene(transitionScene);

}

