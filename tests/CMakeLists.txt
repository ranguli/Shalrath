# tests/CMakeLists.txt

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(run_tests
  DatabaseTests.cpp
  NetworkTests.cpp
  ParserTests.cpp
)

target_link_libraries(run_tests
  gtest
  gtest_main
  parser_lib
  network_lib
  database_lib
  model_lib
)

# Copy the test fixture to the build directory
add_custom_command(
  TARGET run_tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/tests/fixtures/quaddicted_database.xml
    ${CMAKE_BINARY_DIR}/tests/quaddicted_database.xml
)

# Add tests
add_test(NAME run_tests COMMAND run_tests)
