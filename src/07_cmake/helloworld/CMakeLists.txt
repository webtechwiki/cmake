# 指定cmake最低版本
cmake_minimum_required(VERSION 3.0)
# 指定项目名称为 HELLOWORLD
project(HELLOWORLD)
# 编译源代码文件 helloword.cpp，生成可执行文件 helloworld_cmake.out
add_executable(helloworld_cmake.out helloworld.cpp)
