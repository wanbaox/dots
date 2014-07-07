//
//  CCiAd.m
//  dots
//
//  Created by 谢元潮 on 13-12-18.
//
//

#import "cocos2d.h"
#import "CCiAd.h"
#import "EAGLView.h"
#import "ADDL.h"
#import "GADBannerView.h"
#import "GADRequest.h"
#import "RootViewController.h"

void CCiAd::addAdBanner(bool isOnBottomTmp){
    
    //GOOGLE ADMOB
    // 在屏幕底部创建标准尺寸的视图。
    adBannerView = [[GADBannerView alloc]
                   initWithFrame:CGRectMake(0.0,
                                            ((EAGLView *)view).frame.size.height,
                                            320,
                                            50)];
    
    // 指定广告的“单元标识符”，也就是您的 AdMob 发布商 ID。
    ((GADBannerView*)adBannerView).adUnitID = @"a152b798b2285a6";
    
    dl=[[ADDL alloc] init];
    ((GADBannerView*)adBannerView).delegate = (ADDL *)dl;

    // 告知运行时文件，在将用户转至广告的展示位置之后恢复哪个 UIViewController
    // 并将其添加至视图层级结构。
    [((GADBannerView*)adBannerView) setRootViewController:(UIViewController*)viewController];
    [((EAGLView *)view) addSubview:(GADBannerView*)adBannerView];
    
    // 启动一般性请求并在其中加载广告。
    [((GADBannerView*)adBannerView) loadRequest:[GADRequest request]];
    
    
    
    //apple iAd
////    CCiAd::isOnBottom = isOnBottomTmp;
//    
//    isIAD = false;
//    
//    NSString* versionString = [[UIDevice currentDevice] systemVersion];
//    int verNum = [versionString intValue];
//    
//    if (verNum >= 4) {
//        isIAD = true;
//        // create and setup adview
//        dl=[[ADDL alloc] init];
//        
////        if ([ADBannerView instancesRespondToSelector:@selector(initWithAdType:)]) {
////            adView = [[ADBannerView alloc] initWithAdType:ADAdTypeBanner];
////        } else {
////            adView = [[ADBannerView alloc] init];
////        }
//        
//        
//        adBannerView = [[ADBannerView alloc] initWithFrame:CGRectZero];
//        ((ADBannerView *)adBannerView).requiredContentSizeIdentifiers = [NSSet setWithObjects: ADBannerContentSizeIdentifierPortrait , nil];
//        
//        
//        
//        
//        ((ADBannerView *)adBannerView).center = OUT_POS;
//        ((ADBannerView *)adBannerView).delegate =(ADDL *)dl;
//        bannerIsVisible =false;
//        [(EAGLView *)view addSubview: (ADBannerView *)adBannerView];
//        
//        
//        
//        
//    }
    
}

//void CCiAd::changeAdPos(){
//
//    CCiAd::isOnBottom = !CCiAd::isOnBottom;
//    
//    cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
//    cocos2d::CCPoint origin =cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
//    
//    CGRect bannerFrame = ((ADBannerView *)CCiAd::adView).frame;
//    bannerFrame.origin.x = 0;
//    
//    if (CCiAd::isOnBottom) {
//        
//        bannerFrame.origin.y = origin.y+visibleSize.height-bannerFrame.size.height;
//    }else{
//        
//        bannerFrame.origin.y = 0;
//    }
//    
//    ((ADBannerView *)CCiAd::adView).frame = bannerFrame;
//
//}

void CCiAd::deletAdBanner(){
//    if(isIAD){
//        ((ADBannerView *)adBannerView).delegate = nil;
//        [((ADBannerView *)adBannerView) removeFromSuperview];
//        [((ADBannerView *)adBannerView) release];
//        adBannerView = nil;
//        [((ADDL *)dl) release];
//    }
    
    if (adBannerView) {
    
        [UIView animateWithDuration:0.2 animations:^ {
            ((GADBannerView*)adBannerView).frame = CGRectMake(0.0,
                                                              ((EAGLView *)view).frame.size.height,
                                                              320,
                                                              50);
            
        }];
    }
    

    
}


void CCiAd::addAdFullScreen(){
    
    if (!dl) {
        
        dl=[[ADDL alloc] init];
    }
    
//    // Clean up the old interstitial...
//    ((ADInterstitialAd *)adInterstitialView).delegate = nil;
//    [((ADInterstitialAd *)adInterstitialView) release];
    // and create a new interstitial. We set the delegate so that we can be notified of when
    adInterstitialView = [[ADInterstitialAd alloc] init];
    ((ADInterstitialAd *)adInterstitialView).delegate = (ADDL *)dl;
}

void CCiAd::delAdFullScreen(){
    
    if(adInterstitialView){
        ((ADInterstitialAd *)adInterstitialView).delegate = nil;
//        [((ADInterstitialAd *)adInterstitialView) removeFromSuperview];
        [((ADInterstitialAd *)adInterstitialView) release];
        adInterstitialView = nil;
        [((ADDL *)dl) release];
    }
}

void * CCiAd::dl;
void * CCiAd::adBannerView;
bool  CCiAd::bannerIsVisible;
bool  CCiAd::isIAD;
void * CCiAd::view;
void * CCiAd::adInterstitialView;

void * CCiAd::viewController;


