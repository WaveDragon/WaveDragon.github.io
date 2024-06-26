---
title: Algorithms-DengNo1
author: WaveDragon
date: 2022-11-13 23:11:00 +0800
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

# 第一章 绪论
## 1.1 计算机与算法
#### 起泡排序 bubblesort
整数数组的起泡排序
```cpp
void bubblesort1A(int A[], int n)
{
    bool sorted = false;//整体排序标志，假设尚未排序
    while (！sorted){
        sorted = true;
        for(int i = 1;i<n;i++)
        {
            if(A[i-1] > A[i])//一旦依序，就交换顺序
            {
                swap(A[i-1],A[i]);
                sorted = false;
            }
        }
        n--;
    }
}
```
#### 算法的有穷性与正确性
## 1.2 复杂度度量
### 1.2.1 时间复杂度
时间复杂度T(n),特定算法处理规模为n的问题所需的时间记作T(n)。
### 1.2.2 渐进复杂度
#### 大O记号
关注T(n)的渐进上届。
#### 起泡排序
在每一类内循环，需要扫描和比较n-1对元素，至多需要交换n-1对元素。元素的比较和交换都属于基本操作，故每一轮内循环至多需要执行2(n-1)次基本操作，外循环至多执行n-1轮。故 $T(n) =O(2(n-1)^2) = O(n^2) $

#### 最好与最坏情况
渐进下届 大$ \Omega$记号
#### 平均情况
算法运行时间同阶 大 $\Theta$ 记号
### 1.2.3 空间复杂度
时间复杂度本身就是空间复杂度的一个天然上界

## 1.3 复杂度分析

### 1.3.1 常数O(1)
仅含一次或常数次基本操作的算法，此类通常不含循环，分支，子程序调用等。

### 1.3.2  对数O(logn)
函数 $log_r n $ 统称O(logn) 对数时间复杂度，效率极为高效

### 1.3.3 线性O(n)
此类效率足以令人满意

### 1.3.4 多项式O(n^m)
起泡排序 O(n²) 多项式级的运行时间成本，一般是可接受的，故在此范围内，都称为是可以有效求解或者易解的

### 1.3.5 指数O(2^n)
### 1.3.6 复杂度层次

![复杂度层次](https://user-images.githubusercontent.com/78013131/202640816-b4dc11b8-f039-4ffd-a911-69bbb6411e2b.jpg){width="972" height="589" }
<br>

  
### 1.3.7 输入规模 
所谓待计算问题的输入规模，应严格定义为：用以描述输入所需的空间规模

## 1.4 *递归
递归是一种基本而典型的算法设计模式，这一模式可以对实际问题中反复出现的结构和形式做高度概况，并从本质层面加以描述和刻画。
### 1.4.1 线性递归
#### 数组求和

```cpp
int sum(int A[] , int n)
{
    if(1 > n)//平凡情况，递归基
        return 0;
    else //一般情况
        return sum(A,n-1) + A[n-1];//递归：前n-1项之和，再累计第n-1项
}
```

#### 线性递归

#### 减而治之

线性递归的模式，往往对应于所谓减而治之的策略，递归每深入一层，待求解问题的规模都缩减一个常数，直至退化为平凡的小问题

满足有穷性。当抵达递归基时，算法将执行非递归的计算

### 1.4.2 递归分析

#### 递归跟踪

递归跟踪可以用来分析递归算法的总体运行时间与空间。
> 1. 算法的每一个递归实例都表示为一个方框，其中注明该实例调用的参数
> 2. 若实例M调用N，则在M与N之间添加一条有向连线

![递归跟踪分析](https://user-images.githubusercontent.com/78013131/202645057-5746dfdf-0459-42d5-88c9-6d5abfb35734.png){: width="972" height="589" }
<br>

**递推方程**

### 1.4.3 递归模式

#### 多递归基

为保证有穷性，递归算法都必须设置递归基，且确保总能执行到。
同一算法的递归基可能(显式或隐式地)不止一个

```cpp
void reverse( int *A ,int lo, int hi)
{
    if(lo < hi)
    {
        swap(A[lo],A[hi]);
        reverse(A, lo+1,hi-1);
    }
}
```
#### 多向递归

不仅递归基可以有多个，递归调用也可能有多种选择分支
对于幂函数power2(n) = 2^n，按照线性递归的构思，可以重新定义

$$
power2(n) = \left\{\begin{matrix}
1  & (若n=0)\\ 
 power2(\left \lfloor n/2 \right \rfloor )^2\times 2 &(若n>0且为奇数) \\
power2(\left \lfloor n/2 \right \rfloor )^2 &(若n>0且为偶数)
\end{matrix}\right.

$$

一般的，若n的二进制展开式为 $ b_1b_2b_3...b_k $
则有
$$
2^{n_k} = (2^{n_{k-1}}) * 2^{b_k}
$$
可得递推式:

$$
power2(n_k) = \left\{\begin{matrix}
power2(n_{k-1})^2 *2  & (若b_k=1)\\ 
 power2(n_{k-1})^2 &(若b_k=0) 
\end{matrix}\right.

$$

基于此递推式，可得幂函数的多向递归版本power2():

```cpp
inline __int64 sqr(__int64 a ){return a*a;}
__inline power2(int n)
{
    if(0 == n) return 1;//递归基
    return (n & 1) ? sqr(power2(n >> 1)) <<1 : sqr(power2(n >> 1));//视n奇偶分别递归;
}//O(logn) = O(r) r为输入指数n的比特数
```

### 1.4.4 递归消除
递归模式并非十全十美，优点背后也隐含某些代价
#### 空间成本
递归算法所消耗的空间量取决于递归深度，故其往往消耗更多空间。

#### 尾递归及其消除
若递归调用在递归实例中恰好以最后一步操作的形式出现，则成为尾递归(tail recursion) 数组交换算法即属于典型尾递归。实际上属于尾递归的算法，均可以简捷地转换为等效迭代版本

```cpp
void reverse(int* A, int lo, int hi)
{
    while (lo < hi)
    {
        swap(A[lo++],A[hi--]);
    }
}//O(hi-lo+1);
```

### 1.4.5 二分递归
#### 分而治之
**优化策略** 为消除递归算法中重复的递归实例，可以：
> 借助一定量的辅助空间，在各个子问题求解后，记录下对应的解答。


## 1.5 抽象数据类型
体现数据结构的通用性，普遍采用模板类的描述方式。