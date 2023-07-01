#include "core/base.h"
signed main(){
	void solve();
	for(int ti=1,t=input1();ti<=t;ti++)
		// print("Case #",ti,": "),
		solve();
	// assert(cin.get()==' ');
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
}
int n;
Arr<pint> a;
map<pair<int,Arr<pint>>,int> dp;
int f(int turn){
	bool free=true, lose=false;
	for(auto i:a){
		free &= i.fi<0 or i.se<0;
		lose |= !i.fi and !i.se;
	}
	if(lose)
		return 1;
	if(free)
		return 0;
	auto it=dp.lb({turn,a});
	if(it!=dp.end() and it->fi==mkp(turn,a))
		return it->se;
	int&ret=dp[{turn,a}];
	if(!turn){
		ret=1;

		int fail=0;
		for(auto&i:a)
			fail|=!--i.fi and !i.se;
		if(!fail)
			ret&=f(!turn);
		for(auto&i:a)
			++i.fi;

		fail=0;
		for(auto&i:a)
			fail |= (--i.se,!i.fi and !i.se);
		if(!fail)
			ret&=f(!turn);
		for(auto&i:a)
			++i.se;
	}else{
		ret=0;
		for(int mask=0;mask<(1ll<<n);mask++){
			for(int i=0;i<n;i++)
				(mask>>i&1?a[i].fi:a[i].se)--;
			ret|=f(!turn);
			for(int i=0;i<n;i++)
				(mask>>i&1?a[i].fi:a[i].se)++;
			if(ret)
				break;
		}
	}
	return ret;
}
void solve(){
	n=input1();
	for(int i=0;i<n;i++){
		auto [x,y]=input<int,int>();
		a.emplace_back(x,y);
	}
	println(f(0));
}
