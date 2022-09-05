//
// Created by 森 on 2021/10/29.
//

#ifndef HOMEWORK5_BTREE_H
#define HOMEWORK5_BTREE_H

template<class T>
class bTree {
public:
    virtual void clear() = 0;

    virtual bool isEmpty() const = 0;

    virtual T Root(T flag) const = 0;

    virtual T parent(T x, T flag) const = 0;

    virtual T lchild(T x, T flag) const = 0;

    virtual T rchild(T x, T flag) const = 0;

    virtual void delLeft(T x) = 0;

    virtual void delRight(T x) = 0;

    virtual void preOrder() const = 0;

    virtual void midOrder() const = 0;

    virtual void postOrder() const = 0;

    virtual void levelOrder() const = 0;
};

#endif //HOMEWORK5_BTREE_H
