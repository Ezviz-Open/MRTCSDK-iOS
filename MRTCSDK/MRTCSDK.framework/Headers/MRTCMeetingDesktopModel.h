//
//  MRTCMeetingDesktopModel.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/9.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MRTCMeetingDesktopModel : NSObject
#pragma mark 共享屏幕当前帧率
/// 共享屏幕当前帧率
@property (assign, nonatomic) int fps;
#pragma mark 共享屏幕流宽
/// 共享屏幕流宽
@property (assign, nonatomic) int width;
#pragma mark 共享屏幕流高
/// 共享屏幕流高
@property (assign, nonatomic) int height;
@end

NS_ASSUME_NONNULL_END
