#pragma once
#include "Core.h"

//Upd=Assignment
template<int n, typename T>
struct Seg{
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, T val){upd(1,0,n,p,val);}
protected:
	virtual T qf(const T& a, const T& b)=0;

	T q(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e){
			return tree[cur];
		}
		int m=(cs+ce)/2;
		return qf(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int p, T val){
		if (p>=ce||p+1<=cs)
			return;
		if (p<=cs&&ce<=p+1){
			tree[cur]=val;
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,p,val);
		upd(cur*2+1,m,ce,p,val);
		tree[cur]=qf(tree[cur*2],tree[cur*2+1]);
	}
	array<T, 4*n> tree{{0,}};
};

template<int n, typename T> struct SegAdd:public Seg<n,T>{T qf(const T& a, const T& b)override{return a+b;}};
template<int n, typename T> struct SegMax:public Seg<n,T>{T qf(const T& a, const T& b)override{return max(a,b);}};
template<int n, typename T> struct SegMin:public Seg<n,T>{T qf(const T& a, const T& b)override{return min(a,b);}};