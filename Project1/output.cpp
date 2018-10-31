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

class LineException {};
class LineSame :public LineException {};

struct Line
{
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

struct Segment :public Line
{
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
		std::sort(vtx.begin(), vtx.end(), bind(cmpccw, _1, _2, *min_element(vtx.begin(), vtx.end())));
	}

	//graham scan
	Polygon convex_hull()
	{
		sort();
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
			ans += vtx[0].cross(vtx[i], vtx[i + 1]);
		return ans / 2;
	}

	Vec2::T circum()
	{
		Vec2::T ret = 0;
		forh(i, 0, size())
			ret += (vtx[i] - vtx[(i + 1) % size()]).size();
		return ret;
	}

	vector<Segment> to_segments()const
	{
		vector<Segment> ret;
		forh(i, 0, vtx.size())
			ret.emplace_back(vtx[i], vtx[(i + 1) % vtx.size()]);
		return ret;
	}

	virtual bool contains(const Vec2 &v) const
	{
		auto arr = to_segments();
		for (auto i : arr)
			if (i.contains(v))
				return true;
		int cnt = 0;
		auto l = Segment(v, v + Vec2(prime, 1));
		for (auto i : arr)
		{
			if (i.intersect_det(l))
				cnt++;
		}
		return cnt % 2;
	}

	Polygon intersect(const Polygon &r)
	{
		//see jongman book geometry
		throw 0;
	}
};

struct Convex :public Polygon
{
	virtual bool contains(const Vec2 &v)const override
	{
		Vec2::T tmp = v.cross(vtx[0], vtx[1]);
		forh(i, 0, size())
			if (tmp*v.cross(vtx[i], vtx[(i + 1) % vtx.size()]) <= 0)
				return false;
		return true;
	}

	Polygon intersect(const Convex &r)const
	{
		Convex ret;
		for (auto i : vtx)
			if (r.contains(i))
				ret.pushback(i);
		for (auto i : r.vtx)
			if (contains(i))
				ret.pushback(i);
		auto s1 = to_segments();
		auto s2 = r.to_segments();
		for(auto i:s1)
			for (auto j : s2)
			{
				try {
					auto res = i.intersect(j);
					if (res != err)
						ret.pushback(res);
				}
				catch (...) {}
			}
		return ret.convex_hull();
	}
};

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(12);
	srand((uint)time(0));

	int n, m;
	cin >> n >> m;
	Convex p1, p2;
	forh(i, 0, n)
	{
		int x, y;
		cin >> x >> y;
		p1.pushback(Vec2(x, y));
	}
	forh(i, 0, m)
	{
		int x, y;
		cin >> x >> y;
		p2.pushback(Vec2(x, y));
	}
	cout << p1.intersect(p2).area() << endl;

	return 0;
}
