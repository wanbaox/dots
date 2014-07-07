//
//  DownStateLayer.h
//  disappear
//
//  Created by CpyShine on 13-5-29.
//  Copyright 2013年 CpyShine. All rights reserved.
//

#ifndef __DownStateLayer__
#define __DownStateLayer__


#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class DownStateLayer : public cocos2d::CCLayerColor {
    
    
public:
    
    DownStateLayer();
	~DownStateLayer();
    
    virtual bool init();
    
    CREATE_FUNC(DownStateLayer);
    
    void startAnimationDisplay();
    
    void moveOut();
    
    void skillThreePressed();
    void skillTwoPressed();
    void skillOnePressed();
    
};

#endif