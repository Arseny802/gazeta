cmake_minimum_required(VERSION 3.30)
project(gazeta.storage.tests VERSION 0.0.1 LANGUAGES CXX)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} 
    src/reader.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../src/
    ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    gazeta.storage
    hare
    GTest::gtest_main
    GTest::gtest
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src/pch.h)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_tests_properties(${PROJECT_NAME} PROPERTIES TIMEOUT 10)