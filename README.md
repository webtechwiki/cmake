# Linux下开发C/C++

> 此文档是在Linuxx下C/C++开发的cmake编译工具文档

在文档开始之前，我们先安装编译工具与调试工具

```shell
sudo apt install -y build-essential gcc g++ gdb cmake
```

安装验证，如果成功显示版本号，则代表安装成功

```shell
gcc --version
g++ --version
gdb --version
cmake --version
```


以下是文档目录
 

- [1. GCC编译器](./note/01-gcc.md)
- [2. g++命令行编译实战](./note/02-compile.md)
- [3. GDB调试器](./note/03-dbg.md)
- [4. 命令行调试实战](./note/04-debug.md)