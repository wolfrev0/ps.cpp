#include "core/base.h"
#include "misc/random.h"
#include "misc/gccext.h"

void solve(){
	pbds_set<int> a,b;
	a.insert(rd(n));
	for(int i=0;i<n;i++)
		if(i!=*a.begin())
			b.insert(i);
	for(int i=0;i<n-1;i++){
		auto ai=a.find_by_order(rd(sz(a)));
		auto bi=b.find_by_order(rd(sz(b)));
		a.insert(*bi),b.erase(bi);
	}
}
signed main(){
	// for(int ti=1,t=TC;ti<=t;ti++)
	// 	print(TC_OUT_PREFIX),
		solve();
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
}