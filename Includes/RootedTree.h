#pragma once
#include "SimpleTree.h"

template<typename T>
struct RootedTree:public Tree<T>{
  using P=Tree<T>;
  RootedTree(const P& tree, int r)
  :P(tree),r(r),parent(n),children(P::g){
    dfs_rootize(r, -1);
    for(const auto &i:parent)
      if(i.s!=i.e)//if not root
        children[i.s].erase(children[i.s].begin()+i.ei);
  }
protected:
  using P::n;
  using P::g;
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