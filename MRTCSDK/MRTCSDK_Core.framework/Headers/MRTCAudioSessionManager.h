//
//  MRTCAudioSessionManager.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/2/21.
//

#import <Foundation/Foundation.h>
#import <MRTCSDK/MRTCEnum.h>

NS_ASSUME_NONNULL_BEGIN

@interface MRTCAudioSessionManager : NSObject

/// 有线耳机是否可用
@property (nonatomic, assign, readonly) BOOL headphoneDeviceAvailable;
/// 蓝牙耳机是否可用
@property (nonatomic, assign, readonly) BOOL bluetoothDeviceAvailable;

#pragma mark 获取音频会话单例
/// 获取音频会话单例
+(instancetype)sharedInstance;

#pragma mark 设置音频路由
/// 设置音频路由
/// - Parameter route: 音频路由
- (void)setAudioRoute:(MRTCAudioRoute)route;

#pragma mark 获取当前音频路由
/// 获取当前音频路由
- (MRTCAudioRoute)currentAudioRoute;

#pragma mark 释放音频会话
/// 释放音频会话
- (void)destroy;
@end

NS_ASSUME_NONNULL_END
