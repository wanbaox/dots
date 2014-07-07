//
//  Utils.cpp
//  dots
//
//  Created by 谢元潮 on 13-12-20.
//
//

#include "XYCUtils.h"

long XYCUtils::GetCurrentTime()
{
    
    struct cc_timeval tv;
    CCTime::gettimeofdayCocos2d(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}