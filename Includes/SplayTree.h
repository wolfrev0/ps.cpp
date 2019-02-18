#pragma once
#include "DynamicTree.h"

template<typename T, typename U>
struct SplayNode{
  SplayNode *p=nullptr,*l=nullptr,*r=nullptr;
  int sz=1;
  T val,acc;
  U lazy;
  ~SplayNode(){
    if(l) delete l;
    if(r) delete r;
  }

  void adoptL(SplayNode* n){l=n; if(n) n->p=this;}
  void adoptR(SplayNode* n){r=n; if(n) n->p=this;}
};

template<typename T, typename U>
struct SplayFDefault{
  static T idT(){return T();}
  static U idU(){return U();}
  static T q(const T& a, const T& b){return a+b;}
  static void upd(SplayNode<T,U>* x){x->val+=x->lazy; x->acc+=x->lazy*x->sz;}
  static U propa(const U& clazy, const U& lazy){return clazy+lazy;}
};

//warning: implement is 1-based index(while interface is 0-based).
//since mock nodes(idx:0, idx:n+1) for convenient interval().
template<typename T, typename U=T, typename F=SplayFDefault<T, U>>
struct SplayTree:public DynamicTree{
  using Node=SplayNode<T,U>;
  SplayTree(int n=0):DynamicTree(){
    //mock nodes
    root=new_node();
    root->adoptR(new_node());
    renew(root);
    
    //real nodes
    forh(i,0,n)
      insert(0);
  }
  ~SplayTree(){delete root;}

  void update(int i, U val){update(i,i+1,val);}
  T query(int i){return query(i,i+1);}

  void update(int s, int e, U val){
    if(s==e)
      return;
    auto x=interval(s+1,e+1);
    x->lazy=F::propa(x->lazy,val);
    renew(x,true);
  }
  
  T query(int s, int e){
    if(s==e)
      return F::idT();
    return acc(interval(s+1,e+1));
  }

  void insert(int ord, T val=F::idT()){
    splay(ord);
    auto r=root->r;
    root->adoptR(new_node(val));
    root->r->adoptR(r);
    renew(root->r,true);
  }

  void erase(int ord){
    auto x=interval(ord+1,ord+2);
    auto p=x->p;
    delete x;
    p->l=nullptr;
    renew(p,true);
  }

  Node* find_by_order(int ord){return splay(ord+1);}
  int order_of(Node* x){return size(splay(x)->l)-1;}
  int size()const{return root->sz-2;}
protected:
  Node* root=nullptr;

  int size(Node* x)const{return x?x->sz:0;}
  T acc(Node* x)const{return x?x->acc:F::idT();}

  Node* new_node(T val=F::idT()){
    auto ret=new Node();
    ret->val=ret->acc=val;
    ret->lazy=F::idU();
    return ret;
  }

  //children should be renewed.
  void renew(Node* x, bool with_ancestor=false){
    if(!x)
      return;
    
    propagate(x);
    propagate(x->l);
    propagate(x->r);
    x->sz=1+size(x->l)+size(x->r);
    x->acc=F::q(F::q(acc(x->l),x->val),acc(x->r));

    if(with_ancestor)
      renew(x->p,with_ancestor);
  }

  Node* nth(Node* x, int n){
    assert(x);
    propagate(x);
    int lsz=size(x->l);
    if(lsz>n)
      return nth(x->l,n);
    if(lsz<n)
      return nth(x->r,n-lsz-1);
    return x;
  }

  Node* splay(int ord){return splay(nth(root,ord));}
  Node* splay(Node *x, Node *rp=nullptr){
    while(x->p!=rp){
      auto p=x->p;
      if (p->p!=rp)
        rotate((x==p->l)==(p==p->p->l)?p:x);
      rotate(x);
    }
    return x;
  }

  void rotate(Node* x){
    if(!x->p)
      return;
    
    auto p=x->p;
    propagate(p);
    propagate(p->l);
    propagate(p->r);
    if(!p->p)
      root=x;
    else if(p->p->l==p)
      p->p->l=x;
    else
      p->p->r=x;
    x->p=p->p;

    Node* mid;
    if (x==p->l){
        p->adoptL(mid=x->r);
        x->adoptR(p);
    } else{
        p->adoptR(mid=x->l);
        x->adoptL(p);
    }
    if (mid)
      mid->p=p;
    renew(p);
    renew(x);
  }

  Node* interval(int s, int e){
    auto a=nth(root,s-1);
    auto b=nth(root,e);
    splay(a);
    splay(b,a);
    return root->r->l;
  }
  
  void propagate(Node* x){
    if(!x)
      return;
    if(x->lazy==F::idU())
      return;
    
    F::upd(x);
    if(x->l)
      x->l->lazy=F::propa(x->l->lazy,x->lazy);
    if(x->r)
      x->r->lazy=F::propa(x->r->lazy,x->lazy);
    x->lazy=F::idU();
  }
};
