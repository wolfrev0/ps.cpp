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
		forh(i, 0, n)
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
		for (auto i : in)
			if (i)
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
		uint s;
		uint e;
		uint ei;
		T w;
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	const uint n;
	vector<vector<Edge>> g;

	WeightedGraph(uint n) :n(n), g(n) {}

	inline void add_edge(uint s, uint e, T w) { g[s].push_back({ s, e, g[s].size(), w }); }

	void dijikstra(vector<T>& d, vector<pair<uint, uint>>& p, int s) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;//dest, v
		d = vector<T>(n, inf<T>());
		p = vector<pair<uint, uint>>(n, { inf<uint>(), inf<uint>() });
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
					d[i.e] = cur.first + i.w;
					p[i.e] = { cur.second, i.ei };
					pq.push({ cur.first + i.w, i.e });
				}
			}
		}
	}

	bool spfa(vector<T>& ub, vector<pair<uint, uint>>& p, int s) {
		queue<int> q;
		vector<bool> inq(n);
		ub = vector<T>(n, inf<T>());
		p = vector<pair<uint, uint>>(n, { inf<uint>(), inf<uint>() });

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		trav1(i, 0u, i < n&&q.size()) {
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
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }

	vector<Edge> mst_prim() {

		vector<Edge> ret;
		vector<bool> vis(n);
		priority_queue<Edge, vector<Edge>, greater<Edge>> q;
		q.push({ 0, inf<uint>(), 0 });
		while (q.size()) {
			auto cur = q.top();
			q.pop();

			auto curv = cur.s == inf<uint>() ? 0 : g[cur.s][cur.ei].e;
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
};

struct MCMFWeight {
	uint si;
	int cap, cost;
	MCMFWeight(int cost) :cost(cost) {}
	MCMFWeight(uint si, int cap, int cost) :si(si), cap(cap), cost(cost) {}
	bool operator< (const MCMFWeight& r)const { return cost < r.cost; }
	MCMFWeight operator+(const MCMFWeight& r)const { return cost + r.cost; }
};
template<>
inline MCMFWeight inf() { return inf<int>(); }

struct MCMF : public WeightedGraph<MCMFWeight> {
	uint src, snk;

	MCMF(uint n) :WeightedGraph(n + 2), src(n), snk(n + 1) {}

	inline void add_edge(uint s, uint e, int cap, int cost) {
		WeightedGraph::add_edge(s, e, { g[e].size(), cap, cost });
		WeightedGraph::add_edge(e, s, { g[s].size() - 1, 0, -cost });
	}

	int process(uint v, int mf, vector<bool>& vis) {
		if (v == snk)
			return mf;

		vis[v] = true;
		for (auto& i : g[v]) {
			if (!vis[i.e] && i.w.cap) {
				int f = process(i.e, min(mf, i.w.cap), vis);
				if (f > 0) {
					i.w.cap -= f;
					g[i.e][i.w.si].w.cap += f;
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
		vector<pair<uint, uint>> p;
		if (!spfa(ub, p, src) || p[snk].first == inf<uint>())
			return { 0, 0 };
		for (int cur = snk; p[cur].first != inf<uint>(); cur = p[cur].first)
			flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
		for (int cur = snk; p[cur].first != inf<uint>(); cur = p[cur].first) {
			auto& e = g[p[cur].first][p[cur].second];
			e.w.cap -= flow;
			g[e.e][e.w.si].w.cap += flow;
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