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
constexpr T inf() { return numeric_limits<T>::max() / 2; }

struct Vec2
{
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
	inline T ccw(const Vec2 &a, const Vec2 &b) const { return cross(a, b); }
	inline T angle()const { auto ret = atan2(y, x); return fmod(ret + 2 * pi, 2 * pi); }
	inline T tan()const { if (x == 0) return abs(y) / x; if (y == 0)return 0; return y / x; }
	inline Vec2 project(const Vec2 &p)const { Vec2 base = normalize(); return base * base.dot(p); }
} zero, err = Vec2(inf<Vec2::T>(), inf<Vec2::T>()), epsv = Vec2(eps, eps);

inline bool cmpccw(const Vec2 &l, const Vec2 &r, const Vec2 &base) {
	Vec2::T val = base.ccw(l, r);
	if (val == 0)
		return (l - base).sizesq() < (r - base).sizesq();
	return val > 0;
}

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

struct Polygon
{
	vector<Vec2> vtx;

	Polygon() {}
	explicit Polygon(int n) :vtx(n) {}
	inline int size()const { return vtx.size(); }
	inline Vec2 &front() { return vtx.front(); }
	inline Vec2 &back1() { return vtx.back(); }
	inline Vec2 &back2() { return vtx[size() - 2]; }
	inline void pushback(const Vec2 &v) { vtx.push_back(v); }
	inline void popback() { vtx.pop_back(); }
	inline Vec2 &operator[](int idx) { return vtx[idx]; }
	inline void clear() { vtx.clear(); }

	void sort()
	{
		swap(vtx[0], *min_element(vtx.begin(), vtx.end()));
		std::sort(vtx.begin() + 1, vtx.end(), bind(cmpccw, _1, _2, vtx[0]));
	}

	//graham scan
	Polygon convex_hull()
	{
		for (int i = 1; i < size() - 1; i++)
			assert(vtx[0].ccw(vtx[i], vtx[i + 1]) >= 0);

		Polygon ret;
		forh(i, 0, size())
		{
			while (ret.size() >= 2)
			{
				auto ltop = ret.back1() - ret.back2();
				auto lcandi = vtx[i] - ret.back2();
				if (ltop.cross(lcandi) <= 0)
					ret.popback();
				else
					break;
			}
			ret.pushback(vtx[i]);
		}

		return ret;
	}

	ld area()
	{
		ld ans = 0;
		forh(i, 1, size() - 1)
			ans += vtx[0].ccw(vtx[i], vtx[i + 1]);
		return ans / 2;
	}

	Vec2::T circum()
	{
		Vec2::T ret = 0;
		forh(i, 0, size())
			ret += (vtx[i] - vtx[(i + 1) % size()]).size();
		return ret;
	}
};

class LineException {};
class LineSame :public LineException {};

struct Line
{
	Vec2 s, e;
	explicit Line() :Line(zero, zero) {}
	explicit Line(Vec2 s, Vec2 e) :s(s), e(e) { }
	inline Vec2 dir()const { return e - s; }

	Vec2 intersect(Line &r)
	{
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

	virtual Vec2 perpend_foot(Vec2 p) const {
		auto res = s + dir().project(p - s);
		return valid_foot(res) ? res : err;
	}

private:
	virtual bool valid_intersect(const Vec2 &p) const { return true; }
	virtual bool valid_foot(const Vec2 &p) const { return true; }
};

struct Segment :public Line
{
	explicit Segment() :Segment(zero, zero) {}
	explicit Segment(Vec2 s, Vec2 e) :Line(s, e) {}
	virtual bool valid_intersect(const Vec2 &p)const override { return s <= p && p <= e; }
	virtual bool valid_foot(const Vec2& p)const override { return s <= p && p <= e; }
};

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
	inline ModNum operator / (const ModNum b)const { return fastpow(ModNum(m, b.val()), m - 2)*n; }
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

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	Polygon p(n);
	forh(i, 0, n)
		cin >> p[i].x >> p[i].y;

	ll ans = 0;
	forh(i, 0, n)
	{
		p.sort();
		int j = (i + 1) % n;
	}
	cout << ans / 2 << endl;

	return 0;
}
