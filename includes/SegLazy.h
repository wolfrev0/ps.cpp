#pragma once
#include "Core.h"

template<typename T, typename F>
struct SegLazy{
	SegLazy(int n=0):n(n), tr(4*n, F::id()), lz(4*n, inf<T>()){}
	SegLazy(int n, const Arr<T>& arr):n(n), tr(4*n, F::id()), lz(4*n, inf<T>()){ build(1,0,n,arr); }
	T q(int p){ return q(p,p+1); }
	T q(int s, int e){ return q(1,0,n,s,e); }
	void upd(int p, T val){ upd(p, p+1, val); }
	void upd(int s, int e, T val){ upd(1,0,n,s,e,val); }
protected:
	int n;
	Arr<T> tr;
	Arr<T> lz;//lz_id=inf
	
	void build(int cur, int cs, int ce, const Arr<T>& arr){
		if(ce-cs==1)
			tr[cur]=arr[cs];
		else{
			int m=(cs+ce)/2;
			build(cur*2,cs,m,arr);
			build(cur*2+1,m,ce,arr);
			tr[cur]=F::q(tr[cur*2],tr[cur*2+1]);
		}
	}

	T q(int cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return F::id();
		if (s<=cs&&ce<=e)
			return tr[cur];
		int m=(cs+ce)/2;
		return F::q(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int s, int e, T val){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlz(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,s,e,val);
		upd(cur*2+1,m,ce,s,e,val);
		tr[cur]=F::q(tr[cur*2],tr[cur*2+1]);
	}
	
	void propa(int cur, int cs, int ce){
		if(lz[cur]!=inf<T>()){
			tr[cur]=F::upd(tr[cur],lz[cur],cs,ce);
			if(ce-cs>1){
				addlz(cur*2, lz[cur]);
				addlz(cur*2+1, lz[cur]);
			}
			lz[cur]=inf<T>();
		}
	}
	
	void addlz(int v, T val){lz[v]=lz[v]==inf<T>()?val:F::propa(lz[v],val);}
};
