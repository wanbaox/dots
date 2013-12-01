//
//  TableLayer.cpp
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#include "TableLayer.h"
#include "DataController.h"

TableLayer::TableLayer()
{
    
}

TableLayer::~TableLayer()
{
    
}

bool TableLayer::init()
{
    
    if ( !CCNode::init() )
    {
        return false;
    }
    
    m_localLayer = CCLayerColor::create(ccc4(255, 255, 255, 255), 200, 150);
    
    m_worldLayer = CCLayerColor::create(ccc4(255, 255, 255, 255), 200, 150);
    
    m_worldLayer->setPosition(ccp(220, 0));
    
    this->addChild(m_localLayer);
    this->addChild(m_worldLayer);
    
    m_pageMaxCount = 2;
    m_pageCurrent = 1;
    
    return true;
}

void TableLayer::loadLoaclLayer(int score){
    
    
    m_localLayer->removeAllChildren();
    
    CCLabelTTF * tile = CCLabelTTF::create("you top score", "Arial", 14);
    
    tile->setPosition(ccp(m_localLayer->getContentSize().width/2, m_localLayer->getContentSize().height+10));
    
    m_localLayer->addChild(tile);
    
    CCArray *  scorearray = DataController::getSharedDataController()->readLoaclScoreTopList();
    
    CCInteger * object;
    int count = 6;
    bool flag = true;
    
    //    [self loadWorldTopList:score];
    
    if (scorearray->count()==0) {
        
        this->setNoDataInlist(m_localLayer);
    }
    
    this->loadLoaclLayer(1);
    
    int arrarCount = scorearray->count();
    
    for (int i = 0; i < arrarCount ; i++) {

        object = (CCInteger*)scorearray->objectAtIndex(i);
        
//        if (![object isKindOfClass:[NSNumber class]]) {
//            continue;
//        }
//        
//        NSNumber * number = (NSNumber*)object;
        
        int nu = object->getValue();
        
        CCLabelTTF * scorelabel = CCLabelTTF::create(CCString::createWithFormat("%d",nu)->getCString(), "Arial", 18);
        
        CCLabelTTF * namelabel = CCLabelTTF::create("YOU", "Arial", 18);
                                                    
        if (score == nu && flag) {
            
            flag = false;
            scorelabel->setColor(ccc3(255, 0, 0));
            namelabel->setColor(ccc3(255, 0, 0));
            
        }else{
            
            scorelabel->setColor(ccc3(0, 0, 0));
            namelabel->setColor(ccc3(0, 0, 0));
            
        }
        
        scorelabel->setAnchorPoint(ccp(1,0));
        scorelabel->setPosition(ccp(150, 20*count));
        
        namelabel->setAnchorPoint(ccp(0,0));
        namelabel->setPosition(ccp(15, 21*count));
        
        m_localLayer->addChild(scorelabel);
        m_localLayer->addChild(namelabel);
        
        count --;
    }
}

void TableLayer::loadWorldTopList(int score){
    
    
    m_worldLayer->removeAllChildren();
    
    CCLabelTTF * tile = CCLabelTTF::create("world top score", "Arial", 14);
    
    tile->setPosition(ccp(m_localLayer->getContentSize().width/2, m_localLayer->getContentSize().height+10));
    m_worldLayer->addChild(tile);
    
    
    CCDictionary * dic = DataController::getSharedDataController()->readWorldScpreTopList();
    
    if (dic==NULL) {
        
        this->setNoDataInlist(m_worldLayer);
        return;
    }
    
    CCArray * scorearray = (CCArray*)dic->objectForKey("score");
    CCArray * nameArray = (CCArray*)dic->objectForKey("name");
    
    if (scorearray==NULL || nameArray==NULL) {
        
        this->setNoDataInlist(m_worldLayer);
        return;
    }
    int count = 6;
    bool flag = true;
    
    this->loadWorldTopList(score);
    
    if (scorearray->count()==0) {
        this->setNoDataInlist(m_worldLayer);
        return;
    }
    
    for (int i = 0; i<scorearray->count();i++) {
        
        
        CCInteger * number = (CCInteger *)scorearray->objectAtIndex(i);
        
        if (number==NULL) {
            continue;
        }
        
        int nu = number->getValue();
        
        CCLabelTTF * scorelabel = CCLabelTTF::create(CCString::createWithFormat("%d",nu)->getCString(), "Arial", 18);
        CCLabelTTF * namelabel = CCLabelTTF::create(((CCString*)nameArray->objectAtIndex(i))->getCString(), "Arial", 18);
        
        if (score == nu && flag) {
            
            flag = false;
            scorelabel->setColor(ccc3(255, 0, 0));
            scorelabel->setColor(ccc3(255, 0, 0));
            
        }else{
            
            scorelabel->setColor(ccc3(0, 0, 0));
            namelabel->setColor(ccc3(0, 0, 0));
            
        }
        
        scorelabel->setAnchorPoint(ccp(1, 0));
        scorelabel->setPosition(ccp(135, 20*count));
        
        namelabel->setAnchorPoint(ccp(0, 0));
        namelabel->setPosition(ccp(15, 21*count));
        
        m_localLayer->addChild(scorelabel);
        m_localLayer->addChild(namelabel);
        count --;
    }
}

void TableLayer::setNoDataInlist(CCLayer* l){
    
    CCLabelTTF * alert = CCLabelTTF::create("目前没有记录!", "Arial", 18);
    alert->setColor(ccc3(10, 10, 10));
    alert->setPosition(ccp(80, 75));
    l->addChild(alert);
}

void TableLayer::leftPageMove(float distance){
    
    if (m_pageCurrent<=1) {
        m_pageCurrent = 1;
        return;
    }
    
    m_pageCurrent --;
    this->stopAllActions();
    CCPoint pos = this->getPosition();
    
    CCMoveTo * moveto = CCMoveTo::create(0.2, ccp(pos.x + distance+20, pos.y));
    CCMoveTo * moveto2 = CCMoveTo::create(0.2, ccp(pos.x + distance, pos.y));
    
    this->runAction(CCSequence::create(moveto,moveto2,NULL));
    
}

void TableLayer::rightPageMove(float distance){
    
    if (m_pageCurrent>=m_pageMaxCount) {
        m_pageCurrent = m_pageMaxCount;
        return;
    }
    //    NSLog(@"right move");
    m_pageCurrent ++;
    this->stopAllActions();
    
    CCPoint pos = this->getPosition();
    CCMoveTo * moveto = CCMoveTo::create(0.2, ccp(pos.x - distance-20, pos.y));
    CCMoveTo * moveto2 = CCMoveTo::create(0.2, ccp(pos.x -distance, pos.y));
    
    this->runAction(CCSequence::create(moveto,moveto2,NULL));
    
}


