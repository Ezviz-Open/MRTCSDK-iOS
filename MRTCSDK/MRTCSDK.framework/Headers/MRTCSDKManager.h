//
//  MRTCSDKManager.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/2/21.
//

#import <Foundation/Foundation.h>
#import <MRTCSDK/MRTCSDKManagerProtocol.h>
#import <MRTCSDK/MRTCSDKConfigModel.h>
#import <MRTCSDK/MRTCSDKJoinRoomParam.h>
#import <MRTCSDK/MRTCLocalPreView.h>
#import <MRTCSDK/MRTCNetworkConfig.h>
#import <MRTCSDK/MRTCMeetingDesktopModel.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^MRTCGetThirdRTCInfoBlock)( NSError * _Nullable error);

@class ERTCEngine;
@class DingRtcEngine;
@interface MRTCSDKManager : NSObject
#pragma mark 是否是三方RTC
@property (nonatomic, assign) BOOL isThirdRTC;
#pragma mark 流媒体类型
@property (nonatomic, assign)MRTCMediaType mediaType;

#pragma mark SDK初始化配置
@property (nonatomic, strong) MRTCSDKConfigModel *config;

#pragma mark 视频会议相关代理
@property (nonatomic, weak) id <MRTCSDKManagerProtocol> delegate;

#pragma mark 视频会议本地采集相关代理
@property (nonatomic, weak) id <MRTCSDKManagerCameraProtocol> cameraDelegate;

#pragma mark 自研RTC实例
@property (nonatomic, strong, nullable) ERTCEngine *engine;

#pragma mark DingDingRTC实例
@property (nonatomic, strong, nullable) DingRtcEngine *dingdingEngine;

#pragma mark 本地用户小窗口视图
@property (nonatomic, strong)MRTCLocalPreView *localSmallView;

#pragma mark 屏幕共享groupId
@property (nonatomic, copy) NSString *appGroup;

@property (nonatomic, assign) int64_t startGetThirdInfoTimer;

@property (nonatomic, assign) int64_t startJoinRoomTimer;

@property (nonatomic, assign) int64_t startSubscribeTimer;

@property (nonatomic, assign) int64_t remoteUserJoinRoomTimer;

#pragma mark 单例模式初始化流媒体服务类
+(instancetype)sharedManager;

#pragma mark (音频转发包 视频转发包 数据转发包 SDP转发包)
#pragma mark - -------- SDK初始化 ---------
- (void)setMediaConfig:(MRTCSDKConfigModel *)config;
#pragma mark 初始化会议SDK(YES-连接成功，NO-连接失败)
/// 初始化会议SDK(YES-连接成功，NO-连接失败)
/// @param meetingParam 会控参数
/// @param delegate 代理委托
- (BOOL)initMediaSessionWithMeetingParam:(MRTCSDKJoinRoomParam *)meetingParam  delegate:(id <MRTCSDKManagerProtocol>)delegate;

#pragma mark 获取三方RTC房间信息
/// @param userId 用户id
/// @param roomId 房间号
/// @param token 资源token 服务端生成
/// @param appId 服务端返回
/// @param platAddress 服务端返回
/// @param infoBlock 回调结果
- (void)getThirdRTCRoomInfoWithUserId:(NSString *)userId roomId:(NSString *)roomId token:(NSString *)token appId:(NSString *)appId platAddress:(NSString *)platAddress infoBlock:(MRTCGetThirdRTCInfoBlock)infoBlock;

#pragma mark 重新加入会议
/// 重新加入会议(网络异常后重新入会调用)
/// @param meetingHost 互动服务器地址
/// @param meetingPort 互动服务器端口
/// @param streamHost 流媒体服务器地址
/// @param streamPort 流媒体服务器端口
/// @param session 进入房间凭证
- (void)restartMeetingWithMeetingHost:(NSString *)meetingHost meetingPort:(int)meetingPort streamHost:(NSString *)streamHost streamPort:(int)streamPort session:(NSString *)session;

#pragma mark 销毁释放视频会议资源
/// 销毁释放视频会议资源
/// @param initiative 是否主动退出(用户点击退出会议时需要传YES)
/// @param finishBlock 释放完成回调
- (void)destroy:(BOOL)initiative finishBlock:(VCSMeetingManagerDestroyBlock)finishBlock;

#pragma mark 是否支持自研ERTC
- (BOOL)isSupprotERTC;

#pragma mark 获取自研ERTC版本号
- (int)getERTCVersion;

#pragma mark 获取MRTC版本号
- (NSString *)getMRTCSDKVersion;

#pragma mark - -------- 音频采集相关接口 ---------
#pragma mark 设置是否打开传统降噪
- (void)setEnableAudioCaptureANR:(BOOL)open;


#pragma mark - -------- 视频会议屏幕录制相关接口 ---------
#pragma mark 开启屏幕录制
/// 开启屏幕录制
/// @param appGroup Application Group Identifier
- (void)startScreenRecordWithAppGroup:(nullable NSString *)appGroup;

#pragma mark - 关闭屏幕录制
/// 关闭屏幕录制
- (void)stopScreenRecord;

#pragma mark - -------- 视频会议流媒体服务相关接口 ---------
#pragma mark 设置网络延时抗抖动等级(重传档位)
/// 设置网络延时抗抖动等级(重传档位)
/// @param state 档位(默认为VCSNetworkDelayShakeStateMedium)
- (void)setNetworkDelayShakeWithState:(VCSNetworkDelayShakeState)state;

#pragma mark 开启/关闭语音模式
/// 开启/关闭语音模式
/// @param isAudioMode YES-开启 NO-关闭
- (void)enableAudioMode:(BOOL)isAudioMode;

#pragma mark 关闭/开启音频(是否发送音频)
/// 关闭/开启音频(是否发送音频)
/// @param state 设备状态
- (void)enableSendAudio:(DeviceState)state;

#pragma mark 关闭/开启视频(是否发送视频)
/// 关闭/开启视频(是否发送视频)
- (void)enableSendVideo:(DeviceState)state;

#pragma mark 暂停/恢复本地视频流的发送
/// @param mute YES-表示暂停视频流的发送。 NO-表示恢复视频流的发送
- (void)muteLocalCamera:(BOOL)mute;

#pragma mark 设置自己是否接收对方音频 自研ERTC调用
/// 设置自己是否接收对方音频
/// @param otherClientId 目标UID(传0代表所有与会人员)
/// @param enabled  Yes-接收  No-不接收
- (void)enableRecvAudioWithClientId:(int)otherClientId enabled:(BOOL)enabled;

#pragma mark 设置自己是否接收对方视频 订阅大小码流
/// 设置自己是否接收对方视频
/// @param otherClientId  目标UID(传0代表所有与会人员)
/// @param besidesId  除此SDKNO以外的用户(NoPickAudio模式使用)
/// @param mark  码流类型 1:小码流 2 大码流 4：共享流
/// @param enabled  Yes-接收  No-不接收
- (void)enableRecvVideoWithClientId:(int)otherClientId besidesId:(nullable NSString *)besidesId mark:(int)mark enabled:(BOOL)enabled;

#pragma mark 设置音频优先 VCSSDK调用
/// 设置音频优先
/// @param clientId 会者ID(码流ID)
/// @param enable YES-开启 NO-关闭
/// 开启音频优先策略缓存长度将变为1000毫秒
- (void)setAudioPriorityWithClientId:(int)clientId enable:(BOOL)enable;

#pragma mark 停止发送媒体流(音频和视频) 自研ERTC调用
/// 停止发送媒体流(音频和视频)
/// @param pause 1-停止发送，0-恢复发送
- (NSInteger)stopSendAudioAndVideo:(int)pause;

#pragma mark 设置声音播放开关 应用上层调用
/// 设置声音播放开关
/// @param isOpen YES-打开 NO-关闭
- (void)setSpeakerSwitch:(BOOL)isOpen;

#pragma mark 开启网络监测
/// 开启网络监测
/// @param config 检测配置
- (BOOL)startNetworkDetectionWithConfig:(MRTCNetworkConfig *_Nonnull)config;

#pragma mark 停止网络监测
/// 停止网络监测
- (void)stopNetworkDetection;

#pragma mark 获取当前接收的共享屏幕流信息
/// 获取当前接收的共享屏幕流信息
- (MRTCMeetingDesktopModel *)getSharingDesktopInfo;

#pragma mark 设置云端系统录制轨道 VCSSDK 调用
/// 设置云端系统录制轨道
/// @param identifier 轨道标识
- (void)setCloudRecordIdentifier:(VCSStreamIdentifier)identifier;

#pragma mark - -------- 视频会议本地采集相关接口 ---------
#pragma mark 改变屏幕方向
/// 改变屏幕方向
/// @param orientation 预览画面方向
/// @param previewSize 预览画面尺寸
/// @param isHorizontalScreen YES-横屏 NO-竖屏
- (void)changeScreenOrientation:(UIDeviceOrientation)orientation previewSize:(CGSize)previewSize isHorizontalScreen:(BOOL)isHorizontalScreen;

#pragma mark 切换摄像头(前置or后置)
/// 切换摄像头(前置or后置)
- (void)switchCamera;


#pragma mark 加载采集实例
/// 加载采集实例
/// @param displayView 预览播放器
- (void)onLocalDisplayViewReady:(MRTCLocalPreView *)displayView;

#pragma mark 判断设备是否有摄像头
/// 判断设备是否有摄像头
- (BOOL)isCameraAvailable;

#pragma mark 设置画面预览方向
/// 设置画面预览方向
/// @param deviceOrientation 预览方向
- (void)setPreviewOrientation:(UIDeviceOrientation)deviceOrientation;

#pragma mark 手动修正预览界面
/// 手动修正预览界面
/// @param size 大小
//- (void)revisePreviewSize:(CGSize)size;

#pragma mark 获取当前摄像头
/// 获取当前摄像头 0-代表前置 1-代表后置
- (int)getCurrenCamera;

#pragma mark 获取之前的缩放的倍数
/// @param userId 如果是屏幕共，传入userId为0
/// @param regionID 窗口ID，支持 0、1、2、3
- (CGFloat)viewScaleOfUserId:(NSString *)userId withRegionID:(NSInteger)regionID;

#pragma mark 移动/拖动播放视图
/// @param viewSize 播放视图的大小
/// @param userId 如果是屏幕共，传入userId为0
/// @param regionID  窗口ID
/// @param movement 移动的方向，和viewSize同单位
- (void)zoomMoveView:(CGSize)viewSize
            WithUserId:(NSString *)userId
        withRegionID:(NSInteger)regionID
            movement:(CGVector)movement;

#pragma mark 缩放播放视图
/// @param viewSize 播放视图的大小
/// @param userId 如果是屏幕共，传入userId为0
/// @param regionID 窗口ID
/// @param scale 缩放的倍数 不小于0，且不大于3
/// @param center 缩放的中心位置坐标
- (void)zoomScaleView:(CGSize)viewSize
           WithUserId:(NSString *)userId
         withRegionID:(NSInteger)regionID
                scale:(CGFloat)scale
               center:(CGPoint)center;

///获取播放视频时对应的图片
/// @param userId 远端用户ID
- (NSData *)getJPEGOfUserId:(NSString *)userId;

#pragma mark - -------- 视频会议互动消息服务相关接口 ---------
#pragma mark 发送退出房间消息
- (void)sendExitRoom;

#pragma mark 设置房间成员扩展信息
/// 设置房间成员扩展信息
/// - Parameters:
///   - targetId: 目标用户标识
///   - extendInfo: 扩展信息
///   - selves: 是否为当前账户(YES-自己 NO-其它成员)
- (void)sendRoomMemberExtendWithTargetId:(nullable NSString *)targetId extendInfo:(NSString *)extendInfo selves:(BOOL)selves;
/**
#pragma mark 发送举手操作消息
/// 发送举手操作消息
/// @param hus 举手类型(HandUpStatus_HusNone-无，HandUpStatus_HusLiftTheBan-解除禁言请求)
- (void)sendRaiseHandWithHus:(HandUpStatus)hus;

#pragma mark 发送聊天消息
/// 发送聊天消息
/// @param message 消息内容
/// @param targetId 目标用户ID(不传代表发送给会议室全体人员)
/// @param type 消息类型(MessageType_MtPicture消息待完善)
- (void)sendTextChatWithMessage:(nullable NSString *)message targetId:(nullable NSString *)targetId type:(MessageType)type;

#pragma mark 发送主持人踢人消息
/// 发送主持人踢人消息
/// @param targetId 目标用户ID
- (void)sendKickoutWithTargetId:(nullable NSString *)targetId;

#pragma mark 发送主持人禁用/关闭/开启音频消息
/// 发送主持人禁用/开启音频消息
/// @param targetId 目标用户ID(为空时代表全局禁用)
/// @param audioState 音频状态(DeviceState_DsActive-正常，DeviceState_DsClosed-关闭，DeviceState_DsDisabled-禁用)
- (void)sendKostCtrlAudioWithTargetId:(nullable NSString *)targetId audioState:(DeviceState)audioState DEPRECATED_MSG_ATTRIBUTE("此方法已经弃用，请迁移到sendKostCtrlMemberAudioWithTargetidsArray:audioState:接口");

#pragma mark 发送主持人禁用/关闭/开启视频消息
/// 发送主持人禁用/开启视频消息
/// @param targetId 目标用户ID(为空时代表全局禁用)
/// @param videoState 视频状态(DeviceState_DsActive-正常，DeviceState_DsClosed-关闭，DeviceState_DsDisabled-禁用)
- (void)sendKostCtrlVideoWithTargetId:(nullable NSString *)targetId videoState:(DeviceState)videoState DEPRECATED_MSG_ATTRIBUTE("此方法已经弃用，请迁移到sendKostCtrlMemberVideoWithTargetidsArray:videoState:接口");

#pragma mark 发送主持人操作成员音频消息
/// 发送主持人操作成员音频消息
/// @param targetidsArray 成员列表(为空时表示全局禁用)
/// @param audioState 音频状态(DeviceState_DsActive-正常，DeviceState_DsClosed-关闭，DeviceState_DsDisabled-禁用)
- (void)sendKostCtrlMemberAudioWithTargetidsArray:(nullable NSMutableArray<NSString *> *)targetidsArray audioState:(DeviceState)audioState;

#pragma mark 发送主持人操作成员视频消息
/// 发送主持人操作成员视频消息
/// @param targetidsArray 成员列表(为空时表示全局禁用)
/// @param videoState 视频状态(DeviceState_DsActive-正常，DeviceState_DsClosed-关闭，DeviceState_DsDisabled-禁用)
- (void)sendKostCtrlMemberVideoWithTargetidsArray:(nullable NSMutableArray<NSString *> *)targetidsArray videoState:(DeviceState)videoState;

#pragma mark 发送主持人操作房间音频消息
/// 发送主持人操作房间音频消息
/// @param audioState 音频状态(DeviceState_DsActive-正常，DeviceState_DsClosed-关闭，DeviceState_DsDisabled-禁用)
- (void)sendKostCtrlRoomAudioWithAudioState:(DeviceState)audioState;

#pragma mark 主持人处理举手
/// 主持人处理举手
/// @param targetId 目标用户
/// @param hus 举手类型(HandUpStatus_HusNone-无，HandUpStatus_HusLiftTheBan-解除禁言请求)
/// @param result 处理结果(YES-同意，NO-不同意)
- (void)hostDisposeRoomRaiseHandWithTargetId:(NSString *)targetId hus:(HandUpStatus)hus result:(BOOL)result;

#pragma mark 开始分享
/// 开始分享(包括：白板、图片、桌面)
/// @param sharingType 分享类型
/// @param sharingPicURL 分享图片时的图片地址
/// @param sharingRelativePicURL 分享图片时的图片相对地址
- (void)sendRoomStartToShareWithSharingType:(SharingType)sharingType sharingPicURL:(nullable NSString *)sharingPicURL sharingRelativePicURL:(nullable NSString *)sharingRelativePicURL;

#pragma mark 停止分享
/// 停止分享(包括：白板、图片、桌面)
- (void)sendRoomStopSharing;

#pragma mark 设置开启&关闭水印
/// 设置开启&关闭水印
/// @param openState YES-开启水印 NO-关闭水印
- (void)sendRoomWaterMarkWithOpenState:(BOOL)openState;

#pragma mark 转移房间主持人权限
/// 转移房间主持人权限
/// @param targetId 目标用户
- (void)sendRoomMoveHostWithTargetId:(NSString *)targetId;

#pragma mark 设置房间联席主持人权限
/// 设置房间联席主持人权限
/// @param targetId 目标用户
/// @param enable YES-设置 NO-回收
- (void)sendRoomUnionHostWithTargetId:(NSString *)targetId enable:(BOOL)enable;

#pragma mark 回收房间主持人权限
/// 回收房间主持人权限
/// @param targetId 目标用户
- (void)sendRoomRecoveryHostWithTargetId:(nullable NSString *)targetId;

#pragma mark 设置房间静音状态
/// 设置房间静音状态
/// @param state 静音状态
- (void)sendRoomMuteWithState:(MuteState)state;

#pragma mark 设置房间成员昵称
/// 设置房间成员昵称
/// @param targetId 目标用户ID
/// @param nickname 目标昵称
/// @param selves 是否为当前账户(YES-自己 NO-其它成员)
- (void)sendRoomMemberNicknameWithTargetId:(nullable NSString *)targetId nickname:(NSString *)nickname selves:(BOOL)selves;

#pragma mark 设置房间是否允许自行解除禁音
/// 设置房间是否允许自行解除禁音
/// @param enable YES-允许解除禁音 NO-不允许解除禁音
- (void)sendRoomRelieveStateWithEnable:(BOOL)enable;

#pragma mark 设置房间成员扩展信息
/// 设置房间成员扩展信息
/// - Parameters:
///   - targetId: 目标用户标识
///   - extendInfo: 扩展信息
///   - selves: 是否为当前账户(YES-自己 NO-其它成员)
- (void)sendRoomMemberExtendWithTargetId:(nullable NSString *)targetId extendInfo:(NSString *)extendInfo selves:(BOOL)selves;
 
 */
@end

NS_ASSUME_NONNULL_END
