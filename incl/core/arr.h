#pragma once
#include "core/std.h"
#include "core/config.h"
#include "core/func.h"

template<class T, class P=
#if CPP20
conditional_t<is_same<bool,T>::value,deque<T>,vector<T>>>
#else
vector<T>>
#endif
struct Arr:public P{
	Arr():Arr(0){P::shrink_to_fit();}
	explicit Arr(signed n,T init=T()):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
#ifdef CPP20
	Arr(auto its, auto ite):P(its,ite){}
#endif
	T& operator[](signed i){
		WARN(i<0,"Negative Index Found");
		return P::operator[](i>=0?i:i+this->size());
	}
	const T& operator[](signed i)const{return P::operator[](i>=0?i:i+this->size());}
	T& at(signed i){return *this[i];}
	const T& at(signed i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}