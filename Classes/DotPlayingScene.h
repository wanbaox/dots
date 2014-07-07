#ifndef __DOTPLAYING_SCENE_H__
#define __DOTPLAYING_SCENE_H__

#include "cocos2d.h"
#include "config.h"
#include "DataHandle.h"
#include "DotHudController.h"

USING_NS_CC;

class DotPlayingScene : public cocos2d::CCLayerColor
{
    
public:
    
    
    DotHudController * m_hudController;

    DataHandle * m_data;
    
    float m_delta;
    
    int m_score;
    
    int m_timeCounter;
    
    bool m_pause;
    
    int m_level;
    
public:
    
    DotPlayingScene();
	~DotPlayingScene();
    
    virtual bool init();  

    static cocos2d::CCScene* scene(bool isContinueGame);
    
    CREATE_FUNC(DotPlayingScene);
    
    void startDotGame(bool isReStart);
    
    void startTimerCounter();
    
    void playingScoreAdd(int score);
    
    void playerUsedToolDisappear(PLAYERTOOLTYPE type);
    
    void pauseGame();
    void resumeGame();
    
    void tick(float dt);
    
    long getCurrrentGoal(int level);
    
    void gotoNextLevel();
    void gameFailed();
    void gameNormalEnded();
    
};

#endif // __DOTPLAYING_SCENE_H__
