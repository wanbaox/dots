//
//  DrawSprite.cpp
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#include "DrawSprite.h"
#include "DataHandle.h"

#define caleActiontag 100

DrawSprite::DrawSprite()
{
    
}

DrawSprite::~DrawSprite()
{
//    CC_SAFE_RELEASE_NULL(__prop);
}


bool DrawSprite::init()
{
    
    if (!CCNode::init()) {
        
        return false;
    }
 
    return true;
}
CCPoint DrawSprite::calcPos(int x , int y){
    
    
    float width = this->getAnchorPoint().x * m_w + x * m_w +addWidth;
    float height = this->getAnchorPoint().y * m_h + y * m_h +AddHeigh;
    
    return ccp(width, height);
    
}

void DrawSprite::calcColor(){
    
    int type = arc4random()%TOTAL_TYPE;
    switch (type) {
        case 0:
            m_color = ccc4fBlue;
            break;
        case 1:
            m_color = ccc4fGreen;
            break;
        case 2:
            m_color = ccc4fRed;
            break;
        case 3:
            m_color = ccc4fPurple;
            break;
        case 4:
            m_color = ccc4fOrange;
            break;
            
        default:
            m_color = ccc4fPurple;
            break;
    }
}

void DrawSprite::spawnAtXYWH(int x, int y ,float w , float h){
    
    m_hasSelected = true;
    m_disappear = false;
    m_x = x;
    m_y = y;
    
    
    m_w = w*2;
    m_h = h*2;
    
    this->calcColor();
    
    //    [self setContentSize:CGSizeMake(DRAWSPRITE_RADIUES, DRAWSPRITE_RADIUES)];
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    float wd = this->getAnchorPoint().x * m_w + x * m_w+addWidth;
    
    m_drawNode = CCDrawNode::create();
    
    m_drawNode->setPosition(wd, origin.y+visibleSize.height);
    m_drawNode->setContentSize(CCSizeMake(DRAWSPRITE_RADIUES, DRAWSPRITE_RADIUES));
    
    this->addChild(m_drawNode);
    
    m_drawNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, m_color);
    
    //选中的时候的node
    m_selectNode = CCDrawNode::create();
    
    m_drawNode->addChild(m_selectNode);
    
    ccColor4F col = ccc4f(m_color.r, m_color.g, m_color.b, 255*0.75);
    
    m_selectNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, col);
    m_selectNode->setVisible(false);
    
    //    [m_drawNode clear];
}

void DrawSprite::respawn(){
    
    m_disappear = false;
    
    m_drawNode->stopAllActions();
    m_drawNode->clear();
    m_drawNode->setScale(1.0f);
    
    m_selectNode->clear();
    m_selectNode->setScale(1.0f);
    
    this->calcColor();
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    float wd = this->getAnchorPoint().x * m_w + m_x * m_w +addWidth;
    
    m_drawNode->setPosition(wd, origin.y+visibleSize.height);
    
    m_drawNode->drawDot(this->getPosition(), DRAWSPRITE_RADIUES, m_color);
    
    ccColor4F col = ccc4f(m_color.r, m_color.g, m_color.b, 255*0.75);
    
    m_selectNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, col);
    
    this->respawnDropdown();
    
}

void DrawSprite::spawnDropdown(){
    m_dropCount = 0;
    
    this->stopAllActions();
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    CCActionInterval * wait = CCActionInterval::create(m_y*SPAWN_DROPDOWN_TIME/5);
    
    CCMoveTo * moveto = CCMoveTo::create(SPAWN_DROPDOWN_TIME/2, pos);
    
    CCJumpTo * jump = CCJumpTo::create(SPAWN_JUMP_TIME, pos, 30, 1);
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected),this);
    
    
    CCSequence * seq = CCSequence::create(wait,moveto,jump,callB,NULL);
    
    m_drawNode->runAction(seq);
    
}

void DrawSprite::callbackNotSeclected(CCObject * sender){

    m_hasSelected = false;
    this->setVisible(true);
    
}

void DrawSprite::respawnDropdown(){
    
    m_dropCount = 0;
    
    this->stopAllActions();
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    //    CCActionInterval * wait = [CCActionInterval actionWithDuration:m_y*SPAWN_DROPDOWN_TIME/5];
    
    CCMoveTo * moveto = CCMoveTo::create(SPAWN_DROPDOWN_TIME/3, pos);
    
    CCJumpTo * jump = CCJumpTo::create(SPAWN_JUMP_TIME/3*2, pos, 20, 1);
    
     CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected),this);
    
    
    CCSequence * seq = CCSequence::create(moveto,jump,callB,NULL);
    
    m_drawNode->runAction(seq);
    
}

void DrawSprite::resetPropertyA(int x , int y ){
    if (y <m_y) {
        m_dropCount ++;
    }
    m_x = x;
    m_y = y;
}

void DrawSprite::resetDropdown(){
    
    m_hasSelected = true;
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    //    CCActionInterval * wait = [CCActionInterval actionWithDuration:m_y*SPAWN_DROPDOWN_TIME/5];
    
    CCMoveTo * moveto = CCMoveTo::create(RESET_DROPDOWN_TIME, pos);
    
    CCJumpTo * jump = CCJumpTo::create(SPAWN_JUMP_TIME/3, pos, 15, 1);
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected0),this);
    
    
    CCSequence * seq = CCSequence::create(moveto,jump,callB,NULL);
    
    m_drawNode->runAction(seq);
    
    
    m_dropCount = 0;
}

void DrawSprite::callbackNotSeclected0(CCObject * sender){
    
    m_hasSelected = false;
    
}

bool DrawSprite::positionInContent(CCPoint pos){
    //
    //    CGFloat width = DRAWSPRITE_WIDTH;
    //    CGFloat height = DRAWSPRITE_HEIGH;
    
    float orgx = m_drawNode->getPosition().x - DRAWSPRITE_WIDTH;
    float orgy = m_drawNode->getPosition().y - DRAWSPRITE_HEIGH;
    
    CCRect rect = CCRectMake(orgx, orgy, DRAWSPRITE_WIDTH*2, DRAWSPRITE_HEIGH*2);
    
    
    return rect.containsPoint(pos);
}

bool DrawSprite::selectedType(){
    
    m_hasSelected = true;
    
    m_selectNode->stopAllActions();
    m_selectNode->setScale(1.0f);
    m_selectNode->setVisible(true);
    
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1, 2.0);
    CCCallFunc * block = CCCallFunc::create(this, callfunc_selector(DrawSprite::callbackSetInVisible));
    
    
    CCSequence * seq = CCSequence::create(scaleBy,scaleBy->reverse(),block,NULL);
    
    m_selectNode->runAction(seq);
    
    return true;
}

void DrawSprite::callbackSetInVisible(CCObject * sender){
    
    m_selectNode->setVisible(false);
    
}

void DrawSprite::disappear(bool callf){
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1f, 1.5);
    
    CCScaleBy * scaleBy2 = CCScaleBy::create(0.2, 0);
    
    CCSequence * seq = NULL;
    
    if (callf) {
        CCCallFuncO * callfu = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callback0), this);
        
        seq = CCSequence::create(scaleBy,scaleBy2,callfu,NULL);
    }else{
        
        seq = CCSequence::create(scaleBy,scaleBy2,NULL);
    }
    
    m_disappear = true;
    
    m_drawNode->runAction(seq);
    
}

void DrawSprite::callback0(CCObject * sender)
{
    
    if (this->getParent()!=NULL) {
        
        DataHandle * data = (DataHandle*)this->getParent();
        data->disappearEnd();
        
    }
    
}

void DrawSprite::unselected(){
    
    m_hasSelected = false;
}

CCPoint DrawSprite::getDrawNodePosition(){
    
    return m_drawNode->getPosition();
}


void DrawSprite::KeepSelected(){
    
    m_hasSelected = true;
    
    m_selectNode->stopAllActions();
    
    m_selectNode->setVisible(true);
    
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1, 1.7);
    
    m_selectNode->runAction(scaleBy);
}

void DrawSprite::unKeepSelected(){
    
    m_hasSelected = false;
    
    m_selectNode->stopAllActions();
    
    
    CCScaleTo * scaleTo = CCScaleTo::create(0.1, 1.0);
    CCCallFunc * block = CCCallFunc::create(this,  callfunc_selector(DrawSprite::callbackSetInVisible));
    
    CCSequence * seq = CCSequence::create(scaleTo,block,NULL);
    seq->setTag(caleActiontag);
    m_selectNode->runAction(seq);
    
}

//void DrawSprite::update(float time)
//{
//
//    
//}


