//
//  MRTCSDKLogManager.h
//  MRTCSDK
//
//  Created by wangjinlong23 on 2025/6/25.
//

#import <Foundation/Foundation.h>
#import <MRTCSDK/MRTCEnum.h>

NS_ASSUME_NONNULL_BEGIN

#define MRTCLogWithType(frmt, ...) \
do {[[MRTCSDKLogManager sharedManager] logWithMessage:[NSString stringWithFormat:(frmt), ##__VA_ARGS__]];} while(0)

#define MRTCLog(frmt, ...) \
MRTCLogWithType(frmt, ##__VA_ARGS__)

@interface MRTCSDKLogManager : NSObject
#pragma mark 获取日志管理模块单例
/// 获取音频会话单例
+(instancetype)sharedManager;

#pragma mark - 输出log
- (void)logWithMessage:(NSString *)message;

#pragma mark - 保存音频日志
/// @param save 是否保存
- (void)saveAudioFile:(BOOL)save;

#pragma mark - 保存视频日志
/// @param save 是否保存
- (void)saveRemoteVideo:(BOOL)save;

#pragma mark -是否打开SDK日志
/// @param open 是否打开
/// @param level 日志等级
/// @param logCallback 日志回调
- (void)openSDKLog:(BOOL)open withLogLevel:(MRTCLogLevel)level withLogCallback:(void(^)(NSString *logStr))logCallback;

#pragma mark -打开文件log功能，将log写入文件
- (void)enableFileLog:(BOOL)enable;

#pragma mark -写入日志
/// @param logMessage 日志信息
-(void)writeLog:(NSString *)logMessage;
@end

NS_ASSUME_NONNULL_END
