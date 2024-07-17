cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
project(OnixEngine VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/lib/*.*)
add_library(OnixEngine STATIC ${SRC_FILES})

target_include_directories(OnixEngine PUBLIC ./include)
target_link_directories(OnixEngine PUBLIC ./lib)
target_link_libraries(OnixEngine glfw3 opengl32)

project(SampleGL VERSION 1.0)

add_executable(SampleGL "src/main_gl.cpp")
target_include_directories(SampleGL PUBLIC ./include)
target_link_directories(SampleGL PUBLIC ./)
target_link_libraries(SampleGL PUBLIC OnixEngine opengl32)