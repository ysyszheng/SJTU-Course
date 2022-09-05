//
// Created by 森 on 2021/11/21.
//

#ifndef HOMEWORK6_PRIORITYQUEUE_H
#define HOMEWORK6_PRIORITYQUEUE_H

template <class T> class priorityQueueMax {
public:
  explicit priorityQueueMax(int capacity = 100);

  priorityQueueMax(const T data[], int size);

  ~priorityQueueMax();

  bool isEmpty() const;

  void enQueue(const T &x);

  T deQueue();

  T getHead() const;

private:
  int curSize;
  int maxSize;
  T *array;

  void doubleSpace();

  void buildHeap();

  void percolateDown(int hole);
};

/********************************************************************************************/

template <class T> class priorityQueueMin {
public:
  explicit priorityQueueMin(int capacity = 100);

  priorityQueueMin(const T data[], int size);

  ~priorityQueueMin();

  bool isEmpty() const;

  void enQueue(const T &x);

  T deQueue();

  T getHead() const;

  int findMin(const T &x) const;

  void decreaseKey(int i, T value);

  void traverse() const;

private:
  int curSize;
  int maxSize;
  T *array;

  void doubleSpace();

  void buildHeap();

  void percolateDown(int hole);
};

/****************************************** Max
 * *************************************************/

template <class T> priorityQueueMax<T>::priorityQueueMax(int capacity) {
  array = new int[capacity];
  curSize = 0;
  maxSize = capacity;
}

template <class T> priorityQueueMax<T>::~priorityQueueMax() {
  curSize = 0;
  delete[] array;
}

template <class T> bool priorityQueueMax<T>::isEmpty() const {
  return curSize == 0;
}

template <class T> T priorityQueueMax<T>::getHead() const { return array[1]; }

template <class T> void priorityQueueMax<T>::doubleSpace() {
  T *tmp = array;
  maxSize *= 2;
  array = new int[maxSize];
  for (int i = 0; i < maxSize / 2; ++i) {
    array[i] = tmp[i];
  }
  delete[] tmp;
}

template <class T> void priorityQueueMax<T>::enQueue(const T &x) {
  if (curSize == maxSize - 1)
    doubleSpace();
  int hole = ++curSize;
  for (; hole > 1 && array[hole / 2] < x; hole /= 2) {
    array[hole] = array[hole / 2];
  }
  array[hole] = x;
}

template <class T> T priorityQueueMax<T>::deQueue() {
  T max = array[1];
  array[1] = array[curSize--];
  percolateDown(1);
  return max;
}

template <class T> void priorityQueueMax<T>::percolateDown(int hole) {
  int child;
  T tmp = array[hole];

  for (; hole * 2 <= curSize; hole = child) {
    child = 2 * hole;
    if (child + 1 <= curSize && array[child + 1] > array[child])
      child++;
    if (tmp < array[child])
      array[hole] = array[child];
    else
      break;
  }
  array[hole] = tmp;
}

template <class T> void priorityQueueMax<T>::buildHeap() {
  for (int i = curSize / 2; i > 0; --i)
    percolateDown(i);
}

template <class T>
priorityQueueMax<T>::priorityQueueMax(const T *data, int size)
    : maxSize(size + 10), curSize(size) {
  array = new int[maxSize];
  for (int i = 0; i < size; ++i)
    array[i + 1] = data[i];
  buildHeap();
}

/*************************************** Min
 * **************************************************/

template <class T> priorityQueueMin<T>::priorityQueueMin(int capacity) {
  array = new int[capacity];
  curSize = 0;
  maxSize = capacity;
}

template <class T> priorityQueueMin<T>::~priorityQueueMin() {
  curSize = 0;
  delete[] array;
}

template <class T> bool priorityQueueMin<T>::isEmpty() const {
  return curSize == 0;
}

template <class T> T priorityQueueMin<T>::getHead() const { return array[1]; }

template <class T> void priorityQueueMin<T>::doubleSpace() {
  T *tmp = array;
  maxSize *= 2;
  array = new int[maxSize];
  for (int i = 0; i < maxSize / 2; ++i) {
    array[i] = tmp[i];
  }
  delete[] tmp;
}

template <class T> void priorityQueueMin<T>::enQueue(const T &x) {
  if (curSize == maxSize - 1)
    doubleSpace();
  int hole = ++curSize;
  for (; hole > 1 && array[hole / 2] > x; hole /= 2) {
    array[hole] = array[hole / 2];
  }
  array[hole] = x;
}

template <class T> T priorityQueueMin<T>::deQueue() {
  T min = array[1];
  array[1] = array[curSize--];
  percolateDown(1);
  return min;
}

template <class T> void priorityQueueMin<T>::percolateDown(int hole) {
  int child;
  T tmp = array[hole];

  for (; hole * 2 <= curSize; hole = child) {
    child = 2 * hole;
    if (child + 1 <= curSize && array[child + 1] < array[child])
      child++;
    if (tmp > array[child])
      array[hole] = array[child];
    else
      break;
  }
  array[hole] = tmp;
}

template <class T> void priorityQueueMin<T>::buildHeap() {
  for (int i = curSize / 2; i > 0; --i)
    percolateDown(i);
}

template <class T>
priorityQueueMin<T>::priorityQueueMin(const T *data, int size)
    : maxSize(size + 10), curSize(size) {
  array = new int[maxSize];
  for (int i = 0; i < size; ++i)
    array[i + 1] = data[i];
  buildHeap();
}

template <class T> int priorityQueueMin<T>::findMin(const T &x) const {
  int tmpIndex = -1;
  T tmpValue = 10000;
  for (int i = 1; i < curSize; ++i) {
    if (array[i] <= 9)
      continue;
    if (tmpValue > array[i]) {
      tmpValue = array[i];
      tmpIndex = i;
    }
  }
  return tmpIndex;
}

template <class T> void priorityQueueMin<T>::decreaseKey(int i, T value) {
  array[i] -= value;
  int tmp = array[i], hole = i;
  for (; hole > 1 && array[hole / 2] > tmp; hole /= 2)
    array[hole] = array[hole / 2];
  array[hole] = tmp;
}

template <class T> void priorityQueueMin<T>::traverse() const {
  for (int i = 1; i <= curSize; ++i) {
    std::cout << array[i] << ' ';
  }
  std::cout << std::endl;
}

#endif // HOMEWORK6_PRIORITYQUEUE_H
