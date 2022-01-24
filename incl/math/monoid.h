#pragma once

#include "core/config.h"
#include "core/arr.h"

#ifdef CONCEPT
	template<typename T>
	concept Monoid=requires(T t){
		T::f(T::id(),T::id());
		T::fn(T::id(),0);
		//T::T;
	};
#else
	#define Monoid class
#endif

template<class T, class M> T fn(T x,int n){
	//f(...f(f(id,x),x),...,x) n겹 O(log(n))
	if(!n)return M::id();
	T res=fn<T,M>(x,n/2);
	return n%2?M::f(M::f(res,res),x):M::f(res,res);
}

template<class T>struct MAdd{
	static T id(){return T(0);}
	static T f(T x,T y){return x+y;}
	static T fn(T x,int n){return x*n;}
};
template<class T>struct MMul{
	static T id(){return T(1);}
	static T f(T x,T y){return x*y;}
	static T fn(T x,int n){return ::fn<T,MMul<T>>(x,n);}
};
template<class T>struct MAss{
	static T id(){return nan<T>();}
	static T f(T x,T y){return y==id()?x:y;}
	static T fn(T x,int n){return x;}
};
template<class T>struct MMin{
	static T id(){return inf<T>();}
	static T f(T x,T y){return min(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T>struct MMax{
	static T id(){return -inf<T>();}
	static T f(T x,T y){return max(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T>struct MXor{
	static T id(){return T(0);}
	static T f(T x,T y){return x^y;}
	static T fn(T x,int n){return n%2?x:0;}
};
template<class T>struct MGcd{
	static T id(){return T(0);}
	static T f(T x,T y){return gcd(x,y);}
	static T fn(T x,int n){return x;}
};
template<class T>struct MFunc{
	static T id(){return T();}
	static T f(T x,T y){return x.f(y);}
	static T fn(T x,int n){return fn(x,n);}
};
#ifdef CPP20
struct TMaxSubArr{
	int s=0,l=-inf<int>(),m=-inf<int>(),r=-inf<int>();
	TMaxSubArr f(TMaxSubArr x)const{return {s+x.s,max(l,s+x.l),max({m,r+x.l,x.m}),max(r+x.s,x.r)};}
	TMaxSubArr nan()const{return {::nan<int>(),::nan<int>(),::nan<int>(),::nan<int>()};}
	friend strong_ordering operator<=>(const TMaxSubArr&,const TMaxSubArr&)=default;
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
#endif