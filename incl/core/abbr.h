#pragma once
#include "core/std.h"
#include "core/config.h"

#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define itos to_string
#define head(x) (x.begin())
#define tail(x) prev(x.end())
#define dbg(...) void(0)
#define dbgif(...) void(0)
#define dbg1(...) void(0)
#define dbg1if(...) void(0)
using i64=long long;using u64=unsigned long long;using u32=unsigned;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;
template<class T,class CMP=less<>>using PQ=std::priority_queue<T,vector<T>,CMP>;

#if CPP20
template<class T>concept Printable=requires(T x){cout<<x<<endl;};
template<class T>concept NotPrintable=not Printable<T>;
template<class T>concept Iterable=requires(T x){x.begin();x.end();begin(x);end(x);};
#endif