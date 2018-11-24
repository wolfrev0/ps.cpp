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

template<typename T>
typename enable_if<std::is_fundamental<T>::value, T>::type fastpow(const T& a, int p) {
	if (p == 0)
		return 1;
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<typename T>
typename enable_if<!is_fundamental<T>::value, T>::type fastpow(const T& a, int p) {
	if (p == 0)
		return a.mulid();
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

ll fibo(int n) {
	static ll memo[100];

	if (n <= 1)
		return 1;
	auto& ret = memo[n];
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

vector<ll> factorization(ll n)
{
	ll cur = n;
	vector<ll> ret;
	trav (i, 2, i*i <= n)
		while (!(cur%i))
		{
			cur /= i;
			ret.push_back(i);
		}
	if (cur > 1)
		ret.push_back(cur);
	return ret;
}

vector<ll> divisors(ll n)
{
	vector<ll> ret, tmp;
	trav(i, 1, i*i <= n){
		if (n%i == 0)
		{
			ret.push_back(i);
			if (i != n / i)
				tmp.push_back(n / i);
		}
	}
	reverse(tmp.begin(), tmp.end());
	ret.insert(ret.end(), tmp.begin(), tmp.end());
	return ret;
}

//n*invackermann(n)
template<int n>
bitset<n> sieve_prime()
{
	bitset<n> ret(3);
	for (ll i = 2; i*i<=n; i++) {
		if (ret[i])
			continue;
		for (ll j = i * i; j < n; j += i)
			ret[j] = true;
	}
	return ret.flip();
}

//harmony series: nlogn
vector<vector<int>> sieve_divs(int n)
{
	vector<vector<int>> ret(n);
	for (ll i = 2; i*i<=n; i++) {
		for (ll j = i + i; j < n; j += i)
			ret[j].push_back(i);
	}
	return ret;
}

//More accurate than floor(log(n))
int lgf(ll n)
{
	assert(n > 0);
	int ret = -1;
	while (n)
		n /= 2, ret++;
	return ret;
}

//More accurate than ceil(log(n))
int lgc(ll n) {
	return lgf(n) + __builtin_popcountll(n) != 1;
}

class NoModInv {};

struct ModNum {
	using T = ll;
	ModNum(T n = 0, T m = mod) :n((n%m + m) % m), m(m) {}
	inline T val()const { return n; }
	inline ModNum mulid() const { return { 1, m }; }

	inline ModNum operator - () const { return { -n, m }; }
	inline ModNum operator + (const ModNum& b)const { return { n + b.val(), m }; }
	inline ModNum operator - (const ModNum& b)const { return { n - b.val() + m, m }; }
	inline ModNum operator * (const ModNum& b)const { return { n * b.val(), m }; }
	inline ModNum operator / (const ModNum& b)const { return *this * inv(b); }
	inline ModNum operator+= (const ModNum& b) { return *this = *this + b; }
	inline ModNum operator-= (const ModNum& b) { return *this = *this - b; }
	inline ModNum operator*= (const ModNum& b) { return *this = *this * b; }
	inline ModNum operator/= (const ModNum& b) { return *this = *this / b; }

	inline ModNum& operator++ () { *this += 1; return *this; }
	inline ModNum& operator-- () { *this -= 1; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum& r) const { return n == r.n; }
	inline bool operator!=(const ModNum& r) const { return !(*this == r); }
	inline bool operator<(const ModNum& r) const { return n < r.n; }
	inline bool operator<=(const ModNum& r) const { return n <= r.n; }
	inline bool operator>(const ModNum& r) const { return n > r.n; }
	inline bool operator>=(const ModNum& r) const { return n >= r.n; }

	inline ModNum inv(const ModNum &b)const {
		ll x, y;
		ll g = xgcd(b.val(), -m, x, y);
		if (1 % g)
			throw NoModInv();
		x *= 1 / g;
		while (x < 0)
			x += -m / g;
		return { x, m };
		//extended gcd is better than fastpow.
		//return fastpow(ModNum(m, b.val()), m - 2)*n; 
	}

	//operator T() const { return n; }
	ModNum(const ModNum& r) : m(r.m), n(r.n) {}
	inline ModNum& operator= (const ModNum& r) { n = r.n; return *this; }
private:
	T n;
	const T m;
};

ostream& operator<<(ostream& s, const ModNum& n) { return s << n.val(); }
istream& operator<<(istream& s, const ModNum& n) { return s << n.val(); }

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	char buf[1000010];
	while (true)
	{
		cin.getline(buf, sizeof buf);
		if (string(buf) == ".")
			break;
		string p = buf;

		ModNum h = 0;
		ModNum pw = 1;
		forh(i, 0, p.size()) {
			h *= prime;
			pw *= prime;
			h += p[i];
		}
		auto t = h;
		forho(i, 0, p.size()) {
			h -= p[p.size() - 1 - i];
			h /= prime;
			t -= (pw /= prime) * p[i];
			if (h == t)
				break;
		}
		if (p.size() % (i + 1))
			cout << 1 << endl;
		else
			cout << p.size() / (i + 1) << endl;
	}

	return 0;
}
