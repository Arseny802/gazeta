cmake_minimum_required(VERSION 3.23)
project(gazeta.gui.gtk VERSION 0.0.1)
set(VENDOR "Arseny802")

if (MSVC)
    message(WARNING "MSVC is not supported for ${PROJECT_NAME}!")
    return()
endif(MSVC)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

add_executable(${PROJECT_NAME}
    src/infobook/infobook_object.cpp
    src/infobook/infobook_page_object.cpp
    src/main_window.cpp
    src/hare_gtk.cpp
    src/main.cpp
    src/pch.cpp)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${GTKMM_INCLUDE_DIRS} 
    src)    

target_link_libraries(${PROJECT_NAME} PRIVATE
    gazeta.info_controller
    hare
    ${GTKMM_LIBRARIES})
