enable_testing()

add_executable(run_tests
  DatabaseTests.cpp
  NetworkTests.cpp
  ParserTests.cpp
)

target_link_libraries(run_tests
  gtest_main
  parser_lib
  network_lib
  database_lib
  ui_lib
)

include(GoogleTest)
gtest_discover_tests(run_tests)

# Test fixtures
file(COPY ${CMAKE_SOURCE_DIR}/tests/fixtures/quaddicted_database.xml DESTINATION ${CMAKE_BINARY_DIR}/tests/fixtures)
