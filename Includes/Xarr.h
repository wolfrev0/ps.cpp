#pragma once
#include "Core.h"

template<typename T>
struct Xarr{
	Xarr(int n=0, const T& init=T(), int offset=1):offset(offset), a(n+offset, init){}
	T& operator[](int idx){return a[idx+offset];}
	auto begin(){return a.begin();}
	auto end(){return a.end();}
	int offset;
	Arr<T> a;
};