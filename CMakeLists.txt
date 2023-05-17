cmake_minimum_required(VERSION 3.5)

project(curr3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS AxContainer REQUIRED)
find_package(Qt6 COMPONENTS Concurrent REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        fullinfo.cpp
        fullinfo.h
        fullinfo.ui
        OS_CHECK.h
        viewfile.h
        viewfile.cpp
        viewfile.ui
        readword.h
        readword.cpp
        myaxwidget.h
        myaxwidget.cpp
        zipmanage.h
        zipmanage.cpp
)

qt6_add_resources(RESOURCES icons.qrc)
qt6_add_resources(RESOURCES db_rc.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(curr3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET curr3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation


else()
    if(ANDROID)
        add_library(curr3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(curr3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_sources(curr3 PRIVATE acc2.rc)


target_link_libraries(curr3 PRIVATE Qt6::Sql)
target_link_libraries(curr3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(curr3 PRIVATE Qt${QT_VERSION_MAJOR}::AxContainer)
target_link_libraries(curr3 PRIVATE Qt6::Gui)
target_link_libraries(curr3 PRIVATE Qt6::Core5Compat)

target_include_directories(curr3 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(curr3 PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(curr3 PRIVATE minizip.lib aes.lib zlibstatic.lib)



set_target_properties(curr3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS curr3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(curr3)
endif()

if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries(curr3, ${SQLite3_LIBRARIES})
endif(SQLite3_FOUND)



