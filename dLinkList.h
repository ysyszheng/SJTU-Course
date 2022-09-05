#ifndef DLINKLIST_H
#define DLINKLIST_H

#include <iostream>
#include "list.h"
using std::cout;
using std::endl;

template <class T>
class dLinkList : public list<T>
{
    // problem 8
    template <class T1>
    friend dLinkList<T1> operator+(const dLinkList<T1> &l1, const dLinkList<T1> &l2);

private:
    struct node
    {
        T data;
        node *prev, *next;

        node(const T &a, node *p, node *n) : data(a), prev(p), next(n) {}
        node() : prev(NULL), next(NULL){};
        ~node(){};
    };

    node *head, *tail;
    int currentLength;
    node *move(int idx) const;

public:
    dLinkList();
    ~dLinkList();
    void clear();
    int length() const;
    void insert(int idx, const T &a);
    void remove(int idx);
    int search(const T &a) const;
    T visit(int idx) const;
    void traverse() const;
    // problem 8
    dLinkList<T> &operator=(const dLinkList<T> &l);
};

template <class T>
dLinkList<T>::dLinkList()
{
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

template <class T>
dLinkList<T>::~dLinkList()
{
    clear();
    delete head;
    delete tail;
}

template <class T>
typename dLinkList<T>::node *dLinkList<T>::move(int idx) const
{
    node *p = head;
    while (idx-- >= 0)
        p = p->next;
    return p;
}

template <class T>
void dLinkList<T>::clear()
{
    head->next = tail;
    tail->prev = head;

    node *tmp = head->next;
    while (head->next != tail)
    {
        head->next = tmp->next;
        delete tmp;
        tmp = head->next;
    }

    currentLength = 0;
}

template <class T>
int dLinkList<T>::length() const
{
    return currentLength;
}

template <class T>
void dLinkList<T>::insert(int idx, const T &a)
{
    node *p = move(idx);
    p->prev = new node(a, p->prev, p);
    p->prev->prev->next = p->prev;
    currentLength++;
}

template <class T>
void dLinkList<T>::remove(int idx)
{
    node *p = move(idx);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    currentLength--;
}

template <class T>
int dLinkList<T>::search(const T &a) const
{
    node *p = head->next;
    int cnt = 0;
    while (p != tail && p->data != a)
    {
        p = p->next;
        cnt++;
    }
    if (p == tail)
        return -1;
    else
        return cnt;
}

template <class T>
T dLinkList<T>::visit(int idx) const
{
    return move(idx)->data;
}

template <class T>
void dLinkList<T>::traverse() const
{
    cout << endl;
    node *p = head->next;
    while (p != tail)
    {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

// problem 8
template <class T>
dLinkList<T> &dLinkList<T>::operator=(const dLinkList<T> &l)
{
    this->clear();

    node *p = (l.head)->next;
    node *q = head;

    while (p != l.tail)
    {
        q->next = new node(p->data, q, tail);
        q = q->next;
        tail->prev = q;
        p = p->next;
        currentLength++;
    }

    return *this;
}

// problem 8
template <class T>
dLinkList<T> operator+(const dLinkList<T> &l1, const dLinkList<T> &l2)
{
    dLinkList<T> l3;
    l3 = l1;
    typename dLinkList<T>::node *p = l2.head->next;
    int cnt = l3.currentLength;

    while (p != l2.tail)
    {
        l3.insert(cnt, p->data);
        cnt++;
        p = p->next;
    }

    return l3;
}

#endif