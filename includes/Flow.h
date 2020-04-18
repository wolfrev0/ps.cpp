#pragma once
#include "Graph.h"

struct FlowW {
	int si;
	i64 cap, cost;
	FlowW(i64 cost) :cost(cost) {}
	FlowW(int si, i64 cap, i64 cost) :si(si), cap(cap), cost(cost) {}
	bool operator< (const FlowW& r)const { return cost < r.cost; }
	bool operator> (const FlowW& r)const { return cost > r.cost; }
	FlowW operator+(const FlowW& r)const { return cost + r.cost; }
	FlowW operator/(const FlowW& r)const { return cost / r.cost; }
};

namespace std{template<> class numeric_limits<FlowW>{public: static FlowW max() {return FlowW(inf<i64>());};};}

struct Flow : public Graph<FlowW> {
	int src, snk;

	Flow(int n) :Graph(n + 2), src(n), snk(n + 1) {}

	void add_edge(int s, int e, i64 cap, i64 cost) {
		Graph::add_edge(s, e, {sz(g[e]), cap, cost});
		Graph::add_edge(e, s,	{sz(g[s])-1, 0, -cost});
	}

	i64 mf(i64 flow = inf<i64>()) {
		i64 sum = 0;
		auto vis=Arr<bool>(n+2);
		while (i64 f = process_mf(src, flow-sum, vis)){
			sum += f;
			vis=Arr<bool>(n+2);
		}
		return sum;
	}

	i64 dinic(i64 flow = inf<i64>()){
		i64 sum = 0;
		return sum;
	}

	pair<i64, i64> mcmf(i64 flow = inf<i64>()) {
		pair<i64, i64> ret;
		while (true) {
			auto res = process_mcmf(flow-ret.se);
			ret.fi += res.fi;
			ret.se += res.se;
			if (!res.fi && !res.se)
				break;
		}
		return ret;
	}
	
	//successive shortest path || primal-dual
	pair<i64, i64> mcmf_fast(i64 flow = inf<i64>()){
		return {};
	}
	
	void gomory_hu(){
	}
private:
	i64 process_mf(int v, i64 mf, Arr<bool>& vis) {
		if (v == snk)
			return mf;

		vis[v] = true;
		for (auto& i : g[v]) {
			if (!vis[i.e] && i.w.cap) {
				i64 f = process_mf(i.e, min(mf, i.w.cap), vis);
				if (f > 0) {
					i.w.cap -= f;
					g[i.e][i.w.si].w.cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	pair<i64, i64> process_mcmf(i64 flow) {
		Arr<FlowW> d;
		Arr<Edge> p;
		if (!spfa(d, p, src) || p[snk].s == -1)
			return {};
		for (int cur = snk; p[cur].s != -1; cur = p[cur].s)
			flow = min(flow, g[p[cur].s][p[cur].ei].w.cap);
		i64 cost = 0;
		for(auto& e:cons_path(d,p,snk)){
			g[e.s][e.ei].w.cap-=flow;
			g[e.e][e.w.si].w.cap+=flow;
			cost += e.w.cost*flow;
		}

		return {cost, flow};
	}

	virtual bool valid_spfa_edge(const Edge& e) const override { return e.w.cap; }
};
