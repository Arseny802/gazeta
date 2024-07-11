cmake_minimum_required(VERSION 3.30)
project(gazeta VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")

set(CMAKE_CXX_STANDARD 20)

find_package(Boost CONFIG REQUIRED)
find_package(libxml2 CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(ZLIB CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

add_subdirectory(dependencies/hare)

add_executable(gazeta
    src/hare_gazeta.cpp
    src/main.cpp
    src/pch.cpp)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

target_link_libraries(${PROJECT_NAME} PRIVATE
    hare
    boost::boost
    LibXml2::LibXml2
    pugixml::pugixml
    fmt::fmt
    openssl::openssl
    OpenSSL::Crypto
    ZLIB::ZLIB
    CURL::libcurl)

if (WIN32) # building on windows
    ADD_DEFINITIONS("/EHsc")
elseif (MSVC) # building on visual c++
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    ADD_DEFINITIONS("/EHsc")
elseif (UNIX) # building on unix (mac, linux)
endif (WIN32)

#add_subdirectory(tests)
