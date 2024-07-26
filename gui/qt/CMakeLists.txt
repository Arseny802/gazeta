cmake_minimum_required(VERSION 3.24)
project(gazeta.gui.qt)

if ("${BUILD_ARCHITECTURE}" STREQUAL "x86")
    message(WARNING "x86 is not supported for ${PROJECT_NAME}!")
    return()
endif("${BUILD_ARCHITECTURE}" STREQUAL "x86")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)

qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME} 
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    )

if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
    target_compile_options(${PROJECT_NAME} PUBLIC "/permissive-")
endif ()
