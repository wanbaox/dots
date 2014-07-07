

#include "DataHandle4Tap.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"
#include "XYCUtils.h"

DataHandle4Tap::DataHandle4Tap()
{
    
}

DataHandle4Tap::~DataHandle4Tap()
{
    
    
}

bool DataHandle4Tap::init()
{
    
    DataHandle::init();
    
    array4Remain = CCArray::create();
    array4Remain->retain();
    
    return true;
    
}


bool DataHandle4Tap::touchBegine(CCPoint local){
    
//    if (m_toolsDisappear) {
//        
//        this->toolDisappearSelected(local);
//        
//        return false;
//    }
    
    m_movePos = local;
    m_objectHasContina = false;
    m_removeAllSameColor = false;
    
//    int count = m_stackArray->count();
//    if (count !=0) {
//        
//        for (int i = 0; i < count; i++) {
//            
//            DrawSprite * node = (DrawSprite * )m_stackArray->objectAtIndex(i);
//            
//            node->unselected();
//        }
//        
//        m_stackArray->removeAllObjects();
//        
//    }
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    
    if (ds!=NULL) {
        
        m_stackArray->addObject(ds);
        
        m_currentDrawColor = ds->m_itemType;
        m_drawLine = true;
        
        this->checkSurround(ds);
        
        if (m_stackArray->count()>=3) {
            
            showGotScore(local, getCurrentScore(m_stackArray->count()));
            
            
            this->hideSelected();
        }else{
        
            m_stackArray->removeAllObjects();
        }
        
        return true;
    }
    return false;
}



void DataHandle4Tap::hideSelected()
{
    m_drawLine = false;
    
    //声音
    long currentTime = XYCUtils::GetCurrentTime();
    
    if ((currentTime-lastTimeDismiss)>1000) {
        
        count4Continue = 1;
    }else{
        
        count4Continue++;
    }
    lastTimeDismiss = currentTime;
    
    AudioHelper::playingSound(count4Continue);
    
    m_canPlaying = false;
    
    for (int i=0; i<m_stackArray->count(); i++) {
        
        DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
        if (node!=NULL) {
            
            node->disappearImmediate();
            
            if (i == m_stackArray->count()-1) {
                
                this->disappearEnd();
            }
        }
    }
    m_stackArray->removeAllObjects();
    
}

void DataHandle4Tap::alert()
{

    if (hasMoreMatched()) {
        
        //还有match的
        for (int i = 0; i < array4Remain->count(); i++) {
            
//            CCLog("%i,%i",((DrawSprite*)array4Remain->objectAtIndex(i))->m_x,((DrawSprite*)array4Remain->objectAtIndex(i))->m_y);
            
            DrawSprite * ds = (DrawSprite*)array4Remain->objectAtIndex(i);
            ds->alert();
        }
        
    }else{
    
        //没有了,添加并提示
        //下半部分
        int i  = arc4random()%m_totalX*m_totalY/2;
        this->giveMoreMatch(i);
        
        //上半部分
        int j  = arc4random()%m_totalX*m_totalY/2+m_totalX*m_totalY/2;
        this->giveMoreMatch(j);
    }
}

//没有可以消除的，给出一些可以消除的
void DataHandle4Tap::giveMoreMatch(int scage)
{

    int matchedCount = 1;
    
    //随机选三个，让它可以match
    
    DrawSprite* drawSprite = (DrawSprite*)m_drawSpriteArray->objectAtIndex(scage);
    
    int x = drawSprite->m_x;
    int y = drawSprite->m_y;
    
    //右
    if (x!=m_totalX-1) {
        
        int index = y*m_totalX + x + 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            matchedCount++;
        }else{
            
            ds->refresh(drawSprite->m_itemType);
        }
    }
    
    //左
    if (x!=0) {
        
        int index = y*m_totalX + x - 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            
            matchedCount++;
        }else{
            
            ds->refresh(drawSprite->m_itemType);
        }
    }
    
    
    if (matchedCount>=3) {
        
        return;
    }
    
    //上
    if (y!=m_totalY-1) {
        
        int index = (y+1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            matchedCount++;
        }else{
        
            ds->refresh(drawSprite->m_itemType);
        }
    }
    
    
    if (matchedCount>=3) {
        
        return;
    }
    
    //下
    if (y!=0) {
        
        int index = (y-1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            matchedCount++;
        }else{
            
            ds->refresh(drawSprite->m_itemType);
        }
    }
    
    

}

bool DataHandle4Tap::hasMoreMatched()
{
    
    
    if (array4Remain->count()>0) {
        
        array4Remain->removeAllObjects();
    }
    
    int count = m_drawSpriteArray->count();
    
    for (int i = 0; i<count; i++) {
        
        DrawSprite* ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(i);
        if (ds->m_disappear) {
            
            continue;
        }
        
        array4Remain->addObject(ds);
        
        checkSurround4(ds);
        
        if (array4Remain->count()>=3) {
            
            return true;
        }else{
        
            array4Remain->removeAllObjects();
        }
    }
    
    //没有可以match的了
//    CCLog("没有可以match的");
    
    //没有了,添加并提示
    //下半部分
    int i  = arc4random()%m_totalX*m_totalY/2;
    this->giveMoreMatch(i);
    
    //上半部分
    int j  = arc4random()%m_totalX*m_totalY/2+m_totalX*m_totalY/2;
    this->giveMoreMatch(j);
    
    return false;
}

void DataHandle4Tap::checkSurround4(DrawSprite *drawSprite)
{
    
    
    int x = drawSprite->m_x;
    int y = drawSprite->m_y;
    
    
    //上
    if (y!=m_totalY-1) {
        
        int index = (y+1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            if (!array4Remain->containsObject(ds)) {
                
                array4Remain->addObject(ds);
                this->checkSurround4(ds);
            }
            
        }
    }
    
    //下
    if (y!=0) {
        
        int index = (y-1) * m_totalX +x;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            if (!array4Remain->containsObject(ds)) {
                
                array4Remain->addObject(ds);
                this->checkSurround4(ds);
            }
            
        }
    }
    
    //右
    if (x!=m_totalX-1) {
        
        int index = y*m_totalX + x + 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            if (!array4Remain->containsObject(ds)) {
                
                array4Remain->addObject(ds);
                this->checkSurround4(ds);
            }
        }
    }
    
    //左
    if (x!=0) {
        
        int index = y*m_totalX + x - 1;
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds!=NULL && !ds->m_disappear && drawSprite->m_itemType==ds->m_itemType)) {
            
            
            if (!array4Remain->containsObject(ds)) {
                
                array4Remain->addObject(ds);
                this->checkSurround4(ds);
            }
            
        }
    }
    
}


void DataHandle4Tap::checkSurround(DrawSprite *drawSprite)
{
    int x = drawSprite->m_x;
    int y = drawSprite->m_y;
    
    
    //上
    if (y<m_totalY-1) {
        int index = (y+1) * m_totalX +x;
        
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds && m_currentDrawColor==ds->m_itemType)) {
            
            if (!m_stackArray->containsObject(ds)) {
                
//                ds->selectedType();
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //下
    if (y>0) {
        
        int index = (y-1) * m_totalX +x;
        
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds && m_currentDrawColor==ds->m_itemType)) {
            
            if (!m_stackArray->containsObject(ds)) {
                
//                ds->selectedType();
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //右
    if (x<m_totalX-1) {
        
        int index = y*m_totalX + x + 1;
        
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds && m_currentDrawColor==ds->m_itemType)) {
            
            if (!m_stackArray->containsObject(ds)) {
                
//                ds->selectedType();
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
    //左
    if (x>0) {
        
        int index = y*m_totalX + x - 1;
        
        DrawSprite *ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(index);
        if ((ds && m_currentDrawColor==ds->m_itemType)) {
            
            if (!m_stackArray->containsObject(ds)) {
                
//                ds->selectedType();
                m_stackArray->addObject(ds);
                this->checkSurround(ds);
            }
        }
    }
    
}

void DataHandle4Tap::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent){}

void DataHandle4Tap::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent){}

void DataHandle4Tap::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){}


void DataHandle4Tap::touchMove(CCPoint local){}

void DataHandle4Tap::touchEnd(CCPoint local){}


bool DataHandle4Tap::ccTouchBegan(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return false;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchBegine(local);
}




