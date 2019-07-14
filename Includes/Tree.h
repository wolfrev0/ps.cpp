#pragma once
#include "RootedTree.h"

template<typename T>
struct Tree{
	struct Edge{ int e; T w; };
	Tree(int n=0):n(n), g(n){}

	void add_edge(int s, int e, T w){ g[s].pb({e,w}); g[e].pb({s,w}); }
	T diameter()const {	return dfs_diameter(0, -1).fi; }
	
	RootedTree<T> rootize(int r){
		vector<int> pv(n);
		vector<T> pwv(n);
		parvec(r, -1, 0, pv, pwv);
		return RootedTree<T>(pv, pwv);
	}
private:
	int n;
	vector<vector<Edge>> g;
	
	pair<T, T> dfs_diameter(int v, int p)const{
		T diam = 0;
		vector<int> lens;
		for(auto i:g[v]){
			if(i.e==p)
				continue;
			auto res=dfs_diameter(i.e, v);
			diam=max(diam, res.fi);
			lens.pb(res.se + i.w);
		}
		int len=0;
		if(lens.size()==1){
			diam=max(diam, len=lens.back());
		}
		else if(lens.size()>1){
			auto it = max_element(lens.begin(), lens.end());
			len=*it; lens.erase(it);
			it=max_element(lens.begin(), lens.end());
			diam=max(diam, len+*it);
		}
		return {diam,len};
	}
	
	void parvec(int c, int p, T pw, vector<int>& pv, vector<T>& pwv){
		pv[c]=p;
		pwv[c]=pw;
		for(auto i:g[c])
			if(i.e!=p)
				parvec(i.e, c, i.w, pv, pwv);
	}
};

struct SimpleTree: public Tree<int>{
	SimpleTree(int n=0):Tree(n){}
	void add_edge(int s, int e) { Tree<int>::add_edge(s, e, 1); }
};