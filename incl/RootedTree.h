#pragma once
#include "Tree.h"
#include "SegBU.h"

//Static Rooted Tree
template<typename T>
struct RootedTree{
	struct F{
		static pair<int,int> id(){return {inf<int>(),-1};}
		static pair<int,int> q(const pair<int,int>& a, const pair<int,int>& b){return min(a,b);}
	};
	
	RootedTree(const Arr<pair<int,T>>& p)
	:n(sz(p)), r(0), ch(n), p(p), tsz(n), dpt(n), cost(n){
		while(p[r].fi!=-1)
			r=p[r].fi;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].fi].pushb({i, p[i].se});
		dfs_init(r,0,0);
	}
	int dfs_init(int cur, int d, T c){
		dpt[cur]=d, cost[cur]=c, tsz[cur]=1;
		for(const auto &i:ch[cur])
			tsz[cur]+=dfs_init(i.fi, d+1, c+i.se);
		return tsz[cur];
	}

	pair<Arr<int>,Arr<int>> euler(){
		Arr<int> eu,v2eu(n*2);
		dfs_euler(r,eu,v2eu);
		return {eu,v2eu};
	}
	void dfs_euler(int cur, Arr<int>& eu, Arr<int>& v2eu){
		v2eu[cur]=sz(eu), eu.pushb(cur);
		for(const auto &i:ch[cur])
			dfs_euler(i.fi,eu,v2eu), v2eu[cur]=sz(eu), eu.pushb(cur);
	}

	pair<Arr<int>,Arr<int>> pre(){
		Arr<int> pre,v2pre(n);
		dfs_pre(r,pre,v2pre);
		return {pre,v2pre};
	}
	void dfs_pre(int cur, Arr<int>& pre, Arr<int>& v2pre){
		v2pre[cur]=sz(pre), pre.pushb(cur);
		for(const auto &i:ch[cur])
			dfs_pre(i.fi,pre,v2pre);
	}

	pair<Arr<int>,Arr<int>> post(){
		Arr<int> po,v2po(n);
		dfs_post(r,po,v2po);
		return {po,v2po};
	}
	void dfs_post(int cur, Arr<int>& post, Arr<int>& v2post){
		for(const auto &i:ch[cur])
			dfs_post(i.fi,post,v2post);
		v2post[cur]=sz(post), post.pushb(cur);
	}
	
	int n, r;
	Arr<Arr<pair<int,T>>> ch;
	Arr<pair<int,T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};
