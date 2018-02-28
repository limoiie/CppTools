cmake_minimum_required(VERSION 3.7)
project(CppTools)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
