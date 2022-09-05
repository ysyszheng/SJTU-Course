//
// Created by 森 on 2021/11/21.
//

#ifndef HOMEWORK6_SET_H
#define HOMEWORK6_SET_H

template<class KEY, class OTHER>
struct SET {
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class linkList {
private:
    struct node {
        SET<KEY, OTHER> data;
        node *next;

        node(const SET<KEY, OTHER> &x, node *n = NULL) : data(x), next(n) {}
    };

    node *head;
    int curLen;
public:
    linkList(SET<KEY, OTHER> data[], int size);

    ~linkList();

    int seqSearch(const KEY &x);
};

template<class KEY, class OTHER>
linkList<KEY, OTHER>::linkList(SET<KEY, OTHER> *data, int size) {
    curLen = size;
    head = new node;
    node *p = head;
    for (int i = 0; i < size; ++i) {
        p = p->next = new node(data[i]);
    }
}

template<class KEY, class OTHER>
linkList<KEY, OTHER>::~linkList() {
    while (head != NULL) {
        node *tmp = head;
        head = head->next;
        delete tmp;
    }
}


// problem 2
template<class KEY, class OTHER>
int linkList<KEY, OTHER>::seqSearch(const KEY &x) {
    node *tmp = head->next;
    int cnt = 1;
    while (tmp != NULL && tmp->data.key != x) {
        tmp = tmp->next;
        cnt++;
    }
    if (tmp == NULL)
        return 0;
    else
        return cnt;
}

// problem 1
template<class KEY, class OTHER>
int binSearch(SET<KEY, OTHER> data[], const KEY &x, int low, int high) {
    if (low > high)
        return 0;
    int mid = (low + high) / 2;
    if (data[mid].key == x)
        return mid;
    else if (data[mid].key > x)
        return binSearch(data, x, low, mid - 1);
    else
        return binSearch(data, x, mid + 1, high);
}

template<class KEY, class OTHER>
int binarySearch(SET<KEY, OTHER> data[], int size, const KEY &x) {
    binSearch(data, x, 1, size);
}

// problem 5
template<class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY &x) {
    data[0].key = x;
    int i = size;
    for (; x != data[i].key; i--);
    if (i != 0 && i != size) {
        SET<KEY, OTHER> tmp = data[i];
        data[i] = data[i + 1];
        data[i + 1] = tmp;
    }
    return i;
}

#endif //HOMEWORK6_SET_H
