#pragma once
#include "core/std.h"
#include "core/config.h"

#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define lb lower_bound
#define ub upper_bound
#define itos to_string
#define head(x) (x.begin())
#define tail(x) prev(x.end())
using i32=signed;
using u32=unsigned;
using i64=long long;
using u64=unsigned long long;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;
template<class T,class CMP=less<>>using PQ=std::priority_queue<T,vector<T>,CMP>;

template<class T, class U> istream& operator>>(istream& is, pair<T,U>& a){ return is>>a.fi>>a.se; }
template<typename... Args, size_t... Is>
void read_tuple(istream& is, tuple<Args...>& tuple, index_sequence<Is...>) { (..., (is >> std::get<Is>(tuple)));}
template<typename... Args>
istream& operator>>(istream& is, tuple<Args...>& tuple){
	read_tuple(is, tuple, index_sequence_for<Args...>{});
	return is;
}
template<class T>concept PrintPrimitive=requires(T x){cout<<x;};
template<class T>concept NotPrintPrimitive=not PrintPrimitive<T>;
template<class T>concept InputPrimitive=requires(T x){cin>>x;};
template<class T>concept NotInputPrimitive=not InputPrimitive<T>;
template<class T>concept Iterable=requires(T x){x.begin();x.end();begin(x);end(x);};
