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
  spec.version      = "1.0.1"
  spec.summary      = "A short description of MRTCSDK."
  spec.description  = <<-DESC
  TODO: Add long description of the pod here.
                   DESC

  spec.homepage     = "https://github.com/Ezviz-Open/MRTCSDK-iOS.git"
  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author             = { "jinlongyu23" => "open-team@ezvizlife.com" }
  
  spec.ios.deployment_target = "12.0"
  
  spec.static_framework = true
  
  spec.weak_frameworks = 'SystemConfiguration', 'Accelerate', 'AVFoundation', 'QuartzCore', 'CoreGraphics', 'CoreMedia', 'CoreAudio', 'CoreVideo', 'CoreML', 'OpenGLES', 'Security', 'CFNetwork', 'UIKit', 'Foundation', 'ReplayKit', 'PushKit', 'CoreTelephony'

  spec.source       = { :git => "https://github.com/Ezviz-Open/MRTCSDK-iOS.git", :tag => "#{spec.version}" }

  spec.source_files = "MRTCSDK/MRTCSDK.framework/Headers/*.{h,m}"
  
  spec.framework  = "Foundation", "UIKit"
  
  spec.vendored_frameworks = 'MRTCSDK/MRTCSDK.framework'
  
  # 依赖开源库
  spec.dependency 'ERTCSDK'
  spec.dependency 'VCSSDK'
  spec.dependency 'MMKV'
  spec.dependency 'Protobuf'
  spec.dependency 'DingRTC_iOS'
  spec.dependency 'SSZipArchive', '>= 2.4.3'
  spec.dependency 'AFNetworking', '>= 4.0.0'
  
  spec.requires_arc = true
  
  spec.user_target_xcconfig = { 'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1' }
  
  spec.pod_target_xcconfig = { 'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) VCS_USE_PROTOBUF_BEAUTY_IMPORTS=1' }
end
