#pragma once
#include "core/base.h"
#include "math/monoid.h"

//NOTE: 교환법칙 불가능하면 2의 거듭제곱 사이즈로 조정필요
template<Monoid Q, Monoid U> struct Seg{
	// static_assert(Q::T()==U::T());
	using T=decltype(Q::id());
	Seg(int n=0):n(n),tr(n<<1,Q::id()){}
	void upd(int i,T val){
		i+=n,tr[i]=U::f(tr[i],val);
		while(i>>=1)tr[i]=Q::f(tr[i<<1],tr[i<<1|1]);
	}
	T q(int s,int e){
		T rs=Q::id(),re=Q::id();
		for(s+=n,e+=n;s<e;s>>=1,e>>=1){
			if(s&1)rs=Q::f(rs,tr[s++]);
			if(e&1)re=Q::f(tr[--e],re);
		}
		return Q::f(rs,re);
	}
	int n;
	Arr<T> tr;
};
