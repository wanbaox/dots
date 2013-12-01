

#include "DataHandle.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"


DataHandle::DataHandle()
{
    
}

DataHandle::~DataHandle()
{
    
    m_stackArray->removeAllObjects();
    m_stackArray->release();
    m_stackArray = NULL;
    
    
    m_drawSpriteArray->removeAllObjects();
    m_drawSpriteArray->release();
    m_drawSpriteArray = NULL;
    
    
    
//    [m_stackArray removeLastObject]; [m_stackArray release];
//    [m_drawSpriteArray removeLastObject]; [m_drawSpriteArray release];
    
}

void loadEffectSounds(){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("1.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("2.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("3.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("4.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("5.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("6.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("7.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("8.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("9.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("10.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("11.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("12.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("13.aif");
    
}

void playingSound(int count){
    
    if (count>13) {
        count = 13;
    }
    
    CCString * soundName = CCString::createWithFormat("%d.aif",count);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundName->getCString());
    
}

bool DataHandle::init()
{
    
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        
        return false;
    }
    
    m_drawSpriteArray = CCArray::create();
    m_drawSpriteArray->retain();
    
    for (int y = 0; y<TOTALY; y++) {
        for (int x = 0; x<TOTALX; x++) {
            
            DrawSprite * drawS = DrawSprite::create();
            drawS->spawnAtXYWH(x, y, DRAWSPRITE_WIDTH, DRAWSPRITE_HEIGH);
            m_drawSpriteArray->addObject(drawS);
            
            this->addChild(drawS,1);
        }
    }
    m_stackArray = CCArray::create();
    
    m_stackArray->retain();
    
    this->setVisible(false);
    loadEffectSounds();
    
    return true;
}

DrawSprite * DataHandle::getCurrentSelectSprite(CCPoint pos) {
    
    if (m_drawSpriteArray!=NULL && m_drawSpriteArray->count()>0) {
        
        int count = m_drawSpriteArray->count();
        for (int i = 0; i<count; i++) {
            
            DrawSprite * node = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
            
            if (node!=NULL && node->positionInContent(pos)) {
                
                return node;
            }
        }
        
    }
    
    return NULL;
}

bool DataHandle::touchBegine(CCPoint local){
    
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
        playingSound(count);
        
        m_currentDrawColor = ds->m_color;
        m_drawLine = true;
        return true;
    }
    return false;
}

void DataHandle::touchMove(CCPoint local){
    
    m_movePos = local;
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    
    //判断两个ds是不是相同类型的
    if (ds!=NULL && ccc4FEqual(m_currentDrawColor, ds->m_color)) {
        
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
            playingSound(m_stackArray->count());//play sounds
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
            
            if (((absValue == 1 || absValue == 2) && hValue != 2 && wValue != 2) && ds->selectedType()) {//支持对角
//            if (absValue == 1 && ds->selectedType()) {//不支持对角
                
                //如果当前选中的item和已经选中的最后一个item相距很近（小于1）
                //选中这个item
                m_objectHasContina = true;
                m_removeAllSameColor = true;
                
                m_stackArray->addObject(ds);
                playingSound(m_stackArray->count());//play sounds
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
        
        if (((absValue == 1 || absValue == 2) && hValue != 2 && wValue != 2) && ds->selectedType()) {
//        if (absValue == 1 && ds->selectedType()) {
        
            //选中
            m_stackArray->addObject(ds);
            playingSound(m_stackArray->count());//play sounds
            
        }
    }
}

void DataHandle::touchEnd(){
    
    m_drawLine = false;
    
    int disappearCount = 0;
    
    if (m_stackArray->count()>=2) {
        if (m_removeAllSameColor) {
            
            this->disappearAllSameColorDotsWithSelected();
            
        }else{
            
            for (int i=0; i<m_stackArray->count(); i++) {
                
                DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
                if (node!=NULL) {
                    
                    if (i == m_stackArray->count()-1) {
                        
                        node->disappear(true);
                        
                    }
                    
                    node->disappear(false);
                    
                    disappearCount ++;
                }
            }
        }
    }else{
        
        int count = m_stackArray->count();
        for (int i = 0; i < count; i++) {
            
            DrawSprite * node = (DrawSprite *)m_stackArray->objectAtIndex(i);
            node->unselected();
        }
    }
    m_stackArray->removeAllObjects();
    
    if (this->getParent()!=NULL) {
        
        ((DotPlayingScene*)this->getParent())->playingScoreAdd(disappearCount);
        
        //        DotPlayingScnen * playing = (DotPlayingScnen*)self.parent;
        //
        //        if (playing) {
        //            [playing playingScoreAdd:disappearCount];
        //        }
    }
    
}

int DataHandle::disappearAllSameColorDotsWithSelected(){
    
    int count = 0;
    bool dis = true;
    for (int i=0; i<m_drawSpriteArray->count(); i++) {
        
        DrawSprite * node = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
        if (node && ccc4FEqual(m_currentDrawColor, node->m_color)) {
            if (dis) {
                
                node->disappear(true);
                dis = false;
            }
            node->disappear(false);
            
            count ++;
        }
    }
    return count;
}

void DataHandle::draw(void){
    
    CCLayerColor::draw();
    
    
    if (m_drawLine && m_canPlaying) {
        
        glLineWidth(10);
        
        ccColor4B c4b = ccc4BFromccc4F(m_currentDrawColor);
        ccDrawColor4B(c4b.r, c4b.g, c4b.b, c4b.a);
        
        if (m_stackArray!=NULL && m_stackArray->count()>=2) {
            DrawSprite * ds = (DrawSprite *)m_stackArray->objectAtIndex(0);
            CCPoint pos = ds->getDrawNodePosition();
            for (int c=1; c<m_stackArray->count(); c++) {
                ds  = (DrawSprite *)m_stackArray->objectAtIndex(c);
                CCPoint pos1 = ds->getDrawNodePosition();
                ccDrawLine(pos, pos1);
                pos = pos1;
            }
        }
        DrawSprite * ds = (DrawSprite *)m_stackArray->lastObject();
        CCPoint pos = ds->getDrawNodePosition();
        ccDrawLine(pos, m_movePos);
    }
}

void DataHandle::disappearEnd(){
    
    CCArray * dropArray = CCArray::create();
    
    for (int i = 0; i< m_drawSpriteArray->count(); i++) {
        
        DrawSprite * ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(i);
        
        this->calcDropDown(ds, dropArray);
        
    }
    
    for (int i = 0; i<dropArray->count(); i++) {
        
        DrawSprite * ds = (DrawSprite*)dropArray->objectAtIndex(i);
        
        ds->resetDropdown();
    }
    
    for (int i = 0; i< m_drawSpriteArray->count(); i++) {
        
        DrawSprite * ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(i);
        
        if (ds->m_disappear) {
            
            ds->respawn();
            
        }
    }
}

void DataHandle::calcDropDown(DrawSprite* drawSprite,CCArray *resultArray){
    
    if (drawSprite==NULL) {
        return;
    }
    
    while (true) {
        int x = drawSprite->m_x;
        int y = drawSprite->m_y;
        
        int index = y*TOTALY + x;
        int nIndex = (y-1) * TOTALY +x;
        
        if (nIndex<0) {
            break;
        }
        
        DrawSprite * nDS = (DrawSprite *)m_drawSpriteArray->objectAtIndex(nIndex);
        if (nDS!=NULL && nDS->m_disappear) {
            int nX = nDS->m_x;
            int nY = nDS->m_y;
            
            nDS->resetPropertyA(x, y);
            drawSprite->resetPropertyA(nX, nY);
            
            m_drawSpriteArray->exchangeObjectAtIndex(index, nIndex);
            
            if (!resultArray->containsObject(drawSprite) && !drawSprite->m_disappear) {
                
                resultArray->addObject(drawSprite);
            }
        }
        if(nDS!=NULL && !nDS->m_disappear){
            break;
        }
    }
}

void DataHandle::toolDisappearSelected(CCPoint local){
    
    DrawSprite * ds = this->getCurrentSelectSprite(local);
    
    int count = 0;
    
    if (ds!=NULL) {
        
        this->cancelAllDrawNodeBeSelected();
        
        if (m_toolsDisappearType) {
            
            m_currentDrawColor = ds->m_color;
            count = this->disappearAllSameColorDotsWithSelected();
            
        }else{
            
            ds->disappear(true);
            count = 1;
        }
        m_toolsDisappear = false;
        
        if (this->getParent()!=NULL) {
            
            DotPlayingScene * playing = (DotPlayingScene*)this->getParent();
            
            if (playing!=NULL) {
                
                playing->playingScoreAdd(count);
            }
        }
    }
    
}


bool DataHandle::allDrawNodeBeSelected(bool disappearType){
    
    if (m_toolsDisappear) {
        
        return false;
    }
    
    m_toolsDisappearType = disappearType;
    m_toolsDisappear = false;
    
    for (int i=0; i< m_drawSpriteArray->count(); i++) {
        
        DrawSprite *ds = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
        if (ds) {
            
            ds->KeepSelected();
        }
    }
    
    return true;
}


void DataHandle::cancelAllDrawNodeBeSelected(){
    
    for (int i=0; i< m_drawSpriteArray->count(); i++) {
        
        DrawSprite *ds = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
        if (ds) {
            
            ds->unKeepSelected();
        }
    }
}


void DataHandle::startAnimtionDisplay(){
    
    this->setVisible(true);
    if (m_drawSpriteArray!=NULL) {
        
        int count = m_drawSpriteArray->count();
        for (int i = 0; i<count; i++) {
            
            DrawSprite * node = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
            
            if (node!=NULL) {
                
                node->spawnDropdown();
            }
        }
        
    }
}


void DataHandle::startPlaying(){
    
    m_toolsDisappear = false;
    m_canPlaying = true;
    
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    
}

bool DataHandle::ccTouchBegan(CCTouch * touch, CCEvent * event){
    
    if (!m_canPlaying) {
        return false;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchBegine(local);
}

void DataHandle::ccTouchMoved(CCTouch * touch, CCEvent * event){
    
    
    if (!m_canPlaying) {
        return ;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    
    return this->touchMove(local);
    
}
void DataHandle::ccTouchEnded(CCTouch * touch, CCEvent * event){
    
    this->touchEnd();
    
}

void DataHandle::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){
    
    this->touchEnd();
}

void DataHandle::moveOut(){
    
    m_canPlaying = false;
    this->setVisible(false);
    
}

void DataHandle::moveIn(){
    
    m_canPlaying = true;
    this->setVisible(true);
}



