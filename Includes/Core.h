#pragma once
#ifndef DEBUG 
	#pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>
using namespace std;

#define hfor(var, s, e) for(int var=s; int(s)<=var && var<int(e); ++var)//half-opened range
#define hfori(var, s, e) for(int var=e-1; int(s)<=var && var<int(e); --var)//inversion
#define hforo(var, s, e) int var=s; for(; int(s)<=var && var<int(e); ++var)//out declaration
#define hforoi(var, s, e) int var=e-1; for(; int(s)<=var && var<int(e); --var)
#define cfor(var, s, e) hfor(var, s, e+1)//closed range
#define cfori(var, s, e) hfori(var, s, e+1)
#define cforo(var, s, e) hforo(var, s, e+1)
#define cforoi(var, s, e) hforoi(var, s, e+1)
#define rep(x) hfor(repi,0,x)
#define all(x) x.begin(),x.end()
#define sum_in(s,e) accumulate(s,e,0ll)
#define mri(it) make_reverse_iterator(it)//*mri(it) == *prev(it)
template<typename C, typename RI> RI rerase(C& c, RI ri){return next(mri(c.erase(prev(ri.base()))));}
template<typename T> T inf() { return numeric_limits<T>::max() / 2; }
using f64 = double;using i64=long long;using u64=unsigned long long;
const f64 pi=acos(-1), eps=1e-12;
const int prime=998244353;//1073741783 int(2e9+11) int(1e9+9)
const int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//r, cw
const int mod=int(1e9+7);

auto _dummy=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),
(cout<<fixed<<setprecision(11)), srand((int)time(0)), 0);