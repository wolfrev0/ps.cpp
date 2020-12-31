#pragma once
#include "Core.h"

template <class T, typename = void>
struct is_iterable : false_type {};
template <class T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

template<class A, class B, typename enable_if<!is_iterable<pair<A,B>>::value,int>::type = 0>
void debug(const pair<A,B>& a, int d=0);
template<class TupType, size_t... I>
void debug(const TupType& _tup, index_sequence<I...>, int d=0);
template<class... T>
void debug (const tuple<T...>& _tup, int d=0);

template<class T, typename enable_if<!is_iterable<T>::value,int>::type = 0>
void debug(const T& a, int d=0){cerr<<a<<',';}
template<class T, typename enable_if<is_iterable<T>::value,int>::type = 0>
void debug(const T& a, int d=0){
	static string ob="[{(", cb="]})";
	cerr<<endl<<string(d,' ')+ob[d%sz(ob)];
	for(const auto& i:a)debug(i,d+1);
	cerr<<cb[d%sz(ob)];
}
template<class A, class B, typename enable_if<!is_iterable<pair<A,B>>::value,int>::type = 0>
void debug(const pair<A,B>& a, int d){cerr<<endl<<string(d,' ')+'<'; debug(a.fi,d+1); debug(a.se,d+1);cerr<<'>';}
template<class TupType, size_t... I>
void debug(const TupType& _tup, index_sequence<I...>, int d){cerr<<endl<<string(d,' ')+'<'; (..., debug(get<I>(_tup),d+1)); cerr<<'>';}
template<class... T>
void debug(const tuple<T...>& _tup, int d){debug(_tup, make_index_sequence<sizeof...(T)>(), d);}
