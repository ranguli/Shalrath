test_exe = executable('run_tests',
  [
     # Add all your test files here
    'DatabaseTests.cpp',
    'NetworkTests.cpp', 
  ], 
  dependencies: [gtest_dep, gtest_main_dep, network_dep, database_dep],
  install: true,
)

test('run tests', test_exe)
