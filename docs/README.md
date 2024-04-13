# C/C++ 库的创建和使用
## 说明
1. 工程文件结构

```shell
.
├── bin                     // 可执行文件目录
│   ├── dynamic_demo
│   └── static_demo
├── build                   // 构建目录 
│   ├── lib                 // 库
│   │   ├── libdemo.a       // 静态库
│   │   └── libdydemo.so    // 动态库
│   └── obj                 // 存放编译后的二进制文件
│       ├── bubblesort.o
│       ├── dybubblesort.o
│       ├── dyswap.o
│       └── swap.o
├── docs
│   └── README.md
├── include                 // 头文件目录
│   └── bubble.hpp
└── src                     // 源代码目录
    ├── bubblesort.cpp
    ├── main.cpp
    └── swap.cpp
```

2. 我们将使用`src`文件夹中的swap.cpp和bubblesort.cpp文件去创建我们的库，这两个文件合起来可以实现对整数数组的冒泡排序算法。main.cpp文件用来读取冒泡排序后的数组并打印出来，它将会被用来创建可执行程序。

## 一、静态库的创建和使用
### 1. 将源代码编译为目标文件(.o)
```bash
g++ -c ./src/swap.cpp -o ./build/obj/swap.o -I ./include/
g++ -c ./src/bubblesort.cpp -o ./build/obj/bubblesort.o -I ./include/
```

> *说明*:  
参数-c 将指定源代码编译为二进制汇编代码  
参数-o 指定生成文件名(及后缀)  
参数-I 添加头文件目录

经过上述操作，./build/obj文件夹中就会出现swap.o和bubblesort.o两份二进制文件。

### 2. 创建静态库: 使用ar命令行工具创建静态库(.a)
```bash
ar -rcs ./build/lib/libdemo.a ./build/obj/*.o
```
> *说明：*  
参数-rcs r将文件插入备存文件中， c创建备存文件， s建立索引  
静态库的命名格式`lib + name + .a`，如本次示例`libdemo.a`，"demo"是静态库的名字。

经过上述操作，.build/lib文件夹中会出现libdemo.a文件，此时静态库创建成功。
### 3. 使用静态库
```bash
g++ ./src/main.cpp -o ./bin/static_demo -I ./include/ -L ./build/lib/ -l demo
```
> *说明：*  
./src/main.cpp  为主程序源代码  
参数-o 指定生成的可执行程序路径和名称`static_demo`  
参数-L 指定静态库的路径，可以使用相对路径  
参数-l 指定库的名称`demo`。

经过上述操作，./bin文件夹中会出现可执行文件static_demo。在终端输入`./bin/static_demo`执行该文件，主程序会输出：
```bash
1, 2, 3, 4, 5, 6, 7
```

## 二、动态库的创建和使用
### 1. 将源代码编译为可以被动态库使用的地址无关代码
```bash
g++ -fPIC -c ./src/swap.cpp -o ./build/obj/dyswap.o -I ./include/
g++ -fPIC -c ./src/bubblesort.cpp -o ./build/obj/dybubblesort.o -I ./include/
```
> *说明：*  
参数-fPIC 使生成的二进制文件是地址无关代码

上述操作会在./build/obj文件夹中生成dyswap.o和dybubblesort.o两份文件(笔者注：前缀dy表示dynamic，这样写便于读者区分，实际应用可不加dy，但需要注意文件名称冲突)

### 2. 创建动态库: 使用g++创建动态库(.so)
```bash
g++ -shared ./build/obj/dy*.o -o ./build/lib/libdydemo.so
```
> *说明：*  
参数-shared 指定生成共享库(动态库)

### 3. 使用动态库
1. 生成可执行文件
```bash
g++ ./src/main.cpp -o ./bin/dynamic_demo -I ./include/ -L ./build/lib/ -l dydemo
```
> *说明：*  
参数-L 指定静态库的路径，可以使用相对路径  
参数-l 指定库的名称`dydemo`

2. 执行可执行文件

在终端输入命令`./bin/dynamic_demo`，回车执行，会出现如下错误：
```bash
./bin/dynamic_demo: error while loading shared libraries: libdydemo.so: cannot open shared object file: No such file or directory
```

**为什么会出现这个问题呢？**  

虽然编译器g++成功地找到了名为该动态库的库文件，但在程序运行时，操作系统需要在运行时动态加载这个动态库。
静态库在链接时会直接被复制到程序中，因此程序可以随时使用静态库中的代码。但是动态库不会被复制到程序中，只有在主程序需要时，操作系统才会将它加载到内存中，以供程序调用  
所以尽管程序知道这个库的存在，但是操作系统却不知道这个动态库的具体位置。因此，当程序尝试调用该动态库中的函数时，操作系统无法找到它，于是就会报错找不到这个共享库文件。
总之，问题不在于程序不知道库的位置，而在于操作系统无法找到这个库的位置。

**那么，如何解决呢？**
* (1). 尝试使用`ldd exeutable`来查看excutable与动态库的依赖关系。如，在终端输入`ldd ./bin/dynamic_demo`，终端会输出：
```bash
        linux-vdso.so.1 (0x00007ffde39ba000)
        libdydemo.so => not found
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007946f7400000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007946f7000000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007946f76a9000)
        /lib64/ld-linux-x86-64.so.2 (0x00007946f77c3000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007946f7689000)
```
可以注意到`libdydemo.so => not found`，说明我们的操作系统并未找到这个库。
* (2). 现在将我们的库文件路径添加到系统的环境变量中，在运行程序前，在终端输入`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库文件所在的绝对路径`回车（记得将你libdydemo.so文件的绝对路径替换掉`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库文件所在的绝对路径`中的`库文件所在的绝对路径`字段）。

* (3). 此时再在终端输入`ldd ./bin/dynamic_demo`，回车执行，终端会打印出：
```bash
        linux-vdso.so.1 (0x00007fff753ab000)
        libdydemo.so => ~/Lib/build/lib/libdydemo.so (0x000072ac60450000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x000072ac60000000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000072ac5fc00000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x000072ac6033d000)
        /lib64/ld-linux-x86-64.so.2 (0x000072ac6045c000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x000072ac6031d000)
```
注意，我们已经可以看到`libdydemo.so => ~/Lib/build/lib/libdydemo.so (0x000072ac60450000)`，即系统已经可以识别到执行文件和我们自定义的动态库之间的依赖关系了。

* (4).在终端输入`./bin/dynamic_demo`，终端输出：
```bash
1, 2, 3, 4, 5, 6, 7
```  
主程序成功运行。

> tips  
在终端输入`gedit .bashrc`，在打开的文件的最后加上如下代码：
> ```bash
> # link my customized c++ dynamic library to the environment variable
> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库文件所在的绝对路径
> ```
> 可以不用每次在运行对应可执行程序前在终端输入同样的代码。

