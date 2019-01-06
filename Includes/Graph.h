#pragma once
#include "Core.h"
#include "DisjointSet.h"

template<typename T>
struct WeightedGraph {
	struct Edge {
		uint s;
		uint e;
		uint ei;
		T w;
		Edge(uint s, uint e, uint ei, T w):s(s),e(e),ei(ei),w(w){};
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	uint n;
	vector<vector<Edge>> g;

	WeightedGraph(uint n) :n(n), g(n) {}

	inline void add_edge(uint s, uint e, T w, bool dir=false){ 
		g[s].push_back(Edge(s, e, g[s].size(), w));
		if(!dir)
			g[e].push_back(Edge(e, s, g[e].size(), w));
	}

	void dijkstra(vector<T>& d, vector<pair<uint, uint>>& p, int s) {
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

	void dijkstra_vsq(vector<T>& d, vector<pair<uint, uint>>& p, int s) {

	}

	void floyd(){
		//v * dijkstra_vsq?
	}

	bool spfa(vector<T>& ub, vector<pair<uint, uint>>& p, int s) {
		queue<int> q;
		vector<bool> inq(n);
		ub = vector<T>(n, inf<T>());
		p = vector<pair<uint, uint>>(n, { inf<uint>(), inf<uint>() });

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		trav(i, 0u, i < n&&q.size()) {
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

protected:
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }
};

struct MCMFWeight {
	uint si;
	ll cap, cost;
	MCMFWeight(ll cost) :cost(cost) {}
	MCMFWeight(uint si, ll cap, ll cost) :si(si), cap(cap), cost(cost) {}
	bool operator< (const MCMFWeight& r)const { return cost < r.cost; }
	MCMFWeight operator+(const MCMFWeight& r)const { return cost + r.cost; }
};
template<>
inline MCMFWeight inf() { return inf<ll>(); }

struct MCMF : public WeightedGraph<MCMFWeight> {
	uint src, snk;

	MCMF(uint n) :WeightedGraph(n + 2), src(n), snk(n + 1) {}

	inline void add_edge(uint s, uint e, ll cap, ll cost) {
		WeightedGraph::add_edge(s, e, { (uint)g[e].size(), cap, cost });
		WeightedGraph::add_edge(e, s, { (uint)g[s].size() - 1, 0, -cost });
	}

	ll mf(ll flow = inf<ll>()) {
		ll sum = 0;
		while (ll f = process_mf(src, flow - sum, vector<bool>(n)))
			sum += f;
		return sum;
	}

	pair<ll, ll> mcmf(ll flow = inf<ll>()) {
		pair<ll, ll> ret = { 0, 0 };
		while (true) {
			auto res = process_mcmf(flow-ret.second);
			ret += res;
			if (!res.first && !res.second)
				break;
		}
		return ret;
	}
private:
	ll process_mf(uint v, ll mf, vector<bool>&& vis) {
		if (v == snk)
			return mf;

		vis[v] = true;
		for (auto& i : g[v]) {
			if (!vis[i.e] && i.w.cap) {
				ll f = process_mf(i.e, min(mf, i.w.cap), vector<bool>(vis));
				if (f > 0) {
					i.w.cap -= f;
					g[i.e][i.w.si].w.cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	pair<ll, ll> process_mcmf(ll flow) {
		vector<MCMFWeight> ub;
		vector<pair<uint, uint>> p;
		if (!spfa(ub, p, src) || p[snk].first == inf<uint>())
			return { 0, 0 };
		for (int cur = snk; p[cur].first != inf<uint>(); cur = p[cur].first)
			flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
		ll cost = 0;
		for (int cur = snk; p[cur].first != inf<uint>(); cur = p[cur].first) {
			auto& e = g[p[cur].first][p[cur].second];
			e.w.cap -= flow;
			g[e.e][e.w.si].w.cap += flow;
			cost += e.w.cost*flow;
		}

		return {cost, flow};
	}

	virtual bool valid_spfa_edge(const Edge& e) const override { return e.w.cap; }
};

struct Graph: public WeightedGraph<uint>{
	Graph(uint n):WeightedGraph<uint>(n) {}

	inline void add_edge(uint s, uint e, bool dir=false) {
		WeightedGraph::add_edge(s, e, 1);
	}

	vector<uint> topo_sort() {
		vector<int> in(n);
		forh(i, 0, n){
			for(auto &j:g[i])
				in[j.e]++;
		}
		queue<uint> q;
		forh(i, 0, n)
			if (!in[i])
				q.push(i);
		vector<uint> ret;
		while (q.size()) {
			auto cur = q.front();
			ret.push_back(cur);
			q.pop();
			for (auto &i : g[cur])
				if (--in[i.e] == 0)
					q.push(i.e);
		}
		reverse(ret.begin(), ret.end());
		for (auto i: in)
			if (i)
				throw "Error";
		return ret;
	}

	vector<vector<int>> scc(){
		vector<vector<int>> ret;

		return ret;
	}

	 void bcc(){

	 }
	//bfs()
	//maybe useless?
};

struct UndirectedGraph: public Graph{
	UndirectedGraph(uint n):Graph(n){}

	vector<uint> articul_points(){
		vector<uint> ord(n), ret;
		uint o=1;
		forh(i, 0, n){
			if(ord[i])
				continue;
			dfs_ap(i, -1, o, ord, ret);
		}
		return ret;
	}

	vector<pair<uint,uint>> bridges(){
		vector<uint> ord(n);
		vector<pair<uint,uint>> ret;
		uint o=1;
		forh(i, 0, n){
			if(ord[i])
				continue;
			dfs_bridge(i, -1, o, ord, ret);
		}
		return ret;
	}
private:
	uint dfs_ap(uint v, uint p, uint &o, vector<uint>& ord, vector<uint>& ans){
		uint ret = ord[v]=o++;
		uint subcnt=0;
		bool isAP = false;
		for(auto i: g[v]){
			if(ord[i.e]){
				ret = min(ret, ord[i.e]);
				continue;
			}

			uint res=dfs_ap(i.e, v, o, ord, ans);
			subcnt++;
			isAP |= res>=ord[v];
			ret = min(ret, res);
		}
		if(isAP && (p!=-1u || subcnt>1))
				ans.push_back(v);
		return ret;
	}
	uint dfs_bridge(uint v, uint p, uint &o, vector<uint>& ord, vector<pair<uint, uint>>& ans){
		uint ret = ord[v]=o++;
		bool conn = false;
		for(auto i: g[v]){
			if(ord[i.e]){
				if(p!=-1)
					conn |= ord[i.e]<ord[p];
				ret = min(ret, ord[i.e]);
				continue;
			}

			uint res=dfs_bridge(i.e, v, o, ord, ans);
			conn |= res<ord[v];
			ret = min(ret, res);
		}
		if(!conn && p!=-1u)
				ans.push_back({min(v, p), max(v, p)});
		return ret;
	}
};