#pragma once
#include "Core.h"

struct Mat
{
	using T = int;
	vector<vector<T>> arr;
	explicit Mat(int r, int c) :arr(r, vector<T>(c)) {}
	explicit Mat(vector<vector<T>> arr) :arr(arr) {
		for (auto &i : arr)
			assert(i.size() == c());
	}
	Mat(const Mat &r) :arr(r.arr) {	}

	inline int r()const { return arr.size(); }
	inline int c()const { return arr[0].size(); }

	inline Mat operator*(const Mat &o)const {
		assert(c() == o.r());

		Mat ret(r(), o.c());
		forh(i, 0, r()) {
			forh(j, 0, o.c()) {
				forh(k, 0, c())
					ret.arr[i][j] += arr[i][k] * o.arr[k][j];
			}
		}
		return ret;
	}
};

struct SqMat : public Mat
{
	explicit SqMat(int n) :Mat(n, n) {}
	explicit SqMat(const Mat &m) :Mat(m) { assert(m.r() == m.c()); }

	inline int n()const { return r(); }

	inline SqMat mulid() const {
		SqMat ret(n());
		forh(i, 0, n())
			ret.arr[i][i] = 1;
		return ret;
	}

	inline Mat operator*(const Mat &o)const { return Mat::operator*(o); }
	inline SqMat operator*(const SqMat &o)const { return SqMat(Mat::operator*(o)); }
};