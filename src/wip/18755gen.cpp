#include "core/base.h"
#include "misc/gen.h"

#define endl '\n' // Remove it when interactive
#define CHECK_INPUT 1
#define TC 1
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
	println(1);
	int n=5,k=3,max_len=10;
	println(n,' ',k);
	for(auto [u,v]:gen::tree(n))
		println(u+1,' ',v+1,' ',rd(max_len));
}
