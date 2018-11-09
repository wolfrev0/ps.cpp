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

template<typename T>
typename enable_if<std::is_fundamental<T>::value, T>::type fastpow(const T &a, int p)
{
	if (p == 0)
		return 1;
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<typename T>
typename enable_if<!is_fundamental<T>::value, T>::type fastpow(const T &a, int p)
{
	if (p == 0)
		return a.mulid();
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

ll fibo(int n)
{
	static ll memo[100];

	if (n <= 1)
		return 1;
	auto &ret = memo[n];
	if (ret)
		return ret;
	return ret = fibo(n - 1) + fibo(n - 2);
}

ll xgcd(ll a, ll b, ll& x, ll& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}

	ll xtmp, ytmp;
	ll g = xgcd(b%a, a, xtmp, ytmp);
	x = ytmp - (b / a) * xtmp;
	y = xtmp;
	return g;
}

pair<ll, ll> xgcd2(ll a, ll b) {
	if (b == 0)
		return { 1,0 };
	auto t = xgcd2(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}

class NoModInv {};

struct ModNum
{
	using T = ll;
	ModNum(T n = 0, T m = T(1e9+7)) :n((n%m + m) % m), m(m) {}
	inline T val()const { return n; }
	inline ModNum mulid() const { return 1; }

	inline ModNum operator - () const { return -n; }
	inline ModNum operator + (const ModNum b)const { return n + b.val(); }
	inline ModNum operator - (const ModNum b)const { return n - b.val() + m; }
	inline ModNum operator * (const ModNum b)const { return n * b.val(); }
	inline ModNum operator / (const ModNum b)const {
		ll x, y;
		ll g = xgcd(b.val(), -mod, x, y);
		if (1 % g)
			throw NoModInv();
		x *= 1 / g;
		while (x < 0)
			x += -mod / g;
		return x;
		//extended gcd is better than fastpow.
		//return fastpow(ModNum(m, b.val()), m - 2)*n; 
	}
	inline ModNum operator+= (const ModNum b) { return *this = *this + b.val(); }
	inline ModNum operator-= (const ModNum b) { return *this = *this - b.val(); }
	inline ModNum operator*= (const ModNum b) { return *this = *this * b.val(); }
	inline ModNum operator/= (const ModNum b) { return *this = *this / b.val(); }

	inline ModNum &operator++ () { *this += 1; return *this; }
	inline ModNum &operator-- () { *this -= 1; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum &r) const { return n == r.n; }
	inline bool operator!=(const ModNum &r) const { return !(*this == r); }
	inline bool operator<(const ModNum &r) const { return n < r.n; }
	inline bool operator<=(const ModNum &r) const { return n <= r.n; }
	inline bool operator>(const ModNum &r) const { return n > r.n; }
	inline bool operator>=(const ModNum &r) const { return n >= r.n; }

	//operator T() const { return n; }
	inline ModNum &operator= (const ModNum &r) { n = r.n; return *this; }
private:
	T n;
	const T m;
};

ll f(int n)
{
	ll res = 1;
	forc(i, 1, n)
		res = res * i % mod;
	return res;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, k;
	cin >> n >> k;
	ModNum mi1 = 1;	mi1 /= f(k);
	ModNum mi2 = 1; mi2 /= f(n - k);
	cout << (mi1*mi2*f(n)).val() << endl;

	return 0;
}
