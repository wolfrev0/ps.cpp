#pragma once
#include "SimpleTree.h"
#include "SegmentTree.h"

template<typename T>
struct RootedTree:public Tree<T>{
  RootedTree(const Tree<T>& tree, int r)
  :Tree<T>(tree),r(r),parent(n),children(Tree<T>::g){
    dfs_rootize(r, -1);
    for(const auto &i:parent)
      if(i.s!=i.e)//if not root
        children[i.s].erase(children[i.s].begin()+i.ei);
  }
protected:
  using Tree<T>::n;
  using Tree<T>::g;
  using typename Graph<T>::Edge;

  int r;
  vector<Edge> parent;
  decltype(g)& children;

  //O(N log N)
  void dfs_rootize(int cur, int p){
    for(const auto &i:children[cur])
      if(i.e==p)
        parent[cur]=i;
      else
        dfs_rootize(i.e, cur);
  }
};