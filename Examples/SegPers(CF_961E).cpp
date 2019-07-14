#include "SegPers.h"
#include "XArr.h"
#define endl '\n'//not interactive?
#define int i64//overflow?

signed main(){
	cin.sync_with_stdio(false), cin.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n;
	cin >> n;
	vector<int> arr(n);
	hfor(i,0,n){
		cin>>arr[i];
		arr[i]=min(arr[i]-1, n-1);
	}
	
	SegPersSum<int> pst(n);
	using Node=SegPers<int>::Node;
	XArr<Node *> v(n);
	pst.build(v[-1]=new Node());
	int ans=0;
	hfor(i,0,n){
		ans += pst.q(v[min(i-1, arr[i])], i, n);
		auto tmp = pst.q(v[i-1], arr[i], arr[i]+1);
		v[i]=pst.upd(v[i-1], arr[i], tmp+1);
	}
	cout<<ans<<endl;

	return 0;
}