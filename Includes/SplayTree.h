#pragma once
#include "Core.h"

template<typename T>
struct SplayTree{
  SplayTree(int n, T id_qry, T id_upd,
    const function<T(const T&, const T&)>& queryf,
	  const function<T(const T&, const T&, int)>& updf,
	  const function<T(const T&, const T&)>& propaf)
    :n(n), id_qry(id_qry), id_upd(id_upd), queryf(queryf), updf(updf), propaf(propaf)
  {
    root=new_node();
    root->adoptR(new_node());
    renew(root);
    
    forh(i, 0, n)
      insert(0);
  }

	SplayTree(int n=0)
		:SplayTree(n, T::zero(), T::zero(),
    [](const T& a, const T& b) {return a + b; },
    [](const T& tval, const T& lval, int cnt) {return tval + lval * cnt; }, 
    [](const T& lval, const T& val) { return lval + val; })
  {}

  void update(int i, T val) {update(i, i+1, val);}
  T query(int i){return query(i, i+1);}

  void update(int s, int e, T val){
    s++,e++;//cuz left mock node
    auto x=interval(s, e);
    x->lazy=propaf(x->lazy, val);
  }
  
  T query(int s, int e){
    s++,e++;//cuz left mock node
    return interval(s, e)->acc;
  }

  void insert(int ord){
    ord++;//cuz left mock node
    splay(nth(root, ord-1));
    auto r = root->r;
    root->adoptR(new_node());
    root->r->adoptR(r);
    renew(root->r, true);
  }

  void erase(int ord){
    ord++;//cuz left mock node
    auto x = interval(ord, ord+1);
    auto p = x->p;
    delete x;
    p->l=nullptr;
    renew(p, true);
  }

  int size()const{return root?root->sz:0;}
protected:
  struct Node{
    Node *p=nullptr, *l=nullptr, *r=nullptr;
    int sz=1;
    T val, acc;
    T lazy;

    void adoptL(Node* n){l=n; if(n)n->p=this;}
    void adoptR(Node* n){r=n; if(n)n->p=this;}
  };

  Node* root=nullptr;
  int n;
  const T id_qry, id_upd;
	const function<T(const T&, const T&)> queryf;
	const function<T(const T&, const T&, int cnt)> updf;
	const function<T(const T&, const T&)> propaf;

  int size(Node* x)const{return x?x->sz:0;}
  T acc(Node* x)const{return x?x->acc:id_qry;}

  Node* new_node(){
    auto ret = new Node();
    ret->val = ret->acc = ret->lazy = id_upd;
    return ret;
  }

  //children should be renewed.
  void renew(Node* x, bool with_ancestor = false){
    if(!x)
      return;
    x->sz=1+size(x->l)+size(x->r);
    x->acc=queryf(queryf(acc(x->l), x->val), acc(x->r));

    if(with_ancestor)
      renew(x->p, with_ancestor);
  }

  Node* nth(Node* x, int n){
    assert(x);
    update_lazy(x);
    update_lazy(x->l);
    update_lazy(x->r);
    renew(x);

    int lsz=size(x->l);
    if(lsz>n)
      return nth(x->l, n);
    if(lsz<n)
      return nth(x->r, n-lsz-1);
    return x;
  }

  void splay(Node *x) {
    while(x->p){
      auto p = x->p;
      if (p->p)
        rotate((x == p->l) == (p == p->p->l) ? p : x);
      rotate(x);
    }
  }

  void rotate(Node* x){
    if(!x->p)
      return;
    
    auto p = x->p;
    if(!p->p)
      root=x;
    else if(p->p->l == p)
      p->p->l=x;
    else
      p->p->r=x;
    x->p = p->p;

    Node* mid;
    if (x == p->l) {
        p->adoptL(mid=x->r);
        x->adoptR(p);
    } else {
        p->adoptR(mid=x->l);
        x->adoptL(p);
    }
    if (mid)
      mid->p = p;
    renew(p);
    renew(x);
  }

  Node* interval(int s, int e){
    splay(nth(root, s-1));
    
    auto sav = root;
    root->r->p=nullptr;
    root=root->r;
    splay(nth(root, e-size(sav->l)-1));
    sav->r=root;
    root->p=sav;
    root=sav;
    return root->r->l;
  }
  
  //should call before when accesses children. (example: nth, search, insert etc...)
  //and access should be started at root.
  void update_lazy(Node* x){
    if(!x)
      return;
    if(x->lazy == id_upd)
      return;

    x->val=updf(x->val, x->lazy, 1);
    x->acc=updf(x->acc, x->lazy, x->sz);
    if(x->l){
      x->l->lazy=propaf(x->l->lazy, x->lazy);
    }
    if(x->r){
      x->r->lazy=propaf(x->r->lazy, x->lazy);
    }
    x->lazy=id_upd;
  }
};
