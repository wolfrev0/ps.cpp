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
	//dp[x][k]=정점x서브트리에서 k개를 선택할때 비용
	auto dp=ARR(n,k+1,-inf<int>());
	func(void,f,int x,int p){
		for(auto [y,w]:g[x])
			if(y!=p)
				f(y,x);
		dp[x][0]=0;
		dp[x][1]=0;
		for(auto [y,w]:g[x])
			if(y!=p){
				auto z=ARR(k+1,-inf<int>());
				z[0]=0;
				for(int i=0;i<=k;i++)
					for(int j=0;j<=k;j++)
						if(i+j<=k)
							z[i+j]=max(z[i+j],dp[x][i]+dp[y][j]+2*w*min(j,k-j));
				for(int i=0;i<=k;i++)
					dp[x][i]=max(dp[x][i],z[i]);
			}
	};
	f(0,0);
	int ans=0;
	for(int i=0;i<n;i++)
		ans=max(ans,dp[i][k]);
	cout<<ans<<endl;
}