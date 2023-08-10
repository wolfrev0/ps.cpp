//functions before include <arr.h>
#pragma once
#include "core/config.h"
#include "core/abbr.h"

//Math
#if !(CPP20)
	#define countl_zero(x) __builtin_clzll(x)
	#define popcount(x) __builtin_popcountll(x)
	#define bit_ceil(x) (1<<clg2(x))
#endif
#if CPP20
	#define sz ssize
#else
	template<class T>int sz(const T& x){return x.size();}
#endif
int fdiv(int a,int b){return a/b-((a^b)<0&&a%b);}
int cdiv(int a,int b){return (a^b>0)?(a+b-1)/b:a/b;}
i64 flg2(u64 x){return 63-countl_zero(x);}
i64 clg2(u64 x){return x-1==0?0:64-countl_zero(x-1);}
int fsqrt(i64 n) {i64 i=sqrtl(n);while(i*i>n)i--;while(i*i<=n)i++;return i-1;}
int csqrt(i64 n) {i64 i=sqrtl(n);while(i*i>=n)i--;while(i*i<n)i++;return i;}
template<class T>T sq(T x){return x*x;}
template<class T>constexpr T inf(){return numeric_limits<T>::max()/2;}
template<class T>constexpr T nan(){return numeric_limits<T>::max();}
#if CPP20
template<typename T> concept MemberInf=requires(T t){t.inf();};
template<typename T> concept MemberNan=requires(T t){t.nan();};
template<MemberInf T>T inf(){return T().inf();}
#endif

//IO & misc
template<class...A>ostream& osprint(ostream& os, A...a){return ((os<<a),...);}
#define print(...) osprint(cout,__VA_ARGS__)
#define println(...) osprint(cout,__VA_ARGS__,'\n')
template<class T,class U>bool assmin(T& a,U&& b){return a>b?a=b,true:false;}
template<class T,class U>bool assmax(T& a,U&& b){return a<b?a=b,true:false;}
#define ARG(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}
#define lamp(expr,...) [](__VA_ARGS__){return expr;}

auto key2cmp(auto key){return [key](auto x, auto y){return mkp(key(x),x)<mkp(key(y),y);};}
auto fmap(auto a, auto f)->remove_reference_t<decltype(a)>{
	auto b=a;
	for(auto&i:b)
		i=f(i);
	return b;
}