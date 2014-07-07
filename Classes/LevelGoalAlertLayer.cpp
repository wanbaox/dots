

#include "LevelGoalAlertLayer.h"
#include "DotGameScene.h"
#include "CCLocalizedString.h"
#include "DotHudController.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

LevelGoalAlertLayer::LevelGoalAlertLayer()
{
    
}

LevelGoalAlertLayer::~LevelGoalAlertLayer()
{
    
}

bool LevelGoalAlertLayer::init()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Up_Down,origin.x+visibleSize.width,Height4MiddleAlert)) {
        
        return false;
    }
    
    m_labelLevel = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);
    m_labelGoal = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);
    
    m_labelLevel->setColor(Color_Text);
    m_labelGoal->setColor(Color_Text);
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(ccp(0.5, 0.5));
    
    this->addChild(m_labelLevel);
    this->addChild(m_labelGoal);
    
    this->setVisible(false);
    
    return true;
}

void LevelGoalAlertLayer::startAnimationDisplay(int level,long goal){
    
   
    this->setVisible(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    m_labelLevel->setString(CCString::createWithFormat("%s  %i",CCLocalizedString("level", "Level"),level)->getCString());
    m_labelGoal->setString(CCString::createWithFormat("%s  %li",CCLocalizedString("goal", "Goal"),goal)->getCString());
    
    m_labelLevel->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert*3/4-10));
    m_labelGoal->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert/4+10));
    
    this->setPosition(ccp((origin.x+visibleSize.width)/2, origin.y+visibleSize.height+this->getContentSize().height));
    
    CCMoveTo * movein = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    CCMoveTo * moveout = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -this->getContentSize().height));
    
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(LevelGoalAlertLayer::callBack0));
    CCCallFunc *callMenuOut = CCCallFunc::create(this, callfunc_selector(LevelGoalAlertLayer::callBackMenuOut));
    
    AudioHelper::playMenuIn();
    this->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseBackOut::create(movein),CCDelayTime::create(1.5),callMenuOut,CCEaseBackIn::create(moveout),call,NULL));
    
    
}

void LevelGoalAlertLayer::startAnimationDisplay4NextLevel(int level,long goal){
    
    if (level != 1) {
        AudioHelper::playStageClear();
    }
    
    this->setVisible(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    m_labelLevel->setString(CCString::createWithFormat("%s  %i",CCLocalizedString("level", "Level"),level)->getCString());
    m_labelGoal->setString(CCString::createWithFormat("%s  %li",CCLocalizedString("goal", "Goal"),goal)->getCString());
    
    m_labelLevel->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert*3/4-10));
    m_labelGoal->cocos2d::CCNode::setPosition(ccp((origin.x+visibleSize.width)/2, Height4MiddleAlert/4+10));
    
    this->setPosition(ccp((origin.x+visibleSize.width)/2, origin.y+visibleSize.height+this->getContentSize().height));
    
    CCMoveTo * movein = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2));
    CCMoveTo * moveout = CCMoveTo::create(0.4, ccp((origin.x+visibleSize.width)/2, -this->getContentSize().height));
    
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(LevelGoalAlertLayer::callBack1));
    CCCallFunc *callMenuOut = CCCallFunc::create(this, callfunc_selector(LevelGoalAlertLayer::callBackMenuOut));
    
    AudioHelper::playMenuIn();
    this->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseBackOut::create(movein),CCDelayTime::create(1.5),callMenuOut,CCEaseBackIn::create(moveout),call,NULL));
    
    
}

void LevelGoalAlertLayer::callBackMenuOut(CCObject* sender){
    
    AudioHelper::playMenuOut();
}

void LevelGoalAlertLayer::callBack0(CCObject* sender){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->startGame();
        
    }
}

void LevelGoalAlertLayer::callBack1(CCObject* sender){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->moveOut4NewLevel();
        
    }
}
