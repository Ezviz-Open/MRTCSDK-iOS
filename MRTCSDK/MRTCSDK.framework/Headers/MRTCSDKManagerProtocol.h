//
//  MRTCSDKManagerProtocol.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/2/21.
//

#import <VCSSDK/VCSSDK.h>
#import <MRTCSDK/MRTCEnum.h>
#import <VCSSDK/VCSReplayKit.h>
NS_ASSUME_NONNULL_BEGIN

#pragma mark - 本地采集相关代理
@protocol MRTCSDKManagerCameraProtocol <NSObject>
#pragma mark 可选实现代理方法
@optional

#pragma mark 实际的采集大小回调
/// 实际的采集大小回调
/// @param imageWidth 视频宽
/// @param imageHeight 视频高
- (void)captureVideoRealWithWidth:(int)imageWidth height:(int)imageHeight;

#pragma mark 摄像头采集视频数据回调
/// 摄像头采集视频数据回调
/// @param pixelbuffer 视频采集数据
- (void)captureCameraDataWithCVPixleBuffer:(CVPixelBufferRef)pixelbuffer;

@end

#pragma mark - 视频会议相关代理
@protocol MRTCSDKManagerProtocol <NSObject>

#pragma mark 可选实现代理方法
@optional

#pragma mark - -------- 流媒体服务相关代理 --------
#pragma mark 会议室流媒体码率自适应状态(接收网络状态回调)
/// 会议室流媒体码率自适应状态(接收网络状态回调)
/// @param linkId 链路ID(SDKNO&streamID)
/// @param lrlState 端到端链路状态
/// @param lrdState 下行链路状态
- (void)roomXbitrateChangeStateWithLinkId:(NSString *)linkId lrlState:(VCSXbitrateInceptState)lrlState lrdState:(VCSXbitrateInceptState)lrdState;

///TODO 自研待适配
#pragma mark 码率自适应状态(当前发送端码率变化回调)
/// 码率自适应状态(当前发送端码率变化回调)
/// @param state 当前发送端码率变化状态
- (void)roomSenderXbitrateChangeWithStreamState:(VCSXbitrateSendState)state;

#pragma mark 会议室其它与会人员上传流媒体状态回调
/// 会议室其它与会人员上传流媒体状态回调
/// @param ptr 底层防止溢出字段
/// @param streamData 流媒体信息
/// {
///     "recvinfo": [
///          {
///              "linkid": 12340001,  对方sdkno
///              "recv": 4127，接收包信息
///              "comp": 13,  补偿 高 网络不稳定
///              "losf": 0,   丢失包信息  高 就是网络差
///              "lrl": 6.8,  短时端到端丢包率（对方手机到你手机）
///              "lrd": 8.9,   短时下行丢包率（服务器到你）
///              "audio": 600,   接收音频包信息
///              "audio_speed": -1,   音频速率
///              "total_speed": -1,    视频速率
///          }
///      ]
///  }
- (void)roomParticipantStreamStatusWithPtr:(NSString *)ptr streamData:(NSDictionary *)streamData;

#pragma mark 会议室当前用户上传流媒体状态回调
/// 会议室当前用户上传流媒体状态回调
/// @param ptr 底层防止溢出字段
/// @param streamData 流媒体信息
/// {
///    uploadinfo =     (
///                {
///            buffer = 0; 上传缓冲包0-4正常
///            delay = 0; 上传延迟时间
///            overflow = 0; 上传缓冲包0-4正常
///            speed = 0kps; 上传视频速率
///            audio_speed: 0kps; 上传音频速率
///            status = "-2"; -1上传出错 >=0正常
///            loss_r = "0.00"; 当前上传丢包率
///            loss_c  = "0.00"; 经过补偿的最终上传丢包率
///        }
///    );
/// }
- (void)roomCurrentStreamStatusWithPtr:(NSString *)ptr streamData:(NSDictionary *)streamData;

#pragma mark 短时平均下行丢包率回调
/// 短时平均下行丢包率回调
/// @param average 平均下行丢包率
- (void)roomDownstreamLossWithAverage:(CGFloat)average;

#pragma mark 开启网络检测
/// 开启网络检测
- (void)roomNetworkManagerDidBegined;

#pragma mark 完成网络检测
/// 完成网络检测
/// @param uploadModel 上行网络状况
/// @param downModel 下行网络状况
/// @param connectModel 网络连接状况
- (void)roomNetworkManagerDidFinshedWithUploadModel:(nullable VCSNetworkModel *)uploadModel downModel:(nullable VCSNetworkModel *)downModel connectModel:(VCSNetworkConnectModel *)connectModel;

#pragma mark 流媒体重连结果回调
/// 流媒体重连结果回调
/// @param succeed 重连是否成功，YES-成功 NO-失败
- (void)roomStreamMediaDidReconnectFinish:(BOOL)succeed;

#pragma mark 音频路由变更回调
/// 音频路由变更回调
/// @param route 音频路由
/// @param previousRoute 变更前的音频路由
- (void)onAudioRouteChanged:(MRTCAudioRoute)route previousRoute:(MRTCAudioRoute)previousRoute;

#pragma mark 流媒体连接结果回调
/// 流媒体连接结果回调
/// @param succeed 连接是否成功，YES-成功 NO-失败
- (void)roomStreamMediaDidConnectFinish:(BOOL)succeed;

#pragma mark 录屏服务状态码回调
/// 录屏服务状态码回调
/// @param status 状态码(0-停止，1-开始，-1-连接失败)
- (void)pushScreenStreamProcessStatus:(int)status;

#pragma mark 下行网络丢包档位变化回调
/// 下行网络丢包档位变化回调
/// @param state 下行丢包档位
- (void)roomDownstreamLevelChangeWithState:(VCSDownLevelState)state;


#pragma mark 语音模式状态变更回调
/// 语音模式状态变更回调
/// @param audioMode 语音模式状态(YES-开启 NO-关闭)
- (void)roomAudioModeChangeWithAudioMode:(BOOL)audioMode;

#pragma mark 会议室视频进入和退出流媒体输出信息回调
/// 会议室视频进入和退出流媒体输出信息回调
/// @param lparam 宽/高
/// @param wparam 宽/高
/// @param ptr 底层防止溢出字段
- (void)roomStreamDataWithLparam:(int)lparam wparam:(int)wparam ptr:(NSString *)ptr;


#pragma mark 会议室参会人流媒体数据回调(可根据不同linkId显示/处理窗口)
/// 会议室参会人流媒体数据回调(可根据不同linkId显示/处理窗口)
/// @param linkId 视频链路ID
/// @param stamp 时间戳
/// @param track 视频轨道
/// @param type 视频存储格式(0 - I420 , 1 - NV12, 2 - NV21)
/// @param lable 视频角度
/// @param width 宽/高
/// @param height 宽/高
/// @param yData 流媒体像素数据
/// @param uData 流媒体像素数据
/// @param vData 流媒体像素数据
- (void)roomParticipantCameraDataWithLinkId:(int)linkId stamp:(int)stamp track:(int)track type:(int)type lable:(int)lable width:(int)width height:(int)height yData:(nullable void *)yData uData:(nullable void *)uData vData:(nullable void *)vData;

//会议室其他人视频数据回调
/// @param linkId 视频链路ID
/// @param pixelBuffer 视频数据
- (void)roomOtherVideoData:(int)linkId sampleBuffer:(CVPixelBufferRef)pixelBuffer;

#pragma mark 当前服务器是否允许本人发言回调
/// 当前服务器是否允许本人发言回调
/// @param state 是否允许发言
- (void)roomServiceSpeechWithState:(BOOL)state;

#pragma mark 当前讲话人员音频数据信息回调
/// 当前讲话人员音频数据信息回调
/// @param audioArray 讲话人员音频数据列表
/// {
///    streamId = 20000016; 链接ID(即：sdkno)
///    power = 6766; 功率
///    db = "-99"; 分贝值
/// }
- (void)roomAudioSpeakingStatusWithAudioArray:(NSMutableArray *)audioArray;

#pragma mark 本地音频编码数据
/// 音频编码后的数据
/// @param audioData 音频数据
- (void)roomLocalEncodedAudioData:(NSData *)audioData;

#pragma mark 本地网络状态回调
- (void)roomLocalUserNetworkQualityWithUp:(MRTCNetworkQuality)upQuality down:(MRTCNetworkQuality)downQuality;

#pragma mark - -------- 互动服务服务相关代理 --------
#pragma mark 互动服务闪断重连成功回调
/// 互动服务闪断重连成功回调
- (BOOL)roomReconnectedSucceed;

#pragma mark 互动服务连接失败(进入房间失败)
/// 互动服务连接失败(进入房间失败)
/// @param command cmd指令
/// @param result 结果
- (void)roomListenRoomEnterFailedCommand:(Command)command result:(Result)result;

#pragma mark 会议室状态通知
/// 会议室状态通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomStateWithNotify:(RoomNotify *)notify error:(nullable NSError *)error;

#pragma mark 会议开始通知
/// 会议开始通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomBeginWithNotify:(RoomBeginNotify *)notify error:(NSError *)error;

#pragma mark 本地用户成功加入房间
///本地用户成功加入房间
///@param result 结果 0:成功
- (void)onListenLocalUserEnterRoom:(NSInteger)result;
#pragma mark 远端用户加入房间通知
/// 成员进入会议室通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenEnterWithNotify:(EnterNotify *)notify error:(nullable NSError *)error;

#pragma mark 远端用户离开房间通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenExitWithNotify:(ExitNotify *)notify error:(nullable NSError *)error;

#pragma mark 我的状态变化通知
/// 我的状态变化通知
/// @param notify 通知信息
/// @param error 错误信息
/// @param firstNotify 是否为首次状态通知
- (void)onListenMyAccountWithNotify:(MyAccountNotify *)notify error:(nullable NSError *)error firstNotify:(BOOL)firstNotify;

#pragma mark 成员状态通知
/// 成员状态通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenAccountStateWithNotify:(AccountNotify *)notify error:(nullable NSError *)error;

#pragma mark 被踢出房间通知
/// 被踢出房间通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenKickoutWithNotify:(KickoutNotify *)notify error:(NSError *)error;

#pragma mark 云录制状态通知
/// 云录制状态通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomCloudRecordEventWithNotify:(McuRunStateNotify *)notify error:(NSError *)error;

#pragma mark 会议结束通知
/// 会议结束通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomEndedWithNotify:(RoomEndedNotify *)notify error:(NSError *)error;

#pragma mark 聊天消息通知
/// 聊天消息通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenChatWithNotify:(ChatNotify *)notify error:(NSError *)error;

#pragma mark 举手发言的处理通知
/// 举手发言的处理通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomRaiseHandWithNotify:(HandUpNotify *)notify error:(NSError *)error;

#pragma mark 收回主持人通知
/// 收回主持人通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomRecoveryHostWithNotify:(RoomRecoveryHostNotify *)notify error:(NSError *)error;

#pragma mark 转移主持人通知
/// 转移主持人通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomMoveHostWithNotify:(RoomMoveHostNotify *)notify error:(NSError *)error;

#pragma mark 设置联席主持人通知
/// 设置联席主持人通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenRoomUnionHostWithNotify:(RoomUnionHostNotify *)notify error:(NSError *)error;

#pragma mark 事件命令透传通知
/// 事件命令透传通知
/// @param command 消息指令
/// @param content 消息内容
- (void)onListenRoomEventWithCommand:(VCSCommandEventState)command content:(NSString *)content;

#pragma mark 网络研讨成员角色通知
/// 网络研讨成员角色通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenWebinarMemberRoleWithNotify:(WebinarRoleNotify *)notify error:(NSError *)error;

#pragma mark 网络研讨会观众数量通知
/// 网络研讨会观众数量通知
/// @param notify 通知信息
/// @param error 错误信息
- (void)onListenWebinarAudienceCountWithNotify:(WebinarAudienceNumNotify *)notify error:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
