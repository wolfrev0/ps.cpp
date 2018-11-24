#pragma GCC optimize ("Ofast")
#include "bits/stdc++.h"
//syntax sugars
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forho(var, begin, end) auto var = begin; for(; var < end; ++var)//out declaration
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#define forco(var, begin, end) auto var = begin; for(; var <= end; ++var)//out declaration
#define trav(var, begin, cond) for(auto var = begin; cond; ++var)//travel
#define travo(var, begin, cond) auto var = begin; for(; cond; ++var)//out declaration

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
template<typename T, typename U>
inline pair<T, U> operator-(const pair<T, U> &a, const pair<T, U> &b) { return { a.first - b.first, a.second - b.second }; }
template<typename T, typename U>
inline pair<T, U> operator-=(pair<T, U> &a, const pair<T, U> &b) { return a = a - b; }

//a.k.a. partial match table, pi
vector<int> failure_function(const string &p) {
	vector<int> ret(p.size());
	int si = 1, pi = 0;
	while (si + pi < p.size()) {
		if (pi < p.size() && p[si + pi] == p[pi]) {
			pi++;
			ret[si + pi - 1] = pi;
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ret[pi - 1];
				pi = ret[pi - 1];
			}
		}
	}
	return ret;
}

vector<int> kmp(const string &s, const string &p) {
	if (s.size() < p.size())
		return {};
	vector<int> ret;
	auto ff = failure_function(p);
	int si = 0, pi = 0;
	while (si <= s.size() - p.size()) {
		if (pi < p.size() && s[si + pi] == p[pi]) {
			if (++pi == p.size())
				ret.push_back(si);
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ff[pi - 1];
				pi = ff[pi - 1];
			}
		}
	}

	return ret;
}

vector<int> failure_function2(const string &p) {
	int pi = 0;
	vector<int> ret(p.size());
	forh(i, 1, p.size()) {
		while (pi > 0 && p[i] != p[pi])
			pi = ret[pi - 1];
		if (p[i] == p[pi])
			ret[i] = ++pi;
	}
	return ret;
}

vector<int> kmp2(const string &s, const string &p) {
	const auto &ff = failure_function2(p);
	vector<int> ans(s.size());
	int pi = 0;
	forh(i, 0, s.size()) {
		while (pi > 0 && s[i] != p[pi])
			pi = ff[pi - 1];
		if (s[i] == p[pi] && (ans[i] = ++pi) == p.size())
			pi = ff[pi - 1];
	}
	return ans;
}

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
