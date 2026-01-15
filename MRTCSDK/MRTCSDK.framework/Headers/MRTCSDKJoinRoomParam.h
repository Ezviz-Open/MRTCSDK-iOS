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
///会议房间号
@property (nonatomic, copy) NSString *roomNo;
///用户userID
@property (nonatomic, copy) NSString *userID;

//是否是研讨会嘉宾
@property (nonatomic, assign) BOOL isSeminarGuest;

//是否是研讨会观众
@property (nonatomic, assign) BOOL isSeminarAudience;

@end

NS_ASSUME_NONNULL_END
