#pragma once

#include "core/config.h"
#include "core/arr.h"
//Monoid
#ifdef CPP20
template<class T, auto _f=[](T x,T y){return x+y;}, T _id=0>
struct Monoid{static cxp auto f=_f,id=_id;};
template<class T, class M=Monoid<T>>
Arr<T> cumf(const Arr<T>& a){
	Arr<T> b(sz(a)+1,M::id);
	for(int i=0;i<sz(a);i++)
		b[i]=M::f(b[i-1],a[i]);
	return b;
}
#endif