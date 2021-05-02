#pragma once
#include "Core.h"
#include "UnionFind.h"

template<class T> struct Graph {
	struct Edge {
		int s;
		int e;
		int ei;
		T w;
		Edge() : s(0), e(0), ei(0), w(T()){};
		Edge(int s, int e, int ei, T w) : s(s), e(e), ei(ei), w(w){};
		bool operator<(const Edge& r) const { return w < r.w; }
		bool operator>(const Edge& r) const { return w > r.w; }
	};
	int n;
	Arr<Arr<Edge>> g;

	Graph(int n = 0) : n(n), g(n) {}
	Graph(const Graph& r) : n(r.n), g(r.g) {}

	void add_edge(int s, int e, T w, bool bidir = false) {
		g[s].pushb({s, e, sz(g[s]), w});
		if(bidir) g[e].pushb({e, s, sz(g[e]), w});
	}

	struct DNV {
		T dist;
		int v;
		bool operator<(const DNV& r) const { return dist > r.dist; }
	};
	void dijkstra(Arr<T>& d, Arr<Edge>& p, int s) {
		PQ<DNV> pq;
		d = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n, {-1, -1, -1, -1});
		pq.push({d[s] = 0, s});
		while(size(pq)) {
			auto c = pq.top();
			pq.pop();

			if(c.dist != d[c.v]) continue;

			auto& cg = g[c.v];
			for(auto& i : cg) {
				if(d[i.e] > c.dist + i.w) {
					p[i.e] = i;
					pq.push({d[i.e] = c.dist + i.w, i.e});
				}
			}
		}
	}

	Arr<Arr<int>> floyd() {
		Arr<Arr<int>> a(n, Arr<int>(n, inf<int>()));
		for(int i = 0; i < n; i++) {
			for(auto j : g[i]) a[i][j.e] = 1;
			a[i][i] = 0;
		}
		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++) a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		return a;
	}

	bool spfa(Arr<T>& ub, Arr<Edge>& p, int s) {
		deque<int> q;
		Arr<bool> inq(n);
		ub = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n, {-1, -1, -1, -1});
		int c[n]{};

		ub[s] = 0;
		inq[s] = true;
		q.pushb(s);
		while(sz(q)) {
			int j = q.front();
			inq[j] = false;
			q.popf();
			for(auto k : g[j]) {
				if(valid_spfa_edge(k) && ub[j] + k.w < ub[k.e]) {
					p[k.e] = k;
					ub[k.e] = ub[j] + k.w;
					if(!inq[k.e]) {
						inq[k.e] = true;
						if(++c[k.e] > n) return false;
						if(sz(q) && ub[k.e] < ub[q.front()]) q.pushf(k.e);
						else
							q.pushb(k.e);
					}
				}
			}
		}

		return q.empty();
	}

	Arr<Edge> cons_path(const Arr<T>& d, const Arr<Edge>& p, int dest) {
		Arr<Edge> ret;
		while(p[dest].s != -1) {
			ret.pushb(g[p[dest].s][p[dest].ei]);
			dest = p[dest].s;
		}
		return ret;
	}

	Arr<Edge> mst_prim() {
		Arr<Edge> ret;
		Arr<bool> vis(n);
		PQMin<Edge> q;
		for(auto i : g[0]) q.push(i);
		vis[0] = true;
		while(sz(q)) {
			auto c = q.top();
			q.pop();

			if(vis[c.e]) continue;
			vis[c.e] = true;

			ret.pushb(c);
			for(auto& i : g[c.e]) {
				if(!vis[i.e]) { q.push(i); }
			}
		}
		return ret;
	}

	Arr<Edge> mst_kruskal() {
		Arr<Edge> e;
		for(auto& i : g)
			for(auto& j : i) e.pushb(j);
		sort(e.begin(), e.end());

		UF uf(n);
		Arr<Edge> ret;
		for(auto& i : e) {
			if(uf.find(i.s) != uf.find(i.e)) {
				uf.uni(i.s, i.e);
				ret.pushb(i);
			}
		}
		return ret;
	}
protected:
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }
};

template<class T>
struct EdgeList{
	struct E{
		int v[2],vi[2]; T x;
		int opp(int self){return v[self==v[0]];}
		int oppi(int self){return vi[self==v[0]];}
	};

	EdgeList(int n):n(n),m(0),adj(n){}

	void add(int s, int e, T x, bool dir=false){
		edg.emplb(E{{s,e},{sz(adj[e]),sz(adj[s])},x});
		if(!dir)adj[e].emplb(m);
		adj[s].emplb(m);
		m++;
	}

	//SeeAlso) https://codeforces.com/blog/entry/90137?#comment-785463
	Arr<pint> boomerang(){
		//boj.kr/16583
		//https://codeforces.com/contest/1519/problem/E
		//https://codeforces.com/contest/858/problem/F
		// https://www.acmicpc.net/problem/13353 ?
		Arr<bool> vis(n);
		Arr<pint> ret;
		Arr<int> ok(m,true);
		func(dfs, void, int v, int pei){
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

	int n,m;
	Arr<E> edg;
	Arr<Arr<int>> adj;
};