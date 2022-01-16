cmake_minimum_required(VERSION 3.15)

project(static_vector)

set(CXX_STANDARD 17)
find_package(glog 0.6.0 REQUIRED)


add_compile_options(-fno-elide-constructors)

add_executable(static_vector static_vector.cpp)
target_link_libraries (static_vector glog::glog)