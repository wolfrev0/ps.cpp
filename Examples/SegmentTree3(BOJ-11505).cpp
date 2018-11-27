#include "Core.h"
#include "ModNum.h"
#include "SegmentTree.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	SegmentTree<ModNum> st(1000000, 1, [](auto a, auto b) {return a * b; }, [](int l, int r, auto a, auto b) {return b; }, [](auto a, auto b) {return b; });
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		ll x;
		cin >> x;
		st.update(i, x);
	}
	for (int i = 0; i < m + k; i++)
	{
		int a, b;
		ll c;
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c;
			st.update(--b, c);
		}
		else
		{
			cin >> b >> c;
			cout << st.query(--b, --c).val() << endl;
		}
	}

	return 0;
}