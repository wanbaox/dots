#include "DotPlayingScene.h"

USING_NS_CC;

CCScene* DotPlayingScene::scene()
{
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
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setAnchorPoint(ccp(0,0));
    
    m_data = DataHandle::create();;
    
    this->addChild(m_data);
    
    m_hudController = DotHudController::create();
    
    this->addChild(m_hudController);
    
    return true;
}

void DotPlayingScene::startDotGame(){
    
    m_data->startAnimtionDisplay();
    m_data->startPlaying();
    this->startTimerCounter();
    
}

void DotPlayingScene::playingScoreAdd(int score){
    
    m_score += score;
    CCString * scores = CCString::createWithFormat("%d",m_score);
    m_hudController->resetScoreString(scores);
    
}


void DotPlayingScene::startTimerCounter(){
    
    m_pause = false;
    m_timeCounter = 60;
    this->schedule(schedule_selector(DotPlayingScene::tick));
    
}

void DotPlayingScene::tick(float dt){
    
    if (!m_pause) {
        m_delta +=dt;
    }
    
    if (m_delta>=0.9999) {
        m_delta = 0.0;
        m_timeCounter -=1;
        if (m_timeCounter<=0) {
#warning gameover
            m_hudController->resetTimeString(CCString::createWithFormat("%d",m_timeCounter));
            m_data->moveOut();
            
            //            [m_hudController gamePause];
            m_hudController->currentGameOver(m_score);
            this->unscheduleAllSelectors();
            
        }else{
            
            m_hudController->resetTimeString(CCString::createWithFormat("%d",m_timeCounter));
        }
    }
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
