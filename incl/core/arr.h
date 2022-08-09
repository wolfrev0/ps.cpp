#pragma once
#include "core/std.h"
#include "core/config.h"
#include "core/func1.h"
#include "core/debug.h"

template<class T, class P=vector<T>>
struct Arr:public P{
	Arr(){P::shrink_to_fit();}
	explicit Arr(signed n):P(n){}
	explicit Arr(signed n,T init):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
	Arr(auto its, auto ite):P(its,ite){}
	inline T& operator[](signed i){
		int n=sz(*this);
		if(i<0)
			i+=n,dbg1("Neg Index Found");
		if(i>=n)
			i-=n,dbg1("Over Index Found");
		return P::operator[](i);
	}
	const T& operator[](signed i)const{	
		int n=sz(*this);
		if(i<0)
			i+=n,dbg1("Neg Index Found");
		if(i>=n)
			i-=n,dbg1("Over Index Found");
		return P::operator[](i);
	}
	T& at(signed i){return *this[i];}
	const T& at(signed i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}