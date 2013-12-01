//
//  IntroLayer.cpp
//  dots
//
//  Created by 谢元潮 on 13-11-23.
//
//

#include "IntroLayer.h"
#include "DotGameScene.h"

CCScene* IntroLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    IntroLayer *layer = IntroLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    CCSprite* background = CCSprite::create("Default.png");
    
    background->setAnchorPoint(ccp(1, 1));
    // position the sprite on the center of the screen
    background->setPosition((ccp((origin.x + visibleSize.width)/2 ,
                                 (origin.y + visibleSize.height)/2)));
    
    // add the sprite as a child to this layer
    this->addChild(background, 0);

    
    return true;
}

void IntroLayer::onEnter()
{
    
    CCLayer::onEnter();
    
    CCScene *pScene = DotGameScene::scene();
    CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
    
}
