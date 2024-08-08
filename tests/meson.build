test_fixture = 'fixtures/quaddicted_database.xml'

test_fixture_target = custom_target(
    'test_fixture_target',
    output: 'quaddicted_database.xml',
    input: test_fixture,
    command: ['cp', '@INPUT@', '@OUTPUT@'],
    install: false,
    build_by_default: true
)

test_exe = executable('run_tests',
  [
     'DatabaseTests.cpp',
     'NetworkTests.cpp', 
     'ParserTests.cpp'
  ], 
  dependencies: [gtest_dep, gtest_main_dep, parser_dep, network_dep, database_dep],
  install: true,
)

test('run tests', test_exe, env: {'QT_QPA_PLATFORM': 'offscreen'}, depends: [test_fixture_target])
