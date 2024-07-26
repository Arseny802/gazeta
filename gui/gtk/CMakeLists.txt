cmake_minimum_required(VERSION 3.23)
project(gazeta.gui.gtk VERSION 0.0.1)
set(VENDOR "Arseny802")

if (MSVC)
    message(WARNING "x86 is not supported for ${PROJECT_NAME}!")
    return()
endif(MSVC)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME}
    src/helloworld.cc
    src/helloworld.h
    src/main.cc)

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
