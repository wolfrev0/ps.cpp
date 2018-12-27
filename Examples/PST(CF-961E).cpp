#include "PST.h"

int main()
{
	cin.sync_with_stdio(false), cin.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	int arr[200001];
	cin >> n;
	forh(i, 0, n)
	{
		cin >> arr[i];
		arr[i] = min(arr[i]-1, n-1);
	}

	PST<ll> pst(n);
	ull ans = 0;
	forh(i, 0, n)
	{
		ans += pst.query(pst.ver(min(i - 1, arr[i])), i, n-1);
		auto tmp = pst.query(pst.ver(i - 1), arr[i], arr[i]);
		pst.upgrade(pst.ver(i - 1), pst.ver(i), arr[i], tmp+1);
	}
	cout << ans << endl;

	return 0;
}