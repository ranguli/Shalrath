# src/Model/CMakeLists.txt
add_library(model_lib Map.cpp)
target_include_directories(model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
