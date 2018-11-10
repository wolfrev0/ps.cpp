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
typename enable_if<std::is_fundamental<T>::value, T>::type fastpow(const T &a, int p) {
	if (p == 0)
		return 1;
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<typename T>
typename enable_if<!is_fundamental<T>::value, T>::type fastpow(const T &a, int p) {
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

struct Vec2 {
	using T = ld;
	T x, y;
	explicit Vec2() :Vec2(0, 0) {}
	explicit Vec2(T x, T y) :x(x), y(y) {}
	inline bool operator==(const Vec2 &r)const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vec2 &r)const { return !(*this == r); }
	inline bool operator<(const Vec2 &r)const { return x == r.x ? y < r.y : x < r.x; }
	inline bool operator<=(const Vec2 &r)const { return *this == r || *this < r; }
	inline bool operator>(const Vec2 &r)const { return x == r.x ? y > r.y : x > r.x; }
	inline bool operator>=(const Vec2 &r)const { return *this == r || *this > r; }
	inline Vec2 operator+ (const Vec2 &r)const { return Vec2(x + r.x, y + r.y); }
	inline Vec2 operator-()const { return Vec2(-x, -y); }
	inline Vec2 operator- (const Vec2 &r)const { return *this + -r; }
	inline Vec2 operator* (T r)const { return Vec2(x*r, y*r); }
	inline Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
	inline T size()const { return hypot(x, y); }
	inline T sizesq()const { return dot(*this); }
	inline Vec2 normalize()const { return Vec2(x / size(), y / size()); }
	inline T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	inline T dot(const Vec2 &a, const Vec2 &b) const { return (a - *this).dot(b - *this); }
	inline T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	inline T cross(const Vec2 &a, const Vec2 &b) const { return (a - *this).cross(b - *this); }
	inline T ccw(const Vec2 &a, const Vec2 &b) const { return cross(a, b) ? cross(a, b) / abs(cross(a, b)) : 0; }
	inline T angle()const { auto ret = atan2(y, x); return fmod(ret + 2 * pi, 2 * pi); }
	inline T tan()const { if (x == 0) return abs(y) / x; if (y == 0)return 0; return y / x; }
	inline Vec2 project(const Vec2 &p)const { Vec2 base = normalize(); return base * base.dot(p); }
} zero, err = Vec2(inf<Vec2::T>(), inf<Vec2::T>()), epsv = Vec2(eps, eps);

inline bool cmpccw(const Vec2 &l, const Vec2 &r, const Vec2 &base) {
	Vec2::T val = base.ccw(l, r);
	assert(base <= l && base <= r);
	if (val == 0)
		//need some thinking but ok. because base should be left-bottom element.
		return l < r;
	return val > 0;
}

class NoModInv {};

struct ModNum {
	using T = ll;
	ModNum(T n = 0, T m = mod) :n((n%m + m) % m), m(m) {}
	inline T val()const { return n; }
	inline ModNum mulid() const { return 1; }

	inline ModNum operator - () const { return -n; }
	inline ModNum operator + (const ModNum b)const { return n + b.val(); }
	inline ModNum operator - (const ModNum b)const { return n - b.val() + m; }
	inline ModNum operator * (const ModNum b)const { return n * b.val(); }
	inline ModNum operator / (const ModNum b)const {
		ll x, y;
		ll g = xgcd(b.val(), -m, x, y);
		if (1 % g)
			throw NoModInv();
		x *= 1 / g;
		while (x < 0)
			x += -m / g;
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

class LineException {};
class LineSame :public LineException {};

struct Line {
	Vec2 s, e;
	explicit Line() :Line(zero, zero) {}
	explicit Line(Vec2 s, Vec2 e) :s(s), e(e) { }
	inline Vec2 dir()const { return e - s; }

	Vec2 intersect(Line &r) {
		if (s > e)
			swap(s, e);
		if (r.s > r.e)
			swap(r.s, r.e);

		Vec2::T det = dir().cross(r.dir());
		if (abs(det) < eps)
			if (abs((r.s - s).cross(e - s)) < eps)
				throw LineSame();
			else
				return err;
		auto res = s + dir()*((r.s - s).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res) ? res : err;
	}

	bool intersect_det(Line &r) {
		if (s > e)
			swap(s, e);
		if (r.s > r.e)
			swap(r.s, r.e);

		Vec2::T det1 = s.ccw(e, r.s) * s.ccw(e, r.e);
		Vec2::T det2 = r.s.ccw(r.e, s) * r.s.ccw(r.e, e);
		if (!det1 && !det2)
			return e >= r.s && r.e >= s;
		return det1 <= 0 && det2 <= 0;
	}

	Vec2 perpend_foot(const Vec2 &p) {
		if (s > e)
			swap(s, e);
		auto res = s + dir().project(p - s);
		return valid_foot(res) ? res : err;
	}

	bool contains(const Vec2 &v) {
		if (s > e)
			swap(s, e);
		return valid_contains(v) && v.ccw(s, e) == 0;
	}

private:
	virtual bool valid_intersect(const Vec2 &p) const { return true; }
	virtual bool valid_foot(const Vec2 &p) const { return true; }
	virtual bool valid_contains(const Vec2 &p) const { return true; }
};

struct Segment :public Line {
	explicit Segment() :Segment(zero, zero) {}
	explicit Segment(Vec2 s, Vec2 e) :Line(s, e) {}
	virtual bool valid_intersect(const Vec2 &p)const override {
		if (abs(s.x - e.x) < eps && abs(p.x - s.x) < eps)
			return s.y <= p.y && p.y <= e.y;
		if (abs(s.y - e.y) < eps && abs(p.y - s.y) < eps)
			return s.x <= p.x && p.x <= e.x;
		return s <= p && p <= e;
	}
	virtual bool valid_foot(const Vec2& p)const override { return s <= p && p <= e; }
	virtual bool valid_contains(const Vec2 &p) const override { return s <= p && p <= e; }
};

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Segment segn[2000];
	for (int i = 0; i < n; i++)
		cin >> segn[i].s.x >> segn[i].s.y >> segn[i].e.x >> segn[i].e.y;
	Segment segm[2000];
	for (int j = 0; j < m; j++)
		cin >> segm[j].s.x >> segm[j].s.y >> segm[j].e.x >> segm[j].e.y;

	double ans = inf<int>();
	for (int i = 0; i < n; i++)
	{
		;;
	}
	cout << ans << endl;

	return 0;
}
