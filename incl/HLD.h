#pragma once
#include "RootedTree.h"

template<typename T, typename F>
struct HLD:public RootedTree<T>{
	using P=RootedTree<T>;
	HLD(const Arr<pair<int,T>>& pi)
	:P(pi), st(n), cn(n), top(n), si(n), tsz(n){
		dfs_size(r);
		int csi=0, ccn=0;
		dfs_hld(r, csi, ccn);
		top[0]=0;
	}

	T q(int u, int v, bool edge_w=true){
		T ret = T();
		int w = lca(u, v);
		while(cn[w]!=cn[u])
			ret = F::q(ret, st.q(si[top[cn[u]]], si[u]+1)), u = p[top[cn[u]]].fi;
		ret = F::q(ret, st.q(si[w]+edge_w, si[u]+1));
		
		while(cn[w]!=cn[v])
			ret = F::q(ret, st.q(si[top[cn[v]]], si[v]+1)), v = p[top[cn[v]]].fi;
		ret = F::q(ret, st.q(si[w]+edge_w, si[v]+1));

		return ret;
	}
	T q_non_commutative(){return T();}

	void upd(int cur, T w){return st.upd(si[cur], w);}
	void upd(int s, int e, T w){}
protected:
	using P::n;using P::r;using P::p;using P::ch;using P::lca;
	SegBU<T, F> st;
	Arr<int> cn,top,si,tsz;

	int dfs_size(int cur){
		tsz[cur]=1;
		for(const auto& i:ch[cur])
			tsz[cur]+=dfs_size(i.fi);
		sort(all(ch[cur]), [&](auto a, auto b){return tsz[a.fi]>tsz[b.fi];});
		return tsz[cur];
	}

	void dfs_hld(int cur, int& csi, int& ccn){
		st.upd(si[cur]=csi++, p[cur].se);
		cn[cur]=ccn;
		rep(i,sz(ch[cur])){
			if(i)
				top[++ccn]=ch[cur][i].fi;
			dfs_hld(ch[cur][i].fi, csi, ccn);
		}
	}
};