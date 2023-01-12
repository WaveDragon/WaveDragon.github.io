---
title: Algorithms-DengNo3
author: WaveDragon
date: 2022-12-29 11:11:00 +0800
categories: [Blogging, Structures and Algorithms]
tags: [Study]
math: true
mermaid: true
# image:
#   path: /commons/devices-mockup.png
#   width: 800
#   height: 500
#   alt: Responsive rendering of Chirpy theme on multiple devices.
---

# 第四章 栈与队列

栈与队列与列表和向量一样，都是线性序列结构。其基础性是其他结构无法比拟的。

**着重介绍如何利用栈结构，实现基于试探回溯策略的高效搜索算法。**
**在队列方面，将介绍如何实现基于轮值策略的通用循环分配器，并以银行窗口为例实现基础的调度算法**

## 4.1 栈
### 4.1.1 ADT接口

栈中可以操作的一端更多的称为栈顶，另一方无法操作的称为栈底。

|操作接口|功能|
|:--:|:--:|
|size()|报告栈的规模|
|empty()|判断栈是否为空|
|push(e)|将e插至栈顶|
|pop()|删除栈顶对象|
|top()|引用栈顶对象|

#### 后出先进

### 4.1.3 Stack模板类

利用C++继承，按向量模板实现栈结构

```cpp
#include "../Vector/Vector.h" //以向量为基类，派生出栈模板类
template <typename T>
class Stack : public Vector<T>
{                                                // 将向量癿首/末端作为栈底/顶
public:                                          // size()、empty()以及其它开放接口，均可直接沿用
    void push(T const &e) { insert(size(), e); } // 入栈：等效于将新元素作为向量癿末元素揑入
    T pop() { return remove(size() - 1); }       // 出栈：等效亍初除向量癿末元素
    T &top() { return (*this)[size() - 1]; }     // 取顶：直接返回向量癿末元素
};
```
### 4.2 栈与递归

#### 4.2.1 函数调用栈

![图04-03 函数调用栈实例：主函数main()调用funcA()，funcA()调用funcB()，funcB()再自我调用](https://user-images.githubusercontent.com/78013131/212068196-52d9cc17-ed12-4a83-b47d-1ceb3c1e4c08.png)

> 如图4.3所示，调用栈的基本单位是帧（frame）。每次函数调用时，都会相应地创建一帧，记录该函数实例在二进制程序中的返回地址（return address），以及局部变量、传入参数等，并将该帧压入调用栈。若在该函数返回之前又发生新的调用，则同样地要将与新函数对应的一帧压入栈中，成为新的栈顶。函数一旦运行完毕，对应的帧随即弹出，运行控制权将被交还给该函数的上层调用函数，并按照该帧中记录的返回地址确定在二进制程序中继续执行的位置。

>在任一时刻，调用栈中的各帧，依次对应于那些尚未返回的调用实例，亦即当时的活跃函数实例（active function instance）。特别地，位于栈底的那帧必然对应于入口主函数main()，若它从调用栈中弹出，则意味着整个程序的运行结束，此后控制权将交还给操作系统。仿照递归跟踪法，程序执行过程出现过的函数实例及其调用关系，也可构成一棵树，称作该程序的运行树。任一时刻的所有活跃函数实例，在调用栈中自底到顶，对应于运行树中从根节点到最新活跃函数实例的一条调用路径。
