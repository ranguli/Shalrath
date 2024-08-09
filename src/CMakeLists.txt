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


if (MSVC)
    set(QT_WINDEPLOYQT_EXECUTABLE "C:/Qt/6.7.2/msvc2019_64/bin/windeployqt.exe")

    add_custom_command(TARGET shalrath POST_BUILD
    COMMAND ${QT_WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:shalrath>
    COMMENT "Running windeployqt to deploy Qt dependencies..."
)
endif()