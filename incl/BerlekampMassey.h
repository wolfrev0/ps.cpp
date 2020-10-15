#pragma once
#include "Core.h"

template<int mod=int(1e9+7)>
int fp(int x, int p){
	if(!p) return 1;
	int z=fp(x,p/2);
	return z*z%mod*(p%2?x:1)%mod;
}

//Berlekamp Massey
//NOTE: Linear Recurrence Sequence의 점화식 도출은 행렬형태로 표현해서 O(n^3)가능할듯 한데,
//Berlekamp Massey는 O(n^2)이다.
template<int mod=int(1e9+7)>
Arr<int> bm(Arr<int> x){
	for(auto& i:x)i=(i%mod+mod)%mod;
	//b: best(=shortest) relation so far
	//c: current relation
	Arr<int> b,c;
	//bi: pos of b
	//bd: delta of b
	int bi,bd;
	rep(i,sz(x)){
		int v=(-x[i]+mod)%mod;//evaluated value at i
		rep(j,sz(c))
			v=(v+c[j]*x[i-j-1])%mod;
		if(!v)continue;//good
		if(c.empty()){//first non-zero pos
			c.pushb(0), bi=i, bd=v;
			continue;
		}
		int coef=v*fp<mod>(bd,mod-2)%mod;
		Arr<int> a(i-bi-1);//add zeroes in front
		a.pushb(coef);
		for(auto j:b)
			a.pushb((-coef+mod)*j%mod);
		if(sz(c)>sz(a))
			a.resize(sz(c));
		rep(j,sz(c))
			a[j]=(a[j]+c[j])%mod;
		if(sz(c)<=i-bi+sz(b))
			b=c, bi=i, bd=v;
		c=a;
	}
	return c;
}