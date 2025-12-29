//
//  MRTCLocalPreView.h
//  ERTCVCSSDK
//
//  Created by wangjinlong23 on 2024/2/4.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class DingRtcVideoCanvas;
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

///获取钉钉播放视图
- (DingRtcVideoCanvas *)getCanvasWithView;
@end

NS_ASSUME_NONNULL_END
