#ifndef __DOTPLAYING_SCENE_H__
#define __DOTPLAYING_SCENE_H__

#include "cocos2d.h"
#include "config.h"
#include "DataHandle.h"
#include "DotHudController.h"

USING_NS_CC;

class DotPlayingScene : public cocos2d::CCLayer
{
    
    DotHudController * m_hudController;

    DataHandle * m_data;
    
    float m_delta;
    
    int m_score;
    
    int m_timeCounter;
    
    bool m_pause;
    
public:
    
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(DotPlayingScene);
    
    void startDotGame();
    
    void startTimerCounter();
    
    void playingScoreAdd(int score);
    
    void playerUsedToolDisappear(PLAYERTOOLTYPE type);
    
    void pauseGame();
    void resumeGame();
    
    void tick(float dt);
    
};

#endif // __DOTPLAYING_SCENE_H__
