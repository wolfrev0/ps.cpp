#pragma once
#include "core/base.h"
#include "math/monoid2.h"

template<class T, class F> struct SegLazy {
	SegLazy(int n=0,const Arr<T>& a={})
		:n(n),tr(n<<2,F::idT()),lz(n<<2,F::idU())
		{if(sz(a))build(1,0,n,a);}
	T q(int p){return q(p,p+1);}
	T q(int s,int e){return q(1,0,n,s,e);}
	void upd(int p,T val){upd(p,p+1,val);}
	void upd(int s,int e,T val){upd(1,0,n,s,e,val);}
private:
	void build(int c,int cs,int ce,const Arr<T>& arr){
		if(ce-cs==1){
			tr[c]=arr[cs];
			return;
		}
		int m=cs+ce>>1;
		build(c<<1,cs,m,arr);
		build(c<<1|1,m,ce,arr);
		tr[c]=F::f(tr[c<<1],tr[c<<1|1]);
	}
	T q(int c,int cs,int ce,int s,int e){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return F::idT();
		if(s<=cs&&ce<=e) return tr[c];
		int m=cs+ce>>1;
		return F::f(q(c<<1,cs,m,s,e),q(c<<1|1,m,ce,s,e));
	}
	void upd(int c,int cs,int ce,int s,int e,T val){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return;
		if(s<=cs&&ce<=e){
			addlz(c,val);
			propa(c,cs,ce);
			return;
		}
		int m=cs+ce>>1;
		upd(c<<1,cs,m,s,e,val);
		upd(c<<1|1,m,ce,s,e,val);
		tr[c]=F::f(tr[c<<1],tr[c<<1|1]);
	}
	void propa(int c,int cs,int ce){
		if(lz[c]==F::idU()) return;
		tr[c]=F::updn(tr[c],lz[c],ce-cs,this);
		if(ce-cs>1)
			addlz(c<<1,lz[c]),addlz(c<<1|1,lz[c]);
		lz[c]=F::idU();
	}
	void addlz(int v,T val){lz[v]=lz[v]==F::idU()?val:F::propa(lz[v],val);}

	int n;
	Arr<T> tr, lz;
};
