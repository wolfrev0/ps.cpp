#pragma once
#include "Graph.h"
#include "Vec2.h"

struct FlowWeight {
  int si;
  i64 cap, cost;
  FlowWeight(i64 cost) :cost(cost) {}
  FlowWeight(int si, i64 cap, i64 cost) :si(si), cap(cap), cost(cost) {}
  bool operator< (const FlowWeight& r)const { return cost < r.cost; }
  FlowWeight operator+(const FlowWeight& r)const { return cost + r.cost; }
};

template<>
FlowWeight inf(){return inf<i64>();}

struct FlowGraph : public Graph<FlowWeight> {
  int src, snk;

  FlowGraph(int n) :Graph(n + 2), src(n), snk(n + 1) {}

  void add_edge(int s, int e, i64 cap, i64 cost) {
    Graph::add_edge(s, e, FlowWeight(g[e].size(), cap, cost));
    Graph::add_edge(e, s, FlowWeight(g[s].size() - 1, 0, -cost));
  }

  i64 mf(i64 flow = inf<i64>()) {
    i64 sum = 0;
    auto vis=vector<bool>(n+2);
    while (i64 f = process_mf(src, flow-sum, vis)){
      sum += f;
      vis=vector<bool>(n+2);
    }
    return sum;
  }

  i64 dinic(i64 flow = inf<i64>()){
    i64 sum = 0;
    return sum;
  }

  Vec2<i64> mcmf(i64 flow = inf<i64>()) {
    Vec2<i64> ret;
    while (true) {
      auto res = process_mcmf(flow-ret.y);
      ret += res;
      if (!res.x && !res.y)
        break;
    }
    return ret;
  }
private:
  i64 process_mf(int v, i64 mf, vector<bool>& vis) {
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

  Vec2<i64> process_mcmf(i64 flow) {
    vector<FlowWeight> ub;
    vector<pair<int, int>> p;
    if (!spfa(ub, p, src) || p[snk].first == inf<int>())
      return {};
    for (int cur = snk; p[cur].first != inf<int>(); cur = p[cur].first)
      flow = min(flow, g[p[cur].first][p[cur].second].w.cap);
    i64 cost = 0;
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