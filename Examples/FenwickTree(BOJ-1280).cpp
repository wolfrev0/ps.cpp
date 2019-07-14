#include "Core.h"
#include "Fenwick.h"
#include "Mod.h"
#define endl '\n'//not interactive?
//#define int i64//overflow?

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((unsigned)time(0));

	int n;
	cin >> n;
	Fenwick<Mod<mod>> st(200001), st2(200001);
	Mod<mod> ans = 1;
	hfor(i, 0, n)
	{
		int x;
		cin >> x;
		if (i)
			ans *= st2.q(x, 200001) - st.q(x, 200001)*x + st.q(0, x+1)*x - st2.q(0, x+1);
		st.upd(x, 1);
		st2.upd(x, x);
	}
	cout << ans.val() << endl;

	return 0;
}
