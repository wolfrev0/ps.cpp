#pragma once
#include "DirGraph.h"

struct SimpleGraph: public DirGraph{
	SimpleGraph(int n=0):DirGraph(n){}

	void add_edge(int s, int e){ DirGraph::add_edge(s, e, false); }

	Arr<int> art_points(){
		int ordi=0;
		Arr<int> ord(n,-1), ret;
		rep(i,n)
			if(ord[i]==-1)
				dfs_ap(i, -1, ordi, ord, ret);
		return ret;
	}

	Arr<pair<int,int>> bridges(){
		int ordi=0;
		Arr<int> ord(n,-1);
		Arr<pair<int,int>> ret;
		rep(i,n)
			if(ord[i]==-1)
				dfs_bridge(i, -1, ordi, ord, ret);
		return ret;
	}
	
	void blossom(){}
private:
	int dfs_ap(int v, int p, int& ordi, Arr<int>& ord, Arr<int>& ans){
		int mo=ord[v]=ordi++;
		int sc=p!=-1;
		//subtree중 하나라도 ord[v]보다 낮으면 단절점
		bool fail=false;
		for(auto i:g[v]){
			if(i.e==p)
				continue;
			if(ord[i.e]==-1){
				int res=dfs_ap(i.e, v, ordi, ord, ans);
				mo=min(mo, res);
				fail |= res>=ord[v];
				sc++;
			}
			else
				mo=min(mo, ord[i.e]);
		}
		if(fail and sc>=2)
			ans.pushb(v);
		return mo;
	}

	//check if v-p is bridge
	int dfs_bridge(int v, int p, int& ordi, Arr<int>& ord, Arr<pair<int, int>>& ans){
		int mo = ord[v]=ordi++;
		for(auto i:g[v])
			if(i.e!=p)
				mo=min(mo, ord[i.e]==-1?dfs_bridge(i.e, v, ordi, ord, ans):ord[i.e]);
		if(p!=-1 and mo==ord[v])
			ans.pushb({v,p});
		return mo;
	}
};