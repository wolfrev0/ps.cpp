#include "core/base.h"
#include "misc/random.h"
#include "misc/gccext.h"

#define CHECK_INPUT 0
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
	int tc=50;
	println(tc);
	while(tc--){
		int n=rd(3999, 4000);
		println(n,' ',rd(2,n+1));
		pbds_set<int> a,b;
		a.insert(rd(n));
		for(int i=0;i<n;i++)
			if(i!=*a.begin())
				b.insert(i);
		for(int i=0;i<n-1;i++){
			auto ai=a.find_by_order(rd(sz(a)));
			auto bi=b.find_by_order(rd(sz(b)));
			println(*ai+1,' ',*bi+1,' ',rd(1000));
			a.insert(*bi),b.erase(bi);
		}
	}
}
