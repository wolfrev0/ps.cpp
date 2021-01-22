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

	int dinic(int flow = inf<int>()){
		int r=0;
		while(int f=_dinic(flow-r))
			r+=f;
		return r;
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

	tuple<Arr<Edge>,Arr<int>,Arr<int>> cuts(){
		Arr<Edge> r;
		auto vis=Arr<bool>(n+2), pvis=Arr<bool>(n+2);
		_cuts_pre(src,pvis), _cuts(src,vis,pvis,r);
		sort(r.begin(),r.end(),[&](auto x, auto y){return make_pair(x.s,x.e)<make_pair(y.s,y.e);});
		r.erase(unique(r.begin(),r.end(),[&](auto x, auto y){return make_pair(x.s,x.e)==make_pair(y.s,y.e);}),r.end());

		Arr<int> srcv, snkv;
		for(int i=0;i<n-2;i++)
			(pvis[i]?srcv:snkv).pushb(i);

		return {r,srcv,snkv};
	}
	void _cuts_pre(int v, Arr<bool>& vis){
		if(vis[v])return;
		vis[v]=true;
		for(auto i:g[v])
			if(i.w.cap)
				_cuts_pre(i.e,vis);
	}
	void _cuts(int v, Arr<bool>& vis, Arr<bool>& pvis, Arr<Edge>& r){
		if(vis[v]) return;
		vis[v]=true;

		for(auto i:g[v]){
			if(!i.w.cap and !pvis[i.e]) r.pushb(i);
			else _cuts(i.e,vis,pvis,r);
		}
	}

	Arr<bool> ff(){
		Arr<bool> vis(n);
		_ff(src,vis);
		return vis;
	}
	void _ff(int v, Arr<bool>& vis){
		if(vis[v]) return;
		vis[v]=true;
		for(auto i:g[v])
			if(i.w.cap)
				_ff(i.e,vis);
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

	int _dinic(int flow){
		queue<int> q;
		Arr<int> d(n,inf<int>());
		d[src]=0, q.empl(src);
		while(sz(q)){
			int x=q.front(); q.pop();
			for(auto i:g[x])
				if(i.w.cap and d[i.e]>d[i.s]+1)
					d[i.e]=d[i.s]+1, q.push(i.e);
		}
		decltype(g) l(n);//level graph, DAG
		for(auto i:g)
			for(auto j:i)
				if(j.w.cap and d[j.e]==d[j.s]+1)
					l[j.s].emplb(j);
		Arr<int> ii(n);
		Func<int(int,int)> block_flow=[&](int u, int flow)->int{
			if(u==snk) return flow;
			for(auto& _i=ii[u];_i<sz(l[u]);_i++){
				auto i=l[u][_i];
				if(g[i.s][i.ei].w.cap){
					int f=block_flow(i.e,min(flow,g[i.s][i.ei].w.cap));
					if(f>0){
						g[i.s][i.ei].w.cap-=f;
						g[i.e][i.w.si].w.cap+=f;
						return f;
					}
				}
			}
			return 0;
		};
		int r=0;
		while(int f=block_flow(src,flow-r))
			r+=f;
		return r;
	}

	pair<i64, i64> process_mcmf(i64 flow) {
		Arr<FlowW> d;
		Arr<Edge> p;
		if (!spfa(d, p, src) || p[snk].s == -1)
			return {};
		for(auto& e:cons_path(d,p,snk))
			flow=min(flow, g[e.s][e.ei].w.cap);
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
