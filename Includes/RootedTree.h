#pragma once
#include "Tree.h"
#include "SegmentTree.h"

template<typename T>
struct RootedTree:public Tree<T>{
  using Tree<T>::n;
  using Tree<T>::g;
  int root;
  vector<int> parent;
  decltype(g)& children;

  RootedTree(int n, int r):Tree<T>(n),root(r),parent(n), children(Tree<T>::g){dfs_parent(root, -1);}
protected:
  void dfs_parent(int cur, int p)const{
    parent[cur]=p;
    if(p!=-1)
      children[cur].erase(find_if(children[cur].begin(), children[cur].end(), [p](auto& a){return a.e==p;}));
    for(auto &i:children[cur]){
      dfs_parent(i.e, cur);
    }
  }

  SegmentTree<int> st;
  void euler_tour(int u, int v){

  }

  int lca(int a, int b){
    return 0;
  }
};