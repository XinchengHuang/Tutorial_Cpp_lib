# C/C++ 库的创建和使用
## 一、静态库的创建和使用(based on g++ command)
### 1. 将源代码编译为目标文件(.o结尾)
```bash
g++ -c src/math.cpp -o build/obj/math.o
g++ -c src/int2ascii.cpp -o build/obj/int2ascii.o
```

### 2. 使用ar命令行工具创建静态库(.a结尾)
```bash
ar -rcs ./build/lib/libdemo.a ./build/obj/*.o
```

### 3. 程序中使用静态库
```bash
g++ ./src/main.cpp -o ./bin/demo -L ./build/lib -ldemo
```
