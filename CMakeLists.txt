cmake_minimum_required(VERSION 3.13)
project(GeneticTSP)

set(CMAKE_CXX_COMPILER "c++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-g3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES src/path.cpp src/graph.cpp src/simulation.cpp src/parse.cpp src/selector.cpp src/terminator.cpp src/main.cpp)
add_executable(GeneticTSP ${SOURCE_FILES})
