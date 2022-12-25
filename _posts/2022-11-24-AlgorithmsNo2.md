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
