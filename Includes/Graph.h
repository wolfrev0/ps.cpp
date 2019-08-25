#pragma once
#include "Core.h"
#include "DisjointSet.h"

template<typename T>
struct Graph {
	struct Edge {
		int s;
		int e;
		int ei;
		T w;
		Edge():s(0),e(0),ei(0),w(T()){};
		Edge(int s, int e, int ei, T w):s(s),e(e),ei(ei),w(w){};
		bool operator<(const Edge &r)const { return w < r.w; }
		bool operator>(const Edge &r)const { return w > r.w; }
	};
	int n;
	Arr<Arr<Edge>> g;

	Graph(int n=0) :n(n), g(n) {}
	Graph(const Graph& r) :n(r.n), g(r.g) {}

	void add_edge(int s, int e, T w, bool dir=true){
		g[s].pushb({s, e, sz(g[s]), w});
		if(!dir)
			g[e].pushb({e, s, sz(g[e]), w});
	}

	struct DNV{T dist; int v; bool operator<(const DNV& r)const{return dist>r.dist;}};
	void dijkstra(Arr<T>& d, Arr<Edge>& p, int s) {
		priority_queue<DNV> pq;
		d = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n, {-1,-1,-1,-1});
		pq.push({ d[s]=0, s });
		while (size(pq)){
			auto c = pq.top();
			pq.pop();

			if (c.dist != d[c.v])
				continue;

			auto& cg = g[c.v];
			for (auto &i : cg) {
				if (d[i.e] > c.dist + i.w) {
					p[i.e] = i;
					pq.push({ d[i.e]=c.dist + i.w, i.e });
				}
			}
		}
	}

	void dijkstra_vsq(Arr<T>& d, Arr<Edge>& p, int s) {

	}

	int floyd(int s, int e, int m, Arr<Arr<Arr<int>>>& memo){
		if(m==n){
			for(auto& i:g[s])
				if(i.e==e)
					return i.w;
			return inf<T>();
		}
		auto& ret=memo[s][e][m];
		if(ret!=-1)
			return ret;
		return ret = min(floyd(s, e, m+1, memo), floyd(s, m, m+1, memo)+floyd(m, e, m+1, memo));
	}

	bool spfa(Arr<T>& ub, Arr<Edge>& p, int s) {
		queue<int> q;
		Arr<bool> inq(n);
		ub = Arr<T>(n, inf<T>());
		p = Arr<Edge>(n,{-1,-1,-1,-1});

		ub[s] = 0;
		inq[s] = true;
		q.push(s);
		for(int i=0; i<n&&sz(q); i++) {
			int qsz = sz(q);
			while (qsz--) {
				int j = q.front();
				inq[j] = false;
				q.pop();
				for (auto k : g[j]) {
					if (valid_spfa_edge(k) && ub[j] + k.w < ub[k.e]) {
						p[k.e] = k;
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

	Arr<Edge> mst_prim() {

		Arr<Edge> ret;
		Arr<bool> vis(n);
		priority_queue<Edge, Arr<Edge>, greater<Edge>> q;
		for(auto i:g[0])
			q.push(i);
		vis[0]=true;
		while (sz(q)) {
			auto c = q.top();
			q.pop();

			if (vis[c.e])
				continue;
			vis[c.e] = true;

			ret.pushb(c);
			for (auto &i : g[c.e]) {
				if (!vis[i.e]) {
					q.push(i);
				}
			}
		}
		return ret;
	}

	Arr<Edge> mst_kruskal() {
		Arr<Edge> e;
		for (auto &i : g)
			for (auto &j : i)
				e.pushb(j);
		sort(all(e));

		DisjointSet djs(n);
		Arr<Edge> ret;
		for (auto &i : e) {
			if (djs.find(i.s) != djs.find(i.e)) {
				djs.uni(i.s, i.e);
				ret.pushb(i);
			}
		}
		return ret;
	}

protected:
	virtual bool valid_spfa_edge(const Edge& w) const { return true; }
};