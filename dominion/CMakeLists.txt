cmake_minimum_required(VERSION 3.5)
project(dominion)

set(CMAKE_C_COMPILER /usr/local/bin/gcc-5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES playdom.c dominion.c interface.c rngs.c)
add_executable(playdom ${SOURCE_FILES})
