#pragma once
#include "graph/WD.h"

using T=i64;
struct FlowW {
	int cap; T cost;
	int inv;
	FlowW(T cost=0) : cost(cost) {}
	FlowW(int cap, T cost): cap(cap), cost(cost) {}
	bool operator<(const FlowW& r) const { return cost < r.cost; }
	bool operator>(const FlowW& r) const { return cost > r.cost; }
	bool operator==(const FlowW& r)const{return !(cost<r.cost) and !(cost>r.cost);}
	FlowW operator+(const FlowW& r) const { return cost + r.cost; }
	FlowW operator/(const FlowW& r) const { return cost / r.cost; }
};

namespace std{
	template<> class numeric_limits<FlowW> {
	public:
		static FlowW max(){return FlowW(inf<int>());}
	};
}
struct Flow:public GraphWD<FlowW>{
	int src, snk;
	Flow(int n):GraphWD(n+2),src(n),snk(n+1){}

	void add_edge(int s, int e, int cap, T cost) {
		GraphWD::add_edge(s,e,{cap,cost});
		GraphWD::add_edge(e,s,{0,-cost});
		edg[-2].w.inv=sz(edg)-1;
		edg[-1].w.inv=sz(edg)-2;
	}

	int mf(int flow = inf<int>()){
		func(int,step,int v,int ubf,Arr<char>& vis){
			if(v == snk) return ubf;
			vis[v]=true;
			for(auto i:adj[v]){
				if(!vis[edg[i].v[1]] && edg[i].w.cap){
					int f=step(edg[i].v[1],min(ubf, edg[i].w.cap),vis);
					if(f>0){
						edg[i].w.cap-=f;
						edg[edg[i].w.inv].w.cap+=f;
						return f;
					}
				}
			}
			return 0;
		};

		int sum=0;
		auto vis=Arr<char>(n+2);
		while(int f=step(src,flow-sum,vis)){
			sum+=f;
			vis=Arr<char>(n+2);
		}
		return sum;
	}

	int dinic(int flow=inf<int>()){
		func(int,step,int flow){
			queue<int> q;
			Arr<int> d(n,inf<int>());
			d[src]=0,q.empl(src);
			while(sz(q)){
				int x=q.front();
				q.pop();
				for(auto i:adj[x])
					if(edg[i].w.cap and d[edg[i].v[1]]>d[x]+1)
						d[edg[i].v[1]]=d[x]+1,q.push(edg[i].v[1]);
			}
			decltype(adj) l(n);  // level graph, DAG
			for(auto i:adj)
				for(auto j:i)
					if(edg[j].w.cap and d[edg[j].v[1]]==d[edg[j].v[0]]+1)
						l[edg[j].v[0]].emplb(j);
			Arr<int> ii(n);
			func(int,block_flow,int u,int flow){
				if(u==snk) return flow;
				for(auto& _i=ii[u]; _i<sz(l[u]); _i++) {
					auto i=l[u][_i];
					if(edg[i].w.cap) {
						int f=block_flow(edg[i].v[1], min(flow, edg[i].w.cap));
						if(f>0){
							edg[i].w.cap-=f;
							edg[edg[i].w.inv].w.cap+=f;
							return f;
						}
					}
				}
				return 0;
			};
			int r=0;
			while(int f=block_flow(src,flow-r))r+=f;
			return r;
		};
		int r=0;
		while(int f=step(flow-r))r+=f;
		return r;
	}

	pair<T,int> mcmf(int flow=inf<int>()){
		func(ARG(pair<T,int>),step,int flow){
			Arr<FlowW> d;
			Arr<Arr<int>> p;
			if(!spfa(d,p,src) || p[snk].empty())
				return {};
			int x=snk;
			for(;x!=src;x=edg[p[x].front()].opp(x))
				flow=min(flow,edg[p[x].front()].w.cap);
			T cost=0;
			x=snk;
			for(;x!=src;x=edg[p[x].front()].opp(x)){
				edg[p[x].front()].w.cap-=flow;
				edg[edg[p[x].front()].w.inv].w.cap+=flow;
				cost+=edg[p[x].front()].w.cost*flow;
			}
			return {cost,flow};
		};
		pair<T,int> ret;
		while(true){
			auto res=step(flow-ret.se);
			ret.fi+=res.fi,ret.se+=res.se;
			if(!res.fi&&!res.se)break;
		}
		return ret;
	}

	// successive shortest path || primal-dual
	pair<int, int> mcmf_fast(int flow = inf<int>()){return {};}
	void gomory_hu(){}

	//not tested
	tuple<Arr<E>, Arr<int>, Arr<int>> cuts(){
		Arr<E> r;
		
		Arr<char> vis1(n+2);
		func(void,dfs1,int v){
			if(vis1[v]) return;
			vis1[v]=true;
			for(auto i:adj[v])
				if(edg[i].w.cap)
					dfs1(edg[i].v[1]);
		};
		dfs1(src);
		
		Arr<char> vis2(n+2);
		func(void,dfs2,int v){
			if(vis2[v])return;
			vis2[v]=true;
			for(auto i:adj[v]){
				if(!edg[i].w.cap and !vis1[edg[i].v[1]])r.pushb(edg[i]);
				else dfs2(edg[i].v[1]);
			}
		};
		dfs2(src);

		sort(r.begin(),r.end(),lam(mkp(x.v[0],x.v[1])<mkp(y.v[0],y.v[1]),auto x,auto y));
		r.erase(unique(r.begin(),r.end(),lam(mkp(x.v[0],x.v[1])==mkp(y.v[0],y.v[1]),auto x,auto y)),r.end());

		Arr<int> srcv, snkv;
		for(int i=0;i<n-2;i++)
			(vis1[i]?srcv:snkv).pushb(i);
		return {r,srcv,snkv};
	}
	
	virtual bool isvalid(const E& e)const override{return e.w.cap;}
};
