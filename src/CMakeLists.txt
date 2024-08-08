# src/CMakeLists.txt
add_subdirectory(UI)
add_subdirectory(Database)
add_subdirectory(Model)
add_subdirectory(Network)
add_subdirectory(Parser)

add_executable(shalrath main.cpp)

target_include_directories(shalrath
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(shalrath
  ui_lib
  network_lib
  database_lib
  model_lib
  parser_lib
  resources
)
