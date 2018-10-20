#pragma once
#include "Vec2.h"

struct Polygon
{
	vector<Vec2> vs;

	Polygon() {}
	explicit Polygon(int n) :vs(n) {}
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