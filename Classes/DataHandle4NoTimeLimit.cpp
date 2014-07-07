

#include "DataHandle4NoTimeLimit.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

DataHandle4NoTimeLimit::DataHandle4NoTimeLimit()
{
    
}

DataHandle4NoTimeLimit::~DataHandle4NoTimeLimit()
{
    
    
    
}

bool DataHandle4NoTimeLimit::init()
{
    
    DataHandle::init();
    
//    m_Suggestion = CCArray::create();
    
    m_drawLine = false;
    return true;
    
}


bool DataHandle4NoTimeLimit::touchBegine(CCPoint local){
    
    //某个小道具
    if (m_toolsDisappear) {
        
        this->toolDisappearSelected(local);
        
        return false;
    }
    
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
    if (m_stackArray!=NULL ) {
        
        if (m_stackArray->count()>0) {
            
            if (m_stackArray->containsObject(ds)) {
                
                //包含在已选中的items中
                m_canPlaying = false;
                
                showGotScore(local, getCurrentScore(m_stackArray->count()));
                
                hideSelected();
                
                CCLog("开始消除");
                
                return false;
                
            }else{
                
                //不包含在已选中的items中
                
                
                AudioHelper::playItemTaped();
                
                int count = m_stackArray->count();
                for (int i = 0; i < count; i ++) {
                    
                    DrawSprite * ds = (DrawSprite *)m_stackArray->objectAtIndex(i);
                    ds->unKeepSelected();
                }
                
                m_stackArray->removeAllObjects();
                
            }
        }else{
        
            AudioHelper::playItemTaped();
        }
        
    }else{
    
        
        AudioHelper::playItemTaped();
    }
    
    m_movePos = local;
    m_objectHasContina = false;
    m_removeAllSameColor = false;
    
    int count = m_stackArray->count();
    if (count !=0) {
        
        for (int i = 0; i < count; i++) {
            
            DrawSprite * node = (DrawSprite * )m_stackArray->objectAtIndex(i);
            
            node->unselected();
        }
        
        m_stackArray->removeAllObjects();
        
    }
    
    
    if (ds!=NULL && ds->selectedType()) {
        
        m_stackArray->addObject(ds);
        
        m_currentDrawColor = ds->m_itemType;
        
        
        this->checkSurround(ds);
    
        if (m_stackArray!=NULL && m_stackArray->count()<=1) {
            
            //只选中了一个
            m_stackArray->removeAllObjects();
        }
        
        return true;
    }
    return false;
}

void DataHandle4NoTimeLimit::touchMove(CCPoint local){
}

void DataHandle4NoTimeLimit::touchEnd(CCPoint local){
}


void DataHandle4NoTimeLimit::hideSelected()
{
    
    AudioHelper::playingSound(m_stackArray->count());
    
//    int disappearCount = 0;

//    if (m_stackArray->count()>=1) {
//        if (m_removeAllSameColor) {
//            
//            this->disappearAllSameColorDotsWithSelected();
//
//        }else{
//
    
            for (int i=0; i<m_stackArray->count(); i++) {
                
                DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
                if (node!=NULL) {
                    
//                    if (i==m_stackArray->count()-1) {
//                        
//                        node->disappear(true);
//                    }else{
//                        
//                        node->disappear(false);
//                    }
                    
                    node->disappearImmediate();
                    if (i == m_stackArray->count()-1) {
                        
                        
                        //最后一个
                        disappearEnd();
                    }
                    
                    
                    
                }
            }
//        }
//    }else{
//        
//        int count = m_stackArray->count();
//        for (int i = 0; i < count; i++) {
//            
//            DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
//            node->unselected();
//        }
//    }

    
    m_stackArray->removeAllObjects();
}


bool DataHandle4NoTimeLimit::hasMoreMatched()
{
    CCArray* remainArray = m_drawSpriteArray;
    
    int count = remainArray->count();
    
    for (int i = 0; i<count; i++) {
        
        DrawSprite* ds = (DrawSprite*)remainArray->objectAtIndex(i);
        if (ds->m_disappear) {
            
            continue;
        }
       
        
        if (checkSurround(ds, remainArray)) {
            
            CCLog("还有可以消除的");
            return true;
        }
    }
    
    //提示游戏结束
    CCLog("没有相同的了");
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

bool DataHandle4NoTimeLimit::checkSurround(DrawSprite *drawSprite,CCArray* remainArray)
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

void DataHandle4NoTimeLimit::checkSurround(DrawSprite *drawSprite)
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

bool DataHandle4NoTimeLimit::ccTouchBegan(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return false;
    }
    
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchBegine(local);
}

void DataHandle4NoTimeLimit::ccTouchMoved(CCTouch * touch, CCEvent * event){}

void DataHandle4NoTimeLimit::ccTouchEnded(CCTouch * touch, CCEvent * event){}

void DataHandle4NoTimeLimit::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){}


