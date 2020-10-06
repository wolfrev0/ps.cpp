#pragma once
#include <bits/stdc++.h>

//Settings
#define INT64 0 //MLE?
#define INTERACTIVE 0
#define COUT_PRECISION 11
#define C20 1

//Common
#define hfor(v, s, e) for(int v=(s);(s)<=v&&v<(e);++v)//half-opened range
#define hfori(v, s, e) for(int v=(e)-1;(s)<=v&&v<(e);--v)//inversion
#define hforo(v, s, e) int v=(s);for(;(s)<=v&&v<(e);++v)//out declaration
#define hforoi(v, s, e) int v=(e)-1; for(;(s)<=v&&v<(e);--v)
#define cfor(v, s, e) hfor(v,(s),(e)+1)//closed range
#define cfori(v, s, e) hfori(v,(s),(e)+1)
#define cforo(v, s, e) hforo(v,(s),(e)+1)
#define cforoi(v, s, e) hforoi(v,(s),(e)+1)
#define rep(v,x) hfor(v,0,(x))
#define repi(v,x) hfori(v,0,(x))
#define repo(v,x) hforo(v,0,(x))
#define all(x) (x).begin(),(x).end()
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
#define PQMAX(...) std::priority_queue<__VA_ARGS__>
#define PQMIN(...) std::priority_queue<__VA_ARGS__,Arr<__VA_ARGS__>,greater<__VA_ARGS__>>
#define lb lower_bound
#define ub upper_bound
#define unify(x) sort(all(x)),x.erase(unique(all(x)),x.end())
#if INT64
	#define int i64
#endif
using namespace std;using f64 = double;using i64=long long;using u64=unsigned long long;
using pint = pair<int,int>; using tint = tuple<int,int,int>;
template<class T> using Arr=vector<T>;template<class T> using Func=function<T>;template<class T> using Str=basic_string<T>;
template<class T> int sz(const T& x){return x.size();}

//Math
template<class T> cxp T inf() { return numeric_limits<T>::max() / 2; }
template<class T> inline T sq(T x){return x*x;}
cxp int lgc(int x){return 64-__builtin_clzll(x-1);}
cxp int lgf(int x){return 63-__builtin_clzll(x);}
const f64 pi=acosl(-1), eps=1e-10;

//IO
#if !(DEBUG)
	auto __PRE_RUN__=(ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),(cout<<fixed<<setprecision(COUT_PRECISION)), 0);
	#if !(INTERACTIVE)
		#define endl '\n'//interactive?
	#endif
#endif

//Misc
//#pragma GCC optimize ("Ofast")
#ifdef DEBUG
	mt19937 _rng(i64(new int)+time(0));
#else
	mt19937 _rng(i64(new int));
#endif
int rd(){static uniform_int_distribution<int> dist(0,inf<int>()); return dist(_rng);}
int rd(int e){return rd()%e;}
int rd(int s, int e){return rd()%(e-s)+s;}
f64 rdf(){static uniform_real_distribution<f64> dist(0,1); return dist(_rng);}
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
	template<class... Args> void _cin_(Args&... arg) { ((cin>>arg),...); }
	#define CIN(T,...) T __VA_ARGS__; _cin_(__VA_ARGS__);
	template<class... Args> void _cout_(Args... arg) { ((cout<<arg<<' '),...); }
	#define COUT(...) _cout_(__VA_ARGS__), cout<<endl;
	template<class T> T dupl(const T& x, int n){ T r; rep(_,n)r.insert(r.end(),all(x)); return r; }
#endif
