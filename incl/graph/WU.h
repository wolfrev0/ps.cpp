#pragma once
#include "graph/WD.h"
#include "misc/uf.h"

template<class T>
struct GraphWU: GraphWD<T>{
	using GraphWD<T>::edg;
	using GraphWD<T>::adj;
	using GraphWD<T>::n;
	using E=GraphWD<T>::E;
	GraphWU(int n):GraphWD<T>(n){}
	void add_edge(int s, int e, T w){
		edg.emplace_back(E{{s,e},{sz(adj[e]),sz(adj[s])},sz(edg),w});
		adj[e].emplace_back(sz(edg)-1);
		adj[s].emplace_back(sz(edg)-1);
	}
	//kruskal
	Arr<E> mst(){
		auto e=edg;
		sort(e.begin(),e.end());
		UFgroup uf(n);
		Arr<E> ret;
		ret.reserve(n-1);
		for(auto i:e) {
			if(uf.r(i.v[0])^uf.r(i.v[1])){
				uf.uni(i.v[0],i.v[1]);
				ret.emplace_back(move(i));
			}
		}
		return ret;
	}
	//prim
	Arr<E> mst2(){
		Arr<E> ret;
		Arr<bool> vis(n);
		PQ<tuple<T,int,int>,greater<>> pq;
		for(auto i:adj[0])
			pq.empl(edg[i].w,edg[i].opp(0),i);
		vis[0]=true;
		while(sz(pq)){
			auto [w,x,idx]=pq.top();pq.pop();
			if(vis[x]) continue;
			vis[x]=true;
			ret.emplace_back(edg[idx]);
			for(auto& i:adj[x])
				if(!vis[edg[i].opp(x)])
					pq.empl(edg[i].w,edg[i].opp(x),i);
		}
		return ret;
	}

	//SeeAlso) https://codeforces.com/blog/entry/90137?#comment-785463
	Arr<pint> boomerang(){
		//boj.kr/16583
		//https://codeforces.com/contest/1519/problem/E
		//https://codeforces.com/contest/858/problem/F
		// https://www.acmicpc.net/problem/13353 ?
		Arr<bool> vis(n);
		Arr<pint> ret;
		Arr<int> ok(sz(edg),true);
		func(void,dfs,int v,int pei){
			vis[v]=true;
			Arr<int> y;
			for(auto i:adj[v]){
				if(i==pei)continue;
				int opp=edg[i].opp(v);
				if(!vis[opp])
					dfs(opp,i);
				if(ok[i])
					y.emplace_back(i);
			}
			if(pei!=-1)y.emplace_back(pei);
			for(int i=0;i+1<sz(y);i+=2)
				ok[y[i]]=ok[y[i+1]]=false,ret.emplace_back(y[i],y[i+1]);
		};
		for(int i=0;i<n;i++)
			if(!vis[i])
				dfs(i,-1);
		return ret;
	}
};
