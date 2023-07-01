#include "core/base.h"
#include "math/struct/ordering.h"

#define endl '\n' // Remove it when interactive
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
	int n=6;
	Arr<int> a(n); iota(a.begin(),a.end(),0);
	Arr<int> b(n); iota(b.begin(),b.end(),0);
	random_shuffle(a.begin(),a.end());
	random_shuffle(b.begin(),b.end());
	dbg(n,a,b);

	auto gt=lamp(x>y,int x,int y);
	auto ord_m2=lam(mkp(x%2,x)<mkp(y%2,y),int x,int y);
	auto ord_a=lam(a[x]<a[y],int x,int y);
	auto ord_b=lam(b[x]<b[y],int x,int y);
	Ordering<int,
		decltype(gt),
		decltype(ord_m2),
		decltype(ord_a),
		decltype(ord_b)> ordering(
			gt,ord_m2,ord_a,ord_b);
	for(int i=0;i<n;i++)
		ordering.add(i);
	for(int i=0;i<ordering.cmpcnt;i++){
		Arr<int> arr(n); iota(arr.begin(),arr.end(),0);
		sort(arr.begin(),arr.end(),ordering.cmptor(i));
		
		print("Sorted: ");
		for(auto i:arr)
			print(i,' ');
		println("");

		println("Front: ",ordering.front(i));
		println("Back: ",ordering.back(i));
		for(int j=0;j<n;j++)
			println("next(",j,")=",ordering.ub(i,j).value_or(-1),' ');
		println("");
	}
}
