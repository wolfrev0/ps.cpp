#pragma once
#include "Core.h"

//Static Rooted Tree
template<class T>
struct RootedTree{
	RootedTree(){}
	RootedTree(const Arr<pair<int,T>>& p): n(sz(p)), r(0), ch(n), p(p), tsz(n), dpt(n), cost(n){
		while(p[r].fi!=r)
			r=p[r].fi;
		rep(i,n)
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

	Arr<Arr<int>> euler(){ int co=0; Arr<Arr<int>> ord(n); dfs_euler(r,co,ord); return ord; }
	void dfs_euler(int x, int& co, Arr<Arr<int>>& ord){ ord[x].emplb(co++); for(auto [i,_]:ch[x])dfs_euler(i,co,ord),ord[x].emplb(co++); }

	Arr<int> pre(){ int co=0; Arr<int> ord(n); dfs_pre(r,co,ord); return ord; }
	void dfs_pre(int x, int& co, Arr<int>& ord){ ord[x]=co++; for(auto [i,_]:ch[x])dfs_pre(i,co,ord); }
	
	Arr<int> post(){ int co=0; Arr<int> ord(n); dfs_post(r,co,ord); return ord; }
	void dfs_post(int x, int& co, Arr<int>& ord){ for(auto [i,_]:ch[x])dfs_post(i,co,ord); ord[x]=co++; }

	int n, r;
	Arr<Arr<pair<int,T>>> ch;
	Arr<pair<int,T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};
