#pragma once
#include "Graph.h"

struct DirGraph: public Graph<int>{
	DirGraph(int n=0):Graph<int>(n) {}

	void add_edge(int s, int e, bool dir=true) {Graph::add_edge(s, e, 1, dir);}

	DirGraph reversed(){
		DirGraph ret(n);
		for(auto& i:g)
			for(auto j:i)
				ret.add_edge(j.e, j.s);
		return ret;
	}

	Arr<int> topo_sort() {
		Arr<int> in(n);
		hfor(i, 0, n){
			for(auto &j:g[i])
				in[j.e]++;
		}
		queue<int> q;
		hfor(i, 0, n)
			if (!in[i])
				q.push(i);
		Arr<int> ret;
		while (sz(q)) {
			auto cur = q.front();
			ret.pushb(cur);
			q.pop();
			for (auto &i : g[cur])
				if (--in[i.e] == 0)
					q.push(i.e);
		}
		return ret;
	}

	Arr<int> topo_sort_lex() {
		Arr<int> in(n);
		hfor(i, 0, n){
			for(auto &j:g[i])
				in[j.e]++;
		}
		PQ<int,Arr<int>,greater<int>> q;
		hfor(i, 0, n)
			if (!in[i])
				q.push(i);
		Arr<int> ret;
		while (sz(q)) {
			auto cur = q.top();
			ret.pushb(cur);
			q.pop();
			for (auto &i : g[cur])
				if (--in[i.e] == 0)
					q.push(i.e);
		}
		return ret;
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_tarjan(){
		Arr<Arr<int>> scc;
		Arr<int> stat(n), ord(n);
		stack<int> stk;
		int ordi=0;
		rep(i,n)
			if(!stat[i])
				dfs_tj(i, stat, ord, ordi, stk, scc);
		return scc_util(scc);
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_kosaraju(){
		Arr<int> post_ord;
		Arr<bool> vis(n);
		rep(i,n)
			if(!vis[i])
				dfs_ksrj(i, post_ord, vis, *this);
		auto rg=reversed();
		Arr<Arr<int>> scc;
		fill(all(vis), false);
		reverse(all(post_ord));
		for(auto i:post_ord)
			if(!vis[i])
				scc.pushb({}), dfs_ksrj(i, scc.back(), vis, rg);
		return scc_util(scc);
	}
private:
	int dfs_tj(int v, Arr<int>& stat, Arr<int>& ord, int& ordi, stack<int>& stk, Arr<Arr<int>>& scc){
		stat[v]=1;
		stk.push(v);
		int ret = ord[v]=ordi++;
		for(auto i: g[v]){
			if(stat[i.e]==0)//tree edge
				ret = min(ret, dfs_tj(i.e, stat, ord, ordi, stk, scc));
			else if(stat[i.e]==1)//bwd edge
				ret = min(ret, ord[i.e]);
			else if(stat[i.e]==2){
				if(ord[i.e]<=ord[v])//cross edge which not scc grouped
					ret=min(ret, ord[i.e]);
				//else fwd edge
			}
			//else state==3 (scc grouped)
		}
		//nothing goes to ancestor => root of scc
		if(ret == ord[v]){
			scc.pushb({});
			int prv=-1;
			while(sz(stk) && prv!=v){
				scc.back().pushb(prv=stk.top());
				stat[prv]=3;
				stk.pop();
			}
		}
		else
			stat[v]=2;
		return ret;
	}

	void dfs_ksrj(int v, Arr<int>& out, Arr<bool>& vis, DirGraph& g){
		vis[v]=true;
		for(auto i:g.g[v])
			if(!vis[i.e])
				dfs_ksrj(i.e, out, vis, g);
		out.pushb(v);
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_util(Arr<Arr<int>> scc){
		Arr<int> v2scc(n);
		rep(i,sz(scc))
			for(auto j:scc[i])
				v2scc[j]=i;
		
		DirGraph sccg(sz(scc));
		rep(i,n)
			for(auto& j:g[i])
				if(v2scc[i]!=v2scc[j.e])
					sccg.add_edge(v2scc[i], v2scc[j.e]);
		return {scc, v2scc, sccg};
	}
};