

#include "DataHandleClassic.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"

DataHandleClassic::DataHandleClassic()
{
    
}

DataHandleClassic::~DataHandleClassic()
{
    
    
}

bool DataHandleClassic::init()
{
    
    DataHandle::init();
    
    
    return true;
}

bool DataHandleClassic::touchBegine(CCPoint local){
    
    
    if (m_toolsDisappear) {
        
        this->toolDisappearSelected(local);
        
        return false;
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
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    
    if (ds!=NULL && ds->selectedType()) {
        
        m_stackArray->addObject(ds);
        AudioHelper::playingSound(m_stackArray->count());
        
        m_currentDrawColor = ds->m_itemType;
        m_drawLine = true;
        return true;
    }
    return false;
}

void DataHandleClassic::touchMove(CCPoint local){
    
    m_movePos = local;
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    
    //判断两个ds是不是相同类型的
    if (ds!=NULL && m_currentDrawColor==ds->m_itemType) {
        
        if (ds == m_stackArray->lastObject()) {
            
            //当前选中的item是上次最后一次选中的
            return;
        }
        if (m_stackArray->count() >=2 && ds == m_stackArray->objectAtIndex(m_stackArray->count()-2)) {
            //当前选中的item是选中的item里倒数第二个item
            //需要倒退一格
            
            DrawSprite * tds = (DrawSprite *)m_stackArray->lastObject();
            tds->unselected();
            
            if (m_objectHasContina) {
                m_removeAllSameColor = false;
                m_objectHasContina = false;
            }
            m_stackArray->removeLastObject();
            ds->selectedType();
            AudioHelper::playingSound(m_stackArray->count());//play sounds
            return;
        }
        
        if (!m_objectHasContina && m_stackArray->containsObject(ds)) {
            
            //已经包含了这个item，不是在最后一个，也不是在倒数第二个
            //取消选中效果
            
            DrawSprite * tds = (DrawSprite *)m_stackArray->lastObject();
            
            int hValue = abs(ds->m_x - tds->m_x);
            int wValue = abs(ds->m_y - tds->m_y);
            int absValue = abs(ds->m_x - tds->m_x) + abs(ds->m_y - tds->m_y);//选中的倒数位数 1，表示是上下左右相邻；2，表示左下，左上，右下，右上
            ds->unselected();
            
//            if (((absValue == 1 || absValue == 2) && hValue != 2 && wValue != 2) && ds->selectedType()) {//支持对角
            if (absValue == 1 && ds->selectedType()) {//不支持对角
                
                //如果当前选中的item和已经选中的最后一个item相距很近（小于1）
                //选中这个item
                m_objectHasContina = true;
                m_removeAllSameColor = true;
                
                m_stackArray->addObject(ds);
                AudioHelper::playingSound(m_stackArray->count());//play sounds
            }
        }
        
        if (m_objectHasContina && m_stackArray->containsObject(ds)) {
            
            //已经包含在选中的array里面了
            //直接返回
            return;
        }
        
        m_objectHasContina = false;
        DrawSprite * tds = (DrawSprite *)m_stackArray->lastObject();
        
        int hValue = abs(ds->m_x - tds->m_x);
        int wValue = abs(ds->m_y - tds->m_y);
        int absValue = abs(ds->m_x - tds->m_x) + abs(ds->m_y - tds->m_y);
        
//        if (((absValue == 1 || absValue == 2) && hValue != 2 && wValue != 2) && ds->selectedType()) {
        if (absValue == 1 && ds->selectedType()) {
        
            //选中
            m_stackArray->addObject(ds);
            AudioHelper::playingSound(m_stackArray->count());//play sounds
            
        }
    }
}

void DataHandleClassic::touchEnd(CCPoint local){
    
    if (!m_canPlaying) {
        
        if(m_stackArray!=NULL && m_stackArray->count()>0)
        {
        
            m_stackArray->removeAllObjects();
        }
            
        return;
    }
    
    m_drawLine = false;
    
    if (m_stackArray->count()>=2) {
        
        
        if (m_stackArray->count()>=4) {
            
            
            count4Continue +=2;
        }else{
        
            
            count4Continue=0;
        }
        
        
        
        m_canPlaying=false;
        if (m_removeAllSameColor) {
            
            //奖励效果
            if (this->getParent()!=NULL && !m_stageCleared && SettingHelper::getGameType()==GAME_TYPE_CLASSIC_LEVEL) {
                
                DotPlayingScene * dotplaying = (DotPlayingScene*)this->getParent();
                if (dotplaying->m_score >= dotplaying->getCurrrentGoal(dotplaying->m_level)) {
                    
//                    AudioHelper::playGoalFinished();
//                    m_stageCleared = true;
                }else{
                    
                    AudioHelper::playAnnouncer4HideAllSame();
                }
            }else{
                
                AudioHelper::playAnnouncer4HideAllSame();
            }
            
            
            int count = this->disappearAllSameColorDotsWithSelected();
            
            showGotScore(local, getCurrentScore(8));
        }else{
            //奖励效果
            if (this->getParent()!=NULL && !m_stageCleared && SettingHelper::getGameType()==GAME_TYPE_CLASSIC_LEVEL) {
                
                DotPlayingScene * dotplaying = (DotPlayingScene*)this->getParent();
                if (dotplaying->m_score >= dotplaying->getCurrrentGoal(dotplaying->m_level)) {
                    
//                    AudioHelper::playGoalFinished();
//                    m_stageCleared = true;
                    
                }else{
                    if (count4Continue>=Announcer1) {
                        
                        showAnnouncer(count4Continue);
                    }else{
                        
                        if (m_stackArray->count()>AnnoucerByNumber) {
                            
                            AudioHelper::playAnnouncerByNumber();
                        }
                    }
                }
            }else{
                if (count4Continue>=Announcer1) {
                    
                    showAnnouncer(count4Continue);
                }else{
                    
                    if (m_stackArray->count()>AnnoucerByNumber) {
                        
                        AudioHelper::playAnnouncerByNumber();
                    }
                }
            }
            
            
            showGotScore(local, getCurrentScore(m_stackArray->count()));
            for (int i=0; i<m_stackArray->count(); i++) {
                
                DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
                if (node!=NULL) {
                    
                    if (i == m_stackArray->count()-1) {
                        
                        node->disappear(true);
                        
                    }
                    
                    node->disappear(false);
                    
                }
            }
        }
    }else{
        
        count4Continue = 0;
        
        int count = m_stackArray->count();
        
        for (int i = 0; i < count; i++) {
            
            DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
            node->unselected();
        }
    }
    
    m_stackArray->removeAllObjects();
    
}


bool DataHandleClassic::ccTouchBegan(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return false;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchBegine(local);
}

void DataHandleClassic::ccTouchMoved(CCTouch * touch, CCEvent * event){
    
    
    if (!m_canPlaying) {
        return ;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchMove(local);
    
}
void DataHandleClassic::ccTouchEnded(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return ;
    }
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);

    this->touchEnd(local);
    
}

void DataHandleClassic::ccTouchCancelled(CCTouch * touch, CCEvent * pEvent){
    
    if (!m_canPlaying) {
        return ;
    }
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);

    this->touchEnd(local);
}



