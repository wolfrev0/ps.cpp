#pragma once
#include "Core.h"
#include "DisjointSet.h"

template<typename T>
struct Graph {
	struct Edge {
		int s;
		int e;
		int ei;
		T w;
		Edge():s(0),e(0),ei(0),w(T()){};
		Edge(int s, int e, int ei, T w):s(s),e(e),ei(ei),w(w){};
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	int n;
	vector<vector<Edge>> g;

	Graph(int n=0) :n(n), g(n) {}
	Graph(const Graph& r) :n(r.n), g(r.g) {}

	void add_edge(int s, int e, T w, bool dir=true){ 
		g[s].push_back(Edge(s, e, g[s].size(), w));
		if(!dir)
			g[e].push_back(Edge(e, s, g[e].size(), w));
	}

	void dijkstra(vector<T>& d, vector<pair<int, int>>& p, int s) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;//dest, v
		d = vector<T>(n, inf<T>());
		p = vector<pair<int, int>>(n, { inf<T>(), inf<T>() });
		d[s] = 0;
		pq.push({ 0, s });
		while (!pq.empty())
		{
			auto cur = pq.top();
			pq.pop();

			if (cur.first != d[cur.second])
				continue;

			auto& cg = g[cur.second];
			for (auto &i : cg) {
				if (d[i.e] > cur.first + i.w) {
					p[i.e] = { cur.second, i.ei };
					pq.push({ d[i.e]=cur.first + i.w, i.e });
				}
			}
		}
	}

	void dijkstra_vsq(vector<T>& d, vector<pair<int, int>>& p, int s) {

	}

	int floyd(int s, int e, int m, vector<vector<vector<int>>>& memo){
		if(m==n){
			for(auto& i:g[s])
				if(i.e==e)
					return i.w;
			return inf<T>();
		}
		auto& ret=memo[s][e][m];
		if(ret!=-1)
			return ret;
		return ret = min(floyd(s, e, m+1, memo), floyd(s, m, m+1, memo)+floyd(m, e, m+1, memo));
	}

	bool spfa(vector<T>& ub, vector<pair<int, int>>& p, int s) {
		queue<int> q;
		vector<bool> inq(n);
		ub = vector<T>(n, inf<T>());
		p = vector<pair<int, int>>(n, { inf<int>(), inf<int>() });

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		trav(i, 0, i < n&&q.size()) {
			int qsz = q.size();
			while (qsz--) {
				int j = q.front();
				inq[j] = false;
				q.pop();
				for (auto k : g[j]) {
					if (valid_spfa_edge(k) && ub[j] + k.w < ub[k.e]) {
						p[k.e] = { j, k.ei };
						ub[k.e] = ub[j] + k.w;
						if (!inq[k.e]) {
							inq[k.e] = true;
							q.push(k.e);
						}
					}
				}
			}
		}
		return q.empty();
	}

	vector<Edge> mst_prim() {

		vector<Edge> ret;
		vector<bool> vis(n);
		priority_queue<Edge, vector<Edge>, greater<Edge>> q;
		q.push({ 0, inf<T>(), 0 });
		while (q.size()) {
			auto cur = q.top();
			q.pop();

			auto curv = cur.s == inf<T>() ? 0 : g[cur.s][cur.ei].e;
			if (vis[curv])
				continue;
			vis[curv] = true;
			if (cur.s != -1)
				ret.push_back(cur);

			for (auto &i : g[curv]) {
				if (!vis[i.e]) {
					q.push(i);
				}
			}
		}
		return ret;
	}

	vector<Edge> mst_kruskal() {
		vector<Edge> e;
		for (auto &i : g)
			for (auto &j : i)
				e.push_back(j);
		sort(e.begin(), e.end());

		DisjointSet djs(n);
		vector<Edge> ret;
		for (auto &i : e) {
			int ie = g[i.s][i.ei].e;
			if (djs.find(i.s) != djs.find(ie)) {
				djs.uni(i.s, ie);
				ret.push_back(i);
			}
		}
		return ret;
	}

protected:
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }
};