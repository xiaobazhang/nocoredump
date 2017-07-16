# nocoredump

## (1) nocoredump介绍
nocoredump是一个可用于捕捉程序中出现严重的错误的程序,它能够捕捉到如下引起程序崩溃的严重bug,同时能够跳过出问题的程序,继续运行程序。同时在出问题的地方会打印出问题堆栈帮助调试:

## (2) nocoredump能够处理的bug
nocoredump能够处理的严重崩溃问题如下,按照bug所触发的信号分为三类如下:

信号|  值  |  动作 | 说明
----|---|---|---
SIGILL | 4 |  Core	|  非法指令(程序错误、试图执行数据段、栈溢出等)
SIGFPE  |  8 |  Core |  算术运行错误(浮点运算错误、除数为零等)
SIGSEGV	 | 11  |  Core | 无效内存引用(试图访问不属于自己的内存空间、对只读内存空间进行写操作)

## (3) nocoredump的使用
首先下载该项目,由于项目程序全是以头文件提供,所以只需将该项目头文件包含到工程项目中即可,使用也非常简单,如下所示:

```
    #include "srv/catch_exceptions.h" //头文件
    
    Try("bug_name") //此处名字是所要标记try这段代码的名字,可以任意取,但是一定要记住不能和其他Try块的名字重复!!!
        bug();      //有可能引起异常的的程序段
    EndTry          //EndTry一定要加上
    CatchExceptions //假如出现了bug,catch到bug后所要运行的代码
        cout << "catch the bug bug_name!!!" << endl;
    EndCatch        //EndCatch 一定要加上
```

## (4) nocoredump的线程安全问题
经过测试,多线程下nocoredump是线程安全的,可以在多个线程中安全运行,并且打印的堆栈是当前出问题的堆栈,非常好用。
但是一定要注意的是,在两个或多个线程同时触发bug的时候,这里所说的同时使指两个线程触发bug时间差小于百万分之一秒


