#pragma once
#include "Core.h"

struct SplayTree{
  struct Node{
    Node *p, *l, *r;
    int cnt=0;
    i64 val=0, acc=0;

    void renew(){
      cnt=1;
      acc = val;
      if (l) {
        cnt += l->cnt;
        acc += l->acc;
      }
      if (r) {
        cnt += r->cnt;
        acc += r->acc;
      }
    }
  };
  Node* root;
  int n;

  SplayTree(int n):n(n){
    Node *x;
    int i;
    root = x = new Node();
    x->l = x->r = x->p = nullptr;
    x->cnt = n;
    x->acc = x->val = 0;
    for (i = 1; i < n; i++) {
        x->r = new Node();
        x->r->p = x;
        x = x->r;
        x->l = x->r = nullptr;
        x->cnt = n - i;
        x->acc = x->val = 0;
    }
  }

  void rotate(Node* x){
    auto p = x->p;
    Node* b;
    if (x == p->l) {
        p->l = b = x->r;
        x->r = p;
    } else {
        p->r = b = x->l;
        x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if (b)
      b->p = p;
    (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
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
  void nth(int n) {
    auto x = root;
    while (true) {
      while (x->l && x->l->cnt > n)
        x = x->l;
      if (x->l)
        n -= x->l->cnt;
      if (!n--)
        break;
      x = x->r;
    }
    splay(x);
  }

  void add(int i, i64 z) {
    nth(i);
    root->acc += z;
    root->val += z;
  }
  
  void interval(int l, int r) {
    nth(l - 1);
    Node *x = root;
    root = x->r;
    root->p = NULL;
    nth(r - l + 1);
    x->r = root;
    root->p = x;
    root = x;
  }
  
  i64 sum(int l, int r) {
    interval(l, r);
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
//     i64 val=0, acc=0, cnt=0;

//     //move to position of root
//     void splay(Node*& root){
//       while(p != Node::null){
//         ((this==p->l)==(p==p->p->l)?p:this)->rotate();
//         this->rotate();
//       }
//       root=this;
//     }

//     Node* nth(i64 ord){
//       if(cnt-1-r->cnt > ord)
//         return l->nth(ord);
//       else if(cnt-1-r->cnt<ord)
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
//       cnt = 1+l->cnt+r->cnt;
//       acc = val+l->acc+r->acc;
//     }
//   };

//   Node* root;

//   SplayTree(i64 n, i64 id=0, i64 lazyid=0){
//     auto prev=root=Node::create();
//     root->cnt=n;
//     forh(i, 0, n-1){
//       auto cur=Node::create();
//       cur->cnt=prev->cnt-1-i;
//       cur->p=prev;
//       prev->r=cur;
//       prev=cur;
//     }
//     auto dummy = Node::null;
//     dummy->r=root;
//     dummy->l=prev;
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