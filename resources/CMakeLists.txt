# resources/CMakeLists.txt
qt6_add_resources(QT_RESOURCES resources.qrc)

add_library(resources STATIC ${QT_RESOURCES})

install(FILES assets/hello.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/images)
