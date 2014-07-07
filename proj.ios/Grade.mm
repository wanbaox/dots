//
//  Grade.m
//  dots
//
//  Created by 谢元潮 on 13-12-18.
//
//

#import "CCGrade.h"

void CCGrade::rate()
{

    NSString *evaluateString = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=587767923"];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:evaluateString]];
    
}

void CCGrade::gotoMyQQ()
{
    
    NSString *urlString = [NSString stringWithFormat:@"http://user.qzone.qq.com/360348837/"];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlString]];
    
}


