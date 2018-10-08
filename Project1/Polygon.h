#pragma once
#include "Vec2.h"

using Polygon = vector<Vec2>;

//graham scan
Polygon convex_hull(vector<Vec2> &pts)
{
	swap(pts[0], *min_element(pts.begin(), pts.end()));
	auto base = pts[0];
	sort(pts.begin() + 1, pts.end(), [base](const Vec2 &l, const Vec2 &r) {
		return (l - base).angle() < (r - base).angle();
	});

	Polygon ret;
	forc(i, 0, pts.size())
	{
		auto im = i % pts.size();

		while (ret.size() >= 2)
		{
			auto base = ret[ret.size() - 2];
			auto top = ret.back() - base;
			auto candi = pts[im] - base;
			if (top.ccw(candi) < 0 || top.ccw(candi) == 0 && candi.size() > top.size())
				ret.pop_back();
			else
				break;
		}

		if (ret.size() < 2)
			ret.push_back(pts[im]);
		else
		{
			auto base = ret[ret.size() - 2];
			auto top = ret.back() - base;
			auto candi = pts[im] - base;
			if (top.ccw(candi) > 0 || candi.size() > top.size())
				ret.push_back(pts[im]);
		}
	}
	if (ret.front() == ret.back())
		ret.pop_back();

	return ret;
}