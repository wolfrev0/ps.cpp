#pragma GCC optimize ("Ofast")
#include "bits/stdc++.h"
//syntax sugars
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#define trav(var, begin, cond) for(auto var = begin; cond; ++var)//travel
#define travo(var, begin, cond) auto var = begin; for(; cond; ++var)//travel

using namespace std;
using namespace std::placeholders;

using ld = double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using ushort = unsigned short;
using uchar = unsigned char;

const int mod = int(1e9 + 7);
const int prime = int(2e9 + 11);
const ld pi = acos(-1);
const ld eps = 1e-12;
const int dir[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

template<typename T>
constexpr inline T inf() { return numeric_limits<T>::max() / 2; }

template<typename T, typename U>
inline pair<T, U> operator+(const pair<T, U> &a, const pair<T, U> &b) { return { a.first + b.first, a.second + b.second }; }
template<typename T, typename U>
inline pair<T, U> operator+=(pair<T, U> &a, const pair<T, U> &b) { return a = a + b; }

struct Frac
{
	ll a, b;
	bool operator<(const Frac &r)const { return a * r.b < r.a*b; }
};

int n, k;
ll arr[200000];
ll cnt[200001] = { 0, };

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	cin >> n >> k;
	forh(i, 0, n) {
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	vector<pair<Frac, ll>> v;
	forc(i, 1, 200000)
		v.push_back({ { cnt[i], 1 }, i });
	sort(v.begin(), v.end());
	multiset<pair<Frac, ll>> ans;
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
