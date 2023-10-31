

muduo库源码github仓库地址：
https://github.com/chenshuo/muduo

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

root@tony-virtual-machine:/home/tony/package/muduo-master# apt-get install cmake

然后执行build.sh程序：

root@tony-virtual-machine:/home/tony/package/muduo-master# ./build.sh

3.编译完成后，在输入./build.sh install命令进行muduo库安装

root@tony-virtual-machine:/home/tony/package/muduo-master# ./build.sh install


这个./build.sh install实际上把muduo的头文件和lib库文件放到了muduo-master同级目录下的build目录下的release-install-cpp11文件夹下面了：

root@tony-virtual-machine:/home/tony/package# ls
build  muduo-master  muduo-master.zip
root@tony-virtual-machine:/home/tony/package# cd build/
root@tony-virtual-machine:/home/tony/package/build# ls
release-cpp11  release-install-cpp11
root@tony-virtual-machine:/home/tony/package/build# cd release-install-cpp11/
root@tony-virtual-machine:/home/tony/package/build/release-install-cpp11# ls
include  lib



所以上面的install命令并没有把它们拷贝到系统路径下，导致我们每次编译程序都需要指定muduo库的头文件和库文件路径，很麻烦，所以我们选择直接把inlcude（头文件）和lib（库文件）目录下的文件拷贝到系统目录下：


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



拷贝完成以后使用muduo库编写C++网络程序，不用在指定头文件和lib库文件路径信息了，因为g++会自动从/usr/include和/usr/local/lib路径下寻找所需要的文件。