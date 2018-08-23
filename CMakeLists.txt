cmake_minimum_required(VERSION 3.5.2)
project(AffineBigram)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(AffineBigram
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/functions.cpp
        ${PROJECT_SOURCE_DIR}/src/functions2.cpp
        ${PROJECT_SOURCE_DIR}/src/functions3.cpp
        )
