#ifndef LIST_H
#define LIST_H

template <class T>
class list
{
public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int idx, const T &a) = 0;
    virtual void remove(int idx) = 0;
    virtual int search(const T &a) const = 0;
    virtual T visit(int idx) const = 0;
    virtual void traverse() const = 0;
    virtual ~list(){};
};

#endif