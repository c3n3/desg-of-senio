project('MessageStructure', 'cpp')

StringManipulation_dep = dependency('StringManipulation', fallback : ['StringManipulation', 'StringManipulation_dep'])
Debug_dep = dependency('Debug', fallback : ['Debug', 'Debug_dep'])

inc = include_directories('include')
libMessageStructure = shared_library('MessageStructure',
  'src/Message.cpp',
  'src/StepperMotorMessage.cpp',
  include_directories : inc,
  install : true,
  dependencies : [StringManipulation_dep, Debug_dep])

MessageStructure_dep = declare_dependency(
    include_directories : inc,
    link_with : libMessageStructure)
