#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#pragma GCC optimize ("Ofast")

using namespace std;

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using ushort = unsigned short;
using uchar = unsigned char;

const int mod = int(1e9 + 7);
const int prime = int(2e9 + 11);
const ld pi = acosl(-1);
const ld eps = 1e-13;
const int dir[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

template<typename T>
constexpr T inf() { return numeric_limits<T>::max() / 2; }

struct Vec2
{
	using T = double;
	T x, y;
	Vec2() :x(0), y(0) {}
	Vec2(T x, T y) :x(x), y(y) {}
	inline bool operator==(const Vec2 &r)const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vec2 &r)const { return !(*this == r); }
	inline bool operator<(const Vec2 &r)const { return x == r.x ? y < r.y : x < r.x; }
	inline bool operator<=(const Vec2 &r)const { return *this == r || *this < r; }
	inline bool operator>(const Vec2 &r)const { return x == r.x ? y > r.y : x > r.x; }
	inline bool operator>=(const Vec2 &r)const { return *this == r || *this > r; }
	inline Vec2 operator+ (const Vec2 &r)const { return { x + r.x, y + r.y }; }
	inline Vec2 operator-()const { return { -x, -y }; }
	inline Vec2 operator- (const Vec2 &r)const { return *this + -r; }
	inline Vec2 operator* (T r)const { return { x*r, y*r }; }
	inline T size()const { return hypot(x, y); }
	inline Vec2 normalize()const { return { x / size(), y / size() }; }
	inline T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	inline T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	inline T ccw(const Vec2 &a, const Vec2 &b) { return (a - *this).cross(b - *this); }
	inline T angle()const { return atan2(y, x); }
	inline Vec2 project(const Vec2 &base)const { Vec2 b = base.normalize(); return b * b.dot(*this); }
	inline Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
} zero, err = { inf<Vec2::T>(), inf<Vec2::T>() };

bool bound_rect(Vec2 a, Vec2 b, Vec2 p)
{
	if (a > b)
		swap(a, b);
	return a <= p && p <= b;
}

Vec2 perpend_foot(Vec2 a, Vec2 p)
{
	auto res = p.project(a);
	return bound_rect(Vec2(), a, res) ? res : err;
}

struct Segment
{
	Vec2 s, e;
	Segment(Vec2 s, Vec2 e) :s(s), e(e) {}
	Vec2 dir() { return e - s; }
};

Vec2 line_intersect(Segment l1, Segment l2)
{
	Vec2::T det = l1.dir().cross(l2.dir());
	if (abs(det) < eps)
		return err;
	return l1.s + l1.dir()*((l2.s - l1.s).cross(l2.dir()) / det);
}

Vec2 paral_seg(Segment s1, Segment s2)
{
	if (s1.e < s1.s) swap(s1.s, s1.e);
	if (s2.e < s2.s) swap(s2.s, s2.e);
	if (s1.dir().cross(s2.s - s1.s) != 0 || s1.e < s2.s || s2.e < s1.s)
		return err;
	return max(s1.s, s2.s);
}

Vec2 seg_intersect(Segment s1, Segment s2)
{
	auto p = line_intersect(s1, s2);
	if (p == err)
		return paral_seg(s1, s2);
	bool in = bound_rect(s1.s, s1.e, p) && bound_rect(s2.s, s2.e, p);

	return in ? p : err;
}

Vec2::T distm(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	if (seg_intersect({ pa, a }, { pb, b }) != err)
		return 0;

	Vec2::T ans = inf<Vec2::T>();
	auto v = perpend_foot(b - pb, pa - pb);
	if (v != err)
		ans = min(ans, (v - pa).size());

	v = perpend_foot(b - pb, a - pb);
	if (v != err)
		ans = min(ans, (v - a).size());

	v = perpend_foot(a - pa, b - pa);
	if (v != err)
		ans = min(ans, (v - b).size());

	v = perpend_foot(a - pa, pb - pa);
	if (v != err)
		ans = min(ans, (v - pb).size());

	ans = min(ans, (pa - pb).size());
	ans = min(ans, (pa - b).size());
	ans = min(ans, (a - pb).size());
	ans = min(ans, (a - b).size());

	return ans;
}

Vec2::T distM(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	Vec2::T ans = inf<Vec2::T>();
	ans = max(ans, (pa - b).size());
	ans = max(ans, (a - pb).size());
	ans = max(ans, (a - b).size());
	return ans;
}

struct Polygon
{
	vector<Vec2> vs;

	Polygon() {}
	Polygon(int n) :vs(n) {}
	int size()const { return vs.size(); }
	Vec2 &front() { return vs.front(); }
	Vec2 &back1() { return vs.back(); }
	Vec2 &back2() { return vs[size() - 2]; }
	void pushback(const Vec2 &v) { vs.push_back(v); }
	void popback() { vs.pop_back(); }
	Vec2 &operator[](int idx) { return vs[idx]; }
	void clear() { vs.clear(); }

	void sort()
	{
		//too high error. see BOJ-11620
		//swap(vs[0], *min_element(vs.begin(), vs.end()));
		//auto ret.back2() = vs[0];
		//std::sort(vs.begin() + 1, vs.end(), [ret.back2()](const Vec2 &l, const Vec2 &r) {
		//	auto la = (l - ret.back2()).angle(); 
		//	auto ra = (r - ret.back2()).angle();
		//	if (abs(la - ra) < eps)
		//		return l < r;
		//	return la < ra;
		//});
		//not useful sort(can't calculate convex hull)
		//std::sort(vs.begin(), vs.end(), [](const Vec2& a, const Vec2& b) {
		//	ld val = a.cross(b);
		//	if (val == 0)
		//		return a < b;
		//	else
		//		return val > 0;
		//});
		swap(vs[0], *min_element(vs.begin(), vs.end()));
		auto base = vs[0];
		std::sort(vs.begin() + 1, vs.end(), [base](const Vec2 &l, const Vec2 &r) {
			auto ll = l - base;
			auto lr = r - base;
			ld val = ll.cross(lr);
			if (val == 0)
				return ll < lr;
			else
				return val > 0;
		});
	}

	//graham scan
	Polygon convex_hull()
	{
		Polygon ret;
		forc(i, 0, vs.size())
		{
			auto im = i % vs.size();

			while (ret.size() >= 2)
			{
				auto ltop = ret.back1() - ret.back2();
				auto lcandi = vs[im] - ret.back2();
				if (ltop.cross(lcandi) < 0 || ltop.cross(lcandi) == 0 && lcandi.size() > ltop.size())
					ret.popback();
				else
					break;
			}

			if (ret.size() < 2)
				ret.pushback(vs[im]);
			else
			{
				auto ltop = ret.back1() - ret.back2();
				auto lcandi = vs[im] - ret.back2();
				if (ltop.cross(lcandi) > 0 || lcandi.size() > ltop.size())
					ret.pushback(vs[im]);
			}
		}
		if (ret.front() == ret.back1())
			ret.popback();

		return ret;
	}

	ld area()
	{
		ld ans = 0;
		forh(i, 1, vs.size() - 1)
			ans += vs[0].ccw(vs[i], vs[i + 1]);
		return ans / 2;
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
	cout << fixed << setprecision(10);
	srand((uint)time(0));

	int n;
	cin >> n;
	Polygon polygon(n);
	forh(i, 0, n)
		cin >> polygon[i].x >> polygon[i].y;
	polygon.sort();
	cout << polygon.convex_hull().size() << endl;

	return 0;
}
