//
//  CCGrade.h
//  dots
//
//  去市场评分
//
//  Created by 谢元潮 on 13-12-18.
//
//

#ifndef dots_CCGrade_h
#define dots_CCGrade_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

class CCGrade: public cocos2d::CCObject
{
    
public:
    
    CCGrade();
    ~CCGrade();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    static void rate();
    
    static void gotoMyQQ();
    
#endif  // CC_PLATFORM_IOS
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    static void rate(){
    
        JniMethodInfo method;
        
        bool b = JniHelper::getStaticMethodInfo(method, "com.wanbaox.dots.JniTestHelper", "rate", "(II)I");
        if(b) {
            method.env->CallStaticIntMethod(method.classID, method.methodID, 50, 60);
            
        }
    };
    
    static void gotoMyQQ(){
    
        
        JniMethodInfo method;
        
        bool b = JniHelper::getStaticMethodInfo(method, "com.wanbaox.dots.JniTestHelper", "gotoMyQQ", "(II)I");
        if(b) {
            method.env->CallStaticIntMethod(method.classID, method.methodID, 50, 60);
            
        }
    
    };
    
#endif  // CC_PLATFORM_ANDROID
    
    
    
};

#endif
