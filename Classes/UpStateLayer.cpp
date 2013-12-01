

#include "UpStateLayer.h"
#include "DotHudController.h"

UpStateLayer::UpStateLayer()
{
    
}

UpStateLayer::~UpStateLayer()
{
    
}

bool UpStateLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(ccc4(198, 203, 206, 255),origin.x+visibleSize.width,60)) {
        
        return false;
    }
    
    m_scoreItem = CCMenuItemImage::create("scorebutton.png", "score_unselect.png",this, menu_selector(UpStateLayer::menuBePressed));

    m_timeItem = CCMenuItemImage::create("timebutton.png", "time_unselect.png",this, menu_selector(UpStateLayer::menuBePressed));

    
    m_scoreItem->setAnchorPoint(ccp(0, 0));
    m_timeItem->setAnchorPoint(ccp(1, 0));
    
    m_scoreItem->setPosition(ccp(0, 0));
    m_timeItem->setPosition(ccp(origin.x+visibleSize.width, 0));
    
    
    CCMenu * menu = CCMenu::create(m_scoreItem,m_timeItem,NULL);
    
    menu->setPosition(ccp(0, 2));
    this->addChild(menu);
    
    m_labelScore = CCLabelTTF::create("0", "Arial", 18.0f);
    m_labelTime = CCLabelTTF::create("60", "Arial", 18.0f);
    
    m_labelScore->setAnchorPoint(ccp(0, 0.5));
    m_labelScore->setColor(ccc3(0, 0, 0));
    m_labelScore->setPosition(ccp(m_scoreItem->getContentSize().width/2+10,
                                  m_scoreItem->getContentSize().height/2));
    
    m_labelTime->setAnchorPoint(ccp(0, 0.5));
    m_labelTime->setColor(ccc3(0, 0, 0));
    m_labelTime->setPosition(ccp(m_timeItem->getContentSize().width/2+10,
                                 m_timeItem->getContentSize().height/2));
    
    m_timeItem->addChild(m_labelTime, 11);
    m_scoreItem->addChild(m_labelScore, 11);
    
    this->setVisible(false);
    
    return true;
}

void UpStateLayer::startAnimationDisplay(){
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->setVisible(true);
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, origin.y+visibleSize.height));
    
    CCMoveTo * moveTo1 = CCMoveTo::create(0.2, ccp(0, origin.y+visibleSize.height-60));
    CCMoveTo * moveTo2 = CCMoveTo::create(0.2, ccp(0, origin.y+visibleSize.height-43));
    
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(UpStateLayer::callBack0));
    
    this->runAction(CCSequence::create(moveTo1,moveTo2,call,NULL));
    
}

void UpStateLayer::callBack0(CCObject* sender){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->startGame();

    }
}
void UpStateLayer::resetScoreString(CCString * string){
    
    m_labelScore->setString(string->getCString());
}
void UpStateLayer::resetTimeString(CCString * string){
    
    m_labelTime->setString(string->getCString());
}

void UpStateLayer::menuBePressed(CCObject* sender){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->gamePause();
        
    }
    
}

