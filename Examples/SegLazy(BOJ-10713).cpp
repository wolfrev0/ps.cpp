#include "Core.h"
#include "SegPredefs.h"
#include "SegLazy.h"

const int N = 100000;
const int M = 100000;

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n,m;
	cin>>n>>m;
	i64 arr[M];
	hfor(i,0,m){
		cin>>arr[i];
		arr[i]--;
	}
	i64 a[N],b[N],c[N];
	hfor(i,0,n-1)
		cin>>a[i]>>b[i]>>c[i];
	SegLazy<i64,SegfSumAdd<i64>> st(n);
	hfor(i,1,m)
		st.upd(min(arr[i-1],arr[i]),max(arr[i-1],arr[i]),1);
	i64 ans=0;
	hfor(i,0,n-1){
		i64 cnt=st.q(i,i+1);
		ans+=min(cnt*b[i]+c[i],cnt*a[i]);
	}
	cout<<ans<<endl;
  
	return 0;
}