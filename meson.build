
project('tutorial', 'cpp', default_options : ['c_std=c11', 'cpp_std=c++20'])

cmake = import('cmake')

lvgl_dep = cmake.subproject('lvgl')



deps = [dependency('nlohmann_json'),dependency('cpr'),dependency('lvgl')]
executable('demo', ['main.cpp'], dependencies: deps)

message('Info')
message(meson.get_compiler('c').get_id())
