#pragma once
#include "Core.h"
#include "GccExts.h"

//upperbound of 2^(ceil(log2(n))+1)/n is 4. (plot floor(2^(ceil(log2(x))+1)/x) from x=0 to 100000000)
template<typename T, typename U=T>
struct Seg{
	Seg(int n)
	:n(n),tree(4*n)
	{}

	void update(int p, U val){update(1,0,n,p,val);}
	T query(int i){return query(i,i+1);}
	T query(int s, int e){return query(1,0,n,s,e);}
protected:
	const int n;
	vector<T> tree;

	virtual T q(const T& a, const T& b)=0;
	virtual T upd(const T& a, const U& b)=0;

	void update(int cur, int cs, int ce, int p, U val){
		if (p>=ce||p+1<=cs)
			return;
		if (p<=cs&&ce<=p+1){
			tree[cur]=upd(tree[cur],val);
			return;
		}
		int m=(cs+ce)/2;
		update(cur*2,cs,m,p,val);
		update(cur*2+1,m,ce,p,val);
		tree[cur]=q(tree[cur*2],tree[cur*2+1]);
	}

	T query(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e){
			return tree[cur];
		}
		int m=(cs+ce)/2;
		return q(query(cur*2,cs,m,s,e),query(cur*2+1,m,ce,s,e));
	}
};

struct SegSumAss:public Seg<int,int>{
	using T=int; using U=int;
	T q(const T& a, const T& b)override{return a+b;};
	T upd(const T& a, const U& b)override{return b;};
};

struct SegMaxAdd:public Seg<int,int>{
	using T=int; using U=int;
	T q(const T& a, const T& b)override{return max(a,b);};
	T upd(const T& a, const U& b)override{return a+b;};
};

template<typename T, typename U=T>
struct DynSeg{
	DynSeg(int n)
	:n(n)
	{}

	void update(int p, U val){update(1,0,n,p,val);}
	T query(int i){return query(i,i+1);}
	T query(int s, int e){return query(1,0,n,s,e);}
private:
	const int n;
	cc_hash_table<int, T> tree;

	virtual T q(const T& a, const T& b)=0;
	virtual T upd(const T& a, const U& b)=0;

	void update(int cur, int cs, int ce, int p, U val){
		if (p>=ce||p+1<=cs)
			return;
		if (p<=cs&&ce<=p+1){
			tree[cur]=upd(tree[cur],val);
			return;
		}
		int m=(cs+ce)/2;
		update(cur*2,cs,m,p,val);
		update(cur*2+1,m,ce,p,val);
		tree[cur]=q(tree[cur*2],tree[cur*2+1]);
	}

	T query(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e){
			return tree[cur];
		}
		int m=(cs+ce)/2;
		return q(query(cur*2,cs,m,s,e),query(cur*2+1,m,ce,s,e));
	}
};