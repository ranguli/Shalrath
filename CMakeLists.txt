cmake_minimum_required(VERSION 3.14)
project(Shalrath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings and options
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -fstack-protector
)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Add subdirectories
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(tests)
