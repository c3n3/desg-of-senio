project('CommonTests', 'cpp')
Common = dependency('Common', fallback : ['Common', 'Common_dep'])

extra_args = ['-Oz']

executable('CommonTests', 'src/main.cpp',
    dependencies : [Common], c_args: extra_args)
