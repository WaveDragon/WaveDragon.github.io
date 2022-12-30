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

# 第三章 列表

循链接访问

## 3.1 从向量到列表
### 3.1.1 从静态到动态

size()和get()等静态操作均可以在常数时间完成。而insert()和remove()等动态操作却需要线性时间。究其原因，在于各个元素物理地址连续---即所谓的**静态存储策略**

而列表结构未对物理地址做限制，即**动态存储策略**。

链表<font color = salmon>linked list</font>即是一种典型的动态存储结构

### 3.1.2 由秩到位置

### 3.1.3 列表
列表是具有线性逻辑次序的一组元素构成的集合。
列表是链表结构的一般化推广，其中元素称为节点(node)。与向量一样，在元素之间也可以定义前驱、直接前驱、以及后继和直接后继等关系。

## 3.2 接口
### 3.2.1 列表接口

#### ListNode模板类

```cpp
using Rank = int; //秩
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; //列表节点位置
template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
 // 成员
    T data; ListNodePosi<T> pred; ListNodePosi<T> succ; //数值、前驱、后继
 // 构造函数
    ListNode() {} //针对header和trailer的构造
    ListNode ( T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL )
       : data ( e ), pred ( p ), succ ( s ) {} //默认构造器
 // 操作接口
    ListNodePosi<T> insertAsPred ( T const& e ); //紧靠当前节点之前插入新节点
    ListNodePosi<T> insertAsSucc ( T const& e ); //紧随当前节点之后插入新节点
 };
```

### 3.2.2 列表

#### ADT接口
#### List模板类


## 3.3 列表
### 3.3.1 头尾节点
哨兵节点

### 3.3.2 默认构造方法

```cpp
template <typename T> void List<T>::init() { //列表初始化，在创建列表对象时统一调用
    header = new ListNode<T>; //创建头哨兵节点
    trailer = new ListNode<T>; //创建尾哨兵节点
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    _size = 0; //记录规模
 }
 ```
 
### 3.3.3 由秩到位置的转换

 <font color = salmon size = 5>重载操作符[ ]，提供转换接口</font>

 ```cpp
 template <typename T> //重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，需慎用）
 T& List<T>::operator[] ( Rank r ) const { //assert: 0 <= r < size
    ListNodePosi<T> p = first(); //从首节点出发
    while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
    return p->data; //目标节点，返回其中所存元素
 }
 ```


 ### 3.3.4 查找
 <font color = salmon size = 5>实现</font>

 ```cpp
 template <typename T> //在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
 ListNodePosi<T> List<T>::find ( T const& e, int n, ListNodePosi<T> p ) const {
    while ( 0 < n-- ) //（0 <= n <= rank(p) < _size）对于p的最近的n个前驱，从右向左
       if ( e == ( p = p->pred )->data ) return p; //逐个比对，直至命中或范围越界
    return NULL; //p越出左边界意味着区间内不含e，查找失败
 } //失败时，返回NULL
 ```


 ### 3.3.5 插入
 <font color = salmon size = 5>实现</font>

 ```cpp
 template <typename T> ListNodePosi<T> List<T>::insertAsFirst ( T const& e )
 {  _size++; return header->insertAsSucc ( e );  } //e当作首节点插入
 
 template <typename T> ListNodePosi<T> List<T>::insertAsLast ( T const& e )
 {  _size++; return trailer->insertAsPred ( e );  } //e当作末节点插入
 
 template <typename T> ListNodePosi<T> List<T>::insert ( ListNodePosi<T> p, T const& e )
 {  _size++; return p->insertAsSucc ( e );  } //e当作p的后继插入
 
 template <typename T> ListNodePosi<T> List<T>::insert ( T const& e, ListNodePosi<T> p )
 {  _size++; return p->insertAsPred ( e );  } //e当作p的前驱插入
```

将新元素e作为当前节点的前驱插至列表的过程

```cpp
 template <typename T> //将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
 ListNodePosi<T> ListNode<T>::insertAsPred ( T const& e ) {
    ListNodePosi<T> x = new ListNode ( e, pred, this ); //创建新节点
    pred->succ = x; pred = x; //设置正向链接
    return x; //返回新节点的位置
 }
```

后插入
```cpp
 template <typename T> //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
 ListNodePosi<T> ListNode<T>::insertAsSucc ( T const& e ) {
    ListNodePosi<T> x = new ListNode ( e, this, succ ); //创建新节点
    succ->pred = x; succ = x; //设置逆向链接
    return x; //返回新节点的位置
 }
```

### 3.3.6 基于复制的构造

<font color = salmon size = 6>copyNodes() </font>

```cpp
 template <typename T> //列表内部方法：复制列表中自位置p起的n项
 void List<T>::copyNodes ( ListNodePosi<T> p, int n ) { //p合法，且至少有n-1个真后继节点
    init(); //创建头、尾哨兵节点并做初始化
    while ( n-- ) { insertAsLast ( p->data ); p = p->succ; } //将起自p的n项依次作为末节点插入
 }
```

### 3.3.7 删除

```cpp
template <typename T> T List<T>:: remove(ListNodePPosi(T) p)
{
   T e = p-data;//备份待删除的节点数值
   p->pred->succ= p->succ;
   p->succ->pred = p->pred;//
   delete p;
   _size--;
   return e;//返回备份的数值
}
```

### 3.3.8 析构
释放资源，清除节点

```cpp
template <typename T> List<T>::~List()
{
   clear();
   delete header;
   delete trailer;
   }
```

### 3.3.9 唯一化

```cpp
 template <typename T> int List<T>::deduplicate() {
    int oldSize = _size; ListNodePosi<T> p = first();
    for ( Rank r = 0; p != trailer; p = p->succ ) //O(n)
       if ( ListNodePosi<T> q = find(p->data, r, p) )
          remove(q); //此时q与p雷同，但删除前者更为简明
       else r++; //r为无重前缀的长度
    return oldSize - _size; //删除元素总数
 }
 ```
总体执行时间为 $ O(n^2) $

### 3.3.10 遍历

<font color = salmon size = 5>实现</font>

```cpp
 template <typename T> void List<T>::traverse ( void ( *visit ) ( T& ) ) //借助函数指针机制遍历
 {  for ( ListNodePosi<T> p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
 
 template <typename T> template <typename VST> //元素类型、操作器
 void List<T>::traverse ( VST& visit ) //借助函数对象机制遍历
 {  for ( ListNodePosi<T> p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
 ```

 ## 3.4 有序列表

 ### 3.4.1 唯一化