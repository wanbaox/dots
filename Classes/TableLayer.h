//
//  TableLayer.h
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#ifndef __PlayThePlane__TableLayer__
#define __PlayThePlane__TableLayer__

#include "cocos2d.h"
#include "config.h"

USING_NS_CC;

class TableLayer : public cocos2d::CCNode
{
    
    CCLayerColor * m_localLayer;
    CCLayerColor * m_worldLayer;
    
    int m_pageMaxCount;
    int m_pageCurrent;
    
public:
    TableLayer();
	~TableLayer();
    
    virtual bool init();
    
    CREATE_FUNC(TableLayer);
    
    
    void loadLoaclLayer(int score);
    
    void loadWorldLayer();
    
    void leftPageMove(float distance);
    
    void rightPageMove(float distance);
    
    void setNoDataInlist(CCLayer* l);
    
    void loadWorldTopList(int score);
    
        
};



#endif /* defined(__PlayThePlane__TableLayer__) */
