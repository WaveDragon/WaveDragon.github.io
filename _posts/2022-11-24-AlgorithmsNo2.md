---
title: Algorithms-DengNo2
author: WaveDragon
date: 2022-11-24 11:11:00 +0800
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

# 第二章 向量
最基本的线性结构称为序列，根据数据项的逻辑次序与其物理存储地址的对应关系不同，又可以进一步区分为**向量(vector)**和**列表(list)**

## 2.1 从数组到向量
 线性数组
 向量各元素的**秩**互异，称为循秩访问

 ## 2.2 接口
 ### 2.2.3 vector模板类

```cpp
0001 using Rank = int; //秩
0002 #define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）
0003 
0004 template <typename T> class Vector { //向量模板类
0005 protected:
0006    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
0007    void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
0008    void expand(); //空间不足时扩容
0009    void shrink(); //装填因子过小时压缩
0010    bool bubble ( Rank lo, Rank hi ); //扫描交换
0011    void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
0012    Rank maxItem ( Rank lo, Rank hi ); //选取最大元素
0013    void selectionSort ( Rank lo, Rank hi ); //选择排序算法
0014    void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
0015    void mergeSort ( Rank lo, Rank hi ); //归并排序算法
0016    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
0017    Rank partition ( Rank lo, Rank hi ); //轴点构造算法
0018    void quickSort ( Rank lo, Rank hi ); //快速排序算法
0019    void shellSort ( Rank lo, Rank hi ); //希尔排序算法
0020 public:
0021 // 构造函数
0022    Vector ( int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
0023    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
0024    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
0025    Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
0026    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
0027    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
0028 // 析构函数
0029    ~Vector() { delete [] _elem; } //释放内部空间
0030 // 只读访问接口
0031    Rank size() const { return _size; } //规模
0032    bool empty() const { return !_size; } //判空
0033    Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
0034    Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
0035    Rank search ( T const& e ) const //有序向量整体查找
0036    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
0037    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
0038 // 可写访问接口
0039    T& operator[] ( Rank r ); //重载下标操作符，可以类似于数组形式引用各元素
0040    const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本
0041    Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
0042    T remove ( Rank r ); //删除秩为r的元素
0043    int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
0044    Rank insert ( Rank r, T const& e ); //插入元素
0045    Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
0046    void sort ( Rank lo, Rank hi ); //对[lo, hi)排序
0047    void sort() { sort ( 0, _size ); } //整体排序
0048    void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
0049    void unsort() { unsort ( 0, _size ); } //整体置乱
0050    Rank deduplicate(); //无序去重
0051    Rank uniquify(); //有序去重
0052 // 遍历
0053    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
0054    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
0055 }; //Vector
```


## 2.3 构造与析构
向量中秩为r的元素，对应内部数组中的_elem[r]，其物理地址为_elem + r

### 2.3.1 基于复制的构造方法
### 2.3.3 析构方法

## 2.4 动态空间管理
### 2.4.1 静态空间管理
向量实际规模与其内部数组容量的比值(_size/_capacity),亦称为装填因子。

### 2.4.2 可扩充向量
在即将发生上溢时，适当地扩大内部数组容量。
扩容算法
新数组的容量总是取原数组的两倍
容量加倍策略，总体耗时 O(n)，每次扩容分摊成本为O(1)

### 2.4.5 缩容
## 2.5 常规向量

### 2.5.1 直接引用元素
重组操作符[]
置乱算法permute()
区间置乱接口 unsort()
```cpp
template <typename T> void Vector<T>:unsort(Rank lo,Rank hi){
    T* V = _elem+lo;
    for (Rank i = hi-lo; i>0; i--)
        swap(V[i-1], V[rand() % i]);//将V[i-1]与V[0,i)中某一元素随机交换。
}
```
### 查找 
无序向量 T为可以判等的基本类型
有序向量 T为可以比较的基本类型
### 去重/唯一化

### 遍历

## 2.6 有序向量

若向量不仅按线性次序存放，而且其数值大小也按次序单调分布，则成为有序向量。

### 唯一化
```cpp
template <typename T> int Vector<T>::uniquify()
{
    Rank i = 0,j =  0;
    while(++j < size)
    {
        if (_elem[i]  !=  _elem[j])
            _elem[++i]  =  _elem[j];
    }
    _size = ++i;
    shrink();
    return j-i;
}
```
复杂度为O(n)

### 2.6.5 二分查找
循秩访问加上有序性，我们可以减而治之，来运用于有序向量查找。
<font color = Salmon size = 6>版本A</font>

```cpp
template <typename T> static Rank binSearch(T* A, T  const& e, Rank lo,Rank hi)
{
    while (lo < hi)
        {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi])
            hi = mi;
        else if( A[mi] < e)
            lo = mi+1;
        else 
            return mi;
        }
    return -1;//查找失败    
}//有多个命中元素时，不能保证返回秩最大者；查找失败时，简单返回-1，而不能指示位置
```

不足，最短和最长分支对应的查找长度相差两倍。

### 2.6.6 Fibonacci查找
其一，调整前后区域的宽度，适当地加长(缩短)前后子向量
其二，统一沿两个方向深入所需执行的比较次数，比如都统一为1次

#### 黄金分割
实现Fibonacci查找算法
```cpp
#include "..\fibonacci\Fib.h"//引入Fib数列类

template <typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi)
{
    Fib fib(hi - lo);//创建Fib数列
    while(lo < hi)
    {
        while (hi - lo < ifb.get())
            fib.prev();//通过向前顺序查找 
        Rank mi = lo + fib.get() - 1;//确定形如Fib(k) - 1 的轴点；
        if (e < A[mi])
            hi = mi;
        else if( A[mi] < e)
            lo = mi+1;
        else 
            return mi;
    }
    return -1;
}

```

### 2.6.7 二分查找
<font color = Salmon size = 6 >版本B</font>
在每个切分点 仅做一次元素比较

```cpp
template<tpyename T> static Rank binSearch(T* A,const& e, Rank lo, Rank hi)
{
    while( 1 < hi-lo )
    {
        Rank mi = (lo+hi ) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo] ) ? lo : -1;

}
```

<font color = Salmon size = 6 >版本C</font>

```cpp
template<tpyename T> static Rank binSearch(T* A,const& e, Rank lo, Rank hi)
{
    while( lo < hi )
    {
        Rank mi = (lo+hi ) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi+1;
    }
    return --lo;//循环结束时，lo为大于e的最小秩，

}//有多个命中元素时，总能保证返回秩最大者，失败时，能够返回失败的位置。
```
C中的循环体，具有以下不变性。
<table><tr><td bgcolor=DarkSeaGreen>
<font color = #000000 size =4 >
A[0, lo] 中的元素皆不大于e；A[hi,n) 中的元素皆大于e；
</font>
</td></tr></table>

### 比较树

基于比较式算法，称为CBA式算法


## 2.8 排序器

### 2.8.1 统一入口

```cpp
template <typename T> void Vector<T>::sort (Rank lo,Rank hi)
{
    switch (rand() % 5)
    {
        case 1: bubbleSort();break;//起泡排序；
        case 2: selectSort();break;//选择排序；
        case 3: mergeSort();break;//归并排序；
        case 4: heapSort();break;//堆排序；
        default: quickSort();break;//快速排序；
    }
}
```
<font color = Salmon size =4 >
单趟排序
</font>

```cpp
template <typename T> book Vector<T>:: bubble(Rank lo,Rank hi)
{
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo-1] > _elem[lo])//如果逆序，则
            {
            sorted = false;
            swap(_elem[lo-1] , _elem[lo])//交换局部有序
            }
}
```

```cpp
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while(!bubble(lo,hi--));//逐趟扫描交换，直至全序。
}
```


### 2.8.3 归并排序(mergesort)
在最坏情况仍有O(n**log**n)

归并排序可以理解为通过反复调用**二路归并**算法实现
所谓二路归并，就是将两个有序序列合并成一个有序序列

#### 分治策略
```cpp
template <typename  T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2) return;//单元素区间有序，否则……
    int mi = (lo + hi) >> 1;//以中点为界
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);//分别对前后半段排序然后归并

}
```

归并排序是否可实现，关键在于二路归并算法。


![复杂度层次](https://user-images.githubusercontent.com/78013131/209563002-4c27970c-1562-4928-aa07-490511c676ae.png)
针对有序向量结构，二路归并算法 一种实现：

```cpp
template <typename T> //有序向量（区间）的归并
0002 void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) { //[lo, mi)和[mi, hi)各自有序，lo < mi < hi
0003    Rank i = 0; T* A = _elem + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)，就地
0004    Rank j = 0, lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
0005    for ( Rank i = 0; i < lb; i++ ) B[i] = A[i]; //复制自A的前缀
0006    Rank k = 0, lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)，就地
0007    while ( ( j < lb ) && ( k < lc ) ) //反复地比较B、C的首元素
0008       A[i++] = ( B[j] <= C[k] ) ? B[j++] : C[k++]; //将更小者归入A中
0009    while ( j < lb ) //若C先耗尽，则
0010       A[i++] = B[j++]; //将B残余的后缀归入A中——若B先耗尽呢？
0011    delete [] B; //释放临时空间：mergeSort()过程中，如何避免此类反复的new/delete？
0012 }
```