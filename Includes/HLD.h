#pragma once
#include "LCA.h"

template<typename T, typename U=T>
struct HLD:public LCA<T>, public Seg<T, U>{
	using L=LCA<T>;
	using S=Seg<T, U>;
	HLD(const Tree<T>& t, int r)
	:L(t, r), S(n), chain(n), head(n), segidx(n), sz(n){
		dfs_size(r);
		int segi=0, cur_chain=0;
		dfs_hld(r, segi, cur_chain);
		head[0]=0;
	}

	//commutativeness free
	T query(int u, int v, bool edge_w=true){
		T ret = T();
		int w = lca(u, v);
		while(chain[w]!=chain[u])
			ret = S::q(ret, S::query(segidx[head[chain[u]]], segidx[u]+1)), u = parent[head[chain[u]]].e;
		ret = S::q(ret, S::query(segidx[w]+edge_w, segidx[u]+1));

		vector<pair<int,int>> ranges;
		while(chain[w]!=chain[v])
			ranges.emplace_back(segidx[head[chain[v]]], segidx[v]+1), v = parent[head[chain[v]]].e;
		ranges.emplace_back(segidx[w]+1, segidx[v]+1);
		reverse(ranges.begin(), ranges.end());
		for(const auto&i:ranges)
			ret = S::q(ret, S::query(i.first, i.second));

		return ret;
	}

	void update(int cur, U w){return S::update(segidx[cur], w);}
	void update(int s, int e, U w){}
protected:
	using L::n;
	using L::r;
	using L::parent;
	using L::children;
	using L::lca;
	vector<int> chain;
	vector<int> head;
	vector<int> segidx;
	vector<int> sz;

	int dfs_size(int cur){
		sz[cur]=1;
		for(const auto& i:children[cur])
			sz[cur]+=dfs_size(i.e);
		sort(children[cur].begin(), children[cur].end(), [&](auto a, auto b){return sz[a.e]>sz[b.e];});
		return sz[cur];
	}

	void dfs_hld(int cur, int& segi, int& cur_chain){
		S::update(segidx[cur]=segi++, parent[cur].w);
		chain[cur]=cur_chain;
		auto c = children[cur];
		hfor(i, 0, c.size()){
			if(i)
				head[++cur_chain]=c[i].e;
			dfs_hld(c[i].e, segi, cur_chain);
		}
	}
};