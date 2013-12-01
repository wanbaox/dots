//
//  DrawSprite.h
//  PlayThePlane
//
//  Created by jun on 13-8-23.
//
//

#ifndef __PlayThePlane__DrawSprite__
#define __PlayThePlane__DrawSprite__

#import "cocos2d.h"
#include "config.h"

USING_NS_CC;

class DrawSprite : public cocos2d::CCNode
{
    
    int m_w;
    int m_h;
    
    bool m_hasSelected;//可否被选择
    
    CCDrawNode * m_drawNode;// 画当前颜色的圆点
    
    CCDrawNode * m_selectNode;// 用于 被选中时播放动画
    
    int m_dropCount;
    
public:
    int m_x;
    int m_y;
    ccColor4F m_color;
    bool m_disappear;//是否消失
    
public:
    DrawSprite();
	~DrawSprite();
    
    virtual bool init();
    
    CREATE_FUNC(DrawSprite);
    
//    void update(float time);
    
    
//    static DrawSprite * create(void);
//    void initWithType(propsType type);
//    void propAnimation();
//    //cocos2d::CCSprite *prop;
//    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, __prop, Prop);
    
    
    CCPoint calcPos(int x , int y);
    
    void calcColor();
    
    //生成 该节点 x y 宽和高
    void spawnAtXYWH(int x, int y ,float w , float h);
    
    void respawn();// 重新生成
    
    void spawnDropdown();//生成后掉落下来
    
    void respawnDropdown();
        
    void resetPropertyA(int x , int y);// 重置属性 x和y坐标值
    
    void resetDropdown();// 重置后掉落函数
    
    bool positionInContent(CCPoint pos);// 判断是移动的点是否在 检查范围内
    
    bool selectedType();// 被选中调用该方法
    
    void disappear(bool callf);// 消失
    
    void unselected();// 取消选中状态
    
    CCPoint getDrawNodePosition();//得到当前 绘制节点的位置
    
    void KeepSelected();//保持被选中状态
    
    void unKeepSelected();// 取消保持被选中状态
    
    
    
    //callbackfunction
    void callbackNotSeclected(CCObject * sender);
    void callbackNotSeclected0(CCObject * sender);
    void callbackSetInVisible(CCObject * sender);
    void callback0(CCObject * sender);
    
};



#endif /* defined(__PlayThePlane__DrawSprite__) */
