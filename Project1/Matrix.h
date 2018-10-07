#pragma once
#include "Core.h"
#include "NumberTheory.h"

struct Mat
{
	using T = int;
	vector<vector<T>> arr;
	Mat(int r, int c) :arr(r)
	{
		for (auto &i : arr)
			i.resize(c);
	}
	Mat(int r, int c, vector<vector<T>> arr) :arr(arr) 
	{
		assert(arr.size() == r);
		for (auto &i : arr)
			assert(i.size() == c);
	}

	int r()const { return arr.size(); }
	int c()const { return arr[0].size(); }

	Mat operator*(const Mat &o)const
	{
		assert(c() == o.r());

		Mat ret(r(), o.c());
		forh(i, 0, r())
		{
			forh(j, 0, o.c())
			{
				forh(k, 0, c())
					ret.arr[i][j] += arr[i][k] * o.arr[k][j];
			}
		}
		return ret;
	}
};

struct SqMat : public Mat
{
	SqMat(int n) :Mat(n, n) {}
	explicit SqMat(const Mat &m) :Mat(m.r(), m.c(), m.arr) { assert(m.r() == m.c()); }

	int n()const { return r(); }

	SqMat id()
	{
		SqMat ret(n());
		forh(i, 0, n())
			ret.arr[i][i] = 1;
		return ret;
	}

	Mat operator*(const Mat &o)const { return Mat::operator*(o); }
	SqMat operator*(const SqMat &o)const { return SqMat(Mat::operator*(o)); }
};