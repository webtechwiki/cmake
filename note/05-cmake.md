# 跨平台编译工具-CMake的语法特性与常用变量

## 1. 概述

- Cmake (Cross Platform Make) 是一个跨平台的编译工具，可以用简单的语句来描述跨平台的编译过程

- CMake已经成为了大部分C++开源项目的首要编译工具

> 在不同的操作系统上，我们可以使用不同的编译工具，比如 windows 中使用 Visual Studio 的开发套件， mac 中使用 xcode 开发套件，Linux 中使用 Makefile 结合 g++ 编译，那如果我们使用 cmake 就可以解决了跨平台的问题。

## 2. cmake 基础知识

### 2.1. cmake 的基本语法特性

```shell
指令名称(参数1 参数2)
```

参数使用小括号包裹起来，参数之间使用空格或者分号隔开。cmake的指令不区分大小写，但是参数严格区分大小写，如下示例

```cpp
set(HELLO hello.cpp)
add_executable(hello main.cpp hello.cpp)
ADD_EXECUTABLE(hello main.cpp ${HELLO})
```

cmake指令的变量使用 `${变量}` 的形式读取变量，但在 IF 逻辑判断中，直接输入变量名称即可，如上面示例代码中的 `HELLO`

### 2.2. cmake的重要指令和常用变量

- `cmake_minimum_required` : 指定cmake最小版本要求

```shell
# 指定cmake最小版本要求为 2.8.3
cmake_minimum_required(VERSION 2.8.3)
```

- `project` : 定义工程名称，并可以指定工程可支持的语言，语法格式为 `project(项目域名 语言)`，如下示例

```shell
# 指定工程的名称为HELLO
project(HELLO)
```

- `set` : 显示定义变量

```shell
# 定义SRC 变量值为： hello.cpp main.cpp
set(SRC hello.cpp main.cpp)
```

- `include_directories` : 向工程中添加多个头文件搜索路径，相当于指定 `g++` 的 `-I` 参数

```shell
# 将 /usr/include 和 ./include 路径添加到头文件搜索路径中
include_directories(/usr/include ./include)
```

- `link_directories` : 向工程中添加多个库文件搜索路径，相当于 `g++` 的 `-L` 参数

```shell
# 将 /usr/lib 和 ./lib 路径添加到库文件搜索路径中
link_directories(/usr/lib ./lib)
```

- `add_library` : 生成库文件

```shell
# 通过变量SRC生成hello.so 共享库，第二个参数填 SHARED 或 STATIC 或 MOUDLE
add_library(hello SHARED ${SRC})
```

- `add_compile_options` : 添加编译参数

```shell
# 添加编译参数 -Wall -std=c++11 以及 -o2
add_compile_options(-Wall -std=c++11 -o2)
```

- `add_excutable` : 生成可执行文件

```shell
# 编译 main.cpp 生成可执行文件 main
add_excutable(main main.cpp)
```

- `target_link_libraries` : 为目标可执行文件添加需要的共享库

```shell
# 将hello动态库文件链接到可执行文件main
target_link_libraries(main hello)
```

- `add_subdirectory` : 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置

```shell
# 添加src子目录，src中需要有一个 CMakeLists.txt
add_subdirectory(src)
```

- `aux_source_directory` : 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表。

```shell
# 定义 SRC 变量，其值为当前目录下所有的源代码文件
aux_source_directory(. SRC)
# 编译SRC 变量下的源代码文件，生成 mian 可执行文件
add_excutable(main ${SRC)
```

### 2.3. Cmake 常用变量

- `CMAKE_FLAGS` : gcc 编译选项
- `CMAKE_CXX_FLAGS` : g++ 编译选项

```shell
# 在 CMAKE_CXX_FLAGS 编译选项后追加 -std=c++11
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -std=c++11")
```

- `CMAKE_BUILD_TYPE` : 编译类型(Debug，Release)

```shell
# 设定编译类型为 debug ，调试时需要选择 debug 
set(CMAKE_BUILD_TYPE Debug)
# 设定编译类型为release，发布时需要选择 release
set(CMAKE_BUILD_TYPE Release)
```

- `CMAKE_BINARY_DIR`、`PROJECT_BINARY_DIR`、`<projectname>_BINARY_DIR`

1. 这三个变量指代的内容是一致的
2. 如果是 in binary build ，指的就是工程顶级目录
3. 如果是 out-of-binary 编译，指的是工程编译发生的目录
4. PROJECT_BINARY_DIR 跟其他指令稍有区别，但这里可以理解他们是一致的

- `CMAKE_SOURCE_DIR`、`PROJECT_SOURCE_DIR`、`<projectname>_SOURCE_DIR`

1. 这三个变量指代的内容是一致的，不论采用何种编译方式，都是工程经层目录
2. 如果是 in source build ，跟 CMAKE_BINARY_DIR 变量一致
3. PROJECT_SOURCE_DIR 跟其他指令稍有区别，但这里可以理解他们是一致的

- `CMAKE_C_COMPILE` : 指定C编译器

- `CMAKE_CXX_COMPILE` : 指定C++编译器

- `EXECUTABLE_OUT_PATH` : 可执行文件输出的存放路径

- `LIBRARY_OUTOUT_PATH` : 库文件输出的存放路径
