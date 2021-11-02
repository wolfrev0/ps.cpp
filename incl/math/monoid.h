#pragma once

#include "core/config.h"
#include "core/arr.h"

#ifdef CPP20

template<class T, auto _f=[](T x,T y){return x+y;}, T _id=0>
struct Monoid{static cxp auto f=_f,id=_id;};

template<class T> struct MonoidPlus:Monoid<T,[](T x,T y){return x+y;},T(0)>{};
template<class T> struct MonoidMin:Monoid<T,[](T x,T y){return min(x,y);},inf<T>()>{};
template<class T> struct MonoidMax:Monoid<T,[](T x,T y){return max(x,y);},-inf<T>()>{};
template<class T> struct MonoidXor:Monoid<T,[](T x,T y){return x^y;},T(0)>{};
template<class T> struct MonoidMul:Monoid<T,[](T x,T y){return x*y;},T(1)>{};
template<class T> struct MonoidAss:Monoid<T,[](T x,T y){return y;},inf<T>()*2>{};
template<class T,T id=inf<T>()*2> struct MonoidAssOnce:Monoid<T,[](T x,T y){return x==id?y:x;},id>{};

template<class T, class M=Monoid<T>>
Arr<T> cumf(const Arr<T>& a){
	Arr<T> b(sz(a)+1,M::id);
	for(int i=0;i<sz(a);i++)
		b[i]=M::f(b[i-1],a[i]);
	return b;
}

#endif