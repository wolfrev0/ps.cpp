#pragma once
#include "Core.h"

//Upd=Assignment
template<typename T, T id=T()>
struct Seg{
	Seg(int n=0):n(n), tr(4*n, id){}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, T val){upd(1,0,n,p,val);}
protected:
	int n;
	vector<T> tr;
	
	virtual T fq(const T& a, const T& b)=0;

	T q(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return id;
		if (s<=cs&&ce<=e)
			return tr[cur];
		int m=(cs+ce)/2;
		return fq(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int p, T val){
		if (p>=ce||p+1<=cs)
			return;
		if (p<=cs&&ce<=p+1){
			tr[cur]=val;
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,p,val);
		upd(cur*2+1,m,ce,p,val);
		tr[cur]=fq(tr[cur*2],tr[cur*2+1]);
	}
};

template<typename T> struct SegSum:public Seg<T>{
	SegSum(int n=0):Seg<T>(n){}
	T fq(const T& a, const T& b)override{return a+b;}
};
template<typename T> struct SegMax:public Seg<T,-inf<T>()>{
	SegMax(int n=0):Seg<T>(n){}
	T fq(const T& a, const T& b)override{return max(a,b);}
};
template<typename T> struct SegMin:public Seg<T,-inf<T>()>{
	SegMin(int n=0):Seg<T>(n){}
	T fq(const T& a, const T& b)override{return min(a,b);}
};