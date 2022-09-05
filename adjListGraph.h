#ifndef ADJLISTGRAPH_H
#define ADJLISTGRAPH_H

#include "graph.h"
#include "linkQueue.h"
#include <iostream>

template <typename TypeOfVer, typename TypeOfEdge>
class adjListGraph : public graph<TypeOfVer, TypeOfEdge> {
private:
  struct edgeNode {
    int end;
    TypeOfEdge weight;
    edgeNode *next;
    edgeNode(int e, TypeOfEdge w, edgeNode *n = nullptr)
        : end(e), weight(w), next(n) {}
  };
  struct verNode {
    TypeOfVer ver;
    edgeNode *head;
    verNode(edgeNode *h = nullptr) : head(h) {}
  };

  verNode *verList;
  int find(TypeOfVer v) const {
    for (int i = 0; i < this->Vers; i++) {
      if (verList[i].ver == v)
        return i;
    }
    return -1;
  }
  void find(int start, int M, int curNode, bool visited[], int path[]) const;
  void topoSort_all(int degree[], int path[], bool visited[],
                    int noOfNodes) const;

public:
  adjListGraph(int vSize, const TypeOfVer d[]);
  void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void remove(TypeOfVer x, TypeOfVer y);
  bool exists(TypeOfVer x, TypeOfVer y) const;
  ~adjListGraph();
  //
  bool isDAG() const;
  void find(TypeOfVer start, int M) const;
  bool isExistPath(TypeOfVer x, TypeOfVer y) const;
  //
  void topologicalSort() const;
  void findSCC() const;
  void EulerPath() const;
  void dfsSCC() const;
  void topoSort_all() const;
  void findAllVertex(TypeOfVer source, int M) const;
};

template <typename TypeOfVer, typename TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize,
                                                  const TypeOfVer d[]) {
  this->Vers = vSize;
  this->Edges = 0;
  verList = new verNode[vSize];
  for (int i = 0; i < vSize; i++)
    verList[i].ver = d[i];
}

template <typename TypeOfVer, typename TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
  edgeNode *p;
  for (int i = 0; i < this->Vers; i++)
    while ((p = verList[i].head) != nullptr) {
      verList[i].head = p->next;
      delete p;
    }

  delete[] verList;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y,
                                                 TypeOfEdge w) {
  int u = find(x), v = find(y);
  verList[u].head = new edgeNode(v, w, verList[u].head);
  ++this->Edges;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
  int u = find(x), v = find(y);
  edgeNode *p = verList[u].head;
  if (p == nullptr)
    return;
  if (p->end == v) {
    verList[u].head = verList[u].head->next;
    delete p;
    --this->Edges;
  }
  while (p->next != nullptr && p->next->end != v)
    p = p->next;
  if (p->next != nullptr) {
    edgeNode *q = p->next;
    p->next = q->next;
    delete q;
    --this->Edges;
  }
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exists(TypeOfVer x,
                                                 TypeOfVer y) const {
  int u = find(x), v = find(y);
  edgeNode *p = verList[u].head;
  while (p != nullptr && p->end != v)
    p = p->next;
  if (p != nullptr)
    return true;
  else
    return false;
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isDAG() const {
  edgeNode *p;
  linkQueue<int> que;
  int curVer;
  for (int i = 0; i < this->Vers; i++) {
    bool visited[this->Vers] = {false};
    // for (int i = 0; i < this->Vers; i++)
    //   visited[this->Vers] = false;
    que.enQueue(i);
    while (!que.isEmpty()) {
      curVer = que.deQueue();
      if (visited[curVer] == true)
        continue;
      visited[curVer] = true;
      for (p = verList[curVer].head; p != nullptr; p = p->next) {
        if (p->end == i)
          return true;
        if (visited[p->end] == false)
          que.enQueue(p->end);
      }
    }
  }
  return false;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::find(TypeOfVer start, int M) const {
  int u = find(start);
  bool *visited = new bool[this->Vers];
  for (int i = 0; i < this->Vers; i++)
    visited[i] = false;
  int *path = new int[M + 1];
  int curNode = 0; // 0~M
  // M edges -> M+1 vers
  find(u, M + 1, curNode, visited, path);
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::find(int start, int M, int curNode,
                                               bool visited[],
                                               int path[]) const {
  edgeNode *p = verList[start].head;
  visited[start] = true;
  path[curNode] = start;

  // 递归终止 & 输出
  if (curNode + 1 == M) {
    for (int i = 0; i < M; ++i)
      std::cout << verList[path[i]].ver << ' ';
    std::cout << std::endl;

    visited[start] = false;
    return;
  }

  while (p != nullptr) {
    if (visited[p->end] == false)
      find(p->end, M, curNode + 1, visited, path);
    p = p->next;
  }

  visited[start] = false;
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isExistPath(TypeOfVer x,
                                                      TypeOfVer y) const {
  int u = find(x), v = find(y);
  edgeNode *p;
  linkQueue<int> que;
  int curVer;
  bool visited[this->Vers] = {false};
  que.enQueue(u);
  while (!que.isEmpty()) {
    curVer = que.deQueue();
    if (visited[curVer] == true)
      continue;
    visited[curVer] = true;
    for (p = verList[curVer].head; p != nullptr; p = p->next) {
      if (p->end == v)
        return true;
      if (visited[p->end] == false)
        que.enQueue(p->end);
    }
  }
  return false;
}

template <typename TypeOfVer, typename TypeOfEdge> // O(|V|^2)
void adjListGraph<TypeOfVer, TypeOfEdge>::topologicalSort() const {
  if (this->isDAG()) {
    std::cout << "don't exists" << std::endl;
    return;
  }

  int *degree = new int[this->Vers];
  int *path = new int[this->Vers];
  int cnt = 0, i = 0;

  // O(|V|)
  for (int i = 0; i < this->Vers; ++i)
    degree[i] = 0;

  // O(|V|+|E|)
  for (int i = 0; i < this->Vers; ++i) {
    edgeNode *p = verList[i].head;
    while (p != nullptr) {
      degree[p->end]++;
      p = p->next;
    }
  }

  // O(|V|^2)
  while (cnt != this->Vers) {
    for (i = 0; i < this->Vers && degree[i] != 0; ++i)
      ;
    path[cnt++] = i;
    degree[i] = -1;
    edgeNode *p = verList[i].head;
    while (p != nullptr) {
      degree[p->end]--;
      p = p->next;
    }
  }

  // O(|V|)
  for (int i = 0; i < this->Vers; ++i)
    std::cout << verList[path[i]].ver << ' ';
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::findSCC() const {
  // 修改dfs 先深度优先遍历当前节点的每一个后续节点 再访问当前节点 按此次序编号
  // 将有向图边反向 得到Gr
  // 按编号从大到小dfsGr 输出SCC
  // 释放动态内存
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerPath() const {
  // 先找到度数为奇数的顶点
  // 从该顶点出发，其他步骤与寻找欧拉回路相同
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfsSCC() const {
  // visited 数组 0：未访问 -1：已访问 且属于一强连通分量 其他：dfs的次序
  // ancestors 数组
  // 初始被遍历 设置为自己
  // 遍历后继 若 visit[后继]=-1 break
  // 若 后继在搜索树上 更新 ancestors的值为后继的 ancestors
  // 后继未被访问过 访问后继 若返回值 < ancestors 更新ancestors
  // 找一个SCC
  // 检查是否有未被访问的节点 同样的算法寻找新的SCC
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topoSort_all() const {
  if (this->isDAG()) {
    std::cout << "don't exists" << std::endl;
    return;
  }

  int *degree = new int[this->Vers];
  int *path = new int[this->Vers];
  bool *visited = new bool[this->Vers];

  for (int i = 0; i < this->Vers; ++i) {
    degree[i] = 0;
    visited[i] = false;
  }

  topoSort_all(degree, path, visited, 0);
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topoSort_all(int *degree, int *path,
                                                       bool *visited,
                                                       int noOfNodes) const {
  if (noOfNodes == this->Vers) {
    for (int i = this->Vers - 1; i >= 0; --i)
      std::cout << verList[path[i]].ver << ' ';
    std::cout << std::endl;
    return;
  }

  for (int i = 0; i < this->Vers; i++) {
    if (degree[i] == 0 && visited[i] == false) {
      edgeNode *p = verList[i].head;
      while (p != nullptr) {
        degree[p->end]--;
        p = p->next;
      }
      visited[i] = true;
      path[noOfNodes] = i;
      noOfNodes++;

      topoSort_all(degree, path, visited, noOfNodes);

      p = verList[i].head;
      while (p != nullptr) {
        degree[p->end]++;
        p = p->next;
      }
      visited[i] = false;
      noOfNodes--;
    }
  }
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::findAllVertex(TypeOfVer source,
                                                        int M) const {
  int u = find(source), flag = 1, newflag = 0;
  edgeNode *p;
  linkQueue<int> que;
  bool visited[this->Vers] = {false};
  que.enQueue(u);

  while (M--) {
    newflag = 0;
    for (auto &i : visited)
      i = false;
    for (int i = 0; i < flag; ++i) {
      u = que.deQueue();
      p = verList[u].head;
      while (p != nullptr) {
        if (!visited[p->end]) {
          que.enQueue(p->end);
          visited[p->end] = true;
          newflag++;
        }
        p = p->next;
      }
    }
    flag = newflag;
  }

  while (!que.isEmpty())
    std::cout << verList[que.deQueue()].ver << ' ';
}

#endif
