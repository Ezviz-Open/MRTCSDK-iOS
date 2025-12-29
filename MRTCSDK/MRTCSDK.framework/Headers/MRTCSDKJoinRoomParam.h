//
//  MRTCSDKJoinRoomParam.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/2/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class VCSMeetingParam;
@interface MRTCSDKJoinRoomParam : NSObject
////会控相关入参
@property (nonatomic, strong) VCSMeetingParam *vcsMeetingParam;
///是否开启NoPickAudio模式(视频默认选择4方，音频选择所有发言者)
@property (nonatomic, assign) BOOL isNoPickAudio;
///自研 ERTC 加入房间的鉴权 token
@property (nonatomic, copy) NSString *ertcToken;
///会议房间号
@property (nonatomic, copy) NSString *roomNo;
///用户userID
@property (nonatomic, copy) NSString *userID;

//房间内请求地址
@property(nonatomic, strong) NSString *apiUrl;

//appID 外部传入
@property(nonatomic, strong) NSString *appID;

//是否是研讨会嘉宾
@property (nonatomic, assign) BOOL isSeminarGuest;

//是否是研讨会观众
@property (nonatomic, assign) BOOL isSeminarAudience;

@end

NS_ASSUME_NONNULL_END
