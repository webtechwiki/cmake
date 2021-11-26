# CMake编译工程

> 完成P18 3：30

## 1. 概述

> CMake项目 主要目录存在一个 `CMakeLists.txt` 文件

我们有两种当时设置编译规则

- 包含源文件的子文件夹包含 `CMakeLists.txt` 文件，主目录的 `CMakeLists.txt` 通过 `addZ_subdirectory` 添加子目录即可
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
