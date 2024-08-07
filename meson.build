project('shalrath', 'cpp',
  default_options: [
    'cpp_std=c++17',
    'warning_level=3',
    'werror=false'
  ]
)

# Additional specific compiler warnings and options
add_project_arguments([
  '-Wpedantic',
  '-Wshadow',
  '-Wnon-virtual-dtor',
  '-Wold-style-cast',
  '-Wcast-align',
  '-Wunused',
  '-Woverloaded-virtual',
  '-Wconversion',
  '-Wsign-conversion',
  '-Wmisleading-indentation',
  '-Wduplicated-cond',
  '-Wlogical-op',
  '-Wnull-dereference',
  '-Wdouble-promotion',
  '-Wformat=2',
  '-fstack-protector'
], language: 'cpp')



cmake = import('cmake')

gtest_cmake = cmake.subproject('googletest', cmake_options : [
  '-DBUILD_GMOCK=OFF',
  '-DBUILD_GTEST=ON',
  '-DBUILD_SHARED_LIBS=OFF',
  '-DINSTALL_GTEST=OFF'
])

gtest_dep = gtest_cmake.dependency('gtest')
gtest_main_dep = gtest_cmake.dependency('gtest_main')

subdir('resources')
subdir('src')
subdir('tests')
