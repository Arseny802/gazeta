cmake_minimum_required(VERSION 3.30)
project(gazeta.storage.example VERSION 0.0.1 LANGUAGES CXX)
set(VENDOR "Arseny802")


add_executable(${PROJECT_NAME}
    src/hare_storage_example.cpp
    src/main.cpp
    src/pch.h
    src/pch.cpp)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

target_link_libraries(${PROJECT_NAME} PRIVATE gazeta.storage)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CMAKE_CXX_STANDARD 20)
  