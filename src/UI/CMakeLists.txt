# src/UI/CMakeLists.txt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt6_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/resources/resources.qrc)

set(ui_sources
    MainWindow.cpp
    LeftPane.cpp
    RightPane.cpp
    StatusBar.cpp
    WelcomeDialog.cpp
    ${QT_RESOURCES}
)

set(ui_headers
    MainWindow.h
    LeftPane.h
    RightPane.h
    StatusBar.h
    WelcomeDialog.h
)

add_library(ui_lib ${ui_sources} ${ui_headers})

target_include_directories(ui_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui_lib database_lib network_lib Qt6::Core Qt6::Gui Qt6::Widgets)
