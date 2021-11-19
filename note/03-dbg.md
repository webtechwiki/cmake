# GDB调试器

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
