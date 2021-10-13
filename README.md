# cmake的使用
> 10.12: 完成 P7 编译过程
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


### 2. G++重要编译参数

（1）编译带调试信息的可执行文件
```shell
# -g 选项告诉GCC产生能被 GNU 调试器DGB试用的调试信息，以调试程序

# 产生带调试信息的可执行文件terst
g++ -g test.cpp -o test
```

（2）优化源代码
所谓优化，例如省略代码中从来未试用过的变量、直接常亮表达式用结果替代等，这些操作会缩减目标文件所含的代码，提高最终生成的执行文件的运行效率。

-O 告诉 g++ 对源代码进行基本优化。这些优化在大多数情况下都使程序执行得更快。-O2 告诉 g++ 产生尽可能小和尽可能快的代码。如 -O2，-O3，-On（n通常为3）

-O 同时减少代码的长度和执行时间，其效果等价于 -O1
-O0 表示不做优化
-O1 表示默认优化
-O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等
-O3 则包括循环展开和其他一些与处理性相关的优化工作，选项将使编译的速度比 -O 慢，但通常产生的代码执行速度会更快。

```shell
# 使用 -O2 优化源代码，并输出可执行文件。
g++ -O2 test.cpp
```

（3）代码优化示例
