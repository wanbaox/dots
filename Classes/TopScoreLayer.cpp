

#include "TopScoreLayer.h"
#include "SimpleAudioEngine.h"
#include "DotPlayingScene.h"
#include "DataController.h"
#include "config.h"

TopScoreLayer::TopScoreLayer()
{
    
}

TopScoreLayer::~TopScoreLayer()
{
    
}

CCScene* TopScoreLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TopScoreLayer *layer = TopScoreLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TopScoreLayer::init()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(Color_Bg)) {
        
        return false;
    }
    
    this->setAnchorPoint(ccp(0,0));
    
    m_logoLabel = CCLabelTTF::create("FUCK SHIT","Arial",32);
    m_logoLabel->setColor(ccc3(0, 0, 0));
    m_logoLabel->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height - 50));
    this->addChild(m_logoLabel);
    
    
    CCSprite * thisRound = CCSprite::create("thisRoundScore.png");
    thisRound->setPosition(ccp(60, origin.y+visibleSize.height-130));
    this->addChild(thisRound);
    
    m_thisRound = CCLabelTTF::create("", "Arial", 18);
    m_thisRound->setColor(ccc3(0, 0, 0));
    m_thisRound->setPosition(ccp(40, 10));
    thisRound->addChild(m_thisRound);
    
    
    CCSprite * highScore = CCSprite::create("HighScore.png");
    highScore->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height-130));
    this->addChild(highScore);
    
    m_highScore = CCLabelTTF::create("", "Arial", 18);
    m_highScore->setColor(ccc3(0, 0, 0));
    m_highScore->setPosition(ccp(40, 10));
    highScore->addChild(m_highScore);
    
    
    CCSprite * goldSprite = CCSprite::create("gold.png");
    goldSprite->setPosition(ccp(origin.x+visibleSize.width-60, origin.y+visibleSize.height-130));
    this->addChild(goldSprite);
    
    m_goldlabel = CCLabelTTF::create("", "Arial", 18);
    m_goldlabel->setColor(ccc3(0, 0, 0));
    m_goldlabel->setPosition(ccp(40, 10));
    goldSprite->addChild(m_goldlabel);
    
    
    CCSprite * timerSprite = CCSprite::create("timerb.png");
    timerSprite->setAnchorPoint(ccp(0, 0));
    timerSprite->setPosition(ccp(20, origin.y+visibleSize.height-200));
    this->addChild(timerSprite);
    
    
    m_expProgress = CCProgressTimer::create(CCSprite::create("timer.png"));
    m_expProgress->setAnchorPoint(ccp(0,0));
    m_expProgress->setType(kCCProgressTimerTypeBar);
    m_expProgress->setMidpoint(ccp(0, 0));
    m_expProgress->setBarChangeRate(ccp(1,0));
    m_expProgress->setPosition(ccp(3.5, 4.0));
    timerSprite->addChild(m_expProgress);
    m_expProgress->setPercentage(60);
    
    
    m_levelLabel = CCLabelTTF::create("Level:", "Arial", 18);
    m_levelLabel->setAnchorPoint(ccp(0, 0.5));
    m_levelLabel->setColor(ccc3(0, 0, 0));
    m_levelLabel->setPosition(ccp(5, 20));
    timerSprite->addChild(m_levelLabel);
    
    m_tableLayer = TableLayer::create();
    m_tableLayer->setPosition(ccp(60, (origin.y+visibleSize.height)/6));
    this->addChild(m_tableLayer);
    
    m_imageItem = CCMenuItemImage::create(NULL,NULL,this, menu_selector(TopScoreLayer::imageItemPressed));
    
    CCMenu *menu = CCMenu::create(m_imageItem,NULL);
    m_imageItem->setPosition(ccp(0, -(origin.y+visibleSize.height)/2+30));
    this->addChild(menu);
    
    this->setVisible(false);
    
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(false);
    
    return true;
}

void TopScoreLayer::startAnimationDisplay(int score){
    
    m_imageButtonResponseType = true;//play again
    
    this->setVisible(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    this->stopAllActions();
    this->setPosition(ccp(origin.x+visibleSize.width, 0));
    
    CCMoveTo  * moveTo = CCMoveTo::create(0.2, ccp(0, 0));
    
    CCCallFuncO * callB = CCCallFuncO::create(this, callfuncO_selector(TopScoreLayer::callback0), CCInteger::create(score));
    
    this->runAction(CCSequence::create(moveTo,callB,NULL));
    
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("TopPlayingNow.png");
    
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    
    m_imageItem->setNormalSpriteFrame(frame);
    
    this->setTouchEnabled(true);
    
}

void TopScoreLayer::callback0(CCInteger score)
{
    this->loadAnimation(score.getValue(), DataController::getSharedDataController()->readPlayerDefaultProperty());
    
}

void TopScoreLayer::startAnimationDisplay(){
    
    m_imageButtonResponseType = false;//return back
    
    this->setVisible(true);
    
    this->loadAnimation(0, DataController::getSharedDataController()->readPlayerDefaultProperty());
    
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("TopExit.png");
    
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    
    m_imageItem->setNormalSpriteFrame(frame);
    
    this->setTouchEnabled(true);
    
}

void TopScoreLayer::imageItemPressed(){
    
    if (m_imageButtonResponseType) {
        
        CCScene * playingScene = DotPlayingScene::scene(false);
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.2, playingScene));
        
    }else{
        
        CCDirector::sharedDirector()->popScene();
        
    }
}

void TopScoreLayer::loadAnimation(int score ,CCArray* array){
    
    int level = 1;
    int gold = 1;
    long int exp = 0;
    int high = DataController::getSharedDataController()->getHighScore();
    
    if (array != NULL) {
        
        CCInteger * l = (CCInteger *)array->objectAtIndex(0);
        CCInteger * g = (CCInteger *)array->objectAtIndex(1);
        CCInteger * e = (CCInteger *)array->objectAtIndex(2);
        
        level = l->getValue();
        gold = g->getValue();
        exp = e->getValue();
        
    }
    
    m_levelLabel->setString(CCString::createWithFormat("level:%d",level)->getCString());
    m_goldlabel->setString(CCString::createWithFormat("%d",gold)->getCString());
    m_thisRound->setString(CCString::createWithFormat("%d",score)->getCString());
    m_highScore->setString(CCString::createWithFormat("%d",high)->getCString());
    
    if (m_imageButtonResponseType) {
        
        m_thisRound->setString(CCString::createWithFormat("%d",score)->getCString());
        
    }else{
        
        m_thisRound->setString(CCString::create("--")->getCString());
        
    }
    
    m_tableLayer->loadLoaclLayer(1);
    
}

bool TopScoreLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
    
    if (!this->isVisible()) {
        
        return false;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
    
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    m_touchStartLocation = this->convertToNodeSpace(touchLocation);
    
    m_canTriggerAction = true;
    
    return true;
}

void TopScoreLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
    
    if (!m_canTriggerAction) {
        return;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    float distance = ccpDistance(local, m_touchStartLocation);
    
    if (distance>=20) {
        m_canTriggerAction = false;
        
        if (m_touchStartLocation.x < local.x) {
            
            m_tableLayer->leftPageMove(200);
            
        }else{
            
            m_tableLayer->rightPageMove(200);
            
        }
    }
}

//-(void)ccTouchCancelled:(UITouch *)touch withEvent:(UIEvent *)event{
//    NSLog(@"toch cancel!");
//}

void TopScoreLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){
    
    if (m_canTriggerAction) {
        return;
    }
    
    CCPoint touchLocation = touch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    float distance = ccpDistance(local, m_touchStartLocation);
    
    if (distance>=5) {
        m_canTriggerAction = false;
        
        if (m_touchStartLocation.x < local.x) {
            
            m_tableLayer->leftPageMove(200);
            
        }else{
            
            m_tableLayer->rightPageMove(200);
            
        }
    }
    
}

void TopScoreLayer::onExit(){
    
    CCLayerColor::onExit();
    this->setTouchEnabled(false);
    
}

