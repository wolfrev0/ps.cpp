#pragma once
#include "Core.h"

template<typename T>
struct RootedTree{
	struct Edge{ int e; T w; };
	
	RootedTree(const vector<int>& par, const vector<T>& pw):n(sz(par)), ch(n), d(n), anc(n){
		hfor(i,0,n)
			p.pb({par[i], pw[i]});
		r=0;
		while(p[r].e!=-1)
			r=p[r].e;
		hfor(i,0,n)
			if(i!=r)
				ch[p[i].e].pb({i, p[i].w});
		dfs_init(r);
	}
	
	int lca(int a, int b){
		if(d[a]>d[b])
			swap(a,b);
		int diff=d[b]-d[a];
		while(diff){
			b=getanc(b, __builtin_ctz(diff));
			diff -= diff&-diff;
		}
		if(a==b)
			return a;
		hfori(i,0,32)
			if(getanc(a,i)!=getanc(b,i))
				a=getanc(a,i), b=getanc(b,i);
		return getanc(a,0);
	}
	
	//vector<int> pre_tour(){}
	//vector<int> in_tour(){}
	//vector<int> post_tour(){}
	//vector<int> euler_tour(){}
protected:
	int n, r;
	vector<Edge> p;
	vector<vector<Edge>> ch;
	//anc[i][j] = (2^j)th ancestor of i
	vector<int> d;
	vector<vector<int>> anc;
	int getanc(int i, int j){
		if(j<0)
			return i;
		if(sz(anc[i])<=j)
			return -1;
		return anc[i][j];
	}

	vector<int> pbuf;
	void dfs_init(int cur){
		d[cur] = p[cur].e>=0 ? d[p[cur].e]+1 : 0;
		for(int i=1;i<=sz(pbuf);i*=2)
			anc[cur].pb(*(pbuf.end()-i));
		for(const auto &i:ch[cur]){
			pbuf.pb(cur);
			dfs_init(i.e);
			pbuf.eb();
		}
	}
};