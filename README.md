# cmake的使用
> 10.14: 完成 P8 g++重要编译参数 8:10 时间处，完成代码在编译过程中的优化。
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
