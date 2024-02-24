
project('tutorial', ['c','cpp'], default_options : ['c_std=gnu11', 'cpp_std=gnu++20'])


cmake = import('cmake')


#curl_dep = subproject('curl', default_options: ['default_library=static', 'ssh=disabled', 'ssl=disabled' ])
#dependency('cpr'),

lvgl_dep = cmake.subproject('lvgl')

deps = [dependency('nlohmann_json'),dependency('lvgl'),dependency('lvgl_demos')]
executable('demo', ['main.cpp'], dependencies: deps)

