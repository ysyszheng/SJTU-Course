#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "dynamicSearchTable.h"
#include "linkStack.h"

template <class KEY, class OTHER>
class BinarySearchTree : public dynamicSearchTable<KEY, OTHER> {
private:
  struct BinaryNode {
    SET<KEY, OTHER> data;
    BinaryNode *left, *right;

    BinaryNode(const SET<KEY, OTHER> &x, BinaryNode *lt = nullptr,
               BinaryNode *rt = nullptr)
        : data(x), left(lt), right(rt) {}
  };
  struct stNode {
    BinaryNode *node;
    int TimesPop;

    stNode(BinaryNode *t = nullptr) : node(t), TimesPop(0) {}
  };
  BinaryNode *root;

public:
  BinarySearchTree();
  ~BinarySearchTree();
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);
  // 1
  bool checkOrder() const;
  // 2
  void delLess(const KEY &x);
  void delGreater(const KEY &x);
  void delRange(const KEY &low, const KEY &high); // Closed interval
  // 6
  SET<KEY, OTHER> *findMax() const;
  SET<KEY, OTHER> *findMin() const;
  // 7
  SET<KEY, OTHER> *findILargest(int i) const;
  // 8
  SET<KEY, OTHER> *findISmallest(int i) const;

private:
  SET<KEY, OTHER> *find(const KEY &x, BinaryNode *t) const;
  void insert(const SET<KEY, OTHER> &x, BinaryNode *&t);
  void remove(const KEY &x, BinaryNode *&t);
  void makeEmpty(BinaryNode *t);
  // 1
  bool checkOrder(BinaryNode *t) const;
  // 2
  void delLess(const KEY &x, BinaryNode *&t);
  void delGreater(const KEY &x, BinaryNode *&t);
  void delRange(const KEY &low, const KEY &high, BinaryNode *&t);
};

template <typename KEY, typename OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::find(const KEY &x) const {
  return find(x, root);
}

template <typename KEY, typename OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::find(const KEY &x,
                                                    BinaryNode *t) const {
  if (t == nullptr || t->data.key == x)
    // return (SET<KEY, OTHER> *)t;
    return reinterpret_cast<SET<KEY, OTHER> *>(t);
  if (t->data.key > x)
    return find(x, t->left);
  else
    return find(x, t->right);
}

template <typename KEY, typename OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  insert(x, root);
}

template <typename KEY, typename OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x,
                                          BinaryNode *&t) {
  if (t == nullptr) {
    t = new BinaryNode(x);
    return;
  }
  if (x.key < t->data.key)
    insert(x, t->left);
  else
    insert(x, t->right);
}

template <typename KEY, typename OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY &x) {
  remove(x, root);
}

template <typename KEY, typename OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY &x, BinaryNode *&t) {
  if (t == nullptr)
    return;
  if (x < t->data.key)
    remove(x, t->left);
  else if (x > t->data.key)
    remove(x, t->right);
  else if (t->left != nullptr && t->right != nullptr) // x.key = t->data.key
  {
    BinaryNode *tmp = t->left;
    while (tmp->right != nullptr)
      tmp = tmp->right;
    t->data = tmp->data;
    remove(tmp->data.key, t->left);
  } else {
    BinaryNode *del = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete del;
  }
}

template <typename KEY, typename OTHER>
void BinarySearchTree<KEY, OTHER>::makeEmpty(BinaryNode *t) {
  if (t == nullptr)
    return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
}

template <typename KEY, typename OTHER>
BinarySearchTree<KEY, OTHER>::BinarySearchTree() {
  root = nullptr;
}

template <typename KEY, typename OTHER>
BinarySearchTree<KEY, OTHER>::~BinarySearchTree() {
  makeEmpty(root);
}

// problem 1

template <class KEY, class OTHER>
bool BinarySearchTree<KEY, OTHER>::checkOrder() const {
  return checkOrder(root);
}

template <class KEY, class OTHER>
bool BinarySearchTree<KEY, OTHER>::checkOrder(BinaryNode *t) const {
  if (t->left == nullptr && t->right == nullptr)
    return true;
  if (t->left == nullptr) {
    if (t->right->data.key > t->data.key)
      return true;
    else
      return false;
  }
  if (t->right == nullptr) {
    if (t->left->data.key < t->data.key)
      return true;
    else
      return false;
  }
  if (t->left->data.key < t->data.key && t->right->data.key > t->data.key)
    return true;
  else
    return false;
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delLess(const KEY &x) {
  delLess(x, root);
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delLess(const KEY &x, BinaryNode *&t) {
  if (t == nullptr)
    return;
  else if (t->data.key >= x)
    delLess(x, t->left);
  else if (t->data.key < x) {
    makeEmpty(t->left);
    delLess(x, t->right);
    BinaryNode *tmp = t;
    t = t->right;
    delete tmp;
  }
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delGreater(const KEY &x) {
  delGreater(x, root);
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delGreater(const KEY &x, BinaryNode *&t) {
  if (t == nullptr)
    return;
  else if (t->data.key <= x)
    delGreater(x, t->right);
  else if (t->data.key > x) {
    makeEmpty(t->right);
    delGreater(x, t->left);
    BinaryNode *tmp = t;
    t = t->left;
    delete tmp;
  }
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delRange(const KEY &low, const KEY &high) {
  delRange(low, high, root);
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::delRange(const KEY &low, const KEY &high,
                                            BinaryNode *&t) {
  if (t == nullptr)
    return;
  else if (t->data.key < low)
    delRange(low, high, t->right);
  else if (t->data.key > high)
    delRange(low, high, t->left);
  else {
    delRange(low, high, t->left);
    delRange(low, high, t->right);
    remove(t->data.key, t);
  }
}
template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::findMax() const {
  BinaryNode *tmp = root;
  if (tmp == nullptr)
    return nullptr;
  while (tmp->right != nullptr) {
    tmp = tmp->right;
  }
  return reinterpret_cast<SET<KEY, OTHER> *>(tmp);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::findMin() const {
  BinaryNode *tmp = root;
  if (tmp == nullptr)
    return nullptr;
  while (tmp->left != nullptr) {
    tmp = tmp->left;
  }
  return reinterpret_cast<SET<KEY, OTHER> *>(tmp);
}
template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::findILargest(int i) const {
  linkStack<stNode> st;
  stNode current(root);
  BinaryNode *tmp = nullptr;
  st.push(current);
  while (i > 0 && !st.isEmpty()) {
    current = st.pop();
    if (++current.TimesPop == 2) {
      i--;
      tmp = current.node;
      if (tmp->left != nullptr)
        st.push(stNode(tmp->left));
    } else {
      st.push(current);
      if (current.node->right != nullptr)
        st.push(stNode(current.node->right));
    }
  }
  if (i == 0)
    return reinterpret_cast<SET<KEY, OTHER> *>(tmp);
  else
    return nullptr;
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::findISmallest(int i) const {
  linkStack<stNode> st;
  stNode current(root);
  st.push(current);
  BinaryNode *tmp = nullptr;
  while (i > 0 && !st.isEmpty()) {
    current = st.pop();
    if (++current.TimesPop == 2) {
      i--;
      tmp = current.node;
      if (tmp->right != nullptr)
        st.push(tmp->right);
    } else {
      st.push(current);
      if (current.node->left != nullptr)
        st.push(current.node->left);
    }
  }
  if (i == 0)
    return reinterpret_cast<SET<KEY, OTHER> *>(tmp);
  else
    return nullptr;
}

#endif