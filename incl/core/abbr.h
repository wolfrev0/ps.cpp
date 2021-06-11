#pragma once

//Abbrevs
#if INT64
#define int i64
#endif
#define pushb push_back
#define pushf push_front
#define popb pop_back
#define popf pop_front
#define empl emplace
#define emplb emplace_back
#define emplf emplace_front
#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define cxp constexpr
#define lb lower_bound
#define ub upper_bound
#define reduce accumulate
using i64=long long;using u64=unsigned long long;using f64=double;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;