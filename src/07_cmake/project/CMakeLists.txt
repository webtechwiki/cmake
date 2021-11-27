# 指定最低cmake版本
cmake_minimum_required(VERSION 3.0)
# 指定项目名称为 SWAP 
project(SWAP)
# 引入头文件目录
include_directories(include)
# 生成可执行文件
add_executable(main_cmake.out main.cpp src/swap.cpp)
