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

struct Rect
{
	using T = ll;
	T x1, y1, x2, y2;
	Rect(T x1, T y1, T x2, T y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

	T width()const { return x2 - x1 + 1; }
	T height()const { return y2 - y1 + 1; }

	Rect intersect(const Rect &r) const {
		if (x1 > r.x2 || x2 < r.x1 || y1 > r.y2 || y2 < r.y1)
			throw 0;
		return Rect(max(x1, r.x1), max(y1, r.y1), min(x2, r.x2), min(y2, r.y2));
	}
};

pair<ll, ll> cnt(Rect r) {
	ll black = r.width() * r.height() / 2, white = r.width() * r.height() / 2;
	((r.x1 + r.y1) % 2 ? black : white) += r.width() * r.height() % 2;
	return { black, white };
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	ll t;
	cin >> t;
	while (t--)
	{
		ll n, m;
		cin >> n >> m;
		ll x1, x2, x3, x4, y1, y2, y3, y4;
		cin >> x1 >> y1 >> x2 >> y2;
		cin >> x3 >> y3 >> x4 >> y4;
		pair<ll, ll> base = { n * m / 2 , n * m / 2 + n * m % 2 };
		Rect r1 = { x1, y1, x2, y2 };
		Rect r2 = { x3, y3, x4, y4 };
		auto a = cnt(r1);
		a = pair<ll, ll>{ -a.first, a.first };
		auto b = cnt(r2);
		b = pair<ll, ll>{ b.second, -b.second };
		pair<ll, ll> inter = { 0,0 };
		try {
			inter = cnt(r1.intersect(r2));
		}
		catch (...) {}
		inter = pair<ll, ll>{ inter.first,-inter.first };
		auto ans = base + a + b + inter;
		cout << ans.second << ' ' << ans.first << endl;
	}

	return 0;
}
