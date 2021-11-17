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

给出一段代码，准备调试

```cpp
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int N = 100;
	int sum = 0;
	int i = 1;

	while(i <= N){
		sum = sum + i;
		i = i + 1;
	}

	cout << "sum = " << sum <<endl;
	cout << "The program is over " <<endl;

	return 0;
}
```

普通编译方式
```shell
g++ sum.cpp -o a_no_g
```

编译出用于调试的可执行文件
```shell
g++ -g sum.cpp -o a_yes_g
```

使用`gdb`命令进行调试，如果我们调试 `a_no_g` ，将会提示一下错误
```shell
pan@pan-PC:~/Work/md/cmake/src/gcc_dbg$ gdb a_no_g 
GNU gdb (Uos 8.2.1.1-1+security) 8.2.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a_no_g...(no debugging symbols found)...done.
(gdb)
```

因为`a_no_g`这个可执行文件不包含用于调试的信息，输入`quit`再按回车即可，通过`gdb a_yes_g`指令执行可调试的可执行文件

```
pan@pan-PC:~/Work/md/cmake/src/gcc_dbg$ gdb a_yes_g 
GNU gdb (Uos 8.2.1.1-1+security) 8.2.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a_yes_g...done.
(gdb)
```

此时可以正常进入调试

**调试过程**

直接执行
```
run
```

或者使用简写`r`，运行结果
```shell
(gdb) run
Starting program: /home/pan/Work/md/cmake/src/gcc_dbg/a_yes_g 
sum = 5050
The program is over 
[Inferior 1 (process 21340) exited normally]
```

在第13行打断点
```shell
break 13
```

运行结果如下
```
(gdb) break 11
Breakpoint 1 at 0x4011ae: file sum.cpp, line 11.
```

也可以使用简写的方式，在第12行打断点
```shell
b 12
```

结果如下
```
(gdb) break 12
Breakpoint 3 at 0x4011b4: file sum.cpp, line 12.
```

使用`info break`指令或者指令简写`i b`查看当前的断点，如下结果
```
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004011ae in main(int, char const**) 
                                                   at sum.cpp:11
2       breakpoint     keep y   0x00000000004011b4 in main(int, char const**) 
                                                   at sum.cpp:12
```

使用`run`指令或者`r`指令执行程序，此时命中了第11行断点，如下内容
```shell
(gdb) r
Starting program: /home/pan/Work/md/cmake/src/gcc_dbg/a_yes_g 

Breakpoint 1, main (argc=1, argv=0x7fffffffca48) at sum.cpp:11
11                      sum = sum + i;
```

此时可以查看变量的值，如查看i的值，可以使用`print i`或者`p i`指令，如下

```shell
(gdb) print i
$1 = 1
```

使用`p N` 查看N的值，如下
```shell
(gdb) p N
$2 = 100
```

此时程序执行到第11行处，如果我们需要继续执行，输入`continue`指令并按回车即可，程序将执行到代码的第12行，如下
```shell
Continuing.

Breakpoint 2, main (argc=1, argv=0x7fffffffca48) at sum.cpp:12
12                      i = i + 1;
```

因为我们是在`while`循环体内，`i`的值将不断变化，如果我们需要跟中`i`值的变化，需要输入`display i`指令即可，再输入`continue`指令让程序单步执行，如下

```shell
(gdb) display i
1: i = 1
(gdb) continue
Continuing.

Breakpoint 1, main (argc=1, argv=0x7fffffffca48) at sum.cpp:11
11                      sum = sum + i;
1: i = 2
```
可以观察到，通过循环，有回到了第一个断点，此时`i`的值已经变成了2。在gdb调试中，如果我们只按回车键，gdb将执行我们最后一次输入的指令，所以我们可以一直按回车键继续让程序单步执行。

当断点执行都某个位置时，我们想要查看断点附近的代码，可以执行`list`指令进行查看，如下

```shell
(gdb) list
7               int sum = 0;
8               int i = 1;
9
10              while(i <= N){
11                      sum = sum + i;
12                      i = i + 1;
13              }
14
15              cout << "sum = " << sum <<endl;
16              cout << "The program is over " <<endl;
```