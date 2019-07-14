#pragma once
#include "Core.h"
#include "SegBU.h"

//Is Dynamic Rooted Tree Useful??
//Disjoint Set, BBST, Link Cut Tree belongs to it.
//But I think it doesn't need now.

//Static Rooted Tree
template<typename T>
struct RootedTree{
	struct Edge{ int e; T w; };
	struct SegLCA:public SegBU<int, 200000>{
		const RootedTree& p;
		SegLCA(const RootedTree& p):SegBU<int,200000>(inf<int>()), p(p){}
		int fq(const int& a, const int& b)override{
			if(a==inf<int>())return b;
			if(b==inf<int>())return a;
			return p.d[a]<p.d[b]?a:b;
		}
	};
	
	RootedTree(const vector<int>& par, const vector<T>& pw)
		:n(sz(par)), ch(n), d(n), rpos(n), st(*this){
		hfor(i,0,n)
			p.pb({par[i], pw[i]});
		r=0;
		while(p[r].e!=-1)
			r=p[r].e;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].e].pb({i, p[i].w});
		dfs_init(r);
	}
	
	int lca(int a, int b){
		if(rpos[a]>rpos[b])
			swap(a,b);
		return st.q(rpos[a], rpos[b]+1);
	}
	
protected:
	int n,r;
	vector<Edge> p;
	vector<vector<Edge>> ch;
	vector<int> d;
	vector<int> rpos;
	vector<int> etour;
	//vector<int> pre_tour, post_tour; cant define infix
	SegLCA st;
	void dfs_init(int cur){
		d[cur] = p[cur].e>=0 ? d[p[cur].e]+1 : 0;
		st.upd(rpos[cur]=sz(etour), cur), etour.pb(cur);
		for(const auto &i:ch[cur]){
			dfs_init(i.e);
			st.upd(rpos[cur]=sz(etour), cur), etour.pb(cur);
		}
	}
};