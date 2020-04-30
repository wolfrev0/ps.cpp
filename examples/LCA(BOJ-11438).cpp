#include "LCA.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

signed main(){
	int n; cin>>n;
	Tree<int> t(n);
	rep(i,n-1){
		int u,v;cin>>u>>v; u--,v--;
		t.add_edge(u,v,0);
	}
	LCA<int> lca(t.rootize(0));
	int m; cin>>m;
	rep(i,m){
		int a,b; cin>>a>>b; a--,b--;
		cout<<lca.lca(a,b)+1<<endl;
	}

	return 0;
}