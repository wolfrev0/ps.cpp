#include "Tree.h"
#include "FastIO.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

signed main(){
	int n;
	cin>>n;
	SimpleTree t(n);
	hfor(i,0,n-1){
		int a,b;
		cin>>a>>b;
		a--,b--;
		t.add_edge(a,b);
	}
	auto rt=t.rootize(0);
	int m;
	cin>>m;
	hfor(i,0,m){
		int a,b;
		cin>>a>>b;
		a--,b--;
		cout<<rt.lca(a,b)+1<<endl;
	}
	
	return 0;
}