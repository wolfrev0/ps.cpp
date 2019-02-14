#pragma once
#include "Core.h"

template<typename T, typename U>
struct SegFDefault{
	static T idT(){return T();}
	static T idU(){return U();}
	static T q(const T& a, const T& b){return a+b;}
	static T upd(const T& a, const U& b, int c){return a+b*c;}
	static U propa(const U& a, const U& b){return a+b;}
};

//upperbound of 2^(ceil(log2(n))+1)/n is 4. (plot floor(2^(ceil(log2(x))+1)/x) from x=0 to 100000000)
template<typename T, typename U=T, typename F=SegFDefault<T, U>>
struct SegTree{
	SegTree(int n)
	:n(n),tree(4*n,F::idT()),lazy(4*n,F::idU())
	{}

	void update(int p, U val){update_range(1,0,n,p,p+1,val);}
	void update(int s, int e, U val){update_range(1,0,n,s,e,val);}
	T query(int s, int e, bool revord=false){return query2(1,0,n,s,e,revord);}
private:
	const int n;
	vector<T> tree;
	vector<U> lazy;

	void propagate(int cur, int cs, int ce){
		if(lazy[cur]==F::idU())
			return;
		tree[cur]=F::upd(tree[cur],lazy[cur],ce-cs);
		if (ce-cs>1){
			lazy[cur*2]=F::propa(lazy[cur*2],lazy[cur]);
			lazy[cur*2+1]=F::propa(lazy[cur*2+1],lazy[cur]);
		}
		lazy[cur]=F::idU();
	}

	void update_range(int cur, int cs, int ce, int s, int e, U val){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			lazy[cur]=F::propa(lazy[cur],val);
      propagate(cur,cs,ce);
			return;
		}
    int m=(cs+ce)/2;
		update_range(cur*2,cs,m,s,e,val);
		update_range(cur*2+1,m,ce,s,e,val);
		tree[cur]=F::q(tree[cur*2],tree[cur*2+1]);
	}

	T query2(int cur, int cs, int ce, int s, int e, bool revord){
		propagate(cur,cs,ce);
		if (s>=ce||e<=cs)
			return F::idT();
		if (s<=cs&&ce<=e)
			return tree[cur];
		if(revord)
			return F::q(query2(cur*2+1,(cs+ce)/2,ce,s,e,revord),query2(cur*2,cs,(cs+ce)/2,s,e,revord));
		return F::q(query2(cur*2,cs,(cs+ce)/2,s,e,revord),query2(cur*2+1,(cs+ce)/2,ce,s,e,revord));
	}
};