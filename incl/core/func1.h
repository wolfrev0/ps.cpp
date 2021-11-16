#pragma once
#include "core/config.h"
#include "core/abbr.h"

//Handy Funcs
template<class T>int sz(const T& x){return x.size();}
template<class T>cxp T inf(){return numeric_limits<T>::max()/2;}
int divc(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?(a+b-1)/b:a/b;}
int divf(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?a/b:(a-b+1)/b;}
cxp i64 lg2f(i64 x){return 63-__builtin_clzll(x);}
cxp i64 lg2c(i64 x){return 64-__builtin_clzll(x-1);}
template<class T>T sq(T x){return x*x;}

void WARN(bool cond,const char* str){
	#if DEBUG
	static set<const char*> z;
	if(cond&&!z.count(str))z.insert(str),cerr<<"[WARN] "<<str<<endl;
	#endif
}