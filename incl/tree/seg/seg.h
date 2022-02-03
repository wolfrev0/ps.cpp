#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<Monoid Q, Monoid U> struct Seg{
	// static_assert(Q::T()==U::T());
	using T=decltype(Q::id());
	int n; Arr<T> tr;
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
	//pred(acc[s,i))를 만족하는 최소i
	int liftLR(auto pred,int s=0){T acc=Q::id();return liftLR(1,0,n,s,pred,acc);}
	//pred(acc[i,e))를 만족하는 최대i
	int liftRL(auto pred){return liftRL(pred,n);}
	int liftRL(auto pred,int e){T acc=Q::id();return liftRL(1,0,n,e,pred,acc);}
	//ex) kth(boj2243), mex(폴리곤_숲게임_lib.cpp), nextgreateridx(boj2493)
private:
	int liftLR(int c,int cs,int ce,int s,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=inf<int>();
		if(ce<=s);
		else if(cs<s)
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
		else{
			if(!pred(Q::f(acc,tr[c]),cs,ce))return inf<int>();
			//now, pred(acc[s,ce))=True
			if(ce-cs==1)return ce;
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
			acc=Q::f(acc,tr[c]);
		}
		return ret;
	}
	int liftRL(int c,int cs,int ce,int e,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=-1;
		if(e<=cs);
		else if(e<ce)
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
		else{
			if(!pred(Q::f(tr[c],acc),cs,ce))return -1;
			//now, pred(acc[cs,e))=True
			if(ce-cs==1)return cs;
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
			acc=Q::f(tr[c],acc);
		}
		return ret;
	}
};
