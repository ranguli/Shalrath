gtest_dep = dependency('gtest', required: true)

test_sources = [
  'DatabaseTests.cpp',
  'NetworkTests.cpp',
  'main.cpp'
]

test_executable = executable('run_tests',
  sources: test_sources,
  dependencies: [gtest_dep, network_dep, database_dep],
  install: false
)

test('run_tests', test_executable)
