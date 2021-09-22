#pragma once
#include "core/base.h"
#include "misc/uf.h"

//NOTE: if bidir -> use e.opp(x)
//			else -> can use e.opp(x) but e.v[1] is simpler
template<class T>
struct GraphWD{
	struct E{
		int v[2],vi[2],ei; T w;
		int opp(int self){return v[self==v[0]];}
		int oppi(int self){return vi[self==v[0]];}
		bool operator<(const E&r)const{return w<r.w;}
	};
	GraphWD(int n):n(n),adj(n){}

	void add_edge(int s,int e,T w){
		edg.pushb(E{{s,e},{sz(adj[e]),sz(adj[s])},sz(edg),w});
		adj[s].pushb(sz(edg)-1);
	}

	void dijkstra_trackall(Arr<T>& d,Arr<Arr<int>>& p,int s){
		d=Arr<T>(n,inf<T>());
		p=Arr<Arr<int>>(n);
		PQMin<pair<T,int>> pq;
		pq.push({d[s]=T(),s});
		while(sz(pq)){
			auto [dist,x]=pq.top(); pq.pop();
			if(dist!=d[x])continue;
			for(auto& i:adj[x]){
				int y=edg[i].opp(x);
				T w=edg[i].w;
				if(d[y]>dist+w)
					p[y]={i}, pq.push({d[y]=dist+w,y});
				else if(d[y]==dist+w)
					p[y].pushb(i);
			}
		}
	}
	void dijkstra_trackone(Arr<T>& d,Arr<int>& p,int s){
		d=Arr<T>(n,inf<T>());
		p=Arr<int>(n,-1);
		PQMin<pair<T,int>> pq;
		pq.push({d[s]=T(),s});
		while(sz(pq)){
			auto [dist,x]=pq.top(); pq.pop();
			if(dist!=d[x])continue;
			for(auto& i:adj[x]){
				int y=edg[i].opp(x);
				T w=edg[i].w;
				if(d[y]>dist+w)
					p[y]=i, pq.push({d[y]=dist+w,y});
			}
		}
	}

	Arr<Arr<int>> floyd(){
		Arr<Arr<int>> a(n,Arr<int>(n,inf<int>()));
		for(int i=0;i<n;a[i][i]=0,i++)
			for(auto j:adj[i])
				a[edg[j].v[0]][edg[j].v[1]]=edg[j].w;
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
		return a;
	}

	bool spfa_trackall(Arr<T>& ub,Arr<Arr<int>>& p,int s){
		deque<int> q;
		Arr<char> inq(n);
		ub=Arr<T>(n,inf<T>());
		p=Arr<Arr<int>>(n);
		Arr<int> c(n);

		ub[s]=0;
		inq[s]=true;
		q.pushb(s);
		while(sz(q)){
			int x=q.front(); inq[x]=false, q.popf();
			for(auto i:adj[x]){
				int y=edg[i].opp(x);
				auto w=edg[i].w;
				if(isvalid(edg[i])){
					if(ub[y]>ub[x]+w){
						p[y]={i}, ub[y]=ub[x]+w;
						if(!inq[y]){
							inq[y]=true;
							if(++c[y]>n)return false;
							if(sz(q) && ub[y]<ub[q.front()])q.pushf(y);
							else q.pushb(y);
						}
					}else if(ub[y]==ub[x]+w)
						p[y].pushb(i);
				}
			}
		}
		return q.empty();
	}
	bool spfa_trackone(Arr<T>& ub,Arr<int>& p,int s){
		deque<int> q;
		Arr<char> inq(n);
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
				if(isvalid(edg[i])){
					if(ub[y]>ub[x]+w){
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
		}
		return q.empty();
	}

	int n;
	Arr<E> edg;
	Arr<Arr<int>> adj;
protected:
	virtual bool isvalid(const E& e)const{return true;}
};