//
// Created by 森 on 2021/10/28.
//

#ifndef HOMEWORK4_QUEUE_H
#define HOMEWORK4_QUEUE_H

template<class T>
class queue {
public:
    virtual bool isEmpty() const = 0;

    virtual void enQueue(const T &x) = 0;

    virtual T deQueue() = 0;

    virtual T getHead() const = 0;

    virtual ~queue() = default;
};

#endif //HOMEWORK4_QUEUE_H
