//
//  IntroLayer.h
//  dots
//
//  Created by 谢元潮 on 13-11-23.
//
//

#ifndef dots_IntroLayer_h
#define dots_IntroLayer_h


#include "cocos2d.h"

USING_NS_CC;

class IntroLayer : public CCLayer
{
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(IntroLayer);

};

#endif
