cmake_minimum_required(VERSION 3.5.2)
project(AffineBigram)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AffineBigram_SOURCE_DIR}/build)

add_executable(AffineBigram
        src/main.cpp
        src/functions.cpp
        src/functions2.cpp
        src/functions3.cpp
        )
