#pragma once
#include <bits/stdc++.h>
using namespace std;using f64 = double;using i64=long long;using u64=unsigned long long;
template<typename T> using Arr=vector<T>;
#define hfor(v, s, e) for(int v=(s);(s)<=v&&v<(e);++v)//half-opened range
#define hfori(v, s, e) for(int v=(e)-1;(s)<=v&&v<(e);--v)//inversion
#define cfor(v, s, e) hfor(v,(s),(e)+1)//closed range
#define cfori(v, s, e) hfori(v,(s),(e)+1)
#define rep(v,x) hfor(v,0,(x))
#define repi(v,x) hfori(v,0,(x))
#define all(x) (x).begin(),(x).end()
#define pushb push_back
#define pushf push_front
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
//template<typename T> cxp T inf() { return numeric_limits<T>::max() / 2; }
template<typename T> inline T sq(T x){return x*x;}
const f64 pi=acosl(-1), eps=1e-10;
#ifndef DEBUG
	auto __PRE_RUN__=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(11)), 0);
#endif
int sz(const auto& x){return x.size();}
#define lam(expr, ...) [&](__VA_ARGS__){return expr;}