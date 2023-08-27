#pragma once
#include "core/std.h"
#include "core/config.h"
#include "core/func1.h"
#include "core/debug.h"

template<class T, class P=vector<T>>
struct Arr:public P{
	Arr(){P::shrink_to_fit();}
	explicit Arr(i32 n):P(n,T()){}
	explicit Arr(i32 n,T init):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
	Arr(auto its, auto ite):P(its,ite){}
	inline T& operator[](i32 i){return P::operator[](i<0?i+sz(*this):i);}
	const T& operator[](i32 i)const{return P::operator[](i<0?i+sz(*this):i);}
	T& at(i32 i){return *this[i];}
	const T& at(i32 i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}
