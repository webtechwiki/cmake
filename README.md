# cmake的使用
> 10.12: P7 编译过程 4:49
>

## 一、安装编译环境

编译工具与调试工具

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

## 二、基础

### 1. GCC编译器

- GCC编译器支持编译 Go、Object-C、Object-C ++、Fortran、Ada、BRIG（HSAIL）等程序；
- Linux开发 C/C++一定要熟悉GCC；
- VSCode是通过调用GCC编译器来实现C/C++的编译工作的。

实际使用中
- 使用GCC编译C代码；
- 使用G++编译C++代码。


**(1)编译过程**

第一步：预处理 Pre-processing，生成.i 文件
```shell
# -E 选项指示编译器仅对输入文件进行预编译
g++ -E test.cpp -o testr.i
```

第二步：编译-Compiling，生成.s 文件
```shell
# -S 编译选项告诉 g++ 在为 c++ 代码产生了汇编语言文件后停止编译
# g++ 产生的汇编语言文件的缺省扩展名是 .s
g++ -S test.i -o test.s
```

第三步：汇编-Assembing，生成.o 文件
```shell
# -c 选项告诉 g++ 仅把源代码编译为机器语言的目标代码
# 缺省时 g++ 建立的目标代码文件有一个 .o 的扩展名
g++ -c test.s -o test.o
```

第四步：链接-Lingking，生成bin二进制文件
```shell
# -o 编译选项来为将产生的可执行文件指定文件名
g++ test.o -o test
```