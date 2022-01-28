#pragma once
#include "core/base.h"

template<class T> struct List{
	struct Node{T dt;Node *nn=0;};
	Node *h=0,*t=0;
	Node* begin()const{return h;}
	Node* end()const{return 0;}
	void push_back(T a){
		if(!h) h=t=new Node{a};
		else t=t->nn=new Node{a};}
	List<T> splice(const List<T> &a){t->nn=a.h,t=a.t;}
};