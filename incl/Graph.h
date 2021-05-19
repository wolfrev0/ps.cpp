#pragma once
#include "Core.h"
#include "UnionFind.h"

//NOTE: if bidir -> use e.opp(x)
//			else -> can use e.opp(x) but e.v[1] is simpler
template<class T, bool bidir>
struct Graph{
	struct E{
		int v[2],vi[2],ei; T w;
		int opp(int self){return v[self==v[0]];}
		int oppi(int self){return vi[self==v[0]];}
		bool operator<(const E&r)const{return w<r.w;}
	};
	Graph(int n):n(n),adj(n){}

	void add_edge(int s, int e, T w){
		edg.emplb(E{{s,e},{sz(adj[e]),sz(adj[s])},sz(edg),w});
		if(bidir)adj[e].emplb(sz(edg)-1);
		adj[s].emplb(sz(edg)-1);
	}

	void dijkstra(Arr<T>& d, Arr<int>& p, int s){
		d=Arr<T>(n,inf<T>());
		p=Arr<int>(n,-1);
		PQMin<pair<T,int>> pq;
		pq.empl(d[s]=0,s);
		while(sz(pq)){
			auto [dist,x]=pq.top(); pq.pop();
			if(dist!=d[x])continue;
			for(auto& i:adj[x]){
				int y=edg[i].opp(x);
				int w=edg[i].w;
				if(d[y]>dist+w)
					p[y]=i, pq.empl(d[y]=dist+w,y);
			}
		}
	}

	Arr<Arr<int>> floyd(){
		Arr<Arr<int>> a(n,Arr<int>(n,inf<int>()));
		for(int i=0;i<n;i++)a[i][i]=0;
		for(auto i:edg){
			a[i.v[0]][i.v[1]]=i.w;
			if(bidir)a[i.v[1]][i.v[0]]=i.w;
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
		return a;
	}

	bool spfa(Arr<T>& ub, Arr<int>& p, int s) {
		deque<int> q;
		Arr<bool> inq(n);
		ub=Arr<T>(n,inf<T>());
		p=Arr<int>(n,-1);
		Arr<int> c(n);

		ub[s]=0;
		inq[s]=true;
		q.pushb(s);
		while(sz(q)){
			int x=q.front(); inq[x]=false, q.popf();
			for(auto i:adj[x]){
				int y=edg[i].opp(x);
				auto w=edg[i].w;
				if(isvalid(edg[i]) && ub[y]>ub[x]+w){
					p[y]=i, ub[y]=ub[x]+w;
					if(!inq[y]){
						inq[y]=true;
						if(++c[y]>n)return false;
						if(sz(q) && ub[y]<ub[q.front()])q.pushf(y);
						else q.pushb(y);
					}
				}
			}
		}
		return q.empty();
	}
	//kruskal
	Arr<E> mst(){ assert(bidir);
		auto e=edg;
		sort(e.begin(),e.end());
		UF uf(n);
		Arr<E> ret;
		ret.reserve(n-1);
		for(auto i:e) {
			if(uf.find(i.v[0])^uf.find(i.v[1])){
				uf.uni(i.v[0],i.v[1]);
				ret.emplb(move(i));
			}
		}
		return ret;
	}
	//prim
	Arr<E> mst2(){ assert(bidir);
		Arr<E> ret;
		Arr<bool> vis(n);
		PQMin<tuple<T,int,int>> pq;
		for(auto i:adj[0])
			pq.empl(edg[i].w,edg[i].opp(0),i);
		vis[0]=true;
		while(sz(pq)){
			auto [w,x,idx]=pq.top();pq.pop();
			if(vis[x]) continue;
			vis[x]=true;
			ret.pushb(edg[idx]);
			for(auto& i:adj[x])
				if(!vis[edg[i].opp(x)])
					pq.empl(edg[i].w,edg[i].opp(x),i);
		}
		return ret;
	}

	//SeeAlso) https://codeforces.com/blog/entry/90137?#comment-785463
	Arr<pint> boomerang(){ assert(bidir);
		//boj.kr/16583
		//https://codeforces.com/contest/1519/problem/E
		//https://codeforces.com/contest/858/problem/F
		// https://www.acmicpc.net/problem/13353 ?
		Arr<bool> vis(n);
		Arr<pint> ret;
		Arr<int> ok(sz(edg),true);
		func(void,dfs,int v,int pei){
			vis[v]=true;
			Arr<int> y;
			for(auto i:adj[v]){
				if(i==pei)continue;
				int opp=edg[i].opp(v);
				if(!vis[opp])
					dfs(opp,i);
				if(ok[i])
					y.emplb(i);
			}
			if(pei!=-1)y.emplb(pei);
			for(int i=0;i+1<sz(y);i+=2)
				ok[y[i]]=ok[y[i+1]]=false,ret.emplb(y[i],y[i+1]);
		};
		for(int i=0;i<n;i++)
			if(!vis[i])
				dfs(i,-1);
		return ret;
	}

	int n;
	Arr<E> edg;
	Arr<Arr<int>> adj;
protected:
	virtual bool isvalid(const E& e)const{return true;}
};