#pragma once
#include "Tree.h"
#include "SegBU.h"
#include "SegPredefs.h"

//Is Dynamic Rooted Tree Useful??
//Disjoint Set, BBST, Link Cut Tree belongs to it.
//But I think it doesn't need now.

//Static Rooted Tree
template<typename T>
struct RootedTree{
	struct F{
		static pair<int,int> id(){return {inf<int>(),-1};}
		static pair<int,int> q(const pair<int,int>& a, const pair<int,int>& b){return min(a,b);}
	};
	
	RootedTree(const Arr<pair<int,T>>& p)
	:n(sz(p)), r(0),
	ch(n), p(p), dpt(n), tsz(n), rpos(n), seg(n*2){
		while(p[r].fi!=-1)
			r=p[r].fi;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].fi].pushb({i, p[i].se});
		dfs_init(r);
	}
	
	int lca(int a, int b){
		if(rpos[a]>rpos[b])
			swap(a,b);
		return seg.q(rpos[a], rpos[b]+1).se;
	}
	
	int n, r;
	Arr<Arr<pair<int,T>>> ch;
	Arr<pair<int,T>> p;
	Arr<int> dpt, tsz, rpos, etour;
	SegBU<pair<int,int>,F> seg;
	//Arr<int> pre_tour, post_tour; cant define infix
	
	int dfs_init(int cur){
		dpt[cur] = p[cur].fi>=0 ? dpt[p[cur].fi]+1 : 0;
		tsz[cur]=1;
		seg.upd(rpos[cur]=sz(etour), {dpt[cur],cur}), etour.pushb(cur);
		for(const auto &i:ch[cur]){
			tsz[cur]+=dfs_init(i.fi);
			seg.upd(rpos[cur]=sz(etour), {dpt[cur],cur}), etour.pushb(cur);
		}
		return tsz[cur];
	}
};