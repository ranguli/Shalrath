# src/Network/CMakeLists.txt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui)

set(network_sources
    DownloadManager.cpp
)

set(network_headers
    DownloadManager.h
)

qt6_wrap_cpp(MOC_SOURCES ${network_headers})

add_library(network_lib ${network_sources} ${MOC_SOURCES})

target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(network_lib Qt6::Core Qt6::Network Qt6::Gui)
