#pragma once

#include "core/config.h"
#include "core/arr.h"

template<class T>
struct Monoid{
	using Type=T;
	function<T(T,T)> f; T id;
	function<T(T,int)> fn; //f(...f(f(id,x),x),...,x) n겹
	Monoid(function<T(T,T)> _f,T _id=T()):f(_f),id(_id){
		fn=[&](T x,int n){ //O(log(n))
			if(!n)return id;
			T res=fn(x,n/2);
			res=f(res,res);
			if(n%2)res=f(res,x);
			return res;
			return n%2?f(f(res,res),x):f(res,res);
		};
	}
};
template<class T>
struct MAdd:Monoid<T>{
	MAdd():Monoid<T>(lamp(x+y,T x,T y),T(0)){Monoid<T>::fn=lamp(x*n,T x,int n);}
};
template<class T>
struct MMul:Monoid<T>{
	MMul():Monoid<T>(lamp(x*y,T x,T y),T(1)){}
};
template<class T>
struct MAss:Monoid<T>{
	MAss():Monoid<T>(lamp(y,T x,T y),inf<T>()+1){Monoid<T>::fn=lamp(x,T x,int n);}
};
template<class T>
struct MMin:Monoid<T>{
	MMin():Monoid<T>(lamp(min(x,y),T x,T y),inf<T>()){Monoid<T>::fn=lamp(x,T x,int n);}
};
template<class T>
struct MMax:Monoid<T>{
	MMax():Monoid<T>(lamp(max(x,y),T x,T y),-inf<T>()){Monoid<T>::fn=lamp(x,T x,int n);}
};
template<class T>
struct MXor:Monoid<T>{
	MXor():Monoid<T>(lamp(x^y,T x,T y),T(0)){Monoid<T>::fn=lamp(n%2?x:0,T x,int n);}
};
template<class T>
struct MGcd:Monoid<T>{
	MGcd():Monoid<T>(lamp(gcd(x,y),T x,T y),T(0)){Monoid<T>::fn=lamp(x,T x,int n);}
};

template<class T>
Arr<T> cumf(const Arr<T>& a, const Monoid<T>& m=MAdd<T>()){
	Arr<T> b(sz(a)+1,m.id);
	for(int i=0;i<sz(a);i++)
		b[i]=m.f(b[i-1],a[i]);
	return b;
}
template<class T>
Arr<T> cumb(const Arr<T>& a, const Monoid<T>& m=MAdd<T>()){
	Arr<T> b(sz(a)+1,m.id);
	for(int i=sz(a)-1;~i;i--)
		b[i]=m.f(b[i-1],a[i]);
	return b;
}