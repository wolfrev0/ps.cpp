#pragma once
#include "core/base.h"

template<class T,bool mx=false> struct HeapSet{
	void add(T x){a.push(mx?-x:x);}
	void del(T x){b.push(mx?-x:x);}
	T get(){
		while(sz(b)&&b.top()==a.top())b.pop(),a.pop();
		if(a.empty())return mx?-inf<int>():inf<int>();
		return mx?-a.top():a.top();}
	int size()const{return sz(a)-sz(b);}
	PQ<T,greater<>> a,b;
};