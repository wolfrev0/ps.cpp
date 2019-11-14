#pragma once
#ifndef DEBUG 
	#pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>

using namespace std;

using f64 = double;using i64=long long;using u64=unsigned long long;
template<typename T> using Arr=vector<T>;
#define PQ std::priority_queue

#define hfor(v, s, e) for(int v=s; s<=v && v<e; ++v)//half-opened range
#define hfori(v, s, e) for(int v=e-1; s<=v && v<e; --v)//inversion
#define hforo(v, s, e) int v=s; for(; s<=v && v<e; ++v)//out declaration
#define hforoi(v, s, e) int v=e-1; for(; s<=v && v<e; --v)
#define cfor(v, s, e) hfor(v, s, (e)+1)//closed range
#define cfori(v, s, e) hfori(v, s, (e)+1)
#define cforo(v, s, e) hforo(v, s, (e)+1)
#define cforoi(v, s, e) hforoi(v, s, (e)+1)
#define rep(v,x) hfor(v,0,x)
#define repi(v,x) hfori(v,0,x)
#define all(x) x.begin(),x.end()
#define pushb push_back
#define pushf push_front
#define popb pop_back
#define popf pop_front
#define emplb emplace_back
#define emplf emplace_front
#define empl emplace
#define fi first
#define se second
#define gcd __gcd

template<typename T> constexpr T inf() { return numeric_limits<T>::max() / 2; }
auto mri(auto it){ return make_reverse_iterator(it); }//*mri(it) == *prev(it)
auto rerase(auto& c, auto ri){ return next(mri(c.erase(prev(ri.base())))); }
auto fold(auto a, auto b, auto c, auto f){ return accumulate(a,b,c,f); }
auto fold(auto a, auto b, auto c){ return fold(a,b,c,[](auto acc, auto x){return acc+x;}); }
auto mapf(auto a, auto f){for(auto& x:a)x=f(x); return a;}
int sz(const auto& x){ return (int)x.size(); }
int rd(int lb, int ub){static mt19937 rng(time(0)^i64(new int)); return uniform_int_distribution<int>(lb, ub-1)(rng);}
int rd(int ub=inf<int>()){return rd(0,ub);}
#define random rd

const f64 pi=acos(-1), eps=1e-12;
const int prime=998244353;//1073741783 int(2e9+11) int(1e9+9)
const int mod=int(1e9+7);
#ifndef DEBUG
	auto __PRE_RUN__=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(11)), 0);
#endif