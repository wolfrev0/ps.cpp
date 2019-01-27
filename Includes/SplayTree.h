#pragma once
#include "Core.h"

struct SplayTree{
  struct Node{
    Node *p=nullptr, *l=nullptr, *r=nullptr;
    int size=0;
    i64 val=0, acc=0;

    void adoptL(Node* n){l=n; if(n)n->p=this;}
    void adoptR(Node* n){r=n; if(n)n->p=this;}

    void renew(){
      size=1;
      acc = val;
      if (l) {
        size += l->size;
        acc += l->acc;
      }
      if (r) {
        size += r->size;
        acc += r->acc;
      }
    }

    Node* nth(int n){
      int lsz = l?l->size:0;
      if(lsz>n+1)
        return l->nth(n);
      if(lsz<n+1)
        return r->nth(n-lsz-1);
      return this;
    }
  };
  Node* root;
  int n;

  SplayTree(int n):n(n){
    Node* x = new Node();
    root=x;
    //+2 is Left(-1) Right(n) mock nodes
    x->size = n+2;
    forh(i, 1, n+2){
      x->adoptR(new Node());
      x->r->size = n+2 - i;
      x=x->r;
    }
  }

  void rotate(Node* x){
    if(!x->p)
      return;
    
    auto p = x->p;
    //Mock Adopter?
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
    p->renew();
    x->renew();
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

  void add(int i, i64 z) {
    splay(root->nth(i));
    root->acc += z;
    root->val += z;
  }
  
  i64 sum(int l, int r) {
    splay(root->nth(l-1));
    
    auto sav = root;
    root->r->p=nullptr;
    root=root->r;
    splay(root->nth(r+1 - (sav->l?sav->l->size:0)-1));
    sav->r=root;
    root->p=sav;
    root=sav;
    
    return root->r->l->acc;
  }
};
