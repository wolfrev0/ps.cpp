#pragma once
#include "Graph.h"

struct DirGraph : public Graph<int> {
	DirGraph(int n = 0) : Graph<int>(n) {}

	void add_edge(int s, int e, bool bidir = false) {
		Graph::add_edge(s, e, 1, bidir);
	}

	DirGraph reversed() {
		DirGraph ret(n);
		for(auto& i : g)
			for(auto j : i) ret.add_edge(j.e, j.s);
		return ret;
	}

	Arr<int> topo_sort() {
		Arr<int> in(n);
		for(int i = 0; i < n; i++)
			for(auto& j : g[i]) in[j.e]++;
		queue<int> q;
		for(int i = 0; i < n; i++)
			if(!in[i]) q.push(i);
		Arr<int> ret;
		while(sz(q)) {
			auto cur = q.front();
			ret.pushb(cur);
			q.pop();
			for(auto& i : g[cur])
				if(--in[i.e] == 0) q.push(i.e);
		}
		return ret;
	}

	Arr<int> topo_sort_lex() {
		Arr<int> in(n);
		for(int i = 0; i < n; i++)
			for(auto& j : g[i]) in[j.e]++;
		PQMin<int> q;
		for(int i = 0; i < n; i++)
			if(!in[i]) q.push(i);
		Arr<int> ret;
		while(sz(q)) {
			auto cur = q.top();
			ret.pushb(cur);
			q.pop();
			for(auto& i : g[cur])
				if(--in[i.e] == 0) q.push(i.e);
		}
		return ret;
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_tarjan() {
		Arr<Arr<int>> scc;
		Arr<int> stat(n), ord(n);
		stack<int> stk;
		int ordi = 0;
		for(int i = 0; i < n; i++)
			if(!stat[i]) dfs_tj(i, stat, ord, ordi, stk, scc);
		return scc_util(scc);
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_kosaraju() {
		Arr<int> post_ord;
		Arr<bool> vis(n);
		for(int i = 0; i < n; i++)
			if(!vis[i]) dfs_ksrj(i, post_ord, vis, *this);
		auto rg = reversed();
		Arr<Arr<int>> scc;
		fill(vis.begin(), vis.end(), false);
		reverse(post_ord.begin(), post_ord.end());
		for(auto i : post_ord)
			if(!vis[i]) scc.pushb({}), dfs_ksrj(i, scc.back(), vis, rg);
		return scc_util(scc);
	}

private:
	int dfs_tj(int v, Arr<int>& stat, Arr<int>& ord, int& ordi, stack<int>& stk,
	           Arr<Arr<int>>& scc) {
		stat[v] = 1;
		stk.push(v);
		int ret = ord[v] = ordi++;
		for(auto i : g[v]) {
			if(stat[i.e] == 0)  // tree edge
				ret = min(ret, dfs_tj(i.e, stat, ord, ordi, stk, scc));
			else if(stat[i.e] == 1)  // bwd edge
				ret = min(ret, ord[i.e]);
			else if(stat[i.e] == 2) {
				if(ord[i.e] <= ord[v])  // cross edge which not scc grouped
					ret = min(ret, ord[i.e]);
				// else fwd edge
			}
			// else state==3 (scc grouped)
		}
		// nothing goes to ancestor => root of scc
		if(ret == ord[v]) {
			scc.pushb({});
			int prv = -1;
			while(sz(stk) && prv != v) {
				scc.back().pushb(prv = stk.top());
				stat[prv] = 3;
				stk.pop();
			}
		} else
			stat[v] = 2;
		return ret;
	}

	void dfs_ksrj(int v, Arr<int>& out, Arr<bool>& vis, DirGraph& g) {
		vis[v] = true;
		for(auto i : g.g[v])
			if(!vis[i.e]) dfs_ksrj(i.e, out, vis, g);
		out.pushb(v);
	}

	tuple<Arr<Arr<int>>, Arr<int>, DirGraph> scc_util(Arr<Arr<int>> scc) {
		Arr<int> v2scc(n);
		for(int i = 0; i < sz(scc); i++)
			for(auto j : scc[i]) v2scc[j] = i;

		DirGraph sccg(sz(scc));
		for(int i = 0; i < n; i++)
			for(auto& j : g[i])
				if(v2scc[i] != v2scc[j.e]) sccg.add_edge(v2scc[i], v2scc[j.e]);
		return {scc, v2scc, sccg};
	}
};

struct SAT2 {
	SAT2(int n) : n(n), g(n * 2) {}
	void add(int a, int b, bool inva, bool invb) {
		g.add_edge(a * 2 + inva, b * 2 + !invb);
		g.add_edge(b * 2 + invb, a * 2 + !inva);
	}
	Arr<int> sat() {
		auto [sccs, v2scc, __] = g.scc_tarjan();
		bool fail = false;
		for(int i = 0; i < n; i++) fail = fail or v2scc[i * 2] == v2scc[i * 2 + 1];
		if(fail) return {};
		Arr<int> r(n, -1);
		for(auto scc : sccs) {
			bool v = false;
			for(auto j : scc)
				if(r[j / 2] != -1) {
					v = j % 2 ? !r[j / 2] : r[j / 2];
					break;
				}
			for(auto j : scc) r[j / 2] = j % 2 ? !v : v;
		}
		return r;
	}
	int n;
	DirGraph g;
};
