//
//  CCiAd.h
//  dots
//
//  Created by 谢元潮 on 13-12-18.
//
//

#ifndef dots_CCiAd_h
#define dots_CCiAd_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

class CCiAd: public cocos2d::CCObject
{
    
public:
    
    CCiAd();
    ~CCiAd();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    
    static void addAdBanner(bool isOnBottom);//添加iad
    static void deletAdBanner();//删除iad

    static void addAdFullScreen();
    static void delAdFullScreen();
    
#endif  // CC_PLATFORM_IOS
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
    static void addAdBanner(bool isOnBottom){
    
        CCLOG("c++准备调用addbanner方法");
        JniMethodInfo method;
        
        bool b = JniHelper::getStaticMethodInfo(method, "com.wanbaox.dots.JniTestHelper", "addBanner", "(II)I");
        if(b) {
            method.env->CallStaticIntMethod(method.classID, method.methodID, 50, 60);
            
        }
        
    };//添加iad
    static void deletAdBanner(){
        
        CCLOG("c++准备调用deleteBanner方法");
        JniMethodInfo method;
        
        bool b = JniHelper::getStaticMethodInfo(method, "com.wanbaox.dots.JniTestHelper", "deleteBanner", "(II)I");
        if(b) {
            method.env->CallStaticIntMethod(method.classID, method.methodID, 50, 60);
            
        }
    };//删除iad
    
    static void addAdFullScreen(){};
    static void delAdFullScreen(){};
    
#endif  // CC_PLATFORM_ANDROID
    
    
    static void * viewController;
    static void * view;//EGLView指针
    static void * adBannerView;//广告
    static void * dl;//广告的delegate
    static bool bannerIsVisible;//设置是否可见
    static bool isIAD;//是否创建了广告
    //    static bool isOnBottom;
    
    static void  *adInterstitialView;
    
};

#endif
