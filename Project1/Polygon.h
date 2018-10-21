#pragma once
#include "Vec2.h"

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
		auto base = vtx[0];
		std::sort(vtx.begin() + 1, vtx.end(), [base](const Vec2 &l, const Vec2 &r) {
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