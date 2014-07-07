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

enum ItemType {
    ItemType1 = 0,
    ItemType2 = 1,
    ItemType3 = 2,
    ItemType4 = 3,
    ItemType5 = 4
};

class DrawSprite : public cocos2d::CCNode
{
 
    
    CCSprite * m_normalNode;//和m_drawNode是一样的，只是目前cocos2d－x下drawdot会出现锯齿的情况。
    
    int m_dropCount;
    
    CCSize visibleSize;
    CCPoint origin;
    
public:
    int m_x;
    int m_y;
    ItemType m_itemType;
    bool m_disappear;//是否消失
    bool m_hasSelected;//是否被选择
    
public:
    DrawSprite();
	~DrawSprite();
    
    virtual bool init();
    
    CREATE_FUNC(DrawSprite);

    CCPoint calcPos(int x , int y);
    
    void calcColor();
    
    //生成 该节点 x y 宽和高
    void spawnAtXYWH(int x, int y ,float w , float h);
    
    void respawn();// 重新生成
    
    void spawnDropdown(bool isLast);//生成后掉落下来
    
    void respawnDropdown();
        
    void resetPropertyA(int x , int y);// 重置属性 x和y坐标值
    
    void refresh(ItemType itemType);//刷新自己,转换成别的类型
    
    void moveToLeft(bool isLast);
    
    void callbackFinishMoveLeft(CCObject * sender);
    
    void resetDropdown(bool end);// 重置后掉落函数
    
    bool positionInContent(CCPoint pos);// 判断是移动的点是否在 检查范围内
    
    bool selectedType();// 被选中调用该方法
    
    bool alert();// 提示的时候
    
    void disappearImmediate();//马上消失，没有动画
    void disappear(bool callf);// 消失
    
    void unselected();// 取消选中状态
    
    CCPoint getDrawNodePosition();//得到当前 绘制节点的位置
    
    void KeepSelected();//保持被选中状态
    
    void unKeepSelected();// 取消保持被选中状态
    
    float getPositionX();//计算x坐标
    float getPositionY();//计算y坐标
    
    //callbackfunction
    void callbackNotSeclected(CCObject * sender);
    void callbackFinishDrop(CCObject * sender);
    void callbackNotSeclected0(CCObject * sender);
    
    void callback0(CCObject * sender);
    void callbackReadyForPlaying(CCObject * sender);
};



#endif /* defined(__PlayThePlane__DrawSprite__) */
