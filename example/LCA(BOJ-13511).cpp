#include "Core.h"
#include "LCA.h"

#define endl '\n'//not interactive?
#define int i64//MLE?
using pint = pair<int,int>;
using tint = tuple<int,int,int>;

signed main(){
	int n; cin>>n;
	Tree<int> t(n);
	rep(i,n-1){
		int u,v,w;cin>>u>>v>>w; u--,v--;
		t.add_edge(u,v,w);
	}
	LCA<int> lca(t.rootize(0));
	int m; cin>>m;
	rep(i,m){
		int t; cin>>t;
		if(t==1){
			int u,v; cin>>u>>v; u--,v--;
			cout<<lca.cost[u]+lca.cost[v]-2*lca.cost[lca.lca(u,v)]<<endl;
		}else{
			int u,v,k; cin>>u>>v>>k; u--,v--,k--;
			int z=lca.lca(u,v);
			if(k<=lca.dpt[u]-lca.dpt[z])
				cout<<lca.anc(u,k)+1<<endl;
			else
				cout<<lca.anc(v,lca.dpt[v]+lca.dpt[u]-2*lca.dpt[z]-k)+1<<endl;
		}
	}

	return 0;
}
