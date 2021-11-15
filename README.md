# cmake 的使用

> 11.12: 完成 P10 开始 P11

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

### 1. GCC 编译器

- GCC 编译器支持编译 Go、Object-C、Object-C ++、Fortran、Ada、BRIG（HSAIL）等程序；
- Linux 开发 C/C++一定要熟悉 GCC；
- VSCode 是通过调用 GCC 编译器来实现 C/C++的编译工作的。

实际使用中

- 使用 GCC 编译 C 代码；
- 使用 G++编译 C++代码。

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

第四步：链接-Lingking，生成 bin 二进制文件

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

-O 告诉 g++ 对源代码进行基本优化。这些优化在大多数情况下都使程序执行得更快。-O2 告诉 g++ 产生尽可能小和尽可能快的代码。如 -O2，-O3，-On（n 通常为 3）

-O 同时减少代码的长度和执行时间，其效果等价于 -O1
-O0 表示不做优化
-O1 表示默认优化
-O2 除了完成-O1 的优化之外，还进行一些额外的调整工作，如指令调整等
-O3 则包括循环展开和其他一些与处理性相关的优化工作，选项将使编译的速度比 -O 慢，但通常产生的代码执行速度会更快。

```shell
# 使用 -O2 优化源代码，并输出可执行文件。
g++ -O2 test.cpp
```

**示例**
创建一个效率低下的代码块`inefficency.cpp`，添加以下内容

```cpp
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	unsigned long int counter;
	unsigned long int result;
	unsigned long int temp;
	unsigned long int five;

	for (counter = 0; counter < 2009 * 2009 * 100 / 4 + 2010 ; counter += (10-6)/4)
	{
		temp = counter/1979;
		for (int i = 0; i < 20; i++)
		{
			// 每次循环都会进行一次无用的 复杂的运算
			five = 200 * 200 / 8000;
			result = counter;
		}
	}

	cout << "result = " << result << endl;

	return 0;
}
```

先使用直接编译的方式生成`a_without_o`可执行文件，如下命令

```shell
g++ inefficency.cpp -o a_without_o
```

接下来我们再室友优化后的编译方式，如下命令

```shell
g++ inefficency.cpp -O2 -o a_with_o2
```

后执行两种方式编译生成的可执行文件，如下结果

```shell
pan@pan-PC:~/Work/src/cmake/src$ ./a_without_o
result = 100904034
pan@pan-PC:~/Work/src/cmake/src$ ./a_with_o2
result = 100904034
pan@pan-PC:~/Work/src/cmake/src$
```

可以看到计算的结果是一样的，但是没有编译优化的 `a_without_o` 执行时间明显大于 `a_with_o2`。我们可以使用再次使用 `time` 命令计算执行程序所需的时间，可以看到明显的时间区别，如下结果

```shell
pan@pan-PC:~/Work/src/cmake/src$ time ./a_without_o
result = 100904034

real    0m4.212s
user    0m4.212s
sys     0m0.000s
pan@pan-PC:~/Work/src/cmake/src$ time ./a_with_o2
result = 100904034

real    0m0.001s
user    0m0.001s
sys     0m0.000s
pan@pan-PC:~/Work/src/cmake/src$
```

> 总结：加上 -O 优化参数后，我们一般使用 -O2 ，编译器会帮我们优化低效率的代码。从而提高最终程序的执行效率。

（3）`-l` 或者 `-L` 指定库文件 | 指定库文件路径
-l 参数（小写）就是用来指定程序要链接的库，-l 参数紧接着就是库名，在`/lib`和`/usr/lib`和`/usr/local/lib`里的库直接调用 -l 参数就能链接

```shell
# 链接 glog库
g++ -lglog test.cpp
```

如果库文件没有放在上面的三个目录里，需要试用-L 参数（大写）指定库文件所在目录，-L 参数跟着的是库文件所在的目录名

```shell
# 链接 mytest库。libmytest.so 在 ~/lib目录下
g++ -L~/lib -lmytest test.cpp
```

（4）-I 指定头文件搜索目录
`/usr/include` 目录一般不用指定，gcc 知道去那里找，但是如果头文件不在`/usr/include`里我们就要用 `-I` 参数指定了，比如头文件放在 `/myinclude`目录里，那编译命令行就要加上 `-I/myinclude`参数了，如果不加你会得到一个`xxx.h: No such file or directory`的错误。-I 参数可以试用相对路径，比如头文件在当前目录，可以用 -I 来指定。上面我们提到的-cflags 参数就是用来生成-I 参数的。

```shell
g++ -I/myinclde test.cpp
```

（5）-Wall 打印警告信息

```shell
打印出gcc提供的警告信息
g++ -Wall test.cpp
```

（6）-w 关闭警告信息

```shell
# 关闭所有警告信息
g++ -w test.cpp
```

（7）-std=c++11 设置编译标准

```shell
# 使用 c++11 标准编译 test.cpp
g++ -std=c++11 test.cpp
```

（8）-o（小写） 指定输出文件名

```shell
# 指定即将产生的文件名未test
g++ test.cpp -o test
```

（9）-D 定义宏
在使用 gcc/g++编译的时候定义宏，常用场景：
-DDEBUG 定义 DEBUG 宏，可能文件中有 DEBUG 宏部分的相关信息，用 DEBUG 来选择开启或者关闭 DEBUG

添加源码文件`test2.cpp`，示例代码

```cpp
#include <stdio.h>

int main()
{
	#ifdef DEBUG
	  printf("DEBUG LOG\n");
	#endif
	  printf("in\n");
	return 0;
}
```

在编译的时候，使用 `g++ -DDEBUG test2.cpp` 后执行可执行文件，可以看到 "DEBUG LOG" 被输出

## 三、g++实战命令行编译

在一个工作目录中创建添加代码，文件结构如下

```shell
pan@pan-PC:~/Work/md/cmake/src/gcc_demo_swap$ tree .
.
├── include
│   └── swap.h
├── main.cpp
└── src
    └── swap.cpp
```

代码内容如下：

swap.h

```cpp
#include <iostream>
using namespace std;
```

swap.cpp

```cpp
#include "swap.h"

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
```

main.cpp

```cpp
#include <iostream>
#include "swap.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int val1 = 10;
    int val2 = 20;

    cout << " Before swap:" << endl;
    cout << " val1:" << val1 << endl;
    cout << " val2:" << val2 << endl;

    swap(val1, val2);

    cout << " After swap:" << endl;
    cout << " val1:" << val1 << endl;
    cout << " val2:" << val2 << endl;

    return 0;
}
```

### 1.引入目录进行编译

直接编译

```shell
g++ main.cpp src/swap.cpp
```

此时会看到如下错误

```shell
pan@pan-PC:~/Work/md/cmake/src/gcc_demo_swap$ g++ main.cpp src/swap.cpp
main.cpp:2:10: fatal error: swap.h: 没有那个文件或目录
 #include "swap.h"
          ^~~~~~~~
compilation terminated.
src/swap.cpp:1:10: fatal error: swap.h: 没有那个文件或目录
 #include "swap.h"
          ^~~~~~~~
compilation terminated.
```

这是因为 g++ 找不到`include`目录下的`swap.h` 文件，所以我们需要将`-I`参数将`include`包含进来，如下命令

```shell
g++ main.cpp src/swap.cpp -Iinclude
```

这时候代码就可以顺便通过编译了。

### 2. 使用-Wall、-std 参数进行编译

`-Wall` 代表程序编译过程中输出警告信息，`-std`代表使用的 c++标准，如下命令

```
# 使用c++11标准进行编译，并且使用-Wall参数
g++ main.cpp src/swap.cpp -Iinclude -Wall -std=c++11 -o b.out
```

此时我们看到，还是能正常编译，也没有输出警告，我们也可以正常执行`b.out`。因为我们的代码是符合`c++11`标准的，为了演示一个警告，我们在`main.cpp`中加一行代码。如下

```cpp
#include <iostream>
#include "swap.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int val1 = 10;
    int val2 = 20;
	// 定义一个变量，但是不使用
	double d = 0.0;

    cout << " Before swap:" << endl;
    cout << " val1:" << val1 << endl;
    cout << " val2:" << val2 << endl;

    swap(val1, val2);

    cout << " After swap:" << endl;
    cout << " val1:" << val1 << endl;
    cout << " val2:" << val2 << endl;

    return 0;
}
```

把输出文件改为`c.aot`，再次执行编译，如下命令

```
g++ main.cpp src/swap.cpp -Iinclude -Wall -std=c++11 -o b.out
```

此时出现如下警告

```shell
pan@pan-PC:~/Work/md/cmake/src/gcc_demo_swap$ g++ main.cpp src/swap.cpp -Iinclude -Wall -std=c++11
main.cpp: In function ‘int main(int, const char**)’:
main.cpp:9:12: warning: unused variable ‘d’ [-Wunused-variable]
     double d = 0.0;
            ^
pan@pan-PC:~/Work/md/cmake/src/gcc_demo_swap$
```

因为定义一个变量不使用，是不符合`c++11`的标准的，但不是错误，`c.out`也能正常执行。

### 3. 生成库文件

我们先删除调在 2 中会进行警告的代码

**链接静态库生成可执行文件**

```shell
# 先进入src目录
cd  src
# 汇编生成swap.o 文件
g++ swap.cpp -c -I../include
# 生成静态库libSwap.o
ar rs libswap.a swap.o
# 回到代码根目录，调用静态链接库生成可执行文件
g++ main.cpp -lswap -Lsrc -Iinclude -o static_main
```

**链接动态库生成可执行文件**

```shell
# 进入src目录
cd  src
# 生成动态链库文件libswap.so
g++ swap.cpp -I../include -fPIC -shared -o libswap.so
# 上面的指令等价于下面两条指令
# gcc swap -I../include -c -fPIC
# gcc -shared -o libswap.so swap.o

# 回到上级目录
cd ..
# 链接生成可执行文件 dyna_main
g++ main.cpp -Iinclude -lswap -Lsrc -o dyna_main
```

静态库和动态库生成可执行文件的区别

- 静态库在打包生成二进制文件的时候，直接将静态库包含进来
- 动态库则在打包时不打包库文件，而在运行时再把动态库文件引进来

所以我们运行的时候，静态库文件打包的可执行文件可以直接运行，而动态库运行会报错，是因为动态链接文件在我们的代码目录，并不在系统的库搜索目录，如果要运行动态链接库打包生成的可执行文件，我们需要手动指定程勋运行的库目录。

运行可执行文件命令如下：

运行静态打包的可执行文件

```shell
./static_main
```

运行动态链接库打包生成的可执行文件

```shell
LD_LIBRARY_PATH=src ./dyna_main
```


## 四、GDB调试器

* GDB(GNU Debugger) 是一个用来调试**C/C++**程序的抢到功能的调试器，是Linux系统开发C/C++最常用的调试器

* 程序员可以使用GDB来跟踪程序中的错误，从而减少程序员的工作量

* Linux开发C/C++一定要熟悉GDB

* VScode是通过调用GDB调试器来实现工作的

> Windows中，常用的集成开发环境，如VS，VC等已经内嵌了相应的调试器

GDB的主要功能：
* 设置断点（断点可以是条件表达式）
* 使程序在指定的代码上暂停执行，便于观察
* 单步执行程序，便于调试
* 查看程序中变量值的变化
* 动态改变程序的执行环境
* 分析崩溃程序产生的core文件

### 1. 常用调试命令参数

调试开始：执行`gdb [exefilename]`，进入gdb调试程序，其中`exfilename`为要调试的执行文件名，以下命令后括号内为命令的简化使用，比如run(r)，直接输入命令 r 就代表命令 run
```shell
help(h) #查看命令帮助，具体命令查询在gdb 中输入help + 命令
run(r) #重新开始运行文件（run-text:加载文本文件，run-bin:加载二进制文件）
start(s) #单步执行，运行程序，停在第一行执行语句
list(l) #查看源代码（list-n从第n行开始查看代码。list+函数名：查看具体函数）
set #设置变量的值
next(n) #单步调试（逐过程，函数直接执行）
step(s) #单步调试（逐语句，跳入自定义函数内部执行）
backtrace(bt) #查看函数的调用栈帧和层级关系
frame(f) #切换函数的栈帧
info(i) #查看函数内部局部变量的数值
finish #结束当前函数，返回到函数调用点
continue(c) #继续执行
print(p) #打印值及地址
quit(q) #退出gdb
break + num(b) #在某行达断点
info + breakpoints #查看当前设置的所有断点
delete + breakpoints num(d) #删除第num个断点
display #跟踪查看具体的变量值
undisplay #取消跟踪观察变量
watch #被设置观察点的变量发生修改时，打印显示
i watch #显示观察点
enable breakpoints #启用断点
disable breakpoints #禁用断点
x #查看内存x/20xw 显示20个单元，16进制，4个字节没单元
run argv[1] argv[2] #调试命令传参
set follow-fork-mode child #Makefile项目管理，选择跟踪父子进程（fork）
```

> 1. 编译程序时需要加上 `-g` ，之后才能用 `gdb` 进行调试，例如：`gcc -g main.cpp -o main`
> 2. 回车键：重复上一条命令


### 2. 命令行调试
