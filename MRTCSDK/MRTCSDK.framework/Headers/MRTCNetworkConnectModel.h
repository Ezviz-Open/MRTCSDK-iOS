//
//  MRTCNetworkConnectModel.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MRTCNetworkConnectModel : NSObject
/// 网络回环延迟
@property (nonatomic, assign) NSInteger delay;

/// 互联网连接情况(YES-正常 NO-异常)
@property (nonatomic, assign) BOOL internetConnect;
/// 流媒体服务器连接情况(YES-正常 NO-异常)
@property (nonatomic, assign) BOOL streamConnect;
/// 信令服务器连接情况(YES-正常 NO-异常)
@property (nonatomic, assign) BOOL signalingConnect;
@end

NS_ASSUME_NONNULL_END
