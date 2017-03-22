cmake_minimum_required(VERSION 3.6)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lGLU -lglut")

set(SOURCE_FILES main.cpp)
add_executable(Assignment_4 ${SOURCE_FILES})