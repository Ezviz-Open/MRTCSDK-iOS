//
//  MRTCPlayerZoomView.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/2.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

//画中画视图
@interface MRTCPlayerZoomView : UIView
#pragma mark 视图初始化
/// @param frame 视图大小
-(instancetype)initWithFrame:(CGRect)frame;

#pragma mark -开启画中画
/// - Parameter userID: 用户ID
///-   Parameter isSharing: 用户共享状态
- (void)startPIP:(NSString *)userID isSharing:(BOOL)isSharing;

#pragma mark -停止画中画
- (void)stopPIP;

#pragma mark -更新数据状态
/// - Parameter userID: 用户ID
///-   Parameter isSharing: 用户共享状态
- (void)updateUserInfo:(NSString *)userID isSharing:(BOOL)isSharing;

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

#pragma mark - 设置自定义显示控制模式
/// 设置自定义显示控制模式
/// 当开启自定义显示控制模式时，[使用 setViewScaleType:、setViewflip:、setViewRotate: 定义画面旋转角度、显示翻转以及显示模式]
/// - Parameter use: 是否开启，默认不开启
- (void)customDisplayCtrl:(BOOL)use;

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

#pragma mark - 释放播放器
/// 释放播放器
- (void)ReleasePlay;

@end

NS_ASSUME_NONNULL_END
