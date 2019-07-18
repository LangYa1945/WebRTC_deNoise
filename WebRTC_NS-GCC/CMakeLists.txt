cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99")
project(ns)

add_executable(ns main.c ns_process.c)

target_link_libraries(ns -lm)


