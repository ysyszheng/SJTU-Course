#ifndef AVLTREE_H
#define AVLTREE_H

#include "dynamicSearchTable.h"

template <typename KEY, typename OTHER>
class AvlTree : public dynamicSearchTable<KEY, OTHER> {
private:
  struct AvlNode {
    SET<KEY, OTHER> data;
    AvlNode *left, *right;
    int height;

    AvlNode(const SET<KEY, OTHER> &x, AvlNode *lt = nullptr,
            AvlNode *rt = nullptr, int h = 1)
        : data(x), left(lt), right(rt), height(h) {}
  };
  AvlNode *root;

public:
  AvlTree() { root = nullptr; }
  ~AvlTree() { makeEmpty(root); }
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);

private:
  void insert(const SET<KEY, OTHER> &x, AvlNode *&t);
  bool remove(const KEY &x, AvlNode *&t);
  void makeEmpty(AvlNode *t);
  int height(AvlNode *t) { return t == nullptr ? 0 : t->height; }
  bool max(int a, int b) { return (a > b) ? a : b; }
  void LL(AvlNode *&t);
  void LR(AvlNode *&t);
  void RL(AvlNode *&t);
  void RR(AvlNode *&t);
  bool adjust(AvlNode *t, int subTree);
};

template <typename KEY, typename OTHER>
SET<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY &x) const {
  AvlNode *tmp = root;
  while (tmp != nullptr && tmp->data.key != x) {
    if (tmp->data.key < x)
      tmp = tmp->right;
    else
      tmp = tmp->left;
  }
  if (tmp == nullptr)
    return nullptr;
  else
    return reinterpret_cast<SET<KEY, OTHER> *>(tmp);
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode *&t) {
  AvlNode *tmp = t->left;
  t->left = tmp->right;
  tmp->right = t;
  t->height = max(height(t->left), height(t->right)) + 1;
  tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
  t = tmp;
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode *&t) {
  RR(t->left);
  LL(t);
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode *&t) {
  LL(t->right);
  RR(t);
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode *&t) {
  AvlNode *tmp = t->right;
  t->right = tmp->left;
  tmp->left = t;
  t->height = max(height(t->left), height(t->right)) + 1;
  tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
  t = tmp;
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  insert(x, root);
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AvlNode *&t) {
  if (t == nullptr)
    t = new AvlNode(x);
  else if (x.key < t->data.key) {
    insert(x, t->left);
    if (height(t->left) - height(t->right) == 2) {
      if (x.key < t->data.key)
        LL(t);
      else
        LR(t);
    }
  } else {
    insert(x, t->right);
    if (height(t->right) - height(t->left) == 2) {
      if (x.key > t->data.key)
        RR(t);
      else
        RL(t);
    }
  }
  t->height = max(height(t->left), height(t->right));
}

template <typename KEY, typename OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY &x) {
  remove(x, root);
}

template <typename KEY, typename OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlNode *&t) {
  if (t == nullptr)
    return true;
  if (x == t->data.key) {
    if (t->left == nullptr || t->right == nullptr) {
      AvlNode *oldNode = t;
      t = (t->left == nullptr) ? t->right : t->left;
      delete oldNode;
      return false;
    } else {
      AvlNode *tmp = t->left;
      while (tmp->left != nullptr) {
        tmp = tmp->left;
      }
      t->data = tmp->data;
      if (remove(tmp->data.key, t->right))
        return true;
      return adjust(t, 0);
    }
  }
  if (x < t->data.key) {
    if (remove(x, t->left))
      return true;
    return adjust(t, 0);
  }
  if (x > t->data.key) {
    if (remove(x, t->right))
      return true;
    return adjust(t, 1);
  }
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode *t, int subTree) {
  if (subTree) {
    if (height(t->left) == height(t->right)) {
      --t->height;
      return false;
    }
    if (height(t->left) > height(t->right))
      return true;
    if (height(t->left->right) > height(t->right->left)) {
      RL(t);
      return false;
    }
    RR(t);
    if (height(t->left) == height(t->right))
      return false;
    return true;
  } else {
    if (height(t->left) == height(t->right)) {
      --t->height;
      return false;
    }
    if (height(t->left) < height(t->right))
      return true;
    if (height(t->right->left) > height(t->right->right)) {
      LR(t);
      return false;
    }
    LL(t);
    if (height(t->left) == height(t->right))
      return false;
    return true;
  }
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(AvlNode *t) {
  if (t == nullptr)
    return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
}

#endif