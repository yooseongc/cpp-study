cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_GENERATOR "MinGW Makefiles")
add_definitions("-Wall -std=c++20")

project(Fluxer VERSION 1.0.0 LANGUAGES CXX)

# mesher didn't work as lib name for Vs
add_library(mesherlib SHARED mesher.cpp)
add_library(solver solver.cpp)

add_executable(fluxer fluxer.cpp)
target_link_libraries(fluxer solver mesherlib)
