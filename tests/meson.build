gtest_dep = dependency('gtest', required: true)
curl_dep = dependency('libcurl', required: true)

test_sources = [
  'NetworkTests.cpp',
  'main.cpp'
]

test_executable = executable('run_tests',
  sources: test_sources,
  dependencies: [gtest_dep, curl_dep, network_dep],
  install: false
)

test('run_tests', test_executable)
