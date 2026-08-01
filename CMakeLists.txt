cmake_minimum_required(VERSION 3.20)

project(HelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# You only need basic HTTP, so disable optional compression and HTTPS features.
set(HTTPLIB_INSTALL OFF CACHE BOOL "" FORCE)
set(HTTPLIB_TEST OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_OPENSSL_IF_AVAILABLE OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZLIB_IF_AVAILABLE OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_BROTLI_IF_AVAILABLE OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZSTD_IF_AVAILABLE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.50.1
)

FetchContent_MakeAvailable(httplib)

add_library(cube
    src/Cube.cpp
)

target_include_directories(cube
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(server src/server.cpp)

target_link_libraries(
    server
    PRIVATE
        httplib::httplib
)

add_executable(cube_test
    tests/cube_test.cpp
    src/Cube.cpp
)

enable_testing()

find_package(GTest REQUIRED)

target_link_libraries(
    cube_test
    PRIVATE
        cube
        GTest::gtest_main

)

include(GoogleTest)

gtest_discover_tests(cube_test)