cmake_minimum_required(VERSION 3.24)
project(gazeta.common.tests)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} 
    src/pch.cpp
    src/article.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../src/
    ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    gazeta.common
    GTest::gtest_main
    GTest::gtest
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/common/pch.h)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_tests_properties(${PROJECT_NAME} PROPERTIES TIMEOUT 10)



set(passRegex "^Test passed" "^All ok")
set(failRegex "Error" "Fail")
set_property(TEST ${PROJECT_NAME} PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
set_property(TEST ${PROJECT_NAME} PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")
