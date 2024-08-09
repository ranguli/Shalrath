# tests/CMakeLists.txt

# Configure Google Test to use the same runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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

# Ignore compiler warnings about the googletest library

if (MSVC)
    target_compile_options(gtest PRIVATE /w /EHsc /wd4530)
    target_compile_options(gtest_main PRIVATE /w /EHsc /wd4530)
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

# Copy the DLLs if on Windows to the build directory
if (MSVC)
    set(QT_WINDEPLOYQT_EXECUTABLE "C:/Qt/6.7.2/msvc2019_64/bin/windeployqt.exe")
endif()

# Add tests
add_test(NAME run_tests COMMAND run_tests)