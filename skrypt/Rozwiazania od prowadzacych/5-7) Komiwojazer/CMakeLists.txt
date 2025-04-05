cmake_minimum_required(VERSION 3.13)
project(tsp)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include
)

set(SOURCE_FILES
        src/tsp.cpp
        )

add_executable(tsp_debug ${SOURCE_FILES} main.cpp)
