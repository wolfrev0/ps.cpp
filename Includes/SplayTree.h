#pragma once
#include "Core.h"

struct SplayTree{
  SplayTree(int n, i64 id_upd, i64 id_qry,
    const function<i64(i64, i64)>& queryf,
	  const function<i64(int, int, i64, i64)>& lazyf,
	  const function<i64(i64, i64)>& propaf)
    :n(n), id_upd(id_upd), id_qry(id_qry), queryf(queryf), lazyf(lazyf), propaf(propaf)
  { Build(); }

	SplayTree(
		int n=0,
		i64 id_upd=I64::zero(),
		i64 id_qry=I64::zero())
		:SplayTree(n, id_upd, id_qry,[](i64 a, i64 b) {return a + b; },
    [id_upd, id_qry](int s, int e, i64 tval, i64 lval) {return tval + (lval != id_upd ? lval : id_upd) * (e - s); }, 
    [id_upd, id_qry](i64 lval, i64 val) { return (lval != id_upd ? lval : id_upd) + val; })
  {}

  void update(int i, i64 z) {
    splay(nth(root, i));
    root->acc += z;
    root->val += z;
  }
  
  i64 query(int s, int e) {
    return interval(s, e)->acc;
  }

private:
  struct Node{
    Node *p=nullptr, *l=nullptr, *r=nullptr;
    int sz=0;
    i64 val=0, acc=0;

    void adoptL(Node* n){l=n; if(n)n->p=this;}
    void adoptR(Node* n){r=n; if(n)n->p=this;}
  };

  Node* root;
  int n;
  const int id_upd, id_qry;
	const function<i64(i64, i64)> queryf;
	const function<i64(int, int, i64, i64)> lazyf;
	const function<i64(i64, i64)> propaf;

  inline int size(Node* x)const{return x?x->sz:0;}
  inline i64 acc(Node* x)const{return x?x->acc:id_upd;}

  void Build(){
    Node* x = new Node();
    root=x;
    //+2 is Left(-1) Right(n) mock nodes
    x->sz = n+2;
    forh(i, 1, n+2){
      x->adoptR(new Node());
      x->r->sz = n+2 - i;
      x=x->r;
    }
  }

  //children should be renewed.
  void renew(Node* x){
    if(!x)
      return;
    x->sz=1+size(x->l)+size(x->r);
    x->acc=x->val+acc(x->l)+acc(x->r);
  }

  Node* nth(Node* x, int n){
    assert(x);
    int lsz=size(x->l);
    if(lsz>n+1)
      return nth(x->l, n);
    if(lsz<n+1)
      return nth(x->r, n-lsz-1);
    return x;
  }

  void splay(Node *x) {
    while (x->p) {
      auto p = x->p;
      auto pp = p->p;
      if (pp)
        rotate((x == p->l) == (p == pp->l) ? p : x);
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
    splay(nth(root, e - size(sav->l)-1));
    sav->r=root;
    root->p=sav;
    root=sav;
    return root->r->l;
  }
};
