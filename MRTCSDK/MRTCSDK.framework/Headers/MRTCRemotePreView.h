//
//  MRTCRemotePreView.h
//  ERTCVCSSDK
//
//  Created by wangjinlong23 on 2024/2/4.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MRTCRemotePreView : UIView
//窗口标识 0:小窗口 1:大窗口
@property(nonatomic, assign) int regionID;
//屏幕共享开始标识
@property (nonatomic, assign) BOOL startScreenSharing;

#pragma mark 视图初始化
/// 初始化会议SDK(YES-连接成功，NO-连接失败)
/// @param frame 视图大小
/// @param regionID 窗口ID 0:小窗口 1:大窗口
-(instancetype)initWithFrame:(CGRect)frame regionID:(int)regionID;

#pragma mark 获取播放视图
- (UIView *)getLocalPlayerView;

#pragma mark - 渲染显示PixelBuffer数据[YUV]
/// 渲染显示PixelBuffer数据[YUV]
/// - Parameter pixelBuffer: 像素数据
- (int)displayCVPixleBuffer:(CVPixelBufferRef)pixelBuffer;

#pragma mark - 渲染显示YUV数据
/// 渲染显示YUV数据
/// - Parameters:
///   - track: 视频流轨道
///   - type: YUV数据类型(0-I420 1-NV12 2-NV21)
///   - lable: 视频流角度
///   - width: 视频流宽
///   - height: 视频流高
///   - yData: Y数据
///   - uData: U数据
///   - vData: V数据
- (int)displayYUVData:(int)track type:(int)type lable:(int)lable width:(int)width height:(int)height yData:(void *)yData uData:(void *)uData vData:(void *)vData;

#pragma mark - 清除像素
/// 清除像素
- (void)cleanpixels;

#pragma mark - 重置布局
/// 重置布局
/// - Parameter set: YES-重新计算
- (void)SetLayoutReset:(BOOL)set;

#pragma mark - 设置显示翻转
/// 设置显示翻转
/// 当开启自定义显示控制模式时有效
/// - Parameters:
///   - flipX: X轴翻转
///   - flipY: Y轴翻转
- (void)setViewflip:(BOOL)flipX flipY:(BOOL)flipY;

#pragma mark - 设置画面旋转角度
/// 设置画面旋转角度
/// 当开启自定义显示控制模式时有效
/// - Parameter rotateAngle: 旋转角度
- (void)setViewRotate:(int)rotateAngle;

#pragma mark - 设置自定义显示控制模式
/// 设置自定义显示控制模式
/// 当开启自定义显示控制模式时，[使用 setViewScaleType:、setViewflip:、setViewRotate: 定义画面旋转角度、显示翻转以及显示模式]
/// - Parameter use: 是否开启，默认不开启
- (void)customDisplayCtrl:(BOOL)use;

#pragma mark - 开启支持视图缩放移动
/// 开启支持视图缩放移动
/// 当开启支持视图缩放移动，[使用 move:、zoom:、directZoom:、getCurrentScale 操作视图的移动和缩放]
/// - Parameter open: 是否开启，默认 不开启
- (void)openViewZoomAndMove:(BOOL)open;

#pragma mark - 平移视图
/// 平移视图
/// 开启支持视图缩放移动有效
/// - Parameters:
///   - dx: X轴偏移量
///   - dy: Y轴偏移量
- (void)move:(float)dx dy:(float)dy;

#pragma mark - 缩放视图
/// 缩放视图
/// 开启支持视图缩放移动有效
/// - Parameter scale: 缩放比例
- (void)zoom:(float)scale;

#pragma mark - 中心点缩放视图
/// 中心点缩放视图
/// 开启支持视图缩放移动有效
/// - Parameter scale: 缩放比例
- (void)directZoom:(float)scale;

#pragma mark - 获取当前的缩放比例
/// 获取当前的缩放比例
/// 开启支持视图缩放移动有效
- (float)getCurrentScale;

#pragma mark - 释放播放器
/// 释放播放器
- (void)ReleasePlay;

#pragma mark -适配层代码新增
/// - Parameter userId:用户id 传空则表示预览本地摄像头
- (void)setRemotePlayerView:(nullable NSString *)streamId;

#pragma mark -设置本地画面
- (void)setLocalView;

#pragma mark -清空本地画面
- (void)resetLocalView;

#pragma mark-清空远端画面
/// @param streamId 流媒体标识
- (void)resetRemoteView:(NSString *)streamId;

#pragma mark-Dingding屏幕共享缩放
#pragma mark-更新屏幕的相对缩放比例。
- (void)updateScreenScaling:(CGFloat)scale focus:(CGPoint)focus;

#pragma mark- 更新屏幕的相对移动距离。
- (void)updateScreenMoving:(CGPoint)distance;

#pragma mark - 缩放手势处理
- (void)handlePinchGestureRecognizer:(UIPinchGestureRecognizer *)sender;
#pragma mark - 拖动手势处理
- (void)handlePanGestureRecognizer:(UIPanGestureRecognizer *)sender;

@end

NS_ASSUME_NONNULL_END
