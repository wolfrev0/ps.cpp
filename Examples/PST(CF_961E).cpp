#include "PST.h"
#include "XArr.h"

int main(){
	cin.sync_with_stdio(false), cin.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n;
	int arr[200001];
	cin >> n;
	forh(i, 0, n)
	{
		cin >> arr[i];
		arr[i] = min(arr[i]-1, n-1);
	}

	PST<i64> pst(n, [](i64 a, i64 b){return a+b;});
	XArr<PST<i64>::Node *> v(n, 1);
	pst.build(v[-1]=new PST<i64>::Node());
	u64 ans = 0;
	forh(i, 0, n){
		ans += pst.query(v[min(i-1, arr[i])], i, n);
		auto tmp = pst.query(v[i-1], arr[i], arr[i]+1);
		pst.upgrade(v[i], v[i-1], arr[i], tmp+1);
	}
	cout << ans << endl;

	return 0;
}