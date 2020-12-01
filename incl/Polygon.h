#pragma once
#include "Line.h"

template<class T>
struct Polygon{
	Arr<Vec2<T>> vtx;

	Polygon() {}
	explicit Polygon(int n) :vtx(n) {}
	explicit Polygon(const Arr<Vec2<T>>& v) :vtx(v) {}
	int size()const { return sz(vtx); }
	void pushb(const Vec2<T>& v) { vtx.pushb(v); }
	void eb() { vtx.eb(); }
	Vec2<T>& operator[](int idx) { return vtx[idx]; }

	f64 area() {
		f64 ans = 0;
		hfor(i, 1, size() - 1)
			ans += vtx[0].cross(vtx[i], vtx[i + 1]);
		return ans / 2;
	}

	Arr<Segment<T>> to_segments()const {
		Arr<Segment<T>> ret;
		hfor(i, 0, sz(vtx))
			ret.emplace_back(vtx[i], vtx[(i + 1) % sz(vtx)]);
		return ret;
	}

	virtual bool contains(const Vec2<T>& v) const {
		auto arr = to_segments();
		for (auto i : arr)
			if (i.contains(v))
				return true;
		int cnt = 0;
		auto l = Segment<T>(v, v + Vec2<T>(int(1e9+9), 1));
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

template<class T>
struct Convex :public Polygon<T>{
	using Polygon<T>::vtx;
	using Polygon<T>::contains;
	using Polygon<T>::to_segments;
	Convex():Polygon<T>() {}
	explicit Convex(int n) :Polygon<T>(n) {}
	explicit Convex(const Arr<Vec2<T>>& v) :Polygon<T>(v) { normalize(); }

	//graham scan
	void normalize() {
		if (vtx.empty())
			return;
		auto me = *min_element(all(vtx));
		sort(all(vtx), [&](auto &a, auto &b){return Vec2<T>::cmpccw(a,b,me);});
		Arr<Vec2<T>> res;
		hfor(i, 0, sz(vtx)) {
			while (sz(res) >= 2) {
				auto ltop = res[sz(res) - 1] - res[sz(res) - 2];
				auto lcandi = vtx[i] - res[sz(res) - 2];
				if (ltop.cross(lcandi) <= 0)
					res.popb();
				else
					break;
			}
			res.pushb(vtx[i]);
		}
		vtx = res;
	}

	virtual bool contains(const Vec2<T>& v)const override	{
		T tmp = v.cross(vtx[0], vtx[1]);
		hfor(i, 0, sz(vtx))
			if (tmp*v.cross(vtx[i], vtx[(i + 1) % sz(vtx)]) <= 0)
				return false;
		return true;
	}

	virtual Polygon<T> intersect(const Polygon<T>& r)const override {
		Arr<Vec2<T>> ret;
		for (auto i : vtx)
			if (r.contains(i))
				ret.pushb(i);
		for (auto i : r.vtx)
			if (contains(i))
				ret.pushb(i);
		auto s1 = to_segments();
		auto s2 = r.to_segments();
		for (auto i : s1)
			for (auto j : s2) {
				try {
					Vec2<T> res;
					if (i.intersect(j, res))
						ret.pushb(res);
				}
				catch (...) {}
			}
		return Convex(ret);
	}
};