#include "core/base.h"

const int mod=1e9+7;

Arr<Arr<int>> permu_decomp(const Arr<int>& a, const Arr<int>& b){
	int n=sz(a);
	Arr<Arr<int>> ret;
	Arr<char> vis(n);
	map<int,int> ib;
	for(int i=0;i<n;i++)
		ib[b[i]]=i;
	func(void,f,int idx,Arr<int>& group){
		if(vis[idx]) return;
		vis[idx]=true;
		group.push_back(idx);
		f(ib[a[idx]],group);
	};
	for(int i=0;i<n;i++){
		if(vis[i]) continue;
		Arr<int> group;
		f(i,group);
		ret.push_back(group);
	}
	return ret;
}

void solve(){
	int n; cin>>n;
	Arr<int> a(n),b(n),d(n);
	for(auto&i:a){cin>>i;i--;}
	for(auto&i:b){cin>>i;i--;}
	Arr<int> ai(n),bi(n);
	for(int i=0;i<n;i++)
		ai[a[i]]=i,bi[b[i]]=i;
	for(auto&i:d){cin>>i;i--;}
	auto pd=permu_decomp(a,b);
	int ans=1;
	for(auto& g:pd){
		bool ok=true;
		for(auto i:g)
			ok&=d[i]==-1;
		if(ok)
			ans*=min(2,sz(g)),ans%=mod;
	}
	println(ans);
}
signed main(){
	int ti=0,t;cin>>t;
	while(++ti<=t)
	// 	cout<<"Case #"<<ti<<": ",
		solve();
}