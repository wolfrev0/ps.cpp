#pragma once
#include "Core.h"

//Upd=Assignment
template<typename T, int n, T id=T()>
struct Seg{
	//생성자 대신 선언에{}붙여도 되는데, gcc버그로 컴파일하다 죽는다.
	Seg():tree(){fill(tree, tree+4*n, id);}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, T val){upd(1,0,n,p,val);}
protected:
	virtual T fq(const T& a, const T& b)=0;

	T q(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return id;
		if (s<=cs&&ce<=e)
			return tree[cur];
		int m=(cs+ce)/2;
		return fq(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
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
		tree[cur]=fq(tree[cur*2],tree[cur*2+1]);
	}
	T tree[4*n];
};

template<typename T, int n> struct SegSum:public Seg<T,n>{T fq(const T& a, const T& b)override{return a+b;}};
template<typename T, int n> struct SegMax:public Seg<T,n,-inf<T>()>{T fq(const T& a, const T& b)override{return max(a,b);}};
template<typename T, int n> struct SegMin:public Seg<T,n,inf<T>()>{T fq(const T& a, const T& b)override{return min(a,b);}};