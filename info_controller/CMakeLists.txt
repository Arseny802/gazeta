cmake_minimum_required(VERSION 3.30)
project(gazeta.info_controller VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(libxml2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(ZLIB CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

add_library(${PROJECT_NAME} STATIC
    src/controllers/base_controller.cpp
    src/controllers/controller_ria.cpp
    src/controllers/fabric.cpp
    src/info_sources/reader.cpp
    src/info_sources/telegram_web.cpp
    src/info_controller.cpp
    src/hare_gazeta_ic.cpp
    src/pch.h
    src/pch.cpp)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

target_link_libraries(${PROJECT_NAME} PUBLIC
    gazeta.common
    gazeta.storage
    LibXml2::LibXml2
    fmt::fmt
    openssl::openssl
    OpenSSL::Crypto
    ZLIB::ZLIB
    CURL::libcurl)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_CXX_STANDARD 20)
    
add_subdirectory(example)
add_subdirectory(tests)
