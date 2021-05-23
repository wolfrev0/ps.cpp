#pragma once 
#include "core/base.h"

template<class T>
struct IterRange {
  IterRange(T s, T e):s(s),e(e){}
  T begin()const{ return s; }
  T end()const{ return e; }
	T s,e;
};

template<class T> T dupl(const T& x, int n) {
	T r;
	for(int _ = 0; _ < n; _++) r.insert(r.end(), all(x));
	return r;
}

Arr<int> range(int n) {
	Arr<int> r(n);
	for(int i = 0; i < n; i++) r[i] = i;
	return r;
}

template<class T>
Arr<pair<T,int>> enumerate(Arr<T> a){
	Arr<pair<T,int>> r;
	for(int i=0;i<sz(a);i++)
		r.emplb(a[i],i);
	return r;
}