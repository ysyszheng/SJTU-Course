#ifndef DYNAMICSEARCHTABLE_H
#define DYNAMICSEARCHTABLE_H

template <class KEY, class OTHER> struct SET {
  KEY key;
  OTHER other;

  SET(KEY a, OTHER b) : key(a), other(b) {}
};

template <class KEY, class OTHER> class dynamicSearchTable {
public:
  virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
  virtual void insert(const SET<KEY, OTHER> &set) = 0;
  virtual void remove(const KEY &key) = 0;
  virtual ~dynamicSearchTable(){};
};

#endif