//
//  MRTCReplayKit.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/5.
//

#import <Foundation/Foundation.h>
#import <hkScreenShared/hkScreenShared.h>
#import <CoreMedia/CoreMedia.h>
#import <ReplayKit/ReplayKit.h>
#import <MRTCSDK/MRTCEnum.h>

NS_ASSUME_NONNULL_BEGIN

@class MRTCReplayKit;
#pragma mark - 录屏代理回调
/// 录屏代理回调
API_AVAILABLE(ios(12.0))
@protocol MRTCReplayKitDelegate <NSObject>

#pragma mark 录屏完成回调
/// 录屏完成回调
/// - Parameters:
///   - broadcast: 录屏实例
///   - reason: 录屏结束原因
- (void)broadcastFinished:(MRTCReplayKit *)broadcast reason:(NSString *)reason;

@end

#pragma mark - 录屏主入口类
/// 录屏主入口类
API_AVAILABLE(ios(12.0))
@interface MRTCReplayKit : NSObject
#pragma mark 获取单例
/// 获取单例
+ (MRTCReplayKit *)sharedInstance;

- (MRTCReplayKitState)getReplayKitState;

#pragma mark 录屏启动方法
/// 录屏启动方法
/// 需要在 RPBroadcastSampleHandler 的实现类中的 broadcastStartedWithSetupInfo 方法中调用
/// - Parameters:
///   - appGroup: Application Group Identifier
///    - isERTC: 是否是自研流媒体
///   - delegate: 回调对象
- (void)broadcastStartedWithAppGroup:(NSString *)appGroup delegate:(id<MRTCReplayKitDelegate>)delegate;

#pragma mark 录屏结束
- (void)broadcastFinished;

#pragma mark 媒体数据(音视频)发送方法
/// 媒体数据(音视频)发送方法
/// - Parameters:
///   - sampleBuffer: 系统回调的视频或音频帧
///   - sampleBufferType: 媒体输入类型
///   - isERTC: 是否是自研流媒体
/// 注释：sampleBufferType 当前支持 RPSampleBufferTypeVideo 和 RPSampleBufferTypeAudioApp 类型的数据帧处理；
/// RPSampleBufferTypeAudioMic 不支持，可以在宿主 App 处理麦克风采集数据。
- (void)sendSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;
@end

NS_ASSUME_NONNULL_END
