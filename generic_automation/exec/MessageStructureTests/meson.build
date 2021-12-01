project('MessageTests', 'cpp')
StringManipulation_dep = dependency('StringManipulation', fallback : ['StringManipulation', 'StringManipulation_dep'])
MessageStructure_dep = dependency('MessageStructure', fallback : ['MessageStructure', 'MessageStructure_dep'])
Debug_dep = dependency('Debug', fallback : ['Debug', 'Debug_dep'])

executable('MessageTests', 'src/main.cpp',
    dependencies : [MessageStructure_dep, StringManipulation_dep, Debug_dep])
