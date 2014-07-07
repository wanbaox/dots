

#include "DownStateLayer.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"


DownStateLayer::DownStateLayer()
{
    
}

DownStateLayer::~DownStateLayer()
{
    
}

bool DownStateLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Up_Down,origin.x+visibleSize.width,BottomHeight)) {
        
        return false;
    }
    
    this->setAnchorPoint(ccp(0,0));
                         
    
    

    return true;
}


void DownStateLayer::startAnimationDisplay(){
    
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, -BottomHeight));
    
    this->setVisible(true);
    
    CCMoveBy* moveTo2 = CCMoveBy::create(0.2, ccp(0,BottomHeight));
    
    this->runAction(CCSequence::create(CCEaseBackOut::create(moveTo2),NULL));
    
}

//隐藏的动画
void DownStateLayer::moveOut(){
    
    
    this->setVisible(true);
    
    CCMoveBy* moveTo2 = CCMoveBy::create(0.2, ccp(0,-BottomHeight));
    
    this->runAction(CCSequence::create(CCEaseBackIn::create(moveTo2),NULL));
    
}

void DownStateLayer::skillOnePressed(){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->playerUseSkill(tooltime);
        
    }
    
}

void DownStateLayer::skillTwoPressed(){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->playerUseSkill(toolDisappearOne);
        
    }
    
}

void DownStateLayer::skillThreePressed(){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->playerUseSkill(toolDisappearAll);
        
    }
    
}

