#include "core/base.h"
#include "misc/ordering.h"

void solve(){
	auto [n,m]=input<int,int>();
	auto a=ARR(n,0ll); input(a);
	auto b=ARR(m,2,0ll); input(b);

	int ans=0;
	multiset<int> z(a.begin(),a.end());
	sort(b.begin(),b.end(),lam(x[1]<y[1],auto& x,auto& y));
	for(const auto& i:b){
		auto it = z.lb(i[0]);
		if(it!=z.end() and *it<=i[1])
			ans++,z.erase(it);
	}
	println(ans);
}
