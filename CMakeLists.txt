cmake_minimum_required(VERSION 3.14)
project(Shalrath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the runtime library for your project
if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()


# Set compiler-specific flags
if (MSVC)
    # MSVC specific flags
    add_compile_options(/W4 /WX)
else()
    # GCC/Clang specific flags
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wmisleading-indentation
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -fstack-protector
    )
endif()

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Add subdirectories
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(tests)

# List of source files for clang-format and clang-tidy
file(GLOB_RECURSE ALL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/tests/*.cpp"
    "${PROJECT_SOURCE_DIR}/tests/*.h"
    "${PROJECT_SOURCE_DIR}/resources/*.cpp"
    "${PROJECT_SOURCE_DIR}/resources/*.h"
)


if (MSVC)
    # Clang-format
    find_program(CLANG_FORMAT "clang-format"
        HINTS "C:/Program Files/LLVM/bin/"
    )
else() 
    find_program(CLANG_FORMAT "clang-format")
endif()

if(CLANG_FORMAT)
    add_custom_target(clang_format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format on source files..."
    )
else()
    message(WARNING "clang-format not found!")
endif()


if (MSVC)
    # Clang-tidy
    find_program(CLANG_TIDY "clang-tidy"
        HINTS "C:/Program Files/LLVM/bin/"
    )
else()
    find_program(CLANG_TIDY "clang-tidy")
endif()

if(CLANG_TIDY)
    add_custom_target(clang_tidy
        COMMAND ${CLANG_TIDY} -p ${CMAKE_BINARY_DIR} ${ALL_SOURCE_FILES}
        COMMENT "Running clang-tidy on source files..."
    )
else()
    message(WARNING "clang-tidy not found!")
endif()

# Ensure clang-format runs before any build steps
add_dependencies(shalrath clang_format)
add_dependencies(core_lib clang_format)
add_dependencies(ui_lib clang_format)
add_dependencies(network_lib clang_format)
add_dependencies(database_lib clang_format)
add_dependencies(model_lib clang_format)
add_dependencies(parser_lib clang_format)
add_dependencies(run_tests clang_format)