#pragma once
#include "LCA.h"
#include "Seg.h"

template<typename T, typename F>
struct HLD: public LCA<T>{
	using RT=RootedTree<T>;
	HLD(const Arr<pair<int,T>>& pi)
	:LCA<T>(pi), st(n), cn(n), top(n), si(n){
		int csi=0, ccn=0;
		dfs_hld(r, csi, ccn);
		top[0]=0;
	}

	T q(int u, int v, bool edge_w=true){
		T ret = F::id();
		int w = lca(u, v);
		while(cn[w]!=cn[u])
			ret = F::q(ret, st.q(si[top[cn[u]]], si[u]+1)), u = p[top[cn[u]]].fi;
		ret = F::q(ret, st.q(si[w]+edge_w, si[u]+1));
		
		while(cn[w]!=cn[v])
			ret = F::q(ret, st.q(si[top[cn[v]]], si[v]+1)), v = p[top[cn[v]]].fi;
		ret = F::q(ret, st.q(si[w]+edge_w, si[v]+1));

		return ret;
	}

	void upd(int cur, T w){return st.upd(si[cur], w);}
	void upd(int s, int e, T w){}
protected:
	using RT::n;using RT::r;using RT::ch;using RT::p;using RT::tsz;using LCA<T>::lca;
	Seg<T,F> st;
	Arr<int> cn,top,si;

	void dfs_hld(int cur, int& csi, int& ccn){
		sort(all(ch[cur]), [this](auto a, auto b){return this->tsz[a.fi]>this->tsz[b.fi];});
		st.upd(si[cur]=csi++, p[cur].se);
		cn[cur]=ccn;
		rep(i,sz(ch[cur])){
			if(i)
				top[++ccn]=ch[cur][i].fi;
			dfs_hld(ch[cur][i].fi, csi, ccn);
		}
	}
};