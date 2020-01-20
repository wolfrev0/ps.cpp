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

	tuple<Arr<int>, Arr<Arr<int>>, DirGraph> scc(){
		Arr<int> stat(n), ord(n), scc_id(n, -1);
		stack<int> stk;
		int oi=0, scci=0;
		rep(i,n)
			if(!stat[i])
				dfs_scc(i, stat, ord, stk, oi, scci, scc_id);

		auto grp=Arr<Arr<int>>(scci);
		rep(i,n)
			grp[scc_id[i]].pushb(i);
		DirGraph sccg(scci);
		rep(i,n)
			for(auto& j:g[i])
				if(scc_id[i]!=scc_id[j.e])
					sccg.add_edge(scc_id[i], scc_id[j.e]);

		return {scc_id, grp, sccg};
	}

private:
	int dfs_scc(int v, Arr<int>& stat, Arr<int>& ord, stack<int>& stk, int& oi, int &scci, Arr<int>& scc_id){
		stat[v]=1;
		stk.push(v);
		int ret = ord[v]=oi++;
		for(auto i: g[v]){
			if(stat[i.e]==0)//tree edge
				ret = min(ret, dfs_scc(i.e, stat, ord, stk, oi, scci, scc_id));
			else if(stat[i.e]==1)//bwd edge
				ret = min(ret, ord[i.e]);
			else if(stat[i.e]==2){
				if(ord[i.e]>ord[v])//fwd edge
					;
				else//cross edge
					if(scc_id[i.e]==-1)
						ret=min(ret, ord[i.e]);
			}
		}
		//nothing goes to ancestor => root of scc
		if(ret == ord[v]){
			int cur;
			do{
				cur = stk.top();
				stk.pop();
				scc_id[cur]=scci;
			}while(sz(stk) && cur!=v);
			scci++;
		}

		stat[v]=2;
		return ret;
	}
};