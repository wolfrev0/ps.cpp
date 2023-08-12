#pragma once
#include "core/base.h"
#include "math/struct/monoid.h"

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
	int prefix_search(auto pred,int s=0){T acc=Q::id();return prefix_search(1,0,n,s,pred,acc);}
	//pred(acc[i,e),i)를 만족하는 최대i
	int suffix_search(auto pred){return suffix_search(pred,n);}
	int suffix_search(auto pred,int e){T acc=Q::id();return suffix_search(1,0,n,e,pred,acc);}
	//kth: boj2243
	//mex: 폴리곤_숲게임_lib.cpp
	//nearest_greaters: https://codeforces.com/contest/1691/submission/159109187
private:
	int prefix_search(int c,int cs,int ce,int s,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=inf<int>();
		if(ce<=s)
			;
		else if(cs<s)
			assmin(ret,prefix_search(c<<1,cs,cm,s,pred,acc))||assmin(ret,prefix_search(c<<1|1,cm,ce,s,pred,acc));
		else{
			if(pred(acc,cs)){acc=Q::f(acc,tr[c]);return cs;}
			if(!pred(Q::f(acc,tr[c]),ce)){acc=Q::f(acc,tr[c]);return inf<int>();}
			if(ce-cs==1)return ce;
			assmin(ret,prefix_search(c<<1,cs,cm,s,pred,acc))||assmin(ret,prefix_search(c<<1|1,cm,ce,s,pred,acc));
		}
		return ret;
	}
	int suffix_search(int c,int cs,int ce,int e,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=-1;
		if(e<=cs)
			;
		else if(e<ce)
			assmax(ret,suffix_search(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,suffix_search(c<<1,cs,cm,e,pred,acc));
		else{
			if(pred(acc,ce)){acc=Q::f(acc,tr[c]);return ce;}
			if(!pred(Q::f(tr[c],acc),cs)){acc=Q::f(tr[c],acc);return -1;}
			if(ce-cs==1)return cs;
			assmax(ret,suffix_search(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,suffix_search(c<<1,cs,cm,e,pred,acc));
		}
		return ret;
	}
};
