project('Common', 'cpp')

inc = include_directories('./include')
libCommon = shared_library('Common',
  './src/Message.cpp',
  './src/MessageId.cpp',
  './src/HexStringSerializer.cpp',
  './src/StepperMotorMessage.cpp',
  './src/StringBuilder.cpp',
  include_directories : inc,
  install : true,
  dependencies : [])

curlpp = dependency('curlpp')

Common_dep = declare_dependency(
    include_directories : inc,
    link_with : [libCommon],
    dependencies: [curlpp])
