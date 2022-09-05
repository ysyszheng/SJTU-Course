//
// Created by 森 on 2021/10/29.
//

#ifndef HOMEWORK5_BINARYTREE_H
#define HOMEWORK5_BINARYTREE_H

#include "bTree.h"
#include "linkQueue.h"
#include "linkStack.h"
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <class T> class binaryTree : public bTree<T> {
  template <class type>
  friend void printTree(const binaryTree<type> &t, type flag);

  template <class type>
  friend bool operator==(const binaryTree<type> &t1,
                         const binaryTree<type> &t2);

private:
  struct node {
    T data;
    node *left;
    node *right;

    explicit node() : left(NULL), right(NULL) {}

    explicit node(T x, node *l = NULL, node *r = NULL)
        : data(x), left(l), right(r) {}

    ~node() = default;
  };

  struct stNode {
    node *ptr;
    int timesPop;

    explicit stNode(node *tmp) : ptr(tmp), timesPop(0) {}

    stNode() = default;
  };

  node *root;

  node *find(T x, node *t) const;

  void clear(node *&t);

  void preOrder(node *t) const;

  void midOrder(node *t) const;

  void postOrder(node *t) const;

  int height(node *tmp) const;

  int size(node *tmp) const;

  void changeLeftRight(node *tmp);

  int degree2(node *tmp);

  bool isEqual(node *t1, node *t2);

  bool isImage(node *t1, node *t2);

public:
  binaryTree() : root(NULL) {}

  explicit binaryTree(T x) { root = new node(x); }

  ~binaryTree();

  void clear();

  bool isEmpty() const;

  T Root(T flag) const;

  T lchild(T x, T flag) const;

  T rchild(T x, T flag) const;

  void delLeft(T x);

  void delRight(T x);

  void preOrder() const;

  void midOrder() const;

  void postOrder() const;

  void preOrder_stack() const;

  void midOrder_stack() const;

  void postOrder_stack() const;

  void levelOrder() const;

  void createTree(T flag);

  T parent(T x, T flag) const { return flag; }

  int height() const;

  int size() const;

  void changeLeftRight();

  int degree2();

  bool isFull();

  bool isCompleted();

  bool isImage(const binaryTree<T> &t);
};

template <class T> binaryTree<T>::~binaryTree() { clear(); }

template <class T>
typename binaryTree<T>::node *
binaryTree<T>::find(T x, typename binaryTree<T>::node *t) const { // todo
  if (t == NULL)
    return NULL;
  if (t->data == x)
    return t;
  if (find(x, t->left))
    return find(x, t->left);
  else
    return find(x, t->right);
}

template <class T> void binaryTree<T>::clear(binaryTree::node *&t) {
  if (t == NULL)
    return;
  else {
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
  }
}

template <class T> void binaryTree<T>::preOrder(binaryTree::node *t) const {
  cout << t->data << ' ';
  if (t->left != NULL)
    preOrder(t->left);
  if (t->right != NULL)
    preOrder(t->right);
}

template <class T> void binaryTree<T>::midOrder(binaryTree::node *t) const {
  if (t->left != NULL)
    midOrder(t->left);
  cout << t->data << ' ';
  if (t->right != NULL)
    midOrder(t->right);
}

template <class T> void binaryTree<T>::postOrder(binaryTree::node *t) const {
  if (t->left != NULL)
    postOrder(t->left);
  if (t->right != NULL)
    postOrder(t->right);
  cout << t->data << ' ';
}

template <class T> void binaryTree<T>::clear() { clear(root); }

template <class T> bool binaryTree<T>::isEmpty() const { return root == NULL; }

template <class T> T binaryTree<T>::Root(T flag) const {
  if (root == NULL)
    return flag;
  else
    return root->data;
}

template <class T> T binaryTree<T>::lchild(T x, T flag) const {
  node *t = find(x, root);
  if (t == NULL || t->left == NULL)
    return flag;
  else
    return t->left->data;
}

template <class T> T binaryTree<T>::rchild(T x, T flag) const {
  node *t = find(x, root);
  if (t == NULL || t->right == NULL)
    return flag;
  else
    return t->right->data;
}

template <class T> void binaryTree<T>::delLeft(T x) {
  node *t = find(x, root);
  if (t == NULL || t->left == NULL)
    return;
  else
    clear(t->left);
}

template <class T> void binaryTree<T>::delRight(T x) {
  node *t = find(x, root);
  if (t == NULL || t->right == NULL)
    return;
  else
    clear(t->right);
}

template <class T> void binaryTree<T>::preOrder() const {
  cout << "前序遍历：";
  preOrder(root);
  cout << endl;
}

template <class T> void binaryTree<T>::midOrder() const {
  cout << "中序遍历：";
  midOrder(root);
  cout << endl;
}

template <class T> void binaryTree<T>::postOrder() const {
  cout << "后序遍历：";
  postOrder(root);
  cout << endl;
}

template <class T> void binaryTree<T>::preOrder_stack() const {
  cout << "前序遍历 栈实现";
  linkStack<node *> st;
  st.push(root);
  node *tmp;
  while (!st.isEmpty()) {
    tmp = st.pop();
    cout << tmp->data << ' ';
    if (tmp->right)
      st.push(tmp->right);
    if (tmp->left)
      st.push(tmp->left);
  }
  cout << endl;
}

template <class T> void binaryTree<T>::midOrder_stack() const {
  cout << "中序遍历 栈实现";
  linkStack<stNode> st;
  st.push(stNode(root));
  stNode tmp;
  while (!st.isEmpty()) {
    tmp = st.pop();
    if (++tmp.timesPop == 2) {
      cout << tmp.ptr->data << ' ';
      if (tmp.ptr->right)
        st.push(stNode(tmp.ptr->right));
    } else {
      st.push(tmp);
      if (tmp.ptr->left)
        st.push(stNode(tmp.ptr->left));
    }
  }
  cout << endl;
}

template <class T> void binaryTree<T>::postOrder_stack() const {
  cout << "后序遍历 栈实现";
  linkStack<stNode> st;
  st.push(stNode(root));
  stNode tmp;
  while (!st.isEmpty()) {
    tmp = st.pop();
    if (++tmp.timesPop == 2) {
      cout << tmp.ptr->data << ' ';
    } else {
      st.push(tmp);
      if (tmp.ptr->right)
        st.push(stNode(tmp.ptr->right));
      if (tmp.ptr->left)
        st.push(stNode(tmp.ptr->left));
    }
  }
  cout << endl;
}

template <class T> void binaryTree<T>::levelOrder() const {
  cout << "层次遍历：";
  linkQueue<node *> que;
  if (root == NULL)
    return;

  que.enQueue(root);

  while (!que.isEmpty()) {
    node *tmp = que.deQueue();
    cout << tmp->data << ' ';
    if (tmp->left)
      que.enQueue(tmp->left);
    if (tmp->right)
      que.enQueue(tmp->right);
  }
  cout << endl;
}

template <class T> void binaryTree<T>::createTree(T flag) {
  linkQueue<node *> que;
  node *tmp;
  T x, lc, rc;
  cout << "输入根节点：";
  cin >> x;
  que.enQueue(root = new node(x));

  while (!que.isEmpty()) {
    tmp = que.deQueue();
    cout << "输入" << tmp->data << "的两个儿子（" << flag << "表示空节点）：";
    cin >> lc >> rc;
    if (lc != flag)
      que.enQueue(tmp->left = new node(lc));
    if (rc != flag)
      que.enQueue(tmp->right = new node(rc));
  }
  cout << "完成建树！" << endl;
}

template <class T> void printTree(const binaryTree<T> &t, T flag) {
  linkQueue<typename binaryTree<T>::node *> que;
  typename binaryTree<T>::node *tmp;
  T lc, rc;
  if (t.root == NULL)
    return;
  que.enQueue(t.root);
  while (!que.isEmpty()) {
    tmp = que.deQueue();
    lc = (tmp->left == NULL) ? flag : tmp->left->data;
    rc = (tmp->right == NULL) ? flag : tmp->right->data;
    cout << tmp->data << ' ' << lc << ' ' << rc << endl;
    if (lc != flag)
      que.enQueue(tmp->left);
    if (rc != flag)
      que.enQueue(tmp->right);
  }
}

template <class T> int binaryTree<T>::height(node *tmp) const {
  if (tmp == NULL)
    return 0;
  return ((height(tmp->left) > height(tmp->right)) ? height(tmp->left)
                                                   : height(tmp->right)) +
         1;
}

template <class T> int binaryTree<T>::size(node *tmp) const {
  if (tmp == NULL)
    return 0;
  return size(tmp->left) + size(tmp->right) + 1;
}

template <class T> int binaryTree<T>::height() const { return height(root); }

template <class T> int binaryTree<T>::size() const { return size(root); }

template <class T> void binaryTree<T>::changeLeftRight(node *tmp) {
  if (tmp == NULL)
    return;
  else {
    node *n = tmp->left;
    tmp->left = tmp->right;
    tmp->right = n;
    changeLeftRight(tmp->left);
    changeLeftRight(tmp->right);
  }
}

template <class T> void binaryTree<T>::changeLeftRight() {
  return changeLeftRight(root);
}

template <class T> int binaryTree<T>::degree2(node *tmp) {
  if (tmp == NULL)
    return 0;
  else {
    int n = (tmp->left != NULL && tmp->right != NULL) ? 1 : 0;
    return n + degree2(tmp->left) + degree2(tmp->right);
  }
}

template <class T> int binaryTree<T>::degree2() { return degree2(root); }

template <class T> bool binaryTree<T>::isFull() {
  return this->size() == pow(2, this->height()) - 1;
}

// template<class T>
// bool binaryTree<T>::isCompleted() {
//     int s = 0;
//     int threshold = pow(2, this->height() - 2) - 1;
//     linkQueue<node *> que;
//     que.enQueue(root);
//     while (!que.isEmpty()) {
//         s++;
//         node *t = que.deQueue();
//         if (s <= threshold && (t->left == NULL || t->right == NULL))
//             return false;
//         if (t->left != NULL)
//             que.enQueue(t->left);
//         if (t->right != NULL)
//             que.enQueue(t->right);
//     }
//     return true;
// }

template <class T> bool binaryTree<T>::isCompleted() {
  linkQueue<node *> que;
  node *p;
  que.enQueue(root);
  bool flag = true;

  while (!que.isEmpty()) {
    if (p->left != nullptr && p->right != nullptr) {
      if (!flag)
        return false;
      que.enQueue(p->left);
      que.enQueue(p->right);
    } else {
      flag = false;
      if (p->left != nullptr)
        que.enQueue(p->left);
      if (p->right != nullptr)
        que.enQueue(p->right);
    }
  }
  return true;
}

template <class T> bool binaryTree<T>::isEqual(node *t1, node *t2) {
  binaryTree<T> t;
  if (t1 == NULL && t2 == NULL)
    return true;
  else if (t1 != NULL && t2 != NULL && t1->data == t2->data)
    return t.isEqual(t1->left, t2->left) && t.isEqual(t1->right, t2->right);
  else
    return false;
}

template <class T>
bool operator==(const binaryTree<T> &t1, const binaryTree<T> &t2) {
  binaryTree<T> t;
  return t.isEqual(t1.root, t2.root);
}

template <class T>
bool binaryTree<T>::isImage(binaryTree::node *t1, binaryTree::node *t2) {
  binaryTree<T> t;
  if (t1 == NULL && t2 == NULL)
    return true;
  else if (t1 != NULL && t2 != NULL && t1->data == t2->data)
    return t.isImage(t1->left, t2->right) && t.isImage(t1->right, t2->left);
  else
    return false;
}

template <class T> bool binaryTree<T>::isImage(const binaryTree<T> &t) {
  binaryTree<T> tmp;
  return tmp.isImage(this->root, t.root);
}

#endif // HOMEWORK5_BINARYTREE_H
