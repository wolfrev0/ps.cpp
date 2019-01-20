#include "Core.h"
#include "ModNum.h"
#include "SegmentTree.h"

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	SegmentTreeLazy<ModNum> st(1000000, 1, I32::inf(), [](auto a, auto b) {return a * b; }, [](int s, int e, auto a, auto b) {return b; }, [](auto a, auto b) {return b; });
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++){
		i64 x;
		cin >> x;
		st.update(i, x);
	}
	for (int i = 0; i < m + k; i++){
		int a, b;
		i64 c;
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c;
			st.update(--b, c);
		}
		else
		{
			cin >> b >> c;
			cout << st.query(--b, c).val() << endl;
		}
	}

	return 0;
}