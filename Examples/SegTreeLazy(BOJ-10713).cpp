#include "Core.h"
#include "Line.h"
#include "SegTreeLazy.h"

const int N = 100000;
const int M = 100000;

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n,m;
	cin>>n>>m;
	i64 arr[M];
	forh(i,0,m){
		cin>>arr[i];
		arr[i]--;
	}
	i64 a[N],b[N],c[N];
	forh(i,0,n-1)
		cin>>a[i]>>b[i]>>c[i];
	SegTreeLazy<i64> st(n);
	forh(i,1,m)
		st.update(min(arr[i-1],arr[i]),max(arr[i-1],arr[i]),1);
	i64 ans=0;
	forh(i,0,n-1){
		i64 cnt=st.query(i,i+1);
		ans+=min(cnt*b[i]+c[i],cnt*a[i]);
	}
	cout<<ans<<endl;
  
	return 0;
}