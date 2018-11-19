#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#pragma GCC optimize ("Ofast")

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

vector<int> failure_function2(const string &p){
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
	vector<int> ans;
	int pi = 0;
	forh(i, 0, s.size()) {
		while (pi > 0 && s[i] != p[pi])
			pi = ff[pi - 1];
		if (s[i] == p[pi] && ++pi == p.size())
		{
			ans.push_back(i - pi + 1);
			pi = ff[pi - 1];
		}
	}
	return ans;
}

char text[1000010];
char pattern[1000010];

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	cin.getline(text, 1000010);
	cin.getline(pattern, 1000010);
	auto res = kmp2(text, pattern);
	cout << res.size() << endl;
	for (auto i : res)
		cout << i + 1 << ' ';

	return 0;
}
