#pragma once
#include "RootedTree.h"

template<typename T>
struct LCA:public RootedTree<T>{
  using RootedTree<T>::n;
  using RootedTree<T>::r;
  using RootedTree<T>::parent;
  using RootedTree<T>::children;
  
  LCA(const Tree<T>& t, int r)
  :RootedTree<T>(t, r), st(n*2, [](const auto& a, const auto& b){return min(a, b);}, [](const auto& a, const auto& b){return min(a, b);}),lpos(n)
  {int segi=0; dfs_lca(r, segi);}

  int lca(int a, int b){
    int l=lpos[a], r=lpos[b];
    if(l>r)
      swap(l, r);
    return st.query(l, r+1).idx;
  }
protected:
  struct LCA_ORD_IDX{
    static LCA_ORD_IDX zero(){return{0x7fffffff/2, -1};}
    int ord, idx;
    bool operator<(const LCA_ORD_IDX& r)const{return ord<r.ord;}
  };
  SegmentTree<LCA_ORD_IDX> st;
  vector<int> lpos;

  void dfs_lca(int cur, int& segi){
    int ord = segi;
    lpos[cur]=ord;
    st.update(segi++, {ord, cur});

    for(const auto& i:children[cur]){
      dfs_lca(i.e, segi);
      st.update(segi++, {ord, cur});
    }
  }
};