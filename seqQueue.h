//
// Created by 森 on 2021/10/28.
//

#ifndef HOMEWORK4_SEQQUEUE_H
#define HOMEWORK4_SEQQUEUE_H

#include "queue.h"

template<class T>
class seqQueue : public queue<T> {
private:
    T *elem;
    int maxSize;
    int rear;

    void doubleSpace();

public:
    explicit seqQueue(int n = 10);

    bool isEmpty() const;

    void enQueue(const T &x);

    T deQueue();

    T getHead() const;

    ~seqQueue();
};

template<class T>
void seqQueue<T>::doubleSpace() {
    T *tmp = elem;
    maxSize *= 2;
    elem = new T[maxSize];
    for (int i = 0; i <= rear; ++i) {
        elem[i] = tmp[i];
    }
    delete tmp;
}

template<class T>
seqQueue<T>::seqQueue(int n) {
    maxSize = n;
    elem = new T[n];
    rear = -1;
}

template<class T>
bool seqQueue<T>::isEmpty() const {
    return rear == -1;
}

template<class T>
void seqQueue<T>::enQueue(const T &x) {
    if (rear == maxSize - 1) {
        doubleSpace();
    }
    elem[++rear] = x;
}

template<class T>
T seqQueue<T>::deQueue() {
    T res = elem[0];
    for (int i = 0; i < rear; ++i) {
        elem[i] = elem[i + 1];
    }
    rear--;
    return res;
}

template<class T>
T seqQueue<T>::getHead() const {
    return elem[0];
}

template<class T>
seqQueue<T>::~seqQueue() {
    delete elem;
    rear = -1;
}


#endif //HOMEWORK4_SEQQUEUE_H
