#pragma once
#include "Core.h"

template<typename T>
struct Monoid{
	virtual T f(T a, T b)const=0;
	virtual T id()const=0;
	virtual T fn(T a, int n)const{if(n==0)return id(); return f(a,fn(a,n-1));}
};
template<typename T>
struct MonoidPlus:Monoid<T>{
	T f(T a, T b)const{return a+b;}
	T id()const{return T(0);}
	T fn(T a, int n)const{return a*n;}
};
template<typename T>
struct MonoidMin:Monoid<T>{
	T f(T a, T b)const{return min(a,b);}
	T id()const{return inf<T>();}
	T fn(T a, int n)const{return a;}
};
template<typename T>
struct MonoidMax:Monoid<T>{
	T f(T a, T b)const{return max(a,b);}
	T id()const{return -inf<T>();}
	T fn(T a, int n)const{return a;}
};