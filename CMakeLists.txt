cmake_minimum_required(VERSION 3.29.3)

project(OnixEngine VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.*)
add_executable(OnixEngine ${SRC_FILES})

target_include_directories(OnixEngine PUBLIC ./include)
target_link_directories(OnixEngine PUBLIC ./lib)
target_link_libraries(OnixEngine glfw3 opengl32)