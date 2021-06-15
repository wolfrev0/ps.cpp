#pragma once
#include "core/std.h"
//Arr
template<class T, class P=
#if CPP20
conditional_t<is_same<bool,T>::value,deque<T>,vector<T>>>
#else
vector<T>>
#endif
struct Arr:public P{
	Arr():Arr(0){}
	explicit Arr(int n,T init=T()):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
#ifdef CPP20
	Arr(auto its, auto ite):P(its,ite){}
#endif
	T& operator[](int i){
		#if DEBUG
		static bool _z=false;
		if(i<0&&!_z)_z=true,cerr<<"[INFO] Negative Index Found"<<endl;
		#endif
		return P::operator[](i>=0?i:i+this->size());
	}
	const T& operator[](int i)const{return P::operator[](i>=0?i:i+this->size());}
	T& at(int i){return *this[i];}
	const T& at(int i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}