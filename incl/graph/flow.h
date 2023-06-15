#pragma once
#include "graph/WD.h"

// TODO: dinic과 push relabel등의 bfs는
// snk에서부터 역방향으로 진행해주는 간단한 휴리스틱의 성능향상이 크다
template<class T>
struct FlowW{
	int cap; T cost;
	int inv;
	FlowW(T cost=0):cost(cost){}
	FlowW(int cap,T cost):cap(cap),cost(cost){}
	bool operator<(const FlowW& r)const{return cost<r.cost;}
	bool operator>(const FlowW& r)const{return cost>r.cost;}
	bool operator==(const FlowW& r)const{return !(cost<r.cost) and !(cost>r.cost);}
	FlowW operator+(const FlowW& r)const{return cost+r.cost;}
	FlowW operator/(const FlowW& r)const{return cost/r.cost;}
	FlowW inf()const{return ::inf<int>();}
};

//이분그래프 최대독립집합 재구성:종만북참고
template<class T=i64>
struct Flow:public GraphWD<FlowW<T>>{
	using W=FlowW<T>;
	using P=GraphWD<W>;
	using E=P::E;using P::edg;using P::adj;using P::n;
	Flow(int n):P(n){}

	void add_edge(int s,int e,int cap,T cost){
		P::add_edge(s,e,{cap,cost});
		P::add_edge(e,s,{0,-cost});
		edg[-2].w.inv=sz(edg)-1;
		edg[-1].w.inv=sz(edg)-2;
	}

	int mf(int src,int snk,int flow=inf<int>()){
		func(int,step,int v,int ubf,Arr<char>& vis){
			if(v==snk) return ubf;
			vis[v]=true;
			for(auto i:adj[v]){
				if(!vis[edg[i].v[1]] && edg[i].w.cap){
					int f=step(edg[i].v[1],min(ubf,edg[i].w.cap),vis);
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
		auto vis=Arr<char>(n);
		while(int f=step(src,flow-sum,vis))
			sum+=f,vis=Arr<char>(n);
		return sum;
	}

	int dinic(int src,int snk,int flow=inf<int>()){
		func(int,step,int flow){
			queue<int> q;
			Arr<int> d(n,inf<int>());
			d[src]=0,q.push(src);
			while(sz(q)){
				int x=q.front();
				q.pop();
				for(auto i:adj[x])
					if(edg[i].w.cap and d[edg[i].v[1]]>d[x]+1)
						d[edg[i].v[1]]=d[x]+1,q.push(edg[i].v[1]);
			}
			decltype(adj) l(n);//level graph,DAG
			for(auto i:adj)
				for(auto j:i)
					if(edg[j].w.cap and d[edg[j].v[1]]==d[edg[j].v[0]]+1)
						l[edg[j].v[0]].emplace_back(j);
			Arr<int> ii(n);
			func(int,block_flow,int u,int flow){
				if(u==snk) return flow;
				for(auto& _i=ii[u]; _i<sz(l[u]); _i++){
					auto i=l[u][_i];
					if(edg[i].w.cap){
						int f=block_flow(edg[i].v[1],min(flow,edg[i].w.cap));
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

	pair<T,int> mcmf(int src,int snk,int flow=inf<int>()){
		func(ARG(pair<T,int>),step,int flow){
			auto [d,p]=this->spfa_track({src});
			if(d[snk]==inf<T>() || p[snk]==-1)
				return{};
			int x=snk;
			for(;x!=src;x=edg[p[x]].opp(x))
				flow=min(flow,edg[p[x]].w.cap);
			T cost=0;
			x=snk;
			for(;x!=src;x=edg[p[x]].opp(x)){
				edg[p[x]].w.cap-=flow;
				edg[edg[p[x]].w.inv].w.cap+=flow;
				cost+=edg[p[x]].w.cost*flow;
			}
			return{cost,flow};
		};
		pair<T,int> ret;
		while(true){
			auto res=step(flow-ret.se);
			ret.fi+=res.fi,ret.se+=res.se;
			if(!res.fi&&!res.se)break;
		}
		return ret;
	}

	void gomory_hu(){}

	//not tested
	tuple<Arr<E>,Arr<int>,Arr<int>> cuts(int src,int snk){
		Arr<E> r;
		Arr<char> vis1(n);
		func(void,dfs1,int v){
			if(vis1[v]) return;
			vis1[v]=true;
			for(auto i:adj[v])
				if(edg[i].w.cap)
					dfs1(edg[i].v[1]);
		};
		dfs1(src);
		
		Arr<char> vis2(n);
		func(void,dfs2,int v){
			if(vis2[v])return;
			vis2[v]=true;
			for(auto i:adj[v]){
				if(!edg[i].w.cap and !vis1[edg[i].v[1]])r.emplace_back(edg[i]);
				else dfs2(edg[i].v[1]);
			}
		};
		dfs2(src);

		sort(r.begin(),r.end(),lam(mkp(x.v[0],x.v[1])<mkp(y.v[0],y.v[1]),auto x,auto y));
		r.erase(unique(r.begin(),r.end(),lam(mkp(x.v[0],x.v[1])==mkp(y.v[0],y.v[1]),auto x,auto y)),r.end());

		Arr<int> srcv,snkv;
		for(int i=0;i<n-2;i++)
			(vis1[i]?srcv:snkv).emplace_back(i);
		return{r,srcv,snkv};
	}
	
	virtual bool isvalid(const E& e)const override{return e.w.cap;}

	void trace(){
		for(auto i:edg){
			//not residual edge
			if(i.w.inv%2 and edg[i.w.inv].w.cap)// and i.v[1]==snk)
				dbgprintln(i.v[0],i.v[1],edg[i.w.inv].w.cap);
		}
	}
};

template<class T>
struct FlowLB:public Flow<T>{
	using P=Flow<T>;
	using E=P::E;using P::edg;using P::adj; using P::n;
	int SRC,SNK,demands=0;
	FlowLB(int n):P(n+2),SRC(n),SNK(n+1){}

	//NOTE:cost처리 잘 된건지 모름. 검증필요(Library Checker에 있을듯?)
	void add_edge(int s,int e,pint cap,int cost){
		auto [lo,hi]=cap;
		demands+=lo;
		if(lo){
			P::add_edge(SRC,e,lo,cost);
			P::add_edge(s,SNK,lo,cost);
			P::add_edge(s,e,hi-lo,cost);
		}else
			P::add_edge(s,e,hi,cost);
	}

	int dinic(int src,int snk,int flow=inf<int>()){
		P::add_edge(snk,src,inf<int>(),0);
		if(P::dinic(SRC,SNK,flow)!=demands)
			return -1;
		int r=edg[-1].w.cap;
		adj[edg[-1].v[0]].popb(),edg.popb();
		adj[edg[-1].v[0]].popb(),edg.popb();
		r+=P::dinic(src,snk,flow);
		return r;
	}
};
