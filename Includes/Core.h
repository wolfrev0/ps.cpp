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
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define gcd __gcd

template<typename T> constexpr T inf() { return numeric_limits<T>::max() / 2; }
auto mri(auto it){ return make_reverse_iterator(it); }//*mri(it) == *prev(it)
auto rerase(auto& c, auto ri){ return next(mri(c.erase(prev(ri.base())))); }
auto accumulate(auto a, auto b, int c=0){ return std::accumulate(a,b,i64(c)); }
auto sum(auto a, auto b){return accumulate(a,b);}
int size(auto x){ return (int)x.size(); }
int rd(int lb, int ub){static mt19937 rng(time(0)^i64(new int)); return uniform_int_distribution<int>(lb, ub-1)(rng);}
int rd(int ub=inf<int>()){return rd(0,ub);}
#define random rd

const f64 pi=acos(-1), eps=1e-12;
const int prime=998244353;//1073741783 int(2e9+11) int(1e9+9)
const int mod=int(1e9+7);
auto ___=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(11)), srand((int)time(0)), 0);