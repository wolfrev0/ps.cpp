#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<Monoid Q, Monoid U> struct Seg{
	// static_assert(Q::T()==U::T());
	using T=decltype(Q::id());
	Seg(u64 n=0):n(bit_ceil(n)),tr(this->n*2,Q::id()){}
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
	//pred(acc[s,i))를 만족하는 최소i, liftR은 반대방향
	//ex) kth(boj2243), mex(폴리곤_숲게임_lib.cpp), next_bigger_idx(?)
	int liftL(auto pred){return liftL(0,n,pred);}
	int liftL(int s,int e,auto pred){return liftL(1,0,n,s,e,pred,Q::id());}
	int liftL(int c,int cs,int ce,int s, int e,auto pred,int acc){
		if(!pred(Q::f(acc,tr[c]),cs,ce))return e+1;
		//now, pred(acc[s,ce))=True
		if(ce-cs==1)return ce;
		int cm=(cs+ce)/2;
		int res=e+1;
		if(cm<=s)
			return liftL(c<<1|1,cm,ce,s,e,pred,acc);
		if(!assmin(res,liftL(c<<1,cs,cm,s,e,pred,acc)))
			assmin(res,liftL(c<<1|1,cm,ce,s,e,pred,Q::f(acc,tr[c<<1])));
		return res;
	}
	int n;
	Arr<T> tr;
};
