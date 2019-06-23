#pragma once
#include "Core.h"

template<int n, typename T, typename U=T>
struct SegLazy{
	//생성자 대신 선언에{}붙여도 되는데, gcc버그로 컴파일하다 죽는다.
	SegLazy():tree(), lazy(), dirty(){}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, U val){upd(p, p+1, val);}
	void upd(int s, int e, U val){upd(1,0,n,s,e,val);}
protected:
	virtual T qf(const T& a, const T& b)=0;
	virtual T uf(const T& a, const U& b, int c)=0;
	virtual U propaf(const U& a, const U& b)=0;

	T q(int cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e)
			return tree[cur];
		int m=(cs+ce)/2;
		return qf(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int s, int e, U val){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			holdlazy(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,s,e,val);
		upd(cur*2+1,m,ce,s,e,val);
		tree[cur]=qf(tree[cur*2],tree[cur*2+1]);
	}
	
	void propa(int cur, int cs, int ce){
		if(!dirty[cur])
			return;
		tree[cur]=uf(tree[cur],lazy[cur],ce-cs);
		dirty[cur]=false;
		if(ce-cs>1){
			holdlazy(cur*2,lazy[cur]);
			holdlazy(cur*2+1,lazy[cur]);
		}
	}
	
	void holdlazy(int v, U val){
		lazy[v]=dirty[v]?propaf(lazy[v],val):val;
		dirty[v]=true;
	}
	
	array<T,4*n> tree;
	array<U,4*n> lazy;
	array<bool,4*n> dirty;
};

template<int n, typename T, typename U=T>
struct SegLazySumAdd:public SegLazy<n,T,U>{
	T qf(const T& a, const T& b)override{return a+b;}
	T uf(const T& a, const U& b, signed c)override{return a+b*c;}
	U propaf(const U& a, const U& b)override{return a+b;}
};
template<int n, typename T, typename U=T>
struct SegLazyMaxAdd:public SegLazy<n,T,U>{
	T qf(const T& a, const T& b)override{return max(a,b);}
	T uf(const T& a, const U& b, signed c)override{return a+b;}
	U propaf(const U& a, const U& b)override{return a+b;}
};
template<int n, typename T, typename U=T>
struct SegLazySumAss:public SegLazy<n,T,U>{
	T qf(const T& a, const T& b)override{return a+b;}
	T uf(const T& a, const U& b, signed c)override{return b*c;}
	U propaf(const U& a, const U& b)override{return b;}
};