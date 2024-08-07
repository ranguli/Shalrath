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

# Custom function to find qmake
qmake_paths = [
  '/usr/lib/qt6/bin/qmake',
  '/usr/bin/qmake6',
  '/opt/qt6/bin/qmake',
  '/usr/local/bin/qmake6'
]

qmake_found = false
foreach path : qmake_paths
  if run_command('test', '-x', path).returncode() == 0
    qmake_found = true
    env = environment()
    env.set('QMAKE', path)
    break
  endif
endforeach

if not qmake_found
  error('qmake not found in the specified paths')
endif

qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets', 'Network', 'Sql'], required: true, method: 'pkg-config')

subdir('resources')
subdir('src')
subdir('tests')
