//
// Created by 森 on 2021/11/7.
//

#ifndef HOMEWORK5_CHILDSIBLINGTREE_H
#define HOMEWORK5_CHILDSIBLINGTREE_H

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

template<class T>
class childSiblingTree {
private:
    struct node {
        node *child, *sibling;
        T data;

        explicit node(T x, node *c = NULL, node *s = NULL) : data(x), child(c), sibling(s) {}
    };

    node *root;

    void clear(node *&tmp);

    int height(node *tmp);

    int size(node *tmp);

public:
    childSiblingTree() { root = NULL; }

    ~childSiblingTree();

    void createTree(T flag);

    int height();

    int size();
};

template<class T>
void childSiblingTree<T>::clear(node *&tmp) {
    if (tmp == NULL)
        return;
    else {
        clear(tmp->sibling);
        clear(tmp->child);
        delete tmp;
        tmp = NULL;
    }
}

template<class T>
childSiblingTree<T>::~childSiblingTree() {
    clear(root);
}

template<class T>
void childSiblingTree<T>::createTree(T flag) {
    T tmp, s, c;
    node *p;
    cout << "输入根节点：";
    cin >> tmp;
    root = new node(tmp);
    linkQueue<node *> que;
    que.enQueue(root);
    while (!que.isEmpty()) {
        p = que.deQueue();
        cout << "输入" << p->data << "的左孩子和右兄弟：";
        cin >> c >> s;
        if (s != flag) {
            que.enQueue(p->sibling = new node(s));
        }
        if (c != flag) {
            que.enQueue(p->child = new node(c));
        }
    }
}

template<class T>
int childSiblingTree<T>::size(node *tmp) {
    if (tmp == NULL)
        return 0;
    else
        return 1 + size(tmp->child) + size(tmp->sibling);
}

template<class T>
int childSiblingTree<T>::size() {
    return size(root);
}

template<class T>
int childSiblingTree<T>::height(node *tmp) {
    if (tmp == NULL)
        return 0;
    else {
        int maxH = 0;
        node *t = tmp->child;
        while (t != NULL) {
            maxH = (height(t) > maxH) ? height(t) : maxH;
            t = t->sibling;
        }
        return 1 + maxH;
    }
}

template<class T>
int childSiblingTree<T>::height() {
    return height(root);
}


#endif //HOMEWORK5_CHILDSIBLINGTREE_H
