//
//  ADDL.m
//  dots
//
//  Created by 谢元潮 on 13-12-18.
//
//

#import "ADDL.h"
#import "CCiAd.h"
#include "cocos2d.h"
#import "EAGLView.h"

@implementation ADDL

- (id)init{
    self = [super init];
    if (self) {
        
    }
    
    return self;
}
-(void)relaease
{
    [super dealloc];
}
- (void)dealloc
{
    
    [super dealloc];
}
-(void) bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    
    NSLog(@"banner加载失败");
    
//    if (CCiAd::bannerIsVisible) {
//        [UIView beginAnimations:@"animateAdBannerOff" context:NULL];
//        // banner is visible and we move it out of the screen, due to connection issue
//        ((ADBannerView *)CCiAd::adView).center = OUT_POS;
//        [UIView commitAnimations];
//        CCiAd::bannerIsVisible = false;
//    }
}

-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation) toInterfaceOrientation duration:(NSTimeInterval)duration
{
    
}

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    
    [self layoutAnimated:YES];
}



- (void)layoutAnimated:(BOOL)animated
{
    
    //        CGRect bannerFrame = ((ADBannerView *)adView).frame;
    //        if (((ADBannerView *)adView).bannerLoaded) {
    //            contentFrame.size.height -= ((ADBannerView *)adView).frame.size.height;
    //            bannerFrame.origin.y = size.height;
    //        } else {
    //            bannerFrame.origin.y = size.height;
    //        }
    //
    //        [UIView animateWithDuration:animated ? 0.25 : 0.0 animations:^{
    //            _contentView.frame = contentFrame;
    //            [_contentView layoutIfNeeded];
    //            _bannerView.frame = bannerFrame;
    //        }];
    
    cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    cocos2d::CCPoint origin =cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
    CGRect bannerFrame = ((ADBannerView *)CCiAd::adBannerView).frame;
    bannerFrame.origin.x = 0;
  
    bannerFrame.origin.y = origin.y+visibleSize.height-bannerFrame.size.height;
    
    ((ADBannerView *)CCiAd::adBannerView).frame = bannerFrame;
    
}

#pragma mark -
#pragma mark Interstitial Management


- (void)presentInterlude
{
    
    if(((ADInterstitialAd *)CCiAd::adInterstitialView).loaded){
    
        [((ADInterstitialAd *)CCiAd::adInterstitialView) presentInView:(UIView*)CCiAd::view];
    }else{
    
        
    }
}

#pragma mark ADInterstitialViewDelegate methods

// When this method is invoked, the application should remove the view from the screen and tear it down.
// The content will be unloaded shortly after this method is called and no new content will be loaded in that view.
// This may occur either when the user dismisses the interstitial view via the dismiss button or
// if the content in the view has expired.
- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd
{
    
//    [self cycleInterstitial];
}

- (void)interstitialAdDidLoad:(ADInterstitialAd *)interstitialAd
{
    
    NSLog(@"加载interstitial广告成功");
    [self presentInterlude];
    
}

// This method will be invoked when an error has occurred attempting to get advertisement content.
// The ADError enum lists the possible error codes.
- (void)interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
    NSLog(@"加载interstitial广告失败");
    
}

#pragma mark GADBannerViewDelegate impl

// Since we've received an ad, let's go ahead and set the frame to display it.
- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received ad");
    
    [UIView animateWithDuration:0.2 animations:^ {
        ((UIView*)CCiAd::adBannerView).frame = CGRectMake(0.0,
                                                          ((EAGLView *)CCiAd::view).frame.size.height-50,
                                                          320,
                                                          50);
        
    }];

}

- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive ad with error: %@", [error localizedFailureReason]);
    
    
    [UIView animateWithDuration:0.2 animations:^ {
        ((UIView*)CCiAd::adBannerView).frame = CGRectMake(0.0,
                                                          ((EAGLView *)CCiAd::view).frame.size.height,
                                                          320,
                                                          50);
        
    }];
    
}

@end
