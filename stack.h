//
// Created by 森 on 2021/10/16.
//

#ifndef HOMEWORK3_STACK_H
#define HOMEWORK3_STACK_H

template<class T>
class stack {
public:
    virtual bool isEmpty() = 0;

    virtual void push(const T &x) = 0;

    virtual T pop() = 0;

    virtual T top() const = 0;

    virtual ~stack() = default;
};

#endif //HOMEWORK3_STACK_H
