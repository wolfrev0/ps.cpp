#include "core/base.h"
#include "misc/gen.h"

#define endl '\n' // Remove it when interactive
#define CHECK_INPUT 1
#define TC get<0>(input()) //1
#define TC_OUT_PREFIX ""//"Case #",ti,": "
signed main(){
	void solve();
	for(int ti=1,t=TC;ti<=t;ti++)
		print(TC_OUT_PREFIX),
		solve();
#if CHECK_INPUT
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
#endif
}

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
	func(void,dbgstatus,const Arr<int>& a){
		for(int i=0;i<=k;i++)
			dbgprint(a[i],' ');
		dbgprintln("");
	};
	func(void,f,int x,int p){
		for(auto [y,w]:g[x])
			if(y!=p)
				f(y,x);
		dp[x][0]=0;
		dp[x][1]=0;
		
		dbgprintln("status of ",x);
		dbgstatus(dp[x]);
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
				dbgstatus(dp[x]);
			}
		dbgprintln("=======================");
	};
	f(0,0);
	int ans=0;
	for(int i=0;i<n;i++)
		ans=max(ans,dp[i][k]);
	cout<<ans<<endl;
}
