#pragma once
#include "Core.h"
#include "DisjointSet.h"

template<typename T>
struct WeightedGraph {
	struct Edge {
		int s;
		int e;
		int ei;
		T w;
		Edge(int s, int e, int ei, T w):s(s),e(e),ei(ei),w(w){};
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	int n;
	vector<vector<Edge>> g;

	WeightedGraph(int n) :n(n), g(n) {}

	inline void add_edge(int s, int e, T w, bool dir=true){ 
		g[s].push_back(Edge(s, e, g[s].size(), w));
		if(!dir)
			g[e].push_back(Edge(e, s, g[e].size(), w));
	}

	void dijkstra(vector<T>& d, vector<pair<int, int>>& p, int s) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;//dest, v
		d = vector<T>(n, inf<T>());
		p = vector<pair<int, int>>(n, { inf<int>(), inf<int>() });
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

	void dijkstra_vsq(vector<T>& d, vector<pair<int, int>>& p, int s) {

	}

	void floyd(){
		//v * dijkstra_vsq?
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
		q.push({ 0, inf<int>(), 0 });
		while (q.size()) {
			auto cur = q.top();
			q.pop();

			auto curv = cur.s == inf<int>() ? 0 : g[cur.s][cur.ei].e;
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

struct FlowWeight {
	int si;
	ll cap, cost;
	FlowWeight(ll cost) :cost(cost) {}
	FlowWeight(int si, ll cap, ll cost) :si(si), cap(cap), cost(cost) {}
	bool operator< (const FlowWeight& r)const { return cost < r.cost; }
	FlowWeight operator+(const FlowWeight& r)const { return cost + r.cost; }
};
template<>
inline FlowWeight inf() { return inf<ll>(); }

struct FlowGraph : public WeightedGraph<FlowWeight> {
	int src, snk;

	FlowGraph(int n) :WeightedGraph(n + 2), src(n), snk(n + 1) {}

	inline void add_edge(int s, int e, ll cap, ll cost) {
		WeightedGraph::add_edge(s, e, FlowWeight(g[e].size(), cap, cost));
		WeightedGraph::add_edge(e, s, FlowWeight(g[s].size() - 1, 0, -cost));
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
	ll process_mf(int v, ll mf, vector<bool>&& vis) {
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
		vector<FlowWeight> ub;
		vector<pair<int, int>> p;
		if (!spfa(ub, p, src) || p[snk].first == inf<int>())
			return { 0, 0 };
		for (int cur = snk; p[cur].first != inf<int>(); cur = p[cur].first)
			flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
		ll cost = 0;
		for (int cur = snk; p[cur].first != inf<int>(); cur = p[cur].first) {
			auto& e = g[p[cur].first][p[cur].second];
			e.w.cap -= flow;
			g[e.e][e.w.si].w.cap += flow;
			cost += e.w.cost*flow;
		}

		return {cost, flow};
	}

	virtual bool valid_spfa_edge(const Edge& e) const override { return e.w.cap; }
};

struct Graph: public WeightedGraph<int>{
	Graph(int n):WeightedGraph<int>(n) {}

	inline void add_edge(int s, int e, bool dir=true) {
		WeightedGraph::add_edge(s, e, 1, dir);
	}

	vector<int> topo_sort() {
		vector<int> in(n);
		forh(i, 0, n){
			for(auto &j:g[i])
				in[j.e]++;
		}
		queue<int> q;
		forh(i, 0, n)
			if (!in[i])
				q.push(i);
		vector<int> ret;
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
		vector<int> state(n), ord(n), scc_id(n, -1);
		stack<int> stk;
		int o=0;
		forh(i, 0, n){
			if(!state[i])
				dfs_scc(i, o, state, ord, scc_id, stk);
		}
		int c=0;
		vector<int> sccid2idx(n, -1);
		for(auto i:scc_id)
			if(sccid2idx[i]==-1)
				sccid2idx[i]=c++;

		vector<vector<int>> ret(c);
		forh(i, 0, n)
			ret[sccid2idx[scc_id[i]]].push_back(i);
		return ret;
	}

	void bcc(){

	}

private:
	int dfs_scc(int v, int &o, vector<int> &state, vector<int>& ord, vector<int>& scc_id, stack<int>& stk){
		state[v]=1;
		stk.push(v);
		int ret = ord[v]=o++;
		for(auto i: g[v]){
			switch(state[i.e]){
				case 0:
					ret = min(ret, dfs_scc(i.e, o, state, ord, scc_id, stk));
					break;
				case 1://back
					ret = min(ret, ord[i.e]);
					break;
				case 2:
					if(ord[i.e]>ord[v])//fwd
						;
					else if(ord[i.e]<ord[v]){//cross
						if(scc_id[i.e]==-1)
							ret = min(ret, ord[i.e]);
					}
					else//loop
						;
					break;
			}
		}
		if(ret == ord[v]){
			int cur;
			do{
				cur = stk.top();
				stk.pop();
				scc_id[cur]=ord[v];
			}while(stk.size() && cur!=v);
		}

		state[v]=2;
		return ret;
	}
	//bfs()
	//maybe useless?
};

struct UndirectedGraph: public Graph{
	UndirectedGraph(int n):Graph(n){}

	inline void add_edge(int s, int e) {
		Graph::add_edge(s, e, false);
	}

	vector<int> articul_points(){
		vector<int> ord(n, -1), ret;
		int o=0;
		forh(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_ap(i, -1, o, ord, ret);
		}
		return ret;
	}

	vector<pair<int,int>> bridges(){
		vector<int> ord(n, -1);
		vector<pair<int,int>> ret;
		int o=0;
		forh(i, 0, n){
			if(ord[i] != -1)
				continue;
			dfs_bridge(i, -1, o, ord, ret);
		}
		return ret;
	}
private:
	int dfs_ap(int v, int p, int &o, vector<int>& ord, vector<int>& ans){
		int ret = ord[v]=o++;
		int subcnt=0;
		bool isAP = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_ap(i.e, v, o, ord, ans);
			subcnt++;
			isAP |= res>=ord[v];
			ret = min(ret, res);
		}
		if(isAP && (p!=-1 || subcnt>1))
				ans.push_back(v);
		return ret;
	}
	int dfs_bridge(int v, int p, int &o, vector<int>& ord, vector<pair<int, int>>& ans){
		int ret = ord[v]=o++;
		bool conn = false;
		for(auto i: g[v]){
			if(ord[i.e] != -1){
				if(p!=-1)
					conn |= ord[i.e]<ord[p];
				ret = min(ret, ord[i.e]);
				continue;
			}

			int res=dfs_bridge(i.e, v, o, ord, ans);
			conn |= res<ord[v];
			ret = min(ret, res);
		}
		if(!conn && p!=-1)
				ans.push_back({min(v, p), max(v, p)});
		return ret;
	}
};