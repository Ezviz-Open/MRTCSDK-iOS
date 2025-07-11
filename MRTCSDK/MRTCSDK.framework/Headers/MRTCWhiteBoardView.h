//
//  MRTCWhiteBoardView.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2024/3/4.
//

#import <UIKit/UIKit.h>
#import <MRTCSDK/MRTCEnum.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^MRTCDrawingConnectBlock)(MRTCDrawConnectState state);

typedef void (^MRTCDrawingClearBlock)(void);

/// 电子画板事件代理
@protocol MRTCDrawingDelegate <NSObject>

@optional

/// 图片按钮点击事件
- (void)onSelectedPictureEvent;

/// 电子画板图片变更事件
/// @param imageUrl 背景图片路径
- (void)onChangeDrawBackImageEvent:(nullable NSString *)imageUrl;

@end


@interface MRTCWhiteBoardView : UIView
#pragma mark - 电子画板事件代理
@property (nonatomic, weak) id <MRTCDrawingDelegate> delegate;

#pragma mark 视图初始化
/// @param frame 视图大小
-(instancetype)initWithFrame:(CGRect)frame drawingParam:(MRTCDrawingParam *)param;

#pragma mark - 设置画笔工具栏中图片按钮状态
/// 设置画笔工具栏中图片按钮状态
/// @param state YES-隐藏 NO-显示
- (void)setupPictureButtonWithState:(BOOL)state;

#pragma mark - 设置按钮配置参数
/// 设置按钮配置参数
/// @param param 配置参数
- (void)setupDrawingParam:(MRTCDrawingParam *)param;

#pragma mark - 电子白板服务连接
/// 电子白板服务连接
/// @param address 电子白板服务地址
/// @param port 电子白板服务端口
/// @param roomId 房间ID
/// @param userId 用户ID
/// @param privileges 是否开启书写权限
/// @param eraserImage 橡皮擦画笔图标
/// @param imageUrl 背景图片路径(共享白板时，无需传此参数)
/// @param image 背景图片(共享白板时，无需传此参数)
/// @param connectBlock 连接状态回调(YES-连接状态，NO-断开连接状态)
/// @param clearBlock 清空电子画板数据回调
- (void)drawServicConnectWithAddress:(NSString *)address port:(int)port roomId:(NSString *)roomId userId:(NSString *)userId privileges:(BOOL)privileges eraserImage:(nullable UIImage *)eraserImage image:(nullable UIImage *)image imageUrl:(nullable NSString *)imageUrl connectBlock:(nullable MRTCDrawingConnectBlock)connectBlock clearBlock:(nullable MRTCDrawingClearBlock)clearBlock;

#pragma mark - 更换服务背景图片
/// 更换服务背景图片
/// @param image 背景图片
/// @param imageUrl 背景图片路径
- (void)changeDrawBackImageWithImage:(nullable UIImage *)image imageUrl:(nullable NSString *)imageUrl;

#pragma mark - 清空电子画板数据
/// 清空电子画板数据
- (void)drawingClear;

#pragma mark -关闭白板
-(void)closeWhiteBoardShareView;
@end

NS_ASSUME_NONNULL_END
