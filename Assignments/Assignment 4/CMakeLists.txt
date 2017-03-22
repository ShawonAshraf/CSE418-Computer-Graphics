cmake_minimum_required(VERSION 3.6)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS})

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL")
else()
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lGLU -lglut")
endif()


set(SOURCE_FILES main.cpp)
#set(SOURCE_FILES test.cpp)
add_executable(Assignment_4 ${SOURCE_FILES})