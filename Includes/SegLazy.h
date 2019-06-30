#pragma once
#include "Core.h"

template<typename T, typename U, int n>
struct SegLazy{
	//생성자 대신 선언에{}붙여도 되는데, gcc버그로 컴파일하다 죽는다.
	SegLazy():tree(), lazy(){ fill(lazy,lazy+4*n,inf<U>()); }
	void init(const array<T,n>& arr){build(1,0,n,arr);}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, U val){upd(p, p+1, val);}
	void upd(int s, int e, U val){upd(1,0,n,s,e,val);}
protected:
	virtual T fq(const T& a, const T& b)=0;
	virtual T fupd(const T& a, const U& b, signed c)=0;
	virtual U fpropa(const U& a, const U& b)=0;
	
	void build(int cur, int cs, int ce, const array<T,n>& arr){
		if(ce-cs==1)
			tree[cur]=arr[cs];
		else{
			int m=(cs+ce)/2;
			build(cur*2,cs,m,arr);
			build(cur*2+1,m,ce,arr);
			tree[cur]=fq(tree[cur*2],tree[cur*2+1]);
		}
	}

	T q(int cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e)
			return tree[cur];
		int m=(cs+ce)/2;
		return fq(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int s, int e, U val){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlazy(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,s,e,val);
		upd(cur*2+1,m,ce,s,e,val);
		tree[cur]=fq(tree[cur*2],tree[cur*2+1]);
	}
	
	void propa(int cur, int cs, int ce){
		if(lazy[cur]!=inf<U>()){
			tree[cur]=fupd(tree[cur],lazy[cur],ce-cs);
			if(ce-cs>1){
				addlazy(cur*2, lazy[cur]);
				addlazy(cur*2+1, lazy[cur]);
			}
			lazy[cur]=inf<U>();
		}
	}
	
	void addlazy(int v, U val){lazy[v]=lazy[v]==inf<U>()?val:fpropa(lazy[v],val);}
	
	T tree[4*n];
	U lazy[4*n];//inf=id, shortened_dirty_flag_pattern
};

template<typename T, typename U, int n>
struct SegLazySumAdd:public SegLazy<T,U,n>{
	T fq(const T& a, const T& b)override{return a+b;}
	T fupd(const T& a, const U& b, signed c)override{return a+b*c;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyMaxAdd:public SegLazy<T,U,n>{
	T fq(const T& a, const T& b)override{return max(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return a+b;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyMinAss:public SegLazy<T,U,n>{
	T fq(const T& a, const T& b)override{return min(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return b;}
	U fpropa(const U& a, const U& b)override{return b;}
};