#ifndef GRAPH_H
#define GRAPH_H

template <class TypeOfVer, class TypeOfEdge> class graph {
public:
  virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
  virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
  virtual bool exists(TypeOfVer x, TypeOfVer y) const = 0;
  int numOfVers() const { return Vers; }
  int numOfEdges() const { return Edges; }

protected:
  int Vers, Edges;
};

#endif