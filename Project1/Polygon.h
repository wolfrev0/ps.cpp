#pragma once
#include "Line.h"

struct Polygon
{
	vector<Vec2> vtx;

	Polygon() {}
	explicit Polygon(int n) :vtx(n) {}
	explicit Polygon(const vector<Vec2>& v) :vtx(v) {}
	inline int size()const { return vtx.size(); }
	inline Vec2& front() { return vtx.front(); }
	inline void pushback(const Vec2& v) { vtx.push_back(v); }
	inline void popback() { vtx.pop_back(); }
	inline Vec2& operator[](int idx) { return vtx[idx]; }
	inline void clear() { vtx.clear(); }

	ld area() {
		ld ans = 0;
		forh(i, 1, size() - 1)
			ans += vtx[0].cross(vtx[i], vtx[i + 1]);
		return ans / 2;
	}

	Vec2::T circum() {
		Vec2::T ret = 0;
		forh(i, 0, size())
			ret += (vtx[i] - vtx[(i + 1) % size()]).size();
		return ret;
	}

	vector<Segment> to_segments()const {
		vector<Segment> ret;
		forh(i, 0, vtx.size())
			ret.emplace_back(vtx[i], vtx[(i + 1) % vtx.size()]);
		return ret;
	}

	virtual bool contains(const Vec2& v) const {
		auto arr = to_segments();
		for (auto i : arr)
			if (i.contains(v))
				return true;
		int cnt = 0;
		auto l = Segment(v, v + Vec2(prime, 1));
		for (auto i : arr) {
			if (i.intersect_det(l))
				cnt++;
		}
		return cnt % 2;
	}

	virtual Polygon intersect(const Polygon& r)const {
		//see jongman book geometry
		throw 0;
	}
};

struct Convex :public Polygon
{
	Convex() {}
	explicit Convex(int n) :Polygon(n) {}
	explicit Convex(const vector<Vec2>& v) :Polygon(v) { normalize(); }

	//graham scan
	void normalize() {
		if (vtx.empty())
			return;
		sort(vtx.begin(), vtx.end(), bind(cmpccw, _1, _2, *min_element(vtx.begin(), vtx.end())));
		vector<Vec2> res;
		forh(i, 0, size()) {
			while (res.size() >= 2) {
				auto ltop = res[res.size() - 1] - res[res.size() - 2];
				auto lcandi = vtx[i] - res[res.size() - 2];
				if (ltop.cross(lcandi) <= 0)
					res.pop_back();
				else
					break;
			}
			res.push_back(vtx[i]);
		}
		vtx = res;
	}

	virtual bool contains(const Vec2& v)const override
	{
		Vec2::T tmp = v.cross(vtx[0], vtx[1]);
		forh(i, 0, size())
			if (tmp*v.cross(vtx[i], vtx[(i + 1) % vtx.size()]) <= 0)
				return false;
		return true;
	}

	virtual Polygon intersect(const Polygon& r)const override {
		vector<Vec2> ret;
		for (auto i : vtx)
			if (r.contains(i))
				ret.push_back(i);
		for (auto i : r.vtx)
			if (contains(i))
				ret.push_back(i);
		auto s1 = to_segments();
		auto s2 = r.to_segments();
		for (auto i : s1)
			for (auto j : s2) {
				try {
					auto res = i.intersect(j);
					if (res != err)
						ret.push_back(res);
				}
				catch (...) {}
			}
		return Convex(ret);
	}
};