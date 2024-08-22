cmake_minimum_required(VERSION 3.30)
project(gazeta.common VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
  src/article.cpp
  src/pch.cpp)

target_precompile_headers(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common/pch.h)

target_link_libraries(${PROJECT_NAME} PUBLIC
  hare)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)
