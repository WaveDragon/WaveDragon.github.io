---
title: Algorithms-DengNo5
author: WaveDragon
date: 2023-1-14 11:11:00 +0800
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

# 第五章 二叉树
基于数组的结构，可以在常数时间内找到对象，但是修改消耗线性时间
基于链表的结构，可以在常数时间修改，但是查找要消耗线性时间
二叉树属于半线性结构

## 5.1 二叉及其表示

### 5.1.1 树

#### 深度与层次

根节点深度为0， v通过树根沿途所经过的每个节点都是其足下，v是他们的后代
高一层称为父亲，低一层为孩子。v的孩子总数，称为其度数或度degree，记作deg(v)。无孩子的节点称为叶节点，包括根在内的其余节点称为内部节点。

v所有的后代及其之间的联边称作子树，记作subtree(v)

#### 高度
树T中所有节点深度的最大值称为高度
本书约定，仅含单个节点的树高度为0，空树高度为-1

### 5.1.2 二叉树

二叉树每个节点的度数均不超过2

同一父节点的孩子都可以左右区分，此时亦可以称为有序二叉树，本树所提树默认都是有序的

特别地，不含一度节点的二叉树称为真二叉树。

### 5.1.3 多叉树

每个节点的孩子不超过k个的有根树，称作k叉树

有序多叉树=二叉树

当然，为了保证作为多叉树特例的二叉树有足够的能力表示任何一棵多叉树，我们只需给多叉树增加一项约束条件同一节点的所有孩子之间必须具有某一线性次序。仿照有序二叉树的定义，凡符合这一条件的多叉树也称作有序树（ordered tree）。幸运的是，这一附加条件在实际应用问题中往往自然满足。以互联网域名系统所对应的多叉树为例，其中同一域名下的分支通常即按照字典序排列。

#### 长子+兄弟

### 5.1.5

## 5.2 编码树

### 5.2.1 二进制编码

### 生成编码表

前缀无歧义编码，简称PFC编码

### 5.2.2 二叉编码树

PFC编码树

## 5.3 二叉树的实现

```cpp
#define BinNodePosi(T) BinNode<T> *         // 节点位置
#define stature(p) ((p) ? (p)->height : -1) // 节点高度（与“空树高度为-1”癿约定相统一）
typedef enum
{
    RB_RED,
    RB_BLACK
} RBColor; // 节点颜色

template <typename T>
struct BinNode
{ // 二叉树节点模板类
    // 成员（为简化描述起见统一开放，读者可根据需要迕一步封装）
    T data; // 数值
    BinNodePosi(T) parent;
    BinNodePosi(T) lChild;
    BinNodePosi(T) rChild; // 父节点及左、右孩子
    int height;            // 高度（通用）
    int npl;               // Null Path Length（左式堆，也可直接用height代替）
    RBColor color;         // 颜色（红黑树）
    // 极造函数
    BinNode() : parent(NULL), lChild(NULL), rChild(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
            int h = 0, int l = 1, RBColor c = RB_RED)
        : data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {}
    // 操作接口
    int size();                           // 统计弼前节点后代总数，亦即以其为根癿子树癿觃模
    BinNodePosi(T) insertAsLC(T const &); // 作为弼前节点癿左孩子揑入新节点
    BinNodePosi(T) insertAsRC(T const &); // 作为弼前节点癿右孩子揑入新节点
    BinNodePosi(T) succ();                // 叏弼前节点癿直接后继
    template <typename VST>
    void travLevel(VST &); // 子树局次遍历
    template <typename VST>
    void travPre(VST &); // 子树先序遍历
    template <typename VST>
    void travIn(VST &); // 子树中序遍历
    template <typename VST>
    void travPost(VST &); // 子树后序遍历
    // 比较器、刞等器（各列其一，其余自行补充）
    bool operator<(BinNode const &bn) { return data < bn.data; }   // 小亍
    bool operator==(BinNode const &bn) { return data == bn.data; } // 等亍
};

```

## 5.4 遍历


二叉树本身并不具有天然的全局次序，故为了实现遍历，需要在各节点与其孩子之间约定某种局部次序，间接地定义某种全局次序。

节点左孩子右孩子分别记作 V L R
则局部访问次序有 VLR，LVR和LRV三种。根据节点V在其中的访问次序，可以分别称为先序遍历，中序遍历和后序遍历。

### 递归遍历

先序递归版本
```cpp
template <typename T, typename VST> // 元素类型、操作器
void travPre_R(BinNodePosi(T) x, VST &visit)
{ // 二叉树先序遍历算法（逑弻版）
    if (!x)
        return;
    visit(x->data);
    travPre_R(x->lChild, visit);
    travPre_R(x->rChild, visit);
}
```

后序遍历与中序遍历类似

### <font color = Salmon> 迭代版遍历</font>

#### 先序遍历

<font color = salmon>(1)</font>

先序遍历递归版本 针对右子树的递归属于尾递归，参照消除尾递归的一般方法，可以改写为迭代版。
[版本1](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travpreorder_i1.h.htm)

<font color = salmon>(2)</font>

![图05-32 先序遍历过程：先沿左侧通路自顶而下访问沿途节点，再自底而上依次遍历这些节点的右子树](https://user-images.githubusercontent.com/78013131/212477813-e2bcda8a-7968-4efa-8b33-5f8c4ba24809.png)

先序遍历序列可分解为两段：沿最左侧通路自顶而下访问的各节点，以及自底而上遍历的对应右子树。基于对先序遍历序列的这一理解，可以导出以下迭代式先序遍历算法。

[版本2](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travpreorder_i2.h.htm)

#### 中序遍历

<font color = salmon>(1)</font>

沿最左侧通路自底而上，以沿途各节点为界，中序遍历序列可分解为d + 1段。
如图5.19左侧所示，各段均包括访问来自最左侧通路的某一节点Lk，以及遍历其右子树Tk。



![图05-33.中序遍历过程：顺着左侧通路，自底而上依次访问沿途各节点及其右子树](https://user-images.githubusercontent.com/78013131/212478012-fdfe6694-1bd2-4cdc-9282-bc1bf55d6054.png)

[版本1](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travinorder_i1.h.htm)

<font color = salmon>(2)</font>

使用后继succ()
[版本2](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travinorder_i2.h.htm)

[版本3](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travinorder_i3.h.htm)

[版本4](https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/bintree/binnode_travinorder_i4.h.htm)


#### 后序遍历

