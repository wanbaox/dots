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
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = IntroLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    
    //设置素材目录
    CCSize frameSize = pEGLView->getFrameSize();
    
    Resource actualResource;
    float actualHeight = fmax(frameSize.width, frameSize.height);
    float actualWidth = fmin(frameSize.width, frameSize.height);
    
    if (actualHeight == resPhone.sizeInPixel.height) {
        
        actualResource = resPhone;
        
    }else if (actualHeight == resPhone4Retina.sizeInPixel.height) {
        
        actualResource = resPhone4Retina;
        
    }else if (actualHeight == resPhone5Retina.sizeInPixel.height) {
        
        actualResource = resPhone5Retina;
        
    }else if (actualHeight == resPad.sizeInPixel.height) {
        
        actualResource = resPad;
        
    }else if (actualHeight == resPadRetina.sizeInPixel.height) {
        
        actualResource = resPadRetina;
        
    }else{
        
        actualResource = resPhone;
        
    }
    
    vector<string> searchPaths;
    searchPaths.push_back(actualResource.directory);
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
//    CCLog(CCString::create(actualResource.directory)->getCString());
    
    pDirector->setContentScaleFactor(1.0 *actualResource.sizeInPixel.height / actualResource.sizeDesign.height);
    
    // Set the design resolution
    pEGLView->setDesignResolutionSize(actualResource.sizeDesign.width, actualResource.sizeDesign.height, kResolutionNoBorder);
    
    
//    pDirector->setContentScaleFactor(2.0f);
//    pEGLView->setDesignResolutionSize(320, 480, kResolutionNoBorder);
    
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
