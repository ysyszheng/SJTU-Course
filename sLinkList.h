#ifndef SLINKLIST_H
#define SLINKLIST_H

#include <iostream>
#include "list.h"
using std::cout;
using std::endl;

template <class T>
class sLinkList : public list<T>
{
    // problem 7
    template <class T1>
    friend sLinkList<T1> operator+(const sLinkList<T1> &l1, const sLinkList<T1> &l2);
    // problem 10
    template <class T1>
    friend typename sLinkList<T1>::node *findSuffix(const sLinkList<T1> &l1, const sLinkList<T1> &l2);

private:
    struct node
    {
        T data;
        node *next;

        node(const T &a, node *n = NULL) : data(a), next(n){};
        node() : next(NULL){};
        ~node(){};
    };
    int currentLength;
    node *head;
    node *move(int idx) const;

public:
    sLinkList();
    ~sLinkList();
    void clear();
    int length() const;
    void insert(int idx, const T &a);
    void remove(int idx);
    int search(const T &a) const;
    T visit(int idx) const;
    void traverse() const;
    // problem 1
    void erase(int x, int y);
    // problem 6
    void reverse();
    // problem 7
    sLinkList<T> &operator=(const sLinkList<T> &l);
};

template <class T>
typename sLinkList<T>::node *sLinkList<T>::move(int idx) const //从0开始计数
{
    node *p = head;
    while (idx-- >= 0)
    {
        p = p->next;
    }
    return p;
}

template <class T>
sLinkList<T>::sLinkList()
{
    head = new node;
    currentLength = 0;
}

template <class T>
sLinkList<T>::~sLinkList()
{
    clear();
    delete head;
}

template <class T>
void sLinkList<T>::clear()
{
    while (head->next != NULL)
    {
        node *p = head->next;
        head->next = p->next;
        delete p;
    }
    currentLength = 0;
}

template <class T>
int sLinkList<T>::length() const
{
    return currentLength;
}

template <class T>
void sLinkList<T>::insert(int idx, const T &a)
{
    node *p = move(idx - 1);
    p->next = new node(a, p->next);
    ++currentLength;
}

template <class T>
void sLinkList<T>::remove(int idx)
{
    node *p = move(idx - 1);
    node *delp = p->next;
    p->next = delp->next;
    delete delp;
    currentLength--;
}

template <class T>
int sLinkList<T>::search(const T &a) const //头结点序号为-1
{
    node *p = head->next;
    int idx = 0;

    while (p != NULL && p->data != a)
    {
        p = p->next;
        idx++;
    }

    if (p == NULL)
        return -1;
    else
        return idx;
}

template <class T>
T sLinkList<T>::visit(int idx) const
{
    return move(idx)->data;
}

template <class T>
void sLinkList<T>::traverse() const
{
    node *p = head->next;
    cout << endl;

    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
}

// problem 1
template <class T>
void sLinkList<T>::erase(int x, int y)
{
    node *st = move(x - 1);
    node *en = move(y + 1);
    while (st->next != en)
    {
        node *q = st->next;
        st->next = q->next;
        delete q;
    }
}

// problem 6
template <class T>
void sLinkList<T>::reverse()
{
    node *p = head->next;
    head->next = NULL;

    while (p != NULL)
    {
        this->insert(0, p->data);
        node *tmp = p;
        p = p->next;
        delete tmp;
    }
}

// problem 7
template <class T>
sLinkList<T> &sLinkList<T>::operator=(const sLinkList<T> &l)
{
    this->clear();

    node *p = (l.head)->next;
    node *q = head;

    while (p != NULL)
    {
        q->next = new node(p->data, NULL);
        q = q->next;
        p = p->next;
        currentLength++;
    }

    return *this;
}

// problem 7
template <class T>
sLinkList<T> operator+(const sLinkList<T> &l1, const sLinkList<T> &l2)
{
    sLinkList<T> l3;
    l3 = l1;
    typename sLinkList<T>::node *p = l2.head->next;
    int cnt = l3.currentLength;

    while (p != NULL)
    {
        l3.insert(cnt, p->data);
        cnt++;
        p = p->next;
    }

    return l3;
}

// problem 10
template <class T>
typename sLinkList<T>::node *findSuffix(const sLinkList<T> &l1, const sLinkList<T> &l2)
{
    int len1 = l1.length(), len2 = l2.length();
    if (len1 > len2)
    {
        int st = len1 - len2;
        typename sLinkList<T>::node *p = l1.move(st), *q = (l2.head)->next;
        typename sLinkList<T>::node *tmp = p;
        while (p != NULL)
        {
            if (p->data != q->data)
                tmp = p->next;
            p = p->next;
            q = q->next;
        }
        return tmp;
    }
    else
    {
        int st = len2 - len1;
        typename sLinkList<T>::node *p = l2.move(st), *q = (l1.head)->next;
        typename sLinkList<T>::node *tmp = p;
        while (p != NULL)
        {
            if (p->data != q->data)
                tmp = p->next;
            p = p->next;
            q = q->next;
        }
        return tmp;
    }
}

#endif