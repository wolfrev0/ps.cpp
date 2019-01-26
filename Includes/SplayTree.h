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
      if(lsz>n)
        return l->nth(n);
      if(lsz<n)
        return r->nth(n-lsz-1);
      return this;
    }
  };
  Node* root;
  int n;

  SplayTree(int n):n(n){
    Node* x = new Node();
    root=x;
    x->size = n;
    forh(i, 1, n){
      x->adoptR(new Node());
      x->r->size = n - i;
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

// struct SplayTree2{
//   struct Node{
//     static Node* null;
//     static Node* create(){
//       if(!null){
//         null=new Node();
//         null->p=null->l=null->r=null;
//       }
//       auto ret = new Node();
//       ret->p=ret->l=ret->r=null;
//       return ret;
//     }
//     Node *p, *l, *r;
//     i64 val=0, acc=0, size=0;

//     //move to position of root
//     void splay(Node*& root){
//       while(p != Node::null){
//         ((this==p->l)==(p==p->p->l)?p:this)->rotate();
//         this->rotate();
//       }
//       root=this;
//     }

//     Node* nth(i64 ord){
//       if(size-1-r->size > ord)
//         return l->nth(ord);
//       else if(size-1-r->size<ord)
//         return r->nth(ord);
//       return this;
//     }
//   private:
//     Node(){}

//     //move to parent pos
//     void rotate(){
//       if(this->p==null)
//         return;
//       Node* m;
//       function<Node*&(Node*)> a=[](Node* x)->Node*&{return x->l;};
//       function<Node*&(Node*)> b=[](Node *x)->Node*&{return x->r;};
//       if(this==p->r)
//         swap(a,b);
      
//       m=a(p)=b(this);
//       b(this)=p;

//       auto psav=p;
//       p=p->p;
//       psav->p=this;
//       if(m!=Node::null)
//         m->p=p;
//       a(p)=this;
//       psav->renew();
//       this->renew();
//     }

//     void renew(){
//       size = 1+l->size+r->size;
//       acc = val+l->acc+r->acc;
//     }
//   };

//   Node* root;

//   SplayTree(i64 n, i64 id=0, i64 lazyid=0){
//     auto x=root=Node::create();
//     root->size=n;
//     forh(i, 0, n-1){
//       auto cur=Node::create();
//       cur->size=x->size-1-i;
//       cur->p=x;
//       x->r=cur;
//       x=cur;
//     }
//     auto dummy = Node::null;
//     dummy->r=root;
//     dummy->l=x;
//   }

//   Node* nth(i64 ord){
//     return root->nth(ord);
//   }

//   void upd(i64 i, i64 val){
//     auto x = nth(i);
//     x->splay(root);
//     x->val+=val;
//     x->acc+=val;
//   }

//   i64 query(i64 l, i64 r){
//     auto x = nth(l-1);
//     x->splay(root);
//     auto y = nth(r+1);
//     y->splay(root);
//     return root->l->r->acc;
//   }
// };

// SplayTree::Node* SplayTree::Node::null = nullptr;