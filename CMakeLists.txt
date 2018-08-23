cmake_minimum_required(VERSION 3.5.2)
project(AffineBigram)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(AffineBigram
        src/main.cpp
        src/functions.cpp
        src/functions2.cpp
        src/functions3.cpp
        )
