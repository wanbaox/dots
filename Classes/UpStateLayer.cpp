

#include "UpStateLayer.h"
#include "DotHudController.h"
#include "SimpleAudioEngine.h"
#include "AudioHelper.h"
#include "DotPlayingScene.h"
#include "SettingHelper.h"
#include "CCLocalizedString.h"

float paddingItem = 10.0f;

UpStateLayer::UpStateLayer()
{
    
}

UpStateLayer::~UpStateLayer()
{
    
}

bool UpStateLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Up_Down,origin.x+visibleSize.width,UpHeight)) {
        
        return false;
    }
    
    m_Level_bg = CCMenuItem::create(this, menu_selector(UpStateLayer::menuBePressed));
    m_Top_bg = CCMenuItem::create(this, menu_selector(UpStateLayer::menuBePressed));
    m_Score_bg = CCMenuItem::create(this, menu_selector(UpStateLayer::menuBePressed));
    

    m_Level_bg->ignoreAnchorPointForPosition(false);
    m_Top_bg->ignoreAnchorPointForPosition(false);
    m_Score_bg->ignoreAnchorPointForPosition(false);
    m_Level_bg->setAnchorPoint(ccp(0, 0.5));
    m_Top_bg->setAnchorPoint(ccp(0, 0.5));
    m_Score_bg->setAnchorPoint(ccp(0, 0.5));
    
    
    
    //menu
    CCMenu * menu = CCMenu::create(m_Level_bg,m_Top_bg,m_Score_bg,NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    if (SettingHelper::getGameType() == GAME_TYPE_CLASSIC || SettingHelper::getGameType() == GAME_TYPE_SPEED) {
        
        m_Score_bg->setContentSize(CCSizeMake(this->getContentSize().width/2, UpHeight));
        m_Top_bg->setContentSize(CCSizeMake(this->getContentSize().width/2, UpHeight));
        
        //最高分/得分
        m_Top_bg->setPosition(ccp(0,UpHeight/2));
        m_Score_bg->setPosition(ccp(this->getContentSize().width/2,UpHeight/2));
        
    }else{
        
        m_Level_bg->setContentSize(CCSizeMake(this->getContentSize().width/3, UpHeight));
        m_Score_bg->setContentSize(CCSizeMake(this->getContentSize().width/3, UpHeight));
        
        //等级/目标/得分
        m_Level_bg->setPosition(ccp(0,UpHeight/2));
        m_Score_bg->setPosition(ccp(this->getContentSize().width/2,UpHeight/2));
        
    }

    title_score = CCLabelTTF::create(CCLocalizedString("score", ""), "fonts/Josefin Sans.ttf", 12);
    title_level = CCLabelTTF::create(CCLocalizedString("level", ""), "fonts/Josefin Sans.ttf", 12);
    title_top = CCLabelTTF::create(CCLocalizedString("top", ""), "fonts/Josefin Sans.ttf", 12);
    title_goal = CCLabelTTF::create(CCLocalizedString("goal", ""), "fonts/Josefin Sans.ttf", 12);
    
    title_score->setAnchorPoint(ccp(0, 0.5));
    title_score->setColor(Color_Text);
    
    title_top->setAnchorPoint(ccp(0, 0.5));
    title_top->setColor(Color_Text);
    
    title_level->setAnchorPoint(ccp(0, 0.5));
    title_level->setColor(Color_Text);
    
    title_goal->setAnchorPoint(ccp(0, 0.5));
    title_goal->setColor(Color_Text);
    
    
    
    m_Level_bg->addChild(title_level);
    m_Level_bg->addChild(title_goal);
    m_Top_bg->addChild(title_top);
    m_Score_bg->addChild(title_score);
    
    

    
    
    //labels
    m_labelScore = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);
    m_labelLevel = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);
    m_labelGoal = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);
    m_labelTop = CCLabelTTF::create("0", "fonts/Josefin Sans.ttf", 20);

    
    
    m_labelTop->setAnchorPoint(ccp(0, 0.5));
    m_labelTop->setColor(Color_Text);
    
    m_labelScore->setAnchorPoint(ccp(0, 0.5));
    m_labelScore->setColor(Color_Text);
    
    m_labelLevel->setAnchorPoint(ccp(0, 0.5));
    m_labelLevel->setColor(Color_Text);
    
    m_labelGoal->setAnchorPoint(ccp(0, 0.5));
    m_labelGoal->setColor(Color_Text);
    
    m_Level_bg->addChild(m_labelLevel);
    m_Level_bg->addChild(m_labelGoal);
    m_Top_bg->addChild(m_labelTop);
    m_Score_bg->addChild(m_labelScore);
    
    
    
    //设置位置
    resetItemPosition();
    
    
    //progress
    CCSprite *psSprite1 = CCSprite::create("progress_bar.png");
    
    //利用精灵创建进度条，并设置一些属性
    progresstime1 = CCProgressTimer::create(psSprite1);    //初始化CCProgressTimer
    progresstime1->setPercentage(100.0f);    //设置初始百分比的值
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    progresstime1->setMidpoint(ccp(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    progresstime1->setBarChangeRate(ccp(1, 0));
    progresstime1->setType(kCCProgressTimerTypeBar);    //设置进度条为水平
    progresstime1->setAnchorPoint(ccp(0, 0));
    progresstime1->setPosition(ccp(0, 0));    //放置进度条位置
    
    
    this->addChild(progresstime1, 100);    //加入Layer中
    
    
    
    this->scheduleUpdate();
    
    
    this->setVisible(false);
    
    return true;
}

void UpStateLayer::resetItemPosition()
{

    //设置位置
    if (SettingHelper::getGameType() == GAME_TYPE_CLASSIC || SettingHelper::getGameType() == GAME_TYPE_SPEED) {
        
        title_top->setPosition(ccp(2*paddingItem, m_Top_bg->getContentSize().height/2));
        
        
        m_labelTop->setPosition(ccp(title_top->getContentSize().width+title_top->getPosition().x+paddingItem/2, m_Top_bg->getContentSize().height/2));
        
        title_score->setPosition(ccp(2*paddingItem, m_Score_bg->getContentSize().height/2));
        
        m_labelScore->setPosition(ccp(title_score->getContentSize().width+title_score->getPosition().x+paddingItem/2, m_Score_bg->getContentSize().height/2));
        
    }else{
        
        title_level->setPosition(ccp(paddingItem, m_Level_bg->getContentSize().height/2));
        
        m_labelLevel->setPosition(ccp(title_level->getContentSize().width+title_level->getPosition().x+paddingItem/2,m_Level_bg->getContentSize().height/2));
        
        title_goal->setPosition(ccp(m_labelLevel->getContentSize().width+m_labelLevel->getPosition().x+2*paddingItem,m_Level_bg->getContentSize().height/2));
        
        
        m_labelGoal->setPosition(ccp(title_goal->getContentSize().width+title_goal->getPosition().x+paddingItem/2, m_Level_bg->getContentSize().height/2));
        
        title_score->setPosition(ccp(3*paddingItem+paddingItem/2, m_Score_bg->getContentSize().height/2));
        
        
        m_labelScore->setPosition(ccp(title_score->getContentSize().width+title_score->getPosition().x+paddingItem/2, m_Score_bg->getContentSize().height/2));
    }
}

void UpStateLayer::resetProgressBar(int currentTime){
    
    float ct1;
    if (SettingHelper::getGameType() == GAME_TYPE_CLASSIC || SettingHelper::getGameType() == GAME_TYPE_SPEED) {
        
        ct1 = currentTime*100.0f/TIME4ONELEVEL;
    }else if (SettingHelper::getGameType() == GAME_TYPE_CLASSIC_LEVEL || SettingHelper::getGameType() == GAME_TYPE_SPEED_LEVEL) {
        
        ct1 = currentTime*100.0f/TIME4ONELEVELHalf;
    }
    
    //如果进度条小于100%，设置进度条的百分比
    if (ct1 <= 100)
    {
        
        progresstime1->setPercentage(ct1);
        
    }
}

void UpStateLayer::startAnimationDisplay(int level,long goal){
    
    switch (SettingHelper::getGameType()) {
        case GAME_TYPE_CLASSIC:
            
            m_Top_bg->setVisible(true);
            m_Level_bg->setVisible(false);
//            m_Goal_bg->setVisible(false);
            m_Score_bg->setVisible(true);

            m_labelTop->setString(CCString::createWithFormat("%i",SettingHelper::getToppestScore4Classic())->getCString());
            
            break;
        case GAME_TYPE_CLASSIC_LEVEL:
            
            
            m_Top_bg->setVisible(false);
            m_Level_bg->setVisible(true);
//            m_Goal_bg->setVisible(true);
            m_Score_bg->setVisible(true);
            
            
            m_labelTop->setString(CCString::createWithFormat("%i",SettingHelper::getToppestScore4ClassicLevel())->getCString());
            
            break;
        case GAME_TYPE_SPEED:
            
            m_Top_bg->setVisible(true);
            m_Level_bg->setVisible(false);
//            m_Goal_bg->setVisible(false);
            m_Score_bg->setVisible(true);
            
            m_labelTop->setString(CCString::createWithFormat("%i",SettingHelper::getToppestScore4Tap())->getCString());
            
            break;
        case GAME_TYPE_SPEED_LEVEL:
            
            m_Top_bg->setVisible(false);
            m_Level_bg->setVisible(true);
//            m_Goal_bg->setVisible(true);
            m_Score_bg->setVisible(true);
            
            m_labelTop->setString(CCString::createWithFormat("%i",SettingHelper::getToppestScore4TapLevel())->getCString());

            break;
        case GAME_TYPE_NOTIMELIMIT:
            
            m_Top_bg->setVisible(false);
            m_Level_bg->setVisible(true);
//            m_Goal_bg->setVisible(true);
            m_Score_bg->setVisible(true);
            
            m_labelTop->setString(CCString::createWithFormat("%i",SettingHelper::getToppestScore4NoLimit())->getCString());
            break;
            
        default:
            break;
    }
    
    
    m_labelLevel->setString(CCString::createWithFormat("%i",level)->getCString());
    m_labelGoal->setString(CCString::createWithFormat("%li",goal)->getCString());
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->setVisible(true);
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, origin.y+visibleSize.height));
    
    CCMoveBy * moveTo2 = CCMoveBy::create(0.2, ccp(0, -UpHeight));
    
    this->runAction(CCSequence::create(CCEaseBackOut::create(moveTo2),NULL));
    
    
    
}

//隐藏的动画
void UpStateLayer::moveOut(){
    
    this->setVisible(true);
    
    CCMoveBy * moveTo2 = CCMoveBy::create(0.2, ccp(0, UpHeight));
    
    this->runAction(CCSequence::create(CCEaseBackIn::create(moveTo2),NULL));
    
}

void UpStateLayer::callBack0(CCObject* sender){
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
        dhc->startGame();

    }
}
void UpStateLayer::resetScoreString(CCString * string){
    
    m_score = string->intValue();
    m_scoreShowed = m_score;
    
    m_labelScore->setString(string->getCString());
}

void UpStateLayer::scoreAdded(int score){
    
    m_score += score;
    
}

void UpStateLayer::resetToppestScore(CCString * string){
    
    m_labelTop->setString(string->getCString());
    
}

void UpStateLayer::resetTimeString(CCString * string){
    
//    m_labelTime->setString(string->getCString());
}

void UpStateLayer::menuBePressed(CCObject* sender){
    
    AudioHelper::playMenuPress();
    
    if (this->getParent()!=NULL) {
        
        DotHudController * dhc = (DotHudController*)this->getParent();
//        DotPlayingScene * dp = (DotPlayingScene *)dhc->getParent();
//        if (!dp->m_data->m_canPlaying) {
//            
//            return;
//        }
        if (dhc->m_pause) {
            
//            AudioHelper::playMenuOut();
            return;
        }else{
            if (dhc->getParent()!=NULL) {
                
                DotPlayingScene * dotPlaying = (DotPlayingScene*)dhc->getParent();
                if (dotPlaying->m_data==NULL || !dotPlaying->m_data->m_canPlaying) {
                    
                    //玩家按下停止按钮的时候，有可能正好这时候在播放游戏结束（进入下一关）的动画
                    return;
                }
            }
            AudioHelper::playMenuIn();
        }
        
        
        
        dhc->gamePause();
        
    }
    
}

void UpStateLayer::update(float time)
{
    if (m_score-m_scoreShowed>500) {
        
        m_scoreShowed +=100;
    }else if (m_score-m_scoreShowed>100) {
        
        m_scoreShowed +=50;
    }else if(m_score-m_scoreShowed>50){
    
        
        m_scoreShowed +=10;
    }else if(m_score-m_scoreShowed>0){
    
        m_scoreShowed++;
    }
    
    if (SettingHelper::getGameType()!=GAME_TYPE_CLASSIC && SettingHelper::getGameType()!=GAME_TYPE_SPEED) {
        
        
        DotPlayingScene * dp = (DotPlayingScene*)(getParent()->getParent());
        if (dp->getCurrrentGoal(dp->m_level)<=m_scoreShowed) {
            
            
            if (!dp->m_data->m_stageCleared) {
                
                AudioHelper::playGoalFinished();
                dp->m_data->m_stageCleared = true;
            }
            
        }
    }
    
    
    
    m_labelScore->setString(CCString::createWithFormat("%i",m_scoreShowed)->getCString());
}

