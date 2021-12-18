#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<class MQ, class MU> struct Seg{
	// static_assert(MQ::T()==MU::T());
	using T=MQ::T;
	Seg(int n=0):n(n),tr(n<<1,MU::id()){}
	void upd(int i,T val) {i+=i<0?n:0;
		i+=n,tr[i]=MU::f(tr[i],val);
		while(i>>=1)tr[i]=MQ::f(tr[i<<1], tr[i<<1|1]);
	}
	T q(int s,int e){s+=s<0?n:0,e+=e<0?n:0;
		if(s>e) return MQ::f(q(s,n),q(0,e));
		assert(0<=s&&s<=e&&e<=n);
		T rs=MQ::id(),re=MQ::id();
		for(s+=n,e+=n;s<e;s>>=1,e>>=1){
			if(s&1)rs=MQ::f(rs,tr[s++]);
			if(e&1)re=MQ::f(tr[--e],re);
		}
		return MQ::f(rs,re);
	}
	int n;
	Arr<T> tr;
};
