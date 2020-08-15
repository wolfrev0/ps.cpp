#pragma once
#include "Core.h"
#include "Monoid.h"

template<typename T, typename Q, typename U>
struct SegLazy{
	static_assert(is_base_of<Monoid<T>, Q>::value, "Q is not monoid");
	static_assert(is_base_of<Monoid<T>, U>::value, "U is not monoid");
	SegLazy(int n=0):n(n), tr(4*n, mq.id()), lz(4*n, mu.id()){}
	SegLazy(int n, const Arr<T>& a):SegLazy(n){build(1,0,n,a);}
	T q(int p){ return q(p,p+1); }
	T q(int s, int e){ return q(1,0,n,s,e); }
	void upd(int p, T val){ upd(p, p+1, val); }
	void upd(int s, int e, T val){ upd(1,0,n,s,e,val); }
protected:
	int n;
	Q mq;
	U mu;
	Arr<T> tr,lz;
	
	void build(int c, int cs, int ce, const Arr<T>& arr){
		if(ce-cs==1){ tr[c]=arr[cs]; return; }
		int m=(cs+ce)/2;
		build(c*2,cs,m,arr);
		build(c*2+1,m,ce,arr);
		tr[c]=mq.f(tr[c*2],tr[c*2+1]);
	}
	T q(int c, int cs, int ce, int s, int e){
		propa(c, cs, ce);
		if (s>=ce||e<=cs) return mq.id();
		if (s<=cs&&ce<=e) return tr[c];
		int m=(cs+ce)/2;
		return mq.f(q(c*2,cs,m,s,e),q(c*2+1,m,ce,s,e));
	}
	void upd(int c, int cs, int ce, int s, int e, T val){
		propa(c, cs, ce);
		if (s>=ce||e<=cs) return;
		if (s<=cs&&ce<=e){
			addlz(c, val);
			propa(c, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(c*2,cs,m,s,e,val);
		upd(c*2+1,m,ce,s,e,val);
		tr[c]=mq.f(tr[c*2],tr[c*2+1]);
	}
	void propa(int c, int cs, int ce){
		if(lz[c]!=mu.id()){
			tr[c]=mu.f(tr[c], mu.fn(lz[c],ce-cs));
			if(ce-cs>1){
				addlz(c*2, lz[c]);
				addlz(c*2+1, lz[c]);
			}
			lz[c]=mu.id();
		}
	}
	void addlz(int v, T val){ lz[v] = lz[v]==mu.id() ? val : mu.f(lz[v],val); }
};
