#pragma once
#include "Core.h"

template<typename T>
struct List{
	struct Node{
		T dt;
		Node *nn=0;
	};
	Node *h=0, *t=0;
	Node *begin()const{return h;}
	Node *end()const{return 0;}
	void pushb(const T& a){
		if(!h) h=t=new Node{a};
		else t=t->nn=new Node{a};
	}
	
	List<T> splice(const List<T>& a){
		t->nn=a.h;t=a.t;
	}
};