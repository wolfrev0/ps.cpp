#include "core/base.h"
signed main(){
	void solve();
	// for(int ti=1,t=get<0>(input());ti<=t;ti++)
		// print("Case #",ti,": "),
		solve();
	// assert(cin.get()==' ');
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
}
#include "math/struct/mod.h"
#include "tree/seg/segdyn.h"
using M=Mod<998244353>;
void solve(){
	auto [n]=input();
	Arr<Arr<int>> ch(n);
	int r=-1;
	for(int i=0;i<n;i++){
		int x; cin>>x; x--;
		if(x>=0)
			ch[x].push_back(i);
		else
			r=i;
	}
	auto a=input(ARR(n,0ll));
	func(ARG(SegDyn<MAdd<M>,0,1'000'009>),f,int x,int d){
		SegDyn<MAdd<M>,0,1'000'009> st;
		for(auto y:ch[x]){
			auto tmp=f(y,d+1);
			st.join(&tmp);
		}
		if(sz(ch[x])==0)
			st.upd(d,1);
		else
			st.upd(d,st.q(d+1,d+a[x]+1));
		return st;
	};
	println(f(r,0).q(0,1));
}
