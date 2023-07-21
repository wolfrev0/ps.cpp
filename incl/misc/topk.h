#pragma once
#include "misc/heapset.h"

//NOTE: delete non-existent element cause UB
template<class T>
struct TopK{
	TopK(int k):k(k){}
	int k;
	HeapSet<T,less<T>> l;
	HeapSet<T,greater<T>> r;
	void add(const T& x){
		r.add(x);
		while(sz(r)>k){
			l.add(r.top());
			r.del(r.top());
		}
	}
	void del(const T& x){
		if(x<r.top())
			l.del(x);
		else{
			r.del(x);
			if(sz(l)){
				r.add(l.top());
				l.del(l.top());
			}
		}
	}
};