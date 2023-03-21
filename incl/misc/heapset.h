#pragma once
#include "core/base.h"

template<class T, class CMP> struct HeapSet{
	HeapSet(CMP cmp):a(cmp),b(cmp){}
	inline void add(T x){a.push(x);}
	inline void del(T x){b.push(x);}
	inline T get(){
		while(sz(b)&&b.top()==a.top())
			b.pop(),a.pop();
		return a.top();
	}
	inline int size()const{return sz(a)-sz(b);}
	PQ<T,CMP> a,b;
};
