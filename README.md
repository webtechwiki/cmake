# Linux下开发C/C++

> 此文档是在Linuxx下C/C++开发的工具文档

在文档开始之前，我们先安装编译工具与调试工具

```shell
sudo apt install -y build-essential gcc g++ gdb cmake
```

安装验证，分别执行以下每一行命令，如果成功显示版本号，则代表安装成功

```shell
gcc --version
g++ --version
gdb --version
cmake --version
```

如果你想继续阅读此系列文档，并希望有所收获，现在你应当具备以下技能

- C++编程语言基础
- Linux系统基本操作能力

以下是文档目录

- [1. Linux中编译C++代码的g++工具，以及g++的常用操作指令](./note/01-g++.md)
- [2. Linux下C++命令行编译示例](./note/02-compile.md)
- [3. GDB调试器](./note/03-dbg.md)
- [4. Linux下C++命令行调试实战](./note/04-debug.md)
- [5. 跨平台编译工具-CMake的语法特性与常用变量](./note/05-cmake.md)
- [6. CMake项目的编译流程](./note/06-cmake-compile-step.md)
- [7. CMake项目编译实战](./note/07-cmake-compile.md)
- [8. 怎样在VSCode中调试C++程序](./note/08-vscode-debug.md)

> 本系列文章为自己的亲手笔记，**禁止转载！**，欢迎关注作者微信订阅号：**极客开发者**

感谢B站up主 xiaobing1016 的学习视频：[https://www.bilibili.com/video/BV1fy4y1b7TC](https://www.bilibili.com/video/BV1fy4y1b7TC)
