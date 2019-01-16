#pragma once
#include "WeightedGraph.h"
#include "Vec2.h"

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
	  auto vis=vector<bool>(n+2);
		while (ll f = process_mf(src, flow-sum, vis)){
			sum += f;
      vis=vector<bool>(n+2);
    }
		return sum;
	}

	ll dinic(ll flow = inf<ll>()){
		ll sum = 0;
		return sum;
	}

	Vec2<ll> mcmf(ll flow = inf<ll>()) {
		Vec2<ll> ret;
		while (true) {
			auto res = process_mcmf(flow-ret.y);
			ret += res;
			if (!res.x && !res.y)
				break;
		}
		return ret;
	}
private:
	ll process_mf(int v, ll mf, vector<bool>& vis) {
		if (v == snk)
			return mf;

		vis[v] = true;
		for (auto& i : g[v]) {
			if (!vis[i.e] && i.w.cap) {
				ll f = process_mf(i.e, min(mf, i.w.cap), vis);
				if (f > 0) {
					i.w.cap -= f;
					g[i.e][i.w.si].w.cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	Vec2<ll> process_mcmf(ll flow) {
		vector<FlowWeight> ub;
		vector<pair<int, int>> p;
		if (!spfa(ub, p, src) || p[snk].first == inf<int>())
			return {};
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