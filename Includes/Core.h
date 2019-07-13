#pragma once
#ifndef DEBUG 
	#pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>

using namespace std;
using f64 = double;using i64=long long;using u64=unsigned long long;

#define hfor(var, s, e) for(int var=s; s<=var && var<e; ++var)//half-opened range
#define hfori(var, s, e) for(int var=e-1; s<=var && var<e; --var)//inversion
#define hforo(var, s, e) int var=s; for(; s<=var && var<e; ++var)//out declaration
#define hforoi(var, s, e) int var=e-1; for(; s<=var && var<e; --var)
#define cfor(var, s, e) hfor(var, s, (e)+1)//closed range
#define cfori(var, s, e) hfori(var, s, (e)+1)
#define cforo(var, s, e) hforo(var, s, (e)+1)
#define cforoi(var, s, e) hforoi(var, s, (e)+1)
#define rep(x) hfor(repi,0,x)
#define all(x) x.begin(),x.end()
#define sum_in(s,e) accumulate(s,e,0ll)
#define mri(it) make_reverse_iterator(it)//*mri(it) == *prev(it)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define sz(x) (int)size(x)
#define gcd __gcd

template<typename C, typename RI> RI rerase(C& c, RI ri){return next(mri(c.erase(prev(ri.base()))));}
template<typename T> constexpr T inf() { return numeric_limits<T>::max() / 2; }
int rand(int lb, int ub){static mt19937 rng(time(0)^i64(new int)); return uniform_int_distribution<int>(lb, ub-1)(rng);}
int rand(int ub){return rand(0,ub);}
int rand(){return rand(inf<int>());}

const f64 pi=acos(-1), eps=1e-12;
const int prime=998244353;//1073741783 int(2e9+11) int(1e9+9)
const int mod=int(1e9+7);
auto ___=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(11)), srand((int)time(0)), 0);