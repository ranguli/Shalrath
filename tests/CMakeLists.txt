# tests/CMakeLists.txt


# FetchContent module
include(FetchContent)
# Fetch GoogleTest from GitHub
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG     main  # Use the appropriate tag or branch
)

# Make the googletest content available
FetchContent_MakeAvailable(googletest)

# Set compiler-specific flags
if (MSVC)
  set_target_properties(gtest PROPERTIES COMPILE_FLAGS "/w")
  set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS "/w")
else()
  set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-w")
  set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS "-w")
endif()

enable_testing()

# Add test executable
add_executable(run_tests
  DatabaseTests.cpp
  NetworkTests.cpp
  ParserTests.cpp
)

# Link against GoogleTest and GoogleMock
target_link_libraries(run_tests
  gtest
  gtest_main
  gmock
  gmock_main
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