# src/Parser/CMakeLists.txt
find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(parser_lib QuaddictedXMLParser.cpp)

target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(parser_lib Qt6::Core model_lib)
