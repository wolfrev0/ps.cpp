#include "Core.h"
#include "FFT.h"

#define endl '\n'//not interactive?
#define int i64//overflow?

signed main(){
	int n;
	cin>>n;
	vector<int> a(n), b(n);
	hfor(i,0,n)
		cin>>a[i];
	hfor(i,0,n)
		cin>>b[n-1-i];
	auto res=conv_cir(a,b);
	cout<<*max_element(all(res))<<endl;

	return 0;
}
