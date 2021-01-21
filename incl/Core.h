#pragma once
#include <bits/stdc++.h>

//Settings
#define INT64 1 //MLE?
#define INTERACTIVE 0
#define FP_PRECISION 11
#define C20 1

//Common
#define forh(v, s, e) for(int v=(s);(s)<=v&&v<(e);++v)//half-opened range
#define forhi(v, s, e) for(int v=(e)-1;(s)<=v&&v<(e);--v)//inversion
#define forho(v, s, e) int v=(s);for(;(s)<=v&&v<(e);++v)//out declaration
#define forhoi(v, s, e) int v=(e)-1; for(;(s)<=v&&v<(e);--v)
#define forc(v, s, e) forh(v,(s),(e)+1)//closed range
#define forci(v, s, e) forhi(v,(s),(e)+1)
#define forco(v, s, e) forho(v,(s),(e)+1)
#define forcoi(v, s, e) forhoi(v,(s),(e)+1)
#define rep(v,x) forh(v,0,(x))
#define repi(v,x) forhi(v,0,(x))
#define repo(v,x) forho(v,0,(x))
#define repoi(v,x) forhoi(v,0,(x))
#define all(x) begin(x),end(x)
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
#define PQ std::priority_queue
#define lb lower_bound
#define ub upper_bound
#define unify(x) sort(all(x)),x.erase(unique(all(x)),x.end())
#if INT64
	#define int i64
#endif
using namespace std;
using i64=long long;
using u64=unsigned long long;
using f64 = double;
using pint = pair<int,int>;
using tint = tuple<int,int,int>;
template<class T> using Arr=vector<T>;
template<class T> using Func=function<T>;
template<class T> using Str=basic_string<T>;
template<class T> using PQMax=PQ<T>;
template<class T> using PQMin=PQ<T,Arr<T>,greater<T>>;
template<class T> int sz(const T& x){return x.size();}

//Math
template<class T> cxp T inf() { return numeric_limits<T>::max() / 2; }
template<class T> inline T sq(T x){return x*x;}
cxp int lgc(int x){return 64-__builtin_clzll(x-1);}
cxp int lgf(int x){return 63-__builtin_clzll(x);}
const f64 pi=acosl(-1), eps=1e-10;

//IO
#if !(DEBUG)
	auto __PRE_RUN__=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(FP_PRECISION)), 0);
	#if !(INTERACTIVE)
		#define endl '\n'//interactive?
	#endif
#endif

//Random
mt19937 _rng(i64(new int)^time(0));
int rd(){static uniform_int_distribution<int> dist(0,inf<int>()); return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s, int e){return rd()%(e-s)+s;}
f64 rdf(){static uniform_real_distribution<f64> dist(0,1); return dist(_rng);}

//Misc
//#pragma GCC optimize ("Ofast")
template<class T> T rev(const T& a){return {a.rbegin(),a.rend()};}
Arr<int> range(int n){ Arr<int> ret(n); rep(i,n)ret[i]=i; return ret; }
#define lam(expr, ...) [&](__VA_ARGS__){return expr;}
#define reduce accumulate
#if C20
	void shuffle(auto is, auto ie){shuffle(is,ie,_rng);}
	struct defer{ defer(auto f):f(f){} ~defer(){f();} function<void()> f; };
	#define defer(x) auto _##__COUNTER__ = defer([&](){x;});
	template<class... A>
	auto ARR(auto n, A&&...a){
		if constexpr(sizeof...(a)==0) return n;
		else return vector(n,ARR(a...));
	}
#endif
