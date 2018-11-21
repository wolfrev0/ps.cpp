#pragma once
#include "Core.h"
#include "DisjointSet.h"

struct Graph {
	const int n;
	vector<vector<int>> g;
	vector<int> in;

	Graph(int n) :n(n), g(n), in(n) {}

	inline void add_edge(int s, int e) {
		g[s].push_back(e);
		in[e]++;
	}

	vector<int> topo_sort() {
		queue<int> q;
		forh(i, 0u, n)
			if (!in[i])
				q.push(i);
		vector<int> ret;
		while (q.size()) {
			auto cur = q.front();
			ret.push_back(cur);
			q.pop();
			for (auto i : g[cur])
				if (--in[i] == 0)
					q.push(i);
		}
		reverse(ret.begin(), ret.end());
		forh(i, 0u, n)
			if (in[i])
				throw "Error";
		return ret;
	}
	//dfs()
	//bfs()
	//maybe useless?
};

template<typename T>
struct WeightedGraph {
	struct Edge {
		int dest;
		T w;
	};
	const int n;
	vector<vector<Edge>> g;

	WeightedGraph(int n) :n(n), g(n) {}

	inline void add_edge(int s, int e, T w) { g[s].push_back({ e, w }); }

	void dijikstra(vector<T>& d, vector<pair<int, int>>& p, int s) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;//dest, v
		d.resize(n, inf<int>());
		p.resize(n, { -1, -1 });
		d[s] = 0;
		pq.push({ 0, s });
		while (!pq.empty())
		{
			auto cur = pq.top();
			pq.pop();

			if (cur.first != d[cur.second])
				continue;

			auto& cg = g[cur.second];
			forh(i, 0u, cn)
			{
				if (d[cg[i].v] > cur.first + cg[i].w) {
					d[cg[i].v] = cur.first + cg[i].w;
					p[cg[i].v] = { cur.second, i };
					pq.push({ cur.first + cg[i].w,cg[i].v });
				}

			}
		}
	}

	bool spfa(vector<T>& ub, vector<pair<int, int>>& p, int s) {
		queue<int> q;
		vector<bool> inq(n);
		ub.resize(n, inf<int>());
		p.resize(n, { -1, -1 });

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		int i;
		for (i = 0; i < n && q.size(); i++) {
			int qsz = q.size();
			while (qsz--) {
				int j = q.front();
				inq[j] = false;
				q.pop();
				forh(k, 0u, g[j].size())
					if (valid_spfa_edge(g[j][k]) && ub[j] + g[j][k].w < ub[g[j][k].dest]) {
						p[g[j][k].dest] = { j, k };
						ub[g[j][k].dest] = ub[j] + g[j][k].w;
						if (!inq[g[j][k].dest]) {
							inq[g[j][k].dest] = true;
							q.push(g[j][k].dest);
						}
					}
			}
		}
		return q.empty();
	}
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }

	vector<pair<int, int>> mst_prim() {
		struct E {
			int cost, s, ei;
			bool operator<(const E& r)const { return cost > r.cost; }
		};

		vector<pair<int, int>> ret;
		vector<bool> vis(n);
		priority_queue<E> q;
		q.push({ 0, -1, 0 });
		while (q.size()) {
			auto cur = q.top();
			q.pop();

			auto curv = cur.s == -1 ? 0 : g[cur.s][cur.ei].dest;
			if (vis[curv])
				continue;
			vis[curv] = true;
			if (cur.s != -1)
				ret.push_back({ cur.s, cur.ei });

			forh(i, 0, g[curv].size()) {
				auto &r = g[curv];
				if (!vis[r[i].dest])
					q.push({ r[i].w, curv, i });
			}
		}
		return ret;
	}

	vector<pair<int, int>> mst_kruskal() {
		struct E {
			int cost, s, ei;
			bool operator<(const E& r)const { return cost < r.cost; }
		};
		vector<E> e;
		forh(i, 0, n) {
			auto &gi = g[i];
			forh(j, 0, gi.size()) {
				auto gij = gi[j];
				e.push_back({ gij.w, i, j });
			}
		}
		sort(e.begin(), e.end());

		DisjointSet djs(n);
		vector<pair<int, int>> ret;
		for (auto &i : e) {
			int ie = g[i.s][i.ei].dest;
			if (djs.find(i.s) != djs.find(ie)) {
				djs.uni(i.s, ie);
				ret.push_back({ i.s, i.ei });
			}
		}
		return ret;
	}
};

struct MCMFWeight {
	uint ei;
	int cap, cost;
	MCMFWeight(int cost) :cost(cost) {}
	MCMFWeight(uint ei, int cap, int cost) :ei(ei), cap(cap), cost(cost) {}
	bool operator< (const MCMFWeight& r)const { return cost < r.cost; }
	MCMFWeight operator+(const MCMFWeight& r)const { return cost + r.cost; }
};

struct MCMF : public WeightedGraph<MCMFWeight> {
	int src, snk;

	MCMF(int n) :WeightedGraph(n + 2), src(n), snk(n + 1) {}

	inline void add_edge_mcmf(uint s, uint e, int cap, int cost) {
		WeightedGraph::add_edge(s, e, { g[e].size(), cap, cost });
		WeightedGraph::add_edge(e, s, { g[s].size() - 1, 0, -cost });
	}

	int process(int v, int mf, vector<bool>& vis)
	{
		if (v == snk)
			return mf;

		vis[v] = true;
		for (auto& i : g[v]) {
			if (!vis[i.dest] && i.w.cap) {
				int f = process(i.dest, min(mf, i.w.cap), vis);
				if (f > 0) {
					i.w.cap -= f;
					g[i.dest][i.w.ei].w.cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	int mf() {
		int sum = 0;
		vector<bool> vis(n);
		while (int flow = process(src, inf<int>(), vis)) {
			sum += flow;
			vis = vector<bool>(n);
		}
		return sum;
	}

	pair<int, int> process() {
		pair<int, int> ret = { 0,0 };
		int& flow = ret.second;
		flow = inf<int>();

		vector<MCMFWeight> ub;
		vector<pair<int, int>> p;
		if (!spfa(ub, p, src) || p[snk].first == -1)
			return { 0, 0 };
		for (int cur = snk; p[cur].first != -1; cur = p[cur].first)
			flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
		for (int cur = snk; p[cur].first != -1; cur = p[cur].first) {
			auto& e = g[p[cur].first][p[cur].second];
			e.w.cap -= flow;
			g[e.dest][e.w.ei].w.cap += flow;
			ret.first += e.w.cost*flow;
		}

		return ret;
	}

	pair<int, int> mcmf() {
		pair<int, int> ret = { 0, 0 };
		while (true) {
			auto res = process();
			if (!res.first && !res.second)
				break;
			ret.first += res.first;
			ret.second += res.second;
		}
		return ret;
	}

	virtual bool valid_spfa_edge(const Edge& e) const override { return e.w.cap; }
};