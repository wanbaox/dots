#include "AppDelegate.h"
#include "IntroLayer.h"
#include "config.h"

USING_NS_CC;
using namespace std;

typedef struct tagResource
{
    CCSize sizeInPixel;
    CCSize sizeDesign;
    char directory[100];
}Resource;


#warning 更具横竖屏幕的不同，需要调换x,y的位置
//iphone4(s)  ：   960x640
//iphone5     ：   1136x640

static Resource resPhone  =  { CCSizeMake(320, 480), CCSizeMake(320, 480), "iphone" };
static Resource resPhone4Retina =  { CCSizeMake(640, 960), CCSizeMake(320, 480), "iphonehd"   };
static Resource resPhone5Retina =  { CCSizeMake(640, 1136), CCSizeMake(320, 568), "iphonehd"   };
static Resource resPad =  { CCSizeMake(768, 1024), CCSizeMake(384, 512), "ipad"   };
static Resource resPadRetina  =  { CCSizeMake(1536, 2048), CCSizeMake(384, 512), "ipadhd" };

//ldpi          240*320
//mdpi          320*480
//hdpi   		480*800  			nexus s／one
//hdpi   		480*854 			nexus s／one
//large tvdpi  	800*1280            nexus 7
//xhdpi 		768*1280			nexus 4
//xhdpi 		720*1280			galaxy nexus

static Resource resLdpi  =  { CCSizeMake(240, 320), CCSizeMake(240, 320), "ldpi" };
static Resource resMdpi  =  { CCSizeMake(320, 480), CCSizeMake(320, 480), "mdpi" };
static Resource resHdpi  =  { CCSizeMake(480, 800), CCSizeMake(480, 800), "hdpi800" };
static Resource resHdpi854  =  { CCSizeMake(480, 854), CCSizeMake(480, 854), "hdpi854" };
static Resource resXhdpi720  =  { CCSizeMake(720, 1280), CCSizeMake(720, 1280), "xhdpi720" };
static Resource resXhdpi768  =  { CCSizeMake(768, 1280), CCSizeMake(768, 1280), "xhdpi720" };
static Resource resXhdpi800  =  { CCSizeMake(800, 1280), CCSizeMake(800, 1280), "xhdpi800" };



AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);


    
    //设置素材目录
    CCSize frameSize = pEGLView->getFrameSize();
    
    Resource actualResource;
    float actualHeight = fmax(frameSize.width, frameSize.height);
    float actualWidth = fmin(frameSize.width, frameSize.height);
    
    CCLog("%f,%f",actualWidth,actualHeight);
    
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    
//    // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.
//    CCLog("ios平台");
//    
//    if (actualHeight == resPhone.sizeInPixel.height) {
//        
//        actualResource = resPhone;
//        
//    }else if (actualHeight == resPhone4Retina.sizeInPixel.height) {
//        
//        actualResource = resPhone4Retina;
//        
//    }else if (actualHeight == resPhone5Retina.sizeInPixel.height) {
//        
//        actualResource = resPhone5Retina;
//        
//    }else if (actualHeight == resPad.sizeInPixel.height) {
//        
//        actualResource = resPad;
//        
//    }else if (actualHeight == resPadRetina.sizeInPixel.height) {
//        
//        actualResource = resPadRetina;
//        
//    }else{
//        
//        actualResource = resPhone;
//        
//    }
//    
//#endif  // CC_PLATFORM_IOS
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    
//    // OpenGLView initialized in HelloWorld/android/jni/helloworld/main.cpp
//    // the default setting is to create a fullscreen view
//    // if you want to use auto-scale, please enable view->create(320,480) in main.cpp
//    
////    static Resource resLdpi  =  { CCSizeMake(240, 320), CCSizeMake(240, 320), "ldpi" };
////    static Resource resMdpi  =  { CCSizeMake(320, 480), CCSizeMake(320, 480), "mdpi" };
////    static Resource resHdpi  =  { CCSizeMake(480, 800), CCSizeMake(480, 800), "hdpi800" };
////    static Resource resHdpi854  =  { CCSizeMake(480, 854), CCSizeMake(480, 854), "hdpi854" };
////    static Resource resXhdpi720  =  { CCSizeMake(720, 1280), CCSizeMake(720, 1280), "xhdpi720" };
////    static Resource resXhdpi768  =  { CCSizeMake(768, 1280), CCSizeMake(768, 1280), "xhdpi768" };
////    static Resource resXhdpi800  =  { CCSizeMake(800, 1280), CCSizeMake(800, 1280), "xhdpi800" };
//    CCLog("andorid平台");
//    
//
//    //先对比width，再对比height，android存在虚拟按键，也会占用一部分屏幕,比如：768*1184
//    
//    if (actualWidth==resLdpi.sizeInPixel.width) {
//        
//        actualResource = resLdpi;
//    }else if (actualWidth==resMdpi.sizeInPixel.width) {
//        
//        actualResource = resMdpi;
//    }else if (actualWidth==resHdpi.sizeInPixel.width) {
//        
//        
//        if (actualHeight == resHdpi.sizeInPixel.height) {
//            
//            actualResource = resHdpi;
//            
//        }else if (actualHeight == resHdpi854.sizeInPixel.height) {
//            
//            actualResource = resHdpi854;
//            
//        }else{
//        
//            actualResource = resHdpi;
//        }
//    }else if (actualWidth==resXhdpi720.sizeInPixel.width) {
//        
//        actualResource = resXhdpi720;
//    }else if (actualWidth==resXhdpi768.sizeInPixel.width) {
//        
//        actualResource = resXhdpi768;
//    }else if (actualWidth==resXhdpi800.sizeInPixel.width) {
//        
//        actualResource = resXhdpi800;
//    }else{
//        
//        actualResource = resHdpi;
//    }
//    
//  
//#endif  // CC_PLATFORM_ANDROID
//    
//    
//    //存放资源的文件夹
//    vector<string> searchPaths;
//    searchPaths.push_back(actualResource.directory);
//    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
//    CCLog(CCString::create(actualResource.directory)->getCString());
    
//    pDirector->setContentScaleFactor(1.0 *actualResource.sizeInPixel.height / actualResource.sizeDesign.height);
//    
//    // Set the design resolution
//    pEGLView->setDesignResolutionSize(actualResource.sizeDesign.width, actualResource.sizeDesign.height, kResolutionNoBorder);
    
    
    float scale = max( actualWidth/320.0 ,  actualHeight/480.0);//缩放比例
    pDirector->setContentScaleFactor(scale);
    
    // Set the design resolution
    pEGLView->setDesignResolutionSize(actualWidth/scale, actualHeight/scale, kResolutionNoBorder);//图片以及代码里面的尺寸所按照的屏幕分辨率
    
    
    
    
    
//    pDirector->setContentScaleFactor(2.0f);
//    pEGLView->setDesignResolutionSize(320, 480, kResolutionNoBorder);
    
    
    
    
    // create a scene. it's an autorelease object
    CCScene *pScene = IntroLayer::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
