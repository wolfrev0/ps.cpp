#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<Monoid Q> struct Seg{
	using T=decltype(Q::id());
	int n; Arr<T> tr;
	Seg(u32 n=0):n(bit_ceil(n)),tr(this->n*2,Q::id()){}
	void upd(int i,T val){for(tr[i+=n]=val;i>>=1;)tr[i]=Q::f(tr[i<<1],tr[i<<1|1]);}
	T q(int i){return tr[n+i];}
	T q(int s,int e){
		T rs=Q::id(),re=Q::id();
		for(s+=n,e+=n;s<e;s>>=1,e>>=1){
			if(s&1)rs=Q::f(rs,tr[s++]);
			if(e&1)re=Q::f(tr[--e],re);
		}
		return Q::f(rs,re);
	}
	//pred(acc[s,i),i)를 만족하는 최소i
	int liftLR(auto pred,int s=0){T acc=Q::id();return liftLR(1,0,n,s,pred,acc);}
	//pred(acc[i,e),i)를 만족하는 최대i
	int liftRL(auto pred){return liftRL(pred,n);}
	int liftRL(auto pred,int e){T acc=Q::id();return liftRL(1,0,n,e,pred,acc);}
	//kth: boj2243
	//mex: 폴리곤_숲게임_lib.cpp
	//nearest_greaters: https://codeforces.com/contest/1691/submission/159109187
private:
	int liftLR(int c,int cs,int ce,int s,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=inf<int>();
		if(ce<=s)
			;
		else if(cs<s)
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
		else{
			if(pred(acc,cs)){acc=Q::f(acc,tr[c]);return cs;}
			if(!pred(Q::f(acc,tr[c]),ce)){acc=Q::f(acc,tr[c]);return inf<int>();}
			if(ce-cs==1)return ce;
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
		}
		return ret;
	}
	int liftRL(int c,int cs,int ce,int e,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=-1;
		if(e<=cs)
			;
		else if(e<ce)
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
		else{
			if(pred(acc,ce)){acc=Q::f(acc,tr[c]);return ce;}
			if(!pred(Q::f(tr[c],acc),cs)){acc=Q::f(tr[c],acc);return -1;}
			if(ce-cs==1)return cs;
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
		}
		return ret;
	}
};
