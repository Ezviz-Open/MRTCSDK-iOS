//
//  MRTCNetworkModel.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - 网络状况
/**
 网络状况
 
 - MRTCNetworkStateNormal: 良好
 - MRTCNetworkStatePoor: 不佳
 - MRTCNetworkStateBad:  较差
 - MRTCNetworkStateVeryBad: 极差
 */
typedef enum : NSInteger {
    
    MRTCNetworkStateNormal = 0,
    MRTCNetworkStatePoor = 1,
    MRTCNetworkStateBad = 2,
    MRTCNetworkStateVeryBad = 3
} MRTCNetworkState;

@interface MRTCNetworkModel : NSObject
// 接收/发送包数
@property (nonatomic, assign) NSInteger recv;
/// 错序数
@property (nonatomic, assign) NSInteger miss;
/// 丢包数
@property (nonatomic, assign) NSInteger losf;
/// 速率/码率(kbps)
@property (nonatomic, assign) NSInteger speed;
/// 网络延迟
@property (nonatomic, assign) NSInteger delay;

/// 丢包率
@property (nonatomic, assign) float dropRate;
/// 网络状况
@property (nonatomic, assign) MRTCNetworkState state;

@end

NS_ASSUME_NONNULL_END
