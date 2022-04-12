project('Common', 'cpp')

inc = include_directories('./include')
libCommon = shared_library('Common',
  './src/Message.cpp',
  './src/Timer.cpp',
  './src/MessageId.cpp',
  './src/HexStringSerializer.cpp',
  './src/StepperMotorMessage.cpp',
  './src/ButtonMessage.cpp',
  './src/PwmMessage.cpp',
  './src/SubscribeMessage.cpp',
  './src/DebugDevice.cpp',
  './src/Device.cpp',
  './src/EncoderMessage.cpp',
  './src/Capabilities.cpp',
  './src/Router.cpp',
  './src/Subscriber.cpp',
  include_directories : inc,
  install : true,
  dependencies : [])

curlpp = dependency('curlpp')

Common_dep = declare_dependency(
    include_directories : inc,
    link_with : [libCommon],
    dependencies: [curlpp])
