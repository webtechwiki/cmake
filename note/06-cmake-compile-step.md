# CMake项目的编译流程

## 1. 概述

> CMake项目的主要目录存在一个 `CMakeLists.txt` 文件

我们有两种当时设置编译规则

- 包含源文件的子文件夹包含 `CMakeLists.txt` 文件，主目录的 `CMakeLists.txt` 通过 `add_subdirectory` 添加子目录即可
- 包含源文件的子文件夹未包含 `CMakeLists.txt` 文件，子目录编译规则体现在主目录的 `CMakeLists.txt` 文件

## 2. 编译流程

在 Linux 平台下使用 CMake 构建 C/C++ 工程的流程如下：

- 编写 `CMakeLists.txt` 规则
- 执行 `cmake $PATH` 生成 `Makefile`(PATH 是CMakeLists.txt 所在的顶层目录)
- 执行 `make` 进行编译

注意一下 `Linux` 以下几个文件目录知识

- `.`或者 `./` 代表当前目录
- `..`或者 `../` 代表上一级目录
- `../..`或者 `../../` 代表上上一级目录

## 3. CMake的两种构建方式

### 3.1. 内部构建 (in-source build) : 不推荐使用

内部构建会产生很多中间文件，这些文件并不是我们最终想要的，和工程源代码文件放在一起会显得杂乱无章。

内部构建示例

```shell
# 在项目源代码根目录下，使用  cmake 指令解析 CMakeLists.txt ，生成 Makefile 和其他文件
cmake .
# 执行 make 命令，生成 target
make
```

### 3.2. 外部构建 (out-of-source build) :   推荐使用

将编译的目录和源代码目录区分开来，放在不同目录中

外部编译示例

```shell
# 1. 在当前目录下，创建 build 文件夹
mkdir build
# 2. 进入build目录
cd build
# 3. 解析上级目录的 CMakeLists.txt ，生成 Makefile 和其他文件
cmake ..
# 4. 执行 make ，生成 target
make
```
