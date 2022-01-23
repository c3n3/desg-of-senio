project('Common', 'cpp')

inc = include_directories('.')
libCommon = shared_library('Common',
  'Message.cpp',
  'StepperMotorMessage.cpp',
  'StringBuilder.cpp',
  include_directories : inc,
  install : true,
  dependencies : [])

Common_dep = declare_dependency(
    include_directories : inc,
    link_with : libCommon)
