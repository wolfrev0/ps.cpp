#pragma once
#include "core/base.h"

// Static Rooted Tree
template<class T> struct RootedTree {
	RootedTree() {}
	RootedTree(const Arr<pair<int, T>>& p)
	    : n(sz(p)),r(0),ch(n),p(p),tsz(n),dpt(n),cost(n) {
		while(p[r].fi!=r)
			r=p[r].fi;
		for(int i = 0; i < n; i++)
			if(i != r)
				ch[p[i].fi].pushb({i, p[i].se});
		func(int,dfs,int x,int d,T c){
			dpt[x]=d,cost[x]=c,tsz[x]=1;
			for(auto [i,w]:ch[x])tsz[x]+=dfs(i,d+1,c+w);
			return tsz[x];
		};
		dfs(r,0,0);
	}

	int centroid(){
		func(int,dfs,int x,int p){
			for(auto [i,w]:ch[x])
				if(tsz[i] > n/2)
					return dfs(i,x);
			return x;
		};
		return dfs(r, r);
	}

	Arr<Arr<int>> euler() {
		int co = 0;
		Arr<Arr<int>> ord(n);
		func(void,dfs,int x){
			ord[x].emplb(co++);
			for(auto [i,_]:ch[x])
				dfs(i),ord[x].emplb(co++);
		};
		dfs(r);
		return ord;
	}

	Arr<int> pre(){
		int co=0;
		Arr<int> ord(n);
		func(void,dfs,int x){
			ord[x]=co++;
			for(auto [i,_]:ch[x])
				dfs(i);
		};
		dfs(r);
		return ord;
	}

	Arr<int> post(){
		int co=0;
		Arr<int> ord(n);
		func(void,dfs,int x){
			for(auto [i,_]:ch[x])
				dfs(i);
			ord[x]=co++;
		};
		dfs(r);
		return ord;
	}

	int n, r;
	Arr<Arr<pair<int, T>>> ch;
	Arr<pair<int, T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};
