# 概述
该仓库用于存储**Amirkabir University of Technology 1400-2: Advanced Programming Course**的课程作业完成代码。

Homework原始地址：[点我](https://github.com/courseworks?q=AP1400&type=all&language=&sort=)

只完成了前 6 个，因为第7个是个 Python 项目。

目前进度及homework简介：

- [x] **HW1：** 实现一个 Matrix 类以及相关函数。
- [x] **HW2：** 实现一个模拟加密货币客户端/服务端执行过程的程序。
- [x] **HW3：** 实现一个 Binary Search Tree (BST)。
- [x] **HW4：** 实现 C++ 中的 SharedPtr 和 UniquePtr 智能指针。
- [x] **HW5：** 使用继承和多态实现多个类。
- [x] **HW6：** 使用 STL 库解决 4 个问题。

# 食用步骤

## 前言

本人的开发环境为：`Windows`下的`VScode` + `Ubuntu`虚拟机

在`VScode`中使用插件`Remote-SSH`来远程连接自己的虚拟机进行开发。所以，后面说的命令和配置方法均是在Ubuntu环境下的进行的。

## 克隆仓库

在自己的存放目录下执行命令：**`git clone git@github.com:YouZhiZheng/AUT1400-2.git`**

比如你在目录`example`下执行的这条命令，那么在`example`目录下就会多出一个名为`AUT1400-2`的目录，这就表示你成功的将此仓库克隆到本地了。

**注意：** 执行此命令时请确保已经配置好自己GitHub账号中的`SSH keys`。

## 环境安装

### 安装g++或clang++

`g++`和`clang++`都是优秀的C++编译器，根据自己的习惯和喜好随意选择其中一个即可，这里选择`clang++`来讲解。

首先执行命令：**`clang++ --version`** 查看自己的`Ubuntu`是否安装了`clang++`编译器。

如果没有安装则依次执行以下命令进行安装：

1. 更新包列表：`sudo apt update`
2. 进行安装：`sudo apt install clang`

### 安装CMake

执行命令查看是否已安装CMake：`cmake --version`

若未安装，请参考[此文章](https://zhuanlan.zhihu.com/p/519732843)进行安装。

**注意：** CMake版本不应低于 `3.13`

### 安装GoogleTest

`Google Test`是C++的一个流行的测试框架，也被称为`Google's C++ Testing Framework`，简称为`gtest`，可以帮助开发者编写自动化的、可重复的、可维护的测试用例，测试程序的正确性。它是一个开源项目，在GitHub上有详细的介绍文档，点击[此处](https://github.com/google/googletest/tree/main)即可访问。

在本项目中，不要求你会使用它（因为测试流程已经编写好了），只需要安装即可。如果你想学习怎么使用`gtest`，可参考[官方文档](https://google.github.io/googletest/quickstart-cmake.html)。


在你想要的安装目录下依次执行以下命令即可安装`gtest`：

```bash
$ git clone git@github.com:google/googletest.git
$ cd googletest
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## 完成代码并测试

**以`AP1400-2-HW1`为例：**
1. 进入该目录：`cd ./AP1400-2-HW1`
2. 阅读该目录下的`README.md`，该文件是题目
3. 根据题目完成对应的`hw1.cpp`和`hw1.h`文件
4. 每完成一个成员函数就应进行测试，不要等全部写完了再进行测试。比如完成了`zeros`函数就去`unit_test.cpp`文件中将对应部分取消注释，zeros的测试函数为`TEST(HW1Test, ZEROS){......}`
5. 写好`zeros`函数后，就该编译运行进行测试，在`AP1400-2-HW1`目录下依次执行以下命令：  
```bash
mkdir build
cd build
cmka ..
make
./main
```
6. 当在终端打印`<<SUCCESS>>`则表示测试通过。
7. 重复上述过程，直到编写完整个类且成员函数均通过测试，则完成了此homework。

**注意：** Answer目录下存放的是作者写的每个homework答案（水平有限，难免存在错误，发现错误请联系作者），在实在没有办法完成时再参考！！！

**Note：** 
1. HW3中的successor节点指的是**前继节点**，即左子树的最右节点或父节点。
2. HW5的`ingredient.h`中get_name应该为纯虚函数，`price`应为非虚函数。
3.  HW6中在测试的时候请将 `unit_test.cpp` 中的文件目录换为正确的文件放置目录。
