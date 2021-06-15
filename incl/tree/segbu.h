#pragma once
#include "core/base.h"
#include "math/monoid2.h"

template<class T,class F> struct SegBU{
	SegBU(int n=0,T init=F::idT()):n(n),tr(n<<1,init){}
	void upd(int i,T val) {i+=i<0?n:0;
		i+=n,tr[i]=F::upd(tr[i],val);
		while(i>>=1)tr[i]=F::f(tr[i<<1], tr[i<<1|1]);
	}
	T q(int s,int e){s+=s<0?n:0,e+=e<0?n:0;
		if(s>e) return F::f(q(s,n),q(0,e));
		assert(0<=s&&s<=e&&e<=n);
		T rs=F::idT(),re=F::idT();
		for(s+=n,e+=n;s<e;s>>=1,e>>=1){
			if(s&1)rs=F::f(tr[s++],rs);
			if(e&1)re=F::f(re,tr[--e]);
		}
		return F::f(rs,re);
	}
protected:
	int n;
	Arr<T> tr;
};
