//
// Created by 森 on 2021/10/28.
//

#ifndef HOMEWORK4_LINKQUEUE_H
#define HOMEWORK4_LINKQUEUE_H

#include "queue.h"

template <class T> class linkQueue : public queue<T> {
private:
  struct node {
    T data;
    node *next;

    explicit node(T a, node *n = nullptr) : data(a), next(n){};

    node() = default;
  };

  node *head, *tail;

public:
  linkQueue();

  bool isEmpty() const;

  void enQueue(const T &x);

  T deQueue();

  T getHead() const;

  ~linkQueue();
};

template <class T> linkQueue<T>::linkQueue() { head = tail = nullptr; }

template <class T> bool linkQueue<T>::isEmpty() const {
  return head == nullptr;
}

template <class T> void linkQueue<T>::enQueue(const T &x) {
  if (head == nullptr) {
    head = tail = new node(x);
  } else {
    tail = tail->next = new node(x);
  }
}

template <class T> T linkQueue<T>::deQueue() {
  T res = head->data;
  node *tmp = head;
  head = head->next;
  delete tmp;
  if (head == nullptr) {
    tail = nullptr;
  }

  return res;
}

template <class T> T linkQueue<T>::getHead() const { return head->data; }

template <class T> linkQueue<T>::~linkQueue<T>() {
  while (head != nullptr) {
    node *tmp = head;
    head = head->next;
    delete tmp;
  }
}

#endif // HOMEWORK4_LINKQUEUE_H
