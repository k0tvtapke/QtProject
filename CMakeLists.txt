cmake_minimum_required(VERSION 3.5)

project(QtProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h"
        "forms/*.ui"
        # "resources/*.qrc"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(QtProject PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(QtProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(QtProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtProject)
endif()

#cmake_minimum_required(VERSION 3.19)
#project(QtProject LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

#find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

#qt_standard_project_setup()

#set(CMAKE_AUTOUIC_SEARCH_PATHS
#        ${CMAKE_CURRENT_SOURCE_DIR}/forms
#)

#file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
#        "src/*.cpp"
#        "include/*.h"
#        "forms/*.ui"
#        # "resources/*.qrc"
#)

#qt_add_executable(QtProject
#        WIN32 MACOSX_BUNDLE
#        ${PROJECT_SOURCES}
#)

#target_link_options(QtProject PRIVATE -static-libgcc -static-libstdc++)

#target_include_directories(QtProject PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)

#target_link_libraries(QtProject
#        PRIVATE
#        Qt::Core
#        Qt::Widgets
#)

#install(TARGETS QtProject
#        BUNDLE DESTINATION .
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

#qt_generate_deploy_app_script(
#        TARGET QtProject
#        OUTPUT_SCRIPT deploy_script
#        NO_UNSUPPORTED_PLATFORM_ERROR
#)
#install(SCRIPT ${deploy_script})
