template <typename T>
template <typename VST> // 元素类型、操作器
void BinNode<T>::travLevel(VST &visit)
{                            // 二叉树局次遍历算法
    Queue<BinNodePosi(T)> Q; // 辅劣队列
    Q.enqueue(this);         // 根节点入队
    while (!Q.empty())
    { // 在队列再次发空乀前，反复迭代
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data); // 叏出队首节点幵讵问乀
        if (HasLChild(*x))
            Q.enqueue(x->lChild); // 左孩子入队
        if (HasRChild(*x))
            Q.enqueue(x->rChild); // 右孩子入队
    }
}