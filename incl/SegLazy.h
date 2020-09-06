#pragma once
#include "Core.h"
#include "Monoid.h"

template<class T, class Q, class U>
struct SegLazy{
	SegLazy(int n=0):n(n), tr(4*n, Q::id()), lz(4*n, U::id()){}
	SegLazy(int n, const Arr<T>& a):SegLazy(n){build(1,0,n,a);}
	T q(int p){ return q(p,p+1); }
	T q(int s, int e){ return q(1,0,n,s,e); }
	void upd(int p, T val){ upd(p, p+1, val); }
	void upd(int s, int e, T val){ upd(1,0,n,s,e,val); }
private:
	void build(int c, int cs, int ce, const Arr<T>& arr){
		if(ce-cs==1){ tr[c]=arr[cs]; return; }
		int m=(cs+ce)/2;
		build(c*2,cs,m,arr);
		build(c*2+1,m,ce,arr);
		tr[c]=Q::f(tr[c*2],tr[c*2+1]);
	}
	T q(int c, int cs, int ce, int s, int e){
		propa(c, cs, ce);
		if (s>=ce||e<=cs) return Q::id();
		if (s<=cs&&ce<=e) return tr[c];
		int m=(cs+ce)/2;
		return Q::f(q(c*2,cs,m,s,e),q(c*2+1,m,ce,s,e));
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
		tr[c]=Q::f(tr[c*2],tr[c*2+1]);
	}
	void propa(int c, int cs, int ce){
		if(lz[c]!=U::id()){
			tr[c]=U::f(tr[c], Q::fn(lz[c],ce-cs));
			if(ce-cs>1){
				addlz(c*2, lz[c]);
				addlz(c*2+1, lz[c]);
			}
			lz[c]=U::id();
		}
	}
	void addlz(int v, T val){ lz[v] = lz[v]==U::id() ? val : U::f(lz[v],val); }

	int n;
	Arr<T> tr,lz;
};
