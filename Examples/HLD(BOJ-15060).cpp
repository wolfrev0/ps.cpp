#include "HLD.h"
#include "UnionFind.h"
#include "SegPredefs.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?
using pii = pair<int,int>;
ostream& operator<<(ostream& s, const pii& a) { return s<<'('<<a.fi<<','<<a.se<<')'; }

struct E{int s, e, w;};
 
signed main(){
	int n,r;
	cin>>n>>r;
	Arr<Arr<pii>> g(n);
	Arr<E> e;
	map<pii, int> m;
	rep(i,r){
		int u,v,w;
		cin>>u>>v>>w;
		u--,v--;
		g[u].pushb({v,w});
		g[v].pushb({u,w});
		e.pushb({u,v,w});
		m[{min(u,v),max(u,v)}]=w;
	}
	sort(all(e), [](auto z1, auto z2){return z1.w<z2.w;});
	UF uf(n);
	Arr<E> mst;
	int mst_w=0;
	for(auto i:e)
		if(uf.find(i.s) != uf.find(i.e)){
			uf.uni(i.s, i.e);
			mst.pushb(i);
			mst_w+=i.w;
		}
	Tree<int> t(n);
	for(auto i:mst)
		t.add_edge(i.s,i.e,i.w);
	Arr<pii> tmp(n,{-1,inf<int>()});
	t.rootize(0,tmp);
	HLD<int,SegfMaxAss<int,int>> s(tmp);
	
	int q;
	cin>>q;
	rep(_,q){
		int u,v;
		cin>>u>>v;
		u--,v--;
		cout<<mst_w-s.q(u,v)+m[{min(u,v),max(u,v)}]<<endl;
	}
	
	return 0;
}