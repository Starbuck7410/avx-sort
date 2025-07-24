cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
project(avx-sort LANGUAGES C)
file(GLOB SOURCES src/*.c)

add_executable(avx-sort ${SOURCES})
target_include_directories(avx-sort PRIVATE include)