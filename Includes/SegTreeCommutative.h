#pragma once
#include "Core.h"

template<typename T, typename U>
struct SegFDefault{
  static T idT(){return T();}
  static T q(const T& a, const T& b){return a+b;}
  static T upd(const T& a, const U& b){return a+b;}
};

template<typename T, typename U, typename F=SegFDefault<T,U>>
struct SegTreeCommutative{
  SegTreeCommutative(int n):n(n),tree(4*n, F::idT()){}
  int n;
  vector<T> tree;

  void update(int p, U val){
    p+=n;
    for (tree[p]=F::upd(tree[p], val); p>1; p>>=1)
      tree[p>>1]=F::q(tree[p],tree[p^1]);
  }

  T query(int l, int r) {
    T res=F::idT();
    for (l+=n,r+=n; l<r; l>>=1,r>>=1) {
      if (l&1)res=F::q(res,tree[l++]);
      if (r&1)res=F::q(res,tree[--r]);
    }
    return res;
  }
};