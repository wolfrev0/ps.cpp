#include "Core.h"
#include "Fenwick.h"
#include "ModNum.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	int n;
	cin >> n;
	FenwickTree<ModNum> st(200001), st2(200001);
	ModNum ans = 1;
	forh(i, 0, n)
	{
		int x;
		cin >> x;
		if (i)
			ans *= st2.query(x, 200001) - st.query(x, 200001)*x + st.query(0, x+1)*x - st2.query(0, x+1);
		st.update(x, 1);
		st2.update(x, x);
	}
	cout << ans.val() << endl;

	return 0;
}