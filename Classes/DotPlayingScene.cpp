#include "DotPlayingScene.h"
#include "DataHandle4Tap.h"
#include "DataHandleClassic.h"
#include "AudioHelper.h"
#include "NormalEndLayer.h"
#include "CCiAd.h"
#include "DataHandle4NoTimeLimit1Tap.h"
#include "XYCUtils.h"
#include "IntroLayer.h"

USING_NS_CC;

static bool m_isContiuneGame;


DotPlayingScene::DotPlayingScene()
{
    
}

DotPlayingScene::~DotPlayingScene()
{
    
    
    
//    m_hudController->m_downStateLayer->setColor(Color_Up_Down3B);
    
    CCiAd::deletAdBanner();
    
    
}

CCScene* DotPlayingScene::scene(bool isContinueGame)
{
    
    
    m_isContiuneGame = isContinueGame;
    
    if (m_isContiuneGame) {
        
        SettingHelper::setGameType(SettingHelper::getLastGameType());
    }
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DotPlayingScene *layer = DotPlayingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
    
}

// on "init" you need to initialize your instance
bool DotPlayingScene::init()
{
    
    if (!CCLayerColor::initWithColor(Color_Bg))
    {
        return false;
    }
    
    m_score=0;
    m_level=1;
    
    extern int m_totalX;
    extern int m_totalY;
    m_totalX = DataHandle::GetXNumber();
    m_totalY = DataHandle::GetYNumber();
    
    
    this->setAnchorPoint(ccp(0,0));
 
    
    switch (m_isContiuneGame?SettingHelper::getLastGameType():SettingHelper::getGameType()) {
            
        case GAME_TYPE_CLASSIC:
            
        {
            
             m_data = DataHandleClassic::create();;
            break;
        }
        case GAME_TYPE_CLASSIC_LEVEL:
            
        {
            
            m_data = DataHandleClassic::create();;
            break;
        }
        case GAME_TYPE_SPEED:
        {
            
            m_data = DataHandle4Tap::create();
            break;
        }
            
        case GAME_TYPE_SPEED_LEVEL:
        {
            
            m_data = DataHandle4Tap::create();
            break;
        }
        case GAME_TYPE_NOTIMELIMIT:
        {
            
            m_data = DataHandle4NoTimeLimit1Tap::create();
            break;
        }
        default:
            break;
            
    }
    
    if (m_isContiuneGame) {
        
        m_level = SettingHelper::getLastLevel();
        m_score = SettingHelper::getLastScore();
    }
    
    
    m_hudController = DotHudController::create();
    
    this->addChild(m_hudController);
    this->addChild(m_data);
    m_data->setPosition(ccp(0, BottomHeight));
    
    CCString * scores = CCString::createWithFormat("%i",m_score);
    m_hudController->resetScoreString(scores);
    
    AudioHelper::playGameStart();
    
    
    
//    m_hudController->m_downStateLayer->setColor(Color_Bg3B);
    
    CCiAd::addAdBanner(true);
    
    
    
    
    return true;
}

void DotPlayingScene::startDotGame(bool isReStart){
    
    
    if (isReStart) {
        
        m_level = SettingHelper::getLastLevel();
//        m_timeCounter = SettingHelper::getLastTime();
        m_score = SettingHelper::getLastScore();
        
    }else{
    
        SettingHelper::setLastLevel(m_level);
        SettingHelper::setLastScore(m_score);
        SettingHelper::setLastGameType(SettingHelper::getGameType());
//        SettingHelper::setLastTime(TIME4ONELEVEL);
    }
    
    
    
    
    m_data->startAnimtionDisplay();
    
    if (SettingHelper::getGameType()!=GAME_TYPE_NOTIMELIMIT) {
        
        this->startTimerCounter();
    }
    
}

void DotPlayingScene::playingScoreAdd(int score){
    
    m_score += score;
    m_hudController->m_upstateLayer->scoreAdded(score);
//    CCString * scores = CCString::createWithFormat("%i",m_score);
//    m_hudController->resetScoreString(scores);
    
}


void DotPlayingScene::startTimerCounter(){
    
    m_pause = false;
    if (SettingHelper::getGameType() == GAME_TYPE_SPEED_LEVEL || SettingHelper::getGameType() == GAME_TYPE_CLASSIC_LEVEL) {
        
        m_timeCounter = TIME4ONELEVELHalf;
    }else{
    
        
        m_timeCounter = TIME4ONELEVEL;
    }
    this->schedule(schedule_selector(DotPlayingScene::tick),1.0);
    
}

void DotPlayingScene::tick(float dt){
    
    long currentTime = XYCUtils::GetCurrentTime();
    
    if ((currentTime-m_data->lastTimeDismiss)>2500) {
        
        //需要给用户一点提示
        m_data->alert();
    }
    
    
    if (m_pause) {
        
        return;
    }
    m_timeCounter -=1;
    if (m_timeCounter<0) {
        
        
        //游戏中玩家选中后，disappear item的时候有动画，会有延迟，这时候如果刚好时间到了，两个同时进行的话，会有混乱的情况，所以这里先让对方完成，再提示游戏结束（时间到了）
        if (!m_data->m_canPlaying) {
            
            return;
        }
        
#warning gameover
        this->unscheduleAllSelectors();
        
        m_data->m_canPlaying = false;
        
        m_hudController->resetTimeString(0);
        
        switch (SettingHelper::getGameType()) {
            case GAME_TYPE_CLASSIC:
                
                this->gameNormalEnded();
                break;
            case GAME_TYPE_CLASSIC_LEVEL:
                
                if (m_score<getCurrrentGoal(m_level)) {
                    
                    this->gameFailed();
                    
                }else{
                    
                    //进入下一level
                    
                    this->gotoNextLevel();
                    
                }
                
                break;
            case GAME_TYPE_SPEED:
                
                this->gameNormalEnded();
                break;
            case GAME_TYPE_SPEED_LEVEL:
                
                if (m_score<getCurrrentGoal(m_level)) {
                    
                    this->gameFailed();
                    
                }else{
                    
                    //进入下一level
                    
                    this->gotoNextLevel();
                    
                }
                
                break;
                
            default:
                break;
        }
        
    }else{
        
        if (m_timeCounter<=6) {
            
            AudioHelper::playTimeUp();
        }
        
        m_hudController->resetTimeString(m_timeCounter);
    }
}

void DotPlayingScene::gameNormalEnded()
{
    
    
    
    m_hudController->m_pause = true;
    m_pause = true;
    
    
    int count = m_data->m_stackArray->count();
    
    for (int i =0; i < count; i++) {
        
        DrawSprite * ds = (DrawSprite *)m_data->m_stackArray->objectAtIndex(i);
        
        ds->selectedType();
    }
    
    m_data->m_stackArray->removeAllObjects();
    
    m_data->moveOut();//隐藏所有items
    
   
    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC:
            
            if (m_score>SettingHelper::getToppestScore4Classic()) {
                
                SettingHelper::setToppestScore4Classic(m_score);
            }
            m_hudController->gameNormalEned(m_score>SettingHelper::getToppestScore4Classic());
            break;
            
        case GAME_TYPE_CLASSIC_LEVEL:
            
            if (m_score>SettingHelper::getToppestScore4ClassicLevel()) {
                
                SettingHelper::setToppestScore4ClassicLevel(m_score);
            }
            m_hudController->gameNormalEned(m_score>SettingHelper::getToppestScore4ClassicLevel());
            break;
            
        case GAME_TYPE_SPEED:
            
            if (m_score>SettingHelper::getToppestScore4Tap()) {
                
                SettingHelper::setToppestScore4Tap(m_score);
            }
            m_hudController->gameNormalEned(m_score>SettingHelper::getToppestScore4Tap());
            break;
            
        case GAME_TYPE_SPEED_LEVEL:
            
            if (m_score>SettingHelper::getToppestScore4TapLevel()) {
                
                SettingHelper::setToppestScore4TapLevel(m_score);
            }
            m_hudController->gameNormalEned(m_score>SettingHelper::getToppestScore4TapLevel());
            break;
            
        case GAME_TYPE_NOTIMELIMIT:
            
            if (m_score>SettingHelper::getToppestScore4NoLimit()) {
                
                SettingHelper::setToppestScore4NoLimit(m_score);
            }
            m_hudController->gameNormalEned(m_score>SettingHelper::getToppestScore4NoLimit());
            break;
            
        default:
            break;
    }
    
    
    
}

void DotPlayingScene::gameFailed()
{
    
    m_hudController->m_pause = true;
    m_pause = true;
    
    
    int count = m_data->m_stackArray->count();
    
    for (int i =0; i < count; i++) {
        
        DrawSprite * ds = (DrawSprite *)m_data->m_stackArray->objectAtIndex(i);
        
        ds->selectedType();
    }
    
    m_data->m_stackArray->removeAllObjects();
    
    m_data->moveOut();//隐藏所有items
    
    m_hudController->gameFailed();
}

void DotPlayingScene::gotoNextLevel()
{

    int count = m_data->m_stackArray->count();
    
    for (int i =0; i < count; i++) {
        
        DrawSprite * ds = (DrawSprite *)m_data->m_stackArray->objectAtIndex(i);
        
        ds->selectedType();
    }
    
    m_data->m_stackArray->removeAllObjects();
    
    
    m_level++;
    
    m_data->moveOut();//隐藏所有items
    
    m_hudController->gotoNextLevel();
}


long DotPlayingScene::getCurrrentGoal(int level)
{
    long goal;
    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC_LEVEL:
            
            if (level==1) {
                goal = 500;
            }else if (level==2) {
                goal = 1000;
            }else{
                
                int during = 6;//每隔during个之后，多加500
                long l2 =500*(level/during);
                
                goal = (1000+2*500*(level-2)+l2);
                
            }

            break;
        case GAME_TYPE_SPEED_LEVEL:
            
            if (level==1) {
                goal = 1000;
            }else if (level==2) {
                goal = 2000;
            }else{
                
                int during = 3;//每隔during个之后，多加1500
                long l2 =2500*(level/during);
                
                goal = (2000+2000*(level-2)+l2);
                
            }

            break;
        case GAME_TYPE_NOTIMELIMIT:
            
            if (level==1) {
                goal = 1000;
            }else if (level==2) {
                goal = 2500;
            }else{
                
                int during = 6;//每隔during个之后，多加1000
                long l2 =1000*(level/during);
                
                goal = (2500+2*1000*(level-2)+l2);
                
            }
            
            break;
            
        default:
            break;
    }
    return goal;
}

void DotPlayingScene::pauseGame(){
    
    m_pause = true;
    
    
    m_data->moveOut();
}

void DotPlayingScene::resumeGame(){
    
    m_pause = false;
    m_data->moveIn();
}

void DotPlayingScene::playerUsedToolDisappear(PLAYERTOOLTYPE type){
    
    if (type == tooltime) {
        
    }else{
        if (type == toolDisappearAll) {
            
            if(m_data->allDrawNodeBeSelected(true)){
                
            }
        }else{
            
            if(m_data->allDrawNodeBeSelected(false)){
                
            }
        }
    }
}
