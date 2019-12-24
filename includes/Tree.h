#pragma once

#include "Core.h"

template<typename T>
struct Tree{
	Tree(int n=0):n(n), g(n){}

	void add_edge(int s, int e, T w){ g[s].pushb({e,w}); g[e].pushb({s,w}); }
	T diameter()const {	return dfs_diameter(0, -1).fi; }
	void rootize(int r, Arr<pair<int,T>>& res, int p=-1)const{
		for(auto i:g[r]){
			if(i.fi==p)
				continue;
			res[i.fi]={r,i.se};
			rootize(i.fi,res,r);
		}
	}
private:
	int n;
	Arr<Arr<pair<int,T>>> g;
	
	pair<T, T> dfs_diameter(int v, int p)const{
		T diam = 0;
		Arr<int> lens;
		for(auto i:g[v]){
			if(i.fi==p)
				continue;
			auto res=dfs_diameter(i.fi, v);
			diam=max(diam, res.fi);
			lens.pushb(res.se + i.w);
		}
		int len=0;
		if(sz(lens)==1){
			diam=max(diam, len=lens.back());
		}
		else if(sz(lens)>1){
			auto it = max_element(all(lens));
			len=*it; lens.erase(it);
			it=max_element(all(lens));
			diam=max(diam, len+*it);
		}
		return {diam,len};
	}
};

struct SimpleTree: public Tree<int>{
	SimpleTree(int n=0):Tree(n){}
	void add_edge(int s, int e) { Tree<int>::add_edge(s, e, 1); }
};
