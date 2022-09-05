//
// Created by 森 on 2021/10/16.
//

#ifndef HOMEWORK3_LINKSTACK_H
#define HOMEWORK3_LINKSTACK_H

#include "stack.h"

template <class T> class linkStack : public stack<T> {
private:
  struct node {
    T data;
    node *next;

    explicit node(const T &x, node *N = nullptr) : data(x), next(N){};

    ~node() = default;
  };

  node *top_p;

public:
  linkStack();

  ~linkStack();

  bool isEmpty();

  void push(const T &x);

  T pop();

  T top() const;
};

template <class T> linkStack<T>::linkStack() { top_p = nullptr; }

template <class T> linkStack<T>::~linkStack() {
  node *tmp;
  while (top_p != nullptr) {
    tmp = top_p;
    top_p = top_p->next;
    delete tmp;
  }
}

template <class T> bool linkStack<T>::isEmpty() { return top_p == nullptr; }

template <class T> void linkStack<T>::push(const T &x) {
  top_p = new node(x, top_p);
}

template <class T> T linkStack<T>::pop() {
  node *tmp = top_p;
  T res = top_p->data;
  top_p = top_p->next;
  delete tmp;
  return res;
}

template <class T> T linkStack<T>::top() const { return top_p->data; }

#endif // HOMEWORK3_LINKSTACK_H
