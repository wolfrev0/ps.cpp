#pragma once
#include "graph/WD.h"
#include "misc/uf.h"

struct GraphUD: public GraphWD<int>{
	GraphUD(int n=0):GraphWD(n){}

	void add_edge(int s,int e){GraphWD::add_edge(s,e,1);}

	Arr<int> topo_sort(){
		Arr<int> in(n);
		for(int i=0;i<n;i++)
			for(auto& j:adj[i])
				in[edg[j].v[1]]++;
		queue<int> q;
		for(int i=0;i<n;i++)
			if(!in[i])
				q.push(i);
		Arr<int> ret;
		while(sz(q)){
			auto x=q.front(); q.pop();
			ret.emplace_back(x);
			for(auto& i:adj[x])
				if(!--in[edg[i].v[1]])
					q.push(edg[i].v[1]);
		}
		return ret;
	}

	Arr<int> topo_sort_lex(){
		Arr<int> in(n);
		for(int i=0;i<n;i++)
			for(auto& j:adj[i])
				in[edg[j].v[1]]++;
		PQ<int,greater<int>> q;
		for(int i=0;i<n;i++)
			if(!in[i])
				q.push(i);
		Arr<int> ret;
		while(sz(q)){
			auto x=q.top();q.pop();
			ret.emplace_back(x);
			for(auto& i:adj[x])
				if(!--in[edg[i].v[1]])
					q.push(edg[i].v[1]);
		}
		return ret;
	}

	// https://www.acmicpc.net/source/59882090
	tuple<Arr<Arr<int>>, Arr<int>, GraphUD> scc_tarjan() {
		Arr<Arr<int>> scc;
		Arr<int> stat(n),ord(n);
		stack<int> stk;
		int ordi=0;
		func(int,dfs,int v){
			stat[v]=1, stk.push(v);
			int ret=ord[v]=ordi++;
			for(auto i:adj[v]){
				if(stat[edg[i].v[1]]==0)// tree edge
					ret=min(ret,dfs(edg[i].v[1]));
				else if(stat[edg[i].v[1]]==1)// bwd edge
					ret=min(ret,ord[edg[i].v[1]]);
				else if(stat[edg[i].v[1]]==2) {
					if(ord[edg[i].v[1]]<=ord[v])// cross edge which not scc grouped
						ret=min(ret, ord[edg[i].v[1]]);
					// else fwd edge
				}
				// else state==3 (scc grouped)
			}
			// nothing goes to ancestor => root of scc
			if(ret==ord[v]){
				scc.emplace_back();
				int prv=-1;
				while(sz(stk) && prv!=v)
					scc.back().emplace_back(prv=stk.top()), stat[prv]=3, stk.pop();
			}else stat[v]=2;
			return ret;
		};

		for(int i=0;i<n;i++)
			if(!stat[i])
				dfs(i);
		return scc_util(scc);
	}
	
	//https://www.acmicpc.net/source/59897682
	tuple<Arr<Arr<int>>, Arr<int>, GraphUD> scc_kosaraju(){
		Arr<int> post_ord;
		Arr<char> vis(n);
		func(void,dfs,int x){
			if(vis[x])return;
			vis[x]=true;
			for(auto i:adj[x])
				dfs(edg[i].v[1]);
			post_ord.emplace_back(x);
		};
		for(int i=0;i<n;i++)
			if(!vis[i])
				dfs(i);
		
		auto rg=reversed();
		vis=Arr<char>(n);
		Arr<Arr<int>> scc;
		func(void,get_scc,int x){
			if(vis[x]) return;
			vis[x]=true;
			for(auto i:rg.adj[x])
				get_scc(rg.edg[i].v[1]);
			scc.back().push_back(x);
		};
		for(auto i:views::reverse(post_ord))
			if(!vis[i]){
				scc.emplace_back();
				get_scc(i);
			}
		return scc_util(scc);
	}

	//based on https://github.com/ei1333/library/blob/master/graph/others/dominator-tree.hpp
	Arr<int> domtree(int src){
		auto rg=reversed();
		Arr<int> r(n),val(n),idom(n,-1),sdom(n,-1),o,p(n),u(n);
		Arr<Arr<int>> buf(n);
		iota(r.begin(),r.end(),0),iota(val.begin(),val.end(),0);
		func(int,find,int x){
			if(r[x]==x)return x;
			int ret=find(r[x]);
			if(sdom[val[x]]>sdom[val[r[x]]]) val[x]=val[r[x]];
			return r[x]=ret;
		};
		func(int,eval,int x){find(x);return val[x];};
		func(void,link,int x,int y){r[x]=y;};
		func(void,dfs,int x){
			sdom[x]=sz(o),o.emplace_back(x);
			for(auto i:adj[x])
				if(int y=edg[i].v[1];!~sdom[y])
					p[y]=x,dfs(y);
		};
		dfs(src);
		int m=sz(o);
		dbg1if(m!=n,"Not Connected");

		for(int i=m-1;~i;i--){
			for(auto j:rg.adj[o[i]]){
				if(!~sdom[rg.edg[j].v[1]])continue;
				int x=eval(rg.edg[j].v[1]);
				if(sdom[o[i]]>sdom[x])sdom[o[i]]=sdom[x];
			}
			buf[o[sdom[o[i]]]].emplace_back(o[i]);
			for(auto x:buf[p[o[i]]])u[x]=eval(x);
			buf[p[o[i]]].clear();
			link(o[i],p[o[i]]);
		}
		idom[src]=src;
		for(int i=1;i<m;i++){
			int x=o[i],y=u[x];
			idom[x]=sdom[x]==sdom[y]?sdom[x]:idom[y];
		}
		for(int i=1;i<m;i++)
			idom[o[i]]=o[idom[o[i]]];
		return idom;
	}

private:
	tuple<Arr<Arr<int>>,Arr<int>,GraphUD> scc_util(Arr<Arr<int>> scc){
		Arr<int> v2scc(n);
		for(int i=0;i<sz(scc);i++)
			for(auto j:scc[i])
				v2scc[j]=i;
		GraphUD sccg(sz(scc));
		for(int i=0;i<n;i++)
			for(auto& j:adj[i])
				if(v2scc[i]!=v2scc[edg[j].v[1]])
					sccg.add_edge(v2scc[i],v2scc[edg[j].v[1]]);
		return {scc,v2scc,sccg};
	}
};

struct SAT2{
	SAT2(int n):n(n),g(n*2){}
	void add(int a,int b,bool inva,bool invb) {
		g.add_edge(a*2+inva,b*2+!invb);
		g.add_edge(b*2+invb,a*2+!inva);
	}
	Arr<int> sat(){
		auto [sccs,v2scc,__]=g.scc_tarjan();
		bool fail=false;
		for(int i=0;i<n;i++) fail|=v2scc[i*2]==v2scc[i*2+1];
		if(fail) return {};
		Arr<int> r(n,-1);
		for(auto scc:sccs){
			bool v=false;
			for(auto j:scc)
				if(r[j/2]!=-1){
					v=j%2?!r[j/2]:r[j/2];
					break;
				}
			for(auto j:scc)
				r[j/2]=j%2?!v:v;
		}
		return r;
	}
	int n;
	GraphUD g;
};