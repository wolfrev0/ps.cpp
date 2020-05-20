#include "Core.h"
#include "Graph.h"

#define endl '\n'//not interactive?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

const int N=1e5;
int tr[N*2];
void upd(int i, int v){
	for(tr[i+=N]=v;i>1;i/=2)
		tr[i/2]=min(tr[i],tr[i^1]);
}
int q(int s, int e){
	int r=inf<int>();
	for(s+=N,e+=N; 

signed main(){
	int n; cin>>n;
	int a,b,c; cin>>a>>b>>c; a--,b--,c--;
	int m; cin>>m;
	Graph<int> g(n);
	rep(i,m){
		int x,y,z; cin>>x>>y>>z; x--,y--;
		g.add_edge(x,y,z,true);
	}
	Arr<int> da, db, dc; Arr<Graph<int>::Edge> p;
	g.dijkstra(da,p,a);
	g.dijkstra(db,p,b);
	g.dijkstra(dc,p,c);
	auto o = range(n);
	sort(all(o),[&](int x, int y){return da[x]<da[y];});
	Arr<int> zb=db; sort(all(zb)); zb.erase(unique(all(zb)),zb.end());
	

	int t; cin>>t;
	rep(i,t){
		int q; cin>>q;
	}
	return 0;
}

