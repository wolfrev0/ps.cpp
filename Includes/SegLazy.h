#pragma once
#include "Core.h"
#include "GccExts.h"

template<typename T, typename U>
struct LazyFSumAdd{
	static T q(const T& a, const T& b){return a+b;}
	static T upd(const T& a, const U& b, int c){return a+b*c;}
	static U propa(const U& a, const U& b){return a+b;}
};

template<typename T, typename U>
struct LazyFMaxAdd{
	static T q(const T& a, const T& b){return max(a,b);}
	static T upd(const T& a, const U& b, int c){return a+b;}
	static U propa(const U& a, const U& b){return a+b;}
};

//upperbound of 2^(ceil(log2(n))+1)/n is 4. (plot floor(2^(ceil(log2(x))+1)/x) from x=0 to 100000000)
template<typename T, typename U=T, typename F=LazyFSumAdd<T, U>>
struct SegLazy{
	SegLazy(int n)
	:n(n),tree(4*n),lazy(4*n)
	{}

	void update(int p, U val){update(1,0,n,p,p+1,val);}
	void update(int s, int e, U val){update(1,0,n,s,e,val);}
	T query(int s, int e){return query(1,0,n,s,e);}
private:
	const int n;
	vector<T> tree;
	vector<U> lazy;

	void propagate(int cur, int cs, int ce){
		if(lazy[cur]==U())
			return;
		tree[cur]=F::upd(tree[cur],lazy[cur],ce-cs);
		if (ce-cs>1){
			lazy[cur*2]=F::propa(lazy[cur*2],lazy[cur]);
			lazy[cur*2+1]=F::propa(lazy[cur*2+1],lazy[cur]);
		}
		lazy[cur]=U();
	}

	void update(int cur, int cs, int ce, int s, int e, U val){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			lazy[cur]=F::propa(lazy[cur],val);
			propagate(cur,cs,ce);
			return;
		}
		int m=(cs+ce)/2;
		update(cur*2,cs,m,s,e,val);
		update(cur*2+1,m,ce,s,e,val);
		tree[cur]=F::q(tree[cur*2],tree[cur*2+1]);
	}

	T query(int cur, int cs, int ce, int s, int e){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e)
			return tree[cur];
		return F::q(query(cur*2,cs,(cs+ce)/2,s,e),query(cur*2+1,(cs+ce)/2,ce,s,e));
	}
};

template<typename T, typename U=T, typename F=LazyFSumAdd<T, U>>
struct DynSegLazy{
	DynSegLazy(int n)
	:n(n)//,tree(4*n),lazy(4*n)
	{}

	void update(int p, U val){update(1,0,n,p,p+1,val);}
	void update(int s, int e, U val){update(1,0,n,s,e,val);}
	T query(int s, int e){return query(1,0,n,s,e);}
private:
	const int n;
	cc_hash_table<int,T> tree;
	cc_hash_table<int,U> lazy;

	void propagate(int cur, int cs, int ce){
		if(lazy[cur]==U())
			return;
		tree[cur]=F::upd(tree[cur],lazy[cur],ce-cs);
		if (ce-cs>1){
			lazy[cur*2]=F::propa(lazy[cur*2],lazy[cur]);
			lazy[cur*2+1]=F::propa(lazy[cur*2+1],lazy[cur]);
		}
		lazy[cur]=U();
	}

	void update(int cur, int cs, int ce, int s, int e, U val){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			lazy[cur]=F::propa(lazy[cur],val);
			propagate(cur,cs,ce);
			return;
		}
		int m=(cs+ce)/2;
		update(cur*2,cs,m,s,e,val);
		update(cur*2+1,m,ce,s,e,val);
		tree[cur]=F::q(tree[cur*2],tree[cur*2+1]);
	}

	T query(int cur, int cs, int ce, int s, int e){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return T();
		if (s<=cs&&ce<=e)
			return tree[cur];
		return F::q(query(cur*2,cs,(cs+ce)/2,s,e),query(cur*2+1,(cs+ce)/2,ce,s,e));
	}
};