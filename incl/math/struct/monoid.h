#pragma once
#include "core.h"

template<typename T>
concept Monoid=requires(T t){
	T::f(T::id(),T::id());
	T::fn(T::id(),0);
	//T::T;
};

template<class T, class M> T fn(T x,int n){
	//f(...f(f(id,x),x),...,x) n겹 O(log(n))
	if(!n)return M::id();
	T res=fn<T,M>(x,n/2);
	return n%2?M::f(M::f(res,res),x):M::f(res,res);
}

template<class T, T _id=T(0)>struct MAdd{
	static T id(){return _id;}
	static T f(T x,T y){return x+y;}
	static T fn(T x,int n){return x*n;}
};
template<class T, T _id=T(1)>struct MMul{
	static T id(){return _id;}
	static T f(T x,T y){return x*y;}
	static T fn(T x,int n){return ::fn<T,MMul<T>>(x,n);}
};
template<class T, T _id=nan<T>()>struct MAss{
	static T id(){return _id;}
	static T f(T x,T y){return y==id()?x:y;}
	static T fn(T x,int n){return x;}
};
template<class T, T _id=nan<T>()>struct MAssOnce{
	static T id(){return _id;}
	static T f(T x,T y){return x==id()?y:x;}
	static T fn(T x,int n){return x;}
};
template<class T, T _id=inf<T>()>struct MMin{
	static T id(){return _id;}
	static T f(T x,T y){return min(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T, T _id=-inf<T>()>struct MMax{
	static T id(){return _id;}
	static T f(T x,T y){return max(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T, T _id=T(0)>struct MXor{
	static T id(){return _id;}
	static T f(T x,T y){return x^y;}
	static T fn(T x,int n){return n%2?x:0;}
};
template<class T, T _id=T(0)>struct MGcd{
	static T id(){return _id;}
	static T f(T x,T y){return gcd(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T, T _id=T()>struct MFunc{
	static T id(){return _id;}
	static T f(T x,T y){return x.f(y);}
	static T fn(T x,int n){return ::fn<T,MFunc<T>>(x,n);}
};

// https://codeforces.com/contest/1691/submission/159072343
// NOTE: non-empty. empty-able일시 max(0,val.m)하면 됨
struct TMaxSubArr{
	int s=0,l=-inf<int>(),m=-inf<int>(),r=-inf<int>();
	TMaxSubArr f(TMaxSubArr x)const{return {s+x.s,max(l,s+x.l),max({m,r+x.l,x.m}),max(r+x.s,x.r)};}
	friend strong_ordering operator<=>(const TMaxSubArr&,const TMaxSubArr&)=default;
	TMaxSubArr rev()const{return {s,r,m,l};}//for commutativeless query, refer boj13519
};
template<Monoid M>
auto scanl(auto s,auto e){
	using T=decltype(M::id()); int n=e-s;
	Arr<T> b={M::id()};
	while(s!=e)
		b.emplace_back(M::f(b.back(),*s++));
	rotate(b.begin(),b.begin()+1,b.end());
	return b;
}
template<Monoid M>
auto scanr(auto s,auto e){
	using T=decltype(M::id()); int n=e-s;
	Arr<T> b={M::id()};
	while(s!=e)
		b.emplace_back(M::f(b.back(),*--e));
	reverse(b.begin(),b.end());
	return b;
}
