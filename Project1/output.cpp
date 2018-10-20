#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#pragma GCC optimize ("Ofast")

using namespace std;

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
	using T = ll;
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
	inline T size()const { return hypot(x, y); }
	inline T sizesq()const { return dot(*this); }
	inline Vec2 normalize()const { return Vec2(x / size(), y / size()); }
	inline T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	inline T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	inline T ccw(const Vec2 &a, const Vec2 &b) const { return (a - *this).cross(b - *this); }
	inline T angle()const { return atan2(y, x); }
	inline Vec2 project(const Vec2 &p)const { Vec2 base = normalize(); return base * base.dot(p); }
	inline Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
} zero, err = Vec2(inf<Vec2::T>(), inf<Vec2::T>());

struct Polygon
{
	vector<Vec2> vs;

	Polygon() {}
	explicit Polygon(int n) :vs(n) {}
	inline int size()const { return vs.size(); }
	inline Vec2 &front() { return vs.front(); }
	inline Vec2 &back1() { return vs.back(); }
	inline Vec2 &back2() { return vs[size() - 2]; }
	inline void pushback(const Vec2 &v) { vs.push_back(v); }
	inline void popback() { vs.pop_back(); }
	inline Vec2 &operator[](int idx) { return vs[idx]; }
	inline void clear() { vs.clear(); }

	void sort()
	{
		swap(vs[0], *min_element(vs.begin(), vs.end()));
		auto base = vs[0];
		std::sort(vs.begin() + 1, vs.end(), [base](const Vec2 &l, const Vec2 &r) {
			Vec2::T val = base.ccw(l, r);
			if (val == 0)
				return l < r;//need some thinking but ok.
			else
				return val > 0;
		});
	}

	//graham scan
	Polygon convex_hull()
	{
		for (int i = 1; i < vs.size() - 1; i++)
			assert(vs[0].ccw(vs[i], vs[i + 1]) >= 0);

		Polygon ret;
		forh(i, 0, vs.size())
		{
			while (ret.size() >= 2)
			{
				auto ltop = ret.back1() - ret.back2();
				auto lcandi = vs[i] - ret.back2();
				if (ltop.cross(lcandi) <= 0)
					ret.popback();
				else
					break;
			}
			ret.pushback(vs[i]);
		}

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

class LineException {};
class LineSame :public LineException {};

struct Line
{
	Vec2 s, e;
	explicit Line() :Line(zero, zero) {}
	explicit Line(Vec2 s, Vec2 e) :s(s), e(e) { if (s > e)swap(this->s, this->e); }
	inline Vec2 dir()const { return e - s; }

	Vec2 intersect(const Line &r)const
	{
		Vec2::T det = dir().cross(r.dir());
		if (abs(det) < eps)
			if ((s - r.s).size() < eps)
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

void error()
{
	cout << -1 << endl;
	exit(0);
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(0);
	srand((uint)time(0));

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		Polygon p(n);
		forh(i, 0, n)
			cin >> p[i].x >> p[i].y;
		p.sort();
		p = p.convex_hull();

		int j = 1;
		Vec2 a1 = p[0], a2 = p[1];
		forh(i, 0, p.size())
		{
			int ni = (i + 1) % p.size();
			int nj = (j + 1) % p.size();
			while ((p[ni] - p[i]).cross(p[nj] - p[j]) > 0)
				j = nj, nj = (nj + 1) % p.size();
			if ((a1 - a2).sizesq() < (p[j] - p[i]).sizesq())
				a1 = p[i], a2 = p[j];
		}
		cout << a1.x << ' ' << a1.y << ' ' << a2.x << ' ' << a2.y << endl;
	}

	return 0;
}
