#pragma once
#include "Core.h"

template<class T> struct Carr : public vector<T> {
	using P = vector<T>;
	Carr(int n = 0, T v = T()) : P(n, v) {}
	T& operator[](int idx) {
		return P::operator[]((idx % sz(*this) + sz(*this)) % sz(*this));
	}
};