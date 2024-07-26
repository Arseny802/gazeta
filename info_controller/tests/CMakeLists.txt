cmake_minimum_required(VERSION 3.24)
project(gazeta.info_controller.tests)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} 
    src/article.cpp
    src/reader.cpp
    src/telegram_web.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    gazeta.info_controller
    hare
    GTest::gtest_main
    GTest::gtest
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_tests_properties(${PROJECT_NAME} PROPERTIES TIMEOUT 10)



set(passRegex "^Test passed" "^All ok")
set(failRegex "Error" "Fail")
#set_property(TEST ${PROJECT_NAME} PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
#set_property(TEST ${PROJECT_NAME} PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")
