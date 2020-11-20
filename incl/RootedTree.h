#pragma once
#include "Core.h"

//Static Rooted Tree
template<typename T>
struct RootedTree{
	RootedTree(){}
	RootedTree(const Arr<pair<int,T>>& p)
	:n(sz(p)), r(0), ch(n), p(p), tsz(n), dpt(n), cost(n){
		while(p[r].fi!=r)
			r=p[r].fi;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].fi].pushb({i, p[i].se});
		dfs_init(r,0,0);
	}
	int dfs_init(int x, int d, T c){
		dpt[x]=d, cost[x]=c, tsz[x]=1;
		for(auto [i,w]:ch[x])
			tsz[x]+=dfs_init(i, d+1, c+w);
		return tsz[x];
	}

	int centroid(){return _centroid(r,r);}
	int _centroid(int x, int p){
		for(auto [i,w]:ch[x])
			if(tsz[i]>n/2)
				return _centroid(i,x);
		return x;
	}

	pair<Arr<int>,Arr<int>> euler(){
		Arr<int> eu,v2eu(n*2);
		dfs_euler(r,eu,v2eu);
		return {eu,v2eu};
	}
	void dfs_euler(int x, Arr<int>& eu, Arr<int>& v2eu){
		v2eu[x]=sz(eu), eu.pushb(x);
		for(auto [i,w]:ch[x])
			dfs_euler(i,eu,v2eu), v2eu[x]=sz(eu), eu.pushb(x);
	}

	pair<Arr<int>,Arr<int>> pre(){
		Arr<int> pre,v2pre(n);
		dfs_pre(r,pre,v2pre);
		return {pre,v2pre};
	}
	void dfs_pre(int x, Arr<int>& pre, Arr<int>& v2pre){
		v2pre[x]=sz(pre), pre.pushb(x);
		for(auto [i,w]:ch[x])
			dfs_pre(i,pre,v2pre);
	}

	pair<Arr<int>,Arr<int>> post(){
		Arr<int> po,v2po(n);
		dfs_post(r,po,v2po);
		return {po,v2po};
	}
	void dfs_post(int x, Arr<int>& post, Arr<int>& v2post){
		for(auto [i,w]:ch[x])
			dfs_post(i,post,v2post);
		v2post[x]=sz(post), post.pushb(x);
	}
	
	int n, r;
	Arr<Arr<pair<int,T>>> ch;
	Arr<pair<int,T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};
