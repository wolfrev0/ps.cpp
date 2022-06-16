#include "core/base.h"
#include "misc/ordering.h"

void solve(){
	int n=6;
	Arr<int> a(n); iota(a.begin(),a.end(),0);
	Arr<int> b(n); iota(b.begin(),b.end(),0);
	random_shuffle(a.begin(),a.end());
	random_shuffle(b.begin(),b.end());
	dbg(n,a,b);

	auto lt=lamp(x<y,int x,int y);
	auto gt=lamp(x>y,int x,int y);
	auto ord_a=lam(a[x]<a[y],int x,int y);
	auto ord_b=lam(b[x]<b[y],int x,int y);
	Ordering<int,decltype(lt),decltype(gt),decltype(ord_a),decltype(ord_b)> ordering(lt,gt,ord_a,ord_b);
	for(int i=0;i<n;i++)
		ordering.insert(i);
	for(int i=0;i<ordering.cmpcnt;i++){
		Arr<int> arr(n); iota(arr.begin(),arr.end(),0);
		sort(arr.begin(),arr.end(),ordering.cmptor(i));
		
		print("Sorted: ");
		for(auto i:arr)
			print(i,' ');
		println();

		println("Front: ",ordering.front(i));
		println("Back: ",ordering.back(i));
		for(int j=0;j<n;j++)
			println("Next of ",j,"=",ordering.ub(i,j).value_or(-1),' ');
		println();
	}
}
signed main(){
	// for(int ti=1,t=input();ti<=t;ti++)
	// 	cout<<"Case #"<<ti<<": ",
		solve();
}
