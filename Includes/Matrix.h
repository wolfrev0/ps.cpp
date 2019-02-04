#pragma once
#include "Core.h"

template<typename T>
struct Mat
{
	vector<vector<T>> arr;
	explicit Mat(int r, int c) :arr(r, vector<T>(c)) {}
	explicit Mat(vector<vector<T>> arr) :arr(arr) {
		for (auto& i : arr)
			assert(i.size() == c());
	}
	Mat(const Mat& r) :arr(r.arr) {	}

	inline int r()const { return arr.size(); }
	inline int c()const { return arr[0].size(); }

	inline Mat operator*(const Mat& o)const {
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

	Mat transpose() const{
		Mat ret(r(), c());
		forh(i, 0, r()) {
			forh(j, 0, c()) {
				ret.arr[i][j]=arr[j][i];
			}
		}
		return ret;
	}

	Mat gaussian_elim()const{
		Mat ret(r(), c());
		return ret;
	}
};

template<typename T>
struct SqMat : public Mat<T>{
	explicit SqMat(int n) :Mat<T>(n, n) {}
	explicit SqMat(const Mat<T>& m) :Mat<T>(m) { assert(m.r() == m.c()); }

	inline int n()const { return Mat<T>::r(); }

	
	inline SqMat one() const {
		SqMat ret(n());
		forh(i, 0, n())
			ret.arr[i][i] = 1;
		return ret;
	}

	inline Mat<T> operator*(const Mat<T>& o)const { return Mat<T>::operator*(o); }
	inline SqMat operator*(const SqMat& o)const { return SqMat(Mat<T>::operator*(o)); }
};