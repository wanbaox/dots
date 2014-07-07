

#include "DataHandle.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "AudioHelper.h"
#include "XYCUtils.h"

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



bool DataHandle::init()
{
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    if (!CCLayerColor::initWithColor(Color_Bg,origin.x+visibleSize.width,origin.y+visibleSize.height-UpHeight-BottomHeight)) {
        
        return false;
    }
    
    m_drawSpriteArray = CCArray::create();
    m_drawSpriteArray->retain();
    
    lastTimeDismiss = XYCUtils::GetCurrentTime();
    
    int tx = m_totalX;
    int ty = m_totalY;
    
    for (int y = 0; y<ty; y++) {
        for (int x = 0; x<tx; x++) {
            
            DrawSprite * drawS = DrawSprite::create();
            drawS->spawnAtXYWH(x, y, DRAWSPRITE_WIDTH, DRAWSPRITE_HEIGH);
            m_drawSpriteArray->addObject(drawS);
            
            this->addChild(drawS,1);
        }
    }
    m_stackArray = CCArray::create();
    
    m_stackArray->retain();
    
    this->setVisible(false);
    
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


int DataHandle::disappearAllSameColorDotsWithSelected(){
    
    int count = 0;
    bool dis = true;
    for (int i=0; i<m_drawSpriteArray->count(); i++) {
        
        DrawSprite * node = (DrawSprite *)m_drawSpriteArray->objectAtIndex(i);
        if (node && m_currentDrawColor==node->m_itemType) {
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
        
        glLineWidth(10);//ccDrawLine线条的宽度
        
        ccColor4B c4b = ccc4BFromccc4F(ccc4fBlue);
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
        if (ds!=NULL) {
            
            CCPoint pos = ds->getDrawNodePosition();
            ccDrawLine(pos, m_movePos);
        }
    }
}

//隐藏drawsprite结束
void DataHandle::disappearEnd(){
    
    CCArray * dropArray = CCArray::create();
    
    for (int i = 0; i< m_drawSpriteArray->count(); i++) {
        
        DrawSprite * ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(i);
        
//        ds->stopAllActions();
        this->calcDropDown(ds, dropArray);
        
    }
    
    //下落动画
    for (int i = 0; i<dropArray->count(); i++) {
        
        DrawSprite * ds = (DrawSprite*)dropArray->objectAtIndex(i);
        
        
        ds->resetDropdown(i==(dropArray->count()-1));
    }
    
    //如果没有下落的item，就直接调用检查是否有空列的方法
    if (dropArray->count()==0) {
        
        checkEmptyColumn();
    }
    
    if (SettingHelper::getGameType()!=GAME_TYPE_NOTIMELIMIT) {
        
        for (int i = 0; i< m_drawSpriteArray->count(); i++) {
            
            DrawSprite * ds = (DrawSprite*)m_drawSpriteArray->objectAtIndex(i);
            
            if (ds->m_disappear) {
                
                ds->respawn();
                
            }
        }
    }
    
}

void DataHandle::checkEmptyColumn(){
    
//    std::vector<int> emptyColumns;
    
    CCArray * moveLeftArray = CCArray::create();
    
    int emptyColumn = -1;//前面空列的位置
    
    for (int x = 0; x< m_totalX; x++) {
        
        DrawSprite * nDS = (DrawSprite*)m_drawSpriteArray->objectAtIndex(x);
        
        if (nDS!=NULL && !nDS->m_disappear) {
            
            if (emptyColumn!=-1) {
                //前面有空列
                int numberOfEmptyColumn = x-emptyColumn;//前面空列的数量
                
                for (int y = 0 ; y<m_totalY; y++) {
                    
                    
                    int indexLeft = y*m_totalX + x-numberOfEmptyColumn;
                    int indexRight = y * m_totalX +x;
                    
                    
                    
                    DrawSprite * dsLeft = (DrawSprite*)m_drawSpriteArray->objectAtIndex(indexLeft);
                    DrawSprite * dsRight = (DrawSprite*)m_drawSpriteArray->objectAtIndex(indexRight);
                    
                    if (dsRight!=NULL && !dsRight->m_disappear) {
                        
                        
                        moveLeftArray->addObject(dsRight);
                        
                        dsLeft->resetPropertyA(x, y);
                        dsRight->resetPropertyA(x-numberOfEmptyColumn, y);
                        
                        m_drawSpriteArray->exchangeObjectAtIndex(indexLeft, indexRight);
                        
                        CCLog("numberOfEmptyColumn:%i,y:%i,x move to:%i",numberOfEmptyColumn,y,x-numberOfEmptyColumn);
                    }else{
                        
                        emptyColumn = -1;
                        x -=numberOfEmptyColumn;
                        break;
                    }
                    
                    if (y==(m_totalY-1)) {
                        
                        emptyColumn=-1;
                        x -=numberOfEmptyColumn;
                    }
                        
                    
                }
            }
            
        }else{
        
            //空列
            if (emptyColumn==-1) {
                
                emptyColumn = x;
            }
            
        }
    }

    
    
    int count = moveLeftArray->count();
    for (int i = 0; i<count; i++) {
        
        DrawSprite * ds = (DrawSprite*)moveLeftArray->objectAtIndex(i);
        
        if (i == (count-1)) {
            
            
            ds->moveToLeft(true);
            return;
        }
        
        ds->moveToLeft(false);
    }
    
    if (count==0) {
        
        m_canPlaying = true;
        hasMoreMatched();//判断是否还有可以消除的items
    }
    
}

void DataHandle::calcDropDown(DrawSprite* drawSprite,CCArray *resultArray){
    
    if (drawSprite==NULL) {
        return;
    }
    
    while (true) {
        int x = drawSprite->m_x;
        int y = drawSprite->m_y;
        
        int index = y*m_totalX + x;
        int nIndex = (y-1) * m_totalX +x;
        
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
            
            m_currentDrawColor = ds->m_itemType;
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
                
                node->respawn();
                
                
                if (i == m_drawSpriteArray->count()-1) {
                    
                    
                    node->spawnDropdown(true);
                }else{
                
                    
                    node->spawnDropdown(false);
                }
            }
        }
        
    }
}


void DataHandle::startPlaying(){
    
    count4Continue = 0;
    
    lastTimeDismiss = XYCUtils::GetCurrentTime();
    
    m_toolsDisappear = false;
    m_canPlaying = true;
    m_stageCleared = false;
    
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    
}

//bool DataHandle::ccTouchBegan(CCTouch * touch, CCEvent * event){
//    
//    if (!m_canPlaying) {
//        return false;
//    }
//    
//    CCPoint touchLocation = touch->getLocationInView();
//    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
//    
//    CCPoint local = this->convertToNodeSpace(touchLocation);
//    
//    
//    return this->touchBegine(local);
//}
//
//void DataHandle::ccTouchMoved(CCTouch * touch, CCEvent * event){
//    
//    
//    if (!m_canPlaying) {
//        return ;
//    }
//    
//    CCPoint touchLocation = touch->getLocationInView();
//    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
//    
//    CCPoint local = this->convertToNodeSpace(touchLocation);
//    
//    
//    return this->touchMove(local);
//    
//}
//void DataHandle::ccTouchEnded(CCTouch * touch, CCEvent * event){
//    
//    this->touchEnd();
//    
//}
//
//void DataHandle::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent){
//    
//    this->touchEnd();
//}

void DataHandle::moveOutForNextLevel()
{
    
    for (int y = 0; y<m_totalY; y++) {
        
        for (int x = 0; x<m_totalX; x++) {
            
            int index = y*m_totalX+x;
            DrawSprite *ds = (DrawSprite *)m_drawSpriteArray->objectAtIndex(index);
            ds->disappear(false);
            ds->spawnAtXYWH(x, y, DRAWSPRITE_WIDTH, DRAWSPRITE_HEIGH);

        }
    }
    
    CCMoveBy * moveto = CCMoveBy::create(0, ccp(-this->getContentSize().width, 0));
    this->runAction(moveto);
    
}

//和moveOutForNextLevel相比，这个移出是没有动画效果的
void DataHandle::moveOutForRestart()
{
    
    this->unscheduleAllSelectors();
    
    for (int y = 0; y<m_totalY; y++) {
        
        for (int x = 0; x<m_totalX; x++) {
            
            int index = y*m_totalX+x;
            DrawSprite *ds = (DrawSprite *)m_drawSpriteArray->objectAtIndex(index);
            ds->disappearImmediate();
            ds->spawnAtXYWH(x, y, DRAWSPRITE_WIDTH, DRAWSPRITE_HEIGH);
            
        }
    }
    
}

void DataHandle::moveOut(){
    
    
    
    CCMoveBy * moveto = CCMoveBy::create(0.5, ccp(-this->getContentSize().width, 0));
    
//    CCEaseBackIn * action = CCEaseBackIn::create(moveto);
//    this->runAction(action);
    
//    bgLayer->setPosition(ccp((origin.x+visibleSize.width)*3/2, (origin.y+visibleSize.height)/2) );
//    CCMoveTo * moveTo = CCMoveTo::create(0.6, ccp((origin.x+visibleSize.width)/2, (origin.y+visibleSize.height)/2+50));
    CCEaseExponentialOut * action0 = CCEaseExponentialOut::create(moveto);
    this->runAction(action0);
    

    
//    m_canPlaying = false;
//    this->setVisible(false);
    
    this->scheduleOnce(schedule_selector(DataHandle::moveOutCallBack), 0.5);
    
}

void DataHandle::moveOutCallBack(){
    
    m_canPlaying = false;
    this->setVisible(false);

}

void DataHandle::moveIn(){
    
    this->setVisible(true);

    
    CCMoveBy * moveto = CCMoveBy::create(0.5, ccp(this->getContentSize().width, 0));
    CCEaseExponentialOut * action0 = CCEaseExponentialOut::create(moveto);
    this->runAction(action0);
    
    this->scheduleOnce(schedule_selector(DataHandle::moveInCallBack), 0.5);
    
//    m_canPlaying = true;
}


void DataHandle::moveInCallBack(){
    
    m_canPlaying = true;
//    this->setVisible(true);
    
}


void DataHandle::showGotScore(CCPoint position, int score)
{
    
    
    // CCLabelBMFont
//    CCLabelBMFont * m_labelGotScore = CCLabelBMFont::create(CCString::createWithFormat("%i",score)->getCString(), "futura-48.fnt");
//    
//    m_labelGotScore->setAnchorPoint(ccp(0.5f, 0.5f));
//    
//    this->addChild(m_labelGotScore,100);
//    
//    CCPoint local = calcMidPos(position);
//    
//    
//    m_labelGotScore->setPosition(local);
//    m_labelGotScore->setScale(0);
//    
//    CCSpawn * spawn = CCSpawn::create(CCFadeIn::create(0),CCScaleTo::create(0.2, 1.5),CCMoveBy::create(0.4f, ccp(0, 100)),CCSequence::create(CCDelayTime::create(0.4),CCFadeOut::create(0.4),NULL),NULL);
//    
//    
//    m_labelGotScore->runAction(CCSequence::create(spawn,CCCallFunc::create(m_labelGotScore, callfunc_selector(DataHandle::removeSprite)),NULL));
    
}

void DataHandle::removeSprite(CCNode * node){

    node->removeFromParentAndCleanup(true);
}

int DataHandle::getCurrentScore(int count)
{

    int score;
    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC:
            
            score = 10*count+5*(count-2)*count;
            
                
            break;
        case GAME_TYPE_CLASSIC_LEVEL:
            
            score = 10*count+5*(count-2)*count;
            
            
            break;
        case GAME_TYPE_SPEED:
            
            score = (count==1)?-count*50:10*count+5*(count-2)*count;
            break;
        case GAME_TYPE_SPEED_LEVEL:
            
            score = (count==1)?-count*50:10*count+5*(count-2)*count;
            break;
        case GAME_TYPE_NOTIMELIMIT:
//            20  10*2
//            45  10*3+5*3
//            80  10*4+10*4*
//            125 10*5+15*5
//            180 10*6+20*6
            
            score = 10*count+5*(count-2)*count;
            break;
        default:
            break;
    }
    
    
    
    if (this->getParent()!=NULL) {
        
        ((DotPlayingScene*)this->getParent())->playingScoreAdd(score);
    }
    return score;
}

CCPoint DataHandle::calcMidPos(CCPoint currentPressed){

    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC:
        {
            
            DrawSprite * ds = (DrawSprite *)m_stackArray->lastObject();

            
            return ccp(ds->getPositionX(), ds->getPositionY());
            break ;
        }
        case GAME_TYPE_CLASSIC_LEVEL:
        {
            
            DrawSprite * ds = (DrawSprite *)m_stackArray->lastObject();
            
            
            return ccp(ds->getPositionX(), ds->getPositionY());
            break ;
        }
        case GAME_TYPE_SPEED:
            
            return currentPressed;
            break;
        case GAME_TYPE_SPEED_LEVEL:
            
            return currentPressed;
            break;
        case GAME_TYPE_NOTIMELIMIT:
            
            return currentPressed;
            break;
        default:
            break;
    }
    
    return ccp(100, 100);
}

void DataHandle::showAnnouncer(int announcer){
    
//    CCSprite * announcerSprite;
    
    if (announcer>=Announcer5) {
        
        AudioHelper::playAnnouncer(Announcer5);
//        announcerSprite = CCSprite::create("announcer_5.png");
    }else if (announcer>=Announcer4) {
        
        AudioHelper::playAnnouncer(Announcer4);
//        announcerSprite = CCSprite::create("announcer_4.png");
    }else if (announcer>=Announcer3) {
        
        AudioHelper::playAnnouncer(Announcer3);
//        announcerSprite = CCSprite::create("announcer_3.png");
    }else if (announcer>=Announcer2) {
        
        AudioHelper::playAnnouncer(Announcer2);
//        announcerSprite = CCSprite::create("announcer_2.png");
    }else if (announcer>=Announcer1) {
        
        AudioHelper::playAnnouncer(Announcer1);
//        announcerSprite = CCSprite::create("announcer_1.png");
    }else{
    
        return;
    }
    
//    if (announcerSprite!=NULL) {
//        
////        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh");
////        
////        CCSize s = CCDirector::sharedDirector()->getWinSize();
////        sn->setPosition(ccp(s.width/2, s.height/2));
////        
////        addChild(sn);
//        
//        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//        
//        CCPoint local = ccp((origin.x+visibleSize.width)/2,(origin.y+visibleSize.height)/2);
//        
//        announcerSprite->setPosition(local);
//        announcerSprite->setScale(0);
//        
//        this->addChild(announcerSprite,100);
//        
//        
//        CCSequence *sequeue = CCSequence::create(CCScaleTo::create(0.4f, 1.0f, 1.0f),CCFadeOut::create(0.2f),CCCallFunc::create(announcerSprite, callfunc_selector(DataHandle::removeSprite)),NULL);
//        announcerSprite->runAction(sequeue);
//        
//        
//
//    }
}

