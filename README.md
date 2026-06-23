# MRTCSDK-iOS

萤石融合 RTC SDK（Multi-platform Real-Time Communication SDK）for iOS，提供多平台实时音视频通信能力。

## 功能特性

- 音视频通话（支持多人会议）
- 屏幕共享（基于 ReplayKit）
- 网络自适应码率调控
- 音频降噪
- 摄像头前后置切换 & 镜像
- 主持人会控能力（禁言、踢人、转让主持人等）
- 网络探测与质量回调
- 云端录制
- 网络研讨会（Webinar）

## 架构说明

SDK 支持多种 RTC 后端引擎：

| Subspec | 说明 |
|---------|------|
| `Core` | 基于自研 ERTC + VCS，不包含钉钉 RTC |
| `DingRTC`（默认） | 在 Core 基础上增加钉钉 RTC 支持 |

## 环境要求

- iOS 12.0+
- Xcode 14+
- CocoaPods

## 安装

在 `Podfile` 中添加：

```ruby
# 默认引入（含 DingRTC）
pod 'MRTCSDK'

# 或仅使用 Core（不含 DingRTC）
pod 'MRTCSDK/Core'
```

然后执行：

```bash
pod install
```

## 快速开始

### 1. 初始化 SDK

```objc
#import <MRTCSDK/MRTCSDKManager.h>

// 获取单例
MRTCSDKManager *manager = [MRTCSDKManager sharedManager];

// 设置媒体配置
MRTCSDKConfigModel *config = [[MRTCSDKConfigModel alloc] init];
[manager setMediaConfig:config];
```

### 2. 加入房间

```objc
MRTCSDKJoinRoomParam *param = [[MRTCSDKJoinRoomParam alloc] init];
// 配置入会参数...

BOOL success = [manager initMediaSessionWithMeetingParam:param delegate:self];
```

### 3. 音视频控制

```objc
// 开启/关闭音频
[manager enableSendAudio:DeviceState_DsActive];

// 开启/关闭视频
[manager enableSendVideo:DeviceState_DsActive];

// 切换摄像头
[manager switchCamera];
```

### 4. 屏幕共享

```objc
// 开启屏幕录制（需配置 App Group）
[manager startScreenRecordWithAppGroup:@"group.com.your.appgroup"];

// 停止屏幕录制
[manager stopScreenRecord];
```

### 5. 退出会议

```objc
[manager destroy:YES finishBlock:^{
    // 资源释放完成
}];
```

## 主要类说明

| 类名 | 职责 |
|------|------|
| `MRTCSDKManager` | SDK 核心管理类（单例），负责入会、音视频控制、互动消息 |
| `MRTCSDKConfigModel` | SDK 初始化配置 |
| `MRTCSDKJoinRoomParam` | 入会参数模型 |
| `MRTCLocalPreView` | 本地视频预览视图 |
| `MRTCRemotePreView` | 远端视频渲染视图 |
| `MRTCNetworkConfig` | 网络探测配置 |
| `MRTCBeautyManager` | 美颜管理 |
| `MRTCAudioSessionManager` | 音频会话管理 |
| `MRTCWhiteBoardView` | 白板视图 |
| `MRTCReplayKit` | 屏幕共享录制工具 |

## 回调代理

实现 `MRTCSDKManagerProtocol` 获取会议事件回调：

- 远端用户进入/退出房间
- 码流状态变化
- 网络质量回调
- 主持人会控事件
- 聊天消息
- 屏幕共享状态
- 云录制状态

实现 `MRTCSDKManagerCameraProtocol` 获取本地采集数据回调。

## 依赖库

- [ERTCSDK](https://github.com/Ezviz-Open) — 自研 RTC 引擎
- [VCSSDK](https://github.com/Ezviz-Open) — 视频会议服务
- [DingRTC_iOS](https://github.com/AlivcRTC) — 钉钉 RTC（DingRTC subspec）
- MMKV
- Protobuf
- SSZipArchive (>= 2.4.3)
- AFNetworking (>= 4.0.0)

## 许可证

本项目基于 MIT 许可证开源，详见 [LICENSE](LICENSE) 文件。
