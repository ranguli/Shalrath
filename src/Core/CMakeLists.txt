# Enable automatic MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find necessary Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# List of source and header files
set(core_sources
    Shalrath.cpp
    CommandLineOptions.cpp
)

set(core_headers
    Shalrath.h
    CommandLineOptions.h
)

# Create the core library
add_library(core_lib ${core_sources} ${core_headers})

# Include the current directory and any necessary directories
target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link against the necessary Qt libraries
target_link_libraries(core_lib ui_lib parser_lib database_lib Qt6::Core Qt6::Widgets)
