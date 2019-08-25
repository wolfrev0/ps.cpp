#pragma once
#include "RootedTree.h"

template<typenaem T, T id=T()>
struct HLD:public RootedTree<T>{
	using E=typename Tree<T>::E;
	using P=RootedTree<T>;
	using P::n, P::r;
	struct S:public SegBU<T>{
		S(int n):SegBU<T>(n){}
		T fq(const T& a, const T& b)override{return HLD::fq(a, b);}
	};
	
	RootedTree(const Arr<E>& pinfo)
	:RootedTree<T>(pinfo),v2seg(n),v2i(n),v2sv(n)
	{ dfs(r); }
	
	//Can make commutativeness free, but too complex.
	//wtype: (F=edge, T=vertex) weighted.
	T q(int u, int v, bool wtype){
		T ret=id;
		int l=lca(u,v);
		
		
		// T ret = T();
		// int w = lca(u, v);
		// while(chain[w]!=chain[u])
		// 	ret = S::q(ret, S::query(segidx[head[chain[u]]], segidx[u]+1)), u = parent[head[chain[u]]].e;
		// ret = S::q(ret, S::query(segidx[w]+edge_w, segidx[u]+1));

		// Arr<pair<int,int>> ranges;
		// while(chain[w]!=chain[v])
		// 	ranges.emplace_back(segidx[head[chain[v]]], segidx[v]+1), v = parent[head[chain[v]]].e;
		// ranges.emplace_back(segidx[w]+1, segidx[v]+1);
		// reverse(all(ranges));
		// for(const auto&i:ranges)
		// 	ret = S::q(ret, S::query(i.fi, i.se));

		// return ret;
	}
	
	Arr<S> segv;
	Arr<int> v2seg, v2i, seg2tv;

	Arr<int> buf;
	void dfs(int cur){
		sort(all(ch), [](auto a, auto b){return sz[a.e]>sz[b.e];});
		buf.pushb(cur);
		
		dfs(ch[0].e);
		hfor(i,1,sz(ch))
			dfs(ch[i].e);
		
		if(!sz(ch)){
			int sn=sz(buf);
			segv.pushb({sn});
			seg2tv[sz(segv)-1]=buf.front();
			
			reverse(all(buf));
			hfor(i,0,sn){
				v2seg[buf[i]]=sz(segv)-1;
				segv.back().upd(v2i[buf[i]]=i, buf[i]);
			}
			buf.clear();
		}
	}
};

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

		Arr<pair<int,int>> ranges;
		while(chain[w]!=chain[v])
			ranges.emplace_back(segidx[head[chain[v]]], segidx[v]+1), v = parent[head[chain[v]]].e;
		ranges.emplace_back(segidx[w]+1, segidx[v]+1);
		reverse(all(ranges));
		for(const auto&i:ranges)
			ret = S::q(ret, S::query(i.fi, i.se));

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
	Arr<int> chain;
	Arr<int> head;
	Arr<int> segidx;
	Arr<int> sz;

	int dfs_size(int cur){
		sz[cur]=1;
		for(const auto& i:children[cur])
			sz[cur]+=dfs_size(i.e);
		sort(all(children[cur]), [&](auto a, auto b){return sz[a.e]>sz[b.e];});
		return sz[cur];
	}

	void dfs_hld(int cur, int& segi, int& cur_chain){
		S::update(segidx[cur]=segi++, parent[cur].w);
		chain[cur]=cur_chain;
		auto c = children[cur];
		hfor(i, 0, sz(c)){
			if(i)
				head[++cur_chain]=c[i].e;
			dfs_hld(c[i].e, segi, cur_chain);
		}
	}
};