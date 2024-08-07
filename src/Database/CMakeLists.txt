# src/Database/CMakeLists.txt
add_library(database_lib SQLManager.cpp)
target_include_directories(database_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
