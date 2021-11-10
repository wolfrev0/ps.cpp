#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<class T> struct Seg{
	Seg(int n=0,Monoid<T> mq=MPLUS(T),Monoid<T> mu=MASS(T)):n(n),mq(mq),mu(mu),tr(n<<1,mu.id){}
	void upd(int i,T val) {i+=i<0?n:0;
		i+=n,tr[i]=mu.f(tr[i],val);
		while(i>>=1)tr[i]=mq.f(tr[i<<1], tr[i<<1|1]);
	}
	T q(int s,int e){s+=s<0?n:0,e+=e<0?n:0;
		if(s>e) return mq.f(q(s,n),q(0,e));
		assert(0<=s&&s<=e&&e<=n);
		T rs=mq.id,re=mq.id;
		for(s+=n,e+=n;s<e;s>>=1,e>>=1){
			if(s&1)rs=mq.f(tr[s++],rs);
			if(e&1)re=mq.f(re,tr[--e]);
		}
		return mq.f(rs,re);
	}
protected:
	int n;
	Monoid<T> mq,mu;
	Arr<T> tr;
};
