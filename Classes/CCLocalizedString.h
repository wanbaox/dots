//
//  CCLocalizedString.h
//  SkeletonX
//
//  Created by 小苏 on 11-12-1.
//  Copyright (c) 2011年 GeekStudio. All rights reserved.
//

#ifndef _CCLocalizedString_h
#define _CCLocalizedString_h

#import "cocos2d.h"

/*get the localized string by the key, if can't get the value then return mComment
 */
const char * CCLocalizedString(const char * mKey,const char * mComment);

#endif
