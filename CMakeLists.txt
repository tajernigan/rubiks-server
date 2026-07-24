cmake_minimum_required(VERSION 3.20)

project(HelloWorld)

add_executable(hellocmake main.cpp)

add_executable(server server.cpp)

target_include_directories(server PRIVATE .)