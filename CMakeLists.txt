cmake_minimum_required(VERSION 3.10)
project(avx-sort LANGUAGES C)



set(CMAKE_C_STANDARD 11)
file(GLOB SOURCES src/*.c)
add_executable(avx-sort ${SOURCES})

target_include_directories(avx-sort PRIVATE include)


target_compile_options(avx-sort PRIVATE -mavx2)