#include "Frac.h"

int n, k;
i64 arr[200000];
i64 cnt[200001] = { 0, };

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((u32)time(0));

	cin >> n >> k;
	forh(i, 0, n) {
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	vector<pair<Frac, i64>> v;
	forc(i, 1, 200000)
		v.push_back({ { cnt[i], 1 }, i });
	sort(v.begin(), v.end());
	multiset<pair<Frac, i64>> ans;
	forh(i, v.size() - k, v.size())
		ans.insert(v[i]);
	while (ans.begin()->first < Frac{ (--ans.end())->first.a, (--ans.end())->first.b + ans.begin()->first.b }) {

		auto it = --ans.end();
		ans.insert({ { it->first.a, it->first.b + ans.begin()->first.b }, it->second });
		ans.erase(ans.begin());
		ans.erase(it);
	}
	for (auto &i : ans)
		forh(j, 0, i.first.b)
		cout << i.second << ' ';

	return 0;
}
