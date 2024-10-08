# src/CMakeLists.txt
add_subdirectory(Core)
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
  core_lib
  ui_lib
  network_lib
  database_lib
  model_lib
  parser_lib
  resources
)

# Copy the DLLs if on Windows to the right directory
if (MSVC)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "C:/Qt/6.7.2/msvc2019_64/bin")

    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET shalrath POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:shalrath>
            COMMENT "Running windeployqt to deploy Qt dependencies..."
        )
    else()
        message(WARNING "windeployqt not found, skipping deployment of Qt dependencies.")
    endif()
endif()