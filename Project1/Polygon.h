#pragma once
#include "Line.h"

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

	vector<Segment> to_segments()
	{
		vector<Segment> ret;
		forh(i, 0, vtx.size())
			ret.emplace_back(vtx[i], vtx[(i + 1) % vtx.size()]);
		return ret;
	}

	bool contains(const Vec2 &v)
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
};