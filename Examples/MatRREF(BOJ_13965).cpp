#include "Core.h"
#include "Matrix.h"
#include "Mod.h"
#include "Graph.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?
using pii = pair<int,int>;
ostream& operator<<(ostream& s, const pii& a) { return s<<'('<<a.fi<<','<<a.se<<')'; }

signed main(){
	int n,a,r,t;
	cin>>n>>a>>r>>t;
	
	Arr<pii> b[t];
	int c[t];
	Arr<pii> za;
	rep(i,t){
		int p,z;
		cin>>c[i]>>p;
		cin>>z; z--;
		hfor(j,1,p){
			int x;
			cin>>x;x--;
			b[i].pushb({min(z,x), max(z,x)});
			za.pushb({min(z,x), max(z,x)});
			z=x;
		}
	}
	sort(all(za));
	za.erase(unique(all(za)), za.end());
	auto zip = [&](pii x){
		return lower_bound(all(za),pii{min(x.fi,x.se),max(x.fi,x.se)})-za.begin();
	};
	Mat<Mod<13>> mat(t, sz(za)+1);
	rep(i,t){
		mat.a[i][sz(za)]=c[i];
		for(auto j:b[i])
			mat.a[i][zip(j)]++;
	}
	mat.RREF(sz(za));
	
	Graph<int> g(n);
	rep(i,t){
		rep(j,sz(za))
			if(mat.a[i][j])
				g.add_edge(za[j].fi, za[j].se, mat.a[i][sz(za)].val(), false);
	}
	Arr<int> dd; Arr<Graph<int>::Edge> pp;
	g.dijkstra(dd,pp,a-1);
	cout<<dd[r-1]<<endl;
	
	return 0;
}