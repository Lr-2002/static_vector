cmake_minimum_required(VERSION 3.15)

project(static_vector)

set(CXX_STANDARD 17)

add_compile_options(-fno-elide-constructors)

add_executable(static_vector static_vector.cpp)
