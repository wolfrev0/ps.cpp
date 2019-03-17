#pragma once
#include "Core.h"

template<typename T>
struct PST{
  struct Node{
    Node *l=nullptr, *r=nullptr;
    T val=T();
  };

  const int n;
  function<T(const T&, const T&)> q;

  PST(int n, function<T(const T&, const T&)> q):n(n), q(q){}
  void build(Node*& cur){ build(cur, 0, n); }
  void upgrade(Node*& tree, Node*& base, int idx, int val){ upgrade(tree, base, 0, n, idx, val); }
  T query(Node* tree, int s, int e){ return query(tree, 0, n, s, e); }

private:
  T val(Node *x){ return x?x->val:T(); }

  void build(Node*& cur, int s, int e){
    cur=new Node();
    if(e-s==1)
      return;

    int m=(s+e)/2;
    build(cur->l,s,m);
    build(cur->r,m,e);
    cur->val=q(val(cur->l), val(cur->r));
  }

  void upgrade(Node*& cur, Node* base, int s, int e, int idx, T v){
    if(e<=idx or idx<s)
      return;
    cur=new Node();
    if(e-s==1){
      cur->val=v;
      return;
    }

    int m=(s+e)/2;
    cur->r=base->r;
    cur->l=base->l;
    upgrade(cur->l, base->l, s, m, idx, v);
    upgrade(cur->r, base->r, m, e, idx, v);
    cur->val=q(val(cur->l), val(cur->r));
  }

  T query(Node* cur, int cs, int ce, int s, int e){
    if(ce<=s or e<=cs or e<=s)
      return T();
    if(s<=cs and ce<=e)
      return cur->val;
    int m=(cs+ce)/2;
    return q(query(cur->l, cs, m, s, e), query(cur->r, m, ce, s, e));
  }
};