#pragma once
#include "Core.h"

struct SplayTree{
  struct Node{
    Node *p=nullptr, *l=nullptr, *r=nullptr;
    int sz=0;
    i64 val=0, acc=0;

    void adoptL(Node* n){l=n; if(n)n->p=this;}
    void adoptR(Node* n){r=n; if(n)n->p=this;}
  };
  Node* root;
  int n;

  SplayTree(int n):n(n){
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

  void update(int i, i64 z) {
    splay(nth(root, i));
    root->acc += z;
    root->val += z;
  }
  
  i64 query(int s, int e) {
    splay(nth(root, s-1));
    
    auto sav = root;
    root->r->p=nullptr;
    root=root->r;
    splay(nth(root, e - size(sav->l)-1));
    sav->r=root;
    root->p=sav;
    root=sav;
    
    return root->r->l->acc;
  }

private:
  const int id=0;
  inline int size(Node* x)const{return x?x->sz:0;}
  inline i64 acc(Node* x)const{return x?x->acc:id;}

  void renew(Node* x){
    if(!x)
      return;
    x->sz=1+size(x->l)+size(x->r);
    x->acc=x->val+acc(x->l)+acc(x->r);
  }

  Node* nth(Node* cur, int n){
    assert(cur);
    int lsz=size(cur->l);
    if(lsz>n+1)
      return nth(cur->l, n);
    if(lsz<n+1)
      return nth(cur->r, n-lsz-1);
    return cur;
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
};
