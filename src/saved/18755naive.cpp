#include "core/base.h"
#include "misc/gen.h"

void solve(){
	auto[n,k]=input<int,2>();
	Arr<Arr<pint>> g(n);
	for(int i=0;i<n-1;i++){
		auto[u,v,w]=input<int,3>();
		u--,v--;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	auto dist=ARR(n,n,0ll);
	for(int i=0;i<n;i++){
		func(void,dfs,int x,int p,int d){
			dist[i][x]=d;
			for(auto [y,w]:g[x])
				if(y!=p)
					dfs(y,x,d+w);
		};
		dfs(i,i,0);
	}
	int ans=0;
	for(auto&a:gen::enum_npr(n,k)){
		int cur=0;
		for(int i=0;i<k;i++)
			cur+=dist[a[i-1]][a[i]];
		ans=max(ans,cur);
	}
	println(ans);
}
signed main(){
	for(int ti=1,t=get<0>(input());ti<=t;ti++)
	// 	print("Case #",ti,": "),
		solve();
}