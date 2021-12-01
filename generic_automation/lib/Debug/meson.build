project('Debug', 'cpp')

inc = include_directories('include')
libDebug = shared_library('Debug',
  include_directories : inc,
  install : true)

Debug_dep = declare_dependency(
    include_directories : inc,
    link_with : libDebug)
