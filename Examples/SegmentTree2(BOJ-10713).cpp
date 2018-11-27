#include "Core.h"
#include "Line.h"
#include "SegmentTree.h"

const int N = 100000;
const int M = 100000;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	ll arr[M];
	forh(i, 0, m)
	{
		cin >> arr[i];
		arr[i]--;
	}
	ll a[N], b[N], c[N];
	forh(i, 0, n - 1)
		cin >> a[i] >> b[i] >> c[i];
	SegmentTree<ll> st(n);
	forh(i, 1, m)
		st.update(min(arr[i - 1], arr[i]), max(arr[i - 1], arr[i]) - 1, 1);
	ll ans = 0;
	forh(i, 0, n - 1)
	{
		ll cnt = st.query(i, i);
		ans += min(cnt * b[i] + c[i], cnt * a[i]);
	}
	cout << ans << endl;

	return 0;
}