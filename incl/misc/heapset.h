#pragma once
#include "core/base.h"

template<class T, bool mx=false> struct HeapSet {
	void add(const T& x){a.push(mx?-x:x);}
	void del(const T& x){b.push(mx?-x:x);}
	T get(){
		while(sz(b)&&b.top()==a.top()) b.pop(),a.pop();
		if(a.empty()) return mx?-inf<int>():inf<int>();
		return mx?-a.top():a.top();
	}
	int size()const{return sz(a)-sz(b);}
	PQMin<T> a,b;
};