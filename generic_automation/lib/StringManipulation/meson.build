project('StringManipulation', 'cpp')

inc = include_directories('include')
libStringManipulation = shared_library('StringManipulation',
  'src/StringBuilder.cpp',
  include_directories : inc,
  install : true)

StringManipulation_dep = declare_dependency(
    include_directories : inc,
    link_with : libStringManipulation)
