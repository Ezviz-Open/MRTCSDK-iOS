//
//  MRTCNetworkManager.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/7.
//

#import <Foundation/Foundation.h>
#import <MRTCSDK/MRTCNetworkConfig.h>
#import <MRTCSDK/MRTCNetworkModel.h>
#import <MRTCSDK/MRTCNetworkConnectModel.h>

NS_ASSUME_NONNULL_BEGIN
@class MRTCNetworkManager;
@class MRTCNetworkConfig;
@class MRTCNetworkModel;
@class MRTCNetworkConnectModel;
@class ERTCSpeedTestResult;
#pragma mark - 网络检测服务相关代理
@protocol MRTCNetworkManagerDelegate <NSObject>

#pragma mark 可选实现代理方法
@optional

#pragma mark - ----- Core Delegate Methods -----

#pragma mark 开启网络检测
/// 开启网络检测
/// @param networkManager 网络检测对象
- (void)networkManagerDidBegined:(nonnull MRTCNetworkManager *)networkManager;

#pragma mark 完成网络检测
/// 完成网络检测
/// @param networkManager 网络检测对象
/// @param uploadModel 上行网络状况
/// @param downModel 下行网络状况
/// @param connectModel 网络连接状况
- (void)networkManagerDidFinshed:(nonnull MRTCNetworkManager *)networkManager uploadModel:(nullable MRTCNetworkModel *)uploadModel downModel:(nullable MRTCNetworkModel *)downModel connectModel:(MRTCNetworkConnectModel *)connectModel;

@end
@interface MRTCNetworkManager : NSObject

#pragma mark - -------- 网络检测服务基础接口 ---------
#pragma mark 单例模式获取网络检测服务实例
/// 单例模式获取网络检测服务实例
+(instancetype)sharedManager;

#pragma mark 开启网络监测
/// 开启网络监测
/// @param config 检测配置
/// @param delegate 回调代理
- (BOOL)startDetectionWithConfig:(nonnull MRTCNetworkConfig *)config delegate:(id <MRTCNetworkManagerDelegate>)delegate;

#pragma mark 停止网络监测
/// 停止网络监测
- (void)stopNetworkDetection;

- (void)onSpeedTestResult:(ERTCSpeedTestResult *)result;
@end

NS_ASSUME_NONNULL_END
