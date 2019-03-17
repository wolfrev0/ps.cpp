#pragma once
#include "Line.h"

template<typename T>
struct Polygon
{
  vector<Vec2<T>> vtx;

  Polygon() {}
  explicit Polygon(int n) :vtx(n) {}
  explicit Polygon(const vector<Vec2<T>>& v) :vtx(v) {}
  int size()const { return vtx.size(); }
  void pushb(const Vec2<T>& v) { vtx.push_back(v); }
  void popb() { vtx.pop_back(); }
  Vec2<T>& operator[](int idx) { return vtx[idx]; }

  f64 area() {
    f64 ans = 0;
    forh(i, 1, size() - 1)
      ans += vtx[0].cross(vtx[i], vtx[i + 1]);
    return ans / 2;
  }

  vector<Segment<T>> to_segments()const {
    vector<Segment<T>> ret;
    forh(i, 0, vtx.size())
      ret.emplace_back(vtx[i], vtx[(i + 1) % vtx.size()]);
    return ret;
  }

  virtual bool contains(const Vec2<T>& v) const {
    auto arr = to_segments();
    for (auto i : arr)
      if (i.contains(v))
        return true;
    int cnt = 0;
    auto l = Segment<T>(v, v + Vec2<T>(prime, 1));
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

template<typename T>
struct Convex :public Polygon<T>{
  using Polygon<T>::vtx;
  using Polygon<T>::contains;
  using Polygon<T>::to_segments;
  Convex():Polygon<T>() {}
  explicit Convex(int n) :Polygon<T>(n) {}
  explicit Convex(const vector<Vec2<T>>& v) :Polygon<T>(v) { normalize(); }

  //graham scan
  void normalize() {
    if (vtx.empty())
      return;
    auto me = *min_element(vtx.begin(), vtx.end());
    sort(vtx.begin(), vtx.end(), [&](auto &a, auto &b){return Vec2<T>::cmpccw(a,b, me);});
    vector<Vec2<T>> res;
    forh(i, 0, vtx.size()) {
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

  virtual bool contains(const Vec2<T>& v)const override	{
    T tmp = v.cross(vtx[0], vtx[1]);
    forh(i, 0, vtx.size())
      if (tmp*v.cross(vtx[i], vtx[(i + 1) % vtx.size()]) <= 0)
        return false;
    return true;
  }

  virtual Polygon<T> intersect(const Polygon<T>& r)const override {
    vector<Vec2<T>> ret;
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
          Vec2<T> res;
          if (i.intersect(j, res))
            ret.push_back(res);
        }
        catch (...) {}
      }
    return Convex(ret);
  }
};