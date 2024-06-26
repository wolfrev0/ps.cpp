//functions after include <arr.h>
#pragma once
#include "core/arr.h"

template<class T>int argmin(const Arr<T>& a){return min_element(a.begin(),a.end())-a.begin();}
template<class T>int argmax(const Arr<T>& a){return max_element(a.begin(),a.end())-a.begin();}
template<Iterable T> map<typename T::value_type,Arr<int>> classify(const T& a){
	map<typename T::value_type,Arr<int>> r;
	int idx=0;
	for(auto x:a)
		r[x].push_back(idx++);
	return r;
}
template<class T=int,class... Ts> requires InputPrimitive<T>
tuple<T,Ts...> input(istream& is=cin){
	T x; is>>x;
	if constexpr (sizeof...(Ts)==0) return mkt(x);
	else return tuple_cat(mkt(x),input<Ts...>());
}
template<class T> requires InputPrimitive<T>
T input(T&& a, istream& is=cin){ is>>a; return a;}
template<class T> requires NotInputPrimitive<T>&&Iterable<T>
T input(T&& a){ for(auto&i:a)input(i); return a; }
template<class T=int> T input1(istream& is=cin){return get<0>(input<T>());}
