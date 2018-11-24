#include "String.h"

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	string s;
	cin >> s;
	int ans = 0;
	forh(i, 0, s.size()) {
		auto t = s.substr(i);
		auto res= kmp2(s, t);
		int cnt[5001] = { 0, };
		forh(j, 0, res.size())
			cnt[res[j]]++;
		forhi(j, 0, 5001)
			if (cnt[j] >= 2)
				ans = max(ans, j);
	}
	cout<<ans<<endl;

	return 0;
}