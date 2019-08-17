#include "Core.h"
#include "FFT.h"

#define endl '\n'//not interactive?
#define int i64//overflow?

signed main(){
	int n;
	cin>>n;
	vector<int> a(200001);
	hfor(i,0,n){
		int x;
    cin>>x;
		a[x]++;
  }
	int m;
	cin>>m;
	int b[200000];
  hfor(i,0,m)
    cin>>b[i];
  auto res=conv_mul(a,a);
	int ans=0;
	hfor(i,0,m)
		ans+=res[b[i]]||a[b[i]];
	cout<<ans<<endl;

	return 0;
}