#pragma once
#include "Graph.h"

struct DirGraph: public Graph<int>{
	DirGraph(int n=0):Graph<int>(n) {}

	void add_edge(int s, int e, bool dir=true) {Graph::add_edge(s, e, 1, dir);}

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
		Arr<int> stat(n), ord(n), sccid(n, -1);
		stack<int> stk;
		int oi=0, scci=0;
		rep(i,n)
			if(!stat[i])
				dfs_tj(i, stat, ord, stk, oi, scci, sccid);

		auto grp=Arr<Arr<int>>(scci);
		rep(i,n)
			grp[sccid[i]].pushb(i);
		DirGraph sccg(scci);
		rep(i,n)
			for(auto& j:g[i])
				if(sccid[i]!=sccid[j.e])
					sccg.add_edge(sccid[i], sccid[j.e]);

		return {grp, sccid, sccg};
	}
	DirGraph reversed(){
		DirGraph ret(n);
		for(auto& i:g)
			for(auto j:i)
				ret.add_edge(j.e, j.s);
		return ret;
	}
	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_kosaraju(){
		Arr<int> post_ord;
		Arr<bool> vis(n);
		rep(i,n)
			if(!vis[i])
				dfs_ksrj(i, post_ord, vis, *this);
				
		auto rg=reversed();
		Arr<Arr<int>> grp;
		fill(all(vis), false);
		reverse(all(post_ord));
		for(auto i:post_ord)
			if(!vis[i])
				grp.pushb({}), dfs_ksrj(i, grp.back(), vis, rg);

		Arr<int> sccid(n);
		rep(i,sz(grp))
			for(auto j:grp[i])
				sccid[j]=i;
		DirGraph sccg(sz(grp));
		for(auto& i:g)
			for(auto j:i)
				if(sccid[j.s] != sccid[j.e])
					sccg.add_edge(sccid[j.s], sccid[j.e]);
		return {grp, sccid, sccg};
	}
private:
	int dfs_tj(int v, Arr<int>& stat, Arr<int>& ord, stack<int>& stk, int& oi, int &scci, Arr<int>& sccid){
		stat[v]=1;
		stk.push(v);
		int ret = ord[v]=oi++;
		for(auto i: g[v]){
			if(stat[i.e]==0)//tree edge
				ret = min(ret, dfs_tj(i.e, stat, ord, stk, oi, scci, sccid));
			else if(stat[i.e]==1)//bwd edge
				ret = min(ret, ord[i.e]);
			else if(stat[i.e]==2){
				if(ord[i.e]>ord[v])//fwd edge
					;
				else//cross edge
					if(sccid[i.e]==-1)
						ret=min(ret, ord[i.e]);
			}
		}
		//nothing goes to ancestor => root of scc
		if(ret == ord[v]){
			int cur;
			do{
				cur = stk.top();
				stk.pop();
				sccid[cur]=scci;
			}while(sz(stk) && cur!=v);
			scci++;
		}

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
};