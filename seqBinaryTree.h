//
// Created by 森 on 2021/11/6.
//

#ifndef HOMEWORK5_SEQBINARYTREE_H
#define HOMEWORK5_SEQBINARYTREE_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

template<class T>
class seqBinaryTree {
private:
    T* data;
    int maxSize;
    int curSize;

    void doubleSpace();

    void preOrder(int n, T flag);

    void midOrder(int n, T flag);

    void postOrder(int n, T flag);

public:
    explicit seqBinaryTree(int s = 10) : maxSize(s),curSize(0) { data = new T[maxSize]; }

    ~seqBinaryTree() { delete[]data; }

    void createTree(T flag);

    void preOrder(T flag);

    void midOrder(T flag);

    void postOrder(T flag);
};

template<class T>
void seqBinaryTree<T>::doubleSpace() {
    T* tmp = data;
    maxSize *= 2;
    data = new T[maxSize];
    for (int i = 0; i < maxSize; ++i) {
        data[i] = tmp[i];
    }
    delete tmp;
}

template<class T>
void seqBinaryTree<T>::createTree(T flag) {
    T tmp;
    int cnt = 0;
    cout << "输入节点：";
    while (cin >> tmp) {
        ++curSize;
        data[++cnt] = tmp;
        if (cnt == maxSize - 1)
            doubleSpace();
    }
    cout << "完成建树" << endl;
}

template<class T>
void seqBinaryTree<T>::preOrder(int n, T flag) {
    if (n <= curSize && data[n] != flag) {
        cout << data[n] << ' ';
        preOrder(2 * n, flag);
        preOrder(2 * n + 1, flag);
    }
    else
        return;
}

template<class T>
void seqBinaryTree<T>::preOrder(T flag) {
    cout << "前序遍历：";
    preOrder(1, flag);
    cout << endl;
}

template<class T>
void seqBinaryTree<T>::midOrder(int n, T flag) {
    if (n <= curSize && data[n] != flag) {
        midOrder(2 * n, flag);
        cout << data[n] << ' ';
        midOrder(2 * n + 1, flag);
    }
    else
        return;
}

template<class T>
void seqBinaryTree<T>::midOrder(T flag) {
    cout << "中序遍历：";
    midOrder(1, flag);
    cout << endl;
}

template<class T>
void seqBinaryTree<T>::postOrder(int n, T flag) {
    if (n <= curSize && data[n] != flag) {
        postOrder(2 * n, flag);
        postOrder(2 * n + 1, flag);
        cout << data[n] << ' ';
    }
    else
        return;
}

template<class T>
void seqBinaryTree<T>::postOrder(T flag) {
    cout << "后序遍历：";
    postOrder(1, flag);
    cout << endl;
}

#endif //HOMEWORK5_SEQBINARYTREE_H
