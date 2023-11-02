muduo网络库是一个基于C++语言的高性能网络库，它提供了一系列的网络编程工具和组件，用于开发高性能的服务器应用程序。muduo网络库的设计目标是简单、可扩展、高效，它的核心思想是基于Reactor模式和事件驱动，提供了事件循环、定时器、网络编程等功能，使得开发者能够更加方便地编写高性能的网络应用程序。

在Ubuntu 22.04中配置muduo网络库的详细教程如下：

1. 安装必要的依赖项
   ```bash
   sudo apt update
   sudo apt install g++ make cmake libboost-all-dev
   ```

2. 下载muduo源代码
   ```bash
   git clone https://github.com/chenshuo/muduo.git
   ```

3. 创建并进入build目录
   ```bash
   cd muduo
   mkdir build
   cd build
   ```

4. 使用CMake配置muduo
   ```bash
   cmake ..
   ```

5. 编译muduo
   ```bash
   make
   ```

6. 安装muduo
   ```bash
   sudo make install
   ```

7. 配置环境变量
   将muduo库的路径添加到LD_LIBRARY_PATH中，例如：
   ```bash
   export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
   ```

muduo库源码github仓库地址：
https://github.com/chenshuo/muduo

如果采用下载压缩包后配置的方式

1.拷贝muduo的源码压缩包muduo-master.zip到Linux系统下

```shell
root@tony-virtual-machine:/home/tony/package# ls
muduo-master.zip
root@tony-virtual-machine:/home/tony/package# unzip muduo-master.zip
```

解压完成后，进入muduo库的解压目录里面

```shell
root@tony-virtual-machine:/home/tony/package# ls
muduo-master  muduo-master.zip
root@tony-virtual-machine:/home/tony/package# cd muduo-master
root@tony-virtual-machine:/home/tony/package/muduo-master# ls
armlinux.diff  build.sh   clang.diff      Doxyfile  License      muduo         README
backport.diff  ChangeLog  CMakeLists.txt  examples  MacOSX.diff  premake4.lua  TODO

```

2.看到有一个build.sh源码编译构建程序，运行该程序（注意：muduo是用cmake来构建的，需要先安装cmake，ubuntu下直接sudo apt-get install cmake就可以，redhat或者centos可以从yum仓库直接安装）：

拿ubuntu举例，如果没有安装cmake，执行下面的命令安装cmake：
```shell
root@tony-virtual-machine:/home/tony/package/muduo-master# apt-get install cmake
```

然后执行build.sh程序：

```shell
root@tony-virtual-machine:/home/tony/package/muduo-master# ./build.sh
```

3.编译完成后，在输入./build.sh install命令进行muduo库安装

```shell
root@tony-virtual-machine:/home/tony/package/muduo-master# ./build.sh install
```

这个./build.sh install实际上把muduo的头文件和lib库文件放到了muduo-master同级目录下的build目录下的release-install-cpp11文件夹下面了：

```shell
root@tony-virtual-machine:/home/tony/package# ls
build  muduo-master  muduo-master.zip
root@tony-virtual-machine:/home/tony/package# cd build/
root@tony-virtual-machine:/home/tony/package/build# ls
release-cpp11  release-install-cpp11
root@tony-virtual-machine:/home/tony/package/build# cd release-install-cpp11/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# ls
include  lib
```

所以上面的install命令并没有把它们拷贝到系统路径下，导致我们每次编译程序都需要指定muduo库的头文件和库文件路径，很麻烦，所以我们选择直接把inlcude（头文件）和lib（库文件）目录下的文件拷贝到系统目录下：

```shell
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# ls
include  lib
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# cd include/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/include# ls
muduo
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/include# mv muduo/ /usr/include/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/include# cd ..
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# ls
include  lib
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# cd lib/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/lib# ls
libmuduo_base.a  libmuduo_http.a  libmuduo_inspect.a  libmuduo_net.a
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/lib# mv * /usr/local/lib/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11/lib# 
```

拷贝完成以后使用muduo库编写C++网络程序，不用在指定头文件和lib库文件路径信息了，因为g++会自动从/usr/include和/usr/local/lib路径下寻找所需要的文件。