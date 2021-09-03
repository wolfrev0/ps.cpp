#include "core/base.h"

//Don't use it at interactive
#include "core/fastio.h"
#define endl '\n'

#include "misc/random.h"
#include "misc/gccext.h"

void solve(){
	int n=6;
	Xet<int> a,b;
	a.insert(rd(n));
	cout<<n<<endl;
	for(int i=0;i<n;i++)
		if(i!=*a.begin())
			b.insert(i);
	for(int i=0;i<n-1;i++){
		auto ai=a.find_by_order(rd(sz(a)));
		auto bi=b.find_by_order(rd(sz(b)));
		cout<<*ai+1<<' '<<*bi+1<<endl;
		a.insert(*bi),b.erase(bi);
	}
}
signed main(){
	// int ti=0,t=cin.tok();
	// while(++ti<=t)
	// 	cout<<"Case #"<<ti<<": ",
		solve();
}