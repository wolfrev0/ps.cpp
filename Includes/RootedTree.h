#pragma once
#include "Tree.h"
#include "SegBU.h"

//Is Dynamic Rooted Tree Useful??
//Disjoint Set, BBST, Link Cut Tree belongs to it.
//But I think it doesn't need now.

//Static Rooted Tree

#define LCA 1
#define HLD 1

template<typename T>
struct RootedTree:private SegBU<int, inf<int>()>{
	struct N{
		N *p;
		Arr<N*> ch;
		T w;
	};
	
	RootedTree(const Arr<E>& pinfo)
		:SegBU<int, inf<int>()>(sz(pinfo)*2), n(sz(pinfo)), d(n), tsz(n), rpos(n){
		
		int ri=0;
		while(p[ri].e!=-1)
			ri=p[ri].e;
		hfor(i,0,n)
			if(i!=r){
				ch[p[i].e].pushb({i, p[i].w});
			}
		dfs_init(r);
	}
	
	int lca(int a, int b){
		if(rpos[a]>rpos[b])
			swap(a,b);
		return q(rpos[a], rpos[b]+1);
	}
	
protected:
	int n; N *r=new N();
	Arr<int> d, tsz, rpos, etour;
	//Arr<int> pre_tour, post_tour; cant define infix
	int fq(const int& a, const int& b)override{
		if(a==inf<int>())return b;
		if(b==inf<int>())return a;
		return d[a]<d[b]?a:b;
	}
	int dfs_init(int cur){
		d[cur] = p[cur].e>=0 ? d[p[cur].e]+1 : 0;
		tsz[cur]=1;
		upd(rpos[cur]=sz(etour), cur), etour.pushb(cur);
		for(const auto &i:ch[cur]){
			tsz[cur]+=dfs_init(i.e);
			upd(rpos[cur]=sz(etour), cur), etour.pushb(cur);
		}
		return tsz[cur];
	}
};