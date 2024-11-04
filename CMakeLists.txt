cmake_minimum_required(VERSION 3.13)
project(GeneticTSP)

set(CMAKE_CXX_COMPILER "c++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES src/path.cpp src/main.cpp src/simulation.cpp)
add_executable(GeneticTSP ${SOURCE_FILES})
