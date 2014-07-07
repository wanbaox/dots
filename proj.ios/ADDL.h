//
//  ADDL.h
//  dots
//
//  Created by 谢元潮 on 13-12-18.
//
//

#import <Foundation/Foundation.h>

#import "GADBannerViewDelegate.h"
#import <iAd/iAd.h>
#define OUT_POS CGPointMake(-1024, -1024)

@interface ADDL :NSObject<ADBannerViewDelegate,ADInterstitialAdDelegate,GADBannerViewDelegate>

@end
