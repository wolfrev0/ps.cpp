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
#define debug(...)
using i64=long long;using u64=unsigned long long;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;
template<class T,class CMP=greater<>>using PQ=std::priority_queue<T,vector<T>,CMP>;