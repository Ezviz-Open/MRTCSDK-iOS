/**
 * MRTCSDKDefines.h
 * MRTCSDK —— 全局宏定义
 *
 * 需求：2.3.0
 */

#ifndef MRTCSDKDefines_h
#define MRTCSDKDefines_h

/**
 * MRTC_DINGRTC_ENABLED
 *
 * 控制是否编译 DingRTC 相关代码。
 * - 默认值为 1（启用），业务方引入 DingRTC_iOS pod 时正常编译。
 * - 不需要 DingRTC 的业务方，在 Build Settings 的 GCC_PREPROCESSOR_DEFINITIONS 中
 *   设置 MRTC_DINGRTC_ENABLED=0，并移除 DingRTC_iOS pod 依赖即可。
 */
#ifndef MRTC_DINGRTC_ENABLED
#define MRTC_DINGRTC_ENABLED 1
#endif

#endif /* MRTCSDKDefines_h */
