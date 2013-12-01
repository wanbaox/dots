

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
    
    if (!CCLayerColor::initWithColor(ccc4(198, 203, 206, 255),origin.x+visibleSize.width,60)) {
        
        return false;
    }
    
    this->setAnchorPoint(ccp(0,0));
                         
    
    CCMenuItemImage * skillOne = CCMenuItemImage::create("skillbutton.png", "skillButton_unselect.png",this, menu_selector(DownStateLayer::skillOnePressed));
    
     CCMenuItemImage * skillTwo = CCMenuItemImage::create("skillbutton.png", "skillButton_unselect.png",this, menu_selector(DownStateLayer::skillTwoPressed));
    
     CCMenuItemImage * skillThree = CCMenuItemImage::create("skillbutton.png", "skillButton_unselect.png",this, menu_selector(DownStateLayer::skillThreePressed));
    
    skillOne->setAnchorPoint(ccp(0, 0));
    skillTwo->setAnchorPoint(ccp(0.5, 0));
    skillThree->setAnchorPoint(ccp(1, 0));
    
    skillOne->setPosition(ccp(0, 0));
    skillTwo->setPosition(ccp((origin.x+visibleSize.width)/2, 0));
    skillThree->setPosition(ccp(origin.x+visibleSize.width, 0));
    
    
    
    CCMenu * menu = CCMenu::create(skillOne,skillTwo,skillThree,NULL);
    menu->setPosition(ccp(0, 17));
    this->addChild(menu);
    this->setVisible(false);
    
    return true;
}

void DownStateLayer::startAnimationDisplay(){
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, -60));
    
    this->setVisible(true);
    
    CCMoveTo * moveTo1 = CCMoveTo::create(0.2, ccp(0, 0));
    
    CCMoveTo * moveTo2 = CCMoveTo::create(0.2, ccp(0,-17));
    
    this->runAction(CCSequence::create(moveTo1,moveTo2,NULL));
    
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

