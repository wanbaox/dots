

#include "DataHandle4NoTimeLimit1Tap.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

DataHandle4NoTimeLimit1Tap::DataHandle4NoTimeLimit1Tap()
{
    
}

DataHandle4NoTimeLimit1Tap::~DataHandle4NoTimeLimit1Tap()
{
    
    
    
}

bool DataHandle4NoTimeLimit1Tap::init()
{
    
    DataHandle::init();
    
//    m_Suggestion = CCArray::create();
    
    m_drawLine = false;
    return true;
    
}


bool DataHandle4NoTimeLimit1Tap::touchBegine(CCPoint local){
    
    //某个小道具
//    if (m_toolsDisappear) {
//        
//        this->toolDisappearSelected(local);
//        
//        return false;
//    }
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    if (ds==NULL || ds->m_disappear) {
        
        CCLog("DS == NULL  或者ds不可见");
        
        int count = m_stackArray->count();
        if (count !=0) {
            
            for (int i = 0; i < count; i++) {
                
                DrawSprite * node = (DrawSprite * )m_stackArray->objectAtIndex(i);
                
                node->unselected();
            }
            
            m_stackArray->removeAllObjects();
            
        }
        
        return true;
    }
    
    if (ds!=NULL) {
        
        m_stackArray->addObject(ds);
        
        m_currentDrawColor = ds->m_itemType;
        
        
        this->checkSurround(ds);
    
        if (m_stackArray!=NULL && m_stackArray->count()<=1) {
            
            //只选中了一个
            m_stackArray->removeAllObjects();
        }else if (m_stackArray!=NULL && m_stackArray->count()>1){
        
            m_canPlaying = false;
            
            showGotScore(local, getCurrentScore(m_stackArray->count()));
            
            this->hideSelected();
        }
        
        return true;
    }
    return false;
}

void DataHandle4NoTimeLimit1Tap::touchMove(CCPoint local){
}

void DataHandle4NoTimeLimit1Tap::touchEnd(CCPoint local){
}


void DataHandle4NoTimeLimit1Tap::hideSelected()
{
    
    AudioHelper::playingSound(m_stackArray->count());
    
    for (int i=0; i<m_stackArray->count(); i++) {
        
        DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
        if (node!=NULL) {
            
            node->disappearImmediate();
            if (i == m_stackArray->count()-1) {
                
                //最后一个
                disappearEnd();
            }
            
        }
    }

    
    m_stackArray->removeAllObjects();
}


bool DataHandle4NoTimeLimit1Tap::hasMoreMatched()
{
    CCArray* remainArray = m_drawSpriteArray;
    
    int count = remainArray->count();
    
    for (int i = 0; i<count; i++) {
        
        DrawSprite* ds = (DrawSprite*)remainArray->objectAtIndex(i);
        if (ds->m_disappear) {
            
            continue;
        }
       
        
        if (checkSurround(ds, remainArray)) {
            
            return true;
        }
    }
    
    //提示游戏结束
    if (this->getParent()!=NULL) {
        
        
        if (((DotPlayingScene*)this->getParent())->getCurrrentGoal(((DotPlayingScene*)this->getParent())->m_level)>((DotPlayingScene*)this->getParent())->m_score) {
            
            //分数不够
            ((DotPlayingScene*)this->getParent())->gameFailed();
            
        }else{
        
            ((DotPlayingScene*)this->getParent())->gotoNextLevel();
        }
        
    }
    return false;
}

bool DataHandle4NoTimeLimit1Tap::checkSurround(DrawSprite *drawSprite,CCArray* remainArray)
{
    int x = drawSprite->m_x;
    int y = drawSprite->m_y;
    
    
    //上
    if (y!=m_totalY-1) {
        
        int index = (y+1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)remainArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            return true;
        }
    }
    
    //下
    if (y!=0) {
        
        int index = (y-1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)remainArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            
            return true;
            
        }
    }
    
    //右
    if (x!=m_totalX-1) {
        
        int index = y*m_totalX + x + 1;
        DrawSprite *ds = (DrawSprite*)remainArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            
            return true;
        }
    }
    
    //左
    if (x!=0) {
        
        int index = y*m_totalX + x - 1;
        DrawSprite *ds = (DrawSprite*)remainArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            
            return true;
            
        }
    }
    return false;
}

void DataHandle4NoTimeLimit1Tap::checkSurround(DrawSprite *drawSprite)
{
    int x = drawSprite->m_x;
    int y = drawSprite->m_y;
    
    
    //上
    if (y!=m_totalY-1) {
        
        int index = (y+1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && m_currentDrawColor==ds->m_itemType)) {
            
//            ds->selectedType();
            ds->KeepSelected();
            if (!m_stackArray->containsObject(ds)) {
                
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //下
    if (y!=0) {
        
        int index = (y-1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && m_currentDrawColor==ds->m_itemType)) {
            
//            ds->selectedType();
            ds->KeepSelected();
            if (!m_stackArray->containsObject(ds)) {
                
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //右
    if (x!=m_totalX-1) {
        
        int index = y*m_totalX + x + 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && m_currentDrawColor==ds->m_itemType)) {
            
//            ds->selectedType();
            ds->KeepSelected();
            if (!m_stackArray->containsObject(ds)) {
                
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //左
    if (x!=0) {
        
        int index = y*m_totalX + x - 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && m_currentDrawColor==ds->m_itemType)) {
            
//            ds->selectedType();
            ds->KeepSelected();
            if (!m_stackArray->containsObject(ds)) {
                
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
}

bool DataHandle4NoTimeLimit1Tap::ccTouchBegan(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return false;
    }
    
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchBegine(local);
}

void DataHandle4NoTimeLimit1Tap::ccTouchMoved(CCTouch * touch, CCEvent * event){}

void DataHandle4NoTimeLimit1Tap::ccTouchEnded(CCTouch * touch, CCEvent * event){}

void DataHandle4NoTimeLimit1Tap::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){}


