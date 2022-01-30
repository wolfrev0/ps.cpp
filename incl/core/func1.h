//functions before include <arr.h>
#pragma once
#include "core/config.h"
#include "core/abbr.h"

//Math
template<class T>int sz(const T& x){return x.size();}
int fdiv(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?a/b:(a-b+1)/b;}
int cdiv(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?(a+b-1)/b:a/b;}
i64 flg2(i64 x){return 63-__builtin_clzll(x);}
i64 clg2(i64 x){return 64-__builtin_clzll(x-1);}
int fsqrt(i64 n) {i64 i=1;while(i*i<=n)i++;return i-1;}
int csqrt(i64 n) {i64 i=1;while(i*i<n)i++;return i;}
template<class T>T sq(T x){return x*x;}
template<class T>T inf(){return numeric_limits<T>::max()/2;}
template<class T>T nan(){return inf<T>()+1;}
#ifdef CONCEPT
template<typename T> concept MemberInf=requires(T t){t.inf();};
template<typename T> concept MemberNan=requires(T t){t.nan();};
template<MemberInf T>T inf(){return T().inf();}
template<MemberNan T>T nan(){return T().nan();}
#endif

//IO & misc
template<char endch=0,char sepch=' ',class... A>
void print(A...a){((cout<<a<<sepch),...,(cout<<(!endch?"":string(1,endch))));}
template<class T,class U>bool assmin(T& a,U&& b){return a>b?a=b,true:false;}
template<class T,class U>bool assmax(T& a,U&& b){return a<b?a=b,true:false;}
void WARN(bool cond,const char* str){
#if DEBUG
	static set<const char*> z;
	if(cond&&!z.count(str))z.insert(str),cerr<<"[WARN] "<<str<<endl;
#endif
}
void MUST(bool expr){
#if DEBUG
	#include <csignal>
	if(!expr)
		raise(SIGINT);
#endif
}
#define ARG(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}
#define lamp(expr,...) [](__VA_ARGS__){return expr;}