//
//  MRTCEnum.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/2/21.
//

#import <Foundation/Foundation.h>

#define include_ERTCMeidaModule 1

NS_ASSUME_NONNULL_BEGIN

#pragma mark - SDK使用场景
typedef enum {
    MRTCMediaScene_Video_Call = 0,//视频通话场景
    MRTCMediaScene_Meeting_Minutes = 1, //会议纪要
} MRTCMediaScene;


#pragma mark - 音视频内核类型
typedef enum {
    MRTCMediaType_None = 0,
    MRTCMediaType_ERTC = 1, //自研流媒体
    MRTCMediaType_VCS = 2 //风远流媒体
} MRTCMediaType;

#pragma mark -码流类型
typedef enum {
    MRTCStreamMediaType_None = 0,
    MRTCStreamMediaType_Small = 1, //小码流
    MRTCStreamMediaType_Big = 2, //大码流
    MRTCStreamMediaType_Sharing = 4 //共享流
} MRTCStreamMediaType;


#pragma mark -音频路由类型
/**
 音频路由类型
 
 - MRTCAudioRouteUnknow: 未知
 - MRTCAudioRouteSpeaker: 扬声器
 - MRTCAudioRouteReceiver: 听筒
 - MRTCAudioRouteHeadphone: 有线耳机
 - MRTCAudioRouteBluetooth: 蓝牙耳机
 */
typedef enum : NSInteger {
    
    MRTCAudioRouteUnknow,
    MRTCAudioRouteSpeaker,
    MRTCAudioRouteReceiver,
    MRTCAudioRouteHeadphone,
    MRTCAudioRouteBluetooth
} MRTCAudioRoute;

#pragma mark -SDK日志等级
typedef NS_ENUM(NSUInteger, MRTCLogLevel) {
    MRTCLogLevelOff = 0,
    MRTCLogLevelError,
    MRTCLogLevelWarning,
    MRTCLogLevelInfo,
    MRTCLogLevelDefault,
    MRTCLogLevelDebug,
    MRTCLogLevelAll,
};


#pragma mark -美颜日志等级
typedef NS_ENUM(NSInteger, MRTCBeautyLogLevel) {
    
    MRTCBeautyLogLevelTrace = 0,
    MRTCBeautyLogLevelDebug = 1,
    MRTCBeautyLogLevelInfo = 2,
    MRTCBeautyLogLevelWarn = 3,
    MRTCBeautyLogLevelError = 4,
    MRTCBeautyLogLevelCritical = 5,
    MRTCBeautyLogLevelOff = 6,
};

#pragma mark - 电子画板连接状态
/**
 电子画板连接状态
 
 - MRTCDrawConnectStateNormal: 默认状态
 - MRTCDrawConnectStateSucceed: 连接成功
 - MRTCDrawConnectStateFail: 连接失败
 */
typedef enum : NSInteger {
    
    MRTCDrawConnectStateNormal = 0,
    MRTCDrawConnectStateSucceed = 1,
    MRTCDrawConnectStateFail = 2,
} MRTCDrawConnectState;


typedef enum : NSUInteger {
    MRTCReplayKitStateUnconnected,
    MRTCReplayKitStateConnecting,
    MRTCReplayKitStateConnected,
    MRTCReplayKitStateStopped,
} MRTCReplayKitState;

#pragma mark - 网络状态
/**
* 网络质量
*
* ERTC 会每隔两秒对当前的网络质量进行评估，评估结果为六个等级：Excellent 表示最好，Down 表示最差。
*/
typedef NS_ENUM(NSUInteger, MRTCNetworkQuality) {
    
    ///未定义
    MRTCNetworkQuality_Unknown = 0,

    ///当前网络非常好
    MRTCNetworkQuality_Excellent = 1,

    ///当前网络比较好
    MRTCNetworkQuality_Good = 2,

    ///当前网络一般
    MRTCNetworkQuality_Poor = 3,

    ///当前网络较差
    MRTCNetworkQuality_Bad = 4,

    ///当前网络很差
    MRTCNetworkQuality_Vbad = 5,

    ///当前网络不满足 TRTC 的最低要求
    MRTCNetworkQuality_Down = 6,

    ///暂时无法检测到网络质量
    MRTCNetworkQuality_Unsupported = 7,

    ///网络质量检测已开始还没有完成
    MRTCNetworkQuality_Detecting = 8,
};


@interface MRTCEnum : NSObject

@end

@interface MRTCDrawingParam : NSObject

/// 钢笔按钮标题
@property (nonatomic, copy) NSString *penTitle;
/// 荧光笔按钮标题
@property (nonatomic, copy) NSString *highlighterTitle;
/// 橡皮擦按钮标题
@property (nonatomic, copy) NSString *eraserTitle;
/// 颜色按钮标题
@property (nonatomic, copy) NSString *colorTitle;
/// 清除按钮标题
@property (nonatomic, copy) NSString *clearTitle;
/// 图片按钮标题
@property (nonatomic, copy) NSString *pictureTitle;

/// 钢笔按钮图标
@property (nonatomic, copy) NSString *penImage;
/// 荧光笔按钮图标
@property (nonatomic, copy) NSString *highlighterImage;
/// 橡皮擦按钮图标
@property (nonatomic, copy) NSString *eraserImage;
/// 清除按钮图标
@property (nonatomic, copy) NSString *clearImage;

/// 钢笔选中按钮图标
@property (nonatomic, copy) NSString *penSelectImage;
/// 荧光笔选中按钮图标
@property (nonatomic, copy) NSString *highlighterSelectImage;
/// 橡皮擦选中按钮图标
@property (nonatomic, copy) NSString *eraserSelectImage;
/// 清除选中按钮图标
@property (nonatomic, copy) NSString *clearSelectImage;

@end

NS_ASSUME_NONNULL_END
