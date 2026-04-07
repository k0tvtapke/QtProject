cmake_minimum_required(VERSION 3.19)
project(QtProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h"
        "forms/*.ui"
        # "resources/*.qrc"
)

qt_add_executable(QtProject
        WIN32 MACOSX_BUNDLE
        ${PROJECT_SOURCES}
)

target_include_directories(QtProject PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(QtProject
        PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS QtProject
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
        TARGET QtProject
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
