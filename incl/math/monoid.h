#pragma once

#include "core/config.h"
#include "core/arr.h"

template<class T>
struct Monoid{
	function<T(T,T)> f; T id;
	Monoid(function<T(T,T)> f,T id=T()):f(f),id(id){}
};
#define MPLUS(T) Monoid<T>(lamp(x+y,T x,T y),T(0))
#define MMIN(T) Monoid<T>(lamp(min(x,y),T x,T y),inf<T>())
#define MMAX(T) Monoid<T>(lamp(max(x,y),T x,T y),-inf<T>())
#define MXOR(T) Monoid<T>(lamp(x^y,T x,T y),T(0))
#define MMUL(T) Monoid<T>(lamp(x*y,T x,T y),T(1))
#define MASS(T) Monoid<T>(lamp(y,T x,T y),inf<T>()+1)

template<class T>
Arr<T> cumf(const Arr<T>& a, const Monoid<T>& m=MPLUS(T)){
	Arr<T> b(sz(a)+1,m.id);
	for(int i=0;i<sz(a);i++)
		b[i]=m.f(b[i-1],a[i]);
	return b;
}
template<class T>
Arr<T> cumb(const Arr<T>& a, const Monoid<T>& m=MPLUS(T)){
	Arr<T> b(sz(a)+1,m.id);
	for(int i=sz(a)-1;~i;i--)
		b[i]=m.f(b[i-1],a[i]);
	return b;
}