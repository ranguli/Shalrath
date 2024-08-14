# src/UI/CMakeLists.txt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

qt6_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/resources/resources.qrc)

set(db_sources
    MapDao.cpp
    DatabaseManager.cpp
    
    ${QT_RESOURCES}
)

set(db_headers
    MapDao.h
    DatabaseManager.h
)

add_library(database_lib ${db_sources} ${db_headers})

target_include_directories(database_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(database_lib model_lib Qt6::Core Qt6::Sql)
