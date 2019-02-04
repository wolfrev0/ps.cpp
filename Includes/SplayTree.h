#pragma once
#include "DynamicTree.h"

template<typename T, typename U=T>
struct SplayTree:public DynamicTree{
  struct Node{
    Node *p=nullptr, *l=nullptr, *r=nullptr;
    int sz=1;
    T val, acc;
    U lazy;

    void adoptL(Node* n){l=n; if(n)n->p=this;}
    void adoptR(Node* n){r=n; if(n)n->p=this;}
  };

  SplayTree(int n,
    const function<T(const T&, const T&)>& queryf,
	  const function<void(Node*)>& updf,
	  const function<U(const U&, const U&)>& propaf)
    :queryf(queryf), updf(updf), propaf(propaf)
  {
    root=new_node();
    root->adoptR(new_node());
    renew(root);
    
    forh(i, 0, n)
      insert(0);
  }

	SplayTree(int n=0)
		:SplayTree(n,
    [](const T& a, const T& b) {return a + b; },
    [](Node* x) {x->val+=x->lazy; x->acc+=x->lazy*x->sz;}, 
    [](const U& clazy, const U& lazy) { return clazy + lazy; })
  {}

  void update(int i, T val) {update(i, i+1, val);}
  T query(int i){return query(i, i+1);}

  void update(int s, int e, U val){
    if(s++ == e++)//cuz left mock node
      return;
    auto x=interval(s, e);
    x->lazy=propaf(x->lazy, val);
  }
  
  T query(int s, int e){
    if(s++ == e++)//cuz left mock node
      return T::zero();
    return acc(interval(s, e));
  }

  void insert(int ord, T val = T::zero()){
    ord++;//cuz left mock node
    splay(ord-1);
    auto r = root->r;
    root->adoptR(new_node(val));
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

  int size()const{return root->sz-2;}
protected:
  Node* root=nullptr;
	const function<T(const T&, const T&)> queryf;
	const function<void(Node* x)> updf;
	const function<U(const U&, const U&)> propaf;

  int size(Node* x)const{return x?x->sz:0;}
  T acc(Node* x)const{return x?x->acc:T::zero();}

  Node* new_node(T val = T::zero()){
    auto ret = new Node();
    ret->val = ret->acc = val;
    ret->lazy = U::zero();
    return ret;
  }

  //children should be renewed.
  void renew(Node* x, bool with_ancestor = false){
    if(!x)
      return;
    update_lazy(x);
    update_lazy(x->l);
    update_lazy(x->r);
    
    x->sz=1+size(x->l)+size(x->r);
    x->acc=queryf(queryf(acc(x->l), x->val), acc(x->r));

    if(with_ancestor)
      renew(x->p, with_ancestor);
  }

  Node* nth(Node* x, int n){
    assert(x);
    renew(x);

    int lsz=size(x->l);
    if(lsz>n)
      return nth(x->l, n);
    if(lsz<n)
      return nth(x->r, n-lsz-1);
    return x;
  }

  void splay(int ord) {splay(nth(root, ord));}
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
    update_lazy(x->p);
    update_lazy(x->p->l);
    update_lazy(x->p->r);
    
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
    splay(s-1);
    
    auto sav = root;
    root->r->p=nullptr;
    root=root->r;
    splay(e-size(sav->l)-1);
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
    if(x->lazy == U::zero())
      return;

    updf(x);
    if(x->l){
      x->l->lazy=propaf(x->l->lazy, x->lazy);
    }
    if(x->r){
      x->r->lazy=propaf(x->r->lazy, x->lazy);
    }
    x->lazy=U::zero();
  }
};
