# cmake语法特性与常用变量

> 进度：p17 3:30

## 1. 概述

- Cmake 是一个跨平台的编译工具，可以用简单的语句来描述跨平台的编译过程

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

- `link_directories` : 向工程中添加多个库文件搜索路径，相当与 `g++` 的 `-L` 参数

```shell
# 将 /usr/lib 和 ./lib 路径添加到库文件搜索路径中
link_directories(/usr/lib ./lib)
```

- `add_library` : 生成库文件

```shell
# 通过变量SRC生成hello.so 共享库
add_library(hello SHARED ${SRC})
```








