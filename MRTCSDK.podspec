#
#  Be sure to run `pod spec lint TestERTCSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/podspec.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |spec|

  # ―――  Spec Metadata  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  These will help people to find your library, and whilst it
  #  can feel like a chore to fill in it's definitely to your advantage. The
  #  summary should be tweet-length, and the description more in depth.
  #

  spec.name         = "MRTCSDK"
  spec.version      = "2.1.0"
  spec.summary      = "MRTCSDK is a multi-platform real-time communication SDK for iOS."
  spec.description  = <<-DESC
  MRTCSDK provides multi-platform real-time communication capabilities for iOS,
  supporting audio/video calls, screen sharing, and whiteboard collaboration.
  It integrates with ERTC, VCS, and optionally DingRTC backends.
                   DESC

  spec.homepage     = "https://github.com/Ezviz-Open/MRTCSDK-iOS.git"
  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author             = { "jinlongyu23" => "open-team@ezvizlife.com" }
  
  spec.ios.deployment_target = "12.0"
  
  spec.static_framework = true
  
  spec.weak_frameworks = 'SystemConfiguration', 'Accelerate', 'AVFoundation', 'QuartzCore', 'CoreGraphics', 'CoreMedia', 'CoreAudio', 'CoreVideo', 'CoreML', 'OpenGLES', 'Security', 'CFNetwork', 'UIKit', 'Foundation', 'ReplayKit', 'PushKit', 'CoreTelephony'

  spec.source       = { :git => "https://github.com/Ezviz-Open/MRTCSDK-iOS.git", :tag => "#{spec.version}" }

  spec.requires_arc = true

  # ―――  Subspecs  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  
  # Core subspec: 不包含 DingRTC 依赖（使用 MRTC_DINGRTC_ENABLED=0 编译的 framework）
  spec.subspec 'Core' do |core|
    core.vendored_frameworks = 'Core/MRTCSDK.framework'
    core.source_files = 'Core/MRTCSDK.framework/Headers/*.h'
    core.framework = "Foundation", "UIKit"
    core.dependency 'ERTCSDK'
    core.dependency 'VCSSDK'
    core.dependency 'MMKV'
    core.dependency 'Protobuf'
    core.dependency 'SSZipArchive', '>= 2.4.3'
    core.dependency 'AFNetworking', '>= 4.0.0'
    core.pod_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1 MRTC_DINGRTC_ENABLED=0'
    }
    core.user_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1 MRTC_DINGRTC_ENABLED=0'
    }
  end

  # DingRTC subspec: 包含 DingRTC 依赖（使用 MRTC_DINGRTC_ENABLED=1 编译的 framework，默认启用）
  spec.subspec 'DingRTC' do |ding|
    ding.vendored_frameworks = 'Full/MRTCSDK.framework'
    ding.source_files = 'Full/MRTCSDK.framework/Headers/*.h'
    ding.framework = "Foundation", "UIKit"
    ding.dependency 'ERTCSDK'
    ding.dependency 'VCSSDK'
    ding.dependency 'MMKV'
    ding.dependency 'Protobuf'
    ding.dependency 'SSZipArchive', '>= 2.4.3'
    ding.dependency 'AFNetworking', '>= 4.0.0'
    ding.dependency 'DingRTC_iOS/RtcBasic'
    ding.dependency 'DingRTC_iOS/AudioEnhance'
    ding.pod_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1 MRTC_DINGRTC_ENABLED=1'
    }
    ding.user_target_xcconfig = {
      'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1 MRTC_DINGRTC_ENABLED=1'
    }
  end

  # 默认引入 DingRTC
  spec.default_subspecs = 'DingRTC'
end
