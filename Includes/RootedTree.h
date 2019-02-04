#pragma once
#include "Tree.h"
#include "SegmentTree.h"

template<typename T>
struct RootedTree:public Tree<T>{
  RootedTree(const Tree<T>& tree, int r)
  :Tree<T>(tree),root(r),parent(n), children(Tree<T>::g), 
  st(n*2, [](const auto& a, const auto& b){return min(a, b);}, [](const auto& a, const auto& b){return min(a, b);}),
  lpos(n) {int segi=0; dfs_precalc(root, -1, segi);}

  int lca(int a, int b){
    int l=lpos[a], r=lpos[b];
    if(l>r)
      swap(l, r);
    return st.query(l, r+1).idx;
  }
protected:
  struct A{
    static A zero(){return{0x7fffffff/2, -1};}
    int ord, idx;
    bool operator<(const A& r)const{return ord<r.ord;}
  };

  using Tree<T>::n;
  using Tree<T>::g;

  int root;
  vector<int> parent;
  decltype(g)& children;
  SegmentTree<A> st;
  vector<int> lpos;

  //O(N log N)
  void dfs_precalc(int cur, int p, int& segi){
    parent[cur]=p;
    int ord = segi;
    lpos[cur]=ord;
    st.update(segi++, {ord, cur});
    if(p!=-1)
      children[cur].erase(find_if(children[cur].begin(), children[cur].end(), [p](auto& a){return a.e==p;}));
    for(auto &i:children[cur]){
      dfs_precalc(i.e, cur, segi);
      st.update(segi++, {ord, cur});
    }
  }
};