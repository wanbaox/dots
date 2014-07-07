//
//  DrawSprite.cpp
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#include "DrawSprite.h"
#include "DataHandle.h"
#include "SettingHelper.h"

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
 
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    return true;
}
CCPoint DrawSprite::calcPos(int x , int y){
    
    
    float width = getPositionX();
    float height = getPositionY();
    
    return ccp(width, height);
    
}

void DrawSprite::calcColor(){
    
    int i  = arc4random()%TOTAL_TYPE;
    switch (i) {
        case 0:
            m_itemType = ItemType1;
            break;
        case 1:
            m_itemType = ItemType2;
            break;
        case 2:
            m_itemType = ItemType3;
            break;
        case 3:
            m_itemType = ItemType4;
            break;
        case 4:
            m_itemType = ItemType5;
            break;
            
        default:
            m_itemType = ItemType4;
            break;
    }
}

float DrawSprite::getPositionX()
{
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    extern int m_totalX;
    
    return (origin.x+visibleSize.width-m_totalX*2*DRAWSPRITE_RADIUES)*(m_x+1)/(m_totalX+1)+DRAWSPRITE_RADIUES*(2*m_x+1);
}

float DrawSprite::getPositionY()
{
    
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
//    float heightFromBottom = BottomHeight+(visibleSize.height+origin.y-BottomHeight-UpHeight-visibleSize.width)/2;
    
    extern int m_totalX;
    extern int m_totalY;
    
    float heightFromBottom = 0;
//    if (SettingHelper::getGameType() != GAME_TYPE_NOTIMELIMIT) {
    
        heightFromBottom = (visibleSize.height+origin.y-BottomHeight-UpHeight-(origin.x+visibleSize.width)*m_totalY/m_totalX)/2;
//    }
    
    return (origin.x+visibleSize.width-m_totalX*2*DRAWSPRITE_RADIUES)*(m_y+1)/(m_totalX+1)+DRAWSPRITE_RADIUES*(2*m_y+1)+heightFromBottom;
}

void DrawSprite::spawnAtXYWH(int x, int y ,float w , float h){
    
    m_hasSelected = true;
    m_disappear = false;
    m_x = x;
    m_y = y;
    
    this->calcColor();
    
    //    [self setContentSize:CGSizeMake(DRAWSPRITE_RADIUES, DRAWSPRITE_RADIUES)];
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    float wd = getPositionX();
    
    switch (m_itemType) {
        case ItemType1:
            m_normalNode = CCSprite::create("item1.png");
            //选中的时候的node
//            m_selectNode = CCSprite::create("item1.png");
            break;
            
        case ItemType2:
            m_normalNode = CCSprite::create("item2.png");
            //选中的时候的node
//            m_selectNode = CCSprite::create("item2.png");
            break;
            
        case ItemType3:
            m_normalNode = CCSprite::create("item3.png");
            //选中的时候的node
//            m_selectNode = CCSprite::create("item3.png");
            break;
            
        case ItemType4:
            m_normalNode = CCSprite::create("item4.png");
            //选中的时候的node
//            m_selectNode = CCSprite::create("item4.png");
            break;
            
        case ItemType5:
            m_normalNode = CCSprite::create("item5.png");
            //选中的时候的node
//            m_selectNode = CCSprite::create("item5.png");
            break;
            
        default:
            break;
    }
    
    m_normalNode->setPosition(ccp(wd, origin.y+visibleSize.height));
    
    
    this->addChild(m_normalNode);
    
//    m_drawNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, m_color);
    
    

    
    
//    m_normalNode->addChild(m_selectNode);
    
    
//    m_drawNode = CCDrawNode::create();
//    
//    m_drawNode->setPosition(wd, origin.y+visibleSize.height);
//    m_drawNode->setContentSize(CCSizeMake(DRAWSPRITE_RADIUES, DRAWSPRITE_RADIUES));
//    
//    this->addChild(m_drawNode);
//    
//    m_drawNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, m_color);
//    
//    //选中的时候的node
//    m_selectNode = CCDrawNode::create();
//    
//    m_drawNode->addChild(m_selectNode);
    
//    ccColor4F col = ccc4f(m_color.r, m_color.g, m_color.b, 255*0.75);
//    
//    m_selectNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, col);
//    m_selectNode->setPosition(ccp(m_normalNode->getContentSize().width/2, m_normalNode->getContentSize().height/2));
//    m_selectNode->setVisible(false);
    
    //    [m_drawNode clear];
}


void DrawSprite::respawn(){
    
    
    m_disappear = false;
    m_hasSelected = false;
    
    m_normalNode->stopAllActions();
    m_normalNode->cleanup();
    m_normalNode->setScale(1.0f);
    
//    m_drawNode->stopAllActions();
//    m_drawNode->clear();
//    m_drawNode->setScale(1.0f);
//    m_selectNode->cleanup();
//    m_selectNode->setScale(1.0f);
    
    this->calcColor();
    switch (m_itemType) {
        case ItemType1:
        {
        
//            CCSprite *  headSprite=[CCSprite spriteWithFile:@"avatar_hall.png"];
//            UIImage * image=[UIImage imageNamed:@"avatar_hall2.png"];
//            CCTexture2D  * newTexture=[[CCTextureCache sharedTextureCache]  addCGImage:image.CGImage forKey:nil];
//            [headSprite  setTexture:newTexture];
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item1.png");
            m_normalNode->setTexture(texture);
//            CCTexture2D * texture_H =CCTextureCache::sharedTextureCache()->addImage("item1_h.png");
//            m_selectNode->setTexture(texture_H);
            
            break;
        }
            
        case ItemType2:
        {
        
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item2.png");
            m_normalNode->setTexture(texture);
//            CCTexture2D * texture_H =CCTextureCache::sharedTextureCache()->addImage("item2_h.png");
//            m_selectNode->setTexture(texture_H);
            break;
        }
            
            
        case ItemType3:
        {
            
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item3.png");
            m_normalNode->setTexture(texture);
//            CCTexture2D * texture_H =CCTextureCache::sharedTextureCache()->addImage("item3_h.png");
//            m_selectNode->setTexture(texture_H);
            break;
        }
        case ItemType4:
        {
            
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item4.png");
            m_normalNode->setTexture(texture);
//            CCTexture2D * texture_H =CCTextureCache::sharedTextureCache()->addImage("item4_h.png");
//            m_selectNode->setTexture(texture_H);
            break;
        }
        case ItemType5:
        {
            
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item5.png");
            m_normalNode->setTexture(texture);
//            CCTexture2D * texture_H =CCTextureCache::sharedTextureCache()->addImage("item5_h.png");
//            m_selectNode->setTexture(texture_H);
            break;
        }
        default:
            break;
    }

    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    float wd = getPositionX();
    
    m_normalNode->setPosition(ccp(wd, origin.y+visibleSize.height));
//    m_normalNode->drawDot(this->getPosition(), DRAWSPRITE_RADIUES, m_color);
    
//    m_drawNode->setPosition(wd, origin.y+visibleSize.height);
//    
//    m_drawNode->drawDot(this->getPosition(), DRAWSPRITE_RADIUES, m_color);
    
//    ccColor4F col = ccc4f(m_color.r, m_color.g, m_color.b, 255*0.75);
//    
//    m_selectNode->drawDot(ccp(0, 0), DRAWSPRITE_RADIUES, col);
    
    this->respawnDropdown();
    
}

void DrawSprite::spawnDropdown(bool isLast){
    
    m_dropCount = 0;
    
    this->stopAllActions();
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    //todo
    m_normalNode->setPosition(pos);
    m_normalNode->setScale(0);
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected),this);
    
    CCSequence * seq;
    if (isLast) {
        
        CCCallFuncO * call = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackReadyForPlaying),this);
        
        
        seq = CCSequence::create(CCSpawn::create(CCFadeIn::create(SPAWN_DROPDOWN_TIME/2),CCScaleTo::create(SPAWN_DROPDOWN_TIME/2, 1.0f),NULL),callB,call,NULL);
    }else{
        
        seq = CCSequence::create(CCSpawn::create(CCFadeIn::create(SPAWN_DROPDOWN_TIME/2),CCScaleTo::create(SPAWN_DROPDOWN_TIME/2, 1.0f),NULL),callB,NULL);
    }
    
    m_normalNode->runAction(seq);
    
}

void DrawSprite::callbackReadyForPlaying(CCObject * sender){
    
    if (this->getParent()!=NULL) {
        
        DataHandle * data = (DataHandle*)this->getParent();
        data->startPlaying();
        
    }
    
}

void DrawSprite::callbackNotSeclected(CCObject * sender){

    m_hasSelected = false;
    this->setVisible(true);
    
}

void DrawSprite::respawnDropdown(){
    
    m_dropCount = 0;
    
    this->stopAllActions();
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    CCMoveTo * moveto = CCMoveTo::create(SPAWN_DROPDOWN_TIME/3, pos);
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected),this);
    
    CCSequence * seq = CCSequence::create(CCEaseExponentialOut::create(moveto),callB,NULL);
    
    m_normalNode->runAction(seq);
    
}

void DrawSprite::resetPropertyA(int x , int y ){
    
    if (y <m_y) {
        m_dropCount ++;
    }
    m_x = x;
    m_y = y;
}

void DrawSprite::refresh(ItemType itemType)
{

    this->m_itemType = itemType;
    
    switch (m_itemType) {
        case ItemType1:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item1.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType2:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item2.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType3:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item3.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType4:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item4.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType5:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item5.png");
            m_normalNode->setTexture(texture);
            break;
        }
        default:
            break;
    }

}

void DrawSprite::moveToLeft(bool isLast){
    
    
    m_hasSelected = true;
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    CCMoveTo * moveto = CCMoveTo::create(RESET_DROPDOWN_TIME, pos);
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected0),this);
    
    CCSequence * seq ;
    if (isLast) {
        
        CCCallFuncO * call = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackFinishMoveLeft),this);
        
        seq = CCSequence::create(CCEaseExponentialOut::create(moveto),callB,call,NULL);
        
    }else{
    
        seq = CCSequence::create(CCEaseExponentialOut::create(moveto),callB,NULL);
    }

    m_normalNode->runAction(seq);
    
    
    m_dropCount = 0;

}

void DrawSprite::callbackFinishMoveLeft(CCObject * sender){
    
    //最后一个下落完成，开始检查是否有空列
    
    if (this->getParent()!=NULL) {
        
        DataHandle * data = (DataHandle*)this->getParent();
        data->m_canPlaying = true;
        
        data->hasMoreMatched();//判断是否还有可以消除的items
    }
}

void DrawSprite::resetDropdown(bool isLast){
    
    m_hasSelected = true;
    
    CCPoint pos = this->calcPos(m_x, m_y);
    
    CCMoveTo * moveto = CCMoveTo::create(RESET_DROPDOWN_TIME, pos);
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackNotSeclected0),this);
    
    CCSequence * seq;
    if (isLast) {
        
         CCCallFuncO * call = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callbackFinishDrop),this);
        
        seq = CCSequence::create(CCEaseExponentialOut::create(moveto),callB,call,NULL);
        
    }else{
    
        seq = CCSequence::create(CCEaseExponentialOut::create(moveto),callB,NULL);
    }
    
    m_normalNode->runAction(seq);
    
    
    m_dropCount = 0;
}

void DrawSprite::callbackFinishDrop(CCObject * sender){
    
    //最后一个下落完成，开始检查是否有空列
    
    if (this->getParent()!=NULL) {
        
        DataHandle * data = (DataHandle*)this->getParent();
        data->checkEmptyColumn();
        
    }
    
}

void DrawSprite::callbackNotSeclected0(CCObject * sender){
    
    m_hasSelected = false;
    
}

bool DrawSprite::positionInContent(CCPoint pos){
    //
    //    CGFloat width = DRAWSPRITE_WIDTH;
    //    CGFloat height = DRAWSPRITE_HEIGH;
    
    float orgx = m_normalNode->getPosition().x - DRAWSPRITE_WIDTH;
    float orgy = m_normalNode->getPosition().y - DRAWSPRITE_HEIGH;
    
    CCRect rect = CCRectMake(orgx, orgy, DRAWSPRITE_WIDTH*2, DRAWSPRITE_HEIGH*2);
    
    
    return rect.containsPoint(pos);
}

bool DrawSprite::selectedType(){
    
    m_hasSelected = true;
    
    m_normalNode->stopAllActions();
    m_normalNode->setScale(1.0f);
    m_normalNode->setVisible(true);
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1, 2.0);
    
    CCSequence * seq = CCSequence::create(scaleBy,scaleBy->reverse(),NULL);
    
    m_normalNode->runAction(seq);
    
    return true;
}

bool DrawSprite::alert(){
    
    m_hasSelected = true;
    
    m_normalNode->stopAllActions();
    m_normalNode->setScale(1.0f);
    m_normalNode->setVisible(true);
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1, 1.7);
    
    CCSequence * seq = CCSequence::create(scaleBy,scaleBy->reverse(),CCDelayTime::create(0.5),scaleBy,scaleBy->reverse(),NULL);
    
    m_normalNode->runAction(seq);
    
    return true;
}

void DrawSprite::disappearImmediate(){
    
    CCScaleBy * scaleBy2 = CCScaleBy::create(0, 0);
    
    m_disappear = true;
    
    m_normalNode->runAction(scaleBy2);
    
}

/**
 callf 标志是否提示隐藏选中items的动画全部结束
 */
void DrawSprite::disappear(bool callf){
    
    
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1f, 2.0);
    
    CCScaleBy * scaleBy2 = CCScaleBy::create(0.2, 0);
    
    CCSequence * seq = NULL;
    
    if (callf) {
        CCCallFuncO * callfu = CCCallFuncO::create(this, callfuncO_selector(DrawSprite::callback0), this);
        
        seq = CCSequence::create(scaleBy,scaleBy2,callfu,NULL);
        
    }else{
        
        seq = CCSequence::create(scaleBy,scaleBy2,NULL);
    }
    
    m_disappear = true;
    
    m_normalNode->runAction(seq);
    
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
    
    return m_normalNode->getPosition();
}


void DrawSprite::KeepSelected(){
    
    m_hasSelected = true;
    
    m_normalNode->stopAllActions();
    
    m_normalNode->setVisible(true);

    
    
    switch (m_itemType) {
        case ItemType1:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item1_s.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType2:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item2_s.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType3:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item3_s.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType4:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item4_s.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType5:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item5_s.png");
            m_normalNode->setTexture(texture);
            break;
        }
        default:
            break;
    }
}

void DrawSprite::unKeepSelected(){
    
    m_hasSelected = false;
    
    m_normalNode->stopAllActions();
    
    switch (m_itemType) {
        case ItemType1:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item1.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType2:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item2.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType3:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item3.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType4:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item4.png");
            m_normalNode->setTexture(texture);
            break;
        }
        case ItemType5:
        {
            
            CCTexture2D * texture =CCTextureCache::sharedTextureCache()->addImage("item5.png");
            m_normalNode->setTexture(texture);
            break;
        }
        default:
            break;
    }
    
}

//void DrawSprite::update(float time)
//{
//
//    CCNode::update(time);
//    
//}


