#pragma once
#include "Core.h"

template<typename T, typename U, T id=T()>
struct SegLazy{
	SegLazy(int n):n(n), tr(4*n, id), lz(4*n, inf<U>()){}
	SegLazy(int n, const vector<T>& arr):n(n), tr(4*n, id), lz(4*n, inf<U>()){ build(1,0,n,arr); }
	T q(int p){ return q(p,p+1); }
	T q(int s, int e){ return q(1,0,n,s,e); }
	void upd(int p, U val){ upd(p, p+1, val); }
	void upd(int s, int e, U val){ upd(1,0,n,s,e,val); }
protected:
	int n;
	vector<T> tr;
	vector<U> lz;//lz_id=inf
	
	virtual T fq(const T& a, const T& b)=0;
	virtual T fupd(const T& a, const U& b, signed c)=0;
	virtual U fpropa(const U& a, const U& b)=0;
	
	void build(int cur, int cs, int ce, const vector<T>& arr){
		if(ce-cs==1)
			tr[cur]=arr[cs];
		else{
			int m=(cs+ce)/2;
			build(cur*2,cs,m,arr);
			build(cur*2+1,m,ce,arr);
			tr[cur]=fq(tr[cur*2],tr[cur*2+1]);
		}
	}

	T q(int cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return id;
		if (s<=cs&&ce<=e)
			return tr[cur];
		int m=(cs+ce)/2;
		return fq(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int s, int e, U val){
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
		tr[cur]=fq(tr[cur*2],tr[cur*2+1]);
	}
	
	void propa(int cur, int cs, int ce){
		if(lz[cur]!=inf<U>()){
			tr[cur]=fupd(tr[cur],lz[cur],ce-cs);
			if(ce-cs>1){
				addlz(cur*2, lz[cur]);
				addlz(cur*2+1, lz[cur]);
			}
			lz[cur]=inf<U>();
		}
	}
	
	void addlz(int v, U val){lz[v]=lz[v]==inf<U>()?val:fpropa(lz[v],val);}
};

template<typename T, typename U>
struct SegLazySumAdd:public SegLazy<T,U>{
	SegLazySumAdd(int n=0):SegLazy<T,U>(n){}
	T fq(const T& a, const T& b)override{return a+b;}
	T fupd(const T& a, const U& b, signed c)override{return a+b*c;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U>
struct SegLazyMaxAdd:public SegLazy<T,U>{
	SegLazyMaxAdd(int n=0):SegLazy<T,U>(n){}
	T fq(const T& a, const T& b)override{return max(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return a+b;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U>
struct SegLazyMinAss:public SegLazy<T,U>{
	SegLazyMinAss(int n=0):SegLazy<T,U>(n){}
	T fq(const T& a, const T& b)override{return min(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return b;}
	U fpropa(const U& a, const U& b)override{return b;}
};