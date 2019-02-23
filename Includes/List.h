#pragma once
#include "Core.h"

template<typename T>
struct List{
  struct Node{
    Node *prev=nullptr, *next=nullptr;
    T val;
    Node(T val):val(val){}
  };

  //mock node;
  Node *head, *tail;
  int sz;
  List():head(new Node(0)), tail(new Node(0)), sz(0){
    head->next=tail;
    tail->prev=head;
  }
  ~List(){
    while(head->next){
      head=head->next;
      delete head->prev;
    }
    delete head;
  }

  int size()const{return sz;}
  bool empty()const{return !sz;}

  T front()const{return head->next->val;}
  T back()const{return tail->prev->val;}

  void push_back(T val){insert(tail, val);}
  void push_front(T val){insert(head->next, val);}
  void pop_back(){erase(tail->prev);}
  void pop_front(){erase(head->next);}

  void insert(Node* i, T val){
    auto node=new Node(val);
    node->prev=i->prev;
    node->next=i;
    i->prev->next=node;
    i->prev=node;
    sz++;
  }

  void erase(Node* i){
    i->prev->next=i->next;
    i->next->prev=i->prev;
    delete i;
    sz--;
  }

  void append(List& li){
    li.head->next->prev=tail->prev;
    tail->prev->next=li.head->next;
    swap(tail, li.tail);
    li.head->next=li.tail;
    li.tail->prev=li.head;
    sz+=li.sz;
  }

  void traverse(const function<void(T&)>& f){
    auto it=head->next;
    while(it!=tail){
      f(it->val);
      it=it->next;
    }
  }

  //not tested yet.
  void reverse(Node *s, Node *e){
    auto l=s;
    auto r=e->prev;
    auto lp=l->prev;
    auto rn=r->next;
    lp->next=r;
    rn->prev=l;
    l->prev=rn;
    r->next=lp;
  }
};