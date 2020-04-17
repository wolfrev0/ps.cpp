#pragma once
#include "Tree.h"
#include "SegBU.h"

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
	:n(sz(p)), r(0), ch(n), p(p), dpt(n), tsz(n), v2euler(n), v2pre(n), v2post(n), seg(n*2){
		while(p[r].fi!=-1)
			r=p[r].fi;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].fi].pushb({i, p[i].se});
		dfs_init(r);
	}
	
	int lca(int a, int b){
		if(v2euler[a]>v2euler[b])
			swap(a,b);
		return seg.q(v2euler[a], v2euler[b]+1).se;
	}
	
	int n, r;
	Arr<Arr<pair<int,T>>> ch;
	Arr<pair<int,T>> p;
	Arr<int> dpt, tsz, euler, v2euler, pre, v2pre, post, v2post;
	SegBU<pair<int,int>,F> seg;
	//cant define infix tour
private:
	int dfs_init(int cur){
		dpt[cur] = p[cur].fi>=0 ? dpt[p[cur].fi]+1 : 0;
		tsz[cur]=1;
		v2pre[cur]=sz(pre), pre.pushb(cur);
		seg.upd(v2euler[cur]=sz(euler), {dpt[cur],cur}), euler.pushb(cur);
		for(const auto &i:ch[cur]){
			tsz[cur]+=dfs_init(i.fi);
			seg.upd(v2euler[cur]=sz(euler), {dpt[cur],cur}), euler.pushb(cur);
		}
		v2post[cur]=sz(post), post.pushb(cur);
		return tsz[cur];
	}
};