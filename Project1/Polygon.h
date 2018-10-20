#pragma once
#include "Vec2.h"

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