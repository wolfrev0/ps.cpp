#pragma once
#include "core/func1.h"
#include "core/config.h"

template<class T,typename=void> struct is_iterable:false_type{};
template<class T> struct is_iterable<T,void_t<decltype(begin(declval<T>())),decltype(end(declval<T>()))>>:true_type{};

template<class A,class B,typename enable_if<!is_iterable<pair<A,B>>::value,int>::type=0>
void debug(const pair<A,B>& a,int d=0);
template<class TupType,size_t... I>
void debug(const TupType& _tup,index_sequence<I...>,int d=0);
template<class... T> void debug(const tuple<T...>& _tup,int d=0);

template<class T,typename enable_if<!is_iterable<T>::value,int>::type=0>
void debug(const T& a,int d=0){
	cerr<<setw(DBG_SETW)<<a<<',';
	if(!d)cerr<<endl;}
template<class T,typename enable_if<is_iterable<T>::value,int>::type=0>
void debug(const T& a,int d=0){
	static string ob="[{(",cb="]})";
	cerr<<endl<<string(d,' ')+ob[d%sz(ob)];
	for(const auto& i:a)debug(i,d+1);
	cerr<<cb[d%sz(ob)];
	if(!d)cerr<<endl;}
template<class A,class B,typename enable_if<!is_iterable<pair<A,B>>::value,int>::type=0>
void debug(const pair<A,B>& a,int d){
	cerr<<endl<<string(d,' ')+'<';
	debug(a.fi,d+1);
	debug(a.se,d+1);
	cerr<<'>';
	if(!d)cout<<endl;}
template<class TupType,size_t... I>
void debug(const TupType& _tup,index_sequence<I...>,int d){
	cerr<<endl<<string(d,' ')+'<';
	(...,debug(get<I>(_tup),d+1));
	cerr<<'>';
	if(!d)cout<<endl;}
template<class... T> void debug(const tuple<T...>& _tup,int d){
	debug(_tup,make_index_sequence<sizeof...(T)>(),d);
	if(!d)cout<<endl;}

#if DEBUG
	#define watch(...)(cerr<<(#__VA_ARGS__)<<";=",debug(mkt(__VA_ARGS__)))
#else
	#define watch(...)
#endif