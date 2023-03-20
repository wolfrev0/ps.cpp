#include "core/base.h"

//https://atcoder.jp/contests/abc241/tasks/abc241_e
//sparse table 풀이도 괜찮은듯.
void solve(){
	int n,k; cin>>n>>k;
	Arr<int> a(n);
	for(auto&i:a)cin>>i;
	Arr<int> vis(n,-1);
	int cur=0,idx=0;
	while(vis[cur]==-1){
		vis[cur]=idx++;
		cur=(cur+a[cur])%n;
	}
	// int cross=vis[cur];
	//[0,cross) 번호들: 사이클 외부
	//[cross~cross+(idx-cross)-1]: 사이클
	//idx-cross=사이클 크기
	int cycn=idx-vis[cur];
	int cycsum=0;
	for(int _=0;_<cycn;_++){
		cycsum+=a[cur];
		cur=(cur+a[cur])%n;
	}
	int i=0;
	int outn=vis[cur];//0포함,cur제외
	int outsum=0;
	while(i!=cur){
		outsum+=a[i];
		i=(i+a[i])%n;
	}
	int ans=0;
	if(k<=outn){
		i=0;
		for(int _=0;_<k;_++){
			ans+=a[i];
			i=(i+a[i])%n;
		}
	}else{
		ans+=outsum;
		k-=outn;
		ans+=k/cycn*cycsum;
		k%=cycn;
		
		i=cur;
		for(int _=0;_<k;_++){
			ans+=a[i];
			i=(i+a[i])%n;
		}
	}
	println(ans);
}
signed main(){
	for(int ti=1,t=TC;ti<=t;ti++)
		print(TC_OUT_PREFIX),
		solve();
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
}