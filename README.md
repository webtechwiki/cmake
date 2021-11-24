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
 

- [1. GCC编译器](./note/01-g++.md)
- [2. g++命令行编译实战](./note/02-compile.md)
- [3. GDB调试器](./note/03-dbg.md)
- [4. 命令行调试实战](./note/04-debug.md)
- [5. cmake语法特性与常用变量](./note/05-cmake.md)


> 本系列文章原创，**禁止转载！**，欢迎关注作者微信订阅号：**极客开发者up**