#pragma once
#include "GraphWU.h"

struct GraphUU:public GraphWU<int>{
	GraphUU(int n=0):GraphWU(n){}
	void add_edge(int s,int e){GraphWU::add_edge(s,e,1);}
	Arr<int> art_points(){
		int ordi=0;
		Arr<int> ord(n,-1),ret;
		func(int,dfs,int v,int p){
			int mo=ord[v]=ordi++;
			int sc=p!=-1;
			// subtree중 하나라도 ord[v]보다 낮으면 단절점
			bool fail=false;
			for(auto i:adj[v]){
				if(edg[i].opp(v)==p) continue;
				if(ord[edg[i].opp(v)]==-1){
					int res=dfs(edg[i].opp(v),v);
					mo=min(mo,res);
					fail|=res>=ord[v];
					sc++;
				}else mo=min(mo,ord[edg[i].opp(v)]);
			}
			if(fail and sc>=2) ret.pushb(v);
			return mo;
		};

		for(int i=0;i<n;i++)
			if(ord[i]==-1)
				dfs(i,-1);
		return ret;
	}
	Arr<pair<int,int>> bridges(){
		int ordi=0;
		Arr<int> ord(n,-1);
		Arr<pair<int,int>> ret;

		// check if v-p is bridge
		func(int,dfs,int v,int p){
			int mo=ord[v]=ordi++;
			for(auto i:adj[v])
				if(edg[i].opp(v)!=p)
					mo = min(mo, ord[edg[i].opp(v)]==-1 ? dfs(edg[i].opp(v),v) : ord[edg[i].opp(v)]);
			if(~p and mo==ord[v])ret.pushb({v,p});
			return mo;
		};
		for(int i=0;i<n;i++)
			if(ord[i]==-1)
				dfs(i,-1);
		return ret;
	}
	void blossom(){}
};
