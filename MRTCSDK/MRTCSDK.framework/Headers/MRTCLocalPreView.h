//
//  MRTCLocalPreView.h
//  ERTCVCSSDK
//
//  Created by wangjinlong23 on 2024/2/4.
//

#import <UIKit/UIKit.h>
#import <MRTCSDK/MRTCSDKDefines.h>

NS_ASSUME_NONNULL_BEGIN

#if MRTC_DINGRTC_ENABLED
@class DingRtcVideoCanvas;
#endif
@interface MRTCLocalPreView : UIView

///窗口标识 0:小窗口 1:大窗口
@property(nonatomic, assign) int regionID;

#pragma mark 视图初始化
/// 初始化会议SDK(YES-连接成功，NO-连接失败)
/// @param frame 视图大小
/// @param regionID 窗口ID 0:小窗口 1:大窗口
-(instancetype)initWithFrame:(CGRect)frame regionID:(int)regionID;

#pragma mark 获取播放视图
- (UIView *)getLocalPlayerView;

#pragma mark 重置播放视图
- (void)resetLocalPlayerView;

#pragma mark - 清除像素
/// 清除像素
- (void)cleanpixels;

/// 手动修正预览界面
/// @param size 大小
- (void)revisePreviewSize:(CGSize)size;

#pragma mark - 设置显示翻转
/// 设置显示翻转
/// 当开启自定义显示控制模式时有效
/// - Parameters:
///   - flipX: X轴翻转
///   - flipY: Y轴翻转
- (void)setViewflip:(BOOL)flipX flipY:(BOOL)flipY;

#pragma mark - 开启支持视图缩放移动
/// 开启支持视图缩放移动
/// 当开启支持视图缩放移动，[使用 move:、zoom:、directZoom:、getCurrentScale 操作视图的移动和缩放]
/// - Parameter open: 是否开启，默认 不开启
- (void)openViewZoomAndMove:(BOOL)open;

#if MRTC_DINGRTC_ENABLED
///获取钉钉播放视图
- (DingRtcVideoCanvas *)getCanvasWithView;
#endif
@end

NS_ASSUME_NONNULL_END
