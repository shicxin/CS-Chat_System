#!/bin/bash
#指定shell解释器为bash

gcc ../src/server/*.c -o server #编译./server目录下的所有.c文件，生成名为server的可执行程序
gcc ../src/client/*.c -o client #编译./client目录下的所有.c文件，生成名为client的可执行程序
