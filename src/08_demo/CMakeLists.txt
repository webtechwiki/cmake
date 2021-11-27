# 指定cmake版本
cmake_minimum_required(VERSION 3.0)
# 设置项目名称
project(SOLIDERFIRE)
# 添加编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")
# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
# 编译
add_executable(my_cmake.out main.cpp src/Gun.cpp src/Solider.cpp)