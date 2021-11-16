#pragma once
#include "core/std.h"
#include "core/config.h"

#define pushb(...) push_back({__VA_ARGS__})
#define pushf(...) push_front({__VA_ARGS__})
#define push_(...) push({__VA_ARGS__})
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define cxp constexpr
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define reduce accumulate
#define itos to_string
using i64=long long;using u64=unsigned long long;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;
template<class T,class CMP=greater<>>using PQ=std::priority_queue<T,vector<T>,CMP>;

#define head(x) (x.begin())
#define tail(x) prev(x.end())